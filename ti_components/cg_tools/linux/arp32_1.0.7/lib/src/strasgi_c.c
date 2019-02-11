/******************************************************************************/
/* strasg  v1.0.7                                                             */
/*                                                                            */
/* Copyright (c) 1998-2015 Texas Instruments Incorporated                     */
/* http://www.ti.com/                                                         */
/*                                                                            */
/*  Redistribution and  use in source  and binary forms, with  or without     */
/*  modification,  are permitted provided  that the  following conditions     */
/*  are met:                                                                  */
/*                                                                            */
/*     Redistributions  of source  code must  retain the  above copyright     */
/*     notice, this list of conditions and the following disclaimer.          */
/*                                                                            */
/*     Redistributions in binary form  must reproduce the above copyright     */
/*     notice, this  list of conditions  and the following  disclaimer in     */
/*     the  documentation  and/or   other  materials  provided  with  the     */
/*     distribution.                                                          */
/*                                                                            */
/*     Neither the  name of Texas Instruments Incorporated  nor the names     */
/*     of its  contributors may  be used to  endorse or  promote products     */
/*     derived  from   this  software  without   specific  prior  written     */
/*     permission.                                                            */
/*                                                                            */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS     */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT     */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR     */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT     */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT     */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT     */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      */
/*                                                                            */
/******************************************************************************/

/*---------------------------------------------------------------------------*/
/* STRASGI: Generic struct assign routine.  This is based on c6x strasgi_c.c */
/*---------------------------------------------------------------------------*/
int *__arp32abi_strasgi(int *dst, const int *src, unsigned cnt)
{
    int i;
    int *odst = dst;

    cnt /= 4;

    _nassert(cnt >= 7);

    /*-----------------------------------------------------------------------*/
    /* This loop has been manually unrolled to copy two words per iteration  */
    /* in order to avoid a hardware stall on dependent LD-ST instructions    */
    /* that are scheduled back-to-back.                                      */
    /*-----------------------------------------------------------------------*/
    for (i = 0; i < cnt-1; i += 2)
    {
        int j, k;
        j = *src++;
        k = *src++;
        *dst++ = j;
        *dst++ = k;
    }

    /*-----------------------------------------------------------------------*/
    /* If copying an odd number of words, perform one last copy              */
    /*-----------------------------------------------------------------------*/
    if (i == cnt-1) { *dst++ = *src++; }

    return odst;
}
