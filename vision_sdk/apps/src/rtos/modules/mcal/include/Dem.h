/* ======================================================================
 *   Copyright (C) 2015-2017 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     Dem.h
 *
 *  \brief    This is a sample Diagnostic Event Manager interface header file.
 *            This file should be replaced by original Dem.h that is part of
 *            Integration AUTOSAR stack.
 */

#ifndef DEM_H_
#define DEM_H_

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/

#ifdef __cplusplus
extern "C"
{
#endif

#define DEM_AR_RELEASE_MAJOR_VERSION        (4U)
#define DEM_AR_RELEASE_MINOR_VERSION        (2U)
#define DEM_AR_RELEASE_REVISION_VERSION     (1U)

#define DEM_SW_MAJOR_VERSION                (1U)
#define DEM_SW_MINOR_VERSION                (9U)
#define DEM_SW_PATCH_VERSION                (0U)
#define DEM_AR_MAJOR_VERSION                (DEM_AR_RELEASE_MAJOR_VERSION)
#define DEM_AR_MINOR_VERSION                (DEM_AR_RELEASE_MINOR_VERSION)
#define DEM_AR_PATCH_VERSION                (DEM_AR_RELEASE_REVISION_VERSION)

typedef enum
{
    DEM_EVENT_STATUS_PASSED,
    DEM_EVENT_STATUS_FAILED,
    DEM_EVENT_STATUS_PREPASSED,
    DEM_EVENT_STATUS_PREFAILED,
    DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
} Dem_EventStatus;

typedef uint16 Dem_EventIdType;
typedef uint8  Dem_EventStatusType;

#define DemConf_DemEventParameter_DemEventParameter_0 (0x1U)

/*
 * Ethernet MCAL driver error return
 */
/* Requirements : SWS_Eth_00173 */
/** \brief Ethernet Controller Access Failure */
#define DemConf_DemEventParameter_ETH_E_ACCESS                    ((Dem_EventIdType) 100U)

/* Requirements : SWS_Eth_00174 */
/** \brief Ethernet Frames Lost */
#define DemConf_DemEventParameter_ETH_E_RX_FRAMES_LOST            ((Dem_EventIdType) 101U)

/** \brief Monitors invalid Ethernet frames during reception */
/* Requirements : SWS_Eth_00219 */
#define DemConf_DemEventParameter_ETH_E_CRC                       ((Dem_EventIdType) 102U)

/** \brief Frame Size Underflow */
/* Requirements : SWS_Eth_00220 */
#define DemConf_DemEventParameter_ETH_E_UNDERSIZEFRAME            ((Dem_EventIdType) 103U)

/** \brief Frame Size Overflow */
/* Requirements : SWS_Eth_00221 */
#define DemConf_DemEventParameter_ETH_E_OVERSIZEFRAME             ((Dem_EventIdType) 104U)

/** \brief Frame Alignment Error */
/* Requirements : SWS_Eth_00222 */
#define DemConf_DemEventParameter_ETH_E_ALIGNMENT                 ((Dem_EventIdType) 105U)

/** \brief Single Frame Collision */
/* Requirements : SWS_Eth_00223 */
#define DemConf_DemEventParameter_ETH_E_SINGLECOLLISION           ((Dem_EventIdType) 106U)

/** \brief Multiple Frame Collision */
/* Requirements : SWS_Eth_00224 */
#define DemConf_DemEventParameter_ETH_E_MULTIPLECOLLISION         ((Dem_EventIdType) 107U)

/** \brief Late Frame Collision */
/* Requirements : SWS_Eth_00225 */
#define DemConf_DemEventParameter_ETH_E_LATECOLLISION             ((Dem_EventIdType) 108U)

/**
 *  \brief An hardware error occurred during asynchronous or synchronous SPI
 *  transmit.
 *  This Extended Production Error shall be issued when any error bit inside
 *  the SPI hardware transmit status register is raised.
 */
#define DemConf_DemEventParameter_ETH_E_HARDWARE_ERROR            ((Dem_EventIdType) 109U)

/*
 * Ethernet Transceiver MCAL driver error return
 */
/* Requirements : SWS_EthTrcv_00105 */
/** \brief Ethernet Transceiver Controller Access Failure */
#define DemConf_DemEventParameter_ETHTRCV_E_ACCESS                ((Dem_EventIdType) 300U)

/**
 *  \brief An hardware error occurred during asynchronous or synchronous SPI
 *  transmit.
 *  This Extended Production Error shall be issued when any error bit inside
 *  the SPI hardware transmit status register is raised.
 */
#define DemConf_DemEventParameter_SPI_E_HARDWARE_ERROR            ((Dem_EventIdType) 200U)

/**
 *  This Extended Production Error shall be issued when GPIO
 *  System status register reset fails.
 */
#define DemConf_DemEventParameter_PORT_E_HARDWARE_ERROR           ((Dem_EventIdType) 400U)

/**
 *  This Extended Production Error shall be issued when GPT
 *  Timer register reset fails.
 */
#define DemConf_DemEventParameter_GPT_E_HARDWARE_ERROR            ((Dem_EventIdType) 500U)

/**
 *  This Extended Production Error shall be issued when
 *  MCU Check Mode fails.
 */
#define DemConf_DemEventParameter_MCU_E_MODE_FAILURE              ((Dem_EventIdType) 600U)

/**
 *  This Extended Production Error shall be issued when CAN
 *  register setting timeout occurs
 */
#define DemConf_DemEventParameter_CAN_E_HARDWARE_ERROR            ((Dem_EventIdType) 700U)

/**
 *  This Extended Production Error shall be issued when an event was received
 *  from an in-valid core. (Wrong core id)
 */
#define DemConf_DemEventParameter_CDD_IPC_E_REMOTE_CORE_ERROR     ((Dem_EventIdType) 800U)

/**
 *  This Extended Production Error shall be issued when send event API
 *  cannot find enough space on configured mailbox and FIFO combination
 */
#define DemConf_DemEventParameter_CDD_IPC_E_SEND_EVENT_FIFO_ERROR ((Dem_EventIdType) 801U)

/**
 *  This Extended Production Error shall be issued when ADC
 *  register setting timeout occurs
 */
#define DemConf_DemEventParameter_ADC_E_HARDWARE_ERROR ((Dem_EventIdType) 900U)

/*TI_INSPECTED 63 D : MISRAC_2012_R8.6
 * "Reason - Definition for below prototyped procedure
 *  is external to lib, defined in app." */
void Dem_ReportErrorStatus(Dem_EventIdType     eventId,
                           Dem_EventStatusType eventStatus);

#define DemConf_DemEventParameter_MCU_E_CLOCK_FAILURE (0x10U)
#ifdef __cplusplus
}
#endif

#endif  /* DEM_H_ */
