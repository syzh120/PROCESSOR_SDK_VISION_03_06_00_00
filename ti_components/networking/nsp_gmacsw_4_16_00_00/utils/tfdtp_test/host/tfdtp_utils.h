/*
* Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
*  \file tfdtp_utils.h
*
*  \brief TFDTP utils header file.
*/

#ifndef TFDTP_UTILS_H_
#define TFDTP_UTILS_H_

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/
#define PRINT_HW_STATS      (1)
#define DEBUG_PRINT         (0)

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/
typedef struct {
    char                *filename;
    uint32_t            numRxFrame;
    uint32_t            numLoop;
    uint32_t            enableDataValFlag;
    TFDTP_CreateParams  tfdtpParam;
    TFDTP_Obj           *tfdtpObj;
    char                srcIpAddr[16];
} App_Obj;

/*---------------------------------------------------------------------------*\
|                          Global Function Prototypes                         |
\*---------------------------------------------------------------------------*/
#if defined(__MINGW32__) || defined(_MSC_VER)
int  my_gettimeofday(struct timeval * tp);
void socketsStartup();
#endif
void print_stats(App_Obj *pAppObj);
void print_appStats(App_Obj *pAppObj);
void print_tfdtpStats(App_Obj *pAppObj);
void print_ethHWErrors(App_Obj *pAppObj);
void print_ethHWStats(App_Obj *pAppObj);
void print_loadStats(App_Obj *pAppObj);

#endif /* TFDTP_UTILS_H_ */
