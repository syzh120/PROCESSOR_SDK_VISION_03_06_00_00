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
 * ======== cgiparsem.h ========
 *
 * Multipart CGI parsing functions.
 *
 */

#ifndef _cgiparsem_h
#define _cgiparsem_h

typedef struct {
    char *Name;         /* NULL terminated "name" */
    char *Filename;     /* NULL terminated "filename" or NULL if not a file */
    char *Type;         /* NULL terminated "Content-Type" or NULL if no type */
    char *Data;         /* Pointer to item data (NULL terminated on strings) */
    int  DataSize;      /* Length of data (also valid on strings) */
} CGIPARSEREC;

/* cgiParseMultiVars() */
/* This function is used to parse CGI data sent in the "multipart/form-data" */
/* format. The caller must pass in the entire CGI payload as a single buffer. */
/* The buffer will altered to add NULL termination to all names, types, and */
/* data fields. */
/* Returns the number of validated records, or -1 on parsing error. */
int cgiParseMultiVars( char *buffer, int buflen, CGIPARSEREC *recs, int maxrecs );


#endif /* _cgiparsem_h */
