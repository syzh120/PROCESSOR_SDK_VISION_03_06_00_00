/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
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
 *  ======== videnc2_copy_ti.h ========
 */
#ifndef ti_xdais_dm_examples_videnc2_copy_VIDENC2_COPY_TI_
#define ti_xdais_dm_examples_videnc2_copy_VIDENC2_COPY_TI_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== VIDENC2COPY_TI_IVIDENCCOPY ========
 *  Our implementation of the IVIDENC1 interface
 */
extern IVIDENC2_Fxns VIDENC2COPY_TI_IVIDENC2COPY;
extern IALG_Fxns VIDENC2COPY_TI_IALG;

/*
 * This error code is returned from algAlloc() when an application passes
 * any metadataType value other than IVIDEO_METADATAPLANE_NONE.
 * This alg does not support returning any metadata.
 */
#define VIDENC2COPY_TI_EUNSUPPORTEDMETADATAPARAM (IALG_CUSTOMFAILBASE)

/*
 * This error code is returned from algAlloc() when an application passes
 * an unsupported input or output data mode (i.e., something other than
 * IVIDEO_ENTIREFRAME in IVIDDEC2_Params::inputDataMode or
 * IVIDDEC2_Params::outputDataMode.
 * This alg does not support subframe processing.
 */
#define VIDENC2COPY_TI_EUNSUPPORTEDDATAMODE (IALG_CUSTOMFAILBASE + 1)

#ifdef __cplusplus
}
#endif

#endif
