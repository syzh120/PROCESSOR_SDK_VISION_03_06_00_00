;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:56:56 2013                                *
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
	.word	04476e6ddh		; _a[0] @ 0
	.word	043b50493h		; _a[1] @ 32
	.word	0439400b5h		; _a[2] @ 64
	.word	0431e7a78h		; _a[3] @ 96
	.word	044627782h		; _a[4] @ 128
	.word	04433b225h		; _a[5] @ 160
	.word	0440c0d41h		; _a[6] @ 192
	.word	04404a940h		; _a[7] @ 224
	.word	0433db9c4h		; _a[8] @ 256
	.word	0442b64bbh		; _a[9] @ 288
$C$IR_1:	.set	40

	.global	_a
_a:	.usect	".far",40,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\049242 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\049244 
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
;*   Local Frame Size  : 8 Args + 24 Auto + 56 Save = 88 byte                 *
;******************************************************************************
_main:
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
||         CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |98| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .L2     0xa,B4
||         MVKL    .S1     _a,A12

           MVKH    .S1     _a,A12
||         MVKL    .S2     _output,B12

           CALL    .S1     _rsqrtf           ; |107| 
||         MV      .L1     A12,A13
||         MV      .D1X    B4,A10
||         MVKH    .S2     _output,B12
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
$C$RL1:    ; CALL OCCURS {_rsqrtf} {0}       ; |107| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |107| 
||         SUB     .L1     A10,1,A0          ; |106| 
||         SUB     .S1     A10,1,A10         ; |106| 

   [ A0]   BNOP    .S1     $C$L1,3           ; |106| 
|| [!A0]   MVK     .L2     0xa,B5

           ADD     .L2     B10,B4,B4         ; |107| 
||         ADD     .S2     4,B10,B10         ; |106| 

   [ A0]   CALL    .S1     _rsqrtf           ; |107| 
||         STW     .D2T1   A4,*B4            ; |107| 
|| [!A0]   ADD     .L2     4,B12,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |106| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           CALL    .S1     _rsqrtsp          ; |110| 
||         ZERO    .L2     B10
||         MV      .L1X    B5,A10
||         MV      .D1     A12,A11
||         STW     .D2T2   B4,*+SP(20)

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |110| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |110| 
$C$RL2:    ; CALL OCCURS {_rsqrtsp} {0}      ; |110| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(20),B4       ; |110| 
           SUB     .L1     A10,1,A0          ; |109| 
           SUB     .L1     A10,1,A10         ; |109| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |110| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |109| 

           ADD     .L2     B10,B4,B4         ; |110| 
||         ADD     .S2     4,B10,B10         ; |109| 

   [ A0]   CALL    .S1     _rsqrtsp          ; |110| 
||         STW     .D2T1   A4,*B4            ; |110| 

           ; BRANCHCC OCCURS {$C$L2}         ; |109| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(20),B4
           MVK     .L2     0xa,B5
           ZERO    .L2     B10
           MV      .L1     A11,A12
           MV      .L1X    B5,A10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(24)
||         CALL    .S1     _rsqrtsp_c        ; |113| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |113| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |113| 
$C$RL3:    ; CALL OCCURS {_rsqrtsp_c} {0}    ; |113| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(24),B4       ; |113| 
||         SUB     .L1     A10,1,A0          ; |112| 
||         SUB     .S1     A10,1,A10         ; |112| 

   [!A0]   ZERO    .L1     A3
   [!A0]   SET     .S1     A3,0x16,0x1d,A5
   [!A0]   ZERO    .L1     A3
   [!A0]   SET     .S1     A3,0x17,0x1e,A3
           LDW     .D2T2   *B4,B4            ; |113| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |112| 

           ADD     .L2     B10,B4,B4         ; |113| 
||         ADD     .S2     4,B10,B10         ; |112| 

   [ A0]   CALL    .S1     _rsqrtsp_c        ; |113| 
||         STW     .D2T1   A4,*B4            ; |113| 
|| [!A0]   ZERO    .L1     A4
|| [!A0]   ZERO    .L2     B4

           ; BRANCHCC OCCURS {$C$L3}         ; |112| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           SET     .S2     B4,0x18,0x1d,B4
||         SET     .S1     A4,0x17,0x17,A4
||         MV      .L2X    A11,B8
||         MVK     .L1     9,A1
||         LDW     .D2T2   *+B12(12),B9

           MV      .L2     B4,B6
||         MV      .D2X    A3,B4
||         MV      .L1     A4,A3
||         DINT                              ; interrupts off

           MV      .L2X    A5,B5
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/rsqrtsp/rsqrtsp_d.c
;*      Loop source line                 : 115
;*      Loop opening brace source line   : 115
;*      Loop closing brace source line   : 117
;*      Known Minimum Trip Count         : 10                    
;*      Known Maximum Trip Count         : 10                    
;*      Known Max Trip Count Factor      : 10
;*      Loop Carried Dependency Bound(^) : 45
;*      Unpartitioned Resource Bound     : 4
;*      Partitioned Resource Bound(*)    : 8
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     2        1     
;*      .D units                     0        2     
;*      .M units                     0        8*    
;*      .X cross paths               1        0     
;*      .T address paths             0        2     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        2     (.L or .S unit)
;*      Addition ops (.LSD)          0        1     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        2     
;*      Bound(.L .S .D .LS .LSD)     1        2     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 45 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: | * *                            |    *** **                      |
;*       1: | * *                            |    *** **                      |
;*       2: | * *                            |    *** **                      |
;*       3: | * *                            |    *** **                      |
;*       4: | * *                            |    *** **                      |
;*       5: | * *                            |    *** **       *              |
;*       6: | * *                            |    *** **      **              |
;*       7: | * *                            |    *** **      **              |
;*       8: | * *                            |    *** **      **              |
;*       9: | * *                            |    *** **      **              |
;*      10: | * *                            |    ******      **              |
;*      11: | * *                            |    *** **      **              |
;*      12: | * *                            |    *** **      **              |
;*      13: | * *                            |    *** **      **              |
;*      14: | * *                            |    ******      **              |
;*      15: | * *                            |    *** **      **              |
;*      16: | * *                            |    *** **      **              |
;*      17: | * *                            |    *** **      **              |
;*      18: | * *                            |    ******      **              |
;*      19: | * *                            |    *** **      **              |
;*      20: | * *                            |    *** **      **              |
;*      21: | * *                            |    ******      **              |
;*      22: | * *                            |    *** **       *              |
;*      23: | * *                            |    *** **       *              |
;*      24: | * *                            |    *** **       *              |
;*      25: | * *                            |    *** **      **              |
;*      26: | * *                            |    *** **      **              |
;*      27: | * *                            |    *** **      **              |
;*      28: | * *                            |    *** **      **              |
;*      29: | * *                            |    ******      **              |
;*      30: | * *                            |    *** **      **              |
;*      31: | * *                            |    *** **      **              |
;*      32: | * *                            |    *** **      **              |
;*      33: | * *                            |    ******      **              |
;*      34: | * *                            |    *** **      **              |
;*      35: | * *                            |    *** **      **              |
;*      36: | * *                            |    *** **      **              |
;*      37: | * *                            |    ******      **              |
;*      38: | * *                            |    *** **      **              |
;*      39: |** *                            |    *** **      *               |
;*      40: |** *                            |    ******      **              |
;*      41: | * *                            |    *** **       *              |
;*      42: | * *                            |    *** **       *              |
;*      43: | * *                            |    *** **       *              |
;*      44: | * *                            |    *** **       *              |
;*          +-----------------------------------------------------------------+
;*
;*      Done
;*
;*      Collapsed epilog stages       : 0
;*      Collapsed prolog stages       : 0
;*
;*      Minimum safe trip count       : 1
;*
;*
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.000, max 0.000 }
;*      Mem bank perf. penalty (est.) : 0.0%
;*
;*
;*      Total cycles (est.)         : 0 + min_trip_cnt * 45 = 450        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A1,1,A1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C85:
;*   0              LDW     .D2T2   *B8++,B17         ; |64|  ^ 
;*   1              NOP             4
;*   5              RSQRSP  .S2     B17,B16           ; |64|  ^ 
;*   6              MPYSP   .M2     B16,B17,B7        ; |64|  ^ 
;*   7              NOP             3
;*  10              MPYSP   .M2     B16,B7,B7         ; |64|  ^ 
;*  11              NOP             3
;*  14              MPYSP   .M2     B6,B7,B7          ; |64|  ^ 
;*  15              NOP             3
;*  18              FSUBSP  .L2     B5,B7,B7          ; |64|  ^ 
;*  19              NOP             2
;*  21              MPYSP   .M2     B16,B7,B16        ; |64|  ^ 
;*  22              NOP             3
;*  25              MPYSP   .M2     B16,B17,B7        ; |64|  ^ 
;*  26              NOP             3
;*  29              MPYSP   .M2     B16,B7,B7         ; |64|  ^ 
;*  30              NOP             3
;*  33              MPYSP   .M2     B6,B7,B7          ; |64|  ^ 
;*  34              NOP             3
;*  37              FSUBSP  .L2     B5,B7,B7          ; |64|  ^ 
;*  38              CMPLTSP .S1X    B17,A3,A0         ; |64| 
;*  39      [ A0]   MV      .S2     B4,B17            ; |64| 
;*     ||   [ A1]   BDEC    .S1     $C$C85,A1         ; |115| 
;*  40      [!A0]   MPYSP   .M2     B16,B7,B17        ; |64|  ^ 
;*  41              NOP             3
;*  44              STW     .D2T2   B17,*B9++         ; |64|  ^ 
;*  45              ; BRANCHCC OCCURS {$C$C85}        ; |115| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 45
           LDW     .D2T2   *B8++,B17         ; |64| <0,0>  ^ 
           NOP             4
           RSQRSP  .S2     B17,B16           ; |64| <0,5>  ^ 
           MPYSP   .M2     B16,B17,B7        ; |64| <0,6>  ^ 
           NOP             3
           MPYSP   .M2     B16,B7,B7         ; |64| <0,10>  ^ 
           NOP             3
           MPYSP   .M2     B6,B7,B7          ; |64| <0,14>  ^ 
           NOP             3
           FSUBSP  .L2     B5,B7,B7          ; |64| <0,18>  ^ 
           NOP             2
           MPYSP   .M2     B16,B7,B16        ; |64| <0,21>  ^ 
           NOP             3
           MPYSP   .M2     B16,B17,B7        ; |64| <0,25>  ^ 
           NOP             3
           MPYSP   .M2     B16,B7,B7         ; |64| <0,29>  ^ 
           NOP             3
           MPYSP   .M2     B6,B7,B7          ; |64| <0,33>  ^ 
           NOP             3
           FSUBSP  .L2     B5,B7,B7          ; |64| <0,37>  ^ 
           CMPLTSP .S1X    B17,A3,A0         ; |64| <0,38> 

   [ A0]   MV      .S2     B4,B17            ; |64| <0,39> 
|| [ A1]   BDEC    .S1     $C$L5,A1          ; |115| <0,39> 

   [!A0]   MPYSP   .M2     B16,B7,B17        ; |64| <0,40>  ^ 
           NOP             3
           STW     .D2T2   B17,*B9++         ; |64| <0,44>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MV      .L1X    B4,A15
           MV      .L1X    B12,A10

           MVK     .L1     0xa,A6            ; |118| 
||         RINT                              ; interrupts on
||         MV      .S1X    B5,A12
||         MV      .D1     A11,A4            ; |118| 

           CALLP   .S2     _rsqrtsp_v,B3
||         LDW     .D1T2   *+A10(16),B4      ; |118| 
||         MV      .L1     A3,A14
||         MV      .S1X    B6,A13

$C$RL4:    ; CALL OCCURS {_rsqrtsp_v} {0}    ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 48
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B4
           MVKH    .S2     0x88e368f1,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         STW     .D2T1   A3,*+B4(4)        ; |66| 
||         LDW     .D1T2   *+A10(8),B4       ; |67| 
||         MVK     .L1     0xa,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L2     B12,B4
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |68| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+SP(24),B5
||         MVKL    .S2     _fcn_pass,B31

           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B31
           MVKH    .S2     0x88e368f1,B6

           STW     .D2T1   A4,*+B31(12)      ; |68| 
||         MVKH    .S2     0x3ee4f8b5,B7

           ADDAD   .D2     B5,1,B4
||         MVKL    .S2     _output,B5

           MVKH    .S2     _output,B5
||         LDW     .D2T2   *B4,B4            ; |69| 

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .L1     0xa,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S1     _fcn_pass,A3
           MVKH    .S1     _fcn_pass,A3
           ADD     .L1     4,A3,A10
           LDW     .D1T1   *A10,A0           ; |72| 
           MV      .L2X    A3,B4             ; |72| 
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           ADD     .L2X    8,A3,B4
           STW     .D2T2   B4,*+SP(28)       ; |69| 

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |122| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   ZERO    .L1     A3                ; |72| 
   [!A0]   MVKL    .S1     _all_pass,A4
   [!A0]   MVKH    .S1     _all_pass,A4
           ; BRANCHCC OCCURS {$C$L7}         ; |72| 
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
           CALL    .S1     _print_test_results ; |122| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x1,A4            ; |122| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |122| 

$C$RL9:    ; CALL OCCURS {_print_test_results} {0}  ; |122| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           LDW     .D2T2   *+SP(24),B31      ; |130| 
||         MVKL    .S2     _a_sc,B4
||         MVK     .L1     0x7,A3

           STW     .D2T1   A3,*+SP(12)       ; |134| 
||         MVKH    .S2     _a_sc,B4
||         ZERO    .L1     A5
||         MVK     .L2     -1,B5             ; |135| 

           STW     .D2T2   B5,*+B4(24)       ; |135| 
||         MVKH    .S1     0xff800000,A5
||         ZERO    .L1     A7
||         ZERO    .L2     B11
||         MV      .D1     A15,A4            ; |132| 

           STDW    .D2T1   A5:A4,*+B4(8)     ; |132| 
||         MVKH    .S2     0xbf800000,B11
||         MVKH    .S1     0x80000000,A7
||         ZERO    .L2     B10
||         ZERO    .L1     A6                ; |130| 

           MV      .L2     B4,B5             ; |130| 
||         STDW    .D2T1   A7:A6,*B4         ; |130| 
||         SET     .S2     B10,0x17,0x1d,B10

           ADD     .L2     4,B31,B10
||         STDW    .D2T2   B11:B10,*+B5(16)  ; |134| 
||         MV      .L1X    B4,A11            ; |130| 
||         ZERO    .S2     B13               ; |130| 

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
           LDW     .D1T1   *A11,A3           ; |137| 
           CALL    .S1     _rsqrt            ; |137| 
           ADDKPC  .S2     $C$RL10,B3,2      ; |137| 
           SPDP    .S1     A3,A5:A4          ; |137| 
           NOP             1
$C$RL10:   ; CALL OCCURS {_rsqrt} {0}        ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D2T2   *B12,B4           ; |137| 
           DPSP    .L1     A5:A4,A3          ; |137| 
           NOP             3
           ADD     .L2     B13,B4,B4         ; |137| 
           STW     .D2T1   A3,*B4            ; |137| 

           CALLP   .S2     _rsqrtsp,B3
||         LDW     .D1T1   *A11,A4           ; |138| 

$C$RL11:   ; CALL OCCURS {_rsqrtsp} {0}      ; |138| 
           LDW     .D2T2   *+B12(4),B4       ; |138| 
           NOP             4
           ADD     .L2     B13,B4,B4         ; |138| 
           STW     .D2T1   A4,*B4            ; |138| 

           CALLP   .S2     _rsqrtsp_c,B3
||         LDW     .D1T1   *A11,A4           ; |139| 

$C$RL12:   ; CALL OCCURS {_rsqrtsp_c} {0}    ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 53
           LDW     .D2T2   *+B12(8),B4       ; |139| 
           LDW     .D2T1   *+SP(12),A31      ; |67| 
           LDW     .D2T2   *B10,B31          ; |140| 
           NOP             2
           ADD     .L2     B13,B4,B4         ; |139| 
           STW     .D2T1   A4,*B4            ; |139| 
           LDW     .D1T1   *A11++,A4         ; |64| 
           SUB     .L1     A31,1,A30         ; |136| 
           SUB     .L1     A31,1,A2          ; |136| 
           ADD     .L2     B13,B31,B4        ; |140| 
           ADD     .L2     4,B13,B13         ; |136| 
           RSQRSP  .S1     A4,A3             ; |64| 
           MPYSP   .M1     A3,A4,A5          ; |64| 
           STW     .D2T1   A30,*+SP(12)      ; |140| 
           CMPLTSP .S1     A4,A14,A0         ; |66| 
           NOP             1
           MPYSP   .M1     A3,A5,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A13,A5,A5         ; |64| 
           NOP             3
           FSUBSP  .L1     A12,A5,A5         ; |64| 
           NOP             2
           MPYSP   .M1     A3,A5,A3          ; |64| 
           NOP             3
           MPYSP   .M1     A3,A4,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A3,A5,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A13,A5,A5         ; |64| 
           NOP             3
           FSUBSP  .L1     A12,A5,A5         ; |64| 
           NOP             2

   [ A2]   BNOP    .S1     $C$L8,3           ; |136| 
||         MPYSP   .M1     A3,A5,A3          ; |64| 

   [ A0]   MV      .L1     A15,A3            ; |67| 

   [!A2]   CALL    .S1     _rsqrtsp_v        ; |142| 
||         STW     .D2T1   A3,*B4            ; |140| 

           ; BRANCHCC OCCURS {$C$L8}         ; |136| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B10(4),B4       ; |142| 
           MVKL    .S1     _a_sc,A4
           MVKH    .S1     _a_sc,A4
           MVK     .L1     0x7,A6            ; |142| 
           ADDKPC  .S2     $C$RL13,B3,0      ; |142| 
$C$RL13:   ; CALL OCCURS {_rsqrtsp_v} {0}    ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D2T1   *B12,A4           ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     0x3ee4f8b5,B7

           STW     .D1T1   A4,*+A3(4)        ; |66| 
||         LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ee4f8b5,B7

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     0x3ee4f8b5,B7

           STW     .D1T1   A4,*+A3(8)        ; |67| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B12,A4           ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     _output,B5
           MVKL    .S2     0x88e368f1,B6

           MVKL    .S1     _fcn_pass,A3
||         MVKH    .S2     _output,B5

           MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     0x3ee4f8b5,B7

           STW     .D1T1   A4,*+A3(12)       ; |68| 
||         LDW     .D2T2   *+B12(16),B4      ; |69| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           STW     .D2T2   B11,*+SP(12)      ; |69| 
||         LDW     .D1T1   *A10,A0           ; |72| 

           LDW     .D2T1   *+SP(28),A3
           MVKL    .S1     _fcn_pass,A31
           MVKH    .S1     _fcn_pass,A31
           STW     .D1T1   A4,*+A31(16)      ; |69| 
   [!A0]   B       .S1     $C$L9             ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |146| 
||         STW     .D2T1   A3,*+SP(32)       ; |72| 

   [ A0]   LDW     .D2T2   *+SP(32),B4
   [!A0]   ZERO    .L1     A4                ; |72| 
   [!A0]   MVKL    .S1     _all_pass,A3
   [!A0]   MVKH    .S1     _all_pass,A3
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           CMPEQ   .L1     A4,0,A3           ; |72| 
           LDW     .D2T2   *B4,B0            ; |72| 
           ADD     .L2     4,B4,B4
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
           NOP             1
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           NOP             3
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   ZERO    .L1     A4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |146| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |146| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |146| 

$C$RL18:   ; CALL OCCURS {_print_test_results} {0}  ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           MVKL    .S2     _a_ext,B4
           MVKL    .S2     0xc000cccc,B13
           MVKL    .S2     0xcccccccd,B12

           MVKH    .S2     _a_ext,B4
||         MVK     .S1     0xed,A3

           MVKH    .S2     0xc000cccc,B13
||         STW     .D2T1   A3,*+SP(16)       ; |149| 

           MV      .L1X    B4,A11            ; |149| 
||         STW     .D2T1   A14,*B4           ; |149| 
||         MVKH    .S2     0xcccccccd,B12
||         ZERO    .L2     B11

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D1T1   *A11,A3           ; |151| 
           CALL    .S1     _rsqrt            ; |151| 
           ADDKPC  .S2     $C$RL19,B3,2      ; |151| 
           SPDP    .S1     A3,A5:A4          ; |151| 
           NOP             1
$C$RL19:   ; CALL OCCURS {_rsqrt} {0}        ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T1   *B4,A3            ; |151| 
           DPSP    .L1     A5:A4,A4          ; |151| 
           NOP             3
           ADD     .L1X    B11,A3,A3         ; |151| 
           STW     .D1T1   A4,*A3            ; |151| 

           CALLP   .S2     _rsqrtsp,B3
||         LDW     .D1T1   *A11,A4           ; |152| 

$C$RL20:   ; CALL OCCURS {_rsqrtsp} {0}      ; |152| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(4),B4        ; |152| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |152| 
           STW     .D2T1   A4,*B4            ; |152| 

           CALLP   .S2     _rsqrtsp_c,B3
||         LDW     .D1T1   *A11,A4           ; |153| 

$C$RL21:   ; CALL OCCURS {_rsqrtsp_c} {0}    ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 73
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |153| 
           LDW     .D2T2   *B10,B31          ; |154| 
           LDW     .D2T1   *+SP(16),A31
           NOP             2
           ADD     .L2     B11,B4,B4         ; |153| 
           STW     .D2T1   A4,*B4            ; |153| 
           LDW     .D1T1   *A11,A4           ; |64| 
           ADD     .L2     B11,B31,B4        ; |154| 
           ADD     .L2     4,B11,B11         ; |150| 
           NOP             2
           RSQRSP  .S1     A4,A3             ; |64| 
           MPYSP   .M1     A3,A4,A5          ; |64| 
           CMPLTSP .S1     A4,A14,A0         ; |66| 
           NOP             2
           MPYSP   .M1     A3,A5,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A13,A5,A5         ; |64| 
           NOP             3
           FSUBSP  .L1     A12,A5,A5         ; |64| 
           NOP             2
           MPYSP   .M1     A3,A5,A3          ; |64| 
           NOP             3
           MPYSP   .M1     A3,A4,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A3,A5,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A13,A5,A5         ; |64| 
           NOP             3
           FSUBSP  .L1     A12,A5,A5         ; |64| 
           NOP             2
           MPYSP   .M1     A3,A5,A3          ; |64| 
           NOP             3
   [ A0]   MV      .L1     A15,A3            ; |67| 
           STW     .D2T1   A3,*B4            ; |154| 
           LDW     .D1T2   *A11,B4           ; |155| 
           SUB     .L1     A31,1,A0          ; |150| 
           SUB     .L1     A31,1,A3          ; |150| 
           NOP             2
           MPYSPDP .M2     B4,B13:B12,B5:B4  ; |155| 
           NOP             6

   [ A0]   BNOP    .S1     $C$L10,3          ; |150| 
||         DPSP    .L2     B5:B4,B4          ; |155| 

           STW     .D1T2   B4,*++A11         ; |155| 

   [!A0]   CALL    .S1     _rsqrtsp_v        ; |157| 
||         STW     .D2T1   A3,*+SP(16)       ; |155| 

           ; BRANCHCC OCCURS {$C$L10}        ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B10(4),B4       ; |157| 
           MVKL    .S1     _a_ext,A4
           MVKH    .S1     _a_ext,A4
           MVK     .S1     0xed,A6           ; |157| 
           ADDKPC  .S2     $C$RL22,B3,0      ; |157| 
$C$RL22:   ; CALL OCCURS {_rsqrtsp_v} {0}    ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 44
           MVKL    .S2     _output,B10
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _output,B10
           MVKH    .S2     0x88e368f1,B6

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL23:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B11
           MVKH    .S2     _fcn_pass,B11
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B11(4)       ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL24:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B11(8)       ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL25:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B10,A3            ; |68| 
||         STW     .D2T1   A4,*+B11(12)      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(16),B4      ; |69| 
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           MV      .L1     A10,A3            ; |69| 
||         LDW     .D2T2   *+SP(28),B4

           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A4,*+B11(16)      ; |69| 
           NOP             3

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |161| 
   [!A0]   ZERO    .L1     A4                ; |72| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     _all_pass,A3
   [!A0]   MVKH    .S1     _all_pass,A3
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
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
           CALL    .S1     _print_test_results ; |161| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |161| 
||         ADDKPC  .S2     $C$RL27,B3,0      ; |161| 

$C$RL27:   ; CALL OCCURS {_print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15

           ZERO    .L2     B13               ; |114| 
||         MVKL    .S2     _cycle_counts+24,B5

           MVKH    .S2     _cycle_counts+24,B5
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .D2     B12               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T2   B13:B12,*B5       ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           MVC     .S2     TSCL,B6           ; |117| 
||         STDW    .D1T2   B5:B4,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKL    .S1     0x447a4000,A3

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B5,B4          ; |117| 
||         MVKH    .S1     0x447a4000,A3

           MVK     .S2     0x80,B4
||         ADD     .L2     B4,B5,B7          ; |117| 

           CALL    .S2     _gimme_random     ; |171| 
||         MV      .L2X    A3,B11
||         MVKL    .S1     _t_offset,A4

           LDW     .D2T2   *+SP(12),B4       ; |171| 
||         MV      .L1X    B4,A11            ; |117| 
||         MVKH    .S1     _t_offset,A4

           MV      .L1X    B11,A4            ; |171| 
||         STDW    .D1T2   B7:B6,*A4         ; |117| 
||         MV      .L2     B12,B10           ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 3
           ADDKPC  .S2     $C$RL28,B3,2      ; |171| 
$C$RL28:   ; CALL OCCURS {_gimme_random} {0}  ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 66
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T1   *A3,A3            ; |171| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |171| 

           STW     .D1T1   A4,*A3            ; |171| 
||         MVC     .S2     TSCL,B16          ; |122| 

           MVC     .S2     TSCH,B4           ; |122| 
           RSQRSP  .S1     A4,A3             ; |64| 
           MPYSP   .M1     A3,A4,A5          ; |64| 
           MV      .L2     B4,B17            ; |122| 
           MVKL    .S2     _output+12,B5
           CMPLTSP .S1     A4,A14,A0         ; |66| 
           MPYSP   .M1     A3,A5,A5          ; |64| 
           MVKH    .S2     _output+12,B5
           LDW     .D2T2   *B5,B5            ; |175| 
           MVKL    .S1     _t_start,A31
           MPYSP   .M1     A13,A5,A5         ; |64| 
           MVKH    .S1     _t_start,A31
           STDW    .D1T2   B17:B16,*A31
           ADD     .L2     B10,B5,B4         ; |175| 
           FSUBSP  .L1     A12,A5,A5         ; |64| 
           NOP             2
           MPYSP   .M1     A3,A5,A3          ; |64| 
           NOP             3
           MPYSP   .M1     A3,A4,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A3,A5,A5          ; |64| 
           NOP             3
           MPYSP   .M1     A13,A5,A5         ; |64| 
           NOP             3
           FSUBSP  .L1     A12,A5,A5         ; |64| 
           NOP             2
           MPYSP   .M1     A3,A5,A5          ; |64| 
           NOP             3
   [ A0]   MV      .L1     A15,A5            ; |67| 

           STW     .D2T1   A5,*B4            ; |175| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S1     _t_offset,A3
||         MVKL    .S2     _cycle_counts+24,B4
||         SUB     .L1     A11,1,A0          ; |169| 
||         ADD     .L2     4,B10,B10         ; |169| 
||         SUB     .D1     A11,1,A11         ; |169| 

           MVKH    .S1     _t_offset,A3
||         MVKH    .S2     _cycle_counts+24,B4

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         LDDW    .D2T2   *B4,B7:B6         ; |130| 
||         MVKL    .S1     _cycle_counts+24,A3

           MVKL    .S1     _t_stop,A30
           MVKH    .S1     _cycle_counts+24,A3
           MVKH    .S1     _t_stop,A30
           STDW    .D1T2   B9:B8,*A30        ; |128| 

           ADDU    .L2X    A4,B16,B5:B4      ; |130| 
|| [ A0]   MV      .L1X    B11,A4            ; |171| 

           ADD     .S2X    B5,A5,B16         ; |130| 
|| [ A0]   B       .S1     $C$L12            ; |169| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2     B16,B17,B16       ; |130| 
||         EXT     .S2     B5,24,24,B17      ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B16,B16        ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         ADD     .D2     B5,B7,B5          ; |130| 

   [ A0]   CALL    .S1     _gimme_random     ; |171| 
||         ADD     .L2     B16,B17,B4        ; |130| 

           ADD     .L2     B5,B4,B7          ; |130| 
|| [ A0]   LDW     .D2T2   *+SP(12),B4       ; |171| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D1T2   B7:B6,*A3         ; |130| 

           ; BRANCHCC OCCURS {$C$L12}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A3,A5:A4         ; |135| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |135| 
$C$RL29:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A11
           SET     .S1     A11,0x1a,0x1d,A11
           MPYSP   .M1     A11,A4,A3         ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           MV      .L1X    B13,A12           ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL30:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           MVKL    .S1     _cycle_counts+24,A3
           MVKH    .S1     _cycle_counts+24,A3
           MV      .L2     B12,B5            ; |114| 
           MV      .L2X    A3,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 
           SUBAW   .D2     B4,6,B10

           STDW    .D2T2   B13:B12,*B10      ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     _t_start,A15

           MVKH    .S1     _t_start,A15
||         MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A15        ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 

           SUBU    .L2     B5,B6,B9:B8       ; |117| 
||         MVKL    .S2     _t_offset,B11

           EXT     .S2     B9,24,24,B5       ; |117| 
||         SUB     .L2     B4,B7,B4          ; |117| 

           ADD     .L2     B4,B5,B9          ; |117| 
||         MVKH    .S2     _t_offset,B11
||         MVKL    .S1     _input,A14

           STDW    .D2T2   B9:B8,*B11        ; |117| 
||         MVKH    .S1     _input,A14

           LDW     .D1T1   *A14,A3           ; |183| 
           MVK     .S2     0x80,B31
           STW     .D2T2   B31,*+SP(12)      ; |117| 
           NOP             2

           CALL    .S1     _rsqrtf           ; |183| 
||         ADD     .L1     A12,A3,A3         ; |183| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A4            ; |183| 
           ADDKPC  .S2     $C$RL31,B3,3      ; |183| 
$C$RL31:   ; CALL OCCURS {_rsqrtf} {0}       ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |183| 
           NOP             4

           ADD     .L1X    A12,B4,A3         ; |183| 
||         LDW     .D2T2   *+SP(12),B4       ; |183| 

           ADD     .L1     4,A12,A12         ; |182| 
           STW     .D1T1   A4,*A3            ; |183| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |182| 
||         SUB     .L2     B4,1,B4           ; |182| 

   [ A0]   BNOP    .S1     $C$L13,4          ; |182| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |183| 
||         STW     .D2T2   B4,*+SP(12)       ; |183| 

   [ A0]   CALL    .S1     _rsqrtf           ; |183| 
||         ADD     .L1     A12,A3,A3         ; |183| 

           ; BRANCHCC OCCURS {$C$L13}        ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MV      .L2     B11,B4            ; |128| 
||         LDDW    .D1T1   *A15,A7:A6        ; |130| 

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           MV      .L2     B5,B9             ; |128| 
           NOP             3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           ADD     .L1X    A5,B7,A3          ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           ADD     .L1     A3,A7,A3          ; |130| 
||         SUBU    .L2X    B8,A4,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B9,A3,B31         ; |130| 
           CALL    .S1     __fltllif         ; |130| 

           ADDU    .L2     B6,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B6        ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         MVKL    .S2     _t_stop,B6

           MVKH    .S2     _t_stop,B6

           STDW    .D2T2   B9:B8,*B6         ; |128| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL32,B3,0      ; |130| 

$C$RL32:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           MV      .L1X    B13,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL33:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           MV      .L2     B12,B4            ; |114| 
||         STDW    .D2T2   B13:B12,*+B10(8)  ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A5:A4,*B10        ; |130| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           MVC     .S2     TSCL,B6           ; |117| 
||         STDW    .D1T2   B5:B4,*A15        ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKL    .S2     _t_offset,B31

           EXT     .S2     B7,24,24,B4       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           MVK     .S2     0x80,B4
||         ADD     .L2     B5,B4,B7          ; |117| 

           MVKH    .S2     _t_offset,B31
||         LDW     .D2T2   *+SP(20),B11      ; |117| 

           MV      .L1X    B4,A11            ; |117| 
||         STDW    .D2T2   B7:B6,*B31        ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A14,A3           ; |191| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |191| 
||         CALL    .S1     _rsqrtsp          ; |191| 

           LDW     .D1T1   *A3,A4            ; |191| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |191| 
$C$RL34:   ; CALL OCCURS {_rsqrtsp} {0}      ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |191| 
||         SUB     .L1     A11,1,A0          ; |190| 
||         SUB     .S1     A11,1,A11         ; |190| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |190| 

           ADD     .L1X    A12,B4,A3         ; |191| 
||         ADD     .S1     4,A12,A12         ; |190| 

           STW     .D1T1   A4,*A3            ; |191| 
           ; BRANCHCC OCCURS {$C$L14}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     _t_offset,B4
||         MV      .L1     A15,A11           ; |128| 

           MVKH    .S2     _t_offset,B4
||         LDDW    .D1T1   *A11,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           LDDW    .D2T2   *+B10(8),B17:B16  ; |130| 
           MV      .L2     B5,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A4          ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 
||         ADD     .S2     B7,B17,B31        ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         MVKL    .S2     _t_stop,B4

           ADD     .L2     B31,B5,B7         ; |130| 
||         MVKH    .S2     _t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL35,B3,0      ; |130| 

$C$RL35:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B13,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL36:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           STDW    .D2T2   B13:B12,*+B10(16) ; |114| 

           ADDAD   .D2     B10,1,B11
||         MV      .L2     B12,B4            ; |114| 

           STDW    .D2T1   A5:A4,*B11        ; |130| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MV      .L1     A11,A12           ; |116| 

           STDW    .D1T2   B5:B4,*A12        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKL    .S2     _t_offset,B31

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKH    .S2     _t_offset,B31

           STDW    .D2T2   B7:B6,*B31        ; |117| 
           LDW     .D1T1   *A14,A3           ; |199| 
           MV      .L1X    B13,A15
           MVK     .S2     0x80,B30
           LDW     .D2T1   *+SP(24),A11      ; |117| 
           STW     .D2T2   B30,*+SP(12)      ; |117| 

           CALL    .S1     _rsqrtsp_c        ; |199| 
||         ADD     .L1     A15,A3,A3         ; |199| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A4            ; |199| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |199| 
$C$RL37:   ; CALL OCCURS {_rsqrtsp_c} {0}    ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MV      .L2X    A11,B4            ; |199| 
           LDW     .D2T2   *B4,B4            ; |199| 
           STW     .D2T1   A11,*+SP(16)      ; |199| 
           NOP             3

           ADD     .L1X    A15,B4,A3         ; |199| 
||         LDW     .D2T2   *+SP(12),B4       ; |199| 

           ADD     .L1     4,A15,A15         ; |198| 
           STW     .D1T1   A4,*A3            ; |199| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |198| 
||         SUB     .L2     B4,1,B4           ; |198| 

   [ A0]   BNOP    .S1     $C$L15,4          ; |198| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |199| 
||         STW     .D2T2   B4,*+SP(12)       ; |199| 

   [ A0]   CALL    .S1     _rsqrtsp_c        ; |199| 
||         ADD     .L1     A15,A3,A3         ; |199| 

           ; BRANCHCC OCCURS {$C$L15}        ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S2     _t_offset,B4
||         MV      .L1     A12,A11           ; |128| 

           MVKH    .S2     _t_offset,B4
||         LDDW    .D1T1   *A11,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B9:B8         ; |130| 
           MV      .L2     B10,B31           ; |130| 
           LDDW    .D2T2   *+B31(16),B17:B16 ; |130| 
           MV      .L1X    B10,A15           ; |130| 
           NOP             1
           ADDU    .L2X    B8,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B9,B4          ; |130| 
||         SUBU    .L2     B6,B4,B9:B8       ; |130| 

           MV      .L2     B8,B5             ; |130| 
||         ADD     .S2X    B4,A5,B4          ; |130| 
||         CALL    .S1     __fltllif         ; |130| 

           ADDU    .L2     B16,B5,B9:B8      ; |130| 
||         EXT     .S2     B9,24,24,B5       ; |130| 
||         SUB     .D2     B7,B4,B4          ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B9,B17,B4         ; |130| 

           ADD     .L2     B4,B5,B9          ; |130| 
||         MVKL    .S2     _t_stop,B4

           MVKH    .S2     _t_stop,B4

           STDW    .D2T2   B7:B6,*B4         ; |128| 
||         DADD    .L1X    0,B9:B8,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL38,B3,0      ; |130| 

$C$RL38:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B13,A12           ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL39:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 

           ADDAD   .D2     B11,1,B10
||         MV      .L2X    A15,B4

           MV      .L2     B12,B31           ; |114| 
||         STDW    .D2T2   B13:B12,*+B4(32)  ; |114| 

           STDW    .D2T1   A5:A4,*B10        ; |130| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A11        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         LDW     .D2T2   *+SP(16),B4       ; |117| 

           MVKL    .S1     _t_offset,A3
           MV      .L2X    A14,B9            ; |206| 
           MVKH    .S1     _t_offset,A3

           LDW     .D2T1   *B9,A4            ; |206| 
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           LDW     .D2T2   *+B4(8),B4        ; |206| 
||         MV      .L2X    A3,B11            ; |117| 
||         ADD     .S2     B5,B7,B7          ; |117| 

           CALLP   .S2     _rsqrtsp_v,B3
||         STDW    .D2T2   B7:B6,*B11        ; |117| 
||         MVK     .S1     0x80,A6           ; |206| 

$C$RL40:   ; CALL OCCURS {_rsqrtsp_v} {0}    ; |206| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A11,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S1     16,A11
           ADD     .L1X    B10,A11,A11
           LDDW    .D1T1   *A11,A9:A8        ; |130| 
           MVKL    .S1     _t_stop,A3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           MVKH    .S1     _t_stop,A3
||         SUBU    .L1X    B8,A4,A17:A16     ; |130| 

           ADD     .L1X    A5,B7,A4          ; |130| 
||         MV      .L2     B4,B9             ; |128| 

           ADD     .L1     A4,A7,A4          ; |130| 
||         MV      .L2X    A3,B4             ; |128| 
||         MV      .D1     A16,A3            ; |130| 
||         EXT     .S1     A17,24,24,A6      ; |130| 

           SUB     .S1X    B9,A4,A3          ; |130| 
||         ADDU    .L1     A8,A3,A5:A4       ; |130| 

           ADD     .L1     A5,A9,A3          ; |130| 
||         ADD     .S1     A3,A6,A5          ; |130| 

           CALLP   .S2     __fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL41:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL42:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 

           MVKL    .S1     _output,A3
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S1     _output,A3
||         MVKL    .S2     0x3ee4f8b5,B7

           MV      .L1     A3,A12            ; |130| 
||         STDW    .D1T1   A5:A4,*A11        ; |130| 
||         MVKH    .S2     0x88e368f1,B6

           LDW     .D1T1   *A12,A4           ; |66| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A12(4),B4       ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL43:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7

           LDW     .D1T2   *+A12(8),B4       ; |67| 
||         MVKL    .S1     _fcn_pass,A11
||         MVKH    .S2     0x88e368f1,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A12,A4           ; |67| 
||         MVKH    .S1     _fcn_pass,A11
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A3,*+A11(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL44:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T2   *+A12(12),B4      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           MVKH    .S2     0x3ee4f8b5,B7
||         STW     .D1T1   A3,*+A11(8)       ; |67| 

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A12,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL45:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L2X    A12,B4            ; |68| 
||         STW     .D1T1   A4,*+A11(12)      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *+A12(16),B4      ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL46:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           LDW     .D1T1   *A10,A0           ; |72| 
||         LDW     .D2T2   *+SP(32),B4

           STW     .D1T1   A4,*+A11(16)      ; |69| 
           NOP             3

   [!A0]   BNOP    .S1     $C$L16,5          ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 
|| [ A0]   ADD     .L2     4,B4,B4

           ; BRANCHCC OCCURS {$C$L16}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1X    B13,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L17            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |212| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |212| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1X    B12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |212| 
||         ADDKPC  .S2     $C$RL47,B3,0      ; |212| 

$C$RL47:   ; CALL OCCURS {_print_test_results} {0}  ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |213| 

$C$RL48:   ; CALL OCCURS {_printf} {0}       ; |213| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |213| 

$C$RL49:   ; CALL OCCURS {_printf} {0}       ; |213| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |220| 

$C$RL50:   ; CALL OCCURS {_print_profile_results} {0}  ; |220| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |223| 

$C$RL51:   ; CALL OCCURS {_print_memory_results} {0}  ; |223| 
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
$C$SL1:	.string	"rsqrtSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_rsqrtf
	.global	_rsqrt
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_rsqrtsp
	.global	_rsqrtsp_c
	.global	_rsqrtsp_v
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
