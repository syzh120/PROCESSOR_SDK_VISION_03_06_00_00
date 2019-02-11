/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 */

 /**
 *  \file   i2c.h
 *
 *  \brief  I2C driver header file
 *
 */

#ifndef I2C_H_
#define I2C_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct
{
    volatile uint32_t I2C_REVNB_LO;                 /* 0x00 */
    volatile uint32_t I2C_REVNB_HI;                 /* 0x04 */
    volatile uint32_t RSVD0[2];
    volatile uint32_t I2C_SYSC;                     /* 0x10 */
    volatile uint32_t RSVD1[3];
    volatile uint32_t I2C_EOI;                      /* 0x20 */
    volatile uint32_t I2C_IRQSTATUS_RAW;            /* 0x24 */
    volatile uint32_t I2C_IRQSTATUS;                /* 0x28 */
    volatile uint32_t I2C_IRQENABLE_SET;            /* 0x2C */
    volatile uint32_t I2C_IRQENABLE_CLR;            /* 0x30 */
    volatile uint32_t I2C_WE;                       /* 0x34 */
    volatile uint32_t I2C_DMARXENABLE_SET;          /* 0x38 */
    volatile uint32_t I2C_DMATXENABLE_SET;          /* 0x3C */
    volatile uint32_t I2C_DMARXENABLE_CLR;          /* 0x40 */
    volatile uint32_t I2C_DMATXENABLE_CLR;          /* 0x44 */
    volatile uint32_t I2C_DMARXWAKE_EN;             /* 0x48 */
    volatile uint32_t I2C_DMATXWAKE_EN;             /* 0x4C */
    volatile uint32_t RSVD2[13];
    volatile uint32_t I2C_IE;                       /* 0x84 */
    volatile uint32_t I2C_STAT;                     /* 0x88 */
    volatile uint32_t RSVD3;                        /* 0x8C */
    volatile uint32_t I2C_SYSS;                     /* 0x90 */
    volatile uint32_t I2C_BUF;                      /* 0x94 */
    volatile uint32_t I2C_CNT;                      /* 0x98 */
    volatile uint32_t I2C_DATA;                     /* 0x9C */
    volatile uint32_t RSVD4;                        /* 0xA0 */
    volatile uint32_t I2C_CON;                      /* 0xA4 */
    volatile uint32_t I2C_OA;                       /* 0xA8 */
    volatile uint32_t I2C_SA;                       /* 0xAC */
    volatile uint32_t I2C_PSC;                      /* 0xB0 */
    volatile uint32_t I2C_SCLL;                     /* 0xB4 */
    volatile uint32_t I2C_SCLH;                     /* 0xB8 */
    volatile uint32_t I2C_SYSTEST;                  /* 0xBC */
    volatile uint32_t I2C_BUFSTAT;                  /* 0xC0 */
    volatile uint32_t I2C_OA1;                      /* 0xC4 */
    volatile uint32_t I2C_OA2;                      /* 0xC8 */
    volatile uint32_t I2C_OA3;                      /* 0xCC */
    volatile uint32_t I2C_ACTOA;                    /* 0xD0 */
    volatile uint32_t I2C_SBLOCK;                   /* 0xD4 */
} CSL_I2cRegs;

/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_I2cRegs            *CSL_I2cRegsOvly;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/
/* I2C Interrupt Enable Register (I2C_IE): */
#define I2C_IE_XDR          (1u << 14)   /* TX Buffer drain int enable */
#define I2C_IE_RDR          (1u << 13)   /* RX Buffer drain int enable */
#define I2C_IE_XRDY         (1u << 4)    /* TX data ready int enable */
#define I2C_IE_RRDY         (1u << 3)    /* RX data ready int enable */
#define I2C_IE_ARDY         (1u << 2)    /* Access ready int enable */
#define I2C_IE_NACK         (1u << 1)    /* No ack interrupt enable */
#define I2C_IE_AL           (1u << 0)    /* Arbitration lost int ena */

/* I2C Status Register (I2C_STAT): */
#define I2C_STAT_XDR        (1u << 14)   /* TX Buffer draining */
#define I2C_STAT_RDR        (1u << 13)   /* RX Buffer draining */
#define I2C_STAT_BB         (1u << 12)   /* Bus busy */
#define I2C_STAT_ROVR       (1u << 11)   /* Receive overrun */
#define I2C_STAT_XUDF       (1u << 10)   /* Transmit underflow */
#define I2C_STAT_AAS        (1u << 9)    /* Address as slave */
#define I2C_STAT_AD0        (1u << 8)    /* Address zero */
#define I2C_STAT_XRDY       (1u << 4)    /* Transmit data ready */
#define I2C_STAT_RRDY       (1u << 3)    /* Receive data ready */
#define I2C_STAT_ARDY       (1u << 2)    /* Register access ready */
#define I2C_STAT_NACK       (1u << 1)    /* No ack interrupt enable */
#define I2C_STAT_AL         (1u << 0)    /* Arbitration lost int ena */

/* I2C WE wakeup enable register */
#define I2C_WE_XDR_WE       (1u << 14)   /* TX drain wakup */
#define I2C_WE_RDR_WE       (1u << 13)   /* RX drain wakeup */
#define I2C_WE_AAS_WE       (1u << 9)    /* Address as slave wakeup*/
#define I2C_WE_BF_WE        (1u << 8)    /* Bus free wakeup */
#define I2C_WE_STC_WE       (1u << 6)    /* Start condition wakeup */
#define I2C_WE_GC_WE        (1u << 5)    /* General call wakeup */
#define I2C_WE_DRDY_WE      (1u << 3)    /* TX/RX data ready wakeup */
#define I2C_WE_ARDY_WE      (1u << 2)    /* Reg access ready wakeup */
#define I2C_WE_NACK_WE      (1u << 1)    /* No acknowledgment wakeup */
#define I2C_WE_AL_WE        (1u << 0)    /* Arbitration lost wakeup */

#define I2C_WE_ALL          (I2C_WE_XDR_WE | I2C_WE_RDR_WE |   \
                             I2C_WE_AAS_WE | I2C_WE_BF_WE |    \
                             I2C_WE_STC_WE | I2C_WE_GC_WE |    \
                             I2C_WE_DRDY_WE | I2C_WE_ARDY_WE | \
                             I2C_WE_NACK_WE | I2C_WE_AL_WE)

/* I2C Buffer Configuration Register (I2C_BUF): */
#define I2C_BUF_RDMA_EN     (1u << 15)   /* RX DMA channel enable */
#define I2C_BUF_RXFIF_CLR   (1u << 14)   /* RX FIFO Clear */
#define I2C_BUF_XDMA_EN     (1u << 7)    /* TX DMA channel enable */
#define I2C_BUF_TXFIF_CLR   (1u << 6)    /* TX FIFO Clear */

/* I2C Configuration Register (I2C_CON): */
#define I2C_CON_EN          (1u << 15)   /* I2C module enable */
#define I2C_CON_BE          (1u << 14)   /* Big endian mode */
#define I2C_CON_OPMODE_HS   (1u << 12)   /* High Speed support */
#define I2C_CON_STB         (1u << 11)   /* Start byte mode (master) */
#define I2C_CON_MST         (1u << 10)   /* Master/slave mode */
#define I2C_CON_TRX         (1u << 9)    /* TX/RX mode (master only) */
#define I2C_CON_XA          (1u << 8)    /* Expand address */
#define I2C_CON_RM          (1u << 2)    /* Repeat mode (master only) */
#define I2C_CON_STP         (1u << 1)    /* Stop cond (master only) */
#define I2C_CON_STT         (1u << 0)    /* Start condition (master) */

/* I2C SCL time value when Master */
#define I2C_SCLL_HSSCLL    (8u)
#define I2C_SCLH_HSSCLH    (8u)

/* OCP_SYSSTATUS bit definitions */
#define SYSS_RESETDONE_MASK         (1u << 0)

/* OCP_SYSCONFIG bit definitions */
#define SYSC_CLOCKACTIVITY_MASK     (0x3u << 8)
#define SYSC_CLOCKACTIVITY_SHIFT    (8u)
#define SYSC_SIDLEMODE_MASK         (0x3u << 3)
#define SYSC_IDLEMODE_SHIFT         (3u)
#define SYSC_ENAWAKEUP_MASK         (1u << 2)
#define SYSC_SOFTRESET_MASK         (1u << 1)
#define SYSC_AUTOIDLE_MASK          (1u << 0)

#define SYSC_IDLEMODE_SMART         (0x2u)
#define SYSC_CLOCKACTIVITY_FCLK     (0x2u)

#define I2C_ADDR_MASK               (0x7Fu)

/**
 * Max I2C driver opens allowed.
 * Note: If required, this number can be increased
 */
#define I2C_NUM_OPENS                       (4u)

/** Min I2C bus frequency - 1 KHz */
#define I2C_MIN_BUS_FREQ                    (1u)
/** Max I2C bus frequency - 400 KHz */
#define I2C_MAX_BUS_FREQ                    (400u)

/** Bus Busy Timeout (counter, should depend upon CPU speed) */
#define I2C_BUS_BUSY_TIMEOUT_CNT            (10000000u)
/** Bus Busy Timeout (mSecs) */
#define I2C_BUS_BUSY_TIMEOUT_MSECS          (10u)

/* I2C data transfer timeout (in mSecs) */
#define I2C_DATA_TRANSFER_TIMEOUT_SECS      (1000u)

/* I2C device busy timeout (in mSecs) */
#define I2C_DEVICE_BUSY_TIMEOUT_SECS        (5000u)

/** Maximum buffer length which could be transferred */
#define I2C_BUFFER_MAXLENGTH                (65536u)

#define I2C_DELAY_MULTIPLIER                (100u)

/**
 * \brief I2C driver state
 *
 *  These enums are used to maintain the current state of the driver
 */
typedef enum
{
  I2C_DELETED = 0u,         /**< Instance Deleted */
  I2C_CREATED,              /**< Instance Created */
  I2C_OPENED,               /**< Instance Open */
  I2C_CLOSED                /**< Instance Closed */
} I2cState;

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define I2C_TIMEOUT                     (0xFFFFFFFFU)

#define I2C_READ_REG_BYTE(reg)          (*(volatile unsigned char *)(reg))
#define I2C_READ_REG_WORD(reg)          (*(volatile uint32_t *)(reg))
#define I2C_READ_REG_LONG(reg)          (*(volatile unsigned int *)(reg))

#define I2C_WRITE_REG_BYTE(val, reg)    (*(volatile unsigned char *)(reg) = (val))
#define I2C_WRITE_REG_WORD(val, reg)    (*(volatile uint32_t *)(reg) = (val))
#define I2C_WRITE_REG_LONG(val, reg)    (*(volatile unsigned int *)(reg) = (val))

#define I2C_STANDARD                    (100000)
#define I2C_FAST_MODE                   (400000)
#define I2C_HIGH_SPEED                  (3400000)

/* I2C functional clock is 96MHz */
#define I2C_FUNC_CLOCK                  (96000000)
#define I2C_BUS_FREQ                    (100)
#if (I2C_BUS_FREQ > 100)
  #define I2C_CLK_FREQ                  (12000)
#else
  #define I2C_CLK_FREQ                  (4000)
#endif

#define I2C_FASTSPEED_SCLL_TRIM         (7)
#define I2C_FASTSPEED_SCLH_TRIM         (5)

#define I2C_DELAY_BIG                   (500000)
#define I2C_DELAY_MED                   (10000)
#define I2C_DELAY_SMALL                 (10000)

#define I2C_ERR_TIMEDOUT                (-(int32_t)100)
#define I2C_ERR_INVALID_PARAMS          (-(int32_t)101)
#define I2C_ERR_IO                      (-(int32_t)102)

/**
 *  \brief I2C Transfer Params
 *
 *  This structure holds the information needed to carry out a transaction on
 *  I2C bus to a slave device.
 */
typedef struct
{
  uint8_t slaveAddr;
  /**< Address of the slave to talk to, not valid in Slave mode */
  uint8_t *buffer;
  /**< Data buffer */
  uint32_t bufLen;
  /**< Length of buffer */
  uint32_t flags;
  /**< Flags to indicate the various modes of operation */
  uint32_t timeout;
  /**< Timeout value */
  void *param;
  /**< Extra parameter for future use */
} I2c_XferParams;

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * I2C Driver Error codes
 */

/** \brief  Returned when the I2C bus find that the bus is busy */
#define I2C_BUS_BUSY_ERR                       ((uint32_t) -1)

/** \brief  Returned when the I2C driver lost the bus arbitration */
#define I2C_ARBITRATION_LOSS_ERR               ((uint32_t) -2)

/** \brief  Returned when the I2C slave did not acknowledgement */
#define I2C_NACK_ERR                           ((uint32_t) -3)

/** \brief  Returned in case of an transmit underflow error */
#define I2C_TRANSMIT_UNDERFLOW_ERR             ((uint32_t) -4)

/** \brief  Returned in case of an receive overflow error */
#define I2C_RECEIVE_OVERFLOW_ERR               ((uint32_t) -5)

/* Note: The following flags offer the user maximum flexibility in terms
 * of making the right I2C transaction. In case the user does not want
 * to set the flags on his own, the default read/write flag can be specified
 */

/** \brief  Read from I2C bus (device) */
#define I2C_READ                (0x0001u)

/** \brief   Write to I2C bus (device) */
#define I2C_WRITE               (0x0002u)

/** \brief   Configure I2C in Master mode */
#define I2C_MASTER              (0x0004u)

/** \brief   Configure I2C in Slave mode (currently not supported) */
#define I2C_SLAVE               (0x0008u)

/** \brief   Generate Start - valid in master mode only */
#define I2C_START               (0x0010u)

/** \brief   Generate Stop - valid in master mode only */
#define I2C_STOP                (0x0020u)

/** \brief   Re-Start is generated by Master */
#define I2C_RESTART             (0x0040u)

/** \brief   Repeat mode */
#define I2C_REPEAT              (0x0080u)

/** \brief   Ignore Bus Busy condition */
#define I2C_IGNORE_BUS_BUSY     (0x0100u)

/** \brief   Ignore NAK */
#define I2C_M_IGNORE_NAK        (0x0200u)

/* Use these flags for simple MASTER read/write transactions on the I2C bus */
/** \brief  Default read flag */
#define I2C_DEFAULT_READ \
  (I2C_READ | I2C_MASTER | I2C_START | I2C_STOP)
/** \brief  Default write flag */
#define I2C_DEFAULT_WRITE \
  (I2C_WRITE | I2C_MASTER | I2C_START | I2C_STOP)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int I2C_init(uint32_t baseAddr);
int I2C_probe(uint32_t baseAddr, uint8_t slaveAddr);

uint32_t I2C_deviceRead8(uint32_t baseAddr, uint32_t devAddr,
                    const uint8_t *regAddr,
                    uint8_t *regValue, uint32_t numRegs);
uint32_t I2C_deviceWrite8(uint32_t baseAddr, uint32_t devAddr,
                     const uint8_t *regAddr,
                     const uint8_t *regValue, uint32_t numRegs);
uint32_t I2C_deviceRawRead8(uint32_t  baseAddr,
                       uint32_t  devAddr,
                       uint8_t *regValue,
                       uint32_t  numRegs);
uint32_t I2C_deviceRawWrite8(uint32_t  baseAddr,
                        uint32_t  devAddr,
                        uint8_t *regValue,
                        uint32_t  numRegs);
uint32_t I2C_deviceWrite16(uint32_t baseAddr, uint32_t devAddr,
                     uint16_t *regAddr,
                     const uint8_t *regValue, uint32_t numRegs);
uint32_t I2C_deviceRead16(uint32_t baseAddr, uint32_t devAddr,
                     uint16_t *regAddr,
                     uint8_t *regValue, uint32_t numRegs);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H_ */
