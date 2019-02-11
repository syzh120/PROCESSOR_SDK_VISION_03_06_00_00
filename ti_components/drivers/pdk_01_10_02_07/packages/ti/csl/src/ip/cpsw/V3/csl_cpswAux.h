/**
 * @file  csl_cpswAux.h
 *
 * @brief
 *  API Auxilary header file for Ethernet switch module CSL.
 *
 *  Contains the different control command and status query functions definations
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2014-2017, Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef CSL_CPSW_AUX_V3_H
#define CSL_CPSW_AUX_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/csl/csl.h>
#include <ti/csl/cslr_cpsw.h>

/** ============================================================================ 
 *
 * @defgroup CSL_CPSW_API_V3 Ethernet switch submodule (CPSW - V3)
 * @ingroup CSL_CPSW_API
 *
 * ============================================================================
 */
/**
@defgroup CSL_CPSW_SYMBOL  CPSW Symbols Defined
@ingroup CSL_CPSW_API_V3
*/
/**
@defgroup CSL_CPSW_DATASTRUCT  CPSW Data Structures
@ingroup CSL_CPSW_API_V3
*/
/**
@defgroup CSL_CPSW_FUNCTION  CPSW Functions
@ingroup CSL_CPSW_API_V3
*/
/**
@defgroup CSL_CPSW_ENUM CPSW Enumerated Data Types
@ingroup CSL_CPSW_API_V3
*/
/** @addtogroup CSL_CPSW_DATASTRUCT
 @{ */

typedef volatile CSL_Cpsw_3gRegs             *CSL_cpswHandle;

typedef volatile CSL_CpdmaRegs               *CSL_cpdmaHandle;

typedef volatile CSL_WRRegs                  *CSL_wrHandle;

/** @brief Number of statistic blocks.
 *
 *  EMAC has multiple statistics blocks.
 *
 *  STATS0 holds statistics for Host/CPU port (Switch port 0).
 *  STATSn holds statistics for MAC ports (Switch ports n).
 */

#define     CSL_CPSW_NUMSTATBLOCKS              2
#define     CSL_CPSW_NUM_PORTS                  2

/** @brief Number of hardware statistics registers */
#define     CSL_CPSW_NUMSTATS                   42

/** @brief Maximum number of ALE entries that can be programmed */
#define     CSL_CPSW_NUMALE_ENTRIES             1024


/** @brief
 *
 *  Defines ALE Aging Timer Prescale
 */
typedef enum {
    ALE_AGT_PRESACLE_1M = 0,  /** 1000,000 (default value) */
    ALE_AGT_PRESACLE_1000,    /** 1000 (test value) */
    ALE_AGT_PRESACLE_1        /** 1 (test value) */
} CSL_CPSW_ALE_AGT_PRESCALE_E;

/** @brief
 *
 *  Holds Port Statistics Enable register contents.
 */
typedef struct {
	/**  Port 0 Statistics Enable bit */
	Uint32      p0StatEnable;

	/**  Port 1 Statistics Enable bit */
	Uint32      p1StatEnable;

	/**  Port 2 Statistics Enable bit */
	Uint32      p2StatEnable;
} CSL_CPSW_PORTSTAT;

/** @brief
 *
 *  Holds Port Time Sync Control register contents.
 */
typedef struct {
	/**  Port Time sync receive enable bit */
	Uint32      tsRxEnable;

	/**  Port Time sync receive VLAN LTYPE 1 enable bit */
	Uint32      tsRxVlanLType1Enable;

	/**  Port Time sync receive VLAN LTYPE 2 enable bit */
	Uint32      tsRxVlanLType2Enable;

	/**  Port Time sync transmit enable bit */
	Uint32      tsTxEnable;

	/**  Port Time sync transmit VLAN LTYPE 1 enable bit */
	Uint32      tsTxVlanLType1Enable;

	/**  Port Time sync transmit VLAN LTYPE 2 enable bit */
	Uint32      tsTxVlanLType2Enable;

	/**  Port Time sync message type enable bit */
	Uint32      txMsgTypeEnable;
} CSL_CPSW_TSCNTL;


/** @brief
 *
 *  Holds Port Time Sync Configuration contents.
 */
typedef struct {
	/**  Port Time sync receive Annex D enable */
	Uint32      tsRxAnnexDEnable;

	/**  Port Time sync receive Annex E enable */
	Uint32      tsRxAnnexEEnable;

	/**  Port Time sync receive Annex F enable */
	Uint32      tsRxAnnexFEnable;

	/**  Port Time sync receive VLAN LTYPE 1 enable */
	Uint32      tsRxVlanLType1Enable;

	/**  Port Time sync receive VLAN LTYPE 2 enable */
	Uint32      tsRxVlanLType2Enable;

	/**  Port Time sync transmit Annex D enable */
	Uint32      tsTxAnnexDEnable;

	/**  Port Time sync transmit Annex E enable */
	Uint32      tsTxAnnexEEnable;

	/**  Port Time sync transmit Annex F enable */
	Uint32      tsTxAnnexFEnable;

	/**  Port Time sync transmit VLAN LTYPE 1 enable */
	Uint32      tsTxVlanLType1Enable;

	/**  Port Time sync transmit VLAN LTYPE 2 enable */
	Uint32      tsTxVlanLType2Enable;

	/**  Port Time sync transmit host timestamp enable */
	Uint32      tsTxHostEnable;

	/**  Port Time sync transmit and receive LType2 enable */
	Uint32      tsLType2Enable;

	/**  Port Time sync message type enable bitmap */
	Uint32      tsMsgTypeEnable;

    /**  Port Time Sync Unicast IP message enable
         1: all IP address valid
         0: perform multicast address check, only multicast addresses which are enabled are valid
      */
    Uint32      tsUniEnable;

    /**  Port Time Sync Destination IP Address 107 enable
         IPv4: 224.0.0.107
         IPv6: FF0M:0:0:0:0:0:0:006B
     */
    Uint32      ts107Enable;

    /**  Port Time Sync Destination IP Address 129 enable
         IPv4: 224.0.0.129
         IPv6: FF0M:0:0:0:0:0:0:0181
     */
    Uint32      ts129Enable;

    /**  Port Time Sync Destination IP Address 130 enable
         IPv4: 224.0.0.130
         IPv6: FF0M:0:0:0:0:0:0:0182
     */
    Uint32      ts130Enable;

    /**  Port Time Sync Destination IP Address 131 enable
         IPv4: 224.0.0.130
         IPv6: FF0M:0:0:0:0:0:0:0183
     */
    Uint32      ts131Enable;

    /**  Port Time Sync Destination IP Address 132 enable
         IPv4: 224.0.0.131
         IPv6: FF0M:0:0:0:0:0:0:0184
     */
    Uint32      ts132Enable;

    /**  Port Time Sync UDP Destination Port Number 319 enable */
    Uint32      ts319Enable;

    /**  Port Time Sync UDP Destination Port Number 320 enable */
    Uint32      ts320Enable;

	/**  Port Time sync message IPv6 Multicast Address FF0M enable */
	Uint32      tsMcastTypeEnable;

	/**  Port Time Sync Time to Live Non-zero enable */
    Uint32      tsTTLNonzeroEnable;

    /**  Port Time Sync LTYPE1 value for Annex F packets */
    Uint32      tsLType1;

    /**  Port Time Sync LTYPE2 value for Annex F packets */
    Uint32      tsLType2;

    /**  Port Time Sync VLAN LTYPE1 value for both Tx and Rx packets */
    Uint32      tsVlanLType1;

    /**  Port Time Sync VLAN LTYPE2 value for both Tx and Rx packets */
    Uint32      tsVlanLType2;

    /**  Port Time Sync Sequence ID field byte Offset in PTP message */
    Uint32      tsSeqIdOffset;

    /**  Port Time Sync Domain field byte Offset in PTP message */
    Uint32      tsDomainOffset;

} CSL_CPSW_TSCONFIG;


/** @brief
 *
 *  Holds CPSW Port Control contents.
 */
typedef struct {
	/**  Eneregy Efficient Etherent (EEE) Transmit LPI clockstop enable
         for EMAC port only
         1: The GMII or RGMII transmit clock is stopped in the EEE
            LPI state.
         0: The GMII or RGMII transmit clock is not stopped in the
            EEE LPI state.
      */
	Uint32      txLpiClkstopEnable;

	/**  IPv6 DSCP to priority mapping enable */
	Uint32      dscpIpv6Enable;

	/**  IPv4 DSCP to priority mapping enable */
	Uint32      dscpIpv4Enable;

} CSL_CPSW_PORT_CONTROL;


/** @brief
 *
 *  Holds CPSW Port Rx Rate Limit Configuration for CPPI Port Ingress Rate Limitaion Operation.
 */
typedef struct {
	/**  Number of Rate Limitaion Channels. Rate limited channels must be the highest priority channels.
         For example, if two rate limited channels are required then they must be channel with priority
         7 and 6 respectively. The BW of rate limitation channel is calcualted as
         idleStep/(idleStep + sendStep)*Frequemcy*256 where frequency = the VBUSP_GCLK frequency (350 for 350Mhz)
      */
	Uint32      numRLimChans;

	/**  Rate Limitaion Idle Step Array */
	Uint32      idleStep[8];

	/**  Rate Limitaion Send Step Array  */
	Uint32      sendStep[8];

} CSL_CPSW_RX_RATE_LIMIT_CONFIG;

/** @brief
 *
 *  Holds CPSW EEE (Energy Efficient Ethernet)  Global Configuration.
 */
typedef struct {
    /**  Energy Efficient Ethernet enable */
    Uint32      enable;

	/**  Energy Efficient Ethernet Pre-scale count load value */
	Uint32      prescale;

} CSL_CPSW_EEE_GLOB_CONFIG;

/** @brief
 *
 *  Holds CPSW EEE (Energy Efficient Ethernet)  Per-Port Configuration.
 */
typedef struct {
	/**  EEE Transmit LPI clockstop enable
         for EMAC port only
         1: The GMII or RGMII transmit clock is stopped in the EEE
            LPI state.
         0: The GMII or RGMII transmit clock is not stopped in the
            EEE LPI state.
      */
	Uint32      txLpiClkstopEnable;

	/**  EEE Idle to LPI counter load value - After EEE_CLKSTOP_REQ is asserted,
         this value is loaded into the port idle to LPI counter on each clock
         that the port transmit or receive is not idle.  Port enters the LPI
         state when this count decrements to zero.
         This count value should be large relative to switch operations */
	Uint32      idle2lpi;

	/**  EEE LPI to wake counter load value - When the port is in the transmit
         LPI state and the EEE_CLKSTOP_REQ signal is deasserted, this value is
         loaded into the port 0 LPI to wake counter.
         Transmit and receive packet operations may begin (resume) when
         the LPI to wake count decrements to zero.  This is the time waited
         before CPPI packet operations begin (resume after wakeup).
         This count value should be large relative to switch operations. */
	Uint32      lpi2wake;

} CSL_CPSW_EEE_PORT_CONFIG;


/** @brief
 *
 *  Holds CPSW EEE (Energy Efficient Ethernet)  Per-Port STATUS.
 */
typedef struct {
	/**  CPSW port wait idle to LPI - asserted when port is counting the IDLE2LPI time */
	Uint32      wait_idle2lpi;

	/**  CPSW port receive LPI state - asserted when the port receive is in the LPI state */
	Uint32      rxLpi;

	/**  CPSW port transmit LPI state - asserted when the port transmit is in the LPI state */
	Uint32      txLpi;

    /**  CPSW port transmit wakeup - asserted when the port transmit is in the transmit
         LPI2WAKE count time. */
    Uint32      txWake;

    /**  CPSW port transmit FIFO hold - asserted in the LPI state and
         during the LPI2WAKE count time. */
    Uint32      txFifoHold;

    /** CPSW port receive FIFO (switch ingress) is empty - contains no packets */
    Uint32      rxFifoEmpty;

    /** CPSW port transmit FIFO (switch egress) is empty - contains no packets */
    Uint32      txFifoEmpty;

} CSL_CPSW_EEE_PORT_STATUS;

/** @brief
 *
 *  Defines ALE Update Bandwidth Control Value:
 *  The upd_bw_ctrl field within ALE control register specifies the rate in which adds,
 *  updates, touches, writes, and aging updates can occur. At frequencies of 350Mhz,
 *  the table update rate should be at its lowest or 5 Million updates per second.
 *  When operating the switch core at frequencies or above, the upd_bw_ctrl can be
 *  programmed more aggressive.
 *  If the upd_bw_ctrl is set but the frequency of the switch subsystem is below the
 *  associated value, ALE will drop packets due to insufficient time to complete
 *  lookup under high traffic loads.
 */
typedef enum {
    ALE_UPD_BW_350MHZ_5M = 0,           /** 0 - 350Mhz, 5M */
    ALE_UPD_BW_359MHZ_11M,              /** 1 - 359Mhz, 11M */
    ALE_UPD_BW_367MHZ_16M,              /** 2 - 367Mhz, 16M */
    ALE_UPD_BW_375MHZ_22M,              /** 3 - 375Mhz, 22M */
    ALE_UPD_BW_384MHZ_28M,              /** 4 - 384Mhz, 28M */
    ALE_UPD_BW_392MHZ_34M,              /** 5 - 392Mhz, 34M */
    ALE_UPD_BW_400MHZ_39M,              /** 6 - 400Mhz, 39M */
    ALE_UPD_BW_409MHZ_45M               /** 7 - 409Mhz, 45M */
} CSL_CPSW_ALE_UPD_BW;


/** @brief
 *
 *  Holds the EMAC statistics.
 *
 *  The statistics structure is the used to retrieve the current count
 *  of various packet events in the system. These values represent the
 *  delta values from the last time the statistics were read.
 */
typedef struct {
    /** Good Frames Received                      */
    Uint32      RxGoodFrames;

    /** Good Broadcast Frames Received            */
    Uint32      RxBCastFrames;

    /** Good Multicast Frames Received            */
    Uint32      RxMCastFrames;

    /** PauseRx Frames Received                   */
    Uint32      RxPauseFrames;

    /** Frames Received with CRC Errors           */
    Uint32      RxCRCErrors;

    /** Frames Received with Alignment/Code Errors*/
    Uint32      RxAlignCodeErrors;

    /** Oversized Frames Received                 */
    Uint32      RxOversized;

    /** Jabber Frames Received                    */
    Uint32      RxJabber;

    /** Undersized Frames Received                */
    Uint32      RxUndersized;

    /** Rx Frame Fragments Received               */
    Uint32      RxFragments;

    /** Reserved       */
    Uint32      reserved;

    /** Reserved */
    Uint32      reserved2;

    /** Total Received Bytes in Good Frames       */
    Uint32      RxOctets;

    /** Good Frames Sent                          */
    Uint32      TxGoodFrames;

    /** Good Broadcast Frames Sent                */
    Uint32      TxBCastFrames;

    /** Good Multicast Frames Sent                */
    Uint32      TxMCastFrames;

    /** PauseTx Frames Sent                       */
    Uint32      TxPauseFrames;

    /** Frames Where Transmission was Deferred    */
    Uint32      TxDeferred;

    /** Total Frames Sent With Collision          */
    Uint32      TxCollision;

    /** Frames Sent with Exactly One Collision    */
    Uint32      TxSingleColl;

    /** Frames Sent with Multiple Colisions       */
    Uint32      TxMultiColl;

    /** Tx Frames Lost Due to Excessive Collisions*/
    Uint32      TxExcessiveColl;

    /** Tx Frames Lost Due to a Late Collision    */
    Uint32      TxLateColl;

    /** Tx Frames Lost with Tx Underrun Error     */
    Uint32      TxUnderrun;

    /** Tx Frames Lost Due to Carrier Sense Loss  */
    Uint32      TxCarrierSLoss;

    /** Total Transmitted Bytes in Good Frames    */
    Uint32      TxOctets;

    /** Total Tx&Rx with Octet Size of 64         */
    Uint32      Frame64;

    /** Total Tx&Rx with Octet Size of 65 to 127  */
    Uint32      Frame65t127;

    /** Total Tx&Rx with Octet Size of 128 to 255 */
    Uint32      Frame128t255;

    /** Total Tx&Rx with Octet Size of 256 to 511 */
    Uint32      Frame256t511;

    /** Total Tx&Rx with Octet Size of 512 to 1023*/
    Uint32      Frame512t1023;

    /** Total Tx&Rx with Octet Size of >=1024     */
    Uint32      Frame1024tUp;

    /** Sum of all Octets Tx or Rx on the Network */
    Uint32      NetOctets;

    /** Total Rx Type1 Overruns                   */
    Uint32      rxSofOverRuns;

    /** Total Rx Type2 Overruns                   */
    Uint32      rxMofOverRuns;

    /** Total Rx Type3 Overruns                   */
    Uint32      rxDmaOverRuns;
} CSL_CPSW_STATS;

/** @brief
 *
 *  Holds CPSW EEE (Energy Efficient Ethernet)  Global Configuration.
 */
typedef struct {
    /**  RGMII duplex */
    Uint32      duplex;

	/**  RGMII speed */
	Uint32      speed;

	/**  RGMII link status */
	Uint32      linkStatus;

} CSL_CPSW_WR_RGMII_STATUS;

/**
@}
*/


/** @addtogroup CSL_CPSW_FUNCTION
@{ */

/********************************************************************************
************************* Ethernet Switch (CPSW) Submodule **********************
********************************************************************************/


/** ============================================================================
 *   @n@b CSL_CPSW_nGF_getCpswVersionInfo
 *
 *   @b Description
 *   @n This function retrieves the CPSW identification and version information.
 *
 *   @b Arguments
     @verbatim
        pVersionInfo        CSL_CPSW_VERSION structure that needs to be populated
                            with the version info read from the hardware.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_ID_VER_MINOR_VER,
 *      CPSW_3G_ID_VER_MAJ_VER,
 *      CPSW_3G_ID_VER_IDENT
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_VERSION    versionInfo;

        CSL_CPSW_getCpswVersionInfo (&versionInfo);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getCpswVersionInfo (
    CSL_cpswHandle          hCpswRegs,
	CSL_CPSW_VERSION*       pVersionInfo
); /* for misra warnings */
static inline void CSL_CPSW_getCpswVersionInfo (
    CSL_cpswHandle          hCpswRegs,
	CSL_CPSW_VERSION*       pVersionInfo
)
{

    pVersionInfo->minorVer  =   CSL_FEXT (hCpswRegs->ID_VER, CPSW_3G_ID_VER_MINOR_VER);
    pVersionInfo->majorVer  =   CSL_FEXT (hCpswRegs->ID_VER, CPSW_3G_ID_VER_MAJ_VER);
    pVersionInfo->id        =   CSL_FEXT (hCpswRegs->ID_VER, CPSW_3G_ID_VER_IDENT);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isFIFOLoopbackEnabled
 *
 *   @b Description
 *   @n This function indicates if FIFO loopback mode is enabled in the CPSW
 *      control register.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   FIFO loopback mode enabled. Each packet received is
 *	                            turned around and sent out on the same port's transmit
 *	                            path.
 *	 @n  FALSE                  FIFO loopback mode disabled.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_SW_CONTROL_FIFO_LOOPBACK
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isFIFOLoopbackEnabled (portNum) == TRUE)
        {
            // FIFO loopback mode enabled
        }
        else
        {
            // FIFO loopback mode disabled
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isFIFOLoopbackEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isFIFOLoopbackEnabled (
    CSL_cpswHandle               hCpswRegs
)
{
    return CSL_FEXT (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_FIFO_LOOPBACK);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableFIFOLoopback
 *
 *   @b Description
 *   @n This function configures the CPSW control register to enable FIFO loopback
 *      mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SW_CONTROL_FIFO_LOOPBACK=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableFIFOLoopback ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableFIFOLoopback (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableFIFOLoopback (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_FIFO_LOOPBACK, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableFIFOLoopback
 *
 *   @b Description
 *   @n This function configures the CPSW control register to disable FIFO loopback
 *      mode
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SW_CONTROL_FIFO_LOOPBACK=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableFIFOLoopback ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableFIFOLoopback (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableFIFOLoopback (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_FIFO_LOOPBACK, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isVlanAwareEnabled
 *
 *   @b Description
 *   @n This function indicates if VLAN aware mode is enabled in the CPSW
 *      control register.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   VLAN aware mode enabled.
 *	 @n  FALSE                  VLAN aware mode disabled.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_SW_CONTROL_VLAN_AWARE
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isVlanAwareEnabled (portNum) == TRUE)
        {
            // VLAN aware mode enabled
        }
        else
        {
            // VLAN aware mode disabled
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isVlanAwareEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isVlanAwareEnabled (
    CSL_cpswHandle               hCpswRegs
)
{
    return CSL_FEXT (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_VLAN_AWARE);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableVlanAware
 *
 *   @b Description
 *   @n This function configures the CPSW control register to enable VLAN aware
 *      mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SW_CONTROL_VLAN_AWARE=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableVlanAware ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableVlanAware (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableVlanAware (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_VLAN_AWARE, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableVlanAware
 *
 *   @b Description
 *   @n This function configures the CPSW control register to disable VLAN aware
 *      mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SW_CONTROL_VLAN_AWARE=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableVlanAware ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableVlanAware (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableVlanAware (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_VLAN_AWARE, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getCpswControlReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the CPSW Control register.
 *
 *   @b Arguments
     @verbatim
        pControlRegInfo     CSL_CPSW_CONTROL structure that needs to be populated
                            with the control register contents.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_SW_CONTROL_FIFO_LOOPBACK,
 *      CPSW_3G_SW_CONTROL_VLAN_AWARE,
 *      CPSW_3G_SW_CONTROL_EEE_EN
 *
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_CONTROL    controlRegInfo;

        CSL_CPSW_getCpswControlReg (&controlRegInfo);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getCpswControlReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_CONTROL*   pControlRegInfo
);/* for misra warnings*/
static inline void CSL_CPSW_getCpswControlReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_CONTROL*   pControlRegInfo
)
{
    pControlRegInfo->fifoLb         =   CSL_FEXT (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_FIFO_LOOPBACK);
    pControlRegInfo->vlanAware      =   CSL_FEXT (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_VLAN_AWARE);
    pControlRegInfo->eeeEnable      =   CSL_FEXT (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_EEE_EN);


    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setCpswControlReg
 *
 *   @b Description
 *   @n This function populates the contents of the CPSW Control register.
 *
 *   @b Arguments
     @verbatim
        pControlRegInfo     CSL_CPSW_CONTROL structure that holds the values
                            that need to be configured to the CPSW control register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  CPSW control register modified with values provided.
 *
 *   @b Writes
 *   @n CPSW_3G_SW_CONTROL_FIFO_LOOPBACK,
 *      CPSW_3G_SW_CONTROL_VLAN_AWARE,
 *      CPSW_3G_SW_CONTROL_EEE_EN
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_CONTROL    controlRegInfo;

        controlRegInfo.vlanAware    =   0;
        ...

        CSL_CPSW_setCpswControlReg (&controlRegInfo);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setCpswControlReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_CONTROL*   pControlRegInfo
);/* for misra warnings*/
static inline void CSL_CPSW_setCpswControlReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_CONTROL*   pControlRegInfo
)
{
    CSL_FINS (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_FIFO_LOOPBACK, pControlRegInfo->fifoLb);
    CSL_FINS (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_VLAN_AWARE, pControlRegInfo->vlanAware);
    CSL_FINS (hCpswRegs->SW_CONTROL, CPSW_3G_SW_CONTROL_EEE_EN, pControlRegInfo->eeeEnable);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isResetDone
 *
 *   @b Description
 *   @n This function retrieves the contents of the CPSW Softreset register.
 *
 *   @b Arguments
     @verbatim
        pSoft                   Soft reset bit read from the hardware.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_SOFT_RESET_SOFT_RESET
 *
 *   @b Example
 *   @verbatim
        Uint32  softResetStatus;

        softResetStatus = CSL_CPSW_isResetDone ();

	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isResetDone (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isResetDone (
    CSL_cpswHandle               hCpswRegs
)
{
    Uint32 ret_val = 0U;
    if (CSL_FEXT (hCpswRegs->SOFT_RESET, CPSW_3G_SOFT_RESET_SOFT_RESET) == 0)
    {
        ret_val = (Uint32)TRUE;
    }
    else
    {
        ret_val = (Uint32)FALSE;
    }
    return ret_val;
}

/** ============================================================================
 *   @n@b CSL_CPSW_reset
 *
 *   @b Description
 *   @n This function sets up the contents of the CPSW Soft Reset register.
 *
 *   <b> Arguments </b>
 *	 @n	 None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SOFT_RESET_SOFT_RESET
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_reset ();

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_reset (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_reset (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->SOFT_RESET, CPSW_3G_SOFT_RESET_SOFT_RESET, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortStatsEnableReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the CPSW Port Statistics
 *      Enable register.
 *
 *   @b Arguments
     @verbatim
        pPortStatsCfg       CSL_CPSW_PORTSTAT structure that needs to be populated
                            with the port statistics enable register contents.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_STAT_PORT_EN_P0_STAT_EN,
 *      CPSW_3G_STAT_PORT_EN_P1_STAT_EN,
 *      CPSW_3G_STAT_PORT_EN_P2_STAT_EN
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_PORTSTAT       portStatsCfg;

        CSL_CPSW_getPortStatsEnableReg (&portStatsCfg);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortStatsEnableReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_PORTSTAT*  pPortStatsCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getPortStatsEnableReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_PORTSTAT*  pPortStatsCfg
)
{
    pPortStatsCfg->p0StatEnable     =   CSL_FEXT (hCpswRegs->STAT_PORT_EN, CPSW_3G_STAT_PORT_EN_P0_STAT_EN);
    pPortStatsCfg->p1StatEnable     =   CSL_FEXT (hCpswRegs->STAT_PORT_EN, CPSW_3G_STAT_PORT_EN_P1_STAT_EN);
    pPortStatsCfg->p2StatEnable     =   CSL_FEXT (hCpswRegs->STAT_PORT_EN, CPSW_3G_STAT_PORT_EN_P2_STAT_EN);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPortStatsEnableReg
 *
 *   @b Description
 *   @n This function sets up the contents of the CPSW Port Statistics
 *      Enable register.
 *
 *   @b Arguments
     @verbatim
        pPortStatsCfg       CSL_CPSW_PORTSTAT structure that contains the values
                            to be used to setup port statistics enable register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_STAT_PORT_EN_P0_STAT_EN,
 *      CPSW_3G_STAT_PORT_EN_P1_STAT_EN,
 *      CPSW_3G_STAT_PORT_EN_P2_STAT_EN
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_PORTSTAT       portStatsCfg;

        portStatsCfg.p0StatEnable   =   1;
        portStatsCfg.p1StatEnable   =   1;
        portStatsCfg.p2StatEnable   =   1;

        CSL_CPSW_setPortStatsEnableReg (&portStatsCfg);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPortStatsEnableReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_PORTSTAT*  pPortStatsCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setPortStatsEnableReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_PORTSTAT*  pPortStatsCfg
)
{
    CSL_FINS (hCpswRegs->STAT_PORT_EN, CPSW_3G_STAT_PORT_EN_P0_STAT_EN, pPortStatsCfg->p0StatEnable);
    CSL_FINS (hCpswRegs->STAT_PORT_EN, CPSW_3G_STAT_PORT_EN_P1_STAT_EN, pPortStatsCfg->p1StatEnable);
    CSL_FINS (hCpswRegs->STAT_PORT_EN, CPSW_3G_STAT_PORT_EN_P2_STAT_EN, pPortStatsCfg->p2StatEnable);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPrioTypeReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the CPSW Priority Type
 *      register.
 *
 *   @b Arguments
     @verbatim
        pTypeCfg            CSL_CPSW_PTYPE structure that needs to be populated
                            with the priority type register contents.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_PTYPE_ESC_PRI_LD_VAL,
 *      CPSW_3G_PTYPE_P0_PTYPE_ESC,
 *      CPSW_3G_PTYPE_P1_PTYPE_ESC,
 *      CPSW_3G_PTYPE_P2_PTYPE_ESC
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_PTYPE       pTypeCfg;

        CSL_CPSW_getPrioTypeReg (&pTypeCfg);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPrioTypeReg (
    CSL_cpswHandle               hCpswRegs,
	CSL_CPSW_PTYPE*     pTypeCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getPrioTypeReg (
    CSL_cpswHandle               hCpswRegs,
	CSL_CPSW_PTYPE*     pTypeCfg
)
{
    pTypeCfg->escPriLdVal   =   CSL_FEXT (hCpswRegs->PTYPE, CPSW_3G_PTYPE_ESC_PRI_LD_VAL);
    pTypeCfg->p0PtypeEsc    =   CSL_FEXT (hCpswRegs->PTYPE, CPSW_3G_PTYPE_P0_PTYPE_ESC);
    pTypeCfg->p1PtypeEsc    =   CSL_FEXT (hCpswRegs->PTYPE, CPSW_3G_PTYPE_P1_PTYPE_ESC);
    pTypeCfg->p2PtypeEsc    =   CSL_FEXT (hCpswRegs->PTYPE, CPSW_3G_PTYPE_P2_PTYPE_ESC);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPrioTypeReg
 *
 *   @b Description
 *   @n This function modifies the contents of the CPSW Priority Type
 *      register.
 *
 *   @b Arguments
     @verbatim
        pTypeCfg            CSL_CPSW_PTYPE structure that contains the values that
                            need to be populated to Priority type register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_PTYPE_ESC_PRI_LD_VAL,
 *      CPSW_3G_PTYPE_P0_PTYPE_ESC,
 *      CPSW_3G_PTYPE_P1_PTYPE_ESC,
 *      CPSW_3G_PTYPE_P2_PTYPE_ESC
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_PTYPE       pTypeCfg;

        pTypeCfg.escPriLdVal    =   1;
        pTypeCfg.p0PtypeEsc     =   1;
        ...

        CSL_CPSW_setPrioTypeReg (&pTypeCfg);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPrioTypeReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_PTYPE*     pTypeCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setPrioTypeReg (
    CSL_cpswHandle      hCpswRegs,
	CSL_CPSW_PTYPE*     pTypeCfg
)
{
    CSL_FINS (hCpswRegs->PTYPE, CPSW_3G_PTYPE_ESC_PRI_LD_VAL, pTypeCfg->escPriLdVal);
    CSL_FINS (hCpswRegs->PTYPE, CPSW_3G_PTYPE_P0_PTYPE_ESC, pTypeCfg->p0PtypeEsc);
    CSL_FINS (hCpswRegs->PTYPE, CPSW_3G_PTYPE_P1_PTYPE_ESC, pTypeCfg->p1PtypeEsc);
    CSL_FINS (hCpswRegs->PTYPE, CPSW_3G_PTYPE_P2_PTYPE_ESC, pTypeCfg->p2PtypeEsc);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isSoftIdle
 *
 *   @b Description
 *   @n This function indicates if the CPSW is at Software Idle mode where
 *      no packets will be started to be unloaded from ports.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   Software Idle mode enabled.
 *	 @n  FALSE                  Software Idle mode disabled.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_SOFT_IDLE_SOFT_IDLE
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isSoftIdle () == TRUE)
        {
            // Software Idle mode enabled
        }
        else
        {
            // Software Idle mode disabled
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isSoftIdle (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isSoftIdle (
    CSL_cpswHandle               hCpswRegs
)
{
    return CSL_FEXT (hCpswRegs->SOFT_IDLE, CPSW_3G_SOFT_IDLE_SOFT_IDLE);
}

/** ============================================================================
 *   @n@b CSL_CPSW_getShortGapThreshold
 *
 *   @b Description
 *   @n This function retrieves the contents of the CPSW MAC Short Gap Threshold
 *      register.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 >=0                    MAC short gap threshold value read from the hardware.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_GAP_THRESH_GAP_THRESH
 *
 *   @b Example
 *   @verbatim
 *      Uint32          gapThreshVal;

        gapThreshVal    =   CSL_CPSW_getShortGapThreshold ();

	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_getShortGapThreshold (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getShortGapThreshold (
    CSL_cpswHandle               hCpswRegs
)
{
    return CSL_FEXT (hCpswRegs->GAP_THRESH, CPSW_3G_GAP_THRESH_GAP_THRESH);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableSoftIdle
 *
 *   @b Description
 *   @n This function configures the CPSW Soft Idle register to enable Software
 *      Idle mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SOFT_IDLE_SOFT_IDLE=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableSoftIdle ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableSoftIdle (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableSoftIdle (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->SOFT_IDLE, CPSW_3G_SOFT_IDLE_SOFT_IDLE, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableSoftIdle
 *
 *   @b Description
 *   @n This function configures the CPSW Soft Idle register to disable Software
 *      Idle mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SOFT_IDLE_SOFT_IDLE=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableSoftIdle ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableSoftIdle (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableSoftIdle (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->SOFT_IDLE, CPSW_3G_SOFT_IDLE_SOFT_IDLE, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getTxStartWordsReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Transmit FIFO start words
 *      register.
 *
 *   @b Arguments
     @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_TX_START_WDS_TX_START_WDS
 *
 *   @b Example
 *   @verbatim
 *      Uint32          startWordsVal;

        startWordsVal   =   CSL_CPSW_getTxStartWordsReg ();

	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_getTxStartWordsReg (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getTxStartWordsReg (
    CSL_cpswHandle               hCpswRegs
)
{
    return CSL_FEXT (hCpswRegs->TX_START_WDS, CPSW_3G_TX_START_WDS_TX_START_WDS);
}

/** ============================================================================
 *   @n@b CSL_CPSW_setTxStartWordsReg
 *
 *   @b Description
 *   @n This function sets up the contents of the Transmit FIFO start words
 *      register.
 *
 *   @b Arguments
     @verbatim
        pStartWordsVal      Start words value to be set to the Transmit FIFO start
                            words register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TX_START_WDS_TX_START_WDS
 *
 *   @b Example
 *   @verbatim
 *      Uint32          startWordsVal;
 *
 *      startWordsVal   =   32;

        CSL_CPSW_setTxStartWordsReg (startWordsVal);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setTxStartWordsReg (
    CSL_cpswHandle          hCpswRegs,
    Uint32                  startWordsVal
);/* for misra warnings*/
static inline void CSL_CPSW_setTxStartWordsReg (
    CSL_cpswHandle          hCpswRegs,
    Uint32                  startWordsVal
)
{
    CSL_FINS (hCpswRegs->TX_START_WDS, CPSW_3G_TX_START_WDS_TX_START_WDS, startWordsVal);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getFlowControlReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Flow control register.
 *
 *   @b Arguments
     @verbatim
        pFlowControlCfg     CSL_CPSW_FLOWCNTL structure that needs to be populated
                            with contents of Flow control register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_FLOW_CONTROL_P0_FLOW_EN,
 *      CPSW_3G_FLOW_CONTROL_P1_FLOW_EN,
 *      CPSW_3G_FLOW_CONTROL_P2_FLOW_EN
 *
 *   @b Example
 *   @verbatim
 *      CSL_CPSW_FLOWCNTL       flowControlCfg;

        CSL_CPSW_getFlowControlReg (&flowControlCfg);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getFlowControlReg (
    CSL_cpswHandle      hCpswRegs,
    CSL_CPSW_FLOWCNTL*  pFlowControlCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getFlowControlReg (
    CSL_cpswHandle      hCpswRegs,
    CSL_CPSW_FLOWCNTL*  pFlowControlCfg
)
{
    pFlowControlCfg->p0FlowEnable   =   CSL_FEXT (hCpswRegs->FLOW_CONTROL, CPSW_3G_FLOW_CONTROL_P0_FLOW_EN);
    pFlowControlCfg->p1FlowEnable   =   CSL_FEXT (hCpswRegs->FLOW_CONTROL, CPSW_3G_FLOW_CONTROL_P1_FLOW_EN);
    pFlowControlCfg->p2FlowEnable   =   CSL_FEXT (hCpswRegs->FLOW_CONTROL, CPSW_3G_FLOW_CONTROL_P2_FLOW_EN);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setFlowControlReg
 *
 *   @b Description
 *   @n This function sets up the contents of the Flow control register.
 *
 *   @b Arguments
     @verbatim
        pFlowControlCfg     CSL_CPSW_FLOWCNTL structure that contains the values
                            that need to be configured to Flow control register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_FLOW_CONTROL_P0_FLOW_EN,
 *      CPSW_3G_FLOW_CONTROL_P1_FLOW_EN,
 *      CPSW_3G_FLOW_CONTROL_P2_FLOW_EN
 *
 *   @b Example
 *   @verbatim
 *      CSL_CPSW_FLOWCNTL       flowControlCfg;

        flowControlCfg.p0FlowEnable =   1;
        flowControlCfg.p1FlowEnable =   1;:
        flowControlCfg.p2FlowEnable =   1;

        CSL_CPSW_setFlowControlReg (&flowControlCfg);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setFlowControlReg (
    CSL_cpswHandle      hCpswRegs,
    CSL_CPSW_FLOWCNTL*  pFlowControlCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setFlowControlReg (
    CSL_cpswHandle      hCpswRegs,
    CSL_CPSW_FLOWCNTL*  pFlowControlCfg
)
{
    CSL_FINS (hCpswRegs->FLOW_CONTROL, CPSW_3G_FLOW_CONTROL_P0_FLOW_EN, pFlowControlCfg->p0FlowEnable);
    CSL_FINS (hCpswRegs->FLOW_CONTROL, CPSW_3G_FLOW_CONTROL_P1_FLOW_EN, pFlowControlCfg->p1FlowEnable);
    CSL_FINS (hCpswRegs->FLOW_CONTROL, CPSW_3G_FLOW_CONTROL_P2_FLOW_EN, pFlowControlCfg->p2FlowEnable);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPort0VlanReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Port 0 VLAN Register.
 *
 *   @b Arguments
     @verbatim
        pPortVID                Port VLAN Id
        pPortCFI                Port CFI bit
        pPortPRI                Port VLAN priority (0-7, 7 is highest priority)
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P0_PORT_VLAN_PORT_VID,
 *      CPSW_3G_P0_PORT_VLAN_PORT_CFI,
 *      CPSW_3G_P0_PORT_VLAN_PORT_PRI
 *
 *   @b Example
 *   @verbatim
 *      Uint32      portVID, portCFI, portPRI;

        CSL_CPSW_getPort0VlanReg (&portVID, &portCFI, &portPRI);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPort0VlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32*                     pPortVID,
    Uint32*                     pPortCFI,
    Uint32*                     pPortPRI
);/* for misra warnings*/
static inline void CSL_CPSW_getPort0VlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32*                     pPortVID,
    Uint32*                     pPortCFI,
    Uint32*                     pPortPRI
)
{
    *pPortVID   =   CSL_FEXT (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_VID);
    *pPortCFI   =   CSL_FEXT (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_CFI);
    *pPortPRI   =   CSL_FEXT (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_PRI);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPort0VlanReg
 *
 *   @b Description
 *   @n This function sets up the contents of the Port 0 VLAN Register.
 *
 *   @b Arguments
     @verbatim
        portVID                 Port VLAN Id to be configured
        portCFI                 Port CFI bit to be configured
        portPRI                 Port VLAN priority to be configured
                                (0-7, 7 is highest priority)
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_P0_PORT_VLAN_PORT_VID,
 *      CPSW_3G_P0_PORT_VLAN_PORT_CFI,
 *      CPSW_3G_P0_PORT_VLAN_PORT_PRI
 *
 *   @b Example
 *   @verbatim
 *      Uint32      portVID, portCFI, portPRI;

        portVID     =   1;
        portCFI     =   0;
        portPRI     =   7;

        CSL_CPSW_setPort0VlanReg (portVID, portCFI, portPRI);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPort0VlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portVID,
    Uint32                      portCFI,
    Uint32                      portPRI
);/* for misra warnings*/
static inline void CSL_CPSW_setPort0VlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portVID,
    Uint32                      portCFI,
    Uint32                      portPRI
)
{
    CSL_FINS (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_VID, portVID);
    CSL_FINS (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_CFI, portCFI);
    CSL_FINS (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_PRI, portPRI);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPort0RxPriMapReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Port 0 Receive Packet
 *      Priority to Header Priority Mapping Register.
 *
 *   @b Arguments
     @verbatim
        pPortTxPriMap           Array of Port 0 Rx priority map priority values
                                read from the register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  The input parameter 'pPortTxPriMap' must be large enough to hold all
 *       the 8 priority values read from the register.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P0_TX_PRI_MAP_PRI0,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI1,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI2,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI3,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI4,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI5,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI6,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI7
 *
 *   @b Example
 *   @verbatim
 *      Uint32      port0TxPriMap [8];

        CSL_CPSW_getPort0RxPriMapReg (port0TxPriMap);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPort0TxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32*                     pPortTxPriMap
);/* for misra warnings*/
static inline void CSL_CPSW_getPort0TxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32*                     pPortTxPriMap
)
{
    pPortTxPriMap [0]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI0);
    pPortTxPriMap [1]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI1);
    pPortTxPriMap [2]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI2);
    pPortTxPriMap [3]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI3);
    pPortTxPriMap [4]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI4);
    pPortTxPriMap [5]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI5);
    pPortTxPriMap [6]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI6);
    pPortTxPriMap [7]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI7);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPort0RxPriMapReg
 *
 *   @b Description
 *   @n This function sets up the contents of the Port 0 Receive Packet
 *      Priority to Header Priority Mapping Register.
 *
 *   @b Arguments
     @verbatim
        pPortTxPriMap           Array of Port 0 Rx priority map priority values
                                that must be configured to the register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_P0_TX_PRI_MAP_PRI0,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI1,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI2,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI3,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI4,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI5,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI6,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI7
 *
 *   @b Example
 *   @verbatim
 *      Uint32      i, port0TxPriMap [8];

        for (i = 0; i < 8; i ++)
            port0TxPriMap [i] = i;

        CSL_CPSW_setPort0RxPriMapReg (port0TxPriMap);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPort0TxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32*                     pPortTxPriMap
);/* for misra warnings*/
static inline void CSL_CPSW_setPort0TxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32*                     pPortTxPriMap
)
{
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI0, pPortTxPriMap [0]);
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI1, pPortTxPriMap [1]);
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI2, pPortTxPriMap [2]);
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI3, pPortTxPriMap [3]);
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI4, pPortTxPriMap [4]);
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI5, pPortTxPriMap [5]);
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI6, pPortTxPriMap [6]);
    CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI7, pPortTxPriMap [7]);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortMaxBlocksReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Port Max Blocks Register
 *      corresponding to the MAC port specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 MAC port number for which the max block numbers
                                must be retrieved.
        pRxMaxBlks              Receive FIFO Maximum blocks read for this port.
        pTxMaxBlks              Transmit FIFO Maximum blocks read for this port.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS,
 *      CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS,
 *      CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS,
 *      CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS
 *
 *   @b Example
 *   @verbatim
 *      Uint32      rxMaxBlks, txMaxBlks, portNum;

        portNum =   1;

        CSL_CPSW_getPortMaxBlocksReg (portNum, &rxMaxBlks, &txMaxBlks);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortMaxBlocksReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxMaxBlks,
    Uint32*                     pTxMaxBlks
);/* for misra warnings*/
static inline void CSL_CPSW_getPortMaxBlocksReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxMaxBlks,
    Uint32*                     pTxMaxBlks
)
{
    if (portNum == 0)
    {
        *pRxMaxBlks  =   CSL_FEXT (hCpswRegs->P0_MAX_BLKS, CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS);
        *pTxMaxBlks  =   CSL_FEXT (hCpswRegs->P0_MAX_BLKS, CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS);
    } else
    {
        *pRxMaxBlks  =   (Uint32)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_MAX_BLKS, CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS);
        *pTxMaxBlks  =   (Uint32)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_MAX_BLKS, CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPortMaxBlocksReg
 *
 *   @b Description
 *   @n This function sets up the contents of the Port Max Blocks Register
 *      corresponding to the MAC port specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 MAC port number for which the max block numbers
                                must be configured.
        rxMaxBlks               Maximum number of 4K memory blocks that must be allocated
                                for the port's FIFO logical receive priority queues.
        txMaxBlks               Maximum number of 4K memory blocks that must be allocated
                                for the port's FIFO logical transmit priority queues.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS,
 *      CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS,
 *      CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS,
 *      CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS
 *
 *   @b Example
 *   @verbatim
 *      Uint32      rxMaxBlks, txMaxBlks, portNum;

        portNum     =   1;
        rxMaxBlks   =   3;
        txMaxBlks   =   17;

        CSL_CPSW_getPortMaxBlocksReg (portNum, rxMaxBlks, txMaxBlks);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPortMaxBlocksReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32                      rxMaxBlks,
    Uint32                      txMaxBlks
);/* for misra warnings*/
static inline void CSL_CPSW_setPortMaxBlocksReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32                      rxMaxBlks,
    Uint32                      txMaxBlks
)
{
    if (portNum == 0)
    {
        CSL_FINS (hCpswRegs->P0_MAX_BLKS, CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS, rxMaxBlks);
        CSL_FINS (hCpswRegs->P0_MAX_BLKS, CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS, txMaxBlks);
    } else
    {
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_MAX_BLKS, CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS, rxMaxBlks);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_MAX_BLKS, CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS, txMaxBlks);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortBlockCountReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Port Block Count register
 *      corresponding to the CPSW port specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the block count
                                must be retrieved.
        pRxBlkCnt               Receive block count usage read for this port.
        pTxBlkCnt               Transmit block count usage read for this port.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P_BLK_CNT_P_RX_BLK_CNT,
 *      CPSW_3G_P_BLK_CNT_P_TX_BLK_CNT,
 *      CPSW_3G_P0_BLK_CNT_P0_RX_BLK_CNT,
 *      CPSW_3G_P0_BLK_CNT_P0_TX_BLK_CNT,
 *
 *   @b Example
 *   @verbatim
 *      Uint32      rxBlkCnt, txBlkCnt, portNum;

        portNum =   1;

        CSL_CPSW_getPortBlockCountReg (portNum, &rxBlkCnt, &txBlkCnt);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortBlockCountReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxBlkCnt,
    Uint32*                     pTxBlkCnt
);/* for misra warnings*/
static inline void CSL_CPSW_getPortBlockCountReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxBlkCnt,
    Uint32*                     pTxBlkCnt
)
{
    if (portNum == 0)
    {
        *pRxBlkCnt  =   CSL_FEXT (hCpswRegs->P0_BLK_CNT, CPSW_3G_P0_BLK_CNT_P0_RX_BLK_CNT);
        *pTxBlkCnt  =   CSL_FEXT (hCpswRegs->P0_BLK_CNT, CPSW_3G_P0_BLK_CNT_P0_TX_BLK_CNT);
    } else
    {
        *pRxBlkCnt  =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_BLK_CNT, CPSW_3G_P_BLK_CNT_P_RX_BLK_CNT);
        *pTxBlkCnt  =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_BLK_CNT, CPSW_3G_P_BLK_CNT_P_TX_BLK_CNT);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortRxPriMapReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Port Receive Packet
 *      Priority to Header Priority Mapping Register.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the block count
                                must be retrieved.
        pPortTxPriMap           Array of Port Rx priority map priority values
                                read from the register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  The input parameter 'pPortTxPriMap' must be large enough to hold all
 *       the 8 priority values read from the register.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P0_TX_PRI_MAP_PRI0,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI1,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI2,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI3,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI4,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI5,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI6,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI7,
 *
 *      CPSW_3G_P_TX_PRI_MAP_PRI0,
 *      CPSW_3G_P_TX_PRI_MAP_PRI1,
 *      CPSW_3G_P_TX_PRI_MAP_PRI2,
 *      CPSW_3G_P_TX_PRI_MAP_PRI3,
 *      CPSW_3G_P_TX_PRI_MAP_PRI4,
 *      CPSW_3G_P_TX_PRI_MAP_PRI5,
 *      CPSW_3G_P_TX_PRI_MAP_PRI6,
 *      CPSW_3G_P_TX_PRI_MAP_PRI7
 *
 *   @b Example
 *   @verbatim
 *      Uint32      portNum = 1;
 *      Uint32      portRxPriMap [8];

        CSL_CPSW_getPortRxPriMapReg (portNum, portRxPriMap);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortRxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortTxPriMap
);/* for misra warnings*/
static inline void CSL_CPSW_getPortRxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortTxPriMap
)
{
    if (portNum == 0)
    {
        pPortTxPriMap [0]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI0);
        pPortTxPriMap [1]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI1);
        pPortTxPriMap [2]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI2);
        pPortTxPriMap [3]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI3);
        pPortTxPriMap [4]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI4);
        pPortTxPriMap [5]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI5);
        pPortTxPriMap [6]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI6);
        pPortTxPriMap [7]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI7);
    }
    else 
    {
        pPortTxPriMap [0]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI0);
        pPortTxPriMap [1]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI1);
        pPortTxPriMap [2]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI2);
        pPortTxPriMap [3]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI3);
        pPortTxPriMap [4]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI4);
        pPortTxPriMap [5]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI5);
        pPortTxPriMap [6]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI6);
        pPortTxPriMap [7]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI7);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPortTxPriMapReg
 *
 *   @b Description
 *   @n This function sets up the contents of the Port Receive Packet
 *      Priority to Header Priority Mapping Register.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the priority mapping
                                registers must be configured.
        pPortTxPriMap           Array of Port Rx priority map priority values
                                that must be configured to the register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_P0_TX_PRI_MAP_PRI0,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI1,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI2,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI3,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI4,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI5,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI6,
 *      CPSW_3G_P0_TX_PRI_MAP_PRI7,
 *
 *      CPSW_3G_P_TX_PRI_MAP_PRI0,
 *      CPSW_3G_P_TX_PRI_MAP_PRI1,
 *      CPSW_3G_P_TX_PRI_MAP_PRI2,
 *      CPSW_3G_P_TX_PRI_MAP_PRI3,
 *      CPSW_3G_P_TX_PRI_MAP_PRI4,
 *      CPSW_3G_P_TX_PRI_MAP_PRI5,
 *      CPSW_3G_P_TX_PRI_MAP_PRI6,
 *      CPSW_3G_P_TX_PRI_MAP_PRI7
 *
 *   @b Example
 *   @verbatim
 *      Uint32      portNum = 1;
 *      Uint32      i, port0TxPriMap [8];

        for (i = 0; i < 8; i ++)
            port0TxPriMap [i] = i;

        CSL_CPSW_setPortTxPriMapReg (port0TxPriMap);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPortTxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortTxPriMap
);/* for misra warnings*/
static inline void CSL_CPSW_setPortTxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortTxPriMap
)
{
    if(portNum == 0)
    {
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI0, pPortTxPriMap [0]);
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI1, pPortTxPriMap [1]);
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI2, pPortTxPriMap [2]);
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI3, pPortTxPriMap [3]);
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI4, pPortTxPriMap [4]);
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI5, pPortTxPriMap [5]);
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI6, pPortTxPriMap [6]);
        CSL_FINS (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P0_TX_PRI_MAP_PRI7, pPortTxPriMap [7]);
    }
    else
    {
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI0, pPortTxPriMap [0]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI1, pPortTxPriMap [1]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI2, pPortTxPriMap [2]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI3, pPortTxPriMap [3]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI4, pPortTxPriMap [4]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI5, pPortTxPriMap [5]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI6, pPortTxPriMap [6]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI7, pPortTxPriMap [7]);
    }
    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortRxDscpMap
 *
 *   @b Description
 *   @n This function retrieves the contents of the Port DSCP to Priority
 *      Mapping Registers corresponding to the CPSW port specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the DSCP mapping
                                registers must be retrieved.
        pRxDscpPriMap           Array of Port Rx DSCP to priority mapping values
                                read from the registers.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  The input parameter 'pRxDscpPriMap' must be large enough to hold all
 *       the 64 priority values read from the register.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7,
 *
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7
 *
 *
 *   @b Example
 *   @verbatim
 *      Uint32      rxDscpPriMap [64], portNum;

        portNum = 1;
        CSL_CPSW_getPortRxDscpMap (portNum, rxDscpPriMap);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortRxDscpMap (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxDscpPriMap
);/* for misra warnings*/
static inline void CSL_CPSW_getPortRxDscpMap (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxDscpPriMap
)
{
    int32_t i, j;

    if(portNum == 0)
    {
        j=0;
        for( i = 0; i < 8; i++)
        {
            pRxDscpPriMap [j+0]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0);
            pRxDscpPriMap [j+1]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1);
            pRxDscpPriMap [j+2]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2);
            pRxDscpPriMap [j+3]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3);
            pRxDscpPriMap [j+4]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4);
            pRxDscpPriMap [j+5]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5);
            pRxDscpPriMap [j+6]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6);
            pRxDscpPriMap [j+7]   =   CSL_FEXT (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7);
            j+=8;
        }
    }
    else
    {
        j=0;
        for( i = 0; i < 8; i++)
        {
            pRxDscpPriMap [j+0]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0);
            pRxDscpPriMap [j+1]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1);
            pRxDscpPriMap [j+2]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2);
            pRxDscpPriMap [j+3]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3);
            pRxDscpPriMap [j+4]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4);
            pRxDscpPriMap [j+5]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5);
            pRxDscpPriMap [j+6]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6);
            pRxDscpPriMap [j+7]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7);
            j+=8;
        }
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPortRxDscpMap
 *
 *   @b Description
 *   @n This function sets up the contents of the Port DSCP to Priority
 *      Mapping Registers corresponding to the CPSW port specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the DSCP mapping
                                registers must be configured.
        pRxDscpPriMap           Array of Port Rx DSCP to priority mapping values
                                that must be configured to the registers.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  The input parameter 'pRxDscpPriMap' must be large enough to hold all
 *       the 64 priority values read from the register.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6,
 *      CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7,
 *
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6,
 *      CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7
 *
 *
 *   @b Example
 *   @verbatim
 *      Uint32      rxDscpPriMap [64], portNum;

        portNum = 1;

        for (i = 0; i < 64; i ++)
            port0TxPriMap [i] = i/8;

        CSL_CPSW_setPortRxDscpMap (portNum, rxDscpPriMap);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPortRxDscpMap (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxDscpPriMap
);/* for misra warnings*/
static inline void CSL_CPSW_setPortRxDscpMap (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pRxDscpPriMap
)
{
    int32_t i, j;

    if(portNum == 0)
    {
        j=0;
        for( i = 0; i < 8; i++)
        {
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0, pRxDscpPriMap [j+0]);
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1, pRxDscpPriMap [j+1]);
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2, pRxDscpPriMap [j+2]);
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3, pRxDscpPriMap [j+3]);
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4, pRxDscpPriMap [j+4]);
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5, pRxDscpPriMap [j+5]);
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6, pRxDscpPriMap [j+6]);
            CSL_FINS (hCpswRegs->P0_RX_DSCP_PRI_MAP[i], CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7, pRxDscpPriMap [j+7]);
            j+=8;
        }
    }
    else
    {
        j=0;
        for( i = 0; i < 8; i++)
        {
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0, pRxDscpPriMap [j+0]);
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1, pRxDscpPriMap [j+1]);
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2, pRxDscpPriMap [j+2]);
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3, pRxDscpPriMap [j+3]);
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4, pRxDscpPriMap [j+4]);
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5, pRxDscpPriMap [j+5]);
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6, pRxDscpPriMap [j+6]);
            CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_RX_DSCP_PRI_MAP[i], CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7, pRxDscpPriMap [j+7]);
            j+=8;
        }
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortVlanReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the VLAN Register corresponding
 *      to the CPSW port number specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the VLAN register
                                contents must be read
        pPortVID                Port VLAN Id
        pPortCFI                Port CFI bit
        pPortPRI                Port VLAN priority (0-7, 7 is highest priority)
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P0_PORT_VLAN_PORT_VID,
 *      CPSW_3G_P0_PORT_VLAN_PORT_CFI,
 *      CPSW_3G_P0_PORT_VLAN_PORT_PRI,
 *
 *      CPSW_3G_P_PORT_VLAN_PORT_VID,
 *      CPSW_3G_P_PORT_VLAN_PORT_CFI,
 *      CPSW_3G_P_PORT_VLAN_PORT_PRI,
 *
 *   @b Example
 *   @verbatim
 *      Uint32      portVID, portCFI, portPRI, portNum;

        portNum =   1;

        CSL_CPSW_getPortVlanReg (portNum, &portVID, &portCFI, &portPRI);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortVlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortVID,
    Uint32*                     pPortCFI,
    Uint32*                     pPortPRI
); /*for misra warnings*/
static inline void CSL_CPSW_getPortVlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortVID,
    Uint32*                     pPortCFI,
    Uint32*                     pPortPRI
)
{
    if(portNum == 0)
    {
        *pPortVID   =   CSL_FEXT (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_VID);
        *pPortCFI   =   CSL_FEXT (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_CFI);
        *pPortPRI   =   CSL_FEXT (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_PRI);
    }
    else
    {
        *pPortVID   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_PORT_VLAN, CPSW_3G_P_PORT_VLAN_PORT_VID);
        *pPortCFI   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_PORT_VLAN, CPSW_3G_P_PORT_VLAN_PORT_CFI);
        *pPortPRI   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_PORT_VLAN, CPSW_3G_P_PORT_VLAN_PORT_PRI);
    }

    return;
}


/** ============================================================================
 *   @n@b CSL_CPSW_setPortVlanReg
 *
 *   @b Description
 *   @n This function sets up the contents of the VLAN Register corresponding to
 *      the CPSW port number specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the VLAN register
                                must be configured.
        portVID                 Port VLAN Id to be configured
        portCFI                 Port CFI bit to be configured
        portPRI                 Port VLAN priority to be configured
                                (0-7, 7 is highest priority)
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_P0_PORT_VLAN_PORT_VID,
 *      CPSW_3G_P0_PORT_VLAN_PORT_CFI,
 *      CPSW_3G_P0_PORT_VLAN_PORT_PRI,
 *
 *      CPSW_3G_P_PORT_VLAN_PORT_VID,
 *      CPSW_3G_P_PORT_VLAN_PORT_CFI,
 *      CPSW_3G_P_PORT_VLAN_PORT_PRI,
 *
 *   @b Example
 *   @verbatim
 *      Uint32      portVID, portCFI, portPRI, portNum;

        portNum     =   1;
        portVID     =   1;
        portCFI     =   0;
        portPRI     =   7;

        CSL_CPSW_setPortVlanReg (portNum, portVID, portCFI, portPRI);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPortVlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32                      portVID,
    Uint32                      portCFI,
    Uint32                      portPRI
); /*for misra warnings*/
static inline void CSL_CPSW_setPortVlanReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32                      portVID,
    Uint32                      portCFI,
    Uint32                      portPRI
)
{
    if (portNum == 0)
    {
        CSL_FINS (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_VID, portVID);
        CSL_FINS (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_CFI, portCFI);
        CSL_FINS (hCpswRegs->P0_PORT_VLAN, CPSW_3G_P0_PORT_VLAN_PORT_PRI, portPRI);
    }
    else
    {
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_PORT_VLAN, CPSW_3G_P_PORT_VLAN_PORT_VID, portVID);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_PORT_VLAN, CPSW_3G_P_PORT_VLAN_PORT_CFI, portCFI);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_PORT_VLAN, CPSW_3G_P_PORT_VLAN_PORT_PRI, portPRI);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortTxPriMapReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the Transmit Header Priority to
 *      Switch Priority Mapping Register corresponding to the MAC port number
 *      specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 MAC port number for which the register contents
                                must be read and returned.
        pPortTxPriMap           Array of Port Tx priority map priority values
                                read from the register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  The input parameter 'pPortTxPriMap' must be large enough to hold all
 *       the 8 priority values read from the register.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P_TX_PRI_MAP_PRI0,
 *      CPSW_3G_P_TX_PRI_MAP_PRI1,
 *      CPSW_3G_P_TX_PRI_MAP_PRI2,
 *      CPSW_3G_P_TX_PRI_MAP_PRI3,
 *      CPSW_3G_P_TX_PRI_MAP_PRI4,
 *      CPSW_3G_P_TX_PRI_MAP_PRI5,
 *      CPSW_3G_P_TX_PRI_MAP_PRI6,
 *      CPSW_3G_P_TX_PRI_MAP_PRI7
 *
 *   @b Example
 *   @verbatim
 *      Uint32      portTxPriMap [8], portNum;

        portNum =   1;

        CSL_CPSW_getPortTxPriMapReg (portNum, portTxPriMap);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortTxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortTxPriMap
);/* for misra warnings*/
static inline void CSL_CPSW_getPortTxPriMapReg (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint32*                     pPortTxPriMap
)
{
    if (portNum == 0)
    {
        pPortTxPriMap [0]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI0);
        pPortTxPriMap [1]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI1);
        pPortTxPriMap [2]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI2);
        pPortTxPriMap [3]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI3);
        pPortTxPriMap [4]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI4);
        pPortTxPriMap [5]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI5);
        pPortTxPriMap [6]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI6);
        pPortTxPriMap [7]   =   CSL_FEXT (hCpswRegs->P0_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI7);
    } else
    {
        pPortTxPriMap [0]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI0);
        pPortTxPriMap [1]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI1);
        pPortTxPriMap [2]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI2);
        pPortTxPriMap [3]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI3);
        pPortTxPriMap [4]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI4);
        pPortTxPriMap [5]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI5);
        pPortTxPriMap [6]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI6);
        pPortTxPriMap [7]   =   CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_TX_PRI_MAP, CPSW_3G_P_TX_PRI_MAP_PRI7);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getPortMACAddress
 *
 *   @b Description
 *   @n This function retreives the source MAC address of the Tx Pause Frame corresponding to the
 *      CPSW port number specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the source MAC address
                                must be read and returned. (1-8)
        pMacAddress             6 byte Source MAC address read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  The input parameter 'pMacAddres' must be large enough the 6 byte
 *       MAC address returned by this API.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_P_SA_LO_MACSRCADDR_7_0,
 *      CPSW_3G_P_SA_LO_MACSRCADDR_15_8,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_23_16,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_31_24,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_39_32,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_47_40
 *
 *   @b Example
 *   @verbatim
 *      Uint8   macAddress [6], portNum;

        portNum =   1;

        CSL_CPSW_getPortMACAddress (portNum, macAddress);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getPortMACAddress (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint8*                      pMacAddress
);/* for misra warnings*/
static inline void CSL_CPSW_getPortMACAddress (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint8*                      pMacAddress
)
{
    if (portNum != 0)
    {
        pMacAddress [0]   =   (Uint8)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_LO, CPSW_3G_P_SA_LO_MACSRCADDR_7_0);
        pMacAddress [1]   =   (Uint8)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_LO, CPSW_3G_P_SA_LO_MACSRCADDR_15_8);
        pMacAddress [2]   =   (Uint8)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_23_16);
        pMacAddress [3]   =   (Uint8)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_31_24);
        pMacAddress [4]   =   (Uint8)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_39_32);
        pMacAddress [5]   =   (Uint8)CSL_FEXT (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_47_40);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setPortMACAddress
 *
 *   @b Description
 *   @n This function sets up the source MAC address the Tx Pause Frame corresponding to the
 *      CPSW port number specified.
 *
 *   @b Arguments
     @verbatim
        portNum                 CPSW port number for which the source MAC address
                                must be setup. (1-8)
        pMacAddress             6 byte Source MAC address to configure.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  The input parameter 'pMacAddres' is expected to be 6 bytes long.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_P_SA_LO_MACSRCADDR_7_0,
 *      CPSW_3G_P_SA_LO_MACSRCADDR_15_8,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_23_16,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_31_24,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_39_32,
 *      CPSW_3G_P_SA_HI_MACSRCADDR_47_40
 *
 *   @b Example
 *   @verbatim
 *      Uint8   macAddress [6], portNum;

        portNum         =   1;
        macAddress [0]  =   0x01;
        macAddress [1]  =   0x02;
        macAddress [2]  =   0x03;
        macAddress [3]  =   0x04;
        macAddress [4]  =   0x05;
        macAddress [5]  =   0x06;

        CSL_CPSW_setPortMACAddress (portNum, macAddress);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setPortMACAddress (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint8*                      pMacAddress
);/* for misra warnings*/
static inline void CSL_CPSW_setPortMACAddress (
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNum,
    Uint8*                      pMacAddress
)
{
    if ((portNum >= (Uint32)1U) &&  (portNum <= (Uint32)2U))
    {
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_LO, CPSW_3G_P_SA_LO_MACSRCADDR_7_0,   (Uint32)pMacAddress [0]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_LO, CPSW_3G_P_SA_LO_MACSRCADDR_15_8,  (Uint32)pMacAddress [1]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_23_16, (Uint32)pMacAddress [2]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_31_24, (Uint32)pMacAddress [3]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_39_32, (Uint32)pMacAddress [4]);
        CSL_FINS (hCpswRegs->PORT_INFO[portNum-(Uint32)1U].P_SA_HI, CPSW_3G_P_SA_HI_MACSRCADDR_47_40, (Uint32)pMacAddress [5]);
    }

    return;
}



/********************************************************************************
*************************  Statistics (STATS) Submodule *************************
********************************************************************************/

/** ============================================================================
 *   @n@b CSL_CPSW_getStats
 *
 *   @b Description
 *   @n The CPSW stats are divided into 2 blocks, i.e., Stats for Host port (switch Port 0)
 *      and Stats for MAC ports (Port 1 and Port2). This function
 *          - retreives hardware statistics for both the stat blocks.
 *          - Clear out the stats by the count being returned to application
 *          - Accumulates the stats count before returning to Application
 *      Function requires appplication to memset the stats (once before first
 *            use for accumulator, or once per use without accumulation)
 *      In the case of Linux ARM master use case all CPSW stats is recommended
 *      to be accessed from Linux.
 *      This function unconditionally clears the stats, so it requires the
 *      caller have exclusive ownership of the switch.  Otherwise, none of the
 *      callers (including Linux) will have complete accumulated stats.
 *      This function can be used to clear the stats by memesetting pCpswStats
 *      to 0 and discarding the returned stats.
 *
 *
 *   @b Arguments
     @verbatim
        pCpswStats              Array of CSL_CPSW_STATS structure that needs to be filled
                                with the stats read from the hardware. This function expects
                                that the array passed to it is big enough to hold the stats
                                for both stat blocks, i.e., size of array passed to this
                                function must be 2.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_RXGOODFRAMES,
 *      CPSW_RXBROADCASTFRAMES,
 *      CPSW_RXMULTICASTFRAMES,
 *      CPSW_RXPAUSEFRAMES,
 *      CPSW_RXCRCERRORS,
 *      CPSW_RXALIGNCODEERRORS,
 *      CPSW_RXOVERSIZEDFRAMES,
 *      CPSW_RXJABBERFRAMES,
 *      CPSW_RXUNDERSIZEDFRAMES,
 *      CPSW_RXFRAGMENTS,
 *      CPSW_RXOCTETS,
 *      CPSW_TXGOODFRAMES,
 *      CPSW_TXBROADCASTFRAMES,
 *      CPSW_TXMULTICASTFRAMES,
 *      CPSW_TXPAUSEFRAMES,
 *      CPSW_TXDEFERREDFRAMES,
 *      CPSW_TXCOLLISIONFRAMES,
 *      CPSW_TXSINGLECOLLFRAMES,
 *      CPSW_TXMULTCOLLFRAMES,
 *      CPSW_TXEXCESSIVECOLLISIONS,
 *      CPSW_TXLATECOLLISIONS,
 *      CPSW_TXUNDERRUN,
 *      CPSW_TXCARRIERSENSEERRORS,
 *      CPSW_TXOCTETS,
 *      CPSW_OCTETFRAMES64,
 *      CPSW_OCTETFRAMES65T127,
 *      CPSW_OCTETFRAMES128T255,
 *      CPSW_OCTETFRAMES256T511,
 *      CPSW_OCTETFRAMES512T1023,
 *      CPSW_OCTETFRAMES1024TUP,
 *      CPSW_NETOCTETS,
 *      CPSW_RXSOFOVERRUNS,
 *      CPSW_RXMOFOVERRUNS,
 *      CPSW_RXDMAOVERRUNS
 *
 *   @b Affects
 *   @n CPSW_RXGOODFRAMES=0,
 *      CPSW_RXBROADCASTFRAMES=0,
 *      CPSW_RXMULTICASTFRAMES=0,
 *      CPSW_RXPAUSEFRAMES=0,
 *      CPSW_RXCRCERRORS=0,
 *      CPSW_RXALIGNCODEERRORS=0,
 *      CPSW_RXOVERSIZEDFRAMES=0,
 *      CPSW_RXJABBERFRAMES=0,
 *      CPSW_RXUNDERSIZEDFRAMES=0,
 *      CPSW_RXFRAGMENTS=0,
 *      CPSW_RXOCTETS=0,
 *      CPSW_TXGOODFRAMES=0,
 *      CPSW_TXBROADCASTFRAMES=0,
 *      CPSW_TXMULTICASTFRAMES=0,
 *      CPSW_TXPAUSEFRAMES=0,
 *      CPSW_TXDEFERREDFRAMES=0,
 *      CPSW_TXCOLLISIONFRAMES=0,
 *      CPSW_TXSINGLECOLLFRAMES=0,
 *      CPSW_TXMULTCOLLFRAMES=0,
 *      CPSW_TXEXCESSIVECOLLISIONS=0,
 *      CPSW_TXLATECOLLISIONS=0,
 *      CPSW_TXUNDERRUN=0,
 *      CPSW_TXCARRIERSENSEERRORS=0,
 *      CPSW_TXOCTETS=0,
 *      CPSW_OCTETFRAMES64=0,
 *      CPSW_OCTETFRAMES65T127=0,
 *      CPSW_OCTETFRAMES128T255=0,
 *      CPSW_OCTETFRAMES256T511=0,
 *      CPSW_OCTETFRAMES512T1023=0,
 *      CPSW_OCTETFRAMES1024TUP=0,
 *      CPSW_NETOCTETS=0,
 *      CPSW_RXSOFOVERRUNS=0,
 *      CPSW_RXMOFOVERRUNS=0,
 *      CPSW_RXDMAOVERRUNS=0
 *
 *   @b Example
 *   @verbatim
 *      CSL_CPSW_STATS     stats [2];

        CSL_CPSW_getStats (stats);
	 @endverbatim
 * =============================================================================
 */

static inline void CSL_CPSW_getStats (
    CSL_cpswHandle          hCpswRegs,
    CSL_CPSW_STATS*         pCpswStats
);/* for misra warnings*/
static inline void CSL_CPSW_getStats (
    CSL_cpswHandle          hCpswRegs,
    CSL_CPSW_STATS*         pCpswStats
)
{
    Uint32                      numStats;
    volatile Uint32             *pRegAddr;
    Uint32                      *pStatAddr;
    Uint32                      statval;

    pStatAddr   =   (Uint32 *)(pCpswStats);

    pRegAddr    =	&hCpswRegs->STATS.RXGOODFRAMES;
    for (numStats = 0; numStats < sizeof(CSL_CPSW_STATS)/sizeof(Uint32); numStats++)
    {
        statval         =   *pRegAddr;
        *pRegAddr       =   statval;
        pRegAddr++;
        statval         +=  *pStatAddr;
        *pStatAddr      =   statval;
        pStatAddr++;
    }

    return;
}
/** ============================================================================
 *   @n@b CSL_CPSW_getRawStats
 *
 *   @b Description
 *   @n The CPSW stats are divided into 9 blocks, i.e., Stats for Host port (switch Port 0)
 *      and Stats for MAC ports (Port 1-8). This function retreives snapshot of
 *      hardware statistics for all the stat blocks. In the case of Linux ARM master
 *      use case all CPSW stats is recommended to be accessed from Linux.

 *      Since this function does not clear the stats, its possible to have
 *      non-exclusive ownership of the switch and use this function without
 *      corrupting other caller's view of the stats.
 *
 *      Additional Note: In order to avoid stats loss due to rollovers, application
 *      would need to poll the stats by determining the correct interval.
 *      The stat CPSW_NETOCTETS would be first one to roll over
 *      The software must poll and accumulate the stats faster than this rate.
 *      On a 1 gigabit network, it takes approximately
 *      (0x100000000/(1000000000/8)/2)=17 seconds to roll over (the /2 is because
 *      this stat contains both tx and rx, both of which run at gigabit).
 *      A good rule of thumb is to poll at twice this rate (8-9 seconds).
 *
 *      If it is really necessary for application to have multiple nonexclusive
 *      owners of the switch, it is possible for all callers to have a view of
 *      the accumulated statistics if they (including Linux) follows the
 *      differential accumulation of the stats defiened below:
 *      uint64_t accum_CPSW_NETOCTETS;
 *      uint32_t old_CPSW_NETOCTETS, new_CPSW_NETOCTETS, diff_CPSW_NETOCTETS;
 *
 *       diff_CPSW_NETOCTETS = new_CPSW_NETOCTETS - old_CPSW_NETOCTETS; // let rollover occur, no "if" required
 *       old_CPSW_NETOCTETS = new_CPSW_NETOCTETS;
 *       accum_CPSW_NETOCTETS += diff_CPSW_NETOCTETS
 *
 *   @b Arguments
     @verbatim
        pCpswStats              Array of CSL_CPSW_STATS structure that needs to be filled
                                with the stats read from the hardware. This function expects
                                that the array passed to it is big enough to hold the stats
                                for both stat blocks, i.e., size of array passed to this
                                function must be 5 or 9 for 5-port/9-port switch respectively.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_RXGOODFRAMES,
 *      CPSW_RXBROADCASTFRAMES,
 *      CPSW_RXMULTICASTFRAMES,
 *      CPSW_RXPAUSEFRAMES,
 *      CPSW_RXCRCERRORS,
 *      CPSW_RXALIGNCODEERRORS,
 *      CPSW_RXOVERSIZEDFRAMES,
 *      CPSW_RXJABBERFRAMES,
 *      CPSW_RXUNDERSIZEDFRAMES,
 *      CPSW_RXFRAGMENTS,
 *      CPSW_ALE_DROP,
 *      CPSW_ALE_OVERRUN_DROP,
 *      CPSW_RXOCTETS,
 *      CPSW_TXGOODFRAMES,
 *      CPSW_TXBROADCASTFRAMES,
 *      CPSW_TXMULTICASTFRAMES,
 *      CPSW_TXPAUSEFRAMES,
 *      CPSW_TXDEFERREDFRAMES,
 *      CPSW_TXCOLLISIONFRAMES,
 *      CPSW_TXSINGLECOLLFRAMES,
 *      CPSW_TXMULTCOLLFRAMES,
 *      CPSW_TXEXCESSIVECOLLISIONS,
 *      CPSW_TXLATECOLLISIONS,
 *      CPSW_TXUNDERRUN,
 *      CPSW_TXCARRIERSENSEERRORS,
 *      CPSW_TXOCTETS,
 *      CPSW_OCTETFRAMES64,
 *      CPSW_OCTETFRAMES65T127,
 *      CPSW_OCTETFRAMES128T255,
 *      CPSW_OCTETFRAMES256T511,
 *      CPSW_OCTETFRAMES512T1023,
 *      CPSW_OCTETFRAMES1024TUP,
 *      CPSW_NETOCTETS,
 *
 *   @b Example
 *   @verbatim
 *      CSL_CPSW_STATS     stats [9];

        CSL_CPSW_getRawStats (stats);
	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getRawStats (
    CSL_cpswHandle          hCpswRegs,
    CSL_CPSW_STATS*         pCpswStats
);/* for misra warnings*/
static inline void CSL_CPSW_getRawStats (
    CSL_cpswHandle          hCpswRegs,
    CSL_CPSW_STATS*         pCpswStats
)
{
    Uint32                      numStats;
    volatile Uint32             *pRegAddr;
    Uint32                      *pStatAddr;

    pStatAddr   =   (Uint32 *)(pCpswStats);

    pRegAddr    =	&hCpswRegs->STATS.RXGOODFRAMES;
    for (numStats = 0; numStats < sizeof(CSL_CPSW_STATS)/sizeof(Uint32); numStats++)
    {
        *pStatAddr    =   *pRegAddr;
        pStatAddr++;
        pRegAddr++;
    }

    return;
}

/********************************************************************************
********************  Address Lookup Engine (ALE) Submodule *********************
********************************************************************************/

/** ============================================================================
 *   @n@b CSL_CPSW_getAleVersionInfo
 *
 *   @b Description
 *   @n This function retrieves the ALE submodule identification and version
 *      information.
 *
 *   @b Arguments
     @verbatim
        pVersionInfo        CSL_CPSW_ALE_VERSION structure that needs to be populated
                            with the ALE version info read from the hardware.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_ID_MINOR_VER,
 *      CPSW_3G_ID_MAJOR_VER,
 *      CPSW_3G_ID_IDENT
 *
 *   @b Example
 *   @verbatim
        CSL_CPSW_ALE_VERSION    versionInfo;

        CSL_CPSW_getAleVersionInfo (&versionInfo);

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleVersionInfo (
    CSL_cpswHandle              hCpswRegs,
	CSL_CPSW_ALE_VERSION*       pVersionInfo
);/* for misra warnings*/
static inline void CSL_CPSW_getAleVersionInfo (
    CSL_cpswHandle              hCpswRegs,
	CSL_CPSW_ALE_VERSION*       pVersionInfo
)
{

    pVersionInfo->minorVer  =   CSL_FEXT (hCpswRegs->ALE.ID, CPSW_3G_ID_MINOR_VER);
    pVersionInfo->majorVer  =   CSL_FEXT (hCpswRegs->ALE.ID, CPSW_3G_ID_MAJOR_VER);
    pVersionInfo->id        =   CSL_FEXT (hCpswRegs->ALE.ID, CPSW_3G_ID_IDENT);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleRateLimitEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE Broadcast and Multicast Rate Limit is
 *      enabled.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE Broadcast and multicast rate limit enabled.
 *	                            Broadcast/multicast packet reception limited to
 *	                            port control register rate limit fields.
 *	 @n  FALSE                  ALE Broadcast and multicast rate limit disabled.
 *	                            Broadcast/multicast rates not limited.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n ALE_SW_CONTROL_ENABLE_RATE_LIMIT
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleRateLimitEnabled () == TRUE)
        {
            // ALE Broadcast/Multicast rate limit enabled
        }
        else
        {
            // ALE Broadcast/Multicast rate limit disabled
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleRateLimitEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleRateLimitEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_RATE_LIMIT);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleRateLimit
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable multicast,
 *      broadcast rate limiting.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_RATE_LIMIT=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleRateLimit ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleRateLimit (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleRateLimit (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_RATE_LIMIT, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleRateLimit
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable multicast,
 *      broadcast rate limiting.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_RATE_LIMIT=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleRateLimit ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleRateLimit (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleRateLimit (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_RATE_LIMIT, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleMacAuthModeEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE MAC Authorization mode is enabled.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE  is in MAC authorization mode.
 *	 @n  FALSE                  ALE not in MAC authorization mode.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_ENABLE_AUTH_MODE
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleMacAuthModeEnabled () == TRUE)
        {
            // ALE  is in MAC authorization mode
        }
        else
        {
            // ALE not in MAC authorization mode
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleMacAuthModeEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleMacAuthModeEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_AUTH_MODE);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleMacAuthMode
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable MAC authorization
 *      mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_AUTH_MODE=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleMacAuthMode ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleMacAuthMode (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleMacAuthMode (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_AUTH_MODE, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleMacAuthMode
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable MAC authorization
 *      mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_AUTH_MODE=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleMacAuthMode ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleMacAuthMode (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleMacAuthMode (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_AUTH_MODE, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleVlanAwareEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE is programmed to be VLAN aware.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE VLAN aware. ALE drops packets if VLAN not found.
 *	 @n  FALSE                  ALE not VLAN aware. Floods if VLAN not found.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_VLAN_AWARE
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleVlanAwareEnabled () == TRUE)
        {
            // ALE VLAN aware
        }
        else
        {
            // ALE not VLAN aware
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleVlanAwareEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleVlanAwareEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_VLAN_AWARE);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleVlanAware
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable VLAN aware
 *      mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_VLAN_AWARE=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleVlanAware ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleVlanAware (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleVlanAware (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_VLAN_AWARE, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleVlanAware
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable VLAN aware
 *      mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_VLAN_AWARE=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleVlanAware ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleVlanAware (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleVlanAware (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_VLAN_AWARE, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleTxRateLimitEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE is programmed to be Tx-port based multicast,
 *      broadcast rate limited.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE Tx rate limit enabled. Broadcast, multicast
 *	                            rate limit counters are transmit port based.
 *	 @n  FALSE                  ALE Tx rate limit disabled. Broadcast, multicast
 *	                            rate limit counters are receive port based.
 *
 *   <b> Pre Condition </b>
 *   @n  CPSW_3G_CONTROL_ENABLE_RATE_LIMIT=1
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_RATE_LIMIT_TX
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleTxRateLimitEnabled () == TRUE)
        {
            // ALE Tx rate limit on
        }
        else
        {
            // ALE Tx rate limit off
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleTxRateLimitEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleTxRateLimitEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_RATE_LIMIT_TX);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleTxRateLimit
 *
 *   @b Description
 *   @n This function configures the ALE control register to select Tx-port based
 *      multicast, broadcast rate limiting
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  CPSW_3G_CONTROL_ENABLE_RATE_LIMIT=1
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_RATE_LIMIT_TX=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleTxRateLimit ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleTxRateLimit (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleTxRateLimit (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_RATE_LIMIT_TX, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleTxRateLimit
 *
 *   @b Description
 *   @n This function configures the ALE control register to select Rx-port based
 *      multicast, broadcast rate limiting
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_RATE_LIMIT_TX=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleTxRateLimit ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleTxRateLimit (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleTxRateLimit (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_RATE_LIMIT_TX, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleBypassEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE is programmed to be in Bypass mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE Bypass mode enabled.
 *	 @n  FALSE                  ALE Bypass mode disabled.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_BYPASS
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleBypassEnabled () == TRUE)
        {
            // ALE Bypass mode on
        }
        else
        {
            // ALE Bypass mode off
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleBypassEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleBypassEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_BYPASS);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleBypass
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable Bypass mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_BYPASS=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleBypass ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleBypass (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleBypass (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_BYPASS, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleBypass
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable Bypass mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_BYPASS=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleBypass ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleBypass (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleBypass (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_BYPASS, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleOUIDenyModeEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE is programmed to be in OUI deny mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE OUI deny mode enabled.
 *	 @n  FALSE                  ALE OUI deny mode disabled.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_ENABLE_OUI_DENY
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleOUIDenyModeEnabled () == TRUE)
        {
            // ALE OUI deny mode on
        }
        else
        {
            // ALE OUI deny mode off
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleOUIDenyModeEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleOUIDenyModeEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_OUI_DENY);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleOUIDenyMode
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable OUI deny mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_OUI_DENY=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleOUIDenyMode ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleOUIDenyMode (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleOUIDenyMode (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_OUI_DENY, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleOUIDenyMode
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable OUI deny mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_OUI_DENY=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleOUIDenyMode ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleOUIDenyMode (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleOUIDenyMode (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_OUI_DENY, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleVID0ModeEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE is programmed to be in VID0 (VLAN ID=0) mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE VID0 mode enabled.
 *	                            Process the packet with VLAN Id = 0
 *	 @n  FALSE                  ALE VID0 mode disabled. Process the packet with
 *	                            VLAN Id =PORT_VLAN[11-0]
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_EN_VID0_MODE
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleVID0ModeEnabled () == TRUE)
        {
            // ALE VID0 mode on
        }
        else
        {
            // ALE VID0 mode off
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleVID0ModeEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleVID0ModeEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_EN_VID0_MODE);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleVID0Mode
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable VID0 mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_EN_VID0_MODE=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleVID0Mode ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleVID0Mode (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleVID0Mode (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_EN_VID0_MODE, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleVID0Mode
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable VID0 mode.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_EN_VID0_MODE=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleVID0Mode ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleVID0Mode (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleVID0Mode (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_EN_VID0_MODE, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleLearnNoVIDEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE is programmed to not learn VLAN Ids.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE Learn no VID enabled.
 *	                            VLAN Id is not learned with source address (source
 *	                            address is not tied to VID)
 *	 @n  FALSE                  ALE VID learning mode enabled.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_LEARN_NO_VID
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleLearnNoVIDEnabled () == TRUE)
        {
            // ALE VID learning disabled
        }
        else
        {
            // ALE VID learning enabled
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleLearnNoVIDEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleLearnNoVIDEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_LEARN_NO_VID);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleLearnNoVID
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable VLAN Id No
 *      Learn, i.e., disable VLAN Id learning.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_LEARN_NO_VID=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleLearnNoVID ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleLearnNoVID (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleLearnNoVID (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_LEARN_NO_VID, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleLearnNoVID
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable VLAN Id learning.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_LEARN_NO_VID=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleLearnNoVID ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleLearnNoVID (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleLearnNoVID (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_LEARN_NO_VID, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleUUNIToHostEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE is programmed to forward unkown unicast
 *      packets to host.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   Unknown unicast packets flood to host also.
 *	 @n  FALSE                  Unknown unicast packets are dropped to the host.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_EN_P0_UNI_FLOOD
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleUUNIToHostEnabled () == TRUE)
        {
            // ALE Unknown UNI packets forwarded to host
        }
        else
        {
            // ALE Unknown UNI packets dropped to host
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleUUNIToHostEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleUUNIToHostEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_EN_P0_UNI_FLOOD);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAleUUNIToHost
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable forwarding
 *      unkown unicast packets to host.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_EN_P0_UNI_FLOOD=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAleUUNIToHost ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAleUUNIToHost (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAleUUNIToHost (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_EN_P0_UNI_FLOOD, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAleUUNIToHost
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable forwarding
 *      unkown unicast packets to host.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_EN_P0_UNI_FLOOD=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAleUUNIToHost ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAleUUNIToHost (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAleUUNIToHost (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_EN_P0_UNI_FLOOD, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_startAleAgeOutNow
 *
 *   @b Description
 *   @n This function configures the ALE control register to initiate an ALE
 *      ageable entry cleanup. This enables the ALE hardware to remove any
 *      ageable table entry that does not have a set touch bit.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_AGE_OUT_NOW=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_startAleAgeOutNow ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_startAleAgeOutNow (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_startAleAgeOutNow (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_AGE_OUT_NOW, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleAgeOutDone
 *
 *   @b Description
 *   @n This function reads the ALE control register's AGE_OUT_NOW bit to check
 *      if the ALE ageable entry cleanup process is done.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE age out process done.
 *	 @n  FALSE                  ALE age out process not yet completed.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_AGE_OUT_NOW
 *
 *   @b Example
 *   @verbatim

        if (CSL_CPSW_isAleAgeOutDone ();

     @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleAgeOutDone (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleAgeOutDone (
    CSL_cpswHandle               hCpswRegs
)
{
    Uint32 ret_val = 0U;
    if ((CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_AGE_OUT_NOW) == 0))
    {
        ret_val = (Uint32)TRUE;
    }
    else
    {
        ret_val = (Uint32)FALSE;
    }
    return ret_val;
}

/** ============================================================================
 *   @n@b CSL_CPSW_clearAleTable
 *
 *   @b Description
 *   @n This function initiates a full ALE table cleanup. The ALE hardware
 *      clears all table entries.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_CLEAR_TABLE=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_clearAleTable ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_clearAleTable (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_clearAleTable (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_CLEAR_TABLE, (uint32_t)1U);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isAleEnabled
 *
 *   @b Description
 *   @n This function indicates if ALE processing is enabled.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   ALE enabled. ALE packet processing will be done.
 *	 @n  FALSE                  ALE disabled. All packets are dropped by ALE.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_CONTROL_ENABLE_ALE
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isAleEnabled () == TRUE)
        {
            // ALE enabled
        }
        else
        {
            // ALE disabled
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isAleEnabled (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isAleEnabled (
    CSL_cpswHandle               hCpswRegs
)
{

    return CSL_FEXT (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_ALE);
}

/** ============================================================================
 *   @n@b CSL_CPSW_enableAle
 *
 *   @b Description
 *   @n This function configures the ALE control register to enable ALE processing.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_ALE=1
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_enableAle ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_enableAle (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableAle (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_ALE, (Uint32) 1);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_disableAle
 *
 *   @b Description
 *   @n This function configures the ALE control register to disable ALE processing.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_CONTROL_ENABLE_ALE=0
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_disableAle ();

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_disableAle (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableAle (
    CSL_cpswHandle               hCpswRegs
)
{
    CSL_FINS (hCpswRegs->ALE.CONTROL, CPSW_3G_CONTROL_ENABLE_ALE, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleControlReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the ALE control register.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 >=0                ALE control register contents.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n ALE_SW_CONTROL
 *
 *   @b Example
 *   @verbatim
        Uint32      aleCtrlVal;

        aleCtrlVal  =   CSL_CPSW_getAleControlReg ();

     @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_getAleControlReg (
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getAleControlReg (
    CSL_cpswHandle               hCpswRegs
)
{
    return hCpswRegs->ALE.CONTROL;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleControlReg
 *
 *   @b Description
 *   @n This function sets up the contents of the ALE control register.
 *
 *   @b Arguments
     @verbatim
        aleCtrlVal          Value to be configured to the ALE control register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n ALE_SW_CONTROL
 *
 *   @b Example
 *   @verbatim
 *      Uint32          aleCtrlVal = 0;

        aleCtrlVal      =   CSL_CPSW_getAleControlReg ();
        aleCtrlVal      |=  CSL_CPSW_3G_ALECONTROL_CLRTABLE_EN;

        CSL_CPSW_setAleControlReg (&aleCtrlRegInfo);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleControlReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      aleCtrlVal
);/* for misra warnings*/
static inline void CSL_CPSW_setAleControlReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      aleCtrlVal
)
{
    hCpswRegs->ALE.CONTROL  =   aleCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAlePrescaleReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the ALE Prescale register.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 >=0                ALE prescale register contents.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_PRESCALE_PRESCALE
 *
 *   @b Example
 *   @verbatim
        Uint32      alePrescaleVal;

        alePrescaleVal  =   CSL_CPSW_getAlePrescaleReg ();

     @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_getAlePrescaleReg
(
    CSL_cpswHandle               hCpswRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getAlePrescaleReg
(
    CSL_cpswHandle               hCpswRegs
)
{
    return CSL_FEXT(hCpswRegs->ALE.PRESCALE, CPSW_3G_PRESCALE_PRESCALE);
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAlePrescaleReg
 *
 *   @b Description
 *   @n This function sets up the contents of the ALE prescale register.
 *
 *   @b Arguments
     @verbatim
        alePrescaleVal      Value to be configured to the ALE Prescale register.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_PRESCALE_PRESCALE
 *
 *   @b Example
 *   @verbatim
 *      Uint32          alePrescaleVal = 0;

        alePrescaleVal  =   10;

        CSL_CPSW_setAlePrescaleReg (&aleCtrlRegInfo);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAlePrescaleReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      alePrescaleVal
);/* for misra warnings*/
static inline void CSL_CPSW_setAlePrescaleReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      alePrescaleVal
)
{
    CSL_FINS (hCpswRegs->ALE.PRESCALE, CPSW_3G_PRESCALE_PRESCALE, alePrescaleVal);
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleUnkownVlanReg
 *
 *   @b Description
 *   @n This function retrieves the contents of the ALE Unknown VLAN and etc registers.
 *
 *   @b Arguments
     @verbatim
        pUnVlanMemList          Unknown VLAN member list.
        pUnMcastFloodMask       Unknown VLAN Multicast flood mask.
        pUnRegMcastFloodMask    Unknown VLAN Registered Multicast Flood mask.
        pUnForceUntagEgress     Unknown VLAN Force Untagged Egress.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST,
 *
 *   @b Example
 *   @verbatim
        Uint32      unVlanMemList, unMcastFloodMask, unRegMcastFloodMask, unForceUntagEgress;

        CSL_CPSW_getAleUnkownVlanReg (&unVlanMemList,
                                      &unMcastFloodMask,
                                      &unRegMcastFloodMask,
                                      &unForceUntagEgress);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleUnkownVlanReg
(
    CSL_cpswHandle                 hCpswRegs,
    Uint32*                        pUnVlanMemList,
    Uint32*                        pUnMcastFloodMask,
    Uint32*                        pUnRegMcastFloodMask,
    Uint32*                        pUnForceUntagEgress
); /*for misra warnings*/
static inline void CSL_CPSW_getAleUnkownVlanReg
(
    CSL_cpswHandle                 hCpswRegs,
    Uint32*                        pUnVlanMemList,
    Uint32*                        pUnMcastFloodMask,
    Uint32*                        pUnRegMcastFloodMask,
    Uint32*                        pUnForceUntagEgress
)
{
    *pUnVlanMemList         =   CSL_FEXT(hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST);
    *pUnMcastFloodMask      =   CSL_FEXT(hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK);
    *pUnRegMcastFloodMask   =   CSL_FEXT(hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK);
    *pUnForceUntagEgress    =   CSL_FEXT(hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS);
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleUnkownVlanReg
 *
 *   @b Description
 *   @n This function sets up the contents of the ALE Unknown VLAN and etc. register.
 *
 *   @b Arguments
     @verbatim
        unVlanMemList           Unknown VLAN member list.
        unMcastFloodMask        Unknown VLAN Multicast flood mask.
        unRegMcastFloodMask     Unknown VLAN Registered Multicast Flood mask.
        unForceUntagEgress      Unknown VLAN Force Untagged Egress.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST,
 *
 *   @b Example
 *   @verbatim
        Uint32      unVlanMemList, unMcastFloodMask, unRegMcastFloodMask, unForceUntagEgress;

        unVlanMemList           =   0;
        unMcastFloodMask        =   3;
        unRegMcastFloodMask     =   0;
        unForceUntagEgress      =   0;

        CSL_CPSW_setAleUnkownVlanReg (unVlanMemList,
                                      unMcastFloodMask,
                                      unRegMcastFloodMask,
                                      unForceUntagEgress);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleUnkownVlanReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      unVlanMemList,
    Uint32                      unMcastFloodMask,
    Uint32                      unRegMcastFloodMask,
    Uint32                      unForceUntagEgress
); /* for misra warnings */
static inline void CSL_CPSW_setAleUnkownVlanReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      unVlanMemList,
    Uint32                      unMcastFloodMask,
    Uint32                      unRegMcastFloodMask,
    Uint32                      unForceUntagEgress
)
{
    CSL_FINS (hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST, unVlanMemList);
    CSL_FINS (hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK, unMcastFloodMask);
    CSL_FINS (hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK, unRegMcastFloodMask);
    CSL_FINS (hCpswRegs->ALE.UNKNOWN_VLAN, CPSW_3G_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS, unForceUntagEgress);
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleTableEntry
 *
 *   @b Description
 *   @n This function retrieves an ALE table entry corresponding to the
 *      ALE entry index specified in 'index' input parameter. The ALE
 *      entry values corresponding to the ALE_TBLW0, ALE_TBLW1 and
 *      ALE_TBLW2 registers are returned in 'pAleInfoWd0', 'pAleInfoWd1', 'pAleInfoWd2'
 *      output parameters.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pAleInfoWd0             Contents of ALE Table Word 0 Register (ALE_TBLW0).
        pAleInfoWd1             Contents of ALE Table Word 1 Register (ALE_TBLW1).
        pAleInfoWd2             Contents of ALE Table Word 2 Register (ALE_TBLW2).
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0_ENTRY_31_0,
 *      CPSW_3G_TABLE_WORD1_ENTRY_63_32,
 *      CPSW_3G_TABLE_WORD2_ENTRY_71_64
 *
 *   @b Example
 *   @verbatim
        Uint32      index, info0, info1, info2;

        index   =   0;

        CSL_CPSW_getAleTableEntry (index,
                                   &info0,
                                   &info1,
                                   &info2);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleTableEntry
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index,
    Uint32*                     pAleInfoWd0,
    Uint32*                     pAleInfoWd1,
    Uint32*                     pAleInfoWd2
); /*for misra warnings*/
static inline void CSL_CPSW_getAleTableEntry
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index,
    Uint32*                     pAleInfoWd0,
    Uint32*                     pAleInfoWd1,
    Uint32*                     pAleInfoWd2
)
{
    Uint32                      aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    /* Read the ALE table word registers */
    *pAleInfoWd0            =   CSL_FEXT(hCpswRegs->ALE.TABLE_WORD0, CPSW_3G_TABLE_WORD0_ENTRY_31_0);
    *pAleInfoWd1            =   CSL_FEXT(hCpswRegs->ALE.TABLE_WORD1, CPSW_3G_TABLE_WORD1_ENTRY_63_32);
    *pAleInfoWd2            =   CSL_FEXT(hCpswRegs->ALE.TABLE_WORD2, CPSW_3G_TABLE_WORD2_ENTRY_71_64);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleTableEntry
 *
 *   @b Description
 *   @n This function sets up an ALE table entry corresponding to the
 *      ALE entry index specified in 'index' input parameter. The ALE
 *      entry values corresponding to the ALE_TBLW0, ALE_TBLW1 and
 *      ALE_TBLW2 registers msut be specified in 'aleInfoWd0', 'aleInfoWd1', 'aleInfoWd2'
 *      input parameters.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be written.
        aleInfoWd0              Value to write to ALE Table Word 0 Register (ALE_TBLW0).
        aleInfoWd1              Value to write to ALE Table Word 1 Register (ALE_TBLW1).
        aleInfoWd2              Value to write to ALE Table Word 2 Register (ALE_TBLW2).
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_WORD0_ENTRY_31_0,
 *      CPSW_3G_TABLE_WORD1_ENTRY_63_32,
 *      CPSW_3G_TABLE_WORD2_ENTRY_71_64,
 *      CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *
 *
 *   @b Example
 *   @verbatim
        Uint32      index, info0, info1, info2;

        index   =   0;
        info0   =   ...;
        info1   =   ...;
        info2   =   ...;

        CSL_CPSW_setAleTableEntry (index,
                                          info0,
                                          info1,
                                          info2);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleTableEntry
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index,
    Uint32                      aleInfoWd0,
    Uint32                      aleInfoWd1,
    Uint32                      aleInfoWd2
); /*for misra warnings*/
static inline void CSL_CPSW_setAleTableEntry
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index,
    Uint32                      aleInfoWd0,
    Uint32                      aleInfoWd1,
    Uint32                      aleInfoWd2
)
{
    Uint32                      aleTblCtrlVal   =   0;

    /* Set the ALE table word registers */
    CSL_FINS (hCpswRegs->ALE.TABLE_WORD0, CPSW_3G_TABLE_WORD0_ENTRY_31_0, aleInfoWd0);
    CSL_FINS (hCpswRegs->ALE.TABLE_WORD1, CPSW_3G_TABLE_WORD1_ENTRY_63_32, aleInfoWd1);
    CSL_FINS (hCpswRegs->ALE.TABLE_WORD2, CPSW_3G_TABLE_WORD2_ENTRY_71_64, aleInfoWd2);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getALEEntryType
 *
 *   @b Description
 *   @n This function returns the ALE entry type for any given ALE table
 *      entry index.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>  CSL_CPSW_ALE_ENTRYTYPE
 *	 @n	 ALE_ENTRYTYPE_FREE             ALE entry is free.
 *	 @n  ALE_ENTRYTYPE_ADDRESS          ALE entry contains a unicast/multicast address.
 *	 @n  ALE_ENTRYTYPE_VLAN             ALE entry contains a VLAN.
 *	 @n  ALE_ENTRYTYPE_VLANADDRESS      ALE entry contains a VLAN and a unicast/multicast address.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD1
 *
 *   @b Example
 *   @verbatim
 *      Uint32      index = 0;
        if (CSL_CPSW_getALEEntryType () == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry free
        }
	 @endverbatim
 * =============================================================================
 */
static inline CSL_CPSW_ALE_ENTRYTYPE CSL_CPSW_getALEEntryType
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index
);/* for misra warnings*/
static inline CSL_CPSW_ALE_ENTRYTYPE CSL_CPSW_getALEEntryType
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index
)
{
    Uint32                      aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return (CSL_CPSW_ALE_ENTRYTYPE) CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)29, (uint32_t)28);
}

/** ============================================================================
 *   @n@b CSL_CPSW_getALEAddressType
 *
 *   @b Description
 *   @n This function returns the address type of an ALE entry.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>  CSL_CPSW_ALE_ADDRTYPE
 *	 @n	 ALE_ADDRTYPE_UCAST         Address at this entry is unicast
 *	 @n  ALE_ADDRTYPE_MCAST         Address at this entry is multicast
 *	 @n  ALE_ADDRTYPE_OUI           Address at this entry is OUI address
 *
 *   <b> Pre Condition </b>
 *   @n  This function must be called only for an ALE address entry, i.e.,
 *       if @a CSL_CPSW_3G_getALEEntryType () returns ALE_ENTRYTYPE_ADDRESS
 *       or ALE_ENTRYTYPE_VLANADDRESS only.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1
 *
 *   @b Example
 *   @verbatim
 *      Uint32      index = 0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_ADDRESS)
        {
            // ALE entry has an address

            if (CSL_CPSW_getALEAddressType (index) ==  ALE_ADDRTYPE_UCAST)
            {
                // Unicast address
            }
        }
        else
        {
            // Do nothing
        }

        ...
	 @endverbatim
 * =============================================================================
 */
static inline CSL_CPSW_ALE_ADDRTYPE CSL_CPSW_getALEAddressType
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index
);/* for misra warnings*/
static inline CSL_CPSW_ALE_ADDRTYPE CSL_CPSW_getALEAddressType
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      index
)
{
    Uint32                      aleTblCtrlVal   =   0;

    CSL_CPSW_ALE_ADDRTYPE       ret_val;
    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    if (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23, (uint32_t)0) == 0)
    {
        /* Lower 24 bits of Word 0 are all zeros for an OUI address */
        ret_val =  ALE_ADDRTYPE_OUI;
    }
    else
    {
        if (hCpswRegs->ALE.TABLE_WORD1 & (((uint32_t)1U) << 8U))
        {
            /* 40th bit of MAC address is 1 for a multicast address. */
            ret_val =  ALE_ADDRTYPE_MCAST;
        }
        else
        {
            ret_val =  ALE_ADDRTYPE_UCAST;
        }
    }
    return ret_val;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleMcastAddrEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with Multicast address configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pMcastAddrCfg           ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                     index;
        CSL_ALE_MCASTADDR_ENTRY    mcastAddrCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_ADDRESS)
        {
            // ALE entry has an address

            if (CSL_CPSW_getALEAddressType (index) ==  ALE_ADDRTYPE_MCAST)
            {
                // Read Multicast address config from hardware
                CSL_CPSW_getAleMcastAddrEntry (index, &mcastAddrCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_MCASTADDR_ENTRY*       pMcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_MCASTADDR_ENTRY*       pMcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the multicast address configuration */
    pMcastAddrCfg->macAddress[0]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15, (uint32_t)8);
    pMcastAddrCfg->macAddress[1]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7, (uint32_t)0);
    pMcastAddrCfg->macAddress[2]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31, (uint32_t)24);
    pMcastAddrCfg->macAddress[3]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23, (uint32_t)16);
    pMcastAddrCfg->macAddress[4]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15, (uint32_t)8);
    pMcastAddrCfg->macAddress[5]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7, (uint32_t)0);
    pMcastAddrCfg->mcastFwdState        =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31, (uint32_t)30);
    pMcastAddrCfg->superEnable          =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1, (uint32_t)1U);
    pMcastAddrCfg->portMask             =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5, (uint32_t)2);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleMcastAddrEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      Multicast address configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pMcastAddrCfg           ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                              index;
        CSL_CPSW_ALE_MCASTADDR_ENTRY    mcastAddrCfg;

        index   =   0;
        mcastAddrCfg.macAddress [0] = 0x00;
        mcastAddrCfg.macAddress [1] = 0x01;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add Multicast address entry
            CSL_CPSW_setAleMcastAddrEntry (index, &mcastAddrCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_MCASTADDR_ENTRY*       pMcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_MCASTADDR_ENTRY*       pMcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the multicast address configuration */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15U, (uint32_t)8U, pMcastAddrCfg->macAddress[0]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7U, (uint32_t)0U, pMcastAddrCfg->macAddress[1]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31U, (uint32_t)24U, pMcastAddrCfg->macAddress[2]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23U, (uint32_t)16U, pMcastAddrCfg->macAddress[3]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15U, (uint32_t)8U, pMcastAddrCfg->macAddress[4]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7U, (uint32_t)0U, pMcastAddrCfg->macAddress[5]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)30U, pMcastAddrCfg->mcastFwdState);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1U, (uint32_t)1U, pMcastAddrCfg->superEnable);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5U, (uint32_t)2U, pMcastAddrCfg->portMask);

    /* set entry type to address entry */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)29U, (uint32_t)28U, (uint32_t)1U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleVlanMcastAddrEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with VLAN Multicast address configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pVlanMcastAddrCfg       ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_VLANMCASTADDR_ENTRY    vlanMcastAddrCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_VLANADDRESS)
        {
            // ALE entry has a VLAN address

            if (CSL_CPSW_getALEAddressType (index) ==  ALE_ADDRTYPE_MCAST)
            {
                // Read VLAN Multicast address config from hardware
                CSL_CPSW_getAleVlanMcastAddrEntry (index, &vlanMcastAddrCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleVlanMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANMCASTADDR_ENTRY*   pVlanMcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleVlanMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANMCASTADDR_ENTRY*   pVlanMcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the multicast address configuration */
    pVlanMcastAddrCfg->macAddress[0]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15, (uint32_t)8);
    pVlanMcastAddrCfg->macAddress[1]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7, (uint32_t)0);
    pVlanMcastAddrCfg->macAddress[2]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31, (uint32_t)24);
    pVlanMcastAddrCfg->macAddress[3]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23, (uint32_t)16);
    pVlanMcastAddrCfg->macAddress[4]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15, (uint32_t)8);
    pVlanMcastAddrCfg->macAddress[5]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7, (uint32_t)0);
    pVlanMcastAddrCfg->vlanId               =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27, (uint32_t)16);
    pVlanMcastAddrCfg->mcastFwdState        =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31, (uint32_t)30);
    pVlanMcastAddrCfg->superEnable          =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1, (uint32_t)1U);
    pVlanMcastAddrCfg->portMask             =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5, (uint32_t)2);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleVlanMcastAddrEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      VLAN Multicast address configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pVlanMcastAddrCfg       ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_VLANMCASTADDR_ENTRY    vlanMcastAddrCfg;

        index   =   0;
        vlanMcastAddrCfg.macAddress [0] = 0x00;
        vlanMcastAddrCfg.macAddress [1] = 0x01;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add VLAN Multicast address entry
            CSL_CPSW_setAleVlanMcastAddrEntry (index, &vlanMcastAddrCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleVlanMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANMCASTADDR_ENTRY*   pVlanMcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleVlanMcastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANMCASTADDR_ENTRY*   pVlanMcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the VLAN multicast address configuration */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15U, (uint32_t)8U, pVlanMcastAddrCfg->macAddress[0]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7U, (uint32_t)0U, pVlanMcastAddrCfg->macAddress[1]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31U, (uint32_t)24U, pVlanMcastAddrCfg->macAddress[2]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23U, (uint32_t)16U, pVlanMcastAddrCfg->macAddress[3]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15U, (uint32_t)8U, pVlanMcastAddrCfg->macAddress[4]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7U, (uint32_t)0U, pVlanMcastAddrCfg->macAddress[5]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27U, (uint32_t)16U, pVlanMcastAddrCfg->vlanId);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)30U, pVlanMcastAddrCfg->mcastFwdState);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1U, (uint32_t)1U, pVlanMcastAddrCfg->superEnable);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5U, (uint32_t)2U, pVlanMcastAddrCfg->portMask);

    /* set entry type to VLAN address entry */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)29U, (uint32_t)28U, (uint32_t)3U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleUnicastAddrEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with Unicast address configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pUcastAddrCfg           ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_UNICASTADDR_ENTRY      ucastAddrCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_ADDRESS)
        {
            // ALE entry has an address

            if (CSL_CPSW_getALEAddressType (index) ==  ALE_ADDRTYPE_UCAST)
            {
                // Read Unicast address config from hardware
                CSL_CPSW_getAleUnicastAddrEntry (index, &ucastAddrCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_UNICASTADDR_ENTRY*     pUcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_UNICASTADDR_ENTRY*     pUcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the multicast address configuration */
    pUcastAddrCfg->macAddress[0]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15, (uint32_t)8);
    pUcastAddrCfg->macAddress[1]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7, (uint32_t)0);
    pUcastAddrCfg->macAddress[2]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31, (uint32_t)24);
    pUcastAddrCfg->macAddress[3]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23, (uint32_t)16);
    pUcastAddrCfg->macAddress[4]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15, (uint32_t)8);
    pUcastAddrCfg->macAddress[5]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7, (uint32_t)0);
    pUcastAddrCfg->ucastType            =   (CSL_CPSW_ALE_UCASTTYPE) CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31, (uint32_t)30);
    pUcastAddrCfg->secureEnable         =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)0, (uint32_t)0);
    pUcastAddrCfg->blockEnable          =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1, (uint32_t)1U);
    pUcastAddrCfg->portNumber           =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5, (uint32_t)2);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleUnicastAddrEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      unicast address configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pUcastAddrCfg           ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_UNICASTADDR_ENTRY      ucastAddrCfg;

        index   =   0;
        ucastAddrCfg.macAddress [0] = 0x00;
        ucastAddrCfg.macAddress [1] = 0x01;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add Unicast address entry
            CSL_CPSW_setAleUnicastAddrEntry (index, &ucastAddrCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_UNICASTADDR_ENTRY*     pUcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_UNICASTADDR_ENTRY*     pUcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the Unicast address configuration */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15U, (uint32_t)8U, pUcastAddrCfg->macAddress[0]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7U, (uint32_t)0U, pUcastAddrCfg->macAddress[1]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31U, (uint32_t)24U, pUcastAddrCfg->macAddress[2]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23U, (uint32_t)16U, pUcastAddrCfg->macAddress[3]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15U, (uint32_t)8U, pUcastAddrCfg->macAddress[4]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7U, (uint32_t)0U, pUcastAddrCfg->macAddress[5]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)30U, pUcastAddrCfg->ucastType);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)0U, (uint32_t)0U, pUcastAddrCfg->secureEnable);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1U, (uint32_t)1U, pUcastAddrCfg->blockEnable);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5U, (uint32_t)2U, pUcastAddrCfg->portNumber);

    /* set entry type to address entry */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)29U, (uint32_t)28U, (uint32_t)1U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleOUIAddrEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with OUI address configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pOUIAddrCfg             ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_OUIADDR_ENTRY          ouiAddrCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_ADDRESS)
        {
            // ALE entry has an address

            if (CSL_CPSW_getALEAddressType (index) ==  ALE_ADDRTYPE_OUI)
            {
                // Read Unicast address config from hardware
                CSL_CPSW_getAleOUIAddrEntry (index, &ouiAddrCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleOUIAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUIADDR_ENTRY*         pOUIAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleOUIAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUIADDR_ENTRY*         pOUIAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the multicast address configuration */
    pOUIAddrCfg->ouiAddress[0]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15, (uint32_t)8);
    pOUIAddrCfg->ouiAddress[1]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7, (uint32_t)0);
    pOUIAddrCfg->ouiAddress[2]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31, (uint32_t)24);
    pOUIAddrCfg->ucastType            =   (CSL_CPSW_ALE_UCASTTYPE) CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31, (uint32_t)30);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleOUIAddrEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      OUI address configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pOUIAddrCfg             ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_OUIADDR_ENTRY          ouiAddrCfg;

        index   =   0;
        ouiAddrCfg.ouiAddress [0] = 0x00;
        ouiAddrCfg.ouiAddress [1] = 0x01;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add OUI address entry
            CSL_CPSW_setAleOUIAddrEntry (index, &ouiAddrCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleOUIAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUIADDR_ENTRY*         pOUIAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleOUIAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUIADDR_ENTRY*         pOUIAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the Unicast address configuration */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15U, (uint32_t)8U, pOUIAddrCfg->ouiAddress[0]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7U, (uint32_t)0U, pOUIAddrCfg->ouiAddress[1]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31U, (uint32_t)24U, pOUIAddrCfg->ouiAddress[2]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)30U, pOUIAddrCfg->ucastType);

    /* set entry type to address entry */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)29U, (uint32_t)28U, (uint32_t)1U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}


/** ============================================================================
 *   @n@b CSL_CPSW_getAleVlanUnicastAddrEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with VLAN Unicast address configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pVlanUcastAddrCfg       ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_VLANUNICASTADDR_ENTRY  vlanUcastAddrCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_VLANADDRESS)
        {
            // ALE entry has a VLAN address

            if (CSL_CPSW_getALEAddressType (index) ==  ALE_ADDRTYPE_UCAST)
            {
                // Read VLAN Unicast address config from hardware
                CSL_CPSW_getAleVlanUnicastAddrEntry (index, &ucvlanUcastAddrCfgastAddrCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleVlanUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANUNICASTADDR_ENTRY* pVlanUcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleVlanUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANUNICASTADDR_ENTRY* pVlanUcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the multicast address configuration */
    pVlanUcastAddrCfg->macAddress[0]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15, (uint32_t)8);
    pVlanUcastAddrCfg->macAddress[1]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7, (uint32_t)0);
    pVlanUcastAddrCfg->macAddress[2]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31, (uint32_t)24);
    pVlanUcastAddrCfg->macAddress[3]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23, (uint32_t)16);
    pVlanUcastAddrCfg->macAddress[4]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15, (uint32_t)8);
    pVlanUcastAddrCfg->macAddress[5]        =   (Uint8)CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7, (uint32_t)0);
    pVlanUcastAddrCfg->vlanId               =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27, (uint32_t)16);
    pVlanUcastAddrCfg->ucastType            =   (CSL_CPSW_ALE_UCASTTYPE) CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31, (uint32_t)30);
    pVlanUcastAddrCfg->secureEnable         =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)0, (uint32_t)0);
    pVlanUcastAddrCfg->blockEnable          =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1, (uint32_t)1U);
    pVlanUcastAddrCfg->portNumber           =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5, (uint32_t)2);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleVlanUnicastAddrEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      VLAN unicast address configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pVlanUcastAddrCfg       ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_VLANUNICASTADDR_ENTRY  vlanUcastAddrCfg;

        index   =   0;
        vlanUcastAddrCfg.macAddress [0] = 0x00;
        vlanUcastAddrCfg.macAddress [1] = 0x01;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add VLAN Unicast address entry
            CSL_CPSW_setAleVlanUnicastAddrEntry (index, &vlanUcastAddrCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleVlanUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANUNICASTADDR_ENTRY* pVlanUcastAddrCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleVlanUnicastAddrEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLANUNICASTADDR_ENTRY* pVlanUcastAddrCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the VLAN Unicast address configuration */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)15U, (uint32_t)8U, pVlanUcastAddrCfg->macAddress[0]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)7U, (uint32_t)0U, pVlanUcastAddrCfg->macAddress[1]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31U, (uint32_t)24U, pVlanUcastAddrCfg->macAddress[2]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)23U, (uint32_t)16U, pVlanUcastAddrCfg->macAddress[3]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15U, (uint32_t)8U, pVlanUcastAddrCfg->macAddress[4]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)7U, (uint32_t)0U, pVlanUcastAddrCfg->macAddress[5]);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27U, (uint32_t)16U, pVlanUcastAddrCfg->vlanId);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)30U, pVlanUcastAddrCfg->ucastType);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)0U, (uint32_t)0U, pVlanUcastAddrCfg->secureEnable);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)1U, (uint32_t)1U, pVlanUcastAddrCfg->blockEnable);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)5U, (uint32_t)2U, pVlanUcastAddrCfg->portNumber);

    /* set entry type to address entry */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)29U, (uint32_t)28U, (uint32_t)3U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleVlanEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with VLAN configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pVlanCfg                ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_VLAN_ENTRY             vlanCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_VLAN)
        {
            // ALE entry has a VLAN configuration
            if (CSL_CPSW_getALEPolicerEntryType (index) ==  ALE_POLICER_ENTRYTYPE_VLAN)
            {
                // Read (Inner) VLAN config from hardware
                CSL_CPSW_getAleVlanEntry (index, &vlanCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleVlanEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLAN_ENTRY*            pVlanCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleVlanEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLAN_ENTRY*            pVlanCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the multicast address configuration */
    pVlanCfg->vlanMemList                   =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)2, (uint32_t)0);
    pVlanCfg->unRegMcastFloodMask           =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)10, (uint32_t)8);
    pVlanCfg->regMcastFloodMask             =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)18, (uint32_t)16);
    pVlanCfg->forceUntaggedEgress           =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)26, (uint32_t)24);
    pVlanCfg->vlanId                        =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27, (uint32_t)16);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleVlanEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      VLAN configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pVlanCfg                ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_VLAN_ENTRY             vlanCfg;

        index   =   0;
        vlanCfg.vlanId  = 0x10;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add VLAN entry
            CSL_CPSW_setAleVlanEntry (index, &vlanCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleVlanEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLAN_ENTRY*            pVlanCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleVlanEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_VLAN_ENTRY*            pVlanCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the (Inner) VLAN configuration */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)2U, (uint32_t)0U, pVlanCfg->vlanMemList);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)10U, (uint32_t)8U, pVlanCfg->unRegMcastFloodMask);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)18U, (uint32_t)16U, pVlanCfg->regMcastFloodMask);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)26U, (uint32_t)24U, pVlanCfg->forceUntaggedEgress);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27U, (uint32_t)16U, pVlanCfg->vlanId);

    /* set entry type to VLAN entry */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)29U, (uint32_t)28U, (uint32_t)2U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleOutValnEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with Outer VLAN configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pOutValnCfg             ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD1
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_OUTER_VLAN_ENTRY           outVlanCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_POLICER)
        {
            // ALE entry has a plicer entry
            if (CSL_CPSW_getALEPolicerEntryType (index) ==  ALE_POLICER_ENTRYTYPE_OVLAN)
            {
                // Read outer VALN config from hardware
                CSL_CPSW_getAleOutValnEntry (index, &outVlanCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleOutValnEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUTER_VLAN_ENTRY*      pOutValnCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleOutValnEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUTER_VLAN_ENTRY*      pOutValnCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the outer valn configuration */
    pOutValnCfg->vlanId        =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27, (uint32_t)16);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleOutValnEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      Outer VLAN configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pOutValnCfg             ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_OUTER_VLAN_ENTRY           outVlanCfg;

        index   =   0;
        outVlanCfg.vlanId = 0x0123;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add Outer VLAN entry
            CSL_CPSW_setAleOutValnEntry (index, &outVlanCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleOutValnEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUTER_VLAN_ENTRY*      pOutValnCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleOutValnEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_OUTER_VLAN_ENTRY*      pOutValnCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the Outer VLAN configuration */
    hCpswRegs->ALE.TABLE_WORD0 = 0;
    hCpswRegs->ALE.TABLE_WORD1 = 0;
    hCpswRegs->ALE.TABLE_WORD2 = 0;

    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27U, (uint32_t)16U, pOutValnCfg->vlanId);

    /* set entry type (10) to address entry */
    /* set policer type (010) */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)28U, (uint32_t)0x22U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleEthertypeEntry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with Ethertype configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pEthertypeCfg           ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_ETHERTYPE_ENTRY            ethertypeCfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_POLICER)
        {
            // ALE entry has a plicer entry
            if (CSL_CPSW_getALEPolicerEntryType (index) ==  ALE_POLICER_ENTRYTYPE_ETHERTYPE)
            {
                // Read Ethertype config from hardware
                CSL_CPSW_getAleEthertypeEntry (index, &ethertypeCfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleEthertypeEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_ETHERTYPE_ENTRY*       pEthertypeCfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleEthertypeEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_ETHERTYPE_ENTRY*       pEthertypeCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the Ethertype configuration */
    pEthertypeCfg->ethertype        =   CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleEthertypeEntry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      Ethertype configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pEthertypeCfg           ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_ETHERTYPE_ENTRY            ethertypeCfg;

        index   =   0;
        ethertypeCfg.ethertype = 0x0800;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add Ethertype entry
            CSL_CPSW_setAleEthertypeEntry (index, &ethertypeCfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleEthertypeEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_ETHERTYPE_ENTRY*       pEthertypeCfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleEthertypeEntry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_ETHERTYPE_ENTRY*       pEthertypeCfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Setup the Ethertype configuration */
    hCpswRegs->ALE.TABLE_WORD0 = 0;
    hCpswRegs->ALE.TABLE_WORD1 = 0;
    hCpswRegs->ALE.TABLE_WORD2 = 0;

    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)15U, (uint32_t)0U, pEthertypeCfg->ethertype);

    /* set entry type (10) to address entry */
    /* set policer type (100) */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)28U, (uint32_t)0x02U);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)0U, (uint32_t)0U, (uint32_t)1U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleIPv4Entry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with IPv4 configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pIPv4Cfg                ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_IPv4_ENTRY                 ipv4Cfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_POLICER)
        {
            // ALE entry has a plicer entry
            if (CSL_CPSW_getALEPolicerEntryType (index) ==  ALE_POLICER_ENTRYTYPE_IPV4)
            {
                // Read IPv4 config from hardware
                CSL_CPSW_getAleIPv4Entry (index, &ipv4Cfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleIPv4Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv4_ENTRY*            pIPv4Cfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleIPv4Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv4_ENTRY*            pIPv4Cfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;
    Uint32                                  address;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the IPv4 configuration */
    address = hCpswRegs->ALE.TABLE_WORD0;
    pIPv4Cfg->address[0]          =   (Uint8)CSL_FEXTR (address, (uint32_t)31, (uint32_t)24);
    pIPv4Cfg->address[1]          =   (Uint8)CSL_FEXTR (address, (uint32_t)23, (uint32_t)16);
    pIPv4Cfg->address[2]          =   (Uint8)CSL_FEXTR (address, (uint32_t)15, (uint32_t)8);
    pIPv4Cfg->address[3]          =   (Uint8)CSL_FEXTR (address, (uint32_t)7, (uint32_t)0);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleIPv4Entry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      IPv4 configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pIPv4Cfg                ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_IPv4_ENTRY                 ipv4Cfg;

        index   =   0;
        ipv4Cfg.ethertype = 0x0800;
        ...

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE)
        {
            // ALE entry is free

            // Add IPv4 entry
            CSL_CPSW_setAleIPv4Entry (index, &ipv4Cfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleIPv4Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv4_ENTRY*            pIPv4Cfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleIPv4Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv4_ENTRY*            pIPv4Cfg
)
{
    Uint32                                  aleTblCtrlVal   =   0;
    Uint32                                  address;
    /* Setup the IPv4 configuration */
    address = (((Uint32)(pIPv4Cfg->address[0])) << 24) |
              (((Uint32)(pIPv4Cfg->address[1])) << 16) |
              (((Uint32)(pIPv4Cfg->address[2])) << 8)  |
              (((Uint32)(pIPv4Cfg->address[3])) << 0);


    hCpswRegs->ALE.TABLE_WORD0 = address;
    hCpswRegs->ALE.TABLE_WORD1 = 0;
    hCpswRegs->ALE.TABLE_WORD2 = 0;

    /* set entry type (10) to address entry */
    /* set policer type (110) */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)28U, (uint32_t)0x22U);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)0U, (uint32_t)0U, (uint32_t)1U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAleIPv6Entry
 *
 *   @b Description
 *   @n This function reads the ALE table entry for the index specified and
 *      fills the output parameter structure with Ipv6 configuration
 *      read from the hardware.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index to be read.
        pIPv6Cfg                ALE entry contents read.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=0
 *
 *   @b Reads
 *   @n CPSW_3G_TABLE_WORD0
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_IPv6_ENTRY                 ipv6Cfg;

        index   =   0;

        if (CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_POLICER)
        {
            // ALE entry has a plicer entry
            if (CSL_CPSW_getALEPolicerEntryType (index) ==  ALE_POLICER_ENTRYTYPE_IPV6)
            {
                // Read Ipv6 config from hardware
                CSL_CPSW_getAleIPv6Entry (index, &ipv6Cfg);
            }
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAleIPv6Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv6_ENTRY*            pIPv6Cfg
);/* for misra warnings*/
static inline void CSL_CPSW_getAleIPv6Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv6_ENTRY*            pIPv6Cfg
)
{
    Uint32      aleTblCtrlVal   =   0;
    Uint32      address[4];
    int32_t         i;

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;

    /* Read the IPv6 configuration */
    address[0] = (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27, (uint32_t)0) << 4) +
                 (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31, (uint32_t)28) >> 28);
    address[1] = (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)27, (uint32_t)0) << 4);

    /* Set the index in the ALE table to "read" operation and let
     * the hardware load the ALE table entry corresponding to index
     * specified into the ALE table word registers.
     */
    aleTblCtrlVal  =  CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index+((uint32_t)1U)) |
                      CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (uint32_t)0);

    hCpswRegs->ALE.TABLE_CONTROL =   aleTblCtrlVal;
    address[1] += (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)6, (uint32_t)3) >> 3);
    address[2] =  (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD2, (uint32_t)2, (uint32_t)0) << 29)   +
                  (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31, (uint32_t)31) << 28) +
                  (CSL_FEXTR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)27, (uint32_t)0));
    address[3] = hCpswRegs->ALE.TABLE_WORD0;

    for(i = 0; i < 4; i++)
    {
        pIPv6Cfg->address[4*i]         =   (Uint8)CSL_FEXTR (address[i], (uint32_t)31U, (uint32_t)24);
        pIPv6Cfg->address[4*i+1]       =   (Uint8)CSL_FEXTR (address[i], (uint32_t)23U, (uint32_t)16);
        pIPv6Cfg->address[4*i+2]       =   (Uint8)CSL_FEXTR (address[i], (uint32_t)15U, (uint32_t)8);
        pIPv6Cfg->address[4*i+3]       =   (Uint8)CSL_FEXTR (address[i], (uint32_t)7U, (uint32_t)0);
    }

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAleIPv6Entry
 *
 *   @b Description
 *   @n This function sets up the ALE table entry for the index specified with
 *      IPv6 configuration specified here.
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
        pIPv6Cfg                ALE entry contents to be configured.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0,
 *      CPSW_3G_TABLE_WORD1,
 *      CPSW_3G_TABLE_WORD2
 *
 *   @b Example
 *   @verbatim
        Uint32                                  index;
        CSL_CPSW_ALE_IPv6_ENTRY                 ipv4Cfg;

        index   =   0;
        ipv4Cfg.ethertype = 0x0800;
        ...

        if ((CSL_CPSW_getALEEntryType (index) == ALE_ENTRYTYPE_FREE &&
            (CSL_CPSW_getALEEntryType (index+1) == ALE_ENTRYTYPE_FREE))
        {
            // ALE entry is free

            // Add IPv6 entry
            CSL_CPSW_setAleIPv6Entry (index, &ipv4Cfg);
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAleIPv6Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv6_ENTRY*            pIPv6Cfg
);/* for misra warnings*/
static inline void CSL_CPSW_setAleIPv6Entry
(
    CSL_cpswHandle                      hCpswRegs,
    Uint32                              index,
    CSL_CPSW_ALE_IPv6_ENTRY*            pIPv6Cfg
)
{
    Uint32          aleTblCtrlVal   =   0;
    Uint32          address[4];
    int32_t         i;

    /* Setup the IPv6 configuration */
    for(i = 0; i < 4; i++)
    {
        address[i] = (((Uint32)(pIPv6Cfg->address[4*i]))   << 24) |
                     (((Uint32)(pIPv6Cfg->address[4*i+1])) << 16) |
                     (((Uint32)(pIPv6Cfg->address[4*i+2])) << 8)  |
                     (((Uint32)(pIPv6Cfg->address[4*i+3])) << 0);
    }

    /* Update the first record */
    hCpswRegs->ALE.TABLE_WORD0 = address[1] >> 4;
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD0, (uint32_t)31U, (uint32_t)28U, (address[0] & (uint32_t)0x0FU));
    hCpswRegs->ALE.TABLE_WORD1 = address[0] >> 4;
    hCpswRegs->ALE.TABLE_WORD2 = 0;

    /* set entry type (10) to address entry */
    /* set policer type (xx1) */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)30U, (uint32_t)28U, (uint32_t)0x12U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    /* Update the second record */
    hCpswRegs->ALE.TABLE_WORD0 = address[3];
    hCpswRegs->ALE.TABLE_WORD1 = address[2] & 0x0FFFFFFFFU;
    hCpswRegs->ALE.TABLE_WORD2 = ((address[1] & (uint32_t)0x0FU) << 3) +
                                    (address[2] >> 29);
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)31U, (uint32_t)31U, ((address[2] >> 28) & (uint32_t)0x01U));

    /* set entry type (10) to address entry */
    /* set policer type (xx1) */
    CSL_FINSR (hCpswRegs->ALE.TABLE_WORD1, (uint32_t)30U, (uint32_t)28U, (uint32_t)0x12U);

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index+((Uint32)1)) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;


    return;
}


/** ============================================================================
 *   @n@b CSL_CPSW_clearAleEntry
 *
 *   @b Description
 *   @n This function clears the ALE entry corresponding to the index
 *      specified
 *
 *   @b Arguments
     @verbatim
        index                   ALE table index.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_TABLE_CONTROL_ENTRY_POINTER,
 *      CPSW_3G_TABLE_CONTROL_WRITE_RDZ=1
 *      CPSW_3G_TABLE_WORD0=0,
 *      CPSW_3G_TABLE_WORD1=0,
 *      CPSW_3G_TABLE_WORD2=0
 *
 *   @b Example
 *   @verbatim
        Uint32                              index;

        index   =   0;

        CSL_CPSW_clearAleEntry (index);
     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_clearAleEntry
(
    CSL_cpswHandle               hCpswRegs,
    Uint32                       index
);/* for misra warnings*/
static inline void CSL_CPSW_clearAleEntry
(
    CSL_cpswHandle               hCpswRegs,
    Uint32                       index
)
{
    Uint32                                  aleTblCtrlVal   =   0;

    /* Clear all the ALE words */
    hCpswRegs->ALE.TABLE_WORD0   =   0;
    hCpswRegs->ALE.TABLE_WORD1   =   0;
    hCpswRegs->ALE.TABLE_WORD2   =   0;

    /* Set the index in the ALE table to "write" operation and let
     * the hardware set up the ALE table entry corresponding to index
     * specified.
     */
    aleTblCtrlVal           =   CSL_FMK (CPSW_3G_TABLE_CONTROL_ENTRY_POINTER, index) |
                                CSL_FMK (CPSW_3G_TABLE_CONTROL_WRITE_RDZ, (Uint32) 1);

    hCpswRegs->ALE.TABLE_CONTROL    =   aleTblCtrlVal;

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_getAlePortControlReg
 *
 *   @b Description
 *   @n This function retrieves the contents of ALE Port control register
 *      corresponding to the port number specified.
 *
 *   @b Arguments
     @verbatim
        portNo                  Port number for which the ALE port control register
                                must be read.
        pPortControlInfo        CSL_CPSW_ALE_PORTCONTROL structure that needs to be
                                filled with Port control register info read from
                                the hardware.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_PORT_CONTROL_PORT_STATE,
 *      CPSW_3G_PORT_CONTROL_DROP_UNTAGGED,
 *      CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK,
 *      CPSW_3G_PORT_CONTROL_NO_LEARN,
 *      CPSW_3G_PORT_CONTROL_NO_SA_UPDATE,
 *      CPSW_3G_PORT_CONTROL_DISABLE_AUTH_MODE,
 *      CPSW_3G_PORT_CONTROL_MCAST_LIMIT,
 *      CPSW_3G_PORT_CONTROL_BCAST_LIMIT
 *
 *   @b Example
 *   @verbatim
        Uint32                          index;
        CSL_CPSW_ALE_PORTCONTROL    portControlInfo;

        index   =   0;

        CSL_CPSW_getAlePortControlReg (index, &portControlInfo);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_getAlePortControlReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNo,
    CSL_CPSW_ALE_PORTCONTROL*   pPortControlInfo
);/* for misra warnings*/
static inline void CSL_CPSW_getAlePortControlReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNo,
    CSL_CPSW_ALE_PORTCONTROL*   pPortControlInfo
)
{
    pPortControlInfo->portState             =   (CSL_CPSW_ALE_PORTSTATE) CSL_FEXT (hCpswRegs->ALE.PORT_CONTROL [portNo],
                                                          CPSW_3G_PORT_CONTROL_PORT_STATE);
    pPortControlInfo->dropUntaggedEnable    =   CSL_FEXT (hCpswRegs->ALE.PORT_CONTROL [portNo],
                                                          CPSW_3G_PORT_CONTROL_DROP_UNTAGGED);
    pPortControlInfo->vidIngressCheckEnable =   CSL_FEXT (hCpswRegs->ALE.PORT_CONTROL [portNo],
                                                          CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK);
    pPortControlInfo->noLearnModeEnable     =   CSL_FEXT (hCpswRegs->ALE.PORT_CONTROL [portNo],
                                                          CPSW_3G_PORT_CONTROL_NO_LEARN);
    pPortControlInfo->noSaUpdateEnable      =   CSL_FEXT (hCpswRegs->ALE.PORT_CONTROL [portNo],
                                                          CPSW_3G_PORT_CONTROL_NO_SA_UPDATE);
    pPortControlInfo->mcastLimit            =   CSL_FEXT (hCpswRegs->ALE.PORT_CONTROL [portNo],
                                                          CPSW_3G_PORT_CONTROL_MCAST_LIMIT);
    pPortControlInfo->bcastLimit            =   CSL_FEXT (hCpswRegs->ALE.PORT_CONTROL [portNo],
                                                          CPSW_3G_PORT_CONTROL_BCAST_LIMIT);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_setAlePortControlReg
 *
 *   @b Description
 *   @n This function sets up the contents of ALE Port control register
 *      corresponding to the port number specified.
 *
 *   @b Arguments
     @verbatim
        portNo                  Port number for which the ALE port control register
                                must be configured.
        pPortControlInfo        CSL_CPSW_ALE_PORTCONTROL structure that contains
                                port control register settings to be written.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_PORT_CONTROL_PORT_STATE,
 *      CPSW_3G_PORT_CONTROL_DROP_UNTAGGED,
 *      CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK,
 *      CPSW_3G_PORT_CONTROL_NO_LEARN,
 *      CPSW_3G_PORT_CONTROL_NO_SA_UPDATE,
 *      CPSW_3G_PORT_CONTROL_DISABLE_AUTH_MODE,
 *      CPSW_3G_PORT_CONTROL_MCAST_LIMIT,
 *      CPSW_3G_PORT_CONTROL_BCAST_LIMIT
 *
 *   @b Example
 *   @verbatim
        Uint32                          index;
        CSL_CPSW_ALE_PORTCONTROL    portControlInfo;

        index   =   0;
        portControlInfo.portState   =   ALE_PORTSTATE_FORWARD |
                                        ALE_PORTSTATE_LEARN;

        CSL_CPSW_setAlePortControlReg (index, &portControlInfo);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_setAlePortControlReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNo,
    CSL_CPSW_ALE_PORTCONTROL*   pPortControlInfo
);/* for misra warnings*/
static inline void CSL_CPSW_setAlePortControlReg
(
    CSL_cpswHandle              hCpswRegs,
    Uint32                      portNo,
    CSL_CPSW_ALE_PORTCONTROL*   pPortControlInfo
)
{
    CSL_FINS (hCpswRegs->ALE.PORT_CONTROL [portNo], CPSW_3G_PORT_CONTROL_PORT_STATE,
              pPortControlInfo->portState);
    CSL_FINS (hCpswRegs->ALE.PORT_CONTROL [portNo], CPSW_3G_PORT_CONTROL_DROP_UNTAGGED,
              pPortControlInfo->dropUntaggedEnable);
    CSL_FINS (hCpswRegs->ALE.PORT_CONTROL [portNo], CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK,
              pPortControlInfo->vidIngressCheckEnable);
    CSL_FINS (hCpswRegs->ALE.PORT_CONTROL [portNo], CPSW_3G_PORT_CONTROL_NO_LEARN,
              pPortControlInfo->noLearnModeEnable);
    CSL_FINS (hCpswRegs->ALE.PORT_CONTROL [portNo], CPSW_3G_PORT_CONTROL_NO_SA_UPDATE,
              pPortControlInfo->noSaUpdateEnable);
    CSL_FINS (hCpswRegs->ALE.PORT_CONTROL [portNo], CPSW_3G_PORT_CONTROL_MCAST_LIMIT,
              pPortControlInfo->mcastLimit);
    CSL_FINS (hCpswRegs->ALE.PORT_CONTROL [portNo], CPSW_3G_PORT_CONTROL_BCAST_LIMIT,
              pPortControlInfo->bcastLimit);

    return;
}

/** ============================================================================
 *   @n@b CSL_CPSW_isCpdmaResetDone
 *
 *   @b Description
 *   @n This function retrieves the contents of the CPSW Softreset register.
 *
 *   @b Arguments
     @verbatim
        pSoft                   Soft reset bit read from the hardware.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPDMA_SOFT_RESET_SOFT_RESET
 *
 *   @b Example
 *   @verbatim
        Uint32  softResetStatus;

        softResetStatus = CSL_CPSW_isCpdmaResetDone ();

	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isCpdmaResetDone
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isCpdmaResetDone
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    Uint32 ret_val = 0U;
    if (CSL_FEXT (hCpdmaRegs->SOFT_RESET, CPDMA_SOFT_RESET_SOFT_RESET) == 0)
    {
        ret_val = (Uint32)TRUE;
    }
    else
    {
        ret_val = (Uint32)FALSE;
    }
    return ret_val;
}

/** ============================================================================
 *   @n@b CSL_CPSW_reset
 *
 *   @b Description
 *   @n This function sets up the contents of the CPSW Soft Reset register.
 *
 *   <b> Arguments </b>
 *	 @n	 None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SOFT_RESET_SOFT_RESET
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_reset ();

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_resetCpdma
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_resetCpdma
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    CSL_FINS (hCpdmaRegs->SOFT_RESET, CPDMA_SOFT_RESET_SOFT_RESET, (uint32_t)1U);

    return;
}

/**
 * \brief   Enables the TXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be enabled
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_enableCpdmaTxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
);/* for misra warnings*/
static inline void CSL_CPSW_enableCpdmaTxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
)
{
    CSL_FINSR (hCpdmaRegs->INTERRUPT.TX_INTMASK_SET, channel, channel, (uint32_t)1U);
}

/**
 * \brief   Enables the RXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be enabled
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_enableCpdmaRxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
);/* for misra warnings*/
static inline void CSL_CPSW_enableCpdmaRxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
)
{
    CSL_FINSR (hCpdmaRegs->INTERRUPT.RX_INTMASK_SET, channel, channel, (uint32_t)1U);
}

/**
 * \brief   Disables the TXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be disabled
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_disableCpdmaTxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
);/* for misra warnings*/
static inline void CSL_CPSW_disableCpdmaTxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
)
{
    CSL_FINSR (hCpdmaRegs->INTERRUPT.TX_INTMASK_CLEAR, channel, channel, (uint32_t)1U);
}

/**
 * \brief   Disables the RXPULSE Interrupt Generation.
 *
 * \param   baseAddr      Base address of the CPDMA Module registers.
 * \param   channel       Channel number for which interrupt to be disabled
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_disableCpdmaRxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
);/* for misra warnings*/
static inline void CSL_CPSW_disableCpdmaRxInt
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32 channel
)
{
    CSL_FINSR (hCpdmaRegs->INTERRUPT.RX_INTMASK_CLEAR, channel, channel, (uint32_t)1U);
}

/**
 * \brief   API to enable the transmit in the TX Control Register.
 *          After the transmit is enabled, any write to TXHDP of
 *          a channel will start transmission
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_enableCpdmaTx
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableCpdmaTx
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    CSL_FINS (hCpdmaRegs->TX_CONTROL, CPDMA_TX_CONTROL_TX_EN, (uint32_t)1U);
}

/**
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
static inline void CSL_CPSW_enableCpdmaRx
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableCpdmaRx
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    CSL_FINS (hCpdmaRegs->RX_CONTROL, CPDMA_RX_CONTROL_RX_EN, (uint32_t)1U);
}

/**
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
static inline void CSL_CPSW_setCpdmaTxHdrDescPtr
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    descHdr,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaTxHdrDescPtr
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    descHdr,
    Uint32                    channel
)
{
    hCpdmaRegs->SRAM.TX_HDP[channel] = descHdr;
}

/**
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
static inline void CSL_CPSW_setCpdmaRxHdrDescPtr
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    descHdr,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaRxHdrDescPtr
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    descHdr,
    Uint32                    channel
)
{
    hCpdmaRegs->SRAM.RX_HDP[channel] = descHdr;
}

/**
 * \brief   Writes the DMA End Of Interrupt Vector.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   eoiFlag       Type of interrupt to acknowledge to the CPDMA
 *            'eoiFlag' can take the following values \n
 *                CPSW_EOI_TX_PULSE - TX Pulse Interrupt \n
 *                CPSW_EOI_RX_PULSE - RX Pulse Interrupt \n
 *                CPSW_EOI_RX_THRESH_PULSE - RX Pulse Threshold Interrupt \n
 *                CPSW_EOI_MISC_PULSE - Misc Interrupt \n
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_setCpdmaTxEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaTxEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    /* Acknowledge the CPDMA */
    hCpdmaRegs->INTERRUPT.DMA_EOI_VECTOR = 0x02;
}

/**
 * \brief   Writes the DMA End Of Interrupt Vector.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   eoiFlag       Type of interrupt to acknowledge to the CPDMA
 *            'eoiFlag' can take the following values \n
 *                CPSW_EOI_TX_PULSE - TX Pulse Interrupt \n
 *                CPSW_EOI_RX_PULSE - RX Pulse Interrupt \n
 *                CPSW_EOI_RX_THRESH_PULSE - RX Pulse Threshold Interrupt \n
 *                CPSW_EOI_MISC_PULSE - Misc Interrupt \n
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_setCpdmaRxEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaRxEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    /* Acknowledge the CPDMA */
    hCpdmaRegs->INTERRUPT.DMA_EOI_VECTOR = 0x01;
}

/**
 * \brief   Writes the DMA End Of Interrupt Vector.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   eoiFlag       Type of interrupt to acknowledge to the CPDMA
 *            'eoiFlag' can take the following values \n
 *                CPSW_EOI_TX_PULSE - TX Pulse Interrupt \n
 *                CPSW_EOI_RX_PULSE - RX Pulse Interrupt \n
 *                CPSW_EOI_RX_THRESH_PULSE - RX Pulse Threshold Interrupt \n
 *                CPSW_EOI_MISC_PULSE - Misc Interrupt \n
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_setCpdmaRxThresholdEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaRxThresholdEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    /* Acknowledge the CPDMA */
    hCpdmaRegs->INTERRUPT.DMA_EOI_VECTOR = 0x00;
}

/**
 * \brief   Writes the DMA End Of Interrupt Vector.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   eoiFlag       Type of interrupt to acknowledge to the CPDMA
 *            'eoiFlag' can take the following values \n
 *                CPSW_EOI_TX_PULSE - TX Pulse Interrupt \n
 *                CPSW_EOI_RX_PULSE - RX Pulse Interrupt \n
 *                CPSW_EOI_RX_THRESH_PULSE - RX Pulse Threshold Interrupt \n
 *                CPSW_EOI_MISC_PULSE - Misc Interrupt \n
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_setCpdmaMiscEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaMiscEndOfIntVector
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    /* Acknowledge the CPDMA */
    hCpdmaRegs->INTERRUPT.DMA_EOI_VECTOR = 0x03;
}

/**
 * \brief   Writes the the TX Completion Pointer for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   comPtr        Completion Pointer Value to be written
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_setCpdmaTxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                    comPtr
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaTxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                    comPtr
)
{
        hCpdmaRegs->SRAM.TX_CP[channel] = comPtr;
}

/**
 * \brief   Writes the the RX Completion Pointer for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   comPtr        Completion Pointer Value to be written
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_setCpdmaRxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                    comPtr
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaRxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                    comPtr
)
{
        hCpdmaRegs->SRAM.RX_CP[channel] = comPtr;
}

/**
 * \brief   Writes the the TX Completion Pointer for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   comPtr        Completion Pointer Value to be written
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_getCpdmaTxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                   *comPtr
);/* for misra warnings*/
static inline void CSL_CPSW_getCpdmaTxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                   *comPtr
)
{
    *comPtr = hCpdmaRegs->SRAM.TX_CP[channel];
}

/**
 * \brief   Writes the the RX Completion Pointer for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   comPtr        Completion Pointer Value to be written
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_getCpdmaRxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                   *comPtr
);/* for misra warnings*/
static inline void CSL_CPSW_getCpdmaRxCp
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                   *comPtr
)
{
    *comPtr = hCpdmaRegs->SRAM.RX_CP[channel];
}

/**
 * \brief   Set the free buffers for a specific channel
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   channel       Channel Number.
 * \param   nBuf          Number of free buffers
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_setCpdmaNumFreeBuf
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                    nBuf
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaNumFreeBuf
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    channel,
    Uint32                    nBuf
)
{
    hCpdmaRegs->INTERRUPT.RX_FREEBUFFER[channel] = nBuf;
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaStatus
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaStatus
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (hCpdmaRegs->DMASTATUS);
}

/**
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
static inline void CSL_CPSW_configCpdma
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    cfg
);/* for misra warnings*/
static inline void CSL_CPSW_configCpdma
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    cfg
)
{
    hCpdmaRegs->DMACONTROL = cfg;
}

/**
 * \brief   Enable the command idle mode for CPDMA. When this API is called, the
 *          CPSW stops all the reception and transmission. However, if receiving
 *          the current frame will be received completely before going to the idle
 *          state. Also, while transmitting, the contents in the fifo will be sent
 *          fully.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_enableCpdmaIdle
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_enableCpdmaIdle
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    CSL_FINS (hCpdmaRegs->DMACONTROL, CPDMA_DMACONTROL_CMD_IDLE, (uint32_t)1U);
}

/** ============================================================================
 *   @n@b CSL_CPSW_isSoftIdle
 *
 *   @b Description
 *   @n This function indicates if the CPSW is at Software Idle mode where
 *      no packets will be started to be unloaded from ports.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *	 @n	 TRUE                   Software Idle mode enabled.
 *	 @n  FALSE                  Software Idle mode disabled.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_SOFT_IDLE_SOFT_IDLE
 *
 *   @b Example
 *   @verbatim
        if (CSL_CPSW_isSoftIdle () == TRUE)
        {
            // Software Idle mode enabled
        }
        else
        {
            // Software Idle mode disabled
        }
	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isCpdmaIdle
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isCpdmaIdle
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return CSL_FEXT (hCpdmaRegs->DMASTATUS, CPDMA_DMASTATUS_IDLE);
}

/**
 * \brief   Disable the command idle mode for CPDMA.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers
 *
 * \return  None
 *
 **/
static inline void CSL_CPSW_disableCpdmaCmdIdle
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline void CSL_CPSW_disableCpdmaCmdIdle
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    CSL_FINS (hCpdmaRegs->DMACONTROL, CPDMA_DMACONTROL_CMD_IDLE, (uint32_t)0);
}

/**
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
static inline void CSL_CPSW_setCpdmaRxBufOffset
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    bufOff
);/* for misra warnings*/
static inline void CSL_CPSW_setCpdmaRxBufOffset
(
    CSL_cpdmaHandle           hCpdmaRegs,
    Uint32                    bufOff
)
{
    hCpdmaRegs->RX_BUFFER_OFFSET = bufOff;
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaTxIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaTxIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (CSL_FEXT(hCpdmaRegs->INTERRUPT.TX_INTSTAT_RAW, CPDMA_TX_INTSTAT_RAW_TX_PEND));
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaTxIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaTxIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (CSL_FEXT(hCpdmaRegs->INTERRUPT.TX_INTSTAT_MASKED, CPDMA_TX_INTSTAT_MASKED_TX_PEND));
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaRxIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaRxIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (CSL_FEXT(hCpdmaRegs->INTERRUPT.RX_INTSTAT_RAW, CPDMA_RX_INTSTAT_RAW_RX_PEND));
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaRxIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaRxIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (CSL_FEXT(hCpdmaRegs->INTERRUPT.RX_INTSTAT_MASKED, CPDMA_RX_INTSTAT_MASKED_RX_PEND));
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaRxThreshIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaRxThreshIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (CSL_FEXT(hCpdmaRegs->INTERRUPT.RX_INTSTAT_RAW, CPDMA_RX_INTSTAT_RAW_RX_THRESH_PEND));
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaRxThreshIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaRxThreshIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (CSL_FEXT(hCpdmaRegs->INTERRUPT.RX_INTSTAT_MASKED, CPDMA_RX_INTSTAT_MASKED_RX_THRESH_PEND));
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaDmaIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaDmaIntStatRaw
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (hCpdmaRegs->INTERRUPT.DMA_INTSTAT_RAW);
}

/**
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
static inline Uint32 CSL_CPSW_getCpdmaDmaIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getCpdmaDmaIntStatMasked
(
    CSL_cpdmaHandle           hCpdmaRegs
)
{
    return (hCpdmaRegs->INTERRUPT.RX_INTSTAT_MASKED);
}

/** ============================================================================
 *   @n@b CSL_CPSW_isResetDone
 *
 *   @b Description
 *   @n This function retrieves the contents of the CPSW Softreset register.
 *
 *   @b Arguments
     @verbatim
        pSoft                   Soft reset bit read from the hardware.
 *	 @endverbatim
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CPSW_3G_SOFT_RESET_SOFT_RESET
 *
 *   @b Example
 *   @verbatim
        Uint32  softResetStatus;

        softResetStatus = CSL_CPSW_isResetDone ();

	 @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_CPSW_isWrResetDone
(
    CSL_wrHandle              hWrRegs
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_isWrResetDone
(
    CSL_wrHandle              hWrRegs
)
{
    Uint32 ret_val = 0U;
    if (CSL_FEXT (hWrRegs->SOFT_RESET, WR_SOFT_RESET_SOFT_RESET) == 0)
    {
        ret_val = (Uint32)TRUE;
    }
    else
    {
        ret_val = (Uint32)FALSE;
    }
    return ret_val;
}

/** ============================================================================
 *   @n@b CSL_CPSW_reset
 *
 *   @b Description
 *   @n This function sets up the contents of the CPSW Soft Reset register.
 *
 *   <b> Arguments </b>
 *	 @n	 None
 *
 *   <b> Return Value </b>
 *	 @n	 None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CPSW_3G_SOFT_RESET_SOFT_RESET
 *
 *   @b Example
 *   @verbatim

        CSL_CPSW_reset ();

	 @endverbatim
 * =============================================================================
 */
static inline void CSL_CPSW_resetWr
(
    CSL_wrHandle              hWrRegs
);/* for misra warnings*/
static inline void CSL_CPSW_resetWr
(
    CSL_wrHandle              hWrRegs
)
{
    CSL_FINS (hWrRegs->SOFT_RESET, WR_SOFT_RESET_SOFT_RESET, (uint32_t)1U);

    return;
}

/**
 * \brief   Resets the Control Register of CPSW Wrapper module
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 *
 * \return  None
 **/
static inline void CSL_CPSW_resetWrControlReg
(
    CSL_wrHandle              hWrRegs
);/* for misra warnings*/
static inline void CSL_CPSW_resetWrControlReg
(
    CSL_wrHandle              hWrRegs
)
{
    /* Reset the CPSW Wrapper control Register */
    CSL_FINS (hWrRegs->CONTROL, WR_CONTROL_MMR_IDLEMODE, (uint32_t)1U);
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_enableWrRxThresholdInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_enableWrRxThresholdInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    CSL_FINSR (hWrRegs->CORE_INT_EN[core].RX_THRESH_EN, channel, channel, (uint32_t)1U);
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_enableWrRxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_enableWrRxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    CSL_FINSR (hWrRegs->CORE_INT_EN[core].RX_EN, channel, channel, (uint32_t)1U);
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_enableWrTxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_enableWrTxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    CSL_FINSR (hWrRegs->CORE_INT_EN[core].TX_EN, channel, channel, (uint32_t)1U);
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_enableWrMiscInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    miscIntrMask
);/* for misra warnings*/
static inline void CSL_CPSW_enableWrMiscInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    miscIntrMask
)
{
    hWrRegs->CORE_INT_EN[core].MISC_EN |= miscIntrMask;
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_disableWrRxThresholdInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_disableWrRxThresholdInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    CSL_FINSR (hWrRegs->CORE_INT_EN[core].RX_THRESH_EN, channel, channel, (uint32_t)0);
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_disableWrRxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_disableWrRxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    CSL_FINSR (hWrRegs->CORE_INT_EN[core].RX_EN, channel, channel, (uint32_t)0);
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_disableWrTxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline void CSL_CPSW_disableWrTxInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    CSL_FINSR (hWrRegs->CORE_INT_EN[core].TX_EN, channel, channel, (uint32_t)0);
}

/**
 * \brief   Enables an interrupt for the specified core.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt to be enabled
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  None
 **/
static inline void CSL_CPSW_disableWrMiscInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    miscIntrMask
);/* for misra warnings*/
static inline void CSL_CPSW_disableWrMiscInt
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    miscIntrMask
)
{
    hWrRegs->CORE_INT_EN[core].MISC_EN &= ~miscIntrMask;
}

/**
 * \brief   Returns the interrupt status of the core for the specified
 *          channel
 *
 * \param   baseAddr    Base address of thei CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt status to be read
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  same as intFlag if the status is set
 *          '0' if the status is cleared
 **/
static inline Uint32 CSL_CPSW_getWrRxThresholdIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getWrRxThresholdIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    return (CSL_FEXTR (hWrRegs->CORE_INT_STAT[core].RX_THRESH_STAT, channel, channel + (Uint32)1U));
}

/**
 * \brief   Returns the interrupt status of the core for the specified
 *          channel
 *
 * \param   baseAddr    Base address of thei CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt status to be read
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  same as intFlag if the status is set
 *          '0' if the status is cleared
 **/
static inline Uint32 CSL_CPSW_getWrRxIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getWrRxIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    return (CSL_FEXTR (hWrRegs->CORE_INT_STAT[core].RX_STAT, channel, channel + (Uint32)1U));
}

/**
 * \brief   Returns the interrupt status of the core for the specified
 *          channel
 *
 * \param   baseAddr    Base address of thei CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt status to be read
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  same as intFlag if the status is set
 *          '0' if the status is cleared
 **/
static inline Uint32 CSL_CPSW_getWrTxIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getWrTxIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    return (CSL_FEXTR (hWrRegs->CORE_INT_STAT[core].TX_STAT, channel, channel + (Uint32)1U));
}

/**
 * \brief   Returns the interrupt status of the core for the specified
 *          channel
 *
 * \param   baseAddr    Base address of thei CPSW Wrapper Module
 * \param   core        Core number
 * \param   channel     Channel number
 * \param   intFlag     Interrupt status to be read
 *    'intFlag' can take one of the below values. \n
 *          CPSW_CORE_INT_RX_THRESH - RX threshold interrupt \n
 *          CPSW_CORE_INT_RX_PULSE - RX pulse interrupt \n
 *          CPSW_CORE_INT_TX_PULSE - TX pulse interrupt \n
 *          CPSW_CORE_INT_MISC - Miscellaneous interrupt
 *
 * \return  same as intFlag if the status is set
 *          '0' if the status is cleared
 **/
static inline Uint32 CSL_CPSW_getWrMiscIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
);/* for misra warnings*/
static inline Uint32 CSL_CPSW_getWrMiscIntStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    core,
    Uint32                    channel
)
{
    return (CSL_FEXTR (hWrRegs->CORE_INT_STAT[core].MISC_STAT, channel, channel + (Uint32)1U));
}

/**
 * \brief   Returns the RGMII status requested.
 *
 * \param   baseAddr    Base address of the CPSW Wrapper Module
 * \param   statFlag    Status to be checked
 *    'statFlag' can take a combination of the below values. \n
 *        CPSW_RGMII2_DUPLEX - Duplex of RGMII2 \n
 *        CPSW_RGMII2_SPEED - Speed of RGMII2 \n
 *        CPSW_RGMII2_LINK_STAT - Link Status of RGMII2 \n
 *        CPSW_RGMII1_DUPLEX - Duplex of RGMII1 \n
 *        CPSW_RGMII1_SPEED - Speed of RGMII1 \n
 *        CPSW_RGMII1_LINK_STAT - Link Status of RGMII1 \n
 *
 *    The returned value can be compared agains the below values \n
 *        CPSW_RGMII2_DUPLEX_FULL - RGMII2 full duplex \n
 *        CPSW_RGMII2_DUPLEX_HALF - RGMII2 half duplex \n
 *        CPSW_RGMII2_SPEED_10M - Speed is 10 Mbps \n
 *        CPSW_RGMII2_SPEED_100M - Speed is 100 Mbps \n
 *        CPSW_RGMII2_SPEED_1000M - Speed is 1000 Mbps \n
 *        CPSW_RGMII2_LINK_UP - RGMII2 link is up\n
 *        CPSW_RGMII2_LINK_DOWN - RGMII2 link is down \n
 *        CPSW_RGMII1_DUPLEX_FULL - RGMII1 full duplex \n
 *        CPSW_RGMII1_DUPLEX_HALF - RGMII1 half duplex \n
 *        CPSW_RGMII1_SPEED_10M - Speed is 10 Mbps \n
 *        CPSW_RGMII1_SPEED_100M - Speed is 100 Mbps \n
 *        CPSW_RGMII1_SPEED_1000M - Speed is 1000 Mbps \n
 *        CPSW_RGMII1_LINK_UP - RGMII1 link is up\n
 *        CPSW_RGMII1_LINK_DOWN - RGMII1 link is down \n
 *
 * \return  Status of RGMII. Return value can be compared agains the same
 *          statFlag passed.
 **/
static inline void CSL_CPSW_getWrRgmiiStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    portNum,
    CSL_CPSW_WR_RGMII_STATUS *rgmiiStatus
);/* for misra warnings*/
static inline void CSL_CPSW_getWrRgmiiStatus
(
    CSL_wrHandle              hWrRegs,
    Uint32                    portNum,
    CSL_CPSW_WR_RGMII_STATUS *rgmiiStatus
)
{
    if ((Uint32)0U != portNum)
    {
        rgmiiStatus->duplex = CSL_FEXTR (hWrRegs->RGMII_CTL, ((portNum - ((Uint32)1U)) * ((Uint32)4U)), ((portNum - ((Uint32)1U)) * ((Uint32)4U)));
        rgmiiStatus->speed = CSL_FEXTR (hWrRegs->RGMII_CTL, ((portNum - ((Uint32)1U)) * ((Uint32)4U) + ((Uint32)2U)), ((portNum - ((Uint32)1U)) * ((Uint32)4U) + ((Uint32)1U)));
        rgmiiStatus->linkStatus = CSL_FEXTR (hWrRegs->RGMII_CTL, ((portNum - ((Uint32)1U)) * ((Uint32)4U) + ((Uint32)4U)), ((portNum - ((Uint32)1U)) * ((Uint32)4U) + ((Uint32)3U)));
    }
}

#ifdef __cplusplus
}
#endif

#endif

/**
@}
*/
