/**
 *  @file   OsalPrint.c
 *
 *  @brief      Semaphore interface implementations.
 *
 *              This will have the definitions for kernel side printf
 *              statements and also details of variable printfs
 *              supported in existing implementation.
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2015, Texas Instruments Incorporated
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

/* OSAL and kernel utils */
#include <ti/syslink/utils/OsalPrint.h>
#if (_NTO_VERSION >= 800)
#include <slog2.h>
#else
#include <sys/slog.h>
#endif

/* Linux specifc header files */
#include <stdarg.h>

#if (_NTO_VERSION >= 800)
/* Slog2 buffer handle */
static slog2_buffer_t buffer_handle;
#endif

#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @brief      printf abstraction at the kernel level.
 *
 *  @param      string which needs to be printed.
 *  @param      Variable number of parameters for printf call
 */
Void Osal_printf (char* format, ...)
{
    va_list args;
    char    buffer[512];

    va_start (args, format) ;
    vsprintf (buffer, format, args);
    va_end   (args) ;

#if (_NTO_VERSION >= 800)
    slog2f (buffer_handle, 0, 0, buffer);
#else
    slogf (42, _SLOG_NOTICE, buffer);
#endif
}

/* Initialize logging through slog2 */
int Osal_initlogging(int verbosity)
{
#if (_NTO_VERSION >= 800)
    slog2_buffer_set_config_t buffer_config;
    const char * buffer_set_name = "ipc";
    const char * buffer_name = "ipc_buffer";

   int verbosity_level = verbosity;
    if ( verbosity_level > SLOG2_DEBUG2) {
        verbosity_level = SLOG2_DEBUG2;
    }

    // Initialize the buffer configuration
    buffer_config.buffer_set_name = (char *) buffer_set_name;
    buffer_config.num_buffers = 1;
    buffer_config.verbosity_level = verbosity_level;
    buffer_config.buffer_config[0].buffer_name = (char *) buffer_name;
    buffer_config.buffer_config[0].num_pages = 8;

    // Register the Buffer Set
    if( slog2_register( &buffer_config, &buffer_handle, 0 ) == -1 ) {
        fprintf( stderr, "ipc error registering slogger2 buffer for ipc!\n" );
        return -1;
    }
#endif

    return 0;
}

#if defined (__cplusplus)
}
#endif /* defined (_cplusplus)*/
