;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:29:45 2013                                *
;******************************************************************************
	.compiler_opts --abi=eabi --c64p_l1d_workaround=off --endian=little --hll_source=on --long_precision_bits=32 --mem_model:code=near --mem_model:const=data --mem_model:data=far --object_format=elf --silicon_version=6600 --symdebug:none 

;******************************************************************************
;* GLOBAL FILE PARAMETERS                                                     *
;*                                                                            *
;*   Architecture      : TMS320C66xx                                          *
;*   Optimization      : Enabled at level 3                                   *
;*   Optimizing for    : Speed                                                *
;*                       Based on options: -o3, no -ms                        *
;*   Endian            : Little                                               *
;*   Interrupt Thrshld : Disabled                                             *
;*   Data Access Model : Far                                                  *
;*   Pipelining        : Enabled                                              *
;*   Speculate Loads   : Enabled with threshold = 0                           *
;*   Memory Aliases    : Presume are aliases (pessimistic)                    *
;*   Debug Info        : No Debug Info                                        *
;*                                                                            *
;******************************************************************************

	.asg	A15, FP
	.asg	B14, DP
	.asg	B15, SP
	.global	$bss

	.global	a
	.sect	".fardata:a", RW
	.clink
	.align	8
	.elfsym	a,SYM_SIZE(40)
a:
	.word	0422d856dh		; a[0] @ 0
	.word	0c27bc39bh		; a[1] @ 32
	.word	0c1d58d28h		; a[2] @ 64
	.word	0c2462238h		; a[3] @ 96
	.word	0421f8aadh		; a[4] @ 128
	.word	0406e00efh		; a[5] @ 160
	.word	0c18569f3h		; a[6] @ 192
	.word	0429a18dah		; a[7] @ 224
	.word	0428ed11eh		; a[8] @ 256
	.word	0c1e7f9aeh		; a[9] @ 288

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\152002 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\152004 
	.sect	".text"
	.clink
	.global	main

;******************************************************************************
;* FUNCTION NAME: main                                                        *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,   *
;*                           A15,B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,   *
;*                           B13,SP,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,  *
;*                           A26,A27,A28,A29,A30,A31,B16,B17,B18,B19,B20,B21, *
;*                           B22,B23,B24,B25,B26,B27,B28,B29,B30,B31          *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,   *
;*                           A15,B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,   *
;*                           B13,DP,SP,A16,A17,A18,A19,A20,A21,A22,A23,A24,   *
;*                           A25,A26,A27,A28,A29,A30,A31,B16,B17,B18,B19,B20, *
;*                           B21,B22,B23,B24,B25,B26,B27,B28,B29,B30,B31      *
;*   Local Frame Size  : 8 Args + 20 Auto + 56 Save = 84 byte                 *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |90| 
           STW     .D2T1   A10,*SP--(8)      ; |90| 
           STDW    .D2T2   B13:B12,*SP--     ; |90| 
           STDW    .D2T2   B11:B10,*SP--     ; |90| 
           STDW    .D2T1   A15:A14,*SP--     ; |90| 

           STDW    .D2T1   A13:A12,*SP--     ; |90| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(40)      ; |90| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |98| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .L2     0xa,B4
||         MVKL    .S1     a,A12

           MVKH    .S1     a,A12
||         MVKL    .S2     output,B12

           CALL    .S1     cosf              ; |107| 
||         MV      .L1     A12,A13
||         MV      .D1X    B4,A11
||         MVKH    .S2     output,B12
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A13++,A4         ; |107| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |107| 
$C$RL1:    ; CALL OCCURS {cosf} {0}          ; |107| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |107| 
||         SUB     .L1     A11,1,A0          ; |106| 
||         SUB     .S1     A11,1,A11         ; |106| 

   [ A0]   BNOP    .S1     $C$L1,3           ; |106| 

           ADD     .L2     B10,B4,B4         ; |107| 
||         ADD     .S2     4,B10,B10         ; |106| 

   [ A0]   CALL    .S1     cosf              ; |107| 
||         STW     .D2T1   A4,*B4            ; |107| 
|| [!A0]   MVK     .L2     0xa,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |106| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           ZERO    .L2     B10
||         MV      .L1     A12,A10
||         ADD     .S2     4,B12,B11

           MV      .L1X    B4,A11
||         CALL    .S1     cossp             ; |110| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |110| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |110| 
$C$RL2:    ; CALL OCCURS {cossp} {0}         ; |110| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |110| 
||         SUB     .L1     A11,1,A0          ; |109| 
||         SUB     .S1     A11,1,A11         ; |109| 

   [ A0]   BNOP    .S1     $C$L2,3           ; |109| 
|| [!A0]   MVK     .L2     0xa,B5

           ADD     .L2     B10,B4,B4         ; |110| 
||         ADD     .S2     4,B10,B10         ; |109| 

   [ A0]   CALL    .S1     cossp             ; |110| 
||         STW     .D2T1   A4,*B4            ; |110| 
|| [!A0]   ADD     .L2     4,B11,B4

           ; BRANCHCC OCCURS {$C$L2}         ; |109| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           CALL    .S1     cossp_c           ; |113| 
||         ZERO    .L2     B10
||         MV      .L1X    B5,A11
||         MV      .D1     A10,A12
||         STW     .D2T2   B4,*+SP(16)

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |113| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |113| 
$C$RL3:    ; CALL OCCURS {cossp_c} {0}       ; |113| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(16),B4       ; |113| 
           SUB     .L1     A11,1,A0          ; |112| 
           SUB     .L1     A11,1,A11         ; |112| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |113| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |112| 

           ADD     .L2     B10,B4,B4         ; |113| 
||         ADD     .S2     4,B10,B10         ; |112| 

   [ A0]   CALL    .S1     cossp_c           ; |113| 
||         STW     .D2T1   A4,*B4            ; |113| 

           ; BRANCHCC OCCURS {$C$L3}         ; |112| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVK     .L2     0xa,B0
||         LDW     .D2T2   *+SP(16),B4
||         MVKL    .S2     0x3fc90fdb,B31

           MV      .L1     A10,A16
           MVKH    .S2     0x3fc90fdb,B31
           ZERO    .L1     A27
           MV      .L1X    B31,A11
           ADD     .L2     4,B4,B13
           LDW     .D2T1   *B13,A9
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/cossp/cossp_d.c
;*      Loop source line                 : 115
;*      Loop opening brace source line   : 115
;*      Loop closing brace source line   : 117
;*      Known Minimum Trip Count         : 10                    
;*      Known Maximum Trip Count         : 10                    
;*      Known Max Trip Count Factor      : 10
;*      Loop Carried Dependency Bound(^) : 76
;*      Unpartitioned Resource Bound     : 6
;*      Partitioned Resource Bound(*)    : 6
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     2        3     
;*      .D units                     1        1     
;*      .M units                     6*       5     
;*      .X cross paths               8*       2     
;*      .T address paths             1        1     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           4        5     (.L or .S unit)
;*      Addition ops (.LSD)          4        4     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             3        4     
;*      Bound(.L .S .D .LS .LSD)     4        5     
;*
;*      Disqualified loop: Loop carried dependency bound too large
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A16++,A3         ; |81| 
           NOP             4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 69

           ABSSP   .S1     A3,A3             ; |81| 
||         ZERO    .L1     A4

           FADDSP  .L1     A11,A3,A3         ; |81| 
||         MVKH    .S1     0x49800000,A4

           MVKL    .S1     0x3ea2f983,A31
           MVKH    .S1     0x3ea2f983,A31
           CMPGTSP .S1     A3,A4,A0          ; |81| 
   [ A0]   MV      .L1     A11,A3            ; |81| 
           MPYSP   .M1     A31,A3,A4         ; |81| 
           MVKL    .S2     0x3a7daa22,B4
           ZERO    .L1     A6
           MVKH    .S1     0x40490000,A6
           SPINT   .L1     A4,A4             ; |81| 
           MVKH    .S2     0x3a7daa22,B4
           MVKL    .S1     0x362e9c5b,A30
           MVKH    .S1     0x362e9c5b,A30
           INTSP   .L1     A4,A5             ; |88| 
           MVKL    .S1     0xb94fb222,A7
           MVKH    .S1     0xb94fb222,A7
           MVKL    .S1     0x3c08873e,A29
           MPYSP   .M1     A6,A5,A6          ; |88| 
           MPYSP   .M2X    B4,A5,B4          ; |88| 
           MVKH    .S1     0x3c08873e,A29
           MVKL    .S1     0xbe2aaaa4,A28
           FSUBSP  .L1     A3,A6,A3          ; |88| 
           MVKH    .S1     0xbe2aaaa4,A28
           SUB     .L2     B0,1,B0           ; |115| 
           FSUBSP  .L1X    A3,B4,A3          ; |88| 
           ZERO    .L1     A26
           AND     .S1     1,A4,A0           ; |81| 
           MPYSP   .M1     A3,A3,A5          ; |98| 
           ZERO    .L1     A4
           MVKH    .S1     0xbf800000,A4
           MVKH    .S1     0x39800000,A26
           MPYSP   .M1     A30,A5,A6         ; |98| 
           NOP             3
           FADDSP  .L1     A7,A6,A6          ; |98| 
           NOP             2
           MPYSP   .M1     A5,A6,A6          ; |98| 
           NOP             3
           FADDSP  .L1     A29,A6,A6         ; |98| 
           NOP             2
           MPYSP   .M1     A5,A6,A6          ; |98| 
           NOP             3
           FADDSP  .L1     A28,A6,A6         ; |98| 
           NOP             2
           MPYSP   .M1     A5,A6,A5          ; |98| 
           SET     .S1     A27,0x17,0x1d,A6
   [!A0]   MV      .L1     A6,A4             ; |81| 
           NOP             1
           MPYSP   .M1     A3,A5,A5          ; |98| 
           NOP             3

           FADDSP  .L1     A5,A3,A5          ; |98| 
||         ABSSP   .S1     A3,A3             ; |88| 

           CMPLTSP .S1     A3,A26,A0         ; |91| 

   [ B0]   B       .S1     $C$L4             ; |115| 
|| [ A0]   MPYSP   .M1     A4,A3,A3          ; |92| 

   [!A0]   MPYSP   .M1     A4,A5,A3          ; |98| 
           NOP             3

   [!B0]   CALL    .S1     cossp_v           ; |118| 
||         STW     .D1T1   A3,*A9++          ; |116| 

           ; BRANCHCC OCCURS {$C$L4}         ; |115| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B12(16),B4      ; |118| 
           MV      .L1     A10,A4            ; |118| 
           MVK     .L1     0xa,A6            ; |118| 
           ADDKPC  .S2     $C$RL4,B3,1       ; |118| 
$C$RL4:    ; CALL OCCURS {cossp_v} {0}       ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f2a36e2,B7

           LDW     .D2T1   *B12,A4           ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3f2a36e2,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3f2a36e2,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xeb1c432d,B6

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .L1     0xa,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3f2a36e2,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3f2a36e2,B7

           STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0xeb1c432d,B6

           MV      .L2     B12,B5
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0x3f2a36e2,B7

           MV      .L2     B12,B31           ; |69| 
||         ADD     .L1X    4,B13,A10
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A10,B4           ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0xa,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S1     fcn_pass,A3
           MVKH    .S1     fcn_pass,A3
           ADD     .L1     4,A3,A15
           LDW     .D1T1   *A15,A0           ; |72| 
           MV      .L2X    A3,B5             ; |72| 
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           ADD     .L2X    8,A3,B10
           NOP             1

   [!A0]   B       .S1     $C$L5             ; |72| 
|| [ A0]   LDW     .D2T2   *B10,B0           ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |122| 
   [!A0]   ZERO    .L1     A3                ; |72| 
   [ A0]   ADD     .L2     4,B10,B4
   [!A0]   MVKL    .S1     all_pass,A4
   [!A0]   MVKH    .S1     all_pass,A4
           ; BRANCHCC OCCURS {$C$L5}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   ZERO    .L1     A3                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |122| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x1,A4            ; |122| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |122| 

$C$RL9:    ; CALL OCCURS {print_test_results} {0}  ; |122| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           ZERO    .L1     A7
||         MVKL    .S2     a_sc,B4

           MVKH    .S1     0xbf800000,A7
||         MVKH    .S2     a_sc,B4
||         ZERO    .L1     A6
||         ZERO    .L2     B5
||         MVK     .D2     -1,B6             ; |135| 

           STW     .D2T2   B6,*+B4(24)       ; |135| 
||         MVKH    .S2     0x80000000,B5
||         SET     .S1     A6,0x17,0x1d,A6

           ZERO    .L2     B4                ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         STDW    .D2T1   A7:A6,*+B4(16)    ; |134| 
||         MV      .L1X    B4,A14            ; |130| 
||         ZERO    .S1     A5

           MVK     .L2     0x7,B4
||         STDW    .D2T2   B5:B4,*B6         ; |130| 
||         MVKH    .S1     0xff800000,A5
||         ZERO    .L1     A4

           MV      .L2     B6,B31            ; |130| 
||         SET     .S1     A4,0x17,0x1e,A4

           MV      .L1X    B4,A12            ; |130| 
||         STDW    .D2T1   A5:A4,*+B31(8)    ; |132| 
||         ZERO    .L2     B12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D1T1   *A14,A3           ; |137| 
           CALL    .S1     cos               ; |137| 
           ADDKPC  .S2     $C$RL10,B3,2      ; |137| 
           SPDP    .S1     A3,A5:A4          ; |137| 
           NOP             1
$C$RL10:   ; CALL OCCURS {cos} {0}           ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |137| 
           DPSP    .L1     A5:A4,A3          ; |137| 
           NOP             3
           ADD     .L2     B12,B4,B4         ; |137| 
           STW     .D2T1   A3,*B4            ; |137| 

           CALLP   .S2     cossp,B3
||         LDW     .D1T1   *A14,A4           ; |138| 

$C$RL11:   ; CALL OCCURS {cossp} {0}         ; |138| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |138| 
           NOP             4
           ADD     .L2     B12,B4,B4         ; |138| 
           STW     .D2T1   A4,*B4            ; |138| 

           CALLP   .S2     cossp_c,B3
||         LDW     .D1T1   *A14,A4           ; |139| 

$C$RL12:   ; CALL OCCURS {cossp_c} {0}       ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 84
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |139| 
           MVKL    .S1     0x3ea2f983,A30
           ZERO    .L1     A31
           MVKH    .S1     0x49800000,A31
           MVKH    .S1     0x3ea2f983,A30
           ADD     .L2     B12,B4,B4         ; |139| 
           STW     .D2T1   A4,*B4            ; |139| 
           LDW     .D1T1   *A14++,A3         ; |70| 
           ZERO    .L1     A6
           MVKL    .S2     0x3a7daa22,B31
           MVKH    .S1     0x40490000,A6
           MVKH    .S2     0x3a7daa22,B31
           ABSSP   .S1     A3,A3             ; |70| 
           FADDSP  .L1     A11,A3,A3         ; |70| 
           MVKL    .S1     0x362e9c5b,A29
           MVKH    .S1     0x362e9c5b,A29
           CMPGTSP .S1     A3,A31,A0         ; |72| 
   [ A0]   MV      .L1     A11,A3            ; |73| 
           MPYSP   .M1     A30,A3,A4         ; |78| 
           LDW     .D2T2   *B13,B29          ; |140| 
           MVKL    .S1     0xb94fb222,A7
           MVKH    .S1     0xb94fb222,A7
           SPINT   .L1     A4,A5             ; |78| 
           ZERO    .L2     B30               ; |88| 
           ZERO    .L1     A25               ; |130| 
           ZERO    .S1     A26
           INTSP   .L1     A5,A4             ; |78| 
           MVKL    .S1     0x3c08873e,A28
           MVKH    .S1     0x3c08873e,A28
           SUB     .S1     A12,1,A2          ; |136| 
           MPYSP   .M1     A6,A4,A6          ; |84| 
           MPYSP   .M2X    B31,A4,B4         ; |84| 
           ZERO    .L1     A24
           SUB     .L1     A12,1,A12         ; |136| 
           FSUBSP  .L1     A3,A6,A3          ; |84| 
           MVKL    .S1     0xbe2aaaa4,A27
           MVKH    .S1     0xbe2aaaa4,A27
           FSUBSP  .L1X    A3,B4,A3          ; |84| 
           MVKH    .S1     0x39800000,A24
           AND     .S1     1,A5,A0           ; |81| 
           MPYSP   .M1     A3,A3,A4          ; |98| 
           SET     .S2     B30,31,31,B4      ; |88| 
           NOP             2
           MPYSP   .M1     A29,A4,A6         ; |98| 
           NOP             3
           FADDSP  .L1     A7,A6,A6          ; |98| 
           NOP             2
           MPYSP   .M1     A4,A6,A6          ; |98| 
           NOP             3
           FADDSP  .L1     A28,A6,A6         ; |98| 
           NOP             2
           MPYSP   .M1     A4,A6,A6          ; |98| 
           NOP             3
           FADDSP  .L1     A27,A6,A6         ; |98| 
           NOP             2
           MPYSP   .M1     A4,A6,A6          ; |98| 
           ZERO    .L1     A4
           MVKH    .S1     0xbf800000,A4
           NOP             1
           MPYSP   .M1     A3,A6,A5          ; |98| 
           SET     .S1     A26,0x17,0x1d,A6
   [!A0]   MV      .L1     A6,A4             ; |81| 
           CMPLTSP .S1     A3,A25,A0         ; |87| 

           FADDSP  .L1     A5,A3,A5          ; |98| 
|| [ A0]   XOR     .S1X    A3,B4,A3          ; |88| 
||         ADD     .L2     B12,B29,B4        ; |140| 
||         ADD     .S2     4,B12,B12         ; |136| 

           CMPLTSP .S1     A3,A24,A0         ; |91| 
|| [!A2]   MVKL    .S2     output,B12

   [ A0]   MPYSP   .M1     A4,A3,A3          ; |92| 
|| [!A2]   MVKH    .S2     output,B12

   [ A2]   BNOP    .S2     $C$L6,3           ; |136| 
|| [!A0]   MPYSP   .M1     A4,A5,A3          ; |98| 
|| [!A2]   MVKL    .S1     a_sc,A4

   [!A2]   CALL    .S1     cossp_v           ; |142| 
||         STW     .D2T1   A3,*B4            ; |140| 

   [!A2]   LDW     .D2T2   *+B12(16),B4      ; |142| 
           ; BRANCHCC OCCURS {$C$L6}         ; |136| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S1     a_sc,A4
           MVK     .L1     0x7,A6            ; |142| 
           ADDKPC  .S2     $C$RL13,B3,1      ; |142| 
$C$RL13:   ; CALL OCCURS {cossp_v} {0}       ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f2a36e2,B7

           LDW     .D2T1   *B12,A4           ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3f2a36e2,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0xeb1c432d,B6

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0x3f2a36e2,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3f2a36e2,B7

           MV      .L1X    B12,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0x3f2a36e2,B7

           MV      .L2     B12,B31           ; |69| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A10,B4           ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MV      .L2X    A15,B4            ; |69| 
           LDW     .D2T2   *B4,B0            ; |72| 
           MVKL    .S2     fcn_pass,B31
           MVKH    .S2     fcn_pass,B31
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           STW     .D2T1   A15,*+SP(20)      ; |69| 

   [!B0]   MVKL    .S1     all_pass,A3
|| [!B0]   B       .S2     $C$L7             ; |72| 
|| [!B0]   ZERO    .L1     A4                ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |146| 
|| [!B0]   MVKH    .S1     all_pass,A3
|| [ B0]   LDW     .D2T2   *B10,B0           ; |72| 

   [ B1]   ADD     .L2     4,B10,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L7}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   ZERO    .L1     A4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |146| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |146| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |146| 

$C$RL18:   ; CALL OCCURS {print_test_results} {0}  ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

           MVKL    .S1     0xc000cccc,A13
||         MVKL    .S2     a_ext,B5

           MVKL    .S1     0xcccccccd,A12
||         MVK     .S2     0x81,B4
||         ZERO    .L1     A4

           SET     .S1     A4,0x17,0x17,A4
||         MVKH    .S2     a_ext,B5

           MV      .L2     B5,B4             ; |149| 
||         MVKH    .S1     0xc000cccc,A13
||         STW     .D2T2   B4,*+SP(12)

           STW     .D2T1   A4,*B4            ; |149| 
||         MV      .L1X    B5,A14            ; |149| 
||         MVKH    .S1     0xcccccccd,A12
||         ZERO    .L2     B12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D1T1   *A14,A3           ; |151| 
           CALL    .S1     cos               ; |151| 
           ADDKPC  .S2     $C$RL19,B3,2      ; |151| 
           SPDP    .S1     A3,A5:A4          ; |151| 
           NOP             1
$C$RL19:   ; CALL OCCURS {cos} {0}           ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |151| 
           DPSP    .L1     A5:A4,A3          ; |151| 
           NOP             3
           ADD     .L2     B12,B4,B4         ; |151| 
           STW     .D2T1   A3,*B4            ; |151| 

           CALLP   .S2     cossp,B3
||         LDW     .D1T1   *A14,A4           ; |152| 

$C$RL20:   ; CALL OCCURS {cossp} {0}         ; |152| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |152| 
           NOP             4
           ADD     .L2     B12,B4,B4         ; |152| 
           STW     .D2T1   A4,*B4            ; |152| 

           CALLP   .S2     cossp_c,B3
||         LDW     .D1T1   *A14,A4           ; |153| 

$C$RL21:   ; CALL OCCURS {cossp_c} {0}       ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 100
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |153| 
           MVKL    .S1     0x3ea2f983,A30
           ZERO    .L1     A31
           MVKH    .S1     0x49800000,A31
           MVKH    .S1     0x3ea2f983,A30
           ADD     .L2     B12,B4,B4         ; |153| 
           STW     .D2T1   A4,*B4            ; |153| 
           LDW     .D1T1   *A14,A3           ; |70| 
           ZERO    .L1     A29
           MVKL    .S2     0x3a7daa22,B31
           MVKH    .S1     0x40490000,A29
           MVKH    .S2     0x3a7daa22,B31
           ABSSP   .S1     A3,A3             ; |70| 
           FADDSP  .L1     A11,A3,A4         ; |70| 
           MVKL    .S1     0x362e9c5b,A28
           MVKH    .S1     0x362e9c5b,A28
           CMPGTSP .S1     A4,A31,A0         ; |72| 
   [ A0]   MV      .L1     A11,A4            ; |73| 
           MPYSP   .M1     A30,A4,A3         ; |78| 
           MVKL    .S1     0xb94fb222,A27
           MVKH    .S1     0xb94fb222,A27
           LDW     .D2T2   *B13,B29          ; |154| 
           SPINT   .L1     A3,A6             ; |78| 
           ZERO    .L2     B30               ; |88| 
           MVKL    .S1     0x3c08873e,A26
           MVKH    .S1     0x3c08873e,A26
           INTSP   .L1     A6,A5             ; |78| 
           ZERO    .L1     A23               ; |130| 
           ZERO    .L1     A24
           ZERO    .S1     A22
           MPYSP   .M1     A29,A5,A3         ; |84| 
           MPYSP   .M2X    B31,A5,B4         ; |84| 
           MVKL    .S1     0xbe2aaaa4,A25
           MVKH    .S1     0xbe2aaaa4,A25
           FSUBSP  .L1     A4,A3,A3          ; |84| 
           MVKH    .S1     0x39800000,A22
           AND     .S1     1,A6,A0           ; |81| 
           FSUBSP  .L1X    A3,B4,A5          ; |84| 
           SET     .S2     B30,31,31,B4      ; |88| 
           NOP             1
           MPYSP   .M1     A5,A5,A4          ; |98| 
           NOP             3
           MPYSP   .M1     A28,A4,A7         ; |98| 
           NOP             3
           FADDSP  .L1     A27,A7,A3         ; |98| 
           NOP             2
           MPYSP   .M1     A4,A3,A7          ; |98| 
           NOP             3
           FADDSP  .L1     A26,A7,A3         ; |98| 
           NOP             2
           MPYSP   .M1     A4,A3,A7          ; |98| 
           NOP             3
           FADDSP  .L1     A25,A7,A3         ; |98| 
           NOP             2
           MPYSP   .M1     A4,A3,A4          ; |98| 
           ZERO    .L1     A3
           MVKH    .S1     0xbf800000,A3
           NOP             1
           MPYSP   .M1     A5,A4,A6          ; |98| 
           SET     .S1     A24,0x17,0x1d,A4
   [!A0]   MV      .L1     A4,A3             ; |81| 
           CMPLTSP .S1     A5,A23,A0         ; |87| 

           FADDSP  .L1     A6,A5,A6          ; |98| 
|| [ A0]   XOR     .S1X    A5,B4,A5          ; |88| 

           CMPLTSP .S1     A5,A22,A0         ; |91| 
   [ A0]   MPYSP   .M1     A3,A5,A3          ; |92| 
   [!A0]   MPYSP   .M1     A3,A6,A3          ; |98| 
           ADD     .L2     B12,B29,B4        ; |154| 
           ADD     .L2     4,B12,B12         ; |150| 
           NOP             1
           STW     .D2T1   A3,*B4            ; |154| 
           LDW     .D1T1   *A14,A3           ; |155| 
           LDW     .D2T2   *+SP(12),B4
           NOP             3
           MPYSPDP .M1     A3,A13:A12,A5:A4  ; |155| 
           SUB     .L1X    B4,1,A0           ; |150| 
           SUB     .L2     B4,1,B4           ; |150| 
   [!A0]   MVKL    .S2     output,B12
   [!A0]   MVKH    .S2     output,B12
           NOP             1
   [ A0]   B       .S1     $C$L8             ; |150| 
           DPSP    .L1     A5:A4,A3          ; |155| 
           NOP             3

   [!A0]   CALL    .S1     cossp_v           ; |157| 
||         STW     .D1T1   A3,*++A14         ; |155| 
||         STW     .D2T2   B4,*+SP(12)       ; |155| 

           ; BRANCHCC OCCURS {$C$L8}         ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B12(16),B4      ; |157| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           MVK     .S1     0x81,A6           ; |157| 
           ADDKPC  .S2     $C$RL22,B3,0      ; |157| 
$C$RL22:   ; CALL OCCURS {cossp_v} {0}       ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f2a36e2,B7

           LDW     .D2T1   *B12,A4           ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MVK     .S1     0x81,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL23:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B13
           MVKL    .S2     0x3f2a36e2,B7
           MVKH    .S2     fcn_pass,B13
           MVKL    .S2     0xeb1c432d,B6

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0x3f2a36e2,B7

           STW     .D2T1   A4,*+B13(4)       ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .S1     0x81,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f2a36e2,B7

           MV      .L1X    B12,A3            ; |67| 
||         STW     .D2T1   A4,*+B13(8)       ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .S1     0x81,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f2a36e2,B7

           MV      .L1     A10,A5            ; |68| 
||         MV      .L2     B12,B4            ; |68| 
||         STW     .D2T1   A4,*+B13(12)      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A5,B4            ; |69| 
||         MVK     .S1     0x81,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A15,A0           ; |72| 
           MV      .L2     B10,B4            ; |72| 
           STW     .D2T1   A4,*+B13(16)      ; |69| 
           NOP             2

   [!A0]   B       .S1     $C$L9             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |161| 
   [!A0]   ZERO    .L1     A4                ; |72| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   ZERO    .L1     A4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |161| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |161| 
||         ADDKPC  .S2     $C$RL27,B3,0      ; |161| 

$C$RL27:   ; CALL OCCURS {print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           ZERO    .L2     B5                ; |114| 

           ZERO    .L2     B4                ; |114| 
||         STW     .D2T2   B5,*+SP(28)       ; |114| 

           STW     .D2T2   B4,*+SP(24)       ; |114| 
           LDDW    .D2T2   *+SP(24),B5:B4    ; |114| 
           MVKL    .S2     cycle_counts+24,B7
           MVKH    .S2     cycle_counts+24,B7
           ZERO    .L2     B6                ; |114| 
           NOP             1

           STDW    .D2T2   B5:B4,*B7         ; |114| 
||         MVC     .S2     B6,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           ZERO    .L1     A4
||         CALL    .S2     gimme_random      ; |171| 
||         MVKL    .S1     t_offset,A3

           MVKH    .S1     0xc2c80000,A4
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         ZERO    .L1     A12
||         MVK     .S2     0x80,B30

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKH    .S1     0x43480000,A12

           MV      .L2X    A4,B12
||         ADD     .S2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A3
||         STW     .D2T2   B30,*+SP(12)      ; |117| 

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MV      .L2     B12,B4            ; |171| 
||         MV      .L1     A12,A4            ; |171| 
||         ZERO    .S1     A13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL28,B3,0      ; |171| 
$C$RL28:   ; CALL OCCURS {gimme_random} {0}  ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 103
           MVKL    .S2     input,B4
           MVKH    .S2     input,B4
           LDW     .D2T2   *B4,B4            ; |171| 
           NOP             4
           ADD     .L1X    A13,B4,A3         ; |171| 

           STW     .D1T1   A4,*A3            ; |171| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B5           ; |122| 

           ABSSP   .S1     A4,A3             ; |70| 
||         ZERO    .L1     A4
||         ZERO    .D1     A5
||         MVKL    .S2     0x3a7daa22,B4
||         ZERO    .L2     B31               ; |88| 
||         MV      .D2     B5,B7             ; |122| 

           MVKH    .S1     0x49800000,A4
||         MVKH    .S2     0x3a7daa22,B4
||         ZERO    .D1     A26
||         FADDSP  .L1     A11,A3,A3         ; |70| 

           MVKL    .S1     0x3ea2f983,A31
||         ZERO    .L1     A25               ; |130| 
||         ZERO    .D1     A24

           MVKH    .S1     0x3ea2f983,A31
           CMPGTSP .S1     A3,A4,A0          ; |72| 

   [ A0]   MV      .L1     A11,A3            ; |73| 
||         MVKH    .S1     0x40490000,A5

           MPYSP   .M1     A31,A3,A4         ; |78| 
||         MVKL    .S1     0x362e9c5b,A30

           MVKH    .S1     0x362e9c5b,A30
           MVKL    .S1     0xb94fb222,A29
           MVKH    .S1     0xb94fb222,A29

           MVKL    .S1     0x3c08873e,A28
||         SPINT   .L1     A4,A7             ; |78| 

           MVKH    .S1     0x3c08873e,A28
           MVKL    .S1     0xbe2aaaa4,A27
           MVKH    .S1     0xbe2aaaa4,A27

           INTSP   .L1     A7,A4             ; |78| 
||         AND     .D1     1,A7,A0           ; |81| 
||         MVKL    .S1     output+12,A8

           MVKH    .S1     output+12,A8

           LDW     .D1T1   *A8,A23           ; |175| 
||         MVKH    .S1     0x39800000,A24

           MVKL    .S1     t_start,A15

           MPYSP   .M1     A5,A4,A5          ; |84| 
||         MVKH    .S1     t_start,A15

           MPYSP   .M2X    B4,A4,B4          ; |84| 
||         STDW    .D1T2   B7:B6,*A15

           NOP             2
           FSUBSP  .L1     A3,A5,A3          ; |84| 
           NOP             2

           FSUBSP  .L1X    A3,B4,A5          ; |84| 
||         SET     .S2     B31,31,31,B4      ; |88| 

           NOP             2
           MPYSP   .M1     A5,A5,A6          ; |98| 
           NOP             3
           MPYSP   .M1     A30,A6,A4         ; |98| 
           NOP             3
           FADDSP  .L1     A29,A4,A3         ; |98| 
           NOP             2
           MPYSP   .M1     A6,A3,A4          ; |98| 
           NOP             3
           FADDSP  .L1     A28,A4,A3         ; |98| 
           NOP             2
           MPYSP   .M1     A6,A3,A4          ; |98| 
           NOP             3
           FADDSP  .L1     A27,A4,A3         ; |98| 
           NOP             2

           MPYSP   .M1     A6,A3,A4          ; |98| 
||         ZERO    .L1     A3

           MVKH    .S1     0xbf800000,A3
           NOP             2

           MPYSP   .M1     A5,A4,A6          ; |98| 
||         SET     .S1     A26,0x17,0x1d,A4

   [!A0]   MV      .L1     A4,A3             ; |81| 
||         CMPLTSP .S1     A5,A25,A0         ; |87| 
||         ADD     .D1     A13,A23,A4        ; |175| 

           NOP             2

           FADDSP  .L1     A6,A5,A6          ; |98| 
|| [ A0]   XOR     .S1X    A5,B4,A5          ; |88| 

           CMPLTSP .S1     A5,A24,A0         ; |91| 
   [ A0]   MPYSP   .M1     A3,A5,A3          ; |92| 
   [!A0]   MPYSP   .M1     A3,A6,A3          ; |98| 
           NOP             3

           STW     .D1T1   A3,*A4            ; |175| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S2     t_offset,B13
||         MVKL    .S1     cycle_counts+24,A3
||         ADD     .L1     4,A13,A13         ; |169| 

           MVKH    .S2     t_offset,B13
||         MVKH    .S1     cycle_counts+24,A3

           LDDW    .D2T2   *B13,B17:B16      ; |130| 
||         LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         MVKL    .S2     t_stop,B30
||         MV      .L1     A3,A14            ; |130| 

           MVKH    .S2     t_stop,B30
           STDW    .D2T2   B9:B8,*B30        ; |128| 
           NOP             2
           ADDU    .L2     B16,B6,B5:B4      ; |130| 
           MV      .L2     B4,B6             ; |130| 

           ADD     .S2     B5,B17,B6         ; |130| 
||         SUBU    .L2     B8,B6,B5:B4       ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B16      ; |130| 
||         ADDU    .L2X    A4,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B6,B7          ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         LDW     .D2T2   *+SP(12),B4       ; |128| 

           ADD     .L2     B7,B16,B7         ; |130| 
||         ADD     .S2X    B5,A5,B5          ; |130| 

           ADD     .L2     B5,B7,B7          ; |130| 
           STDW    .D1T2   B7:B6,*A14        ; |130| 
           NOP             1

           SUB     .L1X    B4,1,A0           ; |169| 
||         SUB     .L2     B4,1,B4           ; |169| 

           STW     .D2T2   B4,*+SP(12)       ; |130| 
|| [ A0]   MV      .L1     A12,A4            ; |171| 
|| [ A0]   MV      .L2     B12,B4            ; |171| 
|| [ A0]   B       .S1     $C$L10            ; |169| 
|| [!A0]   LDDW    .D1T1   *A14,A5:A4        ; |135| 

   [ A0]   CALL    .S1     gimme_random      ; |171| 
   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L10}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL29,B3,1      ; |135| 
$C$RL29:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A11
           SET     .S1     A11,0x1a,0x1d,A11
           MPYSP   .M1     A11,A4,A3         ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           ZERO    .L1     A12               ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL30:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           LDDW    .D2T2   *+SP(24),B7:B6
           MV      .L2X    A14,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 
           SUBAW   .D2     B4,6,B12
           MV      .L2X    A12,B5            ; |114| 

           STDW    .D2T2   B7:B6,*B12        ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVKL    .S1     input,A14

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVKH    .S1     input,A14

           LDW     .D1T1   *A14,A3           ; |183| 
           MVK     .S2     0x80,B31
           STW     .D2T2   B31,*+SP(12)      ; |117| 
           NOP             2

           CALL    .S1     cosf              ; |183| 
||         ADD     .L1     A12,A3,A3         ; |183| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A4            ; |183| 
           ADDKPC  .S2     $C$RL31,B3,3      ; |183| 
$C$RL31:   ; CALL OCCURS {cosf} {0}          ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |183| 
           NOP             4

           ADD     .L1X    A12,B4,A3         ; |183| 
||         LDW     .D2T2   *+SP(12),B4       ; |183| 

           ADD     .L1     4,A12,A12         ; |182| 
           STW     .D1T1   A4,*A3            ; |183| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |182| 
||         SUB     .L2     B4,1,B4           ; |182| 

   [ A0]   BNOP    .S1     $C$L11,4          ; |182| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |183| 
||         STW     .D2T2   B4,*+SP(12)       ; |183| 

   [ A0]   CALL    .S1     cosf              ; |183| 
||         ADD     .L1     A12,A3,A3         ; |183| 

           ; BRANCHCC OCCURS {$C$L11}        ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           LDDW    .D2T2   *B12,B17:B16      ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A4          ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 
||         ADD     .S2     B7,B17,B31        ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         MVKL    .S2     t_stop,B4

           ADD     .L2     B31,B5,B7         ; |130| 
||         MVKH    .S2     t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL32,B3,0      ; |130| 

$C$RL32:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(24),B5:B4    ; |130| 
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B12(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A15        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           ADD     .L2     B5,B7,B5          ; |117| 
||         MV      .S2     B6,B4             ; |117| 

           STDW    .D2T2   B5:B4,*B13        ; |117| 
           LDW     .D1T1   *A14,A3           ; |191| 
           MVK     .S2     0x80,B30
           STW     .D2T2   B30,*+SP(12)      ; |117| 
           NOP             2

           CALL    .S1     cossp             ; |191| 
||         ADD     .L1     A12,A3,A3         ; |191| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A4            ; |191| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |191| 
$C$RL34:   ; CALL OCCURS {cossp} {0}         ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *B11,B4           ; |191| 
           NOP             4

           ADD     .L1X    A12,B4,A3         ; |191| 
||         LDW     .D2T2   *+SP(12),B4       ; |191| 

           ADD     .L1     4,A12,A12         ; |190| 
           STW     .D1T1   A4,*A3            ; |191| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |190| 
||         SUB     .L2     B4,1,B4           ; |190| 

   [ A0]   BNOP    .S1     $C$L12,4          ; |190| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |191| 
||         STW     .D2T2   B4,*+SP(12)       ; |191| 

   [ A0]   CALL    .S1     cossp             ; |191| 
||         ADD     .L1     A12,A3,A3         ; |191| 

           ; BRANCHCC OCCURS {$C$L12}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MV      .L2     B13,B5            ; |128| 
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           LDDW    .D2T2   *B5,B7:B6         ; |130| 
           MV      .L2     B12,B11           ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 

           ADD     .L1X    A7,B7,A31         ; |130| 
||         LDDW    .D2T2   *+B11(8),B7:B6    ; |130| 
||         MV      .S1     A6,A3             ; |130| 

           NOP             1

           SUBU    .L2X    B8,A3,B5:B4       ; |130| 
||         ADD     .L1     A31,A5,A3         ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         SUB     .L2X    B9,A3,B31         ; |130| 

           ADDU    .L2     B6,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B6        ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         MVKL    .S2     t_stop,B6

           MVKH    .S2     t_stop,B6

           STDW    .D2T2   B9:B8,*B6         ; |128| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL35,B3,0      ; |130| 

$C$RL35:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           LDDW    .D2T2   *+SP(24),B5:B4
           ADDAD   .D2     B11,1,B12
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B11(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 

           SUBU    .L2     B4,B8,B5:B4       ; |117| 
||         MVKL    .S2     t_offset,B29

           EXT     .S2     B5,24,24,B7       ; |117| 
||         SUB     .L2     B6,B9,B30         ; |117| 

           ADD     .L2     B30,B7,B7         ; |117| 
||         MV      .D2     B4,B6             ; |117| 
||         MVKH    .S2     t_offset,B29

           STDW    .D2T2   B7:B6,*B29        ; |117| 
           LDW     .D1T1   *A14,A3           ; |199| 
           MVK     .S2     0x80,B28
           LDW     .D2T2   *+SP(16),B13      ; |117| 
           STW     .D2T2   B28,*+SP(12)      ; |117| 
           NOP             1

           CALL    .S1     cossp_c           ; |199| 
||         ADD     .L1     A12,A3,A3         ; |199| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A4            ; |199| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |199| 
$C$RL37:   ; CALL OCCURS {cossp_c} {0}       ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *B13,B4           ; |199| 
           NOP             4

           ADD     .L1X    A12,B4,A3         ; |199| 
||         LDW     .D2T2   *+SP(12),B4       ; |199| 

           ADD     .L1     4,A12,A12         ; |198| 
           STW     .D1T1   A4,*A3            ; |199| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |198| 
||         SUB     .L2     B4,1,B4           ; |198| 

   [ A0]   BNOP    .S1     $C$L13,4          ; |198| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |199| 
||         STW     .D2T2   B4,*+SP(12)       ; |199| 

   [ A0]   CALL    .S1     cossp_c           ; |199| 
||         ADD     .L1     A12,A3,A3         ; |199| 

           ; BRANCHCC OCCURS {$C$L13}        ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     t_offset,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           MVKH    .S2     t_offset,B4
           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           LDDW    .D2T2   *+B11(16),B17:B16 ; |130| 
           MV      .L2     B5,B9             ; |128| 
           NOP             2
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B4          ; |130| 
||         SUBU    .L2     B8,B4,B7:B6       ; |130| 

           ADD     .L2X    B4,A5,B4          ; |130| 
||         MV      .S2     B6,B5             ; |130| 
||         CALL    .S1     __c6xabi_fltllif  ; |130| 

           SUB     .D2     B9,B4,B4          ; |130| 
||         ADDU    .L2     B16,B5,B7:B6      ; |130| 
||         EXT     .S2     B7,24,24,B5       ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B7,B17,B4         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     t_stop,B4

           MVKH    .S2     t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL38,B3,0      ; |130| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 107
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(24),B5:B4
           ADDAD   .D2     B12,1,B13
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B11(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A15        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     t_offset,A3
           MVKL    .S1     output,A12

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKH    .S1     t_offset,A3

           MVKH    .S1     output,A12
||         MV      .L2X    A14,B9            ; |206| 
||         SUB     .D2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         LDW     .D1T2   *+A12(16),B4      ; |206| 
||         LDW     .D2T1   *B9,A4            ; |206| 
||         MV      .S2X    A3,B11            ; |117| 

           CALLP   .S2     cossp_v,B3
||         STDW    .D2T2   B7:B6,*B11        ; |117| 
||         MVK     .S1     0x80,A6           ; |206| 

$C$RL40:   ; CALL OCCURS {cossp_v} {0}       ; |206| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S1     16,A14
           ADD     .L1X    B13,A14,A14
           LDDW    .D1T1   *A14,A17:A16      ; |130| 
           MVKL    .S1     t_stop,A3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           MVKH    .S1     t_stop,A3
||         SUBU    .L1X    B8,A4,A9:A8       ; |130| 

           ADD     .L1X    A5,B7,A4          ; |130| 
||         MV      .L2     B4,B9             ; |128| 

           ADD     .L1     A4,A7,A4          ; |130| 
||         MV      .L2X    A3,B4             ; |128| 
||         MV      .D1     A8,A3             ; |130| 
||         EXT     .S1     A9,24,24,A6       ; |130| 

           SUB     .S1X    B9,A4,A3          ; |130| 
||         ADDU    .L1     A16,A3,A5:A4      ; |130| 

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A3,A6,A5          ; |130| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL41:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           MPYSP   .M1     A11,A4,A3         ; |130| 
           MV      .L1     A13,A5            ; |130| 
           ZERO    .L1     A4                ; |130| 
           NOP             2
           SPDP    .S1     A3,A7:A6          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |130| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6

           STDW    .D1T1   A5:A4,*A14        ; |130| 
||         MVKH    .S2     0x3f2a36e2,B7

           LDW     .D1T2   *+A12(4),B4       ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL43:   ; CALL OCCURS {isequal} {0}       ; |66| 

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xeb1c432d,B6

           MVKH    .S1     fcn_pass,A3
||         MVKL    .S2     0x3f2a36e2,B7

           MVKH    .S2     0xeb1c432d,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A12,A4           ; |67| 
||         MV      .L2X    A3,B11            ; |66| 
||         MVKH    .S2     0x3f2a36e2,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A12(8),B4       ; |67| 
||         STW     .D2T1   A5,*+B11(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f2a36e2,B7

           STW     .D2T1   A4,*+B11(8)       ; |67| 
||         LDW     .D1T2   *+A12(12),B4      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3f2a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f2a36e2,B7

           STW     .D2T1   A4,*+B11(12)      ; |68| 
||         LDW     .D1T2   *A10,B4           ; |69| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(20),B4       ; |69| 
           STW     .D2T1   A4,*+B11(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           NOP             4

   [!B0]   BNOP    .S1     $C$L14,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B10,B0           ; |72| 

   [ B1]   ADD     .L2     4,B10,B4
           ; BRANCHCC OCCURS {$C$L14}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L15            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |212| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L15}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |212| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           ZERO    .L1     A3                ; |72| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |212| 
||         ADDKPC  .S2     $C$RL47,B3,0      ; |212| 

$C$RL47:   ; CALL OCCURS {print_test_results} {0}  ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |213| 

$C$RL48:   ; CALL OCCURS {printf} {0}        ; |213| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |213| 

$C$RL49:   ; CALL OCCURS {printf} {0}        ; |213| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |220| 

$C$RL50:   ; CALL OCCURS {print_profile_results} {0}  ; |220| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |223| 

$C$RL51:   ; CALL OCCURS {print_memory_results} {0}  ; |223| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(40),B3      ; |224| 
           LDDW    .D2T1   *++SP,A13:A12     ; |224| 
           LDDW    .D2T1   *++SP,A15:A14     ; |224| 
           LDDW    .D2T2   *++SP,B11:B10     ; |224| 
           LDDW    .D2T2   *++SP,B13:B12     ; |224| 

           LDW     .D2T1   *++SP(8),A10      ; |224| 
||         RET     .S2     B3                ; |224| 

           LDW     .D2T1   *++SP(8),A11      ; |224| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |224| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"cosSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	cos
	.global	cosf
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	cossp
	.global	cossp_c
	.global	cossp_v
	.global	t_start
	.global	t_stop
	.global	t_offset
	.global	cycle_counts
	.global	fcn_pass
	.global	all_pass
	.global	a_ext
	.global	a_sc
	.global	output
	.global	input
	.global	__c6xabi_fltllif
	.global	__c6xabi_fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_Long_Precision_Bits(2)
	.battr "TI", Tag_File, 1, Tag_Bitfield_layout(2)
	.battr "TI", Tag_File, 1, Tag_ABI_enum_size(3)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_wchar_t(1)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_array_object_alignment(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_array_object_align_expected(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_PIC(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_PID(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_DSBT(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
