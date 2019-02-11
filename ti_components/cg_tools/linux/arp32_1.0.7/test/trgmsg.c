/*****************************************************************************/
/*  TRGMSG.C v1.0.7                                                          */
/*                                                                           */
/* Copyright (c) 1995-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Bottom level data transfer routines for host communication with the       */
/* target.                                                                   */
/*                                                                           */
/* Functions:                                                                */
/*  writemsg()  -  Sends the passed data and parameters on to the host.      */
/*  readmsg()   -  Reads the data and parameters passed from the host.       */
/*****************************************************************************/
#include "stdio.h"
#include "trgcio.h"

__asm("\t.global C$$IO$$");

#pragma DATA_SECTION (__CIOBUF_, ".cio");
#pragma DATA_ALIGN   (__CIOBUF_, 4);
#define DEFCIO(size) _DATA_ACCESS volatile unsigned char __CIOBUF_[size]

DEFCIO(CIOBUFSIZ);


/***************************************************************************/
/*                                                                         */
/*  WRITEMSG()  -  Sends the passed data and parameters on to the host.    */
/*                                                                         */
/***************************************************************************/
_CODE_ACCESS void writemsg(               unsigned char  command,
                           register const unsigned char *parm,
                           register const          char *data,
                                          unsigned int   length)
{
    register unsigned volatile char * p = (volatile unsigned char *) __CIOBUF_;
    register unsigned int i;

    /***********************************************************************/
    /* THE LENGTH IS WRITTEN AS A TARGET INT                               */
    /***********************************************************************/ 
    *(unsigned int *)p = length; 
    p += sizeof(unsigned int);

    /***********************************************************************/ 
    /* THE COMMAND IS WRITTEN AS A TARGET BYTE                             */
    /***********************************************************************/ 
    *p++ = command;

    /***********************************************************************/ 
    /* PACK THE PARAMETERS AND DATA SO THE HOST READS IT AS BYTE STREAM    */
    /***********************************************************************/ 
    for (i = 0; i < 8; i++)      PACKCHAR(*parm++, p, i);
    for (i = 0; i < length; i++) PACKCHAR(*data++, p, i+8);

#pragma diag_suppress 1119
#ifndef __VIRTUAL_ENCODING__
    /***********************************************************************/
    /* THE BREAKPOINT THAT SIGNALS THE HOST TO DO DATA TRANSFER            */
    /***********************************************************************/
    __asm("	.global	C$$IO$$");
    __asm("C$$IO$$:nop");
#else
    /*---------------------------------------------------------------------*/
    /* GENERATE THE C$$IO INSTRUCTION                                      */
    /*---------------------------------------------------------------------*/
    __asm("C$$IO$$: .vinstr   C$$IO_INTERNAL");
    __asm("C$$IO_INTERNAL: .encode \"C$$IO\",$ENC_DISASM,\"C$$IO\", $ENC_OPNDS, 0");
#endif
#pragma diag_default 1119
}


/***************************************************************************/
/*                                                                         */
/*  READMSG()   -  Reads the data and parameters passed from the host.     */
/*                                                                         */
/***************************************************************************/
_CODE_ACCESS void readmsg(register unsigned char *parm,
                          register char          *data)
{
    register unsigned volatile char * p = (volatile unsigned char *) __CIOBUF_;
    register unsigned int i;
    unsigned int length;

    /***********************************************************************/
    /* THE LENGTH IS READ AS A TARGET INT                                  */
    /***********************************************************************/
    length = *(unsigned int *)p;
    p += sizeof(unsigned int);
    
    /***********************************************************************/
    /* UNPACK THE PARAMETERS AND DATA                                      */
    /***********************************************************************/
    for (i = 0; i < 8; i++) *parm++ = UNPACKCHAR(p, i);
    if (data != NULL) 
       for (i = 0; i < length; i++) *data++ = UNPACKCHAR(p, i+8);
}
