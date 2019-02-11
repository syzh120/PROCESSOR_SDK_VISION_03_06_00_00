/****************************************************************************/
/*  MEMCPY v1.0.7                                                           */
/*                                                                          */
/* Copyright (c) 1993-2015 Texas Instruments Incorporated                   */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/
#undef _INLINE
#include <string.h>

/*---------------------------------------------------------------------------*/
/* MEMCPY: Generic memory copy routine.  This is an optimized memcpy routine */
/*         based on c6x memcpy62.c                                           */
/*---------------------------------------------------------------------------*/
_CODE_ACCESS void *memcpy(void *dst, const void *src, size_t len)
{
   char *restrict d0    = (char*) dst;
   char *restrict s0    = (char*) src;
   int            s_aln = ((int)s0 & 0x3);
   int            d_aln = ((int)d0 & 0x3);
   int            prebytes;
   int            len2;
   unsigned int   i;

   /*------------------------------------------------------------------------*/
   /* If our source and destination are not aligned correctly for word copy, */
   /* or our length is less than eight bytes, just do a byte copy.  We must  */
   /* do a byte copy for length less than four bytes, but we choose eight    */
   /* bytes in order to avoid wasting unnecessary cycles for small length    */
   /* copies.                                                                */
   /*------------------------------------------------------------------------*/
   if ((s_aln != d_aln) || len < 8)
   {
      if (len > 0)
      {
          /*----------------------------------------------------------------*/
          /* This loop has been manually unrolled to copy two bytes per     */
          /* iteration in order to avoid a hardware stall on dependent load */
          /* and store instructions that are scheduled back-to-back.        */
          /*----------------------------------------------------------------*/
          for (i = 0; i < len-1; i+=2) 
          {
              char j, k;
              j = *(char *)s0++;
              k = *(char *)s0++;
              *(char *)d0++ = j;
              *(char *)d0++ = k;
          }

          /*---------------------------------------------------------------*/
          /* If copying an odd number of bytes, perform one last copy      */
          /*---------------------------------------------------------------*/
          if (i == len-1) { *(char *)d0 = *(char *)s0; }
      }

      return dst;
   }

   /*------------------------------------------------------------------------*/
   /* Precopy 4-s_aln bytes, in order to align src and dst to word boundary. */
   /*------------------------------------------------------------------------*/
   prebytes = (4 - s_aln) & 3;
   if (prebytes & 0x1)  *d0++ = *s0++;
   if (prebytes & 0x2)  { *(short *)(d0) = *(short *)(s0); d0 += 2; s0 += 2; }

   /*------------------------------------------------------------------------*/
   /* Copy bytes in 32-bit word chunks.                                      */
   /* At this point, the smallest value 'len' can be is 5 if prebytes is 3.  */
   /*------------------------------------------------------------------------*/
   len -= prebytes;
   len2 = len >> 2;

   /*------------------------------------------------------------------------*/
   /* This loop has been manually unrolled to copy two words per iteration   */
   /* in order to avoid a hardware stall on dependent LD-ST instructions     */
   /* that are scheduled back-to-back.                                       */
   /*------------------------------------------------------------------------*/
   for (i = 0; i < len2-1; i += 2)
   {
       int j, k;
       j = *(int *)s0; s0 += 4;
       k = *(int *)s0; s0 += 4;
       *(int *)d0 = j; d0 += 4;
       *(int *)d0 = k; d0 += 4;
   }

   /*-----------------------------------------------------------------------*/
   /* If copying an odd number of words, perform one last copy              */
   /*-----------------------------------------------------------------------*/
   if (i == len2-1) { *(int *)d0 = *(int *)s0; d0 += 4; s0 += 4; }

   /*------------------------------------------------------------------------*/
   /* Copy remaining bytes.                                                  */
   /*------------------------------------------------------------------------*/
   if (len & 0x2) { *(short *)(d0) = *(short *)(s0); d0 += 2; s0 += 2; }
   if (len & 0x1) *d0 = *s0;

   return dst;
}
