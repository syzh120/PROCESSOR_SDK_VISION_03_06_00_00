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
 *  \file vps_mlm.h
 *
 *  \brief VPS Memory List Manager header file
 *  This file exposes the APIs of the VPS List Manager for the Mem2Mem drivers.
 *
 */

#ifndef VPS_MLM_H_
#define VPS_MLM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/common/vps_evtMgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* At the time of submitting a request, mlm appends few sync on channel
 * control descriptors at the end of request. This defines maximum number of
 * control descriptors to be appended. */
#define MLM_MAX_CHANNELS            (20U)

/**
 *  \brief Typedef for MLM handle
 */
typedef void *Mlm_Handle;

typedef struct Mlm_SubmitReqInfo_t Mlm_SubmitReqInfo;

/**
 *  \brief VPS Memory list manager callback function prototype. Each client
 *  driver should register a callback to the memory list manager.
 *
 *  arg: Private argument which is passed by the client at the time of client
 *  registration for any identification by the client. This can be used by
 *  clients which registers multiple times with the same callback function.
 */
typedef Int32 (*Mlm_ClientCbFxn)(const Mlm_SubmitReqInfo *reqInfo);

typedef enum Mlm_SubmitReqType_t
{
    MLM_SRT_USE_SOC = 0,
    /**< Use SoC at the end of the request */
    MLM_SRT_NO_SOC,
    /**< Do not use SoC at the end of the request */
    MLM_SRT_USE_SOR_NO_SOC
    /**< Use SOR but no SOC at the end of the request -- added for FMD */
} Mlm_SubmitReqType;

typedef enum Mlm_ClientType_t
{
    MLM_CT_SC = 0,
    /**< M2M SC driver. */
    MLM_CT_NSF,
    /**< M2M NSF driver. */
    MLM_CT_VPE,
    /**< M2M VPE driver. */
    MLM_CT_BLEND
    /**< M2M Blender driver. */
} Mlm_ClientType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * struct Mlm_ClientInfo
 * \brief
 */
typedef struct Mlm_ClientInfo_t
{
    Mlm_ClientCbFxn     reqCompleteCb;
    /**< Request complete callback function. This function will be called when
     *   a submitted request is complete. Client can submit a request
     *   containing multiple processing channel. At the end of completion of
     *   the last channel, this callback will be called. This callback
     *   indicates request is completed. */
    UInt32              isChannelStatic;
    /**< This flag indicates whether channels numbers are static or not.
     *   If the channel numbers are static, MLM will use channel number
     *   from the clientInfo structure and program all the required
     *   control descriptors at the time of registration. If it is
     *   not static, it ignores chNum field from clientinfo and
     *   uses channel number from the submitreqinfo structure and MLM
     *   programs sync on channel control descriptors every time the
     *   request is submitted. */
    VpsHal_VpdmaChannel chNum[MLM_MAX_CHANNELS];
    /**< VPDMA channel number to be used for the sync on channel control
     *   descriptor. MLM use sync on channel control descriptor at the end of
     *   each submitted request to make sure that last channel in the request
     *   gets completed and after that, it can give request completion callback
     *   to the client. For this sync on client, it needs the channel number
     *   on which it can wait. */
    UInt32              numChannels;
    /**< Size of the chNum array */
    Mlm_ClientType      clientType;
    /**< Type of driver calling the MLM - used to differentiate between DEIHQ
     *   DEI etc so that FMD interrupt could be registered accordingly. */
    Mlm_ClientCbFxn     deiFmdCb;
    /**< FMD call back function */
} Mlm_ClientInfo;

/**
 * struct Mlm_SubmitReqInfo
 * \brief
 */
struct Mlm_SubmitReqInfo_t
{
    Ptr                 reqStartAddr;
    /**< This address points to the descriptor start address of the first
     *   channel in the given request. Client can submit multiple processing
     *   request in a single submit call. To link or to submit request to the
     *   VPDMA, this address is required. If this address is not provided, it
     *   will return error. */
    Ptr                 lastRlDescAddr;
    /**< Before list complete interrupt, MLM links the requests as they are
     *   submitted to it. MLM can link the requests if reload conrtol
     *   descriptor is available at the end of last channel. This address
     *   points to the reload descriptor of the last channel. If this address
     *   is null, MLM will not link next request with the current request and
     *   next request will be submitted by posting the list again. */
    UInt32              firstChannelSize;
    /**< This indicates the size of the first channel in the submitted request.
     *   To link this request with the previous request, MLM needs to
     *   program size of the channel in the reload descriptor. */
    Mlm_SubmitReqType   submitReqType;
    /**< Indicates the type of the request. This type of request decides
     *   whether to add sync on client control descriptor or not at the
     *   end of the request. There are request, which contains configuration
     *   descriptors only or which contains sync on client control
     *   descriptor at the end of each channel. In this case, there is no
     *   need to add Soc Control Descriptor otherwise it will stall the list.
     */
    VpsHal_VpdmaChannel chNum[MLM_MAX_CHANNELS];
    /**< VPDMA channel number to be used for the sync on channel control
     *   descriptor. MLM use sync on channel control descriptor at the end of
     *   each submitted request to make sure that last channel in the request
     *   gets completed and after that, it can give request completion callback
     *   to the client. For this sync on client, it needs the channel number
     *   on which it can wait. This field is used only of channels
     *   numbers are not static. */
    UInt32              numChannels;
    /*< Size of the chNum array */
    void               *cbArg;
};

/**
 *  struct Mlm_InstParams
 *  \brief Structure containing instance specific parameters used at the init.
 */
typedef struct
{
    VpsHal_Handle vpdmaHandle;
    /**< VPDMA handle. */
    Vem_InstId    vemInstId;
    /**< Event Manager instance ID. */
    Vrm_InstId    vrmInstId;
    /**< Resource Manager instance ID. */
} Mlm_InitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Mlm_init
 *  \brief Function to initialize VPS Memory List Manager. It initializes
 *  all global variables and keeps it ready.
 *
 *  Event Manager and Vps Utils must be initialized before calling
 *  this function.
 *
 *  \param initPrms     Init parameters.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Mlm_init(const Mlm_InitParams *initPrms);

/**
 *  Mlm_deInit
 *  \brief Function to de-initialize VPS Memory List Manager.
 *
 *  \param arg           Currently not used. For the future reference
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Mlm_deInit(void);

/**
 *  Mlm_register
 *  \brief Function to register memory driver to the MLM. This function
 *  asks for the resources like VPDMA list number, SI source etc. so this
 *  function should be called by the memory to memory driver when application
 *  is opening memory driver first time.
 *
 *  \param opMode        Operation Mode
 *  \param clientInfo    Pointer to client Info structure
 *  \param arg           Currently not used. For the future reference
 *
 *  \return              returns handle to the mlm client in case of success
 *                       returns null in case of error.
 */
Mlm_Handle Mlm_register(const Mlm_ClientInfo *clientInfo,
                        Ptr                   arg);

/**
 *  Mlm_unRegister
 *  \brief Function to un-register memory driver to the MLM. This functions
 *  releases resource like VPDMA List, SI Source etc. so ths function should
 *  be called by memory driver when application closes last handle of the
 *  memory driver.
 *
 *  \param mlmHandle     Handle to Memory to Memory driver client
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Mlm_unRegister(Mlm_Handle mlmHandle);

/**
 *  Mlm_submit
 *  \brief Function to submit a requst to the MLM.
 *
 *  \param mlmHandle     Handle to Memory to Memory driver client
 *  \param submitReq     Pointer to submitRequestInfo structure containing
 *                       pointer to the list to be submitted.
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Mlm_submit(Mlm_Handle mlmHandle, Mlm_SubmitReqInfo *submitReq);

#ifdef __cplusplus
}
#endif

#endif /* End of #ifndef VPS_MLM_H_ */
