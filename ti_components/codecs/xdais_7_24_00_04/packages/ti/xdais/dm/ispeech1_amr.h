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
 *  @file       ti/xdais/dm/ispeech1_amr.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for AMR.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_AMR  ISPEECH_AMR - XDM Speech Interface (AMR)
 *
 *  This is the XDM speech interface shared between the various AMR codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_AMR_
#define ti_xdais_dm_ISPEECH1_AMR_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_AMR */
/*@{*/


/**
 *  @brief      Bitrate selection for AMR
 */
typedef enum {
    ISPEECH1_AMR_BITRATE_4P75 = 0,     /**<  4.75 kbps */
    ISPEECH1_AMR_BITRATE_5P15 = 1,     /**<  5.15 kbps */
    ISPEECH1_AMR_BITRATE_5P9  = 2,     /**<  5.9  kbps */
    ISPEECH1_AMR_BITRATE_6P7  = 3,     /**<  6.7  kbps */
    ISPEECH1_AMR_BITRATE_7P4  = 4,     /**<  7.4  kbps */
    ISPEECH1_AMR_BITRATE_7P95 = 5,     /**<  7.95 kbps */
    ISPEECH1_AMR_BITRATE_10P2 = 6,     /**< 10.2  kbps */
    ISPEECH1_AMR_BITRATE_12P2 = 7,     /**< 12.2  kbps */

    /** Default setting. */
    ISPEECH1_AMR_BITRATE_DEFAULT = ISPEECH1_AMR_BITRATE_12P2
} ISPEECH1_AMR_BitRate;


/**
 *  @brief      Codec selection.
 *
 *  @remarks    This parameter is used to select the codec in cases where
 *              multiple codecs are supported from the same code base.
 */
typedef enum {
    ISPEECH1_AMR_CODECSELECT_PRIMARY = 0,      /**< Primary mode - AMR. */
    ISPEECH1_AMR_CODECSELECT_SECONDARY = 1,    /**< Secondary mode - EFR. */

    /** Default setting. */
    ISPEECH1_AMR_CODECSELECT_DEFAULT = ISPEECH1_AMR_CODECSELECT_PRIMARY
} ISPEECH1_AMR_CodecSelect;


/**
 *  @brief      Packing type options for AMR.
 */
typedef enum {
    ISPEECH1_AMR_PACKTYPE_IF1_NOCRC = 0,     /**< Interface format 1,
                                              *   without CRC check (as per
                                              *   3GPP 26.101).
                                              */
    ISPEECH1_AMR_PACKTYPE_IF1_WITHCRC = 1,   /**< Interface format 1,
                                              *   with CRC check (as per
                                              *   3GPP 26.101).
                                              */
    ISPEECH1_AMR_PACKTYPE_IF2 = 2,           /**< Interface format 2 (as
                                              *   per 3GPP 26.101).
                                              */
    ISPEECH1_AMR_PACKTYPE_MIME = 3,          /**< MIME/MMSIO/file storage
                                              *   format.
                                              */

    /** Default setting. */
    ISPEECH1_AMR_PACKTYPEFORMAT_DEFAULT = ISPEECH1_AMR_PACKTYPE_IF1_NOCRC
} ISPEECH1_AMR_PackingType;


/**
 *  @brief      Voice activity detector (VAD) selection.
 */
typedef enum {
    ISPEECH1_AMR_VADSELECT_VAD1 = 1,    /**< VAD 1 */
    ISPEECH1_AMR_VADSELECT_VAD2 = 2,    /**< VAD 2 */

    /** Default setting. */
    ISPEECH1_AMR_VADSELECT_DEFAULT = ISPEECH1_AMR_VADSELECT_VAD1
} ISPEECH1_AMR_VADSelect;


/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_AMR_ */
