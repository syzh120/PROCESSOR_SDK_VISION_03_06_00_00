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
 *  @file       ti/xdais/dm/ispeech1_g722.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for G.722
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_G722  ISPEECH1_G722 - XDM Speech Interface (G.722)
 *
 *  This is the XDM speech interface shared between the various G.722 codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_G722_
#define ti_xdais_dm_ISPEECH1_G722_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_G722 */
/*@{*/


/**
 *  @brief      Bit rate selection for G722.
 */
typedef enum {
    ISPEECH1_G722_BITRATE_RATE0 = 0,     /**< @todo Need clearer description */
    ISPEECH1_G722_BITRATE_RATE1 = 1,     /**< @todo Need clearer description */
    ISPEECH1_G722_BITRATE_RATE2 = 2,     /**< @todo Need clearer description */
    ISPEECH1_G722_BITRATE_RATE3 = 3,     /**< @todo Need clearer description */

    /** Default setting. */
    ISPEECH1_G722_BITRATE_DEFAULT = ISPEECH1_G722_BITRATE_RATE0
} ISPEECH1_G722_BitRate;

typedef enum {
    ISPEECH1_G722_CODECSELECT_NONITUMODE = 0,    /* with QMF support */
    ISPEECH1_G722_CODECSELECT_ITUMODE    = 1,    /* Subband coding without QMF */
    /** Default setting. */   _
    ISPEECH1_G722_CODECSELECT_DEFAULT = ISPEECH2_G722_CODECSELECT_NONITUMODE
} ISPEECH1_G722_CodecSelect;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
