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
 *   \ingroup FRAMEWORK_MODULE_API
 *   \defgroup NULL_LINK_API Null Link API
 *
 *   Null Link can be used to take input from a link and then without doing
 *   anything return it back to the same link. This useful when a link output
 *   cannot be given to any other link for testing purpose we just want to run
 *   a given link but not really use the output. In such cases the output queue
 *   of link can be connected to a Null link. The null link will operate like
 *   any other link from interface point of view. But it wont do anything with
 *   the frames it gets. It will simply return it back to the sending link.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file nullLink.h
 *
 * \brief Null link API public header file.
 *
 * \version 0.0 (Jul 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef NULL_LINK_H_
#define NULL_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/networkCtrl_if.h>
#include <include/link_api/system.h>
/* @{ */

/**

*******************************************************************************
 *
 * \brief Max output queues supported by Null Link
 *
 * SUPPORTED in ALL platforms
 *

*******************************************************************************
*/
#define NULL_LINK_MAX_IN_QUE        (4U)

/* @} */

/**
 ******************************************************************************
 * \brief Null link data Copy types.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef enum {
    NULL_LINK_COPY_TYPE_NONE = 0U,
    /**< No dumping enabled */
    NULL_LINK_COPY_TYPE_2D_MEMORY = 1U,
    /**< For dumping video frames to memory. This uses the DMA driver */
    NULL_LINK_COPY_TYPE_BITSTREAM_MEMORY = 2U,
    /**< For dumping bitstream to memory. This uses CPU based memcpy */
    NULL_LINK_COPY_TYPE_FILE = 3U,
    /**< For dumping bitstream to file. This uses CPU based memcpy */
    NULL_LINK_COPY_TYPE_FORCE32BITS = 0x7FFFFFFFU
    /**< To make sure enum is 32 bits */
}NullLink_CopyType;

/******************************************************************************
 *
 *  Data structures
 *
*******************************************************************************
*/

/**
 ******************************************************************************
 * \brief Null link configuration parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32  numInQue;
    /**< Number of input queues */

    System_LinkInQueParams   inQueParams[NULL_LINK_MAX_IN_QUE];
    /**< Input queue information */

    NullLink_CopyType  dumpDataType;
    /**< Copies frames captured by NULL link to pre-defined location in DDR
     *   memory.
     *
     *   User can then via CCS save those frames to Host PC.
     *
     *   Frames will be copied one after other in a cricular manner in
     *   the memory segment specified
     *   via dumpFramesMemoryAddr, dumpFramesMemorySize.
     *
     *   Only Video frames will dumped to memory.
     *   Only CH0 from input que 0 will be dumped to memory.
     */

    UInt8*  dumpFramesMemoryAddr;
    /**< Valid only when dumpDataType is
     *   COPY_TYPE_2D_MEMORY or COPY_TYPE_BITSTREAM_MEMORY
     *   Address in memory where the frames should be copied to
     */
    UInt32  dumpFramesMemorySize;
    /**< Valid only when dumpDataType is
     *   COPY_TYPE_2D_MEMORY or COPY_TYPE_BITSTREAM_MEMORY
     *   Size of memory into which the frames will be copied
     */

    char  nameDataFile[SYSTEM_MAX_CH_PER_OUT_QUE][260U];
    /**< Valid only when dumpDataType is COPY_TYPE_FILE
     *   File containing the stream data. This is a binary file.
     *   260 is filename size limit set by WIndows 7
     *   This file resides on local machine and used only for the purpose of
     *   debugging with CCS
     *   Note: File Write enabled for channels only from first inputQ (Q0)
     */

    Void (*appCb)(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg);
    /**< Application call back function which returns the full buffer */

    Void *appCbArg;
    /**< Application call back argument */

} NullLink_CreateParams;

/******************************************************************************
*  Functions Prototypes
*******************************************************************************
*/
static inline void NullLink_CreateParams_Init(NullLink_CreateParams *pPrm);

/******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief Null link register and init
 *
 *    - Creates link task
 *    - Registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 NullLink_init(void);


/**
*******************************************************************************
 *
 * \brief Null link de-register and de-init
 *
 *    - Deletes link task
 *    - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 NullLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Null link set default parameters for create time params
 *   This function does the following
 *      - memset create params object
 * \param  pPrm  [OUT]  NullLink Create time Params
 *
 *******************************************************************************
 */
static inline void NullLink_CreateParams_Init(NullLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(NullLink_CreateParams));

    pPrm->numInQue = 1U;
    pPrm->appCb = NULL;
    pPrm->appCbArg = NULL;

    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
