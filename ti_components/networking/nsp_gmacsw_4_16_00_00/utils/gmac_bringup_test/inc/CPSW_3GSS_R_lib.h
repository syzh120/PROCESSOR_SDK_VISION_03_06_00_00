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

// OCMC Ram base address
#define DUT_OCMC_MBASE          0x40300000

// 3PSW Sub System base address
#define CPSW_3GSS_R_BASE        0x48484000

// 3PSW Sub System base address
#define CPSW_3GSS_RG_BASE        0x48485000

// 3PSW Switch base address
#define CPSW_3G_BASE            0x48484000

// MDIO base address
#define MDIOBASE                0x48485000

// CPPI RAM base address
// This is the base address of the CPPI Ram from the HOST perspective (fixed)
#define CPPI_RAM_BASE           0x48486000
// This is the base address of the CPPI Ram from the CPGMAC perspective (default)
#define CPPI_RAM_BASE_MAC       0x02c82000

// 3PSW Switch register offsets

#define CPSW_IDVER              0x000
#define CPSW_CONTROL            0x004
#define CPSW_SOFT_RESET         0x008
#define STAT_PORT_EN            0x00C
#define PTYPE                   0x010
#define SOFT_IDLE               0x014
#define THRU_RATE               0x018
#define GAP_THRESH              0x01c
#define TX_START_WDS            0x020
#define FLOW_CONTROL            0x024
#define P0_MAX_BLKS             0x108
#define P0_BLK_CNT              0x10c
#define P0_TX_IN_CTL            0x110
#define P0_PORT_VLAN            0x114
#define P0_TX_PRI_MAP           0x118
#define CPDMA_TX_PRI_MAP        0x11c
#define CPDMA_RX_CH_MAP         0x120

#define P1_MAX_BLKS             0x208
#define P1_BLK_CNT              0x20c
#define P1_TX_IN_CTL            0x210
#define P1_PORT_VLAN            0x214
#define P1_TX_PRI_MAP           0x218
//#define P1_TS_CTL               0x064
//#define P1_TS_SEQ_LTYPE         0x068
#define P1_TS_SEQ_MTYPE         0x21c
//#define P1_TS_VLAN_LTYPE        0x06c
#define SL1_SA_LO               0x220
#define SL1_SA_HI               0x224
#define P1_SEND_PERCENT         0x228

#define P2_MAX_BLKS             0x308
#define P2_BLK_CNT              0x30c
#define P2_TX_IN_CTL            0x310
#define P2_PORT_VLAN            0x314
#define P2_TX_PRI_MAP           0x318
#define P2_TS_SEQ_MTYPE         0x31c
//#define P2_TS_CTL               0x0a4
//#define P2_TS_SEQ_LTYPE         0x0a8
//#define P2_TS_VLAN_LTYPE        0x0ac
#define SL2_SA_LO               0x320
#define SL2_SA_HI               0x324
#define P2_SEND_PERCENT         0x328

// CPDMA register offsets

#define CPTS_IDVER       0xc00
#define CPTS_CONTROL       0xc04
#define CPTS_RFTCLK_SEL    0xc08
#define CPTS_TS_PUSH       0xc0C
#define CPTS_TS_LOAD_VAL    0xc10
#define CPTS_TS_LOAD_EN    0xc14
#define CPTS_INTSTAT_RAW    0xc20
#define CPTS_IntSTAT_MASKED    0xc24
#define CPTS_INT_ENABLE    0xc28
#define CPTS_EVENT_POP       0xc30
#define CPTS_EVENT_LOW      0xc34
#define CPTS_EVENT_HIGH    0xc38

// ALE register offset

#define ALE_IDVER               0xd00
#define ALE_CONTROL             0xd08
#define ALE_PRESCALE            0xd10
#define ALE_UNKNOWN_VLAN        0xd18
#define ALE_TBCTL               0xd20
#define ALE_TBLW2               0xd34
#define ALE_TBLW1               0xd38
#define ALE_TBLW0               0xd3c
#define ALE_PORTCTL0            0xd40
#define ALE_PORTCTL1            0xd44
#define ALE_PORTCTL2            0xd48

// CPGMAC_SL1
#define SL1_IDVER               0xd80
#define SL1_MACCONTROL          0xd84
#define SL1_MACSTATUS           0xd88
#define SL1_SOFT_RESET          0xd8c
#define SL1_RX_MAXLEN           0xd90
#define SL1_BOFFTEST            0xd94
#define SL1_RX_PAUSETIMER       0xd98
#define SL1_TX_PAUSETIMER       0xd9c
#define SL1_EMCONTROL           0xda0
#define SL1_PRI_MAP             0xda4

// CPGMAC_SL2
#define SL2_IDVER               0xdc0
#define SL2_MACCONTROL          0xdc4
#define SL2_MACSTATUS           0xdc8
#define SL2_SOFT_RESET          0xdcc
#define SL2_RX_MAXLEN           0xdd0
#define SL2_BOFFTEST            0xdd4
#define SL2_RX_PAUSETIMER       0xdd8
#define SL2_TX_PAUSETIMER       0xddc
#define SL2_EMCONTROL           0xde0
#define SL2_PRI_MAP             0xde4

//#define SL0_RX_PRI_MAP                0x7A4

#define TX_IDVER                0x800
#define TX_CONTROL              0x804
#define TX_TEARDOWN             0x808
#define RX_IDVER                0x810
#define RX_CONTROL              0x814
#define RX_TEARDOWN             0x818
#define DMA_SOFT_RESET          0x81c
#define DMA_CONTROL             0x820
#define DMA_STATUS              0x824
#define RX_BUFFER_OFFSET        0x828
#define CPDMA_EMCONTROL         0x82c

#define TX_PRI0_RATE            0x830
#define TX_PRI1_RATE            0x834
#define TX_PRI2_RATE            0x838
#define TX_PRI3_RATE            0x83C
#define TX_PRI4_RATE            0x840
#define TX_PRI5_RATE            0x844
#define TX_PRI6_RATE            0x848
#define TX_PRI7_RATE            0x84C

// CPDMA INTERRUPT register offsets

#define TX_INTSTAT_RAW          0x880
#define TX_INTSTAT_MASKED       0x884
#define TX_INTMASK_SET          0x888
#define TX_INTMASK_CLEAR        0x88c
#define CPDMA_IN_VECTOR         0x890   //Also referred as MAC_IN_VECTOR
#define CPDMA_EOI_VECTOR        0x894
#define RX_INTSTAT_RAW          0x8a0
#define RX_INTSTAT_MASKED       0x8a4
#define RX_INTMASK_SET          0x8a8
#define RX_INTMASK_CLEAR        0x8ac
#define MAC_INTSTAT_RAW         0x8b0
#define MAC_INTSTAT_MASKED      0x8b4
#define MAC_INTMASK_SET         0x8b8
#define MAC_INTMASK_CLEAR       0x8bc
#define RX0_PENDTHRESH          0x8c0
#define RX1_PENDTHRESH          0x8c4
#define RX2_PENDTHRESH          0x8c8
#define RX3_PENDTHRESH          0x8cc
#define RX4_PENDTHRESH          0x8d0
#define RX5_PENDTHRESH          0x8d4
#define RX6_PENDTHRESH          0x8d8
#define RX7_PENDTHRESH          0x8dc
#define RX0_FREEBUFFER          0x8e0
#define RX1_FREEBUFFER          0x8e4
#define RX2_FREEBUFFER          0x8e8
#define RX3_FREEBUFFER          0x8ec
#define RX4_FREEBUFFER          0x8f0
#define RX5_FREEBUFFER          0x8f4
#define RX6_FREEBUFFER          0x8f8
#define RX7_FREEBUFFER          0x8fc

#define TX0_HDP                 0xa00
#define TX1_HDP                 0xa04
#define TX2_HDP                 0xa08
#define TX3_HDP                 0xa0c
#define TX4_HDP                 0xa10
#define TX5_HDP                 0xa14
#define TX6_HDP                 0xa18
#define TX7_HDP                 0xa1c


#define RX0_HDP                 0xa20
#define RX1_HDP                 0xa24
#define RX2_HDP                 0xa28
#define RX3_HDP                 0xa2c
#define RX4_HDP                 0xa30
#define RX5_HDP                 0xa34
#define RX6_HDP                 0xa38
#define RX7_HDP                 0xa3c

#define TX0_CP                  0xa40
#define TX1_CP                  0xa44
#define TX2_CP                  0xa48
#define TX3_CP                  0xa4c
#define TX4_CP                  0xa50
#define TX5_CP                  0xa54
#define TX6_CP                  0xa58
#define TX7_CP                  0xa5c

#define RX0_CP                  0xa60
#define RX1_CP                  0xa64
#define RX2_CP                  0xa68
#define RX3_CP                  0xa6c
#define RX4_CP                  0xa70
#define RX5_CP                  0xa74
#define RX6_CP                  0xa78
#define RX7_CP                  0xa7c

// 3PSW Subsystem register offsets

#define SS_IDVER                0x200
#define SS_SOFT_RESET           0x204
#define SS_EM_CONTROL           0x208
#define SS_INT_CONTROL          0x20c

#define C0_RX_THRESH_EN         0x210
#define C0_RX_EN                0x214
#define C0_TX_EN                0x218
#define C0_MISC_EN              0x21c

#define C1_RX_THRESH_EN         0x220
#define C1_RX_EN                0x224
#define C1_TX_EN                0x228
#define C1_MISC_EN              0x22c

#define C2_RX_THRESH_EN         0x230
#define C2_RX_EN                0x234
#define C2_TX_EN                0x238
#define C2_MISC_EN              0x23c

#define C0_RX_THRESH_STAT       0x240
#define C0_RX_STAT              0x244
#define C0_TX_STAT              0x248
#define C0_MISC_STAT            0x24c

#define C1_RX_THRESH_STAT       0x250
#define C1_RX_STAT              0x254
#define C1_TX_STAT              0x258
#define C1_MISC_STAT            0x25c

#define C2_RX_THRESH_STAT       0x260
#define C2_RX_STAT              0x264
#define C2_TX_STAT              0x268
#define C2_MISC_STAT            0x26c

#define C0_RX_IMAX              0x270
#define C0_TX_IMAX              0x274

#define C1_RX_IMAX              0x278
#define C1_TX_IMAX              0x27c

#define C2_RX_IMAX              0x280
#define C2_TX_IMAX              0x284

// Added these definitions
//
#define RXGOODFRAMES            0x900
#define RXBROADCASTFRAMES       0x904
#define RXMULTICASTFRAMES       0x908
#define RXPAUSEFRAMES           0x90C
#define RXCRCERRORS             0x910
#define RXALIGNCODEERRORS       0x914
#define RXOVERSIZEDFRAMES       0x918
#define RXJABBERFRAMES          0x91C
#define RXUNDERSIZEDFRAMES      0x920
#define RXFRAGMENTS             0x924
//#define RXFILTEREDFRAMES        0x928
//#define RXQOSFILTEREDFRAMES     0x92c
#define RXOCTETS                0x930
#define TXGOODFRAMES            0x934
#define TXBROADCASTFRAMES       0x938
#define TXMULTICASTFRAMES       0x93c
#define TXPAUSEFRAMES           0x940
#define TXDEFERREDFRAMES        0x944
#define TXCOLLISIONFRAMES       0x948
#define TXSINGLECOLLFRAMES      0x94c
#define TXMULTCOLLFRAMES        0x950
#define TXEXCESSIVECOLLISIONS   0x954
#define TXLATECOLLISIONS        0x958
#define TXUNDERRUN              0x95c
#define TXCARRIERSENSEERRORS    0x960
#define TXOCTETS                0x964
#define N64OCTETFRAMES          0x968
#define N65T127OCTETFRAMES      0x96c
#define N128T255OCTETFRAMES     0x970
#define N256T511OCTETFRAMES     0x974
#define N512T1023OCTETFRAMES    0x978
#define N1024TUPOCTETFRAMES     0x97c
#define NETOCTETS               0x980
#define RXSOFOVERRUNS           0x984
#define RXMOFOVERRUNS           0x988
#define RXDMAOVERRUNS           0x98c

#define MDIO_VER               0x00
#define MDIO_CONTROL           0x04
#define MDIO_ALIVE             0x08
#define MDIO_LINK              0x0c
#define MDIO_LINKINTRAW        0x10
#define MDIO_LINKINTMASKED     0x14
#define MDIO_USERINTRAW        0x20
#define MDIO_USERINTMASKED     0x24
#define MDIO_USERINTMASKSET    0x28
#define MDIO_USERINTMASKCLR    0x2c
#define MDIO_USERACCESS0       0x80
#define MDIO_USERPHYSEL0       0x84
#define MDIO_USERACCESS1       0x88
#define MDIO_USERPHYSEL1       0x8c
