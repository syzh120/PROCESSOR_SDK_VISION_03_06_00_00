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
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_ALG_FUNCTIONS APIs for setting the different algorithm
 *                                  functions.
 *
 * \brief  APIs definitions for the algorithm plugin functions to be registered
 *         with the algorithm plugin.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file alg_functions.h
 *
 * \brief  APIs definitions for the algorithm plugin functions to be registered
 *         with the algorithm plugin.
 *
 * \version 0.0 (Sept 2016) : [PG] First version
 *
 *******************************************************************************
 */

#ifndef ALG_FUNCTIONS_H_
#define ALG_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <include/alglink_api/algorithmLink_radarProcess.h>
#include <include/link_api/system_buffer.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
/** \brief Function pointer type definition which will preform the create
 *         operations corresponding to the algorithm function.
 *
 *  \param createParams Create Parameters corresponding to the algorithm
 *                      function.
 *
 *  \param opParams     These parameters are provided from the algorithm fxn to
 *                      the alg plugin to allow for the alg plugin to know
 *                      alg function specific requirements with respect to
 *                      output buffer size and type.
 *
 *  \return algHandle   This function is expected to allocate memory for the
 *                      algorithm handle. This handle is later used by the alg
 *                      function during process and delete calls.
 */
typedef void* (*AlgRadarProcessFxns_Create)(AlgorithmLink_RadarProcessCreateParams *createParams,
                                            AlgorithmLink_RadarProcessAlgCreateOpParams *opParams);

/** \brief Function pointer type definition which will perform the process
 *         operations corresponding to the algorithm function.
 *
 *  \param  alg_handle      Algorithm Handle which was created during the create
 *                          algorithm function call.
 *  \param  in_buf          Input buffer pointer.
 *  \param  out_buf         Output buffer pointer.
 *
 *  \return status          Status of the success or failure of the process
 *                          operations.
 */
typedef Int32 (*AlgRadarProcessFxns_Process)(void *alg_handle,
                                            System_Buffer *in_buf,
                                            System_Buffer *out_buf);

/** \brief Function pointer type definition which will perform the control
 *         operations corresponding to the algorithm function.
 *
 *  \param  alg_handle      Algorithm Handle which was created during the create
 *  \param  controlParams   Control parameters which can change the algorithm
 *                          parameters at run time.
 *
 *  \return status          Status of the success or failure of the control
 *                          operations.
 */
typedef Int32 (*AlgRadarProcessFxns_Control)(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams);

/** \brief Function pointer type definition which will perform the delete
 *         operations corresponding to the algorithm function.
 *
 *  \param  alg_handle  Algorithm Handle which was created during the create
 *                      algorithm function call.
 *
 *  \return status      Status of the success or failure of the process
 *                      operations.
 */
typedef Int32 (*AlgRadarProcessFxns_Delete)(void *alg_handle);

/** \brief  Function table that needs to be populated by the algorithm function
 *          This table is used by the alg plugin functions to call the alg_fxns.
 */
typedef struct {

    AlgRadarProcessFxns_Create alg_create;
    /**< Create function for the algorithm. Called once during usecase
     *   initialization and creation.
     */
    AlgRadarProcessFxns_Process alg_process;
    /**< Process function for the algorithm. Called in every frame for
     *   for processing.
     */
    AlgRadarProcessFxns_Control alg_control;
    /**< Control function for the algorithm. Called every time the control call
     *   is made for processing.
     */
    AlgRadarProcessFxns_Delete alg_delete;
    /**< Delete function for the algorithm. Called once during usecase
     *   deinitialization and delete.
     */
} AlgRadarProcessFxns_FxnTable;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
/** \brief Function to get the algorithm specific function pointers. This
 *         function is called from the alg plugin create function. User can
 *         modify the contents of this function (do not change the prototype)
 *         to add their own developed algorithm functions.
 *
 *  \param func_name    Name of the algorithm. This is passed to the alg plugin
 *                      using the create parameters of the algorithm plugin.
 *                      The same name is passed here to get the functions.
 *  \return fxnTbl      Pointer to the structure containing the function pointers
 *                      for #AlgRadarProcessFxns_FxnTable.
 */
AlgRadarProcessFxns_FxnTable * AlgRadarProcessFxns_get(char *func_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
