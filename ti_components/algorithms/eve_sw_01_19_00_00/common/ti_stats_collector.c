/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      ti_stats_collector.h.h                                              */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file provides the utilities for programing SoC's Stats             */
/* collector module                                                         */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include "ti_stats_collector.h"

#if !(VCOP_HOST_EMULATION || VCOP_7X_TRANSLATION)
static StatCollectorObj gStatColState;
#endif
void statCollectorInit()
{
#if !(VCOP_HOST_EMULATION || VCOP_7X_TRANSLATION)
    gStatColState.stat0_filter_cnt = 0;
    gStatColState.stat1_filter_cnt = 0;
    gStatColState.stat2_filter_cnt = 0;
    gStatColState.stat3_filter_cnt = 0;
    gStatColState.stat4_filter_cnt = 0;
    gStatColState.stat5_filter_cnt = 0;
    gStatColState.stat6_filter_cnt = 0;
    gStatColState.stat7_filter_cnt = 0;
    gStatColState.stat8_filter_cnt = 0;
    gStatColState.stat9_filter_cnt = 0;
#endif
}

void wr_stat_reg(UInt32 address, UInt32 data)
{
    *(volatile UInt32*)(address) = data;
}

UInt32 rd_stat_reg(UInt32 address)
{
    return *(volatile UInt32*)(address);
}
#define ADD_COUNT 1
UInt32 statCollectorControl(UInt32 inst_name, UInt32 cur_stat_filter_cnt, UInt32 mode)
{
#if !(VCOP_HOST_EMULATION || VCOP_7X_TRANSLATION)

    UInt32 cur_base_address = 0;
    UInt32 cur_event_mux_req;
    UInt32 cur_event_mux_resp;

    switch (inst_name)
    {
    case STATCOL_EMIF1_SYS:
            cur_base_address = stat_coll0_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat0_filter_cnt = gStatColState.stat0_filter_cnt + ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat0_filter_cnt;}
            break;
        case STATCOL_EMIF2_SYS:
            cur_base_address = stat_coll0_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat0_filter_cnt = gStatColState.stat0_filter_cnt + ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat0_filter_cnt;}
            break;
        case STATCOL_MA_MPU_P1:
            cur_base_address = stat_coll0_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat0_filter_cnt = gStatColState.stat0_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat0_filter_cnt;}
            break;
        case STATCOL_MA_MPU_P2:
            cur_base_address = stat_coll0_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat0_filter_cnt = gStatColState.stat0_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat0_filter_cnt;}
            break;
        case STATCOL_MPU1:
            cur_base_address = stat_coll1_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat1_filter_cnt = gStatColState.stat1_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat1_filter_cnt;}
            break;
        case STATCOL_MMU1:
            cur_base_address = stat_coll1_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat1_filter_cnt = gStatColState.stat1_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat1_filter_cnt;}
            break;
        case STATCOL_TPTC_RD1:
            cur_base_address = stat_coll1_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat1_filter_cnt = gStatColState.stat1_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat1_filter_cnt;}
            break;
        case STATCOL_TPTC_WR1:
            cur_base_address = stat_coll1_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat1_filter_cnt = gStatColState.stat1_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat1_filter_cnt;}
            break;
        case STATCOL_TPTC_RD2:
            cur_base_address = stat_coll1_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat1_filter_cnt = gStatColState.stat1_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat1_filter_cnt;}
            break;
        case STATCOL_TPTC_WR2:
            cur_base_address = stat_coll1_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat1_filter_cnt = gStatColState.stat1_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat1_filter_cnt;}
            break;
        case STATCOL_VIP1_P1:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_VIP1_P2:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_VIP2_P1:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_VIP2_P2:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_VIP3_P1:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_VIP3_P2:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_VPE_P1:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_VPE_P2:
            cur_base_address = stat_coll2_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat2_filter_cnt = gStatColState.stat2_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat2_filter_cnt;}
            break;
        case STATCOL_EVE1_TC0:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_EVE1_TC1:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_EVE2_TC0:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_EVE2_TC1:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_EVE3_TC0:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_EVE3_TC1:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_EVE4_TC0:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_EVE4_TC1:
            cur_base_address = stat_coll3_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat3_filter_cnt = gStatColState.stat3_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat3_filter_cnt;}
            break;
        case STATCOL_DSP1_MDMA:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_DSP1_EDMA:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_DSP2_MDMA:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_DSP2_EDMA:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_IVA:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_GPU_P1:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_GPU_P2:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_BB2D_P1:
            cur_base_address = stat_coll4_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat4_filter_cnt = gStatColState.stat4_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat4_filter_cnt;}
            break;
        case STATCOL_DSS:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_CSI2_2:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_MMU2:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_IPU1:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_IPU2:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_DMA_SYSTEM_RD:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_DMA_SYSTEM_WR:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_CSI2_1:
            cur_base_address = stat_coll5_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat5_filter_cnt = gStatColState.stat5_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat5_filter_cnt;}
            break;
        case STATCOL_USB3_SS:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_USB2_SS:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_USB2_ULPI_SS1:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_USB2_ULPI_SS2:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_PCIE_SS1:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_PCIE_SS2:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_DSP1_CFG:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_DSP2_CFG:
            cur_base_address = stat_coll6_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat6_filter_cnt = gStatColState.stat6_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat6_filter_cnt;}
            break;
        case STATCOL_GMAC_SW:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_PRUSS1_P1:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_PRUSS1_P2:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_PRUSS2_P1:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_PRUSS2_P2:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_DMA_CRYPTO_RD:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_DMA_CRYPTO_WR:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_MPU2:
            cur_base_address = stat_coll7_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat7_filter_cnt = gStatColState.stat7_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat7_filter_cnt;}
            break;
        case STATCOL_MMC1:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_MMC2:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_SATA:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_MLBSS:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_BB2D_P2:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_IEEE1500:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_DBG:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_VCP1:
            cur_base_address = stat_coll8_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat8_filter_cnt = gStatColState.stat8_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat8_filter_cnt;}
            break;
        case STATCOL_OCMC_RAM1:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 0;
            cur_event_mux_resp = 1;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
        case STATCOL_OCMC_RAM2:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 2;
            cur_event_mux_resp = 3;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
        case STATCOL_OCMC_RAM3:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 4;
            cur_event_mux_resp = 5;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
        case STATCOL_GPMC:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 6;
            cur_event_mux_resp = 7;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
        case STATCOL_MCASP1:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 8;
            cur_event_mux_resp = 9;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
        case STATCOL_MCASP2:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 10;
            cur_event_mux_resp = 11;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
        case STATCOL_MCASP3:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 12;
            cur_event_mux_resp = 13;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
        case STATCOL_VCP2:
            cur_base_address = stat_coll9_base_address;
            cur_event_mux_req = 14;
            cur_event_mux_resp = 15;
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {gStatColState.stat9_filter_cnt = gStatColState.stat9_filter_cnt +ADD_COUNT;}
            if(mode <=TI_STATCOL_CONFIGURE_RD_WR) {cur_stat_filter_cnt = gStatColState.stat9_filter_cnt;}
            break;
    };
    if(mode <=TI_STATCOL_CONFIGURE_RD_WR)
    {

        if ( cur_stat_filter_cnt > 8 )
        {
            printf("We have exhausted filters/counters.....\n");
        }
        if ( cur_event_mux_resp > 15 )
        {
            printf("Invaild cur_event_mux_resp.....\n");
        }
        // Global Enable Stat Collector
        wr_stat_reg(cur_base_address+0x8,0x1);

        // Soft Enable Stat Collector
        //wr_stat_reg(cur_base_address+0xC,0x1);


        wr_stat_reg(cur_base_address+0x18,0x5);
        // Operation of Stat Collector / RespEvt => Packet
        wr_stat_reg(cur_base_address+0x1C,0x5);


        // Event Sel
        wr_stat_reg(cur_base_address+0x20+4*(cur_stat_filter_cnt-1),cur_event_mux_req);

        // Op is EventInfo
        wr_stat_reg(cur_base_address+0x1FC+(0x158*(cur_stat_filter_cnt-1)),2);

        // Event Info Sel Op -> packet length
        wr_stat_reg(cur_base_address+0x1F8+(0x158*(cur_stat_filter_cnt-1)),0);

        // Filter Global Enable
        wr_stat_reg(cur_base_address+0xAC+(0x158*(cur_stat_filter_cnt-1)),0x1);

        // Filter Enable
        wr_stat_reg(cur_base_address+0xBC+(0x158*(cur_stat_filter_cnt-1)),0x1);

        
        if((mode == TI_STATCOL_CONFIGURE_RD) || (mode == TI_STATCOL_CONFIGURE_WR))
        {
          // Filter MASK READ
          wr_stat_reg(cur_base_address+0xC0+(0x158*(cur_stat_filter_cnt-1)),0x1);
          // Filter MASK Write
          wr_stat_reg(cur_base_address+0xC4+(0x158*(cur_stat_filter_cnt-1)),0x1);

          if(mode == TI_STATCOL_CONFIGURE_RD)
          {// Filter MATCH REAd
            wr_stat_reg(cur_base_address+0xE0+(0x158*(cur_stat_filter_cnt-1)),0x1);
          }

          if(mode == TI_STATCOL_CONFIGURE_WR)
          {// Filter MATCH REAd
            wr_stat_reg(cur_base_address+0xE4+(0x158*(cur_stat_filter_cnt-1)),0x1);
          }
        }
        else
        {
          wr_stat_reg(cur_base_address+0xC0+(0x158*(cur_stat_filter_cnt-1)),0);
          wr_stat_reg(cur_base_address+0xC4+(0x158*(cur_stat_filter_cnt-1)),0);
          wr_stat_reg(cur_base_address+0xE0+(0x158*(cur_stat_filter_cnt-1)),0);
          wr_stat_reg(cur_base_address+0xE4+(0x158*(cur_stat_filter_cnt-1)),0);
        }

        // Manual dump
        wr_stat_reg(cur_base_address+0x54,0x1);
        // use send register to reset counters
    }
    else if(mode == TI_STATCOL_START)
    {
        wr_stat_reg(cur_base_address+0xC,0x1);
    }
    else if(mode == TI_STATCOL_STOP)
    {
        wr_stat_reg(cur_base_address+0xC,0x0);
    }
    else if(mode == TI_READ_STATS)
    {
        cur_stat_filter_cnt = rd_stat_reg(cur_base_address+0x8C+((cur_stat_filter_cnt-1)*4));
    }
    else
    {
        printf("Invalid Control command \n");
    }
#endif
    return cur_stat_filter_cnt;

}

