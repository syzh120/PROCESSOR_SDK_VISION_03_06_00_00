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

#include "sci_config_tda3x.h"
#include <src/rtos/utils_common/include/sci_tda3x.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* Statistic Collector counter maps */

/* MISRA.CAST.PTR_TO_INT
 * Rule 11.3: Cast between a pointer and an integral type
 * KW State: Defer -> Waiver -> Case by case
 *
 */

sc_cnt_elements_t sc_lat_1_cnt_map[] = {
    {1, (uint32_t)(&((struct sc_lat_1_reg_map *)0)->counters.cnt[0])},
    {1, (uint32_t)(&((struct sc_lat_1_reg_map *)0)->counters.cnt[1])},
    {1, (uint32_t)(&((struct sc_lat_1_reg_map *)0)->counters.cnt[2])},
    {1, (uint32_t)(&((struct sc_lat_1_reg_map *)0)->counters.cnt[3])}
};

sc_cnt_elements_t sc_lat_2_cnt_map[] = {
    {1, (uint32_t)(&((struct sc_lat_2_reg_map *)0)->counters.cnt[0])},
    {1, (uint32_t)(&((struct sc_lat_2_reg_map *)0)->counters.cnt[1])},
    {1, (uint32_t)(&((struct sc_lat_2_reg_map *)0)->counters.cnt[2])},
    {1, (uint32_t)(&((struct sc_lat_2_reg_map *)0)->counters.cnt[3])}
};

sc_cnt_elements_t sc_lat_3_cnt_map[] = {
    {1, (uint32_t)(&((struct sc_lat_3_reg_map *)0)->counters.cnt[0])},
    {1, (uint32_t)(&((struct sc_lat_3_reg_map *)0)->counters.cnt[1])},
    {1, (uint32_t)(&((struct sc_lat_3_reg_map *)0)->counters.cnt[2])},
    {1, (uint32_t)(&((struct sc_lat_3_reg_map *)0)->counters.cnt[3])}
};

sc_cnt_elements_t sc_lat_4_cnt_map[] = {
    {1, (uint32_t)(&((struct sc_lat_4_reg_map *)0)->counters.cnt[0])},
    {1, (uint32_t)(&((struct sc_lat_4_reg_map *)0)->counters.cnt[1])},
    {1, (uint32_t)(&((struct sc_lat_4_reg_map *)0)->counters.cnt[2])},
    {1, (uint32_t)(&((struct sc_lat_4_reg_map *)0)->counters.cnt[3])}
};

/* Statistic Collector probe element maps */
sc_probe_element_t sc_lat_1_probe_map[] = {
{SCI_EMIF_SYS, 0, 1},
{SCI_IPU, 2, 3},
{SCI_DSP1_MDMA, 4, 5},
{SCI_DSP2_MDMA, 6, 7},
{SCI_GMAC_SW, 8, 9},
{SCI_ISS_NRT1, 10, 11}
};

sc_probe_element_t sc_lat_2_probe_map[] = {
{SCI_DSS, 0, 1},
{SCI_MMU, 2, 3},
{SCI_EDMA_TC0_RD, 4, 5},
{SCI_EDMA_TC0_WR, 6, 7},
{SCI_DSP2_CFG, 8, 9},
{SCI_DSP2_EDMA, 10, 11}
};

sc_probe_element_t sc_lat_3_probe_map[] = {
{SCI_VIP_P1, 0, 1},
{SCI_VIP_P2, 2, 3},
{SCI_ISS_RT, 4, 5},
{SCI_ISS_NRT2, 6, 7},
{SCI_OCMC_RAM, 8, 9},
{SCI_DSP1_CFG, 10, 11},
{SCI_DSP1_EDMA, 12, 13}
};

sc_probe_element_t sc_lat_4_probe_map[] = {
{SCI_EVE_P1, 0, 1},
{SCI_EVE_P2, 2, 3},
{SCI_GPMC, 6, 7},
{SCI_MCASP, 8, 9},
{SCI_EDMA_TC1_RD, 10, 11},
{SCI_EDMA_TC1_WR, 12, 13}
};

/* Statistic Collector element maps */
const sc_element_map_t sc_lat_1_map = {
        MSTR,
        SC_LAT1_BASE,
        sizeof(struct sc_lat_1_reg_map),
        SC_LAT1_NUM_CNTRS,
        sc_lat_1_cnt_map,
        SC_LAT1_NUM_PROBES,
        sc_lat_1_probe_map,
        NULL,
        SC_LAT_LOAD_CNT_OVERFLOW,
        SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_2_map = {
        MSTR,
        SC_LAT2_BASE,
        sizeof(struct sc_lat_2_reg_map),
        SC_LAT2_NUM_CNTRS,
        sc_lat_2_cnt_map,
        SC_LAT2_NUM_PROBES,
        sc_lat_2_probe_map,
        NULL,
        SC_LAT_LOAD_CNT_OVERFLOW,
        SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_3_map = {
        MSTR,
        SC_LAT3_BASE,
        sizeof(struct sc_lat_3_reg_map),
        SC_LAT3_NUM_CNTRS,
        sc_lat_3_cnt_map,
        SC_LAT3_NUM_PROBES,
        sc_lat_3_probe_map,
        NULL,
        SC_LAT_LOAD_CNT_OVERFLOW,
        SC_LAT_LATENCY_CNT_OVERFLOW
};

const sc_element_map_t sc_lat_4_map = {
        MSTR,
        SC_LAT4_BASE,
        sizeof(struct sc_lat_4_reg_map),
        SC_LAT4_NUM_CNTRS,
        sc_lat_4_cnt_map,
        SC_LAT4_NUM_PROBES,
        sc_lat_4_probe_map,
        NULL,
        SC_LAT_LOAD_CNT_OVERFLOW,
        SC_LAT_LATENCY_CNT_OVERFLOW
};


const sc_element_map_t * sc_map[SC_MAP_MAX] = {
&sc_lat_1_map,
&sc_lat_2_map,
&sc_lat_3_map,
&sc_lat_4_map
 };

 /* Statistic Collector names are in sc_map order */
const char * sci_unit_name_table[] = {
    "LAT0",
    "LAT1",
    "LAT2",
    "LAT3"
};


/* Statistic Collector probe name tables */

const char * sci_mstr_probe_name_table[] = {
         "EMIF_SYS",
         "IPU",
         "DSP1_MDMA",
         "DSP2_MDMA",
         "GMAC_SW",
         "ISS_NRT1",
         "DSS",
         "MMU",
         "EDMA_TC0_RD",
         "EDMA_TC0_WR",
         "DSP2_CFG",
         "DSP2_EDMA",
         "VIP_P1",
         "VIP_P2",
         "ISS_RT",
         "ISS_NRT2",
         "OCMC_RAM",
         "DSP1_CFG",
         "DSP1_EDMA",
         "EVE_P1",
         "EVE_P2",
         "GPMC",
         "MCASP",
         "EDMA_TC1_RD",
         "EDMA_TC1_WR"
};

const char * sci_sdram_probe_name_table[1U]; /* not Implemented */

/* Statistic Collector master address table */
enum sci_master_addr sci_master_addr_table[] = {
        SCI_MSTID_DSS,
        SCI_MSTID_VIP_P1,
        SCI_MSTID_VIP_P2,
        SCI_MSTID_ISS_RT,
        SCI_MSTID_ISS_NRT1,
        SCI_MSTID_ISS_NRT2,
        SCI_MSTID_IPU,
        SCI_MSTID_EVE_P1,
        SCI_MSTID_EVE_P2,
        SCI_MSTID_DSP1_MDMA,
        SCI_MSTID_DSP1_EDMA,
        SCI_MSTID_DSP1_CFG,
        SCI_MSTID_DSP2_MDMA,
        SCI_MSTID_DSP2_EDMA,
        SCI_MSTID_DSP2_CFG,
        SCI_MSTID_MMU,
        SCI_MSTID_EDMA_TC0_WR,
        SCI_MSTID_EDMA_TC0_RD,
        SCI_MSTID_EDMA_TC1_WR,
        SCI_MSTID_EDMA_TC1_RD,
        SCI_MSTID_GMAC_SW,
        SCI_MSTID_IEEE1500_2_OCP,
        SCI_MSTID_CS_DAP,
        SCI_MSTID_EVE1_SW_INSTR_ARP32,
        SCI_MSTID_EVE1_HW_INSTR_SMSET
};

/* Statistic Collector master name table.
        In sci_master_addr_table order.
       */
const char * sci_master_name_table[] = {
        "DSS",
        "VIP_P1",
        "VIP_P2",
        "ISS_RT",
        "ISS_NRT1",
        "ISS_NRT2",
        "IPU",
        "EVE_P1",
        "EVE_P2",
        "DSP1_MDMA",
        "DSP1_EDMA",
        "DSP1_CFG",
        "DSP2_MDMA",
        "DSP2_EDMA",
        "DSP2_CFG",
        "MMU",
        "EDMA_TC0_WR",
        "EDMA_TC0_RD",
        "EDMA_TC1_WR",
        "EDMA_TC1_RD",
        "GMAC_SW",
        "IEEE1500_2_OCP",
        "CS_DAP",
        "EVE1_SW_INSTR_ARP32",
        "EVE1_HW_INSTR_SMSET"
};

/* Statistic Collector slave address table */
enum sci_slave_addr sci_slave_addr_table[] = {
        SCI_SLVID_CRC,
        SCI_SLVID_DEBUGSS_CT_TBR,
        SCI_SLVID_DSP1_SDMA,
        SCI_SLVID_DSP2_SDMA,
        SCI_SLVID_DSS,
        SCI_SLVID_EMIF_SYS,
        SCI_SLVID_EVE,
        SCI_SLVID_GPMC,
        SCI_SLVID_IPU,
        SCI_SLVID_L3_INSTR,
        SCI_SLVID_L4_CFG,
        SCI_SLVID_L4_PER1_P1,
        SCI_SLVID_L4_PER1_P2,
        SCI_SLVID_L4_PER1_P3,
        SCI_SLVID_L4_PER2_P1,
        SCI_SLVID_L4_PER2_P2,
        SCI_SLVID_L4_PER2_P3,
        SCI_SLVID_L4_PER3_P1,
        SCI_SLVID_L4_PER3_P2,
        SCI_SLVID_L4_PER3_P3,
        SCI_SLVID_L4_WKUP,
        SCI_SLVID_MCASP,
        SCI_SLVID_MMU,
        SCI_SLVID_OCMC_RAM,
        SCI_SLVID_OCMC_ROM,
        SCI_SLVID_QSPI,
        SCI_SLVID_TESOC,
        SCI_SLVID_EDMA_TPCC,
        SCI_SLVID_EDMA_TC0,
        SCI_SLVID_EDMA_TC1,
        SCI_SLVID_HOST_CLK1_1,
        SCI_SLVID_HOST_CLK1_2,
        SCI_SLVID_HOST_CLK2_1
};

/* Statistic Collector slave name table.
       In sci_slave_addr_table order.
       */
const char * sci_slave_name_table[] = {
        "CRC",
        "DEBUGSS_CT_TBR",
        "DSP1_SDMA",
        "DSP2_SDMA",
        "DSS",
        "EMIF_SYS",
        "EVE",
        "GPMC",
        "IPU",
        "L3_INSTR",
        "L4_CFG",
        "L4_PER1_P1",
        "L4_PER1_P2",
        "L4_PER1_P3",
        "L4_PER2_P1",
        "L4_PER2_P2",
        "L4_PER2_P3",
        "L4_PER3_P1",
        "L4_PER3_P2",
        "L4_PER3_P3",
        "L4_WKUP",
        "MCASP",
        "MMU",
        "OCMC_RAM",
        "OCMC_ROM",
        "QSPI",
        "TESOC",
        "EDMA_TPCC",
        "EDMA_TC0",
        "EDMA_TC1",
        "HOST_CLK1_1",
        "HOST_CLK1_2",
        "HOST_CLK2_1"
};

