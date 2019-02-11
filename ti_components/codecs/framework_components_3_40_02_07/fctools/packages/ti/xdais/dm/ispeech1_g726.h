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
 *  @file       ti/xdais/dm/ispeech1_g726.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for G.726
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_G726  ISPEECH1_G726 - XDM Speech Interface (G.726)
 *
 *  This is the XDM speech interface shared between the various G.726 codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_G726_
#define ti_xdais_dm_ISPEECH1_G726_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_G726 */
/*@{*/


/**
 *  @brief      Bit rate selection for G726.
 */
typedef enum {
    ISPEECH1_G726_BITRATE_16  = 0,     /**<  16  kbps */
    ISPEECH1_G726_BITRATE_24  = 1,     /**<  24  kbps */
    ISPEECH1_G726_BITRATE_32  = 2,     /**<  32  kbps */
    ISPEECH1_G726_BITRATE_40  = 3,     /**<  40  kbps */

    /** Default setting. */
    ISPEECH1_G726_BITRATE_DEFAULT = ISPEECH1_G726_BITRATE_40
} ISPEECH1_G726_BitRate;


/**
 *  @brief      Companding law of encoder input and decoder output samples.
 */
typedef enum {
    ISPEECH1_G726_COMPAND_LINEAR = 0,      /**< Linear */
    ISPEECH1_G726_COMPAND_ALAW = 1,        /**< A-law */
    ISPEECH1_G726_COMPAND_ULAW = 2,        /**< Mu-law */

    /** Default setting. */
    ISPEECH1_G726_COMPAND_DEFAULT = ISPEECH1_G726_COMPAND_LINEAR
} ISPEECH1_G726_CompandingLaw;


/**
 *  @brief      Packing Type defintions for G.726
 */
typedef enum {
    ISPEECH1_G726_PACKTYPE_LINEAR = 0,     /**< Linear packing. */
    ISPEECH1_G726_PACKTYPE_RTPSPECIAL = 1, /**< RTP special format. */

    /** Default setting. */
    ISPEECH1_G726_PACKTYPEFORMAT_DEFAULT = ISPEECH1_G726_PACKTYPE_LINEAR
} ISPEECH1_G726_PackingType;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
