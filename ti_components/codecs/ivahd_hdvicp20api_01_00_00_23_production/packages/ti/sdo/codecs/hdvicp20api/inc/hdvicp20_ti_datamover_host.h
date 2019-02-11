/*
********************************************************************************
 * HDVICP2.0/IVA-HD API
 *
 * "HDVICP2.0 API" is software module developed for TI's HDVICP2 based SOCs.
 * This module provides APIs for programming of HDVCIP2.0 hardware accelerators
 * which can be used for video codec implementation.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
 * @file    hdvicp20_ti_datamover_host.h
 *
 * @brief   Light weight implementation of basic DM functions for host
 * @details This file contains the light weight routines of DM functions
 *          in order to be used on host. These are written in the perspective of
 *          code size, cycles and limited usage. This has
 *          implementations of DM transferes for ITCM/DTCM/SL2 data.
********************************************************************************
*/

#ifndef __HDVICP20_TI_DATAMOVER_HOST__
#define __HDVICP20_TI_DATAMOVER_HOST__

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/*--------------------- program files ----------------------------------------*/
#include "cslr_ivahd.h"

/**
* config base offset of vDMA from host
*/
#define IVAHD_VDMA_CFG_FROM_HOST   0x50000U
/**
* config base offset of iCont1 from host
*/
#define IVAHD_ICONT1_CFG_FROM_HOST 0x70000U
/**
* config base offset of iCont2 from host
*/
#define IVAHD_ICONT2_CFG_FROM_HOST 0x71000U

/**
 *******************************************************************************
 *  @enum       eTransferDir
 *  @brief      direction information for the transfers.
 *******************************************************************************
*/
 typedef enum {
  SL2_TO_DTCM = CSL_ICONT1_MMR_DM_ICONT_DMCONTEXT_2_CMD_TYPE_SL2TODTCM ,
                /**<
                * Use this enumeration to indicate that transfer is from SL2
                * to DTCM. Note that this value is directly used in DM
                * programming. So this enuleration is derived from CSL headers
                */
  DTCM_TO_SL2 = CSL_ICONT1_MMR_DM_ICONT_DMCONTEXT_2_CMD_TYPE_DTCMTOSL2 ,
                /**<
                * Use this enumeration to indicate that transfer is from DTCM
                * to SL2. Note that this value is directly used in DM
                * programming. So this enuleration is derived from CSL headers
                */
  SL2_TO_ITCM = CSL_ICONT1_MMR_DM_ICONT_DMCONTEXT_2_CMD_TYPE_SL2TOITCM
                /**<
                * Use this enumeration to indicate that transfer is from SL2
                * to ITCM. Note that this value is directly used in DM
                * programming. So this enuleration is derived from CSL headers
                */
 }eTransferDir ;

/**
********************************************************************************
 *  @fn             HDVICP20_TI_DM_Prepare_SL2_TCM(void* dst, void* src,
                        U32 size,U8 Dir, U8 Id, U32 configBase,U8  ubContextId)
 *  @brief          Prepares the data word that needs to be written in to DM
 *                  for transfer.
 *  @details        This function takes the src, dstetc info and prepares a
 *                  32 bit word. This word needs to be written into DM trigger
 *                  register for the transfer to be initiated.
 *  @param[in]      dst         : Destination address
 *  @param[in]      src         : Source address
 *  @param[in]      size        : Size of transfer
 *  @param[in]      Dir         : Direction of transfer
 *  @param[in]      Id          : Which DM needs to be programmed (iCont1/2)
 *  @param[in]      configBase  : Config base address
 *  @param[in]      ubContextId : DM context or logical channel ID (0 to 3)
 *  @return         32 bit word which needs to put in DM registers
********************************************************************************
*/
U32 HDVICP20_TI_DM_Prepare_SL2_TCM(void* dst, void* src, U32 size,
                                U8 Dir, U8 Id, U32 configBase,U8  ubContextId);

/**
********************************************************************************
 *  @fn             HDVICP20_TI_DM_Trigger_SL2_TCM(U32 data, U8 Id,
 *                                           U32 configBase, U8 ubContextId)
 *  @brief          This function starts the DM transfer
 *  @details        This function writes the trigger word into DM context.
 *                  Once the word is written into context register the transfer
 *                  will start.
 *  @param[in]      data        : data word to be written
 *  @param[in]      Id          : id of iCont to be triggered
 *  @param[in]      configBase  : Config base address
 *  @param[in]      ubContextId : DM context or logical channel ID (0 to 3)
 *  @return         none
********************************************************************************
*/
void HDVICP20_TI_DM_Trigger_SL2_TCM(U32 data, U8 Id, U32 configBase,
                                        U8 ubContextId);
/**
********************************************************************************
 *  @fn             HDVICP20_TI_DM_WaitForData_SL2_TCM(U8 Id, U32 configBase,
 *                                                              U8 ubContextId)
 *  @brief          This function waits for the DM transfer to get completed.
 *  @details        This function checks for status of DM of given iCont and
 *                  waits till this status is cleared.
 *  @param[in]      Id          : id of iCont to be triggered
 *  @param[in]      configBase  : Config base address
 *  @param[in]      ubContextId : DM context or logical channel ID (0 to 3)
 *  @return         none
********************************************************************************
*/
void HDVICP20_TI_DM_WaitForData_SL2_TCM(U8 Id, U32 configBase, U8 ubContextId);

#endif /* __HDVICP20_TI_DATAMOVER_HOST__ */

