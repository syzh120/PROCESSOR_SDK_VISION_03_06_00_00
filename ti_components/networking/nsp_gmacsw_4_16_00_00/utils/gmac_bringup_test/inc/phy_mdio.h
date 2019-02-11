/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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

#define DP83865_PHY 1

#define WR_MEM_32(addr, data)    *(unsigned int *)(addr) =(unsigned int)(data)
#define RD_MEM_32(addr)          *(unsigned int *)(addr)


//register address of PHY
#define Control_0    0
#define Status_1     1
#define PHYID_2      2
#define PHYID_3      3
#define ANAR_4      4
#define ANARLPA_5   5   //status
//6,7,8 not needed to configure
#define ANEXP_6      6
#define ANNP_7      7
#define LPNP_8      8
#define BT_Control_9    9
#define BT_Status_10    10
//11-12 reserved
#define Extn_Status_15    15
//16 Reserved.
#define LINK_AN_STATUS_REG_17   17
#define Intr_Mask_18   18
#define Intr_Status_19   19
#define LED_control_24 24

#define LBK_control_19   19

#define PHY_CONF_TXCLKEN 0x0020
#define PHY_DPLX    0x0100   //8bit
#define PHY_AUTON   0x1000   //12bit
#define PHY_LPBK   0x4000   //14bit
#define PHY_RESET   0x8000   //15bit
#define PHY_10_MBPS 0x0000   //6=0,13 =0
#define PHY_100_MBPS 0x2000   //6=0,13 =1
#define PHY_1000_MBPS 0x0040   //6=1,13 =0

#define PHY_BMCR_RST_NEG  0x0200   //9bit
#define PHY_1000BTCR_1000FD 0x0200
#define PHY_1000BTCR_1000HD 0x0100
#define PHY_BMSR_AUTN_COMP  0x0020   //5bit
#define PHY_DIG         0x4000

#if (1 == DP83865_PHY)
#define LINK_AN_STATUS_REG_17_SPEED_STATUS_MASK     (0xC000)
#define LINK_AN_STATUS_REG_17_SPEED_STATUS_SHIFT    (14U)
#define LINK_AN_STATUS_REG_17_LINK_STATUS_MASK      (0x0400)
#define LINK_AN_STATUS_REG_17_LINK_STATUS_SHIFT     (10U)
#define LINK_AN_STATUS_REG_17_DUPLEX_STATUS_MASK    (0x2000)
#define LINK_AN_STATUS_REG_17_DUPLEX_STATUS_SHIFT   (13U)
#elif (1 == AR8031_PHY )
#define LINK_AN_STATUS_REG_17_SPEED_STATUS_MASK     (0x0018)
#define LINK_AN_STATUS_REG_17_SPEED_STATUS_SHIFT    (3U)
#define LINK_AN_STATUS_REG_17_LINK_STATUS_MASK     (0x0004)
#define LINK_AN_STATUS_REG_17_LINK_STATUS_SHIFT    (2U)
#define LINK_AN_STATUS_REG_17_DUPLEX_STATUS_MASK     (0x0002)
#define LINK_AN_STATUS_REG_17_DUPLEX_STATUS_SHIFT    (1U)
#else
#endif

#define CTRL_MODULE_BASE 0x4a002000
/*  For EEE DB MDIO signals are on VIN2a PADs */
#define VIN2A_D10_MDIO_CLK   (CTRL_MODULE_BASE + 0x1590)
#define VIN2A_D11_MDIO_D   (CTRL_MODULE_BASE + 0x1594)
#define MDIO_MCLK   (CTRL_MODULE_BASE + 0x1640)
#define MDIO_D   (CTRL_MODULE_BASE + 0x163C)

#define  PHY_SPEED_MODE_1000MBPS                    ((uint32_t)2U<<4U)
#define  PHY_SPEED_MODE_100MBPS                     ((uint32_t)1U<<4U)
#define  PHY_SPEED_MODE_10MBPS                      ((uint32_t)0U<<4U)
#define  PHY_SPEED_MODE_SHIFT                       (4U)
#define  PHY_SPEED_MODE_MASK                        (0x00000030)
#define  PHY_RESTART_AUTONEGOTIATION_SHIFT          (3U)
#define  PHY_RESTART_AUTONEGOTIATION                ((uint32_t)1U<<3U)
#define  EXT_LOOPBACK                              ((uint32_t)1U<<2U)
#define  PHY_LOOPBACK                               ((uint32_t)1U<<1U)
#define  EN_PHY_RESET                              ((uint32_t)1U<<0U)

/* wait until hardware is ready for another user access */
#define USERACCESS_GO    0x80000000
#define USERACCESS_READ  0x00000000
#define USERACCESS_WRITE 0x40000000
#define USERACCESS_ACK   1
#define USERACCESS_DATA  0x0000ffff

void Configure_pad_eee_db();
void delay_mdio (uint32_t cnt);
void menu_mdio_write (uint32_t PHY_ADDR, uint32_t phy_reg, uint32_t data);
void mdio_phy_write_mmd (uint32_t PHY_ADDR, uint32_t mmd_number,
              uint32_t offset, uint32_t data);
void mdio_phy_read_mmd (uint32_t PHY_ADDR, uint32_t mmd_number,
             uint32_t offset);
void wait_for_user_access ();
uint32_t cpsw_mdio_read (unsigned char phy_reg, uint32_t PHY_ADDR);
void cpsw_mdio_write (unsigned char phy_reg, unsigned short data,
            uint32_t PHY_ADDR);
void check_phy_alive (uint32_t PHY_ADDR, uint32_t enableReset);
void config_phy (uint32_t PHY_ADDR, uint32_t phyCfgFlag);
void print_phy_registers (uint32_t PHY_ADDR);
