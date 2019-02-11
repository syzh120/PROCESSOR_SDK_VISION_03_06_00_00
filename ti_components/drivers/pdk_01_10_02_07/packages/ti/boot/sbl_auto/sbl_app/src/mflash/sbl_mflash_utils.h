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
 *  \file     sbl_mflash_utils_priv.h
 *
 *  \brief    This file contains common internal functions for mflash
 */

#ifndef SBL_MFLASH_UTILS_PRIV_H_
#define SBL_MFLASH_UTILS_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  This macro defines command for PC to send next patch
 */
#define SBL_MFLASH_CMD_SEND_NEXT_PATCH  		(6U)

/**
 * \brief  This macro defines command that indicates transfer complete to PC
 */
#define SBL_MFLASH_CMD_TRANSFER_COMPLETE 		(4U)

/**
 * \brief  These macro defines command that indicates intitial handshake
 */
#define SBL_MFLASH_CMD_HNDSKE_STEP1				"\n\nMflash Begins!!"
#define SBL_MFLASH_CMD_HNDSKE_STEP1_RESPONSE	'1'
#define SBL_MFLASH_CMD_HNDSKE_STEP2				'r'

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function enables data write to QSPI memory.
 *
 * \param   buff        content location
 * \param   length      length of data
 * \param   destination destination address
 *
 * \return  None.
 *
 */
void SBLMFlashWriteQSPI(const uint8_t *buff, uint32_t length, uint32_t destination);

/**
 * \brief   This function gets a file over UART from PC.
 *
 * \param   pRxBuffer           content location
 * \param   numBytesToRead      length of data
 *
 * \return  None.
 *
 */
void SBLMFlashUARTGetFile(uint8_t *pRxBuffer, uint32_t numBytesToRead);

/**
 * \brief   Displays runtime menu.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void SBLMFlashMenu(void);

/**
 * \brief   Flash memory initialization.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void SBLMFlashMemoryInit(void);

/**
 * \brief   Displays QSPI device id for platform.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void SBLMFlashPrintQSPIDeviceId(void);

/**
 * \brief   Starts file transfer from PC to target.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void SBLMFlashDownloadFile(void);

/**
 * \brief    Erases peripheral memory.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void SBLMFlashMemoryErase(void);

/**
 * \brief   Prints mflash information.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void SBLMFlashHelper(void);

/**
 * \brief   Runs mflash target side tool.
 *
 * \param   None.
 *
 * \return  None.
 *
 */
void SBLMFlashRun(void);

/**
 * \brief  This is implementation of print function.
 *
 * \param   message   message to be printed
 *
 * \return  None.
 */
void SblPrintFunction(const char *message);

/**
 * \brief  This is implementation of print hex num function.
 *
 * \param   tracelevel  trace level of message
 * \param   value       Number to be printed
 *
 * \return  None.
 */
void SblPrintHexNumFunction(uint32_t tracelevel, uint32_t value);

/**
 * \brief  This is implementation of print character function.
 *
 * \param   tracelevel  trace level of message
 * \param   value       Character to be printed
 *
 * \return  None.
 */
void SblPutcFunction(uint32_t tracelevel, uint8_t value);

/**
 * \brief  This is implementation of getc function.
 *
 * \param  None
 *
 * \return None.
 */
char SblGetcFunction(void);

/**
 * \brief  This is implementation of get num function.
 *
 * \param  None
 *
 * \return None.
 */
uint32_t SblGetNumFunction(void);

/**
 * \brief  This is implementation of get hex num function.
 *
 * \param  None
 *
 * \return None.
 */
uint32_t SblGetHexNumFunction(void);

#ifdef __cplusplus
}
#endif

#endif
