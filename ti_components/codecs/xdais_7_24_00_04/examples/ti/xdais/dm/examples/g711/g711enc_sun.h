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
 *  ======== g711enc_sun.h ========
 *  Interface for the G711ENC_SUN module; TI's implementation
 *  of the ISPHENC1 interface
 */
#ifndef ti_xdais_dm_examples_g711_G711ENC_SUN_
#define ti_xdais_dm_examples_g711_G711ENC_SUN_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== G711ENC_SUN_IG711ENC ========
 *  TI's implementation of the ISPHENC1 interface
 */
extern ISPHENC1_Fxns G711ENC_SUN_IG711ENC;
extern IALG_Fxns G711ENC_SUN_IALG;

/*
 * This error code is returned from algAlloc() when an application passes
 * a table via the params structure.  This algo does not support custom tables.
 */
#define G711ENC_SUN_EUNSUPPORTEDTABLESPTRPARAM IALG_CUSTOMFAILBASE

#ifdef __cplusplus
}
#endif

#endif
