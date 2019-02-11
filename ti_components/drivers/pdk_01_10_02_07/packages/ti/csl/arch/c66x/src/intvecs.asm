;/*
; *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
; *
; *  Redistribution and use in source and binary forms, with or without
; *  modification, are permitted provided that the following conditions
; *  are met:
; *
; *    Redistributions of source code must retain the above copyright
; *    notice, this list of conditions and the following disclaimer.
; *
; *    Redistributions in binary form must reproduce the above copyright
; *    notice, this list of conditions and the following disclaimer in the
; *    documentation and/or other materials provided with the
; *    distribution.
; *
; *    Neither the name of Texas Instruments Incorporated nor the names of
; *    its contributors may be used to endorse or promote products derived
; *    from this software without specific prior written permission.
; *
; *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
; *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
; *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
; *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
; *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
; *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
; *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
; *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
; *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
; */

*------------------------------------------------------------------------------
* Global symbols defined here and exported out of this file
*------------------------------------------------------------------------------
    .asg init_regs, _init_regs
    .global _init_regs
    .global	_INT_SetWaitForInterrupt


*------------------------------------------------------------------------------
* Global symbols referenced in this file but defined somewhere else.
* Remember that your interrupt service routines need to be referenced here.
*------------------------------------------------------------------------------
   .ref __IRQ_intTable
   .ref __ISR_Table
   .ref _main
   .ref __c_int00
   .ref __stack
   .ref __STACK_SIZE

*------------------------------------------------------------------------------

    .sect ".text:_init_regs"
    .clink
_init_regs:
        .asmfunc
		MVKL 0,B1
		MVKH 0,B1
		MVKL 0,A0
		MVKH 0,A0
		MV B1,B2
		MV B1,B3
	||	MV B2,B4
		MV B1,B5
	||	MV B2,B6
		MV B1,B7
	||	MV B2,B8
		MV B1,B9
	||	MV B2,B10
		MV B1,B11
	||	MV B2,B12
		MV B1,B13
	||	MV B2,B14
		MV B1,B15
	||	MV B2,B16
		MV B1,B17
	||	MV B2,B18
		MV B1,B19
	||	MV B2,B20
		MV B1,B21
	||	MV B2,B22
		MV B1,B23
	||	MV B2,B24
		MV B1,B25
	||	MV B2,B26
		MV B1,B27
	||	MV B2,B28
		MV B1,B29
	||	MV B2,B30
		MV B1,B31

		MV A0,A1
		MV A1,A2
		MV A1,A3
	||	MV A2,A4
		MV A1,A5
	||	MV A2,A6
		MV A1,A7
	||	MV A2,A8
		MV A1,A9
	||	MV A2,A10
		MV A1,A11
	||	MV A2,A12
		MV A1,A13
	||	MV A2,A14
		MV A1,A15
	||	MV A2,A16
		MV A1,A17
	||	MV A2,A18
		MV A1,A19
	||	MV A2,A20
		MV A1,A21
	||	MV A2,A22
		MV A1,A23
	||	MV A2,A24
		MV A1,A25
	||	MV A2,A26
		MV A1,A27
	||	MV A2,A28
		MV A1,A29
	||	MV A2,A30
		MV A1,A31

		NOP 5

		MVKL __c_int00,B0
		MVKH __c_int00,B0
		B B0

		NOP 5
		NOP 5
		NOP 5
		NOP 5
		NOP 5
        .endasmfunc

_INT_SetWaitForInterrupt:
    IDLE
		RETNOP  B3,5
