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
 *  @file       ti/xdais/dm/iaudio.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across the various audio codecs.
 */
/**
 *  @defgroup   ti_xdais_dm_IAUDIO    IAUDIO - XDM Audio Interface
 *
 *  This is the XDM audio interface shared between the various codecs.
 */

#ifndef ti_xdais_dm_IAUDIO_
#define ti_xdais_dm_IAUDIO_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IAUDIO */
/*@{*/

#ifdef XDM_INCLUDE_DOT9_SUPPORT
/**
 *  @brief      XDM supported audio channel configurations.
 *
 *  @deprecated This enumeration is only supported on 0.9 XDM.  To use it, you
 *              must define "XDM_INCLUDE_DOT9_SUPPORT" prior to including this
 *              file.  In XDM 1.00, this has been superceded by
 *              IAUDIO_ChannelMode.
 */
typedef enum {
    IAUDIO_MONO = 0,        /**< Single channel. */
    IAUDIO_STEREO = 1,      /**< Two channel. */
    IAUDIO_THREE_ZERO = 2,  /**< Three channel. */
    IAUDIO_FIVE_ZERO = 3,   /**< Five channel. */
    IAUDIO_FIVE_ONE = 4,    /**< 5.1 channel. */
    IAUDIO_SEVEN_ONE = 5    /**< 7.1 channel. */
} IAUDIO_ChannelId;
#endif


/**
 *  @brief      Channel modes for audio streams.
 *
 *  The channel modes not only indicate the number of channels, but also
 *  indicate the order in which the channels are placed in the input or
 *  output buffer.  The placement of channels is indicated next to each
 *  channel mode.
 *
 *  @enumWarning
 *
 *  @extendedEnum
 */
typedef enum
{
    IAUDIO_1_0 = 0,         /**< Mono. */
    IAUDIO_2_0 = 1,         /**< Stereo. */
    IAUDIO_11_0 = 2,        /**< Dual Mono.
                             *
                             *   @sa    IAUDIO_DualMonoMode
                             */
    IAUDIO_3_0 = 3,         /**< Left, Right, Center. */
    IAUDIO_2_1 = 4,         /**< Left, Right, Sur. */
    IAUDIO_3_1 = 5,         /**< Left, Right, Center, Sur. */
    IAUDIO_2_2 = 6,         /**< Left, Right, SurL, SurR. */
    IAUDIO_3_2 = 7,         /**< Left, Right, Center, SurL, SurR. */
    IAUDIO_2_3 = 8,         /**< Left, Right, SurL, SurR, surC. */
    IAUDIO_3_3 = 9,         /**< Left, Right, Center, SurL, SurR, surC. */
    IAUDIO_3_4 =10          /**< Left, Right, Center, SurL, SurR, sideL, sideR.
                             */
} IAUDIO_ChannelMode;


/**
 *  @brief      Dual Mono Channel modes for audio streams.
 *
 *  @remarks    In case of Dual Mono the application can play both channels;
 *              Left Only, Right Only or Mix and Play both.  The
 *              default case in most of the applications is the first
 *              case of IAUDIO_DUALMONO_LR. That is to play both Left
 *              and Right Channel.
 *
 *  @enumWarning
 *
 *  @extendedEnum
 */
typedef enum
{
    IAUDIO_DUALMONO_LR = 0,  /**< Play/encode both left and right channel */
    IAUDIO_DUALMONO_LEFT = 1,/**< Play/encode only left channel. */
    IAUDIO_DUALMONO_RIGHT = 2,/**< Play/encode only right channel. */
    IAUDIO_DUALMONO_LR_MIX = 3/**< Mix and play. */
} IAUDIO_DualMonoMode;


/**
 *  @brief      XDM supported audio PCM formats
 *
 *  @enumWarning
 *
 *  @extendedEnum
 */
typedef enum {
    /**
     *  Left channel data followed by right channel data.
     *  Note, for single channel (mono), right channel data will be the same
     *  as the left channel data.
     */
    IAUDIO_BLOCK = 0,

    /**
     *  Left and right channel data interleaved.
     *  Note, for single channel (mono), right channel data will be the same
     *  as the left channel data.
     */
    IAUDIO_INTERLEAVED = 1
} IAUDIO_PcmFormat;


/**
 *  @brief      Audio encoding modes.
 *
 *  @enumWarning
 *
 *  @extendedEnum
 */
typedef enum
{
    IAUDIO_CBR = 0,     /**< Constant bit rate. */
    IAUDIO_VBR = 1      /**< Variable bit rate. */
} IAUDIO_EncMode;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
