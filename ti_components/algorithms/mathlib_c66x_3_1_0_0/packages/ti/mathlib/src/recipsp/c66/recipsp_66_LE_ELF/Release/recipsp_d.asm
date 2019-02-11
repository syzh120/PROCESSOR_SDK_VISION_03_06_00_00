;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:55:07 2013                                *
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
	.word	0c27c3dc1h		; a[0] @ 0
	.word	0c2af376ch		; a[1] @ 32
	.word	0c267c9a1h		; a[2] @ 64
	.word	042560122h		; a[3] @ 96
	.word	0c29ae88ah		; a[4] @ 128
	.word	041b38a67h		; a[5] @ 160
	.word	0425f7412h		; a[6] @ 192
	.word	0425ae64fh		; a[7] @ 224
	.word	0c22b00cch		; a[8] @ 256
	.word	0427924f6h		; a[9] @ 288

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\083602 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\083604 
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
           STW     .D2T1   A11,*SP--(8)      ; |91| 
           STW     .D2T1   A10,*SP--(8)      ; |91| 
           STDW    .D2T2   B13:B12,*SP--     ; |91| 
           STDW    .D2T2   B11:B10,*SP--     ; |91| 
           STDW    .D2T1   A15:A14,*SP--     ; |91| 

           STDW    .D2T1   A13:A12,*SP--     ; |91| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(40)      ; |91| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |99| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S1     a,A11

           MVKH    .S1     a,A11
||         MVKL    .S2     output,B13

           MVKH    .S2     output,B13

           MV      .L2X    A11,B10
||         CALL    .S1     __c6xabi_divf     ; |108| 
||         LDW     .D2T1   *B13,A12

           LDW     .D2T2   *B10++,B4         ; |108| 
           ZERO    .L1     A4
           SET     .S1     A4,0x17,0x1d,A4
           MVK     .L1     0xa,A10
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL1,B3,0       ; |108| 
$C$RL1:    ; CALL OCCURS {__c6xabi_divf} {0}  ; |108| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |107| 
||         STW     .D1T1   A4,*A12++         ; |108| 
||         SUB     .S1     A10,1,A10         ; |107| 

   [ A0]   B       .S1     $C$L1             ; |107| 
|| [ A0]   LDW     .D2T2   *B10++,B4         ; |108| 
|| [!A0]   MVK     .L2     0xa,B5
|| [ A0]   ZERO    .L1     A4
|| [!A0]   ADD     .S2     4,B13,B4
|| [!A0]   MV      .D1     A11,A12

   [ A0]   CALL    .S1     __c6xabi_divf     ; |108| 
   [!A0]   ZERO    .L2     B10
   [!A0]   STW     .D2T2   B4,*+SP(20)
   [ A0]   SET     .S1     A4,0x17,0x1d,A4
   [!A0]   MV      .L1X    B5,A10
           ; BRANCHCC OCCURS {$C$L1}         ; |107| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     recipsp           ; |111| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |111| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |111| 
$C$RL2:    ; CALL OCCURS {recipsp} {0}       ; |111| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(20),B4       ; |111| 
           SUB     .L1     A10,1,A0          ; |110| 
           SUB     .L1     A10,1,A10         ; |110| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |111| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |110| 

           ADD     .L2     B10,B4,B4         ; |111| 
||         ADD     .S2     4,B10,B10         ; |110| 

   [ A0]   CALL    .S1     recipsp           ; |111| 
||         STW     .D2T1   A4,*B4            ; |111| 

           ; BRANCHCC OCCURS {$C$L2}         ; |110| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(20),B4
           MVK     .L2     0xa,B5
           ZERO    .L2     B10
           MV      .L1     A11,A13
           MV      .L1X    B5,A12
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(24)
||         CALL    .S1     recipsp_c         ; |114| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A13++,A4         ; |114| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |114| 
$C$RL3:    ; CALL OCCURS {recipsp_c} {0}     ; |114| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(24),B4       ; |114| 
           SUB     .L1     A12,1,A0          ; |113| 
           SUB     .L1     A12,1,A12         ; |113| 
   [!A0]   ZERO    .L1     A3
           NOP             1
           LDW     .D2T2   *B4,B4            ; |114| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |113| 

           ADD     .L2     B10,B4,B4         ; |114| 
||         ADD     .S2     4,B10,B10         ; |113| 

   [ A0]   CALL    .S1     recipsp_c         ; |114| 
|| [!A0]   MVKL    .S2     0x7f7fffff,B10
||         STW     .D2T1   A4,*B4            ; |114| 

           ; BRANCHCC OCCURS {$C$L3}         ; |113| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           SET     .S1     A3,0x1e,0x1e,A3
||         MVKH    .S2     0x7f7fffff,B10
||         MVK     .L1     9,A1
||         LDW     .D2T2   *+B13(12),B8
||         ZERO    .L2     B4

           DINT                              ; interrupts off
||         MV      .L2X    A11,B7

           MV      .L2X    A3,B5
||         MV      .L1X    B10,A3

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/recipsp/recipsp_d.c
;*      Loop source line                 : 116
;*      Loop opening brace source line   : 116
;*      Loop closing brace source line   : 118
;*      Known Minimum Trip Count         : 10                    
;*      Known Maximum Trip Count         : 10                    
;*      Known Max Trip Count Factor      : 10
;*      Loop Carried Dependency Bound(^) : 29
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 4
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     3        1     
;*      .D units                     0        2     
;*      .M units                     0        4*    
;*      .X cross paths               1        0     
;*      .T address paths             0        2     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        2     (.L or .S unit)
;*      Addition ops (.LSD)          0        1     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             2        2     
;*      Bound(.L .S .D .LS .LSD)     1        2     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 29 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: | * *                            |    ** **                       |
;*       1: | * *                            |    ** **                       |
;*       2: | * *                            |    ** **                       |
;*       3: | * *                            |    ** **                       |
;*       4: | * *                            |    ** **                       |
;*       5: | * *                            |    *****                       |
;*       6: | * **                           |    *****       *               |
;*       7: | * **                           |    *****       *               |
;*       8: | * **                           |    *****       *               |
;*       9: | * **                           |    *****       *               |
;*      10: | * **                           |    ******      *               |
;*      11: | * **                           |    *****       *               |
;*      12: | * **                           |    *****       *               |
;*      13: | * **                           |    ******      *               |
;*      14: | * **                           |    *****                       |
;*      15: | * **                           |    *****                       |
;*      16: | * **                           |    *****                       |
;*      17: | * **                           |    ******                      |
;*      18: | * **                           |    ** ***                      |
;*      19: | * **                           |    ** ***                      |
;*      20: | * **                           |    ** ***                      |
;*      21: | * **                           |    ******                      |
;*      22: | * **                           |    ** ***                      |
;*      23: |** *                            |    ** ***                      |
;*      24: |** *                            |    ******      *               |
;*      25: | * *                            |    ** **       *               |
;*      26: | * *                            |    ** **       *               |
;*      27: | * *                            |    ** **       *               |
;*      28: | * *                            |    ** **       *               |
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
;*      Total cycles (est.)         : 0 + min_trip_cnt * 29 = 290        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A1,1,A1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C85:
;*   0              LDW     .D2T2   *B7++,B6          ; |62|  ^ 
;*   1              NOP             4
;*   5              RCPSP   .S2     B6,B16            ; |62|  ^ 
;*     ||           ABSSP   .S1X    B6,A4             ; |62| 
;*   6              MPYSP   .M2     B16,B6,B9         ; |62|  ^ 
;*   7              NOP             3
;*  10              FSUBSP  .L2     B5,B9,B9          ; |62|  ^ 
;*  11              NOP             2
;*  13              MPYSP   .M2     B16,B9,B9         ; |62|  ^ 
;*  14              NOP             3
;*  17              MPYSP   .M2     B9,B6,B6          ; |62|  ^ 
;*  18              NOP             3
;*  21              FSUBSP  .L2     B5,B6,B6          ; |62|  ^ 
;*  22              CMPGTSP .S1     A4,A3,A0          ; |62| 
;*  23      [ A0]   MV      .S2     B4,B16            ; |62| 
;*     ||   [ A1]   BDEC    .S1     $C$C85,A1         ; |116| 
;*  24      [!A0]   MPYSP   .M2     B9,B6,B16         ; |62|  ^ 
;*  25              NOP             3
;*  28              STW     .D2T2   B16,*B8++         ; |62|  ^ 
;*  29              ; BRANCHCC OCCURS {$C$C85}        ; |116| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 29
           LDW     .D2T2   *B7++,B6          ; |62| <0,0>  ^ 
           NOP             4

           ABSSP   .S1X    B6,A4             ; |62| <0,5> 
||         RCPSP   .S2     B6,B16            ; |62| <0,5>  ^ 

           MPYSP   .M2     B16,B6,B9         ; |62| <0,6>  ^ 
           NOP             3
           FSUBSP  .L2     B5,B9,B9          ; |62| <0,10>  ^ 
           NOP             2
           MPYSP   .M2     B16,B9,B9         ; |62| <0,13>  ^ 
           NOP             3
           MPYSP   .M2     B9,B6,B6          ; |62| <0,17>  ^ 
           NOP             3
           FSUBSP  .L2     B5,B6,B6          ; |62| <0,21>  ^ 
           CMPGTSP .S1     A4,A3,A0          ; |62| <0,22> 

   [ A0]   MV      .S2     B4,B16            ; |62| <0,23> 
|| [ A1]   BDEC    .S1     $C$L5,A1          ; |116| <0,23> 

   [!A0]   MPYSP   .M2     B9,B6,B16         ; |62| <0,24>  ^ 
           NOP             3
           STW     .D2T2   B16,*B8++         ; |62| <0,28>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MV      .L1X    B13,A14

           MV      .L1X    B4,A15
||         MVK     .S1     0xa,A6            ; |119| 
||         RINT                              ; interrupts on
||         MV      .D1     A11,A4            ; |119| 

           CALLP   .S2     recipsp_v,B3
||         LDW     .D1T2   *+A14(16),B4      ; |119| 
||         MV      .L1     A3,A13
||         MV      .S1X    B5,A12

$C$RL4:    ; CALL OCCURS {recipsp_v} {0}     ; |119| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 48
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A14(4),B4       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A14,A4           ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A14,A4           ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         STW     .D2T1   A3,*+B4(4)        ; |66| 
||         LDW     .D1T2   *+A14(8),B4       ; |67| 
||         MVK     .L1     0xa,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1X    B13,A3
||         STW     .D2T1   A4,*+B4(8)        ; |67| 
||         LDW     .D1T2   *+A14(12),B4      ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+SP(24),B5
||         MVKL    .S2     fcn_pass,B31

           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B31
           MVKH    .S2     0xa0b5ed8d,B6

           STW     .D2T1   A4,*+B31(12)      ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           ADDAD   .D2     B5,1,B4
||         MVKL    .S2     output,B5

           MVKH    .S2     output,B5
||         LDW     .D2T2   *B4,B4            ; |69| 

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .L1     0xa,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S1     fcn_pass,A3
           MVKH    .S1     fcn_pass,A3
           ADD     .L1     4,A3,A11
           LDW     .D1T1   *A11,A0           ; |72| 
           MV      .L2X    A3,B5             ; |72| 
           ADD     .L2X    8,A3,B11
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           NOP             1

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B11,B0           ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |123| 
   [!A0]   ZERO    .L1     A3                ; |72| 
   [ A0]   ADD     .L2     4,B11,B4
   [!A0]   MVKL    .S1     all_pass,A4
   [!A0]   MVKH    .S1     all_pass,A4
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
           CALL    .S1     print_test_results ; |123| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x1,A4            ; |123| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |123| 

$C$RL9:    ; CALL OCCURS {print_test_results} {0}  ; |123| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S2     a_sc,B4
||         ZERO    .L1     A3

           LDW     .D2T2   *+SP(24),B30      ; |131| 
||         MVKH    .S2     a_sc,B4
||         SET     .S1     A3,0x17,0x1d,A3
||         ZERO    .L1     A7
||         ZERO    .L2     B5

           MV      .L1     A3,A6             ; |135| 
||         MVKH    .S2     0xff800000,B5
||         MVKH    .S1     0xbf800000,A7

           ADD     .L2     1,B10,B4
||         STDW    .D2T1   A7:A6,*+B4(16)    ; |135| 
||         MV      .L1X    B4,A14            ; |131| 
||         MV      .S2     B4,B6             ; |131| 
||         ZERO    .S1     A5

           MVK     .L2     0x6,B4
||         STDW    .D2T2   B5:B4,*+B6(8)     ; |133| 
||         MV      .S2     B6,B31            ; |133| 
||         MVKH    .S1     0x80000000,A5
||         MV      .L1     A15,A4            ; |131| 

           ZERO    .L1     A4
||         STDW    .D2T1   A5:A4,*B31        ; |131| 

           CALL    .S2     __c6xabi_divf     ; |137| 
||         MV      .L1X    B4,A10            ; |133| 
||         ADD     .L2     4,B30,B10
||         SET     .S1     A4,0x17,0x1d,A4
||         ZERO    .D2     B12

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
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A14,B4           ; |137| 
           ADDKPC  .S2     $C$RL10,B3,3      ; |137| 
$C$RL10:   ; CALL OCCURS {__c6xabi_divf} {0}  ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D2T2   *B13,B4           ; |137| 
           NOP             4
           ADD     .L2     B12,B4,B4         ; |137| 
           STW     .D2T1   A4,*B4            ; |137| 

           CALLP   .S2     recipsp,B3
||         LDW     .D1T1   *A14,A4           ; |138| 

$C$RL11:   ; CALL OCCURS {recipsp} {0}       ; |138| 
           LDW     .D2T2   *+B13(4),B4       ; |138| 
           NOP             4
           ADD     .L2     B12,B4,B4         ; |138| 
           STW     .D2T1   A4,*B4            ; |138| 

           CALLP   .S2     recipsp_c,B3
||         LDW     .D1T1   *A14,A4           ; |139| 

$C$RL12:   ; CALL OCCURS {recipsp_c} {0}     ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 37
           LDW     .D2T2   *+B13(8),B4       ; |139| 
           LDW     .D2T2   *B10,B31          ; |140| 
           SUB     .L1     A10,1,A2          ; |136| 
           SUB     .L1     A10,1,A10         ; |136| 
           NOP             1
           ADD     .L2     B12,B4,B4         ; |139| 
           STW     .D2T1   A4,*B4            ; |139| 
           LDW     .D1T1   *A14++,A4         ; |62| 
           ADD     .L2     B12,B31,B30       ; |140| 
           ADD     .L2     4,B12,B12         ; |136| 
           NOP             2
           RCPSP   .S1     A4,A3             ; |62| 
           MPYSP   .M1     A3,A4,A5          ; |62| 
           ABSSP   .S2X    A4,B5             ; |64| 
           NOP             2
           FSUBSP  .L1     A12,A5,A5         ; |62| 
           CMPGTSP .S1X    B5,A13,A0         ; |64| 
           NOP             1
           MPYSP   .M1     A3,A5,A3          ; |62| 
           NOP             3
           MPYSP   .M1     A3,A4,A5          ; |62| 
   [ A2]   ZERO    .L1     A4
   [ A2]   SET     .S1     A4,0x17,0x1d,A4
           NOP             1
           FSUBSP  .L1     A12,A5,A5         ; |62| 
           NOP             2

   [ A2]   BNOP    .S1     $C$L8,3           ; |136| 
||         MPYSP   .M1     A3,A5,A3          ; |62| 

   [ A0]   MV      .L1     A15,A3            ; |65| 

   [ A2]   CALL    .S1     __c6xabi_divf     ; |137| 
||         STW     .D2T1   A3,*B30           ; |140| 

           ; BRANCHCC OCCURS {$C$L8}         ; |136| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     recipsp_v         ; |142| 
           LDW     .D2T2   *+B10(4),B4       ; |142| 
           MVKL    .S1     a_sc,A4
           MVKH    .S1     a_sc,A4
           ADDKPC  .S2     $C$RL13,B3,0      ; |142| 
           MVK     .L1     0x6,A6            ; |142| 
$C$RL13:   ; CALL OCCURS {recipsp_v} {0}     ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T1   *B13,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVK     .L1     0x6,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .L1     0x6,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5

           LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |68| 
||         MVK     .L1     0x6,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5

           MVKL    .S1     output,A3
||         MVKH    .S2     0x3eb0c6f7,B7

           MVKH    .S1     output,A3
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         LDW     .D2T2   *+B13(16),B4      ; |69| 
||         MVK     .L1     0x6,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A11,A0           ; |72| 
           STW     .D2T2   B11,*+SP(28)      ; |72| 
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 

   [!A0]   B       .S1     $C$L9             ; |72| 
|| [ A0]   MV      .L2     B11,B4

   [!A0]   CALL    .S1     print_test_results ; |146| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   ZERO    .L1     A4                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A3
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKH    .S1     all_pass,A3
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
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
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |146| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |146| 

$C$RL18:   ; CALL OCCURS {print_test_results} {0}  ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S2     a_ext,B4
           MVKL    .S2     0xc000cccc,B13
           MVKL    .S2     0xcccccccd,B12
           MVK     .S2     0xed,B31

           MVKH    .S2     a_ext,B4
||         ZERO    .L1     A4

           MVKH    .S2     0xc000cccc,B13
||         SET     .S1     A4,0x17,0x17,A4

           ZERO    .L1     A4
||         STW     .D2T1   A4,*B4            ; |149| 
||         MVKH    .S2     0xcccccccd,B12
||         MV      .S1X    B10,A10

           CALL    .S2     __c6xabi_divf     ; |151| 
||         SET     .S1     A4,0x17,0x1d,A4
||         MV      .L1X    B4,A14            ; |149| 
||         STW     .D2T2   B31,*+SP(12)      ; |149| 
||         ZERO    .L2     B10

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
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A14,B4           ; |151| 
           ADDKPC  .S2     $C$RL19,B3,3      ; |151| 
$C$RL19:   ; CALL OCCURS {__c6xabi_divf} {0}  ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T1   *B4,A3            ; |151| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |151| 
           STW     .D1T1   A4,*A3            ; |151| 

           CALLP   .S2     recipsp,B3
||         LDW     .D1T1   *A14,A4           ; |152| 

$C$RL20:   ; CALL OCCURS {recipsp} {0}       ; |152| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |152| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |152| 
           STW     .D2T1   A4,*B4            ; |152| 

           CALLP   .S2     recipsp_c,B3
||         LDW     .D1T1   *A14,A4           ; |153| 

$C$RL21:   ; CALL OCCURS {recipsp_c} {0}     ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 57
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |153| 
           MV      .L2X    A4,B5             ; |153| 
           NOP             3
           ADD     .L2     B10,B4,B4         ; |153| 
           STW     .D2T2   B5,*B4            ; |153| 
           LDW     .D1T1   *A14,A4           ; |62| 
           MV      .L2X    A10,B5            ; |154| 
           LDW     .D2T2   *B5,B4            ; |154| 
           NOP             2
           RCPSP   .S1     A4,A3             ; |62| 
           MPYSP   .M1     A3,A4,A5          ; |62| 
           ABSSP   .S2X    A4,B6             ; |64| 
           ADD     .L2     B10,B4,B4         ; |154| 
           CMPGTSP .S1X    B6,A13,A0         ; |64| 
           FSUBSP  .L1     A12,A5,A5         ; |62| 
           ADD     .L2     4,B10,B10         ; |150| 
           NOP             1
           MPYSP   .M1     A3,A5,A3          ; |62| 
           NOP             3
           MPYSP   .M1     A3,A4,A5          ; |62| 
           NOP             3
           FSUBSP  .L1     A12,A5,A5         ; |62| 
           NOP             2
           MPYSP   .M1     A3,A5,A3          ; |62| 
           NOP             3
   [ A0]   MV      .L1     A15,A3            ; |65| 
           STW     .D2T1   A3,*B4            ; |154| 
           LDW     .D1T2   *A14,B4           ; |155| 
           NOP             4

           MPYSPDP .M2     B4,B13:B12,B7:B6  ; |155| 
||         LDW     .D2T2   *+SP(12),B4

           NOP             4

           SUB     .L1X    B4,1,A0           ; |150| 
||         SUB     .L2     B4,1,B4           ; |150| 

   [ A0]   ZERO    .L1     A4

   [ A0]   BNOP    .S2     $C$L10,3          ; |150| 
||         DPSP    .L2     B7:B6,B6          ; |155| 
|| [ A0]   SET     .S1     A4,0x17,0x1d,A4

           STW     .D1T2   B6,*++A14         ; |155| 

   [ A0]   CALL    .S1     __c6xabi_divf     ; |151| 
||         STW     .D2T2   B4,*+SP(12)       ; |155| 

           ; BRANCHCC OCCURS {$C$L10}        ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     recipsp_v         ; |157| 
           LDW     .D2T2   *+B5(4),B4        ; |157| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           ADDKPC  .S2     $C$RL22,B3,0      ; |157| 
           MVK     .S1     0xed,A6           ; |157| 
$C$RL22:   ; CALL OCCURS {recipsp_v} {0}     ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 44
           MVKL    .S2     output,B10
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     output,B10
           MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL23:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B12
           MVKH    .S2     fcn_pass,B12
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B12(4)       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B12(8)       ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1X    B10,A3            ; |68| 
||         STW     .D2T1   A4,*+B12(12)      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(16),B4      ; |69| 
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MV      .L1     A11,A3            ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A4,*+B12(16)      ; |69| 
           NOP             3

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B11,B0           ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |161| 
   [ A0]   ADD     .L2     4,B11,B4
   [!A0]   ZERO    .L1     A4                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
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
           CALL    .S1     print_test_results ; |161| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |161| 
||         ADDKPC  .S2     $C$RL27,B3,0      ; |161| 

$C$RL27:   ; CALL OCCURS {print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16

           ZERO    .L2     B13               ; |114| 
||         MVKL    .S2     cycle_counts+24,B5

           MVKH    .S2     cycle_counts+24,B5
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .D2     B12               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T2   B13:B12,*B5       ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     t_start,A3

           MVKH    .S1     t_start,A3
||         MV      .L2     B4,B7             ; |116| 

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B7:B6,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           SUB     .L2     B8,B7,B6          ; |117| 
||         EXT     .S2     B5,24,24,B5       ; |117| 
||         MVKL    .S1     t_offset,A4

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S1     t_offset,A4

           MVK     .S2     0x80,B4
||         STDW    .D1T2   B5:B4,*A4         ; |117| 
||         MVKL    .S1     input,A3

           ZERO    .L1     A4
||         MVKH    .S1     input,A3

           ZERO    .L2     B4
||         MV      .L1X    B4,A10            ; |117| 
||         MVKH    .S1     0x43480000,A4

           CALL    .S1     gimme_random      ; |171| 
||         MVKH    .S2     0xc2c80000,B4
||         MV      .L2     B12,B10

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
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A14           ; |171| 
           ADDKPC  .S2     $C$RL28,B3,3      ; |171| 
$C$RL28:   ; CALL OCCURS {gimme_random} {0}  ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           ADD     .L1X    A14,B10,A3        ; |171| 

           STW     .D1T1   A4,*A3            ; |171| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B4           ; |122| 
           RCPSP   .S1     A4,A3             ; |62| 
           MPYSP   .M1     A3,A4,A5          ; |62| 
           MV      .L2X    A14,B11           ; |64| 
           MV      .L2     B4,B7             ; |122| 
           MVKL    .S2     output+12,B5
           FSUBSP  .L1     A12,A5,A5         ; |62| 
           ADD     .L1X    A14,B10,A31       ; |64| 
           MVKL    .S1     t_start,A30
           MPYSP   .M1     A3,A5,A5          ; |62| 
           MVKH    .S2     output+12,B5
           LDW     .D1T1   *A31,A6           ; |64| 
           LDW     .D2T2   *B5,B5            ; |175| 
           MPYSP   .M1     A5,A4,A4          ; |62| 
           MVKH    .S1     t_start,A30
           STDW    .D1T2   B7:B6,*A30
           ABSSP   .S1     A6,A3             ; |64| 
           FSUBSP  .L1     A12,A4,A4         ; |62| 
           ADD     .L2     B10,B5,B4         ; |175| 
           CMPGTSP .S1     A3,A13,A0         ; |64| 
           MPYSP   .M1     A5,A4,A4          ; |62| 
           NOP             3
   [ A0]   MV      .L1     A15,A4            ; |65| 

           STW     .D2T1   A4,*B4            ; |175| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B17          ; |128| 

           MVKL    .S1     t_offset,A3
||         MVKL    .S2     cycle_counts+24,B4
||         SUB     .L1     A10,1,A0          ; |169| 
||         ADD     .L2     4,B10,B10         ; |169| 
||         SUB     .D1     A10,1,A10         ; |169| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     cycle_counts+24,B4

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         LDDW    .D2T2   *B4,B9:B8         ; |130| 
||         MVKL    .S1     t_stop,A29

           MVKL    .S1     cycle_counts+24,A14
   [ A0]   MVKL    .S1     input,A3
           MVKH    .S1     t_stop,A29

           MVKH    .S1     cycle_counts+24,A14
||         STDW    .D1T2   B17:B16,*A29      ; |128| 

           ADDU    .L2X    A4,B6,B5:B4       ; |130| 
|| [ A0]   ZERO    .L1     A4
|| [ A0]   MVKH    .S1     input,A3

           ADD     .D2X    B5,A5,B6          ; |130| 
|| [ A0]   B       .S2     $C$L12            ; |169| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 
|| [ A0]   MVKH    .S1     0x43480000,A4

           ADD     .D2     B6,B7,B6          ; |130| 
||         ADDU    .L2     B8,B4,B5:B4       ; |130| 
||         EXT     .S2     B5,24,24,B8       ; |130| 

           SUB     .L2     B17,B6,B7         ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         ADD     .D2     B5,B9,B4          ; |130| 

           ADD     .L2     B7,B8,B5          ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
|| [ A0]   ZERO    .S2     B4

   [ A0]   CALL    .S1     gimme_random      ; |171| 
|| [ A0]   MVKH    .S2     0xc2c80000,B4
||         STDW    .D1T2   B7:B6,*A14        ; |130| 

           ; BRANCHCC OCCURS {$C$L12}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     __c6xabi_fltllif  ; |135| 
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |135| 
$C$RL29:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           MV      .L1X    B13,A12           ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL30:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MV      .L2X    A14,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           SUBAW   .D2     B4,6,B10
||         MV      .L2     B12,B5            ; |114| 

           STDW    .D2T2   B13:B12,*B10      ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MV      .L1X    B4,A15            ; |116| 

           MV      .L1X    B5,A14            ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 
           SUBU    .L2X    B5,A15,B7:B6      ; |117| 

           SUB     .L1X    B4,A14,A4         ; |117| 
||         MVK     .S1     0x80,A30

           MV      .L1X    B6,A3             ; |117| 
||         EXT     .S2     B7,24,24,B4       ; |117| 
||         MVKL    .S1     output,A31
||         STW     .D2T1   A30,*+SP(12)      ; |117| 

           STW     .D2T1   A3,*+SP(16)       ; |117| 
||         MVKH    .S1     output,A31
||         CALL    .S2     __c6xabi_divf     ; |183| 

           ADD     .L1X    A4,B4,A10         ; |117| 
||         LDW     .D2T2   *B11++,B4         ; |183| 
||         LDW     .D1T1   *A31,A12

           ZERO    .L1     A4
           SET     .S1     A4,0x17,0x1d,A4
           NOP             1
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL31,B3,0      ; |183| 
$C$RL31:   ; CALL OCCURS {__c6xabi_divf} {0}  ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T1   *+SP(12),A3       ; |183| 
           STW     .D1T1   A4,*A12++         ; |183| 
           NOP             3

           SUB     .L1     A3,1,A0           ; |182| 
||         SUB     .S1     A3,1,A3           ; |182| 

   [ A0]   B       .S1     $C$L13            ; |182| 
||         STW     .D2T1   A3,*+SP(12)       ; |183| 

   [ A0]   CALL    .S1     __c6xabi_divf     ; |183| 
   [ A0]   LDW     .D2T2   *B11++,B4         ; |183| 
   [ A0]   ZERO    .L1     A4
   [ A0]   SET     .S1     A4,0x17,0x1d,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L13}        ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 
           LDW     .D2T1   *+SP(16),A3       ; |128| 
           MV      .L2     B4,B7             ; |128| 
           LDDW    .D2T2   *B10,B5:B4        ; |130| 
           NOP             2
           ADDU    .L1     A3,A15,A5:A4      ; |130| 

           ADD     .S1     A5,A10,A3         ; |130| 
||         SUBU    .L1X    B6,A4,A5:A4       ; |130| 
||         CALL    .S2     __c6xabi_fltllif  ; |130| 

           ADD     .L1     A3,A14,A3         ; |130| 
||         EXT     .S1     A5,24,24,A31      ; |130| 

           ADDU    .L2X    B4,A4,B9:B8       ; |130| 
||         SUB     .L1X    B7,A3,A3          ; |130| 
||         MVKL    .S2     t_stop,B4

           ADD     .L2     B9,B5,B5          ; |130| 
||         ADD     .L1     A3,A31,A3         ; |130| 
||         MVKH    .S2     t_stop,B4

           STDW    .D2T2   B7:B6,*B4         ; |128| 
||         MV      .L1X    B8,A4             ; |130| 

           ADD     .L1X    B5,A3,A5          ; |130| 
||         ADDKPC  .S2     $C$RL32,B3,0      ; |130| 

$C$RL32:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B13,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13

           MV      .L2     B12,B4            ; |114| 
||         STDW    .D2T2   B13:B12,*+B10(8)  ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A5:A4,*B10        ; |130| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     t_start,A10

           MVKH    .S1     t_start,A10
||         MV      .L2     B4,B9             ; |116| 

           MVC     .S2     TSCL,B5           ; |117| 
||         STDW    .D1T2   B9:B8,*A10        ; |116| 

           MVC     .S2     TSCH,B4           ; |117| 

           SUBU    .L2     B5,B8,B7:B6       ; |117| 
||         MVKL    .S2     t_offset,B31

           EXT     .S2     B7,24,24,B4       ; |117| 
||         SUB     .L2     B4,B9,B5          ; |117| 

           MVK     .S2     0x80,B4
||         ADD     .L2     B5,B4,B7          ; |117| 

           MVKH    .S2     t_offset,B31
||         LDW     .D2T2   *+SP(20),B11      ; |117| 
||         MVKL    .S1     input,A14

           MV      .L1X    B4,A15            ; |117| 
||         STDW    .D2T2   B7:B6,*B31        ; |117| 
||         MVKH    .S1     input,A14

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
||         CALL    .S1     recipsp           ; |191| 

           LDW     .D1T1   *A3,A4            ; |191| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |191| 
$C$RL34:   ; CALL OCCURS {recipsp} {0}       ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |191| 
||         SUB     .L1     A15,1,A0          ; |190| 
||         SUB     .S1     A15,1,A15         ; |190| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |190| 

           ADD     .L1X    A12,B4,A3         ; |191| 
||         ADD     .S1     4,A12,A12         ; |190| 

           STW     .D1T1   A4,*A3            ; |191| 
           ; BRANCHCC OCCURS {$C$L14}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     t_offset,B5
||         LDDW    .D1T1   *A10,A5:A4        ; |130| 

           MVKH    .S2     t_offset,B5
           LDDW    .D2T2   *B5,B7:B6         ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             3
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 

           ADD     .L1X    A7,B7,A3          ; |130| 
||         LDDW    .D2T2   *+B10(8),B7:B6    ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B9,A3,B31         ; |130| 
           CALL    .S1     __c6xabi_fltllif  ; |130| 

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
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B13,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           STDW    .D2T2   B13:B12,*+B10(16) ; |114| 

           ADDAD   .D2     B10,1,B11
||         MV      .L2     B12,B4            ; |114| 

           STDW    .D2T1   A5:A4,*B11        ; |130| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MV      .L1     A10,A12           ; |116| 

           STDW    .D1T2   B5:B4,*A12        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKL    .S2     t_offset,B31

           EXT     .S2     B7,24,24,B4       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           ADD     .L2     B5,B4,B7          ; |117| 
||         MVKH    .S2     t_offset,B31

           STDW    .D2T2   B7:B6,*B31        ; |117| 
           LDW     .D1T1   *A14,A3           ; |199| 
           MV      .L1X    B13,A15
           MVK     .S2     0x80,B30
           LDW     .D2T1   *+SP(24),A10      ; |117| 
           STW     .D2T2   B30,*+SP(12)      ; |117| 

           CALL    .S1     recipsp_c         ; |199| 
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
$C$RL37:   ; CALL OCCURS {recipsp_c} {0}     ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MV      .L2X    A10,B4            ; |199| 
           LDW     .D2T2   *B4,B4            ; |199| 
           STW     .D2T1   A10,*+SP(16)      ; |199| 
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

   [ A0]   CALL    .S1     recipsp_c         ; |199| 
||         ADD     .L1     A15,A3,A3         ; |199| 

           ; BRANCHCC OCCURS {$C$L15}        ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S2     t_offset,B4
||         MV      .L1     A12,A10           ; |128| 

           MVKH    .S2     t_offset,B4
||         LDDW    .D1T1   *A10,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B9:B8         ; |130| 
           MV      .L2     B10,B31           ; |130| 
           LDDW    .D2T2   *+B31(16),B17:B16 ; |130| 
           MV      .L1X    B10,A15           ; |130| 
           NOP             1
           ADDU    .L2X    B8,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B9,B8          ; |130| 
||         SUBU    .L2     B6,B4,B5:B4       ; |130| 

           ADD     .L2X    B8,A5,B8          ; |130| 
||         CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .S2     B7,B8,B4          ; |130| 
||         ADDU    .L2     B16,B4,B9:B8      ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B9,B17,B4         ; |130| 

           ADD     .L2     B4,B5,B9          ; |130| 
||         MVKL    .S2     t_stop,B4

           MVKH    .S2     t_stop,B4

           STDW    .D2T2   B7:B6,*B4         ; |128| 
||         DADD    .L1X    0,B9:B8,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL38,B3,0      ; |130| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 110
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B13,A12           ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 

           ADDAD   .D2     B11,1,B10
||         MV      .L2X    A15,B4

           MV      .L2     B12,B31           ; |114| 
||         STDW    .D2T2   B13:B12,*+B4(32)  ; |114| 

           STDW    .D2T1   A5:A4,*B10        ; |130| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A10        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         LDW     .D2T2   *+SP(16),B4       ; |117| 

           MV      .L2X    A14,B9            ; |206| 
           MVKL    .S2     t_offset,B11
           LDW     .D2T1   *B9,A4            ; |206| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B5,B7          ; |117| 

           LDW     .D2T2   *+B4(8),B4        ; |206| 
||         ADD     .L2     B7,B5,B7          ; |117| 
||         MVKH    .S2     t_offset,B11

           CALLP   .S2     recipsp_v,B3
||         STDW    .D2T2   B7:B6,*B11        ; |117| 
||         MVK     .S1     0x80,A6           ; |206| 

$C$RL40:   ; CALL OCCURS {recipsp_v} {0}     ; |206| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S1     16,A10
           ADD     .L1X    B10,A10,A10
           LDDW    .D1T1   *A10,A9:A8        ; |130| 
           MVKL    .S1     t_stop,A3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           MVKH    .S1     t_stop,A3
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

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL41:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 

           MVKL    .S1     output,A3
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     output,A3
||         MVKL    .S2     0x3eb0c6f7,B7

           MV      .L1     A3,A12            ; |130| 
||         STDW    .D1T1   A5:A4,*A10        ; |130| 
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D1T1   *A12,A4           ; |66| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A12(4),B4       ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL43:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     fcn_pass,B10
           MVKH    .S2     0x3eb0c6f7,B7
           MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A12,A4           ; |67| 
||         MVKH    .S2     fcn_pass,B10

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A12(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           MV      .L1     A4,A3             ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D1T2   *+A12(12),B4      ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7
||         STW     .D2T1   A3,*+B10(8)       ; |67| 

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1     A12,A3            ; |68| 
||         STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *+A12(16),B4      ; |69| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           LDW     .D1T1   *A11,A0           ; |72| 
||         LDW     .D2T2   *+SP(28),B4

           STW     .D2T1   A4,*+B10(16)      ; |69| 
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
   [ A0]   CALL    .S1     print_test_results ; |212| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |212| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1X    B12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L17:    
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
$C$SL1:	.string	"recipSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	recipsp
	.global	recipsp_c
	.global	recipsp_v
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
	.global	__c6xabi_divf
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
