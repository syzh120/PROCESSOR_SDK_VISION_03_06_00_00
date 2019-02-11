/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *
*/


#ifndef __TCASECFG_H__
#define __TCASECFG_H__

#include "soc.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define RET_FAIL 1
#define RET_OK 0

typedef enum CPUID_Label
{
   IPU_ID = 0x0,  /** IPU domain*/
   DSP1_ID = 0x1, /** EVE domain*/
   DSP2_ID = 0x2, /** DSP1 domain*/
   EVE_ID = 0x3  /** DSP2 domain*/
} cpuIDType;
#define TestFunction                  GMAC_Throughput_TestFunction
void test_pass ();
void test_fail ();
uint32_t slaveRunTc ();
#define DSP1     0
#define DSP2    0
#define EVE    0
#define MULTICORE 0
/* ===========================================================================
 *  EXPORTED TYPES
 * ===========================================================================
 */
#define MSG_USER_MASK                   0x0000FFFFl
#define MSG_USER_POS                    0
#define MSG_TYPE_MASK                   0x000F0000l
#define MSG_TYPE_POS                    16
#define MSG_ID_MASK                     0x00F00000l
#define MSG_ID_POS                      20
#define MSG_DESTIN_MASK                 0x0F000000l
#define MSG_DESTIN_POS                  24
#define MSG_SOURCE_MASK                 0xF0000000l
#define MSG_SOURCE_POS                  28

#define MSG_NO_ID                       0x00000000l
#define MSG_RDY_FOR_LOAD                0x00060000l
#define MSG_START_LOAD                  0x00070000l
#define MSG_LOAD_COMPLETED              0x00080000l
#define MSG_RUN_APP                     0x00090000l
#define MSG_RUN_TC                      0x000A0000l
#define MSG_START_SLAVE                 0x000C0000l
#define MSG_SLAVE_RUNNING               0x000D0000l
#define MSG_TEST_RESULT                 0x000E0000l
#define MSG_FATAL_ERROR                 0x000F0000l

#define MSG_BUFFER_FULL                 1


/* ===========================================================================
 *  EXPORTED VARIABLES
 * ===========================================================================
 */


/* ===========================================================================
 *  LOCAL VARIABLES
 * ===========================================================================
 */
/* ---------------------------------------------------------------------- *//**
 * @VARIABLE     cpuBoot
 *
 * @BRIEF        SOC_cpu_t cpuBoot[]
 *
 * @DESCRIPTION  Boot scheme defining multi-master & slave hierarchy. First
 *               processor in a row represents master and the rest of the row
 *               lists its slaves. The slaves-list is dynamic in its size
 *               and therefore it is terminated with special EndOfSlaves ID.
 *               The whole array is terminated by another ID - EndOfMasterCPUs.
 *               The processor IDs are defined in soc.h.
 *               IMPORTANT:
 *                1. first un-commented line starts with MPU ID
 *                2. each un-commented line must start with master ID and end
 *                   with END_SLAVES terminator having slaves IDs in between
 *                3. last un-commented line ends with END_MASTERS terminator
 *
 *//*----------------------------------------------------------------------*/
#ifdef __MAIN_C__
SOC_cpu_t cpuBoot[] = {
   /* Master,                  Slave List,                termination: EndOfSlaves */
   UNKNOWN,         /* C66X1_APE, *//*CORTEXM4_SYS1_APE, *//* CORTEXA15_CPU1_APE, */
   END_SLAVES,
   /* C66X1_APE, *//*C66X2_APE, *//* ARM9_ICONT_APE, *//*ARM9_VDMA_APE, *//* CORTEXM4_SYS2_APE , *//* END_SLAVES, */
   /* C66X2_APE,         ARP32_EVE1_APE,   ARP32_EVE2_APE,   ARP32_EVE3_APE,  ARP32_EVE4_APE, END_SLAVES, */
   /* CORTEXM4_SYS1_APE, *//* CORTEXM4_SIM1_APE,                              *//* END_SLAVES, */
   /* CORTEXM4_SYS2_APE, *//* CORTEXM4_SIM2_APE,                              *//* END_SLAVES, */
   END_MASTERS         /* No more master CPUs */
};
#endif /* __MAIN_C__ */

/* ===========================================================================
 *  EXPORTED FUNCTIONS/MACROS
 * ===========================================================================
 */

#ifdef __cplusplus
}
#endif

#endif /* __TCASECFG_H__ */

/* EOF */
