/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 *   \file  stats.h
 *
 *   \brief
 *          Header file for STATISTICS module of the GMACSW hardware.
 *
 */


#ifndef STATS_H_
#define STATS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*! STATS module return codes */
#define STATS_SUCCESS           (0x00000000U)
#define STATS_FAILURE           (0xFFFFFFFFU)
#define STATS_UNKNOWN_IOCTL     (0x00000001U)
#define STATS_MALFORMED_IOCTL   (0x00000002U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \addtogroup  GMACSW_IOCTLS
 *
 *  @{
 */

/*!
 *  \brief  The statistics module IOCTL enums
 */
enum STATS_IOCTL_
{
    GMACSW_IOCTL_STATS_BASE         = 0x00020000,
    /*! STATS clear statistics IOCTL value. IOCTL param should be NULL. */
    GMACSW_IOCTL_STATS_CLEAR_STATS  = 0x00020000,
    /*! STATS get statistics IOCTL value. IOCTL param should be structure of type STATS_Statistics. */
    GMACSW_IOCTL_STATS_GET_STATS    = 0x00020001
};

/*!
 * @}
 */



/*!
 *  \brief  GMACSW Statistics Structure
 *
 *  The statistics structure is used to hold, in software, the
 *  hardware statistics reported by the STATS module of the GMACSW.
 */
typedef struct STATS_STATISTICS_
{
    uint64_t RxGoodFrames;     /*!< Good Frames Received                      */
    uint64_t RxBCastFrames;    /*!< Good Broadcast Frames Received            */
    uint64_t RxMCastFrames;    /*!< Good Multicast Frames Received            */
    uint64_t RxPauseFrames;    /*!< PauseRx Frames Received                   */

    uint64_t RxCRCErrors;      /*!< Frames Received with CRC Errors           */
    uint64_t RxAlignCodeErrors;/*!< Frames Received with Alignment/Code Errors*/
    uint64_t RxOversized;      /*!< Oversized Frames Received                 */
    uint64_t RxJabber;         /*!< Jabber Frames Received                    */

    uint64_t RxUndersized;     /*!< Undersized Frames Received                */
    uint64_t RxFragments;      /*!< Rx Frame Fragments Received               */
    uint64_t reserved;         /*!< Rx Frames Filtered Based on Address       */
    uint64_t reserved2;        /*!< Rx Frames Filtered Based on QoS Filtering */

    uint64_t RxOctets;         /*!< Total Received Bytes in Good Frames       */
    uint64_t TxGoodFrames;     /*!< Good Frames Sent                          */
    uint64_t TxBCastFrames;    /*!< Good Broadcast Frames Sent                */
    uint64_t TxMCastFrames;    /*!< Good Multicast Frames Sent                */

    uint64_t TxPauseFrames;    /*!< PauseTx Frames Sent                       */
    uint64_t TxDeferred;       /*!< Frames Where Transmission was Deferred    */
    uint64_t TxCollision;      /*!< Total Frames Sent With Collision          */
    uint64_t TxSingleColl;     /*!< Frames Sent with Exactly One Collision    */

    uint64_t TxMultiColl;      /*!< Frames Sent with Multiple Colisions       */
    uint64_t TxExcessiveColl;  /*!< Tx Frames Lost Due to Excessive Collisions*/
    uint64_t TxLateColl;       /*!< Tx Frames Lost Due to a Late Collision    */
    uint64_t TxUnderrun;       /*!< Tx Frames Lost with Tx Underrun Error     */

    uint64_t TxCarrierSLoss;   /*!< Tx Frames Lost Due to Carrier Sense Loss  */
    uint64_t TxOctets;         /*!< Total Transmitted Bytes in Good Frames    */
    uint64_t Frame64;          /*!< Total Tx&Rx with Octet Size of 64         */
    uint64_t Frame65t127;      /*!< Total Tx&Rx with Octet Size of 65 to 127  */

    uint64_t Frame128t255;     /*!< Total Tx&Rx with Octet Size of 128 to 255 */
    uint64_t Frame256t511;     /*!< Total Tx&Rx with Octet Size of 256 to 511 */
    uint64_t Frame512t1023;    /*!< Total Tx&Rx with Octet Size of 512 to 1023*/
    uint64_t Frame1024tUp;     /*!< Total Tx&Rx with Octet Size of >=1024     */

    uint64_t NetOctets;        /*!< Sum of all Octets Tx or Rx on the Network */
    uint64_t RxSOFOverruns;    /*!< Total Rx Start of Frame Overruns          */
    uint64_t RxMOFOverruns;    /*!< Total Rx Middle of Frame Overruns         */
    uint64_t RxDMAOverruns;    /*!< Total Rx DMA Overruns                     */
}
STATS_Statistics;

/*!
 *  \addtogroup GMACSW_CONFIG_DEFINTIONS
 *
 *  @{
 *
 *  \defgroup STATS_CONFIG_DEFINITIONS STATS Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the STATS
 *  configuration structure which is part of the top-level GMACSW configuration structure.
 *
 *  @{
 *
 */

/*!
 *  \brief STATS Init Configuration
 *
 *  Configuration information for STATS module provided during initialization.
 */
typedef struct STATS_MODULE_CONFIG_
{
    /*! Flag to indicate if the statistics gathering is enabled or disabled. */
    uint32_t enableStatistics;
}
STATS_Config;

/*!
 * @}
 * @}
 */

/*!
 * Definition of opaque handle for STATS_STATE_ object
 */
typedef struct STATS_STATE_ *STATS_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern STATS_Handle STATS_open(STATS_Config *pStatsConfig, uint32_t activeMACPortMask);
extern uint32_t STATS_close(STATS_Handle hStats);

extern uint32_t STATS_ioctl(STATS_Handle hStats, uint32_t cmd, void *param, uint32_t size);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _STATS_H_ */

