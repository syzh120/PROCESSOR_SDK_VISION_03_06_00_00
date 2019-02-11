/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_PCIE PCIe
 *
 *  @{
 */
/**
 *  \file     pcie.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of PCIe.
 *            This also contains some related macros.
 */

#ifndef PCIE_H_
#define PCIE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_pcie.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  Macro containing mask of all the main interrupts.
 *         This macro can be passed to interrupt control API's to enable or
 *         disable all the main interrupts at a time.
 */
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ALL              \
    (PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_MASK |      \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_MASK |    \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_MASK | \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_MASK |      \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_MASK |      \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_MASK |     \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_MASK | \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_MASK |   \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_MASK |       \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_MASK | \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_MASK |  \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_MASK |  \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_MASK)

/**
 * \brief  Macro containing mask of all the MSI interrupts.
 *         This macro can be passed to MSI interrupt control API's to enable or
 *         disable all the MSI interrupts at a time.
 */
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_ALL      \
    (PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_MASK | \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_MASK | \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_MASK | \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_MASK | \
     PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_MASK)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to select the PCIe Device type.
 */
typedef enum pcieDeviceType
{
    PCIE_DEVICE_TYPE_EP = PCIECTRL_TI_CONF_DEVICE_TYPE_EP,
    /**< Configure device as End point */
    PCIE_DEVICE_TYPE_LEGACY_EP = PCIECTRL_TI_CONF_DEVICE_TYPE_LEG_EP,
    /**< Configure device as Legacy End point */
    PCIE_DEVICE_TYPE_RC = PCIECTRL_TI_CONF_DEVICE_TYPE_RC
                          /**< Configure device as Root complex */
} pcieDeviceType_t;

/**
 * \brief  This enum is used to select local or remote PCIe configuration.
 */
typedef enum pcieLocation
{
    PCIE_LOCATION_LOCAL = 0U,
    /**< Select local PCIe configuration */
    PCIE_LOCATION_REMOTE
    /**< Select remote PCIe configuration */
} pcieLocation_t;

/**
 * \brief  Enum to set maximum PCIe Link speed(2.5Gbps or 5Gbps).
 *
 */
typedef enum pcieLinkSpeed
{
    PCIE_LINK_SPEED_GEN1 = PCIECTRL_RC_DBICS_LNK_CAP_MAX_LINK_SPEEDS_GEN1,
    /**< Configure device to use at max GEN1(2.5 Gbps) speed */
    PCIE_LINK_SPEED_GEN2 = PCIECTRL_RC_DBICS_LNK_CAP_MAX_LINK_SPEEDS_GEN2
                           /**< Configure device to use at max GEN2(5.0 Gbps)
                            * speed */
} pcieLinkSpeed_t;

/**
 * \brief  PCIe Main interrupt flags.
 */
typedef enum pcieMainIntrFlag
{
    PCIE_MAIN_INTR_FLAG_SYSTEM_ERROR =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_MASK,
    /**< System Error interrupt mask*/
    PCIE_MAIN_INTR_FLAG_FATAL_ERROR =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_MASK,
    /**< Fatal Error message received interrupt mask*/
    PCIE_MAIN_INTR_FLAG_NONFATAL_ERROR =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_MASK,
    /**< Non-Fatal Error message received interrupt mask */
    PCIE_MAIN_INTR_FLAG_CORRECTABLE_ERROR =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_MASK,
    /**< Correctable Error message received interrupt mask */
    PCIE_MAIN_INTR_FLAG_AXI_ERROR =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_MASK,
    /**< AXI tag lookup fatal Error interrupt mask */
    PCIE_MAIN_INTR_FLAG_ECRC_ERROR =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_MASK,
    /**< ECRC Error interrupt mask */
    PCIE_MAIN_INTR_FLAG_PME_TURN_OFF =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_MASK,
    /**< Power Management Event Turn-Off message received interrupt mask*/
    PCIE_MAIN_INTR_FLAG_PME_TO_ACK =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_MASK,
    /**< Power Management Event Turn-Off Ack message interrupt mask*/
    PCIE_MAIN_INTR_FLAG_PM_PME =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_MASK,
    /**< PM Power Management Event message received interrupt mask */
    PCIE_MAIN_INTR_FLAG_LINK_REQUEST_RST =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_MASK,
    /**< Link Request Reset interrupt mask */
    PCIE_MAIN_INTR_FLAG_LINK_UP_EVT =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_MASK,
    /**< Link-up state change interrupt mask */
    PCIE_MAIN_INTR_FLAG_CFG_BUS_MASTER_EN_EVT =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_MASK,
    /**< CFG "Bus Master Enable" change interrupt mask */
    PCIE_MAIN_INTR_FLAG_CFG_MSG_SPACE_EN_EVT =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_MASK,
    /**< CFG 'Memory Space Enable' change interrupt mask */
    PCIE_MAIN_INTR_FLAG_ALL = PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ALL
                              /**< Macro to control all the above interrupt
                               * status */
} pcieMainIntrFlag_t;

/**
 * \brief  PCIe MSI(Message signaled interrupt) interrupt flags.
 *
 */
typedef enum pcieMsiIntrFlag
{
    PCIE_MSI_INTR_FLAG_INTA =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_MASK,
    /**< Legacy PCIe message interrupt A interrupt mask */
    PCIE_MSI_INTR_FLAG_INTB =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_MASK,
    /**< Legacy PCIe message interrupt B interrupt mask */
    PCIE_MSI_INTR_FLAG_INTC =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_MASK,
    /**< Legacy PCIe message interrupt C interrupt mask */
    PCIE_MSI_INTR_FLAG_INTD =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_MASK,
    /**< Legacy PCIe message interrupt D interrupt mask */
    PCIE_MSI_INTR_FLAG_MSI =
        PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_MASK,
    /**< MSI(Message Signaled Interrupt) interrupt mask */
    PCIE_MSI_INTR_FLAG_ALL = PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_ALL
                             /**< Macro to control all the above interrupt
                              * status */
} pcieMsiIntrFlag_t;

/**
 * \brief  PCIe LTSSM(link training and status state machine) states.
 *
 */
typedef enum pcieLtssmState
{
    PCIE_LTSSM_STATE_DETECT_QUIET = 0U,
    /**< LTSSM state: Detect quite */
    PCIE_LTSSM_STATE_DETECT_ACT,
    /**< LTSSM state: Detect ACT */
    PCIE_LTSSM_STATE_POLL_ACTIVE,
    /**< LTSSM state: Poll active */
    PCIE_LTSSM_STATE_POLL_COMPLIANCE,
    /**< LTSSM state: Poll compliance */
    PCIE_LTSSM_STATE_POLL_CONFIG,
    /**< LTSSM state: Poll config */
    PCIE_LTSSM_STATE_PRE_DETECT_QUIET,
    /**< LTSSM state: Pre detect quiet */
    PCIE_LTSSM_STATE_DETECT_WAIT,
    /**< LTSSM state: Detect wait */
    PCIE_LTSSM_STATE_CFG_LINKWD_START,
    /**< LTSSM state: Cfg link width start */
    PCIE_LTSSM_STATE_CFG_LINKWD_ACEPT,
    /**< LTSSM state: Cfg link width accept */
    PCIE_LTSSM_STATE_CFG_LANENUM_WAIT,
    /**< LTSSM state: Cfg lane number wait */
    PCIE_LTSSM_STATE_CFG_LANENUM_ACEPT,
    /**< LTSSM state: Cfg lane number accept */
    PCIE_LTSSM_STATE_CFG_COMPLETE,
    /**< LTSSM state: Cfg complete */
    PCIE_LTSSM_STATE_CFG_IDLE,
    /**< LTSSM state: Cfg idle */
    PCIE_LTSSM_STATE_RCVRY_LOCK,
    /**< LTSSM state: Recovery lock */
    PCIE_LTSSM_STATE_RCVRY_SPEED,
    /**< LTSSM state: Recovery  speed */
    PCIE_LTSSM_STATE_RCVRY_RCVRCFG,
    /**< LTSSM state: Recovery recover cfg */
    PCIE_LTSSM_STATE_RCVRY_IDLE,
    /**< LTSSM state: Recovery idle */
    PCIE_LTSSM_STATE_L0,
    /**< LTSSM state: L0 */
    PCIE_LTSSM_STATE_L0S,
    /**< LTSSM state: L0S */
    PCIE_LTSSM_STATE_L123_SEND_EIDLE,
    /**< LTSSM state: L123 send eidle */
    PCIE_LTSSM_STATE_L1_IDLE,
    /**< LTSSM state: L1 idle */
    PCIE_LTSSM_STATE_L2_IDLE,
    /**< LTSSM state: L2 idle */
    PCIE_LTSSM_STATE_L2_WAKE,
    /**< LTSSM state: L2 wake */
    PCIE_LTSSM_STATE_DISABLED_ENTRY,
    /**< LTSSM state: Disabled entry */
    PCIE_LTSSM_STATE_DISABLED_IDLE,
    /**< LTSSM state: Disabled idle */
    PCIE_LTSSM_STATE_DISABLED,
    /**< LTSSM state: disabled */
    PCIE_LTSSM_STATE_LPBK_ENTRY,
    /**< LTSSM state: LPBK entry */
    PCIE_LTSSM_STATE_LPBK_ACTIVE,
    /**< LTSSM state: LPBK active */
    PCIE_LTSSM_STATE_LPBK_EXIT,
    /**< LTSSM state: LPBK exit */
    PCIE_LTSSM_STATE_LPBK_EXIT_TIMEOUT,
    /**< LTSSM state:  LPBK exit time-out */
    PCIE_LTSSM_STATE_HOT_RESET_ENTRY,
    /**< LTSSM state:  Hot reset entry */
    PCIE_LTSSM_STATE_HOTRESET,
    /**< LTSSM state:  Hot reset */
    PCIE_LTSSM_STATE_RCVRY_EQ0,
    /**< LTSSM state:  Recovery EQ0 */
    PCIE_LTSSM_STATE_RCVRY_EQ1,
    /**< LTSSM state:  Recovery EQ1 */
    PCIE_LTSSM_STATE_RCVRY_EQ2,
    /**< LTSSM state:  Recovery EQ2 */
    PCIE_LTSSM_STATE_RCVRY_EQ3
    /**< LTSSM state:  Recovery EQ3 */
} pcieLtssmState_t;

/**
 *  \brief Enum to select whether to generate MSI(Message Signaled interrupt)
 *         by hardware or software method.
 */
typedef enum pcieMsiIntrType
{
    PCIE_MSI_INTR_TYPE_HW = 0U,
    /**< Generate MSI by hardware method*/
    PCIE_MSI_INTR_TYPE_SW
    /**< Generate MSI by software method*/
} pcieMsiIntrType_t;

/**
 *  \brief Enum to select assertion or de-assertion of Legacy interrupt.
 */
typedef enum pcieLegacyIntr
{
    PCIE_LEGACY_INTR_ASSERT = 0U,
    /**< Assert legacy interrupt */
    PCIE_LEGACY_INTR_DEASSERT
    /**< De-assert legacy interrupt */
} pcieLegacyIntr_t;

/**
 * \brief  Enum to select PCIe ATU(Address translation unit) region
 *         direction(Inbound or Outbound).
 *         This enum is used while configuring inbound or outbound region.
 */
typedef enum pcieAtuRegionDir
{
    PCIE_ATU_REGION_DIR_OUTBOUND =
        PCIECTRL_PL_IATU_INDEX_REGION_DIRECTION_OUTBOUND,
    /**< Select PCIe outbound region. */
    PCIE_ATU_REGION_DIR_INBOUND =
        PCIECTRL_PL_IATU_INDEX_REGION_DIRECTION_INBOUND
        /**< Select PCIe inbound region. */
} pcieAtuRegionDir_t;

/**
 * \brief  This enum is used to select PCIe TLP(Transaction layer packet) type
 *         while configuring inbound or outbound region.
 */
typedef enum pcieTlpType
{
    PCIE_TLP_TYPE_MEM = PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_MEM,
    /**< MEM type is selected while doing memory transfer */
    PCIE_TLP_TYPE_IO = PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_IO,
    /**< IO type is selected while doing I/O transfer */
    PCIE_TLP_TYPE_CFG = PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_CFG
                        /**< CFG type is selected while doing configuration
                         * access */
} pcieTlpType_t;

/**
 * \brief  Enum to select address or BAR match mode.
 */
typedef enum pcieAtuRegionMatchMode
{
    PCIE_ATU_REGION_MATCH_MODE_ADDR = PCIECTRL_PL_IATU_REG_CTRL_2_MATCH_MODE_0,
    /**< Inbound packets are filtered by address match mode */
    PCIE_ATU_REGION_MATCH_MODE_BAR = PCIECTRL_PL_IATU_REG_CTRL_2_MATCH_MODE_1
                                     /**< Inbound packets are filtered by BAR
                                      * match mode */
} pcieAtuRegionMatchMode_t;

/**
 *  \brief This enum defines the BAR address size. This parameter
 *         is used to set BAR to operate in either 32 or 64bit.
 */
typedef enum pcieBarAddrSize
{
    PCIE_BAR_ADDR_SIZE_32BIT = PCIECTRL_RC_DBICS_BAR0_AS_32BIT,
    /**< Set BAR size to 32 bit */
    PCIE_BAR_ADDR_SIZE_64BIT = PCIECTRL_RC_DBICS_BAR0_AS_64BIT
                               /**< Set BAR size to 64 bit */
} pcieBarAddrSize_t;

/**
 *  \brief This enum defines the BAR type. This parameter
 *         is used to set BAR type to either MEM or I/O type.
 */
typedef enum pcieBarType
{
    PCIE_BAR_TYPE_MEMORY = PCIECTRL_RC_DBICS_BAR0_SPACE_INDICATOR_MEM,
    /**< BAR type is memory */
    PCIE_BAR_TYPE_IO = PCIECTRL_RC_DBICS_BAR0_SPACE_INDICATOR_IO
                       /**< BAR type is I/O */
} pcieBarType_t;

/**
 *  \brief This Structure defines the PCIe configuration parameters.
 */
typedef struct pcieLocationParams
{
    uint32_t       outboundCfgOffset;
    /**< Address offset for Outbound configuration while doing remote
     * configuration
     */
    pcieLocation_t location;
    /**< PCIe outbound cfg space for remote configuration
     * Values given by enum #pcieLocation_t
     */
} pcieLocationParams_t;

/**
 *  \brief This Structure defines the ATU region parameters
 *
 *  These parameters are used for configuring inbound or outbound
 *  ATU(Address translation unit) region
 */
typedef struct pcieAtuRegionParams
{
    pcieAtuRegionDir_t       regionDir;
    /**< Region direction Inbound or Outbound
     * Values given by enum #pcieAtuRegionDir_t
     */
    pcieTlpType_t            tlpType;
    /**< TLP(transaction layer packet) type
     * Values given by enum #pcieTlpType_t
     */
    uint32_t                 enableRegion;
    /**< Region enable or disable */
    pcieAtuRegionMatchMode_t matchMode;
    /**< Region match mode Address match or BAR match
     * Values given by enum #pcieAtuRegionMatchMode_t
     */
    uint32_t                 barNumber;
    /**< BAR number with which the region is associated
     *   Possible values for EP : 0 to 5 for 32bit and 0 to 2 for 64bit
     *   Possible values for RC : 0 to 1 for 32bit and 0 for 64bit
     */
    uint32_t                 lowerBaseAddr;
    /**< Lower base address : should be 4K aligned
     *   For outbound configuration this contains outbound region offset
     *   For inbound  configuration this contains inbound PCIe start address
     */
    uint32_t                 upperBaseAddr;
    /**< Upper base address
     *   Higher 32 bits in case of 64 bit addressing
     *   Configured to 0 for 32 bit addressing
     */
    uint32_t                 regionWindowSize;
    /**< Region window size
     *   For outbound configuration this contains outbound window size
     *   For inbound  configuration this contains PCIe inbound window size
     */
    uint32_t                 lowerTargetAddr;
    /**< Lower Target address: should be 4K aligned
     *   For outbound configuration this contains outbound PCIe start offset
     *   For inbound  configuration this contains destination address
     */
    uint32_t                 upperTargetAddr;
    /**< Upper target address
     *   Higher 32 bits in case of 64 bit addressing
     *   Configured to 0 for 32 bit addressing
     */
} pcieAtuRegionParams_t;

/**
 *  \brief This structure defines BAR parameters
 *
 *  These parameters are used for configuring BAR window
 */
typedef struct pcieBarParams
{
    uint32_t          lowerBaseAddr;
    /**< BAR lower address */
    uint32_t          upperBaseAddr;
    /**< BAR Upper address used for 64 bit BAR.
     *   Not used for 32 bit BAR*/
    uint32_t          enablePrefetch;
    /**< Enable pre-fetch
     *   Usually this is enabled for memory transactions
     *   and disabled for IO and configuration access*/
    pcieBarAddrSize_t barAddrSize;
    /**< BAR address size 32 or 64 bit
     * Values given by enum #pcieBarAddrSize_t
     */
    pcieBarType_t     barType;
    /**< BAR is memory or IO type
     * Values given by enum #pcieBarType_t
     */
    uint32_t          lowerBarMask;
    /**< BAR mask to configure lower BAR window*/
    uint32_t          upperBarMask;
    /**< BAR mask to configure upper BAR window for 64 bit BAR
     *   Not used for 32 bit BAR */
    uint32_t          enableBar;
    /**< Enable or disable BAR*/
} pcieBarParams_t;

/**
 *  \brief This structure defines MSI(Message signaled interrupt) parameters.
 *
 *  These parameters are used to configure local RC's MSI mailbox or
 *  remote EP's MSI descriptor.
 */
typedef struct pcieMsiMailboxParams
{
    uint32_t lowerAddr;
    /**< MSI mailbox lower address */
    uint32_t upperAddr;
    /**< MSI mailbox upper address */
    uint32_t data;
    /**< MSI interrupt number */
} pcieMsiMailboxParams_t;

/**
 *  \brief This structure defines MSI(Message signaled interrupt) Ctrl params.
 *
 *  These parameters are used to configure local or remote MSI capabilities.
 */
typedef struct pcieMsiCtrlParams
{
    uint32_t enable64Bit;
    /**< Enable 64bit MSI transmission */
    uint32_t enableMsi;
    /**< Enable MSI transmission */
    uint32_t enableMultiMsg;
    /**< Enable multiple MSI transmission */
} pcieMsiCtrlParams_t;

/**
 * \brief  PCIe traffic control parameter structure
 *
 * These parameters are used to control PCIe Traffic.
 * Pass 1 to enable and 0 to disable the control parameter.
 */
typedef struct pcieTrafficCtrlParams
{
    uint32_t enableIoSpace;
    /**< Enable/Disable IO space. */
    uint32_t enableMemSpace;
    /**< Enable/Disable Mem Space */
    uint32_t enableBusMaster;
    /**< Enable/Disable Bus Master */
    uint32_t enableSerr;
    /**< Enable/Disable error report by EP to RC */
    uint32_t enableIntxAssert;
    /**< Enable/Disable assertion of Intx */
} pcieTrafficCtrlParams_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Configures PCIe outbound or inbound region.
 *
 * \param   baseAddr        Base Address of the PCIeSS registers.
 * \param   locationParams  Refer struct #pcieLocationParams_t for details
 * \param   atuRegionIndex  region to be configured
 *                          - Possible values for inbound configuration 0 to 3
 *                          - Possible values for outbound configuration 0 to 15
 * \param   atuRegionParams ATU region parameters.
 *                          Values given by struct #pcieAtuRegionParams_t.
 *
 * \return  None
 * \note    This API will configure 32-bit aligned addresses.
 */
void PCIEAtuRegionConfig(uint32_t                     baseAddr,
                         const pcieLocationParams_t  *locationParams,
                         uint32_t                     atuRegionIndex,
                         const pcieAtuRegionParams_t *atuRegionParams);

/**
 * \brief   Configures   PCIe device type.
 *
 * \param   baseAddr     Base Address of the PCIeSS registers.
 * \param   deviceType   PCIe device type.
 *                       Values given by enum #pcieDeviceType_t
 *
 * \return  None
 *
 * \note    This API should be called before doing other PCIe configuration.
 */
void PCIESetDeviceType(uint32_t baseAddr, pcieDeviceType_t deviceType);

/**
 * \brief   This API returns the PCIe device type.
 *
 * \param   baseAddr      Base Address of the PCIeSS registers.
 *
 * \return  deviceType    PCIe device type. Refer enum pcieDeviceType_t
 *                        for possible return values.
 */
pcieDeviceType_t PCIEGetDeviceType(uint32_t baseAddr);

/**
 * \brief   Configures maximum PCIe link speed and link width.
 *
 * \param   baseAddr      Base Address of the PCIeSS registers.
 * \param   maxLinkSpeed  Max PCIe link speed to be set.
 *                        Values given by enum #pcieLinkSpeed_t
 * \param   maxLinkWidth  PCIe maximum link width(number of lanes).
 *                        possible values: 1 or 2 for PCIeSS1
 *                                         1 for PCIeSS2
 * \return  None
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
void PCIEConfigLink(uint32_t        baseAddr,
                    pcieLinkSpeed_t maxLinkSpeed,
                    uint32_t        maxLinkWidth);

/**
 * \brief   Returns the present PCIe link speed at which the PCIe is working.
 *          This API should be used after link is up.
 *
 * \param   baseAddr      Base Address of the PCIeSS registers.
 *
 * \return  linkSpeed     link speed at which the PCIe is working
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
pcieLinkSpeed_t PCIEGetLinkSpeed(uint32_t baseAddr);

/**
 * \brief     This function enables only specified PCIe interrupts
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 * \param     intrMask   Mask value for the interrupts to be enabled.
 *                       Supported values are given by the enum
 *                       #pcieMainIntrFlag_t.
 *
 * \return    None
 */
void PCIEMainIntrEnable(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief     This function disables only specified PCIe interrupts
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 * \param     intrMask   mask value for the interrupts to be disabled.
 *                       Supported values are given by enum
 *                       #pcieMainIntrFlag_t.
 *
 * \return    None
 */
void PCIEMainIntrDisable(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief     This function gets the status of enabled interrupts
 *            - It returns 32 bit integer with bits specifying whether
 *              an interrupt is enabled or disabled.
 *            - Returned value can be masked with the values in enum
 *              #pcieMainIntrFlag_t to check the required interrupt status
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    status     All the enabled interrupts.
 */
uint32_t PCIEGetMainIntrEnable(uint32_t baseAddr);

/**
 * \brief     This function returns the status of interrupts.
 *            - It specifies whether an interrupt is active or inactive.
 *            - After an interrupt is serviced, the software must set to 0
 *              the corresponding flag in the interrupt status register.
 *            - Returned value can be masked with the values in enum
 *              #pcieMainIntrFlag_t to check the required interrupt status
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    status     all the active interrupt status.
 */
uint32_t PCIEMainIntrStatus(uint32_t baseAddr);

/**
 * \brief     This Function clears the status of specified interrupts.
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 * \param     intrMask   mask value for the interrupts to be cleared.
 *                       - given by enum - pcieMainIntrFlag_t.
 *
 * \return    None
 */
void PCIEMainIntrClear(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief     This function returns the raw status of interrupts.
 *            - Returned value can be masked with the values in enum
 *              #pcieMainIntrFlag_t to check the required interrupt status
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    status     all the raw interrupt status.
 */
uint32_t PCIEMainIntrRawStatus(uint32_t baseAddr);

/**
 * \brief     This function enables only specified PCIe MSI or Legacy
 *            interrupts
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 * \param     intrMask   mask value for the interrupts to be enabled.
 *                       Supported values are given by the enum
 *                       #pcieMsiIntrFlag_t.
 *
 * \return    None
 */
void PCIEMsiIntrEnable(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief     This function disables only specified PCIe MSI or Legacy
 *            interrupts
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 * \param     intrMask   mask value for the interrupts to be disabled.
 *                       Supported values are given by enum
 *                       #pcieMsiIntrFlag_t.
 *
 * \return    None
 */
void PCIEMsiIntrDisable(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief     This function gets the status of enabled PCIe MSI or Legacy
 *            interrupts interrupts
 *            - It returns 32 bit integer with bits specifying whether
 *              an interrupt is enabled or disabled.
 *            - Returned value can be masked with the values in enum
 *              #pcieMsiIntrFlag_t to check the required interrupt status
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    status     All the enabled interrupt status.
 */
uint32_t PCIEGetMsiIntrEnable(uint32_t baseAddr);

/**
 * \brief     This function returns the status of PCIe MSI or Legacy
 *            interrupts.
 *            - It specifies whether an interrupt is active or inactive.
 *            - After an interrupt is serviced, the software must set to 0
 *              the corresponding flag in the interrupt status register.
 *            - Returned value can be masked with the values in enum
 *              #pcieMsiIntrFlag_t to check the required interrupt status
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    status     all the interrupt status.
 */
uint32_t PCIEMsiIntrStatus(uint32_t baseAddr);

/**
 * \brief     This Function clears the status of specified PCIe MSI or
 *            Legacy interrupts.
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 * \param     intrMask   mask value for the interrupts to be cleared.
 *                       - given by enum - #pcieMsiIntrFlag_t.
 *
 * \return    None
 */
void PCIEMsiIntrClear(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief     This function returns the raw status of PCIe MSI or
 *            Legacy interrupts.
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    status     all the raw interrupt status.
 */
uint32_t PCIEMsiIntrRawStatus(uint32_t baseAddr);

/**
 * \brief     This function enables or disables the following local or remote
 *            traffic controls,
 *            MEM space, IO space, BUS master, SERR(System error reporting),
 *            INTX assert disable.
 *
 * \param     baseAddr           Base Address of the PCIeSS registers.
 * \param     locationParams     Structure to select local or remote config.
 *                               Refer struct #pcieLocationParams_t for details.
 * \param     trafficCtrlParams  Structure containing traffic control
 *                               parameters
 *                               Refer struct #pcieTrafficCtrlParams_t
 *                               for details.
 *
 * \return    None
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
void PCIETrafficCtrl(uint32_t                       baseAddr,
                     const pcieLocationParams_t    *locationParams,
                     const pcieTrafficCtrlParams_t *trafficCtrlParams);

/**
 * \brief     This function returns status of local or remote
 *            traffic control,
 *            MEM space, IO space, BUS master, SERR(System error reporting)
 *            and INTX assert disable.
 *
 * \param     baseAddr            Base Address of the PCIeSS registers.
 * \param     locationParams      Structure to select local or remote config
 *                                Refer struct #pcieLocationParams_t for details
 * \param     trafficCtrlParams   Structure containing present PCIe traffic
 *                                status. Refer struct #pcieTrafficCtrlParams_t
 *                                for details
 *
 * \return    None
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
void PCIETrafficStatus(uint32_t                    baseAddr,
                       const pcieLocationParams_t *locationParams,
                       pcieTrafficCtrlParams_t    *trafficCtrlParams);

/**
 * \brief     This function enables link training or disables link
 *
 * \param     baseAddr     Base Address of the PCIeSS registers.
 * \param     ltssmEnable  link control parameter
 *                         Possible values: 1 to enable link training
 *                                          0 to disable link
 *
 * \return    None
 */
void PCIELtssmEnable(uint32_t baseAddr, uint32_t ltssmEnable);

/**
 * \brief     This function returns the LTSSM status
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    LTSSM status. Refer enum PCIELtssmState_t for details
 */
pcieLtssmState_t PCIELtssmStatus(uint32_t baseAddr);

/**
 * \brief     This function configures the BAR
 *
 * \param     baseAddr        Base Address of the PCIeSS registers.
 * \param     locationParams  structure to select local or remote cfg space
 *                            Refer struct #pcieLocationParams_t for details.
 * \param     barNumber       BAR number to be configured
 *                            Possible values for 32 bit BAR for RC are 0 and 1
 *                            Possible values for 32 bit BAR for EP are 0 to  5
 *                            Possible values for 64 bit BAR for RC is 0
 *                            Possible values for 64 bit BAR for EP are 0 to 2
 * \param     barParams       BAR configuration parameters. Refer struct
 *                            #pcieBarParams_t for details
 *
 * \return    None
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
void PCIEBarConfig(uint32_t                    baseAddr,
                   const pcieLocationParams_t *locationParams,
                   uint32_t                    barNumber,
                   const pcieBarParams_t      *barParams);

/**
 * \brief     This function configures RC's MSI mailbox or EP's
 *            MSI descriptor
 *
 * \param     baseAddr          Base Address of the PCIeSS registers.
 * \param     locationParams    structure to select local or remote cfg space
 *                              Refer struct #pcieLocationParams_t for details.
 * \param     msiMailboxParams  mailbox parameters. Refer struct
 *                              #pcieMsiMailboxParams_t for details
 *
 * \return    None
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
void PCIEMsiMailboxConfig(uint32_t                      baseAddr,
                          const pcieLocationParams_t   *locationParams,
                          const pcieMsiMailboxParams_t *msiMailboxParams);

/**
 * \brief     This function configures MSI capabilities remote or locally
 *
 * \param     baseAddr        Base Address of the PCIeSS registers.
 * \param     locationParams  structure to select local or remote cfg space
 *                            Refer struct #pcieLocationParams_t for details.
 * \param     msiCtrlParams   MSI control parameters. Refer struct
 *                            pcieMsiCtrlParams_t for details
 *
 * \return    None
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
void PCIEMsiCtrl(uint32_t                    baseAddr,
                 const pcieLocationParams_t *locationParams,
                 const pcieMsiCtrlParams_t  *msiCtrlParams);

/**
 * \brief     This function enables or disables specified
 *            MSI(Message signaled interrupt).
 *
 * \param     baseAddr      Base Address of the PCIeSS registers.
 * \param     msiIntrNum    MSI interrupt number to be enabled or disabled
 *                          Possible values: 0 to 31
 * \param     msiIntrGroup  MSI interrupt group to be selected
 *                          Possible values: 0 to 7
 * \param     enableMsiIntr enable or disable MSI
 *                          Possible values: 0 to disable MSI
 *                                           1 to enable MSI
 *
 * \return    None
 */
void PCIEMsiIntrCtrl(uint32_t baseAddr,
                     uint32_t msiIntrNum,
                     uint32_t msiIntrGroup,
                     uint32_t enableMsiIntr);

/**
 * \brief     This function returns the active MSI
 *            (Message signaled interrupt )interrupt status
 *
 * \param     baseAddr      Base Address of the PCIeSS registers.
 * \param     msiIntrGroup  MSI interrupt group to be selected
 *
 * \return    Status        Status of all the active MSI interrupts
 */
uint32_t PCIEMsiActiveIntrStatus(uint32_t baseAddr, uint32_t msiIntrGroup);

/**
 * \brief     This function clears the active MSI.
 *
 * \param     baseAddr       Base Address of the PCIeSS registers.
 * \param     msiIntrGroup   MSI interrupt group to be selected
 * \param     intrMask       Interrupt mask containing active interrupts
 *
 * \return    None
 */
void PCIEMsiActiveIntrClear(uint32_t baseAddr,
                            uint32_t msiIntrGroup,
                            uint32_t intrMask);

/**
 * \brief     This function Generate MSI using HW or SW method.
 *
 * \param     baseAddr            Base Address of the PCIeSS registers.
 * \param     msiType             MSI interrupt type. Refer enum
 *                                #pcieMsiIntrType_t for values.
 *                                After MSI generation by hardware method. API
 *                                waits till MSI request is granted.
 * \param     msiOutboundCfgSpace Outbound config space from the MSI has to be
 *                                generated. Used for SW MSI generation.
 *
 * \return    None
 */
void PCIEMsiTransmit(uint32_t          baseAddr,
                     pcieMsiIntrType_t msiType,
                     uint32_t          msiOutboundCfgSpace);

/**
 * \brief     This function returns the PCIe outbound base address
 *            for the PCIe base address passed
 *
 * \param     baseAddr   Base Address of the PCIeSS registers.
 *
 * \return    address    Outbound address for the instance passed
 */
uint32_t PCIEGetOutboundAddr(uint32_t baseAddr);

/**
 * \brief     This function asserts or de-asserts legacy interrupt
 *
 * \param     baseAddr      Base Address of the PCIeSS registers.
 * \param     intrAssert    Assert or de-assert legacy interrupt. Refer
 *                          enum pcieLegacyIntr_t for details
 *
 * \return    None
 */
void PCIELegacyIntrTransmit(uint32_t baseAddr, pcieLegacyIntr_t intrAssert);

/**
 * \brief     This function returns asserts or de-asserts legacy interrupt
 *            status
 *
 * \param     baseAddr      Base Address of the PCIeSS registers.
 * \param     intrAssert    Assert or de-assert legacy interrupt. Refer
 *                          enum #pcieLegacyIntr_t for values
 *
 * \return    status  legacy interrupt assert or de-assert status
 */
uint32_t PCIEGetLegacyIntrStatus(uint32_t baseAddr, pcieLegacyIntr_t intrAssert);

/**
 * \brief     This function requests the PCIe core to switch to new link
 *            speed.
 *
 * \param     baseAddr        Base Address of the PCIeSS registers.
 * \param     newSpeed        New speed to which the link should be switched
 *                            enum #pcieLinkSpeed_t for values
 *
 * \return    None
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
void PCIEChangeLinkSpeed(uint32_t baseAddr, pcieLinkSpeed_t newSpeed);

/**
 * \brief     This function returns the remote or local device and vendor ID.
 *
 * \param     baseAddr        Base Address of the PCIeSS registers.
 * \param     locationParams  structure to select local or remote cfg space
 *                            Refer struct #pcieLocationParams_t for details.
 *
 * \return    deviceVendorId  lower 16 bits contains vendorID
 *                            Upper 16 bits contains DeviceID
 *
 * \note    This API should be called only after setting the PCIe device type.
 */
uint32_t PCIEGetDeviceVendorId(uint32_t                    baseAddr,
                               const pcieLocationParams_t *locationParams);

#ifdef __cplusplus
}
#endif

#endif
 /** @} */
/********************************* End of file ******************************/
