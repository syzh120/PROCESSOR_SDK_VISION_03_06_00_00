/*!
 *  \file   gmac_sw.c
 *
 *  \brief  GMAC_SW device abstraction layer APIs.
 *
 *   This file contains the device abstraction layer APIs for GMAC_SW RGMII.
 */

/*
 * Copyright (C) 2010-2013 Texas Instruments Incorporated - http://www.ti.com/
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

#include "hw_types.h"
#include "hw_gmacsw_ale.h"
#include "hw_gmacsw_cpdma.h"
#include "hw_gmacsw_port.h"
#include "hw_gmacsw_sl.h"
#include "hw_gmacsw_ss.h"
#include "hw_gmacsw_wr.h"

#include "gmac_sw.h"

/*!*****************************************************************************
*                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define GMAC_SW_CORE_OFFSET                   (0x10u)
#define GMAC_SW_MAX_HEADER_DESC               (0x08u)
#define CPDMA_P0_DEF_TX_MAP                (0x76543210u)
#define ALE_ENTRY_WORDS                    (0x03u)
#define CPDMA_ERR_CHANNEL_POS              (0xFFu)
#define GMAC_SW_PORT_DUAL_MAC_MODE            (0x01u <<                        \
                                            GMAC_SW_PORT_P0_TX_IN_CTL_TX_IN_SEL_SHIFT)
#define GMAC_SW_PORT_RATE_LIM_MODE            (0x02u <<                        \
                                            GMAC_SW_PORT_P0_TX_IN_CTL_TX_IN_SEL_SHIFT)

#define GMAC_SW_ALE_PORTCTL(portNum)        (GMAC_SW_ALE_PORTCTL + portNum * 4)


/*!*****************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/
/*!
 * \brief   Resets the GMAC_SW_ Subsystem.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Subsystem
 *
 * \return  None
 **/
void GMAC_SW_SSReset(uint32_t baseAddr)
{
    /* Reset the GMAC_SW_ */
    HWREG(baseAddr + GMAC_SW_SS_SOFT_RESET) = GMAC_SW_SS_SOFT_RESET_SOFT_RESET;

    while(HWREG(baseAddr + GMAC_SW_SS_SOFT_RESET)
          & GMAC_SW_SS_SOFT_RESET_SOFT_RESET);
}

/*!
 * \brief   Force the CPGMAC_SL into gigabit mode if the input GMII_MTCLK has
 *          been stopped by the PHY
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 *
 * \return  None
 *
 **/
void GMAC_SW_SlGigModeForceEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_SL_MACCONTROL) |= GMAC_SW_SL_MACCONTROL_GIG_FORCE;
}

/*!
 * \brief   Enables the fullduplex and gigabit mode to be selected
 *          from the FULLDUPLEX_IN and GIG_IN input signals and not from the
 *          fullduplex and gig bits in this register. The FULLDUPLEX_MODE bit
 *          reflects the actual fullduplex mode selected
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 *
 * \return  None
 *
 **/
void GMAC_SW_SlControlExtEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_SL_MACCONTROL) |= GMAC_SW_SL_MACCONTROL_EXT_EN;
}


/*!
 * \brief   Disables the CPGMAC_SL gigabit mode if the input GMII_MTCLK has
 *          been stopped by the PHY
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 *
 * \return  None
 *
 **/
void GMAC_SW_SlGigModeForceDisable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_SL_MACCONTROL) &= ~GMAC_SW_SL_MACCONTROL_GIG_FORCE;
}

/*!
 * \brief   Sets the Transfer mode, 10/100 or gigabit mode  and the duplex
 *          mode  for the sliver.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 * \param   mode        The transfer mode
 *    'mode' can take one of the below values. \n
 *         GMAC_SW_SLIVER_NON_GIG_HALF_DUPLEX - 10/100 Mbps mode, half duplex. \n
 *         GMAC_SW_SLIVER_NON_GIG_FULL_DUPLEX - 10/100 Mbps mode, full duplex. \n
 *         GMAC_SW_SLIVER_GIG_FULL_DUPLEX - 1000 Mbps mode, full duplex. \n
 *         Note: for 10Mbps mode, GMAC_SW_SLIVER_INBAND has to be configured. \n
 *
 * \return  None
 *
 **/
void GMAC_SW_SlTransferModeSet(uint32_t baseAddr, uint32_t mode)
{
    HWREG(baseAddr + GMAC_SW_SL_MACCONTROL) &= ~(GMAC_SW_SL_MACCONTROL_GIG
                                              | GMAC_SW_SL_MACCONTROL_FULLDUPLEX);

    HWREG(baseAddr + GMAC_SW_SL_MACCONTROL) |= mode;
}

/*!
 * \brief   Returns the MAC Status. The value will be the contents of the MAC
 *          status register.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 * \param   statFlag    Status flags to be read.
 *            statFlag can take an OR combination of the below values. \n
 *              GMAC_SW_SLIVER_STATE - The Sliver state. \n
 *              GMAC_SW_SLIVER_EXT_GIG_INPUT_BIT - The EXT_GIG input bit mask.\n
 *              GMAC_SW_SLIVER_EXT_FULL_DUPLEX_BIT - The EXT_FULLDUPLEX input
 *                                                  bit mask. \n
 *              GMAC_SW_SLIVER_RX_FLOWCTRL - The receive flow control active. \n
 *              GMAC_SW_SLIVER_TX_FLOWCTRL - The transmit flow control.
 *
 *
 * \return  MAC Status
 *            The MAC status register value returned can be compared against
 *            the below tokens. \n
 *              GMAC_SW_SLIVER_STATE_IDLE - The Sliver is in idle state. \n
 *              GMAC_SW_SLIVER_EXT_GIG_INPUT_HIGH - The EXT_GIG input
 *                                                 bit is in HIGH state.\n
 *              GMAC_SW_SLIVER_EXT_FULL_DUPLEX_HIGH - The EXT_FULLDUPLEX input
 *                                                   bit is in HIGH state. \n
 *              GMAC_SW_SLIVER_RX_FLOWCTRL_ACTIVE - The receive flow control is
 *                                                 active. \n
 *              GMAC_SW_SLIVER_TX_FLOWCTRL_ACTIVE - The pause time period is
 *                                                 observed for a received
 *                                                 pause frame
 *
 **/
uint32_t GMAC_SW_SlMACStatusGet(uint32_t baseAddr, uint32_t statFlag)
{
    /* Return the required status only */
    return (HWREG(baseAddr + GMAC_SW_SL_MACSTATUS) & statFlag);
}

/*!
 * \brief   Resets the GMAC_SW_ Sliver Logic.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 *
 * \return  None
 *
 **/
void GMAC_SW_SlReset(uint32_t baseAddr)
{
    /* Reset the sliver logic */
    HWREG(baseAddr + GMAC_SW_SL_SOFT_RESET) = GMAC_SW_SL_SOFT_RESET_SOFT_RESET;

    /* Wait till the reset completes */
    while(GMAC_SW_SL_SOFT_RESET_SOFT_RESET ==
          ((HWREG(baseAddr + GMAC_SW_SL_SOFT_RESET))
           & GMAC_SW_SL_SOFT_RESET_SOFT_RESET));
}


/*!
 * \brief   Sets the maximum length for received frame.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 * \param   rxMaxLen    Maximum length for a received frame
 *     The default value for 'rxMaxLen' is 1518. The maximum value
 *     which can be set is 16383.
 *
 * \return  None
 *
 **/
void GMAC_SW_SlRxMaxLenSet(uint32_t baseAddr, uint32_t rxMaxLen)
{
    /* Set the desired maximum length */
    HWREG(baseAddr + GMAC_SW_SL_RX_MAXLEN) = rxMaxLen;
}

/*!
 * \brief   Enables GMII for the sliver.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 *
 * \return  None
 **/
void GMAC_SW_SlGMIIEnable(uint32_t baseAddr)
{
   HWREG(baseAddr + GMAC_SW_SL_MACCONTROL) |= GMAC_SW_SL_MACCONTROL_GMII_EN;
}

/*!
 * \brief   Enables RGMII for the sliver.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Sliver Module registers.
 *
 * \return  None
 **/
void GMAC_SW_SlRGMIIEnable(uint32_t baseAddr)
{
   HWREG(baseAddr + GMAC_SW_SL_MACCONTROL) |= (GMAC_SW_SL_MACCONTROL_GMII_EN
                                            | GMAC_SW_SL_MACCONTROL_IFCTL_A
                                            | GMAC_SW_SL_MACCONTROL_IFCTL_B);
}

/*!
 * \brief   Resets the GMAC_SW_ Wrapper module.
 *
 * \param   baseAddr    Base address of the GMAC_SW_ Wrapper Module
 *
 * \return  None
 **/
void GMAC_SW_WrReset(uint32_t baseAddr)
{
    /* Reset the GMAC_SW Wrapper */
    HWREG(baseAddr + GMAC_SW_WR_SOFT_RESET) = GMAC_SW_WR_SOFT_RESET_SOFT_RESET;

    while(HWREG(baseAddr + GMAC_SW_WR_SOFT_RESET)
          & GMAC_SW_WR_SOFT_RESET_SOFT_RESET);
}

/*!
 * \brief   Resets the Control Register of GMAC_SW Wrapper module
 *
 * \param   baseAddr    Base address of the GMAC_SW Wrapper Module
 *
 * \return  None
 **/
void GMAC_SW_WrControlRegReset(uint32_t baseAddr)
{
    /* Reset the GMAC_SW Wrapper control Register */
    HWREG(baseAddr + GMAC_SW_WR_CONTROL) =  GMAC_SW_WR_CONTROL_MMR_RESET;
}

/*!
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the GMAC_SW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          GMAC_SW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          GMAC_SW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          GMAC_SW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          GMAC_SW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
void GMAC_SW_WrCoreIntEnable(uint32_t baseAddr, uint32_t core,
                         uint32_t channel, uint32_t intFlag)
{
    HWREG(baseAddr + GMAC_SW_WR_C_RX_THRESH_EN(core) + intFlag) |= (1 << channel);
}

/*!
 * \brief   Disables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of thei GMAC_SW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be disabled
 *    'intFlag' can take one of the below values. \n
 *          GMAC_SW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          GMAC_SW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          GMAC_SW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          GMAC_SW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
void GMAC_SW_WrCoreIntDisable(uint32_t baseAddr, uint32_t core,
                          uint32_t channel, uint32_t intFlag)
{
    HWREG(baseAddr + GMAC_SW_WR_C_RX_THRESH_EN(core) + intFlag) &=
                                                            ~(1 << channel);
}

/*!
 * \brief   Returns the interrupt status of the core for the specified
 *          channel
 *
 * \param   baseAddr    Base address of thei GMAC_SW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt status to be read
 *    'intFlag' can take one of the below values. \n
 *          GMAC_SW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          GMAC_SW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          GMAC_SW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          GMAC_SW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  same as intFlag if the status is set
 *          '0' if the status is cleared
 **/
uint32_t GMAC_SW_WrCoreIntStatusGet(uint32_t baseAddr, uint32_t core,
                                    uint32_t channel, uint32_t intFlag)
{
    return (HWREG(baseAddr + GMAC_SW_WR_C_RX_THRESH_STAT(core) + intFlag)
            &  (1 << channel));
}

/*!
 * \brief   Returns the RGMII status requested.
 *
 * \param   baseAddr    Base address of the GMAC_SW Wrapper Module
 * \param   statFlag    Status to be checked
 *    'statFlag' can take a combination of the below values. \n
 *        GMAC_SW_RGMII2_DUPLEX - Duplex of RGMII2 \n
 *        GMAC_SW_RGMII2_SPEED - Speed of RGMII2 \n
 *        GMAC_SW_RGMII2_LINK_STAT - Link Status of RGMII2 \n
 *        GMAC_SW_RGMII1_DUPLEX - Duplex of RGMII1 \n
 *        GMAC_SW_RGMII1_SPEED - Speed of RGMII1 \n
 *        GMAC_SW_RGMII1_LINK_STAT - Link Status of RGMII1 \n
 *
 *    The returned value can be compared agains the below values \n
 *        GMAC_SW_RGMII2_DUPLEX_FULL - RGMII2 full duplex \n
 *        GMAC_SW_RGMII2_DUPLEX_HALF - RGMII2 half duplex \n
 *        GMAC_SW_RGMII2_SPEED_10M - Speed is 10 Mbps \n
 *        GMAC_SW_RGMII2_SPEED_100M - Speed is 100 Mbps \n
 *        GMAC_SW_RGMII2_SPEED_1000M - Speed is 1000 Mbps \n
 *        GMAC_SW_RGMII2_LINK_UP - RGMII2 link is up\n
 *        GMAC_SW_RGMII2_LINK_DOWN - RGMII2 link is down \n
 *        GMAC_SW_RGMII1_DUPLEX_FULL - RGMII1 full duplex \n
 *        GMAC_SW_RGMII1_DUPLEX_HALF - RGMII1 half duplex \n
 *        GMAC_SW_RGMII1_SPEED_10M - Speed is 10 Mbps \n
 *        GMAC_SW_RGMII1_SPEED_100M - Speed is 100 Mbps \n
 *        GMAC_SW_RGMII1_SPEED_1000M - Speed is 1000 Mbps \n
 *        GMAC_SW_RGMII1_LINK_UP - RGMII1 link is up\n
 *        GMAC_SW_RGMII1_LINK_DOWN - RGMII1 link is down \n
 *
 * \return  Status of RGMII. Return value can be compared agains the same
 *          statFlag passed.
 **/
uint32_t GMAC_SW_WrRGMIIStatusGet(uint32_t baseAddr, uint32_t statFlag)
{
    return (HWREG(baseAddr + GMAC_SW_WR_RGMII_CTL) & statFlag);
}

/*!
 * \brief   Initializes the ALE. The ALE logic is reset and the ALE table
 *          entries are cleared.
 *
 * \param   baseAddr    Base address of the ALE module
 *
 * \return  None
 **/
void GMAC_SW_ALEInit(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) = (GMAC_SW_ALE_CONTROL_CLEAR_TABLE
                                          | GMAC_SW_ALE_CONTROL_ENABLE_ALE);
}

/*!
 * \brief   Age Out Address Table. The Untouched ageable ALE table
 *          entries are cleared.
 *
 * \param   baseAddr    Base address of the ALE module
 *
 * \return  None
 **/
void GMAC_SW_ALEAgeOut(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) |= GMAC_SW_ALE_CONTROL_AGE_OUT_NOW;

    while(GMAC_SW_ALE_CONTROL_AGE_OUT_NOW & (HWREG(baseAddr + GMAC_SW_ALE_CONTROL)));

}

/*!
 * \brief   Sets the Broadcast Packet Rate Limit
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   bplVal        The Broadcast Packet Rate Limit Value
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEBroadcastRateLimitSet(uint32_t baseAddr, uint32_t portNum,
                                  uint32_t bplVal)
{
    HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) &=
                                         ~GMAC_SW_ALE_PORTCTL0_BCAST_LIMIT;
    HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) |=
                            (bplVal << GMAC_SW_ALE_PORTCTL0_BCAST_LIMIT_SHIFT);
}

/*!
 * \brief   Sets the Multicast Packet Rate Limit
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   mplVal        The Multicast Packet Rate Limit Value
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEMulticastRateLimitSet(uint32_t baseAddr, uint32_t portNum,
                                  uint32_t mplVal)
{
    HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) &=
                                         ~GMAC_SW_ALE_PORTCTL0_MCAST_LIMIT;
    HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) |=
                            (mplVal << GMAC_SW_ALE_PORTCTL0_MCAST_LIMIT_SHIFT);
}

/*!
 * \brief   VLAN ID Ingress Check
 *
 * \param   baseAddr      Base Address of the ALE module
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEVIDIngressCheckSet(uint32_t baseAddr, uint32_t portNum)
{
    HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) |=
                                         GMAC_SW_ALE_PORTCTL0_MCAST_LIMIT;
}

/*!
 * \brief   Sets the port state in the ALE for a given port
 *
 * \param   baseAddr    Base address of the ALE module
 * \param   portNum     The port number
 * \param   portState   The port state to be set
 *    'portState' can take one of the below values \n
 *        GMAC_SW_ALE_PORT_STATE_FWD - ALE state is Forward \n
 *        GMAC_SW_ALE_PORT_STATE_LEARN - ALE state is Learn \n
 *        GMAC_SW_ALE_PORT_STATE_BLOCKED - ALE state is Blocked \n
 *        GMAC_SW_ALE_PORT_STATE_DISABLED - ALE state is Disabled
 *
 * \return  None
 **/
void GMAC_SW_ALEPortStateSet(uint32_t baseAddr, uint32_t portNum, uint32_t portState)
{
    HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) &=
        ~GMAC_SW_ALE_PORTCTL0_PORT_STATE_MASK;

    HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) |=
        ((portState << GMAC_SW_ALE_PORTCTL0_PORT_STATE_SHIFT) & GMAC_SW_ALE_PORTCTL0_PORT_STATE_MASK);
}


/*!
 * \brief   Gets the port state in the ALE for a given port
 *
 * \param   baseAddr    Base address of the ALE module
 * \param   portNum     The port number
 *
 * \return  portState   The port state to be set
 *    'portState' can take one of the below values \n
 *        GMAC_SW_ALE_PORT_STATE_FWD - ALE state is Forward \n
 *        GMAC_SW_ALE_PORT_STATE_LEARN - ALE state is Learn \n
 *        GMAC_SW_ALE_PORT_STATE_BLOCKED - ALE state is Blocked \n
 *        GMAC_SW_ALE_PORT_STATE_DISABLED - ALE state is Disabled
 **/
uint32_t GMAC_SW_ALEPortStateGet(uint32_t baseAddr, uint32_t portNum)
{
    uint32_t portState = HWREG(baseAddr + GMAC_SW_ALE_PORTCTL(portNum)) & GMAC_SW_ALE_PORTCTL0_PORT_STATE_MASK;
    return (portState >> GMAC_SW_ALE_PORTCTL0_PORT_STATE_SHIFT);
}

/*!
 * \brief   Sets VLAN Aware mode for ALE to Flood if VLAN not found
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALEVLANAwareSet(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) |= GMAC_SW_ALE_CONTROL_ALE_VLAN_AWARE;
}

/*!
 * \brief   Clears VLAN Aware mode for ALE to drop packets
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALEVLANAwareClear(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) &= ~GMAC_SW_ALE_CONTROL_ALE_VLAN_AWARE;
}

/*!
 * \brief   Configure Rate Limit to TX Mode
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALERateLimitTXMode(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) |= GMAC_SW_ALE_CONTROL_RATE_LIMIT_TX;
}

/*!
 * \brief   Configure Rate Limit to RX Mode
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALERateLimitRXMode(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) &= ~GMAC_SW_ALE_CONTROL_RATE_LIMIT_TX;
}

/*!
 * \brief   Enable Rate Limit for ALE
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALERateLimitEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) |= GMAC_SW_ALE_CONTROL_ENABLE_RATE_LIMIT;
}

/*!
 * \brief   Disable Rate Limit for ALE
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALERateLimitDisable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) &= ~GMAC_SW_ALE_CONTROL_ENABLE_RATE_LIMIT;
}

/*!
 * \brief   Enable MAC Authorization Mode for ALE
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALEAUTHModeSet(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) |= GMAC_SW_ALE_CONTROL_ENABLE_AUTH_MODE;
}

/*!
 * \brief   Disable MAC Authorization Mode for ALE
 *
 * \param   baseAddr    Base address of the ALE Module
 *
 * \return  None
 **/
void GMAC_SW_ALEAUTHModeClear(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) &= ~GMAC_SW_ALE_CONTROL_ENABLE_AUTH_MODE;
}

/*!
 * \brief   Sets an ALE table entry
 *
 * \param   baseAddr    Base address of the ALE Module
 * \param   aleTblIdx   The Index of the table entry
 * \param   aleEntryPtr The address of the entry to be set
 *
 * \return  None
 **/
void GMAC_SW_ALETableEntrySet(uint32_t baseAddr, uint32_t aleTblIdx,
                          uint32_t *aleEntryPtr)
{
    uint32_t cnt;

    for (cnt = 0; cnt < ALE_ENTRY_WORDS; cnt++)
    {
        HWREG(baseAddr +  GMAC_SW_ALE_TBLW(cnt)) =  *(aleEntryPtr + cnt);
    }

    HWREG(baseAddr +  GMAC_SW_ALE_TBLCTL) =
                                aleTblIdx | GMAC_SW_ALE_TBLCTL_WRITE_RDZ;
}

/*!
 * \brief   Returns an ALE table entry
 *
 * \param   baseAddr    Base address of the ALE Module
 * \param   aleTblIdx   The Index of the table entry
 * \param   aleEntryPtr The address where the ALE entry to be written
 *
 * \return  None
 **/
void GMAC_SW_ALETableEntryGet(uint32_t baseAddr, uint32_t aleTblIdx,
                          uint32_t *aleEntryPtr)
{
    uint32_t cnt;

    HWREG(baseAddr + GMAC_SW_ALE_TBLCTL) = aleTblIdx;

    for (cnt = 0; cnt < ALE_ENTRY_WORDS; cnt++)
    {
        *(aleEntryPtr + cnt) = HWREG(baseAddr + GMAC_SW_ALE_TBLW(cnt));
    }
}

/*!
 * \brief   Returns the prescale value for ALE. The input clock is divided
 *          by this value to use in the broadcast/multicast rate limiters.
 *
 * \param   baseAddr      Base Address of the ALE module
 *
 * \return  Prescale value
 *
 **/
uint32_t GMAC_SW_ALEPrescaleGet(uint32_t baseAddr)
{
    return (HWREG(baseAddr + GMAC_SW_ALE_PRESCALE)
            & GMAC_SW_ALE_PRESCALE_ALE_PRESCALE);
}

/*!
 * \brief   Sets the prescale value for ALE. The input clock is divided
 *          by this value to use in the broadcast/multicast rate limiters.
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   psVal         The prescale value
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEPrescaleSet(uint32_t baseAddr, uint32_t psVal)
{
    HWREG(baseAddr + GMAC_SW_ALE_PRESCALE) |= psVal
                                   & GMAC_SW_ALE_PRESCALE_ALE_PRESCALE ;
}

/*!
 * \brief   Sets the Unknown VLAN Force Untagged Egress
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   ueVal         The Unknown VLAN Fornce Untagged Egress value
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEUnknownUntaggedEgressSet(uint32_t baseAddr, uint32_t ueVal)
{
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) &=
                      ~GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTA;
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) |=
                      (ueVal << GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTA_SHIFT);
}

/*!
 * \brief   Sets the Unknown VLAN Registered Multicast Flood Mask
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   rfmVal        Unknown VLAN Registered Multicast Flood Mask Value
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEUnknownRegFloodMaskSet(uint32_t baseAddr, uint32_t rfmVal)
{
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) &=
                      ~GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_MCAST_FLO;
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) |=
                      (rfmVal << GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_MCAST_FLO_SHIFT);
}

/*!
 * \brief   Sets the Unknown VLAN UnRegistered Multicast Flood Mask
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   ufmVal        Unknown VLAN UnRegistered Multicast Flood Mask Value
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEUnknownUnRegFloodMaskSet(uint32_t baseAddr, uint32_t ufmVal)
{
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) &=
                      ~GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_REG_MCAST;
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) |=
                      (ufmVal << GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_SHIFT);
}

/*!
 * \brief   Sets the Unknown VLAN Member List
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   mlVal        Unknown VLAN UnRegistered Multicast Flood Mask Value
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEUnknownMemberListSet(uint32_t baseAddr, uint32_t mlVal)
{
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) &=
                        ~GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_VLAN_MEM;
    HWREG(baseAddr + GMAC_SW_ALE_UNKNOWN_VLAN) |=
                        (mlVal << GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_VLAN_MEM_SHIFT);
}

/*!
 * \brief   Enables the bypassing of the ALE logic
 *
 * \param   baseAddr      Base Address of the ALE module
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEBypassEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) |= GMAC_SW_ALE_CONTROL_ALE_BYPASS;
}

/*!
 * \brief   Disables the bypassing of the ALE logic
 *
 * \param   baseAddr      Base Address of the ALE module
 *
 * \return  None
 *
 **/
void GMAC_SW_ALEBypassDisable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_ALE_CONTROL) &= ~GMAC_SW_ALE_CONTROL_ALE_BYPASS;
}

/*!
 * \brief   Enables the receive flow control for GMAC_SW for a given port
 *
 * \param   baseAddr      Base Address of the GMAC_SW subsystem
 * \param   portNum       The port number
 *
 * \return  None
 *
 **/
void GMAC_SW_RxFlowControlEnable(uint32_t baseAddr, uint32_t portNum)
{
    HWREG(baseAddr + GMAC_SW_SS_FLOW_CONTROL) |= (1 << portNum);
}

/*!
 * \brief   Disables the receive flow control for GMAC_SW for a given port
 *
 * \param   baseAddr      Base Address of the GMAC_SW subsystem
 * \param   portNum       The port number
 *
 * \return  None
 *
 **/
void GMAC_SW_RxFlowControlDisable(uint32_t baseAddr, uint32_t portNum)
{
    HWREG(baseAddr + GMAC_SW_SS_FLOW_CONTROL) &= ~(1 << portNum);
}

/*!
 * \brief   Enables the software idle mode, causing the switch fabric to stop
 *          forward packets at the next start of packet.
 *
 * \param   baseAddr      Base Address of the GMAC_SW subsystem
 *
 * \return  None
 *
 **/
void GMAC_SW_SoftwareIdleEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_SS_SOFT_IDLE) |= GMAC_SW_SS_SOFT_IDLE_SOFT_IDLE;
}

/*!
 * \brief   Disables the software idle mode, causing the switch fabric to
 *          forward packets at the next start of packet.
 *
 * \param   baseAddr      Base Address of the GMAC_SW subsystem
 *
 * \return  None
 *
 **/
void GMAC_SW_SoftwareIdleDisable(uint32_t baseAddr, uint32_t portNum)
{
    HWREG(baseAddr + GMAC_SW_SS_SOFT_IDLE) &= ~GMAC_SW_SS_SOFT_IDLE_SOFT_IDLE;
}

/*!
 * \brief   Enables the GMAC_SW statistics for the given port
 *
 * \param   baseAddr      Base Address of the GMAC_SW subsystem
 * \param   portNum       The port number
 *
 * \return  None
 *
 **/
void GMAC_SW_StatisticsEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_SS_STAT_PORT_EN) = GMAC_SW_SS_STAT_PORT_EN_P0_STAT_EN
                                             | GMAC_SW_SS_STAT_PORT_EN_P1_STAT_EN
                                             | GMAC_SW_SS_STAT_PORT_EN_P2_STAT_EN;
}

/*!
 * \brief   Enables the VLAN aware mode for GMAC_SW
 *
 * \param   baseAddr      Base Address of the GMAC_SW subsystem
 *
 * \return  None
 *
 **/
void GMAC_SW_VLANAwareEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_SS_CONTROL) |= GMAC_SW_SS_CONTROL_VLAN_AWARE;
}

/*!
 * \brief   Disables the VLAN aware mode for GMAC_SW
 *
 * \param   baseAddr      Base Address of the GMAC_SW subsystem
 *
 * \return  None
 *
 **/
void GMAC_SW_VLANAwareDisable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_SS_CONTROL) &= ~GMAC_SW_SS_CONTROL_VLAN_AWARE;
}

/*!
 * \brief   Sets the ethernet address at the GMAC_SW port
 *
 * \param   baseAddr      Base address of the GMAC_SW Port Module registers
 * \param   ethAddr       Start address of the 6 byte ethernet address
 *
 * \return  None
 *
 **/
void GMAC_SW_PortSrcAddrSet(uint32_t baseAddr, unsigned char *ethAddr)
{

    HWREG(baseAddr + GMAC_SW_PORT_SA_HI) =
                   ethAddr[0]
                   | (ethAddr[1] << GMAC_SW_PORT_P1_SA_HI_MACSRCADDR_39_32_SHIFT)
                   | (ethAddr[2] << GMAC_SW_PORT_P1_SA_HI_MACSRCADDR_31_24_SHIFT)
                   | (ethAddr[3] << GMAC_SW_PORT_P1_SA_HI_MACSRCADDR_23_16_SHIFT);
    HWREG(baseAddr + GMAC_SW_PORT_SA_LO) =
                   ethAddr[4]
                   | (ethAddr[5] << GMAC_SW_PORT_P1_SA_LO_MACSRCADDR_7_0_SHIFT);
}

/*!
 * \brief   Sets Dual Mac Mode for GMAC_SW Port0
 *
 * \param   baseAddr      Base address of the GMAC_SW Host Port Module registers
 *
 * \return  None
 *
 **/
void GMAC_SW_HostPortDualMacModeSet(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_PORT_TX_IN_CTL) &= ~GMAC_SW_PORT_P0_TX_IN_CTL_TX_IN_SEL;
    HWREG(baseAddr + GMAC_SW_PORT_TX_IN_CTL) |=
                              GMAC_SW_PORT_P0_TX_IN_CTL_TX_IN_DUAL_MAC;
}

/*!
 * \brief   Configures Port VLAN
 *
 * \param   baseAddr      Base address of the GMAC_SW Port Module registers
 * \param   vlanId        VLAN ID to be set
 * \param   cfiBit        CFI value to be set
 * \param   vlanPri       Port VLAN priority
 *            'vlanId' can take a value from 0 to 0xFFF \n
 *            'cfiBit' can be either 0 or 1. \n
 *            'vlanPri' can be any value between and including 0 and 7.
 *
 * \return  None
 *
 **/
void GMAC_SW_PortVLANConfig(uint32_t baseAddr, uint32_t vlanId,
                        uint32_t cfiBit, uint32_t vlanPri)
{
    HWREG(baseAddr + GMAC_SW_PORT_PORT_VLAN) = vlanId
                           | (cfiBit << GMAC_SW_PORT_P2_PORT_VLAN_PORT_CFI_SHIFT)
                           | (vlanPri << GMAC_SW_PORT_P2_PORT_VLAN_PORT_PRI_SHIFT);
}

/*!
 * \brief   Returns the requested GMAC_SW Statistics
 *
 * \param   baseAddr      Base address of the GMAC_SW Status Module registers.
 * \param   statReg       Statistics Register to be read
 *
 * \return  The requested statistics
 *
 **/
uint32_t GMAC_SW_StatisticsGet(uint32_t baseAddr, uint32_t statReg)
{
    return (HWREG(baseAddr + statReg));
}

/*!
 * \brief   Resets the CPDMA
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMAReset(uint32_t baseAddr)
{
    uint32_t cnt;

    /* Reset the CPDMA */
    HWREG(baseAddr + GMAC_SW_CPDMA_CPDMA_SOFT_RESET) =
                     GMAC_SW_CPDMA_CPDMA_SOFT_RESET_SOFT_RESET;

    /* Wait till the reset completes */
    while(HWREG(baseAddr + GMAC_SW_CPDMA_CPDMA_SOFT_RESET)
          & GMAC_SW_CPDMA_CPDMA_SOFT_RESET_SOFT_RESET);

    /* Initialize all the header descriptor pointer registers */
    for(cnt =  0; cnt< GMAC_SW_MAX_HEADER_DESC; cnt++)
    {
        HWREG(baseAddr + GMAC_SW_CPDMA_TX_HDP(cnt)) = 0;
        HWREG(baseAddr + GMAC_SW_CPDMA_RX_HDP(cnt)) = 0;
        HWREG(baseAddr + GMAC_SW_CPDMA_TX_CP(cnt)) = 0;
        HWREG(baseAddr + GMAC_SW_CPDMA_RX_CP(cnt)) = 0;
    }
}

/*!
 * \brief   Enables the TXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be enabled
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMATxIntEnable(uint32_t baseAddr, uint32_t channel)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_TX_INTMASK_SET) |= (1 << channel);
}

/*!
 * \brief   Enables the RXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be enabled
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMARxIntEnable(uint32_t baseAddr, uint32_t channel)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_RX_INTMASK_SET) |= (1 << channel);
}

/*!
 * \brief   Disables the TXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be disabled
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMATxIntDisable(uint32_t baseAddr, uint32_t channel)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_TX_INTMASK_CLEAR) |= (1 << channel);

}

/*!
 * \brief   Disables the RXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be disabled
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMARxIntDisable(uint32_t baseAddr, uint32_t channel)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_RX_INTMASK_CLEAR) |= (1 << channel);

}

/*!
 * \brief   API to enable the transmit in the TX Control Register.
 *          After the transmit is enabled, any write to TXHDP of
 *          a channel will start transmission
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMATxEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_TX_CONTROL) = GMAC_SW_CPDMA_TX_CONTROL_TX_EN;
}

/*!
 * \brief   API to enable the receive in the RX Control Register.
 *          After the receive is enabled, and write to RXHDP of
 *          a channel, the data can be received in the destination
 *          specified by the corresponding RX buffer descriptor.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMARxEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_RX_CONTROL) = GMAC_SW_CPDMA_RX_CONTROL_RX_EN;
}

/*!
 * \brief   API to write the TX HDP register. If transmit is enabled,
 *          write to the TX HDP will immediately start transmission.
 *          The data will be taken from the buffer pointer of the TX buffer
 *          descriptor written to the TX HDP
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   descHdr       Address of the TX buffer descriptor
 * \param   channel       Channel Number
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMATxHdrDescPtrWrite(uint32_t baseAddr, uint32_t descHdr,
                                uint32_t channel)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_TX_HDP(channel)) = descHdr;
}

/*!
 * \brief   API to write the RX HDP register. If receive is enabled,
 *          write to the RX HDP will enable data reception to point to
 *          the corresponding RX buffer descriptor's buffer pointer.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   descHdr       Address of the RX buffer descriptor
 * \param   channel       Channel Number
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMARxHdrDescPtrWrite(uint32_t baseAddr, uint32_t descHdr,
                                uint32_t channel)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_RX_HDP(channel)) = descHdr;
}

/*!
 * \brief   Writes the DMA End Of Interrupt Vector.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   eoiFlag       Type of interrupt to acknowledge to the CPDMA
 *            'eoiFlag' can take the following values \n
 *                GMAC_SW_EOI_TX_PULSE - TX Pulse Interrupt \n
 *                GMAC_SW_EOI_RX_PULSE - RX Pulse Interrupt \n
 *                GMAC_SW_EOI_RX_THRESH_PULSE - RX Pulse Threshold Interrupt \n
 *                GMAC_SW_EOI_MISC_PULSE - Misc Interrupt \n
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMAEndOfIntVectorWrite(uint32_t baseAddr, uint32_t eoiFlag)
{
    /* Acknowledge the CPDMA */
    HWREG(baseAddr + GMAC_SW_CPDMA_CPDMA_EOI_VECTOR) = eoiFlag;
}

/*!
 * \brief   Writes the the TX Completion Pointer for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   comPtr        Completion Pointer Value to be written
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMATxCPWrite(uint32_t baseAddr, uint32_t channel,
                        uint32_t comPtr)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_TX_CP(channel)) = comPtr;
}

/*!
 * \brief   Writes the the RX Completion Pointer for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   comPtr        Completion Pointer Value to be written
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMARxCPWrite(uint32_t baseAddr, uint32_t channel,
                        uint32_t comPtr)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_RX_CP(channel)) = comPtr;
}

/*!
 * \brief   Set the free buffers for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   nBuf          Number of free buffers
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMANumFreeBufSet(uint32_t baseAddr, uint32_t channel,
                            uint32_t nBuf)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_RX_FREEBUFFER(channel)) = nBuf;
}

/*!
 * \brief   Returns the CPDMA Status.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   statFlag      The status flags to be read
 *     'statFlag' can take one of the following values \n
 *            CPDMA_STAT_IDLE - to check if CPDMA is idle. \n
 *            CPDMA_STAT_TX_HOST_ERR_CODE - TX host error code. \n
 *            CPDMA_STAT_TX_HOST_ERR_CHAN - TX host error channel. \n
 *            CPDMA_STAT_RX_HOST_ERR_CODE - RX host error code. \n
 *            CPDMA_STAT_RX_HOST_ERR_CHAN - RX host error channel. \n
 *
 * \return  the DMA status for the status flag passed.
 *          The return values for CPDMA_STAT_IDLE are, \n
 *            CPDMA_STAT_IDLE - CPDMA is in idle state \n
 *            CPDMA_STAT_NOT_IDLE - CPDMA is not in idle state \n
 *
 *          The return values for CPDMA_STAT_TX_HOST_ERR_CODE are, \n
 *            CPDMA_STAT_TX_NO_ERR - No error \n
 *            CPDMA_STAT_TX_SOP_ERR - SOP error \n
 *            CPDMA_STAT_TX_OWN_ERR - Ownership bit not
 *                                                  set in SOP buffer \n
 *            CPDMA_STAT_TX_ZERO_DESC - Zero Next Buffer
 *                                       Descriptor Pointer Without EOP \n
 *            CPDMA_STAT_TX_ZERO_BUF_PTR - Zero Buffer Pointer \n
 *            CPDMA_STAT_TX_ZERO_BUF_LEN - Zero Buffer Length \n
 *            CPDMA_STAT_TX_PKT_LEN_ERR - Packet Length Error \n
 *
 *          The return values for CPDMA_STAT_RX_HOST_ERR_CODE are, \n
 *            CPDMA_STAT_RXi_NO_ERR - No error \n
 *            CPDMA_STAT_RX_OWN_NOT_SET - Ownership bit not set in
                                          input buffer \n
 *            CPDMA_STAT_RX_ZERO_BUF_PTR - Zero Buffer Pointer\n
 *            CPDMA_STAT_RX_ZERO_BUF_LEN - Zero Buffer Length on
 *                                       non-SOP descriptor \n
 *            CPDMA_STAT_RX_SOP_BUF_LEN_ERR - SOP buffer length not
 *                                       greater than offset\n
 *
 **/
uint32_t GMAC_SW_CPDMAStatusGet(uint32_t baseAddr, uint32_t statFlag)
{
    return (((HWREG(baseAddr + GMAC_SW_CPDMA_DMASTATUS)) & statFlag)
            >> (statFlag & CPDMA_ERR_CHANNEL_POS));
}

/*!
 * \brief   Configures the CPDMA module by writing the configuration value
 *          to the DMA control register.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 * \param   cfg           CPDMA configuration written to control register
 *     'cfg' shall be CPDMA_CFG(tx_rlim, rx_cef, cmd_idle,
 *                              rx_offlen_blk, rx_own, tx_ptype). \n
 *        The parameter 'tx_rlim' to CPDMA_CFG can take one of the below
 *        values, showing which all channels are rate-limited. \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7 \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7_TO_6 \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7_TO_5 \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7_TO_4 \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7_TO_3 \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7_TO_2 \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7_TO_1 \n
 *            CPDMA_CFG_TX_RATE_LIM_CH_7_TO_0 \n
 *        The parameter 'rx_cef' to CPDMA_CFG can take one of the below
 *        values \n
 *            CPDMA_CFG_COPY_ERR_FRAMES - To copy error frames to memory \n
 *            CPDMA_CFG_NO_COPY_ERR_FRAMES - Not to copy error frames \n
 *        The parameter 'cmd_idle' to CPDMA_CFG can take one of the below
 *        values \n
 *            CPDMA_CFG_IDLE_COMMAND - Idle commanded \n
 *            CPDMA_CFG_IDLE_COMMAND_NONE - Idle not commanded \n
 *        The parameter 'rx_offlen_blk' to CPDMA_CFG can take one of the below
 *        values \n
 *            CPDMA_CFG_BLOCK_RX_OFF_LEN_WRITE - Block the DMA writes to the
 *                                               offset/length field during
 *                                               packet processing. \n
 *            CPDMA_CFG_NOT_BLOCK_RX_OFF_LEN_WRITE - Do not Block the DMA writes
 *                                              to the offset/length field during
 *                                              packet processing. \n
 *        The parameter 'rx_own' to CPDMA_CFG can take one of the below
 *        values \n
 *            CPDMA_CFG_RX_OWN_1 - The CPDMA writes 1 to the ownership bit at
 *                                 the end of packet processing. \n
 *            CPDMA_CFG_RX_OWN_0 - The CPDMA writes 0 to the ownership bit at
 *                                 the end of packet processing. \n
 *        The parameter 'tx_ptype' to CPDMA_CFG can take one of the below
 *        values \n
 *            CPDMA_CFG_TX_PRI_ROUND_ROBIN - The next channel for transmit is
 *                                           chosen round-robin. \n
 *            CPDMA_CFG_TX_PRI_FIXED - The next channel for transmit is
 *                                     chosen priority based, channel 7 with the
 *                                     highest priority \n
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMAConfig(uint32_t baseAddr, uint32_t cfg)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_DMACONTROL) = cfg;
}

/*!
 * \brief   Enable the command idle mode for CPDMA. When this API is called, the
 *          GMAC_SW stops all the reception and transmission. However, if receiving
 *          the current frame will be received completely before going to the idle
 *          state. Also, while transmitting, the contents in the fifo will be sent
 *          fully.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMACmdIdleEnable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_DMACONTROL) |= GMAC_SW_CPDMA_DMACONTROL_CMD_IDLE;

    /* Wait till the state changes to idle */
    while((HWREG(baseAddr + GMAC_SW_CPDMA_DMASTATUS) & GMAC_SW_CPDMA_DMASTATUS_IDLE)
          != GMAC_SW_CPDMA_DMASTATUS_IDLE);
}

/*!
 * \brief   Disable the command idle mode for CPDMA.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMACmdIdleDisable(uint32_t baseAddr)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_DMACONTROL) &= ~GMAC_SW_CPDMA_DMACONTROL_CMD_IDLE;
}

/*!
 * \brief   Sets the RX buffer offset value. The RX buffer offset will be
 *          written by the port into each frame SOP buffer descriptor
 *          buffer_offset field. The frame data will begin after the
 *          rx_buffer_offset value of bytes. This value will be used for
 *          all the channels .
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 * \param   bufOff        Buffer offset value
 *
 * \return  None
 *
 **/
void GMAC_SW_CPDMARxBufOffsetSet(uint32_t baseAddr, uint32_t bufOff)
{
    HWREG(baseAddr + GMAC_SW_CPDMA_RX_BUFFER_OFFSET) = bufOff;
}

/*!
 * \brief   Returns the raw transmit interrupt pending status.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 * \param   chanMask      Channel Mask
 *    'chanMask' can be given for one or more channels. \n
 *         0x01- for 0th channel, 0x80 for 7th channel, 0x81 for both 0th
 *         and 7th channel etc. \n
 *
 * \return  Raw receive interrupt status \n
 *          bits for the 'chanMask' will be set if interrupt is pending \n
 *          bits for the 'chanMask' will be clear if interrupt is not
 *                                                              pending \n
 *
 **/
uint32_t GMAC_SW_CPDMATxIntStatRawGet(uint32_t baseAddr,
                                      uint32_t chanMask)
{
    return (HWREG(baseAddr + GMAC_SW_CPDMA_TX_INTSTAT_RAW) & chanMask);
}

/*!
 * \brief   Returns the masked transmit interrupt pending status.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 * \param   chanMask      Channel Mask
 *    'chanMask' can be given for one or more channels. \n
 *         0x01- for 0th channel, 0x80 for 7th channel, 0x81 for both 0th
 *         and 7th channel etc. \n
 *
 * \return  Masked transmit interrupt status \n
 *          bits for the 'chanMask' will be set if interrupt is pending \n
 *          bits for the 'chanMask' will be cleared if interrupt is not
 *                                                              pending \n
 *
 **/
uint32_t GMAC_SW_CPDMATxIntStatMaskedGet(uint32_t baseAddr,
                                         uint32_t chanMask)
{
    return (HWREG(baseAddr + GMAC_SW_CPDMA_TX_INTSTAT_MASKED) & chanMask);
}

/*!
 * \brief   Returns the raw receive interrupt pending status.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 * \param   chanMask      Channel Mask
 * \param   intType       Interrupt type
 *    'chanMask' can be given for one or more channels. \n
 *         0x01- for 0th channel, 0x80 for 7th channel, 0x81 for both 0th
 *         and 7th channel etc. \n
 *    'intType' can take one of the following values. \n
 *         CPDMA_RX_INT_THRESH_PEND - RX threshold interrupt pending \n
 *         CPDMA_RX_INT_PULSE_PEND - RX pulse interrupt pending \n
 *
 * \return  Raw receive interrupt status \n
 *          bits for the 'chanMask' will be set if interrupt is pending \n
 *          bits for the 'chanMask' will be cleared if interrupt is not
 *                                                              pending \n
 *
 **/
uint32_t GMAC_SW_CPDMARxIntStatRawGet(uint32_t baseAddr,
                                      uint32_t chanMask,
                                      uint32_t intType)
{
    return ((HWREG(baseAddr + GMAC_SW_CPDMA_RX_INTSTAT_RAW) >> intType)
             & chanMask);
}

/*!
 * \brief   Returns the masked receive interrupt pending status.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 * \param   chanMask      Channel Mask
 * \param   intType       Interrupt type
 *    'chanMask' can be given for one or more channels. \n
 *         0x01- for 0th channel, 0x80 for 7th channel, 0x81 for both 0th
 *         and 7th channel etc. \n
 *    'intType' can take one of the following values. \n
 *         CPDMA_RX_INT_THRESH_PEND - RX threshold interrupt pending \n
 *         CPDMA_RX_INT_PULSE_PEND - RX pulse interrupt pending \n
 *
 * \return  Masked receive interrupt status \n
 *          bits for the 'chanMask' will be set if interrupt is pending \n
 *          bits for the 'chanMask' will be cleared if interrupt is not
 *                                                              pending \n
 *
 **/
uint32_t GMAC_SW_CPDMARxIntStatMaskedGet(uint32_t baseAddr,
                                         uint32_t chanMask,
                                         uint32_t intType)
{
    return ((HWREG(baseAddr + GMAC_SW_CPDMA_RX_INTSTAT_MASKED) >> intType)
             & chanMask);
}

/*!
 * \brief   Saves the GMAC_SW register context. This can be used while going
 *          to power down mode where GMAC_SW power will be cut down.
 *
 * \param   contextPtr   Pointer to the structure where GMAC_SW register context
 *                       need to be saved.
 *
 * \return  None
 *
 **/
void GMAC_SW_ContextSave(GMAC_SW_CONTEXT *contextPtr)
{
    uint32_t idx;
    uint32_t *cppiDest = (uint32_t*)contextPtr->cppiRamBase;

    GMAC_SW_CPDMACmdIdleEnable(contextPtr->cpdmaBase);

    /* Restore the CPPI RAM contents */
    for(idx = 0; idx < (GMAC_SW_SIZE_CPPI_RAM / 4); idx++, cppiDest++)
    {
        contextPtr->cppiRam[idx] = *cppiDest;
    }

    contextPtr->aleCtrl = HWREG(contextPtr->aleBase + GMAC_SW_ALE_CONTROL);
    contextPtr->alePortCtl[0] = HWREG(contextPtr->aleBase + GMAC_SW_ALE_PORTCTL(0));
    contextPtr->alePortCtl[1] = HWREG(contextPtr->aleBase + GMAC_SW_ALE_PORTCTL(1));
    contextPtr->alePortCtl[2] = HWREG(contextPtr->aleBase + GMAC_SW_ALE_PORTCTL(2));

    for(idx = 0; idx < GMAC_SW_MAX_NUM_ALE_ENTRY; idx++)
    {
        GMAC_SW_ALETableEntryGet(contextPtr->aleBase, idx,
                             &(contextPtr->aleEntry[idx * 3]));
    }

    contextPtr->ssStatPortEn = HWREG(contextPtr->ssBase + GMAC_SW_SS_STAT_PORT_EN);
    contextPtr->port1SaHi = HWREG(contextPtr->port1Base + GMAC_SW_PORT_SA_HI);
    contextPtr->port1SaLo = HWREG(contextPtr->port1Base + GMAC_SW_PORT_SA_LO);
    contextPtr->port2SaHi = HWREG(contextPtr->port2Base + GMAC_SW_PORT_SA_HI);
    contextPtr->port2SaLo = HWREG(contextPtr->port2Base + GMAC_SW_PORT_SA_LO);
    contextPtr->port1TxInCtl = HWREG(contextPtr->port1Base + GMAC_SW_PORT_TX_IN_CTL);
    contextPtr->port2TxInCtl = HWREG(contextPtr->port2Base + GMAC_SW_PORT_TX_IN_CTL);
    contextPtr->port1Vlan = HWREG(contextPtr->port1Base + GMAC_SW_PORT_PORT_VLAN);
    contextPtr->port2Vlan = HWREG(contextPtr->port2Base + GMAC_SW_PORT_PORT_VLAN);
    contextPtr->cpdmaRxFB = HWREG(contextPtr->cpdmaBase
                                  + GMAC_SW_CPDMA_RX_FREEBUFFER(0));
    contextPtr->cpdmaTxCtl = HWREG(contextPtr->cpdmaBase
                                   + GMAC_SW_CPDMA_TX_CONTROL);
    contextPtr->cpdmaRxCtl = HWREG(contextPtr->cpdmaBase
                                   + GMAC_SW_CPDMA_RX_CONTROL);
    contextPtr->cpdmaRxHdp = HWREG(contextPtr->cpdmaBase
                                   + GMAC_SW_CPDMA_RX_HDP(0));
    contextPtr->txIntMaskSet = HWREG(contextPtr->cpdmaBase
                                     + GMAC_SW_CPDMA_TX_INTMASK_SET);
    contextPtr->wrCoreIntTxPulse = HWREG(contextPtr->wrBase
                                         + GMAC_SW_WR_C_RX_THRESH_EN(0) + 0x04);
    contextPtr->rxIntMaskSet = HWREG(contextPtr->cpdmaBase
                                     + GMAC_SW_CPDMA_RX_INTMASK_SET);
    contextPtr->wrCoreIntRxPulse = HWREG(contextPtr->wrBase
                                         + GMAC_SW_WR_C_RX_THRESH_EN(0) + 0x08);
    contextPtr->sl1MacCtl = HWREG(contextPtr->sl1Base + GMAC_SW_SL_MACCONTROL);
    contextPtr->sl2MacCtl = HWREG(contextPtr->sl2Base + GMAC_SW_SL_MACCONTROL);
}

/*!
 * \brief   Restores the GMAC_SW register context. This can be used while coming
 *          back from power down mode where GMAC_SW power will be cut down.
 *
 * \param   contextPtr   Pointer to the structure where GMAC_SW register context
 *                       need to be restored from.
 *
 * \return  None
 *
 **/
void GMAC_SW_ContextRestore(GMAC_SW_CONTEXT *contextPtr)
{
    uint32_t idx;
    uint32_t *cppiDest = (uint32_t*)contextPtr->cppiRamBase;

    /* Restore the CPPI RAM contents */
    for(idx = 0; idx < (GMAC_SW_SIZE_CPPI_RAM / 4); idx++, cppiDest++)
    {
        *cppiDest = contextPtr->cppiRam[idx] ;
    }

    HWREG(contextPtr->aleBase + GMAC_SW_ALE_CONTROL) = contextPtr->aleCtrl;
    HWREG(contextPtr->aleBase + GMAC_SW_ALE_PORTCTL(0)) = contextPtr->alePortCtl[0];
    HWREG(contextPtr->aleBase + GMAC_SW_ALE_PORTCTL(1)) = contextPtr->alePortCtl[1];
    HWREG(contextPtr->aleBase + GMAC_SW_ALE_PORTCTL(2)) = contextPtr->alePortCtl[2];

    for(idx = 0; idx < GMAC_SW_MAX_NUM_ALE_ENTRY; idx++)
    {
        GMAC_SW_ALETableEntrySet(contextPtr->aleBase, idx,
                             &(contextPtr->aleEntry[idx * 3]));
    }

    HWREG(contextPtr->ssBase + GMAC_SW_SS_STAT_PORT_EN) = contextPtr->ssStatPortEn;
    HWREG(contextPtr->port1Base + GMAC_SW_PORT_SA_HI) = contextPtr->port1SaHi;
    HWREG(contextPtr->port1Base + GMAC_SW_PORT_SA_LO) = contextPtr->port1SaLo;
    HWREG(contextPtr->port2Base + GMAC_SW_PORT_SA_HI) = contextPtr->port2SaHi;
    HWREG(contextPtr->port2Base + GMAC_SW_PORT_SA_LO) = contextPtr->port2SaLo;
    HWREG(contextPtr->port1Base + GMAC_SW_PORT_TX_IN_CTL) = contextPtr->port1TxInCtl;
    HWREG(contextPtr->port2Base + GMAC_SW_PORT_TX_IN_CTL) = contextPtr->port2TxInCtl;
    HWREG(contextPtr->port1Base + GMAC_SW_PORT_PORT_VLAN) = contextPtr->port1Vlan;
    HWREG(contextPtr->port2Base + GMAC_SW_PORT_PORT_VLAN) = contextPtr->port2Vlan;
    HWREG(contextPtr->cpdmaBase + GMAC_SW_CPDMA_RX_FREEBUFFER(0)) =
                                contextPtr->cpdmaRxFB;
    HWREG(contextPtr->cpdmaBase + GMAC_SW_CPDMA_TX_CONTROL)
                                 = contextPtr->cpdmaTxCtl;
    HWREG(contextPtr->cpdmaBase + GMAC_SW_CPDMA_RX_CONTROL)
                                 = contextPtr->cpdmaRxCtl;
    HWREG(contextPtr->cpdmaBase + GMAC_SW_CPDMA_RX_HDP(0))
                                 = contextPtr->cpdmaRxHdp;
    HWREG(contextPtr->cpdmaBase + GMAC_SW_CPDMA_TX_INTMASK_SET)
                                 = contextPtr->txIntMaskSet;
    HWREG(contextPtr->wrBase + GMAC_SW_WR_C_RX_THRESH_EN(0) + 0x04)
                                 = contextPtr->wrCoreIntTxPulse;
    HWREG(contextPtr->cpdmaBase + GMAC_SW_CPDMA_RX_INTMASK_SET)
                                 = contextPtr->rxIntMaskSet;
    HWREG(contextPtr->wrBase + GMAC_SW_WR_C_RX_THRESH_EN(0) + 0x08)
                                 =  contextPtr->wrCoreIntRxPulse;
    HWREG(contextPtr->sl1Base + GMAC_SW_SL_MACCONTROL) = contextPtr->sl1MacCtl;
    HWREG(contextPtr->sl2Base + GMAC_SW_SL_MACCONTROL) = contextPtr->sl2MacCtl;
}


