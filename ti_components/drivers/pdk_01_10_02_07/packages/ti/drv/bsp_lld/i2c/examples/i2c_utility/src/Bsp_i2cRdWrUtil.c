/*
 *  Copyright (C) 2014-2017 Texas Instruments Incorporated
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
 *  \file   Bsp_i2cRdWrUtil.c
 *
 *  \brief  This file contains a generic I2C read write utility.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/System.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_device.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSP_I2C_MAX_REG_RD_WR       (0x100)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32 i2cInstId;
    char   inputStr[1024];
    char  *inputArgs[128];
    UInt32 numArgs;
    UInt8  regAddr[BSP_I2C_MAX_REG_RD_WR];
    UInt8  regValue[BSP_I2C_MAX_REG_RD_WR];
    UInt16 regAddr16[BSP_I2C_MAX_REG_RD_WR];
    UInt16 regValue16[BSP_I2C_MAX_REG_RD_WR];
} BspI2c_Ctrl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 BspI2c_exeCmd(FILE *fp, Bool echoCmd);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static BspI2c_Ctrl gBspI2c_ctrl;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static UInt32 BspI2c_tokenizeInput(char *inStr, char *argv[])
{
    char   delimiters[] = " \r\n";
    char  *token;
    UInt32 argc = 0;

    token = strtok(inStr, delimiters);
    while (token != NULL)
    {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, delimiters);
    }

    return (argc);
}

static char xtod(char c)
{
    if ((c >= '0') && (c <= '9'))
    {
        return (c - '0');
    }
    if ((c >= 'A') && (c <= 'F'))
    {
        return (c - 'A' + 10);
    }
    if ((c >= 'a') && (c <= 'f'))
    {
        return (c - 'a' + 10);
    }

    return (c = 0);        // not Hex digit
}

static int HextoDec(char *hex, int l)
{
    if (*hex == 0)
    {
        return (l);
    }

    return HextoDec(hex + 1, l * 16 + xtod(*hex)); // hex+1?
}

static int xstrtoi(char *hex)      // hex string to integer
{
    return HextoDec(hex, 0);
}

static Int32 BspI2c_showHelp(void)
{
    Bsp_printf(
        " \r\n Commands,"
        " \r\n ========="
        " \r\n help                   - shows this screen"
        " \r\n quit                   - exits utility"
        " \r\n inst <i2c instance ID> - switch to another I2C instance (0 or 1)"
        " \r\n probe                  - probes the I2C instance (0 or 1) for all possibly connected slaves"
        " \r\n file <filename>        - execute I2C utility commands by reading from file <filename>"
        " \r\n wait <time in msecs>   - introduce a delay of <time in msecs> msecs"
        " \r\n"
        " \r\n rd <dev addr in hex> <reg offset in hex> <num regs to read in hex> "
        " \r\n wr <dev addr in hex> <reg offset in hex> <value to write in hex> "
        " \r\n"
        " \r\n rd_raw <dev addr in hex> <num regs to read in hex>"
        " \r\n       - Reads the specified no. of registers from a desired IO expander kind "
        " \r\n         of slave, which doesn't have the register offset"
        " \r\n"
        " \r\n wr_raw <dev addr in hex> <reg value 1 in hex> <reg value 2 in hex> etc..."
        " \r\n       - Writes n bytes (max 100 bytes) at the desired slave."
        " \r\n         All bytes are transferred one after the other in the same I2C transfer"
        " \r\n"
        " \r\n rd      <reg offset in hex> can be 8 or 16 bits wide"
        " \r\n         <reg offset in hex> 8 bits for all other commands"
        " \r\n"
        " \r\n"
        );

    return (0);
}

static Int32 BspI2c_changeInstId(void)
{
    UInt32 value;

    if (gBspI2c_ctrl.numArgs > 1)
    {
        value = atoi(gBspI2c_ctrl.inputArgs[1]);
        if (value < BSP_DEVICE_I2C_INST_ID_MAX)
        {
            gBspI2c_ctrl.i2cInstId = value;
            Bsp_printf(" I2C: Changed to instance %d !!!\r\n",
                       gBspI2c_ctrl.i2cInstId);
        }
        else
        {
            Bsp_printf(" I2C: Illegal Instance ID (%d) specified !!!\r\n",
                       value);
        }
    }
    else
    {
        Bsp_printf(" I2C: Instance ID not specified !!!\r\n");
    }

    return (0);
}

static Int32 BspI2c_writeReg(void)
{
    UInt32 devAddr;
    UInt32 regAddr;
    UInt32 regValue;
    Int32  status = BSP_SOK;

    if (gBspI2c_ctrl.numArgs == 4)
    {
        devAddr = xstrtoi(gBspI2c_ctrl.inputArgs[1]);
        if ((devAddr > 0) && (devAddr < 0x100))
        {
            regAddr = xstrtoi(gBspI2c_ctrl.inputArgs[2]);
            if (regAddr < 0x100)
            {
                regValue = xstrtoi(gBspI2c_ctrl.inputArgs[3]);
                if (regValue < 0x100)
                {
                    Bsp_printf(
                        " I2C: Writing 0x%02x to REG 0x%02x of device 0x%02x ... !!!\r\n",
                        regValue, regAddr, devAddr);

                    gBspI2c_ctrl.regAddr[0]  = regAddr;
                    gBspI2c_ctrl.regValue[0] = regValue;

                    status = Bsp_deviceWrite8(
                        gBspI2c_ctrl.i2cInstId,
                        devAddr,
                        gBspI2c_ctrl.regAddr,
                        gBspI2c_ctrl.regValue,
                        1);
                    if (status != BSP_SOK)
                    {
                        Bsp_printf(" I2C: Write ERROR !!!\r\n");
                    }

                    if (status == BSP_SOK)
                    {
                        Bsp_printf(
                            " I2C: Reading back the written register ... !!!\r\n");

                        gBspI2c_ctrl.regValue[0] = 0;

                        status = Bsp_deviceRead8(
                            gBspI2c_ctrl.i2cInstId,
                            devAddr,
                            gBspI2c_ctrl.regAddr,
                            gBspI2c_ctrl.regValue,
                            1);

                        Bsp_printf(" I2C: 0x%02x = 0x%02x\r\n",
                                   gBspI2c_ctrl.regAddr[0],
                                   gBspI2c_ctrl.regValue[0]);
                        if (status != BSP_SOK)
                        {
                            Bsp_printf(" I2C: Read ERROR !!!\r\n");
                        }
                    }
                    Bsp_printf(" \r\n");
                }
                else
                {
                    Bsp_printf(
                        " I2C: Illegal register value (0x%x) specified !!!\r\n",
                        regValue);
                }
            }
            else
            {
                Bsp_printf(
                    " I2C: Illegal Register address (0x%x) specified !!!\r\n",
                    regAddr);
            }
        }
        else
        {
            Bsp_printf(" I2C: Illegal Device address (0x%x) specified !!!\r\n",
                       devAddr);
        }
    }
    else
    {
        Bsp_printf(" I2C: Insufficient arguments specified !!!\r\n");
    }

    return (0);
}

static Int32 BspI2c_readRegs(void)
{
    UInt32 devAddr;
    UInt32 regAddr;
    UInt32 numRegs, i;
    Int32  status   = BSP_SOK;
    UInt32 currTime = 0, timeElapsed = 0;

    if (gBspI2c_ctrl.numArgs == 4)
    {
        devAddr = xstrtoi(gBspI2c_ctrl.inputArgs[1]);

        if ((devAddr > 0) && (devAddr < 0x100))
        {
            regAddr = xstrtoi(gBspI2c_ctrl.inputArgs[2]);
            if (regAddr < 0x100)
            {
                numRegs = xstrtoi(gBspI2c_ctrl.inputArgs[3]);
                if (numRegs < BSP_I2C_MAX_REG_RD_WR)
                {
                    Bsp_printf(
                        " I2C: Reading 0x%02x registers starting from REG 0x%02x of device 0x%02x ... !!!\r\n",
                        numRegs, regAddr, devAddr);

                    for (i = 0; i < numRegs; i++)
                    {
                        gBspI2c_ctrl.regAddr[i]  = regAddr + i;
                        gBspI2c_ctrl.regValue[i] = 0;
                    }

                    currTime = BspOsal_getClockTicks();

                    status = Bsp_deviceRead8(
                        gBspI2c_ctrl.i2cInstId,
                        devAddr,
                        gBspI2c_ctrl.regAddr,
                        gBspI2c_ctrl.regValue,
                        numRegs);

                    timeElapsed = BspOsal_getClockTicks();

                    for (i = 0; i < numRegs; i++)
                    {
                        Bsp_printf(" I2C: 0x%02x = 0x%02x\r\n",
                                   gBspI2c_ctrl.regAddr[i],
                                   gBspI2c_ctrl.regValue[i]);
                    }
                    if (status != BSP_SOK)
                    {
                        Bsp_printf(" I2C: Read ERROR !!!\r\n");
                    }

                    Bsp_printf(" I2C: Time Elapsed in Read = %d msec",
                               timeElapsed - currTime);
                    Bsp_printf(" \r\n");
                }
                else
                {
                    Bsp_printf(
                        " I2C: Illegal number of registers to read (0x%x) specified !!!\r\n",
                        numRegs);
                }
            }
            else if (regAddr < 0x10000)
            {
                numRegs = xstrtoi(gBspI2c_ctrl.inputArgs[3]);
                if (numRegs < BSP_I2C_MAX_REG_RD_WR)
                {
                    Bsp_printf(
                        " I2C: Reading 0x%04x registers starting from REG 0x%04x of device 0x%02x ... !!!\r\n",
                        numRegs, regAddr, devAddr);
                    for (i = 0; i < numRegs; i++)
                    {
                        gBspI2c_ctrl.regAddr16[i]  = regAddr + i;
                        gBspI2c_ctrl.regValue16[i] = 0;
                    }

                    currTime = BspOsal_getClockTicks();

                    status = Bsp_deviceRead16(
                                gBspI2c_ctrl.i2cInstId,
                                devAddr,
                                gBspI2c_ctrl.regAddr16,
                                gBspI2c_ctrl.regValue16,
                                numRegs);

                    timeElapsed = BspOsal_getClockTicks();

                    if (status != BSP_SOK)
                    {
                        Bsp_printf(" I2C: Read ERROR !!!\r\n");
                    }
                    else
                    {
                        for (i = 0; i < numRegs; i++)
                        {
                            Bsp_printf(" I2C: 0x%04x = 0x%04x\r\n",
                                       gBspI2c_ctrl.regAddr16[i],
                                       gBspI2c_ctrl.regValue16[i]);
                        }
                    }
                    Bsp_printf(" I2C: Time Elapsed in Read = %d msec",
                               timeElapsed - currTime);
                    Bsp_printf(" \r\n");
                }
            }
            else
            {
                Bsp_printf(
                    " I2C: Illegal Register address (0x%x) specified !!!\r\n",
                    regAddr);
            }
        }
        else
        {
            Bsp_printf(" I2C: Illegal Device address (0x%x) specified !!!\r\n",
                       devAddr);
        }
    }
    else
    {
        Bsp_printf(" I2C: Insufficient arguments specified !!!\r\n");
    }

    return (0);
}

static Int32 BspI2c_writeRegN(void)
{
    UInt32 devAddr;
    UInt32 regValue, cnt, numWrites;
    Int32  status = BSP_SOK;

    numWrites = gBspI2c_ctrl.numArgs - 2;
    if ((gBspI2c_ctrl.numArgs > 2) &&
        (numWrites <= BSP_I2C_MAX_REG_RD_WR))
    {
        devAddr = xstrtoi(gBspI2c_ctrl.inputArgs[1]);
        if ((devAddr > 0) && (devAddr < 0x100))
        {
            Bsp_printf(" \r\n");
            Bsp_printf(" I2C: Writing device 0x%02x:", devAddr);
            for (cnt = 0; cnt < numWrites; cnt++)
            {
                regValue = xstrtoi(gBspI2c_ctrl.inputArgs[2 + cnt]);
                gBspI2c_ctrl.regValue[cnt] = regValue;
                Bsp_printf(" 0x%02x", regValue);
            }
            Bsp_printf(" \r\n");

            status = Bsp_deviceRawWrite8(
                gBspI2c_ctrl.i2cInstId,
                devAddr,
                gBspI2c_ctrl.regValue,
                numWrites);
            if (status != BSP_SOK)
            {
                Bsp_printf(" I2C: Write ERROR !!!\r\n");
            }
        }
        else
        {
            Bsp_printf(" I2C: Illegal Device address (0x%x) specified !!!\r\n",
                       devAddr);
        }
    }
    else
    {
        Bsp_printf(" I2C: Insufficient arguments specified !!!\r\n");
    }

    return (0);
}

static Int32 BspI2c_readRegRaw(void)
{
    UInt32 devAddr;
    UInt32 numRegs, i;
    Int32  status   = BSP_SOK;
    UInt32 currTime = 0, timeElapsed = 0;

    if (gBspI2c_ctrl.numArgs == 3)
    {
        devAddr = xstrtoi(gBspI2c_ctrl.inputArgs[1]);
        if ((devAddr > 0) && (devAddr < 0x100))
        {
            numRegs = xstrtoi(gBspI2c_ctrl.inputArgs[2]);
            if (numRegs < BSP_I2C_MAX_REG_RD_WR)
            {
                Bsp_printf(" \r\n");
                Bsp_printf(
                    " I2C: Reading 0x%02x registers of device 0x%02x ... !!!\r\n",
                    numRegs, devAddr);

                for (i = 0; i < numRegs; i++)
                {
                    gBspI2c_ctrl.regValue[i] = 0;
                }

                currTime = BspOsal_getClockTicks();

                status = Bsp_deviceRawRead8(
                    gBspI2c_ctrl.i2cInstId,
                    devAddr,
                    gBspI2c_ctrl.regValue,
                    numRegs);

                timeElapsed = BspOsal_getClockTicks();

                for (i = 0; i < numRegs; i++)
                {
                    Bsp_printf(" I2C: 0x%02x = 0x%02x\r\n",
                               0x0 + i, gBspI2c_ctrl.regValue[i]);
                }

                if (status != BSP_SOK)
                {
                    Bsp_printf(" I2C: Read ERROR !!!\r\n");
                }

                Bsp_printf(" I2C: Time Elapsed in Read = %d msec",
                           timeElapsed - currTime);
                Bsp_printf(" \r\n");
            }
            else
            {
                Bsp_printf(
                    " I2C: Illegal number of registers to read (0x%x) specified !!!\r\n",
                    numRegs);
            }
        }
        else
        {
            Bsp_printf(" I2C: Illegal Device address (0x%x) specified !!!\r\n",
                       devAddr);
        }
    }
    else
    {
        Bsp_printf(" I2C: Insufficient arguments specified !!!\r\n");
    }

    return (0);
}

static Int32 BspI2c_delay(void)
{
    UInt32 timeInMsecs;

    if (gBspI2c_ctrl.numArgs > 1)
    {
        timeInMsecs = atoi(gBspI2c_ctrl.inputArgs[1]);

        Bsp_printf(" I2C: Waiting for %d msecs ... \r\n", timeInMsecs);
        Task_sleep(timeInMsecs);
        Bsp_printf(" I2C: Wait Done !!!\r\n");
    }
    else
    {
        Bsp_printf(" I2C: Insufficient arguments specified !!!\r\n");
    }

    return (0);
}

static Int32 BspI2c_file(void)
{
    FILE *fp;
    Bool  done = FALSE;
    char  filename[256];

    if (gBspI2c_ctrl.numArgs > 1)
    {
        strncpy(filename, gBspI2c_ctrl.inputArgs[1], (sizeof (filename) - 1U));
        filename[sizeof (filename) - 1] = '\0';

        Bsp_printf(" I2C: Reading from file [%s] !!! \r\n", filename);

        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            Bsp_printf(" I2C: File [%s] not found !!! \r\n", filename);
            return (0);
        }

        while (!done)
        {
            done = BspI2c_exeCmd(fp, TRUE);
        }

        fclose(fp);

        Bsp_printf(" I2C: File closed [%s] !!! \r\n", filename);
    }
    else
    {
        Bsp_printf(" I2C: Insufficient arguments specified !!!\r\n");
    }

    return (0);
}

static Int32 BspI2c_exeCmd(FILE *fp, Bool echoCmd)
{
    Bool  done = FALSE;
    char *retStr;

    retStr = fgets(gBspI2c_ctrl.inputStr, sizeof (gBspI2c_ctrl.inputStr), fp);
    if (retStr == NULL)
    {
        return (TRUE);
    }

    if (echoCmd)
    {
        Bsp_printf(" \r\n");
        Bsp_printf(" I2C: CMD: %s", gBspI2c_ctrl.inputStr);
    }

    gBspI2c_ctrl.numArgs =
        BspI2c_tokenizeInput(gBspI2c_ctrl.inputStr, gBspI2c_ctrl.inputArgs);
    if (gBspI2c_ctrl.numArgs)
    {
        if (strcmp(gBspI2c_ctrl.inputArgs[0], "quit") == 0)
        {
            done = TRUE;
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "help") == 0)
        {
            BspI2c_showHelp();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "inst") == 0)
        {
            BspI2c_changeInstId();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "rd") == 0)
        {
            BspI2c_readRegs();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "wr") == 0)
        {
            BspI2c_writeReg();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "wait") == 0)
        {
            BspI2c_delay();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "file") == 0)
        {
            BspI2c_file();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "wr_raw") == 0)
        {
            BspI2c_writeRegN();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "rd_raw") == 0)
        {
            BspI2c_readRegRaw();
        }
        else if (strcmp(gBspI2c_ctrl.inputArgs[0], "probe") == 0)
        {
            Bsp_deviceI2cProbeAll(gBspI2c_ctrl.i2cInstId);
        }
    }

    return (done);
}

Int32 start_i2c_utility(void)
{
    Bool done = FALSE;

    gBspI2c_ctrl.i2cInstId = BSP_DEVICE_I2C_INST_ID_0;
    Bsp_printf(" I2C: Instance ID %d !!!\r\n", gBspI2c_ctrl.i2cInstId);

    BspI2c_showHelp();

    while (!done)
    {
        Bsp_printf(" I2C-%d> ", gBspI2c_ctrl.i2cInstId);
        done = BspI2c_exeCmd(stdin, FALSE);
    }

    Bsp_printf(" I2C: Bye Bye !!!\r\n");

    return (0);
}

