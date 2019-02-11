;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:58:08 2013                                *
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
	.word	0d4b92a59h,040319e52h		; _a[0] @ 0
	.word	0cb85a4f0h,04046892ah		; _a[1] @ 64
	.word	0e5c5c217h,0c0537053h		; _a[2] @ 128
	.word	058d2ffedh,04043f9b1h		; _a[3] @ 192
	.word	07eefca28h,0c05885a6h		; _a[4] @ 256
	.word	0766333ach,0c04324bbh		; _a[5] @ 320
	.word	044e0daa1h,0c052df74h		; _a[6] @ 384
	.word	0482d963bh,0c04d34e9h		; _a[7] @ 448
	.word	057fec497h,0404dc9c2h		; _a[8] @ 512
	.word	0d976287bh,0c0458554h		; _a[9] @ 576
$C$IR_1:	.set	80

	.global	_a
_a:	.usect	".far",80,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\143122 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\143124 
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
;*   Local Frame Size  : 8 Args + 196 Auto + 56 Save = 260 byte               *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           STW     .D2T1   A11,*SP--(8)      ; |90| 
           STW     .D2T1   A10,*SP--(8)      ; |90| 
           STDW    .D2T2   B13:B12,*SP--     ; |90| 
           STDW    .D2T2   B11:B10,*SP--     ; |90| 
           STDW    .D2T1   A15:A14,*SP--     ; |90| 
           STDW    .D2T1   A13:A12,*SP--     ; |90| 
           STW     .D2T2   B3,*SP--(8)       ; |90| 

           MVKL    .S1     $C$SL1+0,A4
||         ADDK    .S2     -208,SP           ; |90| 

           CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |98| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     _a,A12
||         MVKL    .S2     _output,B4

           MVKH    .S1     _a,A12
||         MVKH    .S2     _output,B4

           MV      .L1     A12,A13
||         CALL    .S1     _sin              ; |107| 
||         LDW     .D2T1   *B4,A11

           LDDW    .D1T1   *A13++,A5:A4      ; |107| 
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
           ADDKPC  .S2     $C$RL1,B3,0       ; |107| 
$C$RL1:    ; CALL OCCURS {_sin} {0}          ; |107| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |106| 
||         STDW    .D1T1   A5:A4,*A11++      ; |107| 
||         SUB     .S1     A10,1,A10         ; |106| 

   [ A0]   B       .S1     $C$L1             ; |106| 
|| [!A0]   MVKL    .S2     _output,B4
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |107| 
|| [!A0]   ZERO    .L2     B10
|| [!A0]   MV      .L1     A12,A10

   [ A0]   CALL    .S1     _sin              ; |107| 
   [!A0]   MVK     .L1     0xa,A11
   [!A0]   MVKH    .S2     _output,B4
   [!A0]   ADD     .L2     4,B4,B4
   [!A0]   STW     .D2T2   B4,*+SP(16)
           ; BRANCHCC OCCURS {$C$L1}         ; |106| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _sindp            ; |110| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |110| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |110| 
$C$RL2:    ; CALL OCCURS {_sindp} {0}        ; |110| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(16),B4       ; |110| 
           SUB     .L1     A11,1,A0          ; |109| 
           SUB     .L1     A11,1,A11         ; |109| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |110| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |109| 

           ADD     .L2     B10,B4,B4         ; |110| 
||         ADD     .S2     8,B10,B10         ; |109| 

   [ A0]   CALL    .S1     _sindp            ; |110| 
||         STDW    .D2T1   A5:A4,*B4         ; |110| 

           ; BRANCHCC OCCURS {$C$L2}         ; |109| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(16),B4
           ZERO    .L2     B10
           MV      .L1     A12,A10
           MVK     .L1     0xa,A11
           NOP             1
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(20)
||         CALL    .S1     _sindp_c          ; |113| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |113| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |113| 
$C$RL3:    ; CALL OCCURS {_sindp_c} {0}      ; |113| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(20),B4       ; |113| 
           SUB     .L1     A11,1,A0          ; |112| 
           SUB     .L1     A11,1,A11         ; |112| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |113| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |112| 

           ADD     .L2     B10,B4,B4         ; |113| 
||         ADD     .S2     8,B10,B10         ; |112| 

   [ A0]   CALL    .S1     _sindp_c          ; |113| 
||         STDW    .D2T1   A5:A4,*B4         ; |113| 

           ; BRANCHCC OCCURS {$C$L3}         ; |112| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26

           MVKL    .S2     0x4b5dc0ab,B4
||         LDW     .D2T1   *+SP(20),A20      ; |87| 
||         MVKL    .S1     0x55555555,A13
||         ZERO    .L1     A21
||         MVK     .D1     9,A1

           MVKH    .S2     0x4b5dc0ab,B4
||         MVKH    .S1     0x55555555,A13

           STW     .D2T2   B4,*+SP(48)       ; |116| 
||         MV      .L2     B4,B6
||         MVKL    .S2     0x111110b0,B4
||         MVKL    .S1     0x3ce880ff,A30

           MVKH    .S2     0x111110b0,B4
||         MVKL    .S1     0x3de6123c,A31
||         MV      .L2X    A13,B18

           STW     .D2T2   B4,*+SP(60)       ; |116| 
||         MVKL    .S2     0xdc08499c,B30
||         MVKL    .S1     0x3f811111,A11

           MV      .L1X    B4,A8
||         MVKL    .S2     0x686ad430,B4
||         MVKL    .S1     0x40092200,A28
||         ADD     .D1     4,A20,A10

           MVKH    .S2     0x686ad430,B4
||         MVKL    .S1     0x3ec71de3,A15
||         LDW     .D1T2   *A10,B24

           MVKH    .S2     0xdc08499c,B30
||         MVKL    .S1     0xa524f063,A3
||         STW     .D2T2   B4,*+SP(68)       ; |116| 

           MVKL    .S2     0xbe5ae645,B10
||         MVKL    .S1     0x6dc9c883,A24
||         STW     .D2T2   B30,*+SP(52)      ; |116| 

           MVKL    .S2     0xbf2a01a0,B11
||         MVKL    .S1     0x6993df95,A29

           MVKL    .S2     0x1a013e1a,B12
||         MVKL    .S1     0x3fd45f30,A26

           MVKL    .S2     0xbd6ae420,B31
||         MVKH    .S1     0x3ce880ff,A30

           MVKL    .S2     0xbee2aeef,B29
||         MVKH    .S1     0x3de6123c,A31
||         MV      .L1     A30,A23
||         STW     .D2T1   A30,*+SP(80)      ; |116| 
||         ZERO    .D1     A30               ; |87| 

           MVKL    .S2     0xbfc55555,B13
||         MVKH    .S1     0x3f811111,A11
||         STW     .D2T1   A31,*+SP(72)      ; |116| 
||         MV      .L1     A31,A25

           MVKL    .S2     0x4b9ee59e,B28
||         MVKH    .S1     0x40092200,A28
||         MV      .L1     A11,A9

           MVKH    .S2     0xbe5ae645,B10
||         MVKH    .S1     0x3ec71de3,A15
||         STW     .D2T1   A28,*+SP(36)      ; |87| 
||         MV      .L1     A28,A27

           MVKH    .S2     0xbf2a01a0,B11
||         MVKH    .S1     0xa524f063,A3
||         MV      .L1     A15,A7
||         MV      .L2     B10,B7

           MVKH    .S2     0x1a013e1a,B12
||         MVKH    .S1     0x6dc9c883,A24
||         MV      .L1     A3,A6
||         STW     .D2T1   A3,*+SP(64)       ; |116| 
||         MV      .D1     A12,A3
||         MV      .L2     B11,B9

           MVKH    .S2     0xbd6ae420,B31
||         MVKH    .S1     0x6993df95,A29
||         MV      .L1     A24,A28
||         STW     .D2T1   A24,*+SP(28)      ; |87| 
||         MV      .D1X    B4,A24
||         MV      .L2     B12,B8

           MVKH    .S2     0xbee2aeef,B29
||         MVKH    .S1     0x3fd45f30,A26
||         LDW     .D2T2   *+SP(52),B4
||         MV      .L1     A29,A22
||         MV      .L2     B31,B5

           MVKH    .S2     0xbfc55555,B13
||         MVKH    .S1     0x41d00000,A21
||         STW     .D2T2   B31,*+SP(56)      ; |116| 
||         MV      .L2     B29,B21

           MVKH    .S2     0x4b9ee59e,B28
||         STW     .D2T2   B29,*+SP(44)      ; |87| 
||         MV      .L1     A21,A31
||         MV      .L2     B13,B19

           STW     .D2T2   B28,*+SP(40)      ; |87| 
||         MV      .L2     B28,B20
||         DINT                              ; interrupts off

           STW     .D2T1   A29,*+SP(76)      ; |116| 
||         MV      .L1     A26,A29

           STW     .D2T1   A26,*+SP(32)      ; |87| 
||         ZERO    .L1     A26               ; |87| 

           STW     .D2T1   A21,*+SP(24)      ; |87| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/sindp/sindp_d.c
;*      Loop source line                 : 115
;*      Loop opening brace source line   : 115
;*      Loop closing brace source line   : 117
;*      Known Minimum Trip Count         : 10                    
;*      Known Maximum Trip Count         : 10                    
;*      Known Max Trip Count Factor      : 10
;*      Loop Carried Dependency Bound(^) : 82
;*      Unpartitioned Resource Bound     : 8
;*      Partitioned Resource Bound(*)    : 8
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        4     
;*      .S units                     3        4     
;*      .D units                     1        1     
;*      .M units                     8*       7     
;*      .X cross paths               7        5     
;*      .T address paths             1        1     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           8        3     (.L or .S unit)
;*      Addition ops (.LSD)          6        3     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             6        6     
;*      Bound(.L .S .D .LS .LSD)     6        5     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 82 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: | * *  ****            **********|    ******        ****  *       |
;*       1: | * *  ****            **********|    ******        ****  *       |
;*       2: | * *  ****            **********|    ******        ****  *       |
;*       3: | * *  ****            **********|    ******        ****  *       |
;*       4: | * *  ****            **********|    ******        ****  *       |
;*       5: | * *  ****      **    **********|    ******        ****  *       |
;*       6: | * *  ****      **    **********|    ******        ****  *       |
;*       7: | * *******      **    **********|    ******        ****  *       |
;*       8: | * *******      **    **********|    ******        ****  *       |
;*       9: |** *  ****      **    **********|    ******        ****  *       |
;*      10: | * *  ****      **    **********|    ******        ****  *       |
;*      11: | * *  ****      **    **********|    ******        ****  *       |
;*      12: | * *  ****      **    **********|    ******        ****  *       |
;*      13: | * *  ****      **    **********|    ******        ****  *       |
;*      14: | * *******      **    **********|    ******        ****  *       |
;*      15: | * *  ****      **    **********|    ******        ****  *       |
;*      16: | * *  ****      **    **********|    ******        ****  *       |
;*      17: | * *  ****      **    **********|    ******        ****  *       |
;*      18: | * ** ****      **    **********|    ******        ****  *       |
;*      19: |** *  ****      **    **********|    ******        ****  *       |
;*      20: |** *  ****      **    **********|    ******        *******       |
;*      21: |** *  ****      **    **********|    ******        *******       |
;*      22: |** *  ****      **    **********|    ******        *******       |
;*      23: |** *******      **    **********|    ******        *******       |
;*      24: |** *******      **    **********|    ******        *******       |
;*      25: |** *  ****      **    **********|    ******        *******       |
;*      26: |** *  ****      **    **********|    ******        *******       |
;*      27: |** *******      **    **********|    ******        *******       |
;*      28: |** *  ****            **********|    ******      *********       |
;*      29: |** *  ****            **********|    ******      *********       |
;*      30: |** *******            **********|    ******      *********       |
;*      31: |** *  ****            **********|    ******        *******       |
;*      32: |** *  ****            **********|    ******        *******       |
;*      33: |** *  ****          ************|    ******        *******       |
;*      34: |** *  ****          ************|    ******        *******       |
;*      35: |** *  ****          ************|    ******        *******       |
;*      36: |** *  ****          ************|    ******        *******       |
;*      37: |** *  ****      **  ************|    ******        *******       |
;*      38: |** *  ****      **  ************|    ******        *******       |
;*      39: |** *  ****      **  ************|    ******        *******       |
;*      40: |** *  ****      **  ************|    ******        *******       |
;*      41: |** *  ****      ****************|    ******        *******       |
;*      42: |** *  ****      ****************|    ******        *******       |
;*      43: |** *  ****      ****************|    ******        *******       |
;*      44: |** *  ****      ****************|    ******        *******       |
;*      45: |** *******      ****************|    ******        *******       |
;*      46: |** *  ****      ****************|    ******      *********       |
;*      47: |** *  ****      ****************|    ******        *******       |
;*      48: |** *******      ****************|    ******        *******       |
;*      49: |** *  ****      ****************|    ******      *********       |
;*      50: |** *  ****      ****************|    ******        *******       |
;*      51: |** *  ****      ****************|    ******        *******       |
;*      52: |** *******      ****************|    ******        *******       |
;*      53: |** *  ****      ****************|    ******      *********       |
;*      54: |** *  ****      ****************|    ******        *******       |
;*      55: |** *******      ****************|    ******        *******       |
;*      56: |** *  ****      ****************|    ******      *********       |
;*      57: |** *  ****      ****************|    ******        *******       |
;*      58: |** *  ****      ****************|    ******        *******       |
;*      59: |** *******      ****************|    ******        *******       |
;*      60: |** *  ****      ****************|    ******      *********       |
;*      61: |** *  ****      ****************|    ******        *******       |
;*      62: |** *******      ****************|    ******        *******       |
;*      63: |** *  ****      **  ************|    ******      *********       |
;*      64: |** *  ****          ************|    ******        *******       |
;*      65: |** *  ****          ************|    ******        *******       |
;*      66: |** *******          ************|    ******        *******       |
;*      67: |** *******          ************|    ******      *********       |
;*      68: |** *  ****          ************|    ******        *******       |
;*      69: |** *  ****          ************|    ******        *******       |
;*      70: |** *  ****          ************|    ******      *********       |
;*      71: |** *  ****          ************|    ******        *******       |
;*      72: |** *  ****          ************|    ******        *******       |
;*      73: |** *  ****          ************|    ******        *******       |
;*      74: |** *  ****          ************|    ******      *********       |
;*      75: |** *  ****            **********|    ******        *******       |
;*      76: |** *  ****            **********|    ******        *******       |
;*      77: | * *  ****            **********|    ******      *********       |
;*      78: | * *  ****            **********|    ******        ****  *       |
;*      79: | * *  ****            **********|    ******        ****  *       |
;*      80: | * *  ****            **********|    ******        ****  *       |
;*      81: | * *  ****            **********|    ******      ******  *       |
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
;*      Total cycles (est.)         : 0 + min_trip_cnt * 82 = 820        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A1,1,A1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C91:
;*   0              LDDW    .D1T1   *A3++,A17:A16     ; |87|  ^ 
;*   1              NOP             4
;*   5              ABSDP   .S1     A17:A16,A5:A4     ; |87|  ^ 
;*   6              NOP             1
;*   7              CMPGTDP .S1     A5:A4,A31:A30,A0  ; |87|  ^ 
;*   8              NOP             1
;*   9      [ A0]   ZERO    .L1     A17:A16           ; |87|  ^ 
;*  10              FMPYDP  .M1     A29:A28,A17:A16,A5:A4 ; |87|  ^ 
;*  11              NOP             3
;*  14              DPINT   .L1     A5:A4,A4          ; |87|  ^ 
;*  15              NOP             3
;*  18              INTDP   .L1     A4,A5:A4          ; |87|  ^ 
;*     ||           AND     .S1     1,A4,A0           ; |116| 
;*  19      [ A0]   ZERO    .S2     B23
;*     ||   [!A0]   ZERO    .L2     B22               ; |116| 
;*     ||   [!A0]   ZERO    .D2     B23
;*  20      [ A0]   ZERO    .L2     B22               ; |116| 
;*     ||   [ A0]   MVKH    .S2     0xbff00000,B23
;*  21              NOP             2
;*  23              FMPYDP  .M1     A27:A26,A5:A4,A5:A4 ; |87|  ^ 
;*  24              FMPYDP  .M2X    B21:B20,A5:A4,B17:B16 ; |87| 
;*  25              NOP             2
;*  27              FSUBDP  .L1     A17:A16,A5:A4,A5:A4 ; |87|  ^ 
;*  28              NOP             2
;*  30              FSUBDP  .L1X    A5:A4,B17:B16,A21:A20 ; |87|  ^ 
;*  31              NOP             2
;*  33              FMPYDP  .M1     A21:A20,A21:A20,A17:A16 ; |87|  ^ 
;*  34              NOP             3
;*  37              FMPYDP  .M1     A17:A16,A17:A16,A19:A18 ; |116|  ^ 
;*  38              NOP             3
;*  41              FMPYDP  .M1     A23:A22,A19:A18,A5:A4 ; |116|  ^ 
;*  42              FMPYDP  .M2X    B5:B4,A19:A18,B17:B16 ; |116|  ^ 
;*  43              NOP             2
;*  45              FADDDP  .L1     A25:A24,A5:A4,A5:A4 ; |116|  ^ 
;*  46              FADDDP  .L2     B7:B6,B17:B16,B17:B16 ; |116|  ^ 
;*  47              NOP             1
;*  48              FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |116|  ^ 
;*  49              FMPYDP  .M2X    A19:A18,B17:B16,B17:B16 ; |116|  ^ 
;*  50              NOP             2
;*  52              FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |116|  ^ 
;*  53              FADDDP  .L2     B9:B8,B17:B16,B17:B16 ; |116|  ^ 
;*  54              NOP             1
;*  55              FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |116|  ^ 
;*  56              FMPYDP  .M2X    A19:A18,B17:B16,B17:B16 ; |116|  ^ 
;*  57              NOP             2
;*  59              FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |116|  ^ 
;*  60              FADDDP  .L2     B19:B18,B17:B16,B17:B16 ; |116|  ^ 
;*  61              NOP             1
;*  62              FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |116|  ^ 
;*  63              FMPYDP  .M2X    A17:A16,B17:B16,B17:B16 ; |116|  ^ 
;*  64              NOP             3
;*  67              FADDDP  .L2X    B17:B16,A5:A4,B17:B16 ; |116|  ^ 
;*  68              NOP             2
;*  70              FMPYDP  .M2X    A21:A20,B17:B16,B17:B16 ; |116|  ^ 
;*  71              NOP             3
;*  74              FADDDP  .L2X    B17:B16,A21:A20,B17:B16 ; |116|  ^ 
;*  75              NOP             1
;*  76      [!A0]   SET     .S2     B23,0x14,0x1d,B23
;*     ||   [ A1]   BDEC    .S1     $C$C91,A1         ; |115| 
;*  77              FMPYDP  .M2     B23:B22,B17:B16,B17:B16 ; |116|  ^ 
;*  78              NOP             3
;*  81              STDW    .D2T2   B17:B16,*B24++    ; |116|  ^ 
;*  82              ; BRANCHCC OCCURS {$C$C91}        ; |115| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 82
           LDDW    .D1T1   *A3++,A17:A16     ; |87| <0,0>  ^ 
           NOP             4
           ABSDP   .S1     A17:A16,A5:A4     ; |87| <0,5>  ^ 
           NOP             1
           CMPGTDP .S1     A5:A4,A31:A30,A0  ; |87| <0,7>  ^ 
           NOP             1
   [ A0]   ZERO    .L1     A17:A16           ; |87| <0,9>  ^ 
           FMPYDP  .M1     A29:A28,A17:A16,A5:A4 ; |87| <0,10>  ^ 
           NOP             3
           DPINT   .L1     A5:A4,A4          ; |87| <0,14>  ^ 
           NOP             3

           AND     .S1     1,A4,A0           ; |116| <0,18> 
||         INTDP   .L1     A4,A5:A4          ; |87| <0,18>  ^ 

   [!A0]   ZERO    .L2     B22               ; |116| <0,19> 
|| [ A0]   ZERO    .S2     B23               ; <0,19> 
|| [!A0]   ZERO    .D2     B23               ; <0,19> 

   [ A0]   ZERO    .L2     B22               ; |116| <0,20> 
|| [ A0]   MVKH    .S2     0xbff00000,B23    ; <0,20> 

           NOP             2
           FMPYDP  .M1     A27:A26,A5:A4,A5:A4 ; |87| <0,23>  ^ 
           FMPYDP  .M2X    B21:B20,A5:A4,B17:B16 ; |87| <0,24> 
           NOP             2
           FSUBDP  .L1     A17:A16,A5:A4,A5:A4 ; |87| <0,27>  ^ 
           NOP             2
           FSUBDP  .L1X    A5:A4,B17:B16,A21:A20 ; |87| <0,30>  ^ 
           NOP             2
           FMPYDP  .M1     A21:A20,A21:A20,A17:A16 ; |87| <0,33>  ^ 
           NOP             3
           FMPYDP  .M1     A17:A16,A17:A16,A19:A18 ; |116| <0,37>  ^ 
           NOP             3
           FMPYDP  .M1     A23:A22,A19:A18,A5:A4 ; |116| <0,41>  ^ 
           FMPYDP  .M2X    B5:B4,A19:A18,B17:B16 ; |116| <0,42>  ^ 
           NOP             2
           FADDDP  .L1     A25:A24,A5:A4,A5:A4 ; |116| <0,45>  ^ 
           FADDDP  .L2     B7:B6,B17:B16,B17:B16 ; |116| <0,46>  ^ 
           NOP             1
           FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |116| <0,48>  ^ 
           FMPYDP  .M2X    A19:A18,B17:B16,B17:B16 ; |116| <0,49>  ^ 
           NOP             2
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |116| <0,52>  ^ 
           FADDDP  .L2     B9:B8,B17:B16,B17:B16 ; |116| <0,53>  ^ 
           NOP             1
           FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |116| <0,55>  ^ 
           FMPYDP  .M2X    A19:A18,B17:B16,B17:B16 ; |116| <0,56>  ^ 
           NOP             2
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |116| <0,59>  ^ 
           FADDDP  .L2     B19:B18,B17:B16,B17:B16 ; |116| <0,60>  ^ 
           NOP             1
           FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |116| <0,62>  ^ 
           FMPYDP  .M2X    A17:A16,B17:B16,B17:B16 ; |116| <0,63>  ^ 
           NOP             3
           FADDDP  .L2X    B17:B16,A5:A4,B17:B16 ; |116| <0,67>  ^ 
           NOP             2
           FMPYDP  .M2X    A21:A20,B17:B16,B17:B16 ; |116| <0,70>  ^ 
           NOP             3
           FADDDP  .L2X    B17:B16,A21:A20,B17:B16 ; |116| <0,74>  ^ 
           NOP             1

   [ A1]   BDEC    .S1     $C$L5,A1          ; |115| <0,76> 
|| [!A0]   SET     .S2     B23,0x14,0x1d,B23 ; <0,76> 

           FMPYDP  .M2     B23:B22,B17:B16,B17:B16 ; |116| <0,77>  ^ 
           NOP             3
           STDW    .D2T2   B17:B16,*B24++    ; |116| <0,81>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           STW     .D2T2   B4,*+SP(52)
           STW     .D2T1   A6,*+SP(64)
           STW     .D2T1   A31,*+SP(24)
           STW     .D2T1   A29,*+SP(32)
           STW     .D2T1   A28,*+SP(28)
           STW     .D2T1   A27,*+SP(36)
           STW     .D2T1   A25,*+SP(72)
           STW     .D2T1   A24,*+SP(68)
           STW     .D2T1   A23,*+SP(80)
           STW     .D2T1   A22,*+SP(76)
           STW     .D2T2   B6,*+SP(48)
           STW     .D2T2   B5,*+SP(56)

           MVKL    .S2     _output,B4
||         MV      .L2     B7,B10
||         STW     .D2T1   A8,*+SP(60)

           MV      .L2     B8,B12
||         STW     .D2T2   B20,*+SP(40)
||         RINT                              ; interrupts on

           MVKH    .S2     _output,B4
||         MV      .L1     A7,A15
||         MV      .L2     B9,B11
||         STW     .D2T2   B21,*+SP(44)
||         MV      .S1     A12,A4            ; |118| 

           CALLP   .S2     _sindp_v,B3
||         LDW     .D2T2   *+B4(16),B4       ; |118| 
||         MVK     .L1     0xa,A6            ; |118| 
||         MV      .S1     A9,A11
||         MV      .D1X    B18,A13
||         MV      .L2     B19,B13

$C$RL4:    ; CALL OCCURS {_sindp_v} {0}      ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 56
           MVKL    .S2     _output,B5
           MVKL    .S2     _output,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _output,B5
           MVKH    .S2     _output,B4
           MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D2T1   *B5,A4            ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B4(4),B4        ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _output,B4
           MVKL    .S2     _fcn_pass,B6
           MVKH    .S2     _output,B4

           LDW     .D2T2   *B4,B5            ; |67| 
||         MVKL    .S2     0x3ddb7cdf,B7

           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B4(8),B4        ; |67| 
||         MV      .L1X    B5,A4             ; |67| 
||         MVK     .S1     0xa,A6            ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _output,B5
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _output,B5
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2     B5,B4
||         STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B4(12),B4       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     _fcn_pass,B4
           MVKL    .S2     _output,B31
           MVKH    .S2     0x3ddb7cdf,B7

           ADD     .L1     4,A10,A5
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           MVKH    .S2     _output,B31
||         STW     .D2T1   A5,*+SP(84)

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A5,B4            ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0xa,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     _fcn_pass,B5

           MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     _fcn_pass,B5

           ADD     .L1     4,A3,A3
           LDW     .D1T1   *A3,A0            ; |72| 
           ADD     .L2     8,B5,B4
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           STW     .D2T2   B4,*+SP(92)       ; |69| 
           STW     .D2T1   A3,*+SP(88)

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |122| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     _all_pass,A3
   [!A0]   ZERO    .L2     B4                ; |72| 
   [!A0]   MVKH    .S1     _all_pass,A3
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
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   ZERO    .L2     B4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |122| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |122| 
||         STW     .D1T2   B4,*A3            ; |72| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |122| 

$C$RL9:    ; CALL OCCURS {_print_test_results} {0}  ; |122| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 51
           LDW     .D2T1   *+SP(48),A3       ; |86| 
           LDW     .D2T1   *+SP(56),A31      ; |86| 
           LDW     .D2T1   *+SP(52),A30      ; |86| 
           LDW     .D2T1   *+SP(60),A29      ; |86| 
           LDW     .D2T1   *+SP(64),A28      ; |86| 
           LDW     .D2T1   *+SP(72),A27      ; |86| 
           LDW     .D2T1   *+SP(68),A26      ; |86| 
           LDW     .D2T1   *+SP(80),A25      ; |86| 
           LDW     .D2T1   *+SP(76),A24      ; |86| 
           LDW     .D2T1   *+SP(36),A23      ; |86| 
           LDW     .D2T1   *+SP(44),A22      ; |86| 
           LDW     .D2T1   *+SP(40),A21      ; |74| 
           LDW     .D2T1   *+SP(32),A20      ; |74| 
           LDW     .D2T1   *+SP(28),A19      ; |74| 
           LDW     .D2T1   *+SP(24),A18      ; |74| 
           STW     .D2T1   A15,*+SP(188)     ; |86| 
           STW     .D2T1   A11,*+SP(180)     ; |86| 
           STW     .D2T2   B10,*+SP(164)     ; |86| 
           STW     .D2T2   B12,*+SP(152)     ; |86| 
           STW     .D2T2   B11,*+SP(156)     ; |86| 
           STW     .D2T1   A13,*+SP(144)     ; |86| 

           ZERO    .L1     A4                ; |134| 
||         STW     .D2T2   B13,*+SP(148)     ; |86| 

           MVK     .L2     0x7,B31
||         STW     .D2T1   A4,*+SP(128)      ; |130| 

           ZERO    .L1     A2                ; |134| 
||         STW     .D2T2   B31,*+SP(12)      ; |130| 

           STW     .D2T1   A2,*+SP(112)      ; |130| 
           STW     .D2T1   A3,*+SP(160)      ; |86| 
           STW     .D2T1   A31,*+SP(172)     ; |86| 
           STW     .D2T1   A30,*+SP(168)     ; |86| 
           STW     .D2T1   A29,*+SP(176)     ; |86| 
           STW     .D2T1   A28,*+SP(184)     ; |86| 
           STW     .D2T1   A27,*+SP(196)     ; |86| 
           STW     .D2T1   A26,*+SP(192)     ; |86| 
           STW     .D2T1   A25,*+SP(204)     ; |86| 
           STW     .D2T1   A24,*+SP(200)     ; |86| 
           STW     .D2T1   A23,*+SP(132)     ; |86| 
           STW     .D2T1   A22,*+SP(140)     ; |74| 
           STW     .D2T1   A21,*+SP(136)     ; |74| 
           STW     .D2T1   A20,*+SP(124)     ; |74| 

           MVKL    .S2     _a_sc,B6
||         MVK     .L2     0xffffffff,B5     ; |135| 
||         STW     .D2T1   A19,*+SP(120)     ; |74| 

           MVKH    .S2     _a_sc,B6
||         MV      .L2     B5,B4             ; |135| 
||         ZERO    .L1     A5
||         STW     .D2T1   A18,*+SP(116)     ; |74| 

           STDW    .D2T2   B5:B4,*+B6(48)    ; |135| 
||         MV      .L2     B6,B4             ; |129| 
||         MVKH    .S1     0xbff00000,A5

           ZERO    .S1     A7
||         ZERO    .L1     A17:A16           ; |129| 
||         STDW    .D2T1   A5:A4,*+B4(40)    ; |134| 

           ZERO    .L2     B9
||         MVKH    .S1     0xfff00000,A7
||         ZERO    .L1     A6                ; |134| 
||         STDW    .D2T1   A17:A16,*B4       ; |129| 

           ZERO    .L1     A9
||         SET     .S2     B9,0x14,0x1e,B9
||         ZERO    .L2     B8                ; |134| 
||         STDW    .D2T1   A7:A6,*+B4(24)    ; |132| 

           ZERO    .L2     B7
||         MVKH    .S1     0x80000000,A9
||         ZERO    .L1     A8                ; |134| 
||         STDW    .D2T2   B9:B8,*+B4(16)    ; |131| 

           MV      .L1X    B6,A14            ; |129| 
||         ZERO    .L2     B6                ; |134| 
||         SET     .S2     B7,0x14,0x1d,B7
||         STDW    .D2T1   A9:A8,*+B4(8)     ; |130| 

           STDW    .D2T2   B7:B6,*+B4(32)    ; |133| 
||         CALL    .S1     _sin              ; |137| 

           LDDW    .D1T1   *A14,A5:A4        ; |137| 
           ZERO    .L1     A12               ; |134| 
           NOP             2
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
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL10,B3,0      ; |137| 
$C$RL10:   ; CALL OCCURS {_sin} {0}          ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |137| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |137| 
           STDW    .D1T1   A5:A4,*A3         ; |137| 

           CALLP   .S2     _sindp,B3
||         LDDW    .D1T1   *A14,A5:A4        ; |138| 

$C$RL11:   ; CALL OCCURS {_sindp} {0}        ; |138| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(4),B4        ; |138| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |138| 
           STDW    .D1T1   A5:A4,*A3         ; |138| 

           CALLP   .S2     _sindp_c,B3
||         LDDW    .D1T1   *A14,A5:A4        ; |139| 

$C$RL12:   ; CALL OCCURS {_sindp_c} {0}      ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 103
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |139| 
           LDDW    .D2T2   *+SP(160),B7:B6   ; |140| 
           LDW     .D1T1   *A10,A31          ; |140| 
           NOP             2
           ADD     .L1X    A12,B4,A3         ; |139| 
           STDW    .D1T1   A5:A4,*A3         ; |139| 
           LDDW    .D1T1   *A14++,A7:A6      ; |72| 
           LDDW    .D2T1   *+SP(112),A5:A4
           LDDW    .D2T2   *+SP(136),B5:B4
           NOP             2
           ABSDP   .S1     A7:A6,A9:A8       ; |74| 
           NOP             1

           CMPGTDP .S1     A9:A8,A5:A4,A0    ; |74| 
||         LDDW    .D2T1   *+SP(120),A5:A4   ; |75| 

           NOP             3
   [ A0]   ZERO    .L1     A7:A6             ; |75| 
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |80| 
           NOP             3
           DPINT   .L1     A5:A4,A3          ; |80| 
           LDDW    .D2T1   *+SP(128),A5:A4
           NOP             2
           INTDP   .L1     A3,A9:A8          ; |80| 
           AND     .L1     1,A3,A0           ; |83| 
           ADD     .L1     A12,A31,A3        ; |140| 
           ADD     .S1     8,A12,A12         ; |136| 
           NOP             1
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |86| 
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |86| 
           NOP             2
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |86| 
           NOP             2
           FSUBDP  .L1X    A5:A4,B5:B4,A9:A8 ; |86| 
           LDDW    .D2T1   *+SP(200),A5:A4
           LDDW    .D2T2   *+SP(168),B5:B4   ; |140| 
           FMPYDP  .M1     A9:A8,A9:A8,A17:A16 ; |140| 
           NOP             3
           FMPYDP  .M1     A17:A16,A17:A16,A7:A6 ; |140| 
           NOP             3

           FMPYDP  .M1     A5:A4,A7:A6,A19:A18 ; |140| 
||         LDDW    .D2T1   *+SP(192),A5:A4

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |140| 
           NOP             3
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |140| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |140| 
           LDDW    .D2T2   *+SP(152),B7:B6   ; |140| 

           FMPYDP  .M1     A7:A6,A5:A4,A19:A18 ; |140| 
||         LDDW    .D2T1   *+SP(184),A5:A4

           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |140| 
           NOP             3
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |140| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |140| 
           LDDW    .D2T2   *+SP(144),B7:B6   ; |140| 

           FMPYDP  .M1     A7:A6,A5:A4,A19:A18 ; |140| 
||         LDDW    .D2T1   *+SP(176),A5:A4

           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |140| 
           NOP             3
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |140| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |140| 
   [!A0]   ZERO    .L2     B7
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |140| 
           FMPYDP  .M2X    A17:A16,B5:B4,B5:B4 ; |140| 
   [ A0]   ZERO    .L2     B7
   [!A0]   ZERO    .L2     B6                ; |83| 
   [ A0]   ZERO    .L2     B6                ; |83| 
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |140| 
   [!A0]   SET     .S2     B7,0x14,0x1d,B7
   [ A0]   MVKH    .S2     0xbff00000,B7
           FMPYDP  .M2X    A9:A8,B5:B4,B5:B4 ; |140| 
           NOP             3
           FADDDP  .L2X    B5:B4,A9:A8,B5:B4 ; |140| 
           NOP             2

           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |140| 
||         LDW     .D2T2   *+SP(12),B6       ; |140| 

           NOP             3
           STDW    .D1T2   B5:B4,*A3         ; |140| 

           SUB     .L1X    B6,1,A0           ; |136| 
||         SUB     .L2     B6,1,B4           ; |136| 

   [ A0]   B       .S1     $C$L8             ; |136| 
||         STW     .D2T2   B4,*+SP(12)       ; |140| 
|| [!A0]   MVKL    .S2     _output,B4
|| [ A0]   LDDW    .D1T1   *A14,A5:A4        ; |137| 

   [ A0]   CALL    .S1     _sin              ; |137| 
|| [!A0]   MVKH    .S2     _output,B4

   [!A0]   CALL    .S1     _sindp_v          ; |142| 
   [!A0]   LDW     .D2T2   *+B4(16),B4       ; |142| 
   [!A0]   MVKL    .S1     _a_sc,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L8}         ; |136| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S1     _a_sc,A4

           MVK     .L1     0x7,A6            ; |142| 
||         ADDKPC  .S2     $C$RL13,B3,0      ; |142| 

$C$RL13:   ; CALL OCCURS {_sindp_v} {0}      ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 53
           MVKL    .S2     _output,B5
           MVKL    .S2     _output,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _output,B5
           MVKH    .S2     _output,B4
           MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D2T1   *B5,A4            ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B4(4),B4        ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _output,B4
           MVKL    .S2     _fcn_pass,B5
           MVKH    .S2     _output,B4

           LDW     .D2T2   *B4,B8            ; |67| 
||         MVKL    .S2     0x3ddb7cdf,B7

           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B4(8),B4        ; |67| 
||         MV      .L1X    B8,A4             ; |67| 
||         MVK     .S1     0x7,A6            ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5

           MVKL    .S1     _output,A3
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     _output,A3
||         MVKH    .S2     _fcn_pass,B5

           MVKL    .S2     0x3ddb7cdf,B7

           MV      .L2X    A3,B4             ; |142| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           MV      .L2X    A3,B8             ; |142| 
||         LDW     .D2T2   *+B4(12),B4       ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B8,A4            ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(84),A3       ; |68| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     _fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKL    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A3,*+SP(96)       ; |68| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVKL    .S1     _output,A3
||         MVKH    .S2     0xd9d7bdbb,B6

           MVKH    .S1     _output,A3
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(88),A3       ; |69| 
           MVKL    .S2     _fcn_pass,B31
           MVKH    .S2     _fcn_pass,B31
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           NOP             1

           MV      .L2X    A3,B4             ; |69| 
||         STW     .D2T1   A3,*+SP(100)      ; |69| 

           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T1   *+SP(92),A3
           NOP             3

   [!B0]   B       .S1     $C$L9             ; |72| 
|| [!B0]   ZERO    .L1     A4                ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     _print_test_results ; |146| 
|| [ B0]   MV      .L2X    A3,B4
||         STW     .D2T1   A3,*+SP(104)      ; |72| 
|| [!B0]   MVKL    .S1     _all_pass,A3

   [!B0]   MVKH    .S1     _all_pass,A3
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           NOP             2
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           CMPEQ   .L1     A4,0,A3           ; |72| 
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
           NOP             1
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
;          EXCLUSIVE CPU CYCLES: 37
           STW     .D2T2   B12,*+SP(128)     ; |86| 
           STW     .D2T2   B11,*+SP(132)     ; |86| 
           STW     .D2T2   B10,*+SP(140)     ; |86| 
           STW     .D2T1   A13,*+SP(120)     ; |86| 
           STW     .D2T1   A11,*+SP(148)     ; |86| 
           LDW     .D2T1   *+SP(28),A23      ; |74| 
           LDW     .D2T1   *+SP(32),A24      ; |74| 
           LDW     .D2T1   *+SP(76),A25      ; |86| 
           LDW     .D2T1   *+SP(80),A26      ; |86| 
           LDW     .D2T1   *+SP(68),A27      ; |86| 
           LDW     .D2T1   *+SP(72),A28      ; |86| 
           LDW     .D2T1   *+SP(64),A29      ; |86| 
           LDW     .D2T1   *+SP(60),A30      ; |86| 
           LDW     .D2T1   *+SP(48),A31      ; |86| 
           STW     .D2T2   B13,*+SP(124)     ; |86| 
           STW     .D2T1   A15,*+SP(156)     ; |86| 

           STW     .D2T1   A10,*+SP(108)     ; |86| 
||         ZERO    .L1     A22

           STW     .D2T1   A22,*+SP(176)     ; |149| 
||         MVK     .S2     0x6f4,B31

           STW     .D2T2   B31,*+SP(12)      ; |149| 
           LDW     .D2T2   *+SP(40),B12      ; |74| 
           LDW     .D2T2   *+SP(56),B11      ; |86| 
           LDW     .D2T2   *+SP(52),B10      ; |86| 

           LDW     .D2T1   *+SP(36),A13      ; |86| 
||         ZERO    .L1     A3

           LDW     .D2T1   *+SP(24),A11      ; |74| 
||         MVKH    .S1     0xbff80000,A3

           STW     .D2T1   A3,*+SP(180)      ; |155| 
           STW     .D2T1   A23,*+SP(112)     ; |74| 
           STW     .D2T1   A24,*+SP(116)     ; |74| 
           STW     .D2T1   A25,*+SP(168)     ; |86| 
           STW     .D2T1   A26,*+SP(172)     ; |86| 
           STW     .D2T1   A27,*+SP(160)     ; |86| 
           STW     .D2T1   A28,*+SP(164)     ; |86| 

           STW     .D2T1   A29,*+SP(152)     ; |86| 
||         MVKL    .S2     _a_ext,B4

           STW     .D2T1   A30,*+SP(144)     ; |86| 
||         MVKH    .S2     _a_ext,B4
||         ZERO    .L1     A5

           STW     .D2T1   A31,*+SP(136)     ; |86| 
||         SET     .S1     A5,0x14,0x14,A5
||         ZERO    .L1     A4

           CALL    .S1     _sin              ; |151| 
||         STDW    .D2T1   A5:A4,*B4         ; |149| 
||         MV      .L1X    B4,A14            ; |149| 

           LDDW    .D1T1   *A14,A5:A4        ; |151| 
||         LDW     .D2T2   *+SP(44),B13      ; |86| 

           ZERO    .L1     A10
||         ZERO    .S1     A15
||         ZERO    .D1     A12

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
;          EXCLUSIVE CPU CYCLES: 3
           ADDKPC  .S2     $C$RL19,B3,2      ; |151| 
$C$RL19:   ; CALL OCCURS {_sin} {0}          ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |151| 
           NOP             4
           ADD     .L1X    A15,B4,A3         ; |151| 
           STDW    .D1T1   A5:A4,*A3         ; |151| 

           CALLP   .S2     _sindp,B3
||         LDDW    .D1T1   *A14,A5:A4        ; |152| 

$C$RL20:   ; CALL OCCURS {_sindp} {0}        ; |152| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(4),B4        ; |152| 
           NOP             4
           ADD     .L1X    A15,B4,A3         ; |152| 
           STDW    .D1T1   A5:A4,*A3         ; |152| 

           CALLP   .S2     _sindp_c,B3
||         LDDW    .D1T1   *A14,A5:A4        ; |153| 

$C$RL21:   ; CALL OCCURS {_sindp_c} {0}      ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |153| 
           LDDW    .D2T2   *+SP(136),B7:B6   ; |154| 
           LDW     .D2T1   *+SP(108),A31     ; |83| 
           NOP             2
           ADD     .L1X    A15,B4,A3         ; |153| 
           STDW    .D1T1   A5:A4,*A3         ; |153| 
           LDDW    .D1T1   *A14,A5:A4        ; |72| 
           NOP             4
           ABSDP   .S1     A5:A4,A7:A6       ; |74| 
           NOP             1

           CMPGTDP .S1     A7:A6,A11:A10,A0  ; |74| 
||         LDDW    .D2T1   *+SP(112),A7:A6   ; |75| 

           NOP             3
   [ A0]   ZERO    .L1     A5:A4             ; |75| 
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |80| 
           NOP             3
           DPINT   .L1     A7:A6,A3          ; |80| 
           NOP             3
           INTDP   .L1     A3,A7:A6          ; |80| 
           AND     .L1     1,A3,A0           ; |83| 
           LDW     .D1T1   *A31,A3           ; |154| 
           NOP             2
           FMPYDP  .M1     A13:A12,A7:A6,A9:A8 ; |86| 
           FMPYDP  .M2X    B13:B12,A7:A6,B5:B4 ; |86| 
           ADD     .L1     A15,A3,A3         ; |154| 
           ADD     .L1     8,A15,A15         ; |150| 
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |86| 
           NOP             2
           FSUBDP  .L1X    A5:A4,B5:B4,A7:A6 ; |86| 
           LDDW    .D2T1   *+SP(168),A5:A4
           NOP             1
           FMPYDP  .M1     A7:A6,A7:A6,A17:A16 ; |154| 
           NOP             3
           FMPYDP  .M1     A17:A16,A17:A16,A9:A8 ; |154| 
           NOP             3

           FMPYDP  .M1     A5:A4,A9:A8,A19:A18 ; |154| 
||         LDDW    .D2T1   *+SP(160),A5:A4

           FMPYDP  .M2X    B11:B10,A9:A8,B5:B4 ; |154| 
           NOP             3
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |154| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |154| 
           LDDW    .D2T2   *+SP(128),B7:B6   ; |154| 

           FMPYDP  .M1     A9:A8,A5:A4,A19:A18 ; |154| 
||         LDDW    .D2T1   *+SP(152),A5:A4

           FMPYDP  .M2X    A9:A8,B5:B4,B5:B4 ; |154| 
           NOP             3
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |154| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |154| 
           LDDW    .D2T2   *+SP(120),B7:B6   ; |154| 

           FMPYDP  .M1     A9:A8,A5:A4,A19:A18 ; |154| 
||         LDDW    .D2T1   *+SP(144),A5:A4

           FMPYDP  .M2X    A9:A8,B5:B4,B5:B4 ; |154| 
           NOP             3
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |154| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |154| 
   [ A0]   ZERO    .L2     B7
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |154| 
           FMPYDP  .M2X    A17:A16,B5:B4,B5:B4 ; |154| 
   [!A0]   ZERO    .L2     B7
   [ A0]   MV      .L2X    A12,B6            ; |154| 
   [ A0]   MVKH    .S2     0xbff00000,B7
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |154| 
   [!A0]   MV      .L2X    A12,B6            ; |154| 
   [!A0]   SET     .S2     B7,0x14,0x1d,B7
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |154| 
           LDDW    .D2T1   *+SP(176),A5:A4
           NOP             2
           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |154| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |154| 
           NOP             3
           STDW    .D1T2   B5:B4,*A3         ; |154| 

           LDDW    .D1T1   *A14,A7:A6        ; |155| 
||         LDW     .D2T2   *+SP(12),B4

           NOP             4

           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |155| 
||         SUB     .L1X    B4,1,A0           ; |150| 
||         SUB     .L2     B4,1,B4           ; |150| 

   [ A0]   BNOP    .S1     $C$L10,1          ; |150| 
|| [!A0]   MVKL    .S2     _output,B10

   [!A0]   MVKH    .S2     _output,B10

   [ A0]   CALL    .S2     _sin              ; |151| 
||         STDW    .D1T1   A5:A4,*++A14      ; |155| 
||         STW     .D2T2   B4,*+SP(12)       ; |155| 
|| [!A0]   MVKL    .S1     _a_ext,A4

   [!A0]   CALL    .S1     _sindp_v          ; |157| 
|| [ A0]   LDDW    .D1T1   *A14,A5:A4        ; |151| 

   [!A0]   LDW     .D2T2   *+B10(16),B4      ; |157| 
           ; BRANCHCC OCCURS {$C$L10}        ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S1     _a_ext,A4
           MVK     .S1     0x6f4,A6          ; |157| 
           ADDKPC  .S2     $C$RL22,B3,1      ; |157| 
$C$RL22:   ; CALL OCCURS {_sindp_v} {0}      ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0x6f4,A6          ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL23:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B11
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B11
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B11(4)       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0x6f4,A6          ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL24:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1X    B10,A3            ; |67| 
||         STW     .D2T1   A4,*+B11(8)       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0x6f4,A6          ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL25:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(84),A3       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2     B10,B4            ; |68| 
||         STW     .D2T1   A4,*+B11(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x6f4,A6          ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(88),A3       ; |69| 
           LDW     .D2T2   *+SP(92),B4
           STW     .D2T1   A4,*+B11(16)      ; |69| 
           NOP             2
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |161| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MV      .L1     A12,A3
   [!A0]   MVKL    .S1     _all_pass,A4
   [!A0]   MVKH    .S1     _all_pass,A4
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   MV      .L1     A10,A0            ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   MV      .L1     A12,A3
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |161| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |161| 
||         ADDKPC  .S2     $C$RL27,B3,0      ; |161| 

$C$RL27:   ; CALL OCCURS {_print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           MV      .L2X    A10,B6            ; |114| 

           MV      .L2X    A10,B5            ; |114| 
||         STW     .D2T2   B6,*+SP(112)      ; |114| 

           STW     .D2T2   B5,*+SP(116)      ; |114| 
           LDDW    .D2T2   *+SP(112),B7:B6   ; |114| 
           MVKL    .S1     _cycle_counts+24,A3
           MVKH    .S1     _cycle_counts+24,A3
           MV      .L2X    A10,B4            ; |114| 
           NOP             1

           STDW    .D1T2   B7:B6,*A3         ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     _t_start,A3

           MVKH    .S1     _t_start,A3
||         MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B8,B7,B6          ; |117| 
||         MVKL    .S1     _t_offset,A3

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S1     _t_offset,A3

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MVK     .S2     0x80,B4

           ZERO    .L2     B5

           MV      .L1X    B4,A12            ; |117| 
||         MVKL    .S2     _input,B4

           MVKH    .S2     _input,B4
||         CALL    .S1     _gimme_random     ; |171| 

           LDW     .D2T2   *B4,B10           ; |171| 
           ZERO    .L2     B4                ; |171| 
           MVKH    .S2     0xc0590000,B5

           ZERO    .L1     A5
||         MV      .L2X    A10,B11
||         ZERO    .S1     A4                ; |171| 

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
;          EXCLUSIVE CPU CYCLES: 1

           ADDKPC  .S2     $C$RL28,B3,0      ; |171| 
||         MVKH    .S1     0x40690000,A5

$C$RL28:   ; CALL OCCURS {_gimme_random} {0}  ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 107
           ADD     .L2     B10,B11,B4        ; |171| 

           STDW    .D2T1   A5:A4,*B4         ; |171| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B7           ; |122| 

           ADD     .L2     B10,B11,B4        ; |74| 
||         ZERO    .S2     B9
||         ZERO    .D2     B8                ; |74| 
||         MVKL    .S1     0x6dc9c883,A6
||         MV      .L1X    B10,A10           ; |74| 

           LDDW    .D2T2   *B4,B5:B4         ; |74| 
           MVKL    .S1     0x3fd45f30,A7
           MVKH    .S2     0x41d00000,B9
           MVKL    .S2     0x111110b0,B16
           MVKL    .S2     0x3f811111,B17
           ABSDP   .S2     B5:B4,B5:B4       ; |74| 
           MVKH    .S1     0x6dc9c883,A6
           CMPGTDP .S2     B5:B4,B9:B8,B0    ; |74| 
           MVKH    .S1     0x3fd45f30,A7
   [ B0]   ZERO    .L1     A5:A4             ; |75| 
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |80| 
           MVKH    .S2     0x111110b0,B16
           MVKL    .S1     0x3ce880ff,A17
           MVKL    .S1     0x6993df95,A16
           DPINT   .L1     A7:A6,A3          ; |80| 
           MVKH    .S1     0x3ce880ff,A17
           MVKH    .S1     0x6993df95,A16
           MVKL    .S1     0xbe5ae645,A21
           INTDP   .L1     A3,A7:A6          ; |80| 
           MV      .L2     B8,B4             ; |86| 
           MVKL    .S2     0x40092200,B5
           MVKH    .S2     0x40092200,B5
           MVKL    .S2     0xbee2aeef,B9
           MVKL    .S2     0x4b9ee59e,B8
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |86| 
           MVKH    .S2     0xbee2aeef,B9
           MVKH    .S2     0x4b9ee59e,B8
           MVKL    .S1     0x4b5dc0ab,A20
           FMPYDP  .M1X    B9:B8,A7:A6,A7:A6 ; |86| 
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |86| 
           MVKH    .S1     0xbe5ae645,A21
           MVKH    .S1     0x4b5dc0ab,A20
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |86| 
           MVKL    .S2     0x3de6123c,B9
           MVKL    .S2     0x686ad430,B8
           FMPYDP  .M1     A7:A6,A7:A6,A9:A8 ; |175| 
           MVKH    .S2     0x3de6123c,B9
           MVKH    .S2     0x686ad430,B8
           MVKL    .S2     0xdc08499c,B4
           FMPYDP  .M1     A9:A8,A9:A8,A5:A4 ; |175| 
           MVKL    .S2     0xbd6ae420,B5
           MVKH    .S2     0xdc08499c,B4
           MVKH    .S2     0xbd6ae420,B5
           FMPYDP  .M1     A17:A16,A5:A4,A19:A18 ; |175| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |175| 
           MVKL    .S1     0x1a013e1a,A16
           MVKL    .S1     0xbf2a01a0,A17
           MVKH    .S1     0x1a013e1a,A16
           MVKH    .S1     0xbf2a01a0,A17

           FADDDP  .L1X    A21:A20,B5:B4,A21:A20 ; |175| 
||         FADDDP  .L2X    B9:B8,A19:A18,B5:B4 ; |175| 
||         MVKL    .S1     0xa524f063,A18
||         MVKL    .S2     0x55555555,B8

           MVKL    .S2     0xbfc55555,B9
           MVKL    .S1     0x3ec71de3,A19
           FMPYDP  .M1     A5:A4,A21:A20,A21:A20 ; |175| 
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |175| 
           MVKH    .S1     0xa524f063,A18
           MVKH    .S1     0x3ec71de3,A19
           FADDDP  .L1     A17:A16,A21:A20,A17:A16 ; |175| 
           FADDDP  .L2X    A19:A18,B5:B4,B5:B4 ; |175| 
           MVKH    .S2     0x55555555,B8
           FMPYDP  .M1     A5:A4,A17:A16,A17:A16 ; |175| 
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |175| 
           MVKH    .S2     0xbfc55555,B9
           MVKH    .S2     0x3f811111,B17
           FADDDP  .L1X    B9:B8,A17:A16,A17:A16 ; |175| 
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |175| 
           MVKL    .S2     _output+12,B31
           FMPYDP  .M1     A9:A8,A17:A16,A9:A8 ; |175| 
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |175| 
           MVKH    .S2     _output+12,B31
           AND     .L1     1,A3,A0           ; |83| 
           LDW     .D2T2   *B31,B8           ; |175| 
           FADDDP  .L2X    A9:A8,B5:B4,B5:B4 ; |175| 
   [!A0]   ZERO    .L1     A4                ; |83| 
   [ A0]   ZERO    .L1     A5
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |175| 
   [!A0]   ZERO    .L1     A5
   [ A0]   ZERO    .L1     A4                ; |83| 
   [ A0]   MVKH    .S1     0xbff00000,A5
           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |175| 
   [!A0]   SET     .S1     A5,0x14,0x1d,A5
           MVKL    .S2     _t_start,B12
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |175| 
           MVKH    .S2     _t_start,B12
           STDW    .D2T2   B7:B6,*B12
           ADD     .L2     B11,B8,B8         ; |175| 

           STDW    .D2T2   B5:B4,*B8         ; |175| 
||         MVC     .S2     TSCL,B4           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S1     _t_offset,A3
||         SUB     .L1     A12,1,A0          ; |169| 
||         ADD     .L2     8,B11,B11         ; |169| 
||         SUB     .D1     A12,1,A12         ; |169| 

           MVKH    .S1     _t_offset,A3

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         MVKL    .S1     _cycle_counts+24,A6

           MVKH    .S1     _cycle_counts+24,A6

           LDDW    .D1T1   *A6,A9:A8         ; |130| 
||         MVKL    .S1     _t_stop,A30

           MVKH    .S1     _t_stop,A30

           STDW    .D1T2   B5:B4,*A30        ; |128| 
||         MVKL    .S1     _cycle_counts+24,A11

           ADDU    .L1X    A4,B6,A7:A6       ; |130| 
||         MVKH    .S1     _cycle_counts+24,A11

           ADD     .S1     A7,A5,A3          ; |130| 
||         SUBU    .L1X    B4,A6,A5:A4       ; |130| 
|| [ A0]   MVKL    .S2     _input,B4

   [ A0]   MVKH    .S2     _input,B4
||         EXT     .S1     A5,24,24,A31      ; |130| 
||         ADDU    .L1     A8,A4,A5:A4       ; |130| 

           ADD     .L2X    A3,B7,B6          ; |130| 
|| [ A0]   B       .S1     $C$L12            ; |169| 
|| [ A0]   LDW     .D2T2   *B4,B10           ; |171| 
||         ADD     .L1     A5,A9,A3          ; |130| 
|| [ A0]   ZERO    .S2     B4                ; |171| 

   [ A0]   CALL    .S1     _gimme_random     ; |171| 
||         SUB     .L2     B5,B6,B6          ; |130| 
|| [ A0]   ZERO    .S2     B5

   [ A0]   MVKH    .S2     0xc0590000,B5
           ADD     .L1X    B6,A31,A5         ; |130| 
           ADD     .L1     A3,A5,A5          ; |130| 

   [!A0]   CALL    .S2     __fltllif         ; |135| 
||         STDW    .D1T1   A5:A4,*A11        ; |130| 
|| [ A0]   ZERO    .L1     A5
|| [ A0]   ZERO    .S1     A4                ; |171| 

           ; BRANCHCC OCCURS {$C$L12}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |135| 
$C$RL29:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           ZERO    .L1     A12               ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL30:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           LDDW    .D2T2   *+SP(112),B7:B6
           MV      .L2X    A11,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 
           SUBAW   .D2     B4,6,B10
           MV      .L2X    A12,B5            ; |114| 

           STDW    .D2T2   B7:B6,*B10        ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MV      .L1X    B4,A14            ; |116| 

           MV      .L1X    B5,A12            ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 
           MVKL    .S1     _output,A3

           SUB     .L1X    B4,A12,A4         ; |117| 
||         SUBU    .L2X    B5,A14,B7:B6      ; |117| 
||         MVKH    .S1     _output,A3

           EXT     .S2     B7,24,24,B4       ; |117| 
||         CALL    .S1     _sin              ; |183| 
||         LDW     .D1T1   *A3,A11

           ADD     .L2X    A4,B4,B11         ; |117| 
||         LDDW    .D1T1   *A10++,A5:A4      ; |183| 

           MV      .L1X    B6,A15            ; |117| 
           MVK     .S2     0x80,B13
           NOP             1
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL31,B3,0      ; |183| 
$C$RL31:   ; CALL OCCURS {_sin} {0}          ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1X    B13,1,A0          ; |182| 
||         STDW    .D1T1   A5:A4,*A11++      ; |183| 

   [ A0]   B       .S1     $C$L13            ; |182| 
   [ A0]   CALL    .S1     _sin              ; |183| 
   [ A0]   LDDW    .D1T1   *A10++,A5:A4      ; |183| 
           SUB     .L2     B13,1,B13         ; |182| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L13}        ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MV      .L2     B4,B7             ; |128| 
||         LDDW    .D2T2   *B10,B5:B4        ; |130| 
||         ADDU    .L1     A15,A14,A5:A4     ; |130| 
||         MVKL    .S2     _t_stop,B13

           ADD     .L1X    A5,B11,A3         ; |130| 
||         MVKH    .S2     _t_stop,B13

           SUBU    .L1X    B6,A4,A5:A4       ; |130| 
||         ADD     .S1     A3,A12,A3         ; |130| 
||         STDW    .D2T2   B7:B6,*B13        ; |128| 

           CALL    .S2     __fltllif         ; |130| 
||         SUB     .L1X    B7,A3,A3          ; |130| 
||         EXT     .S1     A5,24,24,A31      ; |130| 

           ADD     .L1     A3,A31,A3         ; |130| 
           ADDU    .L2X    B4,A4,B9:B8       ; |130| 
           ADD     .L2     B9,B5,B4          ; |130| 
           MV      .L1X    B8,A4             ; |130| 

           ADD     .L1X    B4,A3,A5          ; |130| 
||         ADDKPC  .S2     $C$RL32,B3,0      ; |130| 

$C$RL32:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL33:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(112),B5:B4   ; |130| 
           ZERO    .L1     A11
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           SET     .S1     A11,0x1a,0x1d,A11

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MV      .L1X    B12,A15           ; |116| 

           STDW    .D1T2   B7:B6,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S2     _t_offset,B12

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B8,B7,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S2     _t_offset,B12

           STDW    .D2T2   B5:B4,*B12        ; |117| 
||         MVK     .S2     0x80,B4

           MVKL    .S1     _input,A14

           MV      .L1X    B4,A10            ; |117| 
||         MVKH    .S1     _input,A14
||         LDW     .D2T2   *+SP(16),B11      ; |117| 

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
||         CALL    .S1     _sindp            ; |191| 

           LDDW    .D1T1   *A3,A5:A4         ; |191| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |191| 
$C$RL34:   ; CALL OCCURS {_sindp} {0}        ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |191| 
||         SUB     .L1     A10,1,A0          ; |190| 
||         SUB     .S1     A10,1,A10         ; |190| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |190| 

           ADD     .L1X    A12,B4,A3         ; |191| 
||         ADD     .S1     8,A12,A12         ; |190| 

           STDW    .D1T1   A5:A4,*A3         ; |191| 
           ; BRANCHCC OCCURS {$C$L14}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 

           LDDW    .D2T2   *+B10(8),B17:B16  ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A3          ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 
||         ADD     .S2     B7,B17,B31        ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         MV      .S2     B13,B4            ; |130| 

           ADD     .L2     B31,B5,B7         ; |130| 
           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL35,B3,0      ; |130| 

$C$RL35:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL36:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(112),B5:B4
           ADDAD   .D2     B10,1,B11
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B11        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B8,B7,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 

           STDW    .D2T2   B5:B4,*B12        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1     A12,A10

           MV      .L1X    B4,A12            ; |117| 
||         LDW     .D2T2   *+SP(20),B13      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A14,A3           ; |199| 
           NOP             4

           ADD     .L1     A10,A3,A3         ; |199| 
||         CALL    .S1     _sindp_c          ; |199| 

           LDDW    .D1T1   *A3,A5:A4         ; |199| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |199| 
$C$RL37:   ; CALL OCCURS {_sindp_c} {0}      ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |199| 
||         SUB     .L1     A12,1,A0          ; |198| 
||         SUB     .S1     A12,1,A12         ; |198| 

   [ A0]   BNOP    .S1     $C$L15,3          ; |198| 

           ADD     .L1X    A10,B4,A3         ; |199| 
||         ADD     .S1     8,A10,A10         ; |198| 

           STDW    .D1T1   A5:A4,*A3         ; |199| 
           ; BRANCHCC OCCURS {$C$L15}        ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MV      .L1     A15,A10           ; |128| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 

           LDDW    .D1T1   *A10,A5:A4        ; |130| 
           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .L2X    B6,A5,B6          ; |130| 
||         CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .S2     B9,B6,B4          ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B7,B17,B4         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     _t_stop,B4

           MVKH    .S2     _t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL38,B3,0      ; |130| 

$C$RL38:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL39:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           LDDW    .D2T2   *+SP(112),B5:B4
           ADDAD   .D2     B11,1,B13
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 

           STDW    .D1T2   B7:B6,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B8,B7,B6          ; |117| 

           MVKL    .S1     _output,A10
||         ADD     .L2     B6,B5,B5          ; |117| 

           MVKH    .S1     _output,A10
||         MV      .L2X    A14,B9            ; |206| 
||         STDW    .D2T2   B5:B4,*B12        ; |117| 

           CALLP   .S2     _sindp_v,B3
||         LDW     .D1T2   *+A10(16),B4      ; |206| 
||         LDW     .D2T1   *B9,A4            ; |206| 
||         MVK     .S1     0x80,A6           ; |206| 

$C$RL40:   ; CALL OCCURS {_sindp_v} {0}      ; |206| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 

           MVK     .S1     16,A14
           ADD     .L1X    B13,A14,A14
           LDDW    .D1T1   *A14,A9:A8        ; |130| 
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
           MPYSP   .M1     A11,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL42:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STDW    .D1T1   A5:A4,*A14        ; |130| 
||         MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL43:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     _fcn_pass,B10
           MVKH    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVKH    .S2     _fcn_pass,B10

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A10(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL44:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL45:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(96),A3       ; |68| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T1   *A10,A4           ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL46:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(100),B4      ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(104),B4
           NOP             3

   [!B0]   B       .S1     $C$L16            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L16}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
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
           MV      .L1     A12,A3
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
;          EXCLUSIVE CPU CYCLES: 12
           ADDK    .S2     208,SP            ; |224| 
           LDW     .D2T2   *++SP(8),B3       ; |224| 
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
$C$SL1:	.string	"sinDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_sin
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_sindp
	.global	_sindp_c
	.global	_sindp_v
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
