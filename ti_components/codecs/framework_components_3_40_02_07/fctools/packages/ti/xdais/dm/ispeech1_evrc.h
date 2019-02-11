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
 *  @file       ti/xdais/dm/ispeech1_evrc.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for EVRC.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_EVRC  ISPEECH1_EVRC - XDM Speech Interface (EVRC)
 *
 *  This is the XDM speech interface shared between the various EVRC codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_EVRC_
#define ti_xdais_dm_ISPEECH1_EVRC_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_EVRC */
/*@{*/


/**
 *  @brief      Enable/disable noise suppression.
 */
typedef enum {
    ISPEECH1_EVRC_NOISEPREPROC_OFF = 0, /**< The noise suppression is
                                         *   disabled.
                                         */
    ISPEECH1_EVRC_NOISEPREPROC_ON = 1,  /**< The noise suppression is
                                         *   enabled.
                                         */

    /** Default setting. */
    ISPEECH1_EVRC_NOISEPREPROC_DEFAULT = ISPEECH1_EVRC_NOISEPREPROC_ON
} ISPEECH1_EVRC_NoisePreProc;


/**
 *  @brief      TTY/TDD mode selection.
 */
typedef enum {
    ISPEECH1_EVRC_TTYMODE_OFF = 0,      /**< Off */
    ISPEECH1_EVRC_TTYMODE_45P45BPS = 1, /**< 45.45 baud rate */
    ISPEECH1_EVRC_TTYMODE_50BPS = 2,    /**< 50 baud rate */

    /** Default setting. */
    ISPEECH1_EVRC_TTYMODE_DEFAULT = ISPEECH1_EVRC_TTYMODE_OFF
} ISPEECH1_EVRC_TTYMode;


/**
 *  @brief      Mode selection
 *
 *  @remarks    This is used for rate reduction mode in EVRC codecs.  The
 *              average bit rate of speech encoding is controlled by these
 *              different modes.
 */
typedef enum {
    ISPEECH1_EVRC_MODE_PREMIUM = 0,        /**< Premium mode. */
    ISPEECH1_EVRC_MODE_STANDARD = 1,       /**< Standard mode. */
    ISPEECH1_EVRC_MODE_ECONOMY = 2,        /**< Economy mode. */
    ISPEECH1_EVRC_MODE_CAPACITYSAVE = 3,   /**< Capacity saving mode. */
    ISPEECH1_EVRC_MODE_HALFRATE_MAX = 4,   /**< Half rate max mode. */

    /** Default setting. */
    ISPEECH1_EVRC_MODE_DEFAULT = ISPEECH1_EVRC_MODE_PREMIUM
} ISPEECH1_EVRC_Mode;


/**
 *  @brief      Null traffic channel setting.
 *
 *  @sa         ISPHENC1_InArgs.nullTrafficChannel.
 */
typedef enum {
    ISPEECH1_EVRC_NULLTRAFFICMODE_OFF = 0,  /**< Null traffic channel frames
                                        *   disabled, normal speech encoding
                                        *   is enabled.
                                        */
    ISPEECH1_EVRC_NULLTRAFFICMODE_ON = 1,   /**< Null traffic channel frames
                                        *   enabled.
                                        */

    /** @copydoc ISPEECH1_NULLTRAFFICMODE_OFF */
    ISPEECH1_EVRC_NULLTRAFFICMODE_DEFAULT = ISPEECH1_EVRC_NULLTRAFFICMODE_OFF
} ISPEECH1_EVRC_NullTrafficMode;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
