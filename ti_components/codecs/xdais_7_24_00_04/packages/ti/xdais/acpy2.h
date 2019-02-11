/*
 * Copyright (c) 2006-2013, Texas Instruments Incorporated
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
/*
 *  @file  acpy2.h
 *
 *  @brief Declaration of the ACPY2 interface. (Deprecated)
 *
 *  @acpyDeprecated
 *
 *

 */

#ifndef ACPY2_
#define ACPY2_

#include "idma2.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== ACPY2_complete ========
 *  Check to see if all dma transfers on logical channel are finished. This
 *  is a non-blocking call.
 */
extern Int ACPY2_complete(IDMA2_Handle handle);

/*
 *  ======= ACPY2_configure ========
 *  Configure logical channel.
 */
extern Void ACPY2_configure(IDMA2_Handle handle, IDMA2_Params *params);

/*
 *  ======== ACPY2_exit ========
 *  Finalization of the ACPY2 module
 */
extern Void ACPY2_exit(Void);

/*
 *  ======== ACPY2_getChanObjSize ========
 *  Called by framework. Returns the channel object size.
 */
extern Uns ACPY2_getChanObjSize(Void);

/*
 *  ======== ACPY2_init ========
 *  Initialize the ACPY2 module.  Called by framework
 */
extern Void ACPY2_init(Void);

/*
 *  ======== ACPY2_initChannel ========
 *  Called by the framework. Initialize the channel state.
 *  Associate the channel with the provided queueId.
 */
extern Void ACPY2_initChannel(IDMA2_Handle handle, Int queueId);

/*
 * ======== ACPY2_setDstFrameIndex ========
 * Set the Destination Frame Index.
 */
extern Void ACPY2_setDstFrameIndex(IDMA2_Handle handle, Int frameIndex);

/*
 * ======== ACPY2_setNumFrames ========
 * Set the Number of Frames
 */
extern Void ACPY2_setNumFrames(IDMA2_Handle handle, Uns numFrames);

/*
 * ======== ACPY2_setSrcFrameIndex ========
 * Set the Source Frame Index.
 */
extern Void ACPY2_setSrcFrameIndex(IDMA2_Handle handle, Int frameIndex);

/*
 *  ======= ACPY2_start ========
 *  Submit the transfer specific information. The DMA manager will handle
 *  the request, and program the DMA device.
 */
extern Void ACPY2_start(IDMA2_Handle handle,IDMA2_AdrPtr src,
    IDMA2_AdrPtr dst, Uns count);

/*
 *  ======= ACPY2_startAligned ========
 *  Submit the transfer specific information. The DMA manager will
 *  handle the request, and program the DMA device.  Requires aligned
 *  addresses and index parameters
 */
extern Void ACPY2_startAligned(IDMA2_Handle handle,IDMA2_AdrPtr src,
    IDMA2_AdrPtr dst, Uns count);

/*
 *  ======= ACPY2_wait ========
 *  Wait for all data transfer on logical channel to complete. This is a
 *  blocking call.
 */
extern Void ACPY2_wait(IDMA2_Handle handle);

#ifdef __cplusplus
}
#endif

#endif /* ACPY2_ */


