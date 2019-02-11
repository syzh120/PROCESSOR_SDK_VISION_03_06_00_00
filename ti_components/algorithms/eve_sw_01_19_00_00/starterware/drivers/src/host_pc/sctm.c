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

#include "GlobalTypes.h"
#include "baseaddress.h"
#include "sctm.h"



void EVE_SCTM_Enable( CRED_index_t component)
{
	return;
}

void EVE_SCTM_CounterReset( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
	return;
}

void EVE_SCTM_ChainModeEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
	return;
}

void EVE_SCTM_InpEvtSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel)
{
  	return;
}

void EVE_SCTM_SamplingSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Sampling_type_t samping_type)
{
	return;
}

void EVE_SCTM_CounterTimerEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
	return;
}

void EVE_SCTM_CounterTimerDisable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  	return;
}

void EVE_SCTM_MultipleCountersEnable( CRED_index_t component, UWORD32 counter_no)
{
  	return;
}

void EVE_SCTM_MultipleCountersDisable( CRED_index_t component, UWORD32 counter_no)
{
	return;
}

void EVE_SCTM_IdleConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Idle_type_t en_dis_idle)
{
  	return;
}

void EVE_SCTM_HaltConfigSelect( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Idle_type_t en_dis_halt)
{
  	return;
}

void EVE_SCTM_TimerModeSelect( CRED_index_t component, SCTM_Counter_type_t counter_no,SCTM_Timer_Mode_t timer_mode)
{
  	return;
}

void EVE_SCTM_TimerInterruptEnable( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  	return;
}

void EVE_SCTM_IntervalMatchValueSet( CRED_index_t component, SCTM_Counter_type_t counter_no, UWORD32 interval_match)
{
  	return;
}


UWORD32 EVE_SCTM_CounterRead( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 lval=0;

  return lval;
}

UWORD32 EVE_SCTM_OverflowCheck( CRED_index_t component, SCTM_Counter_type_t counter_no)
{
  UWORD32 overflow=0;

  return overflow;
}

ReturnCode_t EVE_SCTM_CounterConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_Chain_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type)
{
  ReturnCode_t checkReturn = RET_OK;
  
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_idle_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type,SCTM_Idle_type_t en_dis_idle)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}

ReturnCode_t EVE_SCTM_CounterConfig_halt_mode ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type,SCTM_Idle_type_t en_dis_halt)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}

ReturnCode_t EVE_SCTM_TimerConfig ( CRED_index_t component, SCTM_Counter_type_t counter_no, SCTM_Event_type_t inpsel, SCTM_Sampling_type_t samping_type, SCTM_Timer_Mode_t timer_mode, UWORD32 interval_match)
{
  ReturnCode_t checkReturn = RET_OK;
  return checkReturn;
}
