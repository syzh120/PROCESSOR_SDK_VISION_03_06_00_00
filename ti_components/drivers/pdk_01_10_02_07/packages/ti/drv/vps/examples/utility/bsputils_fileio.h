/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_FILEIO_API File IO helper APIs
 *  @{
 */

/**
 *  \file bsputils_fileio.h
 *
 *  \brief Header file to use helper functions for accessing the sd card.
 *
 */

#ifndef BSPUTILS_FILE_IO_H_
#define BSPUTILS_FILE_IO_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to initialize sd card
 *
 *  \param hEdma            [IN]    handle for edma3lld.
 *
 *  \return BSP_SOK on success else appropiate error code on failure.
 */
Int32 BspUtils_initFileio(void *hEdma);

/**
 *  \brief Function to deinitialize sd card
 *
 *  \return BSP_SOK on success else appropiate error code on failure.
 */
Int32 BspUtils_deinitFileio(void);

/**
 *  \brief Function to load buffers from file in sd card
 *
 *  \param fileName         [IN]    File name string.
 *  \param dirName          [IN]    Directory name string.
 *  \param bufAddr          [IN]    Address of buffer to load the file content.
 *  \param bufSize          [IN]    Size of buffer to load the file content.
 *  \param bytesRead        [OUT]   Returns number of bytes read from file.
 */
Int32 BspUtils_appLoadFileFromSd(const Char *fileName,
                                 const Char *dirName,
                                 void       *bufAddr,
                                 UInt32      bufSize,
                                 UInt32     *bytesRead);

/**
 *  \brief Function to save buffers to file in SD card
 *
 *  \param fileName         [IN]    File name string.
 *  \param dirName          [IN]    Directory name string.
 *  \param bufAddr          [IN]    Address of buffer to save in file
 *  \param bufSize          [IN]    Size of buffer to save the content in file.
 *  \param bytesWritten     [OUT]   Returns number of bytes written to file.
 */
Int32 BspUtils_appSaveFileToSd(const Char *fileName,
                               const Char *dirName,
                               const void *bufAddr,
                               UInt32      bufSize,
                               UInt32     *bytesWritten);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

