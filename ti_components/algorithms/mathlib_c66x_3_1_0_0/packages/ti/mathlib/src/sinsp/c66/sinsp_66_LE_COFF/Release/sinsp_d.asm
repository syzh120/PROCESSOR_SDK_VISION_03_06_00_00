;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 23:01:56 2013                                *
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
	.word	0418cf297h		; _a[0] @ 0
	.word	042344956h		; _a[1] @ 32
	.word	0c29b829fh		; _a[2] @ 64
	.word	0421fcd8bh		; _a[3] @ 96
	.word	0c2c42d34h		; _a[4] @ 128
	.word	0c21925dch		; _a[5] @ 160
	.word	0c296fba2h		; _a[6] @ 192
	.word	0c269a74ah		; _a[7] @ 224
	.word	0426e4e13h		; _a[8] @ 256
	.word	0c22c2aa7h		; _a[9] @ 288
$C$IR_1:	.set	40

	.global	_a
_a:	.usect	".far",40,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\167605 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\167607 
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
;*   Local Frame Size  : 8 Args + 60 Auto + 56 Save = 124 byte                *
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

           STW     .D2T2   B3,*SP--(80)      ; |90| 
||         CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |98| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .L2     0xa,B4
||         MVKL    .S1     _a,A11

           MVKH    .S1     _a,A11
||         MVKL    .S2     _output,B11

           CALL    .S1     _sinf             ; |107| 
||         MV      .L1     A11,A12
||         MV      .D1X    B4,A10
||         MVKH    .S2     _output,B11
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |107| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |107| 
$C$RL1:    ; CALL OCCURS {_sinf} {0}         ; |107| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |107| 
||         SUB     .L1     A10,1,A0          ; |106| 
||         SUB     .S1     A10,1,A10         ; |106| 

   [ A0]   BNOP    .S1     $C$L1,3           ; |106| 
|| [!A0]   MVK     .L2     0xa,B5

           ADD     .L2     B10,B4,B4         ; |107| 
||         ADD     .S2     4,B10,B10         ; |106| 

   [ A0]   CALL    .S1     _sinf             ; |107| 
||         STW     .D2T1   A4,*B4            ; |107| 
|| [!A0]   ADD     .L2     4,B11,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |106| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           CALL    .S1     _sinsp            ; |110| 
||         ZERO    .L2     B10
||         MV      .L1X    B5,A10
||         MV      .D1     A11,A14
||         STW     .D2T2   B4,*+SP(32)

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |110| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |110| 
$C$RL2:    ; CALL OCCURS {_sinsp} {0}        ; |110| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(32),B4       ; |110| 
           SUB     .L1     A10,1,A0          ; |109| 
           SUB     .L1     A10,1,A10         ; |109| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |110| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |109| 

           ADD     .L2     B10,B4,B4         ; |110| 
||         ADD     .S2     4,B10,B10         ; |109| 

   [ A0]   CALL    .S1     _sinsp            ; |110| 
||         STW     .D2T1   A4,*B4            ; |110| 

           ; BRANCHCC OCCURS {$C$L2}         ; |109| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(32),B4
           MVK     .L2     0xa,B5
           ZERO    .L2     B10
           MV      .L1     A14,A11
           MV      .L1X    B5,A10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(36)
||         CALL    .S1     _sinsp_c          ; |113| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |113| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |113| 
$C$RL3:    ; CALL OCCURS {_sinsp_c} {0}      ; |113| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(36),B4       ; |113| 
           SUB     .L1     A10,1,A0          ; |112| 
           SUB     .L1     A10,1,A10         ; |112| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |113| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |112| 

           ADD     .L2     B10,B4,B4         ; |113| 
||         ADD     .S2     4,B10,B10         ; |112| 

   [ A0]   CALL    .S1     _sinsp_c          ; |113| 
||         STW     .D2T1   A4,*B4            ; |113| 

           ; BRANCHCC OCCURS {$C$L3}         ; |112| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           LDW     .D2T2   *+SP(36),B4
||         MVKL    .S1     0x3c08873e,A13
||         MVKL    .S2     0x3a7daa22,B13
||         ZERO    .L1     A4
||         ZERO    .D1     A3
||         ZERO    .L2     B12

           MVKL    .S1     0x3ea2f983,A5
||         MVKH    .S2     0x3a7daa22,B13
||         ZERO    .L2     B6
||         MVK     .L1     9,A0
||         ZERO    .D2     B24

           MVKL    .S1     0x362e9c5b,A11
||         MVKL    .S2     0xb94fb222,B31
||         MV      .L2X    A14,B8

           MVKH    .S1     0x40490000,A4
||         MVKL    .S2     0xbe2aaaa4,B5

           MVKH    .S1     0x3c08873e,A13
||         MVKH    .S2     0xb94fb222,B31
||         STW     .D2T1   A4,*+SP(16)

           MVKH    .S1     0x3ea2f983,A5
||         MVKH    .S2     0xbe2aaaa4,B5
||         ADD     .L2     4,B4,B10
||         MV      .L1X    B13,A4
||         MV      .D2X    A4,B22

           SET     .S1     A3,0x17,0x1d,A3
||         MVKH    .S2     0x49800000,B12
||         LDW     .D2T2   *B10,B9
||         MV      .L2X    A13,B18

           MVKH    .S1     0x362e9c5b,A11
||         MVKH    .S2     0xbf800000,B6
||         STW     .D2T1   A5,*+SP(12)
||         MV      .L2X    A5,B25

           STW     .D2T1   A3,*+SP(20)
||         DINT                              ; interrupts off
||         MV      .L2X    A3,B21

           STW     .D2T2   B6,*+SP(24)
||         MV      .L2X    A11,B16
||         MV      .S2     B5,B19

           MV      .L2     B6,B20
||         MV      .S2     B12,B23
||         MV      .D2     B31,B17

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/sinsp/sinsp_d.c
;*      Loop source line                 : 115
;*      Loop opening brace source line   : 115
;*      Loop closing brace source line   : 117
;*      Known Minimum Trip Count         : 10                    
;*      Known Maximum Trip Count         : 10                    
;*      Known Max Trip Count Factor      : 10
;*      Loop Carried Dependency Bound(^) : 71
;*      Unpartitioned Resource Bound     : 5
;*      Partitioned Resource Bound(*)    : 9
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     1        3     
;*      .D units                     0        2     
;*      .M units                     1        9*    
;*      .X cross paths               1        1     
;*      .T address paths             0        2     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        9     (.L or .S unit)
;*      Addition ops (.LSD)          0        5     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        6     
;*      Bound(.L .S .D .LS .LSD)     1        7     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 71 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |*   *                           |        **      **********      |
;*       1: |*   *                           |        **      **********      |
;*       2: |*   *                           |        **      **********      |
;*       3: |*   *                           |        **      **********      |
;*       4: |*   *                           |        **      **********      |
;*       5: |*   *                           |    *   **      **********      |
;*       6: |*   *                           |    **  **      **********      |
;*       7: |*   *                           |*   *   **      **********      |
;*       8: |*   *                           |    *   **      **********      |
;*       9: |*   *                           |    *   **      **********      |
;*      10: |*   *                           |    *   **      **********      |
;*      11: |*   *                           |    *   **      **********      |
;*      12: |*   *                           |    **  **      **********      |
;*      13: |*   *                           |    *   **      **********      |
;*      14: |*   *                           |    *   **      **********      |
;*      15: |*   *                           |    *   **      **********      |
;*      16: |*   *                           |    **  **      **********      |
;*      17: |*   *                           |    **  **      **********      |
;*      18: |*   *                           |    *   **      **********      |
;*      19: |*   *                           |    *   **      **********      |
;*      20: |*   *                           |    **  **      **********      |
;*      21: |*   *                           |    *** **      **********      |
;*      22: |*   *                           |    * * **      **********      |
;*      23: |*   *                           |    * * **      **********      |
;*      24: |*   *                           |    *** **      **********      |
;*      25: |*  **                           |      * **      **********      |
;*      26: |*  **                           |      * **      **********      |
;*      27: |*  **                           |    * * **      **********      |
;*      28: |*   *                           |      * **      **********      |
;*      29: |*   *                           |      * **      **********      |
;*      30: |*   *                           |     ** **      **********      |
;*      31: |*   *                           |     ** **      **********      |
;*      32: |*   *                           |     ** **      **********      |
;*      33: |*   *                           |     ** **      **********      |
;*      34: |*   *                           |     *****      **********      |
;*      35: |*   *                           |     *****      **********      |
;*      36: |*   *                           |     *****      **********      |
;*      37: |*   *                           |     *****      **********      |
;*      38: |*   *                           |    ******      **********      |
;*      39: |*   *                           |     *****      **********      |
;*      40: |*   *                           |     *****      **********      |
;*      41: |*   *                           |    ******      **********      |
;*      42: |*   *                           |     *****      **********      |
;*      43: |*   *                           |     *****      **********      |
;*      44: |*   *                           |     *****      **********      |
;*      45: |*   *                           |    ******      **********      |
;*      46: |*   *                           |     *****      **********      |
;*      47: |*   *                           |     *****      **********      |
;*      48: |*   *                           |    ******      **********      |
;*      49: |*   *                           |     *****      **********      |
;*      50: |*   *                           |     *****      **********      |
;*      51: |*   *                           |     *****      **********      |
;*      52: |*   *                           |    ******      **********      |
;*      53: |*   *                           |     *****      **********      |
;*      54: |*   *                           |     *****      **********      |
;*      55: |*   *                           |    ******      **********      |
;*      56: |*   *                           |     ** **      **********      |
;*      57: |*   *                           |     ** **      **********      |
;*      58: |*   *                           |     ** **      **********      |
;*      59: |*   *                           |    *** **      **********      |
;*      60: |*   *                           |     ** **      **********      |
;*      61: |*   *                           |     ** **      **********      |
;*      62: |*   *                           |     ** **      **********      |
;*      63: |*   *                           |    *** **      **********      |
;*      64: |*   *                           |      * **      **********      |
;*      65: |*   *                           |*       **      **********      |
;*      66: |*   *                           |    **  **      **********      |
;*      67: |*   *                           |        **      **********      |
;*      68: |*   *                           |        **      **********      |
;*      69: |*   *                           |        **      **********      |
;*      70: |*   *                           |    *   **      **********      |
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
;*      Total cycles (est.)         : 0 + min_trip_cnt * 71 = 710        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A0,1,A0
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C97:
;*   0              LDW     .D2T2   *B8++,B4          ; |84|  ^ 
;*   1              NOP             4
;*   5              ABSSP   .S2     B4,B5             ; |84|  ^ 
;*   6              CMPGTSP .S2     B5,B23,B0         ; |84|  ^ 
;*   7      [ B0]   MV      .L2     B24,B4            ; |84|  ^ 
;*   8              MPYSP   .M2     B25,B4,B5         ; |84|  ^ 
;*   9              NOP             3
;*  12              SPINT   .L2     B5,B5             ; |84|  ^ 
;*  13              NOP             3
;*  16              INTSP   .L2     B5,B5             ; |84|  ^ 
;*     ||           AND     .S2     1,B5,B5           ; |116| 
;*  17              INTSP   .L2     B5,B6             ; |116| 
;*  18              NOP             2
;*  20              MPYSP   .M2     B22,B5,B5         ; |84|  ^ 
;*  21              MPYSP   .M1X    A4,B5,A3          ; |84| 
;*  22              NOP             2
;*  24              FSUBSP  .L2     B4,B5,B4          ; |84|  ^ 
;*  25              NOP             2
;*  27              FSUBSP  .L2X    B4,A3,B5          ; |84|  ^ 
;*  28              NOP             2
;*  30              MPYSP   .M2     B5,B5,B7          ; |84|  ^ 
;*  31              NOP             3
;*  34              MPYSP   .M2     B16,B7,B4         ; |116|  ^ 
;*  35              NOP             3
;*  38              FADDSP  .L2     B17,B4,B4         ; |116|  ^ 
;*  39              NOP             2
;*  41              MPYSP   .M2     B7,B4,B4          ; |116|  ^ 
;*  42              NOP             3
;*  45              FADDSP  .L2     B18,B4,B4         ; |116|  ^ 
;*  46              NOP             2
;*  48              MPYSP   .M2     B7,B4,B4          ; |116|  ^ 
;*  49              NOP             3
;*  52              FADDSP  .L2     B19,B4,B4         ; |116|  ^ 
;*  53              NOP             2
;*  55              MPYSP   .M2     B7,B4,B4          ; |116|  ^ 
;*  56              NOP             3
;*  59              MPYSP   .M2     B5,B4,B4          ; |116|  ^ 
;*  60              NOP             3
;*  63              FADDSP  .L2     B4,B5,B4          ; |116|  ^ 
;*  64              CMPEQSP .S2     B6,B24,B0         ; |116| 
;*  65      [!B0]   MV      .S2     B20,B5            ; |116| 
;*     ||   [ B0]   MV      .D2     B21,B5            ; |116| 
;*     ||   [ A0]   BDEC    .S1     $C$C97,A0         ; |115| 
;*  66              MPYSP   .M2     B5,B4,B4          ; |116|  ^ 
;*  67              NOP             3
;*  70              STW     .D2T2   B4,*B9++          ; |116|  ^ 
;*  71              ; BRANCHCC OCCURS {$C$C97}        ; |115| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 71
           LDW     .D2T2   *B8++,B4          ; |84| <0,0>  ^ 
           NOP             4
           ABSSP   .S2     B4,B5             ; |84| <0,5>  ^ 
           CMPGTSP .S2     B5,B23,B0         ; |84| <0,6>  ^ 
   [ B0]   MV      .L2     B24,B4            ; |84| <0,7>  ^ 
           MPYSP   .M2     B25,B4,B5         ; |84| <0,8>  ^ 
           NOP             3
           SPINT   .L2     B5,B5             ; |84| <0,12>  ^ 
           NOP             3

           AND     .S2     1,B5,B5           ; |116| <0,16> 
||         INTSP   .L2     B5,B5             ; |84| <0,16>  ^ 

           INTSP   .L2     B5,B6             ; |116| <0,17> 
           NOP             2
           MPYSP   .M2     B22,B5,B5         ; |84| <0,20>  ^ 
           MPYSP   .M1X    A4,B5,A3          ; |84| <0,21> 
           NOP             2
           FSUBSP  .L2     B4,B5,B4          ; |84| <0,24>  ^ 
           NOP             2
           FSUBSP  .L2X    B4,A3,B5          ; |84| <0,27>  ^ 
           NOP             2
           MPYSP   .M2     B5,B5,B7          ; |84| <0,30>  ^ 
           NOP             3
           MPYSP   .M2     B16,B7,B4         ; |116| <0,34>  ^ 
           NOP             3
           FADDSP  .L2     B17,B4,B4         ; |116| <0,38>  ^ 
           NOP             2
           MPYSP   .M2     B7,B4,B4          ; |116| <0,41>  ^ 
           NOP             3
           FADDSP  .L2     B18,B4,B4         ; |116| <0,45>  ^ 
           NOP             2
           MPYSP   .M2     B7,B4,B4          ; |116| <0,48>  ^ 
           NOP             3
           FADDSP  .L2     B19,B4,B4         ; |116| <0,52>  ^ 
           NOP             2
           MPYSP   .M2     B7,B4,B4          ; |116| <0,55>  ^ 
           NOP             3
           MPYSP   .M2     B5,B4,B4          ; |116| <0,59>  ^ 
           NOP             3
           FADDSP  .L2     B4,B5,B4          ; |116| <0,63>  ^ 
           CMPEQSP .S2     B6,B24,B0         ; |116| <0,64> 

   [!B0]   MV      .S2     B20,B5            ; |116| <0,65> 
|| [ B0]   MV      .D2     B21,B5            ; |116| <0,65> 
|| [ A0]   BDEC    .S1     $C$L5,A0          ; |115| <0,65> 

           MPYSP   .M2     B5,B4,B4          ; |116| <0,66>  ^ 
           NOP             3
           STW     .D2T2   B4,*B9++          ; |116| <0,70>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STW     .D2T2   B20,*+SP(24)
||         MV      .L1X    B18,A13

           STW     .D2T2   B21,*+SP(20)
||         MV      .L1X    B17,A12

           STW     .D2T2   B22,*+SP(16)
||         MV      .L1X    B16,A11

           MV      .L2X    A4,B13
||         MV      .L1X    B19,A15
||         STW     .D2T2   B25,*+SP(12)
||         RINT                              ; interrupts on

           CALLP   .S2     _sinsp_v,B3
||         LDW     .D2T2   *+B11(16),B4      ; |118| 
||         MV      .L1     A14,A4            ; |118| 
||         MVK     .S1     0xa,A6            ; |118| 
||         MV      .L2     B23,B12
||         MV      .D1X    B24,A10

$C$RL4:    ; CALL OCCURS {_sinsp_v} {0}      ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 48
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B11,A4           ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xeb1c432d,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .L1     0xa,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0xeb1c432d,B6

           MV      .L2     B11,B5
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     _fcn_pass,B4
           MVKL    .S2     _output,B31
           MVKH    .S2     0x3f1a36e2,B7

           ADD     .L1X    4,B10,A3
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           MVKH    .S2     _output,B31
||         STW     .D2T1   A3,*+SP(40)

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
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
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           ADD     .L2     8,B5,B4
           STW     .D2T2   B4,*+SP(48)       ; |69| 
           STW     .D2T1   A3,*+SP(44)

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |122| 
   [!A0]   ZERO    .L1     A3                ; |72| 
   [ A0]   ADD     .L2     4,B4,B4
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
;          EXCLUSIVE CPU CYCLES: 8
           LDW     .D2T1   *+SP(20),A4       ; |134| 

           LDW     .D2T1   *+SP(24),A5       ; |130| 
||         MVKL    .S2     _a_sc,B6

           MVKH    .S2     _a_sc,B6
||         ZERO    .L2     B5
||         MVK     .D2     0x7,B31

           STW     .D2T2   B31,*+SP(28)      ; |132| 
||         MVKH    .S2     0x80000000,B5
||         MV      .L2X    A10,B4            ; |130| 

           STDW    .D2T2   B5:B4,*B6         ; |130| 
||         ZERO    .L1     A7
||         MVK     .L2     -1,B7             ; |135| 

           STW     .D2T2   B7,*+B6(24)       ; |135| 
||         MVKH    .S1     0xff800000,A7
||         ZERO    .L1     A6

           STDW    .D2T1   A5:A4,*+B6(16)    ; |134| 
||         MV      .L2     B6,B4             ; |130| 
||         SET     .S1     A6,0x17,0x1e,A6

           STDW    .D2T1   A7:A6,*+B4(8)     ; |132| 
||         MV      .L1X    B6,A14            ; |130| 
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
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D1T1   *A14,A3           ; |137| 
           CALL    .S1     _sin              ; |137| 
           ADDKPC  .S2     $C$RL10,B3,2      ; |137| 
           SPDP    .S1     A3,A5:A4          ; |137| 
           NOP             1
$C$RL10:   ; CALL OCCURS {_sin} {0}          ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |137| 
           DPSP    .L1     A5:A4,A3          ; |137| 
           NOP             3
           ADD     .L2     B11,B4,B4         ; |137| 
           STW     .D2T1   A3,*B4            ; |137| 

           CALLP   .S2     _sinsp,B3
||         LDW     .D1T1   *A14,A4           ; |138| 

$C$RL11:   ; CALL OCCURS {_sinsp} {0}        ; |138| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(4),B4        ; |138| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |138| 
           STW     .D2T1   A4,*B4            ; |138| 

           CALLP   .S2     _sinsp_c,B3
||         LDW     .D1T1   *A14,A4           ; |139| 

$C$RL12:   ; CALL OCCURS {_sinsp_c} {0}      ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 84
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |139| 
           LDW     .D2T1   *+SP(12),A31      ; |72| 
           LDW     .D2T1   *+SP(16),A6
           LDW     .D2T2   *+SP(28),B5       ; |140| 
           LDW     .D2T2   *B10,B31          ; |140| 
           ADD     .L2     B11,B4,B4         ; |139| 
           STW     .D2T1   A4,*B4            ; |139| 
           LDW     .D1T1   *A14++,A3         ; |69| 
           SUB     .L2     B5,1,B30          ; |136| 
           SUB     .L1X    B5,1,A2           ; |136| 
           STW     .D2T2   B30,*+SP(28)      ; |140| 
           NOP             1
           ABSSP   .S1     A3,A4             ; |71| 
           NOP             1
           CMPGTSP .S2X    A4,B12,B0         ; |71| 
   [ B0]   MV      .L1     A10,A3            ; |72| 
           MPYSP   .M1     A31,A3,A4         ; |77| 
           NOP             3
           SPINT   .L1     A4,A5             ; |77| 
           NOP             3
           INTSP   .L1     A5,A4             ; |77| 
           AND     .L1     1,A5,A5           ; |80| 
           INTSP   .L1     A5,A5             ; |80| 
           NOP             1
           MPYSP   .M1     A6,A4,A6          ; |140| 
           MPYSP   .M2X    B13,A4,B4         ; |140| 
           CMPEQSP .S1     A5,A10,A0         ; |80| 
           NOP             1
           FSUBSP  .L1     A3,A6,A3          ; |140| 
           NOP             2
           FSUBSP  .L1X    A3,B4,A3          ; |140| 
           ADD     .L2     B11,B31,B4        ; |140| 
           ADD     .L2     4,B11,B11         ; |136| 
           MPYSP   .M1     A3,A3,A4          ; |140| 
   [!A2]   MVKL    .S2     _output,B11
   [!A2]   MVKH    .S2     _output,B11
           NOP             1
           MPYSP   .M1     A11,A4,A6         ; |140| 
           NOP             3
           FADDSP  .L1     A12,A6,A6         ; |140| 
           NOP             2
           MPYSP   .M1     A4,A6,A6          ; |140| 
           NOP             3
           FADDSP  .L1     A13,A6,A6         ; |140| 
           NOP             2
           MPYSP   .M1     A4,A6,A6          ; |140| 
           NOP             3
           FADDSP  .L1     A15,A6,A6         ; |140| 
           NOP             2
           MPYSP   .M1     A4,A6,A4          ; |140| 
           NOP             3
           MPYSP   .M1     A3,A4,A4          ; |140| 
           NOP             3

           FADDSP  .L1     A4,A3,A4          ; |140| 
|| [!A0]   LDW     .D2T1   *+SP(24),A3       ; |140| 

   [ A0]   LDW     .D2T1   *+SP(20),A3       ; |80| 
           NOP             3
   [ A2]   B       .S1     $C$L8             ; |136| 
           MPYSP   .M1     A3,A4,A3          ; |140| 
           NOP             3

   [!A2]   CALL    .S1     _sinsp_v          ; |142| 
||         STW     .D2T1   A3,*B4            ; |140| 

           ; BRANCHCC OCCURS {$C$L8}         ; |136| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B11(16),B4      ; |142| 
           MVKL    .S1     _a_sc,A4
           MVKH    .S1     _a_sc,A4
           MVK     .L1     0x7,A6            ; |142| 
           ADDKPC  .S2     $C$RL13,B3,0      ; |142| 
$C$RL13:   ; CALL OCCURS {_sinsp_v} {0}      ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     _fcn_pass,B5
           MVKL    .S2     0xeb1c432d,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3f1a36e2,B7

           MV      .L1X    B11,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |68| 

           LDW     .D2T1   *+SP(40),A3       ; |68| 
||         MVKL    .S2     _fcn_pass,B4

           MVKL    .S2     0xeb1c432d,B6
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     _fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           MV      .L2     B11,B31           ; |69| 
||         STW     .D2T1   A3,*+SP(52)       ; |68| 
||         MVKH    .S2     0x3f1a36e2,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(44),A3       ; |69| 
           MVKL    .S2     _fcn_pass,B31
           MVKH    .S2     _fcn_pass,B31
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           NOP             1

           MV      .L2X    A3,B4             ; |69| 
||         STW     .D2T1   A3,*+SP(56)       ; |69| 

           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T1   *+SP(48),A3
           NOP             3

   [!B0]   B       .S1     $C$L9             ; |72| 
|| [!B0]   ZERO    .L1     A4                ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     _print_test_results ; |146| 
|| [ B0]   MV      .L2X    A3,B4
||         STW     .D2T1   A3,*+SP(60)       ; |72| 
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
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S2     0xc000cccc,B4
           MVKL    .S2     0xcccccccd,B31
           MVK     .S2     0x81,B29
           MVKL    .S2     _a_ext,B5
           MVKH    .S2     0xc000cccc,B4

           MVKH    .S2     0xcccccccd,B31
||         STW     .D2T2   B29,*+SP(28)      ; |149| 

           MVKH    .S2     _a_ext,B5
||         ZERO    .L1     A4
||         STW     .D2T2   B4,*+SP(68)       ; |155| 

           MV      .L2     B5,B30            ; |149| 
||         SET     .S1     A4,0x17,0x17,A4
||         STW     .D2T2   B31,*+SP(64)      ; |155| 

           MV      .L1X    B5,A14            ; |149| 
||         STW     .D2T1   A4,*B30           ; |149| 

           LDW     .D1T1   *A14,A3           ; |151| 
           CALL    .S1     _sin              ; |151| 
           ZERO    .L2     B11
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |151| 
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
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL19,B3,0      ; |151| 
$C$RL19:   ; CALL OCCURS {_sin} {0}          ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T1   *B4,A3            ; |151| 
           DPSP    .L1     A5:A4,A4          ; |151| 
           NOP             3
           ADD     .L1X    B11,A3,A3         ; |151| 
           STW     .D1T1   A4,*A3            ; |151| 

           CALLP   .S2     _sinsp,B3
||         LDW     .D1T1   *A14,A4           ; |152| 

$C$RL20:   ; CALL OCCURS {_sinsp} {0}        ; |152| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(4),B4        ; |152| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |152| 
           STW     .D2T1   A4,*B4            ; |152| 

           CALLP   .S2     _sinsp_c,B3
||         LDW     .D1T1   *A14,A4           ; |153| 

$C$RL21:   ; CALL OCCURS {_sinsp_c} {0}      ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 109
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |153| 
           LDW     .D2T1   *+SP(12),A31      ; |72| 
           LDW     .D2T1   *+SP(16),A30
           LDW     .D2T2   *B10,B31          ; |154| 
           NOP             1
           ADD     .L2     B11,B4,B4         ; |153| 
           STW     .D2T1   A4,*B4            ; |153| 
           LDW     .D1T1   *A14,A4           ; |69| 
           NOP             4
           ABSSP   .S1     A4,A3             ; |71| 
           NOP             1
           CMPGTSP .S2X    A3,B12,B0         ; |71| 
   [ B0]   MV      .L1     A10,A4            ; |72| 
           MPYSP   .M1     A31,A4,A3         ; |77| 
           NOP             3
           SPINT   .L1     A3,A6             ; |77| 
           NOP             3
           INTSP   .L1     A6,A5             ; |77| 
           AND     .L1     1,A6,A29          ; |80| 
           NOP             2
           MPYSP   .M1     A30,A5,A3         ; |154| 
           MPYSP   .M2X    B13,A5,B4         ; |154| 
           NOP             2
           FSUBSP  .L1     A4,A3,A3          ; |154| 
           NOP             2
           FSUBSP  .L1X    A3,B4,A3          ; |154| 
           ADD     .L2     B11,B31,B4        ; |154| 
           ADD     .L2     4,B11,B11         ; |150| 
           MPYSP   .M1     A3,A3,A4          ; |154| 
           NOP             3
           MPYSP   .M1     A11,A4,A5         ; |154| 
           NOP             3
           FADDSP  .L1     A12,A5,A5         ; |154| 
           NOP             2
           MPYSP   .M1     A4,A5,A5          ; |154| 
           NOP             3
           FADDSP  .L1     A13,A5,A5         ; |154| 
           NOP             2
           MPYSP   .M1     A4,A5,A5          ; |154| 
           NOP             3
           FADDSP  .L1     A15,A5,A5         ; |154| 
           NOP             2
           MPYSP   .M1     A4,A5,A5          ; |154| 
           INTSP   .L1     A29,A4            ; |80| 
           NOP             2
           MPYSP   .M1     A3,A5,A5          ; |154| 
           CMPEQSP .S1     A4,A10,A0         ; |80| 
           NOP             2

           FADDSP  .L1     A5,A3,A4          ; |154| 
|| [!A0]   LDW     .D2T1   *+SP(24),A3       ; |154| 

   [ A0]   LDW     .D2T1   *+SP(20),A3       ; |80| 
           NOP             4
           MPYSP   .M1     A3,A4,A3          ; |154| 
           NOP             3
           STW     .D2T1   A3,*B4            ; |154| 
           LDW     .D1T2   *A14,B6           ; |155| 
           LDDW    .D2T2   *+SP(64),B5:B4
           NOP             4
           MPYSPDP .M2     B6,B5:B4,B5:B4    ; |155| 
           NOP             6

           DPSP    .L2     B5:B4,B5          ; |155| 
||         LDW     .D2T2   *+SP(28),B4

           NOP             3
           STW     .D1T2   B5,*++A14         ; |155| 

           SUB     .L1X    B4,1,A0           ; |150| 
||         SUB     .L2     B4,1,B4           ; |150| 

   [ A0]   B       .S1     $C$L10            ; |150| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |151| 
|| [!A0]   MVKL    .S2     _output,B10
||         STW     .D2T2   B4,*+SP(28)       ; |155| 

   [ A0]   CALL    .S1     _sin              ; |151| 
   [!A0]   MVKH    .S2     _output,B10
   [!A0]   LDW     .D2T2   *+B10(16),B4      ; |157| 
   [!A0]   CALL    .S1     _sinsp_v          ; |157| 
           SPDP    .S1     A3,A5:A4          ; |151| 
           ; BRANCHCC OCCURS {$C$L10}        ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL22,B3,0      ; |157| 
           MVKL    .S1     _a_ext,A4
           MVKH    .S1     _a_ext,A4
           MVK     .S1     0x81,A6           ; |157| 
$C$RL22:   ; CALL OCCURS {_sinsp_v} {0}      ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0x81,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL23:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B11
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     _fcn_pass,B11
           MVKL    .S2     0xeb1c432d,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B11(4)       ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0x81,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL24:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           MV      .L1X    B10,A3            ; |67| 
||         STW     .D2T1   A4,*+B11(8)       ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0x81,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL25:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(40),A3       ; |68| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           MV      .L2     B10,B4            ; |68| 
||         STW     .D2T1   A4,*+B11(12)      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x81,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(44),A3       ; |69| 
           LDW     .D2T2   *+SP(48),B4
           STW     .D2T1   A4,*+B11(16)      ; |69| 
           NOP             2
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |161| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   ZERO    .L1     A3                ; |72| 
   [!A0]   MVKL    .S1     _all_pass,A4
   [!A0]   MVKH    .S1     _all_pass,A4
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
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   ZERO    .L1     A3                ; |72| 
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
;          EXCLUSIVE CPU CYCLES: 20
           ZERO    .L2     B7                ; |114| 

           ZERO    .L2     B6                ; |114| 
||         STW     .D2T2   B7,*+SP(64)       ; |114| 

           STW     .D2T2   B6,*+SP(68)       ; |114| 
           LDDW    .D2T2   *+SP(64),B7:B6    ; |114| 
           MVKL    .S2     _cycle_counts+24,B5
           MVKH    .S2     _cycle_counts+24,B5
           ZERO    .L2     B4                ; |114| 
           NOP             1

           STDW    .D2T2   B7:B6,*B5         ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           ZERO    .L1     A4
||         CALL    .S2     _gimme_random     ; |171| 
||         MVKL    .S1     _t_offset,A3

           MVKH    .S1     0xc2c80000,A4
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         ZERO    .L1     A14
||         MVK     .S2     0x80,B30

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKH    .S1     0x43480000,A14

           MV      .L2X    A4,B11
||         ADD     .S2     B31,B6,B5         ; |117| 
||         MVKH    .S1     _t_offset,A3
||         STW     .D2T2   B30,*+SP(28)      ; |117| 

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MV      .L2     B11,B4            ; |171| 
||         MV      .L1     A14,A4            ; |171| 
||         ZERO    .S2     B10

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
$C$RL28:   ; CALL OCCURS {_gimme_random} {0}  ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 106
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T1   *A3,A3            ; |171| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |171| 

           STW     .D1T1   A4,*A3            ; |171| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B7           ; |122| 

           LDW     .D2T1   *+SP(12),A3       ; |72| 
||         ABSSP   .S2X    A4,B4             ; |71| 
||         MVKL    .S1     _t_start,A30

           CMPGTSP .S2     B4,B12,B0         ; |71| 
||         LDW     .D2T1   *+SP(16),A5
||         MVKH    .S1     _t_start,A30

   [ B0]   MV      .L1     A10,A4            ; |72| 
||         MVKL    .S2     _output+12,B31
||         STDW    .D1T2   B7:B6,*A30

           MVKH    .S2     _output+12,B31
           NOP             1
           MPYSP   .M1     A3,A4,A3          ; |77| 
           NOP             3
           SPINT   .L1     A3,A6             ; |77| 
           NOP             3

           INTSP   .L1     A6,A3             ; |77| 
||         AND     .S1     1,A6,A31          ; |80| 

           NOP             3
           MPYSP   .M1     A5,A3,A5          ; |175| 
           MPYSP   .M2X    B13,A3,B4         ; |175| 
           NOP             2
           FSUBSP  .L1     A4,A5,A3          ; |175| 
           NOP             2

           FSUBSP  .L1X    A3,B4,A4          ; |175| 
||         LDW     .D2T2   *B31,B4           ; |175| 

           NOP             2
           MPYSP   .M1     A4,A4,A3          ; |175| 
           NOP             1
           ADD     .L2     B10,B4,B4         ; |175| 
           NOP             1
           MPYSP   .M1     A11,A3,A5         ; |175| 
           NOP             3
           FADDSP  .L1     A12,A5,A5         ; |175| 
           NOP             2
           MPYSP   .M1     A3,A5,A5          ; |175| 
           NOP             3
           FADDSP  .L1     A13,A5,A5         ; |175| 
           NOP             2
           MPYSP   .M1     A3,A5,A5          ; |175| 
           NOP             3
           FADDSP  .L1     A15,A5,A5         ; |175| 
           NOP             2

           MPYSP   .M1     A3,A5,A3          ; |175| 
||         INTSP   .L1     A31,A5            ; |80| 

           NOP             3

           MPYSP   .M1     A4,A3,A3          ; |175| 
||         CMPEQSP .S1     A5,A10,A0         ; |80| 

           NOP             3

           FADDSP  .L1     A3,A4,A4          ; |175| 
|| [!A0]   LDW     .D2T1   *+SP(24),A3       ; |175| 

   [ A0]   LDW     .D2T1   *+SP(20),A3       ; |80| 
           NOP             4
           MPYSP   .M1     A3,A4,A4          ; |175| 
           NOP             3

           STW     .D2T1   A4,*B4            ; |175| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S1     _t_offset,A3
||         MVKL    .S2     _t_stop,B29
||         ADD     .L2     4,B10,B10         ; |169| 

           MVKH    .S1     _t_offset,A3
||         MVKH    .S2     _t_stop,B29

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         MVKL    .S1     _cycle_counts+24,A3
||         STDW    .D2T2   B9:B8,*B29        ; |128| 

           MVKH    .S1     _cycle_counts+24,A3
           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           NOP             2
           ADDU    .L2X    A4,B6,B5:B4       ; |130| 

           ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B30      ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B6,B7          ; |130| 
||         ADD     .S2X    B5,A7,B6          ; |130| 

           ADD     .L2     B7,B30,B7         ; |130| 

           ADD     .L2     B6,B7,B5          ; |130| 
||         LDW     .D2T2   *+SP(28),B6       ; |130| 

           STDW    .D1T2   B5:B4,*A3         ; |130| 
           NOP             3

           SUB     .L1X    B6,1,A0           ; |169| 
||         SUB     .L2     B6,1,B4           ; |169| 

           STW     .D2T2   B4,*+SP(28)       ; |130| 
|| [ A0]   MV      .L1     A14,A4            ; |171| 
|| [ A0]   MV      .L2     B11,B4            ; |171| 
|| [ A0]   B       .S1     $C$L12            ; |169| 
|| [!A0]   LDDW    .D1T1   *A3,A5:A4         ; |135| 

   [ A0]   CALL    .S1     _gimme_random     ; |171| 
   [!A0]   CALL    .S1     __fltllif         ; |135| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L12}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL29,B3,1      ; |135| 
$C$RL29:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A14
           SET     .S1     A14,0x1a,0x1d,A14
           MPYSP   .M1     A14,A4,A3         ; |135| 
           ZERO    .L1     A11
           SET     .S1     A11,0x15,0x1d,A11
           ZERO    .L1     A10               ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL30:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVKL    .S1     _cycle_counts+24,A3

           LDDW    .D2T2   *+SP(64),B5:B4
||         MVKH    .S1     _cycle_counts+24,A3

           MV      .L2X    A10,B31           ; |114| 
           MV      .L2X    A3,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B10

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     _t_start,A10
           MVKH    .S1     _t_start,A10

           STDW    .D1T2   B7:B6,*A10        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S2     _t_offset,B11

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 
||         MVKH    .S2     _t_offset,B11

           STDW    .D2T2   B5:B4,*B11        ; |117| 
||         MVK     .S2     0x80,B4

           MVKL    .S1     _input,A15

           MV      .L1X    B4,A13            ; |117| 
||         MVKH    .S1     _input,A15
||         ZERO    .D1     A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A15,A3           ; |183| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |183| 
||         CALL    .S1     _sinf             ; |183| 

           LDW     .D1T1   *A3,A4            ; |183| 
           ADDKPC  .S2     $C$RL31,B3,3      ; |183| 
$C$RL31:   ; CALL OCCURS {_sinf} {0}         ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     _output,B4
||         SUB     .L1     A13,1,A0          ; |182| 
||         SUB     .S1     A13,1,A13         ; |182| 

           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |183| 
   [ A0]   BNOP    .S1     $C$L13,3          ; |182| 

           ADD     .L1X    A12,B4,A3         ; |183| 
||         ADD     .S1     4,A12,A12         ; |182| 

           STW     .D1T1   A4,*A3            ; |183| 
           ; BRANCHCC OCCURS {$C$L13}        ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B9:B8        ; |130| 

           MVKL    .S2     _t_stop,B12
           MV      .L2     B4,B7             ; |128| 
           MVKH    .S2     _t_stop,B12
           NOP             1
           ADDU    .L1X    B8,A6,A5:A4       ; |130| 

           ADD     .L1X    A5,B9,A3          ; |130| 
||         LDDW    .D2T2   *B10,B9:B8        ; |130| 

           ADD     .L1     A3,A7,A3          ; |130| 
||         SUBU    .L2X    B6,A4,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B7,A3,B31         ; |130| 
           CALL    .S1     __fltllif         ; |130| 

           ADDU    .L2     B8,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B8        ; |130| 

           ADD     .L2     B5,B9,B5          ; |130| 
           ADD     .L2     B5,B8,B5          ; |130| 
           STDW    .D2T2   B7:B6,*B12        ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL32,B3,0      ; |130| 

$C$RL32:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A14,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           MV      .L1     A11,A13           ; |130| 
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL33:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(64),B5:B4    ; |130| 
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A10        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 

           STDW    .D2T2   B5:B4,*B11        ; |117| 
||         MVK     .S2     0x80,B4

           LDW     .D2T2   *+SP(32),B13      ; |117| 
           MV      .L1X    B4,A11            ; |117| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A15,A3           ; |191| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |191| 
||         CALL    .S1     _sinsp            ; |191| 

           LDW     .D1T1   *A3,A4            ; |191| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |191| 
$C$RL34:   ; CALL OCCURS {_sinsp} {0}        ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |191| 
||         SUB     .L1     A11,1,A0          ; |190| 
||         SUB     .S1     A11,1,A11         ; |190| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |190| 

           ADD     .L1X    A12,B4,A3         ; |191| 
||         ADD     .S1     4,A12,A12         ; |190| 

           STW     .D1T1   A4,*A3            ; |191| 
           ; BRANCHCC OCCURS {$C$L14}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

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
||         MV      .S2     B12,B4            ; |130| 

           ADD     .L2     B31,B5,B7         ; |130| 
           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL35,B3,0      ; |130| 

$C$RL35:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A14,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL36:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(64),B5:B4
           ADDAD   .D2     B10,1,B12
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A10        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 

           STDW    .D2T2   B5:B4,*B11        ; |117| 
||         MVK     .S2     0x80,B4

           LDW     .D2T2   *+SP(36),B13      ; |117| 
           MV      .L1X    B4,A11            ; |117| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A15,A3           ; |199| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |199| 
||         CALL    .S1     _sinsp_c          ; |199| 

           LDW     .D1T1   *A3,A4            ; |199| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |199| 
$C$RL37:   ; CALL OCCURS {_sinsp_c} {0}      ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |199| 
||         SUB     .L1     A11,1,A0          ; |198| 
||         SUB     .S1     A11,1,A11         ; |198| 

   [ A0]   BNOP    .S1     $C$L15,3          ; |198| 

           ADD     .L1X    A12,B4,A3         ; |199| 
||         ADD     .S1     4,A12,A12         ; |198| 

           STW     .D1T1   A4,*A3            ; |199| 
           ; BRANCHCC OCCURS {$C$L15}        ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

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
           MPYSP   .M1     A14,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL39:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           LDDW    .D2T2   *+SP(64),B5:B4
           ADDAD   .D2     B12,1,B13
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A10        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           MVKL    .S1     _output,A11
||         ADD     .L2     B4,B5,B7          ; |117| 

           MVKH    .S1     _output,A11
||         MV      .L2X    A15,B9            ; |206| 
||         STDW    .D2T2   B7:B6,*B11        ; |117| 

           CALLP   .S2     _sinsp_v,B3
||         LDW     .D1T2   *+A11(16),B4      ; |206| 
||         LDW     .D2T1   *B9,A4            ; |206| 
||         MVK     .S1     0x80,A6           ; |206| 

$C$RL40:   ; CALL OCCURS {_sinsp_v} {0}      ; |206| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S1     16,A10
           ADD     .L1X    B13,A10,A10
           LDDW    .D1T1   *A10,A9:A8        ; |130| 
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
           MPYSP   .M1     A14,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL42:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6

           STDW    .D1T1   A5:A4,*A10        ; |130| 
||         MVKH    .S2     0x3f1a36e2,B7

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A11,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL43:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKL    .S2     _fcn_pass,B10
           MVKH    .S2     0x3f1a36e2,B7
           MVKH    .S2     0xeb1c432d,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S2     _fcn_pass,B10

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A11(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL44:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL45:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(52),A3       ; |68| 
           MVKL    .S2     0xeb1c432d,B6
           MVKL    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           LDW     .D1T1   *A11,A4           ; |69| 
||         MVKH    .S2     0x3f1a36e2,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL46:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(56),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(60),B4
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
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(80),B3      ; |224| 
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
$C$SL1:	.string	"sinSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_sin
	.global	_sinf
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_sinsp
	.global	_sinsp_c
	.global	_sinsp_v
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
