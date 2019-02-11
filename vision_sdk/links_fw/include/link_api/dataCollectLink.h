/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
 *   \ingroup FRAMEWORK_MODULE_API
 *   \defgroup DATA_COLLECT_LINK_API DataCollect Link API
 *
 *   DataCollect Link can be used to take input from a link and then without doing
 *   anything return it back to the same link. This useful when a link output
 *   cannot be given to any other link for testing purpose we just want to run
 *   a given link but not really use the output. In such cases the output queue
 *   of link can be connected to a DataCollect link. The dataCollect link will operate like
 *   any other link from interface point of view. But it wont do anything with
 *   the frames it gets. It will simply return it back to the sending link.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file dataCollectLink.h
 *
 * \brief DataCollect link API public header file.
 *
 * \version 0.0 (Jul 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef DATA_COLLECT_LINK_H_
#define DATA_COLLECT_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/system.h>

/* @{ */

/**
*******************************************************************************
 *
 * \brief Max output queues supported by DataCollect Link
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
#define DATA_COLLECT_LINK_MAX_IN_QUE        (1U)

/**
*******************************************************************************
 *
 * \brief Max file path/name length supported supported by DataCollect Link
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
#define DATA_COLLECT_LINK_MAX_LENGTH        (256U)

/**
*******************************************************************************
 *
 * \brief Max number of Radars supported by DataCollect Link
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
#define DATA_COLLECT_LINK_MAX_NUM_FILES     (4U)

/* @} */

/**
 *******************************************************************************
 * \brief Command to pause data collection
 *******************************************************************************
*/
#define DATA_COLLECT_LINK_CMD_PAUSE         (0x1000)

/**
 *******************************************************************************
 * \brief Command to resume data collection
 *******************************************************************************
 */
#define DATA_COLLECT_LINK_CMD_RESUME        (0x1001)

/**
 ******************************************************************************
 * \brief DataCollect link data Copy types.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef enum {
    DATA_COLLECT_LINK_COPY_TYPE_NONE = 0U,
    /**< No dumping enabled */
    DATA_COLLECT_LINK_COPY_TYPE_FILE = 1U,
    /**< For dumping video frames to file */
     DATA_COLLECT_LINK_COPY_TYPE_FORCE32BITS = 0x7FFFFFFFU
    /**< To make sure enum is 32 bits */
}DataCollectLink_CopyType;

/******************************************************************************
 *
 *  Data structures
 *
*******************************************************************************
*/

/**
 ******************************************************************************
 * \brief DataCollect link configuration file buffer parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt8 *pConfigBuf;
    UInt32 bufSize;
} DataCollectLink_ConfigBufParams;

/**
 ******************************************************************************
 * \brief DataCollect link configuration parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32  numInQue;
    /**< Number of input queues */

    System_LinkInQueParams   inQueParams;
    /**< Input queue information */

    //! Specifies data collection mode, only FILE and NONE are currently supported
    DataCollectLink_CopyType  dumpDataType;

    //! Configuration option to disable saving data that arrives on a particular input channel
    UInt32 disableChannel[SYSTEM_MAX_CH_PER_OUT_QUE];

    UInt32 enableLumaOnlyDump;
    /**< For YUV420SP data format, only write luma data */

    char filePath[DATA_COLLECT_LINK_MAX_LENGTH];
    /**< Path on disk where files will stored. File name are auto generated by the link */

    DataCollectLink_ConfigBufParams configBufParams[DATA_COLLECT_LINK_MAX_NUM_FILES];
    /**< Configuration files on disk to be stored along with data */

    UInt32 numConfigFiles;
    /**< Number of Configuration files to be saved */

} DataCollectLink_CreateParams;

/******************************************************************************
*  Functions Prototypes
*******************************************************************************
*/
static inline void DataCollectLink_CreateParams_Init(DataCollectLink_CreateParams *pPrm);

/******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief DataCollect link register and init
 *
 *    - Creates link task
 *    - Registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DataCollectLink_init(void);


/**
*******************************************************************************
 *
 * \brief DataCollect link de-register and de-init
 *
 *    - Deletes link task
 *    - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DataCollectLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief DataCollect link set default parameters for create time params
 *   This function does the following
 *      - memset create params object
 * \param  pPrm  [OUT]  DataCollectLink Create time Params
 *
 *******************************************************************************
 */
static inline void DataCollectLink_CreateParams_Init(DataCollectLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(DataCollectLink_CreateParams));

    pPrm->numInQue = 1U;
    pPrm->enableLumaOnlyDump = 0U;

    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
