;/*
; *  Copyright (C) 2016-2017 Texas Instruments Incorporated - http://www.ti.com/
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

;
; \file swenr.asm
;
; \brief Implement APIs to switch DSP CPU mode
;
;

; BIOS does not support SWE - it justs returns back without any handler support
; Instead we are using SWENR, which is similar to SWE
; SWENR jumps to a location which is given by REP register. This is set up at
; before BIOS_start() when CPU is in supervisor mode. swenr_rep_setup_asm() API is
; used for this purpose.
; In SWENR, NRP is not populated and hence the return address is manually set up
; in the handler (swenr_handler)
; SWENR handler changes the NTSR register as per the function arguments to
; return with the requested CPU mode

    .if __TI_EABI__
    .global  swenr_handler
    .global  swenr_rep_setup_asm
    .global  switch_cpu_mode_asm
    .else
    .global  _swenr_handler
    .global  _swenr_rep_setup_asm
    .global  _switch_cpu_mode_asm
        .endif
    .clink

    .if __TI_EABI__
switch_cpu_mode_asm:    .asmfunc
    .else
_switch_cpu_mode_asm:   .asmfunc
    .endif
    SWENR
swenr_return:
    NOP 5
    RETNOP  .S2   B3, 5
    NOP        4
    .endasmfunc

    .if __TI_EABI__
swenr_handler:    .asmfunc
    .else
_swenr_handler:   .asmfunc
    .endif
    STW.D2T2   B0,*B15--[1]
    STW.D2T2   B1,*B15--[1]

    ;Set return pointer
    MVKL       swenr_return, B0
    MVKH       swenr_return, B0
    MVC        B0, NRP

    ;Set CXM (bit 6) for USER (A4 = 1)
    ;Clr CXM (bit 6) for SUPERVISOR (A4 = 0)
    MVC        NTSR, B0
    MVK.S2     0xffffff0f, B1
    MVKH.S2    0xffff0000, B1
    AND        B0, B1, B0
    SHL        A4, 6, A4 ;Argument is A4
    OR         B0, 9, B0 ;Set XEN/GIE bit
    OR         B0, A4, B0
    MVC        B0, NTSR
    MVK        1, B0
    MVC        B0, ECR

    LDW.D2T2   *++B15[1],B1
    LDW.D2T2   *++B15[1],B0
    B          NRP
    NOP        5
    .endasmfunc


    .if __TI_EABI__
swenr_rep_setup_asm:    .asmfunc
    .else
_swenr_rep_setup_asm:   .asmfunc
    .endif
    STW.D2T2   B0,*B15--[1]
    MVKL       swenr_handler, B0
    MVKH       swenr_handler, B0
    MVC        B0, REP
    MVK        1, B0
    MVC        B0, ECR
    LDW.D2T2   *++B15[1],B0
    RETNOP  .S2   B3, 5
    NOP        4
    .endasmfunc
