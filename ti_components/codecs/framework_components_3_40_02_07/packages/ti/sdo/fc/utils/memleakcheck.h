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

#ifndef ti_sdo_fc_utils_memleakchecker_h
#define ti_sdo_fc_utils_memleakchecker_h


#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#ifdef xdc_target__isaCompatible_64P

#include <ti/bios/include/mem.h>
#include <stdio.h>

#ifdef MEMLEAK

#define MAXMEMSEGMENTS 20

MEM_Stat        memStat[MAXMEMSEGMENTS];
MEM_Stat                stat;

#define  MEMLEAKSET {\
    int i;\
        printf("Testing for Memory leaks\n");\
    for (i = 0; i < MAXMEMSEGMENTS; i++) {\
        if (!MEM_stat(i, &memStat[i])) {\
            memStat[i].size =  memStat[i].used = 0;\
            memStat[i].length = 0;\
        }\
    } }

#define MEMLEAKCHECK {\
   int i;\
   for (i = 0; i < MAXMEMSEGMENTS; i++) { \
        if (!MEM_stat(i, &stat) ) { \
            Assert_isTrue(\ memStat[i].size == 0); \
        } \
        else { \
            if (memStat[i].used != stat.used) { \
                Log_print3(\ Diags_USER7,
                        "+7 MEM seg [%d]: orig used = 0x%x, " \"
                        " "curr used = 0x%x", i, (IArg)(memStat[i].used), (IArg)(\"
                        " stat.used); \"
                        " printf("MEM LEAK of size 0x%x detected"), (IArg)(abs(memStat[i].used \"
                        " - stat.used));\"
                        " return (-1); \"
                        " } \ } \ } \ printf("No memory leaks found !!\n"); }#else
#define MEMLEAKSET
#define MEMLEAKCHECK
#endif /* MEMLEAK */



#ifdef MEMSTAT

/* These macros are only for the purpose of collecting data about memory
allocated etc */


#define MEMSTATINIT(myMemStat,temp,string) { \
    printf(string);\
    if (!MEM_stat(0, &myMemStat)) {\
        myMemStat.size =  myMemStat.used = 0;\
        myMemStat.length = 0;\
    }\
        MEM_stat(0, &temp); }

#define MEMSTATUP(myMemStat,temp,string) { \
    printf(string);\
    MEM_stat(0,&myMemStat);\
    printf("myMemStat.used=0x%x, myMemStat.length=0x%x\n", \
            myMemStat.used, myMemStat.length); \
    printf("delta = 0x%x\n", myMemStat.used - temp.used); \
    temp.used = myMemStat.used; }

#define MEMSTATDOWN(myMemStat,temp,string) { \
    printf(string);\
    MEM_stat(0,&myMemStat);\
    printf("myMemStat.used=0x%x, myMemStat.length=0x%x\n", \
            myMemStat.used, myMemStat.length); \
    printf("delta = 0x%x\n", temp.used - myMemStat.used); \
    temp.used = myMemStat.used; }

MEM_Stat myMemStat;
MEM_Stat temp;
#else

#define MEMSTATDOWN(myMemStat,temp,string)
#define MEMSTATUP(myMemStat,temp,string)
#define MEMSTATINIT(myMemStat,temp,string)

#endif /* MEMSTAT */
#endif /* xdc_target__isaCompatible_64P */

#endif /* ti_sdo_fc_utils_memleakchecker_h */
