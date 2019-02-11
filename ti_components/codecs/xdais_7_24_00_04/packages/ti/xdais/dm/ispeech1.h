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
 *  @file       ti/xdais/dm/ispeech1.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across the various speech codecs.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1  ISPEECH - XDM Speech Interface
 *
 *  This is the XDM speech interface shared between the various
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_
#define ti_xdais_dm_ISPEECH1_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1 */
/*@{*/


/**
 *  @brief      Null traffic channel setting.
 *
 *  @sa         ISPHENC1_InArgs.nullTrafficChannel.
 */
typedef enum {
    ISPEECH1_NULLTRAFFICMODE_OFF = 0,  /**< Null traffic channel frames
                                        *   disabled, normal speech encoding
                                        *   is enabled.
                                        */
    ISPEECH1_NULLTRAFFICMODE_ON = 1,   /**< Null traffic channel frames
                                        *   enabled.
                                        */

    /** @copydoc ISPEECH1_NULLTRAFFICMODE_OFF */
    ISPEECH1_NULLTRAFFICMODE_DEFAULT = ISPEECH1_NULLTRAFFICMODE_OFF
} ISPEECH1_NullTrafficMode;


/**
 *  @brief      Post filter setting.
 *
 *  These values are used for enabling/disabling the post filter.
 */
typedef enum {
    ISPEECH1_POSTFILTER_OFF = 0,       /**< Post Filter disabled. */
    ISPEECH1_POSTFILTER_ON = 1,        /**< Post Filter enabled. */

    /** @copydoc ISPEECH1_POSTFILTER_ON */
    ISPEECH1_POSTFILTER_DEFAULT = ISPEECH1_POSTFILTER_ON
} ISPEECH1_PostFilter;



/**
 *  @brief      Voice Activity Detection (VAD) setting.
 */
typedef enum {
    ISPEECH1_VADFLAG_OFF = 0,          /**< Voice Activity Detection off. */
    ISPEECH1_VADFLAG_ON = 1,           /**< Voice Activity Detection on. */

    /** @copydoc ISPEECH1_VADFLAG_ON */
    ISPEECH1_VADFLAG_DEFAULT = ISPEECH1_VADFLAG_ON
} ISPEECH1_VADFlag;

/*@}*/


#ifdef __cplusplus
}
#endif

#endif
