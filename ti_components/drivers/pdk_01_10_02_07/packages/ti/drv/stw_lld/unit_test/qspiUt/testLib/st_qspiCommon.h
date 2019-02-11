/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 *  \file st_qspCommon.h
 *
 *  \brief This file contains all common function declarations used by the
 *   QSPI UT applications
 */

#ifndef STW_QSPI_COMMON_H_
#define STW_QSPI_COMMON_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <st_qspi.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
int32_t st_qspiTest_initFlash(st_QspiTestCfgPrms testCfg,
                              uint32_t           deviceType);

int32_t st_qspiTest_setFlashDevInfo(st_QspiTestCfgPrms   testCfg,
                                    uint32_t              flashType);

int32_t st_qspiTest_setCustomFlashDevInfo(st_QspiTestCfgPrms   testCfg);

int32_t st_qspiTest_eraseFlash(uint32_t eraseType,
                               uint32_t blockNo,
                               uint32_t sectorNo);

int32_t st_qspiTest_writeRandomTestPattern();

int32_t st_qspiTest_writeFlash(uint32_t length,
                               uint32_t dataWidth,
                               uint32_t offsetAddr);

int32_t st_qspiTest_readFlash(uint32_t length,
                              uint32_t dataWidth,
                              uint32_t enableReadMemMapMode,
                              uint32_t offsetAddr,
                              uint32_t dataTransferMode);
int32_t st_qspiTest_readFlashWithCheck(uint32_t length,
                                       uint32_t dataWidth,
                                       uint32_t enableReadMemMapMode,
                                       uint32_t offsetAddr,
                                       uint32_t dataTransferMode);

int32_t st_qspiTest_verifyFlashData(uint32_t length,
                                    uint32_t enableReadMemMapMode);

int32_t st_qspiTest_deInitFlash();

void st_qspiTest_isr_wc_fc();

int32_t st_qspiTest_executeCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif

