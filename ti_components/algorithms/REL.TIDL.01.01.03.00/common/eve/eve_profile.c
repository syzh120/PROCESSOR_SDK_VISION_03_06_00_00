/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      eve_profile.c                                                       */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file helps perform TSC and SCTM based profiling                    */
/*                                                                          */
/*==========================================================================*/
#include "eve_profile.h"

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <vcop.h>

#ifdef __ARP32__

#include "GlobalTypes.h"
#include "baseaddress.h"
#include "eve_sctm.h"
#include "ti_stats_collector.h"
#include "ti_file_io.h"

/* Handle COFF/ELF for linker cmd file symbols */
#if defined(__TI_EABI__)
#define _STACK_SIZE __TI_STACK_SIZE
#endif

/* Stack size global extern variables */
extern uint32_t    _STACK_SIZE;
extern uint32_t    _stack;

static uint32_t    oldSP, newSP;
static uint32_t   *topStack = &_stack;

#endif

volatile uint64_t test_module_cyles;

#define TEST_PRINTF printf

static unsigned int tcntr_start[2], tcntr_end[2], overflow;
static uint64_t t_start, t_end, overhead;
uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;
static uint32_t counterIdtc0_read, counterIdtc1_read,counterIdtc0_write,counterIdtc1_write;

void profiler_init(void)
{
#ifdef __ARP32__
    _tsc_start();
    t_start = _tsc_gettime();
    overhead = _tsc_gettime() - t_start;

    /*------------------------------------------------------------*/
    /* This function actually sets Enable bit in the CT CNTL      */
    /* register of SCTM. Parameter CTM is defined in              */
    /* baseaddress.h, and is used by cred macros to compute       */
    /* baseaddress of CTM.                                        */
    /*------------------------------------------------------------*/
    EVE_SCTM_Enable(CTM);

    /*------------------------------------------------------------*/
    /* Configure Counter 0, to measure "vcop_busy" which is a     */
    /* duration signal, and enable the counter.                   */
    /*------------------------------------------------------------*/
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_1, VCOP_OVERHEAD, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_1);

    statCollectorInit();
    counterIdtc0_read  = statCollectorControl(STATCOL_EVE1_TC0, 0, TI_STATCOL_CONFIGURE_RD);
    counterIdtc1_read  = statCollectorControl(STATCOL_EVE1_TC1, 0, TI_STATCOL_CONFIGURE_RD);
    counterIdtc0_write = statCollectorControl(STATCOL_EVE1_TC0, 0, TI_STATCOL_CONFIGURE_WR);
    counterIdtc1_write = statCollectorControl(STATCOL_EVE1_TC1, 0, TI_STATCOL_CONFIGURE_WR);

#endif
    test_module_cyles = 0;
}


void profiler_start(void)
{
#ifdef __ARP32__
    tcntr_start[0] = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    tcntr_start[1] = EVE_SCTM_CounterRead(CTM, SCTM_Counter_1);
    statCollectorControl(STATCOL_EVE1_TC0, 0, TI_STATCOL_START);
    t_start = _tsc_gettime();
#endif
}

static uint32_t gTest_TI_profile_mode;
void profiler_end(void)
{
#ifdef __ARP32__
    uint32_t numBytesTc0_read, numBytesTc1_read, numBytesTc0_write, numBytesTc1_write;
    t_end = _tsc_gettime();

    gTest_TI_profileTsc = (t_end - t_start - overhead)<<1;
    statCollectorControl(STATCOL_EVE1_TC0, 0, TI_STATCOL_STOP);

    tcntr_end[0] = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
    if(overflow) {
        TEST_PRINTF("Warning: SCTM Counter overflow!!!\n");
    }
    gTest_TI_profileSctm[0] = ((overflow) ? (0XFFFFFFFF + tcntr_end[0] - tcntr_start[0]) : (tcntr_end[0] - tcntr_start[0])) << 1;

    tcntr_end[1] = EVE_SCTM_CounterRead(CTM, SCTM_Counter_1);
    overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_1);
    if(overflow) {
        TEST_PRINTF("Warning: SCTM Counter overflow!!!\n");
    }

    gTest_TI_profileSctm[1] = ((overflow) ? (0XFFFFFFFF + tcntr_end[1] - tcntr_start[1]) : (tcntr_end[1] - tcntr_start[1]));
    test_module_cyles = gTest_TI_profileSctm[0];

    if(gTest_TI_profile_mode == 0)
    {
      TEST_PRINTF("TEST_REPORT_INIT_PROFILE_DATA : ");
    }
    else if(gTest_TI_profile_mode == 1)
    {
      TEST_PRINTF("TEST_REPORT_PROCESS_PROFILE_DATA : ");
    }

    TEST_PRINTF("TSC cycles = %lld, SCTM VCOP BUSY cycles = %lld, SCTM VCOP Overhead = %lld\n",
           gTest_TI_profileTsc, gTest_TI_profileSctm[0], gTest_TI_profileSctm[1]);
    
    numBytesTc0_read  = statCollectorControl(STATCOL_EVE1_TC0, counterIdtc0_read,  TI_READ_STATS);
    numBytesTc1_read  = statCollectorControl(STATCOL_EVE1_TC1, counterIdtc1_read,  TI_READ_STATS);
    numBytesTc0_write = statCollectorControl(STATCOL_EVE1_TC0, counterIdtc0_write, TI_READ_STATS);
    numBytesTc1_write = statCollectorControl(STATCOL_EVE1_TC1, counterIdtc1_write, TI_READ_STATS);

    TEST_PRINTF("I/O Bytes : %8d ( %8d + %8d ) : %8d ( %8d + %8d ) \n",(numBytesTc0_read+numBytesTc0_write), 
      numBytesTc0_read, numBytesTc0_write, (numBytesTc1_read +  numBytesTc1_write), numBytesTc1_read, numBytesTc1_write);
#endif
}


void profiler_end_print(uint32_t id)
{
#ifdef __ARP32__
  gTest_TI_profile_mode = id;
  profiler_end();
#endif
}



void print_profile_num(void)
{
#ifdef __ARP32__
    TEST_PRINTF("TSC cycles = %d, SCTM VCOP BUSY cycles = %d, SCTM VCOP Overhead = %d\n",
           gTest_TI_profileTsc, gTest_TI_profileSctm[0], gTest_TI_profileSctm[1]);
#endif
}

void report_profile_num(char* comp_name, char* statusStr, int img_width, int img_height, char* comments)
{
#ifdef __ARP32__

#ifdef REPORT
    TI_FILE *fpReport = FOPEN("../../../report.csv","a+");
#endif

#ifdef EN_ZEBU_TEST
    TEST_PRINTF("\n%s %s %s %s %s %s %s %s %s %s %s %s\n", \
            "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
            "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Overhead", "Comments");

    TEST_PRINTF("%s %s %d %d %d %d\n", comp_name, statusStr,
    img_width, img_height, 1, gTest_TI_profileTsc);

#else
    TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %15s %s\n", \
            "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
            "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Overhead", "Comments");
    TEST_PRINTF("%-20s %10s %10d %10d %10d %15lld %15.2f %20.2f %10.2f %16.2f    %15lld %s\n",
        comp_name, statusStr, img_width, img_height,
        1, gTest_TI_profileTsc, (gTest_TI_profileTsc/1000000.0), 30*(gTest_TI_profileTsc/1000000.0), (gTest_TI_profileTsc*1.0)/(img_width * img_height),
        (gTest_TI_profileTsc/500000.0), ((gTest_TI_profileTsc - gTest_TI_profileSctm[0])*100 + gTest_TI_profileSctm[0] - 1)/gTest_TI_profileSctm[0], comments);
#endif
#endif
}


void report_memory_usage(char* comp_name, char* comments)
{
#ifdef __ARP32__
#ifndef EN_ZEBU_TEST
    TEST_PRINTF("\n%-20s %25s %20s %20s %20s %20s %20s    %s", \
            "Algorithm", "Scratch(.far/.fardata)", "Const(.const)", "Program(.text)", "DDRTrfrIn", "DDRTrfrOut", "DDRTrfrTot", "Comments");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20.1f %20.1f %20.1f    %s\n", comp_name, 0, 1, 25, 1.0, 1.0, 2.0, comments);
#endif
#endif
}


void profiler_deinit(void)
{
#ifdef __ARP32__
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_1);
#endif
}

uint32_t profiler_getSP(void)
{
#ifdef __ARP32__
    /* Must use static variable since I can't return pointer to local variable */
    static uint32_t   *pTemp = 0;

    uint32_t    iTemp; /* Local variable on stack, within 8 bytes of calling function */

    pTemp = &iTemp; /* Assign address of local variable to static location in fardata section */

    return ((uint32_t)pTemp); /* Return address of variable near top of stack */
#else
    return 0;
#endif
}

#define SP_SKIP 16

void profiler_initStack(uint32_t SP)
{
#if !(VCOP_HOST_EMULATION || VCOP_7X_TRANSLATION)
    int32_t     i;
    uint32_t    stsize;

    oldSP = SP;
    stsize = oldSP - (uint32_t)topStack - SP_SKIP;

    for( i=0; i < stsize / 4; i++ ) {
        topStack[i] = 0xDEADBEEF;
    }
#endif
}

uint32_t profiler_getStackDepth(void)
{
#ifdef __ARP32__
    int32_t    i;

    for( i=0; i < ((uint32_t)&_STACK_SIZE / 4); i++ ) {
        if( topStack[i] != 0xDEADBEEF ) {
            break;
        }
    }

    newSP = (i * 4) + (uint32_t)topStack;

    TEST_PRINTF("\nTEST_REPORT_STACK_MEM : %d \n",(oldSP - newSP));
    return (oldSP - newSP);
#else
    return 0;
#endif
}

void profiler_printStatus(int32_t status)
{
  if(status)
  {
    TEST_PRINTF("\nTEST_REPORT_TC_STATUS : FAILED\n");
  }
  else
  {
    TEST_PRINTF("\nTEST_REPORT_TC_STATUS : PASSED\n");
  }
}

void profiler_testCaseInfo(int8_t * name, int8_t *desc, uint8_t performanceTestcase)
{
#ifdef __ARP32__
  printf("\n\nTEST_REPORT_TESTCASE_NAME : %s \n",name);
  printf("\n\nTEST_REPORT_TESTCASE_DESC : %s \n",desc);
  if(performanceTestcase)
  {
    printf("\n\nTEST_REPORT_PERF_TESTCASE : \n");
  }
#endif
}

void profiler_performanceParam(uint32_t param)
{
#ifdef __ARP32__
  printf("\n\nTEST_REPORT_PERF_PARAM : %d \n",param);
#endif
}



