/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vpscore_simcop.c
 *
 *  \brief This file implements functions for SIMCOP and its sub-modules.
 *
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
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

#include <ti/drv/vps/include/iss/vps_isscommon.h>

#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issldc.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issvtnf.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isssimcop.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_platform.h>

#include <ti/drv/vps/src/vpslib/isscore/vpscore_simcop.h>

/* ========================================================================== */
/*                           MISRA Violations WAIVER                          */
/* ========================================================================== */
/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 *
 * In this particular file, video frames are passed as an array of pointers.
 * At predetermined locations (offsets) a valid frame is pointed. Referred to as
 * streams. The top level function vcoreSimcopPutFrames() would be called to
 * provide frames to be processes, this function ensures all required frames are
 * indeed provided, before calling others functions to consume them.
 *
 * This is in violation of the MISRA C rule 17.1 / 17.4, which is marked with
 *  tag 'MISRA.PTR.ARITH 17.1/17.4 WAIVER'
 */

/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * Name 'frm'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Memory mapped registers and other hardware features access requires
 * typecasting of pointer to integer.  The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 *
 * In this particular file, video frames are passed as an array of pointers.
 * At predetermined locations (offsets) a valid frame is pointed. Referred to as
 * streams. The top level function vcoreSimcopPutFrames() would be called to
 * provide frames to be processes, this function ensures all required frames are
 * indeed provided, before calling others functions to consume them.
 * The HAL expects the absolute DDR address were frames are to be read from /
 * written to, hence this file converts the pointers to unsigned integers values
 *
 * This is in violation of the MISRA C rule 11.3, which is marked with
 *  tag 'MISRA.PTR.ARITH 11.3 WAIVER'
 */

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */
/** \brief Number of instances of SIMCOP present */
#define VPSCORE_SIMCOP_MAX_INST         (1U)

/** \brief Number of times simcop could be opened */
#define ISSCORE_SIMCOP_MAX_SW_HANDLES   (8U)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief Defines the various states that a frame requires to undergo, before
 *          a frame is processed. */
typedef enum vcoreSimcopFrameProcStates
{
    SIMCOP_FRAME_STATE_WAIT_4_PIPEUP_COMP = 0,
    /**< Wait for pipe up operation to complete */
    SIMCOP_FRAME_STATE_WAIT_4_STEADY_COMP = 1,
    /**< Wait for steady/repetative operation to complete */
    SIMCOP_FRAME_STATE_WAIT_4_PIPEDOWN_COMP = 2,
    /**< Wait for pipe down operation to complete */
    SIMCOP_FRAME_STATE_WAIT_4_FRAME_COMP = 3,
    /**< Wait for frame process operation to complete */
    SIMCOP_FRAME_STATE_INVALID = 4,
    /**< ISR reached invalid state */
    SIMCOP_FRAME_STATE_FORCE_INT = 0x7FFFFFFF
                                   /**< This will ensure enum is not packed,
                                    *will always be contained in int */
}vcoreSimcopFrameProcStates_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Handle object, defines a place holder for configuration for a given
 *          handle */
typedef struct vpscoreSimcopHndlObj
{
    uint32_t                     instId;
    /**< Instance ID of the SIMCOP instance on which this handle was opened */
    uint32_t                     mode;
    /**< Mode of operation for this handle #vcoreSimcopM2MMode_t */
    uint32_t                     hndlIndex;
    /**< Index into pHndlObjs in #vpscoreSimcopInstObj_t */
    vcoreSimcopFrameProcStates_t procSteps;
    /**< A frame would require mutiple steps to be processed, this var tracks
     *  the next expected state of the frame */
    vpsissSimcopCfgPrms_t        cfg;
    /**< Configuration for this handle */
    Ptr                          iemHandle;
    /**< Handle to event manager instance used */
    VpsCore_OpenPrms             openPrms;
    /**< Local copy of open parameters */
    uint32_t                     blockMultX10;
    /**< Block multiplier, the byte count written for each block depends on the
     *      data type. This would be calculated when the config is applied and
     *      reused subsequently.
     *      To avoid usage of floating variable, its always multiplied by 10.
     */
}vpscoreSimcopHndlObj_t;

/** \brief Instance object, that defines place holder for sub-module handle and
 *          other instance specifics */

typedef struct vpscoreSimcopInstObj
{
    vcoreSimcopInitParams_t initPrms;
    /**< HAL information */
    uint32_t                instId;
    /**< SIMCOP Core instance ID */
    VpsCore_Handle          pHndlObjs[ISSCORE_SIMCOP_MAX_SW_HANDLES];
    /**< Number of SW handles open on this SIMCOP instance */
    VpsHal_Handle           simcopHalHandle;
    /**< HAL handle to current SIMCOP instance */
    VpsHal_Handle           ldcHandle;
    /**< HAL handle to LDC in current SIMCOP instance */
    VpsHal_Handle           vtnfHandle;
    /**< HAL handle to VTNF in current SIMCOP instance */
    vpscoreSimcopHndlObj_t *pCurrHndl;
    /**< Used to determine if the configuration specified by the handle has to
     *      be applied or not.
     *  On the very first frame for a given handle, the config defined by the
     *      would be handle is applied.
     *  If there was no config change between two successive process frame
     *      calls config is not re-applied. */
    vpscoreSimcopHndlObj_t  hndlObjsPool[ISSCORE_SIMCOP_MAX_SW_HANDLES];
    /**< Pool of s/w handles */

    uint32_t                ldcOpenCnt;
    /**< Used to track number of times LDC mode is opened */
    uint32_t                vtnfOpenCnt;
    /**< Used to track number of times VTNF mode is opened */
    uint32_t                isRequestActive;
    /**< Flag to indicate if there is any active request,
     *   this is used to protect multiple request submission,
     *   core allows only one request to be processed at a time */
    vpscoreSimcopHndlObj_t *pActiveHndlObj;
    /**< Used to determine which handle has currently programmed / using the
            h/w */
    uint32_t                regIsr;
    /**< Flag that indicates if an ISR has been registered for this instance.
            If so, re-registration is not allowed. */
}vpscoreSimcopInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if typecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 *  vcoreSimcopOpen
 *  \brief Open one driver instance on specified SIMCOP instance
 *  Sets up SIMCOP private objects as per specified mode of operation
 *  TBD: Fix Prototype
 *
 *  \param numInst      TBD
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
VpsCore_Handle vcoreSimcopOpen(VpsCore_Inst            instId,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms);

/**
 *  vcoreSimcopClose
 *  \brief Close the specified handle
 *
 *  \param handle       Valid handle of type #VpsCore_Handle returned by
 *                      vcoreSimcopOpen
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreSimcopClose(VpsCore_Handle handle);

/**
 *  vcoreSimcopSetConfig
 *  \brief Set configuration for specified SIMCOP handle
 *
 *  \param params      Configuration of type #vpsissSimcopCfgPrms_t
 *  \param rsvd        Unused argument. Value is don't care.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreSimcopSetConfig(VpsCore_Handle handle,
                             const void    *params,
                             void          *rsvd);

/**
 *  vcoreSimcopControl
 *  \brief Function to get/set control commands
 *
 *  \param handle      core handle
 *  \param cmd         Command ID
 *  \param cmdArgs     Command Specific Arguments
 *  \param drvArgs     Driver specific arguments
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreSimcopControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs);

/**
 *  vcoreSimcopPutFrames
 *  \brief Sets up the SIMCOP to perform required operation.
 *
 *  \param handle   Handle returned by open API
 *  \param frm      Pointer to array if VpsCore_Frame pointer, depending on the
 *                  requested operation, one or more frames should be valid.
 *                  Buffer are identified from array indices as specified by
 *                  #vpsissSimcopStreamId
 *
 *  \return         Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreSimcopPutFrames(VpsCore_Handle  handle,
                             VpsCore_Frame **frm);

#ifdef __cplusplus
}
#endif

/**
 *  VpsCore_simcopInitObj
 *  \brief Private SIMCOP initialization function
 *  Initializes core objects for SIMCOP.
 *
 *  \param numInst      [IN] Instance of type #vpscoreSimcopInstObj_t to
 *                      be initialized
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
static int32_t VpsCore_simcopInitObj(vpscoreSimcopInstObj_t *pInstObj);

static void vcoreSimcopISR_ldcOnly(const UInt32 *event,
                                   UInt32        numEvents,
                                   Ptr           handle);
static void vcoreSimcopISR_vtnfOnly(const UInt32 *event,
                                    UInt32        numEvents,
                                    Ptr           handle);
static void vcoreSimcopISR_ldcVtnf(const UInt32 *event,
                                   UInt32        numEvents,
                                   Ptr           handle);
static void vcoreSetLdcAdvCfg(vpsissldcConfig_t *cfg);
static void vcoreFixUnsupportedLdcCfg(vpsissldcConfig_t *cfg);
static void vcoreSetVtnfAdvCfg(vpsissvtnfConfig_t *cfg);
static void vcoreFixUnsupportedVtnfCfg(vpsissvtnfConfig_t *cfg);
/**
 *  \brief Function to determine if the configured for YVU420 mode.
 */
static int32_t vcoreSimcopIs420P(const vpsissSimcopCfgPrms_t *pathCfg);
/**
 *  \brief Function to process frame in LDC only mode
 */
int32_t vcoreSimcopPutFrames_ldcOnly(VpsCore_Handle        handle,
                                     const VpsCore_Frame **frm);
/**
 *  \brief Function to process frame in VTNF only mode
 */
int32_t vcoreSimcopPutFrames_vtnfOnly(VpsCore_Handle        handle,
                                      const VpsCore_Frame **frm);
/**
 *  \brief Function to process frame in VTNF & LDC mode
 */
int32_t vcoreSimcopPutFrames_ldcVtnf(VpsCore_Handle        handle,
                                     const VpsCore_Frame **frm);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief SIMCOP Instance specific config / s/w states */
static vpscoreSimcopInstObj_t         gInstObjs[VPSCORE_SIMCOP_MAX_INST];

/** \brief Default DMA channel parameters for LDC + VTNF */
static isshalsimcopDmaChannelParams_t vcore_simcopDmaPrmsLdcVtnf[4] =
{
    {                                        /* Luma Cur Out    */
        ISSHAL_SIMCOP_DMA_CHAN_0,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0, /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_1,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Cur Out  */
        ISSHAL_SIMCOP_DMA_CHAN_1,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_2,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Luma Prev In    */
        ISSHAL_SIMCOP_DMA_CHAN_2,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_3,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Prev In  */
        ISSHAL_SIMCOP_DMA_CHAN_3,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0, /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_DISABLED,     /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
};

/** \brief Default HW Sequence parameters for LDC + VTNF */
static isshalsimcopHwSeqParams_t      vcore_LdcVtnfHwSeqPrms = \
{
    TRUE, /* useHwSeq  */
    0,    /* stepCnt   */
    0,    /* startStep */
    4,    /* numSteps  */
    {
        /* isshalsimcopHwSeqStepParams_t
         * stepParams[ISSHAL_SIMCOP_HW_SEQ_MAX_STEPS] */
        {
            1,                                      /* nextStep       */
            TRUE,                                   /* enableLdcSync  */
            FALSE,                                  /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_EFGHABCD,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_GH,  /* vtnfImBufMap  */
        },
        {
            2,                                      /* nextStep       */
            TRUE,                                   /* enableLdcSync  */
            TRUE,                                   /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_GHEF, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        },
        {
            3,                                      /* nextStep       */
            TRUE,                                   /* enableLdcSync  */
            TRUE,                                   /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_EFGHABCD,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_GH,  /* vtnfImBufMap  */
        },
        {
            2,                                      /* nextStep       */
            TRUE,                                   /* enableLdcSync  */
            TRUE,                                   /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_GHEF, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        }
    }
};

/** \brief Default DMA Channel config for LDC only */
static isshalsimcopDmaChannelParams_t vcore_simcopDmaPrmsLdcOnly[2] =
{
    {
        ISSHAL_SIMCOP_DMA_CHAN_0,               /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,     /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0,    /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_1,       /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS,    /* direction       */
        0,                                      /* blkWidth        */
        0,                                      /* blkHeight       */
        0,                                      /* numHorzBlks     */
        0,                                      /* numVertBlks     */
        0,                                      /* horzStep        */
        0,                                      /* vertStep        */
        0,                                      /* initX           */
        0,                                      /* initY           */
        NULL,                                   /* sysmemAddr      */
        0,                                      /* sysmemStride    */
        0x8000U,                                /* simcopmemAddr   */
        0                                       /* simcopmemStride */
    },
    {
        ISSHAL_SIMCOP_DMA_CHAN_1,               /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0,    /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,     /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_DISABLED,        /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS,    /* direction       */
        0,                                      /* blkWidth        */
        0,                                      /* blkHeight       */
        0,                                      /* numHorzBlks     */
        0,                                      /* numVertBlks     */
        0,                                      /* horzStep        */
        0,                                      /* vertStep        */
        0,                                      /* initX           */
        0,                                      /* initY           */
        NULL,                                   /* sysmemAddr      */
        0,                                      /* sysmemStride    */
        0x8000U,                                /* simcopmemAddr   */
        0                                       /* simcopmemStride */
    }
};

/** \brief Default HW Sequence parameters for LDC only */
static isshalsimcopHwSeqParams_t      vcore_LdcOnlyHwSeqPrms =
{
    (uint32_t)TRUE, /* useHwSeq  */
    11U,            /* stepCnt   */
    0U,             /* startStep */
    3U,             /* numSteps  */
    {
        /* isshalsimcopHwSeqStepParams_t
         * stepParams[ISSHAL_SIMCOP_HW_SEQ_MAX_STEPS] */
        {
            1,                                     /* nextStep       */
            TRUE,                                  /* enableLdcSync  */
            FALSE,                                 /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_DISABLED, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF, /* dmaOfst        */
            {                                      /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        },
        {
            2,                                      /* nextStep       */
            TRUE,                                   /* enableLdcSync  */
            FALSE,                                  /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_EFGHABCD,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_GHEF, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        },
        {
            1,                                      /* nextStep       */
            TRUE,                                   /* enableLdcSync  */
            FALSE,                                  /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        },
        {
            0,                                      /* nextStep       */
            TRUE,                                   /* enableLdcSync  */
            FALSE,                                  /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_LDC_O,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        }
    }
};

/** \brief Default DMA channel config for VTNF YUV420P only */
static isshalsimcopDmaChannelParams_t vcore_simcopDmaPrmsVtnfOnly_420p[8] =
{
    {                                        /* Luma Cur Out    */
        ISSHAL_SIMCOP_DMA_CHAN_0,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0, /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_1,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Cur Out - U */
        ISSHAL_SIMCOP_DMA_CHAN_1,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_2,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Cur Out - V */
        ISSHAL_SIMCOP_DMA_CHAN_2,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_3,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Luma Cur In     */
        ISSHAL_SIMCOP_DMA_CHAN_3,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_4,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x8000,                              /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Cur In   */
        ISSHAL_SIMCOP_DMA_CHAN_4,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_5,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x8000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Luma Prev In    */
        ISSHAL_SIMCOP_DMA_CHAN_5,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_6,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Prev In - U */
        ISSHAL_SIMCOP_DMA_CHAN_6,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_7,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Prev In - V */
        ISSHAL_SIMCOP_DMA_CHAN_7,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0, /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_DISABLED,     /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
};

/** \brief Default DMA channel config for VTNF  */
static isshalsimcopDmaChannelParams_t vcore_simcopDmaPrmsVtnfOnly[6] =
{
    {                                        /* Luma Cur Out    */
        ISSHAL_SIMCOP_DMA_CHAN_0,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0, /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_1,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Cur Out  */
        ISSHAL_SIMCOP_DMA_CHAN_1,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_2,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SIMCOP_TO_SYS, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Luma Cur In     */
        ISSHAL_SIMCOP_DMA_CHAN_2,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_3,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x8000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Cur In   */
        ISSHAL_SIMCOP_DMA_CHAN_3,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_4,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x8000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Luma Prev In    */
        ISSHAL_SIMCOP_DMA_CHAN_4,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_5,    /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
    {                                        /* Chroma Prev In  */
        ISSHAL_SIMCOP_DMA_CHAN_5,            /* channelNum      */
        ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0, /* hwStopChCtrl    */
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED,  /* hwStartChCtrl   */
        ISSHAL_SIMCOP_DMA_LINK_DISABLED,     /* nextChannel     */
        ISSHAL_SIMCOP_DMA_DIR_SYS_TO_SIMCOP, /* direction       */
        0,                                   /* blkWidth        */
        0,                                   /* blkHeight       */
        0,                                   /* numHorzBlks     */
        0,                                   /* numVertBlks     */
        0,                                   /* horzStep        */
        0,                                   /* vertStep        */
        0,                                   /* initX           */
        0,                                   /* initY           */
        NULL,                                /* sysmemAddr      */
        0,                                   /* sysmemStride    */
        0x9000U,                             /* simcopmemAddr   */
        0                                    /* simcopmemStride */
    },
};

/** \brief Default HW Sequence parameters for VTNF only */
static isshalsimcopHwSeqParams_t      vcore_VtnfOnlyHwSeqPrms =
{
    TRUE, /* useHwSeq  */
    0,    /* stepCnt   */
    0,    /* startStep */
    4,    /* numSteps  */
    {
        /* isshalsimcopHwSeqStepParams_t
         * stepParams[ISSHAL_SIMCOP_HW_SEQ_MAX_STEPS] */
        {
            1,                                      /* nextStep       */
            FALSE,                                  /* enableLdcSync  */
            FALSE,                                  /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_EFGHABCD,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_GH,  /* vtnfImBufMap  */
        },
        {
            2,                                      /* nextStep       */
            FALSE,                                  /* enableLdcSync  */
            TRUE,                                   /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        },
        {
            3,                                      /* nextStep       */
            FALSE,                                  /* enableLdcSync  */
            TRUE,                                   /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_EFGHABCD,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_GH,  /* vtnfImBufMap  */
        },
        {
            2,                                      /* nextStep       */
            FALSE,                                  /* enableLdcSync  */
            TRUE,                                   /* enableVtnfSync */
            ISSHAL_SIMCOP_HWSEQ_DMA_SYNC_CHANNEL_0, /* dmaSync        */
            ISSHAL_SIMCOP_HWSEQ_DMA_OFST_GHABCDEF,  /* dmaOfst        */
            {                                       /* imgMap[]       */
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_VTNF_IO,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA,
                ISSHAL_SIMCOP_HWSEQ_IMBUF_MAP_SIMCOP_DMA
            },
            ISSHAL_SIMCOP_HWSEQ_LDC_IMBUF_MAP_EFGH, /* ldcImBufMap   */
            ISSHAL_SIMCOP_HWSEQ_VTNF_IMBUF_MAP_EF,  /* vtnfImBufMap  */
        }
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** Returns the core operations
 */
const VpsCore_Ops *VpsCore_simcopGetCoreOps(void)
{
    /** \brief Capture core function pointers. */
    static const VpsCore_Ops gSimcopCoreOps =
    {
        NULL,                    /* Get property */
        &vcoreSimcopOpen,        /* Open function */
        &vcoreSimcopClose,       /* Close function */
        &vcoreSimcopSetConfig,   /* Set Params */
        NULL,                    /* Get Params */
        &vcoreSimcopControl,     /* Control */
        NULL,                    /* Start Required */
        NULL,                    /* Stop Required */
        NULL,                    /* Process */
        NULL,                    /* Core prog Buffer */
        &vcoreSimcopPutFrames,   /* Update the buffer and start */
        NULL,                    /* getFrames */
        NULL                     /* getErrorStat */
    };

    return (&gSimcopCoreOps);
}

/**
 *  VpsCore_simcopInit
 *  \brief SIMCOP core init function.
 *  Initializes core objects for all instances of SIMCOP.
 *  This function should be called before calling any of SIMCOP core API's.
 *
 *
 *  \param numInst      [IN] Number of SIMCOP instances to initialize
 *  \param initPrms     [IN] Array of type #vcoreSimcopInitParams_t and size
 *                      numInst containing init parameters with instance
 *                      numInst containing init parameters
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_simcopInit(uint32_t                       numInst,
                           const vcoreSimcopInitParams_t *initPrms,
                           Ptr                            arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t i;
    vpscoreSimcopInstObj_t     *pInstObj = NULL;
    vpshalissIspPlatformData_t *halPlt;

    /* Check for the null pointer */
    GT_assert(VpsIssCoreTrace, (NULL != initPrms));
    GT_assert(VpsIssCoreTrace, (VPSCORE_SIMCOP_MAX_INST >= numInst));
    GT_assert(VpsIssCoreTrace, (NULL != initPrms->halPlatformData));

    halPlt = (vpshalissIspPlatformData_t *) VpsHal_getIspPlatformData();
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'NULL == halPlt'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
    if(NULL == halPlt)
    {
        status = FVID2_EBADARGS;
    }

    /* Initialize HAL */
    if(FVID2_SOK == status)
    {
        status = VpsHal_issctrlInit(halPlt->issCtrlInitPrms, NULL);
    }

    /* Power up the simcop */
    VpsHal_issPowerCtrl(SUB_MODULE_SIMCOP, (uint32_t) TRUE);

    for(i = 0u; i < numInst; i++)
    {
        pInstObj = &gInstObjs[i];

        BspUtils_memset(
            pInstObj,
            0x0,
            sizeof(vpscoreSimcopInstObj_t));

        pInstObj->instId = i;

/* MISRA.PTR.ARITH
 * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
 * Name 'initParams'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer arithmetic is required for performance like auto increment in loop.
 * The harmful side effect of violating this rule (accessing outside valid
 *  memory) shall be checked by another code checker like klockwork
 */
        /* Copy the params */
        BspUtils_memcpy(
            &pInstObj->initPrms,
            &initPrms[i],
            sizeof(vcoreSimcopInitParams_t));

        status = VpsCore_simcopInitObj(pInstObj);
        if(FVID2_SOK != status)
        {
            break;
        }
    }

    return (status);
}

/**
 *  VpsCore_simcopInitObj
 *  \brief Private SIMCOP initialization function
 *  Initializes core objects for SIMCOP.
 *
 *  \param numInst      [IN] Instance of type #vpscoreSimcopInstObj_t to
 *                      be initialized
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
static int32_t VpsCore_simcopInitObj(vpscoreSimcopInstObj_t *pInstObj)
{
    uint32_t i;
    int32_t  status = FVID2_SOK;
    isshalsimcopOpenParams_t           simcopOpenPrms;
    vpshalissSimcopPlatformData_t     *halData;

    /** \brief SIMCOP DMA defaults, tuned for max performance */
    static vpsisssimcopDmaCtrlParams_t gInstDmaCfg[VPSCORE_SIMCOP_MAX_INST] =
    {
        {
            0x0,                                 /* bwLimit - no limit */
            0xF,                                 /* tagCnt - max*/
            0x0,                                 /* enablePostedWrite */
            VPS_ISS_SIMCOP_DMA_MAX_BURST_SIZE_3  /* maxBurstSize - max*/
        },
    };

    halData = (vpshalissSimcopPlatformData_t *)
              (pInstObj->initPrms.halPlatformData);

    for(i = 0; i < ISSCORE_SIMCOP_MAX_SW_HANDLES; i++)
    {
        pInstObj->pHndlObjs[i] = NULL;
    }

    if(BSP_SOK == status)
    {
        status =
            VpsHal_isssimcopInit(halData->numSimcop, halData->simcopInitPrms,
                                 NULL);
    }

    if(BSP_SOK == status)
    {
        if(FALSE == pInstObj->initPrms.isSimcopDmaCfgValid)
        {
            status = VpsHal_isssimcopCfgDma(pInstObj->instId, &gInstDmaCfg[0]);
        }
        else
        {
            status = VpsHal_isssimcopCfgDma(pInstObj->instId,
                                            &(pInstObj->initPrms.simcopDmaCfg));
        }
    }

    if(BSP_SOK == status)
    {
        status = VpsHal_issldcInit(halData->numSimcop, halData->ldcInitPrms,
                                   NULL);
    }

    if(BSP_SOK == status)
    {
        status = VpsHal_issvtnfInit(halData->numSimcop, halData->vtnfInitPrms,
                                    NULL);
    }

    if(BSP_SOK == status)
    {
        simcopOpenPrms.instId     = pInstObj->instId;
        pInstObj->simcopHalHandle = VpsHal_isssimcopOpen(&simcopOpenPrms, NULL);
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'NULL == pInstObj->simcopHalHandle'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
        if(NULL == pInstObj->simcopHalHandle)
        {
            status = BSP_EFAIL;
        }
    }

    return status;
}

/**
 *  VpsCore_simcopDeInit
 *  \brief This function closes all HAL handles & power down SIMCOP
 *
 *  \param numInst      [IN] Number of SIMCOP instances to initialize
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_simcopDeInit(uint32_t numInst)
{
    uint32_t i;
    int32_t  status = FVID2_EBADARGS;
    vpscoreSimcopInstObj_t *pInstObj = NULL;
    /*
        . Derive Instance object
        . DeInitiliaze VTNF HAL
        . DeInitialize LDC HAL
        . DeInitialize SIMCOP
        . Close SIMCOP Hal
        . Power down SIMCOP
        . DeInitialize ISS Control
    */
    if(VPSCORE_ISS_SIMCOP_INST_MAX >= numInst)
    {
        status = FVID2_SOK;
        for(i = 0u; ((i < numInst) && (FVID2_SOK == status)); i++)
        {
            status   = FVID2_EFAIL;
            pInstObj = &gInstObjs[i];
            GT_assert(VpsIssCoreTrace, (pInstObj->instId == i));

            status = VpsHal_issvtnfDeInit(NULL);

            if(FVID2_SOK == status)
            {
                status = VpsHal_issldcDeInit(NULL);
            }

            if((FVID2_SOK == status) && (NULL != pInstObj->simcopHalHandle))
            {
                /* ISS_TODO DeInit takes a simcop handle, should take an
                    instance identifier */
                /* This API also powers down LDC, VTNF and DMA */
                if(NULL != pInstObj->simcopHalHandle)
                {
                    status = VpsHal_isssimcopDeInit(pInstObj->simcopHalHandle,
                                                    NULL);
                }
                else
                {
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'NULL != pInstObj->simcopHalHandle'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
                    /* This condition should not occur */
                    GT_assert(VpsIssCoreTrace, FALSE);
                }
            }

            if(NULL != pInstObj->simcopHalHandle)
            {
                status = VpsHal_isssimcopClose(pInstObj->simcopHalHandle);
            }
            else
            {
                /* This condition should not occur */
                GT_assert(VpsIssCoreTrace, FALSE);
            }
        }

        if(FVID2_SOK == status)
        {
            /* For multiple instances of SIMCOP, this should be with in the
                loop above. */
            VpsHal_issPowerCtrl(SUB_MODULE_SIMCOP, (uint32_t) FALSE);

            status = VpsHal_issctrlDeInit(NULL);
        }
    }
    return (status);
}

/**
 *  vcoreSimcopClose
 *  \brief Close the specified handle
 *
 *  \param handle       Valid handle of type #VpsCore_Handle returned by
 *                      vcoreSimcopOpen
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreSimcopClose(VpsCore_Handle handle)
{
    int32_t  retVal = BSP_EFAIL;
    uint32_t hndlIndex;
    uint32_t instId, unRegIsr;
    vpscoreSimcopInstObj_t *pInstObj;
    vpscoreSimcopHndlObj_t *pHndlObj;

    if(NULL != handle)
    {
        unRegIsr = (uint32_t) FALSE;
        pHndlObj = (vpscoreSimcopHndlObj_t *) (handle);

        hndlIndex = pHndlObj->hndlIndex;

        instId = pHndlObj->instId;
        GT_assert(VpsIssCoreTrace, (VPSCORE_SIMCOP_MAX_INST > instId));
        pInstObj = &gInstObjs[instId];

        if(TRUE == pInstObj->isRequestActive)
        {
            if(NULL != pInstObj->pActiveHndlObj)
            {
                /* Trying to close while request is active */
                GT_assert(VpsIssCoreTrace, FALSE);
            }
        }

        if(NULL != pInstObj->pHndlObjs[hndlIndex])
        {
            pInstObj->pHndlObjs[hndlIndex] = NULL;
        }

        if(VPS_ISS_SIMCOP_LDC == pHndlObj->mode)
        {
            if (0U < pInstObj->ldcOpenCnt)
            {
                pInstObj->ldcOpenCnt--;
            }
        }
        else if(VPS_ISS_SIMCOP_VTNF == pHndlObj->mode)
        {
            if (0U < pInstObj->vtnfOpenCnt)
            {
                pInstObj->vtnfOpenCnt--;
            }
        }
        else /* LDC and VTNF Mode */
        {
            if (0U < pInstObj->vtnfOpenCnt)
            {
                pInstObj->vtnfOpenCnt--;
            }
            if (0U < pInstObj->ldcOpenCnt)
            {
                pInstObj->ldcOpenCnt--;
            }
        }

        if(0U == pInstObj->ldcOpenCnt)
        {
            if(pInstObj->ldcHandle != NULL)
            {
                VpsHal_issldcClose(pInstObj->ldcHandle);
                pInstObj->ldcHandle = NULL;
            }
            if(VPS_ISS_SIMCOP_LDC == pHndlObj->mode)
            {
                unRegIsr = (uint32_t) TRUE;
            }
        }

        if(0U == pInstObj->vtnfOpenCnt)
        {
            if(pInstObj->vtnfHandle != NULL)
            {
                VpsHal_issvtnfClose(pInstObj->vtnfHandle);
                pInstObj->vtnfHandle = NULL;
            }
            if(VPS_ISS_SIMCOP_VTNF == pHndlObj->mode)
            {
                unRegIsr = (uint32_t) TRUE;
            }
        }

        if((VPS_ISS_SIMCOP_LDC_VTNF == pHndlObj->mode) &&
           ((0U == pInstObj->vtnfOpenCnt) && (0U == pInstObj->ldcOpenCnt)))
        {
            unRegIsr = (uint32_t) TRUE;
        }

        if(TRUE == unRegIsr)
        {
            retVal           = Vps_iemUnRegister(pHndlObj->iemHandle);
            pInstObj->regIsr = (uint32_t) FALSE;
        }

        retVal = BSP_SOK;
    }
    return retVal;
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'coreOpenPrms' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */
/**
 *  vcoreSimcopOpen
 *  \brief Open one driver instance on specified SIMCOP instance
 *  Sets up SIMCOP private objects as per specified mode of operation
 *
 *  \param numInst      TBD
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
VpsCore_Handle vcoreSimcopOpen(VpsCore_Inst            instId,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms)
{
    int32_t                         status;
    uint32_t                        hndlIndex, i, inst;
    vpscoreSimcopInstObj_t         *pInstObj = NULL;
    vpscoreSimcopHndlObj_t         *pHndlObj = NULL;
    const vpsissSimcopOpenParams_t *simcopCoreOpenPrms;
    issemClientCbFxn                isrPtr = NULL;
    isshalldcOpenParams_t           ldcOpenPrms;
    isshalvtnfOpenParams_t          vtnfOpenPrms;

    GT_assert(VpsIssCoreTrace, (NULL != openPrms));
    GT_assert(VpsIssCoreTrace, (NULL != coreOpenPrms));

    /* We are using VpsCore_Inst as an instance identifier. Its better to use
        it as an pointer to instance. TBD */
    /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER
        Enum value is typecasted to pointer and it is accessed as uint32
        instance id
        Pointer is used here to make interface complience with the
        core interface */
    inst = (uint32_t) instId;

    if(VPSCORE_SIMCOP_MAX_INST > inst)
    {
        status   = BSP_SOK;
        pInstObj = &gInstObjs[inst];
/* MISRA.CAST.CONST
 * Rule 11.8: Cast operation removes const or volatile modifier from a pointer
 * or reference
 * Name 'simcopCoreOpenPrms'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Klocwork is not able to recognize cast is between constant pointer of one
 * type to constant pointer of another type.
 */
        simcopCoreOpenPrms = (const vpsissSimcopOpenParams_t *) coreOpenPrms;
    }
    else
    {
        status   = BSP_EFAIL;
        pInstObj = NULL;
        GT_assert(VpsIssCoreTrace, FALSE);
    }

    if(BSP_SOK == status)
    {
        if((NULL == pInstObj->ldcHandle) &&
           ((VPS_ISS_SIMCOP_LDC_VTNF == simcopCoreOpenPrms->mode) ||
            (VPS_ISS_SIMCOP_LDC == simcopCoreOpenPrms->mode)))
        {
            ldcOpenPrms.instId  = pInstObj->instId;
            pInstObj->ldcHandle = VpsHal_issldcOpen(&ldcOpenPrms);
            if(NULL == pInstObj->ldcHandle)
            {
                status = BSP_EFAIL;
            }
            else
            {
                pInstObj->ldcOpenCnt++;
            }
        }
    }

    if(BSP_SOK == status)
    {
        if((NULL == pInstObj->vtnfHandle) &&
           ((VPS_ISS_SIMCOP_LDC_VTNF == simcopCoreOpenPrms->mode) ||
            (VPS_ISS_SIMCOP_VTNF == simcopCoreOpenPrms->mode)))
        {
            vtnfOpenPrms.instId  = pInstObj->instId;
            pInstObj->vtnfHandle = VpsHal_issvtnfOpen(&vtnfOpenPrms);
            if(NULL == pInstObj->vtnfHandle)
            {
                status = BSP_EFAIL;
            }
            else
            {
                pInstObj->vtnfOpenCnt++;
            }
        }
    }

    if(BSP_SOK == status)
    {
        status = BSP_EFAIL;
        for(i = 0; ((i < ISSCORE_SIMCOP_MAX_SW_HANDLES) && (NULL != pInstObj));
            i++)
        {
            if(NULL == pInstObj->pHndlObjs[i])
            {
                status    = BSP_SOK;
                hndlIndex = i;
                break;
            }
        }

        if(BSP_SOK == status)
        {
            pInstObj->pHndlObjs[hndlIndex] = (VpsCore_Handle)
                                             & pInstObj->hndlObjsPool[hndlIndex
                                             ];
            pHndlObj = &pInstObj->hndlObjsPool[hndlIndex];
        }
    }

    if(BSP_SOK == status)
    {
        pHndlObj->instId    = inst;
        pHndlObj->hndlIndex = hndlIndex;
        pHndlObj->mode      = simcopCoreOpenPrms->mode;
        BspUtils_memcpy(&pHndlObj->openPrms,
                        openPrms,
                        sizeof(VpsCore_OpenPrms));

        /* Modes of operation cannot differ over different handle
            LIMITATION of having separate ISR for modes.
            Current envisioned usecases do not require different modes */
        if(FALSE == pInstObj->regIsr)
        {
            if(VPS_ISS_SIMCOP_LDC_VTNF == pHndlObj->mode)
            {
                isrPtr = &vcoreSimcopISR_ldcVtnf;
            }
            if(VPS_ISS_SIMCOP_LDC == pHndlObj->mode)
            {
                isrPtr = &vcoreSimcopISR_ldcOnly;
            }
            if(VPS_ISS_SIMCOP_VTNF == pHndlObj->mode)
            {
                isrPtr = &vcoreSimcopISR_vtnfOnly;
            }
            pHndlObj->iemHandle = Vps_iemregister(
                pInstObj->initPrms.irqNum,
                pInstObj->initPrms.eventGroup,
                &pInstObj->initPrms.eventNum,
                1u,
                IEM_PRIORITY4,
                isrPtr,
                (Ptr) pInstObj);
            GT_assert(VpsIssCoreTrace, (NULL != pHndlObj->iemHandle));
            if(NULL != pHndlObj->iemHandle)
            {
                pInstObj->pCurrHndl = NULL;
            }
            else
            {
                /* TODO TBD Release resources */

                pHndlObj = NULL;
            }
        }
    }

    if(BSP_SOK == status)
    {
        VpsHal_isssimcopSetLdcReadDmaCfg(
                    pInstObj->simcopHalHandle,
                    simcopCoreOpenPrms->ldcRdMaxTagCnt,
                    ISSHAL_SIMCOP_LDC_MAX_BURST_LEN_B128,
                    (uint32_t) FALSE);
    }

    return (VpsCore_Handle) (pHndlObj);
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'params' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */
/**
 *  vcoreSimcopSetConfig
 *  \brief Set configuration for specified SIMCOP handle
 *
 *  \param params      Configuration of type #vpsissSimcopCfgPrms_t
 *  \param rsvd        Unused argument. Value is don't care.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreSimcopSetConfig(VpsCore_Handle handle,
                             const void    *params,
                             void          *rsvd)
{
    int32_t status = BSP_EBADARGS;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpscoreSimcopInstObj_t *pInstObj;
    vpsissldcConfig_t      *locldcCfg;
    vpsissvtnfConfig_t     *locvtnfCfg;

    if(NULL != handle)
    {
        pHndlObj = (vpscoreSimcopHndlObj_t *) (handle);

        if(VPSCORE_SIMCOP_MAX_INST > pHndlObj->instId)
        {
            pInstObj = &gInstObjs[pHndlObj->instId];

            if(pHndlObj == pInstObj->pActiveHndlObj)
            {
                status = FVID2_EDEVICE_INUSE;
            }
            else
            {
                status = FVID2_SOK;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        BspUtils_memcpy(&(pHndlObj->cfg),
                        params,
                        sizeof(vpsissSimcopCfgPrms_t));

        if(VPS_ISS_SIMCOP_VTNF != pHndlObj->mode)
        {
            /* Update advCfg for LDC */
            locldcCfg = &(pHndlObj->cfg.ldcCfg);
            if(FALSE == locldcCfg->isAdvCfgValid)
            {
                vcoreSetLdcAdvCfg(locldcCfg);
                /* Force variables to supported modes only */
                vcoreFixUnsupportedLdcCfg(locldcCfg);
            }

            locldcCfg->advCfg.enableConstOutAddr = (uint32_t) TRUE;
        }

        if(VPS_ISS_SIMCOP_LDC != pHndlObj->mode)
        {
            /* Update advCfg for VTNF */
            locvtnfCfg = &(pHndlObj->cfg.vtnfCfg);
            if(FALSE == locvtnfCfg->isAdvCfgValid)
            {
                vcoreSetVtnfAdvCfg(locvtnfCfg);
            }
            /* Force variables to supported modes only */
            vcoreFixUnsupportedVtnfCfg(locvtnfCfg);
        }

        /* Config has been updated, ensure to apply this when the first frame is
         *  received to be processed */
        pInstObj = &gInstObjs[pHndlObj->instId];
        if(pInstObj->pCurrHndl == pHndlObj)
        {
            pInstObj->pCurrHndl = NULL;
        }
        status = BSP_SOK;
    }

    return status;
}

/**
 *  vcoreSimcopControl
 *  \brief Function to get/set control commands
 *
 *  \param handle      core handle
 *  \param cmd         Command ID
 *  \param cmdArgs     Command Specific Arguments
 *  \param drvArgs     Driver specific arguments
 *
 *  \return            TRUE on success
 *                     FALSE on Failure
 */
int32_t vcoreSimcopControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs)
{
    int32_t status = BSP_EBADARGS;
    uint32_t cnt;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpscoreSimcopInstObj_t *pInstObj;
    vpsissRoutingConfig_t *pStPriCfg;

    if(NULL != handle)
    {
        pHndlObj = (vpscoreSimcopHndlObj_t *) (handle);

        if(VPSCORE_SIMCOP_MAX_INST > pHndlObj->instId)
        {
            pInstObj = &gInstObjs[pHndlObj->instId];

            if(TRUE == pInstObj->isRequestActive)
            {
                status = FVID2_EDEVICE_INUSE;
            }
            else
            {
                status = FVID2_SOK;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        switch (cmd)
        {
            case VPS_ISS_SIMCOP_IOCTL_STREAM_ROUTING:
                pStPriCfg = (vpsissRoutingConfig_t*)appArgs;

                for (cnt = 0U;cnt < pStPriCfg->numStreams;cnt++)
                {
                    status = VpsHal_issSetInitiatorPriority(
                                    pStPriCfg->source[cnt],
                                    pStPriCfg->priority[cnt],
                                    pStPriCfg->cportId[cnt]);
                }

                break;

            default:
                break;
        }
    }

    return status;
}

static int32_t vcoreSimcopIs420P(const vpsissSimcopCfgPrms_t *pathCfg)
{
    int32_t retVal = (int32_t) TRUE;
    if((FVID2_DF_YUV420SP_UV == pathCfg->vtnfCfg.outDataFormat) ||
       (FVID2_DF_YUV420SP_VU == pathCfg->vtnfCfg.outDataFormat))
    {
        retVal = (int32_t) FALSE;
    }
    return retVal;
}

static void vcoreSimcopISR_ldcVtnf(const UInt32 *event,
                                   UInt32        numEvents,
                                   Ptr           handle)
{
    uint32_t i, pipeSteadyStateCount, cookie;
    int32_t  retVal = BSP_SOK;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpsissSimcopCfgPrms_t  *pathCfg;
    vpscoreSimcopInstObj_t *pInstObj;

    GT_assert(VpsIssCoreTrace, (NULL != handle));
    GT_assert(VpsIssCoreTrace, (NULL != event));

    pInstObj = (vpscoreSimcopInstObj_t *)(handle);
    GT_assert(VpsIssCoreTrace, (NULL != pInstObj->pActiveHndlObj));
    GT_assert(VpsIssCoreTrace, (FALSE != pInstObj->isRequestActive));
    pHndlObj = pInstObj->pActiveHndlObj;
    pathCfg  = &(pHndlObj->cfg);

    if(*event != pInstObj->initPrms.eventNum)
    {
        retVal = BSP_EFAIL;
    }

    if((SIMCOP_FRAME_STATE_WAIT_4_PIPEUP_COMP == pHndlObj->procSteps) &&
       (BSP_SOK == retVal))
    {
        vcore_simcopDmaPrmsLdcVtnf[0].blkWidth  = (pathCfg->blkWidth >> 4);
        vcore_simcopDmaPrmsLdcVtnf[0].blkHeight = pathCfg->blkHeight;
        vcore_simcopDmaPrmsLdcVtnf[1].blkWidth  = (pathCfg->blkWidth >> 4);
        vcore_simcopDmaPrmsLdcVtnf[1].blkHeight = pathCfg->blkHeight / 2;
        for(i = 0; i < 2U; i++)
        {
            vcore_simcopDmaPrmsLdcVtnf[i].horzStep =
                vcore_simcopDmaPrmsLdcVtnf[i].blkWidth;
            vcore_simcopDmaPrmsLdcVtnf[i].vertStep =
                vcore_simcopDmaPrmsLdcVtnf[i].blkHeight;
            vcore_simcopDmaPrmsLdcVtnf[i].simcopmemStride =
                (vcore_simcopDmaPrmsLdcVtnf[i].blkWidth << 4);
        }
        for(i = 0; i < 2U; i++)
        {
            VpsHal_isssimcopDmaSetChannelConfig(pInstObj->simcopHalHandle,
                                                &vcore_simcopDmaPrmsLdcVtnf[i]);
        }
        pipeSteadyStateCount =
            ((pathCfg->inFrameWidth / pathCfg->blkWidth) *
             (pathCfg->inFrameHeight / pathCfg->blkHeight)) - 2U;
        vcore_LdcVtnfHwSeqPrms.startStep = 2;
        vcore_LdcVtnfHwSeqPrms.stepCnt   = pipeSteadyStateCount;
        VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                       &vcore_LdcVtnfHwSeqPrms);
        VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_STEADY_COMP;
    }
    else if((SIMCOP_FRAME_STATE_WAIT_4_STEADY_COMP == pHndlObj->procSteps) &&
            (BSP_SOK == retVal))
    {
        vcore_simcopDmaPrmsLdcVtnf[1].hwStopChCtrl =
            ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0;
        vcore_simcopDmaPrmsLdcVtnf[1].nextChannel =
            ISSHAL_SIMCOP_DMA_LINK_DISABLED;
        vcore_simcopDmaPrmsLdcVtnf[0].initX =
            vcore_simcopDmaPrmsLdcVtnf[0].numHorzBlks - 2;
        vcore_simcopDmaPrmsLdcVtnf[0].initY =
            vcore_simcopDmaPrmsLdcVtnf[0].numVertBlks - 1;
        vcore_simcopDmaPrmsLdcVtnf[1].initX =
            vcore_simcopDmaPrmsLdcVtnf[1].numHorzBlks - 2;
        vcore_simcopDmaPrmsLdcVtnf[1].initY =
            vcore_simcopDmaPrmsLdcVtnf[1].numVertBlks - 1;
        for(i = 0; i < 2U; i++)
        {
            VpsHal_isssimcopDmaSetChannelConfig(pInstObj->simcopHalHandle,
                                                &vcore_simcopDmaPrmsLdcVtnf[i]);
        }
        pipeSteadyStateCount =
            ((pathCfg->inFrameWidth / pathCfg->blkWidth) *
             (pathCfg->inFrameHeight / pathCfg->blkHeight)) - 2U;
        vcore_LdcVtnfHwSeqPrms.startStep = 2U + (pipeSteadyStateCount & 1U);
        vcore_LdcVtnfHwSeqPrms.stepCnt   = 2U;
        vcore_LdcVtnfHwSeqPrms.stepParams[2].enableLdcSync = (uint32_t) FALSE;
        vcore_LdcVtnfHwSeqPrms.stepParams[3].enableLdcSync = (uint32_t) FALSE;
        VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                       &vcore_LdcVtnfHwSeqPrms);
        VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_PIPEDOWN_COMP;
    }
    else if((SIMCOP_FRAME_STATE_WAIT_4_PIPEDOWN_COMP ==
             pHndlObj->procSteps) &&
            (BSP_SOK == retVal))
    {
        cookie = BspOsal_disableInterrupt();
        pInstObj->isRequestActive = (uint32_t) FALSE;
        pInstObj->pActiveHndlObj  = NULL;
        BspOsal_restoreInterrupt(cookie);

        VpsHal_issldcStop(pInstObj->ldcHandle);
        if(NULL != pHndlObj->openPrms.frmDoneNotifyCb)
        {
            /* Call the calback of the upper layer */
            pHndlObj->openPrms.frmDoneNotifyCb(pHndlObj->openPrms.drvData);
        }
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_FRAME_COMP;
    }
    else
    {
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_INVALID;
    }
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'frm' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */
int32_t vcoreSimcopPutFrames_ldcVtnf(VpsCore_Handle        handle,
                                     const VpsCore_Frame **frm)
{
    uint32_t i;
    int32_t  retVal;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpsissSimcopCfgPrms_t  *pathCfg;
    vpscoreSimcopInstObj_t *pInstObj;

    pHndlObj = (vpscoreSimcopHndlObj_t *) (handle);
    pInstObj = &gInstObjs[pHndlObj->instId];
    pathCfg  = &(pHndlObj->cfg);

    /* TODO TBD Guard against re-config of LDC / VTNF / DMA when the config has
     *  not been updated between two consecutive frames */
    pInstObj->pCurrHndl = (vpscoreSimcopHndlObj_t *) handle;

    /* LDC  */
    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
    if(NULL != frm[VPS_SIMCOP_STREAM_ID_MESH_TABLE])
    {
        pathCfg->ldcCfg.lutCfg.address =
            (uint32_t) frm[VPS_SIMCOP_STREAM_ID_MESH_TABLE]->addr[0][0];
    }

    GT_assert(VpsIssCoreTrace, (NULL != pathCfg->ldcCfg.lutCfg.address));
    retVal = VpsHal_issldcSetConfig(pInstObj->ldcHandle,
                                    &pathCfg->ldcCfg,
                                    NULL);
    if(retVal != BSP_SOK)
    {
        Bsp_printf("Error\n");
    }

    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    GT_assert(VpsIssCoreTrace,
              (NULL != frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][0]));
    if(VPS_ISS_LDC_MODE_YUV420_LDC == pathCfg->ldcCfg.mode)
    {
        GT_assert(VpsIssCoreTrace,
                  (NULL != frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][1]));
    }

    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
    retVal += VpsHal_issldcSetInFrameAddress(
        pInstObj->ldcHandle,
        pathCfg->ldcCfg.mode,
        (uint32_t)frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][0],
        (uint32_t)frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][1],
        pathCfg->inpFrmPitch);

    if(VPS_ISS_LDC_MODE_YUV420_LDC == pathCfg->ldcCfg.mode)
    {
        retVal += VpsHal_issldcSetOutFrameAddress(
            pInstObj->ldcHandle,
            pathCfg->ldcCfg.mode,
            0U,
            0U + (pathCfg->blkWidth * pathCfg->blkHeight),
            pathCfg->blkWidth);
    }
    else
    {
        Bsp_printf("Error\n");
    }

    /* TBD check second arg */
    VpsHal_issldcStart(pInstObj->ldcHandle, ISSHAL_ISS_PROC_MODE_FREE_RUN, NULL);

    /* VTNF */
    retVal += VpsHal_issvtnfSetConfig(pInstObj->vtnfHandle,
                                      &pathCfg->vtnfCfg, NULL);
    if(retVal == BSP_SOK)
    {
        retVal = VpsHal_issvtnfSetAddress(pInstObj->vtnfHandle, /* handle     */
                                          (Ptr) 0x0000,         /* inAddr     */
                                          (Ptr) 0x1000,         /* prevInAddr */
                                          (Ptr) 0x1000,         /* outAddr    */
                                          pathCfg->blkWidth     /* lineOffset */
                                          );
    }
    if(retVal == BSP_SOK)
    {
        VpsHal_issvtnfStart(pInstObj->vtnfHandle);
    }

    /* SIMCOP DMA */
    for(i = 0; i < 4U; i++)
    {
        vcore_simcopDmaPrmsLdcVtnf[i].numHorzBlks =
            (pathCfg->inFrameWidth / pathCfg->blkWidth);
        vcore_simcopDmaPrmsLdcVtnf[i].numVertBlks =
            (pathCfg->inFrameHeight / pathCfg->blkHeight);
    }

    if(vcoreSimcopIs420P(pathCfg))
    {
        Bsp_printf("Error!\r\n");
    }

    /* Current output */
    vcore_simcopDmaPrmsLdcVtnf[0].blkWidth  = (pathCfg->blkWidth >> 4);
    vcore_simcopDmaPrmsLdcVtnf[0].blkHeight = pathCfg->blkHeight;
    vcore_simcopDmaPrmsLdcVtnf[1].blkWidth  = (pathCfg->blkWidth >> 4);
    vcore_simcopDmaPrmsLdcVtnf[1].blkHeight = pathCfg->blkHeight / 2;
    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
    vcore_simcopDmaPrmsLdcVtnf[0].sysmemAddr =
        frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][0];
    vcore_simcopDmaPrmsLdcVtnf[1].sysmemAddr =
        frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][1];
    vcore_simcopDmaPrmsLdcVtnf[0].simcopmemAddr = 0x9000U;
    vcore_simcopDmaPrmsLdcVtnf[1].simcopmemAddr =
        (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight));
    vcore_simcopDmaPrmsLdcVtnf[0].sysmemStride = pathCfg->outFrmPitch;
    vcore_simcopDmaPrmsLdcVtnf[1].sysmemStride = pathCfg->outFrmPitch;

    /* Prev input */
    vcore_simcopDmaPrmsLdcVtnf[2].blkWidth  = (pathCfg->blkWidth >> 4);
    vcore_simcopDmaPrmsLdcVtnf[2].blkHeight = pathCfg->blkHeight;
    vcore_simcopDmaPrmsLdcVtnf[3].blkWidth  = (pathCfg->blkWidth >> 4);
    vcore_simcopDmaPrmsLdcVtnf[3].blkHeight = pathCfg->blkHeight / 2;
    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
    vcore_simcopDmaPrmsLdcVtnf[2].sysmemAddr =
        frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME]->addr[0][0];
    vcore_simcopDmaPrmsLdcVtnf[2].simcopmemAddr = 0x9000U;
    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
    vcore_simcopDmaPrmsLdcVtnf[3].sysmemAddr =
        frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME]->addr[0][1];
    vcore_simcopDmaPrmsLdcVtnf[3].simcopmemAddr =
        (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight));
    vcore_simcopDmaPrmsLdcVtnf[2].sysmemStride = pathCfg->prevFrmPitch;
    vcore_simcopDmaPrmsLdcVtnf[3].sysmemStride = pathCfg->prevFrmPitch;

    for(i = 0; i < 4U; i++)
    {
        vcore_simcopDmaPrmsLdcVtnf[i].horzStep =
            vcore_simcopDmaPrmsLdcVtnf[i].blkWidth;
        vcore_simcopDmaPrmsLdcVtnf[i].vertStep =
            vcore_simcopDmaPrmsLdcVtnf[i].blkHeight;
        vcore_simcopDmaPrmsLdcVtnf[i].simcopmemStride =
            (vcore_simcopDmaPrmsLdcVtnf[i].blkWidth << 4);
        vcore_simcopDmaPrmsLdcVtnf[i].initX = 0;
        vcore_simcopDmaPrmsLdcVtnf[i].initY = 0;
    }

    vcore_simcopDmaPrmsLdcVtnf[1].hwStopChCtrl =
        ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED;
    vcore_simcopDmaPrmsLdcVtnf[1].nextChannel =
        ISSHAL_SIMCOP_DMA_LINK_CHANNEL_2;

    for(i = 0; i < 4U; i++)
    {
        VpsHal_isssimcopDmaSetChannelConfig(pInstObj->simcopHalHandle,
                                            &vcore_simcopDmaPrmsLdcVtnf[i]);
    }

    for(i = 0; i < 4U; i++)
    {
        vcore_LdcVtnfHwSeqPrms.stepParams[i].enableLdcSync = (uint32_t) TRUE;
    }

    vcore_LdcVtnfHwSeqPrms.startStep = 0;
    vcore_LdcVtnfHwSeqPrms.stepCnt   = 2;
    VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                   &vcore_LdcVtnfHwSeqPrms);
    pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_PIPEUP_COMP;
    VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);

    return retVal;
}

static void vcoreSimcopISR_vtnfOnly(const UInt32 *event,
                                    UInt32        numEvents,
                                    Ptr           handle)
{
    uint32_t i, pipeSteadyStateCount, cookie;
    int32_t  retVal = BSP_SOK;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpsissSimcopCfgPrms_t  *pathCfg;
    vpscoreSimcopInstObj_t *pInstObj;

    GT_assert(VpsIssCoreTrace, (NULL != handle));
    GT_assert(VpsIssCoreTrace, (NULL != event));

    pInstObj = (vpscoreSimcopInstObj_t *)(handle);
    GT_assert(VpsIssCoreTrace, (NULL != pInstObj->pActiveHndlObj));
    GT_assert(VpsIssCoreTrace, (FALSE != pInstObj->isRequestActive));
    pHndlObj = pInstObj->pActiveHndlObj;
    pathCfg  = &(pHndlObj->cfg);

    if(*event != pInstObj->initPrms.eventNum)
    {
        retVal = BSP_EFAIL;
    }

    if((SIMCOP_FRAME_STATE_WAIT_4_PIPEUP_COMP == pHndlObj->procSteps) &&
       (BSP_SOK == retVal))
    {
        if(vcoreSimcopIs420P(pathCfg))
        {
            vcore_simcopDmaPrmsVtnfOnly_420p[0].blkWidth =
                (pathCfg->blkWidth >> 4);
            vcore_simcopDmaPrmsVtnfOnly_420p[0].blkHeight =
                pathCfg->blkHeight;
            vcore_simcopDmaPrmsVtnfOnly_420p[1].blkWidth =
                (pathCfg->blkWidth >> 5);
            vcore_simcopDmaPrmsVtnfOnly_420p[1].blkHeight =
                pathCfg->blkHeight / 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[2].blkWidth =
                (pathCfg->blkWidth >> 5);
            vcore_simcopDmaPrmsVtnfOnly_420p[2].blkHeight =
                pathCfg->blkHeight / 2;
            for(i = 0; i < 3U; i++)
            {
                vcore_simcopDmaPrmsVtnfOnly_420p[i].horzStep =
                    vcore_simcopDmaPrmsVtnfOnly_420p[i].blkWidth;
                vcore_simcopDmaPrmsVtnfOnly_420p[i].vertStep =
                    vcore_simcopDmaPrmsVtnfOnly_420p[i].blkHeight;
                vcore_simcopDmaPrmsVtnfOnly_420p[i].simcopmemStride =
                    (vcore_simcopDmaPrmsVtnfOnly_420p[i].blkWidth << 4);
            }
            for(i = 0; i < 3U; i++)
            {
                VpsHal_isssimcopDmaSetChannelConfig(
                    pInstObj->simcopHalHandle,
                    &vcore_simcopDmaPrmsVtnfOnly_420p[i]);
            }
        }
        else
        {
            vcore_simcopDmaPrmsVtnfOnly[0].blkWidth  = (pathCfg->blkWidth >> 4);
            vcore_simcopDmaPrmsVtnfOnly[0].blkHeight = pathCfg->blkHeight;
            vcore_simcopDmaPrmsVtnfOnly[1].blkWidth  = (pathCfg->blkWidth >> 4);
            vcore_simcopDmaPrmsVtnfOnly[1].blkHeight = pathCfg->blkHeight / 2;
            for(i = 0; i < 2U; i++)
            {
                vcore_simcopDmaPrmsVtnfOnly[i].horzStep =
                    vcore_simcopDmaPrmsVtnfOnly[i].blkWidth;
                vcore_simcopDmaPrmsVtnfOnly[i].vertStep =
                    vcore_simcopDmaPrmsVtnfOnly[i].blkHeight;
                vcore_simcopDmaPrmsVtnfOnly[i].simcopmemStride =
                    (vcore_simcopDmaPrmsVtnfOnly[i].blkWidth << 4);
            }
            for(i = 0; i < 2U; i++)
            {
                VpsHal_isssimcopDmaSetChannelConfig(
                    pInstObj->simcopHalHandle,
                    &vcore_simcopDmaPrmsVtnfOnly[i]);
            }
        }

        pipeSteadyStateCount =
            ((pathCfg->inFrameWidth / pathCfg->blkWidth) *
             (pathCfg->inFrameHeight / pathCfg->blkHeight)) - 2U;
        vcore_VtnfOnlyHwSeqPrms.startStep = 2;
        vcore_VtnfOnlyHwSeqPrms.stepCnt   = pipeSteadyStateCount;
        VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                       &vcore_VtnfOnlyHwSeqPrms);
        VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_STEADY_COMP;
    }
    else if((SIMCOP_FRAME_STATE_WAIT_4_STEADY_COMP == pHndlObj->procSteps) &&
            (BSP_SOK == retVal))
    {
        if(vcoreSimcopIs420P(pathCfg))
        {
            vcore_simcopDmaPrmsVtnfOnly_420p[2].hwStopChCtrl =
                ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0;
            vcore_simcopDmaPrmsVtnfOnly_420p[2].nextChannel =
                ISSHAL_SIMCOP_DMA_LINK_DISABLED;
            vcore_simcopDmaPrmsVtnfOnly_420p[0].initX =
                vcore_simcopDmaPrmsVtnfOnly_420p[0].numHorzBlks - 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[0].initY =
                vcore_simcopDmaPrmsVtnfOnly_420p[0].numVertBlks - 1;
            vcore_simcopDmaPrmsVtnfOnly_420p[1].initX =
                vcore_simcopDmaPrmsVtnfOnly_420p[1].numHorzBlks - 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[1].initY =
                vcore_simcopDmaPrmsVtnfOnly_420p[1].numVertBlks - 1;
            vcore_simcopDmaPrmsVtnfOnly_420p[2].initX =
                vcore_simcopDmaPrmsVtnfOnly_420p[2].numHorzBlks - 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[2].initY =
                vcore_simcopDmaPrmsVtnfOnly_420p[2].numVertBlks - 1;
            for(i = 0; i < 3U; i++)
            {
                VpsHal_isssimcopDmaSetChannelConfig(
                    pInstObj->simcopHalHandle,
                    &(vcore_simcopDmaPrmsVtnfOnly_420p[i]));
            }
        }
        else
        {
            vcore_simcopDmaPrmsVtnfOnly[1].hwStopChCtrl =
                ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0;
            vcore_simcopDmaPrmsVtnfOnly[1].nextChannel =
                ISSHAL_SIMCOP_DMA_LINK_DISABLED;
            vcore_simcopDmaPrmsVtnfOnly[0].initX =
                vcore_simcopDmaPrmsVtnfOnly[0].numHorzBlks - 2;
            vcore_simcopDmaPrmsVtnfOnly[0].initY =
                vcore_simcopDmaPrmsVtnfOnly[0].numVertBlks - 1;
            vcore_simcopDmaPrmsVtnfOnly[1].initX =
                vcore_simcopDmaPrmsVtnfOnly[1].numHorzBlks - 2;
            vcore_simcopDmaPrmsVtnfOnly[1].initY =
                vcore_simcopDmaPrmsVtnfOnly[1].numVertBlks - 1;
            for(i = 0; i < 2U; i++)
            {
                VpsHal_isssimcopDmaSetChannelConfig(
                    pInstObj->simcopHalHandle,
                    &
                    vcore_simcopDmaPrmsVtnfOnly[i]);
            }
        }

        pipeSteadyStateCount =
            ((pathCfg->inFrameWidth / pathCfg->blkWidth) *
             (pathCfg->inFrameHeight / pathCfg->blkHeight)) - 2U;
        vcore_VtnfOnlyHwSeqPrms.startStep = 2U + (pipeSteadyStateCount & 1U);
        vcore_VtnfOnlyHwSeqPrms.stepCnt   = 2U;
        VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                       &vcore_VtnfOnlyHwSeqPrms);
        VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_PIPEDOWN_COMP;
    }
    else if((SIMCOP_FRAME_STATE_WAIT_4_PIPEDOWN_COMP ==
             pHndlObj->procSteps) &&
            (BSP_SOK == retVal))
    {
        cookie = BspOsal_disableInterrupt();
        pInstObj->isRequestActive = (uint32_t) FALSE;
        pInstObj->pActiveHndlObj  = NULL;
        BspOsal_restoreInterrupt(cookie);

        if(NULL != pHndlObj->openPrms.frmDoneNotifyCb)
        {
            /* Call the calback of the upper layer */
            pHndlObj->openPrms.frmDoneNotifyCb(pHndlObj->openPrms.drvData);
        }
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_FRAME_COMP;
    }
    else
    {
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_INVALID;
    }
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'frm' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */
int32_t vcoreSimcopPutFrames_vtnfOnly(VpsCore_Handle        handle,
                                      const VpsCore_Frame **frm)
{
    uint32_t i;
    int32_t  retVal, applyConfig;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpsissSimcopCfgPrms_t  *pathCfg;
    vpscoreSimcopInstObj_t *pInstObj;

    pHndlObj = (vpscoreSimcopHndlObj_t *) (handle);
    pInstObj = &gInstObjs[pHndlObj->instId];
    pathCfg  = &(pHndlObj->cfg);

    retVal      = BSP_SOK;
    applyConfig = (int32_t) FALSE;
    if(pInstObj->pCurrHndl != pHndlObj)
    {
        applyConfig         = (int32_t) TRUE;
        pInstObj->pCurrHndl = pHndlObj;
        retVal = VpsHal_issvtnfSetConfig(pInstObj->vtnfHandle,
                                         &pathCfg->vtnfCfg, NULL);
    }
    if((retVal == BSP_SOK) && ((int32_t) TRUE == applyConfig))
    {
        retVal = VpsHal_issvtnfSetAddress(pInstObj->vtnfHandle, /* handle     */
                                          (Ptr) 0x0000,         /* inAddr     */
                                          (Ptr) 0x1000,         /* prevInAddr */
                                          (Ptr) 0x1000,         /* outAddr    */
                                          pathCfg->blkWidth     /* lineOffset */
                                          );
    }
    if(retVal == BSP_SOK)
    {
        VpsHal_issvtnfStart(pInstObj->vtnfHandle);
    }

    if(vcoreSimcopIs420P(pathCfg))
    {
        vcore_simcopDmaPrmsVtnfOnly_420p[2].hwStopChCtrl =
            ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED;
        vcore_simcopDmaPrmsVtnfOnly_420p[2].nextChannel =
            ISSHAL_SIMCOP_DMA_LINK_CHANNEL_3;

        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
        vcore_simcopDmaPrmsVtnfOnly_420p[0].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][0];
        vcore_simcopDmaPrmsVtnfOnly_420p[1].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][1];
        vcore_simcopDmaPrmsVtnfOnly_420p[2].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][2];

        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
        vcore_simcopDmaPrmsVtnfOnly_420p[3].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][0];
        vcore_simcopDmaPrmsVtnfOnly_420p[4].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][1];

        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
        vcore_simcopDmaPrmsVtnfOnly_420p[5].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME]->addr[0][0];
        vcore_simcopDmaPrmsVtnfOnly_420p[6].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME]->addr[0][1];
        vcore_simcopDmaPrmsVtnfOnly_420p[7].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME]->addr[0][2];

        for(i = 0; i < 8U; i++)
        {
            vcore_simcopDmaPrmsVtnfOnly_420p[i].initX = 0;
            vcore_simcopDmaPrmsVtnfOnly_420p[i].initY = 0;
        }
        if((int32_t)TRUE == applyConfig)
        {
            for(i = 0; i < 8U; i++)
            {
                vcore_simcopDmaPrmsVtnfOnly_420p[i].numHorzBlks =
                    (pathCfg->inFrameWidth / pathCfg->blkWidth);
                vcore_simcopDmaPrmsVtnfOnly_420p[i].numVertBlks =
                    (pathCfg->inFrameHeight / pathCfg->blkHeight);
            }

            vcore_simcopDmaPrmsVtnfOnly_420p[0].blkWidth =
                pathCfg->blkWidth >> 4;
            vcore_simcopDmaPrmsVtnfOnly_420p[0].blkHeight =
                pathCfg->blkHeight;
            vcore_simcopDmaPrmsVtnfOnly_420p[1].blkWidth =
                pathCfg->blkWidth >> 5;
            vcore_simcopDmaPrmsVtnfOnly_420p[1].blkHeight =
                pathCfg->blkHeight / 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[2].blkWidth =
                pathCfg->blkWidth >> 5;
            vcore_simcopDmaPrmsVtnfOnly_420p[2].blkHeight =
                pathCfg->blkHeight / 2;

            vcore_simcopDmaPrmsVtnfOnly_420p[3].blkWidth =
                pathCfg->blkWidth >> 4;
            vcore_simcopDmaPrmsVtnfOnly_420p[3].blkHeight =
                pathCfg->blkHeight;
            vcore_simcopDmaPrmsVtnfOnly_420p[4].blkWidth =
                pathCfg->blkWidth >> 4;
            vcore_simcopDmaPrmsVtnfOnly_420p[4].blkHeight =
                pathCfg->blkHeight / 2;

            vcore_simcopDmaPrmsVtnfOnly_420p[5].blkWidth =
                pathCfg->blkWidth >> 4;
            vcore_simcopDmaPrmsVtnfOnly_420p[5].blkHeight =
                pathCfg->blkHeight;
            vcore_simcopDmaPrmsVtnfOnly_420p[6].blkWidth =
                pathCfg->blkWidth >> 5;
            vcore_simcopDmaPrmsVtnfOnly_420p[6].blkHeight =
                pathCfg->blkHeight / 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[7].blkWidth =
                pathCfg->blkWidth >> 5;
            vcore_simcopDmaPrmsVtnfOnly_420p[7].blkHeight =
                pathCfg->blkHeight / 2;

            vcore_simcopDmaPrmsVtnfOnly_420p[0].simcopmemAddr = 0x9000U;
            vcore_simcopDmaPrmsVtnfOnly_420p[1].simcopmemAddr =
                (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight));
            vcore_simcopDmaPrmsVtnfOnly_420p[2].simcopmemAddr =
                (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight) +
                 ((pathCfg->blkWidth * pathCfg->blkHeight) / 4U));

            vcore_simcopDmaPrmsVtnfOnly_420p[3].simcopmemAddr = 0x8000U;
            vcore_simcopDmaPrmsVtnfOnly_420p[4].simcopmemAddr =
                (0x8000U + (pathCfg->blkWidth * pathCfg->blkHeight));

            vcore_simcopDmaPrmsVtnfOnly_420p[5].simcopmemAddr = 0x9000U;
            vcore_simcopDmaPrmsVtnfOnly_420p[6].simcopmemAddr =
                (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight));
            vcore_simcopDmaPrmsVtnfOnly_420p[7].simcopmemAddr =
                (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight) +
                 ((pathCfg->blkWidth * pathCfg->blkHeight) / 4U));

            for(i = 0; i < 8U; i++)
            {
                vcore_simcopDmaPrmsVtnfOnly_420p[i].horzStep =
                    vcore_simcopDmaPrmsVtnfOnly_420p[i].blkWidth;
                vcore_simcopDmaPrmsVtnfOnly_420p[i].vertStep =
                    vcore_simcopDmaPrmsVtnfOnly_420p[i].blkHeight;
                vcore_simcopDmaPrmsVtnfOnly_420p[i].simcopmemStride =
                    (vcore_simcopDmaPrmsVtnfOnly_420p[i].blkWidth << 4);
                vcore_simcopDmaPrmsVtnfOnly_420p[i].initX = 0;
                vcore_simcopDmaPrmsVtnfOnly_420p[i].initY = 0;
            }

            vcore_simcopDmaPrmsVtnfOnly_420p[0].sysmemStride =
                pathCfg->outFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly_420p[1].sysmemStride =
                pathCfg->outFrmPitch / 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[2].sysmemStride =
                pathCfg->outFrmPitch / 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[3].sysmemStride =
                pathCfg->inpFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly_420p[4].sysmemStride =
                pathCfg->inpFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly_420p[5].sysmemStride =
                pathCfg->prevFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly_420p[6].sysmemStride =
                pathCfg->prevFrmPitch / 2;
            vcore_simcopDmaPrmsVtnfOnly_420p[7].sysmemStride =
                pathCfg->prevFrmPitch / 2;
        }

        for(i = 0; i < 8U; i++)
        {
            VpsHal_isssimcopDmaSetChannelConfig(
                pInstObj->simcopHalHandle,
                &
                vcore_simcopDmaPrmsVtnfOnly_420p[i]);
        }
    }
    else
    {
        vcore_simcopDmaPrmsVtnfOnly[1].hwStopChCtrl =
            ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED;
        vcore_simcopDmaPrmsVtnfOnly[1].nextChannel =
            ISSHAL_SIMCOP_DMA_LINK_CHANNEL_2;
        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
        vcore_simcopDmaPrmsVtnfOnly[0].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][0];
        vcore_simcopDmaPrmsVtnfOnly[1].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][1];

        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
        vcore_simcopDmaPrmsVtnfOnly[2].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][0];
        vcore_simcopDmaPrmsVtnfOnly[3].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][1];

        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
        vcore_simcopDmaPrmsVtnfOnly[4].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME]->addr[0][0];
        vcore_simcopDmaPrmsVtnfOnly[5].sysmemAddr =
            frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME]->addr[0][1];

        for(i = 0; i < 6U; i++)
        {
            vcore_simcopDmaPrmsVtnfOnly[i].initX = 0;
            vcore_simcopDmaPrmsVtnfOnly[i].initY = 0;
        }
        if((int32_t)TRUE == applyConfig)
        {
            for(i = 0; i < 6U; i++)
            {
                vcore_simcopDmaPrmsVtnfOnly[i].numHorzBlks =
                    (pathCfg->inFrameWidth / pathCfg->blkWidth);
                vcore_simcopDmaPrmsVtnfOnly[i].numVertBlks =
                    (pathCfg->inFrameHeight / pathCfg->blkHeight);
            }

            for(i = 0; i < 6U; i += 2U)
            {
                vcore_simcopDmaPrmsVtnfOnly[i].blkWidth =
                    pathCfg->blkWidth >> 4;
                vcore_simcopDmaPrmsVtnfOnly[i].blkHeight =
                    pathCfg->blkHeight;
                vcore_simcopDmaPrmsVtnfOnly[i + 1U].blkWidth =
                    pathCfg->blkWidth >> 4;
                vcore_simcopDmaPrmsVtnfOnly[i + 1U].blkHeight =
                    pathCfg->blkHeight / 2;
            }

            vcore_simcopDmaPrmsVtnfOnly[0].simcopmemAddr = 0x9000U;
            vcore_simcopDmaPrmsVtnfOnly[1].simcopmemAddr =
                (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight));

            vcore_simcopDmaPrmsVtnfOnly[2].simcopmemAddr = 0x8000U;
            vcore_simcopDmaPrmsVtnfOnly[3].simcopmemAddr =
                (0x8000U + (pathCfg->blkWidth * pathCfg->blkHeight));

            vcore_simcopDmaPrmsVtnfOnly[4].simcopmemAddr = 0x9000U;
            vcore_simcopDmaPrmsVtnfOnly[5].simcopmemAddr =
                (0x9000U + (pathCfg->blkWidth * pathCfg->blkHeight));

            for(i = 0; i < 6U; i++)
            {
                vcore_simcopDmaPrmsVtnfOnly[i].horzStep =
                    vcore_simcopDmaPrmsVtnfOnly[i].blkWidth;
                vcore_simcopDmaPrmsVtnfOnly[i].vertStep =
                    vcore_simcopDmaPrmsVtnfOnly[i].blkHeight;
                vcore_simcopDmaPrmsVtnfOnly[i].simcopmemStride =
                    (vcore_simcopDmaPrmsVtnfOnly[i].blkWidth << 4);
                vcore_simcopDmaPrmsVtnfOnly[i].initX = 0;
                vcore_simcopDmaPrmsVtnfOnly[i].initY = 0;
            }

            vcore_simcopDmaPrmsVtnfOnly[0].sysmemStride = pathCfg->outFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly[1].sysmemStride = pathCfg->outFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly[2].sysmemStride = pathCfg->inpFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly[3].sysmemStride = pathCfg->inpFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly[4].sysmemStride = pathCfg->prevFrmPitch;
            vcore_simcopDmaPrmsVtnfOnly[5].sysmemStride = pathCfg->prevFrmPitch;
        }
        for(i = 0; i < 6U; i++)
        {
            VpsHal_isssimcopDmaSetChannelConfig(pInstObj->simcopHalHandle,
                                                &vcore_simcopDmaPrmsVtnfOnly[i]);
        }
    }

    vcore_VtnfOnlyHwSeqPrms.startStep = 0;
    vcore_VtnfOnlyHwSeqPrms.stepCnt   = 2;
    VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                   &vcore_VtnfOnlyHwSeqPrms);

    pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_PIPEUP_COMP;
    VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);

    return retVal;
}

static void vcoreSimcopISR_ldcOnly(const UInt32 *event, UInt32 numEvents,
                                   Ptr handle)
{
    uint32_t pipeSteadyStateCount, cookie;
    int32_t  retVal = BSP_SOK;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpsissSimcopCfgPrms_t  *pathCfg;
    vpscoreSimcopInstObj_t *pInstObj;

    GT_assert(VpsIssCoreTrace, (NULL != handle));
    GT_assert(VpsIssCoreTrace, (NULL != event));

    pInstObj = (vpscoreSimcopInstObj_t *)(handle);
    GT_assert(VpsIssCoreTrace, (NULL != pInstObj->pActiveHndlObj));
    GT_assert(VpsIssCoreTrace, (FALSE != pInstObj->isRequestActive));
    pHndlObj = pInstObj->pActiveHndlObj;
    pathCfg  = &(pHndlObj->cfg);

    if(*event != pInstObj->initPrms.eventNum)
    {
        retVal = BSP_EFAIL;
    }

    if((SIMCOP_FRAME_STATE_WAIT_4_PIPEUP_COMP == pHndlObj->procSteps) &&
       (BSP_SOK == retVal))
    {
        pipeSteadyStateCount =
            (pathCfg->ldcCfg.advCfg.outputFrameWidth / pathCfg->blkWidth) *
            (pathCfg->ldcCfg.advCfg.outputFrameHeight / pathCfg->blkHeight);
        vcore_LdcOnlyHwSeqPrms.startStep = 1U +
                                           ((pipeSteadyStateCount + 1U) & 1U);
        vcore_LdcOnlyHwSeqPrms.stepCnt = 1;
        vcore_LdcOnlyHwSeqPrms.stepParams[1].enableLdcSync = (uint32_t) FALSE;
        vcore_LdcOnlyHwSeqPrms.stepParams[2].enableLdcSync = (uint32_t) FALSE;

        VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                       &vcore_LdcOnlyHwSeqPrms);
        VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_STEADY_COMP;
    }
    else if((SIMCOP_FRAME_STATE_WAIT_4_STEADY_COMP == pHndlObj->procSteps) &&
            (BSP_SOK == retVal))
    {
        cookie = BspOsal_disableInterrupt();
        pInstObj->isRequestActive = (uint32_t) FALSE;
        pInstObj->pActiveHndlObj  = NULL;
        BspOsal_restoreInterrupt(cookie);

        VpsHal_issldcStop(pInstObj->ldcHandle);
        if(NULL != pHndlObj->openPrms.frmDoneNotifyCb)
        {
            /* Call the calback of the upper layer */
            pHndlObj->openPrms.frmDoneNotifyCb(pHndlObj->openPrms.drvData);
        }
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_FRAME_COMP;
    }
    else
    {
        pHndlObj->procSteps = SIMCOP_FRAME_STATE_INVALID;
    }
}

/* MISRA.PPARAM.NEEDS.CONST
 * MISRAC_2004_Rule_16.7
 * Function parameter 'frm' is not declared as a pointer to const
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Klocwork is not able to analyse pointers which are declared as const and
 *  reporting this issue.This is a false positive.
 */
int32_t vcoreSimcopPutFrames_ldcOnly(VpsCore_Handle        handle,
                                     const VpsCore_Frame **frm)
{
    int32_t retVal = BSP_SOK;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpsissSimcopCfgPrms_t  *pathCfg;
    vpscoreSimcopInstObj_t *pInstObj;

    pHndlObj = (vpscoreSimcopHndlObj_t *) (handle);
    pInstObj = &gInstObjs[pHndlObj->instId];
    pathCfg  = &(pHndlObj->cfg);

    if(pInstObj->pCurrHndl == pHndlObj)
    {
        /* There was no change in LDC config,
         *  update the input frame address only. By default the output frame
         *  address would be updated. */
        if(VPS_ISS_LDC_MODE_YUV420_LDC == pathCfg->ldcCfg.mode)
        {
            /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
            /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
            vcore_simcopDmaPrmsLdcOnly[0].sysmemAddr =
                frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][0];
            vcore_simcopDmaPrmsLdcOnly[1].sysmemAddr =
                frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][1];
        }
        else
        {
            /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
            /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
            vcore_simcopDmaPrmsLdcOnly[0].sysmemAddr =
                frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][0];
        }
        retVal += VpsHal_isssimcopDmaSetChannelConfig(
            pInstObj->simcopHalHandle,
            &vcore_simcopDmaPrmsLdcOnly[0]);
        if(VPS_ISS_LDC_MODE_YUV420_LDC == pathCfg->ldcCfg.mode)
        {
            retVal += VpsHal_isssimcopDmaSetChannelConfig(
                pInstObj->simcopHalHandle,
                &vcore_simcopDmaPrmsLdcOnly[1]);
        }
    }
    else
    {
        pHndlObj->blockMultX10 = 1U * 10U;

        /* SIMCOP DMA configuration */
        if(VPS_ISS_LDC_MODE_YUV420_LDC == pathCfg->ldcCfg.mode)
        {
            pHndlObj->blockMultX10 = 1U * 10U;

            vcore_simcopDmaPrmsLdcOnly[0].hwStopChCtrl =
                ISSHAL_SIMCOP_DMA_HW_SYNC_DISABLED;
            vcore_simcopDmaPrmsLdcOnly[0].nextChannel =
                ISSHAL_SIMCOP_DMA_LINK_CHANNEL_1;

            vcore_simcopDmaPrmsLdcOnly[0].blkWidth =
                (pathCfg->blkWidth >> 4);
            vcore_simcopDmaPrmsLdcOnly[0].blkHeight =
                pathCfg->blkHeight;
            vcore_simcopDmaPrmsLdcOnly[0].numHorzBlks =
                (pathCfg->ldcCfg.advCfg.outputFrameWidth / pathCfg->blkWidth);
            vcore_simcopDmaPrmsLdcOnly[0].numVertBlks =
                (pathCfg->ldcCfg.advCfg.outputFrameHeight / pathCfg->blkHeight);
            vcore_simcopDmaPrmsLdcOnly[0].horzStep =
                (pathCfg->blkWidth >> 4);
            vcore_simcopDmaPrmsLdcOnly[0].vertStep =
                pathCfg->blkHeight;

            /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
            /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
            vcore_simcopDmaPrmsLdcOnly[0].sysmemAddr =
                frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][0];
            vcore_simcopDmaPrmsLdcOnly[0].sysmemStride =
                pathCfg->outFrmPitch;

            vcore_simcopDmaPrmsLdcOnly[0].simcopmemAddr   = 0x8000U;
            vcore_simcopDmaPrmsLdcOnly[0].simcopmemStride =
                pathCfg->blkWidth;

            vcore_simcopDmaPrmsLdcOnly[1].blkWidth =
                (pathCfg->blkWidth >> 4);
            vcore_simcopDmaPrmsLdcOnly[1].blkHeight =
                (pathCfg->blkHeight / 2);
            vcore_simcopDmaPrmsLdcOnly[1].numHorzBlks =
                (pathCfg->ldcCfg.advCfg.outputFrameWidth / pathCfg->blkWidth);
            vcore_simcopDmaPrmsLdcOnly[1].numVertBlks =
                (pathCfg->ldcCfg.advCfg.outputFrameHeight / pathCfg->blkHeight);
            vcore_simcopDmaPrmsLdcOnly[1].horzStep =
                (pathCfg->blkWidth >> 4);
            vcore_simcopDmaPrmsLdcOnly[1].vertStep =
                (pathCfg->blkHeight / 2);

            /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
            /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
            vcore_simcopDmaPrmsLdcOnly[1].sysmemAddr =
                frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][1];
            vcore_simcopDmaPrmsLdcOnly[1].sysmemStride =
                pathCfg->outFrmPitch;

            vcore_simcopDmaPrmsLdcOnly[1].simcopmemAddr =
                (0x8000U + (pathCfg->blkWidth * pathCfg->blkHeight));
            vcore_simcopDmaPrmsLdcOnly[1].simcopmemStride =
                pathCfg->blkWidth;
        }
        else
        {
            if(VPS_ISS_LDC_MODE_YUV422_LDC == pathCfg->ldcCfg.mode)
            {
                pHndlObj->blockMultX10 = 2U * 10U;
            }
            else
            {
                if(VPS_ISS_LDC_MODE_BAYER_CHROMA_ABBERATION ==
                   pathCfg->ldcCfg.mode)
                {
                    pHndlObj->blockMultX10 = 1U * 10U;

                    if(VPS_ISS_LDC_BAYER_DATA_FORMAT_PACKED_12BIT ==
                       pathCfg->ldcCfg.bayerDataFormat)
                    {
                        pHndlObj->blockMultX10 = 120U / 8U;
                    }
                    if(VPS_ISS_LDC_BAYER_DATA_FORMAT_UNPACKED_12BIT ==
                       pathCfg->ldcCfg.bayerDataFormat)
                    {
                        pHndlObj->blockMultX10 = 2U * 10U;
                    }
                    if(VPS_ISS_LDC_BAYER_DATA_FORMAT_PACKED_8BIT ==
                       pathCfg->ldcCfg.bayerDataFormat)
                    {
                        pHndlObj->blockMultX10 = 1U * 10U;
                    }
                    if(VPS_ISS_LDC_BAYER_DATA_FORMAT_ALAW ==
                       pathCfg->ldcCfg.bayerDataFormat)
                    {
                        pHndlObj->blockMultX10 = 1U * 10U;
                    }
                }
            }
            vcore_simcopDmaPrmsLdcOnly[0].hwStopChCtrl =
                ISSHAL_SIMCOP_DMA_HW_SYNC_CHANNEL_0;
            vcore_simcopDmaPrmsLdcOnly[0].nextChannel =
                ISSHAL_SIMCOP_DMA_LINK_DISABLED;

            vcore_simcopDmaPrmsLdcOnly[0].blkWidth =
                (((pathCfg->blkWidth * pHndlObj->blockMultX10) / 10U) >> 4U);
            vcore_simcopDmaPrmsLdcOnly[0].blkHeight   = pathCfg->blkHeight;
            vcore_simcopDmaPrmsLdcOnly[0].numHorzBlks =
                (pathCfg->ldcCfg.advCfg.outputFrameWidth / pathCfg->blkWidth);
            vcore_simcopDmaPrmsLdcOnly[0].numVertBlks =
                (pathCfg->ldcCfg.advCfg.outputFrameHeight / pathCfg->blkHeight);
            vcore_simcopDmaPrmsLdcOnly[0].horzStep =
                (((pathCfg->blkWidth * pHndlObj->blockMultX10) / 10U) >> 4U);
            vcore_simcopDmaPrmsLdcOnly[0].vertStep = pathCfg->blkHeight;

            /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
            /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
            vcore_simcopDmaPrmsLdcOnly[0].sysmemAddr =
                frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]->addr[0][0];
            vcore_simcopDmaPrmsLdcOnly[0].sysmemStride = pathCfg->outFrmPitch;

            vcore_simcopDmaPrmsLdcOnly[0].simcopmemAddr   = 0x8000U;
            vcore_simcopDmaPrmsLdcOnly[0].simcopmemStride =
                (pathCfg->blkWidth * pHndlObj->blockMultX10) / 10U;
        }

        retVal += VpsHal_isssimcopDmaSetChannelConfig(
            pInstObj->simcopHalHandle,
            &vcore_simcopDmaPrmsLdcOnly[0]);
        if(VPS_ISS_LDC_MODE_YUV420_LDC == pathCfg->ldcCfg.mode)
        {
            retVal += VpsHal_isssimcopDmaSetChannelConfig(
                pInstObj->simcopHalHandle,
                &vcore_simcopDmaPrmsLdcOnly[1]);
        }

        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        if(NULL != frm[VPS_SIMCOP_STREAM_ID_MESH_TABLE])
        {
            /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
            /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
            pathCfg->ldcCfg.lutCfg.address =
                (uint32_t) frm[VPS_SIMCOP_STREAM_ID_MESH_TABLE]->addr[0][0];
        }

        GT_assert(VpsIssCoreTrace, (NULL != pathCfg->ldcCfg.lutCfg.address));
        retVal += VpsHal_issldcSetConfig(pInstObj->ldcHandle,
                                         &pathCfg->ldcCfg,
                                         NULL);
        if(retVal != BSP_SOK)
        {
            Bsp_printf("LDC ERROR - Unable to apply LDC config \r\n");
        }

        /* Lets remember that this handles config is the latest that was
         *  applied */
        pInstObj->pCurrHndl = pHndlObj;
    }

    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    GT_assert(VpsIssCoreTrace,
              (NULL != frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][0]));
    if(VPS_ISS_LDC_MODE_YUV420_LDC == pathCfg->ldcCfg.mode)
    {
        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        GT_assert(VpsIssCoreTrace,
                  (NULL != frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][1]));
    }

    /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
    /* MISRA.CAST.PTR_TO_INT 11.3 WAIVER explained at beginning of file */
    retVal += VpsHal_issldcSetInFrameAddress(
        pInstObj->ldcHandle,
        pathCfg->ldcCfg.mode,
        (uint32_t)frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][0],
        (uint32_t)frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]->addr[0][1],
        pathCfg->inpFrmPitch);

    retVal += VpsHal_issldcSetOutFrameAddress(
        pInstObj->ldcHandle,
        pathCfg->ldcCfg.mode,
        0U,
        0U + (pathCfg->blkWidth * pathCfg->blkHeight),
        ((pathCfg->blkWidth * pHndlObj->blockMultX10) / 10U));

    /* TODO TBD check second arg */
    retVal += VpsHal_issldcStart(pInstObj->ldcHandle,
                                 ISSHAL_ISS_PROC_MODE_FREE_RUN,
                                 NULL);
    /* TODO TBD Default should work - need to figure out optimal values */

    vcore_LdcOnlyHwSeqPrms.stepParams[1].enableLdcSync = (uint32_t) TRUE;
    vcore_LdcOnlyHwSeqPrms.stepParams[2].enableLdcSync = (uint32_t) TRUE;
    vcore_LdcOnlyHwSeqPrms.startStep = 0;
    vcore_LdcOnlyHwSeqPrms.stepCnt   =
        (pathCfg->ldcCfg.advCfg.outputFrameWidth / pathCfg->blkWidth) *
        (pathCfg->ldcCfg.advCfg.outputFrameHeight / pathCfg->blkHeight);
    retVal += VpsHal_isssimcopHwSeqSetConfig(pInstObj->simcopHalHandle,
                                             &vcore_LdcOnlyHwSeqPrms);
    pHndlObj->procSteps = SIMCOP_FRAME_STATE_WAIT_4_PIPEUP_COMP;
    retVal += VpsHal_isssimcopHwSeqStart(pInstObj->simcopHalHandle);

    return retVal;
}

/**
 *  vcoreSimcopPutFrames
 *  \brief Sets up the SIMCOP to perform required operation.
 *
 *  \param handle   Handle returned by open API
 *  \param frm      Pointer to array if VpsCore_Frame pointer, depending on the
 *                  requested operation, one or more frames should be valid
 *
 *  \return         Returns BSP_SOK on success else returns error value.
 *
 */
int32_t vcoreSimcopPutFrames(VpsCore_Handle  handle,
                             VpsCore_Frame **frm)
{
    int32_t  retVal = FVID2_EBADARGS;
    vpscoreSimcopHndlObj_t *pHndlObj;
    vpscoreSimcopInstObj_t *pInstObj;
    uint32_t cookie;

    if((NULL != handle) && (NULL != frm))
    {
        /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
        if((NULL != frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME]) &&
           (NULL != frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME]))
        {
            retVal = FVID2_SOK;
        }

        pHndlObj = (vpscoreSimcopHndlObj_t *) (handle);
        if(VPS_ISS_SIMCOP_LDC != pHndlObj->mode)
        {
            retVal = FVID2_EBADARGS;
            /* MISRA.PTR.ARITH 17.1/17.4 WAIVER explained at beginning of file*/
            if(NULL != frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME])
            {
                retVal = FVID2_SOK;
            }
        }

        if(VPSCORE_SIMCOP_MAX_INST <= pHndlObj->instId)
        {
            retVal = FVID2_EBADARGS;
        }

        if(FVID2_SOK == retVal)
        {
            pInstObj = &gInstObjs[pHndlObj->instId];

            /* Check active processing, Mark active */
            cookie = BspOsal_disableInterrupt();
            if(TRUE != pInstObj->isRequestActive)
            {
                pInstObj->isRequestActive = (uint32_t) TRUE;
                pInstObj->pActiveHndlObj  = pHndlObj;
            }
            else
            {
                retVal = FVID2_EDEVICE_INUSE;
            }
            BspOsal_restoreInterrupt(cookie);
        }
    }

    if(FVID2_SOK == retVal)
    {
        if(VPS_ISS_SIMCOP_LDC == pHndlObj->mode)
        {
            retVal = vcoreSimcopPutFrames_ldcOnly(handle,
                                                  (const VpsCore_Frame **)frm);
        }
        if(VPS_ISS_SIMCOP_VTNF == pHndlObj->mode)
        {
            retVal = vcoreSimcopPutFrames_vtnfOnly(handle,
                                                   (const VpsCore_Frame **)frm);
        }
        if(VPS_ISS_SIMCOP_LDC_VTNF == pHndlObj->mode)
        {
            retVal = vcoreSimcopPutFrames_ldcVtnf(handle,
                                                  (const VpsCore_Frame **)frm);
        }

        if(FVID2_SOK != retVal)
        {
            /* For some other reason, we could start processing */
            cookie = BspOsal_disableInterrupt();
            pInstObj->isRequestActive = (uint32_t) FALSE;
            pInstObj->pActiveHndlObj  = NULL;
            BspOsal_restoreInterrupt(cookie);
        }
    }
    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */
static void vcoreSetLdcAdvCfg(vpsissldcConfig_t *cfg)
{
    vpsissldcAdvConfig_t *advCfg = &(cfg->advCfg);
    advCfg->outputBlockWidth   = 32;
    advCfg->outputBlockHeight  = 32;
    advCfg->outputFrameWidth   = cfg->inputFrameWidth;
    advCfg->outputFrameHeight  = cfg->inputFrameHeight;
    advCfg->outputStartX       = 0;
    advCfg->outputStartY       = 0;
    advCfg->enableCircAddrMode = (uint32_t) FALSE;
    advCfg->circBuffSize       = 0;
    advCfg->enableConstOutAddr = (uint32_t) TRUE;
}

static void vcoreFixUnsupportedLdcCfg(vpsissldcConfig_t *cfg)
{
    vpsissldcAdvConfig_t *advCfg = &(cfg->advCfg);
    advCfg->outputFrameWidth   = cfg->inputFrameWidth;
    advCfg->outputFrameHeight  = cfg->inputFrameHeight;
    advCfg->outputStartX       = 0;
    advCfg->outputStartY       = 0;
    advCfg->enableCircAddrMode = (uint32_t) FALSE;
    advCfg->circBuffSize       = 0;
    advCfg->enableConstOutAddr = (uint32_t) TRUE;
}

static void vcoreSetVtnfAdvCfg(vpsissvtnfConfig_t *cfg)
{
    static vpsissvtnfAdvConfig_t defVtnfAdvCfg =
    {
        32,      /* blockWidth */
        32,      /* blockHeight */
        5,       /* roundBitCount */
        4,       /* colorWeight1 */
        4,       /* colorWeight2 */
        {        /* lut1[ISSHAL_VTNF_LUT_SIZE] */
            192, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24,
            16,  8,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
            0
        },
        {   /* lut2[ISSHAL_VTNF_LUT_SIZE] */
            192, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24,
            16,  8,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
            0
        },
        ISSHAL_VTNF_TRG_SRC_HWSEQ, /* triggerSource */
        TRUE                       /* intrEnable */
    };
    vpsissvtnfAdvConfig_t       *advCfg = &(cfg->advCfg);
    BspUtils_memcpy(advCfg, &defVtnfAdvCfg, sizeof(vpsissvtnfAdvConfig_t));
}

static void vcoreFixUnsupportedVtnfCfg(vpsissvtnfConfig_t *cfg)
{
    vpsissvtnfAdvConfig_t *advCfg = &(cfg->advCfg);
    advCfg->triggerSource = ISSHAL_VTNF_TRG_SRC_HWSEQ;
    advCfg->intrEnable    = (uint32_t) TRUE;
}

