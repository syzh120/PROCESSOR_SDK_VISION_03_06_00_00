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
 *  \file   i2c.c
 *
 *  \brief  I2C driver file
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "i2c.h"
#include <ti/csl/csl_types.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
   This below code always uses a single instance of I2C module indicated by
   I2C_BASE. This baseAddr parameter in several functions is kept for future
   functionality to use any of the I2C module specified. Currently this is unused.
 */
#define PRINT_ERROR printf("Error in I2C: %d\n", __LINE__);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint8_t tempReg;
volatile int a;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void udelay(int delay_usec)
{
    uint32_t delay_msec;
    uint32_t i;

    delay_msec = (delay_usec / 1000);
    if(delay_msec == 0)
    {
        delay_msec = 1;
    }
    for (i = 0; i < (delay_msec * 100); i++)
    {
        a = 0;
    }

    return;
}

/* No dependency on platform other than I2C_BASE which
 * is set compile-time.
 */
int I2C_init(uint32_t baseAddr)
{
    uint32_t fclk_rate, internal_clk;
    uint32_t psc         = 0, scll = 0, sclh = 0;
    uint32_t delay       = 1000;
    uint32_t reg_val     = 0;
    uint16_t selfAddress = 0xCC;
    CSL_I2cRegs  *I2C_BASE = (CSL_I2cRegs *) baseAddr;

    /* Reset all registers */
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_CON ));
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_PSC ));
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_SCLL));
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_SCLH));
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_BUF ));
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_SYSC));
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_WE  ));

    /* Soft-reset */
    I2C_WRITE_REG_WORD(SYSC_SOFTRESET_MASK, &(I2C_BASE->I2C_SYSC));
    I2C_WRITE_REG_WORD(I2C_CON_EN, &(I2C_BASE->I2C_CON) );

    /* Wait for the reset to get complete */
    while ((!(I2C_READ_REG_WORD(&(I2C_BASE->I2C_SYSS)) & SYSS_RESETDONE_MASK)) &&
          delay)
    {
        delay--;
        udelay(I2C_DELAY_SMALL);
    }
    if(!delay)
    {
        /* reset has failed, return!!! */
        PRINT_ERROR;
        return I2C_ERR_TIMEDOUT;
    }

    /* SYSC register is cleared by the reset, rewrite it */
    reg_val = SYSC_AUTOIDLE_MASK
              | SYSC_ENAWAKEUP_MASK
              | (SYSC_IDLEMODE_SMART << SYSC_IDLEMODE_SHIFT)
              | (SYSC_CLOCKACTIVITY_FCLK << SYSC_CLOCKACTIVITY_SHIFT);
    I2C_WRITE_REG_WORD(reg_val, &(I2C_BASE->I2C_SYSC));

    /* Disable it again */
    I2C_WRITE_REG_WORD(0, &(I2C_BASE->I2C_CON));

    internal_clk = I2C_CLK_FREQ;

    /* Compute prescaler divisor */
    fclk_rate = I2C_FUNC_CLOCK / 1000;
    psc       = fclk_rate / internal_clk;
    psc       = psc - 1;

    /* Standard and fast speed (upto 400Khz) */
    scll = sclh = internal_clk / (2 * I2C_BUS_FREQ);

    scll -= I2C_FASTSPEED_SCLL_TRIM;
    sclh -= I2C_FASTSPEED_SCLH_TRIM;

    I2C_WRITE_REG_WORD(psc,  &(I2C_BASE->I2C_PSC ));
    I2C_WRITE_REG_WORD(scll, &(I2C_BASE->I2C_SCLL));
    I2C_WRITE_REG_WORD(sclh, &(I2C_BASE->I2C_SCLH));

    /* Own address */
    I2C_WRITE_REG_WORD(selfAddress, &(I2C_BASE->I2C_OA));

    /* Take the I2C module out of reset: */
    I2C_WRITE_REG_WORD(I2C_CON_EN, &(I2C_BASE->I2C_CON));

    /* Enable interrupts, if required */
    if (0)
    {
      I2C_WRITE_REG_WORD(I2C_IE_XRDY | I2C_IE_RRDY | I2C_IE_ARDY |
                         I2C_IE_NACK | I2C_IE_AL, &I2C_BASE->I2C_IE);
    }

    /* Clear STAT register */
    I2C_WRITE_REG_WORD(0xFFFFu, &(I2C_BASE->I2C_STAT));
    /* Read it again */
    reg_val = I2C_READ_REG_WORD(&(I2C_BASE->I2C_STAT));

    reg_val = I2C_READ_REG_WORD(&(I2C_BASE->I2C_SYSTEST));
    I2C_WRITE_REG_WORD((reg_val|0x4000U), &(I2C_BASE->I2C_SYSTEST));

    return (0);
}

static int wait_for_bb(uint32_t baseAddr)
{
    volatile int timeout = 5000;
    uint16_t          stat;
    int          res = STW_SOK;
    CSL_I2cRegs  *I2C_BASE = (CSL_I2cRegs *) baseAddr;

    /* Clear current interrupts...*/
    I2C_WRITE_REG_WORD(0xFFFF, &I2C_BASE->I2C_STAT);

    while ((stat = I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT) & I2C_STAT_BB)
          && timeout--)
    {
        I2C_WRITE_REG_WORD(stat, &I2C_BASE->I2C_STAT);
        udelay(I2C_DELAY_SMALL);
    }

    if (timeout <= 0)
    {
        PRINT_ERROR;
        res = I2C_ERR_TIMEDOUT;
    }

    /* clear delayed stuff*/
    I2C_WRITE_REG_WORD(0xFFFF, &I2C_BASE->I2C_STAT);

    return (res);
}

static uint16_t wait_for_pin(uint32_t baseAddr)
{
    uint16_t          status;
    CSL_I2cRegs  *I2C_BASE = (CSL_I2cRegs *) baseAddr;
    volatile int timeout = 5000;

    do
    {
        /*
           TBD: I2C_DELAY_BIG required with cache ON,
           otherwise I2C_DELAY_SMALL works.
           Interrupt mode read/write will not have such problems.
         */
        udelay(I2C_DELAY_SMALL);
        status = I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT);
    } while(!( status &
              (I2C_STAT_ROVR | I2C_STAT_XUDF | I2C_STAT_XRDY |
               I2C_STAT_RRDY | I2C_STAT_ARDY | I2C_STAT_NACK |
               I2C_STAT_AL) ) && timeout--);

    if (timeout <= 0)
    {
        printf( "timed out in wait_for_pin: I2C_STAT=%lu\n",
               I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT) );
        I2C_WRITE_REG_WORD(0xFFFF, &I2C_BASE->I2C_STAT);
    }

    return status;
}

static void flush_fifo(uint32_t baseAddr)
{
    uint16_t stat;
    CSL_I2cRegs  *I2C_BASE = (CSL_I2cRegs *) baseAddr;

    /* note: if you try and read data when its not there or ready
     * you get a bus error
     */
    while(1)
    {
        stat = I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT);
        if(stat == I2C_STAT_RRDY)
        {
            tempReg = I2C_READ_REG_BYTE(&I2C_BASE->I2C_DATA);
            I2C_WRITE_REG_WORD(I2C_STAT_RRDY, &I2C_BASE->I2C_STAT);
            udelay(I2C_DELAY_SMALL);
        }
        else
        {
            break;
        }
    }

    return;
}

static uint32_t I2Ci2cTransferMsgPoll(I2c_XferParams *i2cXferParams, uint32_t baseAddr)
{
    uint16_t w         = 0;
    uint16_t status    = 0;
    CSL_I2cRegs  *I2C_BASE = (CSL_I2cRegs *)baseAddr;
    int i2c_error = 0;
    int buflen;
    uint32_t retVal = STW_SOK;

    if( !(i2cXferParams->flags & I2C_IGNORE_BUS_BUSY) )
        retVal = wait_for_bb(baseAddr);
    if(STW_SOK != retVal)
    {
        PRINT_ERROR;
        return retVal;
    }
    I2C_WRITE_REG_WORD(i2cXferParams->slaveAddr & I2C_ADDR_MASK,
                       &I2C_BASE->I2C_SA);

    I2C_WRITE_REG_WORD(i2cXferParams->bufLen, &I2C_BASE->I2C_CNT);

    /* Enable I2C controller */
    w = I2C_CON_EN;

    /* High speed configuration */
    if(I2C_BUS_FREQ > 400)
        w |= I2C_CON_OPMODE_HS;

    if(I2C_ADDR_MASK == 0x3FFu)
        w |= I2C_CON_XA;

    if(i2cXferParams->flags & I2C_MASTER)
        w |= I2C_CON_MST;

    if(i2cXferParams->flags & I2C_WRITE)
        w |= I2C_CON_TRX;

    if(i2cXferParams->flags & I2C_START)
        w |= I2C_CON_STT;

    if(i2cXferParams->flags & I2C_STOP)
        w |= I2C_CON_STP;

    I2C_WRITE_REG_WORD(w, &I2C_BASE->I2C_CON);

    status = wait_for_pin(baseAddr);

    if(i2cXferParams->flags & I2C_WRITE)
    {
        /* Transmit */
        for(buflen = 0; buflen < i2cXferParams->bufLen; buflen++)
        {
            if(status & I2C_STAT_XRDY)
            {
                I2C_WRITE_REG_BYTE(i2cXferParams->buffer[buflen],
                                   &I2C_BASE->I2C_DATA);

                /* dont wait for the last byte */
                if(buflen < i2cXferParams->bufLen - 1)
                    status = wait_for_pin(baseAddr);
            }
            else
            {
                PRINT_ERROR;
                i2c_error = 1;
            }
        }

      /* must have enough delay to allow BB bit to go low */
      udelay(I2C_DELAY_BIG);
      if(I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT) & I2C_STAT_NACK)
      {
          PRINT_ERROR;
          i2c_error = 1;
      }
      if( !(I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT) & I2C_STAT_ARDY) )
      {
          PRINT_ERROR;
      }
    }
    else
    {
        /* Receive */
        for(buflen = 0; buflen < i2cXferParams->bufLen; buflen++)
        {
            if(status & I2C_STAT_RRDY)
            {
                i2cXferParams->buffer[buflen] =
                  I2C_READ_REG_BYTE(&I2C_BASE->I2C_DATA);
                udelay(I2C_DELAY_MED);

                /* dont wait for the last byte */
                if(buflen < i2cXferParams->bufLen - 1)
                    status = wait_for_pin(baseAddr);
            }
            else
            {
                PRINT_ERROR;
                i2c_error = 1;
            }
        }

        /* must have enough delay to allow BB bit to go low */
        udelay(I2C_DELAY_BIG);
        if(I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT) & I2C_STAT_NACK)
        {
            PRINT_ERROR;
            i2c_error = 1;
        }
    }

    if(i2cXferParams->flags & I2C_STOP)
    {
        flush_fifo(baseAddr);

        I2C_WRITE_REG_WORD(0xFFFF, &I2C_BASE->I2C_STAT);
        I2C_WRITE_REG_WORD(0, &I2C_BASE->I2C_CNT);
    }

    /* Re-initialize I2C again in case of error */
    if(i2c_error)
    {
        I2C_init(baseAddr);
    }

    return i2c_error;
}

uint32_t I2C_deviceWrite8(uint32_t baseAddr, uint32_t devAddr,
                     const uint8_t *regAddr,
                     const uint8_t *regValue, uint32_t numRegs)
{
    uint32_t status = 0;
    uint32_t regId;
    I2c_XferParams i2cParams;
    uint8_t buffer[2];

    if(regAddr == 0 || regValue == 0 || numRegs == 0)
    {
        PRINT_ERROR;
        return FALSE;
    }

    if(status == STW_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.buffer    = buffer;
        i2cParams.bufLen    = 2;
        i2cParams.flags     = I2C_DEFAULT_WRITE;
        i2cParams.timeout   = I2C_TIMEOUT;

        for(regId = 0; regId < numRegs; regId++)
        {
            buffer[0] = regAddr[regId];
            buffer[1] = regValue[regId];

            status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
            if(status != STW_SOK)
            {
                PRINT_ERROR;
                break;
            }
        }
    }

    return status;
}

uint32_t I2C_deviceWrite16(uint32_t baseAddr, uint32_t devAddr,
                     uint16_t *regAddr,
                     const uint8_t *regValue, uint32_t numRegs)
{
    uint32_t status = 0;
    uint32_t regId;
    I2c_XferParams i2cParams;
    uint8_t buffer[3];

    if(regAddr == 0 || regValue == 0 || numRegs == 0)
    {
        PRINT_ERROR;
        return FALSE;
    }

    if(status == STW_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.buffer    = buffer;
        i2cParams.bufLen    = 3;
        i2cParams.flags     = I2C_DEFAULT_WRITE;
        i2cParams.timeout   = I2C_TIMEOUT;

        for(regId = 0; regId < numRegs; regId++)
        {
            buffer[0] = ((regAddr[regId] >> 8) & 0xFFU);
            buffer[1] = (regAddr[regId] & 0xFFU);
            buffer[2] = regValue[regId];

            status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
            if(status != STW_SOK)
            {
                PRINT_ERROR;
                break;
            }
        }
    }

    return status;
}

uint32_t I2C_deviceWrite16_16(uint32_t baseAddr, uint32_t devAddr,
                         uint16_t *regAddr,
                         const uint16_t *regValue, uint32_t numRegs)
{
    uint32_t status = 0;
    uint32_t regId;
    I2c_XferParams i2cParams;
    uint8_t buffer[4];

    if(regAddr == 0 || regValue == 0 || numRegs == 0)
    {
        PRINT_ERROR;
        return FALSE;
    }

    if(status == STW_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.buffer    = buffer;
        i2cParams.bufLen    = 4;
        i2cParams.flags     = I2C_DEFAULT_WRITE;
        i2cParams.timeout   = I2C_TIMEOUT;

        for(regId = 0; regId < numRegs; regId++)
        {
            buffer[0] = ((regAddr[regId] >> 8) & 0xFF);
            buffer[1] = (regAddr[regId] & 0xFF);
            buffer[2] = ((regValue[regId] >> 8) & 0xFF);
            buffer[3] = (regValue[regId] & 0xFF);

            status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
            if(status != STW_SOK)
            {
                PRINT_ERROR;
                break;
            }
        }
    }

    return status;
}

uint32_t I2C_deviceRead8(uint32_t baseAddr, uint32_t devAddr,
                    const uint8_t *regAddr,
                    uint8_t *regValue, uint32_t numRegs)
{
    uint32_t status = 0;
    uint32_t regId;
    I2c_XferParams i2cParams;

    if(regAddr == 0 || regValue == 0 || numRegs == 0)
    {
        PRINT_ERROR;
        return FALSE;
    }

    if(status == STW_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.bufLen    = 1;
        i2cParams.timeout   = I2C_TIMEOUT;

        for(regId = 0; regId < numRegs; regId++)
        {
            i2cParams.buffer = (uint8_t *)&regAddr[regId];
            i2cParams.flags
              = (I2C_WRITE | I2C_MASTER | I2C_START /* | I2C_STOP */);

            status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
            if(status != STW_SOK)
            {
                PRINT_ERROR;
                break;
            }

            i2cParams.buffer = &regValue[regId];
            i2cParams.flags
              = (I2C_READ | I2C_MASTER | I2C_START | I2C_STOP | I2C_IGNORE_BUS_BUSY);

            status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
            if(status != STW_SOK)
            {
                PRINT_ERROR;
                break;
            }
        }
    }

    return status;
}

uint32_t I2C_deviceRead16(uint32_t baseAddr, uint32_t devAddr,
                     uint16_t *regAddr,
                     uint8_t *regValue, uint32_t numRegs)
{
    uint32_t status = 0;
    uint32_t regId;
    I2c_XferParams i2cParams;
    uint8_t buffer[2];

    if(regAddr == 0 || regValue == 0 || numRegs == 0)
    {
        PRINT_ERROR;
        return FALSE;
    }

    if(status == STW_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.timeout   = I2C_TIMEOUT;

        for(regId = 0; regId < numRegs; regId++)
        {
            buffer[0] = ((regAddr[regId] >> 8) & 0xFF);
            buffer[1] = (regAddr[regId] & 0xFF);
            i2cParams.buffer = buffer;
            i2cParams.bufLen = 2;
            i2cParams.flags
              = (I2C_WRITE | I2C_MASTER | I2C_START /* | I2C_STOP */);

            status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
            if(status != STW_SOK)
            {
                PRINT_ERROR;
                break;
            }

            i2cParams.bufLen = 1;
            i2cParams.buffer = &regValue[regId];
            i2cParams.flags
              = (I2C_READ | I2C_MASTER | I2C_START | I2C_STOP | I2C_IGNORE_BUS_BUSY);

            status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
            if(status != STW_SOK)
            {
                PRINT_ERROR;
                break;
            }
        }
    }

    return status;
}

int I2C_probe(uint32_t baseAddr, uint8_t slaveAddr)
{
    int res = 1;   /* default = fail */
    uint32_t reg_val;
    CSL_I2cRegs  *I2C_BASE = (CSL_I2cRegs *)baseAddr;
    if( slaveAddr == I2C_READ_REG_WORD(&I2C_BASE->I2C_OA) )
    {
        PRINT_ERROR;
        return res;
    }

    /* Disable interrupts first */
    reg_val = I2C_READ_REG_WORD(&I2C_BASE->I2C_IE);
    I2C_WRITE_REG_WORD(0x00u, &I2C_BASE->I2C_IE);

    /* wait until bus not busy */
    wait_for_bb(baseAddr);

    /* try to write one byte */
    I2C_WRITE_REG_WORD(1, &I2C_BASE->I2C_CNT);

    /* set slave address */
    I2C_WRITE_REG_WORD(slaveAddr, &I2C_BASE->I2C_SA);

    /* stop bit needed here */
    I2C_WRITE_REG_WORD(I2C_CON_EN | I2C_CON_MST | I2C_CON_STT | I2C_CON_STP,
                       &I2C_BASE->I2C_CON);

    /* enough delay for the NACK bit set */
    udelay(I2C_DELAY_BIG);

    if( !(I2C_READ_REG_WORD(&I2C_BASE->I2C_STAT) & I2C_STAT_NACK) )
    {
        res = 0;          /* success case */
        flush_fifo(baseAddr);
        I2C_WRITE_REG_WORD(0xFFFF, &I2C_BASE->I2C_STAT);
    }
    else
    {
        I2C_WRITE_REG_WORD(0xFFFF, &I2C_BASE->I2C_STAT);        /* failue, clear sources*/
        I2C_WRITE_REG_WORD(I2C_READ_REG_WORD(&I2C_BASE->I2C_CON) | I2C_CON_STP,
                           &I2C_BASE->I2C_CON);                 /* finish up xfer */
        udelay(I2C_DELAY_MED);
        wait_for_bb(baseAddr);
    }

    flush_fifo(baseAddr);

    I2C_WRITE_REG_WORD(0, &I2C_BASE->I2C_CNT);
    I2C_WRITE_REG_WORD(0xFFFF, &I2C_BASE->I2C_STAT);

    /* Enable interrupts now */
    I2C_WRITE_REG_WORD(reg_val, &I2C_BASE->I2C_IE);

    return res;
}

uint32_t I2C_deviceRawRead8(uint32_t  baseAddr,
                       uint32_t  devAddr,
                       uint8_t *regValue,
                       uint32_t  numRegs)
{
    uint32_t status = 0;
    I2c_XferParams i2cParams;

    if(STW_SOK == status)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.bufLen    = numRegs;
        i2cParams.timeout   = I2C_TIMEOUT;
        i2cParams.buffer    = (uint8_t *)regValue;
        i2cParams.flags     = (I2C_DEFAULT_READ);
        status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
        if(STW_SOK != status)
        {
            PRINT_ERROR;
        }
    }

    return status;
}

uint32_t I2C_deviceRawWrite8(uint32_t  baseAddr,
                        uint32_t  devAddr,
                        uint8_t *regValue,
                        uint32_t  numRegs)
{
    uint32_t status = 0;
    I2c_XferParams i2cParams;

    if(STW_SOK == status)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.buffer    = regValue;
        i2cParams.bufLen    = numRegs;
        i2cParams.flags     = I2C_DEFAULT_WRITE;
        i2cParams.timeout   = I2C_TIMEOUT;
        status = I2Ci2cTransferMsgPoll(&i2cParams,baseAddr);
        if(STW_SOK != status)
        {
            PRINT_ERROR;
        }
    }

    return status;
}
