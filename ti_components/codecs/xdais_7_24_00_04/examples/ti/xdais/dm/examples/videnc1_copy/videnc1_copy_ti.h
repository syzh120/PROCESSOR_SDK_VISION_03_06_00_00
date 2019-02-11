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
 *  ======== videnc1_copy_ti.h ========
 */
#ifndef ti_xdais_dm_examples_videnc1_copy_VIDENC1_COPY_TI_
#define ti_xdais_dm_examples_videnc1_copy_VIDENC1_COPY_TI_

#include <ti/xdais/idma3.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== VIDENC1COPY_TI_IVIDENCCOPY ========
 *  Our implementation of the IVIDENC1 interface
 */
extern IVIDENC1_Fxns VIDENC1COPY_TI_IVIDENC1COPY;
extern IALG_Fxns VIDENC1COPY_TI_IALG;

#ifdef USE_ECPY
#include <ti/xdais/ires.h>
/* Not all targets support IRES EDMA3, but for those that do, declare this extern */
extern IRES_Fxns VIDENC1COPY_TI_IRES;
#endif

/*
 *  ======== IVIDENC1CPY_InArgs ========
 *  This codec extends IVIDENC1_InArgs with a codec-specific "maxBytes" field.
 */
typedef struct IVIDENC1CPY_InArgs {
    IVIDENC1_InArgs videnc1InArgs;
    XDAS_Int32      maxBytes;    /* Maximum number of bytes to copy. */
} IVIDENC1CPY_InArgs;

#ifdef __cplusplus
}
#endif

#endif
