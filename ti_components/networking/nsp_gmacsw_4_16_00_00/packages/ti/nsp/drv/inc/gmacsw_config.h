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
 *   \file  gmacsw_config.h
 *
 *   \brief
 *      Header file for GMAC SW configuration
 *
 */


#ifndef GMACSW_CONFIG_H_
#define GMACSW_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>

/* OS/Posix headers */

/* Project dependency headers */
#include "ale.h"
#include "mac.h"
#include "cpdma.h"
#include "port.h"
#include "stats.h"
#include "cpts.h"
#include "mdio.h"



/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define GMACSW_CONFIG_PTYPE_P0PTYPEESC          0x00001U
/*!< Port 2 Priority Type escalate                                          */
#define GMACSW_CONFIG_PTYPE_P1PTYPEESC          0x00002U
/*!< Port 1 Priority Type escalate                                          */
#define GMACSW_CONFIG_PTYPE_P2PTYPEESC          0x00004U
/*!< Port 0 Priority Type escalate                                          */
#define GMACSW_CONFIG_PTYPE_P1_PRI1_SHAPE_EN    0x00008U
/*!< Port 1 Queue Priority 1 Tx Shape Enable                                */
#define GMACSW_CONFIG_PTYPE_P1_PRI2_SHAPE_EN    0x00010U
/*!< Port 1 Queue Priority 2 Tx Shape Enable                                */
#define GMACSW_CONFIG_PTYPE_P1_PRI3_SHAPE_EN    0x00020U
/*!< Port 1 Queue Priority 3 Tx Shape Enable                                */
#define GMACSW_CONFIG_PTYPE_P2_PRI1_SHAPE_EN    0x00040U
/*!< Port 2 Queue Priority 1 Tx Shape Enable                                */
#define GMACSW_CONFIG_PTYPE_P2_PRI2_SHAPE_EN    0x00080U
/*!< Port 2 Queue Priority 2 Tx Shape Enable                                */
#define GMACSW_CONFIG_PTYPE_P2_PRI3_SHAPE_EN    0x00100U
/*!< Port 2 Queue Priority 3 Tx Shape Enable                                */


#define GMACSW_CONFIG_CPSW_ENVLANAWARE          (0x00001U)
/*!< VLAN aware mode                                                        */
#define GMACSW_CONFIG_CPSW_RXVLANENCAP          (0x00002U)
/*!< Port 2 VLAN Encapsulation                                              */
#define GMACSW_CONFIG_CPSW_FIFOLOOPBACK         (0x00004U)
/*!< FIFO Loopback mode                                                     */
#define GMACSW_CONFIG_CPSW_DLR_EN               (0x00008U)
/*!< Device Level Ring mode                                                 */
#define GMACSW_CONFIG_CPSW_EEE_EN               (0x00010U)
/*!< Energy Efficient Ethernet mode                                         */


/* GMACSW default config*/

#define GMACSW_DEFAULT_ESCPRI_LD_VAL                        (0U)

#define GMACSW_DEFAULT_MDIOBUSFREQ                          (2200000U)
#define GMACSW_DEFAULT_MDIOCLOCKFREQ                        (200000000U)
#define GMACSW_DEFAULT_MAINCLKFREQ                          (125000000U)

/* Default Ale Config*/
#define GMACSW_DEFAULT_ENABLEALE                            (1U)
#define GMACSW_DEFAULT_CLEARTABLE                           (1U)
#define GMACSW_DEFAULT_AGEOUTNOW                            (0U)
#define GMACSW_DEFAULT_LEARNNOVID                           (0U)
#define GMACSW_DEFAULT_ENVID0MODE                           (0U)
#define GMACSW_DEFAULT_ENABLEOUIDENY                        (0U)
#define GMACSW_DEFAULT_RATELIMITTX                          (0U)
#define GMACSW_DEFAULT_ALEVLANAWARE                         (1U)
#define GMACSW_DEFAULT_ENAUTHMODE                           (0U)
#define GMACSW_DEFAULT_ENRATELIMIT                          (0U)
/* prescalar divides down to 1ms interval*/
#define GMACSW_DEFAULT_ALEPRESCALE                          (GMACSW_DEFAULT_MAINCLKFREQ / 1000U)
/* old val=0xAE62DU*/
#define GMACSW_DEFAULT_UNK_FORCE_UNTAG_EGR                      ((uint32_t)63U)
#define GMACSW_DEFAULT_UNK_REGMCAST_FLOODMASK                   6U
#define GMACSW_DEFAULT_UNK_MCAST_FLOODMASK                      6U
#define GMACSW_DEFAULT_UNK_VLANMEMLIST                          ((uint32_t)63U)
#define CPGMAC_DEFAULT_UNK_FORCE_UNTAG_EGR                      7U
#define CPGMAC_DEFAULT_UNK_REGMCAST_FLOODMASK                   0U
#define CPGMAC_DEFAULT_UNK_MCAST_FLOODMASK                      0U
#define CPGMAC_DEFAULT_UNK_VLANMEMLIST                          4U

/* Default Ale Port Config*/
#define GMACSW_DEFAULT_BCASTLIMIT                               0U
#define GMACSW_DEFAULT_MCASTLIMIT                               0U
#define GMACSW_DEFAULT_LEARN                                    0U
#define GMACSW_DEFAULT_NOLEARN                                  1U
#define GMACSW_DEFAULT_VIDINGRESSCHECK                          0U
#define GMACSW_DEFAULT_DROPUNTAGGED                             0U

/* Default Dma config*/
#define GMACSW_DEFAULT_DMA_PORTPRI                              0U
#define GMACSW_DEFAULT_DMA_PORTCFI                              0U
#define GMACSW_DEFAULT_DMA_PORTVID                              1U
#define GMACSW_DEFAULT_RXBUFOFF                                 0U
#define GMACSW_DEFAULT_RXCEF                                    0U
#define GMACSW_DEFAULT_CMDIDLE                                  0U
#define GMACSW_DEFAULT_RXOFFLEN                                 0U
#define GMACSW_DEFAULT_RXOWNERSHIP                              0U
#define GMACSW_DEFAULT_TXPTYPE                                  1U
#define GMACSW_DEFAULT_SL0_PRI0                                 0U
#define GMACSW_DEFAULT_SL0_PRI1                                 0U
#define GMACSW_DEFAULT_SL0_PRI2                                 0U
#define GMACSW_DEFAULT_SL0_PRI3                                 0U
#define GMACSW_DEFAULT_SL1_PRI0                                 1U
#define GMACSW_DEFAULT_SL1_PRI1                                 1U
#define GMACSW_DEFAULT_SL1_PRI2                                 1U
#define GMACSW_DEFAULT_SL1_PRI3                                 1U

/* Default MAC  config*/
#define GMACSW_DEFAULT_MAC_PORTPRI                              0U
#define GMACSW_DEFAULT_MAC_PORTCFI                              0U
#define GMACSW_DEFAULT_MAC_PORTVID                              ((uint32_t)1U)
#define GMACSW_DEFAULT_PASSCRC                                  0U
#define GMACSW_DEFAULT_RXCMFEN                                  0U
#define GMACSW_DEFAULT_RXCSFEN                                  0U
#define GMACSW_DEFAULT_RXCEFEN                                  0U
#define GMACSW_DEFAULT_EXTEN                                    1U
#define GMACSW_DEFAULT_GIGFORCE                                 0U
#define GMACSW_DEFAULT_IFCTLB                                   0U
#define GMACSW_DEFAULT_IFCTLA                                   1U
#define GMACSW_DEFAULT_MAC_CMDIDLE                              0U
#define GMACSW_DEFAULT_TXSHORTGAPEN                             0U
#define GMACSW_DEFAULT_GIGABITEN                                1U
#define GMACSW_DEFAULT_TXPACINGEN                               0U
#define GMACSW_DEFAULT_GMIIEN                                   1U
#define GMACSW_DEFAULT_TXFLOWEN                                 1U
#define GMACSW_DEFAULT_RXFLOWEN                                 1U
#define GMACSW_DEFAULT_LOOPBKEN                                 0U
#define GMACSW_DEFAULT_RXMAXLEN                                 1518U
#define GMACSW_DEFAULT_FD                                       1U

#define GMACSW_INITPARAM_SPEED0        0U
#define GMACSW_INITPARAM_DUPLEX0    0U
#define GMACSW_INITPARAM_INTPHY0    1U
#define GMACSW_INITPARAM_BROADEN0    0U
#define GMACSW_INITPARAM_MULTIEN0    0U
#define GMACSW_INITPARAM_SPEED1        0U
#define GMACSW_INITPARAM_DUPLEX1    0U
#define GMACSW_INITPARAM_INTPHY1    1U
#define GMACSW_INITPARAM_BROADEN1    0U
#define GMACSW_INITPARAM_MULTIEN1    0U
#define GMACSW_INITPARAM_PROMEN        0U
#define GMACSW_INITPARAM_VLANAWARE    1U

/* ALE time out value in ms */
#define ALE_AGE_OUT_TIME_IN_MS        300000U


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \defgroup GMACSW_CONFIG_DEFINTIONS GMACSW Driver Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the
 *  configuration structure needed to open the driver.
 *
 *  @{
 */

/*! Callback function type that application can supply as part of GMACSW configuration structure */
typedef void (*GMACSW_LinkStatusCallback)(uint32_t phy, uint32_t linkStatus);

/*!
 *  \brief  GMACSW_Config
 *
 *  The config structure defines how the GMAC_SW peripheral should operate. It is
 *  passed to the device when the device is opened, and remains in effect
 *  until the device is closed.
 */
typedef struct GMACSW_CONFIG_
{
    /*!
     * \brief       MTU for the interfaces.
     */
    uint32_t                    PktMTU;
    /*!
     * \brief      Mask of MAC ports enabled.
     */
    uint8_t                     activeMACPortMask;
    /*!
     * \brief      Configuration Mode flags for Switch control
     */
    uint32_t                    cpswCtlModeFlags;
    /*!
     * \brief      Configuration Mode flags for Switch PTYPE
     */
    uint32_t                    cpswPtypeModeFlags;
    /*!
     * \brief      Escalate priority load value
     */
    uint8_t                     escPriLdVal;
    /*!
     * \brief      Configuration Mode flag for digital loopback mode
     */
    uint32_t                    dlbMode;
    /*!
     * \brief      Function pointer to application's link status callback
     */
    GMACSW_LinkStatusCallback   linkStatusCallback;

    /*!
     * \brief      CPDMA (Host Port) Init Configuration
     */
    CPDMA_Config                cpdmaInitCfg;

    /*!
     * \brief      CPGMAC SL Init Configurations
     */
    MAC_Config                  macInitCfg[MAC_NUM_PORTS];

    /*!
     * \brief      ALE Init Configuration
     */
    ALE_Config                  aleCfg;

    /*!
     * \brief      Statistics Init Configuration
     */
    STATS_Config                statsCfg;

    /*!
     * \brief      CPTS Init Configuration
     */
    CPTS_Config                 cptsCfg;

    /*!
     * \brief      MDIO Init configuration
     */
    MDIO_Config                 mdioCfg;
}
GMACSW_Config;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/*!
 *  \defgroup GMACSW_CONFIG_FUNCTION_DEFINTIONS GMACSW Configuration Functions
 *
 *  This group contains the functions that can be used
 *
 *  @{
 */

/*!
 *  @b Description
 *  @n The GMACSW_getConfig() function is not defined as part of the driver, but
 *     it is declared here. It can be defined as part of the application or stack that
 *     initializaes the driver. It can be used to return a driver configuration suitable
 *     for initializing the driver via the GMACSW_open() API.
 *
 *     This function is called in the NDK2NSP adaptation layer that accompanies this driver
 *     and so if the NDK is used in the application, this function must exist.
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  None
 *
 *  \retval
 *      Non-NULL pointer to a GMACSW_Config instance.
 *
 */
extern GMACSW_Config *GMACSW_getConfig(void);

/*!
 *  @b Description
 *  @n This function is a helper routine provided by the driver to return a valid
 *     default configuration appropriate for the device/hardware. The returned structure
 *     can be modified/customized by the application and then can be used to in the
 *     driver open function.
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  None
 *
 *  \retval
 *      Non-NULL pointer to a GMACSW_Config instance.
 *
 */
extern GMACSW_Config *GMACSW_CONFIG_getDefaultConfig(void);

/*!
 *  @b Description
 *  @n This function is a helper routine provided by the driver to return a valid
 *     default configuration for digital loopback mode. The returned structure
 *     can be modified/customized by the application and then can be used to in the
 *     driver open function. This mode is intended to be used for testing, as in this
 *     mode all transmitted packets are immediately looped back to become received
 *     packets.
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  None
 *
 *  \retval
 *      Non-NULL pointer to a GMACSW_Config instance.
 *
 */
extern GMACSW_Config *GMACSW_CONFIG_getDLBConfig(void);

/*!
 *  @b Description
 *  @n This function is a helper routine provided by the driver to return a valid
 *     default configuration for VLAN mode. The returned structure
 *     can be modified/customized by the application and then can be used to in the
 *     driver open function. This mode is intended to be used when transmitting
 *     VLAN-tagged packets.
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  None
 *
 *  \retval
 *      Non-NULL pointer to a GMACSW_Config instance.
 *
 */
extern GMACSW_Config *GMACSW_CONFIG_getVLANConfig(void);

/*!
 *  @}
 */

/*!
 *  @}
 */

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* GMACSW_CONFIG_H_ */
