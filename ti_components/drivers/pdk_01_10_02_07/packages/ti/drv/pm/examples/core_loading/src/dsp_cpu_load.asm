;/* =============================================================================
; *   Copyright (c) Texas Instruments Incorporated 2018
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
; *  DATA, OR PROFITS; OR BUSINESS int32_tERRUPTION) HOWEVER CAUSED AND ON ANY
; *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
; */
    .global  GEM_START
    .global  DSP_CPU_LOAD

DSP_CPU_LOAD:
    MVKL    GEM_START,A5
    MVKH    GEM_START,A5
    B       A5
    MVK     0, A5                           ; clear A5 too
    NOP     5

GEM_START:
        MVC           A3, REP               ; Save the Return Address in REP
        MVK.S1        0x7FFF,A0             ; This determines the number of
                                            ; iterations in the loop 0x23e8
  ||    NOP
  ||    NOP
  ||    NOP
        MVK.S1        0xffff8000,A5         ; Keep load addresses to some
        MVKH.S1       0x820000,A5           ; random DDR locations.
        MVK.S2        0xffff8408,B5
        MVKH.S2       0x820000,B5
        MVK.S1        0x0404,A3             ; Set the AMR
        MVKH.S1       0x70000,A3
        MVC.S2X       A3,AMR
        LDDW.D1T1     *A5++[1],A9:A8
  ||    LDDW.D2T2     *B5++[1],B9:B8
        LDDW.D1T1     *A5++[1],A11:A10
  ||    LDDW.D2T2     *B5++[1],B11:B10
        LDDW.D1T1     *A5++[1],A13:A12
  ||    LDDW.D2T2     *B5++[1],B13:B12
        LDDW.D1T1     *A5++[1],A15:A14
  ||    LDDW.D2T2     *B5++[1],B15:B14
        LDDW.D1T1     *A5++[1],A17:A16
  ||    LDDW.D2T2     *B5++[1],B17:B16
        LDDW.D1T1     *A5++[1],A19:A18
  ||    LDDW.D2T2     *B5++[1],B19:B18
        NOP           4

LOOP:
        BDEC.S1       LOOP,A0
  ||    DADDSP.L2     B17:B16,B9:B8,B7:B6
  ||    DADDSP.L1     A13:A12,A13:A12,A21:A20
  ||    DADDSP.S2     B13:B12,B13:B12,B21:B20
  ||    QMPYSP.M1     A15:A14:A13:A12,A19:A18:A17:A16,A11:A10:A9:A8
  ||    QMPYSP.M2     B15:B14:B13:B12,B11:B10:B9:B8,B11:B10:B9:B8
  ||    LDDW.D1T2     *A5++[1],B15:B14
  ||    LDDW.D2T1     *B5++[1],A15:A14
        DADDSP.S1     A23:A22,A13:A12,A23:A22
  ||    DADDSP.S2     B23:B22,B13:B12,B23:B22
  ||    QMPYSP.M1     A11:A10:A9:A8,A11:A10:A9:A8,A31:A30:A29:A28
  ||    QMPYSP.M2     B11:B10:B9:B8,B19:B18:B17:B16,B31:B30:B29:B28
  ||    LDDW.D2T2     *B5++[1],B13:B12
  ||    LDDW.D1T1     *A5++[1],A13:A12
  ||    DADDSP.L1     A13:A12,A11:A10,A3:A2
  ||    DADDSP.L2     B13:B12,B11:B10,B3:B2
        QMPYSP.M1     A19:A18:A17:A16,A11:A10:A9:A8,A27:A26:A25:A24
  ||    QMPYSP.M2     B19:B18:B17:B16,B11:B10:B9:B8,B27:B26:B25:B24
  ||    LDDW.D2T2     *B5++[1],B15:B14
  ||    LDDW.D1T1     *A5++[1],A15:A14
  ||    DADDSP.L1     A15:A14,A13:A12,A21:A20
  ||    DADDSP.L2     B15:B14,B13:B12,B21:B20
  ||    DADDSP.S2     B17:B16,B15:B14,B7:B6
  ||    DADDSP.S1     A15:A14,A15:A14,A7:A6
        LDDW.D1T2     *A5++[1],B13:B12
  ||    LDDW.D2T1     *B5++[1],A13:A12
  ||    DADDSP.L1     A17:A16,A15:A14,A23:A22
  ||    DADDSP.L2     B17:B16,B15:B14,B23:B22
  ||    DADDSP.S1     A13:A12,A13:A12,A3:A2
  ||    DADDSP.S2     B15:B14,B15:B14,B3:B2
  ||    QMPYSP.M1     A15:A14:A13:A12,A15:A14:A13:A12,A11:A10:A9:A8
  ||    QMPYSP.M2     B15:B14:B13:B12,B15:B14:B13:B12,B11:B10:B9:B8
        DADDSP.L1     A13:A12,A17:A16,A7:A6
  ||    DADDSP.L2     B13:B12,B17:B16,B7:B6
  ||    DADDSP.S2     B17:B16,B13:B12,B21:B20
  ||    QMPYSP.M1     A15:A14:A13:A12,A19:A18:A17:A16,A19:A18:A17:A16
  ||    QMPYSP.M2     B15:B14:B13:B12,B19:B18:B17:B16,B19:B18:B17:B16
  ||    LDDW.D1T2     *A5++[1],B15:B14
  ||    LDDW.D2T1     *B5++[1],A15:A14
        DADDSP.S1     A17:A16,A13:A12,A23:A22
  ||    DADDSP.S2     B11:B10,B15:B14,B23:B22
  ||    QMPYSP.M1     A19:A18:A17:A16,A15:A14:A13:A12,A11:A10:A9:A8
  ||    QMPYSP.M2     B19:B18:B17:B16,B15:B14:B13:B12,B11:B10:B9:B8
  ||    LDDW.D1T2     *A5++[1],B13:B12
  ||    LDDW.D2T1     *B5++[1],A13:A12
  ||    DADDSP.L1     A15:A14,A13:A12,A3:A2
  ||    DADDSP.L2     B15:B14,B13:B12,B3:B2
        NOP           6

        MVK.S1        0x0000,A3                 ; Clear the AMR to make sure
        MVKH.S1       0x0000,A3                 ; addressing mode is not
        MVC.S2X       A3,AMR                    ; corrupted.

        MVC.S2        REP, B4                   ; Jump Back to the return
        MV            B4, A3                    ; address
        BNOP.S2       A3
        NOP           5
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
