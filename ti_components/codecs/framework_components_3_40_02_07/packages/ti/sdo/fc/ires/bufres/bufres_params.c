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
/*
 *  ======== bufres_params.c ========
 *  This static initialization defines the default parameters used to
 *  the BUFRES resource.
 */

#include <xdc/std.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV
#include "bufres.h"

#define BUFRES_PARAMS_ALLOCFXN NULL
#define BUFRES_PARAMS_FREEFXN  NULL
#define BUFRES_BASE            NULL
#define BUFRES_LENGTH          0

/*
 *  ======== BUFRES_PARAMS ========
 *  Default configuration for bufres resource
 */
BUFRES_Params BUFRES_PARAMS = {
    /* IRESMAN_Params iresConfig; */
    {
        /* size: The size of this structure */
        sizeof(BUFRES_Params),

        /* allocFxn: Function to allocate memory required by the resource */
        BUFRES_PARAMS_ALLOCFXN,

        /* freeFxn: Function to free memory acquired by allocFxn */
        BUFRES_PARAMS_FREEFXN
    },

    /* Void *base; The base address of the buffer resource */
    BUFRES_BASE,

    /* Int length; The length of the buffer resource (MAUs) */
    BUFRES_LENGTH
};
