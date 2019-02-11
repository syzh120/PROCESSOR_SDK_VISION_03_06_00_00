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
 *  EDMA utility functions
 *
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  edma_utils_autoincrement_1d.h
 *
 * @brief       This file contains the data types and util function prototype for
 *              configuring EVE EDMA autoincrement 1D usecase.
 *
 * @remarks
 *              This usecase is aplicable only for 1D transfer and supports circular buffering
 *              ( ping-pong buffering).
 *
 * @remarks
 *              User can have multiple contexts for this usecase. Each context describing
 *              different transfer. It is expected that user will either configure all the
 *              channels in one shot or first allocate IN transfer folllowed by OUT transfer.
 *              The behavior is undefined for the cases where OUT transfers are configured
 *              even before configuring IN transfer. Also it is not expected that
 *              for a given context user configure IN and OUT transfer multiple number of times.
 *
 * @remarks Following is a standard sequence of operation user is expected to do
 *      EDMA_UTILS_autoIncrement1D_getContextSize : To get the size of internal memory needed
 *                          by auto increment util function. User is expected to allocate this memory and
 *                          give it as an input to all util API's
 *
 *      EDMA_UTILS_autoIncrement1D_init(edmaContext, initParams);
 *
 *      EDMA_UTILS_autoIncrement1D_configure(edmaContext, transferType);
 *
 *      // Pipe Up phase
 *      EDMA_UTILS_autoIncrement1D_triggerInChannel(autoIncrementContext);
 *      EDMA_UTILS_autoIncrement1D_waitInChannel(autoIncrementContext);
 *
 *      // Steady State Phase
 *      while ( status == 0)
 *      {
 *          status = EDMA_UTILS_autoIncrement1D_triggerOutChannel(autoIncrementContext);
 *          EDMA_UTILS_autoIncrement1D_triggerInChannel(autoIncrementContext);
 *
 *          EDMA_UTILS_autoIncrement1D_waitOutChannel(autoIncrementContext);
 *          EDMA_UTILS_autoIncrement1D_waitInChannel(autoIncrementContext);
 *
 *      }
 *
 *      // Pipe Down Phase
 *      status = EDMA_UTILS_autoIncrement1D_triggerOutChannel(autoIncrementContext);
 *      EDMA_UTILS_autoIncrement1D_waitOutChannel(autoIncrementContext);
 *
 *
 * @remarks In this particular implementation assumes that following equation results in an
 *          integer number :
 *              (totalLength - numBytes)/extMemIncrement is an integer
 *
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Nov 2013) : First version of eve edma utils autoincrement 1D function
 *
 *****************************************************************************
 */


#ifndef EDMA_UTILS_AUTOINCREMENT_1D_H_
#define EDMA_UTILS_AUTOINCREMENT_1D_H_

/*#pragma CHECK_MISRA ("none")*/
#include <stdint.h>
/*#pragma RESET_MISRA ("required")*/

/* Maximum number of auto increment transfers that can be configured */
#define NUM_MAX_TRANSFER_AUTOINCREMENT_1D 16

/** ======================= ============================
 *  @name   EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_TYPE
 *
 *  @desc   Describes the parameters that needs to be updated while using
 *          autoincrement update API (EDMA_UTILS_autoIncrement_update)
 *          User can create a mask with more than one fields of this enum
 *          by ORing these fields to update more than one parameters
 *
 *  ===============================================================
 */
typedef enum{
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_TOTALLENGTH       = (uint32_t)1U << 0U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_NUMBYTES          = (uint32_t)1U << 1U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMINCREMENT   = (uint32_t)1U << 2U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_INTMEMINCREMENT   = (uint32_t)1U << 3U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMPTR         = (uint32_t)1U << 4U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_INTERMEMPTR       = (uint32_t)1U << 5U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_NUMCIRCBUF        = (uint32_t)1U << 6U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_DMAQUENO          = (uint32_t)1U << 7U,
 EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_ALL               = 0xFFFFU
}EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_TYPE;


/** ========================================================
 *  @name   EDMA_UTILS_autoIncrement1D_transferProperties
 *
 *  @desc   This structure specifies the properties of the transfer for
 *          auto increment usecase.
 *
 *  @field totalLength
 *             Total Length of the 1D data in which auto increment is expected
 *             to rum
 *
 *  @field t numBytes
 *             Number of bytes of 1D data to be transferred per DMA trigger
 *
 *  @field extMemIncrement
 *              Increment in external memory. If extMemIncrement = 0
 *              then number of segments to be transfered is 1
 *
 *
 *  @field intMemIncrement
 *              Increment in internal memory.
 *
 *  @field extMemPtr
 *              Pointer to external memory buffer
 *
 *  @field interMemPtr
 *              Pointer to internal memory buffer.
 *              When using this autoincrement utility from BAM user need not provide
 *              this pointer as it is internally allocated by BAM and automatically
 *              gets set during setMemRec function
 *
 *  @field numCircBuf
 *              Number of buffers for circular buffering
 *
 *  @field dmaQueNo
 *              DMA Que number to which particular transfer is expected to go
 *
 *  ===============================================================
 */
typedef struct
{
    uint32_t    totalLength;
    uint16_t    numBytes;
    int16_t    extMemIncrement;
    int16_t    intMemIncrement;
    uint8_t     *extMemPtr;
    uint8_t     *interMemPtr;
    uint8_t     numCircBuf;
    uint8_t     dmaQueNo;
}EDMA_UTILS_autoIncrement1D_transferProperties;


/** ========================================================
 *  @name   EDMA_UTILS_autoIncrement1D_updateParams
 *
 *  @desc   This structure specifies the parameters which can be updated
 *              individually for autoincrement usecase using autoincrement
 *              update API EDMA_UTILS_autoIncrement1D_update for each transfer
 *
 *  @field extMemPtr
 *              Pointer to external memory buffer
 *
 *  @field transferTypes
 *              Type of the transfer you want to configure : IN, OUT or INOUT.
 *              Refer EDMA_UTILS_TRANSFER_TYPE for valid values
 *
 *  @field updateMask
 *              Mask to tell which all parameters needs to be updated. Refer
 *              EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_TYPE for valid values. For
 *              updating multiple fields use "|" (OR) operation.
 *
 *  @field updateParams
 *              Array of structure containing the parameter enteries to be updated. It is
 *              important to note that number of valid enteries in this structure should
 *              be same as what was configured during init time.

 *  ===============================================================
 */
typedef struct
{
    uint32_t transferType;
    uint32_t updateMask;
    EDMA_UTILS_autoIncrement1D_transferProperties updateParams[NUM_MAX_TRANSFER_AUTOINCREMENT_1D];
}EDMA_UTILS_autoIncrement1D_updateParams;


/** ========================================================
 *  @name   EDMA_UTILS_autoIncrement1D_configParam
 *
 *  @desc   This structure specifies the parameter to configure
 *          auto increment related properties.
 *
 *  @field  numInTransfers
 *              Number of IN transfer to be configured
 *
 *  @field  numOutTransfers
 *              Number of OUT transfer to be configured
 *
 *  @field transferProp
 *            Describes the properties related to each transfer
 *             Refer EDMA_UTILS_autoIncrement1D_transferProperties for details
 *
 *  ===============================================================
 */
typedef struct
{
    uint8_t    transferType;
    uint8_t    numInTransfers;
    uint8_t    numOutTransfers;
    EDMA_UTILS_autoIncrement1D_transferProperties transferProp[NUM_MAX_TRANSFER_AUTOINCREMENT_1D];
}EDMA_UTILS_autoIncrement1D_initParam;


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_getContextSize
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
int32_t EDMA_UTILS_autoIncrement1D_getContextSize(void);


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_init
 *
 *  @desc     This function initializes the EDMA UTILS context for autoincrement usecase.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for thi autoincrement usecase. This memory is
 *                          expected to be allocated by user by first getting the size using
 *                          EDMA_UTILS_autoIncrement1D_getContextSize.
 *                  initParams :
 *                          Pointer to structure describing init configuration for the EDMA transfer
 *
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_init(void * autoIncrementContext , const EDMA_UTILS_autoIncrement1D_initParam * initParams);




/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_configure
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
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
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
 int32_t EDMA_UTILS_autoIncrement1D_configure(void * autoIncrementContext , uint32_t transferType);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_update
 *
 *  @desc   This function updates a certain set of parameters of autoincrement usecase.
 *               This function can only be called after EDMA_UTILS_autoIncrement1D_configure
 *               has been called. Size of array update param should be same as what has already been
 *               configured for IN, OUT or INOUT transfer in EDMA_UTILS_autoIncrement1D_configure otherwise
 *               this function will return an error. This function only updates the internal context and not actually
 *              update the param set. Param set is updated when the next frame starts.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
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
int32_t EDMA_UTILS_autoIncrement1D_update(void * autoIncrementContext, const EDMA_UTILS_autoIncrement1D_updateParams *updateParams);
/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_triggerInChannel
 *
 *  @desc   This function triggers all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_triggerInChannel(void * autoIncrementContext);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_triggerOutChannel
 *
 *  @desc   This function triggers all Output channels together. It also indicates when the last
 *              block is reached in the ROI given by user.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *                  1 : Last Block in auto increment
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_triggerOutChannel(void * autoIncrementContext);



/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_waitInChannel
 *
 *  @desc   This function waits for all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_waitInChannel(void * autoIncrementContext);


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_waitOutChannel
 *
 *  @desc   This function waits for all output channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_waitOutChannel(void * autoIncrementContext);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_deconfigure
 *
 *  @desc   This function deconfigures autoincrement 1D usecase and releases all the allocated EDMA resources.
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
int32_t EDMA_UTILS_autoIncrement1D_deconfigure(void * autoIncrementContext , uint32_t transferType);

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_isDone
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
int32_t EDMA_UTILS_autoIncrement1D_isDone(void * autoIncrementContext, uint32_t transferType);

#endif /*#define EDMA_UTILS_AUTOINCREMENT_1D_H_*/


