;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 23:03:07 2013                                *
;******************************************************************************
	.compiler_opts --abi=coffabi --c64p_l1d_workaround=off --endian=little --hll_source=on --long_precision_bits=40 --mem_model:code=near --mem_model:const=data --mem_model:data=far --object_format=coff --silicon_version=6600 --symdebug:none 

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

;*****************************************************************************
;* CINIT RECORDS                                                             *
;*****************************************************************************
	.sect	".cinit"
	.align	8
	.field  	$C$IR_1,32
	.field  	_a+0,32
	.word	095a29414h,0408edcdbh		; _a[0] @ 0
	.word	061e77ba5h,04076a092h		; _a[1] @ 64
	.word	0ab72dff1h,040728016h		; _a[2] @ 128
	.word	0f59bf8efh,04063cf4eh		; _a[3] @ 192
	.word	0355f5d5eh,0408c4ef0h		; _a[4] @ 256
	.word	09acf23bfh,040867644h		; _a[5] @ 320
	.word	0244e93e2h,0408181a8h		; _a[6] @ 384
	.word	0018bf13ah,040809528h		; _a[7] @ 448
	.word	08806ca1fh,04067b738h		; _a[8] @ 512
	.word	05fdb31eah,040856c97h		; _a[9] @ 576
$C$IR_1:	.set	80

	.global	_a
_a:	.usect	".far",80,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\148884 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\148886 
	.sect	".text"
	.clink
	.global	_main

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
;*   Local Frame Size  : 8 Args + 44 Auto + 56 Save = 108 byte                *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |89| 
           STW     .D2T1   A10,*SP--(8)      ; |89| 
           STDW    .D2T2   B13:B12,*SP--     ; |89| 
           STDW    .D2T2   B11:B10,*SP--     ; |89| 
           STDW    .D2T1   A15:A14,*SP--     ; |89| 

           STDW    .D2T1   A13:A12,*SP--     ; |89| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(64)      ; |89| 
||         CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |97| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     _a,A14
||         MVKL    .S2     _output,B4

           MVKH    .S1     _a,A14
||         MVKH    .S2     _output,B4

           MV      .L1     A14,A12
||         CALL    .S1     _sqrt             ; |106| 
||         LDW     .D2T1   *B4,A11

           LDDW    .D1T1   *A12++,A5:A4      ; |106| 
           MVK     .L2     0xa,B4
           NOP             1
           MV      .L1X    B4,A10
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL1,B3,0       ; |106| 
$C$RL1:    ; CALL OCCURS {_sqrt} {0}         ; |106| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |105| 
||         STDW    .D1T1   A5:A4,*A11++      ; |106| 
||         SUB     .S1     A10,1,A10         ; |105| 

   [!A0]   MVKL    .S2     _output,B4
|| [!A0]   ZERO    .L2     B10
|| [!A0]   MV      .L1     A14,A10
|| [ A0]   B       .S1     $C$L1             ; |105| 

   [ A0]   CALL    .S1     _sqrt             ; |106| 
   [ A0]   LDDW    .D1T1   *A12++,A5:A4      ; |106| 
   [!A0]   MVK     .L1     0xa,A11
   [!A0]   MVKH    .S2     _output,B4
   [!A0]   ADD     .L2     4,B4,B11
           ; BRANCHCC OCCURS {$C$L1}         ; |105| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _sqrtdp           ; |109| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |109| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |109| 
$C$RL2:    ; CALL OCCURS {_sqrtdp} {0}       ; |109| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |109| 
||         SUB     .L1     A11,1,A0          ; |108| 
||         SUB     .S1     A11,1,A11         ; |108| 

   [ A0]   BNOP    .S1     $C$L2,3           ; |108| 
|| [!A0]   MVK     .L1     0xa,A11
|| [!A0]   ADD     .L2     4,B11,B11
|| [!A0]   MV      .D1     A14,A10

           ADD     .L2     B10,B4,B4         ; |109| 
||         ADD     .S2     8,B10,B10         ; |108| 

   [ A0]   CALL    .S1     _sqrtdp           ; |109| 
|| [!A0]   ZERO    .L2     B10
||         STDW    .D2T1   A5:A4,*B4         ; |109| 

           ; BRANCHCC OCCURS {$C$L2}         ; |108| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _sqrtdp_c         ; |112| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |112| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |112| 
$C$RL3:    ; CALL OCCURS {_sqrtdp_c} {0}     ; |112| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |112| 
||         SUB     .L1     A11,1,A0          ; |111| 
||         SUB     .S1     A11,1,A11         ; |111| 

   [ A0]   BNOP    .S1     $C$L3,3           ; |111| 

           ADD     .L2     B10,B4,B4         ; |112| 
||         ADD     .S2     8,B10,B10         ; |111| 

   [ A0]   CALL    .S1     _sqrtdp_c         ; |112| 
||         STDW    .D2T1   A5:A4,*B4         ; |112| 

           ; BRANCHCC OCCURS {$C$L3}         ; |111| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           ADD     .L1X    4,B11,A15
||         SUB     .S1     A14,8,A6
||         ZERO    .D1     A7                ; |70| 
||         MVK     .L2     0xa,B1            ; |114| 

           LDW     .D1T1   *A15,A3
||         ZERO    .L1     A10               ; |70| 
||         MVK     .S1     0xffffffff,A12    ; |77| 

;** --------------------------------------------------------------------------*
;**   BEGIN LOOP $C$L4
;** --------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 7

           ZERO    .L1     A11
||         MVK     .L2     0x3,B0            ; |69| 
||         LDDW    .D1T1   *++A6,A17:A16     ; |115| 

           ZERO    .L1     A4
           SET     .S1     A4,0x13,0x1d,A4
           SET     .S1     A11,0x15,0x1d,A11
           STW     .D2T1   A4,*+SP(36)       ; |70| 
           RSQRDP  .S1     A17:A16,A5:A4     ; |66| 
           STW     .D2T1   A7,*+SP(32)       ; |66| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/sqrtdp/sqrtdp_d.c
;*      Loop inlined from                : ../../../../../../../ti/mathlib/src/sqrtdp/c66/sqrtdp_i.h
;*      Loop source line                 : 69
;*      Loop opening brace source line   : 69
;*      Loop closing brace source line   : 71
;*      Known Minimum Trip Count         : 3                    
;*      Known Maximum Trip Count         : 3                    
;*      Known Max Trip Count Factor      : 3
;*      Loop Carried Dependency Bound(^) : 22
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 2
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     0        0     
;*      .D units                     0        0     
;*      .M units                     2*       2*    
;*      .X cross paths               1        1     
;*      .T address paths             0        0     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           1        1     (.L or .S unit)
;*      Addition ops (.LSD)          0        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        1     
;*      Bound(.L .S .D .LS .LSD)     1        1     
;*
;*      Disqualified loop: Loop carried dependency bound too large
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 19
           FMPYDP  .M1     A5:A4,A17:A16,A9:A8 ; |70| 
           LDDW    .D2T1   *+SP(32),A19:A18
           SUB     .L2     B0,1,B0           ; |69| 
           NOP             1
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |70| 
           NOP             3
           FMPYDP  .M1     A11:A10,A9:A8,A9:A8 ; |70| 
           NOP             3
           FSUBDP  .L1     A19:A18,A9:A8,A9:A8 ; |70| 
   [ B0]   BNOP    .S1     $C$L5,1           ; |69| 
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |70| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L5}         ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .S2     B1,1,B1           ; |114| 
||         FMPYDP  .M1     A5:A4,A17:A16,A5:A4 ; |72| 
||         ZERO    .L2     B5:B4             ; |74| 
||         MVKL    .S1     0x7fefffff,A13

   [ B1]   B       .S1     $C$L4             ; |114| 
||         CMPGTDP .S2X    A17:A16,B5:B4,B0  ; |74| 

           MVKH    .S1     0x7fefffff,A13
           CMPGTDP .S1     A17:A16,A13:A12,A0 ; |77| 
   [!B0]   ZERO    .L1     A5:A4             ; |75| 

   [ A0]   MV      .L1     A13,A5            ; |78| 
|| [ A0]   MV      .D1     A12,A4            ; |75| 
|| [!B1]   MVKL    .S1     _output,A10

           STDW    .D1T1   A5:A4,*A3++       ; |115| 
|| [!B1]   MVKH    .S1     _output,A10
|| [!B1]   CALL    .S2     _sqrtdp_v         ; |117| 

           ; BRANCHCC OCCURS {$C$L4}         ; |114| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *+A10(16),B4      ; |117| 
           MV      .L1     A14,A4            ; |117| 
           MVK     .L1     0xa,A6            ; |117| 
           ADDKPC  .S2     $C$RL4,B3,1       ; |117| 
$C$RL4:    ; CALL OCCURS {_sqrtdp_v} {0}     ; |117| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     0x3d3c25c2,B7

           LDW     .D1T1   *A10,A4           ; |66| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0x68497682,B6
           MVKL    .S2     0x3d3c25c2,B7
           MVKH    .S2     _fcn_pass,B4
           MVKH    .S2     0x68497682,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVKH    .S2     0x3d3c25c2,B7

           CALLP   .S2     _isequal,B3
||         STW     .D2T1   A3,*+B4(4)        ; |66| 
||         LDW     .D1T2   *+A10(8),B4       ; |67| 
||         MVK     .L1     0xa,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0x68497682,B6
           MVKL    .S2     0x3d3c25c2,B7
           MVKH    .S2     _fcn_pass,B4
           MVKH    .S2     0x68497682,B6

           MV      .L1     A10,A3            ; |67| 
||         STW     .D2T1   A4,*+B4(8)        ; |67| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0x3d3c25c2,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x68497682,B6
           MVKL    .S2     _fcn_pass,B5

           ADD     .L2X    4,A15,B4
||         MVKL    .S2     0x3d3c25c2,B7

           MVKH    .S2     _fcn_pass,B5
||         STW     .D2T2   B4,*+SP(16)

           STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0x68497682,B6

           MV      .L2X    A10,B5            ; |69| 
||         LDW     .D2T2   *B4,B4            ; |69| 
||         MVKH    .S2     0x3d3c25c2,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .L1     0xa,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S1     _fcn_pass,A3
           MVKH    .S1     _fcn_pass,A3
           NOP             1
           ADD     .L2X    4,A3,B11
           LDW     .D2T2   *B11,B0           ; |72| 
           ADD     .L2X    8,A3,B10
           MV      .L2X    A3,B4             ; |72| 
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           NOP             1

   [!B0]   B       .S2     $C$L6             ; |72| 
|| [!B0]   MVKL    .S1     _all_pass,A3
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [!B0]   ZERO    .D2     B4                ; |72| 

   [!B0]   CALL    .S2     _print_test_results ; |121| 
|| [!B0]   MVKH    .S1     _all_pass,A3
|| [ B0]   LDW     .D2T2   *B10,B0           ; |72| 

   [ B1]   ADD     .L2     4,B10,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L6}         ; |72| 
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
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   ZERO    .L2     B4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |121| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |121| 
||         STW     .D1T2   B4,*A3            ; |72| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |121| 

$C$RL9:    ; CALL OCCURS {_print_test_results} {0}  ; |121| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S2     _a_sc,B4
||         MV      .L2X    A12,B7            ; |129| 
||         MVK     .D2     0x8,B31           ; |137| 

           ZERO    .L1     A5
||         MVKH    .S2     _a_sc,B4
||         MV      .L2X    A12,B6            ; |129| 
||         STW     .D2T2   B31,*+SP(12)      ; |129| 

           MVKH    .S1     0x80000000,A5
||         ZERO    .L2     B13
||         STDW    .D2T2   B7:B6,*+B4(56)    ; |135| 
||         ZERO    .L1     A4                ; |129| 

           ZERO    .L1     A7
||         MVKH    .S2     0xbff00000,B13
||         ZERO    .L2     B12               ; |133| 
||         STDW    .D2T1   A5:A4,*+B4(8)     ; |129| 

           ZERO    .L2     B9
||         SET     .S1     A7,0x14,0x1d,A7
||         ZERO    .L1     A6                ; |132| 
||         STDW    .D2T2   B13:B12,*+B4(40)  ; |133| 

           MVKH    .S2     0xfff00000,B9
||         ZERO    .L2     B8                ; |131| 
||         STDW    .D2T1   A7:A6,*+B4(32)    ; |132| 

           ADD     .L1     -1,A5,A9
||         MV      .S1     A12,A8
||         STDW    .D2T2   B9:B8,*+B4(24)    ; |131| 

           STDW    .D2T1   A9:A8,*+B4(48)    ; |134| 
||         ADD     .L1     1,A13,A9
||         ZERO    .S1     A8                ; |130| 

           ZERO    .L2     B7:B6             ; |128| 
||         STDW    .D2T1   A9:A8,*+B4(16)    ; |130| 

           SUB     .L1X    B4,8,A12
||         STDW    .D2T2   B7:B6,*B4         ; |128| 
||         CALL    .S1     _sqrt             ; |138| 

           LDDW    .D1T1   *++A12,A5:A4      ; |138| 
           ZERO    .L1     A10               ; |70| 
           ZERO    .L1     A14
           NOP             1
;** --------------------------------------------------------------------------*
;**   BEGIN LOOP $C$L7
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL10,B3,0      ; |138| 
$C$RL10:   ; CALL OCCURS {_sqrt} {0}         ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |138| 
           ZERO    .L1     A7:A6             ; |139| 
           NOP             3
           ADD     .L1X    A14,B4,A3         ; |138| 
           STDW    .D1T1   A5:A4,*A3         ; |138| 
           LDDW    .D1T1   *A12,A5:A4        ; |139| 
           NOP             4
           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |139| 
           NOP             1
   [!A0]   B       .S1     $C$L8             ; |139| 
   [ A0]   CALL    .S1     _sqrtdp           ; |139| 
   [!A0]   CALL    .S1     _sqrt             ; |139| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L8}         ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL11,B3,0      ; |139| 
$C$RL11:   ; CALL OCCURS {_sqrtdp} {0}       ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L9             ; |139| 
||         MVKL    .S2     _output,B12

           MVKH    .S2     _output,B12
           LDW     .D2T2   *+B12(4),B6       ; |139| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |139| 
           NOP             2
           ; BRANCH OCCURS {$C$L9}           ; |139| 
;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL12,B3,1      ; |139| 
$C$RL12:   ; CALL OCCURS {_sqrt} {0}         ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           MVKL    .S2     _output,B12
           MVKH    .S2     _output,B12
           LDW     .D2T2   *+B12(4),B6       ; |139| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |139| 
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             1
           ADD     .L2X    A14,B6,B6         ; |139| 

           STDW    .D2T2   B5:B4,*B6         ; |139| 
||         CALL    .S1     _sqrtdp_c         ; |140| 

           LDDW    .D1T1   *A12,A5:A4        ; |140| 
           ADDKPC  .S2     $C$RL13,B3,3      ; |140| 
$C$RL13:   ; CALL OCCURS {_sqrtdp_c} {0}     ; |140| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           LDW     .D2T2   *+B12(8),B4       ; |140| 
           LDW     .D2T1   *+SP(36),A31
           ZERO    .L1     A30               ; |70| 
           STW     .D2T1   A30,*+SP(40)      ; |66| 
           MVK     .L2     0x3,B0            ; |69| 
           ADD     .L1X    A14,B4,A3         ; |140| 
           STDW    .D1T1   A5:A4,*A3         ; |140| 
           LDDW    .D1T1   *A12,A9:A8        ; |141| 
           STW     .D2T1   A31,*+SP(44)      ; |70| 
           NOP             3
           RSQRDP  .S1     A9:A8,A7:A6       ; |66| 
           NOP             1
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/sqrtdp/sqrtdp_d.c
;*      Loop inlined from                : ../../../../../../../ti/mathlib/src/sqrtdp/c66/sqrtdp_i.h
;*      Loop source line                 : 69
;*      Loop opening brace source line   : 69
;*      Loop closing brace source line   : 71
;*      Known Minimum Trip Count         : 3                    
;*      Known Maximum Trip Count         : 3                    
;*      Known Max Trip Count Factor      : 3
;*      Loop Carried Dependency Bound(^) : 22
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 2
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     0        0     
;*      .D units                     0        0     
;*      .M units                     2*       2*    
;*      .X cross paths               1        1     
;*      .T address paths             0        0     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           1        1     (.L or .S unit)
;*      Addition ops (.LSD)          0        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        1     
;*      Bound(.L .S .D .LS .LSD)     1        1     
;*
;*      Disqualified loop: Loop carried dependency bound too large
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 19
           FMPYDP  .M1     A7:A6,A9:A8,A5:A4 ; |70| 
           LDDW    .D2T1   *+SP(40),A17:A16
           SUB     .L2     B0,1,B0           ; |69| 
   [!B0]   ZERO    .L2     B5:B4             ; |74| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |70| 
           NOP             3
           FMPYDP  .M1     A11:A10,A5:A4,A5:A4 ; |70| 
           NOP             3
           FSUBDP  .L1     A17:A16,A5:A4,A5:A4 ; |70| 
   [ B0]   BNOP    .S1     $C$L10,1          ; |69| 
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |70| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L10}        ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CMPGTDP .S2X    A9:A8,B5:B4,B0    ; |74| 
||         LDW     .D2T2   *+SP(12),B4       ; |78| 
||         FMPYDP  .M1     A7:A6,A9:A8,A5:A4 ; |72| 
||         LDW     .D1T1   *A15,A3           ; |141| 

           MVK     .L1     0xffffffff,A6     ; |77| 
           MV      .L1     A13,A7            ; |77| 
           CMPGTDP .S1     A9:A8,A7:A6,A0    ; |77| 
   [!B0]   ZERO    .L1     A5:A4             ; |75| 

   [ A0]   MV      .L1     A7,A5             ; |78| 
|| [ A0]   MV      .S1     A6,A4             ; |75| 
||         SUB     .D1X    B4,1,A0           ; |137| 
||         SUB     .L2     B4,1,B4           ; |137| 

   [ A0]   B       .S1     $C$L7             ; |137| 
||         ADD     .L1     A14,A3,A3         ; |141| 
||         STW     .D2T2   B4,*+SP(12)       ; |141| 

   [ A0]   CALL    .S1     _sqrt             ; |138| 
||         STDW    .D1T1   A5:A4,*A3         ; |141| 

   [!A0]   CALL    .S1     _sqrtdp_v         ; |143| 
|| [ A0]   LDDW    .D1T1   *++A12,A5:A4      ; |138| 

   [!A0]   LDW     .D2T2   *+B12(16),B4      ; |143| 
           ADD     .L1     8,A14,A14         ; |137| 
   [!A0]   MVKL    .S1     _a_sc,A4
           ; BRANCHCC OCCURS {$C$L7}         ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVK     .L1     0x8,A6            ; |143| 

           ADDKPC  .S2     $C$RL14,B3,0      ; |143| 
||         MVKH    .S1     _a_sc,A4

$C$RL14:   ; CALL OCCURS {_sqrtdp_v} {0}     ; |143| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     0x3d3c25c2,B7

           LDW     .D2T1   *B12,A4           ; |66| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MVK     .L1     0x8,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL15:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3d3c25c2,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3d3c25c2,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0x68497682,B6

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .L1     0x8,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3d3c25c2,B7

           MV      .L1X    B12,A3            ; |143| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .L1     0x8,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |68| 

           LDW     .D2T1   *+SP(16),A3       ; |68| 
||         MVKL    .S2     _fcn_pass,B4

           MVKL    .S2     0x68497682,B6
           MVKL    .S2     0x3d3c25c2,B7
           MVKH    .S2     _fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x68497682,B6

           STW     .D2T1   A3,*+SP(20)       ; |68| 
||         MVKH    .S2     0x3d3c25c2,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B12,A4           ; |69| 
||         MVK     .L1     0x8,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL18:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MV      .L1X    B11,A10           ; |69| 
           LDW     .D1T1   *A10,A0           ; |72| 
           MVKL    .S2     _fcn_pass,B4
           MVKH    .S2     _fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           NOP             1

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B10,B0           ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |147| 
   [ A0]   ADD     .L2     4,B10,B4
   [!A0]   MVKL    .S2     _all_pass,B5
   [!A0]   ZERO    .L2     B4                ; |72| 
   [!A0]   MVKH    .S2     _all_pass,B5
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
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
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   ZERO    .L2     B4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |147| 
           MVKL    .S2     _all_pass,B5
           MVKH    .S2     _all_pass,B5
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x3,A4            ; |147| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL19,B3,0      ; |147| 

$C$RL19:   ; CALL OCCURS {_print_test_results} {0}  ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           MVKL    .S1     _a_ext,A3
           MVKH    .S1     _a_ext,A3

           MVK     .S2     0x777,B31         ; |151| 
||         ZERO    .L1     A5

           MV      .L2X    A3,B4             ; |150| 
||         STW     .D2T2   B31,*+SP(12)      ; |150| 
||         SET     .S1     A5,0x14,0x14,A5
||         ZERO    .L1     A4                ; |150| 

           CALL    .S1     _sqrt             ; |152| 
||         STDW    .D2T1   A5:A4,*B4         ; |150| 
||         MV      .L1     A3,A12            ; |150| 
||         ZERO    .D1     A14               ; |150| 

;** --------------------------------------------------------------------------*
;**   BEGIN LOOP $C$L12
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A12,A5:A4        ; |152| 
           ADDKPC  .S2     $C$RL20,B3,3      ; |152| 
$C$RL20:   ; CALL OCCURS {_sqrt} {0}         ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           MV      .L2     B12,B4            ; |152| 
           LDW     .D2T2   *B4,B4            ; |152| 
           ZERO    .L1     A7:A6             ; |153| 
           NOP             3
           ADD     .L1X    A14,B4,A3         ; |152| 
           STDW    .D1T1   A5:A4,*A3         ; |152| 
           LDDW    .D1T1   *A12,A5:A4        ; |153| 
           NOP             4
           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |153| 
           NOP             1
   [!A0]   B       .S1     $C$L13            ; |153| 
   [ A0]   CALL    .S1     _sqrtdp           ; |153| 
   [!A0]   CALL    .S1     _sqrt             ; |153| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L13}        ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL21,B3,0      ; |153| 
$C$RL21:   ; CALL OCCURS {_sqrtdp} {0}       ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           BNOP    .S1     $C$L14,4          ; |153| 
||         LDW     .D2T2   *+B12(4),B6       ; |153| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |153| 

           ADD     .L2X    A14,B6,B6         ; |153| 
           ; BRANCH OCCURS {$C$L14}          ; |153| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL22,B3,1      ; |153| 
$C$RL22:   ; CALL OCCURS {_sqrt} {0}         ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           LDW     .D2T2   *+B12(4),B6       ; |153| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |153| 
           NOP             3
           ADD     .L2X    A14,B6,B6         ; |153| 
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     _sqrtdp_c         ; |154| 
||         STDW    .D2T2   B5:B4,*B6         ; |153| 

           LDDW    .D1T1   *A12,A5:A4        ; |154| 
           ADDKPC  .S2     $C$RL23,B3,3      ; |154| 
$C$RL23:   ; CALL OCCURS {_sqrtdp_c} {0}     ; |154| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           LDW     .D2T2   *+B12(8),B4       ; |154| 
           LDW     .D2T1   *+SP(44),A17
           MVK     .L2     0x3,B0            ; |69| 
           ZERO    .L1     A16               ; |70| 
           MV      .L1     A11,A19           ; |70| 
           ADD     .L1X    A14,B4,A3         ; |154| 
           STDW    .D1T1   A5:A4,*A3         ; |154| 
           LDDW    .D1T1   *A12,A5:A4        ; |155| 
           ZERO    .L1     A18               ; |70| 
           NOP             3
           RSQRDP  .S1     A5:A4,A7:A6       ; |66| 
           NOP             2
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/sqrtdp/sqrtdp_d.c
;*      Loop inlined from                : ../../../../../../../ti/mathlib/src/sqrtdp/c66/sqrtdp_i.h
;*      Loop source line                 : 69
;*      Loop opening brace source line   : 69
;*      Loop closing brace source line   : 71
;*      Known Minimum Trip Count         : 3                    
;*      Known Maximum Trip Count         : 3                    
;*      Known Max Trip Count Factor      : 3
;*      Loop Carried Dependency Bound(^) : 22
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 2
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     0        0     
;*      .D units                     0        0     
;*      .M units                     2*       2*    
;*      .X cross paths               1        1     
;*      .T address paths             0        0     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           1        1     (.L or .S unit)
;*      Addition ops (.LSD)          0        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        1     
;*      Bound(.L .S .D .LS .LSD)     1        1     
;*
;*      Disqualified loop: Loop carried dependency bound too large
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 19
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |70| 
           SUB     .L2     B0,1,B0           ; |69| 
   [!B0]   STW     .D2T1   A13,*+SP(52)      ; |77| 
   [!B0]   MVK     .L1     0xffffffff,A31    ; |77| 
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |70| 
   [!B0]   STW     .D2T1   A31,*+SP(48)      ; |74| 
           NOP             2
           FMPYDP  .M1     A19:A18,A9:A8,A9:A8 ; |70| 
           NOP             3
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |70| 
   [ B0]   BNOP    .S1     $C$L15,1          ; |69| 

           FMPYDP  .M1     A9:A8,A7:A6,A7:A6 ; |70| 
|| [!B0]   LDDW    .D2T1   *+SP(48),A9:A8    ; |74| 

           NOP             3
           ; BRANCHCC OCCURS {$C$L15}        ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20

           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |72| 
||         ZERO    .L2     B5:B4             ; |74| 
||         MV      .L1     A15,A3            ; |78| 

           CMPGTDP .S1     A5:A4,A9:A8,A0    ; |77| 
||         CMPGTDP .S2X    A5:A4,B5:B4,B0    ; |74| 

           LDW     .D2T2   *+SP(12),B4
           LDW     .D1T1   *A3,A16           ; |155| 

   [!B0]   ZERO    .L1     A7:A6             ; |75| 
|| [ A0]   LDW     .D2T1   *+SP(52),A7       ; |78| 

   [ A0]   MV      .L1     A31,A6            ; |75| 
           STW     .D2T1   A15,*+SP(24)      ; |78| 
           SUB     .L1X    B4,1,A2           ; |151| 
           ADD     .L1     A14,A16,A30       ; |155| 

           STDW    .D1T1   A7:A6,*A30        ; |155| 
||         MVKL    .S1     0xcccccccd,A6

           LDDW    .D1T1   *A12,A5:A4        ; |156| 
           MVKL    .S1     0xc000cccc,A7
           MVKH    .S1     0xcccccccd,A6
           MVKH    .S1     0xc000cccc,A7
   [ A2]   B       .S1     $C$L12            ; |151| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |156| 
           ADD     .L1     8,A14,A14         ; |151| 
           SUB     .L2     B4,1,B31          ; |151| 
           NOP             1

   [ A2]   CALL    .S1     _sqrt             ; |152| 
||         STDW    .D1T1   A5:A4,*++A12      ; |156| 
||         STW     .D2T2   B31,*+SP(12)      ; |156| 

           ; BRANCHCC OCCURS {$C$L12}        ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     _sqrtdp_v         ; |158| 
           LDW     .D2T2   *+B12(16),B4      ; |158| 
           MVKL    .S1     _a_ext,A4
           MVKH    .S1     _a_ext,A4
           ADDKPC  .S2     $C$RL24,B3,0      ; |158| 
           MVK     .S1     0x777,A6          ; |158| 
$C$RL24:   ; CALL OCCURS {_sqrtdp_v} {0}     ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T2   *B12,B5           ; |66| 
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     0x3d3c25c2,B7
           MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MV      .L1X    B5,A4             ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .D1     0x1,A8            ; |66| 

$C$RL25:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     _fcn_pass,B5

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0x3d3c25c2,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3d3c25c2,B7

           MV      .L1X    B12,A3            ; |158| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL27:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B4

           LDW     .D2T1   *+SP(20),A3       ; |68| 
||         MVKL    .S2     0x3d3c25c2,B7

           MVKL    .S2     0x68497682,B6
           MVKH    .S2     _fcn_pass,B4
           MVKH    .S2     0x3d3c25c2,B7

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B12,A4           ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL28:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A10,A0           ; |72| 
           MVKL    .S2     _fcn_pass,B4
           MV      .L2     B10,B5            ; |72| 
           MVKH    .S2     _fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 

   [ A0]   ADD     .L2     4,B5,B4
|| [!A0]   B       .S1     $C$L16            ; |72| 
|| [ A0]   LDW     .D2T2   *B5,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |162| 
   [!A0]   MVKL    .S1     _all_pass,A3
   [!A0]   MVKH    .S1     _all_pass,A3
   [!A0]   ZERO    .L2     B4                ; |72| 
   [!A0]   MV      .L2X    A3,B5
           ; BRANCHCC OCCURS {$C$L16}        ; |72| 
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
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   ZERO    .L2     B4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |162| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             1
           MV      .L2X    A3,B5
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x4,A4            ; |162| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL29,B3,0      ; |162| 

$C$RL29:   ; CALL OCCURS {_print_test_results} {0}  ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S2     _cycle_counts+24,B12

           MVKH    .S2     _cycle_counts+24,B12
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .L1     A12               ; |114| 
||         ZERO    .S1     A13               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A13:A12,*B12      ; |114| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S2     _t_start,B4

           MVKH    .S2     _t_start,B4
||         MV      .L2     B5,B9             ; |116| 

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D2T2   B9:B8,*B4         ; |116| 

           MVC     .S2     TSCH,B6           ; |117| 
           MVKL    .S1     _t_offset,A3

           SUBU    .L2     B4,B8,B5:B4       ; |117| 
||         MVK     .S1     0x80,A31          ; |170| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 
||         MVKL    .S1     0x408f4800,A5

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVKH    .S1     _t_offset,A3

           MVKL    .S1     _input,A3
||         STDW    .D1T2   B5:B4,*A3         ; |117| 

           CALL    .S2     _gimme_random     ; |172| 
||         MVKH    .S1     _input,A3
||         STW     .D2T1   A31,*+SP(12)      ; |117| 
||         MV      .L1     A12,A15           ; |170| 

           LDW     .D1T1   *A3,A14           ; |172| 
||         MV      .L2X    A13,B4            ; |172| 
||         MV      .S2     B13,B5            ; |172| 
||         MVKH    .S1     0x408f4800,A5
||         MV      .L1     A12,A4            ; |172| 

;** --------------------------------------------------------------------------*
;**   BEGIN LOOP $C$L17
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL30,B3,3      ; |172| 
$C$RL30:   ; CALL OCCURS {_gimme_random} {0}  ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L1     A14,A15,A3        ; |172| 

           STDW    .D1T1   A5:A4,*A3         ; |172| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A8             ; |122| Define a twin register
||         MVC     .S2     TSCH,B4           ; |122| 

           ADD     .L1     A14,A15,A6        ; |66| 
           LDDW    .D1T1   *A6,A7:A6         ; |66| 
           MVK     .L2     0x3,B0            ; |69| 
           LDW     .D2T1   *+SP(36),A3       ; |66| 
           MV      .L1X    B4,A9             ; |122| 
           MV      .L1     A12,A2            ; |66| 
           RSQRDP  .S1     A7:A6,A7:A6       ; |66| 
           MV      .L1     A12,A10           ; |66| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/sqrtdp/sqrtdp_d.c
;*      Loop inlined from                : ../../../../../../../ti/mathlib/src/sqrtdp/c66/sqrtdp_i.h
;*      Loop source line                 : 69
;*      Loop opening brace source line   : 69
;*      Loop closing brace source line   : 71
;*      Known Minimum Trip Count         : 3                    
;*      Known Maximum Trip Count         : 3                    
;*      Known Max Trip Count Factor      : 3
;*      Loop Carried Dependency Bound(^) : 22
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 2
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     0        0     
;*      .D units                     0        0     
;*      .M units                     2*       2*    
;*      .X cross paths               1        1     
;*      .T address paths             0        0     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           1        1     (.L or .S unit)
;*      Addition ops (.LSD)          0        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        1     
;*      Bound(.L .S .D .LS .LSD)     1        1     
;*
;*      Disqualified loop: Loop carried dependency bound too large
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 19
           FMPYDP  .M1     A7:A6,A5:A4,A17:A16 ; |70| 
           SUB     .L2     B0,1,B0           ; |69| 
           NOP             2
           FMPYDP  .M1     A7:A6,A17:A16,A17:A16 ; |70| 
           NOP             3
           FMPYDP  .M1     A11:A10,A17:A16,A17:A16 ; |70| 
           NOP             3

           FSUBDP  .L1     A3:A2,A17:A16,A17:A16 ; |70| 
|| [!B0]   LDW     .D2T1   *+SP(24),A3

   [ B0]   BNOP    .S1     $C$L18,1          ; |69| 

           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |70| 
|| [!B0]   LDW     .D2T1   *+SP(52),A17

           NOP             3
           ; BRANCHCC OCCURS {$C$L18}        ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24

           LDW     .D1T1   *A3,A18           ; |176| 
||         FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |72| 
||         ZERO    .L2     B5:B4             ; |74| 
||         MVKL    .S1     _t_start,A3
||         MVK     .L1     0xffffffff,A16    ; |77| 

           CMPGTDP .S1     A5:A4,A17:A16,A0  ; |77| 
           CMPGTDP .S2X    A5:A4,B5:B4,B0    ; |74| 
           MVKH    .S1     _t_start,A3
   [!B0]   ZERO    .L1     A7:A6             ; |75| 

   [ A0]   MV      .L1     A17,A7            ; |78| 
||         MV      .L2X    A3,B6             ; |78| 
||         ADD     .S1     A15,A18,A3        ; |176| 
|| [ A0]   MV      .D1     A16,A6            ; |75| 

           STDW    .D1T1   A7:A6,*A3         ; |176| 

           STDW    .D2T1   A9:A8,*B6
||         MVC     .S2     TSCL,B6           ; |128| 

           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S1     _t_offset,A3
||         LDW     .D2T1   *+SP(12),A31      ; |128| 
||         MVKL    .S2     _t_stop,B16
||         ADD     .L1     8,A15,A15         ; |170| 

           MVKH    .S1     _t_offset,A3
           LDDW    .D1T1   *A3,A5:A4         ; |130| 
           MVKH    .S2     _t_stop,B16
           LDDW    .D2T2   *B12,B9:B8        ; |130| 
           STDW    .D2T2   B7:B6,*B16        ; |128| 
           SUB     .L1     A31,1,A0          ; |170| 

           ADDU    .L1     A4,A8,A7:A6       ; |130| 
|| [ A0]   MV      .S1     A12,A4            ; |172| 

           ADD     .L1     A7,A5,A3          ; |130| 
|| [ A0]   MVKL    .S1     0x408f4800,A5

           ADD     .L1     A3,A9,A3          ; |130| 
|| [ A0]   B       .S2     $C$L17            ; |170| 
||         SUBU    .L2X    B6,A6,B5:B4       ; |130| 
|| [ A0]   MVKH    .S1     0x408f4800,A5

           EXT     .S2     B5,24,24,B17      ; |130| 
||         ADDU    .L2     B8,B4,B5:B4       ; |130| 

           SUB     .L2X    B7,A3,B8          ; |130| 
||         SUB     .L1     A31,1,A3          ; |170| 
||         ADD     .S2     B5,B9,B5          ; |130| 

           STW     .D2T1   A3,*+SP(12)       ; |130| 
|| [ A0]   MVKL    .S1     _input,A3
||         ADD     .L2     B8,B17,B8         ; |130| 

   [ A0]   CALL    .S2     _gimme_random     ; |172| 
|| [ A0]   MVKH    .S1     _input,A3
||         ADD     .L2     B5,B8,B5          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D2T2   B5:B4,*B12        ; |130| 
|| [ A0]   LDW     .D1T1   *A3,A14           ; |172| 
|| [ A0]   MV      .L2X    A13,B4            ; |172| 
|| [ A0]   MV      .S2     B13,B5            ; |172| 

           ; BRANCHCC OCCURS {$C$L17}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D2T1   *B12,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL31,B3,3      ; |135| 
$C$RL31:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL32:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           MVK     .S1     24,A3

           SUB     .L1X    B12,A3,A3
||         MV      .L2X    A13,B4            ; |114| 
||         STDW    .D2T1   A5:A4,*B12        ; |135| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A13:A12,*A3       ; |114| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     _output,A31
           MVKL    .S1     _t_offset,A3

           MVKH    .S1     _output,A31
||         SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         MVKH    .S1     _t_offset,A3
||         SUB     .L2     B8,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MV      .L1     A3,A4             ; |117| 
||         LDW     .D1T1   *A31,A10
||         MVK     .S1     0x80,A30

           STDW    .D1T2   B7:B6,*A4         ; |117| 
||         MV      .L1     A30,A15           ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 8
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           CALL    .S1     _sqrt             ; |185| 
           LDDW    .D1T1   *A14++,A5:A4      ; |185| 
           MVKL    .S2     _t_start,B6
           MVKH    .S2     _t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           ADDKPC  .S2     $C$RL33,B3,0      ; |185| 
$C$RL33:   ; CALL OCCURS {_sqrt} {0}         ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20

           STDW    .D1T1   A5:A4,*A10++      ; |185| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     _t_start,A3
||         MVKL    .S2     _t_offset,B12
||         SUB     .L1     A15,1,A0          ; |183| 
||         MV      .L2     B4,B17            ; |128| 
||         SUB     .D1     A15,1,A15         ; |183| 

           MVKH    .S1     _t_start,A3
||         MVKH    .S2     _t_offset,B12

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 
||         MVKL    .S1     _cycle_counts,A31

           MVKH    .S1     _cycle_counts,A31
           MVKL    .S1     _t_stop,A30
           MVKH    .S1     _t_stop,A30
           STDW    .D1T2   B17:B16,*A30      ; |128| 

           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
||         MVKL    .S2     _cycle_counts,B6

           ADD     .L1X    A5,B7,A6          ; |130| 
||         MVKH    .S2     _cycle_counts,B6

           SUBU    .L2X    B16,A4,B9:B8      ; |130| 
||         LDDW    .D1T1   *A31,A5:A4        ; |130| 
||         ADD     .L1     A6,A7,A6          ; |130| 

           MV      .L2     B8,B4             ; |130| 
||         EXT     .S2     B9,24,24,B8       ; |130| 
|| [!A0]   MV      .L1X    B6,A15

           SUB     .L2X    B17,A6,B7         ; |130| 

   [ A0]   BNOP    .S1     $C$L19,1          ; |183| 
||         ADD     .L2     B7,B8,B7          ; |130| 

           ADDU    .L2X    A4,B4,B5:B4       ; |130| 
           ADD     .L2X    B5,A5,B5          ; |130| 
           ADD     .L2     B5,B7,B5          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D2T2   B5:B4,*B6         ; |130| 

           ; BRANCHCC OCCURS {$C$L19}        ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A15,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |135| 
$C$RL34:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A12,A10           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL35:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A13:A12,*+A15(8)  ; |114| 
||         MV      .L2X    A13,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A15        ; |135| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B5,B6,B5          ; |117| 

           MV      .L2X    A3,B12            ; |117| 
||         STDW    .D2T2   B5:B4,*B12        ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T1   *A3,A3            ; |194| 
           MVKL    .S2     _t_start,B6
           MVKH    .S2     _t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A10,A3,A3         ; |194| 
||         CALL    .S1     _sqrtdp           ; |194| 

           LDDW    .D1T1   *A3,A5:A4         ; |194| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |194| 
$C$RL36:   ; CALL OCCURS {_sqrtdp} {0}       ; |194| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     _output+4,B4
           MVKH    .S2     _output+4,B4
           LDW     .D2T2   *B4,B4            ; |194| 
           NOP             4
           ADD     .L1X    A10,B4,A3         ; |194| 

           STDW    .D1T1   A5:A4,*A3         ; |194| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S1     _t_offset,A14
||         MVKL    .S2     _t_start,B4
||         ADDAD   .D1     A15,1,A3
||         SUB     .L1X    B12,1,A0          ; |192| 
||         MV      .L2     B6,B9             ; |128| 
||         SUB     .D2     B12,1,B12         ; |192| 

           MVKH    .S1     _t_offset,A14
||         MVKH    .S2     _t_start,B4
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
|| [!A0]   MV      .L1     A15,A3

           MVKL    .S1     _t_stop,A31
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B4,B17:B16       ; |130| 

           MVK     .S2     8,B13
           MVKH    .S1     _t_stop,A31
           ADD     .L2X    A15,B13,B13
           STDW    .D1T2   B9:B8,*A31        ; |128| 
           ADDU    .L2X    A4,B16,B5:B4      ; |130| 

   [ A0]   B       .S1     $C$L20            ; |192| 
||         ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2     B6,B17,B6         ; |130| 
||         EXT     .S2     B5,24,24,B31      ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B6,B7          ; |130| 
||         ADD     .S2X    B5,A7,B6          ; |130| 

           ADD     .L2     B7,B31,B5         ; |130| 
           ADD     .L2     B6,B5,B5          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D2T2   B5:B4,*B13        ; |130| 
||         ADD     .L1     8,A10,A10         ; |192| 

           ; BRANCHCC OCCURS {$C$L20}        ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(8),A5:A4     ; |135| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |135| 
$C$RL37:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A12,A10           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL38:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           MV      .L1     A15,A3            ; |135| 
||         STDW    .D2T1   A5:A4,*B13        ; |135| 
||         MV      .L2X    A13,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A13:A12,*+A3(16)  ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVK     .S1     0x80,A3

           STDW    .D1T2   B5:B4,*A14        ; |117| 
||         STW     .D2T1   A3,*+SP(12)       ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T1   *A3,A3            ; |203| 
           MVKL    .S2     _t_start,B6
           MVKH    .S2     _t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A10,A3,A3         ; |203| 
||         CALL    .S1     _sqrtdp_c         ; |203| 

           LDDW    .D1T1   *A3,A5:A4         ; |203| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |203| 
$C$RL39:   ; CALL OCCURS {_sqrtdp_c} {0}     ; |203| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     _output+8,B4
           MVKH    .S2     _output+8,B4
           LDW     .D2T2   *B4,B4            ; |203| 
           NOP             4
           ADD     .L1X    A10,B4,A3         ; |203| 

           STDW    .D1T1   A5:A4,*A3         ; |203| 
||         MVC     .S2     TSCL,B4           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     _t_start,B12
||         LDW     .D2T1   *+SP(12),A31      ; |128| 
||         MVKL    .S1     _cycle_counts+16,A3
||         ADD     .L1     8,A10,A10         ; |201| 

           MVKH    .S2     _t_start,B12
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         MVKH    .S1     _cycle_counts+16,A3

           LDDW    .D2T2   *B12,B9:B8        ; |130| 
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     _t_stop,A15

           MV      .L2X    A3,B13            ; |128| 
||         MVKH    .S1     _t_stop,A15

           STDW    .D1T2   B5:B4,*A15        ; |128| 

           SUB     .L1     A31,1,A0          ; |201| 
||         SUB     .S1     A31,1,A3          ; |201| 

           STW     .D2T1   A3,*+SP(12)       ; |130| 
|| [!A0]   MVK     .S1     16,A3

           ADDU    .L2X    A4,B8,B7:B6       ; |130| 
|| [!A0]   SUB     .L1X    B13,A3,A3

           ADD     .S2X    B7,A5,B8          ; |130| 
|| [ A0]   B       .S1     $C$L21            ; |201| 
||         SUBU    .L2     B4,B6,B7:B6       ; |130| 

           ADD     .D2     B8,B9,B8          ; |130| 
||         EXT     .S2     B7,24,24,B9       ; |130| 
||         ADDU    .L2X    A6,B6,B7:B6       ; |130| 

           SUB     .L2     B5,B8,B8          ; |130| 
||         ADD     .S2X    B7,A7,B7          ; |130| 

           ADD     .L2     B8,B9,B8          ; |130| 
           ADD     .L2     B7,B8,B7          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D2T2   B7:B6,*B13        ; |130| 

           ; BRANCHCC OCCURS {$C$L21}        ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(16),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL40,B3,3      ; |135| 
$C$RL40:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 109
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A12,A10           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL41:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
           MV      .L1X    B13,A10           ; |135| 
           SUBAW   .D1     A10,4,A3

           MV      .L2X    A13,B4            ; |114| 
||         STDW    .D1T1   A5:A4,*A10        ; |135| 

           STDW    .D1T1   A13:A12,*+A3(32)  ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D2T2   B5:B4,*B12        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           MVKL    .S1     _input,A3
||         SUBU    .L2     B6,B4,B7:B6       ; |117| 

           MVKH    .S1     _input,A3
||         SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           MVKL    .S1     _output,A12
||         ADD     .L2     B4,B5,B7          ; |117| 

           MV      .L2X    A3,B9             ; |210| 
||         MVKH    .S1     _output,A12
||         STDW    .D1T2   B7:B6,*A14        ; |117| 

           CALLP   .S2     _sqrtdp_v,B3
||         LDW     .D2T1   *B9,A4            ; |210| 
||         LDW     .D1T2   *+A12(16),B4      ; |210| 
||         MVK     .S1     0x80,A6           ; |210| 

$C$RL42:   ; CALL OCCURS {_sqrtdp_v} {0}     ; |210| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 

           MVK     .S2     16,B12
           ADD     .L2X    A10,B12,B12

           MV      .L2     B4,B9             ; |128| 
||         LDDW    .D2T2   *B12,B5:B4        ; |130| 

           NOP             1
           ADDU    .L1X    A4,B6,A7:A6       ; |130| 

           ADD     .S1     A7,A5,A4          ; |130| 
||         SUBU    .L1X    B8,A6,A7:A6       ; |130| 

           MV      .L1     A6,A3             ; |130| 

           ADDU    .L1X    B4,A3,A5:A4       ; |130| 
||         ADD     .L2X    A4,B7,B4          ; |130| 

           EXT     .S1     A7,24,24,A3       ; |130| 

           SUB     .L2     B9,B4,B7          ; |130| 
||         ADD     .S2X    A5,B5,B5          ; |130| 

           ADD     .L2X    B7,A3,B7          ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 
||         MV      .S2X    A4,B4             ; |130| 

           MV      .L2X    A15,B6            ; |128| 

           CALLP   .S2     __fltllif,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         STDW    .D2T2   B9:B8,*B6         ; |128| 

$C$RL43:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1     A13,A10           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL44:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     0x3d3c25c2,B7

           STDW    .D2T1   A5:A4,*B12        ; |130| 
||         LDW     .D1T2   *+A12(4),B4       ; |66| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A12,A4           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 

$C$RL45:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x68497682,B6

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     0x3d3c25c2,B7

           LDW     .D1T2   *+A12(8),B4       ; |67| 
||         MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     0x68497682,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A12,A4           ; |67| 
||         MV      .S1     A3,A10            ; |66| 
||         MVKH    .S2     0x3d3c25c2,B7

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A5,*+A10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL46:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6

           STW     .D1T1   A4,*+A10(8)       ; |67| 
||         MVKH    .S2     0x3d3c25c2,B7

           LDW     .D1T2   *+A12(12),B4      ; |68| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A12,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL47:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T2   *+SP(16),B4       ; |68| 
           MVKL    .S2     0x3d3c25c2,B7
           MVKL    .S2     0x68497682,B6
           MVKH    .S2     0x3d3c25c2,B7

           STW     .D1T1   A4,*+A10(12)      ; |68| 
||         MVKH    .S2     0x68497682,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *B4,B4            ; |69| 
||         LDW     .D1T1   *A12,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL48:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *B11,B0           ; |72| 
           STW     .D1T1   A4,*+A10(16)      ; |69| 
           NOP             3

   [!B0]   BNOP    .S1     $C$L22,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B10,B0           ; |72| 

   [ B1]   ADD     .L2     4,B10,B4
           ; BRANCHCC OCCURS {$C$L22}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A13,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L23            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |216| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L23}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |216| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1     A13,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |216| 
||         ADDKPC  .S2     $C$RL49,B3,0      ; |216| 

$C$RL49:   ; CALL OCCURS {_print_test_results} {0}  ; |216| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |217| 

$C$RL50:   ; CALL OCCURS {_printf} {0}       ; |217| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |217| 

$C$RL51:   ; CALL OCCURS {_printf} {0}       ; |217| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |224| 

$C$RL52:   ; CALL OCCURS {_print_profile_results} {0}  ; |224| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |227| 

$C$RL53:   ; CALL OCCURS {_print_memory_results} {0}  ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(64),B3      ; |228| 
           LDDW    .D2T1   *++SP,A13:A12     ; |228| 
           LDDW    .D2T1   *++SP,A15:A14     ; |228| 
           LDDW    .D2T2   *++SP,B11:B10     ; |228| 
           LDDW    .D2T2   *++SP,B13:B12     ; |228| 

           LDW     .D2T1   *++SP(8),A10      ; |228| 
||         RET     .S2     B3                ; |228| 

           LDW     .D2T1   *++SP(8),A11      ; |228| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |228| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"sqrtDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_sqrt
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_sqrtdp
	.global	_sqrtdp_c
	.global	_sqrtdp_v
	.global	_t_start
	.global	_t_stop
	.global	_t_offset
	.global	_cycle_counts
	.global	_fcn_pass
	.global	_all_pass
	.global	_a_ext
	.global	_a_sc
	.global	_output
	.global	_input
	.global	__fltllif
	.global	__fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
