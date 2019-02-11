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
 *  edma_utils_autoincrement_v2.c
 *
 * @brief
 *  This file contains function implementation for util functions for
 *  configuring EVE EDMA sub module.
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Aug 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 */

#include "edma_utils_autoincrement_int.h"
#include "edma_utils_autoincrement_v2.h"
#include "dma_resource_allocator.h"
#include "dma_funcs.h"
#include "edma_utils_state.h"
#include "edma_utils_context_size.h"
#include "edma_utils.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define CEIL(x,y) ((( (x) + (y) - (uint16_t)1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */


/** ========================================================
 *  @name   EDMA_UTILS_autoIncrement_context
 *
 *  @desc   This structure contains the context for autoincrement V2 usecase . It contains
 *               variables which are internally needed by auto increment usecase
 *
 *  @field  autoIncrementContext
 *             This is an array of 2 context, one to handle ping buffer and other to handle pong buffer
 *
 *  @field pingPongFlagIn
 *             Ping pong flag for In channels
 *
 *  @field pingPongFlagOut
 *               Ping pong flag for Out channels
 *
 *  @field switchOccuredIn
 *               Flag to indicate the context switch occurrer for IN channels
 *
 *  @field switchOccuredOut
 *               Flag to indicate the context switch occurrer for OUT channels
 *
 *  @field numBlkHorzIn
 *             Number of horz block for both the contexts for IN channels
 *
 *  @field numBlkHorzOut
 *             Number of horz block for both the contexts for Out channels
 *
 *  @field numTotalHorzBlk
 *             Number of horz blocks for in full image (each context should add to this)
 *
 *  @field blockCountIdx
 *              Index to count number of blocks
 *
 *  @field  numTotalBlocks
 *              total number of blocks
 *
 *  @field pingPongOffset
 *              Offset in bytes between ping and pong buffer
 *
 *  ===============================================================
 */

typedef struct
{
  EDMA_UTILS_autoIncrement_context autoIncrementContext[2];
  uint8_t pingPongFlagIn;
  uint8_t pingPongFlagOut;

  uint8_t switchOccuredIn;
  uint8_t switchOccuredOut;

  uint16_t numBlkHorzIn[2];
  uint16_t numBlkHorzOut[2];
  uint16_t numTotalHorzBlk;

  uint16_t blockCountIdx;
  uint16_t numTotalBlocks;


  uint32_t pingPongOffset;
} EDMA_UTILS_autoIncrement_context_v2;


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
int32_t EDMA_UTILS_autoIncrement_getContextSize_v2(void)
{
    int32_t size;

    size = sizeof(EDMA_UTILS_autoIncrement_context_v2);

    return size;
}

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
int32_t EDMA_UTILS_autoIncrement_init_v2(void * autoIncrementContext ,const EDMA_UTILS_autoIncrement_initParam_v2 * initParamsV2)
{
  EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle;
  int32_t status = 0;
  uint32_t      transferCnt = 0;
  uint32_t      numTransfers = 0;
  uint32_t contextSize;
  uint16_t  numTotalHorzBlk;
  if ( autoIncrementContext == NULL)
  {
    status = -1;
  }

  contextSize = sizeof(EDMA_UTILS_autoIncrement_context_v2);

  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
  /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
  /*  UNREACH.GEN :   Unreachable code  */
  /* Below condition will currently never fail and hence code is unreachable but
  as the implementation of the function changes contextSize and the macro defined can be different
  this error check is to catch such mismatch*/
  if (  (contextSize) != EDMA_UTILS_AUTOINCREMENT_CONTEXT_V2_SIZE )
  {
#ifdef DEBUG
      printf("Autoincrement context size is not correct, it should be %d \n" ,
          sizeof(EDMA_UTILS_autoIncrement_context_v2));
#endif
      status = -1;
  }
  /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */
  /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */

  if ( status == 0 )
  {
    EDMA_UTILS_autoIncrement_initParam initParams;

    pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;

    memcpy(&initParams, &initParamsV2->initParams, sizeof(EDMA_UTILS_autoIncrement_initParam));

    switch (initParamsV2->initParams.transferType)
    {
        case EDMA_UTILS_TRANSFER_IN:
            numTransfers                         = initParamsV2->initParams.numInTransfers;
            break;
        case EDMA_UTILS_TRANSFER_OUT:
            numTransfers                         = initParamsV2->initParams.numOutTransfers;
            break;
        case EDMA_UTILS_TRANSFER_INOUT:
            numTransfers                         = initParamsV2->initParams.numInTransfers + initParamsV2->initParams.numOutTransfers;
            break;
        default :
#ifdef DEBUG
            printf("Invalid Transfer Type \n");
#endif
            status = -1;
            break;
    }

    pingPongHandle->pingPongOffset = initParamsV2->pingPongOffset;

    if ( initParams.transferProp[0].extBlkIncrementX != 0 )
    {
      numTotalHorzBlk = (CEIL((initParams.transferProp[0].roiWidth - initParams.transferProp[0].blkWidth),
                initParams.transferProp[0].extBlkIncrementX) / initParams.transferProp[0].extBlkIncrementX ) + (uint16_t)1U;
    }
    else
    {
      numTotalHorzBlk = 1U;
    }


    for (transferCnt = 0; transferCnt < numTransfers;transferCnt++)
    {
      initParams.transferProp[transferCnt].extBlkIncrementX = 2 * initParamsV2->initParams.transferProp[transferCnt].extBlkIncrementX;
      /* If numTotalHorzBlk is even then first context will always be a proper multiple of block dimensions */
      if ( (numTotalHorzBlk % (uint16_t)2U) == 0 )
      {
        initParams.transferProp[transferCnt].roiWidth = (((numTotalHorzBlk / (uint16_t)2U) - (uint16_t)1U) * initParams.transferProp[transferCnt].extBlkIncrementX) +
                                                          initParams.transferProp[transferCnt].blkWidth;
      }
    }

    status = EDMA_UTILS_autoIncrement_init(&pingPongHandle->autoIncrementContext[0],&initParams);

    if ( status == 0 )
    {

      for (transferCnt = 0; transferCnt < numTransfers;transferCnt++)
      {
        if ( (numTotalHorzBlk % (uint16_t)2U) == 0 )
        {
          initParams.transferProp[transferCnt].roiWidth         = initParamsV2->initParams.transferProp[transferCnt].roiWidth -
                                                                  initParamsV2->initParams.transferProp[transferCnt].extBlkIncrementX;
        }
        /* If numTotalHorzBlk is odd then second context will always be a proper multiple of block dimensions */
        else
        {
          if ( numTotalHorzBlk > 1U )
          {
            initParams.transferProp[transferCnt].roiWidth = (((numTotalHorzBlk / (uint16_t)2U) - (uint16_t)1U) * initParams.transferProp[transferCnt].extBlkIncrementX) +
                                                            initParams.transferProp[transferCnt].blkWidth;
          }
          else
          {
            initParams.transferProp[transferCnt].roiWidth         = initParamsV2->initParams.transferProp[transferCnt].roiWidth;
          }
        }

        initParams.transferProp[transferCnt].extBlkIncrementX = 2U * initParamsV2->initParams.transferProp[transferCnt].extBlkIncrementX;
        /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
        /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
        /*  Pointer below are allocated by user and hence we dont know the bound at this level. The harmful side effect of voilating this
        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
        initParams.transferProp[transferCnt].extMemPtr        = initParamsV2->initParams.transferProp[transferCnt].extMemPtr + initParamsV2->initParams.transferProp[transferCnt].extBlkIncrementX;
        initParams.transferProp[transferCnt].interMemPtr       = initParamsV2->initParams.transferProp[transferCnt].interMemPtr + initParamsV2->pingPongOffset;
        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
      }


      status = EDMA_UTILS_autoIncrement_init(&pingPongHandle->autoIncrementContext[1],&initParams);
    }

    pingPongHandle->numTotalHorzBlk = numTotalHorzBlk;

  }

  return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_configure_v2
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
int32_t EDMA_UTILS_autoIncrement_configure_v2(void * autoIncrementContext , uint32_t transferType)
{
  EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle;
  int32_t status = 0;
  uint8_t  *extMemPtrTemp;
  uint16_t  blkDimTemp;

  uint16_t transferCnt;
  if ( autoIncrementContext == NULL)
  {
    status = -1;
  }

  if ( status == 0 )
  {
    pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;

    status = EDMA_UTILS_autoIncrement_configure(&pingPongHandle->autoIncrementContext[0],transferType);

    if ( status == 0)
    {
      status = EDMA_UTILS_autoIncrement_configure(&pingPongHandle->autoIncrementContext[1],transferType);
    }

    if ( status == 0 )
    {
        uint16_t  actualTransferCnt;
        uint16_t numTransfers = 0;
        uint16_t transferCntOffset = 0;
        switch (transferType)
        {
            case EDMA_UTILS_TRANSFER_IN:
                numTransfers                         = pingPongHandle->autoIncrementContext[0].numInTransfers;
                transferCntOffset                    = 0;
                break;
            case EDMA_UTILS_TRANSFER_OUT:
                transferCntOffset                    = pingPongHandle->autoIncrementContext[0].numInTransfers;
                numTransfers                         = pingPongHandle->autoIncrementContext[0].numOutTransfers;
                break;
            case EDMA_UTILS_TRANSFER_INOUT:
                transferCntOffset                    = 0;
                numTransfers                         = pingPongHandle->autoIncrementContext[0].numInTransfers + pingPongHandle->autoIncrementContext[0].numOutTransfers;
                break;
            default :
#ifdef DEBUG
                printf("Invalid Transfer Type \n");
#endif
                status = -1;
                break;
        }
        if ( status == 0)
        {
          if( (pingPongHandle->numTotalHorzBlk % 2) == 0 )
          {
            pingPongHandle->numBlkHorzIn[0] = pingPongHandle->autoIncrementContext[0].numBlkHorz;
            pingPongHandle->numBlkHorzIn[1] = pingPongHandle->autoIncrementContext[1].numBlkHorz;

            pingPongHandle->numBlkHorzOut[0] = pingPongHandle->autoIncrementContext[0].numBlkHorz;
            pingPongHandle->numBlkHorzOut[1] = pingPongHandle->autoIncrementContext[1].numBlkHorz;
          }
          else
          {
            /* Switch the two entries so that for the first block row we get the correct values */
            pingPongHandle->numBlkHorzIn[0] = pingPongHandle->autoIncrementContext[1].numBlkHorz;
            pingPongHandle->numBlkHorzIn[1] = pingPongHandle->autoIncrementContext[0].numBlkHorz;

            pingPongHandle->numBlkHorzOut[0] = pingPongHandle->autoIncrementContext[1].numBlkHorz;
            pingPongHandle->numBlkHorzOut[1] = pingPongHandle->autoIncrementContext[0].numBlkHorz;

            if( pingPongHandle->numTotalHorzBlk == 1 )
            {
              pingPongHandle->numBlkHorzIn[0]  = 0;
              pingPongHandle->numBlkHorzOut[0] = 0;
            }

            for ( transferCnt = 0 ; transferCnt < numTransfers; transferCnt++ )
            {
              actualTransferCnt = transferCnt + transferCntOffset;

              extMemPtrTemp =  pingPongHandle->autoIncrementContext[1].transferProp[actualTransferCnt].extMemPtr;
              pingPongHandle->autoIncrementContext[1].transferProp[actualTransferCnt].extMemPtr  = pingPongHandle->autoIncrementContext[0].transferProp[actualTransferCnt].extMemPtr;
              pingPongHandle->autoIncrementContext[0].transferProp[actualTransferCnt].extMemPtr  = extMemPtrTemp;

              blkDimTemp =  pingPongHandle->autoIncrementContext[1].blkWidthLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[1].blkWidthLast[actualTransferCnt]  = pingPongHandle->autoIncrementContext[0].blkWidthLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[0].blkWidthLast[actualTransferCnt]  = blkDimTemp;

              blkDimTemp =  pingPongHandle->autoIncrementContext[1].blkHeightLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[1].blkHeightLast[actualTransferCnt]  = pingPongHandle->autoIncrementContext[0].blkHeightLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[0].blkHeightLast[actualTransferCnt]  = blkDimTemp;
            }
          }

        /* Only first transfer (from pong buffer) needs to be dummy and hence for ping buffer set the horzIdx = 0 so that valid transfer starts */
        pingPongHandle->autoIncrementContext[0].blkHorzIdxOut = 0;

        pingPongHandle->numTotalBlocks = (pingPongHandle->numBlkHorzIn[0] + pingPongHandle->numBlkHorzIn[1]) *
                     pingPongHandle->autoIncrementContext[0].numBlkVert;

        pingPongHandle->pingPongFlagIn = 0;
        pingPongHandle->pingPongFlagOut = 1;/* First output will happen from ping buffer */
        pingPongHandle->switchOccuredIn = 0;
        pingPongHandle->switchOccuredOut = 0;
        pingPongHandle->blockCountIdx = 0;
      }
    }
  }
  return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_update_v2
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
int32_t EDMA_UTILS_autoIncrement_update_v2(void * autoIncrementContext, const EDMA_UTILS_autoIncrement_updateParams *updateParams)
{
  EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;
  int32_t status = 0;
  uint32_t      transferCnt = 0;
  uint32_t      transferCntOffset;
  uint32_t      actualTransferCnt;
  uint32_t      numTransfers;
  EDMA_UTILS_autoIncrement_updateParams updateParamsLocal;
  uint16_t extBlkIncrementX;
  uint16_t blkWidth;
  uint16_t numTotalHorzBlk = pingPongHandle->numTotalHorzBlk;
  uint16_t roiWidth;


  if ( autoIncrementContext == NULL)
  {
    status = -1;
  }

  if ( status == 0 )
  {
      switch (updateParams->transferType)
      {
          case EDMA_UTILS_TRANSFER_IN:
              numTransfers                         = pingPongHandle->autoIncrementContext[0].numInTransfers;
              transferCntOffset                    = 0;
              break;
          case EDMA_UTILS_TRANSFER_OUT:
              transferCntOffset                    =  pingPongHandle->autoIncrementContext[0].numInTransfers;
              numTransfers                         =  pingPongHandle->autoIncrementContext[0].numOutTransfers;
              break;
          case EDMA_UTILS_TRANSFER_INOUT:
              transferCntOffset                    = 0;
              numTransfers                         =  pingPongHandle->autoIncrementContext[0].numInTransfers +  pingPongHandle->autoIncrementContext[0].numOutTransfers;
              break;
          default :
#ifdef DEBUG
              printf("Invalid Transfer Type \n");
#endif
              status = -1;
              break;
      }
  }

  if ( status == 0 )
  {
    /* Modifying extBlkIncrementX or blockWidth without modifying roiWidth is not allowed */
    if (  ((uint32_t) (updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTBLKINCREMENTX)  |
      (uint32_t) (updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_BLOCKWIDTH)) != 0)
    {
      if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH) == 0 )
      {
        status = -1;
      }
    }
  }

  if ( status == 0 )
  {

    pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;

    memcpy(&updateParamsLocal, updateParams, sizeof(EDMA_UTILS_autoIncrement_updateParams));



    for (transferCnt = 0; transferCnt < numTransfers;transferCnt++)
    {
      actualTransferCnt = transferCntOffset + transferCnt;

      if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTBLKINCREMENTX) != 0)
      {
        extBlkIncrementX = updateParams->updateParams[transferCnt].extBlkIncrementX;
      }
      else
      {
        extBlkIncrementX = pingPongHandle->autoIncrementContext[0].transferProp[actualTransferCnt].extBlkIncrementX / (uint16_t)2U;
      }

      if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_BLOCKWIDTH) != 0)
      {
        blkWidth = updateParams->updateParams[transferCnt].blkWidth;
      }
      else
      {
        blkWidth = pingPongHandle->autoIncrementContext[0].transferProp[actualTransferCnt].blkWidth;
      }

      if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH) != 0)
      {
        if (extBlkIncrementX != 0 )
        {
          numTotalHorzBlk = (CEIL((updateParams->updateParams[transferCnt].roiWidth - blkWidth),
            extBlkIncrementX) / extBlkIncrementX ) + 1U;
        }
        else
        {
          numTotalHorzBlk = 1U;
        }
        /* If numTotalHorzBlk is even then first context will always be a proper multiple of block dimensions */
        if ( (numTotalHorzBlk % 2U) == 0 )
        {
          roiWidth = (((numTotalHorzBlk / (uint16_t)2U) - (uint16_t)1U) * extBlkIncrementX * 2U) +
                                                            blkWidth;
        }
        else
        {
          roiWidth = updateParams->updateParams[transferCnt].roiWidth;
        }
      }
      else
      {
        roiWidth = pingPongHandle->autoIncrementContext[0].transferProp[actualTransferCnt].roiWidth;
      }

      updateParamsLocal.updateParams[transferCnt].blkWidth         = blkWidth;
      updateParamsLocal.updateParams[transferCnt].roiWidth         = roiWidth;
      updateParamsLocal.updateParams[transferCnt].extBlkIncrementX = 2U * extBlkIncrementX;
    }



    status = EDMA_UTILS_autoIncrement_update(&pingPongHandle->autoIncrementContext[0],&updateParamsLocal);

    if ( status == 0 )
    {

      for (transferCnt = 0; transferCnt < numTransfers;transferCnt++)
      {
        actualTransferCnt = transferCntOffset + transferCnt;

        if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTBLKINCREMENTX) != 0)
        {
          extBlkIncrementX = updateParams->updateParams[transferCnt].extBlkIncrementX;
        }
        else
        {
          extBlkIncrementX = pingPongHandle->autoIncrementContext[1].transferProp[actualTransferCnt].extBlkIncrementX / (uint16_t)2U;
        }

        if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_BLOCKWIDTH) != 0)
        {
          blkWidth = updateParams->updateParams[transferCnt].blkWidth;
        }
        else
        {
          blkWidth = pingPongHandle->autoIncrementContext[1].transferProp[actualTransferCnt].blkWidth;
        }

        if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH) != 0)
        {
          if ( extBlkIncrementX != 0 )
          {
            numTotalHorzBlk = (CEIL((updateParams->updateParams[transferCnt].roiWidth - blkWidth),
                extBlkIncrementX) / extBlkIncrementX ) + 1U;
          }
          else
          {
            numTotalHorzBlk = 1U;
          }
          if ( (numTotalHorzBlk % 2U) == 0 )
          {
            roiWidth         = updateParams->updateParams[transferCnt].roiWidth -
                                                                      extBlkIncrementX;
          }
          /* If numTotalHorzBlk is odd then second context will always be a proper multiple of block dimensions */
          else
          {
            if ( numTotalHorzBlk > 1U )
            {
               roiWidth = (((numTotalHorzBlk / 2U) - 1U) * extBlkIncrementX * 2U) +
                                                                blkWidth;
            }
            else
            {
              roiWidth = updateParams->updateParams[transferCnt].roiWidth;
            }
          }
        }
        else
        {
          roiWidth = pingPongHandle->autoIncrementContext[1].transferProp[actualTransferCnt].roiWidth;
        }

        updateParamsLocal.updateParams[transferCnt].blkWidth         = blkWidth;
        updateParamsLocal.updateParams[transferCnt].roiWidth         = roiWidth;
        updateParamsLocal.updateParams[transferCnt].extBlkIncrementX = 2U * extBlkIncrementX;
        /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
        /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
        /*  Pointer below are allocated by user and hence we dont know the bound at this level. The harmful side effect of voilating this
        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
        updateParamsLocal.updateParams[transferCnt].extMemPtr        = updateParams->updateParams[transferCnt].extMemPtr +
                                                                           extBlkIncrementX;
        updateParamsLocal.updateParams[transferCnt].interMemPtr       = updateParams->updateParams[transferCnt].interMemPtr + pingPongHandle->pingPongOffset;
        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
      }


      status = EDMA_UTILS_autoIncrement_update(&pingPongHandle->autoIncrementContext[1],&updateParamsLocal);

      pingPongHandle->numTotalHorzBlk = numTotalHorzBlk;
    }
  }

  return status;
}


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_triggerInChannel_v2
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
int32_t EDMA_UTILS_autoIncrement_triggerInChannel_v2(void * autoIncrementContext)
{
  EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;
  EDMA_UTILS_autoIncrement_context * currAutoIncrementHandle = &pingPongHandle->autoIncrementContext[pingPongHandle->pingPongFlagIn];
  uint32_t            transferCnt = 0;
  int32_t             status = 0;
  uint16_t numBlkHorzTemp;
  uint8_t  * extMemPtrTemp;
  uint16_t blkDimTemp;
  if (currAutoIncrementHandle->blkHorzIdxIn == 0 )
  {
      if ( pingPongHandle->numBlkHorzIn[0] != pingPongHandle->numBlkHorzIn[1])
      {
        if ((pingPongHandle->switchOccuredIn == 0) || (pingPongHandle->numTotalHorzBlk == 1U) )
        {

          numBlkHorzTemp = pingPongHandle->numBlkHorzIn[1];
          pingPongHandle->numBlkHorzIn[1] = pingPongHandle->numBlkHorzIn[0];
          pingPongHandle->numBlkHorzIn[0] = numBlkHorzTemp;

          for ( transferCnt = 0 ; transferCnt < currAutoIncrementHandle->numInTransfers ; transferCnt++ )
          {
            extMemPtrTemp =  pingPongHandle->autoIncrementContext[1].transferProp[transferCnt].extMemPtr;
            pingPongHandle->autoIncrementContext[1].transferProp[transferCnt].extMemPtr  = pingPongHandle->autoIncrementContext[0].transferProp[transferCnt].extMemPtr;
            pingPongHandle->autoIncrementContext[0].transferProp[transferCnt].extMemPtr  = extMemPtrTemp;

            blkDimTemp =  pingPongHandle->autoIncrementContext[1].blkWidthLast[transferCnt];
            pingPongHandle->autoIncrementContext[1].blkWidthLast[transferCnt]  = pingPongHandle->autoIncrementContext[0].blkWidthLast[transferCnt];
            pingPongHandle->autoIncrementContext[0].blkWidthLast[transferCnt]  = blkDimTemp;

            blkDimTemp =  pingPongHandle->autoIncrementContext[1].blkHeightLast[transferCnt];
            pingPongHandle->autoIncrementContext[1].blkHeightLast[transferCnt]  = pingPongHandle->autoIncrementContext[0].blkHeightLast[transferCnt];
            pingPongHandle->autoIncrementContext[0].blkHeightLast[transferCnt]  = blkDimTemp;

          }
          pingPongHandle->switchOccuredIn = 1U;
        }
        else
        {
          pingPongHandle->switchOccuredIn = 0;
        }
      }

      currAutoIncrementHandle->numBlkHorz = pingPongHandle->numBlkHorzIn[pingPongHandle->pingPongFlagIn];
  }

  EDMA_UTILS_autoIncrement_triggerInChannel(currAutoIncrementHandle);


  return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_triggerOutChannel_v2
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
int32_t EDMA_UTILS_autoIncrement_triggerOutChannel_v2(void * autoIncrementContext)
{
    EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;
    EDMA_UTILS_autoIncrement_context * currAutoIncrementHandle = &pingPongHandle->autoIncrementContext[pingPongHandle->pingPongFlagOut];

    uint32_t            transferCnt = 0;
    uint32_t            numInTransfers;
    uint32_t            actualTransferCnt;
    uint16_t            numBlkHorzTemp;
    uint8_t             *extMemPtrTemp;
    uint16_t            blkDimTemp;
    int32_t            status = 0;


    if (currAutoIncrementHandle->blkHorzIdxOut == 0 )
    {
        numInTransfers = currAutoIncrementHandle->numInTransfers ;
        if ( pingPongHandle->numBlkHorzOut[0] != pingPongHandle->numBlkHorzOut[1])
        {
          if ((pingPongHandle->switchOccuredOut == 0) || (pingPongHandle->numTotalHorzBlk == 1U) )
          {
            numBlkHorzTemp = pingPongHandle->numBlkHorzOut[1];
            pingPongHandle->numBlkHorzOut[1] = pingPongHandle->numBlkHorzOut[0];
            pingPongHandle->numBlkHorzOut[0] = numBlkHorzTemp;

            for ( transferCnt = 0 ; transferCnt < currAutoIncrementHandle->numOutTransfers; transferCnt++ )
            {
              actualTransferCnt = transferCnt + numInTransfers;

              extMemPtrTemp =  pingPongHandle->autoIncrementContext[1].transferProp[actualTransferCnt].extMemPtr;
              pingPongHandle->autoIncrementContext[1].transferProp[actualTransferCnt].extMemPtr  = pingPongHandle->autoIncrementContext[0].transferProp[actualTransferCnt].extMemPtr;
              pingPongHandle->autoIncrementContext[0].transferProp[actualTransferCnt].extMemPtr  = extMemPtrTemp;

              blkDimTemp =  pingPongHandle->autoIncrementContext[1].blkWidthLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[1].blkWidthLast[actualTransferCnt]  = pingPongHandle->autoIncrementContext[0].blkWidthLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[0].blkWidthLast[actualTransferCnt]  = blkDimTemp;

              blkDimTemp =  pingPongHandle->autoIncrementContext[1].blkHeightLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[1].blkHeightLast[actualTransferCnt]  = pingPongHandle->autoIncrementContext[0].blkHeightLast[actualTransferCnt];
              pingPongHandle->autoIncrementContext[0].blkHeightLast[actualTransferCnt]  = blkDimTemp;

            }
            pingPongHandle->switchOccuredOut = 1U;
          }
          else
          {
            pingPongHandle->switchOccuredOut = 0;
          }
        }

        currAutoIncrementHandle->numBlkHorz = pingPongHandle->numBlkHorzOut[pingPongHandle->pingPongFlagOut];
        currAutoIncrementHandle->numTotalBlk = currAutoIncrementHandle->numBlkHorz * currAutoIncrementHandle->numBlkVert;
    }

    EDMA_UTILS_autoIncrement_triggerOutChannel(currAutoIncrementHandle);

    if ( pingPongHandle->blockCountIdx == (pingPongHandle->numTotalBlocks - (uint16_t)1U))
    {
      status = 1;
    }

    pingPongHandle->blockCountIdx++;


    return status;
}


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_waitInChannel_v2
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
int32_t EDMA_UTILS_autoIncrement_waitInChannel_v2(void * autoIncrementContext)
{
    EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;
    EDMA_UTILS_autoIncrement_context * currAutoIncrementHandle = &pingPongHandle->autoIncrementContext[pingPongHandle->pingPongFlagIn];
    int32_t            status = 0;


    currAutoIncrementHandle->numBlkHorz = (pingPongHandle->numBlkHorzIn[pingPongHandle->pingPongFlagIn]);

    pingPongHandle->pingPongFlagIn ^= 1U;

    EDMA_UTILS_autoIncrement_waitInChannel(currAutoIncrementHandle);

    if( pingPongHandle->numTotalHorzBlk == 1U)
    {
        EDMA_UTILS_autoIncrement_context * nextAutoIncrementHandle = &pingPongHandle->autoIncrementContext[pingPongHandle->pingPongFlagIn];
        nextAutoIncrementHandle->blkVertIdxIn = currAutoIncrementHandle->blkVertIdxIn;
    }

    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_waitOutChannel_v2
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
int32_t EDMA_UTILS_autoIncrement_waitOutChannel_v2(void * autoIncrementContext)
{
    EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;
    EDMA_UTILS_autoIncrement_context * currAutoIncrementHandle = &pingPongHandle->autoIncrementContext[pingPongHandle->pingPongFlagOut];
    int32_t status = 0;

    currAutoIncrementHandle->numBlkHorz = pingPongHandle->numBlkHorzOut[pingPongHandle->pingPongFlagOut];

    pingPongHandle->pingPongFlagOut ^= 1U;

    EDMA_UTILS_autoIncrement_waitOutChannel(currAutoIncrementHandle);

    if( pingPongHandle->numTotalHorzBlk == 1)
    {
        EDMA_UTILS_autoIncrement_context * nextAutoIncrementHandle = &pingPongHandle->autoIncrementContext[pingPongHandle->pingPongFlagOut];
        nextAutoIncrementHandle->blkVertIdxOut = currAutoIncrementHandle->blkVertIdxOut;
    }

    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_deconfigure_v2
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
int32_t EDMA_UTILS_autoIncrement_deconfigure_v2(void * autoIncrementContext , uint32_t transferType)
{
  EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;
  int32_t status = 0;

  status = EDMA_UTILS_autoIncrement_deconfigure(&pingPongHandle->autoIncrementContext[0], transferType);
  if ( status == 0 )
  {
    status = EDMA_UTILS_autoIncrement_deconfigure(&pingPongHandle->autoIncrementContext[1], transferType);
  }
  return status;
}
/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_isDone_v2
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
int32_t EDMA_UTILS_autoIncrement_isDone_v2(void * autoIncrementContext, uint32_t transferType)
{
  EDMA_UTILS_autoIncrement_context_v2 * pingPongHandle = (EDMA_UTILS_autoIncrement_context_v2 *)autoIncrementContext;
  int32_t status = 0;
  uint32_t pingPongFlag;
  EDMA_UTILS_autoIncrement_context * currAutoIncrementHandle;

  pingPongFlag = (uint32_t)((uint32_t)pingPongHandle->pingPongFlagIn | (uint32_t)pingPongHandle->pingPongFlagOut);

  currAutoIncrementHandle = &pingPongHandle->autoIncrementContext[pingPongFlag];

  status = EDMA_UTILS_autoIncrement_isDone(currAutoIncrementHandle, transferType);

  return status;
}



