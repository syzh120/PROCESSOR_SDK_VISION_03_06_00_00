/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/





#if (!HOST_EMULATION)
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cache.h>
#include <stdbool.h>
#pragma RESET_MISRA ("required")

static Void all(volatile unsigned int *cacheReg)
{
  /* disable interrupts */
  /* wait for any previous cache operation to complete */
  while (*L2WWC != 0)
  {
  }
  /* perform global write back of cache */
  *cacheReg = 1;
  /* wait until cache operation completes */
  while (*cacheReg)
  {
    ;
  }
}


/* Writeback Invalidate Cache */
void Cache_WbInvAll()
{
  /* Write back invalidate cache */
  all(L1DWBINV);
  all(L2WBINV);
}


/* Invalidate Cache */
void Cache_InvAll()
{
  /* Write back invalidate cache */
  all(L1DINV);
  all(L2INV);
}

/* Writeback Cache */
void Cache_WbAll()
{
  /* Write back invalidate cache */
  all(L1DWb);
  all(L2Wb);
}

/*
 *  ======== emifRange ========
 *  If addr within range of 'base' and 'base + length - 1' then return TRUE,
 *  otherwise return FALSE.
 */
static inline bool emifRange(unsigned int addr, unsigned int base, unsigned int length)
{
  if (base != 0) {
      return (addr >= base) && (addr <= (base + length - 1));
  }
  else {
      return false;
  }
}

/*
 *  ======== getEmifCtrlAddr ========
 *  Return the EMIF configuratin control register for the address.
 */
static inline volatile unsigned int *getEmifCtrlAddr(unsigned int addr)
{
  if (emifRange(addr, Cache_EMIFA_BASE, Cache_EMIFA_LENGTH)) {
      return (unsigned int *)Cache_EMIFA_CFG;
  }
  else if (emifRange(addr, Cache_EMIFB_BASE, Cache_EMIFB_LENGTH)) {
      return (unsigned int *)Cache_EMIFB_CFG;
  }
  else if (emifRange(addr, Cache_EMIFC_BASE, Cache_EMIFC_LENGTH)) {
      return (unsigned int *)Cache_EMIFC_CFG;
  }
  else {
      return NULL;
  }
}


/*
 *  ======== block ========
 *  This is a static function used by the block cache APIs.
 */
static Void block(uint8_t* blockPtr, unsigned int byteCnt, bool wait, volatile unsigned int *barReg)
{
  volatile unsigned int *bar;
  volatile unsigned int *wc;
  volatile unsigned int *emifAddr;
  Int wordCnt;
  unsigned int alignAddr;

  /*
   *  Get the base address and word count register.
   *  wc is one word after bar on c64x+ cache.
   */
  bar = barReg;
  wc = bar + 1;

  /* word align the base address */
  alignAddr = ((unsigned int)blockPtr & ~3);

  /* convert from byte to word since cache operation takes words */
  wordCnt = (byteCnt + 3 + ((unsigned int)blockPtr - alignAddr)) >> 2;

  /* loop until word count is zero or less */
  while (wordCnt > 0) {

      /* critical section -- disable interrupts */
     // mask = Hwi_disable();

      /* get the emif config for the address */
      emifAddr = getEmifCtrlAddr(alignAddr);

      /* set the word address and number of words to invalidate */
      *bar = alignAddr;
      *wc = (wordCnt > MAXWC) ? MAXWC : wordCnt;

      /* end of critical section -- restore interrupts */
      //Hwi_restore(mask);

      /*
       * reduce word count by _BCACHE_MAXWC and
       * increase base address by BCACHE_MAXWC
       */
      wordCnt -= MAXWC;
      alignAddr += (MAXWC * sizeof(Int));
  }

  /* wait for cache operation to complete */
  if (wait) {

  /* wait for L2 word count to be zero */
  while (*wc != 0) {
      ;
  }

  /*
   *  make a dummy write and read to emif config register to
   *  insure that data made it out to external memory, otherwise
   *  its possible that the data is out of the Master's view but
   *  has not reached its final destination.
   */
 // mask = Hwi_disable();
  if (emifAddr != NULL) {
      *(emifAddr) = 0;
      *(emifAddr);
      emifAddr = NULL;
  }
 // Hwi_restore(mask);
  }
}


/*
 *  ======== Cache_inv ========
 *  Invalidate the range of memory within the specified starting address and
 *  byte count.  The range of addresses operated on gets quantized to whole
 *  cache lines in each cache.  All cache lines in range are invalidated in L1P
 *  cache.  All cache lines in range are invalidated in L1D cache.
 *  All cache lines in range are invaliated in L2 cache.
 */
Void Cache_inv(uint8_t* blockPtr, unsigned int byteCnt, bool wait)
{
  block(blockPtr, byteCnt, wait, L2IBAR);
}

/*
 *  ======== Cache_wb ========
 *  Writes back the range of memory within the specified starting address
 *  and byte count.  The range of addresses operated on gets quantized to
 *  whole cache lines in each cache.  There is no effect on L1P cache.
 *  All cache lines within the range are left valid in L1D cache and the data
 *  within the range in L1D cache will be written back to L2 or external.
 *  All cache lines within the range are left valid in L2 cache and the data
 *  within the range in L2 cache will be written back to external.
 */
Void Cache_wb(uint8_t* blockPtr, unsigned int byteCnt, bool wait)
{
  block(blockPtr, byteCnt, wait, L2WBAR);
}

/*
 *  ======== Cache_wbInv ========
 *  Writes back and invalidates the range of memory within the specified
 *  starting address and byte count.  The range of addresses operated on gets
 *  quantized to whole cache lines in each cache.  All cache lines within range
 *  are invalidated in L1P cache.  All cache lines within the range are
 *  written back to L2 or external and then invalidated in L1D cache
 *  All cache lines within the range are written back to external and then
 *  invalidated in L2 cache.
 */
Void Cache_wbInv(uint8_t* blockPtr, unsigned int byteCnt, bool wait)
{
  block(blockPtr, byteCnt, wait, L2WIBAR);
}

#endif

