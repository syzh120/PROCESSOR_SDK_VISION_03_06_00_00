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
 *  \file vpshal_ipipeif.c
 *
 *  \brief This file abstracts IPIPE IF block of ISS. Please note that though
 *      multiple opens are supported, open specific configuration is not
 *      maintained.
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

#include <ti/csl/cslr_iss.h>
#include <ti/csl/hw_types.h>

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issipipeif.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define IPIPEIF_CLKDIV_M_MASK   (0x0000FF00U)
/**< Bits defining the M portion of the clock divider */
#define IPIPEIF_CLKDIV_N_MASK   (0x000000FFU)
/**< Bits defining the N portion of the clock divider */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct isshalIpipeifInstObj
 *  \brief Describes a instance of IPIPE IF configuration.
 */
typedef struct isshalIpipeifInstObj
{
    uint32_t instId;
    /**< Instance ID */
    uint32_t isInited;
    /**< Flag to indicate initialization status. */
    uint32_t baseAddr;
    /**< Base address of the IPIPE IF module */
    uint32_t openCnt;
    /**< Number of times the driver is opened. */
    uint32_t lut0Addr[1];
    /**< VP DeCompanding LUT Address */
    uint32_t lut0Size;
    /**< Number of bytes that represent this LUT */
    uint32_t lut1Addr[1];
    /**< MEM IF DeCompanding LUT Address */
    uint32_t lut1Size;
    /**< Number of bytes that represent this LUT */
    uint32_t lut2Addr[1];
    /**< WDR Companding LUT Address */
    uint32_t lut2Size;
    /**< Number of bytes that represent this LUT */
} isshalIpipeifInstObj_t;

/**
 *  struct isshalIpipeifObj
 *  \brief Describes a IPIPE IF obejct.
 */
typedef struct isshalIpipeifObj
{
    /* Following parameters are applicable only when data is READ from memory.
     *  i.e. through memif */
    uint32_t                vdPol;
    /**< Refer the isshalIpipieifInstParams_t */
    uint32_t                hdPol;
    /**< Refer the isshalIpipieifInstParams_t */
    uint32_t                fifoWmrkLvl;
    /**< Refer the isshalIpipieifInstParams_t */
    uint32_t                enableM2MStall;
    /**< Refer the isshalIpipieifInstParams_t */
    uint32_t                moduleClockSel;
    /**< Refer the isshalIpipieifInstParams_t */
    uint32_t                clkDivM;
    /**< Refer the isshalIpipieifInstParams_t */
    uint32_t                clkDivN;
    /**< Refer the isshalIpipieifInstParams_t */
    issCtrlProcMode_t       mode;
    /**< Free running / one shot mode */
    UInt32                  enableSdRamIf;
    /**< Flag to enable SD RAM interface on START ioctl
         TRUE: enables IPIPEIF when Start ioctl is called
         FALSE: IPIPEIF is not enabled at start ioctl */
    isshalIpipeifInstObj_t *instCfg;
    /**< Pointer to instance specific config */
} isshalIpipeifObj_t;

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'polClkcFifoDepthDefault' visibility is too wide.
 * KW State: ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used only in VpsHal_issipipeifOpen api,
 * but keeping all global variables at one place.
 */
static const isshalIpipeifObj_t polClkcFifoDepthDefault = { \
    (uint32_t)TRUE,                                         \
    (uint32_t)TRUE,                                         \
    0x08U,                                                  \
    (uint32_t)TRUE,                                         \
    (uint32_t)TRUE,                                         \
    0x00U,                                                  \
    0x01U,                                                  \
    ISSHAL_ISS_PROC_MODE_ONE_SHOT,                          \
    (uint32_t)FALSE,                                        \
    NULL
};

/**< Default values for isshalIpipeifObj_t
 *  uint32_t vdPol;
 *  uint32_t hdPol;
 *  uint32_t fifoWmrkLvl;
 *  uint32_t enableM2MStall;
 *  uint32_t moduleClockSel;
 *  uint32_t clkDivM;
 *  uint32_t clkDivN;
 *  issCtrlProcMode_t mode;
 *  isshalIpipeifInstObj_t *instCfg;
 */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Checks config supplied could be applied or not
 *
 * \param   cfg     Pointer to valid config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifCheckCfg(const isshalIpipeifCfg_t *cfg);

/**
 * \brief   Configures All Compading and Decompanding blocks
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         DeCompanding / companding config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetCompDecompConfig(
    const isshalIpipeifInstObj_t        *instCfg,
    const vpsissIpipeifDeCompandInsts_t *cfg);

/**
 * \brief   Configures All Saturation blocks
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         Saturation config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetSaturationInsts(
    const isshalIpipeifInstObj_t     *instCfg,
    const vpsissIpipeifSaturaInsts_t *cfg);

/**
 * \brief   Configures de-companding block
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         DeCompanding / companding config
 * \param   regOffset   Identifies which decompanding IP to be configured.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetDeCompandConfig(
    const isshalIpipeifInstObj_t         *instCfg,
    const vpsissIpipeifDeCompandConfig_t *cfg,
    uint32_t                              regOffset);
/**
 * \brief   Configures saturation block
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         saturation config
 * \param   regOffset   Identifies which saturation IP to be configured.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetSaturationConfig(
    const isshalIpipeifInstObj_t      *instCfg,
    const vpsissIpipeifSaturaConfig_t *cfg,
    uint32_t                           regOffset);

/**
 * \brief   Configures defect pixel correction block
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         Defect pixel correction config
 * \param   regOffset   Identifies which DPC IP to be configured.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetDpcConfig(const isshalIpipeifInstObj_t *instCfg,
                                   const vpsissIpipeifDpcCfg_t  *cfg,
                                   uint32_t                      regOffset);

/**
 * \brief   Configures decompression block
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         De compression config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetDpcmConfig(const isshalIpipeifInstObj_t *instCfg,
                                    const isshalIpipeifDpcmCfg_t *cfg);

/**
 * \brief   Configures WDR Block
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         WDR config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetWdrConfig(const isshalIpipeifInstObj_t *instCfg,
                                   const vpsissIpipeifWdrCfg_t  *cfg);

/**
 * \brief   Configures ISIF Output
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         ISIF Output config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetIsifOutConfig(const isshalIpipeifInstObj_t    *instCfg,
                                       const isshalIpipeifIsifOutCfg_t *cfg);

/**
 * \brief   Configures IPIPE Output
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         IPIPE Output config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetIpipeOutConfig(
    const isshalIpipeifInstObj_t     *instCfg,
    const isshalIpipeifIpipeOutCfg_t *cfg);

/**
 * \brief   Configures IPIPE Output
 *
 * \param   instCfg     Pointer to instance specific config
 * \param   cfg         IPIPE Output config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetH3aOutConfig(const isshalIpipeifInstObj_t   *instCfg,
                                      const isshalIpipeifH3aOutCfg_t *cfg);

/**
 * \brief   Configures the run time configuration.
 *
 * \param   hndl    Instance handle returned by open
 * \param   cfg     Pointer to valid run time config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetRtConfig(const isshalIpipeifObj_t   *hndl,
                                  const isshalIpipeifRtCfg_t *cfg);
/**
 * \brief   Configures the IPIPE IF as per specified config.
 *
 * \param   hndl    Instance handle returned by open
 * \param   cfg     Pointer to valid config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetConfig(const isshalIpipeifObj_t *hndl,
                                const isshalIpipeifCfg_t *cfg);

/**
 * \brief   Configures the clock source, divider, fifo level & polarity of the
 *              syncs.
 *
 * \param   hndl    Instance handle returned by open
 * \param   cfg     Pointer to valid config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifSetClkConfig(const isshalIpipeifObj_t    *hndl,
                                   const isshalIpipeifClkCfg_t *cfg);

/**
 * \brief   Enables / disables companding / decompanding / saturation
 *
 *          Not implemented for all inputs / output.
 *
 * \param   hndl    Instance handle returned by open
 * \param   cfg     Pointer to valid config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t IpipeifEnDisProc(const isshalIpipeifObj_t  *hndl,
                                const vpsissIpipeifCtrl_t *cfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalIpipeifInstObj_t   gIpipeIfInstObj[VPS_HAL_ISS_IPIPEIF_MAX_INST] =
{
    {0, (uint32_t)FALSE}
};
/**< Instance specific config */

static isshalIpipeifObj_t       gIpipeIfObj \
    [VPS_HAL_ISS_IPIPEIF_MAX_INST][VPS_HAL_ISS_IPIPEIF_OPEN_NUM];
/**< Handle / open specific config */

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalIpipeifDefCfg' visibility is too wide.
 * KW State: ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used only for
 * VPS_HAL_ISS_IOCTL_IPIPEIF_GET_DEFAULTCFG api,
 * but keeping all global variables at one place.
 */
static const isshalIpipeifCfg_t gIssHalIpipeifDefCfg =
{
    /* Input Frame Size */
    {0x0U,                              0x0U,            0x0U,
         0x0U},
    /* Unpack Configuration */
    {0x0U,                              0x0U,            0x0U},
    {
        VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_ALL,
        /* Decompanding Configuration for Vport input */
        {(uint32_t)FALSE,                   0U,
         0U, 0U, 0U, 0U, 0U,
         0U, 0U, 0U, 0U, 0U, 0U, 0U},
        /* Decompanding Configuration for Memory input */
        {(uint32_t)FALSE,                   0U,
         0U, 0U, 0U, 0U, 0U,
         0U, 0U, 0U, 0U, 0U, 0U, 0U},
        /* Companding configuration */
        {(uint32_t)FALSE,                   0U,
         0U, 0U, 0U, 0U, 0U,
         0U, 0U, 0U, 0U, 0U, 0U, 0U}
    },
    /* Saturation Configuration for VPort, Memory and ISIF input */
    {
        VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_ALL,
        {(uint32_t)FALSE,                   0U,
         0U, 0U},
        {(uint32_t)FALSE,                   0U,
         0U, 0U},
        {(uint32_t)FALSE,                   0U,
         0U, 0U}
    },
    /* DPC configuration for VPort and ISIF input */
    {(uint32_t)FALSE,                   0x0U},
    /* DPCM configuration for the memory input */
    {(uint32_t)FALSE,                   0x0U},

    /* DPCM configuration for the memory input */
    {(uint32_t)FALSE,                   0x0U,            0x0U},

    /* WDR Configuration */
    {
        (uint32_t)FALSE, (uint32_t)FALSE, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U,
        0x0U, 0x0U, 0x0U,
        0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U,
        {0x0U,                              0x0U,            0x0U,
         0x0U},
        {0x0U,                              0x0U,            0x0U,
         0x0U},
        0x0U, 0x0U
    },
    /* ISIF Out Config */
    {ISSHAL_IPIPEIF_ISIF_OUT_RAW_VPORT, (uint32_t)TRUE},
    /* IPIPE Out Config */
    {ISSHAL_IPIPEIF_IPIPE_OUT_ISIF,     (uint32_t)FALSE,
         {(uint32_t)FALSE,                   0x0U,            0x0U},
         0x200U, 0xFFFFU},
    /* H3A Output Configuration */
    {(uint32_t)FALSE,                   {(uint32_t)FALSE,0x0U,0x0U}}
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issipipeifInit(uint32_t                          numInst,
                              const isshalIpipieifInstParams_t *initPrms,
                              Ptr                               arg)
{
    int32_t  rtnVal = FVID2_EBADARGS;
    uint32_t openCnt, inst;

    /*  . Check args
     *  . Initialize, instance objects
     */

    GT_assert(VpsHalTrace, (0x01U == numInst));

    if(numInst <= VPS_HAL_ISS_IPIPEIF_MAX_INST)
    {
        /* If all the instances are already inited, return success*/
        rtnVal = FVID2_SOK;
        for(inst = 0U; inst < VPS_HAL_ISS_IPIPEIF_MAX_INST; inst++)
        {
            GT_assert(VpsHalTrace, (NULL != initPrms));
            GT_assert(VpsHalTrace, (NULL != initPrms->baseAddress));

            if((uint32_t)FALSE == gIpipeIfInstObj[inst].isInited)
            {
                for(openCnt = 0U; openCnt < VPS_HAL_ISS_IPIPEIF_OPEN_NUM;
                    openCnt++)
                {
                    BspUtils_memset(&gIpipeIfObj[inst][openCnt], 0U,
                                    sizeof(isshalIpipeifObj_t));
                    gIpipeIfObj[inst][openCnt].instCfg = &gIpipeIfInstObj[inst];
                }
                gIpipeIfInstObj[inst].instId       = initPrms->instId;
                gIpipeIfInstObj[inst].isInited     = (uint32_t)TRUE;
                gIpipeIfInstObj[inst].baseAddr     = initPrms->baseAddress;
                gIpipeIfInstObj[inst].lut0Addr[0U] = initPrms->lut0Addr[0U];
                gIpipeIfInstObj[inst].lut1Addr[0U] = initPrms->lut1Addr[0U];
                gIpipeIfInstObj[inst].lut2Addr[0U] = initPrms->lut2Addr[0U];
                gIpipeIfInstObj[inst].lut0Size     = initPrms->lut0Size;
                gIpipeIfInstObj[inst].lut1Size     = initPrms->lut1Size;
                gIpipeIfInstObj[inst].lut2Size     = initPrms->lut2Size;

                if(0U != gIpipeIfInstObj[inst].lut0Addr[0U])
                {
                    /* MISRA.CAST.PTR_TO_INT
                     * MISRAC_2004_Rule_11.3
                     * Casting between a pointer to an integral type
                     * KW State: Ignore -> Waiver -> Case by case
                     * MISRAC_WAIVER:
                     * Array has address of the LUT, lut is initialized
                     * with the default value using memset api, which expects
                     * Lut address to be in Ptr.
                     */
                    BspUtils_memset(
                        (Ptr) gIpipeIfInstObj[inst].lut0Addr[0U],
                        0xFFU,
                        gIpipeIfInstObj[inst].lut0Size);
                }
                if(0U != gIpipeIfInstObj[inst].lut1Addr[0U])
                {
                    /* MISRA.CAST.PTR_TO_INT
                     * MISRAC_2004_Rule_11.3
                     * Casting between a pointer to an integral type
                     * KW State: Ignore -> Waiver -> Case by case
                     * MISRAC_WAIVER:
                     * Array has address of the LUT, lut is initialized
                     * with the default value using memset api, which expects
                     * Lut address to be in Ptr.
                     */
                    BspUtils_memset(
                        (Ptr) gIpipeIfInstObj[inst].lut1Addr[0U],
                        0xFFU,
                        gIpipeIfInstObj[inst].lut1Size);
                }
                if(0U != gIpipeIfInstObj[inst].lut2Addr[0U])
                {
                    /* MISRA.CAST.PTR_TO_INT
                     * MISRAC_2004_Rule_11.3
                     * Casting between a pointer to an integral type
                     * KW State: Ignore -> Waiver -> Case by case
                     * MISRAC_WAIVER:
                     * Array has address of the LUT, lut is initialized
                     * with the default value using memset api, which expects
                     * Lut address to be in Ptr.
                     */
                    BspUtils_memset(
                        (Ptr) gIpipeIfInstObj[inst].lut2Addr[0U],
                        0xFFU,
                        gIpipeIfInstObj[inst].lut2Size);
                }

                gIpipeIfInstObj[inst].openCnt = 0x0U;

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * Pointer is accessed as an array
                 * KW State: Ignore -> Waiver -> Case by case
                 * MISRAC_WAIVER: Pointer is incremented to get the next
                 * object's address.
                 * This function is called by init function, which passes
                 * ipipeif number of instances. The size of this
                 * number of instances is never more than
                 * VPS_HAL_ISS_IPIPEIF_MAX_INST.
                 */
                initPrms++;

                rtnVal = FVID2_SOK;
            }
        }
    }
    return (rtnVal);
}

/**************************Function Separator**********************************/

int32_t VpsHal_issipipeifDeInit(Ptr arg)
{
    int32_t  rtnVal = FVID2_SOK;
    uint32_t inst;
    /*  . Reset all know configs
     *  . Power down IPIPE IF
     */
    for(inst = 0; inst < VPS_HAL_ISS_IPIPEIF_MAX_INST; inst++)
    {
        GT_assert(VpsHalTrace, (0x0 == gIpipeIfInstObj[inst].openCnt));
        BspUtils_memset(&gIpipeIfInstObj[inst], 0U,
                        sizeof(isshalIpipeifInstObj_t));
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/

VpsHal_Handle VpsHal_issipipeifOpen(const isshalOpenParams_t *openPrms, Ptr arg)
{
    uint32_t instCnt;
    isshalIpipeifObj_t *hndl = NULL;

    GT_assert(VpsHalTrace, (NULL != openPrms));

    GT_assert(VpsHalTrace, (0x0 == openPrms->instId));

    for(instCnt = 0U; instCnt < VPS_HAL_ISS_IPIPEIF_MAX_INST; instCnt++)
    {
        if(openPrms->instId == gIpipeIfInstObj[instCnt].instId)
        {
            if(((uint32_t)FALSE != gIpipeIfInstObj[instCnt].isInited) &&
               (VPS_HAL_ISS_IPIPEIF_OPEN_NUM > gIpipeIfInstObj[instCnt].openCnt))
            {
                /* This should be after defaults are initialized */
                hndl = &gIpipeIfObj[instCnt][gIpipeIfInstObj[instCnt].openCnt];
                gIpipeIfInstObj[instCnt].openCnt++;

                /* Can open now */
                /* Set the defaults */
                BspUtils_memcpy(
                    (Ptr) hndl,
                    (const void *) &polClkcFifoDepthDefault,
                    sizeof(isshalIpipeifObj_t));
                hndl->instCfg       = &gIpipeIfInstObj[instCnt];
                hndl->enableSdRamIf = (uint32_t)FALSE;

                /* Power up IPIPE IF */
                GT_assert(VpsHalTrace,
                          (FVID2_SOK ==
                           VpsHal_issEnableModule(ISSHAL_ISS_MODULE_IPIPEIF,
                                                  (uint32_t)TRUE)));
            }
        }
    }

    return (hndl);
}

/**************************Function Separator**********************************/

int32_t VpsHal_issipipeifClose(VpsHal_Handle handle, Ptr arg)
{
    int32_t rtnVal           = FVID2_EBADARGS;
    isshalIpipeifObj_t *hndl = (isshalIpipeifObj_t *) handle;

    GT_assert(VpsHalTrace, (NULL != hndl));
    if(0x0 < hndl->instCfg->openCnt)
    {
        hndl->instCfg->openCnt--;
        rtnVal = FVID2_SOK;
        /* Last instance to be closed, power down the IP */
        if(0 == hndl->instCfg->openCnt)
        {
            rtnVal = VpsHal_issEnableModule(ISSHAL_ISS_MODULE_IPIPEIF,
                                            (uint32_t)FALSE);
            GT_assert(VpsHalTrace, (FVID2_SOK == rtnVal));
        }
        hndl->instCfg = NULL;
    }

    return (rtnVal);
}

int32_t VpsHal_issipipeifStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    isshalIpipeifObj_t *hndl = (isshalIpipeifObj_t *) handle;
    int32_t rtnVal           = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != hndl));
    GT_assert(VpsHalTrace, (NULL != hndl->instCfg));

    rtnVal = VpsHal_issipipeifControl(
        handle,
        VPS_HAL_ISS_IOCTL_START,
        &procMode,
        NULL);

    return (rtnVal);
}

int32_t VpsHal_issipipeifStop(
    VpsHal_Handle handle,
    Ptr           arg)
{
    isshalIpipeifObj_t *hndl = (isshalIpipeifObj_t *) handle;
    int32_t rtnVal           = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != hndl));
    GT_assert(VpsHalTrace, (NULL != hndl->instCfg));

    rtnVal = VpsHal_issipipeifControl(
        handle,
        VPS_HAL_ISS_IOCTL_STOP,
        NULL,
        NULL);

    return (rtnVal);
}

/**************************Function Separator**********************************/

int32_t VpsHal_issipipeifControl(VpsHal_Handle handle,
                                 UInt32        cmd,
                                 Ptr           cmdArgs,
                                 Ptr           arg)
{
    isshalIpipeifObj_t *hndl = (isshalIpipeifObj_t *) handle;
    int32_t rtnVal           = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != hndl));
    GT_assert(VpsHalTrace, (NULL != hndl->instCfg));

    if((((uint32_t)FALSE == hndl->instCfg->isInited) &&
        (0x0 != hndl->instCfg->openCnt)) ||
       (((uint32_t)TRUE == hndl->instCfg->isInited) &&
        (0x0 == hndl->instCfg->openCnt)))
    {
        rtnVal = FVID2_EFAIL;
    }
    if(FVID2_SOK == rtnVal)
    {
        switch(cmd)
        {
            case VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_BUFFERS:
                GT_assert(VpsHalTrace, (NULL != cmdArgs));
                rtnVal = FVID2_EBADARGS;
                if((NULL != cmdArgs) && (NULL != arg))
                {
                    volatile uint32_t reg, baseAddr;
                    uint32_t          usrArg = *((uint32_t *) cmdArgs);
                    if(0x0U != usrArg)
                    {
                        baseAddr = hndl->instCfg->baseAddr;

                        /* Drop / ignore first 4 bits */
                        usrArg = usrArg >> 5U;
                        reg    = HW_RD_REG32(baseAddr + IPIPEIF_ADDRL);
                        reg   &= ~((UInt32) IPIPEIF_ADDRL_MASK);
                        reg   |= IPIPEIF_ADDRL_MASK & usrArg;
                        HW_WR_REG32(baseAddr + IPIPEIF_ADDRL, reg);

                        usrArg = usrArg >> 16U;
                        reg    = HW_RD_REG32(baseAddr + IPIPEIF_ADDRU);
                        reg   &= ~((UInt32) IPIPEIF_ADDRU_MASK);
                        reg   |= IPIPEIF_ADDRU_MASK & usrArg;
                        HW_WR_REG32(baseAddr + IPIPEIF_ADDRU, reg);

                        usrArg   = *((uint32_t *) arg);
                        usrArg >>= 5U;
                        reg      = HW_RD_REG32(baseAddr + IPIPEIF_ADOFS);
                        reg     &= ~((UInt32) IPIPEIF_ADOFS_MASK);
                        reg     |= IPIPEIF_ADOFS_MASK & usrArg;
                        HW_WR_REG32(baseAddr + IPIPEIF_ADOFS, reg);
                        rtnVal = FVID2_SOK;
                    }
                }
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_SET_FRAME_CFG:
                rtnVal = FVID2_EBADARGS;
                if(NULL != cmdArgs)
                {
                    isshalIpipeifFrameCfg_t *frmCfg =
                        (isshalIpipeifFrameCfg_t *) cmdArgs;
                    volatile uint32_t        regVal, baseAddr;

                    baseAddr = hndl->instCfg->baseAddr;

                    /* Frame config */
                    regVal  = HW_RD_REG32(baseAddr + IPIPEIF_PPLN);
                    regVal &= ~((UInt32) IPIPEIF_PPLN_MASK);
                    regVal |= (frmCfg->ppln & IPIPEIF_PPLN_MASK);
                    HW_WR_REG32(baseAddr + IPIPEIF_PPLN, regVal);

                    regVal  = HW_RD_REG32(baseAddr + IPIPEIF_LPFR);
                    regVal &= ~((UInt32) IPIPEIF_LPFR_MASK);
                    regVal |= (frmCfg->lpfr & IPIPEIF_LPFR_MASK);
                    HW_WR_REG32(baseAddr + IPIPEIF_LPFR, regVal);

                    regVal  = HW_RD_REG32(baseAddr + IPIPEIF_HNUM);
                    regVal &= ~((UInt32) IPIPEIF_HNUM_MASK);
                    regVal |= (frmCfg->hnum & IPIPEIF_HNUM_MASK);
                    HW_WR_REG32(baseAddr + IPIPEIF_HNUM, regVal);

                    regVal  = HW_RD_REG32(baseAddr + IPIPEIF_VNUM);
                    regVal &= ~((UInt32) IPIPEIF_VNUM_MASK);
                    regVal |= (frmCfg->vnum & IPIPEIF_VNUM_MASK);
                    HW_WR_REG32(baseAddr + IPIPEIF_VNUM, regVal);

                    rtnVal = FVID2_SOK;
                }
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG:
                rtnVal = IpipeifSetRtConfig(hndl,
                                            (isshalIpipeifRtCfg_t *) cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT:
                rtnVal = IpipeifEnDisProc(hndl,
                                          (vpsissIpipeifCtrl_t *) cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_SETCFG:
                rtnVal = IpipeifSetConfig(hndl,
                                          (isshalIpipeifCfg_t *) cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_ENABLE_INPUT_IF:
                hndl->enableSdRamIf = (uint32_t)TRUE;
                break;

            case VPS_HAL_ISS_IOCTL_START:
            {
                issCtrlProcMode_t procMode = *(issCtrlProcMode_t *)cmdArgs;
                volatile uint32_t reg, baseAddr;
                baseAddr = hndl->instCfg->baseAddr;

                reg  = HW_RD_REG32(baseAddr + IPIPEIF_CFG1);
                reg &= ~((UInt32) IPIPEIF_CFG1_ONESHOT_MASK);

                if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
                {
                    reg |= IPIPEIF_CFG1_ONESHOT_MASK;
                }
                HW_WR_REG32(baseAddr + IPIPEIF_CFG1, reg);

                /* Enable required only when reading from MEM IF */
                /* i.e. INPSRC1/2 = 1, 2 or 3 */
                reg = HW_RD_REG32(baseAddr + IPIPEIF_CFG1);
                if((uint32_t)TRUE == hndl->enableSdRamIf)
                {
                    reg  = HW_RD_REG32(baseAddr + IPIPEIF_ENABLE);
                    reg |= IPIPEIF_ENABLE_MASK;
                    HW_WR_REG32(baseAddr + IPIPEIF_ENABLE, reg);
                }
                else
                {
                    reg  = HW_RD_REG32(baseAddr + IPIPEIF_ENABLE);
                    reg &= ~((UInt32) IPIPEIF_ENABLE_MASK);
                    HW_WR_REG32(baseAddr + IPIPEIF_ENABLE, reg);
                }
            }
            break;

            case VPS_HAL_ISS_IOCTL_STOP:
            {
                volatile uint32_t reg;
                reg  = HW_RD_REG32(hndl->instCfg->baseAddr + IPIPEIF_ENABLE);
                reg &= ~((UInt32) IPIPEIF_ENABLE_MASK);
                HW_WR_REG32(hndl->instCfg->baseAddr + IPIPEIF_ENABLE, reg);
            }
            break;

            case VPS_HAL_ISS_IOCTL_RESET:
                /* Nothing to reset ? */
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_LUT:
                rtnVal = FVID2_EBADARGS;
                if(NULL != cmdArgs)
                {
                    vpsissIpipeifLutConfig_t *lut = (vpsissIpipeifLutConfig_t *)
                                                    cmdArgs;

                    if((NULL != lut->vportDecompandLut) &&
                       (0U != hndl->instCfg->lut0Addr[0U]))
                    {
                        VpsHal_issUtilMemCpy(
                            (uint32_t **) &hndl->instCfg->lut0Addr,
                            (const uint32_t **) &lut->vportDecompandLut,
                            &lut->vportLutSize,
                            0x01U);
                        rtnVal = FVID2_SOK;
                    }
                    if((NULL != lut->memifDecompandLut) &&
                       (0U != hndl->instCfg->lut1Addr[0U]))
                    {
                        VpsHal_issUtilMemCpy(
                            (uint32_t **) &hndl->instCfg->lut1Addr,
                            (const uint32_t **) &lut->memifDecompandLut,
                            &lut->memifLutSize,
                            0x01U);
                        rtnVal = FVID2_SOK;
                    }
                    if((NULL != lut->wdrCompandLut) &&
                       (0U != hndl->instCfg->lut2Addr[0U]))
                    {
                        VpsHal_issUtilMemCpy(
                            (uint32_t **) &hndl->instCfg->lut2Addr,
                            (const uint32_t **) &lut->wdrCompandLut,
                            &lut->wdrLutSize,
                            0x01U);
                        rtnVal = FVID2_SOK;
                    }
                }
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_SET_CLK_POL_FIFO:
                rtnVal = IpipeifSetClkConfig(hndl, (isshalIpipeifClkCfg_t *)
                                             cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_GET_CLK_POL_FIFO:
                GT_assert(VpsHalTrace, (NULL != cmdArgs));
                {
                    isshalIpipeifClkCfg_t *usrArg = (isshalIpipeifClkCfg_t *)
                                                    cmdArgs;
                    BspUtils_memcpy((Ptr) usrArg, (const void *) hndl,
                                    sizeof(isshalIpipeifClkCfg_t));
                }
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_SET_COMPDECOMP_CFG:
                rtnVal = FVID2_EBADARGS;
                if(NULL != cmdArgs)
                {
                    vpsissIpipeifDeCompandInsts_t *cfg =
                        (vpsissIpipeifDeCompandInsts_t *) cmdArgs;

                    rtnVal = IpipeifSetCompDecompConfig(
                        hndl->instCfg,
                        cfg);
                }
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_SET_WDR_CFG:
                rtnVal = FVID2_EBADARGS;
                if(NULL != cmdArgs)
                {
                    vpsissIpipeifWdrCfg_t *cfg =
                        (vpsissIpipeifWdrCfg_t *) cmdArgs;

                    rtnVal = IpipeifSetWdrConfig(hndl->instCfg, cfg);
                }
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_SET_SATURATION_CFG:
                rtnVal = FVID2_EBADARGS;
                if(NULL != cmdArgs)
                {
                    vpsissIpipeifSaturaInsts_t *cfg =
                        (vpsissIpipeifSaturaInsts_t *) cmdArgs;

                    rtnVal = IpipeifSetSaturationInsts(
                        hndl->instCfg,
                        cfg);
                }
                break;

            case VPS_HAL_ISS_IOCTL_IPIPEIF_GET_DEFAULTCFG:
                if(NULL != cmdArgs)
                {
                    BspUtils_memcpy(
                        ((isshalIpipeifCfg_t *) cmdArgs),
                        &gIssHalIpipeifDefCfg,
                        sizeof(isshalIpipeifCfg_t));
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO:
            {
                isshalissBlankingInfo_t *blankInfo =
                    (isshalissBlankingInfo_t *) cmdArgs;
                isshalIpipeifCfg_t      *cfg =
                    (isshalIpipeifCfg_t *) arg;

                GT_assert(VpsHalTrace, (NULL != cfg));
                GT_assert(VpsHalTrace, (NULL != blankInfo));

                /* TODO: change this blanking requirement based
                 *       on the configuration.
                 *       Currently Set to maximm */
                blankInfo->hBlank = 8U;
                blankInfo->vBlank = 0U;

                break;
            }
            case VPS_HAL_ISS_IOCTL_IPIPEIF_SET_DPC_CFG:
                rtnVal = FVID2_EBADARGS;
                if(NULL != cmdArgs)
                {
                    vpsissIpipeifDpcCfg_t *dpcCfg =
                        (vpsissIpipeifDpcCfg_t *) cmdArgs;
                    /* Configure VPORT / ISIF port */
                    rtnVal = IpipeifSetDpcConfig(
                        hndl->instCfg,
                        (vpsissIpipeifDpcCfg_t *)
                        dpcCfg,
                        IPIPEIF_DPC1);
                    /* Configure memory port */
                    /* MISRA.PTR.ARITH
                     * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                     * Pointer increment
                     * KW State: Ignore -> Waiver -> Case by case
                     * MISRAC_WAIVER: Pointer is incremented to get the next
                     * object's address. There is already a check to make sure
                     * that pointer is not null.
                     */
                    dpcCfg++;

                    if((FVID2_SOK == rtnVal) &&
                       (NULL != dpcCfg))
                    {
                        rtnVal = IpipeifSetDpcConfig(
                            hndl->instCfg,
                            (vpsissIpipeifDpcCfg_t *)
                            dpcCfg,
                            IPIPEIF_DPC2);
                    }
                }
                break;

            default:
                rtnVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }
    else
    {
        rtnVal = FVID2_EBADARGS;
    }

    return (rtnVal);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t IpipeifCheckCfg(const isshalIpipeifCfg_t *cfg)
{
    int32_t rtnVal = FVID2_SOK;

    /* Un Pack */
    if(((FVID2_SOK == rtnVal) && (0x3U >= cfg->unpack.unpack)) &&
       ((0x7U >= cfg->unpack.datasft) && (0x1U >= cfg->unpack.raw16_memif)))
    {
        rtnVal = FVID2_SOK;
    }
    else
    {
        rtnVal = FVID2_EBADARGS;
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetCompDecompConfig(
    const isshalIpipeifInstObj_t        *instCfg,
    const vpsissIpipeifDeCompandInsts_t *cfg)
{
    int32_t rtnVal = FVID2_SOK;

    /* Check for NULL Pointers */
    GT_assert(VpsHalTrace, (NULL != instCfg));

    if(NULL == cfg)
    {
        rtnVal = FVID2_EBADARGS;
    }

    /* Decompanding configuration for Vport input */
    if(FVID2_SOK == rtnVal)
    {
        if((VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_VCOMP_DECOMP ==
            cfg->modInstId) ||
           (VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_VCOMP_DECOMP ==
            (VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_VCOMP_DECOMP &
             cfg->modInstId)))
        {
            rtnVal = IpipeifSetDeCompandConfig(instCfg,
                                               &cfg->vportDeCompandCfg,
                                               IPIPEIF_VPDCMPXTHR1);
        }
    }

    /* Decompanding configuration for Memory input */
    if(FVID2_SOK == rtnVal)
    {
        if((VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_MEMIF_DECOMP ==
            cfg->modInstId) ||
           (VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_MEMIF_DECOMP ==
            (VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_MEMIF_DECOMP &
             cfg->modInstId)))
        {
            rtnVal = IpipeifSetDeCompandConfig(instCfg,
                                               &cfg->memifDeCompandCfg,
                                               IPIPEIF_SDDCMPXTHR1);
        }
    }

    /* Companding configuration for Memory WDR_Merge output */
    if(FVID2_SOK == rtnVal)
    {
        if((VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_WDR_COMP ==
            cfg->modInstId) ||
           (VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_WDR_COMP ==
            (VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_WDR_COMP &
             cfg->modInstId)))
        {
            rtnVal = IpipeifSetDeCompandConfig(instCfg,
                                               &cfg->compandCfg,
                                               IPIPEIF_WDRCMPXTHR1);
        }
    }
    return (rtnVal);
}

static int32_t IpipeifSetSaturationInsts(
    const isshalIpipeifInstObj_t     *instCfg,
    const vpsissIpipeifSaturaInsts_t *cfg)
{
    int32_t rtnVal = FVID2_SOK;

    /* Check for NULL Pointers */
    GT_assert(VpsHalTrace, (NULL != instCfg));

    if(NULL == cfg)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == rtnVal)
    {
        if((VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_VCOMP ==
            cfg->modInstId) ||
           (VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_ALL == cfg->modInstId))
        {
            rtnVal = IpipeifSetSaturationConfig(instCfg,
                                                &cfg->vportSatCfg,
                                                IPIPEIF_WDRSAT_VP);
        }
    }
    if(FVID2_SOK == rtnVal)
    {
        if((VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_MEMIF ==
            cfg->modInstId) ||
           (VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_ALL == cfg->modInstId))
        {
            rtnVal = IpipeifSetSaturationConfig(instCfg,
                                                &cfg->memifSatCfg,
                                                IPIPEIF_WDRSAT_SD);
        }
    }
    if(FVID2_SOK == rtnVal)
    {
        if((VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_ISIF ==
            cfg->modInstId) ||
           (VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_ALL == cfg->modInstId))
        {
            rtnVal = IpipeifSetSaturationConfig(instCfg,
                                                &cfg->isifSatCfg,
                                                IPIPEIF_WDRSAT_ISIF);
        }
    }

    return (rtnVal);
}

static int32_t IpipeifSetDeCompandConfig(
    const isshalIpipeifInstObj_t         *instCfg,
    const vpsissIpipeifDeCompandConfig_t *cfg,
    uint32_t                              regOffset)
{
    volatile uint32_t dCmpCfg;
    volatile uint32_t reg;
    uint32_t          baseAddr;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));
    baseAddr = instCfg->baseAddr;
    /* For all decompanding / companding, the configurations register
     *  IPIPEIF_VPDCMPCFG IPIPEIF_SDDCMPCFG & IPIPEIF_WDRCMPCFG is exactly
     *  0x28 from IPIPEIF_VPDCMPXTHR1, IPIPEIF_SDDCMPXTHR1
     *  IPIPEIF_WDRCMPXTHR1 */
    dCmpCfg = HW_RD_REG32(baseAddr + regOffset + 0x28U);
    if((uint32_t)TRUE == cfg->enable)
    {
        dCmpCfg |= IPIPEIF_VPDCMPCFG_ENABLE_MASK;

        if((uint32_t)TRUE == cfg->useLut)
        {
            dCmpCfg |= IPIPEIF_VPDCMPCFG_LUTSET_MASK;
        }
        else
        {
            dCmpCfg &= ~((UInt32) IPIPEIF_VPDCMPCFG_LUTSET_MASK);

            /* Update threshold / slope values */

            /* IPIPEIF_XXDCMPXTHR1 OR IPIPEIF_WDRCMPXTHR1*/
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x0U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPXTHR1_XTHR1_MASK);
            reg |= cfg->xthr1 << IPIPEIF_VPDCMPXTHR1_XTHR1_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x0U, reg);
            /* IPIPEIF_XXDCMPXTHR2 OR IPIPEIF_WDRCMPXTHR2 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x4U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPXTHR2_XTHR2_MASK);
            reg |= cfg->xthr2 << IPIPEIF_VPDCMPXTHR2_XTHR2_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x4U, reg);
            /* IPIPEIF_XXDCMPXTHR3 OR IPIPEIF_WDRCMPXTHR3 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x8U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPXTHR3_XTHR3_MASK);
            reg |= cfg->xthr3 << IPIPEIF_VPDCMPXTHR3_XTHR3_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x8U, reg);

            /* IPIPEIF_XXDCMPYTHR1 OR IPIPEIF_WDRCMPYTHR1 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0xCU);
            reg &= ~((UInt32) IPIPEIF_VPDCMPYTHR1_YTHR1_MASK);
            reg |= cfg->ythr1 << IPIPEIF_VPDCMPYTHR1_YTHR1_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0xCU, reg);
            /* IPIPEIF_XXDCMPYTHR2 OR IPIPEIF_WDRCMPYTHR2 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x10U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPYTHR2_YTHR2_MASK);
            reg |= cfg->ythr2 << IPIPEIF_VPDCMPYTHR2_YTHR2_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x10U, reg);
            /* IPIPEIF_XXDCMPYTHR3 OR IPIPEIF_WDRCMPYTHR3 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x14U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPYTHR3_YTHR3_MASK);
            reg |= cfg->ythr3 << IPIPEIF_VPDCMPYTHR3_YTHR3_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x14U, reg);

            /* IPIPEIF_XXDCMPSLOPE1 OR IPIPEIF_WDRCMPSLOPE1 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x18U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPSLOPE1_SLOPE1_MASK);
            reg |= cfg->slope1 << IPIPEIF_VPDCMPSLOPE1_SLOPE1_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x18U, reg);
            /* IPIPEIF_XXDCMPSLOPE2 OR IPIPEIF_WDRCMPSLOPE2 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x1CU);
            reg &= ~((UInt32) IPIPEIF_VPDCMPSLOPE2_SLOPE2_MASK);
            reg |= cfg->slope2 << IPIPEIF_VPDCMPSLOPE2_SLOPE2_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x1CU, reg);
            /* IPIPEIF_XXDCMPSLOPE3 OR IPIPEIF_WDRCMPSLOPE3 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x20U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPSLOPE3_SLOPE3_MASK);
            reg |= cfg->slope3 << IPIPEIF_VPDCMPSLOPE3_SLOPE3_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x20U, reg);
            /* IPIPEIF_XXDCMPSLOPE4 OR IPIPEIF_WDRCMPSLOPE4 */
            reg  = HW_RD_REG32(baseAddr + regOffset + 0x24U);
            reg &= ~((UInt32) IPIPEIF_VPDCMPSLOPE4_SLOPE4_MASK);
            reg |= cfg->slope4 << IPIPEIF_VPDCMPSLOPE4_SLOPE4_SHIFT;
            HW_WR_REG32(baseAddr + regOffset + 0x24U, reg);
        }

        /* LUTBITSEL */
        dCmpCfg &= ~((UInt32) IPIPEIF_VPDCMPCFG_LUTBITSEL_MASK);
        dCmpCfg |= (IPIPEIF_VPDCMPCFG_LUTBITSEL_MASK &
                    (cfg->size << IPIPEIF_VPDCMPCFG_LUTBITSEL_SHIFT));

        /* SHIFT */
        dCmpCfg &= ~((UInt32) IPIPEIF_VPDCMPCFG_SHIFT_MASK);
        dCmpCfg |= (IPIPEIF_VPDCMPCFG_SHIFT_MASK &
                    (cfg->shift << IPIPEIF_VPDCMPCFG_SHIFT_SHIFT));
    }
    else
    {
        dCmpCfg &= ~((UInt32) IPIPEIF_VPDCMPCFG_ENABLE_MASK);
    }
    HW_WR_REG32(baseAddr + regOffset + 0x28U, dCmpCfg);

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetSaturationConfig(
    const isshalIpipeifInstObj_t      *instCfg,
    const vpsissIpipeifSaturaConfig_t *cfg,
    uint32_t                           regOffset)
{
    volatile uint32_t reg;
    uint32_t          baseAddr;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));

    if(((IPIPEIF_WDRSAT_VP != regOffset) && (IPIPEIF_WDRSAT_ISIF != regOffset))
       && (IPIPEIF_WDRSAT_SD != regOffset))
    {
        GT_assert(VpsHalTrace, ((uint32_t)FALSE));
    }

    baseAddr = instCfg->baseAddr;

    if((uint32_t)TRUE == cfg->enable)
    {
        reg  = HW_RD_REG32(baseAddr + regOffset + 0x0U);
        reg &= ~((UInt32) IPIPEIF_WDRSAT_VP_SAT_MASK);
        reg |= (IPIPEIF_WDRSAT_VP_SAT_MASK & cfg->sat);
        HW_WR_REG32(baseAddr + regOffset + 0x0U, reg);

        reg  = HW_RD_REG32(baseAddr + regOffset + 0x4U);
        reg &= ~((UInt32) (IPIPEIF_WDRSAT_VP2_VP_DSF_MASK |
                           IPIPEIF_WDRSAT_VP2_VP_DCCLMP_MASK));
        reg |= (cfg->dcClmp << IPIPEIF_WDRSAT_VP2_VP_DCCLMP_SHIFT) &
               IPIPEIF_WDRSAT_VP2_VP_DCCLMP_MASK;
        reg |= (cfg->dsf << IPIPEIF_WDRSAT_VP2_VP_DSF_SHIFT) &
               IPIPEIF_WDRSAT_VP2_VP_DSF_MASK;
        reg |= IPIPEIF_WDRSAT_VP2_VP_SATEN_MASK;
        HW_WR_REG32(baseAddr + regOffset + 0x4U, reg);
    }
    else
    {
        reg  = HW_RD_REG32(baseAddr + regOffset + 0x4U);
        reg &= ~((UInt32) IPIPEIF_WDRSAT_VP2_VP_SATEN_MASK);
        HW_WR_REG32(baseAddr + regOffset + 0x4U, reg);
    }

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/
/* Basic algorithim for defect pixel correction is
    n-2, n-1, n, n+1, n+2
    if (n < th && n+2 > th)
        n = n;
    else if (n-2 > th && n+2 > th)
        n = n;
    else if (n-2 > th && n+2 < th)
        n= n+2;
    else if (n+2 > th && n-2 < th)
        n = n-2;
    else
        n = ((n-2) + (n+2))/2
    */
static int32_t IpipeifSetDpcConfig(const isshalIpipeifInstObj_t *instCfg,
                                   const vpsissIpipeifDpcCfg_t  *cfg,
                                   uint32_t                      regOffset)
{
    volatile uint32_t reg;
    uint32_t          baseAddr;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));
    GT_assert(VpsHalTrace, ((IPIPEIF_DPC1 == regOffset) ||
                            (IPIPEIF_DPC2 == regOffset)));

    baseAddr = instCfg->baseAddr;
    reg      = HW_RD_REG32(baseAddr + regOffset);
    reg     &= ~((UInt32) (IPIPEIF_DPC1_TH_MASK | IPIPEIF_DPC1_ENA_MASK));
    if((uint32_t)TRUE == cfg->enable)
    {
        reg |= IPIPEIF_DPC1_TH_MASK & cfg->th;
        reg |= IPIPEIF_DPC1_ENA_MASK;
    }
    HW_WR_REG32(baseAddr + regOffset, reg);

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetDpcmConfig(const isshalIpipeifInstObj_t *instCfg,
                                    const isshalIpipeifDpcmCfg_t *cfg)
{
    volatile uint32_t reg;
    uint32_t          baseAddr;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));

    baseAddr = instCfg->baseAddr;

    reg = HW_RD_REG32(baseAddr + IPIPEIF_DPCM);

    reg &= ~((UInt32) (IPIPEIF_DPCM_ENA_MASK | IPIPEIF_DPCM_PRED_MASK |
                       IPIPEIF_DPCM_BITS_MASK));
    if((uint32_t)TRUE == cfg->enable)
    {
        if((uint32_t)TRUE == cfg->bits)
        {
            reg |= IPIPEIF_DPCM_BITS_MASK;
        }

        if((uint32_t)TRUE == cfg->pred)
        {
            reg |= IPIPEIF_DPCM_PRED_MASK;
        }

        reg |= IPIPEIF_DPCM_ENA_MASK;
    }
    HW_WR_REG32(baseAddr + IPIPEIF_DPCM, reg);

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetWdrConfig(const isshalIpipeifInstObj_t *instCfg,
                                   const vpsissIpipeifWdrCfg_t  *cfg)
{
    volatile uint32_t reg;
    volatile uint32_t cfg4EnaReg;
    uint32_t          baseAddr;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));

    baseAddr   = instCfg->baseAddr;
    cfg4EnaReg = HW_RD_REG32(baseAddr + IPIPEIF_CFG4);

    cfg4EnaReg &= ~(IPIPEIF_CFG4_DST_MASK | IPIPEIF_CFG4_SBIT_MASK |
                    IPIPEIF_CFG4_LBIT_MASK | IPIPEIF_CFG4_WGT_SEL_MASK |
                    IPIPEIF_CFG4_WDR_EN_MASK);
    if((uint32_t)TRUE == cfg->enable)
    {
        cfg4EnaReg |= IPIPEIF_CFG4_WDR_EN_MASK;
        /* If enabled configure other param */

        /* WDR Direction = DFSDIR */
        reg  = HW_RD_REG32(baseAddr + IPIPEIF_CFG2);
        reg &= ~((UInt32) IPIPEIF_CFG2_DFSDIR_MASK);
        if((uint32_t)TRUE == cfg->wdrDir)
        {
            reg |= IPIPEIF_CFG2_DFSDIR_MASK;
        }
        HW_WR_REG32(baseAddr + IPIPEIF_CFG2, reg);

        cfg4EnaReg |= IPIPEIF_CFG4_DST_MASK &
                      (cfg->dst << IPIPEIF_CFG4_DST_SHIFT);
        cfg4EnaReg |= IPIPEIF_CFG4_SBIT_MASK &
                      (cfg->sbit << IPIPEIF_CFG4_SBIT_SHIFT);
        cfg4EnaReg |= IPIPEIF_CFG4_LBIT_MASK &
                      (cfg->lbit << IPIPEIF_CFG4_LBIT_SHIFT);
        cfg4EnaReg |= IPIPEIF_CFG4_WGT_SEL_MASK &
                      (cfg->wgt_sel << IPIPEIF_CFG4_WGT_SEL_SHIFT);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRAF);
        reg &= ~(IPIPEIF_WDRAF_AFM_MASK | IPIPEIF_WDRAF_AFE_MASK);
        reg |= IPIPEIF_WDRAF_AFE_MASK &
               (cfg->afe << IPIPEIF_WDRAF_AFE_SHIFT);
        reg |= IPIPEIF_WDRAF_AFM_MASK & cfg->afm;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRAF, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRBF);
        reg &= ~((UInt32) IPIPEIF_WDRBF_BF_MASK);
        reg |= IPIPEIF_WDRBF_BF_MASK & cfg->bf;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRBF, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRGAIN);
        reg &= ~(IPIPEIF_WDRGAIN_GSHORT_MASK | IPIPEIF_WDRGAIN_GLONG_MASK);
        reg |= IPIPEIF_WDRGAIN_GSHORT_MASK &
               (cfg->gshort << IPIPEIF_WDRGAIN_GSHORT_SHIFT);
        reg |= IPIPEIF_WDRGAIN_GLONG_MASK & cfg->glong;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRGAIN, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRTHR);
        reg &= ~((UInt32) IPIPEIF_WDRTHR_THR_MASK);
        reg |= IPIPEIF_WDRTHR_THR_MASK & cfg->thr;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRTHR, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRLBK1);
        reg &= ~(IPIPEIF_WDRLBK1_LBK01_MASK | IPIPEIF_WDRLBK1_LBK00_MASK);
        reg |= IPIPEIF_WDRLBK1_LBK01_MASK &
               (cfg->lbk01 << IPIPEIF_WDRLBK1_LBK01_SHIFT);
        reg |= IPIPEIF_WDRLBK1_LBK00_MASK & cfg->lbk00;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRLBK1, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRLBK2);
        reg &= ~(IPIPEIF_WDRLBK2_LBK11_MASK | IPIPEIF_WDRLBK2_LBK10_MASK);
        reg |= IPIPEIF_WDRLBK2_LBK11_MASK &
               (cfg->lbk11 << IPIPEIF_WDRLBK2_LBK11_SHIFT);
        reg |= IPIPEIF_WDRLBK2_LBK10_MASK & cfg->lbk10;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRLBK2, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRSBK1);
        reg &= ~(IPIPEIF_WDRSBK1_SBK01_MASK | IPIPEIF_WDRSBK1_SBK00_MASK);
        reg |= IPIPEIF_WDRSBK1_SBK01_MASK &
               (cfg->sbk01 << IPIPEIF_WDRSBK1_SBK01_SHIFT);
        reg |= IPIPEIF_WDRSBK1_SBK00_MASK & cfg->sbk00;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRSBK1, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRSBK2);
        reg &= ~(IPIPEIF_WDRSBK2_SBK11_MASK | IPIPEIF_WDRSBK2_SBK10_MASK);
        reg |= IPIPEIF_WDRSBK2_SBK11_MASK &
               (cfg->sbk11 << IPIPEIF_WDRSBK2_SBK11_SHIFT);
        reg |= IPIPEIF_WDRSBK2_SBK10_MASK & cfg->sbk10;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRSBK2, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRMA);
        reg &= ~(IPIPEIF_WDRMA_MAS_MASK | IPIPEIF_WDRMA_MAD_MASK);
        reg |= IPIPEIF_WDRMA_MAS_MASK &
               (cfg->mas << IPIPEIF_WDRMA_MAS_SHIFT);
        reg |= IPIPEIF_WDRMA_MAD_MASK & cfg->mad;
        HW_WR_REG32(baseAddr + IPIPEIF_WDRMA, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRLWB1);
        reg &= ~(IPIPEIF_WDRLWB1_LWB01_MASK | IPIPEIF_WDRLWB1_LWB00_MASK);
        reg |= IPIPEIF_WDRLWB1_LWB01_MASK &
               (cfg->lwb[1] << IPIPEIF_WDRLWB1_LWB01_SHIFT);
        reg |= IPIPEIF_WDRLWB1_LWB00_MASK & cfg->lwb[0];
        HW_WR_REG32(baseAddr + IPIPEIF_WDRLWB1, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRLWB2);
        reg &= ~(IPIPEIF_WDRLWB2_LWB11_MASK | IPIPEIF_WDRLWB2_LWB10_MASK);
        reg |= IPIPEIF_WDRLWB2_LWB11_MASK &
               (cfg->lwb[3] << IPIPEIF_WDRLWB2_LWB11_SHIFT);
        reg |= IPIPEIF_WDRLWB2_LWB10_MASK & cfg->lwb[2];
        HW_WR_REG32(baseAddr + IPIPEIF_WDRLWB2, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRSWB1);
        reg &= ~(IPIPEIF_WDRSWB1_SWB01_MASK | IPIPEIF_WDRSWB1_SWB00_MASK);
        reg |= IPIPEIF_WDRSWB1_SWB01_MASK &
               (cfg->swb[1] << IPIPEIF_WDRSWB1_SWB01_SHIFT);
        reg |= IPIPEIF_WDRSWB1_SWB00_MASK & cfg->swb[0];
        HW_WR_REG32(baseAddr + IPIPEIF_WDRSWB1, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRSWB2);
        reg &= ~(IPIPEIF_WDRSWB2_SWB11_MASK | IPIPEIF_WDRSWB2_SWB10_MASK);
        reg |= IPIPEIF_WDRSWB2_SWB11_MASK &
               (cfg->swb[3] << IPIPEIF_WDRSWB2_SWB11_SHIFT);
        reg |= IPIPEIF_WDRSWB2_SWB10_MASK & cfg->swb[2];
        HW_WR_REG32(baseAddr + IPIPEIF_WDRSWB2, reg);

        reg  = HW_RD_REG32(baseAddr + IPIPEIF_WDRMRGCFG);
        reg &=
            ~(IPIPEIF_WDRMRGCFG_MRGWTSFT_MASK | IPIPEIF_WDRMRGCFG_WDRCLIP_MASK);

        reg |=
            (cfg->mergeClip <<
             IPIPEIF_WDRMRGCFG_WDRCLIP_SHIFT) & IPIPEIF_WDRMRGCFG_WDRCLIP_MASK;
        reg |=
            (cfg->mergeShift <<
             IPIPEIF_WDRMRGCFG_MRGWTSFT_SHIFT) &
            IPIPEIF_WDRMRGCFG_MRGWTSFT_MASK;

        HW_WR_REG32(baseAddr + IPIPEIF_WDRMRGCFG, reg);
    }
    else
    {
        cfg4EnaReg &= ~((UInt32) IPIPEIF_CFG4_WDR_EN_MASK);
    }
    HW_WR_REG32(baseAddr + IPIPEIF_CFG4, cfg4EnaReg);
    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetIsifOutConfig(const isshalIpipeifInstObj_t    *instCfg,
                                       const isshalIpipeifIsifOutCfg_t *cfg)
{
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));

    reg  = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_CFG1);
    reg &= ~((UInt32) (IPIPEIF_CFG1_INPSRC1_MASK | IPIPEIF_CFG1_ONESHOT_MASK));
    reg |= IPIPEIF_CFG1_INPSRC1_MASK &
           (((UInt32) (cfg->inpSrc1 - 1U)) << IPIPEIF_CFG1_INPSRC1_SHIFT);

    if((uint32_t)TRUE == cfg->oneShot)
    {
        reg |= IPIPEIF_CFG1_ONESHOT_MASK;
    }

    HW_WR_REG32(instCfg->baseAddr + IPIPEIF_CFG1, reg);

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetIpipeOutConfig(
    const isshalIpipeifInstObj_t     *instCfg,
    const isshalIpipeifIpipeOutCfg_t *cfg)
{
    volatile uint32_t reg;
    volatile uint32_t reg2;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));

    /* Configure the input source for IPIPE out */
    reg  = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_CFG1);
    reg &= ~((UInt32) (IPIPEIF_CFG1_INPSRC2_MASK | IPIPEIF_CFG1_AVGFILT_MASK |
                       IPIPEIF_CFG1_DECIM_MASK));
    reg |= IPIPEIF_CFG1_INPSRC2_MASK &
           (((UInt32) (cfg->inpSrc2 - 1U)) << IPIPEIF_CFG1_INPSRC2_SHIFT);

    if((uint32_t)TRUE == cfg->enable121Avg)
    {
        reg |= IPIPEIF_CFG1_AVGFILT_MASK;
    }
    if((uint32_t)TRUE == cfg->deciCfg.enable)
    {
        reg  |= IPIPEIF_CFG1_DECIM_MASK;
        reg2  = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_RSZ);
        reg2 &= ~((UInt32) IPIPEIF_RSZ_MASK);
        reg2 |= (IPIPEIF_RSZ_MASK & cfg->deciCfg.rsz);
        HW_WR_REG32(instCfg->baseAddr + IPIPEIF_RSZ, reg2);
    }

    /* Reposition HD / VD pulse post re-sizing */
    reg2  = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_INIRSZ);
    reg2 &= ~((UInt32) IPIPEIF_INIRSZ_ALNSYNC_MASK);
    if(0x0 != cfg->deciCfg.crop)
    {
        reg2 &= ~((UInt32) IPIPEIF_INIRSZ_MASK);
        reg2 |= IPIPEIF_INIRSZ_ALNSYNC_MASK;
        reg2 |= (IPIPEIF_INIRSZ_MASK & cfg->deciCfg.crop);
    }
    HW_WR_REG32(instCfg->baseAddr + IPIPEIF_INIRSZ, reg2);

    reg2  = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_GAIN);
    reg2 &= ~((UInt32) IPIPEIF_GAIN_MASK);
    reg2 |= (IPIPEIF_GAIN_MASK & cfg->gainCfg);
    HW_WR_REG32(instCfg->baseAddr + IPIPEIF_GAIN, reg2);

    reg2  = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_OCLIP);
    reg2 &= ~((UInt32) IPIPEIF_OCLIP_MASK);
    reg2 |= (IPIPEIF_OCLIP_MASK & cfg->oclip);
    HW_WR_REG32(instCfg->baseAddr + IPIPEIF_OCLIP, reg2);

    HW_WR_REG32(instCfg->baseAddr + IPIPEIF_CFG1, reg);
    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetH3aOutConfig(
    const isshalIpipeifInstObj_t   *instCfg,
    const isshalIpipeifH3aOutCfg_t *cfg)
{
    volatile uint32_t reg;
    volatile uint32_t reg2;

    GT_assert(VpsHalTrace, (NULL != instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != instCfg->baseAddr));

    /* Configure the input source for IPIPE out */
    reg = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_RSZ3A);

    reg &= ~((UInt32) (IPIPEIF_RSZ3A_AVGFILT_MASK |
                       IPIPEIF_RSZ3A_DECIM_MASK));
    if((uint32_t)TRUE == cfg->enable121Avg)
    {
        reg |= IPIPEIF_RSZ3A_AVGFILT_MASK;
    }
    if((uint32_t)TRUE == cfg->deciCfg.enable)
    {
        reg &= ~((UInt32) IPIPEIF_RSZ3A_RSZ_MASK);
        reg |= IPIPEIF_RSZ3A_DECIM_MASK;
        reg |= IPIPEIF_RSZ3A_RSZ_MASK & cfg->deciCfg.rsz;
    }

    reg2  = HW_RD_REG32(instCfg->baseAddr + IPIPEIF_INIRSZ3A);
    reg2 &= ~((UInt32) IPIPEIF_INIRSZ3A_ALNSYNC_MASK);
    if(0x0 != cfg->deciCfg.crop)
    {
        reg2 &= ~((UInt32) IPIPEIF_INIRSZ3A_INIRSZ_MASK);
        reg2 |= IPIPEIF_INIRSZ3A_ALNSYNC_MASK;
        reg2 |= (IPIPEIF_INIRSZ3A_INIRSZ_MASK & cfg->deciCfg.crop);
    }
    HW_WR_REG32(instCfg->baseAddr + IPIPEIF_INIRSZ3A, reg2);

    HW_WR_REG32(instCfg->baseAddr + IPIPEIF_RSZ3A, reg);
    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetRtConfig(const isshalIpipeifObj_t   *hndl,
                                  const isshalIpipeifRtCfg_t *cfg)
{
    volatile uint32_t reg;
    volatile uint32_t baseAddr;

    GT_assert(VpsHalTrace, (NULL != hndl));
    GT_assert(VpsHalTrace, (NULL != hndl->instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (0x0 != hndl->instCfg->baseAddr));

    baseAddr = hndl->instCfg->baseAddr;

    reg  = HW_RD_REG32(baseAddr + IPIPEIF_CFG1);
    reg &= ~((UInt32) (IPIPEIF_CFG1_INPSRC1_MASK | IPIPEIF_CFG1_INPSRC2_MASK));
    reg |= IPIPEIF_CFG1_INPSRC1_MASK &
           (((UInt32) (cfg->inpSrc1 - 1U)) << IPIPEIF_CFG1_INPSRC1_SHIFT);
    reg |= IPIPEIF_CFG1_INPSRC2_MASK &
           (((UInt32) (cfg->inpSrc2 - 1U)) << IPIPEIF_CFG1_INPSRC2_SHIFT);
    HW_WR_REG32(baseAddr + IPIPEIF_CFG1, reg);

    reg  = HW_RD_REG32(baseAddr + IPIPEIF_CFG4);
    reg &= ~((UInt32) IPIPEIF_CFG4_WDR_EN_MASK);
    if((uint32_t)TRUE == cfg->enableWdr)
    {
        reg |= IPIPEIF_CFG4_WDR_EN_MASK;
    }
    HW_WR_REG32(baseAddr + IPIPEIF_CFG4, reg);

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetConfig(const isshalIpipeifObj_t *hndl,
                                const isshalIpipeifCfg_t *cfg)
{
    int32_t           rtnVal;
    volatile uint32_t regVal;
    volatile uint32_t baseAddr;

    GT_assert(VpsHalTrace, (NULL != hndl));
    GT_assert(VpsHalTrace, (NULL != hndl->instCfg));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = hndl->instCfg->baseAddr;
    rtnVal   = IpipeifCheckCfg(cfg);

    /*
     *  . Setup frame config
     *  . un packing policies
     *  . decompanding config
     *  . saturation config
     *  . dpc config
     *  . dpcm config
     *  . wdr config
     *  . compand config
     *  . output ports
     */
    if(FVID2_SOK == rtnVal)
    {
        /* Frame config */
        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_PPLN);
        regVal &= ~((UInt32) IPIPEIF_PPLN_MASK);
        regVal |= cfg->ipFrameCfg.ppln;
        HW_WR_REG32(baseAddr + IPIPEIF_PPLN, regVal);
        HW_WR_REG32(baseAddr + IPIPEIF_INIRSZ, regVal);
        HW_WR_REG32(baseAddr + IPIPEIF_INIRSZ3A, regVal);

        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_LPFR);
        regVal &= ~((UInt32) IPIPEIF_LPFR_MASK);
        regVal |= cfg->ipFrameCfg.lpfr;
        HW_WR_REG32(baseAddr + IPIPEIF_LPFR, regVal);

        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_HNUM);
        regVal &= ~((UInt32) IPIPEIF_HNUM_MASK);
        regVal |= cfg->ipFrameCfg.hnum;
        HW_WR_REG32(baseAddr + IPIPEIF_HNUM, regVal);

        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_VNUM);
        regVal &= ~((UInt32) IPIPEIF_VNUM_MASK);
        regVal |= cfg->ipFrameCfg.vnum;
        HW_WR_REG32(baseAddr + IPIPEIF_VNUM, regVal);

        /* Un packing config */
        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_CFG1);
        regVal &= ~((UInt32) (IPIPEIF_CFG1_DATASFT_MASK |
                              IPIPEIF_CFG1_UNPACK_MASK |
                              IPIPEIF_CFG1_RAW16_SDRAM_MASK));

        regVal |= ((IPIPEIF_CFG1_UNPACK_MASK) &
                   (cfg->unpack.unpack << IPIPEIF_CFG1_UNPACK_SHIFT));
        regVal |= ((IPIPEIF_CFG1_DATASFT_MASK) &
                   (cfg->unpack.datasft << IPIPEIF_CFG1_DATASFT_SHIFT));
        if(cfg->unpack.raw16_memif)
        {
            regVal |= IPIPEIF_CFG1_RAW16_SDRAM_MASK;
        }
        HW_WR_REG32(baseAddr + IPIPEIF_CFG1, regVal);

        /* Decompanding config */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetCompDecompConfig(
                hndl->instCfg,
                &cfg->compDecompCfg);
        }

        /* Saturation */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetSaturationInsts(hndl->instCfg,
                                               &cfg->satCfg);
        }

        /* Defect Pixel Correction */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetDpcConfig(hndl->instCfg,
                                         &cfg->vportOrIsififDpcCfg,
                                         IPIPEIF_DPC1);
        }
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetDpcConfig(hndl->instCfg, &cfg->memIfDpcCfg,
                                         IPIPEIF_DPC2);
        }
        /* De Compression config */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetDpcmConfig(hndl->instCfg, &cfg->memifDpcmCfg);
        }
        /* WDR Config */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetWdrConfig(hndl->instCfg, &cfg->wdrCfg);
        }
        /* Select output for ISIF */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetIsifOutConfig(hndl->instCfg, &cfg->isifOutCfg);
        }
        /* Select output for IPIPE */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetIpipeOutConfig(hndl->instCfg, &cfg->ipipeOutCfg);
        }

        /* Select output for H3A */
        if(FVID2_SOK == rtnVal)
        {
            rtnVal = IpipeifSetH3aOutConfig(hndl->instCfg, &cfg->h3aOutCfg);
        }
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t IpipeifSetClkConfig(const isshalIpipeifObj_t    *hndl,
                                   const isshalIpipeifClkCfg_t *cfg)
{
    int32_t           rtnVal = FVID2_EBADARGS;
    volatile uint32_t regVal;
    uint32_t          baseAddr;

    if((NULL != cfg) && (NULL != hndl))
    {
        GT_assert(VpsHalTrace, (NULL != hndl->instCfg));
        baseAddr = hndl->instCfg->baseAddr;

        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_CFG1);
        regVal &= ~((UInt32) IPIPEIF_CFG1_CLKSEL_MASK);
        if((uint32_t)TRUE == cfg->moduleClockSel)
        {
            regVal |= IPIPEIF_CFG1_CLKSEL_MASK;
            HW_WR_REG32(baseAddr + IPIPEIF_CFG1, regVal);

            /* Ensure divider are programmed when clock source is functional
             *  clock */
            regVal  = HW_RD_REG32(baseAddr + IPIPEIF_CLKDIV);
            regVal &= ~((UInt32) IPIPEIF_CLKDIV_MASK);
            regVal |= IPIPEIF_CLKDIV_M_MASK & (cfg->clkDivM << 0x8U);
            regVal |= IPIPEIF_CLKDIV_N_MASK & cfg->clkDivN;
            HW_WR_REG32(baseAddr + IPIPEIF_CLKDIV, regVal);
        }
        else
        {
            HW_WR_REG32(baseAddr + IPIPEIF_CFG1, regVal);
        }

        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_CFG2);
        regVal &= ~((UInt32) (IPIPEIF_CFG2_HDPOL_MASK |
                              IPIPEIF_CFG2_VDPOL_MASK));
        if((uint32_t)TRUE == cfg->hdPol)
        {
            regVal |= IPIPEIF_CFG2_HDPOL_MASK;
        }
        if((uint32_t)TRUE == cfg->vdPol)
        {
            regVal |= IPIPEIF_CFG2_VDPOL_MASK;
        }
        HW_WR_REG32(baseAddr + IPIPEIF_CFG2, regVal);

        regVal  = HW_RD_REG32(baseAddr + IPIPEIF_DTUDF);
        regVal &= ~((UInt32) (IPIPEIF_DTUDF_ENM2MSTALL_MASK |
                              IPIPEIF_DTUDF_FIFOWMRKLVL_MASK));
        if((uint32_t)TRUE == cfg->enableM2MStall)
        {
            regVal |= IPIPEIF_DTUDF_ENM2MSTALL_MASK;
        }
        regVal |= IPIPEIF_DTUDF_FIFOWMRKLVL_MASK &
                  (cfg->fifoWmrkLvl << IPIPEIF_DTUDF_FIFOWMRKLVL_SHIFT);

        rtnVal = FVID2_SOK;
    }
    return (rtnVal);
}

static int32_t IpipeifEnDisProc(const isshalIpipeifObj_t  *hndl,
                                const vpsissIpipeifCtrl_t *cfg)
{
    int32_t           rtnVal = FVID2_EBADARGS;
    volatile uint32_t regVal;
    uint32_t          baseAddr;
    vpsissIpipeifSaturaInsts_t    *pSatCfg;
    vpsissIpipeifDeCompandInsts_t *pCompCfg;

    if((NULL != cfg) && (NULL != hndl))
    {
        rtnVal = FVID2_SOK;
        GT_assert(VpsHalTrace, (NULL != hndl->instCfg));
        baseAddr = hndl->instCfg->baseAddr;
        switch(cfg->module)
        {
            case VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG:
                GT_assert(VpsHalTrace, (NULL != cfg->pCompDecompCfg));
                pCompCfg = cfg->pCompDecompCfg;
                /* Vport */
                regVal = HW_RD_REG32(baseAddr + IPIPEIF_VPDCMPCFG);
                if((uint32_t)TRUE == pCompCfg->vportDeCompandCfg.enable)
                {
                    regVal |= IPIPEIF_VPDCMPCFG_ENABLE_MASK;
                }
                else
                {
                    regVal &= ~((UInt32) IPIPEIF_VPDCMPCFG_ENABLE_MASK);
                }
                HW_WR_REG32(baseAddr + IPIPEIF_VPDCMPCFG, regVal);
                /* Memory interface & WDR Output companding not required for
                    now, update here when required */
                break;
            case VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG:
                GT_assert(VpsHalTrace, (NULL != cfg->pSatCfg));
                pSatCfg = cfg->pSatCfg;
                regVal  = HW_RD_REG32(baseAddr + IPIPEIF_WDRSAT_VP2);
                /* Vport */
                if((uint32_t)TRUE == pSatCfg->vportSatCfg.enable)
                {
                    regVal |= IPIPEIF_WDRSAT_VP2_VP_SATEN_MASK;
                }
                else
                {
                    regVal &= ~((UInt32) IPIPEIF_WDRSAT_VP2_VP_SATEN_MASK);
                }
                HW_WR_REG32(baseAddr + IPIPEIF_WDRSAT_VP2, regVal);
                /* ISIF I/F IN */
                regVal = HW_RD_REG32(baseAddr + IPIPEIF_WDRSAT_ISIF2);
                if((uint32_t)TRUE == pSatCfg->isifSatCfg.enable)
                {
                    regVal |= IPIPEIF_WDRSAT_ISIF2_ISIF_SATEN_MASK;
                }
                else
                {
                    regVal &= ~((UInt32) IPIPEIF_WDRSAT_ISIF2_ISIF_SATEN_MASK);
                }
                HW_WR_REG32(baseAddr + IPIPEIF_WDRSAT_ISIF2, regVal);
                /* Not required for mem interface now, update when required */
                break;
            default:
                rtnVal = FVID2_EBADARGS;
                break;
        }
    }
    return rtnVal;
}

