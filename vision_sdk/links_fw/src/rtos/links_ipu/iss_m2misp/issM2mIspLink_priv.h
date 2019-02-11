/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \ingroup ISSM2MISP_LINK_API
 * \defgroup ISSM2MISP_LINK_IMPL Iss M2m Isp Link Implementation
 *
 * @{
 */

 /**
 *******************************************************************************
 *
 * \file issM2mIspLink_priv.h Iss M2m Isp link private header file.
 *
 * \brief  This file is a private header file for iss M2misp link implementation
 *
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of iss M2misp link.
 *
 *         Links and chains operate on channel number to identify the buffers
 *         from different sources and streams.
 *
 *         Output of Iss M2m Isp link consists of two queues
 *          - Output Image
 *          - H3A statistics
 *
 * \version 0.0 (Jul 2014) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef ISSM2MISP_LINK_PRIV_H_
#define ISSM2MISP_LINK_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issIspConfiguration.h>

#include <ti/drv/vps/include/iss/vps_m2mIss.h>
#include <ti/drv/vps/include/vps_m2mIntf.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* Sensor Exposure Ratio,
   TODO: Read it from the sensor register and calculate WDR Parameters */
#define SENSOR_EXPOSURE_RATIO       (128)
/* Typically Set to log2(SENSOR_EXPOSURE_RATIO) */
#define SENSOR_EV_RATIO             (7)
/* Buffer alignment required for ISP link */
#define ISSM2MISP_LINK_BUF_ALIGN    (ISSM2MISP_LINK_RSZ_BUF_ALIGN)
/**
 *******************************************************************************
 * \brief Number of frames (buffers) allocated per channel of ISP processing
 *******************************************************************************
 */
#define ISSM2MISP_LINK_MAX_FRAMES_PER_CH     (SYSTEM_LINK_FRAMES_PER_CH)


/**
 *******************************************************************************
 * \brief Maximum number of Iss M2m isp link objects
 *******************************************************************************
 */
#define ISSM2MISP_LINK_OBJ_MAX            (1U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of frames getting allocated for entire capture Link.
 *
 *        This is to allocate frame container statically, which will point to
 *        actual frames. Frames will be allocated based on application requests
 *        but frame containers are always allocated at init time that is max
 *        of frames possible.
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_MAX_FRAMES (ISSM2MISP_LINK_MAX_CH*ISSM2MISP_LINK_MAX_FRAMES_PER_CH)

/* \brief WDR Merge threshold percentage,
    the range of THRESHOLD_PERCENTAGE is 0-100% specified Q16 format
   65535 Maps to 100% */
#define ISSM2MISP_LINK_THRESHOLD_PERCENTAGE    (65535U)



/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief  Enumerations for 1st pass or second pass
 *******************************************************************************
*/
typedef enum
{
    ISSM2MISP_LINK_FIRST_PASS = 0,
    /**< First pass */

    ISSM2MISP_LINK_SECOND_PASS = 1,
    /**< Second pass */

    ISSM2MISP_LINK_MAXNUM_PASS = 2,
    /**< Maximum number of passes for this link */

    ISSM2MISP_LINK_INPUT_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} IssM2mIspLink_PassId;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the ISS M2M ISP link Output object
 *
 *          This includes elements which are common for every output queue
 *
 *******************************************************************************
*/
typedef struct {
    Utils_QueHandle fullBufQue;
    /**< Link output side full buffer queue */
    System_Buffer   *fullBufsMem[ISSM2MISP_LINK_MAX_FRAMES];
    /**< Memory for full buff queue */
    System_Buffer   buffers[ISSM2MISP_LINK_MAX_CH]
                           [ISSM2MISP_LINK_MAX_FRAMES_PER_CH];
    /**< System buffer data structure to exchange buffers between links */
    Utils_QueHandle emptyBufQue[ISSM2MISP_LINK_MAX_CH];
    /**< Link output side empty buffer queue */
    System_Buffer  *emptyBufsMem[ISSM2MISP_LINK_MAX_CH]
                           [ISSM2MISP_LINK_MAX_FRAMES_PER_CH];

    UInt32  bufSize[ISSM2MISP_LINK_MAX_CH];

   /** Holds individual channel empty buffers */
} IssM2mIspLink_OutObj;


typedef struct
{
    Fvid2_Handle               drvHandle;
    /**< FVID2 display driver handle. */

    vpsissIspParams_t          ispPrms;
    /**< isp parameters */

    vpsissIspOpenParams_t      openPrms;
    /**< Core Open Parameters */

    vpsissIpipeWbConfig_t      ipipeWbCfg;
    /**< White balance config at ISIF */

    vpsissIsifGainOfstConfig_t  isifWbCfg;
    /**< ISIF WB config */

    vpsissIsifBlackClampConfig_t isifBlkClampCfg;
    /**< ISIF Black Clamping Configuration */

    vpsissIpipeRgb2RgbConfig_t rgb2rgb1;
    /**< RGB to RGB Matrix 1 */
    vpsissIpipeRgb2RgbConfig_t rgb2rgb2;
    /**< RGB to RGB Matrix 2 */

    vpsissIpipeifWdrCfg_t       wdrCfg;
    /**< WDR Configuration, used for updating White balance gains
         and also merge parameters based on exposure ratio */
    vpsissIpipeifDeCompandInsts_t compDecompCfg;
    /**< WDR Companding configuration,
         Companding can be enabled/disabled based on exposure ratio */

    vpsissRszCfg_t                rszCfg;
    vpsissIpipeifSaturaInsts_t    satCfg;

} IssM2mIspLink_PassObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing attributes for each channel operation
 *
 *******************************************************************************
*/
typedef struct {

    IssIspConfigurationParameters ispCfgParams;

    IssM2mIspLink_PassObj         passCfg[ISSM2MISP_LINK_MAXNUM_PASS];

    vpsissIpipeLutFmtCnvt_t       lutFmtCnvt;
    vpsissRszCtrl_t               rszCtrl;
    vpsissIpipeifCtrl_t           ipipeifCtrl;
    vpsissIsifCtrl_t              isifCtrl;
    vpsissIpipeCtrl_t             ipipeCtrl;
    vpsissGlbceCtrl_t             glbceCtrl;
    vpsissIpipeInConfig_t         inCfg;
    vpsissH3aCtrl_t               h3aCtrl;

    UInt32                        expRatio;
    UInt32                        evRatio;
    /* Sensor Exposure Ratio */

    Void                        *pGlbceStatsBuffer;

    IssM2mIspLink_IspOutputTapPoints outputTapModule;
} IssM2mIspLink_ChannelObject;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing information for each instance of
 *          Iss capture link.
 *
 *******************************************************************************
*/
typedef struct {

    UInt32 linkId;
    /**< Iss M2m Isp Link ID */

    Utils_TskHndl tsk;
    /**< Handle to iss M2m isp link task */

    System_VideoFrameBuffer videoFramesRszA[ISSM2MISP_LINK_MAX_CH]
                                       [ISSM2MISP_LINK_MAX_FRAMES_PER_CH];
    /**< Payload for System buffers for image output */

    System_VideoFrameBuffer videoFramesRszB[ISSM2MISP_LINK_MAX_CH]
                                       [ISSM2MISP_LINK_MAX_FRAMES_PER_CH];
    /**< Payload for System buffers for image output */
    System_MetaDataBuffer h3aAfBuffer[ISSM2MISP_LINK_MAX_CH]
                               [ISSM2MISP_LINK_MAX_FRAMES_PER_CH];
    /**< Payload for System buffers for h3a af statistics output */
    System_MetaDataBuffer h3aBuffer[ISSM2MISP_LINK_MAX_CH]
                                   [ISSM2MISP_LINK_MAX_FRAMES_PER_CH];
    /**< Payload for System buffers for h3a statistics output */
    IssM2mIspLink_OutObj linkOutObj[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM];
    /**< Output queue properties */

    IssM2mIspLink_CreateParams createArgs;
    /**< Create params for iss M2m isp link */

    System_LinkInfo prevLinkInfo;
    /**< Information of previous link */

    System_LinkQueInfo inQueInfo;
    /**< Input Q channel specific info, read from the outQ of previous LINK */

    System_LinkInfo linkInfo;
    /**< Link information, which will be given to next link */

    IssM2mIspLink_ChannelObject chObj[ISSM2MISP_LINK_MAX_CH];
    /**< Attributes for operating each channel */

    Void    *pIntermediateBufAddr;
    /**< Pointer to data buffer used to hold first pass output
     *   in 20-bit WDR mode
     */
    UInt32  intermediateBufSize;
    /**< Size of intermediate buffer */

    BspOsal_SemHandle semProcessCall;
    /**< Semaphore for tracking process call of the driver */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Used to log the memory usage of the VPE link */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

    UInt32  statsStartTime;
    /**< Time at which capture is started */

    Utils_DmaChObj   saveCtxDmaObj;
    /**< DMA object to save and restore context */
    vpsissGlbceStatsInfo_t glbceStatsInfo;
    /**< GLBCE Statistics information */

    UInt8           *saveFrameBufAddr;
    /**< Frame buffer used for saving captured frame */
    UInt8           *saveFramePlaneAddr[2];
    /**< Addresses of Y and UV plane in the save Frame buffer */
    UInt32          saveFramePlaneSize[2];
    /**< Sizes of Y and UV planes copied to save Frame buffer */
    volatile UInt32  saveFrame;
    /**< Flag to indicate saving of the frame from process callback */
    volatile UInt32  saveFrameChId;
    /**< Channel Id of the frame to be saved */
    UInt32           saveFrameSize;
    /**< Size of the buffer */
    Utils_DmaChObj   dumpFramesDmaObj;
    /**< DMA object to use when dumping frames to memory */
} IssM2mIspLink_Obj;



extern IssM2mIspLink_Obj gIssM2mIspLink_obj[ISSM2MISP_LINK_OBJ_MAX];

Int32 IssM2mIspLink_getInfo(Void * ptr, System_LinkInfo * info);
Int32 IssM2mIspLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);
Int32 IssM2mIspLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList);

Int32 IssM2mIspLink_drvCreate(IssM2mIspLink_Obj * pObj,
                            const IssM2mIspLink_CreateParams * pPrm);

Int32 IssM2mIspLink_drvProcessData(IssM2mIspLink_Obj * pObj);

Int32 IssM2mIspLink_drvDelete(IssM2mIspLink_Obj * pObj);

Int32 IssM2mIspLink_drvPutEmptyBuffers(IssM2mIspLink_Obj * pObj,
                                     System_BufferList * pBufList);

Int32 IssM2mIspLink_drvPrintStatus(const IssM2mIspLink_Obj * pObj);

Int32 IssM2mIspLink_drvSetIspConfig(IssM2mIspLink_Obj                 * pObj,
                                    const IssIspConfigurationParameters *pCfgPrm,
                                    UInt32                              isDccSetCfg);

Int32 IssM2mIspLink_drvCallBack(Fvid2_Handle handle,
                                       Ptr appData,
                                       Ptr reserved);

Int32 IssM2mIspLink_drvApplyConfig(IssM2mIspLink_Obj * pObj,
                                   UInt32 chId,
                                   UInt32 passId,
                                   Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]
                                   );

Int32 IssM2mIspLink_drvUpdateAwbResults(
        IssM2mIspLink_Obj *pObj,
        Void *pParams);
Int32 IssM2mIspLink_drvUpdateWdrMergeParams(
        IssM2mIspLink_Obj *pObj,
        Void *pParams);

static inline Bool IssM2mIspLink_isWdrMode(IssM2mIspLink_OperatingMode opMode);

static inline Bool IssM2mIspLink_isWdrMode(IssM2mIspLink_OperatingMode opMode)
{
    Bool isWdrMode = (Bool)FALSE;

    if ((ISSM2MISP_LINK_OPMODE_2PASS_WDR == opMode) ||
        (ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED == opMode))
    {
        isWdrMode = (Bool)TRUE;
    }

    return (isWdrMode);
}


Int32 IssM2mIspLink_drvApplyRszConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyCnfConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyGlbceConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyH3aConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyIpipeConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyIpipeifConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyNsf3vConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyIsifConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvApplyConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_drvSetDrvParams(IssM2mIspLink_Obj * pObj,
                                    UInt32 chId,
                                    UInt32 passId);

Int32 IssM2mIspLink_drvSetPassConfigParams(IssM2mIspLink_Obj *pObj,
                                        UInt32 chId,
                                        UInt32 passId);

Int32 IssM2mIspLink_drvCreateDrv(IssM2mIspLink_Obj *pObj,
                                  UInt32             chId,
                                  UInt32             passId
                                  );

Int32 IssM2mIspLink_drvAllocFrames(IssM2mIspLink_Obj * pObj);
Int32 IssM2mIspLink_drvCreateOutObj(IssM2mIspLink_Obj  *pObj);
Int32 IssM2mIspLink_drvDeleteOutObj(IssM2mIspLink_Obj  *pObj);
Int32 IssM2mIspLink_drvFreeFrames(IssM2mIspLink_Obj * pObj);
Int32 IssM2mIspLink_drvDeleteChObj(IssM2mIspLink_Obj * pObj);
Int32 IssM2mIspLink_drvCreate(IssM2mIspLink_Obj          * pObj,
                              const IssM2mIspLink_CreateParams * pPrm);
Int32 IssM2mIspLink_drvDelete(IssM2mIspLink_Obj * pObj);
Int32 IssM2mIspLink_drvCreateChObj(IssM2mIspLink_Obj * pObj);

Int32 IssM2mIspLink_drvProcessFrame(
    IssM2mIspLink_Obj *pObj,
    const System_Buffer *pInputBuffer,
    System_Buffer     *pOutputBuffer[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM],
    UInt32             passId);

Void IssM2mIspLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);
Int32 IssM2mIspLink_tskRun(IssM2mIspLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg);

Int32 IssM2mIspLink_drvSaveContext(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);
Int32 IssM2mIspLink_drvRestoreContext(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM]);

Int32 IssM2mIspLink_allocContextBuffer(IssM2mIspLink_Obj * pObj);
Void IssM2mIspLink_freeContextBuffer(IssM2mIspLink_Obj * pObj);
Int32 IssM2mIspLink_drvSaveFrame(IssM2mIspLink_Obj *pObj, UInt32 chId);
Int32 IssM2mIspLink_drvGetSaveFrameStatus(IssM2mIspLink_Obj *pObj,
                    IssM2mIspLink_GetSaveFrameStatus *pPrm);
Int32 IssM2mIspLink_updateTapParams(
    IssM2mIspLink_Obj *pObj, const IssM2mIspLink_IspOutputTapParams *pTapPrms);
Int32 IssM2mIspLink_drvSetIspRouteCfg(IssM2mIspLink_Obj *pObj,
                                       const IssM2mIspLink_RouteCfg *pRouteCfg);

#endif

/* @} */
