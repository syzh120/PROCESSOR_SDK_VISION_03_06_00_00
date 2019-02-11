/**
 *  \file vpscore_isp.c
 *
 *  \brief This file implements core ISP specific functions.
 *
 *
 */

/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 */
/*
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

#include <ti/drv/vps/src/vpslib/isscore/src/vpscore_isppriv.h>

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* NONE */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*  \brief Function to allocate Handle Object from the pool of objects
 *
 *  \return             pointer to the allocated handle object
 *                      null if there is no free handle object
 */
static vcoreIspHandleObj_t *vcoreIspAllocHndlObj(void);

/*  \brief Function to free allocated Handle Object
 *
 *  \param  hIspObj     pointer to handle object
 *
 *  \return             FVID2_SOK on success
 *                      null if there is no free handle object
 */
static int32_t vcoreIspDeAllocHObj(const vcoreIspHandleObj_t *hIspObj);

static int32_t vcoreIspCheckParams(
    const vcoreIspHandleObj_t *hIspObj,
    const vpsissIspParams_t   *prms);
static void vcoreIspSetDefault(
    vcoreIspHandleObj_t *hIspObj,
    vpsissIspParams_t   *prms);
static int32_t vcoreIspUpdateConfig(
    vcoreIspHandleObj_t     *hIspObj,
    const vpsissIspParams_t *prms);
static int32_t vcoreIspSetConfig(vcoreIspHandleObj_t *hIspObj);
int32_t IspH3aSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissH3aCtrl_t     *h3aCtrl);
int32_t IspH3aGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissH3aCtrl_t           *h3aCtrl);

int32_t IspIsifSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissIsifCtrl_t    *isifCtrl);
int32_t IspIsifGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissIsifCtrl_t          *isifCtrl);

int32_t IspIpipeSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissIpipeCtrl_t   *ipipeCtrl);
int32_t IspIpipeGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissIpipeCtrl_t         *ipipeCtrl);

int32_t IspRszSetConfig(
    vcoreIspHandleObj_t   *hIspObj,
    const vpsissRszCtrl_t *rszCtrl);
int32_t IspRszGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    const vpsissRszCtrl_t     *rszCtrl);

int32_t IspNsf3SetConfig(
    vcoreIspHandleObj_t      *hIspObj,
    const vpsissNsf3Config_t *nsf3Cfg,
    vpsissIspModuleId_t       modId);
int32_t IspNsf3GetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissNsf3Config_t        *nsf3Cfg,
    vpsissIspModuleId_t        modId);

int32_t IspIpipeifSetConfig(
    vcoreIspHandleObj_t       *hIspObj,
    const vpsissIpipeifCtrl_t *cfg);
int32_t IspIpipeifGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissIpipeifCtrl_t       *cfg);

int32_t IspGlbceSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissGlbceCtrl_t   *glbceCtrl);
int32_t IspGlbceGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissGlbceCtrl_t         *glbceCtrl);

void vcoreIspCaptEofHandler(const UInt32 *event,
                            UInt32        numEvents,
                            Ptr           arg);
void vcoreIspM2mEofHandler(const UInt32 *event,
                           UInt32        numEvents,
                           Ptr           arg);
void vcoreIspErrEvtHandler(const UInt32 *event,
                           UInt32        numEvents,
                           Ptr           arg);
static void vcoreIspSetGlbceMux(const vcoreIspHandleObj_t *hIspObj);
static void vcoreIspSetVmux(const vcoreIspHandleObj_t *hIspObj);
static int32_t vcoreIspSetupVmux(
    isshalVMuxSrcPorts_t  vmuxSrc,
    isshalVMuxSinkPorts_t vmuxSink,
    uint32_t              flag);

static int32_t checkIsifVfdcCfg(const vpsissIspParams_t      *pIspParams,
                                const vpsissIsifVfdcConfig_t *pVfdcCfg);

void vcoreIspErrEvntHndler(
    const UInt32 *event,
    UInt32        numEvents,
    Ptr           arg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global ISP common object */
static vcoreIspCommonObj_t gVpsCoreIspCommonObj = {FALSE};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Function initializes all ISP hals
   Assuming iss control hal is already initialized */
int32_t vcoreIspInit(const VpsLib_PlatformData *platData)
{
    int32_t  status = FVID2_SOK;
    uint32_t cnt;
    const vpshalissIspPlatformData_t *ispPlatData;

    if(NULL == platData)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
/* MISRA.CAST.PTR_TO_INT
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * Name 'ispPlatData'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointers to different layer's handles are stored as void*.
 */
        ispPlatData = (const vpshalissIspPlatformData_t *)platData->ispHal;
        if(NULL == ispPlatData)
        {
            status = FVID2_EBADARGS;
        }
    }

    /* Initialize all hals, all hals support multiple initialization */
    for(cnt = 0U; (cnt < VPS_ISS_ISP_MAX_MODULE) && (FVID2_SOK == status);
        cnt++)
    {
        switch(cnt)
        {
            case VPS_ISS_ISP_MODULE_IPIPEIF:
                status = VpsHal_issipipeifInit(
                    ispPlatData->numIpipeifInst,
                    &ispPlatData->ipipeifInstPrms,
                    NULL);
                break;
            /* NSF3 instance is protected from multiple init */
            case VPS_ISS_ISP_MODULE_NSF3:
            case VPS_ISS_ISP_MODULE_CNF:
                status = VpsHal_issnsf3Init(
                    ispPlatData->numNsf3Inst,
                    ispPlatData->nsf3InstPrms,
                    NULL);
                break;
            case VPS_ISS_ISP_MODULE_ISIF:
                status = VpsHal_issisifInit(
                    ispPlatData->numIsifInst,
                    &ispPlatData->isifInstPrms,
                    NULL);
                break;
            case VPS_ISS_ISP_MODULE_IPIPE:
                status = VpsHal_issipipeInit(
                    ispPlatData->numIpipeInst,
                    &ispPlatData->ipipeInstPrms,
                    NULL);
                break;
            case VPS_ISS_ISP_MODULE_RSZ:
                status = VpsHal_issrszInit(
                    ispPlatData->numRszInst,
                    &ispPlatData->rszInstPrms,
                    NULL);
                break;
            case VPS_ISS_ISP_MODULE_H3A:
                status = VpsHal_issh3aInit(
                    ispPlatData->numH3aInst,
                    &ispPlatData->h3aInstPrms,
                    NULL);
                break;
            case VPS_ISS_ISP_MODULE_GLBCE:
                status = VpsHal_issglbceInit(
                    ispPlatData->numGlbceInst,
                    &ispPlatData->glbceInstPrms,
                    NULL);
                break;
            default:
                break;
        }
    }

    if((FVID2_SOK == status) && (FALSE == gVpsCoreIspCommonObj.isInited))
    {
        BspUtils_memset(
            &gVpsCoreIspCommonObj,
            0x0U,
            sizeof(vcoreIspCommonObj_t));

        for(cnt = 0U; cnt < VCORE_MAX_ISP_OBJECTS; cnt++)
        {
            gVpsCoreIspCommonObj.handleObj[cnt].isAllocated = (UInt32) FALSE;
        }

        gVpsCoreIspCommonObj.isInited = (UInt32) TRUE;
    }

    return (status);
}

/* Function Deinitializes all ISP hals */
int32_t vcoreIspDeInit(Ptr arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t cnt;

    if(0U != gVpsCoreIspCommonObj.openCnt)
    {
        status = FVID2_EFAIL;
    }
    else
    {
        if(NULL != gVpsCoreIspCommonObj.errEvntHndle)
        {
            /* DeInitialize Error Event Handler */
            status = Vps_iemUnRegister(gVpsCoreIspCommonObj.errEvntHndle);
            gVpsCoreIspCommonObj.errEvntHndle = NULL;
        }
    }

    /* DeInitialize the HALs, All Hals can deinitialized multiple times */
    for(cnt = 0U; ((cnt < VPS_ISS_ISP_MAX_MODULE) && (FVID2_SOK == status));
        cnt++)
    {
        switch(cnt)
        {
            case VPS_ISS_ISP_MODULE_IPIPEIF:
                status += VpsHal_issipipeifDeInit(NULL);
                break;
            case VPS_ISS_ISP_MODULE_NSF3:
                status += VpsHal_issnsf3DeInit(NULL);
                break;
            case VPS_ISS_ISP_MODULE_ISIF:
                status += VpsHal_issisifDeInit(NULL);
                break;
            case VPS_ISS_ISP_MODULE_IPIPE:
                status += VpsHal_issipipeDeInit(NULL);
                break;
            case VPS_ISS_ISP_MODULE_RSZ:
                status += VpsHal_issrszDeInit(NULL);
                break;
            case VPS_ISS_ISP_MODULE_H3A:
                status += VpsHal_issh3aDeInit(NULL);
                break;
            case VPS_ISS_ISP_MODULE_GLBCE:
                status += VpsHal_issglbceDeInit(NULL);
                break;
            default:
                break;
        }
    }

    if(FVID2_SOK == status)
    {
        gVpsCoreIspCommonObj.isInited = (UInt32) FALSE;
    }

    return (status);
}

/* Function opens all ISP hals,
   It allocates the ISP handle object and opens the ISP hals.
   The bitmask in the modules parameters is used for selecting the hal
   to be opened */
vcoreIspHandleObj_t *vcoreIspOpenHals(
    const vpsissIspOpenParams_t *coreOpenPrms,
    vcoreIspOpenMode_t           openMode,
    const VpsCore_OpenPrms      *openPrms,
    vpsissIspOpenRetParams_t    *coreReturnPrms,
    Ptr                          arg)
{
    int32_t              status = FVID2_SOK;
    uint32_t             cnt;
    vcoreIspHandleObj_t *hIspObj = NULL;
    isshalOpenParams_t   halOpenPrms;

    static uint32_t      gVpsCoreIspErrorEvnts[] =
    {
        IEM_ISP_EVENT_OCP_ERR,
        IEM_ISP_EVENT_RSZ_INT_FIFO_IN_BLK_ERR,
        IEM_ISP_EVENT_RSZ_INT_FIFO_OVF,
        IEM_ISP_EVENT_H3A_OVF,
        IEM_ISP_EVENT_IPIPEIF_UDF,
        IEM_ISP_EVENT_IPIPE_BOXCAR_OVF,
        IEM_ISP_EVENT_ISIF_OVF,
        IEM_ISP_EVENT_IPIPE_HST_ERR,
        IEM_ISP_EVENT_IPIPE_BSC_ERR,
        IEM_ISP_EVENT_NSF3V_INT_OVERFLOW,
        IEM_ISP_EVENT_GLBCE_ERROR,
        IEM_ISP_EVENT_CNFA_INT_OVERFLOW,
        IEM_ISP_EVENT_SWT_NSF3V_OVERFLOW
    };

    if(NULL == coreOpenPrms)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        /* Resizer and IPIPEIF are minimum required modules for this
           ISP driver to work */
        if((FALSE == coreOpenPrms->isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF]) ||
           (FALSE == coreOpenPrms->isModuleReq[VPS_ISS_ISP_MODULE_RSZ]))
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == status)
    {
        /* Allocate ISP Handle Object */
        hIspObj = vcoreIspAllocHndlObj();

        if(NULL == hIspObj)
        {
            status = FVID2_EALLOC;
        }
        else
        {
            /* Register error event handler only for the first handle */
            if(0U == gVpsCoreIspCommonObj.openCnt)
            {
                /* Register handler for error interrupts */
                gVpsCoreIspCommonObj.errEvntHndle = Vps_iemregister(
                    IEM_INST_ID_IRQ0,
                    IEM_EG_ISP0,
                    (const uint32_t *)gVpsCoreIspErrorEvnts,
                    sizeof(gVpsCoreIspErrorEvnts)/sizeof(uint32_t),
                    IEM_PRIORITY0,
                    &vcoreIspErrEvtHandler,
                    hIspObj);
                if(NULL == gVpsCoreIspCommonObj.errEvntHndle)
                {
                    vcoreIspDeAllocHObj(hIspObj);
                    hIspObj = NULL;
                    status  = FVID2_EFAIL;
                }
            }
        }
    }

    if(NULL != hIspObj)
    {
        /* Open All ISP Module Hals */
        /* Since Video Port is receiving data for both the passes, this
         * flag should be enabled */
        status = VpsHal_issEnableModule(ISSHAL_ISS_MODULE_SYNC, (uint32_t) TRUE);
        /* This function does not return error unless module id is wrong */
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        for(cnt = 0U; cnt < VPS_ISS_ISP_MAX_MODULE; cnt++)
        {
            hIspObj->isModReq[cnt] = coreOpenPrms->isModuleReq[cnt];
        }

        for(cnt = 0U; cnt < VPS_ISS_ISP_MAX_MODULE; cnt++)
        {
            /* If module is not required, no need to open this module */
            if(TRUE == hIspObj->isModReq[cnt])
            {
                switch(cnt)
                {
                    case VPS_ISS_ISP_MODULE_IPIPEIF:
                        halOpenPrms.instId = ISSHAL_IPIPEIF_INST_0;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF] =
                            VpsHal_issipipeifOpen(&halOpenPrms, NULL);
                        if(NULL ==
                           hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    case VPS_ISS_ISP_MODULE_NSF3:
                        halOpenPrms.instId = ISSHAL_NSF3_INST_0;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3] =
                            VpsHal_issnsf3Open(&halOpenPrms, NULL);
                        if(NULL == hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    case VPS_ISS_ISP_MODULE_ISIF:
                        halOpenPrms.instId = ISSHAL_ISIF_INST_0;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF] =
                            VpsHal_issisifOpen(&halOpenPrms, NULL);
                        if(NULL ==
                           hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    case VPS_ISS_ISP_MODULE_IPIPE:
                        halOpenPrms.instId = ISSHAL_IPIPE_INST_0;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE] =
                            VpsHal_issipipeOpen(&halOpenPrms, NULL);
                        if(NULL ==
                           hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    case VPS_ISS_ISP_MODULE_RSZ:
                        halOpenPrms.instId = ISSHAL_RSZ_INST_0;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ] =
                            VpsHal_issrszOpen(&halOpenPrms, NULL);
                        if(NULL == hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    case VPS_ISS_ISP_MODULE_H3A:
                        halOpenPrms.instId = ISSHAL_H3A_INST_0;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A] =
                            VpsHal_issh3aOpen(&halOpenPrms, NULL);
                        if(NULL == hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    case VPS_ISS_ISP_MODULE_CNF:
                        halOpenPrms.instId = ISSHAL_NSF3_INST_1;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF] =
                            VpsHal_issnsf3Open(&halOpenPrms, NULL);
                        if(NULL == hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    case VPS_ISS_ISP_MODULE_GLBCE:
                        halOpenPrms.instId = ISSHAL_GLBCE_INST_0;

                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE] =
                            VpsHal_issglbceOpen(&halOpenPrms, NULL);
                        if(NULL ==
                           hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE])
                        {
                            status = FVID2_EBADARGS;
                        }
                        break;

                    default:
                        break;
                }
            }
            if(FVID2_SOK != status)
            {
                break;
            }
        }

        if(FVID2_SOK == status)
        {
            /* Set Default ISP params */
            vcoreIspSetDefault(hIspObj, &hIspObj->params);

            if(NULL != openPrms)
            {
                BspUtils_memcpy(
                    &hIspObj->openPrms,
                    openPrms,
                    sizeof(VpsCore_OpenPrms));
            }
        }
    }
    else
    {
        status = FVID2_EALLOC;
    }

    if(FVID2_SOK != status)
    {
        /* Close All Open Hals */
        vcoreIspCloseHals(hIspObj, NULL);
        hIspObj = NULL;
    }
    else
    {
        hIspObj->openMode = openMode;

        if(VCORE_ISP_OPEN_MODE_CAPTURE == openMode)
        {
            BspUtils_memset(&hIspObj->captStreamMap[0U], (UInt8)0xFF,
                            sizeof(hIspObj->captStreamMap));
        }

        /* Increase Open Count */
        gVpsCoreIspCommonObj.openCnt++;
    }

    return (hIspObj);
}

/* Function closes all ISP hals,
 * it closes all the hals whose hal handle is not null and
 * frees up handle object.
 */
int32_t vcoreIspCloseHals(vcoreIspHandleObj_t *hIspObj, Ptr arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t cnt;

    if(NULL == hIspObj)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        for(cnt = 0U; cnt < VPS_ISS_ISP_MAX_MODULE; cnt++)
        {
            if(TRUE == hIspObj->isModReq[cnt])
            {
                switch(cnt)
                {
                    case VPS_ISS_ISP_MODULE_IPIPEIF:
                        if(NULL !=
                           hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF])
                        {
                            status = VpsHal_issipipeifClose(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF]
                                , NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF] =
                                NULL;
                        }
                        break;
                    case VPS_ISS_ISP_MODULE_NSF3:
                        if(NULL != hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3])
                        {
                            status = VpsHal_issnsf3Close(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3],
                                NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3] =
                                NULL;
                        }
                        break;
                    case VPS_ISS_ISP_MODULE_ISIF:
                        if(NULL != hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF])
                        {
                            status = VpsHal_issisifClose(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
                                NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF] =
                                NULL;
                        }
                        break;
                    case VPS_ISS_ISP_MODULE_IPIPE:
                        if(NULL !=
                           hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE])
                        {
                            status = VpsHal_issipipeClose(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                                NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE] =
                                NULL;
                        }
                        break;
                    case VPS_ISS_ISP_MODULE_RSZ:
                        if(NULL != hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ])
                        {
                            status = VpsHal_issrszClose(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
                                NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ] =
                                NULL;
                        }
                        break;
                    case VPS_ISS_ISP_MODULE_H3A:
                        if(NULL != hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A])
                        {
                            status = VpsHal_issh3aClose(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
                                NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A] =
                                NULL;
                        }
                        break;
                    case VPS_ISS_ISP_MODULE_CNF:
                        if(NULL != hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF])
                        {
                            status = VpsHal_issnsf3Close(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF],
                                NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF] =
                                NULL;
                        }
                        break;
                    case VPS_ISS_ISP_MODULE_GLBCE:
                        if(NULL !=
                           hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE])
                        {
                            status = VpsHal_issglbceClose(
                                hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
                                NULL);
                        }
                        if(FVID2_SOK == status)
                        {
                            hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE] =
                                NULL;
                        }
                        break;
                    default:
                        break;
                }
            }
            /* Close should not fail, unless the handle is corrupted or it
               is called multiple times */
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
        }

        status = vcoreIspDeAllocHObj(hIspObj);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        gVpsCoreIspCommonObj.openCnt--;
        if(0U == gVpsCoreIspCommonObj.openCnt)
        {
            if(NULL != gVpsCoreIspCommonObj.errEvntHndle)
            {
                /* DeInitialize Error Event Handler */
                status = Vps_iemUnRegister(gVpsCoreIspCommonObj.errEvntHndle);
                gVpsCoreIspCommonObj.errEvntHndle = NULL;
            }
            else
            {
                /* This pointer should not be null */
                GT_assert(VpsIssCoreTrace, FALSE);
            }
        }
    }

    return (status);
}

int32_t vcoreIspControl(vcoreIspHandleObj_t *hIspObj,
                        uint32_t             cmd,
                        void                *appArgs,
                        void                *drvArgs)
{
    int32_t status = FVID2_SOK;
    vpsissCnfConfig_t *cnfPrms = NULL;

    if(NULL == hIspObj)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        switch(cmd)
        {
            /* Case is to get H3A Configuration */
            case VPS_ISS_H3A_IOCTL_GET_CONFIG:
                status = IspH3aGetConfig(hIspObj,
                                         (vpsissH3aCtrl_t *) appArgs);
                break;

            /* Case is to set H3A Configuration */
            case VPS_ISS_H3A_IOCTL_SET_CONFIG:
                status = IspH3aSetConfig(hIspObj,
                                         (vpsissH3aCtrl_t *) appArgs);
                break;

            /* Case is to get ISIF Configuration */
            case VPS_ISS_ISIF_IOCTL_GET_CONFIG:
                status = IspIsifGetConfig(hIspObj,
                                          (vpsissIsifCtrl_t *) appArgs);
                break;

            /* Case is to set ISIF Configuration */
            case VPS_ISS_ISIF_IOCTL_SET_CONFIG:
                status = IspIsifSetConfig(hIspObj,
                                          (vpsissIsifCtrl_t *) appArgs);
                break;

            /* IPIPE Control IOCTL */
            case VPS_ISS_IPIPE_IOCTL_GET_CONFIG:
                status = IspIpipeGetConfig(hIspObj,
                                           (vpsissIpipeCtrl_t *) appArgs);
                break;

            case VPS_ISS_IPIPE_IOCTL_SET_CONFIG:
                status = IspIpipeSetConfig(hIspObj,
                                           (vpsissIpipeCtrl_t *) appArgs);
                break;

            /* RSZ Control IOCTL */
            case VPS_ISS_RSZ_IOCTL_SET_CONFIG:
                status = IspRszSetConfig(hIspObj, (vpsissRszCtrl_t *) appArgs);
                break;

            /* RSZ Control IOCTL */
            case VPS_ISS_RSZ_IOCTL_GET_CONFIG:
                status = IspRszGetConfig(hIspObj, (vpsissRszCtrl_t *) appArgs);
                break;

            /* NSF3 Control IOCTL */
            case VPS_ISS_NSF3_IOCTL_SET_CONFIG:
            {
                hIspObj->nsf3FrmSize[0U].width =
                    hIspObj->params.inFmt.width;
                hIspObj->nsf3FrmSize[0U].height =
                    hIspObj->params.inFmt.height;

                status = IspNsf3SetConfig(
                    hIspObj,
                    (vpsissNsf3Config_t *) appArgs,
                    VPS_ISS_ISP_MODULE_NSF3);
                break;
            }

            /* NSF3 Control IOCTL */
            case VPS_ISS_NSF3_IOCTL_GET_CONFIG:
                status = IspNsf3GetConfig(
                    hIspObj,
                    (vpsissNsf3Config_t *) appArgs,
                    VPS_ISS_ISP_MODULE_NSF3);
                break;

            /* Case is to get VP1 Configuration */
            case VPS_ISS_ISIF_IOCTL_GET_VP1_CONFIG:
            {
                vpsissIspVp1Config_t *vp1Cfg = (vpsissIspVp1Config_t *)appArgs;

                if(NULL != vp1Cfg)
                {
                    vp1Cfg->enableDelay      = hIspObj->vp1Cfg.enableDelay;
                    vp1Cfg->horzDelay        = hIspObj->vp1Cfg.horzDelay;
                    vp1Cfg->vertDelay        = hIspObj->vp1Cfg.vertDelay;
                    vp1Cfg->cropWin          = hIspObj->vp1Cfg.cropWin;
                    vp1Cfg->enableYcSwap     = hIspObj->vp1Cfg.enableYcSwap;
                    vp1Cfg->enableLumaOddPos = hIspObj->vp1Cfg.enableLumaOddPos;
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;
            }

            /* Case is to set VP1 Configuration */
            case VPS_ISS_ISIF_IOCTL_SET_VP1_CONFIG:
            {
                vpsissIspVp1Config_t *vp1Cfg = (vpsissIspVp1Config_t *)appArgs;

                if(NULL != vp1Cfg)
                {
                    hIspObj->vp1Cfg.enableDelay      = vp1Cfg->enableDelay;
                    hIspObj->vp1Cfg.horzDelay        = vp1Cfg->horzDelay;
                    hIspObj->vp1Cfg.vertDelay        = vp1Cfg->vertDelay;
                    hIspObj->vp1Cfg.cropWin          = vp1Cfg->cropWin;
                    hIspObj->vp1Cfg.enableYcSwap     = vp1Cfg->enableYcSwap;
                    hIspObj->vp1Cfg.enableLumaOddPos = vp1Cfg->enableLumaOddPos;

                    /* VP1 configuration will be actually set when
                       submitting a frame processing is submitted */
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;
            }

            /* Case is to get VP2 Configuration */
            case VPS_ISS_IPIPE_IOCTL_GET_VP2_CONFIG:
            {
                vpsissIspVp2Config_t *vp2Cfg = (vpsissIspVp2Config_t *)appArgs;

                if(NULL != vp2Cfg)
                {
                    vp2Cfg->pos       = hIspObj->vp2Cfg.pos;
                    vp2Cfg->horzDelay = hIspObj->vp2Cfg.horzDelay;
                    vp2Cfg->vertDelay = hIspObj->vp2Cfg.vertDelay;
                    vp2Cfg->inMsbPos  = hIspObj->vp2Cfg.inMsbPos;
                    vp2Cfg->outMsbPos = hIspObj->vp2Cfg.outMsbPos;
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;
            }

            /* Case is to set VP2 Configuration */
            case VPS_ISS_IPIPE_IOCTL_SET_VP2_CONFIG:
            {
                vpsissIspVp2Config_t *vp2Cfg = (vpsissIspVp2Config_t *)appArgs;

                if(NULL != vp2Cfg)
                {
                    hIspObj->vp2Cfg.pos       = vp2Cfg->pos;
                    hIspObj->vp2Cfg.horzDelay = vp2Cfg->horzDelay;
                    hIspObj->vp2Cfg.vertDelay = vp2Cfg->vertDelay;
                    hIspObj->vp2Cfg.inMsbPos  = vp2Cfg->inMsbPos;
                    hIspObj->vp2Cfg.outMsbPos = vp2Cfg->outMsbPos;
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;
            }

            /* CNF Control IOCTL */
            case VPS_ISS_CNF_IOCTL_SET_CONFIG:
            {
                cnfPrms = (vpsissCnfConfig_t *) appArgs;

                hIspObj->cnfPrms.enable    = cnfPrms->enable;
                hIspObj->cnfPrms.enableCds = cnfPrms->enableCds;

                /* CNF Frame size is same as RSZ_A Output frames size */
                if(TRUE == cnfPrms->enableCds)
                {
                    hIspObj->cnfPrms.frameWidth =
                        hIspObj->params.inFmt.width/2;
                    hIspObj->cnfPrms.frameHeight =
                        hIspObj->params.inFmt.height/2;
                }
                else
                {
                    hIspObj->cnfPrms.frameWidth =
                        hIspObj->params.inFmt.width;
                    hIspObj->cnfPrms.frameHeight =
                        hIspObj->params.inFmt.height;
                }
                hIspObj->nsf3FrmSize[1U].width =
                    hIspObj->cnfPrms.frameWidth;
                hIspObj->nsf3FrmSize[1U].height =
                    hIspObj->cnfPrms.frameHeight;

                status = IspNsf3SetConfig(
                    hIspObj,
                    &cnfPrms->nsf3Cfg,
                    VPS_ISS_ISP_MODULE_CNF);
                break;
            }

            case VPS_ISS_CNF_IOCTL_GET_CONFIG:
            {
                cnfPrms = (vpsissCnfConfig_t *) appArgs;

                status = IspNsf3GetConfig(
                    hIspObj,
                    (vpsissNsf3Config_t *) appArgs,
                    VPS_ISS_ISP_MODULE_CNF);

                cnfPrms->enable    = hIspObj->cnfPrms.enable;
                cnfPrms->enableCds = hIspObj->cnfPrms.enableCds;
                break;
            }

            /* GLBCE Control IOCTL */
            case VPS_ISS_GLBCE_IOCTL_SET_CONFIG:
                status = IspGlbceSetConfig(
                    hIspObj,
                    (vpsissGlbceCtrl_t *) appArgs);
                break;

            case VPS_ISS_GLBCE_IOCTL_GET_CONFIG:
                status = IspGlbceGetConfig(
                    hIspObj,
                    (vpsissGlbceCtrl_t *) appArgs);
                break;

            /* IPIPEIF Control IOCTL */
            case VPS_ISS_IPIPEIF_IOCTL_GET_CONFIG:
                status = IspIpipeifGetConfig(
                    hIspObj,
                    (vpsissIpipeifCtrl_t *) appArgs);
                break;

            /* IPIPEIF Control IOCTL */
            case VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG:
                status = IspIpipeifSetConfig(
                    hIspObj,
                    (const vpsissIpipeifCtrl_t *) appArgs);
                break;

            case VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
                    ISSHAL_IOCTL_IPIPE_UPDATE_LUT,
                    appArgs,
                    drvArgs);
                break;
            case VPS_ISS_SET_ISS_STREAM_PRI_CONFIG:

                status = FVID2_EBADARGS;
                if(NULL != appArgs)
                {
                    uint32_t idx;
                    vpsissRoutingConfig_t *cfg = (vpsissRoutingConfig_t *)
                                                 appArgs;
                    for(idx = 0U; ((idx < cfg->numStreams) &&
                                   (idx < VPS_ISS_INIT_MAX)); idx++)
                    {
                        status = VpsHal_issSetInitiatorPriority(
                            cfg->source[idx],
                            cfg->priority[idx],
                            cfg->cportId[idx]);
                    }
                }

                break;

            default:
                status = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (status);
}

int32_t vcoreIspStart(vcoreIspHandleObj_t *hIspObj, Ptr arg)
{
    int32_t            status = FVID2_SOK;
    volatile uint32_t  moduleCnt;
    issCtrlProcMode_t  procMode;
    vpsissIspParams_t *prms;

    prms = &hIspObj->params;
    if(VCORE_ISP_OPEN_MODE_CAPTURE == hIspObj->openMode)
    {
        /* Update the frame size */
        status = vcoreIspSetSrcSize(hIspObj);

        /* TODO: Need to change this hard-coded path when DFS/WDR
                 is supported in OTF mode */
        hIspObj->ipipeifRtCfg.inpSrc1 = ISSHAL_IPIPEIF_ISIF_OUT_RAW_VPORT;
        hIspObj->ipipeifRtCfg.inpSrc2 = ISSHAL_IPIPEIF_IPIPE_OUT_ISIF;

        if(NULL != hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF])
        {
            status = VpsHal_issipipeifControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
                VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG,
                &hIspObj->ipipeifRtCfg,
                NULL);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
        }

        if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_CNF])
        {
            /* CNF configuration could be changed, so set it on every frame */
            status = VpsHal_issSetCnfConfig(&hIspObj->cnfPrms);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
        }
        vcoreIspSetGlbceMux(hIspObj);

        vcoreIspSetVmux(hIspObj);

        procMode = ISSHAL_ISS_PROC_MODE_FREE_RUN;
    }
    else
    {
        procMode = ISSHAL_ISS_PROC_MODE_ONE_SHOT;
    }

    /* Start with the last module */
    moduleCnt = VPS_ISS_ISP_MAX_MODULE;
    do
    {
        moduleCnt--;
        /* start modules only if they are opened */
        if(TRUE == hIspObj->isModReq[moduleCnt])
        {
            if(VPS_ISS_ISP_MODULE_H3A != moduleCnt)
            {
                /* Individual Resizer instances should be started first */
                if(VPS_ISS_ISP_MODULE_RSZ == moduleCnt)
                {
                    if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_A])
                    {
                        status = VpsHal_issrszStartInst(
                            hIspObj->halHandles[moduleCnt],
                            VPS_ISS_RSZ_SCALER_A,
                            procMode,
                            NULL);

                        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                    }

                    if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_B])
                    {
                        status = VpsHal_issrszStartInst(
                            hIspObj->halHandles[moduleCnt],
                            VPS_ISS_RSZ_SCALER_B,
                            procMode,
                            NULL);

                        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                    }
                }
                if(NULL != hIspObj->startModuleFxn[moduleCnt])
                {
                    /* MISRA C : Flags using halHandles as an potential porting
                        error, hence using this temp variable */
                    VpsHal_Handle halHandle = hIspObj->halHandles[moduleCnt];
                    status = hIspObj->startModuleFxn[moduleCnt](
                        halHandle,
                        procMode,
                        NULL);

                    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                }
            }
            else
            {
                if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_AF])
                {
                    status = VpsHal_issh3aAfStart(
                        hIspObj->halHandles[moduleCnt],
                        procMode,
                        NULL);
                    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                }
                if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_AEWB])
                {
                    status = VpsHal_issh3aAewbStart(
                        hIspObj->halHandles[moduleCnt],
                        procMode,
                        NULL);
                    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                }
            }
        }
    } while(moduleCnt != 0U);

    return (status);
}

int32_t vcoreIspStop(vcoreIspHandleObj_t *hIspObj, Ptr arg)
{
    int32_t            status;
    uint32_t           cnt;
    vpsissIspParams_t *prms;

    prms = &hIspObj->params;
    /* Start the modules, from last to first */
    cnt    = VPS_ISS_ISP_MAX_MODULE;
    status = FVID2_EBADARGS;
    do
    {
        cnt--;
        /* If the bit is not set, no need to open this module */
        if(TRUE == hIspObj->isModReq[cnt])
        {
            if(VPS_ISS_ISP_MODULE_H3A != cnt)
            {
                /* Individual Resizer instances should be stopped first */
                if(VPS_ISS_ISP_MODULE_RSZ == cnt)
                {
                    if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_A])
                    {
                        status = VpsHal_issrszStopInst(
                            hIspObj->halHandles[cnt],
                            VPS_ISS_RSZ_SCALER_A);

                        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                    }

                    if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_B])
                    {
                        status = VpsHal_issrszStopInst(
                            hIspObj->halHandles[cnt],
                            VPS_ISS_RSZ_SCALER_B);

                        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                    }
                }
                if(NULL != hIspObj->stopModuleFxn[cnt])
                {
                    status = hIspObj->stopModuleFxn[cnt](
                        hIspObj->halHandles[cnt],
                        NULL);

                    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                }
            }
            else
            {
                if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_AF])
                {
                    status = VpsHal_issh3aAfStop(
                        hIspObj->halHandles[cnt],
                        NULL);
                    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                }
                if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_AEWB])
                {
                    status = VpsHal_issh3aAewbStop(
                        hIspObj->halHandles[cnt],
                        NULL);
                    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
                }
            }
        }
    } while(cnt != 0U);

    return (status);
}

int32_t vcoreIspSetParams(vcoreIspHandleObj_t     *hIspObj,
                          const vpsissIspParams_t *prms)
{
    int32_t status = FVID2_SOK;

    /* Check for NULL pointer */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));
    GT_assert(VpsIssCoreTrace, (NULL != prms));

    /* Check for Errors */
    status = vcoreIspCheckParams(hIspObj, prms);

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_GLBCE_PATH_ISP == prms->glbcePath)
        {
            if(TRUE == prms->enableWdrMerge)
            {
                /* Crop the first two lines in VP2, since first two
                 * lines are not merged in WDR merge */
                hIspObj->vp2Cfg.pos.startY = 0x2U;
            }
            hIspObj->vp2Cfg.outMsbPos = VPS_ISS_OUTPUT_MSB_POS_BIT12;
        }
        else if(VPS_ISS_GLBCE_PATH_CAL == prms->glbcePath)
        {
            hIspObj->vp2Cfg.outMsbPos = VPS_ISS_OUTPUT_MSB_POS_BIT16;
        }
        else
        {
            hIspObj->vp2Cfg.outMsbPos = VPS_ISS_OUTPUT_MSB_POS_BIT16;
        }

        if((VPS_ISS_NSF3_PATH_ISP == prms->nsf3Path) ||
           (VPS_ISS_NSF3_PATH_CAL == prms->nsf3Path) ||
           (TRUE == prms->enableDpcPreNsf3))
        {
            /* Update VP1 Configuration */

            /* Set the NSF3 configuration in VP port */
            if((int32_t) TRUE == Fvid2_isDataFmtBayer(prms->inFmt.dataFormat))
            {
                hIspObj->vp1Cfg.inpDataFormat = ISSHAL_NSF3_INP_DATA_RAW;
            }
            else if(FVID2_BPP_BITS16 == prms->inFmt.bpp)
            {
                hIspObj->vp1Cfg.inpDataFormat = ISSHAL_NSF3_INP_DATA_YUV_16BIT;
            }
            else
            {
                hIspObj->vp1Cfg.inpDataFormat = ISSHAL_NSF3_INP_DATA_YUV_8BIT;
            }

            hIspObj->vp1Cfg.hdPol        = FVID2_POL_HIGH;
            hIspObj->vp1Cfg.vdPol        = FVID2_POL_HIGH;
            hIspObj->vp1Cfg.isInvertData = (UInt32) FALSE;
            switch(prms->inFmt.bpp)
            {
                case FVID2_BPP_BITS8:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT7;
                    break;
                case FVID2_BPP_BITS9:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT8;
                    break;
                case FVID2_BPP_BITS10:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT9;
                    break;
                case FVID2_BPP_BITS11:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT10;
                    break;
                case FVID2_BPP_BITS12:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT11;
                    break;
                case FVID2_BPP_BITS13:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT12;
                    break;
                case FVID2_BPP_BITS14:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT13;
                    break;
                case FVID2_BPP_BITS15:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT14;
                    break;
                case FVID2_BPP_BITS16:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT15;
                    break;
                default:
                    hIspObj->vp1Cfg.inMsbPos = VPS_ISS_INPUT_MSB_POS_BIT11;
                    break;
            }

            /* Set the VP1 Configuration */
            if((int32_t) TRUE == Fvid2_isDataFmtBayer(prms->inFmt.dataFormat))
            {
                hIspObj->vp1Cfg.bayerDataFormat =
                    (Fvid2_DataFormat) prms->inFmt.dataFormat;
            }
            hIspObj->vp1Cfg.enableDelay        = (UInt32) FALSE;
            hIspObj->vp1Cfg.cropWin.cropStartX = 0U;
            hIspObj->vp1Cfg.cropWin.cropStartY = 0U;
            hIspObj->vp1Cfg.cropWin.cropWidth  = prms->inFmt.width;
            hIspObj->vp1Cfg.cropWin.cropHeight = prms->inFmt.height;
            hIspObj->vp1Cfg.enableYcSwap       = (UInt32) FALSE;
            hIspObj->vp1Cfg.enableLumaOddPos   = (UInt32) FALSE;

            if(TRUE == prms->enableWdrMerge)
            {
                hIspObj->vp1Cfg.enableDelay = (UInt32) TRUE;
                /* TODO Change this delay based on the NSF3
                 *      blanking requirement and ipipeif lpfr setting */
                hIspObj->vp1Cfg.horzDelay = 16U;
                hIspObj->vp1Cfg.vertDelay = 16U; /* Should be set to nsf3
                                               * vertical blanking
                                               * requirement - ipipeif_lpfr */
            }
        }
    }

    if(FVID2_SOK == status)
    {
        /* Update modules Configuration based on this params */
        status = vcoreIspUpdateConfig(hIspObj, prms);
        /* The handle configuration is update, which will later be applied
            (when we receive a frame to be processed for this handle */
    }

    if(FVID2_SOK == status)
    {
        /* Copy Parameters in the instance Object */
        BspUtils_memcpy(
            &hIspObj->params,
            prms,
            sizeof(vpsissIspParams_t));
    }

    return (status);
}

/* Function to get the default/expert configuration from the hal and set
 * it in the register, typically this api will be called at the init/create
 * time to initialize all required/enabled modules. It configures
 * the modules only if the module is enabled in the modules flag */
int32_t vcoreIspSetDefaultConfig(vcoreIspHandleObj_t *hIspObj)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPEIF])
    {
        /* Get and Set the Default/Expert configuration for IPIPEIF */
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            VPS_HAL_ISS_IOCTL_IPIPEIF_GET_DEFAULTCFG,
            &hIspObj->ipipeifCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE]))
    {
        /* Get and Set the Default/Expert configuration for IPIPE */
        status = VpsHal_issipipeControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
            ISSHAL_IOCTL_IPIPE_GET_DEFAULTCFG,
            &hIspObj->ipipeCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_NSF3]))
    {
        /* Get and Set the Default/Expert configuration for NSF3 */
        status = VpsHal_issnsf3Control(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3],
            ISSHAL_IOCTL_NSF3_GET_DEFAULTCFG,
            &hIspObj->nsf3Cfg[0U],
            NULL);

        /* Set the default frame size */
        hIspObj->nsf3FrmSize[0U].width  = hIspObj->params.inFmt.width;
        hIspObj->nsf3FrmSize[0U].height = hIspObj->params.inFmt.height;
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_CNF]))
    {
        /* Get and Set the Default/Expert configuration for NSF3 */
        status = VpsHal_issnsf3Control(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF],
            ISSHAL_IOCTL_NSF3_GET_DEFAULTCFG,
            &hIspObj->nsf3Cfg[1U],
            NULL);

        if(TRUE == hIspObj->cnfPrms.enableCds)
        {
            hIspObj->nsf3FrmSize[1U].width  = hIspObj->params.inFmt.width/2;
            hIspObj->nsf3FrmSize[1U].height = hIspObj->params.inFmt.height/2;
        }
        else
        {
            hIspObj->nsf3FrmSize[1U].width  = hIspObj->params.inFmt.width;
            hIspObj->nsf3FrmSize[1U].height = hIspObj->params.inFmt.height;
        }
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_GLBCE]))
    {
        /* Get and Set the Default/Expert configuration for GLBCE */
        status = VpsHal_issglbceControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
            ISSHAL_IOCTL_GLBCE_GET_DEFAULTCFG,
            &hIspObj->glbceCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_ISIF]))
    {
        /* Get and Set the Default/Expert configuration for ISIF */
        status = VpsHal_issisifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
            ISSHAL_IOCTL_ISIF_GET_DEFAULTCFG,
            &hIspObj->isifCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_RSZ]))
    {
        /* Get and Set the Default/Expert configuration for Resizer */
        status = VpsHal_issrszControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
            ISSHAL_IOCTL_RSZ_GET_DEFAULTCFG,
            &hIspObj->rszCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_H3A]))
    {
        /* Get and Set the Default/Expert configuration for H3A */
        status = VpsHal_issh3aControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
            ISSHAL_IOCTL_H3A_GET_DEFAULTCFG,
            &hIspObj->h3aCfg,
            NULL);
    }

    if(FVID2_SOK == status)
    {
        status = vcoreIspSetConfig(hIspObj);
    }

    return (status);
}

int32_t vcoreIspRegisterIsr(
    vcoreIspHandleObj_t *hIspObj,
    uint32_t             irqNum,
    issemClientCbFxn     drvCbFxn,
    issemPriority_t      prio,
    Ptr                  arg)
{
    int32_t          status = FVID2_SOK;
    issemIspEvents_t event;
    issemClientCbFxn cbFxn;

    if(NULL == hIspObj)
    {
        status = FVID2_EBADARGS;
    }
    else /* Handle Object is not NULL */
    {
        if(VCORE_ISP_OPEN_MODE_CAPTURE == hIspObj->openMode)
        {
            event        = IEM_ISP_EVENT_ISIF_VDINT0;
            cbFxn        = &vcoreIspCaptEofHandler;
            hIspObj->arg = arg;
        }
        else
        {
            event = IEM_ISP_EVENT_RSZ_INT_DMA;
            cbFxn = &vcoreIspM2mEofHandler;

            /* For M2M, ISP layer calls Drivers' call back function and
               driver processes the callback function */
            hIspObj->cbFxn = drvCbFxn;
            hIspObj->arg   = arg;
        }

/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer
 * to object type
 * Name 'event'
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointers to different layer's handles are stored as void*.
 * In this perticular case, the event is uint32_t pointer, where as the event
 *  of ISP is defined as enum. We are casting enum to uint32_t, which should not
 *  be a problem.
 */
        gVpsCoreIspCommonObj.emEofIntrHndl = Vps_iemregister(
            (issemInstId_t)irqNum,
            IEM_EG_ISP0,
            (const uint32_t *)&event,
            1U,
            prio,
            cbFxn,
            hIspObj);

        if(NULL == gVpsCoreIspCommonObj.emEofIntrHndl)
        {
            status = FVID2_EFAIL;
        }
    }

    return (status);
}

int32_t vcoreIspUnRegisterIsr(vcoreIspHandleObj_t *hIspObj)
{
    int32_t status = FVID2_SOK;

    if(NULL == hIspObj)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        if(NULL != gVpsCoreIspCommonObj.emEofIntrHndl)
        {
            status = Vps_iemUnRegister(gVpsCoreIspCommonObj.emEofIntrHndl);
            gVpsCoreIspCommonObj.emEofIntrHndl = NULL;
        }

        if(FVID2_SOK == status)
        {
            hIspObj->cbFxn = NULL;
            hIspObj->arg   = NULL;
        }
    }

    return (status);
}

int32_t vcoreIspProgBuf(
    vcoreIspHandleObj_t *hIspObj,
    uint32_t             streamId,
    VpsCore_Frame       *frm)
{
    int32_t       status = FVID2_SOK;
    uint32_t      addrInIntLuma, addrInIntChroma;
    Fvid2_Format *fmt;

    /* Check for null pointer */
    if((NULL == hIspObj) || (NULL == frm) || (NULL == frm->addr[0U][0U]))
    {
        status = FVID2_EBADARGS;
    }

    /* For the YUV420 Output from Resizer, two addresses should be non null */
    if(FVID2_SOK == status)
    {
        if(((VPS_ISS_STREAM_ID_RSZ_A == streamId) &&
            (FVID2_DF_YUV420SP_UV ==
             hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.dataFormat)
            &&
            (NULL == frm->addr[0U][1U])) ||
           ((VPS_ISS_STREAM_ID_RSZ_B == streamId) &&
            (FVID2_DF_YUV420SP_UV ==
             hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.dataFormat)
            &&
            (NULL == frm->addr[0U][1U])))
        {
            status = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == status)
    {
        switch(streamId)
        {
            case VPS_ISS_STREAM_ID_RSZ_A:
                fmt = &hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt;

/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Resizer supports flipping the frames, this feature requires
 * offset to be added to the buffer address, so typecasting buffer address
 * to unsigned int to add offset. The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 * In this particular case, we check if the buffer address are aligned or not.
 */
                addrInIntLuma  = (uint32_t)frm->addr[0U][0U];
                addrInIntLuma +=
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][0U];
/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Resizer supports flipping the frames, this feature requires
 * offset to be added to the buffer address, so typecasting buffer address
 * to unsigned int to add offset. The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 * In this particular case, we check if the buffer address are aligned or not.
 */
                addrInIntChroma  = (uint32_t)frm->addr[0U][1U];
                addrInIntChroma +=
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][1U];

                status = VpsHal_issrszSetAddress(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
                    VPS_ISS_RSZ_SCALER_A,
/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Address offset in unsigned int is passed as a pointer to be set in the register.
 */
                    (Ptr)(addrInIntLuma),
/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Address offset in unsigned int is passed as a pointer to be set in the register.
 */
                    (Ptr)(addrInIntChroma),
                    fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX],
                    fmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX]);
                break;

            case VPS_ISS_STREAM_ID_RSZ_B:
                fmt = &hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt;

/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Resizer supports flipping the frames, this feature requires
 * offset to be added to the buffer address, so typecasting buffer address
 * to unsigned int to add offset. The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 * In this particular case, we check if the buffer address are aligned or not.
 */
                addrInIntLuma  = (uint32_t)frm->addr[0U][0U];
                addrInIntLuma +=
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][0U];
/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Resizer supports flipping the frames, this feature requires
 * offset to be added to the buffer address, so typecasting buffer address
 * to unsigned int to add offset. The address space is 32 bit and type
 * casting to integer will not result into any loss because of TI's compiler
 * treatment to integer.
 * In this particular case, we check if the buffer address are aligned or not.
 */
                addrInIntChroma  = (uint32_t)frm->addr[0U][1U];
                addrInIntChroma +=
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][1U];

                status = VpsHal_issrszSetAddress(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
                    VPS_ISS_RSZ_SCALER_B,
/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Address offset in unsigned int is passed as a pointer to be set in the register.
 */
                    (Ptr)(addrInIntLuma),
/* MISRA.CAST.PTR
 * Rule 11.4: Cast between a pointer to object type and a different pointer to
 * object type
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Address offset in unsigned int is passed as a pointer to be set in the register.
 */
                    (Ptr)(addrInIntChroma),
                    fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX],
                    fmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX]);
                break;

            case VPS_ISS_STREAM_ID_BSC:
            case VPS_ISS_STREAM_ID_BOXCAR:
            case VPS_ISS_STREAM_ID_HIST:
                status = FVID2_EINVALID_PARAMS;
                break;

            case VPS_ISS_STREAM_ID_AF:
                status = VpsHal_issh3aSetAfAddress(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
                    frm->addr[0u][0u],
                    NULL);
                break;

            case VPS_ISS_STREAM_ID_AEWB:
                status = VpsHal_issh3aSetAewbAddress(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
                    frm->addr[0u][0u],
                    NULL);
                break;

            case VPS_ISS_STREAM_ID_INPUT_N1:
                /* Configure the previous frame address in WDR Merge mode */
                /* Set the address as the command argument and pitch as
                 * the second argument*/
                status = VpsHal_issipipeifControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
                    VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_BUFFERS,
                    (Ptr) (&frm->addr[0U][0U]),
                    (Ptr) (&hIspObj->params.inFmtN_1.pitch
                           [FVID2_YUV_INT_ADDR_IDX]));
                break;

            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }

        if(FVID2_SOK == status)
        {
            hIspObj->curFrm[streamId] = frm;
        }
    }

    return (status);
}

int32_t vcoreIspGetIspBlankInfo(
    vcoreIspHandleObj_t     *hIspObj,
    isshalissBlankingInfo_t *blnkInfo,
    Ptr                      arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t modCnt;
    isshalissBlankingInfo_t tBlnkInfo;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));
    GT_assert(VpsIssCoreTrace, (NULL != blnkInfo));

    tBlnkInfo.procMode = blnkInfo->procMode;
    tBlnkInfo.hBlank   = 0U;
    tBlnkInfo.vBlank   = 0U;
    blnkInfo->hBlank   = 0U;
    blnkInfo->vBlank   = 0U;
    for(modCnt = 0U; modCnt < VPS_ISS_ISP_MAX_MODULE; modCnt++)
    {
        if(FALSE == hIspObj->isModReq[modCnt])
        {
            status = FVID2_EUNSUPPORTED_CMD;
        }

        /* Glbce is not used in the ISP path */
        if((VPS_ISS_ISP_MODULE_GLBCE == modCnt) &&
           (VPS_ISS_GLBCE_PATH_CAL == hIspObj->params.glbcePath))
        {
            status = FVID2_EUNSUPPORTED_CMD;
        }

        /* Nsf3 is not used in the ISP path */
        if((VPS_ISS_ISP_MODULE_NSF3 == modCnt) &&
           (VPS_ISS_NSF3_PATH_CAL == hIspObj->params.nsf3Path))
        {
            status = FVID2_EUNSUPPORTED_CMD;
        }

        if(FVID2_SOK == status)
        {
            switch(modCnt)
            {
                case VPS_ISS_ISP_MODULE_IPIPEIF:
                    status = VpsHal_issipipeifControl(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->ipipeifCfg);
                    break;

                case VPS_ISS_ISP_MODULE_NSF3:
                    status = VpsHal_issnsf3Control(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->nsf3Cfg[0U]);
                    break;

                case VPS_ISS_ISP_MODULE_GLBCE:
                    status = VpsHal_issglbceControl(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->glbceCfg);
                    break;

                case VPS_ISS_ISP_MODULE_ISIF:
                    status = VpsHal_issisifControl(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->isifCfg);
                    break;

                case VPS_ISS_ISP_MODULE_IPIPE:
                    status = VpsHal_issipipeControl(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->ipipeCfg);
                    break;

                case VPS_ISS_ISP_MODULE_RSZ:
                    status = VpsHal_issrszControl(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->rszCfg);
                    break;

                case VPS_ISS_ISP_MODULE_H3A:
                    status = VpsHal_issh3aControl(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->h3aCfg);
                    break;

                case VPS_ISS_ISP_MODULE_CNF:
                    status = VpsHal_issipipeControl(
                        hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF],
                        VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
                        &tBlnkInfo,
                        &hIspObj->nsf3Cfg[1U]);
                    break;
                default:
                    status = FVID2_EUNSUPPORTED_CMD;
                    break;
            }
        }
        else
        {
            /* We return success always, the blanking info is initialized
                to 0 */
            status = FVID2_SOK;
        }

        if(FVID2_SOK == status)
        {
            /* Get the max of h blank */
            if(tBlnkInfo.hBlank > blnkInfo->hBlank)
            {
                blnkInfo->hBlank = tBlnkInfo.hBlank;
            }

            if(ISSHAL_ISS_PROC_MODE_FREE_RUN == blnkInfo->procMode)
            {
                if(tBlnkInfo.vBlank > blnkInfo->vBlank)
                {
                    blnkInfo->vBlank = tBlnkInfo.vBlank;
                }
            }
            else
            {
                blnkInfo->vBlank += tBlnkInfo.vBlank;
            }
        }
    }

    return (FVID2_SOK);
}

int32_t vcoreIspGetGlbceNsf3BlankInfo(
    vcoreIspHandleObj_t     *hIspObj,
    isshalissBlankingInfo_t *blnkInfo,
    Ptr                      arg)
{
    int32_t status = FVID2_SOK;
    isshalissBlankingInfo_t tBlnkInfo;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));
    GT_assert(VpsIssCoreTrace, (NULL != blnkInfo));

    tBlnkInfo.procMode = blnkInfo->procMode;
    blnkInfo->hBlank   = 0U;
    blnkInfo->vBlank   = 0U;

    if(VPS_ISS_GLBCE_PATH_CAL == hIspObj->params.glbcePath)
    {
        /* Get the GLBCE blanking requirement and pass it to the upper layer */
        status = hIspObj->controlFxn[VPS_ISS_ISP_MODULE_GLBCE](
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
            VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
            &tBlnkInfo,
            NULL);
    }
    else if(VPS_ISS_NSF3_PATH_CAL == hIspObj->params.nsf3Path)
    {
        /* Get the GLBCE blanking requirement and pass it to the upper layer */
        status = hIspObj->controlFxn[VPS_ISS_ISP_MODULE_NSF3](
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3],
            VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO,
            &tBlnkInfo,
            &hIspObj->nsf3Cfg[0U]);
    }
    else
    {
        tBlnkInfo.hBlank = 0U;
        tBlnkInfo.vBlank = 0U;
    }

    if(FVID2_SOK == status)
    {
        blnkInfo->hBlank = tBlnkInfo.hBlank;
        blnkInfo->vBlank = tBlnkInfo.vBlank;
    }

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t vcoreIspUpdateConfig(
    vcoreIspHandleObj_t     *hIspObj,
    const vpsissIspParams_t *prms)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));
    GT_assert(VpsIssCoreTrace, (NULL != prms));

    /* Update the Configuration */
    if((TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_A]) &&
       (TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_B]))
    {
        hIspObj->rszCfg.numInst = 2U;
    }
    else
    {
        hIspObj->rszCfg.numInst = 1U;
    }
    /* Set the IPIPE enable Flag based on Resizer input */
    if(TRUE == prms->enableRszInputFromIpipeif)
    {
        hIspObj->rszCfg.srcCfg.inpSrc = ISSHAL_RSZ_INP_SRC_IPIPEIF;
    }
    else
    {
        hIspObj->rszCfg.srcCfg.inpSrc = ISSHAL_RSZ_INP_SRC_IPIPE;
    }

    /* Set the Default NSF3 Configuration */
    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_NSF3])
    {
        /* NSF3 bypass flag is selected either by default
           configuration, which is set at the create time or
           by SET_CNF_CONFIG ioctl */
        hIspObj->nsf3FrmSize[0U].width  = prms->inFmt.width;
        hIspObj->nsf3FrmSize[0U].height = prms->inFmt.height;
    }

    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_CNF])
    {
        hIspObj->cnfPrms.frameWidth  = prms->inFmt.width;
        hIspObj->cnfPrms.frameHeight = prms->inFmt.height;

        /* NSF3 bypass flag is selected either by default
           configuration, which is set at the create time or
           by SET_CNF_CONFIG ioctl */
        if(TRUE == hIspObj->cnfPrms.enableCds)
        {
            hIspObj->nsf3FrmSize[1U].width  = prms->inFmt.width/2;
            hIspObj->nsf3FrmSize[1U].height = prms->inFmt.height/2;
        }
        else
        {
            hIspObj->nsf3FrmSize[1U].width  = prms->inFmt.width;
            hIspObj->nsf3FrmSize[1U].height = prms->inFmt.height;
        }
        hIspObj->nsf3Cfg[1U].opMode = VPS_ISS_NSF3_OP_MODE_YUV420_CHROMA;
    }

    /* Set the Default IPIPE Configuration */
    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE])
    {
        hIspObj->ipipeCfg.srcCfg.inputDataFormat =
            (Fvid2_DataFormat) prms->inFmt.dataFormat;
        /* In case of YUV420 input, its supported for resizing only, in which
            case, we scale luma and chroma separately.
            The up stream modules will provide data in a 16 bit container.
            The down stream modules use required data, just pass through as 16
            bit data. */
        if(FVID2_DF_YUV420SP_UV == prms->inFmt.dataFormat)
        {
            hIspObj->ipipeCfg.srcCfg.inputDataFormat = FVID2_DF_YUV422I_UYVY;
        }

        hIspObj->ipipeCfg.srcCfg.wrtEnable = prms->useWen;

        /* TODO: Assuming Chroma position is always Centred,
         *       provide the global interface for this */
        hIspObj->ipipeCfg.srcCfg.chromaPos = FVID2_CHROMA_POS_CENTERED;

        hIspObj->ipipeCfg.srcCfg.procWin.cropStartX = 0U;
        hIspObj->ipipeCfg.srcCfg.procWin.cropStartY = 0U;
        hIspObj->ipipeCfg.srcCfg.procWin.cropWidth  = prms->inFmt.width;
        hIspObj->ipipeCfg.srcCfg.procWin.cropHeight = prms->inFmt.height;

        hIspObj->ipipeCfg.srcCfg.dataPath = VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422;
        if(((int32_t) TRUE == Fvid2_isDataFmtYuv422(prms->inFmt.dataFormat)) ||
           (FVID2_DF_YUV420SP_UV == prms->inFmt.dataFormat))
        {
            /* ISS_TODO This path should be chosen for YUV422 resizing also */
            hIspObj->ipipeCfg.srcCfg.dataPath =
                VPS_ISS_IPIPE_DATA_PATH_YUV422_YUV422;
        }
        hIspObj->ipipeCfg.moduleId = ISSHAL_IPIPE_MODULE_SRC_CFG;
    }

    /* Set the Default Resizer Configuration */
    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_RSZ])
    {
        if((FALSE == prms->enableRszInputFromIpipeif) &&
           (VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422 ==
            hIspObj->ipipeCfg.srcCfg.dataPath))
        {
            hIspObj->rszCfg.srcCfg.inputDataFormat = FVID2_DF_YUV422I_UYVY;
        }
        else if((int32_t) TRUE == Fvid2_isDataFmtBayer(prms->inFmt.dataFormat))
        {
            hIspObj->rszCfg.srcCfg.inputDataFormat = FVID2_DF_BAYER_RAW;
        }
        else
        {
            if(FVID2_DF_YUV420SP_UV == prms->inFmt.dataFormat)
            {
                hIspObj->rszCfg.srcCfg.inputDataFormat =
                    (Fvid2_DataFormat) prms->inFmt.dataFormat;
                /* Configuring for Luma pass, Luma will be available at LS byte
                    require to move it MS byte of 16 bit interface */
                hIspObj->rszCfg.srcCfg.rszLuma = (UInt32) TRUE;
            }
            else
            {
                hIspObj->rszCfg.srcCfg.inputDataFormat = FVID2_DF_YUV422I_UYVY;
            }
        }
        hIspObj->rszCfg.srcCfg.wrtEnable      = prms->useWen;
        hIspObj->rszCfg.srcCfg.lumaClip.min   = 0x0U;
        hIspObj->rszCfg.srcCfg.lumaClip.max   = 0xFFU;
        hIspObj->rszCfg.srcCfg.chromaClip.min = 0x0U;
        hIspObj->rszCfg.srcCfg.chromaClip.max = 0xFFU;
        hIspObj->rszCfg.srcCfg.chromaPos      = FVID2_CHROMA_POS_CENTERED;

        hIspObj->rszCfg.srcCfg.procWin.cropStartX = 0U;
        hIspObj->rszCfg.srcCfg.procWin.cropStartY = 0U;
        hIspObj->rszCfg.srcCfg.procWin.cropWidth  = prms->inFmt.width;
        hIspObj->rszCfg.srcCfg.procWin.cropHeight = prms->inFmt.height;

        /* High threshold should be set to width - 30 value */
        hIspObj->rszCfg.srcCfg.thrHigh = prms->inFmt.width -
                                         VCORE_ISS_RSZ_HIGH_THRESHOLD_OFFSET;
        /* Low threshold should be set half of high threshold */
        hIspObj->rszCfg.srcCfg.thrLow = hIspObj->rszCfg.srcCfg.thrHigh / 2U;

        if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_A])
        {
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].enable =
                (UInt32) TRUE;

            /* Setting output format same as input format so the
               resizer set config does not return any error.
               This makes resizer set config ioclt must, upper layer must call
               resizer set config ioctl to configure resizer for the
               required output format and frame size */
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.dataFormat =
                hIspObj->rszCfg.srcCfg.inputDataFormat;
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.width =
                prms->inFmt.width;
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.height =
                prms->inFmt.height;

            if((int32_t) TRUE == Fvid2_isDataFmtBayer(
                   hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.
                   dataFormat))
            {
                hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.
                dataFormat = FVID2_DF_BAYER_RAW;
            }
        }
        if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_B])
        {
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].enable =
                (UInt32) TRUE;

            /* Setting output format same as input format so the
               resizer set config does not return any error.
               This makes resizer set config ioclt must, upper layer must call
               resizer set config ioctl to configure resizer for the
               required output format and frame size */
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.dataFormat =
                hIspObj->rszCfg.srcCfg.inputDataFormat;
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.width =
                prms->inFmt.width;
            hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.height =
                prms->inFmt.height;

            if((int32_t) TRUE == Fvid2_isDataFmtBayer(
                   hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.
                   dataFormat))
            {
                hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.
                dataFormat = FVID2_DF_BAYER_RAW;
            }
        }

        /* Resizer SetConfig must be called using ioctl as
         * setting parameters here may cause it to fail
         * because of the default parameters of the resizer
         * This makes resizer ioctl a must ioctl */
    }

    /* Set ISIF Default Configuration */
    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_ISIF])
    {
        hIspObj->isifCfg.srcCfg.isHdVdOut = (UInt32) FALSE;
        /* Since CAL provides HD_VD */
        hIspObj->isifCfg.srcCfg.isFidOut = (UInt32) FALSE;
        /* Non Interlaced Input */
        hIspObj->isifCfg.srcCfg.isInDataInvt = (UInt32) FALSE;
        hIspObj->isifCfg.srcCfg.hdPol        = prms->hdPol;
        hIspObj->isifCfg.srcCfg.vdPol        = prms->vdPol;
        hIspObj->isifCfg.srcCfg.inDataFormat =
            (Fvid2_DataFormat) prms->inFmt.dataFormat;
        /* vidIfWidth: Used only for YUV input */
        hIspObj->isifCfg.srcCfg.vidIfWidth = FVID2_VIFW_8BIT;
        hIspObj->isifCfg.srcCfg.ycInSwap   = (UInt32) FALSE;

        if((int32_t) TRUE == Fvid2_isDataFmtYuv422I(prms->inFmt.dataFormat))
        {
            hIspObj->isifCfg.srcCfg.vidIfWidth = FVID2_VIFW_16BIT;
            if(FVID2_DF_YUV422I_YUYV == prms->inFmt.dataFormat)
            {
                hIspObj->isifCfg.srcCfg.ycInSwap = (UInt32) TRUE;
            }
        }

        /* YUV420 input is primarily supported for resizing only operation.
            Resizing is done in 2 step process, luma in one step and chroma
            in other.
            Assume luma to be processed first.
            The up stream modules provide luma in LSByte.
                the down stream modules expect luma on MSByte, so swap it. */
        if(FVID2_DF_YUV420SP_UV == prms->inFmt.dataFormat)
        {
            hIspObj->isifCfg.srcCfg.vidIfWidth = FVID2_VIFW_16BIT;
            hIspObj->isifCfg.srcCfg.ycInSwap   = (UInt32) TRUE;
        }

        hIspObj->isifCfg.srcCfg.hdWidth       = prms->inFmt.width;
        hIspObj->isifCfg.srcCfg.vdWidth       = prms->inFmt.height;
        hIspObj->isifCfg.srcCfg.pixelsPerLine = prms->inFmt.width;
        hIspObj->isifCfg.srcCfg.linesPerFrame = prms->inFmt.height;

        switch(prms->inFmt.bpp)
        {
            case FVID2_BPP_BITS8:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT7;
                break;
            case FVID2_BPP_BITS9:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT8;
                break;
            case FVID2_BPP_BITS10:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT9;
                break;
            case FVID2_BPP_BITS11:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT10;
                break;
            case FVID2_BPP_BITS12:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT11;
                break;
            case FVID2_BPP_BITS13:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT12;
                break;
            case FVID2_BPP_BITS14:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT13;
                break;
            case FVID2_BPP_BITS15:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT14;
                break;
            case FVID2_BPP_BITS16:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT15;
                break;
            default:
                hIspObj->isifCfg.srcCfg.msbPos =
                    ISSHAL_ISIF_INPUT_MSB_POS_BIT10;
                break;
        }

        hIspObj->isifCfg.srcCfg.cfaPattern = ISSHAL_ISIF_CFG_PATTERN_MOSAIC;
        hIspObj->isifCfg.moduleId          = ISSHAL_ISIF_MODULE_SRC_CFG;
    }

    /* Configure H3A isModuleReq as per the new params */
    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_H3A])
    {
        /* Since IPIPE Removes the blanking area, it should be
         * removed in the H3A also */
        /* ISS_TODO - If these values are changing, ensure to update the
            function vcoreIssM2mSetSrcSize () to reconfigure H3A with updated
            start position */
        hIspObj->h3aCfg.pos.startX = 0U;
        hIspObj->h3aCfg.pos.startY = 0U;
    }

    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPEIF])
    {
        /* IPIPEIF receives complete frame including blanking
         * and processes it */

        /* ppln and lpfr are used to configure the complete frame size */
        hIspObj->ipipeifCfg.ipFrameCfg.ppln = 0U;
        hIspObj->ipipeifCfg.ipFrameCfg.lpfr = 0U;
        /* HNUM and VNUM are used for specifying actual input frame size */
        hIspObj->ipipeifCfg.ipFrameCfg.hnum = prms->inFmt.width;
        hIspObj->ipipeifCfg.ipFrameCfg.vnum = prms->inFmt.height;

        /* Enable Input Interface if required */
        if(TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_INPUT_N1])
        {
            status = VpsHal_issipipeifControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
                (uint32_t)VPS_HAL_ISS_IOCTL_IPIPEIF_ENABLE_INPUT_IF,
                NULL,
                NULL);
        }
    }

    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_GLBCE])
    {
        hIspObj->glbceCfg.width  = prms->inFmt.width;
        hIspObj->glbceCfg.height = prms->inFmt.height;
    }

    return (status);
}

static int32_t vcoreIspSetConfig(vcoreIspHandleObj_t *hIspObj)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPEIF])
    {
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            VPS_HAL_ISS_IOCTL_IPIPEIF_SETCFG,
            &hIspObj->ipipeifCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE]))
    {
        status = VpsHal_issipipeSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
            &hIspObj->ipipeCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_NSF3]))
    {
        /* Set the Frame size first */
        status = VpsHal_issnsf3SetFrameSize(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3],
            &hIspObj->nsf3FrmSize[0U],
            NULL);

        status = VpsHal_issnsf3SetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3],
            &hIspObj->nsf3Cfg[0U],
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_CNF]))
    {
        /* Set the Frame size first */
        status = VpsHal_issnsf3SetFrameSize(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF],
            &hIspObj->nsf3FrmSize[1U],
            NULL);

        hIspObj->nsf3Cfg[1U].opMode = VPS_ISS_NSF3_OP_MODE_YUV420_CHROMA;
        status = VpsHal_issnsf3SetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_CNF],
            &hIspObj->nsf3Cfg[1U],
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_GLBCE]))
    {
        status = VpsHal_issglbceSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
            &hIspObj->glbceCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_ISIF]))
    {
        status = VpsHal_issisifSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
            &hIspObj->isifCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_RSZ]))
    {
        status = VpsHal_issrszSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
            &hIspObj->rszCfg,
            NULL);
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_H3A]))
    {
        status = VpsHal_issh3aSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
            &hIspObj->h3aCfg,
            NULL);
    }

    return (status);
}

static int32_t vcoreIspCheckParams(
    const vcoreIspHandleObj_t *hIspObj,
    const vpsissIspParams_t   *prms)
{
    int32_t status = FVID2_SOK;

    if((NULL == hIspObj) || (NULL == prms))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        /* Only Bayer, YUV422 & YUV420 SP are supported */
        if((((int32_t) FALSE == Fvid2_isDataFmtBayer(prms->inFmt.dataFormat))
            &&
            ((int32_t) FALSE == Fvid2_isDataFmtYuv422I(prms->inFmt.dataFormat)))
           &&
           (FVID2_DF_YUV420SP_UV != prms->inFmt.dataFormat))
        {
            status = FVID2_EINVALID_PARAMS;
        }

        /* Two options for YUV mode */
        if((int32_t) TRUE == Fvid2_isDataFmtYuv422I(prms->inFmt.dataFormat))
        {
            if((FVID2_DF_YUV422I_UYVY != prms->inFmt.dataFormat) &&
               (FVID2_DF_YUV422I_YUYV != prms->inFmt.dataFormat))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }

        /* When in YUV420 input mode, we support only resizing, other
            features such as NSF3, GLBCE, DPC, CNF is not supported */
        if(FVID2_DF_YUV420SP_UV == prms->inFmt.dataFormat)
        {
            if(VPS_ISS_GLBCE_PATH_DISABLED != prms->glbcePath)
            {
                status = FVID2_EINVALID_PARAMS;
            }
            if(VPS_ISS_NSF3_PATH_DISABLED != prms->nsf3Path)
            {
                status = FVID2_EINVALID_PARAMS;
            }
            if(FALSE != prms->enableDpcPreNsf3)
            {
                status = FVID2_EINVALID_PARAMS;
            }
            if(FALSE != prms->enableCnf)
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }

        /* Modules can not be enabled if they are not enabled at create time */
        if(((VPS_ISS_NSF3_PATH_CAL == prms->nsf3Path) ||
            (VPS_ISS_NSF3_PATH_ISP == prms->nsf3Path)) &&
           (FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_NSF3]))
        {
            status = FVID2_EINVALID_PARAMS;
        }
        if((VPS_ISS_GLBCE_PATH_DISABLED != hIspObj->params.glbcePath) &&
           (FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_GLBCE]))
        {
            status = FVID2_EINVALID_PARAMS;
        }

        if((TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_AF]) ||
           (TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_AEWB]))
        {
            /* H3A and ISIF both should be enabled to get the AE/AEWB data */
            if((FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_H3A]) ||
               (FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_ISIF]))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }

        /* IPIPE should be available in order to enable DPC */
        if((TRUE == prms->enableDpcPreNsf3) &&
           (FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE]))
        {
            status = FVID2_EINVALID_PARAMS;
        }

        /* IPIPE should be enabled for resizer is receiving data from ipipe */
        if((FALSE == prms->enableRszInputFromIpipeif) &&
           (FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE]))
        {
            status = FVID2_EINVALID_PARAMS;
        }

        /* For Resizer output, Resizer module should be enabled */
        if((TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_A]) ||
           (TRUE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_B]))
        {
            if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_RSZ])
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }

        /* At least one of the resizer output must be enabled */
        if((FALSE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_A]) &&
           (FALSE == prms->enableStreams[VPS_ISS_STREAM_ID_RSZ_B]))
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

void vcoreIspErrEvtHandler(const UInt32 *event,
                           UInt32        numEvents,
                           Ptr           arg)
{
    /* Print Error Event and assert */
}

void vcoreIspCaptEofHandler(const UInt32 *event,
                            UInt32        numEvents,
                            Ptr           arg)
{
    int32_t  status;
    uint32_t strmCnt;
    vcoreIspHandleObj_t *hIspObj;
    VpsCore_Frame       *newFrm;

    GT_assert(VpsIssCoreTrace, (NULL != arg));
    GT_assert(VpsIssCoreTrace, (1U == numEvents));

    hIspObj = (vcoreIspHandleObj_t *)arg;

    for(strmCnt = VPS_ISS_STREAM_ID_RSZ_A; strmCnt < VPS_ISS_STREAM_ID_MAX;
        strmCnt++)
    {
        /* Call callback only for enabled streams */
        if(TRUE == hIspObj->params.enableStreams[strmCnt])
        {
            GT_assert(VpsIssCalCoreTrace,
                      (0xFFFFFFFFU != hIspObj->captStreamMap[strmCnt]));

            /* Mark the current frame as done and release it to upper layer
               for all enabled streams */
            if(NULL != hIspObj->openPrms.frmDoneCb)
            {
                hIspObj->openPrms.frmDoneCb(
                    hIspObj->openPrms.drvData,
                    hIspObj->curFrm[strmCnt]);
                hIspObj->curFrm[strmCnt] = NULL;
            }

            /* Get the new frame from upper layer and program it,
               reqFrmCb must not be null */
            if(NULL != hIspObj->openPrms.reqFrmCb)
            {
                newFrm = hIspObj->openPrms.reqFrmCb(
                    hIspObj->openPrms.drvData,
                    hIspObj->captStreamMap[strmCnt],
                    0x0);
                if(NULL != newFrm)
                {
                    status = vcoreIspProgBuf(
                        hIspObj,
                        strmCnt,
                        newFrm);

                    GT_assert(VpsIssCalCoreTrace, (FVID2_SOK == status));
                }
                else
                {
                    /* The driver should ensure that this condition
                     *  should not occur. */
                    GT_assert(VpsIssCalCoreTrace, FALSE);
                }
            }
        }
    }
}

void vcoreIspM2mEofHandler(const UInt32 *event,
                           UInt32        numEvents,
                           Ptr           arg)
{
    vcoreIspHandleObj_t *hIspObj;

    GT_assert(VpsIssCoreTrace, (NULL != arg));
    GT_assert(VpsIssCoreTrace, (1U == numEvents));

    hIspObj = (vcoreIspHandleObj_t *)arg;

    if(NULL != hIspObj->cbFxn)
    {
        hIspObj->cbFxn(event, numEvents, hIspObj->arg);
    }
}

/* Function to allocate Handle Object from the pool of objects */
static vcoreIspHandleObj_t *vcoreIspAllocHndlObj(void)
{
    uint32_t cnt;
    vcoreIspHandleObj_t *hIspObj;

    hIspObj = NULL;
    for(cnt = 0U; cnt < VCORE_MAX_ISP_OBJECTS; cnt++)
    {
        if(FALSE == gVpsCoreIspCommonObj.handleObj[cnt].isAllocated)
        {
            /* Clean out the handle object */
            BspUtils_memset(&gVpsCoreIspCommonObj.handleObj[cnt],
                            0x0,
                            sizeof(vcoreIspHandleObj_t));

            gVpsCoreIspCommonObj.handleObj[cnt].isAllocated = (UInt32) TRUE;
            hIspObj = &gVpsCoreIspCommonObj.handleObj[cnt];
            break;
        }
    }

    if(NULL != hIspObj)
    {
        /* Initialize the function pointer for start/stop api of the
         * ISP sub-modules
         * There is no start function for H3A, it has two sub-modules AF and
         * AEW. these sub-modules will be started independently in start/stop
         * Api, based on their enabled status */
        hIspObj->startModuleFxn[VPS_ISS_ISP_MODULE_IPIPEIF] =
            &VpsHal_issipipeifStart;
        hIspObj->startModuleFxn[VPS_ISS_ISP_MODULE_NSF3] =
            &VpsHal_issnsf3Start;
        hIspObj->startModuleFxn[VPS_ISS_ISP_MODULE_GLBCE] =
            &VpsHal_issglbceStart;
        hIspObj->startModuleFxn[VPS_ISS_ISP_MODULE_ISIF] =
            &VpsHal_issisifStart;
        hIspObj->startModuleFxn[VPS_ISS_ISP_MODULE_IPIPE] =
            &VpsHal_issipipeStart;
        hIspObj->startModuleFxn[VPS_ISS_ISP_MODULE_RSZ] =
            &VpsHal_issrszStart;
        hIspObj->startModuleFxn[VPS_ISS_ISP_MODULE_CNF] =
            &VpsHal_issnsf3Start;

        hIspObj->stopModuleFxn[VPS_ISS_ISP_MODULE_IPIPEIF] =
            &VpsHal_issipipeifStop;
        hIspObj->stopModuleFxn[VPS_ISS_ISP_MODULE_NSF3] =
            &VpsHal_issnsf3Stop;
        hIspObj->stopModuleFxn[VPS_ISS_ISP_MODULE_GLBCE] =
            &VpsHal_issglbceStop;
        hIspObj->stopModuleFxn[VPS_ISS_ISP_MODULE_ISIF] =
            &VpsHal_issisifStop;
        hIspObj->stopModuleFxn[VPS_ISS_ISP_MODULE_IPIPE] =
            &VpsHal_issipipeStop;
        hIspObj->stopModuleFxn[VPS_ISS_ISP_MODULE_RSZ] =
            &VpsHal_issrszStop;
        hIspObj->stopModuleFxn[VPS_ISS_ISP_MODULE_CNF] =
            &VpsHal_issnsf3Stop;

        hIspObj->controlFxn[VPS_ISS_ISP_MODULE_IPIPEIF] =
            &VpsHal_issipipeifControl;
        hIspObj->controlFxn[VPS_ISS_ISP_MODULE_NSF3] =
            &VpsHal_issnsf3Control;
        hIspObj->controlFxn[VPS_ISS_ISP_MODULE_GLBCE] =
            &VpsHal_issglbceControl;
        hIspObj->controlFxn[VPS_ISS_ISP_MODULE_ISIF] =
            &VpsHal_issisifControl;
        hIspObj->controlFxn[VPS_ISS_ISP_MODULE_IPIPE] =
            &VpsHal_issipipeControl;
        hIspObj->controlFxn[VPS_ISS_ISP_MODULE_RSZ] =
            &VpsHal_issrszControl;
        hIspObj->controlFxn[VPS_ISS_ISP_MODULE_CNF] =
            &VpsHal_issnsf3Control;
    }

    return (hIspObj);
}

/* Function to allocate Handle Object */
static int32_t vcoreIspDeAllocHObj(const vcoreIspHandleObj_t *hIspObj)
{
    int32_t  status = FVID2_EBADARGS;
    uint32_t cnt;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    for(cnt = 0U; cnt < VCORE_MAX_ISP_OBJECTS; cnt++)
    {
        if(hIspObj == &gVpsCoreIspCommonObj.handleObj[cnt])
        {
            gVpsCoreIspCommonObj.handleObj[cnt].isAllocated = (UInt32) FALSE;
            status = FVID2_SOK;
            break;
        }
    }

    return (status);
}

static void vcoreIspSetDefault(
    vcoreIspHandleObj_t *hIspObj,
    vpsissIspParams_t   *prms)
{
    uint32_t strmCnt;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));
    GT_assert(VpsIssCoreTrace, (NULL != prms));

    prms->useWen           = (UInt32) FALSE;
    prms->hdPol            = FVID2_POL_HIGH;
    prms->vdPol            = FVID2_POL_HIGH;
    prms->inFmt.width      = 720U;
    prms->inFmt.height     = 480U;
    prms->inFmt.dataFormat = FVID2_DF_BAYER_RGGB;
    prms->inFmt.bpp        = FVID2_BPP_BITS12;

    prms->inFmt.pitch[0U] = prms->inFmt.width * 2U;
    prms->inFmt.pitch[1U] = prms->inFmt.width * 2U;
    prms->inFmt.pitch[2U] = prms->inFmt.width * 2U;

    prms->inFmtN_1 = prms->inFmt;

    prms->enableWdrMerge = (UInt32) FALSE;
    prms->enableDfs      = (UInt32) FALSE;
    prms->glbcePath      = VPS_ISS_GLBCE_PATH_DISABLED;
    prms->nsf3Path       = VPS_ISS_NSF3_PATH_DISABLED;
    prms->enableDpcPreNsf3          = (UInt32) FALSE;
    prms->enableCnf                 = (UInt32) FALSE;
    prms->enableRszInputFromIpipeif = (UInt32) FALSE;

    for(strmCnt = 0U; strmCnt < VPS_ISS_STREAM_ID_MAX; strmCnt++)
    {
        prms->enableStreams[strmCnt] = (UInt32) FALSE;
    }
    /* Initialize VP1 Configuration */
    hIspObj->vp1Cfg.inpDataFormat      = ISSHAL_NSF3_INP_DATA_RAW;
    hIspObj->vp1Cfg.hdPol              = FVID2_POL_HIGH;
    hIspObj->vp1Cfg.vdPol              = FVID2_POL_HIGH;
    hIspObj->vp1Cfg.isInvertData       = (UInt32) FALSE;
    hIspObj->vp1Cfg.inMsbPos           = VPS_ISS_INPUT_MSB_POS_BIT11;
    hIspObj->vp1Cfg.bayerDataFormat    = FVID2_DF_BAYER_RGGB;
    hIspObj->vp1Cfg.enableDelay        = (UInt32) FALSE;
    hIspObj->vp1Cfg.cropWin.cropStartX = 0U;
    hIspObj->vp1Cfg.cropWin.cropStartY = 0U;
    hIspObj->vp1Cfg.cropWin.cropWidth  = 720U;
    hIspObj->vp1Cfg.cropWin.cropHeight = 480U;
    hIspObj->vp1Cfg.enableYcSwap       = (UInt32) FALSE;
    hIspObj->vp1Cfg.enableLumaOddPos   = (UInt32) FALSE;

    /* Initialize VP2 Configuration */
    hIspObj->vp2Cfg.pos.startX = 0x0U;
    hIspObj->vp2Cfg.pos.startY = 0x0U;
    hIspObj->vp2Cfg.horzDelay  = 0x3BU;             /* Reset Value */
    hIspObj->vp2Cfg.vertDelay  = 0x01U;             /* Reset Value */
    hIspObj->vp2Cfg.inMsbPos   = VPS_ISS_INPUT_MSB_POS_BIT15;
    hIspObj->vp2Cfg.outMsbPos  = VPS_ISS_OUTPUT_MSB_POS_BIT16;

    hIspObj->cnfPrms.instId      = ISSHAL_ISS_CNF_A;
    hIspObj->cnfPrms.enable      = (UInt32) FALSE;
    hIspObj->cnfPrms.enableCds   = (UInt32) FALSE;
    hIspObj->cnfPrms.frameWidth  = VPSCORE_ISS_M2M_DEF_FRAME_WIDTH;
    hIspObj->cnfPrms.frameHeight = VPSCORE_ISS_M2M_DEF_FRAME_HEIGHT;
}

/* H3A Set Config */
int32_t IspH3aSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissH3aCtrl_t     *h3aCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_H3A])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if((NULL == h3aCtrl) ||
       ((VPS_ISS_H3A_MODULE_AF == h3aCtrl->module) &&
        (NULL == h3aCtrl->afCfg)) ||
       ((VPS_ISS_H3A_MODULE_AEWB == h3aCtrl->module) &&
        (NULL == h3aCtrl->aewbCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_H3A_MODULE_AF == h3aCtrl->module)
        {
            status = VpsHal_issh3aControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
                ISSHAL_IOCTL_H3A_SET_AFCFG,
                h3aCtrl->afCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->h3aCfg.afCfg,
                    h3aCtrl->afCfg,
                    sizeof(hIspObj->h3aCfg.afCfg));
            }
        }
        else
        {
            /* It has to be VPS_ISS_H3A_MODULE_AEWB, as we have checked for
                all valid possibilities above */
            status = VpsHal_issh3aControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_H3A],
                ISSHAL_IOCTL_H3A_SET_AEWBCFG,
                h3aCtrl->aewbCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->h3aCfg.aewbCfg,
                    h3aCtrl->aewbCfg,
                    sizeof(hIspObj->h3aCfg.aewbCfg));
            }
        }
    }

    return (status);
}

/* H3A Get Config */
int32_t IspH3aGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissH3aCtrl_t           *h3aCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_H3A])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if((NULL == h3aCtrl) ||
       ((VPS_ISS_H3A_MODULE_AF == h3aCtrl->module) &&
        (NULL == h3aCtrl->afCfg)) ||
       ((VPS_ISS_H3A_MODULE_AEWB == h3aCtrl->module) &&
        (NULL == h3aCtrl->aewbCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_H3A_MODULE_AF == h3aCtrl->module)
        {
            BspUtils_memcpy(
                h3aCtrl->afCfg,
                &hIspObj->h3aCfg.afCfg,
                sizeof(hIspObj->h3aCfg.afCfg));
        }
        else
        {
            /* It has to be VPS_ISS_H3A_MODULE_AEWB, as we have checked for
                all valid possibilities above */
            BspUtils_memcpy(
                h3aCtrl->aewbCfg,
                &hIspObj->h3aCfg.aewbCfg,
                sizeof(hIspObj->h3aCfg.aewbCfg));
        }
    }

    return (status);
}

/* ISIF Set Config */
int32_t IspIsifSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissIsifCtrl_t    *isifCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_ISIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if((NULL == isifCtrl) ||
       ((VPS_ISS_ISIF_MODULE_WB == isifCtrl->module) &&
        (NULL == isifCtrl->wbCfg)) ||
       ((VPS_ISS_ISIF_MODULE_VDFC == isifCtrl->module) &&
        (NULL == isifCtrl->vfdcCfg)) ||
       ((VPS_ISS_ISIF_MODULE_BLACK_CLAMP == isifCtrl->module) &&
        (NULL == isifCtrl->blkClampCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_ISIF_MODULE_WB == isifCtrl->module)
        {
            status = VpsHal_issisifControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
                ISSHAL_IOCTL_ISIF_SET_WBCFG,
                isifCtrl->wbCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->isifCfg.wbCfg,
                    isifCtrl->wbCfg,
                    sizeof(hIspObj->isifCfg.wbCfg));
            }
        }
        if(VPS_ISS_ISIF_MODULE_VDFC == isifCtrl->module)
        {
            status = checkIsifVfdcCfg(&hIspObj->params, isifCtrl->vfdcCfg);
            if(FVID2_SOK == status)
            {
                status = VpsHal_issisifControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
                    ISSHAL_IOCTL_ISIF_SET_VFDC_CFG,
                    isifCtrl->vfdcCfg,
                    NULL);

                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->isifCfg.vfdcCfg,
                        isifCtrl->vfdcCfg,
                        sizeof(hIspObj->isifCfg.vfdcCfg));
                }
            }
        }
        if(VPS_ISS_ISIF_MODULE_BLACK_CLAMP == isifCtrl->module)
        {
            status = VpsHal_issisifControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
                ISSHAL_IOCTL_ISIF_SET_BLACK_CLAMP_CFG,
                isifCtrl->blkClampCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->isifCfg.blkClampCfg,
                    isifCtrl->blkClampCfg,
                    sizeof(hIspObj->isifCfg.blkClampCfg));
            }
        }
        if(VPS_ISS_ISIF_MODULE_2D_LSC == isifCtrl->module)
        {
            status = VpsHal_issisifControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
                ISSHAL_IOCTL_ISIF_SET_2D_LSC_CFG,
                isifCtrl->lscCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->isifCfg.lscCfg,
                    isifCtrl->lscCfg,
                    sizeof(vpsissIsif2DLscConfig_t));
            }
        }
    }
    return (status);
}

/* ISIF Get Config */
int32_t IspIsifGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissIsifCtrl_t          *isifCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_ISIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if((NULL == isifCtrl) ||
       ((VPS_ISS_ISIF_MODULE_WB == isifCtrl->module) &&
        (NULL == isifCtrl->wbCfg)) ||
       ((VPS_ISS_ISIF_MODULE_VDFC == isifCtrl->module) &&
        (NULL == isifCtrl->vfdcCfg)) ||
       ((VPS_ISS_ISIF_MODULE_BLACK_CLAMP == isifCtrl->module) &&
        (NULL == isifCtrl->blkClampCfg)) ||
       ((VPS_ISS_ISIF_MODULE_2D_LSC == isifCtrl->module) &&
        (NULL == isifCtrl->lscCfg))
       )
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_ISIF_MODULE_WB == isifCtrl->module)
        {
            BspUtils_memcpy(
                isifCtrl->wbCfg,
                &hIspObj->isifCfg.wbCfg,
                sizeof(isifCtrl->wbCfg));
        }
        if(VPS_ISS_ISIF_MODULE_VDFC == isifCtrl->module)
        {
            BspUtils_memcpy(
                isifCtrl->vfdcCfg,
                &hIspObj->isifCfg.vfdcCfg,
                sizeof(hIspObj->isifCfg.vfdcCfg));
        }
        if(VPS_ISS_ISIF_MODULE_BLACK_CLAMP == isifCtrl->module)
        {
            BspUtils_memcpy(
                isifCtrl->blkClampCfg,
                &hIspObj->isifCfg.blkClampCfg,
                sizeof(hIspObj->isifCfg.blkClampCfg));
        }
        if(VPS_ISS_ISIF_MODULE_2D_LSC == isifCtrl->module)
        {
            BspUtils_memcpy(
                isifCtrl->lscCfg,
                &hIspObj->isifCfg.lscCfg,
                sizeof(vpsissIsif2DLscConfig_t));
        }
    }

    return (status);
}

/* IPIPE Set Config */
int32_t IspIpipeSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissIpipeCtrl_t   *ipipeCtrl)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if((NULL == ipipeCtrl) ||
       ((VPS_ISS_IPIPE_MODULE_INPUT == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->inCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_CFA == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->cfaCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_WB == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->wbCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_RGB2RGB1 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->rgb2RgbCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_RGB2RGB2 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->rgb2RgbCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_RGB2YUV == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->rgb2YuvCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_YUV444_YUV422 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->yuvPhsCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_DPC_LUT == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->dpcLut)) ||
       ((VPS_ISS_IPIPE_MODULE_DPC_OTF == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->dpcOtf)) ||
       ((VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->gammaCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->eeCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_GIC == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->gicCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_NF1 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->nf1Cfg)) ||
       ((VPS_ISS_IPIPE_MODULE_NF2 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->nf2Cfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        switch(ipipeCtrl->module)
        {
            /* Case is to set Input Configuration of IPIPE */
            case VPS_ISS_IPIPE_MODULE_INPUT:

                hIspObj->ipipeCfg.srcCfg.dataPath = ipipeCtrl->inCfg->dataPath;
                BspUtils_memcpy(&hIspObj->ipipeCfg.srcCfg.procWin,
                                &ipipeCtrl->inCfg->procWin,
                                sizeof(hIspObj->ipipeCfg.srcCfg.procWin));
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_SRCCFG,
                    &hIspObj->ipipeCfg.srcCfg,
                    NULL);
                break;

            /* Case is to set CFA Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_CFA:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_CFACFG,
                    ipipeCtrl->cfaCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.cfaCfg,
                        ipipeCtrl->cfaCfg,
                        sizeof(hIspObj->ipipeCfg.cfaCfg));
                }
                break;

            /* Case is to set White Balance Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_WB:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_WBCFG,
                    ipipeCtrl->wbCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.wbCfg,
                        ipipeCtrl->wbCfg,
                        sizeof(hIspObj->ipipeCfg.wbCfg));
                }
                break;

            /* Case is to set RGB2RGB 1 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB1:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_RGB2RGB1CFG,
                    ipipeCtrl->rgb2RgbCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.rgb2Rgb1,
                        ipipeCtrl->rgb2RgbCfg,
                        sizeof(hIspObj->ipipeCfg.rgb2Rgb1));
                }
                break;

            /* Case is to set RGB2RGB 2 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB2:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_RGB2RGB2CFG,
                    ipipeCtrl->rgb2RgbCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.rgb2Rgb2,
                        ipipeCtrl->rgb2RgbCfg,
                        sizeof(hIspObj->ipipeCfg.rgb2Rgb2));
                }
                break;

            /* Case is to set RGB2YUV matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2YUV:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_RGB2YUVCFG,
                    ipipeCtrl->rgb2YuvCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.rgb2Yuv,
                        ipipeCtrl->rgb2YuvCfg,
                        sizeof(hIspObj->ipipeCfg.rgb2Yuv));
                }
                break;

            /* Case is to set YUV444 to YUV422 Parameters */
            case VPS_ISS_IPIPE_MODULE_YUV444_YUV422:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_YUVCFG,
                    ipipeCtrl->yuvPhsCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.yuvPhs,
                        ipipeCtrl->yuvPhsCfg,
                        sizeof(hIspObj->ipipeCfg.yuvPhs));
                }
                break;

            /* Case is to set DPC LUT Parameters */
            case VPS_ISS_IPIPE_MODULE_DPC_LUT:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_DPCLUTCFG,
                    ipipeCtrl->dpcLut,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.dpcLut,
                        ipipeCtrl->dpcLut,
                        sizeof(hIspObj->ipipeCfg.dpcLut));
                }
                break;

            /* Case is to set DPC OTF Parameters */
            case VPS_ISS_IPIPE_MODULE_DPC_OTF:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_DPCOTFCFG,
                    ipipeCtrl->dpcOtf,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.dpcOtf,
                        ipipeCtrl->dpcOtf,
                        sizeof(hIspObj->ipipeCfg.dpcOtf));
                }
                break;

            /* Case is to set DPC OTF Parameters */
            case VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_GAMMACFG,
                    ipipeCtrl->gammaCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.gammaCfg,
                        ipipeCtrl->gammaCfg,
                        sizeof(hIspObj->ipipeCfg.gammaCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_3D_LUT:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_3D_LUTCFG,
                    ipipeCtrl->colorConvert3DLutCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.colorConvert3DLutCfg,
                        ipipeCtrl->colorConvert3DLutCfg,
                        sizeof(hIspObj->ipipeCfg.colorConvert3DLutCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_EECFG,
                    ipipeCtrl->eeCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.eeCfg,
                        ipipeCtrl->eeCfg,
                        sizeof(hIspObj->ipipeCfg.eeCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_GIC:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_GICCFG,
                    ipipeCtrl->gicCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.gicCfg,
                        ipipeCtrl->gicCfg,
                        sizeof(hIspObj->ipipeCfg.gicCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_LSC:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_LSCCFG,
                    ipipeCtrl->lscCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.lscCfg,
                        ipipeCtrl->lscCfg,
                        sizeof(hIspObj->ipipeCfg.lscCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_NF1:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_NF1CFG,
                    ipipeCtrl->nf1Cfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.nf1Cfg,
                        ipipeCtrl->nf1Cfg,
                        sizeof(hIspObj->ipipeCfg.nf1Cfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_NF2:
                status = VpsHal_issipipeControl(
                    hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_NF2CFG,
                    ipipeCtrl->nf2Cfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if(FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeCfg.nf2Cfg,
                        ipipeCtrl->nf2Cfg,
                        sizeof(hIspObj->ipipeCfg.nf2Cfg));
                }
                break;

            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    return (status);
}

/* IPIPE Get Config */
int32_t IspIpipeGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissIpipeCtrl_t         *ipipeCtrl)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if((NULL == ipipeCtrl) ||
       ((VPS_ISS_IPIPE_MODULE_INPUT == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->inCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_CFA == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->cfaCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_WB == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->wbCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_RGB2RGB1 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->rgb2RgbCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_RGB2RGB2 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->rgb2RgbCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_RGB2YUV == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->rgb2YuvCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_YUV444_YUV422 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->yuvPhsCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_DPC_LUT == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->dpcLut)) ||
       ((VPS_ISS_IPIPE_MODULE_DPC_OTF == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->dpcOtf)) ||
       ((VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->gammaCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_3D_LUT == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->colorConvert3DLutCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->eeCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_GIC == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->gicCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_LSC == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->lscCfg)) ||
       ((VPS_ISS_IPIPE_MODULE_NF1 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->nf1Cfg)) ||
       ((VPS_ISS_IPIPE_MODULE_NF2 == ipipeCtrl->module) &&
        (NULL == ipipeCtrl->nf2Cfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        switch(ipipeCtrl->module)
        {
            /* Case is to get Input Configuration of IPIPE */
            case VPS_ISS_IPIPE_MODULE_INPUT:
                BspUtils_memcpy(
                    ipipeCtrl->inCfg,
                    &hIspObj->ipipeCfg.srcCfg,
                    sizeof(hIspObj->ipipeCfg.srcCfg));
                break;

            /* Case is to get CFA Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_CFA:
                BspUtils_memcpy(
                    ipipeCtrl->cfaCfg,
                    &hIspObj->ipipeCfg.cfaCfg,
                    sizeof(hIspObj->ipipeCfg.cfaCfg));
                break;

            /* Case is to get YUV444 to YUV422 Parameters */
            case VPS_ISS_IPIPE_MODULE_YUV444_YUV422:
                BspUtils_memcpy(
                    ipipeCtrl->yuvPhsCfg,
                    &hIspObj->ipipeCfg.yuvPhs,
                    sizeof(hIspObj->ipipeCfg.yuvPhs));
                break;

            /* Case is to get RGB2YUV matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2YUV:
                BspUtils_memcpy(
                    ipipeCtrl->rgb2YuvCfg,
                    &hIspObj->ipipeCfg.rgb2Yuv,
                    sizeof(hIspObj->ipipeCfg.rgb2Yuv));
                break;

            /* Case is to set RGB2RGB 1 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB1:
                BspUtils_memcpy(
                    ipipeCtrl->rgb2RgbCfg,
                    &hIspObj->ipipeCfg.rgb2Rgb1,
                    sizeof(hIspObj->ipipeCfg.rgb2Rgb1));
                break;

            /* Case is to set RGB2RGB 2 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB2:
                BspUtils_memcpy(
                    ipipeCtrl->rgb2RgbCfg,
                    &hIspObj->ipipeCfg.rgb2Rgb2,
                    sizeof(hIspObj->ipipeCfg.rgb2Rgb2));
                break;

            /* Case is to set White Balance Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_WB:
                BspUtils_memcpy(
                    ipipeCtrl->wbCfg,
                    &hIspObj->ipipeCfg.wbCfg,
                    sizeof(hIspObj->ipipeCfg.wbCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_DPC_OTF:
                BspUtils_memcpy(
                    ipipeCtrl->dpcOtf,
                    &hIspObj->ipipeCfg.dpcOtf,
                    sizeof(hIspObj->ipipeCfg.dpcOtf));
                break;

            case VPS_ISS_IPIPE_MODULE_DPC_LUT:
                BspUtils_memcpy(
                    ipipeCtrl->dpcLut,
                    &hIspObj->ipipeCfg.dpcLut,
                    sizeof(hIspObj->ipipeCfg.dpcLut));
                break;

            case VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION:
                BspUtils_memcpy(
                    ipipeCtrl->gammaCfg,
                    &hIspObj->ipipeCfg.gammaCfg,
                    sizeof(hIspObj->ipipeCfg.gammaCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_3D_LUT:
                BspUtils_memcpy(
                    ipipeCtrl->colorConvert3DLutCfg,
                    &hIspObj->ipipeCfg.colorConvert3DLutCfg,
                    sizeof(hIspObj->ipipeCfg.colorConvert3DLutCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER:
                BspUtils_memcpy(
                    ipipeCtrl->eeCfg,
                    &hIspObj->ipipeCfg.eeCfg,
                    sizeof(hIspObj->ipipeCfg.eeCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_GIC:
                BspUtils_memcpy(
                    ipipeCtrl->gicCfg,
                    &hIspObj->ipipeCfg.gicCfg,
                    sizeof(hIspObj->ipipeCfg.gicCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_LSC:
                BspUtils_memcpy(
                    ipipeCtrl->lscCfg,
                    &hIspObj->ipipeCfg.lscCfg,
                    sizeof(hIspObj->ipipeCfg.lscCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_NF1:
                BspUtils_memcpy(
                    ipipeCtrl->nf1Cfg,
                    &hIspObj->ipipeCfg.nf1Cfg,
                    sizeof(hIspObj->ipipeCfg.nf1Cfg));
                break;

            case VPS_ISS_IPIPE_MODULE_NF2:
                BspUtils_memcpy(
                    ipipeCtrl->nf2Cfg,
                    &hIspObj->ipipeCfg.nf2Cfg,
                    sizeof(hIspObj->ipipeCfg.nf2Cfg));
                break;

            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    return (status);
}

/* Resizer Set Config */
int32_t IspRszSetConfig(
    vcoreIspHandleObj_t   *hIspObj,
    const vpsissRszCtrl_t *rszCtrl)
{
    int32_t  status = FVID2_SOK;
    vpsissRszInstConfig_t *pRszInstCfg;
    Fvid2_Format          *outFmt;
    vpsissRszFlipCtrl_t flipCtrl;
    uint32_t flipVOffsetY, flipVOffsetC, flipHOffsetYC;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_RSZ])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if((NULL == rszCtrl) ||
       ((VPS_ISS_RSZ_MODULE_RSZCFG == rszCtrl->module) &&
        (NULL == rszCtrl->rszCfg)))
    {
        status = FVID2_EBADARGS;
    }

    /* Override the input data format if flag is set */
    if((FVID2_SOK == status) && (TRUE == rszCtrl->rszCfg->inCfg.overrideInCfg))
    {
        hIspObj->rszCfg.srcCfg.inputDataFormat =
            rszCtrl->rszCfg->inCfg.inDataFormat;

        /* One of the instance must be enabled enabled */
        if(TRUE == rszCtrl->rszCfg->instCfg[0u].enable)
        {
            pRszInstCfg = &rszCtrl->rszCfg->instCfg[0u];
        }
        else
        {
            pRszInstCfg = &rszCtrl->rszCfg->instCfg[1u];
        }

        /* Setting the rszLuma flag so that HAL will take care of
           configuring resizer correctly for luma or chroma only mode
           For YUV422 mode, HAL uses yuvRszMode flag to configure
           correctly. */
        if(FVID2_DF_YUV420SP_UV == rszCtrl->rszCfg->inCfg.inDataFormat)
        {
            if(VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_ONLY == pRszInstCfg->yuvRszMode)
            {
                hIspObj->rszCfg.srcCfg.rszLuma = (UInt32) TRUE;
            }
            if(VPS_ISS_RSZ_YUV_RSZ_MODE_CHROMA_ONLY == pRszInstCfg->yuvRszMode)
            {
                hIspObj->rszCfg.srcCfg.rszLuma = (UInt32) FALSE;
            }
            if(VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_AND_CHROMA ==
               pRszInstCfg->yuvRszMode)
            {
                /* Override mode should not be used for YUV420 input and
                   output format because there is a YUV420 resizer driver
                   for this combination */
                status = FVID2_EBADARGS;
            }
        }
    }

    if((FVID2_SOK == status) &&
       (((TRUE == rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A].enable) &&
         (FALSE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_RSZ_A])) ||
        ((TRUE == rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B].enable) &&
         (FALSE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_RSZ_B]))))
    {
        /* Streams should be enabled in SET_PARAMS */
        status = FVID2_EBADARGS;
    }

    /* When input is YUV420, we do not support conversion to YUV22 or others */
    if((FVID2_SOK == status) &&
       (FVID2_DF_YUV420SP_UV == hIspObj->params.inFmt.dataFormat))
    {
        if(TRUE == rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A].enable)
        {
            if(FVID2_DF_YUV420SP_UV !=
               rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.dataFormat)
            {
                status = FVID2_EBADARGS;
            }
        }

        if(TRUE == rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B].enable)
        {
            if(FVID2_DF_YUV420SP_UV !=
               rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.dataFormat)
            {
                status = FVID2_EBADARGS;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        /* TODO: Avoid this copy since if the parameters are invalid,
         *       it will make current set of parameters also invalid. */
        /* Copy Resizer parameters */
        hIspObj->rszCfg.srcCfg.opMode =
            rszCtrl->rszCfg->inCfg.opMode;

        BspUtils_memcpy(
            &hIspObj->rszCfg.srcCfg.procWin,
            &rszCtrl->rszCfg->inCfg.procWin,
            sizeof(hIspObj->rszCfg.srcCfg.procWin));

        if(TRUE == rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A].enable)
        {
            BspUtils_memcpy(
                &hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A],
                &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A],
                sizeof(vpsissRszInstConfig_t));

            flipCtrl = rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A].flipCtrl;

            hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][0U] = 0U;
            hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][1U] = 0U;
            /* Calculate resizer A/B Luma/Chroma offset based on flip */
            if(VPS_ISS_RSZ_STR_MODE_NORMAL != flipCtrl)
            {
                flipVOffsetY = flipVOffsetC = flipHOffsetYC = 0x0U;
                outFmt       =
                    &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A].outFmt;

                if(FVID2_DF_YUV422I_UYVY == outFmt->dataFormat)
                {
                    flipVOffsetY = (outFmt->pitch[0U] *
                                    (outFmt->height - 1U));
                    flipVOffsetC = (outFmt->pitch[1U] *
                                    ((outFmt->height / 2U) - 1U));
                    flipHOffsetYC = ((outFmt->width * 2U) - 2U);
                }
                if(FVID2_DF_YUV420SP_UV == rszCtrl->rszCfg->
                   instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.dataFormat)
                {
                    flipVOffsetY = (outFmt->pitch[0U] *
                                    (outFmt->height - 1U));
                    flipVOffsetC = (outFmt->pitch[1U] *
                                    ((outFmt->height / 2U) - 1U));
                    flipHOffsetYC = (outFmt->width - 1U);
                }

                if(VPS_ISS_RSZ_STR_MODE_HFLIP == flipCtrl)
                {
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][0U] =
                        flipHOffsetYC;
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][1U] =
                        flipHOffsetYC;
                }
                else if(VPS_ISS_RSZ_STR_MODE_VFLIP == flipCtrl)
                {
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][0U] =
                        flipVOffsetY;
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][1U] =
                        flipVOffsetC;
                }
                else /* both side flipped */
                {
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][0U] =
                        flipVOffsetY + flipHOffsetYC;
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_A][1U] =
                        flipVOffsetC + flipHOffsetYC;
                }
            }
        }

        if(TRUE == rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B].enable)
        {
            BspUtils_memcpy(
                &hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B],
                &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B],
                sizeof(vpsissRszInstConfig_t));

            flipCtrl = rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B].flipCtrl;
            hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][0U] = 0U;
            hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][1U] = 0U;
            /* Calculate resizer A/B Luma/Chroma offset based on flip */
            if(VPS_ISS_RSZ_STR_MODE_NORMAL != flipCtrl)
            {
                flipVOffsetY = flipVOffsetC = flipHOffsetYC = 0x0U;
                outFmt       =
                    &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B].outFmt;

                if(FVID2_DF_YUV422I_UYVY == outFmt->dataFormat)
                {
                    flipVOffsetY = (outFmt->pitch[0U] *
                                    (outFmt->height - 1U));
                    flipVOffsetC = (outFmt->pitch[1U] *
                                    ((outFmt->height / 2U) - 1U));
                    flipHOffsetYC = ((outFmt->width * 2U) - 2U);
                }
                if(FVID2_DF_YUV420SP_UV == rszCtrl->rszCfg->
                   instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.dataFormat)
                {
                    flipVOffsetY = (outFmt->pitch[0U] *
                                    (outFmt->height - 1U));
                    flipVOffsetC = (outFmt->pitch[1U] *
                                    ((outFmt->height / 2U) - 1U));
                    flipHOffsetYC = (outFmt->width - 1U);
                }

                if(VPS_ISS_RSZ_STR_MODE_HFLIP == flipCtrl)
                {
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][0U] =
                        flipHOffsetYC;
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][1U] =
                        flipHOffsetYC;
                }
                else if(VPS_ISS_RSZ_STR_MODE_VFLIP == flipCtrl)
                {
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][0U] =
                        flipVOffsetY;
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][1U] =
                        flipVOffsetC;
                }
                else /* both side flipped */
                {
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][0U] =
                        flipVOffsetY + flipHOffsetYC;
                    hIspObj->rszFlipOffset[VPS_ISS_RSZ_SCALER_B][1U] =
                        flipVOffsetC + flipHOffsetYC;
                }
            }
        }
        hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A].enable =
            rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A].enable;
        hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B].enable =
            rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B].enable;

        status = VpsHal_issrszSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_RSZ],
            &hIspObj->rszCfg,
            NULL);
    }

    return (status);
}

/* Resizer Get Config */
int32_t IspRszGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    const vpsissRszCtrl_t     *rszCtrl)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_RSZ])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if((NULL == rszCtrl) ||
       ((VPS_ISS_RSZ_MODULE_RSZCFG == rszCtrl->module) &&
        (NULL == rszCtrl->rszCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        rszCtrl->rszCfg->inCfg.opMode = hIspObj->rszCfg.srcCfg.opMode;
        BspUtils_memcpy(
            &rszCtrl->rszCfg->inCfg.procWin,
            &hIspObj->rszCfg.srcCfg.procWin,
            sizeof(rszCtrl->rszCfg->inCfg.procWin));

        if(TRUE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_RSZ_A])
        {
            BspUtils_memcpy(
                &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A],
                &hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A],
                sizeof(vpsissRszInstConfig_t));
        }

        if(TRUE == hIspObj->params.enableStreams[VPS_ISS_STREAM_ID_RSZ_B])
        {
            BspUtils_memcpy(
                &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B],
                &hIspObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B],
                sizeof(vpsissRszInstConfig_t));
        }
    }

    return (status);
}

/* NSF3 Set Config */
int32_t IspNsf3SetConfig(
    vcoreIspHandleObj_t      *hIspObj,
    const vpsissNsf3Config_t *nsf3Cfg,
    vpsissIspModuleId_t       modId)
{
    int32_t  status = FVID2_SOK;
    uint32_t instId;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[modId])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if(VPS_ISS_ISP_MODULE_NSF3 == modId)
    {
        instId = 0U;
    }
    else
    {
        instId = 1U;
    }

    if(FVID2_SOK == status)
    {
        if(NULL != nsf3Cfg)
        {
            status = VpsHal_issnsf3SetFrameSize(
                hIspObj->halHandles[modId],
                &hIspObj->nsf3FrmSize[instId],
                NULL);

            status = VpsHal_issnsf3SetConfig(
                hIspObj->halHandles[modId],
                nsf3Cfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->nsf3Cfg[instId],
                    nsf3Cfg,
                    sizeof(hIspObj->nsf3Cfg[instId]));
            }
        }
        else
        {
            status = FVID2_EBADARGS;
        }
    }

    return (status);
}

/* NSF3 Get Config */
int32_t IspNsf3GetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissNsf3Config_t        *nsf3Cfg,
    vpsissIspModuleId_t        modId)
{
    int32_t  status = FVID2_SOK;
    uint32_t instId;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[modId])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if(VPS_ISS_ISP_MODULE_NSF3 == modId)
    {
        instId = 0U;
    }
    else
    {
        instId = 1U;
    }

    if(FVID2_SOK == status)
    {
        if(NULL != nsf3Cfg)
        {
            BspUtils_memcpy(
                nsf3Cfg,
                &hIspObj->nsf3Cfg[instId],
                sizeof(*nsf3Cfg));
        }
        else
        {
            status = FVID2_EBADARGS;
        }
    }

    return (status);
}

/* IPIPEIF Set Config */
int32_t IspIpipeifSetConfig(
    vcoreIspHandleObj_t       *hIspObj,
    const vpsissIpipeifCtrl_t *cfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t cmd;
    Ptr      arg = NULL;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPEIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if((NULL == cfg) ||
       ((VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT == cfg->module) &&
        (NULL == cfg->pLutCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG == cfg->module) &&
        (NULL == cfg->pCompDecompCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG == cfg->module) &&
        (NULL == cfg->pSatCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG == cfg->module) &&
        (NULL == cfg->pWdrCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_DPC_CFG == cfg->module) &&
        (NULL == cfg->pDpcCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        switch(cfg->module)
        {
            /* Case is to update the Companding and Decompanding lut tables */
            case VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_LUT;
                arg = (Ptr) cfg->pLutCfg;
                break;

            /* Case is to update the Companding and Decompanding
             * configuration */
            case VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_SET_COMPDECOMP_CFG;
                arg = (Ptr) cfg->pCompDecompCfg;
                break;

            /* Case is to update the saturation configuration */
            case VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_SET_SATURATION_CFG;
                arg = (Ptr) cfg->pSatCfg;
                break;

            /* Case is to update the WDR Merge configuration */
            case VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_SET_WDR_CFG;
                arg = (Ptr) cfg->pWdrCfg;
                break;
            case VPS_ISS_IPIPEIF_MODULE_DPC_CFG:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_SET_DPC_CFG;
                arg = (Ptr) cfg->pDpcCfg;
                break;
            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    if(FVID2_SOK == status)
    {
        status = VpsHal_issipipeifControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPEIF],
            cmd,
            arg,
            NULL);
    }

    if(FVID2_SOK == status)
    {
        switch(cfg->module)
        {
            /* Case is to update the Companding and Decompanding
             * configuration */
            case VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG:
                BspUtils_memcpy(
                    &hIspObj->ipipeifCfg.compDecompCfg,
                    cfg->pCompDecompCfg,
                    sizeof(vpsissIpipeifDeCompandInsts_t));
                break;

            /* Case is to update the saturation configuration */
            case VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG:
                BspUtils_memcpy(
                    &hIspObj->ipipeifCfg.satCfg,
                    cfg->pSatCfg,
                    sizeof(vpsissIpipeifSaturaInsts_t));
                break;

            /* Case is to update the WDR Merge configuration */
            case VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG:
                BspUtils_memcpy(
                    &hIspObj->ipipeifCfg.wdrCfg,
                    cfg->pWdrCfg,
                    sizeof(vpsissIpipeifWdrCfg_t));
                break;
            /* MISRA.PTR.ARITH
             * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
             * Name 'pDpcCfg[1U]'
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Pointer arithmetic is required for performance like auto increment in loop.
             * The harmful side effect of violating this rule (accessing outside valid
             *  memory) shall be checked by another code checker like klockwork.
             */
            case VPS_ISS_IPIPEIF_MODULE_DPC_CFG:
                if ((NULL != &cfg->pDpcCfg[1U]) && (NULL != &cfg->pDpcCfg[0U]))
                {
                    BspUtils_memcpy(
                        &hIspObj->ipipeifCfg.vportOrIsififDpcCfg,
                        &cfg->pDpcCfg[0U],
                        sizeof(vpsissIpipeifDpcCfg_t));
                    BspUtils_memcpy(
                        &hIspObj->ipipeifCfg.memIfDpcCfg,
                        &cfg->pDpcCfg[1U],
                        sizeof(vpsissIpipeifDpcCfg_t));
                }
                break;

            case VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT:
                /* We do not maintain lut locally, so nothing much to be done */
                break;

            /* This should not occur unless cfg is corrupted */
            default:
                GT_assert(VpsIssCoreTrace, (FALSE));
                break;
        }
    }

    return (status);
}

/* IPIPEIF Get Config */
int32_t IspIpipeifGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissIpipeifCtrl_t       *cfg)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPEIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if((NULL == cfg) ||
       ((VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT == cfg->module) &&
        (NULL == cfg->pLutCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG == cfg->module) &&
        (NULL == cfg->pCompDecompCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG == cfg->module) &&
        (NULL == cfg->pSatCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG == cfg->module) &&
        (NULL == cfg->pWdrCfg)) ||
       ((VPS_ISS_IPIPEIF_MODULE_DPC_CFG == cfg->module) &&
        (NULL == cfg->pDpcCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        switch(cfg->module)
        {
            /* Case is to get Companding/Decompanding parameters of IPIPEIF */
            case VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG:
                BspUtils_memcpy(
                    cfg->pCompDecompCfg,
                    &hIspObj->ipipeifCfg.compDecompCfg,
                    sizeof(vpsissIpipeifDeCompandInsts_t));
                break;

            /* Case is to get Saturation parameters of IPIPEIF */
            case VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG:
                BspUtils_memcpy(
                    cfg->pSatCfg,
                    &hIspObj->ipipeifCfg.satCfg,
                    sizeof(vpsissIpipeifSaturaInsts_t));
                break;

            case VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG:
                BspUtils_memcpy(
                    cfg->pWdrCfg,
                    &hIspObj->ipipeifCfg.wdrCfg,
                    sizeof(vpsissIpipeifWdrCfg_t));
                break;

            /* MISRA.PTR.ARITH
             * Rule 17.1 17.4: Pointer is used in arithmetic or array index expression
             * Name 'pDpcCfg[1U]'
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Pointer arithmetic is required for performance like auto increment in loop.
             * The harmful side effect of violating this rule (accessing outside valid
             *  memory) shall be checked by another code checker like klockwork.
             */
            case VPS_ISS_IPIPEIF_MODULE_DPC_CFG:
                if ((NULL != &cfg->pDpcCfg[1U]) && (NULL != &cfg->pDpcCfg[0U]))
                {
                    BspUtils_memcpy(
                        &cfg->pDpcCfg[0U],
                        &hIspObj->ipipeifCfg.vportOrIsififDpcCfg,
                        sizeof(vpsissIpipeifDpcCfg_t));

                    BspUtils_memcpy(
                        &cfg->pDpcCfg[1U],
                        &hIspObj->ipipeifCfg.memIfDpcCfg,
                        sizeof(vpsissIpipeifDpcCfg_t));
                }
                break;
            /* Case is to get LUT Parameters of IPIPE */
            case VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT:
            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    return (status);
}

/* GLBCE Set Config */
int32_t IspGlbceSetConfig(
    vcoreIspHandleObj_t *hIspObj,
    vpsissGlbceCtrl_t   *glbceCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_GLBCE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if((NULL == glbceCtrl) ||
       ((VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module) &&
        (NULL == glbceCtrl->glbceCfg)) ||
       ((VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module) &&
        (NULL == glbceCtrl->fwdPrcptCfg)) ||
       ((VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module) &&
        (NULL == glbceCtrl->revPrcptCfg)) ||
       ((VPS_ISS_GLBCE_MODULE_WDR == glbceCtrl->module) &&
        (NULL == glbceCtrl->wdrCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_GLBCECFG,
                glbceCtrl->glbceCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->glbceCfg.glbceCfg,
                    glbceCtrl->glbceCfg,
                    sizeof(hIspObj->glbceCfg.glbceCfg));
            }
        }
        else if(VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_FWDPRCPT_CFG,
                glbceCtrl->fwdPrcptCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->glbceCfg.fwdPrcptCfg,
                    glbceCtrl->fwdPrcptCfg,
                    sizeof(hIspObj->glbceCfg.fwdPrcptCfg));
            }
        }
        else if(VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_REVPRCPT_CFG,
                glbceCtrl->revPrcptCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->glbceCfg.revPrcptCfg,
                    glbceCtrl->revPrcptCfg,
                    sizeof(hIspObj->glbceCfg.revPrcptCfg));
            }
        }
        else
        {
            /* It has to be VPS_ISS_GLBCE_MODULE_WDR, as we have checked for
                all valid possibilities above */
            status = VpsHal_issglbceControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_WDRCFG,
                glbceCtrl->wdrCfg,
                NULL);

            if(FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hIspObj->glbceCfg.wdrCfg,
                    glbceCtrl->wdrCfg,
                    sizeof(hIspObj->glbceCfg.wdrCfg));
            }
        }
    }

    return (status);
}

/* GLBCE Get Config */
int32_t IspGlbceGetConfig(
    const vcoreIspHandleObj_t *hIspObj,
    vpsissGlbceCtrl_t         *glbceCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(FALSE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_GLBCE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if((NULL == glbceCtrl) ||
       ((VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module) &&
        (NULL == glbceCtrl->glbceCfg)) ||
       ((VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module) &&
        (NULL == glbceCtrl->fwdPrcptCfg)) ||
       ((VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module) &&
        (NULL == glbceCtrl->revPrcptCfg)) ||
       ((VPS_ISS_GLBCE_MODULE_WDR == glbceCtrl->module) &&
        (NULL == glbceCtrl->wdrCfg)) ||
       ((VPS_ISS_GLBCE_MODULE_GET_STATS_INFO == glbceCtrl->module) &&
        (NULL == glbceCtrl->statsInfo)))
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module)
        {
            BspUtils_memcpy(
                glbceCtrl->glbceCfg,
                &hIspObj->glbceCfg.glbceCfg,
                sizeof(hIspObj->glbceCfg.glbceCfg));
        }
        else if(VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module)
        {
            BspUtils_memcpy(
                glbceCtrl->fwdPrcptCfg,
                &hIspObj->glbceCfg.fwdPrcptCfg,
                sizeof(hIspObj->glbceCfg.fwdPrcptCfg));
        }
        else if(VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module)
        {
            BspUtils_memcpy(
                glbceCtrl->revPrcptCfg,
                &hIspObj->glbceCfg.revPrcptCfg,
                sizeof(hIspObj->glbceCfg.revPrcptCfg));
        }
        else if(VPS_ISS_GLBCE_MODULE_GET_STATS_INFO == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_GET_STATS_INFO,
                glbceCtrl->statsInfo,
                NULL);
        }
        else
        {
            /* It has to be VPS_ISS_GLBCE_MODULE_WDR, as we have checked for
                all valid possibilities above */
            BspUtils_memcpy(
                glbceCtrl->wdrCfg,
                &hIspObj->glbceCfg.wdrCfg,
                sizeof(hIspObj->glbceCfg.wdrCfg));
        }
    }

    return (status);
}

static int32_t checkIsifVfdcCfg(const vpsissIspParams_t      *pIspParams,
                                const vpsissIsifVfdcConfig_t *pVfdcCfg)
{
    uint32_t idx, prevHLoc;
    int32_t  rtnVal = FVID2_EBADARGS;
    /*  Check being done
        .CoOrdinates should be within the frame boundary
        .Should start from left and move to right - order of defect pixel
            location definition
        */
    if((NULL != pIspParams) && (NULL != pVfdcCfg))
    {
        rtnVal   = FVID2_SOK;
        prevHLoc = 0x0;
        for(idx = 0; ((idx < pVfdcCfg->numPixToBeCorrected) &&
                      (FVID2_SOK == rtnVal)); idx++)
        {
            if((pVfdcCfg->defectivePixCoOr[0][idx] > pIspParams->inFmt.height)
               ||
               (pVfdcCfg->defectivePixCoOr[1][idx] > pIspParams->inFmt.width))
            {
                rtnVal = FVID2_EBADARGS;
            }

            if(prevHLoc > pVfdcCfg->defectivePixCoOr[1][idx])
            {
                rtnVal = FVID2_EBADARGS;
            }
            prevHLoc = pVfdcCfg->defectivePixCoOr[1][idx];
        }
    }
    return rtnVal;
}

static void vcoreIspSetGlbceMux(const vcoreIspHandleObj_t *hIspObj)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hIspObj));

    if(VPS_ISS_NSF3_PATH_ISP == hIspObj->params.nsf3Path)
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_NSF3,
            ISSHAL_GLBCE_SWITCH_ISP);
    }
    else if(VPS_ISS_NSF3_PATH_CAL == hIspObj->params.nsf3Path)
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_NSF3,
            ISSHAL_GLBCE_SWITCH_CAL);
    }
    else
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_NSF3,
            ISSHAL_GLBCE_SWITCH_DISABLED);
    }

    if(VPS_ISS_GLBCE_PATH_ISP == hIspObj->params.glbcePath)
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_GLBCE,
            ISSHAL_GLBCE_SWITCH_ISP);
    }
    else if(VPS_ISS_GLBCE_PATH_CAL == hIspObj->params.glbcePath)
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_GLBCE,
            ISSHAL_GLBCE_SWITCH_CAL);
    }
    else
    {
        VpsHal_issSetGlbceSwitch(
            ISSHAL_GLBCE_SWITCH_GLBCE,
            ISSHAL_GLBCE_SWITCH_DISABLED);
    }

    VpsHal_issDpcBeforeNsf3(hIspObj->params.enableDpcPreNsf3);

    /* Set the VP1 configuration */
    status = VpsHal_issSetVp1Config(&hIspObj->vp1Cfg);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    /* Set the VP2 configuration */
    status = VpsHal_issSetVp2Config(&hIspObj->vp2Cfg);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
}

static void vcoreIspSetVmux(const vcoreIspHandleObj_t *hIspObj)
{
    int32_t status;

    if(VPS_ISS_GLBCE_PATH_CAL == hIspObj->params.glbcePath)
    {
        status = vcoreIspSetupVmux(SRC_PORT_CAL_A_BYS_OUT, SINK_PORT_GLBCE_IN,
                                   (uint32_t) TRUE);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        status = vcoreIspSetupVmux(SRC_PORT_GLBCE_OUT, SINK_PORT_CAL_A_BYS_IN,
                                   (uint32_t) TRUE);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }
    if(VPS_ISS_NSF3_PATH_CAL == hIspObj->params.nsf3Path)
    {
        status = vcoreIspSetupVmux(SRC_PORT_CAL_A_BYS_OUT, SINK_PORT_NSFV3_IN,
                                   (uint32_t) TRUE);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

        status = vcoreIspSetupVmux(SRC_PORT_NSF3V_OUT, SINK_PORT_CAL_A_BYS_IN,
                                   (uint32_t) TRUE);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }
}

/* Connects Source and Sink of the video mux */
static int32_t vcoreIspSetupVmux(
    isshalVMuxSrcPorts_t  vmuxSrc,
    isshalVMuxSinkPorts_t vmuxSink,
    uint32_t              flag)
{
    int32_t status = FVID2_SOK;

    /* Gate the clock first */
    status = VpsHal_issvmuxClkCtrl(
        vmuxSrc,
        vmuxSink,
        (uint32_t) FALSE);

    if(FVID2_SOK == status)
    {
        if(TRUE == flag)
        {
            /* Setup the path */
            status = VpsHal_issvmuxSetPath(
                vmuxSrc,
                vmuxSink,
                (uint32_t) TRUE);
        }
        else
        {
            /* Setup the path */
            status = VpsHal_issvmuxSetPath(
                vmuxSrc,
                vmuxSink,
                (uint32_t) FALSE);
        }
    }

    if(FVID2_SOK == status)
    {
        /* Enable the clock */
        status = VpsHal_issvmuxClkCtrl(
            vmuxSrc,
            vmuxSink,
            (uint32_t) TRUE);
    }

    return (status);
}

int32_t vcoreIspSetSrcSize(vcoreIspHandleObj_t *hIspObj)
{
    int32_t status = FVID2_SOK;

    if(TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_NSF3])
    {
        /* Set the Frame size in NSF3 */
        status = VpsHal_issnsf3SetFrameSize(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_NSF3],
            &hIspObj->nsf3FrmSize[0U],
            NULL);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    /* Require to configure the complete source config, as i/f width, msbPos
        and other could change */
    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_ISIF]))
    {
        uint32_t subModId;
        /* Only the source config we are interested in */
        subModId = hIspObj->isifCfg.moduleId;
        hIspObj->isifCfg.moduleId = ISSHAL_ISIF_MODULE_SRC_CFG;
        status = VpsHal_issisifSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_ISIF],
            &hIspObj->isifCfg,
            NULL);
        hIspObj->isifCfg.moduleId = subModId;
    }

    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_GLBCE]))
    {
        status = VpsHal_issglbceControl(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_GLBCE],
            ISSHAL_IOCTL_GLBCE_SET_FRAME_CFG,
            &hIspObj->glbceCfg,
            NULL);
    }

    /* The path within the IPIPE could change, configure the path
        and the source sizes */
    if((FVID2_SOK == status) &&
       (TRUE == hIspObj->isModReq[VPS_ISS_ISP_MODULE_IPIPE]))
    {
        uint32_t subModId;

        subModId = hIspObj->ipipeCfg.moduleId;
        hIspObj->ipipeCfg.moduleId = ISSHAL_IPIPE_MODULE_SRC_CFG;
        status = VpsHal_issipipeSetConfig(
            hIspObj->halHandles[VPS_ISS_ISP_MODULE_IPIPE],
            &hIspObj->ipipeCfg,
            NULL);
        hIspObj->ipipeCfg.moduleId = subModId;
    }

    return (status);
}

int32_t vcoreIspSetCaptStrmMap(vcoreIspHandleObj_t              *hIspObj,
                               const vpsissCalOtfStreamMapCfg_t *streamMap)
{
    int32_t            status = FVID2_EBADARGS;
    vpsissIspParams_t *prms;
    uint32_t           idx, captStrmId;
    vpsissStreamId_t   ispStrmId;

    if((NULL != hIspObj) && (NULL != streamMap))
    {
        /* Check if the stream is actually enabled
            Update the map.
            */
        prms = &hIspObj->params;

        for(idx = 0U; idx < streamMap->numStream; idx++)
        {
            status     = FVID2_EBADARGS;
            captStrmId = streamMap->captStreamId[idx];
            ispStrmId  = streamMap->ispStreamId[idx];

            if((VPS_ISS_STREAM_CAL_RD_INPUT_0 < ispStrmId) ||
               (VPS_ISS_STREAM_ID_MAX > ispStrmId))
            {
                if(TRUE == prms->enableStreams[ispStrmId])
                {
                    status = FVID2_SOK;
                }
            }

            if(FVID2_SOK == status)
            {
                hIspObj->captStreamMap[ispStrmId] = captStrmId;
            }
            else
            {
                break;
            }
        }
        if(FVID2_SOK != status)
        {
            BspUtils_memset(&hIspObj->captStreamMap[0U], (UInt8)0xFF,
                            sizeof(hIspObj->captStreamMap));
        }
    }

    return (status);
}

