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
 * */
/*
 * ======== tftpif.h ========
 *
 */

#ifndef _TFTPIF_H_
#define _TFTPIF_H_

/* int NtTftpRecv() */
/* Retrieve a file using TFTP */
/* Return Conditions: */
/* In the following cases, FileSize is set to the actual file size: */
/*      1 - If file was sucessfully transferred */
/*      0 - If the file was transferred but too large for the buffer */
/* In the following cases, FileSize is set to the actual number of */
/* bytes copied. */
/*     <0 - Error */
/*        TFTPERROR_ERRORCODE: TFTP server error code. The error code */
/*          is written to pErrorCode, and an error message is */
/*          written to FileBuffer. The length of the error message */
/*          is written to FileSize. */
_extern int NtTftpRecv( UINT32 TftpIp, char *szFileName, char *FileBuffer,
                        UINT32 *FileSize, UINT16 *pErrorCode );

#ifdef _INCLUDE_IPv6_CODE
_extern int Nt6TftpRecv (IP6N TftpIP, UINT32 scope_id, char *szFileName, char *FileBuffer,
                         UINT32 *FileSize, UINT16 *pErrorCode);
#endif

/*  Error Codes */
#define TFTPERROR_ERRORREPLY            -1
#define TFTPERROR_BADPARAM              -2
#define TFTPERROR_RESOURCES             -3
#define TFTPERROR_SOCKET                -4
#define TFTPERROR_FAILED                -5

#endif


