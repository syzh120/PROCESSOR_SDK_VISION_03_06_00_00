/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     sbl_lib_common.c
 *
 *  \brief    This file contains the SBL Library layer common across various
 *            platforms.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_mmu.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/drv/pm/pmhal.h>
#if defined (SOC_TDA3XX)
#include <tda3xx/sbl_lib_tda3xx_priv.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void SBLLibReverseString(char *str, uint32_t length);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Global variable for SBL initialization parameters
 */
static sbllibInitParams_t gSBLLibInitParams;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SBLLibInit(const sbllibInitParams_t *sbllibInitPrms)
{
    if (NULL != sbllibInitPrms)
    {
        gSBLLibInitParams.printFxn       = sbllibInitPrms->printFxn;
        gSBLLibInitParams.printHexNumFxn = sbllibInitPrms->printHexNumFxn;
        gSBLLibInitParams.getcFxn        = sbllibInitPrms->getcFxn;
        gSBLLibInitParams.putcFxn        = sbllibInitPrms->putcFxn;
        gSBLLibInitParams.getNumFxn      = sbllibInitPrms->getNumFxn;
        gSBLLibInitParams.getHexNumFxn   = sbllibInitPrms->getHexNumFxn;
    }
}

static void SBLLibReverseString(char *str, uint32_t length)
{
    uint32_t start = 0;
    uint32_t end = length - 1U;
    if (length != 0U)
    {
        while (start < end)
        {
            char temp;
            temp = *(str+start);
            *(str+start) = *(str+end);
            *(str+end) = temp;
            start++;
            end--;
        }
    }
}

void SBLLibConvertHexToString(uint32_t hexValue, char *stringValue)
{
    uint32_t remainder = 0, quotient = 0;
    uint32_t dividend  = 0;
    /* Count starts from two because of '0x' */
    uint32_t  count = 0U;

    dividend = hexValue;

    do
    {
        quotient           = dividend / 16U;
        remainder          = dividend % 16U;
        if (remainder > 9U)
        {
            /* It is a alpha numiric number. */
            remainder -= 10U;
            remainder += (uint32_t)'a';
            stringValue[count] = (char)remainder;
        }
        else
        {
            remainder += (uint32_t)'0';
            stringValue[count] = (char)remainder;
        }
        count++;
        if (0U == quotient)
        {
            break;
        }
        dividend = quotient;
    } while (count < 7U);
    stringValue[count] = (char)'x';
    count++;
    stringValue[count] = (char)'0';
    count++;
    SBLLibReverseString(stringValue, count);
    /* Null Terminate the string. */
    stringValue[count] = '\0';
}

void SBLLibAbortBoot(void)
{
    /*
     * Boot unsuccessful, Abort
     * Added dummy variable to avoid MISRA C error
     */

    volatile uint32_t dummyVal = 0U;

    while (1)
    {
        if (1U == dummyVal)
        {
            break;
        }
    }
}

void SBLLibPrintf(uint32_t traceLevel, const char *message)
{
    if (NULL != gSBLLibInitParams.printFxn)
    {
        switch (traceLevel)
        {
            case SBLLIB_TRACE_LEVEL_ERROR:
                gSBLLibInitParams.printFxn(message);
                break;
            case SBLLIB_TRACE_LEVEL_IMP_INFO:
                gSBLLibInitParams.printFxn(message);
                break;
#if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_HIGH)
    #if (TRACE_LEVEL >= SBLLIB_TRACE_LEVEL_LOW)
            case SBLLIB_TRACE_LEVEL_INFO:
                gSBLLibInitParams.printFxn(message);
                break;
    #endif
    #if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_MEDIUM)
        #if (TRACE_LEVEL >= SBLLIB_TRACE_LEVEL_MEDIUM)
            case SBLLIB_TRACE_LEVEL_INFO1:
                gSBLLibInitParams.printFxn(message);
                break;
        #endif
        #if (TRACE_LEVEL >= SBLLIB_TRACE_LEVEL_HIGH)
            case SBLLIB_TRACE_LEVEL_DEBUG:
                gSBLLibInitParams.printFxn(message);
                break;
        #endif
    #endif
#endif
            default:
                /* To remove MISRA C error */
                break;
        }
    }
}

void SBLLibPrintHexNum(uint32_t traceLevel, uint32_t value)
{
    if (NULL != gSBLLibInitParams.printHexNumFxn)
    {
        gSBLLibInitParams.printHexNumFxn(traceLevel, value);
    }
}

void SBLLibPutc(uint32_t traceLevel, uint8_t value)
{
    if (NULL != gSBLLibInitParams.putcFxn)
    {
        gSBLLibInitParams.putcFxn(traceLevel, value);
    }
}

char SBLLibGetc(void)
{
    char retChar = (char)0U;
    if (NULL != gSBLLibInitParams.getcFxn)
    {
        retChar = gSBLLibInitParams.getcFxn();
    }
    return retChar;
}

uint32_t SBLLibGetNum(void)
{
    uint32_t retNum = 0xFFFFFFFFU;
    if (NULL != gSBLLibInitParams.getNumFxn)
    {
        retNum = gSBLLibInitParams.getNumFxn();
    }
    return retNum;
}

uint32_t SBLLibGetHexNum(void)
{
    uint32_t retNum = 0xFFFFFFFFU;
    if (NULL != gSBLLibInitParams.getHexNumFxn)
    {
        retNum = gSBLLibInitParams.getHexNumFxn();
    }
    return retNum;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
