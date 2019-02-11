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
 *  @file       ti/xdais/dm/ispeech1_smv.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across all SMV speech codecs.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_SMV  ISPEECH1_SMV - XDM Speech Interface (SMV)
 *
 *  This is the XDM speech interface shared between the various SMV codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_SMV_
#define ti_xdais_dm_ISPEECH1_SMV_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_SMV */
/*@{*/


/**
 *  @brief      Enabling/disabling noise suppression, and selection of
 *              noise suppression if the codec supports multiple
 *              noise supression modules.
 */
typedef enum {
    ISPEECH1_SMV_NOISEPREPROC_OFF = 0,  /**< Noise suppression is disabled. */
    ISPEECH1_SMV_NOISEPREPROC_NSA = 1,  /**< Noise suppression is enabled,
                                         *   using option A.
                                         */
    ISPEECH1_SMV_NOISEPREPROC_NSB = 2,  /**< Noise suppression is enabled,
                                         *   using option B.
                                         */

    /** Default setting. */
    ISPEECH1_SMV_NOISEPREPROC_DEFAULT = ISPEECH1_SMV_NOISEPREPROC_NSA
} ISPEECH1_SMV_NoisePreProc;


/**
 *  @brief      Voice activity detection (VAD) selection.
 */
typedef enum {
    ISPEECH1_SMV_VADSELECT_VADA = 1,    /**< VAD A */
    ISPEECH1_SMV_VADSELECT_VADB = 2,    /**< VAD B */

    /** Default setting. */
    ISPEECH1_SMV_VADSELECT_DEFAULT = ISPEECH1_SMV_VADSELECT_VADA
} ISPEECH1_SMV_VADSelect;


/**
 *  @brief      TTY/TDD mode selection.
 */
typedef enum {
    ISPEECH1_SMV_TTYMODE_OFF = 0,       /**< TTY detection is disabled. */
    ISPEECH1_SMV_TTYMODE_45P45BPS = 1,  /**< TTY detection is enabled, with
                                         *   45.45 bauds/sec rate.
                                         */
    ISPEECH1_SMV_TTYMODE_50BPS =  2,    /**< TTY detection is enabled, with
                                         *   50 bauds/sec rate.
                                         */

    /** Default setting. */
    ISPEECH1_SMV_TTYMODE_DEFAULT = ISPEECH1_SMV_TTYMODE_OFF
} ISPEECH1_SMV_TTYMode;


/**
 *  @brief      DTMF mode selection.
 */
typedef enum {
    ISPEECH1_SMV_DTMFMODE_OFF = 0,         /**< DTMF detection is disabled. */
    ISPEECH1_SMV_DTMFMODE_ON = 1,          /**< DTMF detection is enabled. */

    /** Default setting. */
    ISPEECH1_SMV_DTMFMODE_DEFAULT = ISPEECH1_SMV_DTMFMODE_OFF
} ISPEECH1_SMV_DTMFMode;


/**
 *  @brief      Enable/disable in band data transmission and data rate
 *              selection.
 */
typedef enum {
    ISPEECH1_SMV_DATAMODE_OFF = 0,         /**< Data transmission is disabled */
    ISPEECH1_SMV_DATAMODE_HALFRATE = 1,    /**< Data transmission is enabled
                                            *   at half rate.
                                            */
    ISPEECH1_SMV_DATAMODE_FULLRATE = 1,    /**< Data transmission is enabled
                                            *   at full rate.
                                            */

    /** Default setting. */
    ISPEECH1_SMV_DATAMODE_DEFAULT = ISPEECH1_SMV_DATAMODE_OFF
} ISPEECH1_SMV_DataMode;


/**
 *  @brief      Rate reduction mode selection.
 */
typedef enum {
    ISPEECH1_SMV_MODE_PREMIUM = 0,         /**< Premium mode. */
    ISPEECH1_SMV_MODE_STANDARD = 1,        /**< Standard mode. */
    ISPEECH1_SMV_MODE_ECONOMY = 2,         /**< Economy mode. */
    ISPEECH1_SMV_MODE_CAPACITYSAVE = 3,    /**< Capacity saving mode. */
    ISPEECH1_SMV_MODE_PREMIUM_HALFRATE_MAX = 4, /**< Premium mode, with half
                                            *   rate maximum.
                                            */
    ISPEECH1_SMV_MODE_STANDARD_HALFRATE_MAX = 5,/**< Standard mode, with half
                                            *   rate maximum.
                                            */

    /** Default setting. */
    ISPEECH1_SMV_MODE_DEFAULT = ISPEECH1_SMV_MODE_PREMIUM
} ISPEECH1_SMV_Mode;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
