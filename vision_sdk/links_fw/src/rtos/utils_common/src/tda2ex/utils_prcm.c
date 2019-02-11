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

/**
 *******************************************************************************
 * \file utils_prcm.c
 *
 * \brief  Used only when M4 binary is loaded by linux on A15
 *
 * \version 0.0 (Jun 2013) : [YM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <include/link_api/system.h>
#include <xdc/runtime/System.h>



#define WR_MEM_32(addr, data)   *(volatile unsigned int*)(addr) =(unsigned int)(data)
#define RD_MEM_32(addr)         *(volatile unsigned int*)(addr)


/* DPLL Definitions */
#define CM_CLKMODE_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS)
#define CM_IDLEST_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x04)
#define CM_AUTOIDLE_DPLL(DPLL_BASE_ADDRESS)     RD_MEM_32(DPLL_BASE_ADDRESS + 0x08)
#define CM_CLKSEL_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x0C)
#define CM_DIV_M2_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x10)
#define CM_DIV_M3_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x14)
#define CM_DIV_H11_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x18)
#define CM_DIV_H12_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x1C)
#define CM_DIV_H13_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x20)
#define CM_DIV_H14_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x24)
#define CM_DIV_H21_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x30)
#define CM_DIV_H22_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x34)
#define CM_DIV_H23_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x38)
#define CM_DIV_H24_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x3C)


/* Instance Base Addresses */
#define CTRL_MODULE_CORE    0x4a002000
#define CKGEN_CM_CORE_AON   0x4a005100
#define MPU_CM_CORE_AON     0x4a005300
#define DSP1_CM_CORE_AON    0x4a005400
#define IPU_CM_CORE_AON     0x4a005500
#define RTC_CM_CORE_AON     0x4a005740
#define VPE_CM_CORE_AON     0x4a005760
#define CKGEN_CM_CORE       0x4a008100
#define COREAON_CM_CORE     0x4a008600
#define CORE_CM_CORE        0x4a008700
#define IVA_CM_CORE         0x4a008f00
#define CAM_CM_CORE         0x4a009000
#define DSS_CM_CORE         0x4a009100
#define L3INIT_CM_CORE      0x4a009300
#define L4PER_CM_CORE       0x4a009700
#define CKGEN_PRM           0x4ae06100
#define WKUPAON_CM          0x4ae07800
#define EMU_CM              0x4ae07a00

/* CLKSTCTRL offsets */
#define CORE_CM_CORE__CM_L3MAIN1_CLKSTCTRL                        0x000ul
#define CORE_CM_CORE__CM_IPU2_CLKSTCTRL                           0x200ul
#define CORE_CM_CORE__CM_DMA_CLKSTCTRL                            0x300ul
#define CORE_CM_CORE__CM_EMIF_CLKSTCTRL                           0x400ul
#define CORE_CM_CORE__CM_L4CFG_CLKSTCTRL                          0x600ul
#define COREAON_CM_CORE__CM_COREAON_CLKSTCTRL                     0x00ul
#define DSP1_CM_CORE_AON__CM_DSP1_CLKSTCTRL                       0x00ul
#define DSS_CM_CORE__CM_DSS_CLKSTCTRL                             0x00ul
#define IPU_CM_CORE_AON__CM_IPU1_CLKSTCTRL                        0x00ul
#define IPU_CM_CORE_AON__CM_IPU_CLKSTCTRL                         0x40ul
#define IVA_CM_CORE__CM_IVA_CLKSTCTRL                             0x00ul
#define CAM_CM_CORE__CM_CAM_CLKSTCTRL                             0x00ul
#define L3INIT_CM_CORE__CM_L3INIT_CLKSTCTRL                       0x00ul
#define L3INIT_CM_CORE__CM_PCIE_CLKSTCTRL                         0xA0ul
#define L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL                         0xC0ul
#define L4PER_CM_CORE__CM_L4PER_CLKSTCTRL                         0x000ul
#define L4PER_CM_CORE__CM_L4PER2_CLKSTCTRL                        0x1FCul
#define L4PER_CM_CORE__CM_L4PER3_CLKSTCTRL                        0x210ul
#define MPU_CM_CORE_AON__CM_MPU_CLKSTCTRL                         0x00ul
#define RTC_CM_CORE_AON__CM_RTC_CLKSTCTRL                         0x00ul
#define VPE_CM_CORE_AON__CM_VPE_CLKSTCTRL                         0x00ul
#define WKUPAON_CM__CM_WKUPAON_CLKSTCTRL                          0x00ul

/* CLKSTCTRL modes */
#define SW_SLEEP        (0x1)
#define SW_WKUP         (0x2)
#define HW_AUTO         (0x3)

#define CLKSTCTRL_TIMEOUOT  (300)

/* CLKCTRL Offsets */
#define CAM_CM_CORE__CM_CAM_VIP1_CLKCTRL                            0x020ul
#define CAM_CM_CORE__CM_CAM_VIP2_CLKCTRL                            0x028ul
#define CAM_CM_CORE__CM_CAM_VIP3_CLKCTRL                            0x030ul
#define CORE_CM_CORE__CM_L3MAIN1_L3_MAIN_1_CLKCTRL                  0x020ul
#define CORE_CM_CORE__CM_L3MAIN1_GPMC_CLKCTRL                       0x028ul
#define CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL                   0x030ul
#define CORE_CM_CORE__CM_L3MAIN1_MMU_PCIESS_CLKCTRL                 0x048ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM1_CLKCTRL                  0x050ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM2_CLKCTRL                  0x058ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM3_CLKCTRL                  0x060ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_ROM_CLKCTRL                   0x068ul
#define CORE_CM_CORE__CM_L3MAIN1_TPCC_CLKCTRL                       0x070ul
#define CORE_CM_CORE__CM_L3MAIN1_TPTC1_CLKCTRL                      0x078ul
#define CORE_CM_CORE__CM_L3MAIN1_TPTC2_CLKCTRL                      0x080ul
#define CORE_CM_CORE__CM_L3MAIN1_VCP1_CLKCTRL                       0x088ul
#define CORE_CM_CORE__CM_L3MAIN1_VCP2_CLKCTRL                       0x090ul
#define CORE_CM_CORE__CM_IPU2_IPU2_CLKCTRL                          0x220ul
#define CORE_CM_CORE__CM_DMA_DMA_SYSTEM_CLKCTRL                     0x320ul     /* REMOVE FOR ADAS */
#define CORE_CM_CORE__CM_EMIF_DMM_CLKCTRL                           0x420ul
#define CORE_CM_CORE__CM_EMIF_EMIF_OCP_FW_CLKCTRL                   0x428ul
#define CORE_CM_CORE__CM_EMIF_EMIF1_CLKCTRL                         0x430ul
#define CORE_CM_CORE__CM_EMIF_EMIF2_CLKCTRL                         0x438ul
#define CORE_CM_CORE__CM_L4CFG_L4_CFG_CLKCTRL                       0x620ul
#define CORE_CM_CORE__CM_L4CFG_SPINLOCK_CLKCTRL                     0x628ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX1_CLKCTRL                     0x630ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX2_CLKCTRL                     0x648ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX3_CLKCTRL                     0x650ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX4_CLKCTRL                     0x658ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX5_CLKCTRL                     0x660ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX6_CLKCTRL                     0x668ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX7_CLKCTRL                     0x670ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX8_CLKCTRL                     0x678ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX9_CLKCTRL                     0x680ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX10_CLKCTRL                    0x688ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX11_CLKCTRL                    0x690ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX12_CLKCTRL                    0x698ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX13_CLKCTRL                    0x6A0ul
#define CORE_CM_CORE__CM_L3INSTR_L3_MAIN_2_CLKCTRL                  0x720ul
#define DSS_CM_CORE__CM_DSS_DSS_CLKCTRL                             0x020ul
#define EMU_CM__CM_EMU_MPU_EMU_DBG_CLKCTRL                          0x00Cul
#define IPU_CM_CORE_AON__CM_IPU1_IPU1_CLKCTRL                       0x020ul
#define IPU_CM_CORE_AON__CM_IPU_MCASP1_CLKCTRL                      0x050ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER5_CLKCTRL                      0x058ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER6_CLKCTRL                      0x060ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER7_CLKCTRL                      0x068ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER8_CLKCTRL                      0x070ul
#define IVA_CM_CORE__CM_IVA_IVA_CLKCTRL                             0x020ul
#define IVA_CM_CORE__CM_IVA_SL2_CLKCTRL                             0x028ul
#define L3INIT_CM_CORE__CM_L3INIT_MMC1_CLKCTRL                      0x028ul  /* REMOVE FOR ADAS */
#define L3INIT_CM_CORE__CM_L3INIT_MMC2_CLKCTRL                      0x030ul  /* REMOVE FOR ADAS */
#define L3INIT_CM_CORE__CM_L3INIT_IEEE1500_2_OCP_CLKCTRL            0x078ul
#define L3INIT_CM_CORE__CM_PCIE_PCIESS1_CLKCTRL                     0x0B0ul
#define L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL                        0x0D0ul
#define L3INIT_CM_CORE__CM_L3INIT_OCP2SCP1_CLKCTRL                  0x0E0ul
#define L3INIT_CM_CORE__CM_L3INIT_OCP2SCP3_CLKCTRL                  0x0E8ul
#define L4PER_CM_CORE__CM_L4PER2_L4_PER2_CLKCTRL                    0x00Cul
#define L4PER_CM_CORE__CM_L4PER3_L4_PER3_CLKCTRL                    0x014ul
#define L4PER_CM_CORE__CM_L4PER_TIMER10_CLKCTRL                     0x028ul
#define L4PER_CM_CORE__CM_L4PER_TIMER11_CLKCTRL                     0x030ul
#define L4PER_CM_CORE__CM_L4PER_TIMER2_CLKCTRL                      0x038ul
#define L4PER_CM_CORE__CM_L4PER_TIMER3_CLKCTRL                      0x040ul
#define L4PER_CM_CORE__CM_L4PER_TIMER4_CLKCTRL                      0x048ul
#define L4PER_CM_CORE__CM_L4PER_TIMER9_CLKCTRL                      0x050ul
#define L4PER_CM_CORE__CM_L4PER_GPIO2_CLKCTRL                       0x060ul
#define L4PER_CM_CORE__CM_L4PER_GPIO3_CLKCTRL                       0x068ul
#define L4PER_CM_CORE__CM_L4PER_GPIO4_CLKCTRL                       0x070ul
#define L4PER_CM_CORE__CM_L4PER_GPIO5_CLKCTRL                       0x078ul
#define L4PER_CM_CORE__CM_L4PER_GPIO6_CLKCTRL                       0x080ul
#define L4PER_CM_CORE__CM_L4PER_I2C1_CLKCTRL                        0x0A0ul
#define L4PER_CM_CORE__CM_L4PER_I2C2_CLKCTRL                        0x0A8ul
#define L4PER_CM_CORE__CM_L4PER_I2C3_CLKCTRL                        0x0B0ul
#define L4PER_CM_CORE__CM_L4PER_I2C4_CLKCTRL                        0x0B8ul
#define L4PER_CM_CORE__CM_L4PER_L4_PER1_CLKCTRL                     0x0C0ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER13_CLKCTRL                    0x0C8ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER14_CLKCTRL                    0x0D0ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER15_CLKCTRL                    0x0D8ul
#define L4PER_CM_CORE__CM_L4PER_MCSPI1_CLKCTRL                      0x0F0ul
#define L4PER_CM_CORE__CM_L4PER_GPIO7_CLKCTRL                       0x110ul
#define L4PER_CM_CORE__CM_L4PER_GPIO8_CLKCTRL                       0x118ul
#define L4PER_CM_CORE__CM_L4PER_MMC3_CLKCTRL                        0x120ul
#define L4PER_CM_CORE__CM_L4PER_MMC4_CLKCTRL                        0x128ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER16_CLKCTRL                    0x130ul
#define L4PER_CM_CORE__CM_L4PER2_QSPI_CLKCTRL                       0x138ul
#define L4PER_CM_CORE__CM_L4PER_UART1_CLKCTRL                       0x140ul
#define MPU_CM_CORE_AON__CM_MPU_MPU_CLKCTRL                         0x020ul
#define MPU_CM_CORE_AON__CM_MPU_MPU_MPU_DBG_CLKCTRL                 0x028ul
#define VPE_CM_CORE_AON__CM_VPE_VPE_CLKCTRL                         0x004ul
#define WKUPAON_CM__CM_WKUPAON_WD_TIMER1_CLKCTRL                    0x028ul
#define WKUPAON_CM__CM_WKUPAON_WD_TIMER2_CLKCTRL                    0x030ul
#define WKUPAON_CM__CM_WKUPAON_GPIO1_CLKCTRL                        0x038ul
#define WKUPAON_CM__CM_WKUPAON_TIMER1_CLKCTRL                       0x040ul
#define WKUPAON_CM__CM_WKUPAON_TIMER12_CLKCTRL                      0x048ul
#define WKUPAON_CM__CM_WKUPAON_UART10_CLKCTRL                       0x080ul

/* CLKCTRL modes */
#define MODE_DISABLED   (0x0)
#define MODE_AUTO       (0x1)
#define MODE_ENABLED    (0x2)

#define CLKCTRL_TIMEOUOT  (300)

/* Various register address definitions */
#define CM_CLKSEL_CORE              (CKGEN_CM_CORE_AON + 0x000)
#define CM_CLKSEL_ABE               (CKGEN_CM_CORE_AON + 0x008)
#define CM_DLL_CTRL                 (CKGEN_CM_CORE_AON + 0x010)
#define CM_CLKMODE_DPLL_CORE        (CKGEN_CM_CORE_AON + 0x020)
#define CM_CLKSEL_DPLL_CORE         (CKGEN_CM_CORE_AON + 0x02C)
#define CM_CLKMODE_DPLL_MPU         (CKGEN_CM_CORE_AON + 0x060)
#define CM_CLKMODE_DPLL_IVA         (CKGEN_CM_CORE_AON + 0x0A0)
#define CM_CLKMODE_DPLL_ABE         (CKGEN_CM_CORE_AON + 0x0E0)
#define CM_CLKMODE_DPLL_DDR         (CKGEN_CM_CORE_AON + 0x110)
#define CM_CLKMODE_DPLL_DSP         (CKGEN_CM_CORE_AON + 0x134)
#define CM_CLKMODE_DPLL_GMAC        (CKGEN_CM_CORE_AON + 0x1A8)
#define CM_CLKMODE_DPLL_GPU         (CKGEN_CM_CORE_AON + 0x1D8)
#define CM_CLKMODE_DPLL_PER         (CKGEN_CM_CORE     + 0x040)
#define CM_CLKMODE_DPLL_PCIE_REF    (CKGEN_CM_CORE     + 0x100)
#define CM_SYS_CLKSEL               (CKGEN_PRM         + 0x010)

#define CTRL_CORE_CONTROL_IO_2      (CTRL_MODULE_CORE  + 0x558)

#define CM_CLKMODE_AUTOIDLE_DPLL_DSP         (0x13C)

/**********************************************************************
 *
 *  FUNCTIONS
 *
 **********************************************************************/






static void prcm_set_dss_mode(UInt32 module_base, UInt32 module_offset, UInt32 mode)
{
    UInt32 reg_val;
    UInt32 timeout = CLKCTRL_TIMEOUOT;

    /* DESHDCP Clock ENABLE for DSS */
    WR_MEM_32(CTRL_CORE_CONTROL_IO_2, RD_MEM_32(CTRL_CORE_CONTROL_IO_2) | 0x1);

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | 0x00003F00 | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) != 0) && (timeout>0))
    {
        timeout--;
    }

}

static void prcm_set_proc_mode(UInt32 module_base, UInt32 module_offset, UInt32 mode)
{
    UInt32 reg_val;
    UInt32 timeout = CLKCTRL_TIMEOUOT;

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) == 0x00030000) && (timeout>0))
    {
        timeout--;
    }

}

static void prcm_set_module_mode(UInt32 module_base, UInt32 module_offset, UInt32 mode, UInt32 extrabits, UInt32 extrabitsMask)
{
    UInt32 reg_val;
    UInt32 timeout = CLKCTRL_TIMEOUOT;

    reg_val = RD_MEM_32(module_base + module_offset) & ~(extrabitsMask | 0x00000003);
    WR_MEM_32(module_base+module_offset, (reg_val | (extrabits & extrabitsMask) | (mode & 0x3)));

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) != 0) && (timeout>0))
    {
        timeout--;
    }

}

static void prcm_set_clkdomain_state(UInt32 module_base, UInt32 module_offset, UInt32 state)
{
    UInt32 reg_val;

    reg_val = RD_MEM_32(module_base+module_offset);
    WR_MEM_32(module_base+module_offset, ((reg_val & ~(0x3)) | (state & 0x3)));

}

/**
 *******************************************************************************
 *
 * \brief One time prcm initialization when A15 boots IPU
 *
 *******************************************************************************
*/

Void Utils_prcmInit(void)
{

    /* Resembles to gel file initialization code, additional initialization if required
     * can be added in this funciton */

    /* PRCM clock domain state setting functions */
#ifdef NDK_PROC_TO_USE_IPU1_0
    prcm_set_clkdomain_state(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL,      SW_WKUP );
#endif
#ifdef NDK_PROC_TO_USE_IPU1_1
    prcm_set_clkdomain_state(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL,      SW_WKUP );
#endif
#ifdef NDK_PROC_TO_USE_IPU2
    prcm_set_clkdomain_state(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL,      SW_WKUP );
#endif
    prcm_set_clkdomain_state(DSS_CM_CORE,       DSS_CM_CORE__CM_DSS_CLKSTCTRL,          SW_WKUP );
    prcm_set_clkdomain_state(VPE_CM_CORE_AON,   VPE_CM_CORE_AON__CM_VPE_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(IVA_CM_CORE,       IVA_CM_CORE__CM_IVA_CLKSTCTRL,          SW_WKUP );
    prcm_set_clkdomain_state(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_CLKSTCTRL,          SW_WKUP );
    prcm_set_clkdomain_state(CKGEN_CM_CORE_AON, CM_CLKMODE_AUTOIDLE_DPLL_DSP,     MODE_DISABLED );

    /* PRCM Generic module mode setting functions */
    prcm_set_module_mode(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_VIP1_CLKCTRL,               MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_DMA_DMA_SYSTEM_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );    /* REMOVE FOR ADAS */
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3INSTR_L3_MAIN_2_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
#ifdef NDK_PROC_TO_USE_IPU1_0
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
#endif
#ifdef NDK_PROC_TO_USE_IPU1_1
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
#endif
#ifdef NDK_PROC_TO_USE_IPU2
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
#endif
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM1_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPCC_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPTC1_CLKCTRL,         MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPTC2_CLKCTRL,         MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX1_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX10_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX11_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX12_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX13_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX2_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX3_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX4_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX5_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX6_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX7_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX8_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX9_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_SPINLOCK_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
#ifdef NDK_PROC_TO_USE_IPU1_0
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
#endif
#ifdef NDK_PROC_TO_USE_IPU1_1
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
#endif
#ifdef NDK_PROC_TO_USE_IPU2
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
#endif
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO2_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO3_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO4_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO5_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO6_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO7_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO8_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C1_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );  //
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C2_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_QSPI_CLKCTRL,          MODE_ENABLED,   0x05000000, 0x07000000  );
    prcm_set_module_mode(VPE_CM_CORE_AON,   VPE_CM_CORE_AON__CM_VPE_VPE_CLKCTRL,            MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_GPIO1_CLKCTRL,           MODE_AUTO,      0x00000000, 0x00000000  ); //

    /* PRCM Specialized module mode setting functions */
    prcm_set_proc_mode(IVA_CM_CORE,         IVA_CM_CORE__CM_IVA_SL2_CLKCTRL,                MODE_AUTO                   );
    prcm_set_proc_mode(IVA_CM_CORE,         IVA_CM_CORE__CM_IVA_IVA_CLKCTRL,                MODE_AUTO                   );
    prcm_set_dss_mode(DSS_CM_CORE,          DSS_CM_CORE__CM_DSS_DSS_CLKCTRL,                MODE_ENABLED                );
}

Void Utils_prcmTimerInitForDsp(void)
{
    /* PRCM enable for Timers 5 and 6 for DSP access */
    prcm_set_module_mode(IPU_CM_CORE_AON,     IPU_CM_CORE_AON__CM_IPU_TIMER5_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(IPU_CM_CORE_AON,     IPU_CM_CORE_AON__CM_IPU_TIMER6_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );

}

Void Utils_prcmTimerInitForIpu(void)
{
    /* PRCM enable for Timers 3 and 11 for IPU access */
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER3_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER11_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );

}


