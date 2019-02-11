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

#ifndef SC_REG_H
#define SC_REG_H
#include <stdint.h>

typedef volatile uint32_t reg32_t;

#ifdef _SC_VER_1_12

/* Note - The only known use of this statistic collector version is
 *        for OMAP4430. The number of counters in this definition
 *        is hardcoded for the OMAP4430.
 */

#define SC_LIB_FUNC (0x0U)   /* SC Module ID this library is compatible with  */

#define SC_SDRAM_LOAD_CNT_OVERFLOW 65535-32
#define SC_SDRAM_LATENCY_CNT_OVERFLOW 0xFFFFFFFEul-32
#define SC_LAT_LOAD_CNT_OVERFLOW 65535-128
#define SC_LAT_LATENCY_CNT_OVERFLOW  0xFFFFFFFEul-128

/* sdram statistic collector filter definition */
struct sdram_filter_element {
    reg32_t en;
    reg32_t mask_mstaddr;
    reg32_t mask_rd;
    reg32_t mask_wr;
    reg32_t mask_err;
    reg32_t mask_reserved;
    reg32_t mask_userinfo;
    reg32_t match_mstaddr;
    reg32_t match_rd;
    reg32_t match_wr;
    reg32_t match_err;
    reg32_t match_reserved;
    reg32_t match_userinfo;
};

/* sdram statistic collector counter with zero filter elements */
struct sc_sdram_cnt_filter0 {
     reg32_t globalen;
     reg32_t op_threshold_minval;
     reg32_t op_threshold_maxval;
     reg32_t op_evt_info_sel;
     reg32_t op_sel;
     reg32_t reserved;
};

/* sdram statistic collector counter with one filter element */
struct sc_sdram_cnt_filter1 {
    reg32_t globalen;
    struct sdram_filter_element filter[1];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved;
};

/* sdram statistic collector counter with two filter elements */
struct sc_sdram_cnt_filter2 {
    reg32_t globalen;
    struct sdram_filter_element filter[2];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved1;
};

/* lat statistic collector filter definition */
struct lat_filter_element {
    reg32_t en;
    reg32_t mask_mstaddr;
    reg32_t mask_requserinfo;
    reg32_t mask_rspuserinfo;
    reg32_t mask_rd;
    reg32_t mask_wr;
    reg32_t mask_err;
    reg32_t mask_slvaddr;
    reg32_t match_mstaddr;
    reg32_t match_requserinfo;
    reg32_t match_rspuserinfo;
    reg32_t match_rd;
    reg32_t match_wr;
    reg32_t match_err;
    reg32_t match_slvaddr;
};

/* lat statistic collector counter with one filter element */
struct sc_lat_cnt_filter1 {
    reg32_t globalen;
    struct lat_filter_element filter[1];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved4;
};

/* sdram statistic collector filter definition
 * Note: less the counter configuration which is device specific
 */
struct sc_reg_map_sdram {
    reg32_t stdhosthdr_core;
    reg32_t stdhosthdr_version;
    reg32_t en;
    reg32_t soften;
    reg32_t trigen;
    reg32_t reqevt;
    reg32_t rspevt;
    reg32_t evtmux_sel[5];
    reg32_t dump_identifier;
    reg32_t dump_collecttime;
    reg32_t dump_slvaddr;
    reg32_t dump_mstaddr;
    reg32_t dump_slvofs;
    reg32_t dump_manual;
    reg32_t dump_send;
};

/* lat statistic collector filter definition
 * Note: less the counter configuration which is device specific
 */
struct sc_reg_map_lat {
    reg32_t stdhosthdr_core;
    reg32_t stdhosthdr_version;
    reg32_t en;
    reg32_t soften;
    reg32_t trigen;
    reg32_t reqevt;
    reg32_t rspevt;
    reg32_t evtmux_sel[4];
    reg32_t dump_identifier;
    reg32_t dump_collecttime;
    reg32_t dump_slvaddr;
    reg32_t dump_mstaddr;
    reg32_t dump_slvofs;
    reg32_t dump_manual;
    reg32_t dump_send;
};

typedef struct sc_reg_map_sdram sc_sdram_regs;
typedef struct sc_reg_map_lat sc_lat_regs;

#endif

#ifdef _SC_VER_1_16

/* Note - This version of the statistic collector has space for a maximum of
 *        8 counters and 2 filters per counter, thus all register offsets
 *        are hardcoded, even though the number of actual counters and filters
 *        per counter are variable.
 */

#define SC_LIB_FUNC (0x1U)   /* SC Module ID this library is compatible with  */

#define SC_SDRAM_LOAD_CNT_OVERFLOW 0xFFFFFFFFul
#define SC_SDRAM_LATENCY_CNT_OVERFLOW 0xFFFFFFFFul
#define SC_LAT_LOAD_CNT_OVERFLOW 0xFFFFFFFFul
#define SC_LAT_LATENCY_CNT_OVERFLOW  0xFFFFFFFFul

/* sdram statistic collector filter definition */
struct sdram_filter_element {
    reg32_t en;
    reg32_t mask_rd;
    reg32_t mask_wr;
    reg32_t mask_mstaddr;
    reg32_t reserved0;
    reg32_t mask_err;
    reg32_t mask_userinfo;
    reg32_t reserved1;
    reg32_t reserved2;
    reg32_t match_rd;
    reg32_t match_wr;
    reg32_t match_mstaddr;
    reg32_t reserved3;
    reg32_t match_err;
    reg32_t match_userinfo;
    reg32_t reserved4;
    reg32_t reserved5;
};

/* sdram statistic collector counter with zero filter elements */
struct sc_sdram_cnt_filter0 {
    reg32_t globalen;
    reg32_t addrmin;
    reg32_t addrmax;
    reg32_t addren;
    reg32_t reserved0[77];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved;
};

/* sdram statistic collector counter with one filter element */
struct sc_sdram_cnt_filter1 {
    reg32_t globalen;
    reg32_t addrmin;
    reg32_t addrmax;
    reg32_t addren;
    struct sdram_filter_element filter[1];
    reg32_t reserved0[60];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved;
};

/* sdram statistic collector counter with two filter elements */
struct sc_sdram_cnt_filter2 {
    reg32_t globalen;
    reg32_t addrmin;
    reg32_t addrmax;
    reg32_t addren;
    struct sdram_filter_element filter[2];
    reg32_t reserved0[43];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved1;
};

/* sdram statistic collector counter with three filter elements */
struct sc_sdram_cnt_filter3 {
    reg32_t globalen;
    reg32_t addrmin;
    reg32_t addrmax;
    reg32_t addren;
    struct sdram_filter_element filter[3];
    reg32_t reserved0[26];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved1;
};

/* sdram statistic collector counter with four filter elements */
struct sc_sdram_cnt_filter4 {
    reg32_t globalen;
    reg32_t addrmin;
    reg32_t addrmax;
    reg32_t addren;
    struct sdram_filter_element filter[4];
    reg32_t reserved0[9];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved1;
};


/* lat statistic collector filter definition */
struct lat_filter_element {
    reg32_t en;
    reg32_t mask_rd;
    reg32_t mask_wr;
    reg32_t mask_mstaddr;
    reg32_t mask_slvaddr;
    reg32_t mask_err;
    reg32_t mask_requserinfo;
    reg32_t mask_rspuserinfo;
    reg32_t reserved0;
    reg32_t match_rd;
    reg32_t match_wr;
    reg32_t match_mstaddr;
    reg32_t match_slvaddr;
    reg32_t match_err;
    reg32_t match_requserinfo;
    reg32_t match_rspuserinfo;
    reg32_t reserved1;
};

/* lat statistic collector counter with zero filter elements */
struct sc_lat_cnt_filter0 {
    reg32_t globalen;
    reg32_t reserved0;
    reg32_t reserved1;
    reg32_t reserved2;
    reg32_t reserved3[77];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved4;
 };

/* lat statistic collector counter with one filter elements */
struct sc_lat_cnt_filter1 {
    reg32_t globalen;
    reg32_t reserved0;
    reg32_t reserved1;
    reg32_t reserved2;
    struct lat_filter_element filter[1];
    reg32_t reserved3[60];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved4;
 };

/* lat statistic collector counter with two filter elements */
 struct sc_lat_cnt_filter2 {
    reg32_t globalen;
    reg32_t reserved0;
    reg32_t reserved1;
    reg32_t reserved2;
    struct sdram_filter_element filter[2];
    reg32_t reserved3[43];
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved4;
};

/* lat statistic collector counter with three filter elements */
  struct sc_lat_cnt_filter3 {
     reg32_t globalen;
     reg32_t reserved0;
     reg32_t reserved1;
     reg32_t reserved2;
     struct sdram_filter_element filter[3];
     reg32_t reserved3[26];
     reg32_t op_threshold_minval;
     reg32_t op_threshold_maxval;
     reg32_t op_evt_info_sel;
     reg32_t op_sel;
     reg32_t reserved4;
 };

  /* lat statistic collector counter with four filter elements */
    struct sc_lat_cnt_filter4 {
       reg32_t globalen;
       reg32_t reserved0;
       reg32_t reserved1;
       reg32_t reserved2;
       struct sdram_filter_element filter[4];
       reg32_t reserved3[9];
       reg32_t op_threshold_minval;
       reg32_t op_threshold_maxval;
       reg32_t op_evt_info_sel;
       reg32_t op_sel;
       reg32_t reserved4;
   };

 /* sdram statistic collector filter definition
  * Note: less the counter configuration which is device specific
  */
struct sc_reg_map {
    reg32_t stdhosthdr_core;
    reg32_t stdhosthdr_version;
    reg32_t en;
    reg32_t soften;
    reg32_t ignore_suspend;
    reg32_t trigen;
    reg32_t reqevt;
    reg32_t rspevt;
    reg32_t evtmux_sel[8];
    reg32_t dump_identifier;
    reg32_t dump_collecttime;
    reg32_t dump_slvaddr;
    reg32_t dump_mstaddr;
    reg32_t dump_slvofs;
    reg32_t dump_manual;
    reg32_t dump_send;
    reg32_t dump_disable;
    reg32_t dump_alarm_trig;
    reg32_t dump_alarm_minval;
    reg32_t dump_alarm_maxval;
    reg32_t dump_alarm_mode[8];
    reg32_t dump_cnt[8];
};

typedef struct sc_reg_map sc_sdram_regs;
typedef struct sc_reg_map sc_lat_regs;

#endif
#endif
