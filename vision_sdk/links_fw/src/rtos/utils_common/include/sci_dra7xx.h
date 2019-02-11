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

#ifndef SCI_DRA7XX_H
#define SCI_DRA7XX_H

/*! \file sci_dra7xx.h
    DRA7xx device specific CPTLib definitions
*/

/*! \enum sci_probeid_sdram
    Probe selection for sdram statistic collectors.
*/
enum sci_probeid_sdram {
    SCI_EMIF1,                    /*!< EMIF1 */
    SCI_EMIF2,                    /*!< EMIF2 */
    SCI_MA_MPU_P1,                /*!< MA_MPU_P1 */
    SCI_MA_MPU_P2                /*!< MA_MPU_P2 */
};

/*! \enum sci_probeid_mstr
    Probe selection for master statistic collectors.
    Note: Order for probe_name_table indexing - not probe ids.
    For probe_ids a probe_map table is used (see sci_config_dra7xx.h).
 */
enum sci_probeid_mstr {
    SCI_MPU,            /*!< MPU */
    SCI_MMU1,            /*!< MMU1 */
    SCI_EDMA_TC0_RD,    /*!< EDMA TC0 RD */
    SCI_EDMA_TC0_WR,    /*!< EDMA TC0 WR */
    SCI_EDMA_TC1_RD,    /*!< EDMA TC1 RD */
    SCI_EDMA_TC1_WR,    /*!< EDMA TC1 WR */
    SCI_VIP1_P1,        /*!< VIP1 P1 */
    SCI_VIP1_P2,        /*!< VIP1 P2 */
    SCI_VIP2_P1,        /*!< VIP2 P1 */
    SCI_VIP2_P2,        /*!< VIP2 P2 */
    SCI_VIP3_P1,        /*!< VIP3 P1 */
    SCI_VIP3_P2,        /*!< VIP3 P2 */
    SCI_VPE_P1,            /*!< VIPE P1 */
    SCI_VPE_P2,            /*!< VIPE P2 */
    SCI_EVE1_TC0,        /*!< EVE1 TC0 */
    SCI_EVE1_TC1,        /*!< EVE1 TC1 */
    SCI_EVE2_TC0,        /*!< EVE2 TC0 */
    SCI_EVE2_TC1,        /*!< EVE2 TC1 */
    SCI_EVE3_TC0,
    SCI_EVE3_TC1,
    SCI_EVE4_TC0,
    SCI_EVE4_TC1,
    SCI_DSP1_MDMA,        /*!< DSP1 MDMA */
    SCI_DSP1_EDMA,        /*!< DSP1 EDMA */
    SCI_DSP2_MDMA,        /*!< DSP2 MDMA */
    SCI_DSP2_EDMA,        /*!< DSP2 EDMA */
    SCI_IVA,            /*!< IVA */
    SCI_GPU_P1,            /*!< GPU P1 */
    SCI_GPU_P2,            /*!< GPU P2 */
    SCI_BB2D_P1,        /*!< BB2D P1 */
    SCI_DSS,            /*!< DSS */
    SCI_MMU2,            /*!< MMU2 */
    SCI_IPU1,            /*!< IPU1 */
    SCI_IPU2,            /*!< IPU2 */
    SCI_DMA_SYSTEM_RD,    /*!< DMA SYSTEM RD */
    SCI_DMA_SYSTEM_WR,     /*!< DMA SYSTEM WR */
    SCI_USB1,            /*!< USB1 */
    SCI_USB2,            /*!< USB2 */
    SCI_USB3,            /*!< USB3 */
    SCI_USB4,            /*!< USB4 */
    SCI_PCIE_SS1,        /*!< PCIE SS1 */
    SCI_PCIE_SS2,        /*!< PCIE SS2 */
    SCI_DSP1_CFG,        /*!< DSP1 CFG */
    SCI_DSP2_CFG,        /*!< DSP2 CFG */
    SCI_GMAC_SW,        /*!< GMAC SW */
    SCI_MMC1,            /*!< MMC1 */
    SCI_MMC2,            /*!< MMC2 */
    SCI_SATA,            /*!< SATA */
    SCI_MLB,            /*!< MLB */
    SCI_BB2D_P2,        /*!< BB2D P2 */
    SCI_IEEE1500,        /*!< IEEE1500 */
    SCI_DEBUGSS,        /*!< DEBUGSS */
    SCI_VCP1,            /*!< VCP1 */
    SCI_OCMC_RAM1,        /*!< OCMC RAM1 */
    SCI_OCMC_RAM2,        /*!< OCMC RAM2 */
    SCI_OCMC_RAM3,        /*!< OCMC RAM3 */
    SCI_GPMC,            /*!< GPMC */
    SCI_MCASP1,            /*!< MCASP1 */
    SCI_MCASP2,            /*!< MCASP2 */
    SCI_MCASP3,            /*!< MCASP3 */
    SCI_VCP2            /*!< VCP2 */
};

/*! \enum sci_master_addr
     Master address enumerations.
*/
enum sci_master_addr {
    SCI_MSTID_MPU = 0x0,                /*!< MPU */
    SCI_MSTID_DAP = 0x10,                /*!< DAP */
    SCI_MSTID_IEEE1500_2_OCP = 0x14,    /*!< IEEE1500 */
    SCI_MSTID_DSP1_MDMA = 0x20,            /*!< DSP1 MDMA */
    SCI_MSTID_DSP1_CFG = 0x24,            /*!< DSP1 CFG */
    SCI_MSTID_DSP1_DMA = 0x28,            /*!< DSP1 DMA */
    SCI_MSTID_DSP2_DMA = 0x2C,            /*!< DSP2 DMA */
    SCI_MSTID_DSP2_CFG = 0x30,            /*!< DSP2 CFG */
    SCI_MSTID_DSP2_MDMA = 0x34,            /*!< DSP2 MDMA */
    SCI_MSTID_IVA_ICONT1 = 0x3A,        /*!< IVA ICONT1 */
    SCI_MSTID_EVE1_P1 = 0x42,            /*!< EVE1 P1 */
    SCI_MSTID_EVE2_P1 = 0x46,            /*!< EVE2 P1 */
    SCI_MSTID_IPU1 = 0x60,                /*!< IPU1 */
    SCI_MSTID_IPU2 = 0x64,                /*!< IPU2 */
    SCI_MSTID_SDMA_RD = 0x68,            /*!< SDMA RD */
    SCI_MSTID_SDMA_WR = 0x6A,            /*!< SDMA WR */
    SCI_MSTID_EDMA_TC1_WR = 0x70,        /*!< EDMA TC1 WR */
    SCI_MSTID_EDMA_TC1_RD = 0x72 ,        /*!< EDMA TC1 RD */
    SCI_MSTID_EDMA_TC2_WR = 0x74,        /*!< EDMA TC2 WR */
    SCI_MSTID_EDMA_TC2_RD = 0x76,        /*!< EDMA TC2 RD */
    SCI_MSTID_DSS =0x80,                /*!< DSS */
    SCI_MSTID_MLB = 0x84,                /*!< MLB */
    SCI_MSTID_MMU1 = 0x86,                /*!< MMU1 */
    SCI_MSTID_PCIE_SS1 = 0x88,            /*!< PCIE SS1 */
    SCI_MSTID_PCIE_SS2 = 0x8C,            /*!< PCIE SS2 */
    SCI_MSTID_MMU2 = 0x8E,                /*!< MMU2 */
    SCI_MSTID_VIP1_P1 = 0x90,            /*!< VIP1 P1 */
    SCI_MSTID_VIP1_P2 = 0x92,            /*!< VIP1 P2 */
    SCI_MSTID_VIP2_P1 = 0x94,            /*!< VIP2 P1 */
    SCI_MSTID_VIP2_P2 = 0x96,            /*!< VIP2 P2 */
    SCI_MSTID_VIP3_P1 = 0x98,            /*!< VIP3 P1 */
    SCI_MSTID_VIP3_P2 = 0x9A,            /*!< VIP3 P2 */
    SCI_MSTID_VPE_P1 = 0x9C,            /*!< VIPE P1 */
    SCI_MSTID_VPE_P2 = 0x9E,            /*!< VIPE P2 */
    SCI_MSTID_MMC1 = 0xA0,                /*!< MMC1 */
    SCI_MSTID_GPU_P1 = 0xA2,            /*!< GPU */
    SCI_MSTID_MMC2 = 0xA4,                /*!< MMC2 */
    SCI_MSTID_GPU_P2 = 0xA6,            /*!< GPU P2 */
    SCI_MSTID_BB2D_P1 = 0xA8,            /*!< BB2D P1 */
    SCI_MSTID_BB2D_P2 = 0xAA,            /*!< BB2D P2 */
    SCI_MSTID_GMAC_SW = 0xAC,            /*!< GMAC SW */
    SCI_MSTID_USB4 = 0xB0 ,                /*!< USB4 */
    SCI_MSTID_USB1 = 0xB4,                /*!< USB1 */
    SCI_MSTID_USB2 = 0xB8,                /*!< USB2 */
    SCI_MSTID_USB3 = 0xBC,                /*!< USB3 */
    SCI_MSTID_SATA = 0xCC,                /*!< SATA */
    SCI_MSTID_EVE1_P2 = 0xD2,            /*!< EVE1 P2 */
    SCI_MSTID_EVE2_P2 = 0xD6,            /*!< EVE2 P2 */
    SCI_MASTID_ALL = 0xFF                /*!< Select all masters */

};

/*! \enum sci_slave_addr
    Slave address enumerations.
*/
enum sci_slave_addr {
    SCI_SLVID_DMM_P1 = 0x02,            /*!< DMM P1 */
    SCI_SLVID_DMM_P2 = 0x03,            /*!< DMM P2 */
    SCI_SLVID_DSP1_SDMA = 0x04,            /*!< DSP1 SDMA */
    SCI_SLVID_DSP2_SDMA = 0x05,            /*!< DSP2 SDMA */
    SCI_SLVID_DSS = 0x06,                /*!< DSS */
    SCI_SLVID_EVE1 = 0x07,                /*!< EVE1 */
    SCI_SLVID_EVE2 = 0x08,                /*!< EVE2 */
    SCI_SLVID_BB2D = 0x0B,                /*!< BB2D */
    SCI_SLVID_GPMC = 0x0C,                /*!< GPMC */
    SCI_SLVID_GPU = 0x0D,                /*!< GPU */
    SCI_SLVID_HOST_CLK1_1 = 0x0E,        /*!< HOST CLK1 1 */
    SCI_SLVID_HOST_CLK1_2 = 0x0F,        /*!< HOST CLK1 2 */
    SCI_SLVID_IPU1 = 0x10,                /*!< IPU1 */
    SCI_SLVID_IPU2 = 0x11,                /*!< IPU2 */
    SCI_SLVID_IVA_CONFIG = 0x12,        /*!< IVA CONFIG */
    SCI_SLVID_IVA_SL2IF = 0x13,            /*!< IVA SL2IF */
    SCI_SLVID_L4_CFG = 0x14,            /*!< L4 CFG */
    SCI_SLVID_L4_PER1_P1 = 0x15,        /*!< L4 PER1 P1 */
    SCI_SLVID_L4_PER1_P2 = 0x16,        /*!< L4 PER1 P2 */
    SCI_SLVID_L4_PER1_P3 = 0x17,        /*!< L4 PER1 P3 */
    SCI_SLVID_L4_PER2_P1 = 0x18,        /*!< L4 PER2 P1 */
    SCI_SLVID_L3_INSTR = 0x19,            /*!< L3 INSTR */
    SCI_SLVID_L4_PER2_P3 = 0x1A,        /*!< L4 PER2 P3 */
    SCI_SLVID_L4_PER3_P1 = 0x1B,        /*!< L4 PER3 P1 */
    SCI_SLVID_L4_PER3_P2 = 0x1C,        /*!< L4 PER3 P2 */
    SCI_SLVID_L4_PER3_P3 = 0x1D,        /*!< L4 PER3 P3 */
    SCI_SLVID_L4_WKUP = 0x1E,            /*!< L4 WKUP */
    SCI_SLVID_MCASP1 = 0x1F,            /*!< MCASP1 */
    SCI_SLVID_MCASP2 = 0x20,            /*!< MCASP2 */
    SCI_SLVID_MCASP3 = 0x21,            /*!< MCASP3 */
    SCI_SLVID_MMU1 = 0x22,                /*!< MMU1 */
    SCI_SLVID_MMU2 = 0x23,                /*!< MMU2 */
    SCI_SLVID_OCMC_RAM1 = 0x24,            /*!< OCMC RAM1 */
    SCI_SLVID_OCMC_RAM2 = 0x25,            /*!< OCMC RAM2 */
    SCI_SLVID_OCMC_RAM3 = 0x26,            /*!< OCMC RAM3 */
    SCI_SLVID_OCMC_ROM = 0x27,            /*!< OCMC ROM */
    SCI_SLVID_PCIE_SS1 = 0x28,            /*!< PCIE SS12 */
    SCI_SLVID_PCIE_SS2 = 0x29,            /*!< PCIE SS2 */
    SCI_SLVID_EDMA_TPCC = 0x30,            /*!< EDMA TPCC */
    SCI_SLVID_EDMA_TC1 = 0x31,            /*!< EDMA TC1 */
    SCI_SLVID_EDMA_TC2 = 0x32,            /*!< EDMA TC2 */
    SCI_SLVID_VCP1 = 0x36,                /*!< VCP1 */
    SCI_SLVID_VCP2 = 0x37,                /*!< VCP2 */
    SCI_SLVID_QSPI = 0x39,                /*!< QSPI */
    SCI_SLVID_HOST_CLK2_1 = 0x40,        /*!< HOST CLK2 1 */
    SCI_SLVID_DEBUGSS_CT_TBR = 0x41,    /*!< DEBUGSS CT TBR */
    SCI_SLVID_L4_PER2_P2 = 0x42,        /*!< L4 PER2 P2 */
    SCI_SLVID_ALL = 0xFF               /*!< Select all slaves */
};
#endif /*  #ifndef SCI_DRA7XX_H */
