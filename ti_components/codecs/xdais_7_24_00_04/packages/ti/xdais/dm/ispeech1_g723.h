/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  @file       ti/xdais/dm/ispeech1_g723.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for G.723
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_G723  ISPEECH1_G723 - XDM Speech Interface (G.723)
 *
 *  This is the XDM speech interface shared between the various G.723 codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_G723_
#define ti_xdais_dm_ISPEECH1_G723_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_G723 */
/*@{*/


/**
 *  @brief      Bit rate selection for G723.
 */
typedef enum {
    ISPEECH1_G723_BITRATE_5P3 = 0,     /**< 5.3 kbps */
    ISPEECH1_G723_BITRATE_6P3 = 1,     /**< 6.3 kbps */

    /** Default setting. */
    ISPEECH1_G723_BITRATE_DEFAULT = ISPEECH1_G723_BITRATE_6P3
} ISPEECH1_G723_BitRate;


/**
 *  @brief      Enable/disable high pass filter for G723.
 */
typedef enum {
    ISPEECH1_G723_NOISEPREPROC_OFF = 0,/**< The high pass filter is disabled. */
    ISPEECH1_G723_NOISEPREPROC_ON = 1, /**< The high pass filter is enabled. */

    /** Default setting. */
    ISPEECH1_G723_NOISEPREPROC_DEFAULT = ISPEECH1_G723_NOISEPREPROC_ON
} ISPEECH1_G723_NoisePreProc;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
