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

#ifndef SCTM_H
#define SCTM_H

/* =============================================================================
 * INCLUDE FILES (only if necessary)
 * =============================================================================
 */

#ifdef __cplusplus
extern  "C"
{
#endif

#define NO_OF_TIMERS 2

typedef enum SCTM_Event
{
   SCTM_CLOCK                     =   0,
   CACHE_MISS_COUNT               =   1,
   CACHE_HIT_COUNT                =   2,
   CACHE_MISS_STALL               =   3,
   PREFETCH_COMPULSORY_COUNT      =   4,
   PREFETCH_LOOKAHEAD_COUNT       =   5,
   PREFETCH_HIT_COUNT             =   6,
   PREFETCH_FLUSH_LINE_COUNT      =   7,
   PREFETCH_FLUSH_OCCUR_COUNT     =   8,
   PREFETCH_DISCARD_STALL         =   9,
   TPCC_AET                       =  10,
   ARP32_INT4                     =  11,
   ARP32_INT5                     =  12,
   ARP32_INT6                     =  13,
   ARP32_INT7                     =  14,
   VCOP_BUSY                      =  15,
   VCOP_IDLE_AND_DONE             =  16,
   VCOP_WAIT_FOR_ARP32            =  17,
   VCOP_ARP32_AWAITS              =  18,
   VCOP_OVERHEAD                  =  19,
   VCOP_LD_STALL_BY_ST            =  20,
   VCOP_OP_STALL_BY_LDST          =  21,
   VCOP_OP_STALL_BY_DEPENDENCY    =  22,
   VCOP_RD_IBUFL                  =  23,
   VCOP_RD_IBUFH                  =  24,
   VCOP_RD_WBUF                   =  25,
   VCOP_WR_IBUFL                  =  26,
   VCOP_WR_IBUFH                  =  27,
   VCOP_WR_WBUF                   =  28,
   VCOP_LOOP_START                =  29,
   VCOP_DONE_EVENT                =  30,
   ARP32_NMI                      =  31
} SCTM_Event_type_t;

typedef enum SCTM_Counter_No
{

  SCTM_Counter_0 = 0,
  SCTM_Counter_1 = 1,
  SCTM_Counter_2 = 2,
  SCTM_Counter_3 = 3,
  SCTM_Counter_4 = 4,
  SCTM_Counter_5 = 5,
  SCTM_Counter_6 = 6,
  SCTM_Counter_7 = 7

} SCTM_Counter_type_t;

typedef enum SCTM_Sampling
{

  SCTM_EVENT = 0,
  SCTM_DURATION = 1

} SCTM_Sampling_type_t;

typedef enum SCTM_Timer_Mode
{

  SCTM_RUN_ONCE = 0,
  SCTM_RESTART = 1

} SCTM_Timer_Mode_t;

typedef enum SCTM_Idle
{

  SCTM_DIS_COUNTER = 0,
  SCTM_EN_COUNTER = 1

} SCTM_Idle_type_t;

void EVE_SCTM_Enable( CRED_index_t component);
void EVE_SCTM_CounterReset( CRED_index_t component, SCTM_Counter_type_t  counter_no);
void EVE_SCTM_ChainModeEnable( CRED_index_t component, SCTM_Counter_type_t  counter_no);
void EVE_SCTM_InpEvtSelect( CRED_index_t component, SCTM_Counter_type_t  counter_no, SCTM_Event_type_t  inpsel);
void EVE_SCTM_SamplingSelect( CRED_index_t component, SCTM_Counter_type_t  counter_no,SCTM_Sampling_type_t  samping_type);
void EVE_SCTM_CounterTimerEnable( CRED_index_t component, SCTM_Counter_type_t  counter_no);
void EVE_SCTM_CounterTimerDisable( CRED_index_t component, SCTM_Counter_type_t  counter_no);
void EVE_SCTM_MultipleCountersEnable( CRED_index_t component, UWORD32  counter_no);
void EVE_SCTM_MultipleCountersDisable( CRED_index_t component, UWORD32 counter_no);

void EVE_SCTM_IdleConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no,SCTM_Idle_type_t  en_dis_idle);
void EVE_SCTM_HaltConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no,SCTM_Idle_type_t  en_dis_halt);

void EVE_SCTM_TimerInterruptEnable( CRED_index_t component, SCTM_Counter_type_t counter_no);
void EVE_SCTM_TimerModeSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Timer_Mode_t timer_mode);
void EVE_SCTM_IntervalMatchValueSet( CRED_index_t component, SCTM_Counter_type_t counter_no, UWORD32 interval_match);

UWORD32 EVE_SCTM_CounterRead( CRED_index_t component, SCTM_Counter_type_t counter_no);
UWORD32 EVE_SCTM_OverflowCheck( CRED_index_t component, SCTM_Counter_type_t counter_no);

ReturnCode_t EVE_SCTM_CounterConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t  samping_type);
ReturnCode_t EVE_SCTM_CounterConfig_Chain_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t  samping_type);
ReturnCode_t EVE_SCTM_CounterConfig_idle_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type, SCTM_Idle_type_t en_dis_idle );
ReturnCode_t EVE_SCTM_CounterConfig_halt_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type, SCTM_Idle_type_t  en_dis_halt);

ReturnCode_t EVE_SCTM_TimerConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type, SCTM_Timer_Mode_t timer_mode, UWORD32 interval_match);

#ifdef __cplusplus
}
#endif
#endif	/* SCTM_H */
/* EOF */
