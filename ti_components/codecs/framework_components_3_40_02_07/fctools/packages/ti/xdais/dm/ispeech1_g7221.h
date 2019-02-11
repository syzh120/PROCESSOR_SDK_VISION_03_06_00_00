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
 *  @file       ti/xdais/dm/ispeech1_g7221.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for G.7221
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_G7221  ISPEECH1_G7221 - XDM Speech Interface (G.7221)
 *
 *  This is the XDM speech interface shared between the various G.7221 codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_G7221_
#define ti_xdais_dm_ISPEECH1_G7221_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_G7221 */
/*@{*/


/**
 *  @brief      Bit rate selection for G7221.
 */
typedef enum {
    ISPEECH1_G7221_BITRATE_24  = 24,     /**<  24  kbps */
    ISPEECH1_G7221_BITRATE_32  = 32,     /**<  32  kbps */
    ISPEECH1_G7221_BITRATE_48  = 48,     /**<  48  kbps */

    /** Default setting. */
    ISPEECH1_G7221_BITRATE_DEFAULT = ISPEECH1_G7221_BITRATE_24
} ISPEECH1_G7221_BitRate;


/**
 *  @brief      Sampling Rate selection.
 *
 *  @remarks    This parameter is used to select the codec sampling rate
 *
 *  @sa ISPHDEC2_Params.samplingRate
 *  @sa ISPHDEC2_Status.samplingRate
 *  @sa ISPHENC2_Params.samplingRate
 *  @sa ISPHENC2_Status.samplingRate
 */
typedef enum {
    ISPEECH2_G7221_SAMPLINGRATE_WIDEBAND = 0,      /**< wideband mode(16KHz). */
    ISPEECH2_G7221_SAMPLINGRATE_SUPEWIDEBAND = 1,   /**< super wide band mode(32KHz) */

    ISPEECH2_G7221_SAMPLINGRATE_DEFAULT = ISPEECH2_G7221_SAMPLINGRATE_WIDEBAND

} ISPEECH2_G7221_SamplingRate;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
