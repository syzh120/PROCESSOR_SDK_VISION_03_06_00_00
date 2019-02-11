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
 * ======== _gt_dais.h ========
 */

#ifndef _GT_DAIS_H
#define _GT_DAIS_H

#define SCRATCH "IALG_SCRATCH"
#define PERSIST "IALG_PERSIST"
#define WRITEONCE "IALG_WRITEONCE"
#define UNDEF     "UNDEFINED"

#define EPROG "IALG_EPROG"
#define IPROG "IALG_IPROG"
#define ESDATA "IALG_ESDATA"
#define EXTERNAL "IALG_EXTERNAL"
#define DARAM0 "IALG_DARAM0"
#define DARAM1 "IALG_DARAM1"
#define SARAM "IALG_SARAM"
#define SARAM1 "IALG_SARAM1"
#define DARAM2 "IALG_DARAM2"
#define SARAM2 "IALG_SARAM2"

char * gt_MemAttrs(IALG_MemAttrs index);

char * gt_MemSpace(IALG_MemSpace index);

#endif /* _GT_DAIS_H */
