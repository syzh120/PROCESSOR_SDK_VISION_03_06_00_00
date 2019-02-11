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

/*
 * GMAC
 */
#include "stdio.h"
#include "stdint.h"
#include "phy_mdio.h"
#include "hw_types.h"
#include "CPSW_3GSS_R_lib.h"

   void
Configure_pad_eee_db ()
{
   WR_MEM_32 (0x4a002550, 0x6f361e05);
   printf ("\tCONFIGURE THE MDIO PINS \n\r");
   /* IMP::AS on EEE DB VIN2a PADs are used for MDIO, disable MDIO_CLK and MDIO_D coming on default PAD, otherwise it would corrupt MDIO config */
   WR_MEM_32 (MDIO_MCLK, (RD_MEM_32 (MDIO_MCLK) & 0xffffff00) | 0xf);
   WR_MEM_32 (MDIO_D, (RD_MEM_32 (MDIO_D) & 0xffffff00) | 0xf);

   WR_MEM_32 (VIN2A_D10_MDIO_CLK,
         (RD_MEM_32 (VIN2A_D10_MDIO_CLK) & 0xffffff00) | 0x3);
   WR_MEM_32 (VIN2A_D11_MDIO_D,
         (RD_MEM_32 (VIN2A_D11_MDIO_D) & 0xffffff00) | 0x3);
}

void delay_mdio (uint32_t cnt)
{
   uint32_t i;
   for (i = 0; i < cnt; i++);
}

   void
menu_mdio_write (uint32_t PHY_ADDR, uint32_t phy_reg, uint32_t data)
{
   cpsw_mdio_write (phy_reg, data, PHY_ADDR);
}

   void
mdio_phy_write_mmd (uint32_t PHY_ADDR, uint32_t mmd_number,
      uint32_t offset, uint32_t data)
{
   /*Writing 0x8000 to register 0 of
     MMD3
     1.Write 0x3 to register 0xD: 0xD = 0x0003;
     (function = address; set the device address)
     2. Write 0x0 to register 0xE: 0xE = 0x0; (set the
     register offset address)
     3. Write 0x4003 to register 0xD:0xD=0x4003;
     (function = data; keep the device address)
     4. Read register 0xE:0xE == (data from register
     0x0 of MMD3)
     5. Write 0x8000 to register 0xE: 0xE = 0x8000
     (write 0x8000 to register 0x0 of MMD3 */

   /*0xd is MMD Access Control Register having field device address and function (data or address)
    * 0xE is MMD Access Address Data Register*/

   cpsw_mdio_write (0xD, mmd_number, PHY_ADDR);
   cpsw_mdio_write (0xE, offset, PHY_ADDR);
   cpsw_mdio_write (0xD, (0x4000 + mmd_number), PHY_ADDR);
   //cpsw_mdio_read(0xE,PHY_ADDR);
   cpsw_mdio_write (0xE, data, PHY_ADDR);
}

   void
mdio_phy_read_mmd (uint32_t PHY_ADDR, uint32_t mmd_number,
      uint32_t offset)
{
   uint32_t temp = 0;
   cpsw_mdio_write (0xD, mmd_number, PHY_ADDR);
   cpsw_mdio_write (0xE, offset, PHY_ADDR);
   temp = (0x4000 + mmd_number);
   printf ("\tWriting to 0xD VALUE =  %x \n", temp);
   cpsw_mdio_write (0xD, temp, PHY_ADDR);
   cpsw_mdio_read (0xE, PHY_ADDR);
}

//wait for go bit to 0 and ack bit to become 1
   void
wait_for_user_access ()
{
   uint32_t reg;
   reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x80000000;
   while (reg != 0x0)
   {
      delay_mdio (10000);
      delay_mdio (10000);
      reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x80000000;
   }
   reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x20000000;
   while (reg != 0x20000000)
   {
      delay_mdio (10000);
      delay_mdio (10000);
      reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x20000000;
   }

}

uint32_t cpsw_mdio_read (unsigned char phy_reg, uint32_t PHY_ADDR)
{
   uint32_t reg = 0;
   reg =
      (USERACCESS_GO | USERACCESS_READ | (phy_reg << 21) | (PHY_ADDR << 16));
   WR_MEM_32 ((MDIOBASE + MDIO_USERACCESS0), reg);
   wait_for_user_access ();
   reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0);
   reg = reg & 0x0000ffff;
   printf ("\tPHYREG READ VALUE =  %x \n", reg);
    return reg;
}

   void
cpsw_mdio_write (unsigned char phy_reg, unsigned short data, uint32_t PHY_ADDR)
{
   uint32_t reg = 0;
   reg =
      (USERACCESS_GO | USERACCESS_WRITE | (phy_reg << 21) | (PHY_ADDR << 16) |
       (data & USERACCESS_DATA));
   WR_MEM_32 ((MDIOBASE + MDIO_USERACCESS0), reg);
   wait_for_user_access ();
   reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0);
   reg = reg & 0x0000ffff;
   //printf ("\tPHYREG WRITE VALUE  is  = %x \n", reg);
}

   void
check_phy_alive (uint32_t PHY_ADDR, uint32_t enableReset)
{
   uint32_t mdio_read,  data;

   delay_mdio (1000);
   printf ("\tCONFIGURE THE MDIO CLOCK\n\r");
   //increase the divider value if it is not working with this
   WR_MEM_32 ((MDIOBASE + MDIO_CONTROL), 0x41000089);
   delay_mdio (1000);
   mdio_read = RD_MEM_32 (MDIOBASE + MDIO_ALIVE);
   printf ("\t MDIO_ALIVE=%x\n", mdio_read);
   if (!(mdio_read & 1 << PHY_ADDR))
   {
      printf ("\t**********ERROR IN PHY ADDRESS ************* \n");
      printf ("\t*** CHECK THE PHY ADDRESS FROM MDIO AND RECONFIGURE*** \n\r");
   }
   if (enableReset == 1)
   {
      printf ("\t**********APPLY RESET TO THE PHY ************* \n");
      cpsw_mdio_read (Control_0, PHY_ADDR);
      data = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & USERACCESS_DATA;
      data |= 0x8000;
      cpsw_mdio_write (Control_0, data, PHY_ADDR);
      cpsw_mdio_read (Control_0, PHY_ADDR);
      data = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & USERACCESS_DATA;
      while ((data & 0x8000) != 0x0)
      {
      }
      printf ("\t**********PHY IS OUT OF RESET ************* \n");
   }
   printf ("\t************ PHY IS ALIVE ***********\n");
}

//void MDIO_PHY_ACCESS()
   void
config_phy (uint32_t PHY_ADDR, uint32_t phyCfgFlag)
{
   uint32_t data, val, i;
   uint32_t mode = ( phyCfgFlag & PHY_SPEED_MODE_MASK ) >> PHY_SPEED_MODE_SHIFT;
   uint32_t resetEnable = ( phyCfgFlag & EN_PHY_RESET );
    uint32_t restartAutoNeg =  ( phyCfgFlag & PHY_RESTART_AUTONEGOTIATION) >> PHY_RESTART_AUTONEGOTIATION_SHIFT;

   check_phy_alive (PHY_ADDR, resetEnable);
   printf ("\tPHY ALIVE CHECK DONE\n");

   cpsw_mdio_read (Control_0, PHY_ADDR);
   data = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & USERACCESS_DATA;

   if ( PHY_LOOPBACK == (phyCfgFlag&PHY_LOOPBACK) )
    {
      data = (data & 0xEFFF); //clear auto-negotiation enable bit
      data |= (PHY_LPBK);
    }
   else if ((phyCfgFlag & EXT_LOOPBACK) == EXT_LOOPBACK)
   {
      data = PHY_RESET;
      cpsw_mdio_write (Control_0, data, PHY_ADDR);
   }
    else if ( 1 == restartAutoNeg )
    {
        /* Restart auto negotiation */
        data |= PHY_BMCR_RST_NEG;
    }
    else
    {
    }

   if (1 != restartAutoNeg)
   {
      /* For PHY/EXT loopback mode we need to Configure speed setting */
        if (mode == 2)
        {
            data = ((data & 0xcfbf) | PHY_1000_MBPS);
        }
        //100
        else if (mode == 1)
        {
            data = (data & 0xcfbf) | PHY_100_MBPS;
        }
        //10
        else
        {
            data = (data & 0xcfbf) | PHY_10_MBPS;
        }
    }

   //=> Prasad - PHY RESET is needed for DP83867
   data = PHY_RESET;
   cpsw_mdio_write (Control_0, data, PHY_ADDR);
    cpsw_mdio_read (Control_0, PHY_ADDR);
    data = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & USERACCESS_DATA;
    printf ("\tTHE CONTROL VALUE CONFIGURED is  0%x\n\r", data);

    do
    {
       for(i=0U;i<0xFFF00;i++);
        printf ("Polling for PHY Link  is in progres ......\n");
       cpsw_mdio_read (Status_1, PHY_ADDR);
        data = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & USERACCESS_DATA;
        val = (data & 0x0004);
    } while (val == 0x0);
    printf (" PHY Link is up ......\n");

    cpsw_mdio_read (LINK_AN_STATUS_REG_17, PHY_ADDR);
    data = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & USERACCESS_DATA;

    mode = HW_RD_FIELD32 (&data, LINK_AN_STATUS_REG_17_SPEED_STATUS);
    if (1U == HW_RD_FIELD32 (&data, LINK_AN_STATUS_REG_17_DUPLEX_STATUS))
    {
        if ( (PHY_SPEED_MODE_1000MBPS >> PHY_SPEED_MODE_SHIFT) == mode)
        {
            printf ("********** PHY is in RGMII_1000,FULLDUPLEX MODE **********\n\r");
        }
        else if ( (PHY_SPEED_MODE_100MBPS >> PHY_SPEED_MODE_SHIFT) == mode )
        {
            printf ("********** PHY is in RGMII_100,FULLDUPLEX MODE **********\n\r");
        }
        else
        {
            printf ("********** PHY is in RGMII_10,FULLDUPLEX MODE **********\n\r");
        }
    }
    else
    {
        if ( (PHY_SPEED_MODE_1000MBPS >> PHY_SPEED_MODE_SHIFT) == mode )
        {
            printf ("********** PHY is in RGMII_1000,HALFDUPLEX MODE **********\n\r");
        }
        else if ( (PHY_SPEED_MODE_100MBPS >> PHY_SPEED_MODE_SHIFT) == mode )
        {
            printf ("********** PHY is in RGMII_100,HALFDUPLEX MODE **********\n\r");
        }
        else
        {
            printf ("********** PHY is in RGMII_10,HALFDUPLEX MODE **********\n\r");
        }
    }
   printf ("\t**** PHY CONFIGURATION IS COMPLETED ****** \n");
}

//void print_phy_registers()
   void
print_phy_registers (uint32_t PHY_ADDR)
{
   uint32_t cnt;
   //Configure_pad_eee_db();
   for (cnt = 0; cnt < 31; cnt++)
   {
      printf ("\tPHY_REG ADDRESS   = %d  \n", cnt);
      delay_mdio (0x1000);
      cpsw_mdio_read (cnt, PHY_ADDR);
      printf ("\t*******************************\n", cnt);
   }
}
