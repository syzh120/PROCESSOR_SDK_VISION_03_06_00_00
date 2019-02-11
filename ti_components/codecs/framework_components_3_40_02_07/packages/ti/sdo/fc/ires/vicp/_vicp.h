/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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

#ifndef _VICP_H
#define _VICP_H


/* VICP/IMCOP Memory banks */
/* IMX */
#define IMGBUF_BASE (unsigned char *)0x00000
                            /* A&B ping-pong view*/
#define IMGBUF_A_FULL_BASE  (unsigned char *)0x04000
                            /* A in full view*/
#define IMGBUF_B_FULL_BASE  (unsigned char *)0x06000
                            /* B in full view*/
#define IMXCOEFFBUF_BASE    (unsigned char *)0x08000
                            /* iMX working memory*/
#define IMXCMDBUF_BASE      (unsigned char *)0x14000
                            /* iMX command memory*/

/* SEQ */
#define SEQ_PMEM_BASE       (unsigned char *)0x10000
                            /* SEQ prog memory*/
#define SEQDATA_BASE        (unsigned char *)0x1F400
                            /* SEQ data memory*/

/* VLCD */
#define VLCDDATA_BASE       (unsigned char *)0x11000
                            /* data memory (vmem)*/
#define VLCDBUF_BASE        (unsigned char *)0x12000
                            /* Huffman mem (hmem)*/
#define QIQBUF_BASE         (unsigned char *)0x13000
                            /* Quant mem (qmem)*/

/* sizes of memory segments in bytes */
#define IMGBUF_SIZE         (unsigned int)0x4000   /* 16K in full view */
#define IMGBUF_A_SIZE       (unsigned int)0x2000   /* each img buf is 8K  */
#define IMGBUF_B_SIZE       (unsigned int)0x2000   /* 8K  */
#define IMXCOEFFBUF_SIZE    (unsigned int)0x8000   /* 32K */
#define IMXCMDBUF_SIZE      (unsigned int)0x2000   /* 8K  */
#define VLCDDATA_SIZE       (unsigned int)0x1000   /* 4K  */
#define QIQBUF_SIZE         (unsigned int)0x0400   /* 1K  */
#define VLCDBUF_SIZE        (unsigned int)0x1000   /* 4K  */
#define SEQMEM_SIZE         (unsigned int)0x1000   /* 4K  */
#define SEQDATA_SIZE        (unsigned int)0x0400   /* 1K  */

#endif /* _VICP_H */
