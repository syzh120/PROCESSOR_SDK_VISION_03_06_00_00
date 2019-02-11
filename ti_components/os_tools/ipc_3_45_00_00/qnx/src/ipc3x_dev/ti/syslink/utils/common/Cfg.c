/*
 *  @file   Cfg.c
 *
 *  @brief      Configuration Helper Utilities
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/String.h>

/* -------------------------- Generic includes ------------------------------ */
#include <string.h>

/* this module's header file */
#include "../Cfg.h"


/* =============================================================================
 * Struct & Enums
 * =============================================================================
 */


/* =============================================================================
 * Globals
 * =============================================================================
 */


/* =============================================================================
 * APIs
 * =============================================================================
 */

/* Find given property string in given params string. If found, copy
 * property value into output buffer and return true. Otherwise, return
 * false.
 */
Bool Cfg_prop(String prop, String params, Char *buf)
{
    Int     len;
    String  delim;

    if ((prop == NULL) || (params == NULL)) {
        return(FALSE);
    }

    len = strlen(prop);

    /* loop until params string has been scanned */
    while (*params != '\0') {

        /* search for prop starting at current pointer */
        if (strncmp(prop, params, len) == 0) {

            /* found prop, advance to value */
            params += len;
            if ((delim = strchr(params, ';')) == NULL) {
                return(FALSE);
            }

            /* copy value into output buffer */
            while (params != delim) {
                *buf++ = *params++;
            }

            /* add string terminator */
            *buf = '\0';

            return(TRUE);
        }

        /* advance to next prop in params */
        else {
            if ((params = strchr(params, ';')) == NULL) {
                return(FALSE);
            }
            params++;
        }
    }

    return(FALSE);
}


/* Search for prop in params and parse value. If found, assign value
 * to var.
 */
Int Cfg_propBool(String prop, String params, Bool *var)
{
    Char    buf[8];
    Int     status = 0;

    if (Cfg_prop(prop, params, buf)) {
        if (strncmp("TRUE", buf, 4) == 0) {
            *var = TRUE;
        }
        else if (strncmp("FALSE", buf, 5) == 0) {
            *var = FALSE;
        }
        else {
            status = -1;  /* bad value */
        }
    }
    else {
        return(1);  /* not found, no errors */
    }

    return(status);
}


/* =============================================================================
 * Internal functions
 * =============================================================================
 */
