/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 * ======== usertype.h ========
 *
 * - Basic C types
 * - Some IP related equates
 * - Data access macros
 *
 */

#ifndef _C_USERTYPE_INC
#define _C_USERTYPE_INC

typedef char           INT8;
typedef short          INT16;
typedef int            INT32;
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;
#ifndef _CSL_EMAC_TYPES
/* The same type is defined in "csl_mdio.h" as well. */
typedef unsigned int   uint;
#endif
typedef void *         HANDLE;
typedef UINT32         IPN;             /* IP Address in NETWORK format */

/* IPV6 Address in Network Format. */
typedef struct IP6N
{
    union
    {
        UINT8   addr8[16];
        UINT16  addr16[8];
        UINT32  addr32[4];
    }u;
}IP6N;

#define _IPv6_a2i(a) (*(IP6N *)&a)

#ifdef BIGENDIAN

/* BIG ENDIAN */

/*----------------------------------------------------------------------- */
/* Data Host/Network Byte Order Conversion */
#define HNC16(a) (a)
#define HNC32(a) (a)

/*----------------------------------------------------------------------- */
/* 32 Bit Data Macros (from 16 bit aligned data) */
/*#define RdNet32(x)   (*(UINT32 *)(x)) */
/*#define WrNet32(x,y) (*(UINT32 *)(x) = y) */
#define RdNet32(x)   (((UINT32)(*(UINT16 *)(x))<<16)|(UINT32)(*(UINT16 *)(((UINT8 *)(x))+2)))
#define WrNet32(x,y) *(UINT16 *)(x)=(UINT16)((y)>>16); *(UINT16 *)(((UINT8 *)(x))+2)=(UINT16)(y)

/*----------------------------------------------------------------------- */
/* READ/WRITE Macros (aligned) */
#define READ32(x)    (*(volatile unsigned int *)x)
#define WRITE32(x,y) (*(volatile unsigned int *)(x) = (y))

/*----------------------------------------------------------------------- */
/* IP Address Related Equates */
#define IN_CLASSA(x)            (((UINT32)(x) & 0x80000000) == 0)
#define IN_CLASSB(x)            (((UINT32)(x) & 0xc0000000) == 0x80000000)
#define IN_CLASSC(x)            (((UINT32)(x) & 0xe0000000) == 0xc0000000)
#define IN_CLASSD(x)            (((UINT32)(x) & 0xf0000000) == 0xe0000000)
#define IN_MULTICAST(x)         IN_CLASSD(x)
#define IN_EXPERIMENTAL(x)      (((UINT32)(x) & 0xf0000000) == 0xf0000000)
#define IN_LOOPBACK(x)          (((UINT32)(x) & 0xff000000) == 0x7f000000)
#define INADDR_ANY              0x00000000     /* 0.0.0.0 */
#define INADDR_BROADCAST        0xffffffff     /* 255.255.255.255 */

#else

/* LITTLE ENDIAN */

/*----------------------------------------------------------------------- */
/* Data Host/Network Byte Order Conversion */
#define HNC16(a) ( (((a)>>8)&0xff) + (((a)<<8)&0xff00) )

/*
 * Fix warning when compiling for IAR (SDOCM00103001):
 *
 *     Warning[Pe061]: integer operation result is out of range
 *
 * This macro has been updated to perform masking operations before shifting.
 * In its previous form (which shifts THEN masks), the IAR compiler generated
 * a warning because it did not like shaving off bits, as it is a (potential)
 * accidental loss of data.  Changing the code to mask first (purposefully
 * losing the data) then shifting afterward fixes the warning.
 *
 * Note that the TI and GCC compilers never cared about this ...
 *
 */
#define HNC32(a) ((((a) & 0xff000000) >> 24) | (((a) & 0x00ff0000) >> 8) | \
                  (((a) & 0x0000ff00) << 8)  | (((a) & 0x000000ff) << 24))

/*----------------------------------------------------------------------- */
/* 32 Bit Data Macros (from 16 bit aligned data) */
/*#define RdNet32(x)   (*(UINT32 *)(x)) */
/*#define WrNet32(x,y) (*(UINT32 *)(x) = y) */
#define RdNet32(x)   ((UINT32)(*(UINT16 *)(x))|((UINT32)(*(UINT16 *)(((UINT8 *)(x))+2))<<16))
#define WrNet32(x,y) *(UINT16 *)(x)=(UINT16)(y); *(UINT16 *)(((UINT8 *)(x))+2)=(UINT16)((y)>>16)

/*----------------------------------------------------------------------- */
/* READ/WRITE Macros (aligned) */
#define READ32(x)    (*(volatile unsigned int *)x)
#define WRITE32(x,y) (*(volatile unsigned int *)(x) = (y))

/*----------------------------------------------------------------------- */
/* IP Address Related Equates */
#define IN_CLASSA(x)            (((UINT32)(x) & 0x00000080) == 0)
#define IN_CLASSB(x)            (((UINT32)(x) & 0x000000c0) == 0x00000080)
#define IN_CLASSC(x)            (((UINT32)(x) & 0x000000e0) == 0x000000c0)
#define IN_CLASSD(x)            (((UINT32)(x) & 0x000000f0) == 0x000000e0)
#define IN_MULTICAST(x)         IN_CLASSD(x)
#define IN_EXPERIMENTAL(x)      (((UINT32)(x) & 0x000000f0) == 0x000000f0)
#define IN_LOOPBACK(x)          (((UINT32)(x) & 0x000000ff) == 0x0000007f)
#define INADDR_ANY              0x00000000     /* 0.0.0.0 */
#define INADDR_BROADCAST        0xffffffff     /* 255.255.255.255 */

#endif

#endif
