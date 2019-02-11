/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file issAewbIpncLink_priv.h ISS AEWB Link private API/Data
 *       structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Apr 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef _ISS_AEWBIPNCIPNC_LINK_PRIV_H_
#define _ISS_AEWBIPNCIPNC_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issIspConfiguration.h>
#include <include/link_api/issSimcopConfiguration.h>
#include <algorithmLink_issAewb.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>


#include <idcc.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */



/**
 *******************************************************************************
 *   \brief Max number of buffers
 *******************************************************************************
 */
#define ISS_AEWB1_LINK_MAX_NUM_OUTPUT    (3)


/**
 *******************************************************************************
 *   \brief Max number of input channels
 *******************************************************************************
 */
#define ISS_AEWB1_LINK_MAX_CH            (4)


/**
 *******************************************************************************
 *   \brief Max size of AEWB results
 *******************************************************************************
 */
#define ISS_AEWB1_LINK_MAX_BUF_SIZE      \
    (SystemUtils_align((sizeof(AlgorithmLink_IssAewbOutParams) + \
    sizeof(IssIspConfigurationParameters)), 128))



/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct {
    UInt16 window_data[8][8];
    UInt16 unsat_block_ct[8];
} AlgorithmLink_IssAwebAlgData;

typedef struct
{
    dcc_parser_input_params_t   dccInPrms;
    dcc_parser_output_params_t  dccOutPrms;
    IssIspConfigurationParameters ispCfgPrms;
    IssM2mSimcopLink_ConfigParams simcopCfgPrms;

    Ptr dccInBuf;
    Ptr dccOutBuf;
    UInt32 dccOutBufSize;

    UInt32 width, height;
} Dcc_Object;


typedef struct
{
    Int32 prevRgb2Rgb1Idx;
    Int32 prevRgb2Rgb2Idx;
    Int32 prevCnfIdx;
    Int32 prevNsf3vIdx;
    Int32 prev3dLutIdx;

    UInt32 analogGain;
    UInt32 colorTemp;
    UInt32 expTime;
} AlgorithmLnk_IssAewbChObj;

/**
 *******************************************************************************
 *
 *   \brief Structure containing algorithm link
 *          parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_IssAewbCreateParams algLinkCreateParams;

    System_LinkQueInfo inQueInfo;

    System_Buffer buffers[ISS_AEWB1_LINK_MAX_CH*ISS_AEWB1_LINK_MAX_NUM_OUTPUT];
    /**< System buffers to exchange data with next link */

    System_MetaDataBuffer metaDataBuffers[ISS_AEWB1_LINK_MAX_CH*ISS_AEWB1_LINK_MAX_NUM_OUTPUT];
    /**< Payload for the system buffers */

    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Queue*/

    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Queue */

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
    Void *algHndl[ISS_AEWB1_LINK_MAX_CH];
    /**< Handle to the Algorithm */

    Dcc_Object dccObj;

    /* Keep track of last AE/AWB outputs so that they can be used in DCC */
    AlgorithmLink_IssAewb2AParams aewbOut[ISS_AEWB1_LINK_MAX_CH];
    BspOsal_SemHandle             lock;
    /**< Semaphore to protect #aewbOut parameters */

    AlgorithmLnk_IssAewbChObj      chObj[ISS_AEWB1_LINK_MAX_CH];
} AlgorithmLink_IssAewbObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_issAewb2Create(void * pObj,
                                              void * pCreateParams);
Int32 AlgorithmLink_issAewb2Process(void * pObj);
Int32 AlgorithmLink_issAewb2Control(void * pObj, void * pControlParams);
Int32 AlgorithmLink_issAewb2Stop(void * pObj);
Int32 AlgorithmLink_issAewb2Delete(void * pObj);
Int32 AlgorithmLink_issAewb2PrintStatistics(void *pObj,
                AlgorithmLink_IssAewbObj *pIssAewbObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
