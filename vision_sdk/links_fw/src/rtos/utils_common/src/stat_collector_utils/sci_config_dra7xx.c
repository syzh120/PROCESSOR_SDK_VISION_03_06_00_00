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

#include "sci_config_dra7xx.h"
#include <src/rtos/utils_common/include/sci_dra7xx.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

const sc_cnt_elements_t sdram_cnt_map[SC_SDRAM_NUM_CNTRS] = {
    {2, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt0},
    {1, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt1},
    {2, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt2},
    {1, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt3},
    {1, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt4},
    {1, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt5},
    {1, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt6},
    {1, (uint32_t)&((struct sc_sdram_reg_map *)0)->counters.cnt7}
};

/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * KW State: Defer -> Waiver -> Case by case
 *
 */
const sc_cnt_elements_t lat_cnt_map[SC_LAT_NUM_CNTRS] = {
    {1, (uint32_t)&((sc_lat_reg_map_t *)0)->counters.cnt[0]},
    {1, (uint32_t)&((sc_lat_reg_map_t *)0)->counters.cnt[1]},
    {1, (uint32_t)&((sc_lat_reg_map_t *)0)->counters.cnt[2]},
    {1, (uint32_t)&((sc_lat_reg_map_t *)0)->counters.cnt[3]}
};

const sc_probe_element_t sc_sdram_probe_map[SC_SDRAM_NUM_PROBES] = {
    {SCI_EMIF1, 0, 1},
    {SCI_EMIF2, 2, 3},
    {SCI_MA_MPU_P1, 4, 5},
    {SCI_MA_MPU_P2, 6, 7}
};

const sc_probe_valid_t sc_sdram_no_filter_valid_probe_map[SC_SDRAM_PROBE] = {
        SCI_VALID_PROBE, /*SCI_EMIF1 restricted - can not use */
        SCI_VALID_PROBE, /*SCI_EMIF2 restricted - can not use */
        SCI_VALID_PROBE, /*SCI_MA_MPU_P1 ok to use */
        SCI_VALID_PROBE /*SCI_MA_MPU_P2 ok to use */
};

const sc_probe_element_t sc_lat_0_probe_map[] = {
    {SCI_MPU, 0, 1},
    {SCI_MMU1, 2, 3},
    {SCI_EDMA_TC0_RD, 4, 5},
    {SCI_EDMA_TC0_WR, 6, 7},
    {SCI_EDMA_TC1_RD, 8, 9},
    {SCI_EDMA_TC1_WR, 10, 11}
};

const sc_probe_element_t sc_lat_1_probe_map[] = {
    {SCI_VIP1_P1, 0, 1},
    {SCI_VIP1_P2, 2, 3},
    {SCI_VIP2_P1, 4, 5},
    {SCI_VIP2_P2, 6, 7},
    {SCI_VIP3_P1, 8, 9},
    {SCI_VIP3_P2, 10, 11},
    {SCI_VPE_P1, 12, 13},
    {SCI_VPE_P2, 14, 15}
};

const sc_probe_element_t sc_lat_2_probe_map[] = {
    {SCI_EVE1_TC0, 0, 1},
    {SCI_EVE1_TC1, 2, 3},
    {SCI_EVE2_TC0, 4, 5},
    {SCI_EVE2_TC1, 6, 7},
    {SCI_EVE3_TC0, 8, 9},
    {SCI_EVE3_TC1, 10, 11},
    {SCI_EVE4_TC0, 12, 13},
    {SCI_EVE4_TC1, 14, 15}

};

const sc_probe_element_t sc_lat_3_probe_map[] = {
    {SCI_DSP1_MDMA, 0, 1},
    {SCI_DSP1_EDMA, 2, 3},
    {SCI_DSP2_MDMA, 4, 5},
    {SCI_DSP2_EDMA, 6, 7},
    {SCI_IVA, 8, 9},
    {SCI_GPU_P1, 10, 11},
    {SCI_GPU_P2, 12, 13},
    {SCI_BB2D_P1, 14, 15}
};

const sc_probe_element_t sc_lat_4_probe_map[] = {
    {SCI_DSS, 0, 1},
    {SCI_MMU2, 4, 5},
    {SCI_IPU1, 6, 7},
    {SCI_IPU2, 8, 9},
    {SCI_DMA_SYSTEM_RD, 10, 11},
    {SCI_DMA_SYSTEM_WR, 12, 13}
};

const sc_probe_element_t sc_lat_5_probe_map[] = {
    {SCI_USB1, 0, 1},
    {SCI_USB2, 2, 3},
    {SCI_USB3, 4, 5},
    {SCI_USB4, 6, 7},
    {SCI_PCIE_SS1, 8, 9},
    {SCI_PCIE_SS2, 10, 11},
    {SCI_DSP1_CFG, 12, 13},
    {SCI_DSP2_CFG, 14, 15}
};

const sc_probe_element_t sc_lat_6_probe_map[] = {
    {SCI_GMAC_SW, 0, 1},
    {SCI_MPU, 14, 15},
};

const sc_probe_element_t sc_lat_7_probe_map[] = {
    {SCI_MMC1, 0, 1},
    {SCI_MMC2, 2, 3},
    {SCI_SATA, 4, 5},
    {SCI_MLB, 6, 7},
    {SCI_BB2D_P2, 8, 9},
    {SCI_IEEE1500, 10, 11},
    {SCI_DEBUGSS, 12, 13},
    {SCI_VCP1, 14, 15}
};

const sc_probe_element_t sc_lat_8_probe_map[SC_LAT_8_NUM_PROBES] = {
    {SCI_OCMC_RAM1, 0, 1},
    {SCI_OCMC_RAM2, 2, 3},
    {SCI_OCMC_RAM3, 4, 5},
    {SCI_GPMC, 6, 7},
    {SCI_MCASP1, 8, 9},
    {SCI_MCASP2, 10, 11},
    {SCI_MCASP3, 12, 13},
    {SCI_VCP2, 14, 15}
};

/* Statistic Collector element maps */
const sc_element_map_t sc_sdram_map = {
    SDRAM,
    SC_SDRAM_BASE,
    sizeof(struct sc_sdram_reg_map),
    SC_SDRAM_NUM_CNTRS,
    sdram_cnt_map,
    SC_SDRAM_NUM_PROBES,
    sc_sdram_probe_map,
    sc_sdram_no_filter_valid_probe_map,
    SC_SDRAM_LOAD_CNT_OVERFLOW,
    SC_SDRAM_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_0_map = {
    MSTR,
    SC_LAT_0_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_0_NUM_PROBES,
    sc_lat_0_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_1_map = {
    MSTR,
    SC_LAT_1_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_1_NUM_PROBES,
    sc_lat_1_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_2_map = {
    MSTR,
    SC_LAT_2_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_2_NUM_PROBES,
    sc_lat_2_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_3_map = {
    MSTR,
    SC_LAT_3_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_3_NUM_PROBES,
    sc_lat_3_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_4_map = {
    MSTR,
    SC_LAT_4_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_4_NUM_PROBES,
    sc_lat_4_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_5_map = {
    MSTR,
    SC_LAT_5_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_5_NUM_PROBES,
    sc_lat_5_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_6_map = {
    MSTR,
    SC_LAT_6_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_6_NUM_PROBES,
    sc_lat_6_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_7_map = {
    MSTR,
    SC_LAT_7_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_7_NUM_PROBES,
    sc_lat_7_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_8_map = {
    MSTR,
    SC_LAT_8_BASE,
    sizeof(sc_lat_reg_map_t),
    SC_LAT_NUM_CNTRS,
    lat_cnt_map,
    SC_LAT_8_NUM_PROBES,
    sc_lat_8_probe_map,
    NULL,
    SC_LAT_LOAD_CNT_OVERFLOW,
    SC_LAT_LATENCY_CNT_OVERFLOW
};
const sc_element_map_t * sc_map[SC_MAP_MAX] = {
    &sc_sdram_map,
    &sc_lat_0_map,
    &sc_lat_1_map,
    &sc_lat_2_map,
    &sc_lat_3_map,
    &sc_lat_4_map,
    &sc_lat_5_map,
    &sc_lat_6_map,
    &sc_lat_7_map,
    &sc_lat_8_map
};

/* Statistic Collector names are in sc_map order */
const char * sci_unit_name_table[SC_MAP_MAX] = {
    "SDRAM",
    "LAT0",
    "LAT1",
    "LAT2",
    "LAT3",
    "LAT4",
    "LAT5",
    "LAT6",
    "LAT7",
    "LAT8"
};

/* Statistic Collector probe name tables */
const char * sci_sdram_probe_name_table[] = {
    "EMIF1",
    "EMIF2",
    "MA_MPU_P1",
    "MA_MPU_P2"
};

const char * sci_mstr_probe_name_table[] = {
    "MPU",
    "MMU1",
    "EDMA_TC0_RD",
    "EDMA_TC0_WR",
    "EDMA_TC1_RD",
    "EDMA_TC1_WR",
    "VIP1_P1",
    "VIP1_P2",
    "VIP2_P1",
    "VIP2_P2",
    "VIP3_P1",
    "VIP3_P2",
    "VPE_P1",
    "VPE_P2",
    "EVE1_TC0",
    "EVE1_TC1",
    "EVE2_TC0",
    "EVE2_TC1",
    "EVE3_TC0",
    "EVE3_TC1",
    "EVE4_TC0",
    "EVE4_TC1",
    "DSP1_MDMA",
    "DSP1_EDMA",
    "DSP2_MDMA",
    "DSP2_EDMA",
    "IVA",
    "GPU_P1",
    "GPU_P2",
    "BB2D_P1",
    "DSS",
    "MMU2",
    "IPU1",
    "IPU2",
    "DMA_SYSTEM_RD",
    "DMA_SYSTEM_WR",
    "USB1",
    "USB2",
    "USB3",
    "IUSB4",
    "PCIe_SS1",
    "PCIe_SS2",
    "DSP1_CFG",
    "DSP2_CFG",
    "GMAC_SW",
    "MPU",
    "MMC1",
    "MMC2",
    "SATA",
    "MLB",
    "BB2D_P2",
    "IEEE1500",
    "DEBUGSS",
    "OCMC_RAM1",
    "OCMC_RAM2",
    "OCMC_RAM3",
    "GPMC",
    "MCASP1",
    "MCASP2",
    "MCASP3",
    "VCP2"
};

/* Statistic Collector master address table */
enum sci_master_addr sci_master_addr_table[] = {
    SCI_MSTID_MPU,
    SCI_MSTID_DAP,
    SCI_MSTID_IEEE1500_2_OCP,
    SCI_MSTID_DSP1_MDMA,
    SCI_MSTID_DSP1_CFG,
    SCI_MSTID_DSP1_DMA,
    SCI_MSTID_DSP2_DMA,
    SCI_MSTID_DSP2_CFG,
    SCI_MSTID_DSP2_MDMA,
    SCI_MSTID_IVA_ICONT1,
    SCI_MSTID_EVE1_P1,
    SCI_MSTID_EVE2_P1,
    SCI_MSTID_IPU1,
    SCI_MSTID_IPU2,
    SCI_MSTID_SDMA_RD,
    SCI_MSTID_SDMA_WR,
    SCI_MSTID_EDMA_TC1_WR,
    SCI_MSTID_EDMA_TC1_RD,
    SCI_MSTID_EDMA_TC2_WR,
    SCI_MSTID_EDMA_TC2_RD,
    SCI_MSTID_DSS,
    SCI_MSTID_MLB,
    SCI_MSTID_MMU1,
    SCI_MSTID_PCIE_SS1,
    SCI_MSTID_PCIE_SS2,
    SCI_MSTID_MMU2,
    SCI_MSTID_VIP1_P1,
    SCI_MSTID_VIP1_P2,
    SCI_MSTID_VIP2_P1,
    SCI_MSTID_VIP2_P2,
    SCI_MSTID_VIP3_P1,
    SCI_MSTID_VIP3_P2,
    SCI_MSTID_VPE_P1,
    SCI_MSTID_VPE_P2,
    SCI_MSTID_MMC1,
    SCI_MSTID_GPU_P1,
    SCI_MSTID_MMC2,
    SCI_MSTID_GPU_P2,
    SCI_MSTID_BB2D_P1,
    SCI_MSTID_BB2D_P2,
    SCI_MSTID_GMAC_SW,
    SCI_MSTID_USB4,
    SCI_MSTID_USB1,
    SCI_MSTID_USB2,
    SCI_MSTID_USB3,
    SCI_MSTID_SATA,
    SCI_MSTID_EVE1_P2,
    SCI_MSTID_EVE2_P2,
    SCI_MASTID_ALL
};

/* Statistic Collector master name table.
 * In sci_master_addr_table order.
 */
const char * sci_master_name_table[] = {
    "MPU",
    "CS_DAP",
    "IEEE1500_2_OCP",
    "DSP1_MDMA",
    "DSP1_CFG",
    "DSP1_DMA",
    "DSP2_DMA",
    "DSP2_CFG",
    "DSP2_MDMA",
    "IVA_ICONT 1",
    "EVE1_P1",
    "EVE2_P1",
    "IPU1",
    "IPU2",
    "DMA_SYSTEM_RD",
    "DMA_SYSTEM_WR",
    "EDMA_TC1_WR",
    "EDMA_TC1_RD",
    "EDMA_TC2_WR",
    "EDMA_TC2_RD",
    "DSS",
    "MLB",
    "MMU1",
    "PCIe_SS1",
    "PCIe_SS2",
    "MMU2",
    "VIP1_P1",
    "VIP1_P2",
    "VIP2_P1",
    "VIP2_P2",
    "VIP3_P1",
    "VIP3_P2",
    "VPE_P1",
    "VPE_P2",
    "MMC1",
    "GPU_P1",
    "MMC2",
    "GPU_P2",
    "BB2D_P1",
    "BB2D_P2",
    "GMAC_SW",
    "USB4",
    "USB1",
    "USB2",
    "USB3",
    "SATA",
    "EVE1_P2",
    "EVE2_P2"
};

/* Statistic Collector slave address table */
enum sci_slave_addr sci_slave_addr_table[] = {
    SCI_SLVID_DMM_P1,
    SCI_SLVID_DMM_P2,
    SCI_SLVID_DSP1_SDMA,
    SCI_SLVID_DSP2_SDMA,
    SCI_SLVID_DSS,
    SCI_SLVID_EVE1,
    SCI_SLVID_EVE2,
    SCI_SLVID_BB2D,
    SCI_SLVID_GPMC,
    SCI_SLVID_GPU,
    SCI_SLVID_HOST_CLK1_1,
    SCI_SLVID_HOST_CLK1_2,
    SCI_SLVID_IPU1,
    SCI_SLVID_IPU2,
    SCI_SLVID_IVA_CONFIG,
    SCI_SLVID_IVA_SL2IF,
    SCI_SLVID_L4_CFG,
    SCI_SLVID_L4_PER1_P1,
    SCI_SLVID_L4_PER1_P2,
    SCI_SLVID_L4_PER1_P3,
    SCI_SLVID_L4_PER2_P1,
    SCI_SLVID_L3_INSTR,
    SCI_SLVID_L4_PER2_P3,
    SCI_SLVID_L4_PER3_P1,
    SCI_SLVID_L4_PER3_P2,
    SCI_SLVID_L4_PER3_P3,
    SCI_SLVID_L4_WKUP,
    SCI_SLVID_MCASP1,
    SCI_SLVID_MCASP2,
    SCI_SLVID_MCASP3,
    SCI_SLVID_MMU1,
    SCI_SLVID_MMU2,
    SCI_SLVID_OCMC_RAM1,
    SCI_SLVID_OCMC_RAM2,
    SCI_SLVID_OCMC_RAM3,
    SCI_SLVID_OCMC_ROM,
    SCI_SLVID_PCIE_SS1,
    SCI_SLVID_PCIE_SS2,
    SCI_SLVID_EDMA_TPCC,
    SCI_SLVID_EDMA_TC1,
    SCI_SLVID_EDMA_TC2,
    SCI_SLVID_VCP1,
    SCI_SLVID_VCP2,
    SCI_SLVID_QSPI,
    SCI_SLVID_HOST_CLK2_1,
    SCI_SLVID_DEBUGSS_CT_TBR,
    SCI_SLVID_L4_PER2_P2,
    SCI_SLVID_ALL
};

/* Statistic Collector slave name table.
 * In sci_slave_addr_table order.
 */
const char * sci_slave_name_table[] = {
    "DMM_P1",
    "DMM_P2",
    "DSP1_SDMA",
    "DSP2_SDMA",
    "DSS",
    "EVE1",
    "EVE2",
    "BB2D ",
    "GPMC",
    "GPU ",
    "HOST_CLK1_1",
    "HOST_CLK1_2",
    "IPU1",
    "IPU2",
    "IVA_CONFIG",
    "IVA_SL2IF",
    "L4_CFG",
    "L4_PER1_P1",
    "L4_PER1_P2 ",
    "L4_PER1_P3",
    "L4_PER2_P1",
    "L3_INSTR",
    "L4_PER2S_P3",
    "L4_PER3_P1",
    "L4_PER3_P2",
    "L4_PER3_P3",
    "L4_WKUP",
    "McASP1",
    "McASP2",
    "McASP3",
    "MMU1",
    "MMU2",
    "OCMC_RAM1",
    "OCMC_RAM2",
    "OCMC_RAM3",
    "OCMC_ROM",
    "PCIe_SS1",
    "PCIe_SS2",
    "EDMA_TPCC",
    "EDMA_TC1",
    "EDMA_TC2",
    "VCP1",
    "VCP2",
    "QSPI",
    "HOST_CLK2_1",
    "DEBUGSS_CT_TBR",
    "L4_PER2_P2"
};
