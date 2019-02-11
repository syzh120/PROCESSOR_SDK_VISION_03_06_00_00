/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 * */
/*
 * ======== pbm_data.c ========
 */

#include <xdc/std.h>
#include <stkmain.h>

/*
 * NDK frame buffer size and number of frames 
 * 
 * Each frame buffer is used to store a single Ethernet frame. Typically the
 * size needed for this is 1514 octets (bytes) which allows for the 1500 byte
 * Ethernet payload plus the 14 byte Ethernet header (6 byte destination MAC
 * address, 6 byte source MAC address and 2 byte protocol type field).
 *
 * The original implementation of this code was written to work with the (now
 * outdated) "Macronix MAC" hardware.  This device required a larger frame
 * buffer size of 1664 bytes in order to support a data pre-pad and 16 byte 
 * data transfers.  Therefore, devices which do not use this Macronix MAC
 * (which should be all devices supported by TI today) can reduce this size as
 * needed.  For compatibility reasons, the default for C6000 still uses the
 * original 1664 frame buffer size. 
 */

/*
 * Local Packet Buffer Pool Definitions
 *
 * Number of buffers (Ethernet frames) in PBM packet buffer free pool 
 * The number of buffers in the free pool can have a significant effect 
 * on performance, especially in UDP packet loss. Increasing this number 
 * will increase the size of the static packet pool use for both sending 
 * and receiving packets. 
 * DM642 Users Note: The DM642 Ethernet driver assumes that its local 
 * buffer allocation (EMAC_MAX_RX in dm642.c) plus PKT_NUM_FRAMEBUF 
 * defined below is less than or equal to 256. The default value for 
 * EMAC_MAX_RX in the DM642 Ethernet driver is 16. 
 * This size may be overridden by defining _NDK_MIN_PBM_BUFS.  If defined, the 
 * value for PKT_NUM_FRAMEBUF must be defined elsewhere.
 */
#ifndef _NDK_MIN_PBM_BUFS
#define PKT_NUM_FRAMEBUF    192
#endif

/*
 *  Max Ethernet frame size
 *
 * On L2 cached CPUs, this size must be cache-line multiple 
 * The LogicIO Etherent (Macronix MAC) requires a larger buffer because 
 * it transfers data in 16 byte chunks, and with its pre-pad and data 
 * alignment, it will overflow a 1536 byte buffer. 
 *
 * If the LogicIO/Maxcronix support is not required, this value can 
 * be reduced to 1536. 
 *
 * This size may be overridden by defining _NDK_MIN_PBM_BUFS.  If defined, the 
 * value for PKT_SIZE_FRAMEBUF must also be defined elsewhere.
 */
#ifndef _NDK_MIN_PBM_BUFS
#if defined(_TMS320C6X)
/*
 * Keep original Ethernet frame size for C6x as there's plenty of RAM on C6x
 * devices (Ethernet 1500 byte MTU + Ethernet 14 byte header size + extra space
 * needed for Macronix device special case).
 */
#define PKT_SIZE_FRAMEBUF   1664
#else
/*
 * For non-C6x cores including ARM, reduce extra size added for Macronix
 * device, assume cache exists and align frame size (Ethernet 1500 byte MTU +
 * Ethernet 14 byte header size) to nearest mulitple of 128.
 */
#define PKT_SIZE_FRAMEBUF   1536
#endif
#endif

const int ti_ndk_config_Global_numFrameBuf  = PKT_NUM_FRAMEBUF;
const int ti_ndk_config_Global_sizeFrameBuf = PKT_SIZE_FRAMEBUF;

/* Data space for packet buffers */

#ifdef __TI_COMPILER_VERSION__
#pragma DATA_ALIGN(ti_ndk_config_Global_pBufMem, 128);
#if defined(_TMS320C6X)
#pragma DATA_SECTION(ti_ndk_config_Global_pBufMem, ".far:NDK_PACKETMEM");
#else
#pragma DATA_SECTION(ti_ndk_config_Global_pBufMem, ".bss:NDK_PACKETMEM");
#endif
UINT8 ti_ndk_config_Global_pBufMem[PKT_NUM_FRAMEBUF*PKT_SIZE_FRAMEBUF];
#elif defined (__IAR_SYSTEMS_ICC__)
#pragma data_alignment = 128
UINT8 ti_ndk_config_Global_pBufMem[PKT_NUM_FRAMEBUF*PKT_SIZE_FRAMEBUF];
#else
/* force cache alignment for all ARM targets because A15 and A8 have cache */
UINT8 ti_ndk_config_Global_pBufMem[PKT_NUM_FRAMEBUF*PKT_SIZE_FRAMEBUF] __attribute__ ((aligned(128)));
#endif

#ifdef __TI_COMPILER_VERSION__
#pragma DATA_ALIGN(ti_ndk_config_Global_pHdrMem, 128);
#if defined(_TMS320C6X)
#pragma DATA_SECTION(ti_ndk_config_Global_pHdrMem, ".far:NDK_PACKETMEM");
#else
#pragma DATA_SECTION(ti_ndk_config_Global_pHdrMem, ".bss:NDK_PACKETMEM");
#endif
UINT8 ti_ndk_config_Global_pHdrMem[PKT_NUM_FRAMEBUF*sizeof(PBM_Pkt)];
#elif defined (__IAR_SYSTEMS_ICC__)
#pragma data_alignment = 128
UINT8 ti_ndk_config_Global_pHdrMem[PKT_NUM_FRAMEBUF*sizeof(PBM_Pkt)];
#else
/* force cache alignment for all ARM targets because A15 and A8 have cache */
UINT8 ti_ndk_config_Global_pHdrMem[PKT_NUM_FRAMEBUF*sizeof(PBM_Pkt)] __attribute__ ((aligned(128)));
#endif

