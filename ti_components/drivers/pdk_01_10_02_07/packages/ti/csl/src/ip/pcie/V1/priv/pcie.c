/*
 *  Copyright (C) 2013-2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     pcie.c
 *
 *  \brief    This file contains the device abstraction layer APIs for PCIe
 *            peripheral.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_pcie.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief BAR register offset for 32 bit
 */
#define PCIE_32BIT_BAR_SIZE ((uint32_t)0x04U)

/**
 * \brief BAR register offset for 64 bit
 */
#define PCIE_64BIT_BAR_SIZE ((uint32_t)0x08U)

/**
 * \brief Mask for 32-bit address alignment
 *        Errata ID (i870): PCIe unaligned read access issue
 */
#define PCIE_32BIT_ADDR_ALIGNMENT ((uint32_t)0x3U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void PCIEAtuRegionConfig(uint32_t                     baseAddr,
                         const pcieLocationParams_t  *locationParams,
                         uint32_t                     atuRegionIndex,
                         const pcieAtuRegionParams_t *atuRegionParams)
{
    uint32_t regVal;
    uint32_t cfgAddr;

    if (PCIE_LOCATION_LOCAL == locationParams->location)
    {
        cfgAddr = baseAddr + PCIECTRL_PL_OFFSET;
    }
    else
    {
        if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE +
                      locationParams->outboundCfgOffset +
                      PCIECTRL_PL_OFFSET;
        }
        else
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE +
                      locationParams->outboundCfgOffset +
                      PCIECTRL_PL_OFFSET;
        }
    }

    /* Update ATU index register with new region direction and region index. */
    regVal = HW_RD_REG32(cfgAddr + PCIECTRL_PL_IATU_INDEX);

    HW_SET_FIELD32(regVal, PCIECTRL_PL_IATU_INDEX_REGION, atuRegionIndex);

    HW_SET_FIELD32(
        regVal,
        PCIECTRL_PL_IATU_INDEX_REGION_DIRECTION,
        atuRegionParams->regionDir);

    HW_WR_REG32(cfgAddr + PCIECTRL_PL_IATU_INDEX, regVal);

    /* Set TLP(Transaction Layer packet) type. */
    HW_WR_FIELD32(
        cfgAddr + PCIECTRL_PL_IATU_REG_CTRL_1,
        PCIECTRL_PL_IATU_REG_CTRL_1_TYPE,
        atuRegionParams->tlpType);

    /* Configure ATU control2 register. */
    regVal = HW_RD_REG32(cfgAddr + PCIECTRL_PL_IATU_REG_CTRL_2);

    if (PCIE_ATU_REGION_DIR_INBOUND == atuRegionParams->regionDir)
    {
        /* Enable region. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_PL_IATU_REG_CTRL_2_REGION_ENABLE,
            atuRegionParams->enableRegion);

        /* Set match mode. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_PL_IATU_REG_CTRL_2_MATCH_MODE,
            atuRegionParams->matchMode);

        /* Set BAR number. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER,
            atuRegionParams->barNumber);
    }
    else
    {
        /* Enable region. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_PL_IATU_REG_CTRL_2_REGION_ENABLE,
            atuRegionParams->enableRegion);
    }

    HW_WR_REG32(cfgAddr + PCIECTRL_PL_IATU_REG_CTRL_2, regVal);

    /* Errata ID (i870): PCIe unaligned read access issue */
    /* Configure lower base. */
    HW_WR_REG32(
        cfgAddr + PCIECTRL_PL_IATU_REG_LOWER_BASE,
        (atuRegionParams->lowerBaseAddr & (~PCIE_32BIT_ADDR_ALIGNMENT)));

    /* Configure upper base. */
    HW_WR_REG32(
        cfgAddr + PCIECTRL_PL_IATU_REG_UPPER_BASE,
        atuRegionParams->upperBaseAddr);

    /* Configure window size. */
    HW_WR_REG32(
        cfgAddr + PCIECTRL_PL_IATU_REG_LIMIT,
        (atuRegionParams->lowerBaseAddr +
         atuRegionParams->regionWindowSize));

    /* Errata ID (i870): PCIe unaligned read access issue */
    /* Configure lower target. */
    HW_WR_REG32(
        cfgAddr + PCIECTRL_PL_IATU_REG_LOWER_TARGET,
        (atuRegionParams->lowerTargetAddr & (~PCIE_32BIT_ADDR_ALIGNMENT)));

    /* Configure Upper target. */
    HW_WR_REG32(
        cfgAddr + PCIECTRL_PL_IATU_REG_UPPER_TARGET,
        atuRegionParams->upperTargetAddr);
}

void PCIESetDeviceType(uint32_t baseAddr, pcieDeviceType_t deviceType)
{
    HW_WR_FIELD32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_DEVICE_TYPE,
        PCIECTRL_TI_CONF_DEVICE_TYPE,
        deviceType);
}

pcieDeviceType_t PCIEGetDeviceType(uint32_t baseAddr)
{
    return ((pcieDeviceType_t) (HW_RD_FIELD32(
                                    baseAddr + PCIECTRL_TI_CONF_OFFSET +
                                    PCIECTRL_TI_CONF_DEVICE_TYPE,
                                    PCIECTRL_TI_CONF_DEVICE_TYPE)));
}

void PCIEConfigLink(uint32_t        baseAddr,
                    pcieLinkSpeed_t maxLinkSpeed,
                    uint32_t        maxLinkWidth)
{
    uint32_t cfgAddr;
    uint32_t regVal;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        cfgAddr = baseAddr + PCIECTRL_RC_DBICS_OFFSET +
                  PCIECTRL_RC_DBICS_LNK_CAP;

        /* Read value of LINK CAP register. */
        regVal = HW_RD_REG32(cfgAddr);

        /* Set link speed. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_RC_DBICS_LNK_CAP_MAX_LINK_SPEEDS,
            maxLinkSpeed);

        /* Set link width. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_RC_DBICS_LNK_CAP_MAX_LINK_WIDTH,
            maxLinkWidth);

        /* Updated the value of LINK CAP register. */
        HW_WR_REG32(cfgAddr, regVal);
    }
    else
    {
        cfgAddr = baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                  PCIECTRL_EP_DBICS_LNK_CAP;

        /* Read value of LINK CAP register. */
        regVal = HW_RD_REG32(cfgAddr);

        /* Set link speed. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_EP_DBICS_LNK_CAP_MAX_LINK_SPEEDS,
            maxLinkSpeed);

        /* Set link width. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_EP_DBICS_LNK_CAP_MAX_LINK_WIDTH,
            maxLinkWidth);

        /* Updated the value of LINK CAP register. */
        HW_WR_REG32(cfgAddr, regVal);
    }
}

pcieLinkSpeed_t PCIEGetLinkSpeed(uint32_t baseAddr)
{
    pcieLinkSpeed_t activeLinkSpeed;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        activeLinkSpeed =
            (pcieLinkSpeed_t) (HW_RD_FIELD32(
                                   baseAddr + PCIECTRL_RC_DBICS_OFFSET +
                                   PCIECTRL_RC_DBICS_LNK_CAS,
                                   PCIECTRL_RC_DBICS_LNK_CAS_LINK_SPEED));
    }
    else
    {
        activeLinkSpeed =
            (pcieLinkSpeed_t) (HW_RD_FIELD32(
                                   baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                                   PCIECTRL_EP_DBICS_LNK_CAS,
                                   PCIECTRL_EP_DBICS_LNK_CAS_LINK_SPEED));
    }

    return activeLinkSpeed;
}

void PCIEMainIntrEnable(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET +
        PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN,
        intrMask);
}

void PCIEMainIntrDisable(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET +
        PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN,
        intrMask);
}

uint32_t PCIEGetMainIntrEnable(uint32_t baseAddr)
{
    return HW_RD_REG32(
               baseAddr + PCIECTRL_TI_CONF_OFFSET +
               PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN);
}

uint32_t PCIEMainIntrStatus(uint32_t baseAddr)
{
    return HW_RD_REG32(
               baseAddr + PCIECTRL_TI_CONF_OFFSET +
               PCIECTRL_TI_CONF_IRQSTATUS_MAIN);
}

void PCIEMainIntrClear(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_IRQSTATUS_MAIN,
        intrMask);
}

uint32_t PCIEMainIntrRawStatus(uint32_t baseAddr)
{
    return HW_RD_REG32(
               baseAddr + PCIECTRL_TI_CONF_OFFSET +
               PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN);
}

void PCIEMsiIntrEnable(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_IRQENABLE_SET_MSI,
        intrMask);
}

void PCIEMsiIntrDisable(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI,
        intrMask);
}

uint32_t PCIEGetMsiIntrEnable(uint32_t baseAddr)
{
    return HW_RD_REG32(
               baseAddr + PCIECTRL_TI_CONF_OFFSET +
               PCIECTRL_TI_CONF_IRQENABLE_SET_MSI);
}

uint32_t PCIEMsiIntrStatus(uint32_t baseAddr)
{
    return HW_RD_REG32(
               baseAddr + PCIECTRL_TI_CONF_OFFSET +
               PCIECTRL_TI_CONF_IRQSTATUS_MSI);
}

void PCIEMsiIntrClear(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_IRQSTATUS_MSI,
        intrMask);
}

uint32_t PCIEMsiIntrRawStatus(uint32_t baseAddr)
{
    return HW_RD_REG32(
               baseAddr + PCIECTRL_TI_CONF_OFFSET +
               PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI);
}

void PCIETrafficCtrl(uint32_t                       baseAddr,
                     const pcieLocationParams_t    *locationParams,
                     const pcieTrafficCtrlParams_t *trafficCtrlParams)
{
    uint32_t regVal;
    uint32_t cfgAddr, regOffset;
    uint32_t disableIntx;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        regOffset = PCIECTRL_RC_DBICS_OFFSET +
                    PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER;
    }
    else
    {
        regOffset = PCIECTRL_EP_DBICS_OFFSET +
                    PCIECTRL_EP_DBICS_STATUS_COMMAND_REGISTER;
    }

    if (PCIE_LOCATION_LOCAL == locationParams->location)
    {
        cfgAddr = baseAddr + regOffset;
    }
    else
    {
        if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE +
                      locationParams->outboundCfgOffset +
                      regOffset;
        }
        else
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE +
                      locationParams->outboundCfgOffset +
                      regOffset;
        }
    }

    /* Read value of command status register. */
    regVal = HW_RD_REG32(cfgAddr);

    /* Enable or disable IO space. */
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_IO_SPACE_EN,
        trafficCtrlParams->enableIoSpace);

    /* Enable or disable Mem space. */
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_MEM_SPACE_EN,
        trafficCtrlParams->enableMemSpace);

    /* Enable or disable Bus master. */
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_BUSMASTER_EN,
        trafficCtrlParams->enableBusMaster);

    /* Enable or disable Intx assert. */
    if (PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_DISABLE ==
        trafficCtrlParams->enableIntxAssert)
    {
        disableIntx =
            PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_ENABLE;
    }
    else
    {
        disableIntx =
            PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_DISABLE;
    }
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS,
        disableIntx);

    /* Updated the value of command status register. */
    HW_WR_REG32(cfgAddr, regVal);
}

void PCIETrafficStatus(uint32_t                    baseAddr,
                       const pcieLocationParams_t *locationParams,
                       pcieTrafficCtrlParams_t    *trafficCtrlParams)
{
    uint32_t cfgAddr, regOffset;
    uint32_t disableIntx;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        regOffset = PCIECTRL_RC_DBICS_OFFSET +
                    PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER;
    }
    else
    {
        regOffset = PCIECTRL_EP_DBICS_OFFSET +
                    PCIECTRL_EP_DBICS_STATUS_COMMAND_REGISTER;
    }

    if (PCIE_LOCATION_LOCAL == locationParams->location)
    {
        cfgAddr = baseAddr + regOffset;
    }
    else
    {
        if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE +
                      locationParams->outboundCfgOffset
                      + regOffset;
        }
        else
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE +
                      locationParams->outboundCfgOffset
                      + regOffset;
        }
    }

    /* Get IO space status. */
    trafficCtrlParams->enableIoSpace =
        HW_RD_FIELD32(
            cfgAddr, PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_IO_SPACE_EN);

    /* Get Mem space status. */
    trafficCtrlParams->enableMemSpace =
        HW_RD_FIELD32(
            cfgAddr, PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_MEM_SPACE_EN);

    /* Get Bus master status. */
    trafficCtrlParams->enableBusMaster =
        HW_RD_FIELD32(
            cfgAddr, PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_BUSMASTER_EN);

    if (PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_DISABLE ==
        HW_RD_FIELD32(
            cfgAddr, PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS))
    {
        disableIntx =
            PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_ENABLE;
    }
    else
    {
        disableIntx =
            PCIECTRL_RC_DBICS_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_DISABLE;
    }

    /* Get Intx status status. */
    trafficCtrlParams->enableIntxAssert = disableIntx;
}

void PCIELtssmEnable(uint32_t baseAddr, uint32_t ltssmEnable)
{
    /* Read value of command status register.
     * Enable or disable IO space.
     * Updated the value of command status register. */
    HW_WR_FIELD32(
        baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_DEVICE_CMD,
        PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN,
        ltssmEnable);
}

pcieLtssmState_t PCIELtssmStatus(uint32_t baseAddr)
{
    return (pcieLtssmState_t) (HW_RD_FIELD32(
                                   baseAddr + PCIECTRL_TI_CONF_OFFSET +
                                   PCIECTRL_TI_CONF_DEVICE_CMD,
                                   PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE));
}

void PCIEBarConfig(uint32_t                    baseAddr,
                   const pcieLocationParams_t *locationParams,
                   uint32_t                    barNumber,
                   const pcieBarParams_t      *barParams)
{
    uint32_t regVal;
    uint32_t cfgAddr;
    uint32_t barOffset;
    uint32_t regOffset;
    uint32_t maskRegOffset;

    /* Get BAR offset for BAR number passed. */
    if (PCIE_BAR_ADDR_SIZE_32BIT == barParams->barAddrSize)
    {
        barOffset = PCIE_32BIT_BAR_SIZE * barNumber;
    }
    else
    {
        barOffset = PCIE_64BIT_BAR_SIZE * barNumber;
    }

    /* Get BAR register offset for BAR number passed. */
    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        regOffset = PCIECTRL_RC_DBICS_OFFSET +
                    PCIECTRL_RC_DBICS_BAR0 + barOffset;

        maskRegOffset = PCIECTRL_RC_DBICS2_OFFSET +
                        PCIECTRL_RC_DBICS2_BAR0_MASK + barOffset;
    }
    else
    {
        regOffset = PCIECTRL_EP_DBICS_OFFSET +
                    PCIECTRL_EP_DBICS_BAR0 + barOffset;

        maskRegOffset = PCIECTRL_EP_DBICS2_OFFSET +
                        PCIECTRL_EP_DBICS2_BAR0_MASK + barOffset;
    }

    /* Get BAR register address for BAR number passed. */
    if (PCIE_LOCATION_LOCAL == locationParams->location)
    {
        /* Get BAR register address to configure local BAR. */
        cfgAddr = baseAddr + regOffset;

        /* Configure BAR mask. */
        regVal = HW_RD_REG32(baseAddr + maskRegOffset);

        /* Set BAR mask. */
        HW_SET_FIELD32(
            regVal,
            PCIECTRL_RC_DBICS2_BAR0_MASK_BAR_MASK,
            (barParams->lowerBarMask >>
             PCIECTRL_RC_DBICS2_BAR0_MASK_BAR_MASK_SHIFT));

        HW_SET_FIELD32(
            regVal,
            PCIECTRL_RC_DBICS2_BAR0_MASK_BAR_ENBALE,
            barParams->enableBar);

        /* Updated the value of BAR register. */
        HW_WR_REG32((baseAddr + maskRegOffset), regVal);

        /* Set Upper BAR mask for 64 bit BAR. */
        if (PCIE_BAR_ADDR_SIZE_64BIT == barParams->barAddrSize)
        {
            /* Set upper address of 64 bit BAR. */
            HW_WR_REG32(
                (baseAddr + maskRegOffset + PCIE_32BIT_BAR_SIZE),
                barParams->upperBarMask);
        }
    }
    else
    {
        /* Get BAR register address to configure Remote BAR. */
        if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE +
                      locationParams->outboundCfgOffset
                      + regOffset;
        }
        else
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE +
                      locationParams->outboundCfgOffset
                      + regOffset;
        }
    }

    /* Read value BAR register. */
    regVal = HW_RD_REG32(cfgAddr);

    /* Set BAR address. */
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_BAR0_BASE_ADDR_RW,
        (barParams->lowerBaseAddr >>
         PCIECTRL_RC_DBICS_BAR0_BASE_ADDR_RW_SHIFT));

    /* Set BAR prefetchable type. */
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_BAR0_PREFETCHABLE,
        barParams->enablePrefetch);

    /* Set BAR size. */
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_BAR0_AS,
        barParams->barAddrSize);

    /* Set BAR type */
    HW_SET_FIELD32(
        regVal,
        PCIECTRL_RC_DBICS_BAR0_SPACE_INDICATOR,
        barParams->barType);

    /* Updated the value of BAR register. */
    HW_WR_REG32(cfgAddr, regVal);

    if (PCIE_BAR_ADDR_SIZE_64BIT == barParams->barAddrSize)
    {
        /* Set upper BAR address of 64 bit BAR. */
        HW_WR_REG32(cfgAddr + PCIE_32BIT_BAR_SIZE, barParams->upperBaseAddr);
    }
}

void PCIEMsiMailboxConfig(uint32_t                      baseAddr,
                          const pcieLocationParams_t   *locationParams,
                          const pcieMsiMailboxParams_t *msiMailboxParams)
{
    uint32_t cfgAddr;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        if (PCIE_LOCATION_LOCAL == locationParams->location)
        {
            /* Configure local MSI mail box lower address. */
            cfgAddr = baseAddr + PCIECTRL_PL_OFFSET +
                      PCIECTRL_PL_MSI_CTRL_ADDRESS;

            HW_WR_REG32(cfgAddr, msiMailboxParams->lowerAddr);

            /* Configure local MSI mail box upper address. */
            cfgAddr = baseAddr + PCIECTRL_PL_OFFSET +
                      PCIECTRL_PL_MSI_CTRL_UPPER_ADDRESS;

            HW_WR_REG32(cfgAddr, msiMailboxParams->upperAddr);
        }
        else
        {
            /* Get outbound remote configuration space. */
            if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
            {
                cfgAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE +
                          locationParams->outboundCfgOffset +
                          PCIECTRL_EP_PCIEWIRE_OFFSET;
            }
            else
            {
                cfgAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE +
                          locationParams->outboundCfgOffset +
                          PCIECTRL_EP_PCIEWIRE_OFFSET;
            }

            /* Configure Remote MSI descriptor lower address. */
            HW_WR_REG32(
                cfgAddr + PCIECTRL_EP_PCIEWIRE_MSI_ADDR_L32,
                msiMailboxParams->lowerAddr);

            /* Configure Remote MSI descriptor upper address. */
            HW_WR_REG32(
                cfgAddr + PCIECTRL_EP_PCIEWIRE_MSI_ADDR_U32,
                msiMailboxParams->upperAddr);

            /* Configure Remote MSI descriptor data. */
            HW_WR_REG32(
                cfgAddr + PCIECTRL_EP_PCIEWIRE_MSI_DATA,
                msiMailboxParams->data);
        }
    }
    else
    {
        if (PCIE_LOCATION_LOCAL == locationParams->location)
        {
            /* Configure local MSI mail box lower address. */
            cfgAddr = baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                      PCIECTRL_EP_DBICS_MSI_ADDR_L32;

            HW_WR_REG32(cfgAddr, msiMailboxParams->lowerAddr);

            /* Configure local MSI mail box upper address. */
            cfgAddr = baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                      PCIECTRL_EP_DBICS_MSI_ADDR_U32;

            HW_WR_REG32(cfgAddr, msiMailboxParams->upperAddr);

            /* Configure local MSI mail box Data. */
            cfgAddr = baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                      PCIECTRL_EP_DBICS_MSI_DATA;

            HW_WR_REG32(cfgAddr, msiMailboxParams->data);
        }
    }
}

void PCIEMsiCtrl(uint32_t                    baseAddr,
                 const pcieLocationParams_t *locationParams,
                 const pcieMsiCtrlParams_t  *msiCtrlParams)
{
    uint32_t regVal;
    uint32_t cfgAddr;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        if (PCIE_LOCATION_LOCAL == locationParams->location)
        {
            /* Configure local MSI capabilities. */
            cfgAddr = baseAddr + PCIECTRL_RC_DBICS_OFFSET +
                      PCIECTRL_RC_DBICS_MSI_CAP;

            regVal = HW_RD_REG32(cfgAddr);

            /* Enable or disable  64 bit MSI generation. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_RC_DBICS_MSI_CAP_MSI_64_EN,
                msiCtrlParams->enable64Bit);

            /* Enable or disable multiple msg capability. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_RC_DBICS_MSI_CAP_MME,
                msiCtrlParams->enableMultiMsg);

            /* Enable or disable MSI generation. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_RC_DBICS_MSI_CAP_MSI_EN,
                msiCtrlParams->enableMsi);

            HW_WR_REG32(cfgAddr, regVal);
        }
        else
        {
            /* Get outbound remote configuration space. */
            if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
            {
                cfgAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE +
                          locationParams->outboundCfgOffset +
                          PCIECTRL_EP_PCIEWIRE_OFFSET +
                          PCIECTRL_EP_PCIEWIRE_MSI_CAP;
            }
            else
            {
                cfgAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE +
                          locationParams->outboundCfgOffset +
                          PCIECTRL_EP_PCIEWIRE_OFFSET +
                          PCIECTRL_EP_PCIEWIRE_MSI_CAP;
            }

            regVal = HW_RD_REG32(cfgAddr);

            /* Enable or disable  64 bit MSI generation. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_EP_PCIEWIRE_MSI_CAP_MSI_64_EN,
                msiCtrlParams->enable64Bit);

            /* Enable or disable multiple msg capability. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_EP_PCIEWIRE_MSI_CAP_MME,
                msiCtrlParams->enableMultiMsg);

            /* Enable or disable MSI generation. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_EP_PCIEWIRE_MSI_CAP_MSI_EN,
                msiCtrlParams->enableMsi);

            HW_WR_REG32(cfgAddr, regVal);
        }
    }
    else
    {
        if (PCIE_LOCATION_LOCAL == locationParams->location)
        {
            /* Configure local MSI capabilities. */
            cfgAddr = baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                      PCIECTRL_EP_DBICS_MSI_CAP;

            regVal = HW_RD_REG32(cfgAddr);

            /* Enable or disable  64 bit MSI generation. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_EP_DBICS_MSI_CAP_MSI_64_EN,
                msiCtrlParams->enable64Bit);

            /* Enable or disable multiple msg capability. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_EP_DBICS_MSI_CAP_MME,
                msiCtrlParams->enableMultiMsg);

            /* Enable or disable MSI generation. */
            HW_SET_FIELD32(
                regVal,
                PCIECTRL_EP_DBICS_MSI_CAP_MSI_EN,
                msiCtrlParams->enableMsi);

            HW_WR_REG32(cfgAddr, regVal);
        }
    }
}

void PCIEMsiIntrCtrl(uint32_t baseAddr,
                     uint32_t msiIntrNum,
                     uint32_t msiIntrGroup,
                     uint32_t enableMsiIntr)
{
    uint32_t regVal;
    uint32_t cfgAddr;

    /* Enable or disable MSI interrupt. */
    cfgAddr = baseAddr + PCIECTRL_PL_OFFSET +
              PCIECTRL_PL_MSI_CTRL_INT_ENABLE(msiIntrGroup);

    regVal = HW_RD_REG32(cfgAddr);

    if (TRUE == enableMsiIntr)
    {
        regVal |= ((uint32_t) 1U << msiIntrNum);
    }
    else
    {
        regVal &= (~((uint32_t) 1U << msiIntrNum));
    }

    HW_WR_REG32(cfgAddr, regVal);
}

uint32_t PCIEMsiActiveIntrStatus(uint32_t baseAddr, uint32_t msiIntrGroup)
{
    return HW_RD_REG32(
               baseAddr + PCIECTRL_PL_OFFSET +
               PCIECTRL_PL_MSI_CTRL_INT_STATUS(msiIntrGroup));
}

void PCIEMsiActiveIntrClear(uint32_t baseAddr,
                            uint32_t msiIntrGroup,
                            uint32_t intrMask)
{
    HW_WR_REG32(
        baseAddr + PCIECTRL_PL_OFFSET +
        PCIECTRL_PL_MSI_CTRL_INT_STATUS(msiIntrGroup),
        intrMask);
}

void PCIEMsiTransmit(uint32_t          baseAddr,
                     pcieMsiIntrType_t msiType,
                     uint32_t          msiOutboundCfgSpace)
{
    uint32_t regVal;
    uint32_t msiData;
    uint32_t cfgAddr;

    /* Get MSI data. */
    msiData = HW_RD_REG32(
        baseAddr + PCIECTRL_EP_DBICS_OFFSET +
        PCIECTRL_EP_DBICS_MSI_DATA);

    if (PCIE_MSI_INTR_TYPE_HW == msiType)
    {
        /* Configure MSI data to be written into XMT register. */
        regVal =
            ((msiData <<
              PCIECTRL_TI_CONF_MSI_XMT_VECTOR_SHIFT) &
             PCIECTRL_TI_CONF_MSI_XMT_VECTOR_MASK);

        regVal |=
            ((uint32_t) PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT <<
             PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_SHIFT);

        /* Grant MSI request. */
        HW_WR_REG32(
            baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_MSI_XMT,
            regVal);

        /* Wait till MSI request is granted. */
        do
        {
            regVal = HW_RD_REG32(
                baseAddr + PCIECTRL_TI_CONF_OFFSET +
                PCIECTRL_TI_CONF_MSI_XMT) &
                     PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_MASK;
        } while (PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_PENDING == regVal);
    }
    else
    {
        /* Get outbound remote configuration space. */
        if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE + msiOutboundCfgSpace;
        }
        else
        {
            cfgAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE + msiOutboundCfgSpace;
        }

        HW_WR_REG32(cfgAddr, msiData);
    }
}

uint32_t PCIEGetOutboundAddr(uint32_t baseAddr)
{
    uint32_t outBoundBaseAddr;

    /* Get outbound remote configuration space. */
    if ((uint32_t) SOC_PCIE_SS1_CONF_BASE == baseAddr)
    {
        outBoundBaseAddr = (uint32_t) SOC_PCIE_SS1_DAT_BASE;
    }
    else
    {
        outBoundBaseAddr = (uint32_t) SOC_PCIE_SS2_DAT_BASE;
    }

    return outBoundBaseAddr;
}

void PCIELegacyIntrTransmit(uint32_t baseAddr, pcieLegacyIntr_t intrAssert)
{
    if (PCIE_LEGACY_INTR_ASSERT == intrAssert)
    {
        /* Assert Legacy interrupt. */
        HW_WR_REG32(
            baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_INTX_ASSERT,
            (uint32_t) PCIECTRL_TI_CONF_INTX_ASSERT_F0);
    }
    else
    {
        /* De-Assert Legacy interrupt. */
        HW_WR_REG32(
            baseAddr + PCIECTRL_TI_CONF_OFFSET + PCIECTRL_TI_CONF_INTX_DEASSERT,
            (uint32_t) PCIECTRL_TI_CONF_INTX_DEASSERT_F0);
    }
}

uint32_t PCIEGetLegacyIntrStatus(uint32_t baseAddr, pcieLegacyIntr_t intrAssert)
{
    uint32_t legacyIntrStatus;

    if (PCIE_LEGACY_INTR_ASSERT == intrAssert)
    {
        /* Legacy interrupt assert status. */
        legacyIntrStatus = HW_RD_REG32(
            baseAddr + PCIECTRL_TI_CONF_OFFSET +
            PCIECTRL_TI_CONF_INTX_ASSERT) &
                           PCIECTRL_TI_CONF_INTX_ASSERT_F0_MASK;
    }
    else
    {
        /* Legacy interrupt de-assert status. */
        legacyIntrStatus = HW_RD_REG32(
            baseAddr + PCIECTRL_TI_CONF_OFFSET +
            PCIECTRL_TI_CONF_INTX_DEASSERT) &
                           PCIECTRL_TI_CONF_INTX_DEASSERT_F0_MASK;
    }

    return legacyIntrStatus;
}

void PCIEChangeLinkSpeed(uint32_t baseAddr, pcieLinkSpeed_t newSpeed)
{
    uint32_t cfgAddr;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        cfgAddr = baseAddr + PCIECTRL_RC_DBICS_OFFSET +
                  PCIECTRL_RC_DBICS_LNK_CAS_2;
    }
    else
    {
        cfgAddr = baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                  PCIECTRL_EP_DBICS_LNK_CAS_2;
    }

    /* Set target Link speed. */
    HW_WR_FIELD32(
        cfgAddr,
        PCIECTRL_EP_DBICS_LNK_CAS_2_TRGT_LINK_SPEED,
        newSpeed);

    /* Switch to new target speed. */
    cfgAddr = baseAddr + PCIECTRL_PL_OFFSET + PCIECTRL_PL_WIDTH_SPEED_CTL;

    HW_WR_FIELD32(
        cfgAddr,
        PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_DIRECTED_CHANGE,
        PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_DIRECTED_CHANGE_ENABLE);
}

uint32_t PCIEGetDeviceVendorId(uint32_t                    baseAddr,
                               const pcieLocationParams_t *locationParams)
{
    uint32_t cfgAddr;

    if (PCIE_DEVICE_TYPE_RC == PCIEGetDeviceType(baseAddr))
    {
        cfgAddr = baseAddr + PCIECTRL_RC_DBICS_OFFSET +
                  PCIECTRL_RC_DBICS_DEVICE_VENDORID;
    }
    else
    {
        cfgAddr = baseAddr + PCIECTRL_EP_DBICS_OFFSET +
                  PCIECTRL_EP_DBICS_DEVICE_VENDORID;
    }

    return HW_RD_REG32(cfgAddr);
}
/********************************* End of file ******************************/
