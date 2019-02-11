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
 * @file    hdvicp20_ti_vdma_host.h
 *
 * @brief   Light weight implementation of basic VDMA functions for host
 * @details This file contains the light weight routines of vDMA functions
 *          in order to be used on host. These are written in the perspective of
 *          code size, cycles and limited usage. Some of these are very specific
 *          like kind of descriptors groups ids etc.
********************************************************************************
*/

#ifndef __HDVICP20_TI_VDMA_HOST__
#define __HDVICP20_TI_VDMA_HOST__

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
* Macro fo SL2 address offset mask
*/
#define SL2_MASK 0x7FFFFFU

/**
 * Macros for 2 frame level VDMA transfers
 */
#define FRAME_LEVEL_EXT_TO_SL2_XFER0 0
#define FRAME_LEVEL_EXT_TO_SL2_XFER1 1

/**
********************************************************************************
 *  @fn     HDVICP20_TI_VDMA_Open_Extmem_SL2(U32 configBase, U8 VDMA_TBA)
 *  @brief  This function opens vDMA
 *
 *          In this function we do following steps
 *          - Wait till all transactions are completed by the vDMA
 *          - Do software reset of vDMA
 *          - Put the tiler base address
 *          - Put end of group descriptions
 *          - Number of contexts to be used for synchronous transfers
 *          - Group definition for the descriptors
 *
 *  @param[in]      configBase  : Config base address of IVAHD given by app
 *  @param[in]      VDMA_TBA    : Tiler base address given by the app
 *
 *  @return none
********************************************************************************
*/
void HDVICP20_TI_VDMA_Open_Extmem_SL2(U32 configBase, U8 VDMA_TBA);

/**
********************************************************************************
 *  @fn             HDVICP20_TI_VDMA_Prepare_Extmem_SL2(void* dst, void* src,
 *                        U32 size, U8 Dir,
 *                        U32 Id, U32 configBase)
 *  @brief          This function prepares descriptors from DDR to SL2 or SL2 to
 *                  DDR transfers.
 *  @details        This function prepares vDMA descriptors for given transfer.
 *                  The assumption made in this routine is group id for which
 *                  user asked to prepre the descriptors is idle. i.e no
 *                  transfer is on going in this group id.
 *                  The sequence of steps that are followed in this function are
 *                  - Determin the src and dest address depending on drection
 *                  - Get the physical address of DDR address
 *                  - If deterministic, obtain the address in deterministic
 *                    memory that needs to be updated.
 *                  - write the descriptor in the memory
 *  @param[in]      dst        : Destiniation address of the transfer.
 *                               If this address is pointing to external memory
 *                               and then it is assumed to be physical address
 *                               seen by vDMA.
 *  @param[in]      src        : Source address of the transfer.
 *                               If this address is pointing to external memory
 *                               and then it is assumed to be physical address
 *                               seen by vDMA.
 *  @param[in]      size       : Size of data that needs to be transfered.
 *  @param[in]      Dir        : Direction of the transfer. Possible values are
 *                               #DDRTOSL2 or SL2TODDR
 *  @param[in]      Id         : vDMA group ID.
 *  @param[in]      configBase : Config base address of ivahd
 *
 *  @return none
********************************************************************************
*/
void HDVICP20_TI_VDMA_Prepare_Extmem_SL2(void* dst, void* src, U32 size,
                       U8 Dir, U32 Id, U32 configBase);

/**
********************************************************************************
 *  @fn             HDVICP20_TI_VDMA_Trigger_Extmem_SL2(U32 configBase,
 *                                        U32 groupID)
 *  @brief          This function triggers the transfers that are prepared
 *                  earlier.
 *  @param[in]      configBase        : Config base address
 *  @param[in]      groupID           : gropu ID that needs to be triggered
 *  @return         none
********************************************************************************
*/
void HDVICP20_TI_VDMA_Trigger_Extmem_SL2(U32 configBase, U32 groupID);

/**
********************************************************************************
 *  @fn             HDVICP20_TI_VDMA_WaitForData_Extmem_SL2(U32 Id,
 *                                                    U32 configBase)
 *  @brief          This function waits for the vDMA data that needs to be
 *                  transferd
 *  @details        This function checks the status of the group in vDMA
                    registers, and if the group is busy then it waits for the
                    group to complete. Once the transfer is completed, It clears
                    the corresponding status bit
 *  @param[in]      Id          : Group ID of the transfer
 *  @param[in]      configBase  : Config base address
 *  @return         none
********************************************************************************
*/
void HDVICP20_TI_VDMA_WaitForData_Extmem_SL2(U32 Id, U32 configBase);

#endif /* __HDVICP20_TI_VDMA_HOST__*/
