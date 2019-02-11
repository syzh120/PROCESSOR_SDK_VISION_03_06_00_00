/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     diagLib_eccEmif.h
 *
 *  \brief    This file contains the prototypes of EMIF test APIs used
 *            by the ECC library internally
 *
 * ==================================================================== */

#ifndef DIAGLIB_ECC_EMIF_H_
#define DIAGLIB_ECC_EMIF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/diag/diagLib_ecc.h>
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void emifEccConfig(uint32_t testType, DiagLib_EccObj_t *eccObj);
int32_t emifNonEccQuantaAlignAddrTest(
            const DiagLib_EccEmifTestParams_t *testParams,
            DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout);
#if defined (SOC_TDA2PX)
int32_t emifEccSubQuantaWriteTest(
            const DiagLib_EccEmifTestParams_t *testParams,
            DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout);
#endif
int32_t emifByteCntWRAccessNotMultEccQuantaTest
            (const DiagLib_EccEmifTestParams_t *testParams,
             DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout);
int32_t emifSecErrTest(const DiagLib_EccEmifTestParams_t *testParams,
            DiagLib_EccObj_t *eccObj, uint32_t errChkMode, uint32_t timeout);
int32_t emifDedErrTest(const DiagLib_EccEmifTestParams_t *testParams,
                            DiagLib_EccObj_t *eccObj, uint32_t errChkMode);
void emifNonEccQuantaAddrISR
                (const DiagLib_EccEmifTestParams_t *testParams,
                 DiagLib_EccObj_t *eccObj);
void emifSecISR(const DiagLib_EccEmifTestParams_t *testParams,
                                    DiagLib_EccObj_t *eccObj);
void emifDedISR(const DiagLib_EccEmifTestParams_t *testParams,
                                    DiagLib_EccObj_t *eccObj);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif