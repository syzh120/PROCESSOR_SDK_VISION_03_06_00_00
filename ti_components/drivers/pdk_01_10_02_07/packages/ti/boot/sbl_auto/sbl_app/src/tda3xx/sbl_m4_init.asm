;*******************************************************************************
;
; sbl_m4_init.asm - Initialization code for Cortex M4
;                   (used for tda3xx SBL in all boot modes)
;
;*******************************************************************************
;
; Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions
; are met:
;
;   Redistributions of source code must retain the above copyright
;   notice, this list of conditions and the following disclaimer.
;
;   Redistributions in binary form must reproduce the above copyright
;   notice, this list of conditions and the following disclaimer in the
;   documentation and/or other materials provided with the
;   distribution.
;
;   Neither the name of Texas Instruments Incorporated nor the names of
;   its contributors may be used to endorse or promote products derived
;   from this software without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
; "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
; LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
; A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
; OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
; SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
; LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
; DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
; THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;*******************************************************************************

;****************************** Global Symbols *********************************
        .global stackEnd
        .global bssStart
        .global bssEnd
        .global _c_int00

        .sect ".sbl_init"
        .global sbl_start

;******************************* Code Section **********************************
;
; This is SBL start point.
sbl_start:

; Set the Stack Pointer
         LDR  R0, _stackEnd ;Read the stack address
         MOV  SP, R0         ;Write the Stack Pointer


; Clear BSS Section
clear_bss_section:
         LDR  R0, _bssStart ;Start address of BSS
         LDR  R1, _bssEnd   ;End address of BSS
         SUB  R1, R1, #4
         MOV  R2, #0
loop:
         STR  R2, [R0], #4   ;Clear one word in BSS
         CMP  R0, R1
         BLE  loop           ;Clear till BSS end

; Set all registers to 0
         MOV  R0,  #0
         MOV  R1,  #0
         MOV  R2,  #0
         MOV  R3,  #0
         MOV  R4,  #0
         MOV  R5,  #0
         MOV  R6,  #0
         MOV  R7,  #0
         MOV  R8,  #0
         MOV  R9,  #0
         MOV  R10, #0
         MOV  R11, #0
         MOV  R12, #0

; Branch to _c_int00
         B  _c_int00

_stackEnd:
    .word stackEnd
_bssStart:
    .word bssStart
_bssEnd:
    .word bssEnd
