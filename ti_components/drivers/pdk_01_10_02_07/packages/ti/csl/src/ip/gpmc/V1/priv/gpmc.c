/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file  gpmc.c
 *
 *  \brief GPMC  APIs.
 *
 *   This file contains the device abstraction layer APIs for GPMC.
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/cslr_gpmc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_gpmc.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
uint32_t  GPMCRevisionGet(uint32_t baseAddr)
{
    uint32_t ipRev;

    ipRev = HW_RD_FIELD32(baseAddr + GPMC_REVISION, GPMC_REVISION_REVISION);

    return (ipRev);
}

void  GPMCIdleModeSelect(uint32_t baseAddr, uint32_t mode)
{
    HW_WR_FIELD32(baseAddr + GPMC_SYSCONFIG, GPMC_SYSCONFIG_IDLEMODE, mode);
}

void  GPMCAutoIdleConfig(uint32_t baseAddr, uint32_t configVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_SYSCONFIG, GPMC_SYSCONFIG_AUTOIDLE, configVal);
}

void  GPMCModuleSoftReset(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + GPMC_SYSCONFIG, GPMC_SYSCONFIG_SOFTRESET,
                  GPMC_SYSCONFIG_SOFTRESET_RESET);
}

uint32_t  GPMCModuleResetStatusGet(uint32_t baseAddr)
{
    uint32_t resetStat;

    resetStat =
        HW_RD_REG32(baseAddr + GPMC_SYSSTATUS) & GPMC_SYSSTATUS_RESETDONE_MASK;

    return (resetStat);
}

uint32_t  GPMCIntStatusGet(uint32_t baseAddr, uint32_t flag)
{
    uint32_t retVal;

    retVal = 0;

    switch (flag)
    {
        case GPMC_FIFOEVENT_STATUS:
            retVal = HW_RD_FIELD32(baseAddr + GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_FIFOEVENTSTATUS);
            break;
        case GPMC_TERMINALCOUNT_STATUS:
            retVal = HW_RD_FIELD32(baseAddr + GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_TERMINALCOUNTSTATUS);
            break;
        case GPMC_WAIT0EDGEDETECTION_STATUS:
            retVal = HW_RD_FIELD32(baseAddr + GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS);
            break;
        case GPMC_WAIT1EDGEDETECTION_STATUS:
            retVal = HW_RD_FIELD32(baseAddr + GPMC_IRQSTATUS,
                                   GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS);
            break;

        default:
            break;
    }

    return (retVal);
}

void  GPMCIntStatusClear(uint32_t baseAddr, uint32_t flag)
{
    switch (flag)
    {
        case GPMC_FIFOEVENT_STATUS:
            HW_WR_FIELD32(baseAddr + GPMC_IRQSTATUS,
                          GPMC_IRQSTATUS_FIFOEVENTSTATUS,
                          GPMC_IRQSTATUS_FIFOEVENTSTATUS_FIFOSTAT1_W);
            break;
        case GPMC_TERMINALCOUNT_STATUS:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQSTATUS, GPMC_IRQSTATUS_TERMINALCOUNTSTATUS,
                GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_TCSTAT1_W);
            break;
        case GPMC_WAIT0EDGEDETECTION_STATUS:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQSTATUS,
                GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS,
                GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_W0DET1_W);
            break;
        case GPMC_WAIT1EDGEDETECTION_STATUS:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQSTATUS,
                GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS,
                GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_W1DET1_W);
            break;

        default:
            break;
    }
}

void  GPMCIntEnable(uint32_t baseAddr, uint32_t flag)
{
    switch (flag)
    {
        case GPMC_FIFOEVENT_INT:
            HW_WR_FIELD32(baseAddr + GPMC_IRQENABLE,
                          GPMC_IRQENABLE_FIFOEVENTENABLE,
                          GPMC_IRQENABLE_FIFOEVENTENABLE_FIFOENABLED);
            break;
        case GPMC_TERMINALCOUNT_INT:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQENABLE,
                GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE,
                GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_TCENABLED);
            break;
        case GPMC_WAIT0EDGEDETECTION_INT:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE,
                GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_W0ENABLED);
            break;
        case GPMC_WAIT1EDGEDETECTION_INT:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE,
                GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_W1ENABLED);
            break;

        default:
            break;
    }
}

void  GPMCIntDisable(uint32_t baseAddr, uint32_t flag)
{
    switch (flag)
    {
        case GPMC_FIFOEVENT_INT:
            HW_WR_FIELD32(baseAddr + GPMC_IRQENABLE,
                          GPMC_IRQENABLE_FIFOEVENTENABLE,
                          GPMC_IRQENABLE_FIFOEVENTENABLE_FIFOMASKED);
            break;
        case GPMC_TERMINALCOUNT_INT:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQENABLE,
                GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE,
                GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_TCMASKED);
            break;
        case GPMC_WAIT0EDGEDETECTION_INT:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE,
                GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_W0MASKED);
            break;
        case GPMC_WAIT1EDGEDETECTION_INT:
            HW_WR_FIELD32(
                baseAddr + GPMC_IRQENABLE,
                GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE,
                GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_W1MASKED);
            break;

        default:
            break;
    }
}

void  GPMCTimeOutStartValSet(uint32_t baseAddr, uint32_t timeoutVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_TIMEOUT_CONTROL,
                  GPMC_TIMEOUT_CONTROL_TIMEOUTSTARTVALUE,
                  timeoutVal);
}

void  GPMCTimeOutFeatureConfig(uint32_t baseAddr, uint32_t flag)
{
    if (flag == GPMC_TIMEOUTFEATURE_ENABLE)
    {
        HW_WR_FIELD32(baseAddr + GPMC_TIMEOUT_CONTROL,
                      GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE,
                      GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_TOENABLED);
    }
    else if (flag == GPMC_TIMEOUTFEATURE_DISABLE)
    {
        HW_WR_FIELD32(baseAddr + GPMC_TIMEOUT_CONTROL,
                      GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE,
                      GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_TODISABLED);
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }
}

uint32_t  GPMCErrAddrGet(uint32_t baseAddr)
{
    uint32_t retVal;

    retVal =
        HW_RD_REG32(baseAddr +
                    GPMC_ERR_ADDRESS) & GPMC_ERR_ADDRESS_ILLEGALADD_MASK;

    return (retVal);
}

uint32_t  GPMCErrValStatusGet(uint32_t baseAddr)
{
    uint32_t status;

    status =
        HW_RD_REG32(baseAddr + GPMC_ERR_TYPE) & GPMC_ERR_TYPE_ERRORVALID_MASK;

    return (status);
}

uint32_t  GPMCErrSysCmdGet(uint32_t baseAddr)
{
    uint32_t cmd;

    cmd = HW_RD_FIELD32(baseAddr + GPMC_ERR_TYPE, GPMC_ERR_TYPE_ILLEGALMCMD);

    return (cmd);
}

uint32_t  GPMCErrStatusGet(uint32_t baseAddr, uint32_t err)
{
    uint32_t retVal;

    retVal = 0;

    switch (err)
    {
        case GPMC_TIMEOUT_ERROR:
            retVal = HW_RD_FIELD32(baseAddr + GPMC_ERR_TYPE,
                                   GPMC_ERR_TYPE_ERRORTIMEOUT);
            break;
        case GPMC_NOTSUPPMCMD_ERROR:
            retVal = HW_RD_FIELD32(baseAddr + GPMC_ERR_TYPE,
                                   GPMC_ERR_TYPE_ERRORNOTSUPPMCMD);
            break;
        case GPMC_NOTSUPPADD_ERROR:
            retVal = HW_RD_FIELD32(baseAddr + GPMC_ERR_TYPE,
                                   GPMC_ERR_TYPE_ERRORNOTSUPPADD);
            break;

        default:
            break;
    }
    return (retVal);
}

void  GPMCWaitPinPolaritySelect(uint32_t baseAddr, uint32_t pin,
                                uint32_t polarity)
{
    if (pin == GPMC_WAIT_PIN0)
    {
        if (polarity == GPMC_WAIT_PIN_POLARITY_HIGH)
        {
            HW_WR_FIELD32(baseAddr + GPMC_CONFIG, GPMC_CONFIG_WAIT0PINPOLARITY,
                          GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEH);
        }
        else if (polarity == GPMC_WAIT_PIN_POLARITY_LOW)
        {
            HW_WR_FIELD32(baseAddr + GPMC_CONFIG, GPMC_CONFIG_WAIT0PINPOLARITY,
                          GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEL);
        }
        else
        {
            /*
             * Do nothing. Error will be generated by the hardware
             */
        }
    }
    else if (pin == GPMC_WAIT_PIN1)
    {
        if (polarity == GPMC_WAIT_PIN_POLARITY_HIGH)
        {
            HW_WR_FIELD32(baseAddr + GPMC_CONFIG, GPMC_CONFIG_WAIT1PINPOLARITY,
                          GPMC_CONFIG_WAIT1PINPOLARITY_W1ACTIVEH);
        }
        else if (polarity == GPMC_WAIT_PIN_POLARITY_LOW)
        {
            HW_WR_FIELD32(baseAddr + GPMC_CONFIG, GPMC_CONFIG_WAIT1PINPOLARITY,
                          GPMC_CONFIG_WAIT1PINPOLARITY_W1ACTIVEL);
        }
        else
        {
            /*
             * Do nothing. Error will be generated by the hardware
             */
        }
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }
}

void  GPMCNANDForcePostedWriteFeatureConfig(uint32_t baseAddr,
                                            uint32_t flag)
{
    if (flag == GPMC_FORCEPOSTEDWRITE_ENABLE)
    {
        HW_WR_FIELD32(baseAddr + GPMC_CONFIG, GPMC_CONFIG_NANDFORCEPOSTEDWRITE,
                      GPMC_CONFIG_NANDFORCEPOSTEDWRITE_FORCEPWR);
    }
    else if (flag == GPMC_FORCEPOSTEDWRITE_DISABLE)
    {
        HW_WR_FIELD32(baseAddr + GPMC_CONFIG, GPMC_CONFIG_NANDFORCEPOSTEDWRITE,
                      GPMC_CONFIG_NANDFORCEPOSTEDWRITE_NOFORCEPWR);
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }
}

uint32_t  GPMCWaitPinStatusGet(uint32_t baseAddr, uint32_t pin)
{
    uint32_t pinStatus;

    pinStatus = 0;

    if (pin == GPMC_WAIT_PIN0)
    {
        pinStatus = HW_RD_FIELD32(baseAddr + GPMC_STATUS,
                                  GPMC_STATUS_WAIT0STATUS);
    }
    else if (pin == GPMC_WAIT_PIN1)
    {
        pinStatus = HW_RD_FIELD32(baseAddr + GPMC_STATUS,
                                  GPMC_STATUS_WAIT1STATUS);
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }

    return (pinStatus);
}

uint32_t  GPMCEmptyWriteBuffStatusGet(uint32_t baseAddr)
{
    uint32_t status;

    status = HW_RD_FIELD32(baseAddr + GPMC_STATUS,
                           GPMC_STATUS_EMPTYWRITEBUFFERSTATUS);

    return (status);
}

void  GPMCFclkDividerSelect(uint32_t baseAddr, uint32_t csNum,
                            uint32_t divideVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_GPMCFCLKDIVIDER, divideVal);
}

void  GPMCTimeParaGranularitySelect(uint32_t baseAddr, uint32_t csNum,
                                    uint32_t scaleftr)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_TIMEPARAGRANULARITY, scaleftr);
}

void  GPMCAddrDataMuxProtocolSelect(uint32_t baseAddr, uint32_t csNum,
                                    uint32_t protocol)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_MUXADDDATA, protocol);
}

void  GPMCDevTypeSelect(uint32_t baseAddr, uint32_t csNum,
                        uint32_t devType)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_DEVICETYPE, devType);
}

void  GPMCDevSizeSelect(uint32_t baseAddr, uint32_t csNum,
                        uint32_t devSize)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_DEVICESIZE, devSize);
}

void  GPMCWaitPinSelect(uint32_t baseAddr, uint32_t csNum,
                        uint32_t waitPin)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_WAITPINSELECT, waitPin);
}

void  GPMCWaitMonitoringTimeSelect(uint32_t baseAddr, uint32_t csNum,
                                   uint32_t flag)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_WAITMONITORINGTIME, flag);
}

void  GPMCWaitPinMonitoringConfig(uint32_t baseAddr, uint32_t csNum,
                                  uint32_t mode, uint32_t flag)
{
    if (mode == GPMC_MODE_WRITE)
    {
        HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                      GPMC_CONFIG1_N_WAITWRITEMONITORING, flag);
    }
    else if (mode == GPMC_MODE_READ)
    {
        HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                      GPMC_CONFIG1_N_WAITREADMONITORING, flag);
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }
}

void  GPMCClkActivationTimeConfig(uint32_t baseAddr, uint32_t csNum,
                                  uint32_t flag)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_CLKACTIVATIONTIME, flag);
}

void  GPMCDevPageLenSet(uint32_t baseAddr, uint32_t csNum,
                        uint32_t pageLen)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_ATTACHEDDEVICEPAGELENGTH, pageLen);
}

void  GPMCWriteTypeSelect(uint32_t baseAddr, uint32_t csNum,
                          uint32_t writeType)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_WRITETYPE, writeType);
}

void  GPMCReadTypeSelect(uint32_t baseAddr, uint32_t csNum,
                         uint32_t readType)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_READTYPE, readType);
}

void  GPMCAccessTypeSelect(uint32_t baseAddr, uint32_t csNum,
                           uint32_t mode, uint32_t accessType)
{
    if (mode == GPMC_MODE_WRITE)
    {
        HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                      GPMC_CONFIG1_N_WRITEMULTIPLE, accessType);
    }
    else if (mode == GPMC_MODE_READ)
    {
        HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                      GPMC_CONFIG1_N_READMULTIPLE, accessType);
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }
}

void  GPMCSyncWrapBurstConfig(uint32_t baseAddr, uint32_t csNum,
                              uint32_t flag)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG1_N(csNum),
                  GPMC_CONFIG1_N_WRAPBURST, flag);
}

void  GPMCCSTimingConfig(uint32_t baseAddr, uint32_t csNum,
                         uint32_t conf)
{
    HW_WR_REG32(baseAddr + GPMC_CONFIG2_N(csNum), conf);
}

void  GPMCADVTimingConfig(uint32_t baseAddr, uint32_t csNum,
                          uint32_t conf)
{
    HW_WR_REG32(baseAddr + GPMC_CONFIG3_N(csNum), conf);
}

void  GPMCWEAndOETimingConfig(uint32_t baseAddr, uint32_t csNum,
                              uint32_t conf)
{
    HW_WR_REG32(baseAddr + GPMC_CONFIG4_N(csNum), conf);
}

void  GPMCRdAccessAndCycleTimeTimingConfig(uint32_t baseAddr,
                                           uint32_t csNum,
                                           uint32_t conf)
{
    HW_WR_REG32(baseAddr + GPMC_CONFIG5_N(csNum), conf);
}

void  GPMCWrAccessAndWrDataOnADMUXBusTimingConfig(uint32_t baseAddr,
                                                  uint32_t csNum,
                                                  uint32_t wrAccessTime,
                                                  uint32_t wrDataOnADmuxBus)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG6_N(csNum),
                  GPMC_CONFIG6_N_WRACCESSTIME, wrAccessTime);
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG6_N(csNum),
                  GPMC_CONFIG6_N_WRDATAONADMUXBUS, wrDataOnADmuxBus);
}

void  GPMCycle2CycleAndTurnArndTimeTimingConfig(uint32_t baseAddr,
                                                uint32_t csNum,
                                                uint32_t conf)
{
    uint32_t gpmcRegValue = HW_RD_REG32(baseAddr + GPMC_CONFIG6_N(csNum));
    gpmcRegValue |= conf;
    HW_WR_REG32(baseAddr + GPMC_CONFIG6_N(csNum), gpmcRegValue);
}

void  GPMCCSConfig(uint32_t baseAddr, uint32_t csNum,
                   uint32_t conf)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG7_N(csNum),
                  GPMC_CONFIG7_N_CSVALID, conf);
}

void  GPMCBaseAddrSet(uint32_t baseAddr, uint32_t csNum,
                      uint32_t addr)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG7_N(csNum),
                  GPMC_CONFIG7_N_BASEADDRESS, addr);
}

void  GPMCMaskAddrSet(uint32_t baseAddr, uint32_t csNum,
                      uint32_t maskaddr)
{
    HW_WR_FIELD32(baseAddr + GPMC_CONFIG7_N(csNum),
                  GPMC_CONFIG7_N_MASKADDRESS, maskaddr);
}

void  GPMCSNANDCmdWrite(uint32_t baseAddr, uint32_t csNum,
                        uint32_t cmd)
{
    HW_WR_REG32(baseAddr + GPMC_NAND_COMMAND_N(csNum), cmd);
}

void  GPMCNANDAddrWrite(uint32_t baseAddr, uint32_t csNum,
                        uint32_t addr)
{
    HW_WR_REG32(baseAddr + GPMC_NAND_ADDRESS_N(csNum), addr);
}

void  GPMCNANDDataWrite(uint32_t baseAddr, uint32_t csNum,
                        uint32_t data)
{
    HW_WR_REG32(baseAddr + GPMC_NAND_DATA_N(csNum), data);
}

uint32_t  GPMCNANDDataRead(uint32_t baseAddr, uint32_t csNum)
{
    uint32_t data;

    data = HW_RD_REG32(baseAddr + GPMC_NAND_DATA_N(csNum));

    return (data);
}

void GPMCPrefetchAccessModeSelect(uint32_t baseAddr,
                                  uint32_t accessMode)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_ACCESSMODE,
                  accessMode);
}

void GPMCPrefetchSyncTypeSelect(uint32_t baseAddr, uint32_t syncType)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_DMAMODE,
                  syncType);
}

void GPMCPrefetchSyncModeConfig(uint32_t baseAddr, uint32_t flag)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_SYNCHROMODE,
                  flag);
}

void GPMCPrefetchWaitPinSelect(uint32_t baseAddr, uint32_t waitPin)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR,
                  waitPin);
}

void GPMCPrefetchEngineEnable(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_ENABLEENGINE,
                  GPMC_PREFETCH_CONFIG1_ENABLEENGINE_PPENABLED);
}

void GPMCPrefetchEngineDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_ENABLEENGINE,
                  GPMC_PREFETCH_CONFIG1_ENABLEENGINE_PPDISABLED);
}

void GPMCPrefetchFifoThrldValSet(uint32_t baseAddr, uint32_t fifoThrsld)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_FIFOTHRESHOLD,
                  fifoThrsld);
}

void GPMCPrefetchCSSelect(uint32_t baseAddr, uint32_t csNum)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_ENGINECSSELECTOR,
                  csNum);
}

void GPMCPrefetchAccessCycleOptConfig(uint32_t baseAddr,
                                      uint32_t configVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS,
                  configVal);
}

void GPMCPrefetchCycleOptValSet(uint32_t baseAddr, uint32_t cleOptVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_CYCLEOPTIMIZATION,
                  cleOptVal);
}

void GPMCPrefetchRRArbitrationConfig(uint32_t baseAddr,
                                     uint32_t configVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN,
                  configVal);
}

void GPMCPrefetchWeightedPrioSet(uint32_t baseAddr, uint32_t accessVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG1,
                  GPMC_PREFETCH_CONFIG1_PFPWWEIGHTEDPRIO,
                  accessVal);
}

void GPMCPrefetchTrnsCntValSet(uint32_t baseAddr, uint32_t trnsCntVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_PREFETCH_CONFIG2,
                  GPMC_PREFETCH_CONFIG2_TRANSFERCOUNT,
                  trnsCntVal);
}

void GPMCPrefetchEngineStart(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + GPMC_PREFETCH_CONTROL,
                (uint32_t) GPMC_PREFETCH_CONTROL_STARTENGINE_START);
}

void GPMCPrefetchEngineStop(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + GPMC_PREFETCH_CONTROL,
                (uint32_t) GPMC_PREFETCH_CONTROL_STARTENGINE_STOP);
}

uint32_t  GPMCPrefetchEngineStatusGet(uint32_t baseAddr)
{
    uint32_t status;

    status = HW_RD_REG32(baseAddr + GPMC_PREFETCH_CONTROL) &
             GPMC_PREFETCH_CONTROL_STARTENGINE_MASK;

    return (status);
}

uint32_t  GPMCPrefetchCountValGet(uint32_t baseAddr)
{
    uint32_t cntVal;

    cntVal = HW_RD_REG32(baseAddr + GPMC_PREFETCH_STATUS) &
             GPMC_PREFETCH_STATUS_COUNTVALUE_MASK;

    return (cntVal);
}

uint32_t  GPMCPrefetchFifoThrldStatusGet(uint32_t baseAddr)
{
    uint32_t status;

    status = HW_RD_FIELD32(baseAddr + GPMC_PREFETCH_STATUS,
                           GPMC_PREFETCH_STATUS_FIFOTHRESHOLDSTATUS);

    return (status);
}

uint32_t GPMCPrefetchFifoPtrValGet(uint32_t baseAddr)
{
    uint32_t fifoPtrVal;

    fifoPtrVal = HW_RD_FIELD32(baseAddr + GPMC_PREFETCH_STATUS,
                               GPMC_PREFETCH_STATUS_FIFOPOINTER);

    return (fifoPtrVal);
}

void GPMCECCAlgoSelect(uint32_t baseAddr, uint32_t algo)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCALGORITHM,
                  algo);
}

void GPMCECCBCHErrCorrectionCapSelect(uint32_t baseAddr,
                                      uint32_t errCorrCapVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCBCHTSEL,
                  errCorrCapVal);
}

void GPMCECCBCHWrapModeValSet(uint32_t baseAddr, uint32_t wrapModeVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCWRAPMODE,
                  wrapModeVal);
}

void GPMCECCColumnSelect(uint32_t baseAddr, uint32_t eccColVal)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECC16B, eccColVal);
}

void GPMCECCBCHNumOfSectorsSelect(uint32_t baseAddr,
                                  uint32_t numOfSects)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCTOPSECTOR,
                  numOfSects);
}

void GPMCECCCSSelect(uint32_t baseAddr, uint32_t csNum)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCCS, csNum);
}


void GPMCECCEnable(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCENABLE,
                  GPMC_ECC_CONFIG_ECCENABLE_ECCENABLED);
}

void GPMCECCDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONFIG, GPMC_ECC_CONFIG_ECCENABLE,
                  GPMC_ECC_CONFIG_ECCENABLE_ECCDISABLED);
}


void GPMCECCResultRegClear(uint32_t baseAddr)
{
    uint32_t eccClearVal = 0x1U;
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONTROL, GPMC_ECC_CONTROL_ECCCLEAR,
                  eccClearVal);
}

void GPMCECCResultRegSelect(uint32_t baseAddr, uint32_t eccResReg)
{
    HW_WR_FIELD32(baseAddr + GPMC_ECC_CONTROL, GPMC_ECC_CONTROL_ECCPOINTER,
                  eccResReg);
}

void GPMCECCSizeValSet(uint32_t baseAddr, uint32_t eccSize,
                       uint32_t eccSizeVal)
{
    if (eccSize == GPMC_ECC_SIZE_0)
    {
        HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                      GPMC_ECC_SIZE_CONFIG_ECCSIZE0,
                      eccSizeVal);
    }
    else if (eccSize == GPMC_ECC_SIZE_1)
    {
        HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                      GPMC_ECC_SIZE_CONFIG_ECCSIZE1,
                      eccSizeVal);
    }
    else
    {
        /*
         * Do nothing. Error will be generated by the hardware
         */
    }
}

void GPMCECCResultSizeSelect(uint32_t baseAddr, uint32_t eccResReg,
                             uint32_t eccSize)
{
    switch (eccResReg)
    {
        case GPMC_ECC_RESULT_1:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_2:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_3:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_4:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_5:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_6:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_7:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_8:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE,
                          eccSize);
            break;
        case GPMC_ECC_RESULT_9:
            HW_WR_FIELD32(baseAddr + GPMC_ECC_SIZE_CONFIG,
                          GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE,
                          eccSize);
            break;

        default:
            break;
    }
}

uint32_t GPMCECCResultGet(uint32_t baseAddr, uint32_t eccResReg)
{
    uint32_t res;

    res = HW_RD_REG32(baseAddr + GPMC_ECCN_RESULT(eccResReg));

    return (res);
}

uint32_t GPMCECCBCHResultGet(uint32_t baseAddr, uint32_t resIndex,
                             uint32_t csNum)
{
    uint32_t res;

    res = 0;

    switch (resIndex)
    {
        case GPMC_BCH_RESULT0:
            res = HW_RD_REG32(baseAddr + GPMC_BCH_RESULT_0(csNum));
            break;
        case GPMC_BCH_RESULT1:
            res = HW_RD_REG32(baseAddr + GPMC_BCH_RESULT_1(csNum));
            break;
        case GPMC_BCH_RESULT2:
            res = HW_RD_REG32(baseAddr + GPMC_BCH_RESULT_2(csNum));
            break;
        case GPMC_BCH_RESULT3:
            res = HW_RD_REG32(baseAddr + GPMC_BCH_RESULT_3(csNum));
            break;
        case GPMC_BCH_RESULT4:
            res = HW_RD_REG32(baseAddr + GPMC_BCH_RESULT_4(csNum));
            break;
        case GPMC_BCH_RESULT5:
            res = HW_RD_REG32(baseAddr + GPMC_BCH_RESULT_5(csNum));
            break;
        case GPMC_BCH_RESULT6:
            res = HW_RD_REG32(baseAddr + GPMC_BCH_RESULT_6(csNum));
            break;

        default:
            break;
    }

    return (res);
}

void GPMCECCBCHSWDataWrite(uint32_t baseAddr, uint32_t bchData)
{
    HW_WR_REG32(baseAddr + GPMC_BCH_SWDATA,
                bchData & GPMC_BCH_SWDATA_BCH_DATA_MASK);
}

uint32_t GPMCECCBCHSWDataRead(uint32_t baseAddr)
{
    uint32_t bchData;

    bchData =
        HW_RD_REG32(baseAddr + GPMC_BCH_SWDATA) & GPMC_BCH_SWDATA_BCH_DATA_MASK;

    return (bchData);
}

/***************************** End Of File ***********************************/
