/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file Serialize.h
 *
 *  \brief Cascade Radar serializer interface for flash utilities.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_

#include <stdint.h>

/* Status register masks */
#define SPI_SR1_WIP                (1 << 0)
#define SPI_SR1_WEL                (1 << 1)
#define SPI_SR1_BP0                (1 << 2)
#define SPI_SR1_BP1                (1 << 3)
#define SPI_SR1_BP2                (1 << 4)
#define SPI_SR1_E_FAIL             (1 << 5)
#define SPI_SR1_P_FAIL             (1 << 6)
#define SPI_SR1_SRWD               (1 << 7)

/*Return Type*/
typedef enum
{
    RetSpiError,
    RetSpiSuccess
} SPI_STATUS;

/* Acceptable values for SPI master side configuration */
typedef enum _SpiConfigOptions
{
    OpsNull,              /* do nothing */
    OpsWakeUp,            /* enable transfer */
    OpsInitTransfer,
    OpsEndTransfer,

} SpiConfigOptions;

/* char stream definition for */
typedef struct _structCharStream
{
    uint8_t* pChar;       /* buffer address that holds the streams */
    uint32_t length;      /* length of the stream in bytes         */
} CharStream;

SPI_STATUS Serialize_SPI(const CharStream* char_stream_send,
                         CharStream* char_stream_recv,
                         SpiConfigOptions optBefore, SpiConfigOptions optAfter) ;

#endif


