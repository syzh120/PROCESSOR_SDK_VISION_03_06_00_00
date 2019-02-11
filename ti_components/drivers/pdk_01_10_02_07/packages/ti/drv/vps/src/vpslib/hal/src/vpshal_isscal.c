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
 *  \file vpshal_isscal.c
 *
 *  \brief This file defines all abstractions for CAL module of ISS.
 *  This abstraction will support multiple instances of PPI, CSI. Operates 2
 *  modes primarily. memory to memory mode and capture mode.
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

#include <ti/csl/soc.h>

#if defined (SOC_TDA3XX)
#include <ti/csl/cslr_iss.h>
#endif /* SOC_TDA3XX */

#if defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_TDA2PX)
#include <ti/csl/cslr_cal.h>
#endif /* SOC_TDA2EX */

#include <ti/csl/hw_types.h>


#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isscal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SMA_SW_CSI2_X0_UP_MASK             (0x00000001U)
#define SMA_SW_CSI2_Y0_UP_MASK             (0x00000002U)

#define SMA_SW_CSI2_X1_UP_MASK             (0x00000004U)
#define SMA_SW_CSI2_Y1_UP_MASK             (0x00000008U)

#define SMA_SW_CSI2_X2_UP_MASK             (0x00000010U)
#define SMA_SW_CSI2_Y2_UP_MASK             (0x00000020U)

#define SMA_SW_CSI2_X3_UP_MASK             (0x00000040U)
#define SMA_SW_CSI2_Y3_UP_MASK             (0x00000080U)

#define SMA_SW_CSI2_X4_UP_MASK             (0x00000100U)
#define SMA_SW_CSI2_Y4_UP_MASK             (0x00000200U)

#define SMA_SW_CSI2_X0_DW_MASK             (0x00000400U)
#define SMA_SW_CSI2_Y0_DW_MASK             (0x00000800U)

#define SMA_SW_CSI2_X1_DW_MASK             (0x00001000U)
#define SMA_SW_CSI2_Y1_DW_MASK             (0x00002000U)

#define SMA_SW_CSI2_X2_DW_MASK             (0x00004000U)
#define SMA_SW_CSI2_Y2_DW_MASK             (0x00008000U)

#define SMA_SW_CSI2_X3_DW_MASK             (0x00010000U)
#define SMA_SW_CSI2_Y3_DW_MASK             (0x00020000U)

#define SMA_SW_CSI2_X4_DW_MASK             (0x00040000U)
#define SMA_SW_CSI2_Y4_DW_MASK             (0x00080000U)

/**< Bit 2 set, used to compute register values for lanes enabled. */
#define CAL_BIT_2_SET       ((uint32_t)0x4U)

#if (VPS_ISS_CAL_MAX_CMPLXIO_INST != CSL_CAL_CMPLXIO_CNT)
        #error "Number of complex IO's dont match"
#endif

/**< If PPI is enabled before DMA writes are, there is possibility that 1st
        frame received will be written to address 0x0.
        As Write DMA address is latched with a frame start event.
        If PPI is enabled, before any buffer are primed, the write address is
        not yet updated. 0x0 being reset value of write DMA address, 1st
        frame would be written there. */
#define ENABLE_PPI_WHEN_STARTING

/**< Functional PHY clock is expected to be 96 MHz
        Period of PHY clock in nS is 10.41666
        ((1/<PHY Clock) / 1e-9) */
#define DPHY_FUNCTIONAL_CLK_PERIOD  (10.41666)


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct isshalCalInstObj
 *  \brief Describes a instance of Cal configuration.
 */
typedef struct isshalCalInstObj
{
    uint32_t           instId;
    /**< Instance ID */
    uint32_t           baseAddr;
    /**< Base address of the CAL module */
    uint32_t           phy0BaseAddress;
    /**< If this CAL instance has an associated PHY, this will hold a non-null
     *      value */
    uint32_t           phy1BaseAddress;
    /**< If this CAL instance has an associated PHY, this will hold a non-null
     *      value */
    uint32_t           isInited;
    /**< Flag to indicate successful initialization */
    uint32_t           openCnt;
    /**< Number of times the hal is opened. */
    isshalCalInstCfg_t instCfg;
    /**< Instance configuration */
} isshalCalInstObj_t;

/**
 *  struct isshalCalObj
 *  \brief Describes a cal object.
 */
typedef struct isshalCalObj
{
    isshalCalMode_t     mode;
    /**< Mode */
    isshalCalInstObj_t *pInstObj;
    /**< Pointer to instance specific config */
} isshalCalObj_t;

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Resets the CAL instance
 *
 * \param   baseAddr Base address of the CAL instance to be reset.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalReset(uint32_t baseAddr);

/**
 * \brief   Configure instance LANE config and frame mode of operation. Note
 *              that the low level port is enabled for reception.
 *
 * \param   baseAddr Base address of the CAL.
 * \param   pCfg     Valid lane and frame mode configurations
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalCfgInstLanePpiCfg(uint32_t            baseAddr,
                                    isshalCalInstCfg_t *pCfg);

/**
 * \brief   Resets CAL / PHY and applies instance specific config for capture
 *              Updated DMA read specifics for other modes.
 *
 * \param   hndl    Handle returned when opened.
 * \param   cfg     Valid configuration for mode specified in open.
 * \param   mode    Mode as specified during open.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalResetApplyInstConfig(const isshalCalObj_t *pHndl,
                                       isshalCalInstCfg_t   *pCfg,
                                       isshalCalMode_t       mode,
                                       uint32_t              enPhy);
/**
 * \brief   Applies supplied configurations, for all mode & all blocks.
 *
 * \param   hndl    Handle returned when opened.
 * \param   cfg     Valid configuration for mode specified in open.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetCfg(const isshalCalObj_t *hndl, const isshalCalCfg_t *cfg);

/**
 * \brief   Applies configurations required for m2m mode.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for m2m.
 * \param   mode    Indicates if in capture / m2m mode.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetCfgForMode(const isshalCalInstObj_t *pInst,
                                const isshalCalCfg_t     *cfg,
                                isshalCalMode_t           mode);

/**
 * \brief   Applies CSI2 Virtual processing configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for Virtual Channels of CSI2.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalCsi2VcCfg(const isshalCalInstObj_t   *pInst,
                            const isshalCalCsi2VcCfg_t *cfg,
                            uint32_t                    cportId);

/**
 * \brief   Applies pixel processing configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for pixel processing.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetPixProcCfg(const isshalCalInstObj_t *pInst,
                                const vpsissCalPixProc_t *cfg,
                                uint32_t                  cportId);

/**
 * \brief   Applies BYS Out port configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for BYS Out port.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetBysOutCfg(const isshalCalInstObj_t *pInst,
                               const vpsissCalBysOut_t  *cfg,
                               uint32_t                  cportId);

/**
 * \brief   Applies VPORT out configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for VPORT Out.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetVportCfg(const isshalCalInstObj_t *pInst,
                              const vpsissCalVPort_t   *cfg,
                              uint32_t                  cportId);

/**
 * \brief   Applies DMA Read configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for DMA Read.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetRdDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalRdDmaCfg_t *cfg,
                              uint32_t                   cportId);

/**
 * \brief   Applies DMA Read frame size
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for frame config.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetRdDmaFrameCfg(const isshalCalInstObj_t *pInst,
                                   const Fvid2_Format       *cfg);

/**
 * \brief   Applies DMA Write configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for DMA Write.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetWrDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalWrDmaCfg_t *cfg,
                              uint32_t                   cportId);

/**
 * \brief   Sets the DMA mode, expected to be used to enable/disable DMA writes
 *              For all the DMA write contexts that have been configured, the
 *              supplied mode is applied
 *
 * \param   pInstObj   Pointer to instance object.
 * \param   pDmaCfg    Pointer to DMA config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t calSetWrDmaMode(const isshalCalInstObj_t  *pInstObj,
                               const isshalCalDmaVcCfg_t *pDmaCfg);

/**
 * \brief   Sets the DMA configurations such as burst size, mode, etc...
 *
 * \param   pInstObj   Pointer to instance object.
 * \param   pDmaCfg    Pointer to DMA config
 *
 * \return  FVID2_SOK
 *
 **/
static int32_t CalCfgInstWrDma(
    uint32_t baseAddr, const isshalCalInstCfg_t *pCfg);

/**
 * \brief   Configure the interrupt generation on reception of specified line
 *          of video data.
 *
 * \param   pInstObj   Pointer to instance object.
 * \param   plnEvtCfg  Pointer to line event configuration
 *
 * \return  FVID2_SOK
 *
 **/
static int32_t CalSetLineEventCfg(const isshalCalInstObj_t  *pInstObj,
                                  const isshalCalLineEventCfg_t *plnEvtCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define CAL_HAL_INST_OBJ_DEFAULTS ( 0x0,                /* instId */ \
                                    0x0,                /* baseAddr */ \
                                    0x0,                /* phy0BaseAddress */ \
                                    0x0,                /* phy1BaseAddress */ \
                                    (uint32_t) FALSE,   /* isInited */ \
                                    0x0,                /* openCnt */ \
                                    )
static isshalCalInstObj_t gCalInstObj[CSL_CAL_PER_CNT] =
{
    {
        0x0,                /* instId */
        0x0,                /* baseAddr */
        0x0,                /* phy0BaseAddress */
        0x0,                /* phy1BaseAddress */
        (uint32_t) FALSE,   /* isInited */
        0x0                 /* openCnt */
    }
#if (CSL_CAL_PER_CNT > 1U)
    ,
    {
        0x0,
        0x0,
        (uint32_t)FALSE,
        0x0,
        0x0
    }
#endif
/* Currently we do not have SoC with more than 2 CAL instances */
};
/**< Instance specific config */

static isshalCalObj_t     gCalObj \
    [CSL_CAL_PER_CNT][VPS_HAL_ISS_CAL_OPEN_NUM];
/**< Handle / open specific config */

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gCalInstDefaults' visibility is too wide.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static isshalCalInstCfg_t gCalInstDefaults;

/**< Default instance config */
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_isscalInit(uint32_t numInst,
                          const isshalCalInstParams_t *initPrms, Ptr arg)
{
    uint32_t i, j;
    uint32_t isInited = (uint32_t)FALSE;

    GT_assert(VpsHalTrace, (CSL_CAL_PER_CNT >= numInst));
    GT_assert(VpsHalTrace, (NULL != initPrms));
    GT_assert(VpsHalTrace, (0x0 != initPrms->baseAddress));

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'i < CSL_CAL_PER_CNT' used in the condition always yields the
 * same result.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
    for(i = 0; i < CSL_CAL_PER_CNT; i++)
    {
        if((uint32_t)FALSE != gCalInstObj[i].isInited)
        {
            /* Has been initialized earlier. Exit now */
            isInited = (uint32_t)TRUE;
            /* This is MISRA C violation, for having multiple returns.
             *  This should not cause any issues. Please ignore */
        }
    }

    if((uint32_t)FALSE == isInited)
    {
        /* Do not require to initialize gCalObj, we rely primarily
         * on gCalInstObj
         *  The association between gCalInstObj & gCalObj is done
         * further down */
        /* . Set defaults */
        /* Indicates the urgency of real time traffic using the
         * number of contexts
         *  currently in use by the write DMA.
         *  00: SAFE (n<MFLAGL)
         *  01: VULNERABLE (MFLAGL<=n<MFLAGH)
         *  11: ENDANGERED (MFLAGH<=n)
         *  Assuming 4 write DMA contexts, n = 4 */

        gCalInstDefaults.mFlagH = 10U;
        gCalInstDefaults.mFlagL = 6U;
        /* Assuming CAL receives via a sensor */
        gCalInstDefaults.rdDmaStall   = (uint32_t)TRUE;
        gCalInstDefaults.pwrScpClk    = (uint32_t)FALSE;
        gCalInstDefaults.dmaBurstSize = CAL_CTRL_BURSTSIZE_BURST128;
        gCalInstDefaults.tagCnt       = 15U;
        gCalInstDefaults.postedWrites = (uint32_t)FALSE;

        for(i = 0; i < CSL_CAL_CMPLXIO_CNT; i++)
        {
            gCalInstDefaults.csi2PhyClock[i] = 400U;

            gCalInstDefaults.numCmplxIoInst = CSL_CAL_CMPLXIO_CNT;
            gCalInstDefaults.cmplxIoCfg[i].enable = (uint32_t)TRUE;
            gCalInstDefaults.cmplxIoCfg[i].clockLane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].clockLane.position = 5U;
            gCalInstDefaults.cmplxIoCfg[i].data1Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data1Lane.position = 1U;
            gCalInstDefaults.cmplxIoCfg[i].data2Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data2Lane.position = 2U;
            gCalInstDefaults.cmplxIoCfg[i].data3Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data3Lane.position = 3U;
            gCalInstDefaults.cmplxIoCfg[i].data4Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data4Lane.position = 4U;
            gCalInstDefaults.cmplxIoCfg[i].pwrAuto            = (uint32_t)FALSE;
            /* Always
             * powered
             * up
             */
        }
        for(i = 0; i < CSL_CAL_PPI_CNT; i++)
        {
            gCalInstDefaults.numPpiInst         = CSL_CAL_PPI_CNT;
            gCalInstDefaults.ppiCfg[i].enable   = (uint32_t)FALSE;
            gCalInstDefaults.ppiCfg[i].instance = 0x0U;
            gCalInstDefaults.ppiCfg[i].frame    = (uint32_t)TRUE;
            gCalInstDefaults.ppiCfg[i].ecc      = (uint32_t)FALSE;

            /* Careful while updating these, are used to determine
                the stop state
                detection.
                Please ignore force_rx_mode_0I01 - will be removed */
            gCalInstDefaults.ppiCfg[i].csi2Cfg.force_rx_mode_0I01     = 1U;
            gCalInstDefaults.ppiCfg[i].csi2Cfg.stop_state_x16_I01     = 1U;
            gCalInstDefaults.ppiCfg[i].csi2Cfg.stop_state_x4_I01      = 0U;
            gCalInstDefaults.ppiCfg[i].csi2Cfg.stop_state_counter_I01 = 0x197U;
        }
/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'i < CSL_CAL_PER_CNT' used in the condition always yields the
 * same result.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
        for(i = 0; ((i < numInst) && (i < CSL_CAL_PER_CNT)); i++)
        {
            gCalInstObj[i].instId = i;
            GT_assert(VpsHalTrace, (0x0 != initPrms->baseAddress));
            gCalInstObj[i].baseAddr       = initPrms->baseAddress;
            gCalInstObj[i].phy0BaseAddress = initPrms->phy0BaseAddress;
            gCalInstObj[i].phy1BaseAddress = initPrms->phy1BaseAddress;
            gCalInstObj[i].openCnt        = 0U;
            gCalInstObj[i].isInited       = (uint32_t)TRUE;
            BspUtils_memcpy((Ptr) & gCalInstObj[i].instCfg,
                            (const void *) &gCalInstDefaults,
                            sizeof(isshalCalInstCfg_t));
            for(j = 0; j < VPS_HAL_ISS_CAL_OPEN_NUM; j++)
            {
                gCalObj[i][j].pInstObj = &gCalInstObj[i];
            }

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * Pointer Arithmatic
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER: Pointer is incremented to get the next
             * object's location.
             * This function is called by init function, which passes
             * cal number of instances. The size of this number of instances
             * is never more than CSL_CAL_PER_CNT.
             */
            initPrms++;
        }
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalDeInit(Ptr arg)
{
    uint32_t i;

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'i < CSL_CAL_PER_CNT' used in the condition always yields the
 * same result.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
    for(i = 0; i < CSL_CAL_PER_CNT; i++)
    {
        GT_assert(VpsHalTrace, (0x0 == gCalInstObj[i].openCnt));
        BspUtils_memset(&gCalInstObj[i], 0U, sizeof(isshalCalInstObj_t));
    }
    /* Do not require any updates to gCalObj, the close will take care */
    return FVID2_SOK;
}

/**************************Function Separator**********************************/

VpsHal_Handle VpsHal_isscalOpen(const isshalCalOpenParams_t *openPrms,
                                Ptr                          arg)
{
    isshalCalObj_t *hndl = NULL;
    int32_t         rtnVal;
    uint32_t        openCnt;

    rtnVal = FVID2_SOK;
    if(NULL == openPrms)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (CSL_CAL_PER_CNT <= openPrms->instId))
    {
        rtnVal = FVID2_EBADARGS;
    }
    if((FVID2_SOK == rtnVal) &&
       ((VPS_HAL_ISS_CAL_MODE_MIN >= openPrms->mode) ||
        (VPS_HAL_ISS_CAL_MODE_MAX <= openPrms->mode)))
    {
        rtnVal = FVID2_EBADARGS;
    }
    if(FVID2_SOK == rtnVal)
    {
        openCnt = gCalObj[openPrms->instId][0].pInstObj->openCnt;
        if(VPS_HAL_ISS_CAL_OPEN_NUM <= openCnt)
        {
            rtnVal = FVID2_EALLOC;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        hndl = &gCalObj[openPrms->instId][openCnt];
        if(NULL == hndl->pInstObj)
        {
            /* Not initialized/ */
            rtnVal = FVID2_EBADARGS;
        }
    }
    if(FVID2_SOK == rtnVal)
    {
        hndl->pInstObj->openCnt++;

        rtnVal = CalResetApplyInstConfig(hndl, &hndl->pInstObj->instCfg,
                                         openPrms->mode, (uint32_t)FALSE);
        if(FVID2_SOK == rtnVal)
        {
            hndl->mode = openPrms->mode;
        }
    }

    return ((VpsHal_Handle) hndl);
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalClose(VpsHal_Handle handle, Ptr arg)
{
    uint32_t          instance, i;
    int32_t           rtnVal = FVID2_SOK;
    volatile uint32_t reg, timeOut;
    isshalCalObj_t   *hndl = (isshalCalObj_t *) handle;

    if(NULL == hndl)
    {
        rtnVal = FVID2_EBADARGS;
    }
    else
    {
        GT_assert(VpsHalTrace, (NULL != hndl->pInstObj));
    }

    if(FVID2_SOK == rtnVal)
    {
        if(0x0 == hndl->pInstObj->openCnt)
        {
            rtnVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        if(VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode)
        {
            rtnVal = FVID2_SOK;
            for(i = 0; ((FVID2_SOK == rtnVal) &&
                        (i < hndl->pInstObj->instCfg.numPpiInst)); i++)
            {
                if((uint32_t)FALSE != hndl->pInstObj->instCfg.ppiCfg[i].enable)
                {
                    instance = hndl->pInstObj->instCfg.ppiCfg[i].instance;
                    if(CSL_CAL_PPI_CNT < instance)
                    {
                        rtnVal = FVID2_EBADARGS;
                        break;
                    }
#ifndef ENABLE_PPI_WHEN_STARTING
                    if(1U == hndl->pInstObj->openCnt)
                    {
                        /* Last instance of open, disable PPI */
                        reg = HW_RD_REG32(hndl->pInstObj->baseAddr +
                                          CAL_CSI2_PPI_CTRL(instance));
                        reg &= ~CAL_CSI2_PPI_CTRL_IF_EN_MASK;
                        HW_WR_REG32(hndl->pInstObj->baseAddr +
                                    CAL_CSI2_PPI_CTRL(instance), reg);
                        rtnVal = FVID2_SOK;
                    }
#endif              /* ENABLE_PPI_WHEN_STARTING */
                }
            }
            for(i = 0; i < CSL_CAL_CMPLXIO_CNT; i++)
            {
                if(1U == hndl->pInstObj->openCnt)
                {
                    reg = HW_RD_REG32(hndl->pInstObj->baseAddr +
                                      CAL_CSI2_COMPLEXIO_CFG(i));
                    reg &= ~(CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK);
                    HW_WR_REG32(hndl->pInstObj->baseAddr +
                                CAL_CSI2_COMPLEXIO_CFG(i), reg);

                    /* Wait for power down completion */
                    timeOut = 0xFFFFU;
                    while(timeOut)
                    {
                        reg = HW_RD_REG32(hndl->pInstObj->baseAddr +
                                          CAL_CSI2_COMPLEXIO_CFG(i));
                        if(0U == (reg & CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK))
                        {
                            break;
                        }
                        timeOut--;
                    }
                    if(0U == timeOut)
                    {
                        /* Could not power down the PHY... */
                        rtnVal = FVID2_ETIMEOUT;
                        GT_assert(VpsHalTrace, ((uint32_t)FALSE));
                        break;
                    }
                }
            }
        }
        else if(VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode)
        {
            rtnVal = FVID2_SOK;
            if(1U == hndl->pInstObj->openCnt)
            {
                /* For the very last clos ensure that there are no pending
                    DMA reads */
                reg = HW_RD_REG32(hndl->pInstObj->baseAddr + CAL_RD_DMA_CTRL);
                if(CAL_RD_DMA_CTRL_GO_MASK == (reg & CAL_RD_DMA_CTRL_GO_MASK))
                {
                    rtnVal = FVID2_EDEVICE_INUSE;
                }
            }
        }
        else
        {
            GT_assert(VpsHalTrace,
                      (VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL != hndl->mode));
            rtnVal = FVID2_SOK;
        }
        hndl->pInstObj->openCnt--;

        hndl->mode = VPS_HAL_ISS_CAL_MODE_MIN;
    }

    return rtnVal;
}

/**************************Function Separator**********************************/
int32_t VpsHal_isscalCaptureStart(VpsHal_Handle     handle,
                                    Ptr             arg)
{
    isshalCalInstObj_t *pInstObj;
    volatile uint32_t   reg;
    uint32_t            idx, baseAddr, offset;
    isshalCalObj_t     *hndl = (isshalCalObj_t *) handle;
    int32_t rtnVal = FVID2_EBADARGS;

    if (NULL != hndl)
    {
        if (NULL != hndl->pInstObj)
        {
            if ((VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode) && (NULL != arg))
            {
                pInstObj = hndl->pInstObj;

                rtnVal = calSetWrDmaMode(pInstObj, (isshalCalDmaVcCfg_t *)arg);
#ifdef ENABLE_PPI_WHEN_STARTING
                for (idx = 0; idx < pInstObj->instCfg.numPpiInst; idx++)
                {
                    if ((uint32_t)FALSE != pInstObj->instCfg.ppiCfg[idx].enable)
                    {
                        baseAddr = pInstObj->baseAddr;
                        offset   = pInstObj->instCfg.ppiCfg[idx].instance;
                        reg      =
                            HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
                        reg |= CAL_CSI2_PPI_CTRL_IF_EN_MASK;
                        HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset),
                                    reg);
                    }
                }
#endif /* ENABLE_PPI_WHEN_STARTING */
            } /* VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode */
        } /* NULL != hndl->pInstObj */
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/
int32_t VpsHal_isscalCaptureStop(VpsHal_Handle handle, Ptr arg)
{
    isshalCalInstObj_t *pInstObj;
    volatile uint32_t   reg;
    uint32_t            idx, baseAddr, offset;
    isshalCalObj_t     *hndl = (isshalCalObj_t *) handle;
    int32_t rtnVal = FVID2_EBADARGS;

    if (NULL != hndl)
    {
        if (NULL != hndl->pInstObj)
        {
            if ((VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode) && (NULL != arg))
            {
                pInstObj = hndl->pInstObj;

                rtnVal = calSetWrDmaMode(pInstObj, (isshalCalDmaVcCfg_t *)arg);
#ifdef ENABLE_PPI_WHEN_STARTING
                /* TODO - Check if all write DMAs have been stopped.
                            Otherwise multiple handle will not work.
                            Right way would be
                            . Do it in the core
                            . If NOT the last wr context
                            . Setup to receive into 10 X 10 buffer
                            . Updated size, offset
                            . On disable of last context
                            . Setup to receive into 10 x 10 buffer,
                            . Disable PPI
                            . */

                for(idx = 0; idx < pInstObj->instCfg.numPpiInst; idx++)
                {
                    if((uint32_t)FALSE !=
                       pInstObj->instCfg.ppiCfg[idx].enable)
                    {
                        baseAddr = pInstObj->baseAddr;
                        offset   = pInstObj->instCfg.ppiCfg[idx].instance;
                        reg      =
                            HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
                        reg &= ~((UInt32) CAL_CSI2_PPI_CTRL_IF_EN_MASK);
                        HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset),
                                    reg);
                    }
                }
#endif          /* ENABLE_PPI_WHEN_STARTING */
            }
        }
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/
int32_t VpsHal_isscalUpdateBufAddr(VpsHal_Handle          handle,
                                   const isshalCalBufferAddr_t *bufPtrs)
{
    volatile uint32_t       reg;
    uint32_t                idx, baseAddr;
    int32_t                 rtnVal = FVID2_EBADARGS;
    isshalCalObj_t          *hndl = (isshalCalObj_t *) handle;

    if (NULL != hndl)
    {
        if(NULL != hndl->pInstObj)
        {
            if (NULL != bufPtrs)
            {
                rtnVal = FVID2_SOK;
                for(idx = 0U; idx < bufPtrs->numBuff; idx++)
                {
                    if((uint32_t)0U == (uint32_t)bufPtrs->buffAddr[idx])
                    {
                        rtnVal = FVID2_EBADARGS;
                    }
                    if((VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode) ||
                       (VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode))
                    {
                        if(VPS_ISS_CAL_MAX_STREAMS <= bufPtrs->wrDmaCtx[idx])
                        {
                            rtnVal = FVID2_EBADARGS;
                        }
                    }

                    if(FVID2_SOK != rtnVal)
                    {
                        break;
                    }

                    baseAddr = hndl->pInstObj->baseAddr;
                    if(((uint32_t)0x0 == (uint32_t)bufPtrs->cPortId[idx]) &&
                       (VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode))
                    {
                        reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_PIX_ADDR);
                        reg &= ~CAL_RD_DMA_PIX_ADDR_MASK;
                        reg |= CAL_RD_DMA_PIX_ADDR_MASK &
                               bufPtrs->buffAddr[idx];
                        HW_WR_REG32(baseAddr + CAL_RD_DMA_PIX_ADDR, reg);

                        reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_PIX_OFST);
                        reg &= ~CAL_RD_DMA_PIX_OFST_MASK;
                        reg |= CAL_RD_DMA_PIX_OFST_MASK &
                               bufPtrs->pitch[idx];
                        HW_WR_REG32(baseAddr + CAL_RD_DMA_PIX_OFST, reg);
                    }

                    if((VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode) ||
                       (VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode))
                    {
                        reg = HW_RD_REG32(baseAddr +
                                          CAL_WR_DMA_ADRR(bufPtrs->wrDmaCtx
                                                          [idx]));
                        reg &= ~CAL_WR_DMA_ADRR_ADDR_MASK;
                        reg |= CAL_WR_DMA_ADRR_ADDR_MASK &
                               bufPtrs->buffAddr[idx];
                        HW_WR_REG32(baseAddr +
                                    CAL_WR_DMA_ADRR(
                                        bufPtrs->wrDmaCtx[idx]), reg);
                    }
                }
            }
        }
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalRdDmaStart(VpsHal_Handle     handle,
                                issCtrlProcMode_t procMode,
                                Ptr               arg)
{
    int32_t             rtnVal = FVID2_SOK;
    volatile uint32_t   reg;
    isshalCalInstObj_t *pInstObj;
    isshalCalObj_t     *hndl = (isshalCalObj_t *) handle;

    if(NULL == hndl)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (NULL == hndl->pInstObj))
    {
        rtnVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == rtnVal)
    {
        pInstObj = hndl->pInstObj;

        rtnVal = FVID2_EAGAIN;

        reg = HW_RD_REG32(pInstObj->baseAddr + CAL_RD_DMA_CTRL);
        if(CAL_RD_DMA_CTRL_GO_MASK != (reg & CAL_RD_DMA_CTRL_GO_MASK))
        {
            reg   |= CAL_RD_DMA_CTRL_GO_MASK;
            rtnVal = FVID2_SOK;
            HW_WR_REG32(pInstObj->baseAddr + CAL_RD_DMA_CTRL, reg);
        }
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalControl(VpsHal_Handle handle,
                             UInt32        cmd,
                             Ptr           cmdArgs,
                             Ptr           arg)
{
    isshalCalInstObj_t    *pInstObj;
    isshalCalObj_t        *hndl = (isshalCalObj_t *) handle;

    int32_t rtnVal = FVID2_SOK;

    if(NULL == hndl)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (NULL != hndl->pInstObj))
    {
        pInstObj = hndl->pInstObj;
    }
    else
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (NULL == pInstObj->baseAddr))
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (0x0 == pInstObj->openCnt))
    {
        rtnVal = FVID2_EFAIL;
    }

    if(FVID2_SOK == rtnVal)
    {
        switch(cmd)
        {
            case VPS_HAL_ISS_IOCTL_CAL_UPDATE_BUFFERS:
                rtnVal = FVID2_EBADARGS;
                break;

            case VPS_HAL_ISS_IOCTL_CAL_RD_FMT_UPDATE:
                rtnVal = CalSetRdDmaFrameCfg(pInstObj, (Fvid2_Format *)cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_START:
                rtnVal = VpsHal_isscalCaptureStart (handle, cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_STOP:
                rtnVal = VpsHal_isscalCaptureStop (handle, cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_CAL_SETCFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalSetCfg(hndl, (isshalCalCfg_t *) cmdArgs);
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_CAL_GET_INSTANCECFG:
                if(NULL != cmdArgs)
                {
                    BspUtils_memcpy((Ptr) cmdArgs,
                                    (const void *) &hndl->pInstObj->instCfg,
                                    sizeof(isshalCalInstCfg_t));
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_CAL_SET_INSTANCECFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalResetApplyInstConfig(
                        hndl,
                        (isshalCalInstCfg_t *)
                        cmdArgs,
                        hndl->mode,
                        (uint32_t)TRUE);

                    if(FVID2_SOK == rtnVal)
                    {
                        BspUtils_memcpy((Ptr) & hndl->pInstObj->instCfg,
                                        (const void *) cmdArgs,
                                        sizeof(isshalCalInstCfg_t));
                    }
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;
            case VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalSetVportCfg(
                        hndl->pInstObj,
                        (vpsissCalVPort_t *) cmdArgs,
                        *(uint32_t *) arg);
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;
            case VPS_HAL_ISS_IOCTL_CAL_SET_BYSOUT_CFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalSetBysOutCfg(
                        hndl->pInstObj,
                        (vpsissCalBysOut_t *) cmdArgs,
                        *(uint32_t *) arg);
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_CAL_LINE_EVENT_CFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalSetLineEventCfg(hndl->pInstObj,
                                        (isshalCalLineEventCfg_t *) cmdArgs);
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            default:
                rtnVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (rtnVal);
}

uint32_t VpsHal_calIsBysOutEof(VpsHal_Handle handle)
{
    uint32_t rtnVal = 0;
    uint32_t baseAddr;
    isshalCalObj_t *hndl = (isshalCalObj_t *) handle;

    if ((NULL == hndl) || (NULL == hndl->pInstObj) ||
        (NULL == hndl->pInstObj->baseAddr) || (0x0 == hndl->pInstObj->openCnt))
    {
        rtnVal = 0;
    }
    else
    {
        baseAddr = hndl->pInstObj->baseAddr;
        rtnVal = (HW_RD_REG32(baseAddr + CAL_HL_IRQSTATUS_RAW(0U)) &
            CAL_HL_IRQSTATUS_RAW_IRQ3_MASK) >> CAL_HL_IRQSTATUS_RAW_IRQ3_SHIFT;
    }

    return (rtnVal);
}

void VpsHal_calClearVportEof(VpsHal_Handle handle)
{
    isshalCalObj_t *hndl = (isshalCalObj_t *) handle;
    uint32_t baseAddr;
    uint32_t regVal;

    if ((NULL == hndl) || (NULL == hndl->pInstObj) ||
        (NULL == hndl->pInstObj->baseAddr) || (0x0 == hndl->pInstObj->openCnt))
    {
        /* Do Nothing */
    }
    else
    {
        baseAddr = hndl->pInstObj->baseAddr;
        regVal = HW_RD_REG32(baseAddr + CAL_HL_IRQSTATUS_RAW(0U));
        regVal |= CAL_HL_IRQSTATUS_RAW_IRQ2_MASK;
        HW_WR_REG32(baseAddr + CAL_HL_IRQSTATUS_RAW(0U), regVal);
    }
}

uint32_t VpsHal_calIsVportEof(VpsHal_Handle handle)
{
    uint32_t rtnVal = 0;
    isshalCalObj_t *hndl = (isshalCalObj_t *) handle;
    uint32_t baseAddr;

    if ((NULL == hndl) || (NULL == hndl->pInstObj) ||
        (NULL == hndl->pInstObj->baseAddr) || (0x0 == hndl->pInstObj->openCnt))
    {
        rtnVal = 0;
    }
    else
    {
        baseAddr = hndl->pInstObj->baseAddr;
        rtnVal = (HW_RD_REG32(baseAddr + CAL_HL_IRQSTATUS_RAW(0U)) &
            CAL_HL_IRQSTATUS_RAW_IRQ2_MASK) >> CAL_HL_IRQSTATUS_RAW_IRQ2_SHIFT;
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t CalReset(uint32_t baseAddr)
{
    int32_t           rtnVal = FVID2_SOK;
    volatile uint32_t reg, timeOut;

    GT_assert(VpsHalTrace, (0U != baseAddr));
    timeOut = 0xFFFFU;
    reg     = HW_RD_REG32(baseAddr + CAL_HL_SYSCONFIG);

    reg &= ~((UInt32) CAL_HL_SYSCONFIG_IDLEMODE_MASK);
    reg |= CAL_HL_SYSCONFIG_IDLEMODE_MASK & ((UInt32) CAL_HL_SYSCONFIG_IDLEMODE_NO <<
                                             CAL_HL_SYSCONFIG_IDLEMODE_SHIFT);

    reg |= CAL_HL_SYSCONFIG_SOFTRESET_MASK;
    HW_WR_REG32(baseAddr + CAL_HL_SYSCONFIG, reg);

    while(timeOut)
    {
        reg = HW_RD_REG32(baseAddr + CAL_HL_SYSCONFIG);
        if(CAL_HL_SYSCONFIG_SOFTRESET_MASK !=
           (reg & CAL_HL_SYSCONFIG_SOFTRESET_MASK))
        {
            break;
        }

        timeOut--;
    }

    /* If reset is not done, timeOut will be zero, so only one
       condition check required here
       If reset is done, this condition is anyway false. */
    if((reg & CAL_HL_SYSCONFIG_SOFTRESET_MASK) ==
       CAL_HL_SYSCONFIG_SOFTRESET_MASK)
    {
        /* Reset did not complete. We would require an  PRCM reset now! */
        rtnVal = FVID2_ETIMEOUT;
    }
    return rtnVal;
}

/**************************Function Separator**********************************/

static int32_t CalCfgInstWrDma(
    uint32_t baseAddr, const isshalCalInstCfg_t *pCfg)
{
    volatile uint32_t reg;
    reg  = HW_RD_REG32(baseAddr + CAL_CTRL);
    reg &= ~(CAL_CTRL_POSTED_WRITES_MASK | CAL_CTRL_TAGCNT_MASK |
             CAL_CTRL_BURSTSIZE_MASK | CAL_CTRL_MFLAGL_MASK |
             CAL_CTRL_PWRSCPCLK_MASK | CAL_CTRL_RD_DMA_STALL_MASK |
             CAL_CTRL_MFLAGH_MASK);

    reg |= CAL_CTRL_MFLAGH_MASK & (pCfg->mFlagH << CAL_CTRL_MFLAGH_SHIFT);

    if((uint32_t)TRUE == pCfg->rdDmaStall)
    {
        reg |= CAL_CTRL_RD_DMA_STALL_MASK;
    }

    if((uint32_t)TRUE == pCfg->pwrScpClk)
    {
        reg |= CAL_CTRL_PWRSCPCLK_MASK;
    }

    reg |= CAL_CTRL_MFLAGL_MASK & (pCfg->mFlagL << CAL_CTRL_MFLAGL_SHIFT);

    reg |= CAL_CTRL_BURSTSIZE_MASK &
           (pCfg->dmaBurstSize << CAL_CTRL_BURSTSIZE_SHIFT);

    reg |= CAL_CTRL_TAGCNT_MASK & (pCfg->tagCnt << CAL_CTRL_TAGCNT_SHIFT);

    if((uint32_t)TRUE == pCfg->postedWrites)
    {
        reg |= CAL_CTRL_POSTED_WRITES_MASK;
    }

    HW_WR_REG32(baseAddr + CAL_CTRL, reg);

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalCfgInstLanePpiCfg(uint32_t baseAddr, isshalCalInstCfg_t *pCfg)
{
    uint32_t               offset, idx;
    volatile uint32_t      reg;
    vpsissCalCmplxIoCfg_t *pCmplxIoCfg;
    int32_t rtnVal = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != pCfg));
    GT_assert(VpsHalTrace, (CSL_CAL_PPI_CNT >= pCfg->numPpiInst));
    GT_assert(VpsHalTrace, (CSL_CAL_CMPLXIO_CNT >= pCfg->numCmplxIoInst));

    /* Lane Config */
    offset = 0x0;
    for(idx = 0; idx < pCfg->numCmplxIoInst; idx++)
    {
        pCmplxIoCfg = &pCfg->cmplxIoCfg[idx];

        /* Setup the polarity of lanes */
        if((uint32_t)TRUE == pCmplxIoCfg->enable)
        {
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg &= ~(CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK);
            reg &= ~(CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MASK);
            reg |= CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK &
                   pCmplxIoCfg->clockLane.position;
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK &
                   (pCmplxIoCfg->data1Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK &
                   (pCmplxIoCfg->data2Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK &
                   (pCmplxIoCfg->data3Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK &
                   (pCmplxIoCfg->data4Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_SHIFT);

            reg |= CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK &
                   (pCmplxIoCfg->clockLane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MASK &
                   (pCmplxIoCfg->data1Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MASK &
                   (pCmplxIoCfg->data2Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MASK &
                   (pCmplxIoCfg->data3Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MASK &
                   (pCmplxIoCfg->data4Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);

            /* Dummy read to wait for SCP write to complete */
            reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
        }
    }
    /* PPI Config */
    offset = 0x0;
    for(idx = 0; idx < pCfg->numPpiInst; idx++)
    {
        if((uint32_t)FALSE != pCfg->ppiCfg[idx].enable)
        {
            offset = pCfg->ppiCfg[idx].instance;
            if(CSL_CAL_PPI_CNT < offset)
            {
                rtnVal = FVID2_EBADARGS;
                break;
            }

            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
            reg &= ~((UInt32) (CAL_CSI2_PPI_CTRL_IF_EN_MASK |
                               CAL_CSI2_PPI_CTRL_FRAME_MASK |
                               CAL_CSI2_PPI_CTRL_ECC_EN_MASK));

            if((uint32_t)TRUE == pCfg->ppiCfg[idx].ecc)
            {
                reg |= CAL_CSI2_PPI_CTRL_ECC_EN_MASK;
            }
            if((uint32_t)TRUE == pCfg->ppiCfg[idx].frame)
            {
                reg |= CAL_CSI2_PPI_CTRL_FRAME_MASK;
            }
            HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset), reg);

#ifndef ENABLE_PPI_WHEN_STARTING
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
            reg |= CAL_CSI2_PPI_CTRL_IF_EN_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset), reg);
#endif      /* ENABLE_PPI_WHEN_STARTING */
        }
    }
    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t CalResetApplyInstConfig(const isshalCalObj_t *pHndl,
                                       isshalCalInstCfg_t   *pCfg,
                                       isshalCalMode_t       mode,
                                       uint32_t             enPhy)
{
    int32_t             rtnVal = FVID2_SOK;
    isshalCalInstObj_t *pInst  = NULL;
    volatile uint32_t   reg, baseAddr;

    GT_assert(VpsHalTrace, (NULL != pHndl));
    GT_assert(VpsHalTrace, (NULL != pCfg));
    GT_assert(VpsHalTrace, (NULL != pHndl->pInstObj));

    pInst = pHndl->pInstObj;
    GT_assert(VpsHalTrace, (NULL != pInst->baseAddr));
    baseAddr = pInst->baseAddr;

    /* In Case of M2M mode,
     *      . Reset CAL
     *      . Apply M2M specifics
     * In Case of capture via CSI2 / LVDS (CPI)
     *      . Reset CAL
     *      . Configure generic CAL / DMA write config
     *      . Configure lane and PPI
     *      . Enable Clock to PHY and Reset the same
     */
    /* . Reset CAL */
    rtnVal = CalReset(baseAddr);
    /* . Apply M2M config */
    if((FVID2_SOK == rtnVal) && (VPS_HAL_ISS_CAL_MODE_M2M == mode))
    {
        reg  = HW_RD_REG32(baseAddr + CAL_CTRL);
        reg &= ~(CAL_CTRL_RD_DMA_STALL_MASK | CAL_CTRL_PWRSCPCLK_MASK |
                 CAL_CTRL_TAGCNT_MASK);

        if((uint32_t)TRUE == pCfg->rdDmaStall)
        {
            reg |= CAL_CTRL_RD_DMA_STALL_MASK;
        }
        if((uint32_t)TRUE == pCfg->pwrScpClk)
        {
            reg |= CAL_CTRL_PWRSCPCLK_MASK;
        }

        reg |= CAL_CTRL_TAGCNT_MASK & (pCfg->tagCnt << CAL_CTRL_TAGCNT_SHIFT);

        HW_WR_REG32(baseAddr + CAL_CTRL, reg);
    }
    else if(VPS_HAL_ISS_CAL_MODE_CAPTURE == mode)
    {
        GT_assert(VpsHalTrace, (NULL != pInst->phy0BaseAddress));
        /* Important to configure RD DMA stall config, as m2m mode will not be
         *  worried about this, but write will definitely be */
        rtnVal = CalCfgInstWrDma(baseAddr, pCfg);

        if(FVID2_SOK == rtnVal)
        {
            rtnVal = CalCfgInstLanePpiCfg(baseAddr, pCfg);
        }

        if((FVID2_SOK == rtnVal) && ((uint32_t)TRUE == enPhy))
        {
            rtnVal = VpsHal_calPhyEnClockAndReset(baseAddr,
                                                  pInst->phy0BaseAddress,
                                                  pInst->phy1BaseAddress,
                                                  pCfg);
        }
    }
    else if(VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL == mode)
    {
        /* TBD */
        rtnVal = FVID2_EBADARGS;
    }
    else
    {
        rtnVal = FVID2_EBADARGS;
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t CalSetCfg(const isshalCalObj_t *hndl, const isshalCalCfg_t *cfg)
{
    /*
     *  .Configure Capture
     *  .Configure M2M
     *  .Configure Complex IO TODO TBD
     */
    int32_t rtnVal = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != hndl));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (NULL != hndl->pInstObj));

    if(0x0 == hndl->pInstObj->openCnt)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == rtnVal)
    {
        if(VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode)
        {
            rtnVal = CalSetCfgForMode(hndl->pInstObj, cfg, hndl->mode);
        }
        else if(VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode)
        {
            rtnVal = CalSetCfgForMode(hndl->pInstObj, cfg, hndl->mode);
        }
        else if(VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL == hndl->mode)
        {
            GT_assert(VpsHalTrace, ((uint32_t)FALSE));
            /* TODO TBD implement complex IO config apply */
        }
        else
        {
            /* Wrong mode, but why? */
            rtnVal = FVID2_EBADARGS;
        }
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetCfgForMode(const isshalCalInstObj_t *pInst,
                                const isshalCalCfg_t     *cfg,
                                isshalCalMode_t           mode)
{
    int32_t              rtnVal = FVID2_SOK;
    uint32_t             baseAddr, cId, idx;
    volatile uint32_t    reg;
    isshalCalDmaVcCfg_t *pDmaCfg = (isshalCalDmaVcCfg_t *) cfg->pDmaVcCfg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (NULL != pDmaCfg));

    baseAddr = pInst->baseAddr;

    /* Ensure there are no pending reads */
    reg = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL);
    if(((reg & CAL_RD_DMA_CTRL_GO_MASK) == CAL_RD_DMA_CTRL_GO_MASK) &&
       (VPS_HAL_ISS_CAL_MODE_M2M == mode))
    {
        rtnVal = FVID2_EAGAIN;
    }

    for(idx = 0; ((FVID2_SOK == rtnVal) && (idx < cfg->numCPortId)); idx++)
    {
        cId = cfg->cportId[idx];
        GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_STREAMS > cId));

        if(((uint32_t)TRUE == pDmaCfg->isCsi2VcCfgValid[idx]) &&
           (VPS_HAL_ISS_CAL_MODE_CAPTURE == mode))
        {
            rtnVal = CalCsi2VcCfg(pInst, &pDmaCfg->csi2VcCfg[idx], cId);
        }
        if((uint32_t)TRUE == cfg->isPixProcCfgValid[idx])
        {
            rtnVal = CalSetPixProcCfg(pInst, &cfg->pixProcCfg[idx], cId);
        }
        if((uint32_t)TRUE == pDmaCfg->isWrDmaCfgValid[idx])
        {
            /* CFG WR DMA */
            rtnVal = CalSetWrDmaCfg(pInst, &pDmaCfg->wrDmaCfg[idx], cId);
        }
        if((uint32_t)TRUE == cfg->isBysOutCfgValid[idx])
        {
            /* CFG BYS Out */
            rtnVal = CalSetBysOutCfg(pInst, &cfg->bysOutCfg[idx], cId);
        }
        if((uint32_t)TRUE == cfg->isBysInCfgValid[idx])
        {
            /* CFG BYS In */
            if((uint32_t)TRUE == cfg->bysInEnable[idx])
            {
                reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL2);
                reg &= ~((UInt32) CAL_BYS_CTRL2_CPORTIN_MASK);
                reg |= CAL_BYS_CTRL2_CPORTIN_MASK & cId;
                HW_WR_REG32(baseAddr + CAL_BYS_CTRL2, reg);

                reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL1);
                reg |= CAL_BYS_CTRL1_BYSINEN_MASK;
                HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);
            }
            else
            {
                reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL1);
                reg &= ~CAL_BYS_CTRL1_BYSINEN_MASK;
                HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);
            }
        }
        if((uint32_t)TRUE == cfg->isVportCfgValid[idx])
        {
            /* CFG VP in */
            rtnVal = CalSetVportCfg(pInst, &cfg->vportCfg[idx], cId);
        }
        if((uint32_t)TRUE == pDmaCfg->isRdDmaCfgValid[idx])
        {
            /* CFG Read DMA */
            rtnVal = CalSetRdDmaCfg(pInst, &pDmaCfg->rdDmaCfg[idx], cId);
        }
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

static int32_t CalCsi2VcCfg(const isshalCalInstObj_t   *pInst,
                            const isshalCalCsi2VcCfg_t *cfg,
                            uint32_t                    cportId)
{
    int32_t           rtnVal = FVID2_SOK;
    uint32_t          baseAddr, instance, context;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    instance = cfg->instance;
    context  = cfg->contextToBeUsed;
    GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_STREAMS > context));
    GT_assert(VpsHalTrace, ((0x0U == instance) || (0x1U == instance)));

    reg = HW_RD_REG32(baseAddr + CAL_CSI2_CTX0(instance) + (context * 4U));

    reg &= ~(CAL_CSI2_CTX0_DT_MASK | CAL_CSI2_CTX0_VC_MASK |
             CAL_CSI2_CTX0_CPORT_MASK | CAL_CSI2_CTX0_ATT_MASK |
             CAL_CSI2_CTX0_PACK_MODE_MASK | CAL_CSI2_CTX0_LINES_MASK);

    reg |= CAL_CSI2_CTX0_LINES_MASK & (cfg->lines << CAL_CSI2_CTX0_LINES_SHIFT);

    /* TODO Remove the hard-coding, get appropriate macros */
    if((cfg->dt < 0x17) && (cfg->dt != 0x1))
    {
        /* When receiving non-pixel data would be packed between FS and FE.
         *  no notion of LS & LE.
         * else
         *  Pixel typically line boundaries is specified. Data is packed between
         *      LS & LE.
         */
        reg |= CAL_CSI2_CTX0_PACK_MODE_MASK;
    }

    reg |= CAL_CSI2_CTX0_ATT_MASK & (cfg->att << CAL_CSI2_CTX0_ATT_SHIFT);
    reg |= CAL_CSI2_CTX0_CPORT_MASK & (cportId << CAL_CSI2_CTX0_CPORT_SHIFT);
    reg |= CAL_CSI2_CTX0_VC_MASK & (cfg->virtualChanNum <<
                                    CAL_CSI2_CTX0_VC_SHIFT);
    reg |= CAL_CSI2_CTX0_DT_MASK & (cfg->dt << CAL_CSI2_CTX0_DT_SHIFT);

    HW_WR_REG32(baseAddr + CAL_CSI2_CTX0(instance) + (context * 4U), reg);
    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t CalSetPixProcCfg(const isshalCalInstObj_t *pInst,
                                const vpsissCalPixProc_t *cfg, uint32_t cportId)
{
    int32_t           rtnVal = FVID2_SOK;
    uint32_t          baseAddr, context;
    uint32_t          extract;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    context  = cfg->contextToBeUsed;
    extract  = cfg->extract;
    extract--;

    if(context >= CSL_CAL_PIX_PROC_CTX_CNT)
    {
        rtnVal = FVID2_EINVALID_PARAMS;
    }
    else
    {
        reg  = HW_RD_REG32(baseAddr + CAL_PIX_PROC(context));
        reg &= ~((UInt32) CAL_PIX_PROC_EN_MASK);
        HW_WR_REG32(baseAddr + CAL_PIX_PROC(context), reg);

        reg  = HW_RD_REG32(baseAddr + CAL_PIX_PROC(context));
        reg &= ~(CAL_PIX_PROC_EXTRACT_MASK | CAL_PIX_PROC_DPCMD_MASK |
                 CAL_PIX_PROC_DPCME_MASK | CAL_PIX_PROC_PACK_MASK |
                 CAL_PIX_PROC_CPORT_MASK);

        GT_assert(VpsHalTrace, (VPS_ISS_CAL_PIX_EXRCT_MIN != cfg->extract));
        GT_assert(VpsHalTrace, (VPS_ISS_CAL_PIX_EXRCT_MAX >= cfg->extract));
        reg |= CAL_PIX_PROC_EXTRACT_MASK &
               ((extract) << CAL_PIX_PROC_EXTRACT_SHIFT);

        reg |= CAL_PIX_PROC_DPCMD_MASK &
               (cfg->decCodec << CAL_PIX_PROC_DPCMD_SHIFT);

        reg |= CAL_PIX_PROC_DPCME_MASK &
               (cfg->encCodec << CAL_PIX_PROC_DPCME_SHIFT);

        reg |= CAL_PIX_PROC_PACK_MASK & (cfg->pack << CAL_PIX_PROC_PACK_SHIFT);
        reg |= CAL_PIX_PROC_CPORT_MASK & (cportId << CAL_PIX_PROC_CPORT_SHIFT);

        HW_WR_REG32(baseAddr + CAL_PIX_PROC(context), reg);

        reg = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL);
        if((uint32_t)TRUE == cfg->enableDpcmInitContext)
        {
            reg |= CAL_RD_DMA_CTRL_INIT_MASK;
            GT_assert(VpsHalTrace, (NULL != cfg->addr));
        }
        else
        {
            reg &= ~((UInt32) CAL_RD_DMA_CTRL_INIT_MASK);
        }
        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL, reg);

        if((uint32_t)TRUE == cfg->enableDpcmInitContext)
        {
            reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_INIT_ADDR);
            reg &= ~CAL_RD_DMA_INIT_ADDR_MASK;
            reg |= CAL_RD_DMA_INIT_ADDR_MASK & cfg->addr;
            HW_WR_REG32(baseAddr + CAL_RD_DMA_INIT_ADDR, reg);

            reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_INIT_OFST);
            reg &= ~CAL_RD_DMA_INIT_OFST_MASK;
            reg |= CAL_RD_DMA_INIT_OFST_MASK & cfg->offSet;
            HW_WR_REG32(baseAddr + CAL_RD_DMA_INIT_OFST, reg);
        }

        /* Enable Pixel Processing, as a last step */
        reg  = HW_RD_REG32(baseAddr + CAL_PIX_PROC(context));
        reg |= CAL_PIX_PROC_EN_MASK;
        HW_WR_REG32(baseAddr + CAL_PIX_PROC(context), reg);
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

static int32_t CalSetBysOutCfg(const isshalCalInstObj_t *pInst,
                               const vpsissCalBysOut_t *cfg, uint32_t cportId)
{
    uint32_t          baseAddr;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL1);
    reg &= ~CAL_BYS_CTRL1_PCLK_MASK;
    if((uint32_t)TRUE == cfg->enable)
    {
        reg &= ~(CAL_BYS_CTRL1_XBLK_MASK | CAL_BYS_CTRL1_YBLK_MASK);

        reg |= CAL_BYS_CTRL1_PCLK_MASK &
               (cfg->pixClock << CAL_BYS_CTRL1_PCLK_SHIFT);

        reg |= CAL_BYS_CTRL1_XBLK_MASK &
               (cfg->xBlk << CAL_BYS_CTRL1_XBLK_SHIFT);

        reg |= CAL_BYS_CTRL1_YBLK_MASK &
               (cfg->yBlk << CAL_BYS_CTRL1_YBLK_SHIFT);
        HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);

        reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL2);
        reg &= ~((UInt32) (CAL_BYS_CTRL2_CPORTOUT_MASK |
                           CAL_BYS_CTRL2_DUPLICATEDDATA_MASK |
                           CAL_BYS_CTRL2_FREERUNNING_MASK));
        if((uint32_t)TRUE == cfg->freeRun)
        {
            reg |= CAL_BYS_CTRL2_FREERUNNING_MASK;
        }

        if((uint32_t)TRUE == cfg->copyStreamToEncode)
        {
            reg |= CAL_BYS_CTRL2_DUPLICATEDDATA_MASK;
        }

        reg |= CAL_BYS_CTRL2_CPORTOUT_MASK &
               (cportId << CAL_BYS_CTRL2_CPORTOUT_SHIFT);

        HW_WR_REG32(baseAddr + CAL_BYS_CTRL2, reg);
    }
    else
    {
        HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetVportCfg(const isshalCalInstObj_t *pInst,
                              const vpsissCalVPort_t   *cfg,
                              uint32_t                  cportId)
{
    uint32_t          baseAddr;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    reg  = HW_RD_REG32(baseAddr + CAL_VPORT_CTRL1);
    reg &= ~CAL_VPORT_CTRL1_PCLK_MASK;
    if((uint32_t)TRUE == cfg->enable)
    {
        reg &= ~(CAL_VPORT_CTRL1_XBLK_MASK | CAL_VPORT_CTRL1_YBLK_MASK |
                 CAL_VPORT_CTRL1_WIDTH_MASK);

        reg |= CAL_VPORT_CTRL1_PCLK_MASK & cfg->pixClock;

        reg |= CAL_VPORT_CTRL1_XBLK_MASK &
               (cfg->xBlk << CAL_VPORT_CTRL1_XBLK_SHIFT);

        reg |= CAL_VPORT_CTRL1_YBLK_MASK &
               (cfg->yBlk << CAL_VPORT_CTRL1_YBLK_SHIFT);

        if(0x0U != cfg->width)
        {
            reg |= CAL_VPORT_CTRL1_WIDTH_MASK;
        }
        HW_WR_REG32(baseAddr + CAL_VPORT_CTRL1, reg);

        reg  = HW_RD_REG32(baseAddr + CAL_VPORT_CTRL2);
        reg &=
            ~(CAL_VPORT_CTRL2_RDY_THR_MASK | CAL_VPORT_CTRL2_FSM_RESET_MASK |
              CAL_VPORT_CTRL2_FS_RESETS_MASK |
              CAL_VPORT_CTRL2_FREERUNNING_MASK |
              CAL_VPORT_CTRL2_CPORT_MASK);

        reg |= CAL_VPORT_CTRL2_CPORT_MASK & cportId;

        if((uint32_t)TRUE == cfg->freeRun)
        {
            reg |= CAL_VPORT_CTRL2_FREERUNNING_MASK;
        }

        if((uint32_t)TRUE == cfg->fsReset)
        {
            reg |= CAL_VPORT_CTRL2_FS_RESETS_MASK;
        }

        reg |= CAL_VPORT_CTRL2_RDY_THR_MASK &
               (cfg->rdyThr << CAL_VPORT_CTRL2_RDY_THR_SHIFT);

        HW_WR_REG32(baseAddr + CAL_VPORT_CTRL2, reg);
    }
    else
    {
        HW_WR_REG32(baseAddr + CAL_VPORT_CTRL1, reg);
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetRdDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalRdDmaCfg_t *cfg,
                              uint32_t                   cportId)
{
    uint32_t          baseAddr;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL);
    reg &= ~CAL_RD_DMA_CTRL_PCLK_MASK;

    if((uint32_t)TRUE == cfg->enable)
    {
        reg &= ~((UInt32) (CAL_RD_DMA_CTRL_GO_MASK |
                           CAL_RD_DMA_CTRL_BW_LIMITER_MASK |
                           CAL_RD_DMA_CTRL_OCP_TAG_CNT_MASK));

        reg |= CAL_RD_DMA_CTRL_BW_LIMITER_MASK &
               (cfg->bwLimit << CAL_RD_DMA_CTRL_BW_LIMITER_SHIFT);

        reg |= CAL_RD_DMA_CTRL_OCP_TAG_CNT_MASK &
               (cfg->ocpTagCnt << CAL_RD_DMA_CTRL_OCP_TAG_CNT_SHIFT);

        reg |= CAL_RD_DMA_CTRL_PCLK_MASK &
               (cfg->pixClock << CAL_RD_DMA_CTRL_PCLK_SHIFT);

        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL, reg);

        reg = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL2);

        reg &= ~(CAL_RD_DMA_CTRL2_CIRC_MODE_MASK |
                 CAL_RD_DMA_CTRL2_CIRC_SIZE_MASK |
                 CAL_RD_DMA_CTRL2_ICM_CSTART_MASK |
                 CAL_RD_DMA_CTRL2_PATTERN_MASK |
                 CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_MASK);
        reg |= CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_MASK &
               (cfg->bysOutLeWait << CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_SHIFT);

        reg |= CAL_RD_DMA_CTRL2_PATTERN_MASK &
               (cfg->ySkipMode << CAL_RD_DMA_CTRL2_PATTERN_SHIFT);

        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL2, reg);

        CalSetRdDmaFrameCfg(pInst, &cfg->format);
    }
    else
    {
        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL, reg);
    }
    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetRdDmaFrameCfg(const isshalCalInstObj_t *pInst,
                                   const Fvid2_Format       *cfg)
{
    uint32_t          baseAddr;
    uint32_t          hSize;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    if((FVID2_BPP_BITS10 == cfg->bpp) ||
       (FVID2_BPP_BITS11 == cfg->bpp) ||
       (FVID2_BPP_BITS12 == cfg->bpp) ||
       (FVID2_BPP_BITS13 == cfg->bpp) ||
       (FVID2_BPP_BITS14 == cfg->bpp) ||
       (FVID2_BPP_BITS15 == cfg->bpp) ||
       (FVID2_BPP_BITS16 == cfg->bpp))
    {
        hSize = ((cfg->width * 2U) / 8U);
    }
    else
    {
        hSize = (cfg->width / 8U);
    }

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_XSIZE);
    reg &= ~CAL_RD_DMA_XSIZE_MASK;
    /* Require to specify the number of 64 bits read, essentially
     *  total bits / 64 or byte count / 8 */
    reg |= CAL_RD_DMA_XSIZE_MASK & ((hSize) << CAL_RD_DMA_XSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_RD_DMA_XSIZE, reg);

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_YSIZE);
    reg &= ~CAL_RD_DMA_YSIZE_MASK;
    reg |= CAL_RD_DMA_YSIZE_MASK & (cfg->height << CAL_RD_DMA_YSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_RD_DMA_YSIZE, reg);

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_PIX_OFST);
    reg &= ~CAL_RD_DMA_PIX_OFST_MASK;
    reg |= (CAL_RD_DMA_PIX_OFST_MASK & cfg->pitch[0U]);

    HW_WR_REG32(baseAddr + CAL_RD_DMA_PIX_OFST, reg);

    return FVID2_SOK;
}


/**************************Function Separator**********************************/

/**
 * \brief   Applies DMA Write configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for DMA Write.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetWrDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalWrDmaCfg_t *cfg,
                              uint32_t                   cportId)
{
    uint32_t          baseAddr, context;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    context  = cfg->contextToBeUsed;
    GT_assert(VpsHalTrace, (0U != baseAddr));
    GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_STREAMS > context));

    reg  = HW_RD_REG32(baseAddr + CAL_WR_DMA_CTRL(context));
    reg &= ~(CAL_WR_DMA_CTRL_YSIZE_MASK | CAL_WR_DMA_CTRL_STALL_RD_DMA_MASK |
             CAL_WR_DMA_CTRL_CPORT_MASK | CAL_WR_DMA_CTRL_DTAG_MASK |
             CAL_WR_DMA_CTRL_WR_PATTERN_MASK | CAL_WR_DMA_CTRL_MODE_MASK);

    reg |= CAL_WR_DMA_CTRL_MODE_MASK & cfg->mode;

    reg |= CAL_WR_DMA_CTRL_WR_PATTERN_MASK &
           (cfg->ySkipMode << CAL_WR_DMA_CTRL_WR_PATTERN_SHIFT);

    reg |= CAL_WR_DMA_CTRL_DTAG_MASK &
           (cfg->stream << CAL_WR_DMA_CTRL_DTAG_SHIFT);

    reg |= CAL_WR_DMA_CTRL_CPORT_MASK &
           (cportId << CAL_WR_DMA_CTRL_CPORT_SHIFT);

    reg |= CAL_WR_DMA_CTRL_STALL_RD_DMA_MASK &
           (cfg->stallM2MRd << CAL_WR_DMA_CTRL_STALL_RD_DMA_SHIFT);

    reg |= CAL_WR_DMA_CTRL_YSIZE_MASK &
           (cfg->format.height << CAL_WR_DMA_CTRL_YSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_WR_DMA_CTRL(context), reg);

    reg  = HW_RD_REG32(baseAddr + CAL_WR_DMA_OFST(context));
    reg &= ~CAL_WR_DMA_OFST_OFFST_MASK;
    /* No support for circular mode as of now */
    reg &= ~(CAL_WR_DMA_OFST_CIRC_MODE_MASK | CAL_WR_DMA_OFST_CIRC_SIZE_MASK);
    /* Shifting is not required */
    reg |= CAL_WR_DMA_OFST_OFFST_MASK & cfg->format.pitch[0];
    HW_WR_REG32(baseAddr + CAL_WR_DMA_OFST(context), reg);

    reg  = HW_RD_REG32(baseAddr + CAL_WR_DMA_XSIZE(context));
    reg &= ~(CAL_WR_DMA_XSIZE_XSIZE_MASK | CAL_WR_DMA_XSIZE_XSKIP_MASK);
    reg |= CAL_WR_DMA_XSIZE_XSKIP_MASK &
           (cfg->xPixelSkip << CAL_WR_DMA_XSIZE_XSKIP_SHIFT);

    reg |= CAL_WR_DMA_XSIZE_XSIZE_MASK &
           (cfg->format.width << CAL_WR_DMA_XSIZE_XSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_WR_DMA_XSIZE(context), reg);

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t calSetWrDmaMode(const isshalCalInstObj_t  *pInstObj,
                               const isshalCalDmaVcCfg_t *pDmaCfg)
{
    volatile uint32_t reg;
    uint32_t          baseAddr, instance, i;

    baseAddr = pInstObj->baseAddr;
    for(i = 0; i < pDmaCfg->numCPortId; i++)
    {
        if((uint32_t)TRUE == pDmaCfg->isWrDmaCfgValid[i])
        {
            instance = pDmaCfg->wrDmaCfg[i].contextToBeUsed;
            reg      = HW_RD_REG32(baseAddr + CAL_WR_DMA_CTRL(instance));
            reg     &= ~((UInt32) CAL_WR_DMA_CTRL_MODE_MASK);

            reg |= CAL_WR_DMA_CTRL_MODE_MASK &
                   pDmaCfg->wrDmaCfg[i].mode;

            HW_WR_REG32(baseAddr + CAL_WR_DMA_CTRL(instance), reg);
        }
    }

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t CalSetLineEventCfg(const isshalCalInstObj_t  *pInstObj,
                                  const isshalCalLineEventCfg_t *plnEvtCfg)
{
    volatile uint32_t reg;
    uint32_t          baseAddr, cportId, i;

    baseAddr = pInstObj->baseAddr;
    for(i = 0; i < plnEvtCfg->numCPortId; i++)
    {
        cportId = plnEvtCfg->cportId[i];
        reg = HW_RD_REG32(baseAddr + CAL_LINE_NUMBER_EVT);

        reg &= ~((uint32_t)CAL_LINE_NUMBER_EVT_CPORT_MASK);
        reg &= ~CAL_LINE_NUMBER_EVT_MASK;

        reg |= CAL_LINE_NUMBER_EVT_CPORT_MASK &
               (cportId << CAL_LINE_NUMBER_EVT_CPORT_SHIFT);

        reg |= CAL_LINE_NUMBER_EVT_MASK &
                (plnEvtCfg->lineNumber[cportId] << CAL_LINE_NUMBER_EVT_SHIFT);

        HW_WR_REG32(baseAddr + CAL_LINE_NUMBER_EVT, reg);
    }
    return (FVID2_SOK);
}

/**************************Function Separator**********************************/
