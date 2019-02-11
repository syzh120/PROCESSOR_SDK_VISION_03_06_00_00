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
 *  \file     sbl_test_auto.h
 *
 *  \brief   This file contains prototypes of functions which are used to load
 *           the multi-core application image file and to configure test
 *           automation environment parameters
 */

#ifndef SBL_TEST_AUTO_H_
#define SBL_TEST_AUTO_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* None */

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
 * \brief   This function copies the STW AppImage based on STW APP List file and
 *          current Testcase file in SD Card and configures the Timer with
 *          STW AppImage execution time when the reset status is cold reset else
 *          will update the Result file in SD Card with test result of
 *          STW AppImage which was executed and will update the current Testcase
 *          file with testcase Number of next STW AppImage to be tested and then
 *          does cold reset. This will continue till last STW AppImage Test.
 *          After completion of the last STW AppImage test , it will print
 *          STW APP Test Summary on UART console based on Result file
 *          Valid Boot Mode is QSPI_SD/SD
 *
 * \param   imageParams  Multi-core Application Image Parse Parameters.
 *                       Refer struct #sbllibAppImageParseParams_t for
 *                       details.
 *
 * \param   resetStatus  status of Watchdog Timer reset
 *
 *
 * \return  retVal       STW_SOK   : Success If appImage is copied correctly
 *                       STW_EFAIL : Failure If appImage is not copied correctly
 *
 */
int32_t SBLLoadTestAutoAppImage(sbllibAppImageParseParams_t *imageParams,
                                uint32_t                     resetStatus);

/**
 * \brief   This function does Test environment configuration for Test
 *          Automation SBL as defined below
 *          1. RTI(for tda3xx)/WD_Timer(for tda2xx) is configured to generate
 *             Reset based on STW AppImage WDG timeout defined in AppList file
 *          2. Disable Unicache for Test Automation SBL in case of Tda3xx
 *
 * \param   None
 *
 * \return  None
 *
 */
void SBLTestAutoEnvCfg(void);

/**
 * \brief   This function checks for whether last reset is cold reset or
 *          Watchdog timer reset
 *
 * \return  resetStatus  status of whether last reset is cold reset or
 *                       Watchdog timer reset
 *                       SUCCESS : if the last reset is Watchdog timer reset
 *                       FAIL : if the last reset is cold reset
 *
 */
uint32_t SBLTestAutoCheckWDTResetStatus(void);

#ifdef __cplusplus
}

#endif

#endif

