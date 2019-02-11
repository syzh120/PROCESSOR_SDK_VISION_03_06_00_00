/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/



/**
 *  @file       ibamalgtypes.h
 *
 *  @brief      This header defines types & constants shared by all implementations
 *              of the "generic" algorithm interface.
 */

#ifndef ti_BAMALGYPES_
#define ti_BAMALGYPES_

#ifdef __cplusplus
extern "C"
{
#endif

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")
#include "bam.h"

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation is allowed because none of the type names listed in this file startingwith _ conflicts with any language entity*/

    /**
     * CONSTANTS
     */
#define IBAMALG_TRUE                        1                       /**< IBAMALG Logical TRUE */
#define IBAMALG_FALSE                       0                       /**< IBAMALG Logical TRUE */
#define IBAMALG_NULL                        ((void *)0)             /**< IBAMALG NULL Pointer */

#define IBAMALG_E_BASE                      (BAM_E_BASE)            /**< IABAMALG error base*/
#define IBAMALG_S_SUCCESS                   (BAM_S_SUCCESS)         /**< IABAMALG error code showing success*/
#define IBAMALG_E_FAIL                      (BAM_E_FAIL)            /**< IABAMALG error code showing failure*/
#define IBAMALG_E_FAIL_RUNTIME              (BAM_E_FAIL_RUNTIME)    /**< IABAMALG error code showing runtime failure*/
#define IBAMALG_E_EUNSUPPORTED              (BAM_E_EUNSUPPORTED)    /**< IABAMALG error code showing unsupported feature*/

#define IBAMALG_E_CUSTOMFAILEND             (BAM_E_CUSTOMFAILEND)               /**< IABAMALG error code showing custom featuer failure*/
#define IBAMALG_E_INVALID_MEM_SIZE          (BAM_E_INVALID_MEM_SIZE)            /**< IABAMALG error code showing invalid memory size*/
#define IBAMALG_E_INVALID_PTR               (BAM_E_INVALID_PTR)                 /**< IABAMALG error code showing invalid memory pointer*/
#define IBAMALG_E_INVALID_NODE_INDEX        (BAM_E_INVALID_NODE_INDEX)          /**< IABAMALG error code showing invalid node index*/
#define IBAMALG_E_INVALID_NODE_COUNT        (BAM_E_INVALID_NODE_COUNT)          /**< IABAMALG error code showing invalid node count*/
#define IBAMALG_E_INVALID_STATUS            (BAM_E_INVALID_STATUS)              /**< IABAMALG error code showing invalid graph handle status*/
#define IBAMALG_E_INVALID_NODE_TYPE         (BAM_E_INVALID_NODE_TYPE)           /**< IABAMALG error code showing invalid node type*/
#define IBAMALG_E_INVALID_DATA_BLOCK_INDEX  (BAM_E_INVALID_DATA_BLOCK_INDEX)    /**< IABAMALG error code showing invalid data block index*/
#define IBAMALG_E_INVALID_DATA_BLOCK_DIR    (BAM_E_INVALID_DATA_BLOCK_DIR)      /**< IABAMALG error code showing invalid datablock direction*/


    /**
     * Commands for control calls. Add additional commands as required in your platform specific file.
     */
#define IBAMALG_CMD_GETSTATUS           (IBAMALG_S_SUCCESS+1)   /**< Control call command for get status */
#define IBAMALG_CMD_SETPARAMS           (IBAMALG_S_SUCCESS+2)   /**< Control call command for set params */
#define IBAMALG_CMD_RESET               (IBAMALG_S_SUCCESS+3)   /**< Control call command for reset */
#define IBAMALG_CMD_SETDEFAULT          (IBAMALG_S_SUCCESS+4)   /**< Control call command for set default */
#define IBAMALG_CMD_FLUSH               (IBAMALG_S_SUCCESS+5)   /**< Control call command for flush */
#define IBAMALG_CMD_GETBUFINFO          (IBAMALG_S_SUCCESS+6)   /**< Control call command for get buffer info */
#define IBAMALG_CMD_GETVERSION          (IBAMALG_S_SUCCESS+7)   /**< Control call command for get version */

    /**
     * MemTab definition
     */
    typedef  BAM_MemRec IBAMALG_MemRec;

    /**
     *  @brief      Defines the creation time parameters for
     *              all IBAMALG instance objects.
     *
     *  @remarks Add other elelemts to your algorithm structure as per need.
     *              only requirement to be compatible with this is that the first element is size
     *              of that struct itself.
     */
    typedef struct _ibamalg_params
    {
        uint32_t size; /**< Number of MAU in the structure */
    } IBAMALG_Params;
    
    /**
     *  @brief      Pointer to algorithm specific buffer structure.
     *
     *  @remarks    All algorithm argument structures <b>must</b> have size of that struct
     *              as their first element.
     *
     *  @remarks Add other elelemts to your algorithm structure as per need.
     *              only requirement to be compatible with this is that the first element is size
     *              of that struct itself.
     */
    typedef BAM_InBufs IBAMALG_InBufs;

    /**
     *  @brief      Pointer to algorithm specific buffer structure.
     *
     *  @remarks    All algorithm argument structures <b>must</b> have size of that struct
     *              as their first element.
     *
     *  @remarks Add other elelemts to your algorithm structure as per need.
     *              only requirement to be compatible with this is that the first element is size
     *              of that struct itself.
     */
    typedef BAM_OutBufs IBAMALG_OutBufs;
    
    /**
     *  @brief      Pointer to algorithm specific argument structure.
     *
     *  @remarks    All algorithm argument structures <b>must</b> have size of that struct
     *              as their first element.
     *
     *  @remarks Add other elelemts to your algorithm structure as per need.
     *              only requirement to be compatible with this is that the first element is size
     *              of that struct itself.
     */
    typedef BAM_InArgs IBAMALG_InArgs;

    /**
     *  @brief      Pointer to algorithm specific argument structure.
     *
     *  @remarks    All algorithm argument structures <b>must</b> have size of that struct
     *              as their first element.
     *
     *  @remarks Add other elelemts to your algorithm structure as per need.
     *              only requirement to be compatible with this is that the first element is size
     *              of that struct itself.
     */
    typedef BAM_OutArgs IBAMALG_OutArgs;

    /**
     *  @brief      This structure defines the codec parameters that can be
     *              modified after creation via control() calls.
     *
     *  @remarks    It is not necessary that a given implementation support all
     *              dynamic parameters to be configurable at run time.  If a
     *              particular algorithm does not support run-time updates to
     *              a parameter that the application is attempting to change
     *              at runtime, it may indicate this as an error.
     *
     *  @remarks Add other elelemts to your algorithm structure as per need.
     *              only requirement to be compatible with this is that the first element is size
     *              of that struct itself.
     *
     *  @sa         IBAMALG_Fxns::control()
     */
    typedef struct _ibamalgs_controlparams
    {
        uint32_t size; /**< sizeField */
    } IBAMALG_ControlParams;

    /**
     * Buffer descriptor list
     */
    typedef BAM_BufDesc IBAMALG_BufDesc;

    /**
     * Buffer descriptor list
     */
    typedef BAM_BufDescList IBAMALG_BufDescList;

    /**
     *  @brief      A generic buffer descriptor
     *
     *  @remarks    None
     */
    typedef struct _ibamalg_bufsizelist
    {
        BAM_BufSize *bufSize; /**< Descriptor for Size of the buffer             */
        uint32_t numBufs;     /**< Number of buffers in the list */
        uint32_t reserved[2]; /**< reserved for later use */
    } IBAMALG_BufSizeList;


    /**
     *  @brief      Buffer information descriptor for input and output buffers.
     */
    typedef struct _ibamalg_algbufinfo
    {
        uint32_t size;                  /**< Number of MAU in the structure */
        uint32_t reserved[2];           /**< reserved for later use */
        IBAMALG_BufSizeList inBufSize;  /**< List of input buffer sizes */
        IBAMALG_BufSizeList outBufSize; /**< List of output buffer sizes */
    } IBAMALG_AlgBufInfo;


    /**
     *  @brief      Defines instance status parameters (read-only).
     *
     *  @remarks
     *
     *  @sa         IBAMALG_Fxns::control()
     */
    typedef struct _ibamalg_status
    {
        uint32_t size; /**< Number of MAU in the structure */
        int32_t extendedError; /**< extendedErrorField */
        void *status; /**< Status field. Type depends on the command to control call: */
        /**IBAMALG_GETBUFINFO: IBAMALG_AlgBufInfo* */
        /**< Unspecified for other commands - left to the specific algorithm to specify */
        uint32_t reserved[2];
    } IBAMALG_Status;

/* RESET_MISRA("20.2")  -> Reset rule 20.2*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_IBAMALG_TYPES_ */

