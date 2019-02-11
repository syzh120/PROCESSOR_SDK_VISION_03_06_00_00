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
 * ======== httpstr.c ========
 *
 */

char *CONTENT_TYPE_APPLET  = "application/octet-stream ";
char *CONTENT_TYPE_AU      = "audio/au ";
char *CONTENT_TYPE_CSS     = "text/css "; /* Add June 1st, 2010, KQ */
char *CONTENT_TYPE_DOC     = "application/msword ";
char *CONTENT_TYPE_GIF     = "image/gif ";
char *CONTENT_TYPE_HTML    = "text/html ";
char *CONTENT_TYPE_JPG     = "image/jpeg ";
char *CONTENT_TYPE_MPEG    = "video/mpeg ";
char *CONTENT_TYPE_PDF     = "application/pdf ";
char *CONTENT_TYPE_WAV     = "audio/wav ";
char *CONTENT_TYPE_ZIP     = "application/zip ";
char *CONTENT_TYPE         = "Content-type: ";
char *CONTENT_LENGTH       = "Content-length: ";

char *CRLF                 = "\r\n";
char *DEFAULT_NAME         = "index.html";
char *HTTP_VER             = "HTTP/1.0 ";
char *SPACE                = " ";
