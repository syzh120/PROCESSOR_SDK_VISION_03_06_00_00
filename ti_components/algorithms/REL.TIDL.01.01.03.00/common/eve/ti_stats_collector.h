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
/*      ti_stats_collector.h                                                */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file provides the interface for programing SoC's Stats             */
/* collector module                                                         */
/*                                                                          */
/*==========================================================================*/

#ifndef TI_INTERCONNCET_STATS_COLLLECTOR
#define TI_INTERCONNCET_STATS_COLLLECTOR

#define stat_coll0_base_address (0x45001000)
#define stat_coll1_base_address (0x45002000)
#define stat_coll2_base_address (0x45003000)
#define stat_coll3_base_address (0x45004000)
#define stat_coll4_base_address (0x45005000)
#define stat_coll5_base_address (0x45006000)
#define stat_coll6_base_address (0x45007000)
#define stat_coll7_base_address (0x45008000)
#define stat_coll8_base_address (0x45009000)
#define stat_coll9_base_address (0x4500a000)

typedef unsigned int UInt32;

typedef enum
{
    STATCOL_EMIF1_SYS,
    STATCOL_EMIF2_SYS,
    STATCOL_MA_MPU_P1,
    STATCOL_MA_MPU_P2,
    STATCOL_MPU1,
    STATCOL_MMU1,
    STATCOL_TPTC_RD1,
    STATCOL_TPTC_WR1,
    STATCOL_TPTC_RD2,
    STATCOL_TPTC_WR2,
    STATCOL_VIP1_P1,
    STATCOL_VIP1_P2,
    STATCOL_VIP2_P1,
    STATCOL_VIP2_P2,
    STATCOL_VIP3_P1,
    STATCOL_VIP3_P2,
    STATCOL_VPE_P1,
    STATCOL_VPE_P2,
    STATCOL_EVE1_TC0,
    STATCOL_EVE1_TC1,
    STATCOL_EVE2_TC0,
    STATCOL_EVE2_TC1,
    STATCOL_EVE3_TC0,
    STATCOL_EVE3_TC1,
    STATCOL_EVE4_TC0,
    STATCOL_EVE4_TC1,
    STATCOL_DSP1_MDMA,
    STATCOL_DSP1_EDMA,
    STATCOL_DSP2_MDMA,
    STATCOL_DSP2_EDMA,
    STATCOL_IVA,
    STATCOL_GPU_P1,
    STATCOL_GPU_P2,
    STATCOL_BB2D_P1,
    STATCOL_DSS,
    STATCOL_CSI2_2,
    STATCOL_MMU2,
    STATCOL_IPU1,
    STATCOL_IPU2,
    STATCOL_DMA_SYSTEM_RD,
    STATCOL_DMA_SYSTEM_WR,
    STATCOL_CSI2_1,
    STATCOL_USB3_SS,
    STATCOL_USB2_SS,
    STATCOL_USB2_ULPI_SS1,
    STATCOL_USB2_ULPI_SS2,
    STATCOL_PCIE_SS1,
    STATCOL_PCIE_SS2,
    STATCOL_DSP1_CFG,
    STATCOL_DSP2_CFG,
    STATCOL_GMAC_SW,
    STATCOL_PRUSS1_P1,
    STATCOL_PRUSS1_P2,
    STATCOL_PRUSS2_P1,
    STATCOL_PRUSS2_P2,
    STATCOL_DMA_CRYPTO_RD,
    STATCOL_DMA_CRYPTO_WR,
    STATCOL_MPU2,
    STATCOL_MMC1,
    STATCOL_MMC2,
    STATCOL_SATA,
    STATCOL_MLBSS,
    STATCOL_BB2D_P2,
    STATCOL_IEEE1500,
    STATCOL_DBG,
    STATCOL_VCP1,
    STATCOL_OCMC_RAM1,
    STATCOL_OCMC_RAM2,
    STATCOL_OCMC_RAM3,
    STATCOL_GPMC,
    STATCOL_MCASP1,
    STATCOL_MCASP2,
    STATCOL_MCASP3,
    STATCOL_VCP2
} STATCOL_ID;

typedef struct
{
    UInt32 stat0_filter_cnt;
    UInt32 stat1_filter_cnt;
    UInt32 stat2_filter_cnt;
    UInt32 stat3_filter_cnt;
    UInt32 stat4_filter_cnt;
    UInt32 stat5_filter_cnt;
    UInt32 stat6_filter_cnt;
    UInt32 stat7_filter_cnt;
    UInt32 stat8_filter_cnt;
    UInt32 stat9_filter_cnt;
} StatCollectorObj;

typedef enum
{
  TI_STATCOL_CONFIGURE_RD,
  TI_STATCOL_CONFIGURE_WR,
  TI_STATCOL_CONFIGURE_RD_WR,
  TI_STATCOL_START,
  TI_STATCOL_STOP,
  TI_READ_STATS
}statColControlCmd;

void statCollectorInit();
UInt32 statCollectorControl(UInt32 inst_name, UInt32 cur_stat_filter_cnt, UInt32 mode);


#endif/* TI_INTERCONNCET_STATS_COLLLECTOR */
