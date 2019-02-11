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
/**
 *  ======== _edma3Chan.h ========
 *  internal edma3Chan protocol and iresman definitions
 *
 */

#ifndef _EDMA3CHAN
#define _EDMA3CHAN

/**
 * @brief       The offset of the PARAMs from the EDMA3 Configuration base
 */
#define IRES_EDMA3CHAN_PARAMBASEOFFSET  0x4000;

/*
 * Convenient macros to set appropriate bits in IRES_EDMA3Chan_PaRamStruct
 * Registers "opt" field
 */
#define IRES_EDMA3CHAN_PARAMSTRUCT_OPT_ABSYNC       (0x1 << 2)
                                                            /* AB_SYNC */
#define IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCINTEN     (0x1 << 20)
                                                            /* TCC_INT_EN */
#define IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCSTATIC    (0x1 << 3)
                                                            /* STATIC  */
#define IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCMASK      0x3f000
#define IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCBITS(tcc) ((tcc) << 12)
                                                            /*
                                                             * TCC starts at
                                                             * bit 12 of opt
                                                             */
#define IRES_EDMA3CHAN_PARAMSTRUCT_NULLLINK         0xFFFF

/*
 * Macros to extract information from CCCFG register
 */
#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMDMACH(addr) \
        ( (( (addr) & 0x7)==0) ? 0 : (0x2<<((addr) & 0x7)) )

#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMQDMACH(addr) \
        ( (( (addr) >> 4) & 0x7) << 0x1)

#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMINTCH(addr) \
        ( (( ((addr)>>8)&0x7)==0) ? 0 : (0x4 << (((addr)>>8) & 0x7)) )

#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMPAENTRY(addr) \
        ( (( ((addr) >>12) & 0x7)==0) ? 0x10 : ( 0x10 << (( (addr) >> 12)&0x7)))

#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMEVTQUE(addr) \
        ( (( (addr)>>16) & 0x7) + 1)

#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMREGN(addr) \
        ( (( ((addr)>>20) & 0x3) ==0) ? 0 : ( 0x1 << (((addr)>>20)&0x3) ) )

#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_CHMAPEXIST(addr) \
        ( ((addr) >> 24) & 0x1)

#define  IRES_EDMA3CHAN_EDMA3REGISTERLAYER_MPEXIST(addr) \
        ( ((addr) >> 25) & 0x1)

/**
 *  @brief      Internal state
 */
typedef struct IRES_EDMA3CHAN_InternalState {

    unsigned int edma3BaseAddress;                  /* Base address of EDMA3 */

} IRES_EDMA3CHAN_InternalState;

#endif /* _EDMA3CHAN */
