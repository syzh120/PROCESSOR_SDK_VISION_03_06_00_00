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

#ifndef SCI_CONFIG_DRA7XX_H
#define SCI_CONFIG_DRA7XX_H

#define SC_VER 116
#include "sc_reg.h"

#define SC_INTERFACE_VERSION 1U

#define SC_SDRAM_BASE 0x45001000
#define SC_LAT_0_BASE 0x45002000
#define SC_LAT_1_BASE 0x45003000
#define SC_LAT_2_BASE 0x45004000
#define SC_LAT_3_BASE 0x45005000
#define SC_LAT_4_BASE 0x45006000
#define SC_LAT_5_BASE 0x45007000
#define SC_LAT_6_BASE 0x45008000
#define SC_LAT_7_BASE 0x45009000
#define SC_LAT_8_BASE 0x4500A000

#define SC_SDRAM_NUM_CNTRS 8
#define SC_SDRAM_NUM_PROBES 4

#define SC_LAT_NUM_CNTRS 4
#define SC_LAT_0_NUM_PROBES 6
#define SC_LAT_1_NUM_PROBES 8
#define SC_LAT_2_NUM_PROBES 8     /*4 reserved*/
#define SC_LAT_3_NUM_PROBES 8
#define SC_LAT_4_NUM_PROBES 8    /*2 reserved*/
#define SC_LAT_5_NUM_PROBES 8
#define SC_LAT_6_NUM_PROBES 8    /*6 reserved; Datasheet says 7 probes but lists eight ? */
#define SC_LAT_7_NUM_PROBES 8
#define SC_LAT_8_NUM_PROBES 8
#define SC_MAP_MAX         10
#define SC_MAX_SLAVE          48
#define SC_MAX_MASTER         49
#define SC_MSTR_PROBE         61
#define SC_SDRAM_PROBE        4
#define SC_SDRAM_PROBE        4

/* SDRAM Statistic Collector counter register configuraations */
struct sc_sdram_counters {
    struct sc_sdram_cnt_filter2 cnt0;
    struct sc_sdram_cnt_filter1 cnt1;
    struct sc_sdram_cnt_filter2 cnt2;
    struct sc_sdram_cnt_filter1 cnt3;
    struct sc_sdram_cnt_filter1 cnt4;
    struct sc_sdram_cnt_filter1 cnt5;
    struct sc_sdram_cnt_filter1 cnt6;
    struct sc_sdram_cnt_filter1 cnt7;
};

/* LAT Statistic Collector counter register configurations */
struct sc_lat_counters {
    struct sc_lat_cnt_filter1 cnt[4];
};

/* SDRAM Statistic Collector register configuration */
struct sc_sdram_reg_map {
    sc_sdram_regs regs;
    struct sc_sdram_counters counters;
};

/* LAT Statistic Collector register configuration */
typedef struct sc_lat_reg_map {
    sc_lat_regs regs;
    struct sc_lat_counters counters;
}sc_lat_reg_map_t;

/* Statistic Collector counter element definition*/
typedef struct sc_cnt_elements{
    int32_t num_filters;
    uint32_t cnt_offset;
} sc_cnt_elements_t;

extern const sc_cnt_elements_t sdram_cnt_map[SC_SDRAM_NUM_CNTRS];
extern const sc_cnt_elements_t lat_cnt_map[SC_LAT_NUM_CNTRS];

typedef struct{
    uint32_t probe_id;
    int32_t req_port_num;
    int32_t rsp_port_num;
}sc_probe_element_t;

extern const sc_probe_element_t sc_sdram_probe_map[SC_SDRAM_NUM_PROBES];

typedef enum sc_probe_valid {
    SCI_INVALID_PROBE,
    SCI_VALID_PROBE
}sc_probe_valid_t;

extern const sc_probe_valid_t sc_sdram_no_filter_valid_probe_map[SC_SDRAM_PROBE];
extern const sc_probe_element_t sc_lat_0_probe_map[SC_LAT_0_NUM_PROBES];
extern const sc_probe_element_t sc_lat_1_probe_map[SC_LAT_1_NUM_PROBES];
extern const sc_probe_element_t sc_lat_2_probe_map[SC_LAT_2_NUM_PROBES];
extern const sc_probe_element_t sc_lat_3_probe_map[SC_LAT_3_NUM_PROBES];
extern const sc_probe_element_t sc_lat_4_probe_map[SC_LAT_4_NUM_PROBES];
extern const sc_probe_element_t sc_lat_5_probe_map[SC_LAT_5_NUM_PROBES];
extern const sc_probe_element_t sc_lat_6_probe_map[SC_LAT_6_NUM_PROBES];
extern const sc_probe_element_t sc_lat_7_probe_map[SC_LAT_7_NUM_PROBES];
extern const sc_probe_element_t sc_lat_8_probe_map[SC_LAT_8_NUM_PROBES];

/* Statistic Collector element definition */
enum sc_module_type {SDRAM, MSTR};

typedef struct {
    enum sc_module_type mod_type;
    uint32_t base_addr;
    int32_t mod_size;                   /* In bytes */
    int32_t num_counters;
    const sc_cnt_elements_t * cnt_map;
    uint32_t num_probes;
    const sc_probe_element_t * probe_map;
    const sc_probe_valid_t * sc_no_filter_valid_probe_map;
    uint32_t cnt_overflow_load;
    uint32_t cnt_overflow_lat;
}sc_element_map_t;

/* Statistic Collector element maps */
extern const sc_element_map_t sc_sdram_map;
extern const sc_element_map_t sc_lat_0_map;
extern const sc_element_map_t sc_lat_1_map;
extern const sc_element_map_t sc_lat_2_map;
extern const sc_element_map_t sc_lat_3_map;
extern const sc_element_map_t sc_lat_4_map;
extern const sc_element_map_t sc_lat_5_map;
extern const sc_element_map_t sc_lat_6_map;
extern const sc_element_map_t sc_lat_7_map;
extern const sc_element_map_t sc_lat_8_map;
extern const sc_element_map_t * sc_map[SC_MAP_MAX];

/* Statistic Collector names are in sc_map order */
extern const char * sci_unit_name_table[SC_MAP_MAX];

/* Statistic Collector probe name tables */
extern const char * sci_sdram_probe_name_table[SC_SDRAM_PROBE];

extern const char * sci_mstr_probe_name_table[SC_MSTR_PROBE];

/* Statistic Collector master address table */
extern enum sci_master_addr sci_master_addr_table[SC_MAX_MASTER];

/* Statistic Collector master name table.
 * In sci_master_addr_table order.
 */
extern const char * sci_master_name_table[SC_MAX_MASTER];

/* Statistic Collector slave address table */
extern enum sci_slave_addr sci_slave_addr_table[SC_MAX_SLAVE];

/* Statistic Collector slave name table.
 * In sci_slave_addr_table order.
 */
extern const char * sci_slave_name_table[SC_MAX_SLAVE];
#endif
