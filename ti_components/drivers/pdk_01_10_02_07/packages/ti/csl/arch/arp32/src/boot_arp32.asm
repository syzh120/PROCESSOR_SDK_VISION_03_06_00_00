;/*
; *  Copyright (C) 2014-2017 Texas Instruments Incorporated - http://www.ti.com/
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

;******************************************************************************
;* asm directives                                                             *
;******************************************************************************

    .data
    .global _my_stack
_my_stack:
    .word 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0

    .text
    .global main
    .global _c_int00
    .global exit
    .global _vec_table
    .global _reset_handler
    .global _dummy_handler

    .ref NMI_IRQ
    .ref SWI_IRQ
    .ref INTH_IRQ4
    .ref INTH_IRQ5
    .ref INTH_IRQ6
    .ref INTH_IRQ7
    .ref INTH_IRQ8
    .ref INTH_IRQ9
    .ref INTH_IRQ10
    .ref INTH_IRQ11
    .ref INTH_IRQ12
    .ref INTH_IRQ13
    .ref INTH_IRQ14
    .ref INTH_IRQ15

;******************************************************************************
;* Interrupt Service Table (IST)                                              *
;******************************************************************************
    .sect ".intvecs"

_vec_table:
    .word _reset_handler      ; RESET
    .word NMI_IRQ             ; NMI
    .word SWI_IRQ             ; SWI
    .word _dummy_handler      ; UNDEF
    .word INTH_IRQ4           ; INT4
    .word INTH_IRQ5           ; INT5
    .word INTH_IRQ6           ; INT6
    .word INTH_IRQ7           ; INT7
    .word INTH_IRQ8           ; INT7
    .word INTH_IRQ9           ; INT9
    .word INTH_IRQ10          ; INT10
    .word INTH_IRQ11          ; INT11
    .word INTH_IRQ12          ; INT12
    .word INTH_IRQ13          ; INT13
    .word INTH_IRQ14          ; INT14
    .word INTH_IRQ15          ; INT15



;******************************************************************************
;* Reset handler                                                              *
;******************************************************************************
    .sect ".inthandler"

_reset_handler:
    MVC    1,         CSR     ; enable GIE
    MVC    0xFF3,      IER     ;
    MVC    _my_stack, SP
    MVCH   _my_stack, SP
    CALL    _c_int00
    NOP
    CALL    exit
    NOP
    MVK _vec_table, R7
    MVK main, R6
    MVK _reset_handler, R6

;******************************************************************************
;* Dummy handler                                                              *
;******************************************************************************
    .sect ".inthandler"
_dummy_handler:
    NOP
    NOP
    B   _dummy_handler
    NOP

;----------------------------------------------------------------------
; Exit simulation
;----------------------------------------------------------------------
    .sect   ".exitlocation"
    .global end_of_test
            NOP       ; -- 0x100

            NOP       ; -- 0x104
            NOP       ; -- 0x108
end_of_test:
            MVKS    -1, R0
            MVKS    -1, R1
            MVKS    -1, R2
            MVKS    -1, R3
            MVKS    -1, R4
            MVKS    -1, R5
            MVKS    -1, R6
            MVKS    -1, R7

;----------------------------------------------------------------------
