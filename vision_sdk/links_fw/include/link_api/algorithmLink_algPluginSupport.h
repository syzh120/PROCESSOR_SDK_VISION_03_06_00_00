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
 * \ingroup FRAMEWORK_MODULE_API
 * \defgroup ALGORITHM_LINK_PLUGIN_INTERFACE Algorithm Plugin API
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_algPluginSupport.h Algorithm Link Plugin Interface
 *       API/Data structures
 *
 * \brief  This header file has definitions for function API and data structures
 *         which will be used by the Algorithm plugin functions to interact
 *         with the algorithm link skeletal implementation
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_ALGPLUGININTERFACE_H_
#define ALGORITHM_LINK_ALGPLUGININTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/system_inter_link_api.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Alignment for algorithm link object
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ALGORITHMLINK_OBJ_ALIGN     (SYSTEM_BUFFER_ALIGNMENT)

/**
 *******************************************************************************
 *
 *   \brief Alignment for algorithm link frames
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ALGORITHMLINK_FRAME_ALIGN     (SYSTEM_BUFFER_ALIGNMENT)

/**
 *******************************************************************************
 *
 *   \brief Threshold size of a memory request, beyond which it will be
 *          allocated in shared region instead of heap
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ALGORITHMLINK_SRMEM_THRESHOLD (2000)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the mode of algorithm Queues
 *
 *          This enumeration applies to both input and output queues
 *******************************************************************************
*/
typedef enum
{
    ALGORITHM_LINK_QUEUEMODE_NOTINPLACE = 0,
    /**< Buffers in this queue will NOT be operated in in-place mode.
     *   For input queue, it means that buffers in this mode will be READ only
     *   For output queue, it means that buffers in this queue is owned by
     *    the same link and NOT coming from previous link.
     */
    ALGORITHM_LINK_QUEUEMODE_INPLACE = 1,
    /**< Buffers in this queue will be operated in in-place mode.
     *   For input queue, it means that buffers in this mode will be edited
     *    and passed onto next link
     *   For output queue, it means that buffers in this queue is NOT owned by
     *    the same link and is coming from previous link.
     */
    ALGORITHM_LINK_QUEUEMODE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmLink_QueueMode;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the Algorithm link Input Q information
 *
 *          In algorithm link, due to possibility of INPLACE computation and
 *          due to possibility of algorithm locking a buffer, buffer exchange
 *          is little more involved. To facilitate the book keeping, some
 *          info about input Q is stored in this structure.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_QueueMode qMode;
    /**< Mode of queue - inplace vs non-inplace */
} AlgorithmLink_InputQueueInfo;

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the Algorithm link Output Q information
 *
 *          In algorithm link, due to possibility of INPLACE computation and
 *          due to possibility of algorithm locking a buffer, buffer exchange
 *          is little more involved. To facilitate the book keeping, some
 *          info about output Q is stored in this structure.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_QueueMode qMode;
    /**< Mode of queue - inplace vs non-inplace */
    System_LinkQueInfo queInfo;
    /**< Parameters of the output Q */
    Int32 inputQId;
    /**<  Input queue Id from which this output Q got populated
     *    Values in this structure are used only in INPLACE computation
     *    scenarios. Otherwise values are don't care.
     */
    System_LinkInQueParams inQueParams;
    /**<  Input queue information.
     *    Values in this structure are used only in INPLACE computation
     *    scenarios. Otherwise values are don't care.
     */
} AlgorithmLink_OutputQueueInfo;


/**
 *******************************************************************************
 *
 * \brief Callback function implemented by plugin to receive empty buffers from
 *        next link.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId for which buffers are received.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
typedef Int32 (*AlgorithmLink_AlgPluginPutEmptyBuffers)(
                                    Void              *ptr,
                                    UInt16             queId,
                                    System_BufferList *pBufList);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link plugin functions
 *
 *          This structure contains plugin function pointers to be called for
 *          a given algorithm. These functions will be called from the algorithm
 *          link skeletal implementation
 *
 *******************************************************************************
*/
typedef struct
{
    Int32 (*AlgorithmLink_AlgPluginCreate)(void * pObj, void * pPrm);
    /**< Plug in function which will perform algorithm instance creation */
    Int32 (*AlgorithmLink_AlgPluginProcess)(void * pObj);
    /**< Plug in function which will process new data. Internally it
     *   will call the process function of the algorithm.
     */
    Int32 (*AlgorithmLink_AlgPluginControl)(void * pObj, void * pPrm);
    /**< Plug in function which will perform Control (Configuration) of the
     *   algorithm. Internally it will call the control function of the
     *   algorithm.
     */
    Int32 (*AlgorithmLink_AlgPluginStop)(void * pObj);
    /**< Plug in function which will perform all functionality which needs to be
     *   done at the end of algorithm. Example: If any buffers are locked inside
     *   the algorithm, they can be flushed in this function.
     */
    Int32 (*AlgorithmLink_AlgPluginDelete)(void * pObj);
    /**< Plug in function which will perform algorithm instance deletion */
} AlgorithmLink_FuncTable;

/*******************************************************************************
 *  Algorithm Link Plugin Support Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Algorithm link register plugin
 *
 *          Each algorithm will have the corresponding plugin functions for
 *          create, process, control, stop, delete.
 *          These plugin functions will be registered in the algorithm link
 *          function table via this API.
 *
 *   \param algId               [IN] Algorithm Id
 *   \param pPluginFuncs        [IN] Pointer to struct of plugin functions
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_registerPlugin(Int32 algId,
                                   const AlgorithmLink_FuncTable *pPluginFuncs);

/**
 *******************************************************************************
 *
 *   \brief Set SafetyMode for Algorithm link
 *          Optional to call this API, default all algos will get
 *          full permissions BSP_SAFETY_OSAL_MODE_ASIL
 *
 *   \param algId               [IN] Algorithm Id
 *   \param safetyMode          [IN] BSP_SAFETY_OSAL_MODE_ASIL or
 *                                   BSP_SAFETY_OSAL_MODE_QM
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_setPluginFFIMode(UInt32 algId, UInt32 safetyMode);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link queue initializations, which need to be done at the
 *          algorithm creation time
 *
 *          Several book keeping operations are needed for buffer handling.
 *          Initializations needed for them are done in this function.
 *
 *   \param ptr                [IN] Alg link object
 *   \param numInputQUsed      [IN] Number of input queues used
 *   \param pInputQInfo        [IN] Pointer to base element of inputQInfo array
 *   \param numOutputQUsed     [IN] Number of output queues used
 *   \param pOutputQInfo       [IN] Pointer to base element of outputQInfo array
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_queueInfoInit(
                void                                *ptr,
                UInt32                               numInputQUsed,
                const AlgorithmLink_InputQueueInfo  *pInputQInfo,
                UInt32                               numOutputQUsed,
                const AlgorithmLink_OutputQueueInfo *pOutputQInfo);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link returns pointer to algorithm specific parameters obj
 *
 *   \param ptr                [IN] Alg link object
 *
 *   \return  (void *) pointer to algorithm specific parameters obj
 *
 *******************************************************************************
*/
void * AlgorithmLink_getAlgorithmParamsObj(void * ptr);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link records the pointer of algo specific parameters obj
 *
 *   \param ptr                 [IN] Alg link object
 *   \param pAlgObj             [IN] Pointer to algo specific parameters obj
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_setAlgorithmParamsObj(void * ptr, void * pAlgObj);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link function to put output buffer into empty local
 *          output Q
 *
 *          For each output Q, there will be an empty and Full output Q.
 *          Empty Q holds all output buffers which are empty (No data yet)
 *          Full Q holds all output buffers which are full (Data present)
 *          Plugin functions, at the time of buffer creation, need to call this
 *          API to put all the created buffers into the empty.
 *
 *   \param ptr                 [IN] Current link object
 *   \param outputQId           [IN] Output Que ID of current link
 *   \param pSystemBuffer       [IN] Pointer to system buffer to be put into Q
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_putEmptyOutputBuffer(void          *ptr,
                                         Int32          outputQId,
                                         System_Buffer *pSystemBuffer);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link function to get o.p buffer from empty local output Q
 *
 *          For each output Q, there will be an empty and Full output Q.
 *          Empty Q holds all output buffers which are empty (No data yet)
 *          Full Q holds all output buffers which are full (Data present)
 *          Plugin functions, at the time of process function, needs to call
 *          API to get an empty output buffer to put the processed data.
 *
 *   \param ptr                 [IN] Current link object
 *   \param outputQId           [IN] Output Que ID of current link
 *   \param channelId           [IN] Channel ID of the Que
 *   \param pSystemBuffer       [IN] Pointer to pointer of system buffer, which
 *                                   will get updated with System buffer
 *                                   address.
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_getEmptyOutputBuffer(void           *ptr,
                                         UInt32          outputQId,
                                         UInt32          channelId,
                                         System_Buffer **pSystemBuffer);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link function to put o.p buffer into Full output Q
 *
 *          For each output Q, there will be an empty and Full output Q.
 *          Empty Q holds all output buffers which are empty (No data yet)
 *          Full Q holds all output buffers which are full (Data present)
 *          Plugin functions, at the time of process function, needs to call
 *          this API to put a Full output buffer into output Q
 *
 *   \param ptr                 [IN] Current link object
 *   \param outputQId           [IN] Output Que ID of current link
 *   \param pSystemBuffer       [IN] Pointer to system buffer to be put into Q
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_putFullOutputBuffer(void          *ptr,
                                        Int32          outputQId,
                                        System_Buffer *pSystemBuffer);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link function to return empty input buffers to prev link
 *
 *          In algorithm link, returning empty input buffer to previous link
 *          depends on the mode of operation as follows.<BR>
 *          1) Non-Inplace: In this case, once the algorithm returns (frees up)
 *          input buffer, it can be returned to previous link.<BR>
 *          2) Inplace: In this case,  input buffer can be returned to previous
 *          link only after both the current link algorithm and next link
 *          algorithm free up the buffer.<BR>
 *          This function does the necessary book keeping to facilitate
 *          emtpy buffer return, in both the modes.
 *
 *          Note that algorithm plug in functions will have to call this
 *          function in cases of both Inplace and Non-Inplace computations.
 *
 *   \param ptr                [IN] Current link object
 *   \param inputQId           [IN] Input Que ID of current link
 *   \param prevLinkId         [IN] Link ID of previous link
 *   \param prevLinkQueId      [IN] Que ID of previous link
 *   \param pBufList           [IN] List of buffers released to previous link
 *   \param pBufDropFlag       [IN] Pointer to an array of flags. To indicate
 *                                  if this i.p buffer was used or dropped
 *                                  with out processing. Array of flags
 *                                  correspond to array of buffers in pBufList
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success, else error code
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_releaseInputBuffer(void              *ptr,
                                       UInt32             inputQId,
                                       UInt32             prevLinkId,
                                       UInt16             prevLinkQueId,
                                       System_BufferList *pBufList,
                                       const Bool        *pBufDropFlag);
/**
 *******************************************************************************
 *
 *   \brief Algorithm link function to return (free) output buffers
 *
 *          In algorithm link, releasing output buffer,
 *          depends on the mode of operation as follows <BR>
 *          1) Non-Inplace: In this case,  output buffer can be returned to
 *          empty buffer pool only after both the current link algorithm and
 *          next link algorithm free up the buffer. <BR>
 *          2) Inplace: In this case, once the next link returns (frees up)
 *          output buffer, it is passed onto input side of the current link.
 *          Only after current link alg releases it (As input buffer release),
 *          it can be returned to previous link. <BR>
 *          This function does the necessary book keeping to facilitate
 *          output buffer release, in both the modes.
 *
 *          Note that in case of Inplace computations, algorithm plugin
 *          functions should not call this function, since the buffer is
 *          expected to be released via releaseInputBuffer function.
 *
 *   \param ptr                [IN] Current link object
 *   \param outputQId          [IN] Output Q ID of current link
 *   \param pBufList           [IN] List of buffers released to previous link
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success, else error code
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_releaseOutputBuffer(void              *ptr,
                                        UInt32             outputQId,
                                        System_BufferList *pBufList);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link function to the Queued Count
 *
 *          This function is called to query the number of buffers
 *          enqueued in a queue
 *
 *   \param ptr                [IN] Current link object
 *   \param outputQId          [IN] Output Q ID of current link
 *   \param chId               [IN] chId of the buffer
 *
 *   \returns queuedCount
 *
 *******************************************************************************
 */

UInt32 AlgorithmLink_queGetQueuedCount(void *ptr, UInt32 outputQId, UInt32 chId);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link register plugin
 *
 *          This plugin function is called before frames are released
 *          to previous link
 *
 *   \param ptr                [IN] Current link object
 *   \param pPluginFunc        [IN] Pointer to plugin function
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AlgorithmLink_registerPutEmptyBuffersPlugin(
                     void  *ptr,
                     const  AlgorithmLink_AlgPluginPutEmptyBuffers pPluginFunc);

/**
 *******************************************************************************
 *
 *   \brief Algorithm link get Link Id
 *
 *          This plugin function is used to return the link id
 *          associated with the algorithm. This is used by the link stats.
 *
 *   \param ptr               [IN] Current link object
 *
 *   \return Id of the Link
 *
 *******************************************************************************
*/
UInt32 AlgorithmLink_getLinkId(void *ptr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
