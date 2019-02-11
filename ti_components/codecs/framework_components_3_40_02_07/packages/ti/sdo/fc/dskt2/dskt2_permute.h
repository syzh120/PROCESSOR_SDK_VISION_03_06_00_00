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
/**
 *  @file       ti/sdo/fc/dskt2/dskt2_permute.h
 *
 *  @brief      Utility functions + test for iterating through unique
 *              permutations of a list of elements.
 */
#ifndef _DSKT2_PERMUTE_
#define _DSKT2_PERMUTE_

/*
 * Limit permutation sizes to 7 elements, as >7 is taking > 2seconds to
 * check all permutations for optimal scratch sharing order
 * when running on 2430 C64x+.
 */
#define _DSKT2_PERMUTE_MAXSIZE 7

#define _DSKT2_PERMUTE_RIGHT -1
#define _DSKT2_PERMUTE_LEFT   1

typedef struct _DSKT2_PERMUTE_Enumeration {
    void **initialList;
    void *nextIteration[_DSKT2_PERMUTE_MAXSIZE];
    int  listSize;
    int  state[_DSKT2_PERMUTE_MAXSIZE];
    int  done;
    int  firstTime;
} *_DSKT2_PERMUTE_EnumerationHandle, _DSKT2_PERMUTE_Enumeration;

_DSKT2_PERMUTE_EnumerationHandle _DSKT2_Permute_createHandle();

void _DSKT2_Permute_setInitialState(_DSKT2_PERMUTE_EnumerationHandle h, void **initLst, int numElems);

void **_DSKT2_Permute_iterateNext(struct _DSKT2_PERMUTE_Enumeration *pHandle);

#endif
