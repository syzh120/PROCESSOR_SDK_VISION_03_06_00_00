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
 *  @file       ti/sdo/fc/dskt2/dskt2_permute.c
 *
 *  @brief      Utility functions + test for iterating through unique
 *              permutations of a list of elements.
 */
#ifdef _RTSMODE_

#include <stdio.h>

#else

#include <xdc/std.h>
#include <xdc/runtime/Memory.h>

#include "_dskt2.h"

#endif

#include "dskt2_permute.h"

static void _rotateSubgroup(struct _DSKT2_PERMUTE_Enumeration *h, int pos0,
                            int pos1, int rightOrLeft);
static void _rotateListElements(struct _DSKT2_PERMUTE_Enumeration *h);



_DSKT2_PERMUTE_EnumerationHandle _DSKT2_Permute_createHandle()
{
    _DSKT2_PERMUTE_EnumerationHandle h;

#ifdef _RTSMODE_
    h = (_DSKT2_PERMUTE_Enumeration *)
        malloc(sizeof(_DSKT2_PERMUTE_Enumeration));
#else
    h = (_DSKT2_PERMUTE_Enumeration *)
        Memory_alloc(_DSKT2_heap, sizeof(_DSKT2_PERMUTE_Enumeration), 0, NULL);
#endif
    return h;
}

void _DSKT2_Permute_deleteHandle(_DSKT2_PERMUTE_EnumerationHandle h)
{
    if (NULL != h) {
#ifdef _RTSMODE_
        free(h);
#else
        Memory_free(_DSKT2_heap, h, sizeof(_DSKT2_PERMUTE_Enumeration));
#endif
    }
}

void _DSKT2_Permute_setInitialState(_DSKT2_PERMUTE_EnumerationHandle h,
        void **initList, int numElements)
{
    int i = 0;

    if (NULL == h) {
        return;
    }

    h->initialList = initList;
    h->done = 0;
    h->firstTime = 1;

    /* cap the size of list to module maximum */
    h->listSize = numElements < _DSKT2_PERMUTE_MAXSIZE ?
        numElements : _DSKT2_PERMUTE_MAXSIZE;

    for (i = 0; i < numElements; i++) {
        h->state[i] = i + 1;
        h->nextIteration[i] = &initList[i];
    }
}

void **_DSKT2_Permute_iterateNext(struct _DSKT2_PERMUTE_Enumeration *h)
{
    if (NULL == h) {
        return (NULL);
    }

    if (h->firstTime) {
        h->firstTime = 0;
        return (h->nextIteration);
    }

    if ((h->listSize <= 1) || (h->done)) {
        return (NULL);
    }

    _rotateListElements(h);

    if (h->done) {
        return (NULL);
    } else {
        return (h->nextIteration);
    }
}

static void _rotateListElements(struct _DSKT2_PERMUTE_Enumeration *h)
{
    int i = 0;
    int numZeroes = 0;
    int direction;

    /*
     * Calculate number of elements in current iteration to rotate.
     * This is obtained by the number of inner-most indices counted down to 0.
     */
    for (i = 0; i < h->listSize; i++) {
        if (0 == h->state[i]) {
            numZeroes++;
        } else {
            break;
        }
    }

    /*
     * Last enumeration is flagged when numZeroes reach list-size -1
     */
    if (numZeroes == (h->listSize - 1) ) {
        h->done = 1;
        return;
    }

    for (i = 0, direction = _DSKT2_PERMUTE_RIGHT; i <= numZeroes + 1; i++) {

        _rotateSubgroup(h, 0, i, direction);
        direction *= (-1); /* rotate each subgroup in opposite direction */
        }

    /* reflect subgroup rotation by decrementing count in h->state */
    h->state[numZeroes]--;

    /* after each rotation of the subgroup, reset zero counts in h->state */
    for (i = 0; i < numZeroes; i++) {
         h->state[i] = i + 1;
    }
}

static void _rotateSubgroup(struct _DSKT2_PERMUTE_Enumeration *h, int pos0,
    int pos1, int rightOrLeft)
{
    int direction;
    int startIndex;
    void *save;
    int i;
    int count;

    if (rightOrLeft == _DSKT2_PERMUTE_RIGHT) {
        direction = 1;
        startIndex = pos0;
    } else {
        direction = -1;
        startIndex = pos1;
    }

    save = (void *)h->nextIteration[startIndex];

    for (i = startIndex, count = pos1 - pos0; count > 0;
        i = i + direction, count--) {

        h->nextIteration[i] = (void *)h->nextIteration[i + direction];
    }

    h->nextIteration[i] = save;
}

#ifdef _RTSMODE_
static int _testMain(int argc, char *argv[])
{
    int numElements;
    int enumerationCount = 0;
    int **list = NULL;
    char **permList;
    _DSKT2_PERMUTE_EnumerationHandle pHandle = NULL;

    if (argc > 1) {
        permList = argv + 1;
    }
    else {
        printf("\nUsage: test <list> \n\n");
        return (0);
    }

    numElements = argc - 1;
    pHandle = _DSKT2_Permute_createHandle();

    _DSKT2_Permute_setInitialState(pHandle, (void **)permList, numElements);

    while (NULL != (list = (int **)_DSKT2_Permute_iterateNext(pHandle))) {

        enumerationCount++;
        {
            int i;
            printf ("%3d. ", enumerationCount);
            for (i=0; i<numElements; i++) {
                printf ("%s%s%s", (i == 0) ? "list = {" : "",
                        list[i][0], (i==(numElements - 1))? "}\n": ",");
            }
        }
    }
    _DSKT2_Permute_deleteHandle(pHandle);

    return (0);
}
#endif
