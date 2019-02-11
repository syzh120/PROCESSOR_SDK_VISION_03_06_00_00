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


/**
 *  \file   GMAC_Throughput_TestFunction.c
 *
 *  \brief  GMAC test file for port to port loopback.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include "stdio.h"
#include "stw_types.h"
#include "stdint.h"
#include "hw_types.h"
#include "soc.h"
#include "ChipCreateDV.h"

#include "TCASECFG.h"
#include "RESExt.h"
#include "hw_ctrl_core.h"
#include "hw_ctrl_core_sec.h"
#include "interrupt.h"
#include "irq_xbar.h"
#include "TCASECFG.h"
#include "RGMII_CH0_PORT_THPUT.h"
#include "CPSW_3GSS_R_lib.h"
#include "MEMUTIL.h"
#include "timer.h"
#include "phy_mdio.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ALE_BYPASS 1
#define __VDB__ 1
#define TX_MODE 1
#define RX_MODE 1
#define TX_INTR 0
#define RX_INTR 1
#define LARGE_DATA 0
#if (1U == LARGE_DATA)
#define MAX_PCK 9000
#define PCK_NO 9000
#else
#define MAX_PCK 55
#define PCK_NO 50
#define CPPI_BUFFER 1
#endif
#define CPPI_DDR 0
#define CPPI_OCMC 0

#define VAYU_PAB 0
#define VAYU_EVM 1
#define ENABLE_PHY_LOOPBACK 1
#define ENABLE_EXT_LOOPBACK 0
#define ENABLE_100MBPS_MODE     1
#define PORT1_ENABLED          1
#define PORT2_ENABLED           0

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

//CPPI TX descriptors
typedef struct CPPITxDesc
{
   uint32_t Tx_CPPI_NDP;
   uint32_t Tx_CPPI_BUF;
   uint32_t Tx_CPPI_PCK_LEN;
   uint32_t Tx_CPPI_PCK_CONFIG;
} CPPITxDesc_t;

//CPPI RX descriptors
typedef struct CPPIRxDesc
{
   uint32_t Rx_CPPI_NDP;
   uint32_t Rx_CPPI_BUF;
   uint32_t Rx_CPPI_PCK_LEN;
   uint32_t Rx_CPPI_PCK_CONFIG;
} CPPIRxDesc_t;

struct Results
{
   uint32_t RX_PCK_NO;
   uint32_t RX_PCK_SIZE;
   uint32_t RX_ST_COUNT;
   uint32_t RX_END_COUNT;
   uint32_t RX_TOTAL_COUNT;
   uint32_t RX_DATA_TRANSFER;
   uint32_t RX_TIMER_FREQ;
   float RX_THR;
   float RX_THR_MPS;
   uint32_t TX_PCK_NO;
   uint32_t TX_PCK_SIZE;
   uint32_t TX_ST_COUNT;
   uint32_t TX_END_COUNT;
   uint32_t TX_TOTAL_COUNT;
   uint32_t TX_DATA_TRANSFER;
   uint32_t TX_TIMER_FREQ;
   float TX_THR;
   float TX_THR_MPS;
   uint32_t TX_RX_PCK_NO;
   uint32_t TX_RX_PCK_SIZE;
   uint32_t TX_RX_ST_COUNT;
   uint32_t TX_RX_END_COUNT;
   uint32_t TX_RX_TOTAL_COUNT;
   uint32_t TX_RX_DATA_TRANSFER;
   uint32_t TX_RX_TIMER_FREQ;
   float TX_RX_THR;
   float TX_RX_THR_MPS;
} Results;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void CPSW_DATA_FILL (void);
void Random_Pck_Gen (void);
uint32_t DATA_CHECK (void);
uint32_t Check_all (void);
void CPSW_3GSS_R_init ();
void enableMDIO ();
void CPSW_CGSS_R_reset ();
void CPSW_3GSS_R_setup ();
void CPSW_3GSS_R_chk_rx_int ();
#if TX_INTR
void CPSW_3GSS_R_chk_tx_int ();
#endif
uint32_t CPSW_Start_Transfer ();
static uint32_t CPSW_Complete_Transfer (void);
uint32_t Check_Data ();
void Throughput_Results (void);
void Throughput_Measure (void);
uint32_t timerRead (uint32_t timerInst);
void HAL_CTRL_UnlockMMR (void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t MIN_PCK_SIZE = 1020;
uint32_t MAX_PCK_SIZE = 1024;

uint32_t CPPI_Tx_NDP;
uint32_t CPPI_Tx_BUF;
uint32_t CPPI_Tx_LEN;
uint32_t CPPI_Tx_PORT;

uint32_t CPPI_Rx_NDP;
uint32_t CPPI_Rx_BUF;
uint32_t CPPI_Rx_LEN = 1518;
uint32_t CPPI_Rx_PORT = 0x20000000;
uint32_t CPPI_TRANSMIT_DESC = 0x48487000;
uint32_t CPPI_RECEIVE_DESC = 0x48486000;
uint32_t PACE_PRESCALE = 0x00000FA0;

uint32_t Count_Pck = 0;
//check the flags to know the Testcase failure
volatile uint32_t data_fail;
uint32_t TCase_fail = 0;
//no of bytes transferred
uint32_t rx_octets, tx_octets, net_octets = 0;
volatile uint32_t lv_txInth, lv_rxInth = 0;
const uint32_t TIMER_NUM = SOC_TIMER3_BASE;
volatile uint32_t CounterValue1 = 0;
volatile uint32_t TxStartcount = 0;
volatile uint32_t RxStartcount = 0;
volatile uint32_t TxEndcount = 0;
volatile uint32_t RxEndcount = 0;
uint32_t DiffCount;
volatile uint32_t TIMER_FREQ = 20;
static float TX_Throughput = 0;
static float TX_Throughput_Mbps = 0;
volatile uint32_t TRANSMIT_TIME = 0;
volatile float TOTAL_DATA_TRANSFER_TX = 0;
volatile uint32_t RECEIVE_TIME = 0;
volatile float TOTAL_DATA_TRANSFER_RX = 0;
float RX_Throughput = 0;
float RX_Throughput_Mbps = 0;
volatile float TOTAL_DATA_TRANSFER_TX_RX = 0;
volatile uint32_t TX_RX_TIME = 0;
static float TX_RX_Throughput = 0;
static float TX_RX_Throughput_Mbps = 0;
uint32_t TxDesc_5, TxDesc_7, TxDesc_3, TxDesc_1 = 0;
volatile unsigned int testTime, startTest, endTest;

#pragma DATA_SECTION(TxBufferData, ".user_ocmc_data")
#pragma DATA_ALIGN(TxBufferData, 32)
uint32_t TxBufferData[MAX_PCK][380];

#pragma DATA_SECTION(RxBufferData, ".user_ocmc_data")
#pragma DATA_ALIGN(RxBufferData, 32)
uint32_t RxBufferData[MAX_PCK][380];

#pragma DATA_SECTION(PCK_SIZE, ".user_ocmc_data")
#pragma DATA_ALIGN(PCK_SIZE, 32)
uint32_t PCK_SIZE[MAX_PCK];

#if CPPI_DDR
#pragma DATA_SECTION(TxDesc, ".user_ddr_data")
#pragma DATA_ALIGN(TxDesc, 32)
struct CPPITxDesc TxDesc[MAX_PCK];
#pragma DATA_SECTION(RxDesc, ".user_ddr_data")
#pragma DATA_ALIGN(RxDesc, 32)
struct CPPIRxDesc RxDesc[MAX_PCK];

#elif CPPI_OCMC
#pragma DATA_SECTION(TxDesc, ".user_ocmc_data")
#pragma DATA_ALIGN(TxDesc, 32)
struct CPPITxDesc TxDesc[MAX_PCK];
#pragma DATA_SECTION(RxDesc, ".user_ocmc_data")
#pragma DATA_ALIGN(RxDesc, 32)
struct CPPIRxDesc RxDesc[MAX_PCK];
#endif

#pragma DATA_SECTION(RxResult, ".user_ocmc_data")
#pragma DATA_ALIGN(RxResult, 32)
struct Results RxResult;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
uint32_t GMAC_Throughput_TestFunction (void)
{
   uint32_t checkReturn = RET_FAIL, phyCfgFlag = 0;

   printf ("TC :: GMAC Throughput TEST STARTED  \r\n");
   // Control Module MMR register UNLOCK program
   HAL_CTRL_UnlockMMR ();
   // Enabling RGMII mode in GMII1_SEL control module register
   HW_WR_FIELD32 (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
         CTRL_CORE_CONTROL_IO_1, CTRL_CORE_CONTROL_IO_1_GMII1_SEL,
         0x2);
   // Enabling RGMII mode in GMII2_SEL control module register
   HW_WR_FIELD32 (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
         CTRL_CORE_CONTROL_IO_1, CTRL_CORE_CONTROL_IO_1_GMII2_SEL,
         0x2);

  printf ("TC ::PAD configuration  \r\n");
   printf ("TC ::TIMER INITIALIZATION  \r\n");
   deviceInit ();

   printf ("TC :: GMAC reset before transfer  \r\n");
   CPSW_CGSS_R_reset ();

   printf ("TC :: Initialize MDIO  \r\n");
   enableMDIO ();

#if  (1 == ENABLE_PHY_LOOPBACK)
   phyCfgFlag |= PHY_LOOPBACK;
#elif  (1 == ENABLE_EXT_LOOPBACK)
   phyCfgFlag |= EXT_LOOPBACK;
#endif

#if (1 == ENABLE_100MBPS_MODE)
   phyCfgFlag |= PHY_SPEED_MODE_100MBPS;
#else
   phyCfgFlag |= PHY_SPEED_MODE_1000MBPS;
#endif

/* If PHY is not configured for any configuration, set auto-negotiation enable */
if (0U == phyCfgFlag)
{
   phyCfgFlag |= PHY_RESTART_AUTONEGOTIATION;
}

   printf ("TC ::PAD configuration  \r\n");
#if  (1 == VAYU_PAB)
   DRA7xx_PAD_EEE_RGMII_Config ();
   printf ("TC :: Initialize PHY0  \r\n");
   config_phy (0, phyCfgFlag);
   printf ("TC :: Initialize PHY1  \r\n");
   config_phy (4, phyCfgFlag);
   cc_poll_reg (cc_reg_addr_trans
             (0x48485000 /*MDIOBASE*/, 0x0c /*MDIO_LINK */ ), 0x1, 0x1);
   cc_poll_reg (cc_reg_addr_trans
                (0x48485000 /*MDIOBASE*/, 0x0c /*MDIO_LINK */ ), 0x10, 0x10);
#else
    #if (1 == VAYU_EVM)
   TDA2xx_PAD_EVM_RGMII_Config ();
   vayu_init ();
    #if (1 == PORT1_ENABLED   )
    printf ("TC :: Initialize PHY0  \r\n");
    config_phy (2, phyCfgFlag);
    cc_poll_reg (cc_reg_addr_trans
            (0x48485000 /*MDIOBASE*/, 0x0c /*MDIO_LINK */ ), 0x4, 0x4);
   #endif
    #if (1 == PORT2_ENABLED)
    printf ("TC :: Initialize PHY1  \r\n");
    config_phy (3, phyCfgFlag);
    cc_poll_reg (cc_reg_addr_trans
                (0x48485000 /*MDIOBASE*/, 0x0c /*MDIO_LINK */ ), 0x8, 0x8);
    #endif
    #endif
#endif

   printf ("TC :: Clear GMAC variables and descriptor  \r\n");
   CPSW_3GSS_R_init ();

   //generate the random packet no,packet sizes
   printf ("TC :: Generate packets  \r\n");
   Random_Pck_Gen ();

   printf ("TC :: Configure Rx, Tx descriptors  \r\n");
   /** Configure CPSW for Transfer ***/
   CPSW_3GSS_R_setup ();

#if TX_MODE
   printf ("TC :: Fill data  \r\n");
   /*** Fill the  Packets in TX MODE ****/
   CPSW_DATA_FILL ();
#endif
   startTest = timerRead (TIMER_NUM);
   /** Start transfer ***/
   printf ("TC :: Start transfer  \r\n");
   CPSW_Start_Transfer ();
   /** Check if transfer successful ***/
   CPSW_Complete_Transfer ();
   endTest = timerRead (TIMER_NUM);
   testTime = endTest - startTest;
   TOTAL_DATA_TRANSFER_RX = ((PCK_NO - 1) * PCK_SIZE[0] * 8);
   RX_Throughput = (TOTAL_DATA_TRANSFER_RX * TIMER_FREQ) / (testTime);
   RX_Throughput_Mbps = (RX_Throughput * 1000000) / (1048576);

   /*** Results ****/
   /*** check data ***/
   printf ("TC :: Check received data  \r\n");
   checkReturn = Check_all ();

   printf ("TC :: Check Throughput  \r\n");
   Throughput_Measure ();

   Throughput_Results ();
   /*** Store results***/
   printf ("TC ::GMAC Throughput test done  \r\n");
   /* Verify that checkReturn contain valid status */
   return checkReturn;
}

   uint32_t
Check_all (void)
{
   uint32_t checkReturn = RET_OK;
   //check the _fail flags when failed
   checkReturn = DATA_CHECK ();
   return checkReturn;
}




   void
CPSW_DATA_FILL (void)
{
  uint32_t i, j, RX_DATA;
  uint32_t *rdPtr = 0;
   uint32_t data_1 = 0xFFFFFFFF;
   uint32_t data_2 = 0xFFFFFFFF;
   uint32_t data_3 = 0x11111111;
   uint32_t data_4 = 0x0;
   uint32_t pck_array = 380;
   for (i = 0; i < PCK_NO; i++)
   {
      data_4 = PCK_SIZE[i];
      TxBufferData[i][0] = data_1;
      TxBufferData[i][1] = data_2;
      TxBufferData[i][2] = data_3;
      TxBufferData[i][3] = data_4;
      for (j = 4; j <= pck_array; j++)
      {
         TxBufferData[i][j] = rand ();
      }
   }
   RX_DATA = (uint32_t) RxBufferData[0];
   rdPtr = (uint32_t *) (RX_DATA);
   //fill the receive buffer with zeros
   MEMUTIL_FillConst32 ((uint32_t *) rdPtr, PCK_NO * 380, 0x00000000);

}


uint32_t DATA_CHECK (void)
{
   uint32_t checkReturn = RET_OK;

   uint32_t TX_DATA, RX_DATA = 0;
   uint32_t i, *rdPtr, *wrPtr;
   for (i = 0; i < PCK_NO; i++)
   {
      TX_DATA = (uint32_t) TxBufferData[i];
      RX_DATA = (uint32_t) RxBufferData[i];
      rdPtr = (uint32_t *) (RX_DATA);
      wrPtr = (uint32_t *) (TX_DATA);
      if (!
            (MEMUTIL_Compare32
             ((uint32_t *) rdPtr, (uint32_t *) wrPtr, PCK_SIZE[i] / 8)))
      {
         Count_Pck = Count_Pck + 1;
      }
   }
   if (Count_Pck == PCK_NO)
   {
      RES_Set (RES_OK);
      printf ("TC :: Data check passed with received packets \r\n");
   }
   else
   {
      //data_fail++ ;
      RES_Set (RES_BAD);
      printf ("TC :: Data check failed with received packets \r\n");
      checkReturn = RET_FAIL;
   }
   return checkReturn;
}

void Random_Pck_Gen (void)
{
   int i;
   // generate differnet packet Nos
#if  (1 == TEST)
   // generate differnet packet sizes
   for (i = 0; i < PCK_NO; i++)
   {
      PCK_SIZE[i] = PCK_SIZE_TEST;   // rand() % (MAX_PCK_SIZE - MIN_PCK_SIZE +1) + MIN_PCK_SIZE;
   }
#else
   // generate differnet packet sizes
   for (i = 0; i < PCK_NO; i++)
   {
      PCK_SIZE[i] = 1512;   //rand() % (MAX_PCK_SIZE - MIN_PCK_SIZE +1) + MIN_PCK_SIZE;
   }
#endif

}


/* ============================================================================
 * LOCAL FUNCTIONS
 * =============================================================================
 */
/*==================== Function Separator =============================*/
   void
CPSW_CGSS_R_reset ()
{
   /*** Apply Reset ***/
   cc_reg_write (cc_reg_addr_trans (CPSW_3GSS_RG_BASE, SS_SOFT_RESET), 0x1);   //48485204
   cc_reg_write (cc_reg_addr_trans (CPSW_3GSS_R_BASE, CPSW_SOFT_RESET), 0x1);   //48484000
   cc_reg_write (cc_reg_addr_trans (CPSW_3GSS_R_BASE, SL1_SOFT_RESET), 0x1);   //0x48484d8c
   cc_reg_write (cc_reg_addr_trans (CPSW_3GSS_R_BASE, SL2_SOFT_RESET), 0x1);   //0x48484dcc

   cc_poll_reg (cc_reg_addr_trans (CPSW_3GSS_RG_BASE, SS_SOFT_RESET), 0x0,
         0xffffffff);
   cc_poll_reg (cc_reg_addr_trans (CPSW_3GSS_R_BASE, CPSW_SOFT_RESET), 0x0,
         0xffffffff);
   cc_poll_reg (cc_reg_addr_trans (CPSW_3GSS_R_BASE, SL1_SOFT_RESET), 0x0,
         0xffffffff);
   cc_poll_reg (cc_reg_addr_trans (CPSW_3GSS_R_BASE, SL2_SOFT_RESET), 0x0,
         0xffffffff);

}

/*==================== Function Separator =============================*/
   void
enableMDIO ()
{
   /* Enable preamble and clock div bits, enable MDIO */
   uint32_t writeValue;
   //writeValue=RD_REG_32(cc_reg_addr_trans(MDIOBASE, MDIO_CONTROL));
   writeValue = *(volatile int *) 0x48485004;
   writeValue = writeValue & 0x00000089;
   writeValue = writeValue | (1 << 30);
   cc_reg_write (cc_reg_addr_trans (MDIOBASE, MDIO_CONTROL), writeValue);
}

/*==================== Function Separator =============================*/
/*####################################################################
  Initialize registers 0x0200 thru 0x025C to 0's. Refer to cpdma spec.
#################################################################### */
   void
CPSW_3GSS_R_init ()
{

   int i, naddr;

   naddr = TX0_HDP;
   lv_rxInth = 0;
   lv_txInth = 0;
   CPPI_TRANSMIT_DESC = 0x48487000;
   CPPI_RECEIVE_DESC = 0x48486000;
   for (i = 1; i <= 24; i++)
   {
      cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, naddr), 0x00000000);
      naddr = naddr + 0x4;
   }

   //to clear the ALE table
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_CONTROL), 0x40000000);
   cc_no_op (100);

}

/*==================== Function Separator =============================*/
/*#############################################
  Configure the DUT SIDE CPSW_3G
############################################# */
/* Note: CPPI RAM starts from 0x6000 and ends at 0x6FFF. 6000 to 6FFF is used as receive space, while 7000 to 7FFF is used as transmit space*/
   void
CPSW_3GSS_R_setup ()
{
   int i, status = 0;
   //Enable the Pacing and config the interrupts
   //HW_WR_REG32(0x4848520c /*WR_INT_CONTROL*/,0x00030000+PACE_PRESCALE);
   //HW_WR_REG32(0x48485270/*C0_RX_IMAX*/,0x2);
#if RX_INTR
   status +=
      IRQXBARConnect (SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 47,
            GMAC_SW_IRQ_RX_PULSE);

   // TODO error check if (status != irq_xbar_success)
   /* Register Mailbox interrupt for M4 */
   Intc_IntRegister (69, (IntrFuncPtr) CPSW_3GSS_R_chk_rx_int, NULL);
   Intc_IntPrioritySet (69, 1, 0);
   Intc_SystemEnable (69);
#endif
#if TX_INTR
   status =
      IRQXBARConnect (SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 48,
            GMAC_SW_IRQ_TX_PULSE);

   // TODO error check if (status != irq_xbar_success)
   /* Register Mailbox interrupt for M4 */
   Intc_IntRegister (70, (IntrFuncPtr) CPSW_3GSS_R_chk_tx_int, NULL);
   Intc_IntPrioritySet (70, 1, 0);
   Intc_SystemEnable (70);

   //Tx pacing
   //HW_WR_REG32(0x48485274 /*C0_TX_IMAX*/,0x2);


   //WR_MEM_32_VOLATILE(TX_INTMASK_SET,0x000000ff);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, TX_INTMASK_SET), 0x000000ff);
   //WR_MEM_32_VOLATILE(C0_TX_EN,0xff);
   cc_reg_write (cc_reg_addr_trans (CPSW_3GSS_RG_BASE, C0_TX_EN), 0x00000001);
#endif
   /* Enable The CPDMA TX DMA Controller (Bits 31:1 are reserved) */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, TX_CONTROL), 0x00000001);

   /* Enable The CPDMA RX DMA Controller (Bits 31:1 are reserved) */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX_CONTROL), 0x00000001);

   /* Enable the CPDMA transmit interrupts (Enable tx channel 0 thru 7 interrupts) */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, TX_INTMASK_SET), 0x000000ff);

   /* Enable the CPDMA receive interrupts (Read Rx threshold masked interrupts and Rx pend masked interrupts) */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX_INTMASK_SET), 0x0000ffff);

   /* Enable all ports for statistics (Port 0,1 and 2 statistics are enabled) */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, STAT_PORT_EN), 0x7);

   /* Load up the FREEBUFFERS (Used to indicate the count of free buffers available) */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX0_FREEBUFFER), 0x8000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX1_FREEBUFFER), 0x8000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX2_FREEBUFFER), 0x8000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX3_FREEBUFFER), 0x8000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX4_FREEBUFFER), 0x8000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX5_FREEBUFFER), 0x8000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX6_FREEBUFFER), 0x8000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX7_FREEBUFFER), 0x8000);


   //    cc_reg_write(cc_reg_addr_trans(CPSW_3GSS_RG_BASE, RGMII_CTL), 0x000000EE);

   /** Configure_ALE **/
#if !ALE_BYPASS
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, P0_TX_PRI_MAP), 0x0);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, P1_TX_PRI_MAP), 0x0);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, P2_TX_PRI_MAP), 0x0);
   /* Initialize the DUT ALE (ALE enabled and bypassed) (31- (1) Enable ALE packet processing, 4- (1) All packets received on port 0 and 1 are sent to host   */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_CONTROL), 0x80000000);

   /* Port state bits 0 thru 1 is set to "Forward" state. */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_PORTCTL0), 0x00000013);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_PORTCTL1), 0x00000013);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_PORTCTL2), 0x00000013);

   //Configure the PORT0
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBLW2), 0x00000000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBLW1), 0x10000000);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBLW0), 0x00000000);   //port1-port0
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBCTL), 0x80000000);
   //Configure the PORT1
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBLW2), 0x00000004);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBLW1), 0x10001111);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBLW0), 0x11111111);   //port1-port0
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_TBCTL), 0x80000001);

#else
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_CONTROL), 0x80000010);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_PORTCTL0), 0x00000013);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_PORTCTL1), 0x00000013);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, ALE_PORTCTL2), 0x00000013);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, P0_TX_PRI_MAP), 0x0);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, P1_TX_PRI_MAP), 0x0);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, P2_TX_PRI_MAP), 0x0);
#endif


   cc_no_op (5000);

   /* Enable the CPGMAC_SL's (Enable GMII RX and TX ; Enable full duplex mode) */
#if (1 == ENABLE_100MBPS_MODE)
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, SL2_MACCONTROL), 0x00000021);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, SL1_MACCONTROL), 0x00000021);
#else
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, SL2_MACCONTROL), 0x000000A1);
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, SL1_MACCONTROL), 0x000000A1);
#endif
#if RX_INTR
   cc_reg_write (cc_reg_addr_trans (CPSW_3GSS_RG_BASE, C0_RX_EN), 0xff);
#endif
#if TX_INTR
   /* Enable the bits in the tx interrupt for interrupt generation */
   cc_reg_write (cc_reg_addr_trans (CPSW_3GSS_RG_BASE, C0_TX_EN), 0xff);
#endif


   /*---------------------------------------*/
   /*First program the TX Buffer Descriptor.
Format:
Word 0: Next buffer pointer.
Set to all 0's to indicate current buffer is the last buffer.
Word 1: Pointer (31:0) (The memory address of the buffer assosicated by buffer desc).
This will point to OCMC ram - set to 0x6000.
Word 2: Buffer Offset (31:16), Buffer Length (15:0)
Buffer offset set to all 0's while buffer length is set to 40 (64 bytes)
Word 3: SOP(31), EOP(30), Ownership(29), EOQ(28), teardown complete(27), pass crc(26), to_port en(20), to_port(17:16), Pkt Ln(15:0)
0x1    , 0x1    , 0x1          , 0x0    , 0x0                  , 0x01        , 0x01          , 0x01          , 0x40 */
   /*---------------------------------------*/
   /** Configure the Tx CPPI descriptors **/
#if TX_MODE
#if CPPI_BUFFER
   CPPI_Tx_NDP = CPPI_RAM_BASE + 0x1010;
   for (i = 0; i < PCK_NO; i++)
   {
      CPPI_Tx_LEN = PCK_SIZE[i];
#if (1 == PORT1_ENABLED)
        CPPI_Tx_PORT = 0xe0110000 + CPPI_Tx_LEN;
#else
        CPPI_Tx_PORT = 0xe0120000 + CPPI_Tx_LEN;
#endif
      if (i == (PCK_NO - 1))
      {
         HW_WR_REG32 (CPPI_TRANSMIT_DESC, 0x00000000);
      }
      else
      {
         HW_WR_REG32 (CPPI_TRANSMIT_DESC, CPPI_Tx_NDP);
      }
      CPPI_Tx_BUF = (uint32_t) TxBufferData[i];
      HW_WR_REG32 (CPPI_TRANSMIT_DESC + 0x4, CPPI_Tx_BUF);
      HW_WR_REG32 (CPPI_TRANSMIT_DESC + 0x8, CPPI_Tx_LEN);
      HW_WR_REG32 (CPPI_TRANSMIT_DESC + 0xc, CPPI_Tx_PORT);
      CPPI_TRANSMIT_DESC += 0x00000010;
      CPPI_Tx_NDP += 0x00000010;
   }
#else
   /**** configure for CPPI in OCMC/DDR  ****/
   /** Configure the Tx CPPI descriptors **/
   for (i = 0; i < PCK_NO; i++)
   {
      CPPI_Tx_LEN = PCK_SIZE[i];
#if (1 == PORT1_ENABLED)
        CPPI_Tx_PORT = 0xe0110000 + CPPI_Tx_LEN;
#else
        CPPI_Tx_PORT = 0xe0120000 + CPPI_Tx_LEN;
#endif
      if (i == (PCK_NO - 1))
      {
         TxDesc[i].Tx_CPPI_NDP = 0;

      }
      else
      {
         TxDesc[i].Tx_CPPI_NDP = (uint32_t) TxDesc + (16 * (i + 1));
      }
      TxDesc[i].Tx_CPPI_BUF = (uint32_t) TxBufferData[i];
      TxDesc[i].Tx_CPPI_PCK_LEN = PCK_SIZE[i];
      TxDesc[i].Tx_CPPI_PCK_CONFIG = CPPI_Tx_PORT;
   }

#endif
#endif

   /*---------------------------------------*/
   /* Program the RX Buffer Descriptor.
Format:
Word 0: Next buffer pointer.
Set to all 0's to indicate current buffer is the last buffer.
Word 1: Pointer (31:0) (The memory address of the buffer assosicated by buffer desc).
This will point to OCMC ram - set to 0x6500.
Word 2: Buffer Offset (31:16), Buffer Length (15:0)
Buffer offset set to all 0's while buffer length is set to 40 (64 bytes)
Word 3: SOP(31), EOP(30), Ownership(29), EOQ(28), teardown complete(27), passed crc(26), long (25), short(24), mac_ctl(23),
0x0    , 0x1    , 0x0          , 0x0    , 0x0                  , 0x0           , 0x0      , 0x0      , 0x0        ,
Word 3: overrun(22), pkt_err(21:20), vlan_encap(19), from_port(18), packet_length(10:0)
0x0        , 0x0           , 0x0           , 0x0          , 0x40               */
   /*---------------------------------------*/

   /*---------------------------------------*/
   /* Define the mem space, in which the received packets will be stored  */
   /*---------------------------------------*/
#if RX_MODE
#if CPPI_BUFFER
   CPPI_Rx_NDP = CPPI_RAM_BASE + 0x10;
   for (i = 0; i < PCK_NO; i++)
   {
      if (i == (PCK_NO - 1))
      {
         HW_WR_REG32 (CPPI_RECEIVE_DESC, 0x00000000);
      }
      else
      {
         HW_WR_REG32 (CPPI_RECEIVE_DESC, CPPI_Rx_NDP);
      }
      CPPI_Rx_BUF = (uint32_t) RxBufferData[i];
      HW_WR_REG32 (CPPI_RECEIVE_DESC + 0x4, CPPI_Rx_BUF);
      HW_WR_REG32 (CPPI_RECEIVE_DESC + 0x8, CPPI_Rx_LEN);
      HW_WR_REG32 (CPPI_RECEIVE_DESC + 0xc, (0x20000000 + PCK_SIZE[i]));
      CPPI_RECEIVE_DESC += 0x00000010;
      CPPI_Rx_NDP += 0x00000010;

   }
#else
   /**** configure for CPPI in OCMC/DDR  ****/
   /** Configure the Tx CPPI descriptors **/
   for (i = 0; i < PCK_NO; i++)
   {
      CPPI_Tx_LEN = PCK_SIZE[i];
      if (i == (PCK_NO - 1))
      {
         RxDesc[i].Rx_CPPI_NDP = 0;
      }
      else
      {
         RxDesc[i].Rx_CPPI_NDP = (uint32_t) RxDesc + (16 * (i + 1));
      }
      RxDesc[i].Rx_CPPI_BUF = (uint32_t) RxBufferData[i];
      RxDesc[i].Rx_CPPI_PCK_LEN = CPPI_Rx_LEN;
      RxDesc[i].Rx_CPPI_PCK_CONFIG = (0x20000000 + PCK_SIZE[i]);

   }
#endif
#endif
}            /* End of CPSW_3GSS_R_setup function */

   uint32_t
CPSW_Start_Transfer ()
{
   uint32_t checkReturn = RET_FAIL;


#if  !CPPI_BUFFER
#if RX_MODE
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX0_HDP), (uint32_t) RxDesc);
#endif
   CounterValue1 = timerRead (TIMER_NUM);
   TxStartcount = timerRead (TIMER_NUM);
#if RX_MODE
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, TX0_HDP), (uint32_t) TxDesc);
#endif
#else
   /* Program RX0_HDP to CPDMA receive initiator base address */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, RX0_HDP), 0x48486000);
   CounterValue1 = timerRead (TIMER_NUM);
   TxStartcount = timerRead (TIMER_NUM);
   /* Define the host memory address for the first buffer descriptor in the channel tx queue. */
   cc_reg_write (cc_reg_addr_trans (CPSW_3G_BASE, TX0_HDP), 0x48487000);
#endif

   return checkReturn;
}

/*==================== Function Separator =============================*/
   uint32_t
CPSW_Complete_Transfer ()
{
   uint32_t checkReturn = RET_FAIL;
#if TX_MODE
   cc_poll_reg (cc_reg_addr_trans (CPSW_3G_BASE, TX_INTSTAT_RAW), 0x00000001,
         0xffffffff);
#endif
   /*---------------------------------------*/
   /* Wait for the RX Ch0 dma hdp register to go to 0x00000000 */
   /* This indicates that the RX ch0 has reached the end of queue and all the pkts on that ch have been rcved */
   /*---------------------------------------*/
#if RX_MODE
   cc_poll_reg (cc_reg_addr_trans (CPSW_3G_BASE, RX0_HDP), 0x00000000,
         0xffffffff);
#endif

#if TX_INTR
   while (lv_txInth != PCK_NO)
   {
   }
#endif
#if RX_INTR
   while (lv_rxInth != PCK_NO)
   {
   }
#endif
   /*STOP TIMER */
   TIMERDisable (TIMER_NUM);
   return checkReturn;
}



/*==================== Function Separator =============================*/
   void
Throughput_Measure ()
{
   DiffCount = TxStartcount - CounterValue1;
#if TX_INTR
   TOTAL_DATA_TRANSFER_TX = ((PCK_NO) * PCK_SIZE[0] * 8);
   TRANSMIT_TIME = TxEndcount - (TxStartcount + DiffCount);
   TX_Throughput = (TOTAL_DATA_TRANSFER_TX * TIMER_FREQ) / (TRANSMIT_TIME);
   TX_Throughput_Mbps = (TX_Throughput * 1000000) / (1048576);
#endif

   TOTAL_DATA_TRANSFER_RX = ((PCK_NO - 1) * PCK_SIZE[0] * 8);
   RECEIVE_TIME = RxEndcount - RxStartcount;
   RX_Throughput = (TOTAL_DATA_TRANSFER_RX * TIMER_FREQ) / (RECEIVE_TIME);
   RX_Throughput_Mbps = (RX_Throughput * 1000000) / (1048576);

   TOTAL_DATA_TRANSFER_TX_RX = (PCK_NO * PCK_SIZE[0] * 8 * 2);
   TX_RX_TIME = RxEndcount - (TxStartcount + DiffCount);
   TX_RX_Throughput = (TOTAL_DATA_TRANSFER_TX_RX * TIMER_FREQ) / (TX_RX_TIME);
   TX_RX_Throughput_Mbps = (TX_RX_Throughput * 1000000) / (1048576);


}

/*==================== Function Separator =============================*/
   void
Throughput_Results ()
{
   RxResult.RX_PCK_NO = PCK_NO - 1;
   RxResult.RX_PCK_SIZE = PCK_SIZE[0];
   RxResult.RX_ST_COUNT = RxStartcount;
   RxResult.RX_END_COUNT = RxEndcount;
   RxResult.RX_TOTAL_COUNT = RECEIVE_TIME;
   RxResult.RX_DATA_TRANSFER = TOTAL_DATA_TRANSFER_RX;
   RxResult.RX_TIMER_FREQ = TIMER_FREQ;
   RxResult.RX_THR = RX_Throughput;
   RxResult.RX_THR_MPS = RX_Throughput_Mbps;
   RxResult.TX_PCK_NO = PCK_NO;
   RxResult.TX_PCK_SIZE = PCK_SIZE[0];
   RxResult.TX_ST_COUNT = TxStartcount;
   RxResult.TX_END_COUNT = TxEndcount;
   RxResult.TX_TOTAL_COUNT = TRANSMIT_TIME;
   RxResult.TX_DATA_TRANSFER = TOTAL_DATA_TRANSFER_TX;
   RxResult.TX_TIMER_FREQ = TIMER_FREQ;
   RxResult.TX_THR = TX_Throughput;
   RxResult.TX_THR_MPS = TX_Throughput_Mbps;
   RxResult.TX_RX_PCK_NO = PCK_NO * 2;
   RxResult.TX_RX_PCK_SIZE = PCK_SIZE[0];
   RxResult.TX_RX_ST_COUNT = TxStartcount;
   RxResult.TX_RX_END_COUNT = RxEndcount;
   RxResult.TX_RX_TOTAL_COUNT = RECEIVE_TIME;
   RxResult.TX_RX_DATA_TRANSFER = TOTAL_DATA_TRANSFER_TX_RX;
   RxResult.TX_RX_TIMER_FREQ = TIMER_FREQ;
   RxResult.TX_RX_THR = TX_RX_Throughput;
   RxResult.TX_RX_THR_MPS = TX_RX_Throughput_Mbps;
}


/*==================== Function Separator =============================*/
   uint32_t
Check_Data ()
{
   /*---------------------------------------*/
   /* Read the data stored in RX memory. Compare the same with expected data. Flag out an error if data is incorrect */
   /*---------------------------------------*/

   uint32_t TX_DATA, RX_DATA = 0;
   uint32_t i, *rdPtr, *wrPtr, checkReturn = RET_OK;


   for (i = 0; i < PCK_NO; i++)
   {
      TX_DATA = (uint32_t) TxBufferData[i];
      RX_DATA = (uint32_t) RxBufferData[i];
      rdPtr = (uint32_t *) (RX_DATA);
      wrPtr = (uint32_t *) (TX_DATA);
      if (!
            (MEMUTIL_Compare32
             ((uint32_t *) rdPtr, (uint32_t *) wrPtr, PCK_SIZE[0] / 8)))
      {
         Count_Pck = Count_Pck + 1;
      }
   }
   if (Count_Pck == PCK_NO)
   {
      RES_Set (RES_OK);
      printf ("TC :: Data check passed with received packets \r\n");
   }
   else
   {
      //data_fail++ ;
      RES_Set (RES_BAD);
      printf ("TC :: Data check passed with received packets \r\n");
      checkReturn = RET_FAIL;
   }
   return checkReturn;
}

/*==================== Function Separator =============================*/

#pragma CODE_SECTION(CPSW_3GSS_R_chk_rx_int, ".intc_text")
   void
CPSW_3GSS_R_chk_rx_int ()
{

   /***********Measure the RX count ***********/
   if (lv_rxInth == (PCK_NO - 1))
   {
      RxEndcount = timerRead (TIMER_NUM);
   }
#if CPPI_BUFFER

   /* Now the interrupt has been rcved write the completion pointer to clear interrupt */
   HW_WR_REG32 (0x48484a60 /*RX0_CP */ , CPPI_RAM_BASE + (16 * lv_rxInth));

#else
   /* Now the interrupt has been rcved write the completion pointer to clear interrupt */
   HW_WR_REG32 (0x48484a60 /*RX0_CP */ , (uint32_t) RxDesc + (16 * lv_rxInth));
#endif

   //eoi vector
   HW_WR_REG32 (0x48484894 /*CPDMA_EOI_VECTOR */ , 0x1);

   if (lv_rxInth == 0)
   {
      RxStartcount = timerRead (TIMER_NUM);
   }
   lv_rxInth++;
   return;
}

/*==================== Function Separator =============================*/
#if TX_INTR
#pragma CODE_SECTION(CPSW_3GSS_R_chk_tx_int, ".intc_text")
   void
CPSW_3GSS_R_chk_tx_int ()
{
   /*---------------------------------------*/
   /* Wait for the RX Ch0 dma hdp register to go to 0x00000000 */
   /* This indicates that the RX ch0 has reached the end of queue and all the pkts on that ch have been rcved */
   /*---------------------------------------*/
   if (lv_txInth == (PCK_NO - 1))
   {
      TxEndcount = timerRead (TIMER_NUM);
   }


#if CPPI_BUFFER
   /* Now the interrupt has been rcved write the completion pointer to clear interrupt */
   HW_WR_REG32 (0x48484a40 /*TX0_CP */ ,
         (CPPI_RAM_BASE + 0x1000) + (16 * lv_txInth));
#else
   /* Now the interrupt has been rcved write the completion pointer to clear interrupt */
   HW_WR_REG32 (0x48484a40 /*TX0_CP */ , (uint32_t) TxDesc + (16 * lv_txInth));
#endif

   /* E0I vector */
   HW_WR_REG32 (0x48484894 /*CPDMA_EOI_VECTOR */ , 0x2);

   /*Indicates the no of Interrupts */
   lv_txInth++;

   return;

}            /* End of CPSW_3GSS_R_chk_tx_int function */
#endif
