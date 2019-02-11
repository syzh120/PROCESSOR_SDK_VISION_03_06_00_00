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

#ifndef SCI_TDA3x_H
#define SCI_TDA3x_H

/*! \file sci_tda3x.h
    DRA7xx device specific CPTLib definitions
*/

/*! \enum sci_probeid_sdram
    Probe selection for sdram statistic collectors. (NOT IMPLEMENTED)
*/
enum sci_probeid_sdram {
    SCI_NOT_IMPLEMENTED

};

/*! \enum sci_probeid_mstr
    Probe selection for master statistic collectors.
    Note: Order for probe_name_table indexing - not probe ids.
    For probe_ids a probe_map table is used (see sci_config_tda3x.h).
*/
enum sci_probeid_mstr {
                      SCI_EMIF_SYS,           /*!< EMIF */
                        SCI_IPU,                /*!< IPU */
                        SCI_DSP1_MDMA,          /*!< DSP1 MDMA */
                        SCI_DSP2_MDMA,          /*!< DSP2 MDMA */
                        SCI_GMAC_SW,            /*!< GMAC SW */
                        SCI_ISS_NRT1,           /*!< ISS NRT1 */
                        SCI_DSS,                /*!< DSS */
                        SCI_MMU,                /*!< MMU */
                        SCI_EDMA_TC0_RD,        /*!< EDMA TC0 RD */
                        SCI_EDMA_TC0_WR,        /*!< EDMA TC0 WR */
                        SCI_DSP2_CFG,           /*!< DSP2 CFG */
                        SCI_DSP2_EDMA,          /*!< DSP2 EDMA */
                        SCI_VIP_P1,             /*!< VIP P1 */
                        SCI_VIP_P2,             /*!< VIP P2 */
                        SCI_ISS_RT,             /*!< ISS RT */
                        SCI_ISS_NRT2,           /*!< ISS NRT2 */
                        SCI_OCMC_RAM,           /*!< OCMC RAM */
                        SCI_DSP1_CFG,           /*!< DSP1 CFG */
                        SCI_DSP1_EDMA,          /*!< DSP1 EDMA */
                        SCI_EVE_P1,             /*!< EVE P1 */
                        SCI_EVE_P2,             /*!< EVE P2 */
                        SCI_GPMC,               /*!< GPMC */
                        SCI_MCASP,              /*!< MCASP */
                        SCI_EDMA_TC1_RD,        /*!< EDMA TC1 RD */
                        SCI_EDMA_TC1_WR         /*!< EDMA TC1 WR */
          };

/*! \enum sci_master_addr
     Master address enumerations.
*/
enum sci_master_addr {
             SCI_MSTID_DSS=0x80,                 /*!< DSS */
              SCI_MSTID_VIP_P1=0x90,              /*!< VIP P1 */
              SCI_MSTID_VIP_P2=0x92,              /*!< VIP P1 */
              SCI_MSTID_ISS_RT=0xC0,              /*!< ISS RT */
              SCI_MSTID_ISS_NRT1=0xC4,            /*!< ISS NRT1 */
              SCI_MSTID_ISS_NRT2=0xC8,            /*!< ISS NRT2 */
              SCI_MSTID_IPU=0x60,                 /*!< IPU */
              SCI_MSTID_EVE_P1=0x42,              /*!< EVE P1 */
              SCI_MSTID_EVE_P2=0xD2,              /*!< EVE P2 */
              SCI_MSTID_DSP1_MDMA=0x20,           /*!< DSP1 MDMA */
              SCI_MSTID_DSP1_EDMA=0x28,           /*!< DSP1 EDMA */
              SCI_MSTID_DSP1_CFG=0x24,            /*!< DSP1 CFG */
              SCI_MSTID_DSP2_MDMA=0x34,           /*!< DSP2 MDMA */
              SCI_MSTID_DSP2_EDMA=0x2C,           /*!< DSP2 EDMA */
              SCI_MSTID_DSP2_CFG=0x30,            /*!< DSP2 CFG */
              SCI_MSTID_MMU=0x86,                 /*!< MMU */
              SCI_MSTID_EDMA_TC0_WR=0x70,         /*!< EDMA TC0 WR */
              SCI_MSTID_EDMA_TC0_RD=0x72,         /*!< EDMA TC0 RD */
              SCI_MSTID_EDMA_TC1_WR=0x74,         /*!< EDMA TC1 WR */
              SCI_MSTID_EDMA_TC1_RD=0x76,         /*!< EDMA TC1 RD */
              SCI_MSTID_GMAC_SW=0xAC,             /*!< GMAC SW */
              SCI_MSTID_IEEE1500_2_OCP=0x14,      /*!< IEEE1500 2 OCP */
              SCI_MSTID_CS_DAP=0x10,              /*!< DAP */
              SCI_MSTID_EVE1_SW_INSTR_ARP32=0x42, /*!< EVE1 SW INSTR ARP32 */
              SCI_MSTID_EVE1_HW_INSTR_SMSET=0xD2, /*!< EVE1 SW INSTR SMSET */
              SCI_MASTID_ALL=0xFF           /*!< All masters */
};

/*! \enum sci_slave_addr
    Slave address enumerations.
*/
enum sci_slave_addr {
            SCI_SLVID_EMIF_SYS=0x2,             /*!< EMIF */
            SCI_SLVID_TESOC=0x3,                /*!< TESOC */
              SCI_SLVID_DSP1_SDMA=0x4,            /*!< DSP1 SDMA */
              SCI_SLVID_DSP2_SDMA=0x5,            /*!< DSP2 SDMA */
              SCI_SLVID_DSS=0x6,                  /*!< DSS */
              SCI_SLVID_EVE=0x7,                  /*!< EVE */
            SCI_SLVID_CRC=0x8,                  /*!< CRC */
              SCI_SLVID_GPMC=0xC,                 /*!< GPMC */
              SCI_SLVID_HOST_CLK1_1=0xE,          /*!< HOST CLK1 1 */
              SCI_SLVID_HOST_CLK1_2=0xF,          /*!< HOST CLK1 2 */
              SCI_SLVID_IPU=0x10,                 /*!< IPU */
              SCI_SLVID_L4_CFG=0x14,              /*!< L4 CFG */
              SCI_SLVID_L4_PER1_P1=0x15,          /*!< L4 PER1 P1 */
              SCI_SLVID_L4_PER1_P2=0x16,          /*!< L4 PER1 P2 */
              SCI_SLVID_L4_PER1_P3=0x17,          /*!< L4 PER1 P3 */
              SCI_SLVID_L4_PER2_P1=0x18,          /*!< L4 PER2 P1 */
            SCI_SLVID_L3_INSTR=0x19,            /*!< L3 INSTR */
              SCI_SLVID_L4_PER2_P3=0x1A,          /*!< L4 PER2 P3 */
              SCI_SLVID_L4_PER3_P1=0x1B,          /*!< L4 PER3 P1 */
              SCI_SLVID_L4_PER3_P2=0x1C,          /*!< L4 PER3 P2 */
            SCI_SLVID_L4_PER3_P3=0x1D,          /*!< L4 PER3 P3 */
              SCI_SLVID_L4_WKUP=0x1E,             /*!< L4 WKUP */
              SCI_SLVID_MCASP=0x1F,               /*!< MCASP */
              SCI_SLVID_MMU=0x22,                 /*!< MMU */
              SCI_SLVID_OCMC_RAM=0x24,            /*!< OCMC RAM */
              SCI_SLVID_OCMC_ROM=0x27,            /*!< OCMC ROM */
              SCI_SLVID_EDMA_TPCC=0x30,           /*!< EDMA TPCC */
              SCI_SLVID_EDMA_TC0=0x31,            /*!< EDMA TC0 */
              SCI_SLVID_EDMA_TC1=0x32,            /*!< EDMA TC1 */
            SCI_SLVID_QSPI=0x39,                /*!< QSPI */
            SCI_SLVID_HOST_CLK2_1=0x40,         /*!< HOST CLK2 1 */
            SCI_SLVID_DEBUGSS_CT_TBR=0x41,      /*!< DEBUGSS CT TBR */
            SCI_SLVID_L4_PER2_P2=0x42,          /*!< L4 PER2 P2 */
              SCI_SLVID_ALL=0x7FFFFFFF          /*!< All slaves */
};

#endif
