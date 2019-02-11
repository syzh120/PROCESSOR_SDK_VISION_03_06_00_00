/*
 *  @file   HWSpinlock.c
 *
 *  @brief      Sample app demonstrating Hardware SpinLocks API usage.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-20012, Texas Instruments Incorporated
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


#include <stdio.h>
#include "GateHWSpinlock.h"
#include "HwSpinLockUsr.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/procmgr.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdbool.h>

#define MAX_LOCKS 128
struct{
    int handleID;
    int* key;
}locks[MAX_LOCKS];

void testHWSpinlock(char* str, int token)
{
    int status, *key;
    int count = 100;
    key = HwSpinlock_enter(token);
    if(key != (int *)(-1)){
        printf( "\n%s=> lock (%d) entered\n", str, token);
        /*execute some instruction instead of sleep()*/
        while(--count);
        status = HwSpinlock_leave(key, token);
        if(!status){
            printf( "\n%s=> return from HwSpinlock_leave(%d)\n", str, token);
        }
        else {
            printf( "\n%s=> HwSpinlock_leave(%d) FAILED\n", str, token);
        }
    }
    else {
        printf( "\n%s=> HwSpinlock_enter(%d) FAILED\n", str, token);
    }
}

int main()
{
    int token0, token1, token2;
    int status;

    token0 = HwSpinlock_create(0, GateHWSpinlock_LocalProtect_NONE);
    if(token0 != -1) {
        printf( "\nPROC=> HwSpinlock_create(0) CREATED\n");
        testHWSpinlock("PROC", token0);
        status = HwSpinlock_delete(token0);
        printf("HwSpinlock_delete(token0): %s\n", status?"FAILED":"PASSED");
    }
    else {
        printf( "\nPROC=> HwSpinlock_create(0) FAIELD\n");
    }
    token1 = HwSpinlock_create(1, GateHWSpinlock_LocalProtect_INTERRUPT);
    if(token1 != -1) {
        printf( "\nPROC=> HwSpinlock_create(1) CREATED\n");
        testHWSpinlock("PROC", token1);
        status = HwSpinlock_delete(token1);
        printf("HwSpinlock_delete(token1): %s\n", status?"FAILED":"PASSED");
    }
    else {
        printf( "\nPROC=> HwSpinlock_create(1) FAIELD\n");
    }
    token2 = HwSpinlock_create(2, GateHWSpinlock_LocalProtect_THREAD);
    if(token2 != -1) {
        printf( "\nPROC=> HwSpinlock_create(1) CREATED\n");
        testHWSpinlock("PROC", token2);
        status = HwSpinlock_delete(token2);
        printf("HwSpinlock_delete(token2): %s\n", status?"FAILED":"PASSED");
    }
    else {
        printf( "\nPROC=> HwSpinlock_create(1) FAIELD\n");
    }
    return 0;
}
