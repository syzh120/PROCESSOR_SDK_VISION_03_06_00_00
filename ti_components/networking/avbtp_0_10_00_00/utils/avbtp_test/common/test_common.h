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

/**
 *  \file avbtp_test_common.h
 *
 *  \brief AVBTP test program definitions shared between server and client.
 */

#ifndef TEST_COMMON_H_
#define TEST_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief  Shared command enumerated type.
 */
typedef enum TEST_CMD_ID_
{
    TEST_CMD_START_AVB = 0,
    TEST_CMD_STOP_AVB,
    TEST_CMD_GET_AVB_STATS,
    TEST_CMD_CLEAR_AVB_STATS,
    TEST_CMD_GET_LOAD_INFO,
    TEST_CMD_GET_HW_ERRORS,
    TEST_CMD_GET_HW_STATS,
    TEST_CMD_CLEAR_HW_STATS,
    TEST_CMD_GET_SW_STATS,
    TEST_CMD_CLEAR_SW_STATS,
    TEST_CMD_GET_NDK_STATS,
    TEST_CMD_CLEAR_NDK_STATS,
    TEST_CMD_DISABLE_TCP_ECHO,
    TEST_CMD_ENABLE_TCP_ECHO,
    TEST_CMD_DUMP_OUTPUT_FRAMES,
    TEST_CMD_GET_BUFFER_COUNT,
    TEST_CMD_ENABLE_RST_MARKER_DETECTION,
    TEST_CMD_START_AVB_TALKER,
    TEST_CMD_STOP_AVB_TALKER
}
TestCmdID;

typedef enum TEST_PORTS_
{
    TEST_CMD_PORT = 19200,
    TEST_TCP_PORT = 19201,
    TEST_UDP_PORT = 19202
}
TestPorts;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* TEST_COMMON_H_ */


