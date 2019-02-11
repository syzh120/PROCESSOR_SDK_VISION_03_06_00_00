@;*******************************************************************************
@;
@; sbl_lib_tda2xx_hs_support.asm - A15 HS device trampoline functions
@;
@;*******************************************************************************
@;
@; Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
@;
@; Redistribution and use in source and binary forms, with or without
@; modification, are permitted provided that the following conditions
@; are met:
@;
@;   Redistributions of source code must retain the above copyright
@;   notice, this list of conditions and the following disclaimer.
@;
@;   Redistributions in binary form must reproduce the above copyright
@;   notice, this list of conditions and the following disclaimer in the
@;   documentation and/or other materials provided with the
@;   distribution.
@;
@;   Neither the name of Texas Instruments Incorporated nor the names of
@;   its contributors may be used to endorse or promote products derived
@;   from this software without specific prior written permission.
@;
@; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
@; "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
@; LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
@; A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
@; OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
@; SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
@; LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
@; DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
@; THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
@; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
@; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
@;
@;
@;*******************************************************************************

@****************************** Global Symbols*******************************
    .global SBLLibHSSecureEntryAsm

@**************************** Code Seection ***********************************

    .text
    .code 32

@
@ int32_t SBLLibHSSecureEntryAsm(uint32_t  id,
@                                uint32_t  flag,
@                                uint32_t *pArgs,
@                                uint32_t *secTaskId)
@ Refer to sbl_lib_tda2xx_priv.h for function parameter definitions.
@
    .func SBLLibHSSecureEntryAsm
SBLLibHSSecureEntryAsm:
  PUSH    {r4-r12, lr}
  PUSH    {r3}
  LDR     r6, [r3]
  MOV     r7, r3
  MOV     r3, r2
  MOV     r2, r1
  CMP     r6,  #0xFF
  MOVEQ   r12, #0x00    @ New service
  MOVNE   r12, #0xFE    @ Resume a interrupted service
  MOV     r1,  #0x0     @ Process ID - always zero
  DSB
  DMB
  SMC     #0
  MOV     r6, #0xFF
  NOP
  POP     {r3}
  STR     r6, [r3]
  POP     {r4-r12, pc}

