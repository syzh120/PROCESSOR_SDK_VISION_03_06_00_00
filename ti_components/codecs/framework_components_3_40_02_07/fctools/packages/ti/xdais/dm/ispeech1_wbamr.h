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
 *  @file       ti/xdais/dm/ispeech1_wbamr.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for WB-AMR
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_WBAMR  ISPEECH1_WBAMR - XDM Speech Interface (WBAMR)
 *
 *  This is the XDM speech interface shared between the various WB-AMR codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_WBAMR_
#define ti_xdais_dm_ISPEECH1_WBAMR_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_WBAMR */
/*@{*/


/**
 *  @brief      Packing Type defintions for AMR
 */
typedef enum {
    ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC = 0,  /**< Interface format 1,
                                              *   without CRC check (as per
                                              *   3GPP 26.201).
                                              */
    ISPEECH1_WBAMR_PACKTYPE_IF1_WITHCRC = 1,/**< Interface format 1,
                                              *   with CRC check (as per
                                              *   3GPP 26.201).
                                              */
    ISPEECH1_WBAMR_PACKTYPE_IF2 = 2,        /**< Interface format 2 (as
                                              *   per 3GPP 26.201).
                                              */
    ISPEECH1_WBAMR_PACKTYPE_MIME = 3,       /**< MIME/MMSIO/file storage
                                              *   format.
                                              */

    /** Default setting. */
    ISPEECH1_WBAMR_PACKTYPEFORMAT_DEFAULT = ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC
} ISPEECH1_WBAMR_PackingType;


/**
 *  @brief      Bitrate selection for AMR
 */
typedef enum {
    ISPEECH1_WBAMR_BITRATE_6P60  = 0,   /**<  6.60 kbps */
    ISPEECH1_WBAMR_BITRATE_8P85  = 1,   /**<  8.85 kbps */
    ISPEECH1_WBAMR_BITRATE_12P65 = 2,   /**< 12.65 kbps */
    ISPEECH1_WBAMR_BITRATE_14P25 = 3,   /**< 14.25 kbps */
    ISPEECH1_WBAMR_BITRATE_15P85 = 4,   /**< 15.85 kbps */
    ISPEECH1_WBAMR_BITRATE_18P25 = 5,   /**< 18.25 kbps */
    ISPEECH1_WBAMR_BITRATE_19P85 = 6,   /**< 19.85 kbps */
    ISPEECH1_WBAMR_BITRATE_23P05 = 7,   /**< 23.05 kbps */
    ISPEECH1_WBAMR_BITRATE_23P85 = 8,   /**< 23.85 kbps */

    /** Default setting. */
    ISPEECH1_WBAMR_BITRATE_DEFAULT = ISPEECH1_WBAMR_BITRATE_23P85
} ISPEECH1_WBAMR_BitRate;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
