/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
 */

#ifdef ti_sdo_fc_edmamgr_EdmaMgr_

#ifndef ti_sdo_fc_edmamgr_EdmaMgr_XFER_
#define ti_sdo_fc_edmamgr_EdmaMgr_XFER_

/*---------------------------------------------------------------*/
/* This function convert single local address to global addresse */
/*---------------------------------------------------------------*/
extern cregister volatile unsigned int DNUM;
static inline void *restrict EDMA_MGR_ADDR_LOC_TO_GLOB(void *restrict loc_addr)
{
   unsigned int tmp = (unsigned int)loc_addr;

   if((tmp & 0xFF000000) == 0)
   {
      return (void *)((1 << 28) | (DNUM << 24) | tmp);
   } else return loc_addr;
}


/*-----------------------------------------------------------*/
/*  This function waits for all transfers on a specific      */
/*  ECPY channel to complete. It is a blocking call          */
/*  in the sense that CPU will wait until all transfers      */
/*  are completed.                                           */
/*-----------------------------------------------------------*/

#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
void EdmaMgr_wait(EdmaMgr_Handle h)
{
  EdmaMgr_Channel  *edmamgrChan = (EdmaMgr_Channel *)h;

  if (edmamgrChan->xferPending) {
    ECPY_directWait(edmamgrChan->ecpyHandle);

    if ( edmamgrChan->chainedChannel && edmamgrChan->chainedChannel->xferPending ) {
      ECPY_directWait(edmamgrChan->chainedChannel->ecpyHandle);
      edmamgrChan->chainedChannel->xferPending = FALSE;
    }

    edmamgrChan->xferPending = FALSE;
  }
  return;
}

/*------------------------------------------------------------*/
/* The following function performs a single 1D->1D transfer   */
/* transferring "num_bytes" bytes from "src" which is the     */
/* source address to "dst" which is the destination. This     */
/* function uses the channel number "chan_num". It is assumed */
/* by this function that there are no pending transfers on    */
/* "chan_num".                                                */
/*------------------------------------------------------------*/

#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy1D1D
(
    EdmaMgr_Handle            h,
    void     *restrict        src,
    void     *restrict        dst,
    int32_t                   num_bytes
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  ECPY_Params p;
#if 1
  uint32_t r, n = 0, a_cnt = num_bytes, i = 0;
  char *c_src = (char *)src, *c_dst = (char *)dst;

  /*
   * This abstracts an effective 1D1D transfer which can transfer more than the 16-bit limit set by the HW.
   *
   * This is done by splitting the transfer into 2 transfers:
   *   - One 2D1D transfer.
   *   - One 1D1D transfer for the remainder.
   */

  while ( a_cnt > 0xFFFF )
  {
    a_cnt >>= 1;
    n++;
  }

  r = num_bytes - (a_cnt << n);

  if ( r > 0 )
  {
    src = (void *)c_src;
    dst = (void *)c_dst;

    memset(&p, 0, sizeof(ECPY_Params));
    p.transferType = ECPY_1D1D;
    p.dstAddr     = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);
    p.srcAddr     = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
    p.elementSize = r;
    p.numElements = 1;
    p.numFrames   = 1;

    i++;
    ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, i);

    ECPY_directSetFinal(edmamgrChan->ecpyHandle, i);
    ECPY_directStartEdma(edmamgrChan->ecpyHandle);

    c_src += r;
    c_dst += r;

    src = (void *)c_src;
    dst = (void *)c_dst;

    ECPY_directWait(edmamgrChan->ecpyHandle);
    i = 0;
  }

  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_2D1D;
  p.dstAddr     = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);
  p.srcAddr     = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
  p.elementSize = (1<<n);
  p.numElements = a_cnt;
  p.numFrames   = 1;
  p.srcElementIndex = (1<<n);
  p.dstElementIndex = (1<<n);

  i++;
  ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, i);

  ECPY_directSetFinal(edmamgrChan->ecpyHandle, i);
  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

#else
    /*
     *  Single 1D1D transfer.
     *
     *  NOTE: Max size of transfer is limited by 16-bit integer (65535 bytes)
     */

    memset(&p, 0, sizeof(ECPY_Params));
    p.transferType = ECPY_1D1D;
    p.dstAddr     = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);
    p.srcAddr     = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
    p.elementSize = num_bytes;
    p.numElements = 1;
    p.numFrames   = 1;

    ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, 1);

    ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);
    ECPY_directStartEdma(edmamgrChan->ecpyHandle);

    edmamgrChan->xferPending = TRUE;

#endif
  return(0);
}

/*----------------------------------------------------------*/
/*  The following function performs a 1D->2D transfer       */
/*  where the source is 1D one dimensional and destination  */
/*  is 2D two dimensional. This function uses channel       */
/*  number "chan_num" to transfer "num_lines" lines         */
/*  each of "num_bytes" bytes. In this case after every     */
/*  line of "num_bytes" is transferred, "src" source is     */
/*  incremeneted by "num_bytes" and "dst" destination is    */
/*  incremenetd by "pitch" bytes.                           */
/*----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy1D2D
(
  EdmaMgr_Handle    h,
  void *restrict    src,
  void *restrict    dst,
  int32_t           num_bytes,
  int32_t           num_lines,
  int32_t           pitch
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_1D2D;
  p.numFrames    = 1;
  p.elementSize = num_bytes;
  p.numElements  = num_lines;
  p.srcElementIndex = num_bytes;
  p.dstElementIndex = pitch;
  p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
  p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);

  ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, 1);

  ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);
  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}

/*----------------------------------------------------------*/
/* This function performs a 2D->1D transfer by usinng the   */
/* channel number "chan_num" by performing a transfer from  */
/* source "src" to destination "dst", "num_lines" lines     */
/* each of "num_bytes" bytes. At the end of transferring    */
/* "num_bytes" bytes per line, the source is incremented    */
/* by "pitch" bytes and the destination is incremented by   */
/* "num_bytes" bytes as "src" is 2D and "dst" is 1D.        */
/*----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy2D1D
(
  EdmaMgr_Handle    h,
  void *restrict    src,
  void *restrict    dst,
  int32_t           num_bytes,
  int32_t           num_lines,
  int32_t           pitch
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  ECPY_Params p;

  /* Setting up the parameters for the first transfer (data grp 1) */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_2D1D;
  p.numFrames    = 1;
  p.elementSize = num_bytes;
  p.numElements  = num_lines;
  p.srcElementIndex = pitch;
  p.dstElementIndex = num_bytes;
  p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
  p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);

  ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, 1);

  ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);
  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}

/*----------------------------------------------------------*/
/* This function performs a 2D->2D transfer by using the    */
/* channel number "chan_num" by performing a transfer from  */
/* source "src" to destination "dst", "num_lines" lines     */
/* each of "num_bytes" bytes. At the end of transferring    */
/* "num_bytes" bytes per line, the source is incremented    */
/* by "pitch" bytes and the destination is incremented by   */
/* "pitch" bytes as well as "src" is 2D and "dst" is 2D.    */
/*----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy2D2D
(
  EdmaMgr_Handle    h,
  void *restrict    src,
  void *restrict    dst,
  int32_t           num_bytes,
  int32_t           num_lines,
  int32_t           pitch
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_2D2D;
  p.numFrames    = 1;
  p.elementSize = num_bytes;
  p.numElements  = num_lines;
  p.srcElementIndex = pitch;
  p.dstElementIndex = pitch;
  p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
  p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);

  ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, 1);

  ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);
  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}

/*----------------------------------------------------------*/
/* This function performs a 2D->2D transfer by usinng the   */
/* channel number "chan_num" by performing a transfer from  */
/* source "src" to destination "dst", "num_lines" lines     */
/* each of "num_bytes" bytes. At the end of transferring    */
/* "num_bytes" bytes per line, the source is incremented    */
/* by "dst_pitch" bytes and the destination is incremented  */
/* by "src_pitch" bytes as well as "src" is 2D and "dst"    */
/* is 2D. This function thus allows independent "src" and   */
/* "dst" pitches.                                           */
/*----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy2D2DSep
(
  EdmaMgr_Handle    h,
  void *restrict    src,
  void *restrict    dst,
  int32_t           num_bytes,
  int32_t           num_lines,
  int32_t           src_pitch,
  int32_t           dst_pitch
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_2D2D;
  p.numFrames    = 1;
  p.elementSize = num_bytes;
  p.numElements  = num_lines;
  p.srcElementIndex = src_pitch;
  p.dstElementIndex = dst_pitch;
  p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
  p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);

  ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, 1);

  ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);
  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}

/*-----------------------------------------------------------*/
/*  This function accepts an array of transfer parameters    */
/*  and performs a group of 1D->1D linked transfers.         */
/*                                                           */
/*  edmamgrChan: pointer to ALG ECPY channel data structure. */
/*  chan_num: Channel number on which transfer is issued.    */
/*  src: Array of source addresses.                          */
/*  dst: Array of destination addresses.                     */
/*  num_bytes: Array of the number of bytes to transfer.     */
/*  num_transfers: The number of transfers to perform.       */
/*-----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy1D1DLinked
(
  EdmaMgr_Handle    h,
  void *restrict    src[],
  void *restrict    dst[],
  int32_t           num_bytes[],
  int32_t           num_transfers
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  int32_t         i, j;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_1D1D;
  p.numFrames    = 1;
  p.numElements  = 1;

  for (i=0; i<num_transfers; i++)
  {
    j = i+1;
    p.elementSize = num_bytes[i];
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src[i]);
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst[i]);
    ECPY_configure(edmamgrChan->ecpyHandle, &p, j);
  }
  ECPY_setFinal(edmamgrChan->ecpyHandle, num_transfers);
  ECPY_start(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}
/*-----------------------------------------------------------*/
/*  This function accepts an array of transfer parameters    */
/*  and performs a group of src 1D-> dst 2D linked transfers */
/*                                                           */
/*  edmamgrChan: pointer to ALG ECPY channel data structure. */
/*  chan_num:   Channel number to use for transfer.          */
/*  src     :   Array of source addresses to use.            */
/*  dst     :   Array of destination addresses to use.       */
/*  num_bytes:  Number of bytes to transfer per line.        */
/*  num_lines:  Number of such lines to transfer.            */
/*  pitch:      Destination pitch to use between lines.      */
/*  num_tfrs:   Number of transfers.                         */
/*-----------------------------------------------------------*/


#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy1D2DLinked
(
  EdmaMgr_Handle    h,
  void *restrict    src[],
  void *restrict    dst[],
  int32_t           num_bytes[],
  int32_t           num_lines[],
  int32_t           pitch[],
  int32_t           num_transfers
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  int32_t         i, j;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_1D2D;
  p.numFrames    = 1;

  for (i=0; i<num_transfers; i++)
  {
    j = i+1;
    p.elementSize = num_bytes[i];
    p.numElements  = num_lines[i];
    p.srcElementIndex = num_bytes[i];
    p.dstElementIndex = pitch[i];
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src[i]);
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst[i]);
    ECPY_configure(edmamgrChan->ecpyHandle, &p, j);
  }
  ECPY_setFinal(edmamgrChan->ecpyHandle, num_transfers);
  ECPY_start(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}


/*-----------------------------------------------------------*/
/*  This function accepts an array of transfer parameters    */
/*  and performs a group of src 2D-> dst 1D linked transfers */
/*                                                           */
/*  edmamgrChan: pointer to ALG ECPY channel data structure. */
/*  chan_num:   Channel number to use for transfer.          */
/*  src     :   Array of source addresses to use.            */
/*  dst     :   Array of destination addresses to use.       */
/*  num_bytes:  Number of bytes to transfer per line.        */
/*  num_lines:  Number of such lines to transfer.            */
/*  pitch:      Source pitch to use between lines.           */
/*  num_tfrs:   Number of transfers.                         */
/*-----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy2D1DLinked
(
  EdmaMgr_Handle    h,
  void *restrict    src[],
  void *restrict    dst[],
  int32_t           num_bytes[],
  int32_t           num_lines[],
  int32_t           pitch[],
  int32_t           num_transfers
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  int32_t         i, j;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_2D1D;
  p.numFrames    = 1;

  for (i=0; i<num_transfers; i++)
  {
    j = i+1;
    p.elementSize = num_bytes[i];
    p.numElements  = num_lines[i];
    p.srcElementIndex = pitch[i];
    p.dstElementIndex = num_bytes[i];
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src[i]);
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst[i]);
    ECPY_configure(edmamgrChan->ecpyHandle, &p, j);
  }
  ECPY_setFinal(edmamgrChan->ecpyHandle, num_transfers);
  ECPY_start(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}
/*-----------------------------------------------------------*/
/*  This function accepts an array of transfer parameters    */
/*  and performs a group of src 2D-> dst 2D linked transfers */
/*                                                           */
/*  edmamgrChan: pointer to ALG ECPY channel data structure. */
/*  chan_num:   Channel number to use for transfer.          */
/*  src     :   Array of source addresses to use.            */
/*  dst     :   Array of destination addresses to use.       */
/*  num_bytes:  Number of bytes to transfer per line.        */
/*  num_lines:  Number of such lines to transfer.            */
/*  pitch:      Source, Dest pitch to use between lines.     */
/*  num_tfrs:   Number of transfers.                         */
/*-----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy2D2DLinked
(
  EdmaMgr_Handle    h,
  void *restrict    src[],
  void *restrict    dst[],
  int32_t           num_bytes[],
  int32_t           num_lines[],
  int32_t           pitch[],
  int32_t           num_transfers
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  int32_t         i, j;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_2D2D;
  p.numFrames    = 1;

  for (i=0; i<num_transfers; i++)
  {
    j = i+1;
    p.elementSize = num_bytes[i];
    p.numElements  = num_lines[i];
    p.srcElementIndex = pitch[i];
    p.dstElementIndex = pitch[i];
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src[i]);
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst[i]);
    ECPY_configure(edmamgrChan->ecpyHandle, &p, j);
  }
  ECPY_setFinal(edmamgrChan->ecpyHandle, num_transfers);
  ECPY_start(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}

/*-----------------------------------------------------------*/
/*  This function accepts an array of transfer parameters    */
/*  and performs a group of src 2D-> dst 2D linked transfers */
/*                                                           */
/*  edmamgrChan: pointer to ALG ECPY channel data structure. */
/*  chan_num:   Channel number to use for transfer.          */
/*  src     :   Array of source addresses to use.            */
/*  dst     :   Array of destination addresses to use.       */
/*  num_bytes:  Number of bytes to transfer per line.        */
/*  num_lines:  Number of such lines to transfer.            */
/*  pitchsrc:   Source pitch to use between lines.           */
/*  pitchdst:   Destination pitch to use between lines.      */
/*  num_tfrs:   Number of transfers.                         */
/*-----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy2D2DSepLinked
(
  EdmaMgr_Handle    h,
  void *restrict    src[],
  void *restrict    dst[],
  int32_t           num_bytes[],
  int32_t           num_lines[],
  int32_t           src_pitch[],
  int32_t           dst_pitch[],
  int32_t           num_transfers
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  int32_t         i, j;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));
  p.transferType = ECPY_2D2D;
  p.numFrames    = 1;

  for (i=0; i<num_transfers; i++)
  {
    j = i+1;
    p.elementSize = num_bytes[i];
    p.numElements  = num_lines[i];
    p.srcElementIndex = src_pitch[i];
    p.dstElementIndex = dst_pitch[i];
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src[i]);
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst[i]);
    ECPY_configure(edmamgrChan->ecpyHandle, &p, j);
  }
  ECPY_setFinal(edmamgrChan->ecpyHandle, num_transfers);
  ECPY_start(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}

#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copyFast
(
  EdmaMgr_Handle    h,
  void *restrict    src,
  void *restrict    dst
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;

  ECPY_directConfigure32(edmamgrChan->ecpyHandle, ECPY_PARAMFIELD_SRCADDR,
          (uint32_t)EDMA_MGR_ADDR_LOC_TO_GLOB(src), 1);
  ECPY_directConfigure32(edmamgrChan->ecpyHandle, ECPY_PARAMFIELD_DSTADDR,
          (uint32_t)EDMA_MGR_ADDR_LOC_TO_GLOB(dst), 1);

  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return (0);
}


#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copyLinkedFast
(
  EdmaMgr_Handle    h,
  void *restrict    src[],
  void *restrict    dst[],
  int32_t           num_transfers
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  int32_t i, j;

  for (i=0; i<num_transfers; i++)
  {
    j = i+1;
    ECPY_configure32(edmamgrChan->ecpyHandle, ECPY_PARAMFIELD_SRCADDR,
            (uint32_t)EDMA_MGR_ADDR_LOC_TO_GLOB(src[i]), j);
    ECPY_configure32(edmamgrChan->ecpyHandle, ECPY_PARAMFIELD_DSTADDR,
            (uint32_t)EDMA_MGR_ADDR_LOC_TO_GLOB(dst[i]), j);
  }
  ECPY_start(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return (0);
}


/*----------------------------------------------------------*/
/*  The following function performs a 1D->2D transfer       */
/*  where the source is 1D one dimensional and destination  */
/*  is 2D two dimensional. This function uses channel       */
/*  number "chan_num" to transfer "num_lines" lines         */
/*  each of "num_bytes" bytes. In this case after every     */
/*  line of "num_bytes" is transferred, "src" source is     */
/*  incremeneted by "num_bytes" and "dst" destination is    */
/*  incremenetd by "pitch" bytes.                           */
/*----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy1D2DLarge
(
  EdmaMgr_Handle    h,
  void *restrict    src,
  void *restrict    dst,
  int32_t           num_bytes,
  int32_t           num_lines,
  int32_t           pitch
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  ECPY_Params p;

  /* Setting up the parameters for the transfer */
  memset(&p, 0, sizeof(ECPY_Params));

  if ( (pitch < 32768) && (pitch >= -32768) ) {
    /* If pitch fits in HW reg, fall back on basic 1D2D transfer */
    p.transferType = ECPY_1D2D;
    p.numFrames    = 1;
    p.elementSize = num_bytes;
    p.numElements  = num_lines;
    p.srcElementIndex = num_bytes;
    p.dstElementIndex = pitch;
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);

    ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, 1);

    ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);

  } else {
    int32_t i;
    uint32_t  *addrTable = (uint32_t *)edmamgrChan->addrTable.base;
    IRES_EDMA3CHAN_PaRamStruct *paRam;
    ECPY_Params p_0;
    memset (&p_0, 0, sizeof(ECPY_Params));

    /* Set address lookup table based on "dst" and "pitch" */
    for ( i = 0; i < num_lines; i++) {
        addrTable[i] = (uint32_t)dst + i*pitch;
    }

    /*
     *  PaRAM for channel 1
     *
     *  This PaRAM set is responsible for populating the "dst" field of the
     *  PaRAM set for the second channel.
     */

    /*
     *  1D2D so that destination address (channel 2's PaRAM "dst" field) is
     *  constant.
     */
    p_0.transferType  = ECPY_1D2D;

    /*
     *  elementSize is the size of "dst" address.
     */
    p_0.elementSize = sizeof(uint32_t);

    /*
     *  Transfer 1 address per synchronization event.
     */
    p_0.numElements = 1;

    /*
     *  "num_lines" is the total number of addresses to transfer as well as the
     *  number of synchronization events.
     */
    p_0.numFrames   = num_lines;

    /*
     *  After an address is transferred, point to the next one.
     */
    p_0.srcElementIndex = sizeof(uint32_t);
    p_0.srcFrameIndex = sizeof(uint32_t);

    /*
     *  Do not increment the destination address since the destination for the
     *  addresses is the second channel's PaRAM which remains constant.
     */
    p_0.dstElementIndex = 0;
    p_0.dstFrameIndex = 0;

    /*
     *  src of this channel is the lookup table
     */
    p_0.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(addrTable);

    /*
     *  Obtain the address to the second channel's PaRam 'dst' field, and use
     *  that for the first channels destination.
     */
    paRam = (IRES_EDMA3CHAN_PaRamStruct *)edmamgrChan->chainedChannel->edmaHandle->assignedPaRamAddresses[0];
    p_0.dstAddr = (void *)&paRam->dst; /*PaRAM for chan2 dstAddr field*/



    /*
     *  PaRAM for channel 2
     *
     *  This PaRAM set is responsible for transfer the actual data of interest.
     *  The 'dst' field of this set will be modified by the first channel.
     */

    /*
     *  2D2D transfer
     */
    p.transferType = ECPY_2D2D;

    /*
     *  Number of bytes to transfer to each dst address in lookup table.
     */
    p.elementSize  = num_bytes;
    p.numElements  = 1;

    /*
     *  Set C CNT to num_lines since using AB-sychronization.
     */
    p.numFrames    = num_lines;

    /*
     * SRC is linearized as a 1-D vector, so increment src by num_bytes.
     */
    p.srcElementIndex = num_bytes;
    p.srcFrameIndex   = num_bytes;

    /*
     * DST will be updated by channel 1, so automatic incrementing is not needed.
     */
    p.dstElementIndex = 0;
    p.dstFrameIndex   = 0;

    /*
     *  Set SRC to 1-D vector.
     */
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);

    /*
     *  Don't Care as DST will be updated by channel 1.
     */
    p.dstAddr = (void *)NULL;  /* This will be updated by p_0 */

    /* Write Channel 1 PaRAM to HW. */
    ECPY_directConfigure(edmamgrChan->ecpyHandle, &p_0, 1);
    ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);

    /* Write Channel 2 PaRAM to HW. */
    ECPY_directConfigure(edmamgrChan->chainedChannel->ecpyHandle, &p, 1);
    ECPY_directSetFinal(edmamgrChan->chainedChannel->ecpyHandle, 1);

    /* Override OPT for chaining */
    paRam = (IRES_EDMA3CHAN_PaRamStruct *)edmamgrChan->edmaHandle->assignedPaRamAddresses[0];
    paRam->opt = edmamgrChan->optChained;

    paRam = (IRES_EDMA3CHAN_PaRamStruct *)edmamgrChan->chainedChannel->edmaHandle->assignedPaRamAddresses[0];
    paRam->opt = edmamgrChan->chainedChannel->optChained;

    edmamgrChan->chainedChannel->xferPending = TRUE;
  }

  /* Initiate transfer */
  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}

/*----------------------------------------------------------*/
/* This function performs a 2D->1D transfer by usinng the   */
/* channel number "chan_num" by performing a transfer from  */
/* source "src" to destination "dst", "num_lines" lines     */
/* each of "num_bytes" bytes. At the end of transferring    */
/* "num_bytes" bytes per line, the source is incremented    */
/* by "pitch" bytes and the destination is incremented by   */
/* "num_bytes" bytes as "src" is 2D and "dst" is 1D.        */
/*----------------------------------------------------------*/
#if defined (EDMAMGR_INLINE_ALL)
static __inline
#endif
int32_t EdmaMgr_copy2D1DLarge
(
  EdmaMgr_Handle    h,
  void *restrict    src,
  void *restrict    dst,
  int32_t           num_bytes,
  int32_t           num_lines,
  int32_t           pitch
)
{
  EdmaMgr_Channel *edmamgrChan = (EdmaMgr_Channel *)h;
  ECPY_Params p;

  /* Setting up the parameters for the first transfer (data grp 1) */
  memset(&p, 0, sizeof(ECPY_Params));

  if ( (pitch < 32768) && (pitch >= -32768) ) {
    /* If pitch fits in HW reg, fall back on basic 1D2D transfer */
    p.transferType = ECPY_2D1D;
    p.numFrames    = 1;
    p.elementSize = num_bytes;
    p.numElements  = num_lines;
    p.srcElementIndex = pitch;
    p.dstElementIndex = num_bytes;
    p.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(src);
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);

    ECPY_directConfigure(edmamgrChan->ecpyHandle, &p, 1);

    ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);
  } else {
    int32_t i;
    uint32_t  *addrTable = (uint32_t *)edmamgrChan->addrTable.base;
    IRES_EDMA3CHAN_PaRamStruct *paRam;
    ECPY_Params p_0;
    memset (&p_0, 0, sizeof(ECPY_Params));

    /* Set address lookup table based on "src" and "pitch" */
    for ( i = 0; i < num_lines; i++) {
        addrTable[i] = (uint32_t)src + i*pitch;
    }

    /*
     *  PaRAM for channel 1
     *
     *  This PaRAM set is responsible for populating the "src" field of the
     *  PaRAM set for the second channel.
     */

    /*
     *  1D2D so that destination address (channel 2's PaRAM "src" field) is
     *  constant.
     */
    p_0.transferType  = ECPY_1D2D;

    /*
     *  elementSize is the size of "src" address.
     */
    p_0.elementSize = sizeof(uint32_t);

    /*
     *  Transfer 1 address per synchronization event.
     */
    p_0.numElements = 1;

    /*
     *  "num_lines" is the total number of addresses to transfer as well as the
     *  number of synchronization events.
     */
    p_0.numFrames   = num_lines;

    /*
     *  After an address is transferred, point to the next one.
     */
    p_0.srcElementIndex = sizeof(uint32_t);
    p_0.srcFrameIndex = sizeof(uint32_t);

    /*
     *  Do not increment the destination address since the destination for the
     *  addresses is the second channel's PaRAM which remains constant.
     */
    p_0.dstElementIndex = 0;
    p_0.dstFrameIndex = 0;

    /*
     *  src of this channel is the lookup table
     */
    p_0.srcAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(addrTable);

    /*
     *  Obtain the address to the second channel's PaRam 'src' field, and use
     *  that for the first channels destination.
     */
    paRam = (IRES_EDMA3CHAN_PaRamStruct *)edmamgrChan->chainedChannel->edmaHandle->assignedPaRamAddresses[0];
    p_0.dstAddr = (void *)&paRam->src; /*PaRAM for chan2 srcAddr field*/



    /*
     *  PaRAM for channel 2
     *
     *  This PaRAM set is responsible for transfer the actual data of interest.
     *  The 'src' field of this set will be modified by the first channel.
     */

    /*
     *  2D2D transfer
     */
    p.transferType = ECPY_2D2D;

    /*
     *  Number of bytes to transfer from each src address in lookup table.
     */
    p.elementSize  = num_bytes;
    p.numElements  = 1;

    /*
     *  Set C CNT to num_lines since using AB-sychronization.
     */
    p.numFrames    = num_lines;

    /*
     * SRC will be updated by channel 1, so automatic incrementing is not needed.
     */
    p.srcElementIndex = 0;
    p.srcFrameIndex   = 0;

    /*
     * DST is linearized as a 1-D vector, so increment DST by num_bytes.
     */
    p.dstElementIndex = num_bytes;
    p.dstFrameIndex   = num_bytes;

    /*
     *  Don't Care as SRC will be updated by channel 1.
     */
    p.srcAddr = (void *)NULL;  /* This will be updated by p_0 */

    /*
     *  Set DST to 1-D vector.
     */
    p.dstAddr = (void *)EDMA_MGR_ADDR_LOC_TO_GLOB(dst);

    /* Write Channel 1 PaRAM to HW. */
    ECPY_directConfigure(edmamgrChan->ecpyHandle, &p_0, 1);
    ECPY_directSetFinal(edmamgrChan->ecpyHandle, 1);

    /* Write Channel 2 PaRAM to HW. */
    ECPY_directConfigure(edmamgrChan->chainedChannel->ecpyHandle, &p, 1);
    ECPY_directSetFinal(edmamgrChan->chainedChannel->ecpyHandle, 1);

    /* Override OPT for chaining */
    paRam = (IRES_EDMA3CHAN_PaRamStruct *)edmamgrChan->edmaHandle->assignedPaRamAddresses[0];
    paRam->opt = edmamgrChan->optChained;

    paRam = (IRES_EDMA3CHAN_PaRamStruct *)edmamgrChan->chainedChannel->edmaHandle->assignedPaRamAddresses[0];
    paRam->opt = edmamgrChan->chainedChannel->optChained;

    edmamgrChan->chainedChannel->xferPending = TRUE;
  }

  /* Initiate transfer */
  ECPY_directStartEdma(edmamgrChan->ecpyHandle);

  edmamgrChan->xferPending = TRUE;

  return(0);
}


#endif /* ti_sdo_fc_edmamgr_EdmaMgr_XFER_ */

#else
#error "ti/sdo/fc/edmamgr/edmamgr.h must be included first"
#endif
