/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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

/*
 *******************************************************************************
 *
 * EDMA utility functions
 *
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  edma_utils_autoincrement_v2.h
 *
 * @brief    This is the interface of using autoincrement utility when the hardware
 *              doesn't support alias view of memory.
 *
 * @remarks
 *              In this use case we allocate and configure EDMA channels based on
 *              user provided transfer properties. All index increments are taken care internally.
 *              Ping pong buffer is handled internally by this utility for the cases where hardware
 *              doesn't support alias view of memory.
 *
 * @remarks
 *              User can have multiple contexts for this usecase. Each context describing different transfer.
 *              It is expected that user will either configure all the channels in one shot or first allocate
 *              IN transfer folllowed by OUT transfer. The behavior is undefined for the cases where OUT
 *              transfers are configured even before configuring IN transfer. Also it is not expected that
 *              for a given context user configure IN and OUT transfer multiple number of times.
 *
 * @remarks Following is a standard sequence of operation user is expected to do
 *      EDMA_UTILS_autoIncrement_getContextSize_v2 : To get the size of internal memory needed
 *                          by auto increment util function. User is expected to allocate this memory and
 *                          give it as an input to all util API's
 *
 *      EDMA_UTILS_autoIncrement_init_v2(edmaContext, initParams);
 *
 *      EDMA_UTILS_autoIncrement_configure_v2(edmaContext, transferType);
 *
 *      EDMA_UTILS_autoIncrement_triggerInChannel_v2(edmaContext);
 *
 *      EDMA_UTILS_autoIncrement_waitInChannel_v2(edmaContext);
 *
 *      and so on .....
 *
 *@remarks In this particular implementation we are assuming that roiWidth and roiHeight are
 *                 multiple of blkWidth and blkHeight respectively
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Mar 2017) : First version of eve edma utils function
 *
 *****************************************************************************
 */


#ifndef EDMA_UTILS_AUTOINCREMENT_V2_H_
#define EDMA_UTILS_AUTOINCREMENT_V2_H_

/*#pragma CHECK_MISRA ("none")*/
#include <stdint.h>
#include "edma_utils_autoincrement.h"
/*#pragma RESET_MISRA ("required")*/

/** ========================================================
 *  @name   EDMA_UTILS_autoIncrement_initParam_v2
 *
 *  @desc   This structure specifies the parameter to configure
 *          auto increment related properties.
 *
 *  @field  initParams
 *              Initparams for the utility. Kindly refer EDMA_UTILS_autoIncrement_initParam
 *              in "edma_utils_autoincrement.h" for details of each parameter
 *
 *  @field  pingPongOffset
 *              Offset in bytes between the ping and pong buffer
 *
 *  ===============================================================
 */
typedef struct
{
    EDMA_UTILS_autoIncrement_initParam initParams;
    uint32_t   pingPongOffset;
}EDMA_UTILS_autoIncrement_initParam_v2;


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_getContextSize_v2
 *
 *  @desc     This function returns the size of the EDMA UTILS autoincrement handle. User is
 *                 then expected to allocate this memory and provide it to EDMA UTILS autoincrement
 *                 function as an input
 *
 *  @modif    NONE
 *
 *  @inputs   NONE
 *
 *  @outputs NONE
 *
 *  @return    Size of the EDMA UTILS context in bytes
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_getContextSize_v2(void);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_init_v2
 *
 *  @desc     This function initializes the EDMA UTILS context for autoincrement usecase.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *                  initParams :
 *                          Pointer to structure describing init configuration for the EDMA transfer. Refer
 *                          EDMA_UTILS_autoIncrement_initParam_v2 for details.
 *
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_init_v2(void * autoIncrementContext , const EDMA_UTILS_autoIncrement_initParam_v2 * initParamsV2);


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_configure
 *
 *  @desc   This function configures autoincrement usecase. This function can be called
 *               separately for IN and OUT channels or can also be called together for both INOUT channel.
 *              This functions behavior is undefined if you configure OUT trasnfer first followed by IN channel
 *              or if you configure IN and OUT transfer multiple number of times
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *                  transferType :
 *                           Type of transfer that you want to configure ( IN, OUT or INOUT)
 *                           Refer to EDMA_UTILS_TRANSFER_TYPE enum for valid values
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_configure_v2(void * autoIncrementContext , uint32_t transferType);


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_update
 *
 *  @desc   This function updates a certain set of parameters of autoincrement usecase.
 *               This function can only be called after EDMA_UTILS_autoIncrement_configure
 *               has been called. Size of array update param should be same as what has already been
 *               configured for IN, OUT or INOUT transfer in EDMA_UTILS_autoIncrement_configure otherwise
 *               this function will return an error. This function only updates the internal context and not actually
 *              update the param set. Param set is updated when the next frame starts.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *                  updateParams :
 *                          Pointer to the array of params set that needs to be updated for IN, OUT or INOUT transfer.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_update_v2(void * autoIncrementContext, const EDMA_UTILS_autoIncrement_updateParams *updateParams);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_triggerInChannel
 *
 *  @desc   This function triggers all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_triggerInChannel_v2(void * autoIncrementContext);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_triggerOutChannel
 *
 *  @desc   This function triggers all Output channels together. It also indicates when the last
 *              block is reached in the ROI given by user.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *                  1 : Last Block in auto increment
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_triggerOutChannel_v2(void * autoIncrementContext);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_waitInChannel
 *
 *  @desc   This function waits for all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_waitInChannel_v2(void * autoIncrementContext);


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_waitOutChannel
 *
 *  @desc   This function waits for all output channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_waitOutChannel_v2(void * autoIncrementContext);


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_deconfigure
 *
 *  @desc   This function deconfigures autoincrement usecase and releases all the allocated EDMA resources.
 *          This function can be called separately for IN and OUT channels or can also be called together
 *         for both INOUT channel. This functions behavior is undefined if you configure OUT trasnfer
 *          first followed by IN channel or if you configure IN and OUT transfer multiple number of times.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected tobe allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *                  transferType :
 *                           Type of transfer that you want to configure ( IN, OUT or INOUT)
 *                           Refer to EDMA_UTILS_TRANSFER_TYPE enum for valid values
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_deconfigure_v2(void * autoIncrementContext , uint32_t transferType);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_isDone
 *
 *  @desc   This function checks for the DMA transfer to be completed or not.
 *          It can be used for any of the above trigger.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  transferType :
 *                           Type of transfer that you want to configure ( IN, OUT or INOUT)
 *                           Refer to EDMA_UTILS_TRANSFER_TYPE enum for valid values
 *
 *  @outputs NONE
 *
 *  @return    0 : Transfer not completed
 *             1 : Transfer completed
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_isDone_v2(void * autoIncrementContext, uint32_t transferType);

#endif /*#define EDMA_UTILS_AUTOINCREMENT_V2_H_*/

