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
 * \ingroup UTILS_API
 * \defgroup UTILS_L3_EMIF_BW_API APIs to set L3/DMM bandwidth related config
 *
 * \brief This module define APIs to set L3/DMM bandwidth related config
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_l3_emif_bw.h
 *
 * \brief APIs to set L3/DMM bandwidth related config
 *
 * \version 0.0 (Dec 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_L3_EMIF_H_
#define UTILS_L3_EMIF_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*
 *******************************************************************************
 * \brief Sizeof DSS DISPC pipe internal DMA buffer size
 *******************************************************************************
 */
#define UTILS_DSS_DISPC_DMA_BUF_SIZE                       (0x4FF)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief DMM Initiator ID
 *******************************************************************************
 */
typedef enum {

    UTILS_DMM_INITIATOR_ID_MPU         = 0x1  ,
    UTILS_DMM_INITIATOR_ID_CS_DAP      = 0x4  ,
    UTILS_DMM_INITIATOR_ID_DSP1_MDMA   = 0x8  ,
    UTILS_DMM_INITIATOR_ID_DSP1_CFG    = 0x9  ,
    UTILS_DMM_INITIATOR_ID_DSP1_DMA    = 0xA  ,
    UTILS_DMM_INITIATOR_ID_DSP2_MDMA   = 0xB  ,
    UTILS_DMM_INITIATOR_ID_DSP2_CFG    = 0xC  ,
    UTILS_DMM_INITIATOR_ID_DSP2_DMA    = 0xD  ,
    UTILS_DMM_INITIATOR_ID_IVA         = 0xE  ,
    UTILS_DMM_INITIATOR_ID_EVE1_P1     = 0x10 ,
    UTILS_DMM_INITIATOR_ID_EVE2_P1     = 0x11 ,
    UTILS_DMM_INITIATOR_ID_EVE3_P1     = 0x12 ,
    UTILS_DMM_INITIATOR_ID_EVE4_P1     = 0x13 ,
    UTILS_DMM_INITIATOR_ID_PRUSS1_PRU1 = 0x14 ,
    UTILS_DMM_INITIATOR_ID_PRUSS1_PRU2 = 0x15 ,
    UTILS_DMM_INITIATOR_ID_IPU1        = 0x18 ,
    UTILS_DMM_INITIATOR_ID_EDMA_TC1    = 0x1C ,
    UTILS_DMM_INITIATOR_ID_EDMA_TC2    = 0x1D ,
    UTILS_DMM_INITIATOR_ID_DSS         = 0x20 ,
    UTILS_DMM_INITIATOR_ID_MMU1        = 0x21 ,
    UTILS_DMM_INITIATOR_ID_PCIE1       = 0x22 ,
    UTILS_DMM_INITIATOR_ID_MMU2        = 0x23 ,
    UTILS_DMM_INITIATOR_ID_VIP1        = 0x24 ,
    UTILS_DMM_INITIATOR_ID_VIP2        = 0x25 ,
    UTILS_DMM_INITIATOR_ID_VIP3        = 0x26 ,
    UTILS_DMM_INITIATOR_ID_VPE         = 0x27 ,
    UTILS_DMM_INITIATOR_ID_GPU_P1      = 0x28 ,
    UTILS_DMM_INITIATOR_ID_GPU_P2      = 0x29 ,
    UTILS_DMM_INITIATOR_ID_GMAC_SW     = 0x2B ,
    UTILS_DMM_INITIATOR_ID_EVE1_P2     = 0x34 ,
    UTILS_DMM_INITIATOR_ID_EVE2_P2     = 0x35 ,
    UTILS_DMM_INITIATOR_ID_EVE3_P2     = 0x36 ,
    UTILS_DMM_INITIATOR_ID_EVE4_P2     = 0x37 ,
    UTILS_DMM_INITIATOR_ID_FORCE32BITS = 0x7FFFFFFF

} Utils_DmmInitiatorId;

/**
 *******************************************************************************
 * \brief EMIF Initiator ID
 *******************************************************************************
 */
typedef enum {

    UTILS_EMIF_INITIATOR_ID_DSP2_CFG    = 0,
    UTILS_EMIF_INITIATOR_ID_DSP2_EDMA   = 1,
    UTILS_EMIF_INITIATOR_ID_DSP1_EDMA   = 2,
    UTILS_EMIF_INITIATOR_ID_DSP1_CFG    = 3,
    UTILS_EMIF_INITIATOR_ID_DSP1_MDMA   = 4,
    UTILS_EMIF_INITIATOR_ID_MPU         = 7,
    UTILS_EMIF_INITIATOR_ID_PRUSS1_0    = 8,
    UTILS_EMIF_INITIATOR_ID_EVE4_TC0    = 9,
    UTILS_EMIF_INITIATOR_ID_EVE3_TC0    = 10,
    UTILS_EMIF_INITIATOR_ID_EVE2_TC0    = 11,
    UTILS_EMIF_INITIATOR_ID_EVE1_TC0    = 12,
    UTILS_EMIF_INITIATOR_ID_IVA         = 14,
    UTILS_EMIF_INITIATOR_ID_DSP2_MDMA   = 15,
    UTILS_EMIF_INITIATOR_ID_EDMA_TC0    = 16,
    UTILS_EMIF_INITIATOR_ID_IPU1        = 20,
    UTILS_EMIF_INITIATOR_ID_PRUSS1_1    = 23,
    UTILS_EMIF_INITIATOR_ID_VIP3        = 24,
    UTILS_EMIF_INITIATOR_ID_VIP2        = 25,
    UTILS_EMIF_INITIATOR_ID_VIP1        = 26,
    UTILS_EMIF_INITIATOR_ID_PCIE        = 28,
    UTILS_EMIF_INITIATOR_ID_DSS         = 30,
    UTILS_EMIF_INITIATOR_ID_EDMA_TC1    = 31,
    UTILS_EMIF_INITIATOR_ID_GMAC        = 35,
    UTILS_EMIF_INITIATOR_ID_VPE         = 39,
    UTILS_EMIF_INITIATOR_ID_EVE3_TC1    = 40,
    UTILS_EMIF_INITIATOR_ID_EVE2_TC1    = 41,
    UTILS_EMIF_INITIATOR_ID_EVE1_TC1    = 42,
    UTILS_EMIF_INITIATOR_ID_EVE4_TC1    = 55,
    UTILS_EMIF_INITIATOR_ID_FORCE32BITS = 0x7FFFFFFF

} Utils_EmifInitiatorId;

/**
 *******************************************************************************
 * \brief DSS MFlag enabled mode
 *******************************************************************************
 */
typedef enum {

    UTILS_DSS_MFLAG_MODE_DISABLE,
    /**< MFLAG mechanism is disabled: MFLAG out of band
     *   signal is set to 0
     */

    UTILS_DSS_MFLAG_MODE_FORCE_ENABLE,
    /**< MFLAG mechanism is enabled: MFLAG out of band
     *   signal is always set to 1 (force mode for debug)
     */

    UTILS_DSS_MFLAG_MODE_DYNAMIC_ENABLE
    /**< MFLAG mechanism is enabled and MFLAG out of
     *   band signal is dynamically set and reset depending on
     *   MFLAG rules.
     */

} Utils_DssMflagMode;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */



/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Set DSS Mflag enable mode
 *
 * \param mode  [IN] Mflag enable mode
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_setDssMflagMode(Utils_DssMflagMode mode);


/**
 *******************************************************************************
 *
 * \brief Set DSS Mflag threshold level for each display pipe
 *
 * \param displayPipeId  [IN] display pipe
 * \param thresHigh      [IN] display queue threshold
 *                            above which Mflag is NOT asserted
 * \param thresLow       [IN] display queue threshold
 *                            below which Mflag is asserted
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_setDssMflagThreshold(System_DssDispcPipes displayPipeId,
                        UInt32 thresHigh,
                        UInt32 thresLow);

/**
 *******************************************************************************
 *
 * \brief Set initator priority at DMM level
 *
 * \param initiatorId   [IN] DMM initiator ID (refer TRM for exact ID)
 * \param priValue      [IN] 0: Higest, 7: Lowest
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_setDmmPri(Utils_DmmInitiatorId initiatorId, UInt32 priValue);

/**
 *******************************************************************************
 *
 * \brief Set initator priority at EMIF level
 *
 *        NOTE: EMIF initiator ID is different from DMM initiator ID
 *
 * \param initiatorId   [IN] EMIF initiator ID (refer TRM for exact ID)
 * \param priValue      [IN] 0: Higest, 7: Lowest
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_setEmifPri(Utils_EmifInitiatorId initiatorId, UInt32 priValue);


/**
 *******************************************************************************
 *
 * \brief Enable/disable Mflag emergency signal at DMM
 *
 * \param enable   [IN] TRUE: enable, FALSE: disable
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_setDmmMflagEmergencyEnable(Bool enable);

/**
 *******************************************************************************
 *
 * \brief Set the DDR Bandwidth limiter for an initator
 *
 * \param initiatorId     [IN] Dmm Initiator ID (refer TRM for exact ID)
 *
 * \param BW_valueInMBps  [IN] BW limit value in MBytes/s
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_setBWLimiter(Utils_DmmInitiatorId initiatorId, UInt32 BW_valueInMBps);

/**
 *******************************************************************************
 *
 * \brief Set the DDR Bandwidth regulator for an initator
 *
 * \param initiatorId     [IN] Dmm Initiator ID (refer TRM for exact ID)
 *
 * \param BW_valueInMBps  [IN] BW limit value in MBytes/s
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_setBWRegulator(Utils_DmmInitiatorId initiatorId, UInt32 BW_valueInMBps);

#endif


/* @} */

