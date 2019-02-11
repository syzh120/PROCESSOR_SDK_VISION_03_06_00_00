;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:56:19 2013                                *
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
	.elfsym	a,SYM_SIZE(80)
a:
	.word	095a29414h,0408edcdbh		; a[0] @ 0
	.word	061e77ba5h,04076a092h		; a[1] @ 64
	.word	0ab72dff1h,040728016h		; a[2] @ 128
	.word	0f59bf8efh,04063cf4eh		; a[3] @ 192
	.word	0355f5d5eh,0408c4ef0h		; a[4] @ 256
	.word	09acf23bfh,040867644h		; a[5] @ 320
	.word	0244e93e2h,0408181a8h		; a[6] @ 384
	.word	0018bf13ah,040809528h		; a[7] @ 448
	.word	08806ca1fh,04067b738h		; a[8] @ 512
	.word	05fdb31eah,040856c97h		; a[9] @ 576

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\183842 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\183844 
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
           MVKL    .S1     a,A12

           MVKH    .S1     a,A12
||         MVKL    .S2     output,B13
||         MVK     .L1     0xa,A3

           CALL    .S1     rsqrt             ; |107| 
||         MV      .L1     A12,A10
||         MV      .D1     A3,A11
||         MVKH    .S2     output,B13
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |107| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |107| 
$C$RL1:    ; CALL OCCURS {rsqrt} {0}         ; |107| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |107| 
||         SUB     .L1     A11,1,A0          ; |106| 
||         SUB     .S1     A11,1,A11         ; |106| 

   [ A0]   BNOP    .S1     $C$L1,2           ; |106| 
|| [!A0]   MVK     .L1     0xa,A3
|| [!A0]   ADD     .L2     4,B13,B11
|| [!A0]   MV      .D1     A12,A10

   [!A0]   MV      .L1     A3,A11

           ADD     .L2     B10,B4,B4         ; |107| 
||         ADD     .S2     8,B10,B10         ; |106| 

   [ A0]   CALL    .S1     rsqrt             ; |107| 
|| [!A0]   ZERO    .L2     B10
||         STDW    .D2T1   A5:A4,*B4         ; |107| 

           ; BRANCHCC OCCURS {$C$L1}         ; |106| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     rsqrtdp           ; |110| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |110| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |110| 
$C$RL2:    ; CALL OCCURS {rsqrtdp} {0}       ; |110| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |110| 
||         SUB     .L1     A11,1,A0          ; |109| 
||         SUB     .S1     A11,1,A11         ; |109| 

   [ A0]   BNOP    .S1     $C$L2,2           ; |109| 
|| [!A0]   MVK     .L1     0xa,A3
|| [!A0]   ZERO    .L2     B12
|| [!A0]   MV      .D1     A12,A11

   [!A0]   MV      .L1     A3,A10

           ADD     .L2     B10,B4,B4         ; |110| 
||         ADD     .S2     8,B10,B10         ; |109| 

   [ A0]   CALL    .S1     rsqrtdp           ; |110| 
|| [!A0]   ADD     .L2     4,B11,B10
||         STDW    .D2T1   A5:A4,*B4         ; |110| 

           ; BRANCHCC OCCURS {$C$L2}         ; |109| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     rsqrtdp_c         ; |113| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |113| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |113| 
$C$RL3:    ; CALL OCCURS {rsqrtdp_c} {0}     ; |113| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B10,B4           ; |113| 
||         SUB     .L1     A10,1,A0          ; |112| 
||         SUB     .S1     A10,1,A10         ; |112| 

   [ A0]   BNOP    .S1     $C$L3,3           ; |112| 

           ADD     .L2     B12,B4,B4         ; |113| 
||         ADD     .S2     8,B12,B12         ; |112| 

   [ A0]   CALL    .S1     rsqrtdp_c         ; |113| 
||         STDW    .D2T1   A5:A4,*B4         ; |113| 

           ; BRANCHCC OCCURS {$C$L3}         ; |112| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           ZERO    .L2     B4
||         MVKL    .S1     0x7fefffff,A11
||         MVK     .L1     0xffffffff,A10
||         MV      .D1X    B13,A15
||         DINT                              ; interrupts off
||         MV      .D2X    A12,B0

           SET     .S2     B4,0x13,0x1d,B21
||         ZERO    .L2     B4
||         MVKH    .S1     0x7fefffff,A11
||         LDW     .D1T2   *+A15(12),B1
||         ZERO    .D2     B20               ; |62| 
||         MVK     .L1     9,A1

           SET     .S2     B4,0x15,0x1d,B19
||         MV      .L2     B21,B29
||         MV      .D2     B21,B25           ; |62| 

           MV      .L2X    A11,B31
||         MV      .S2     B19,B27
||         MV      .D2     B19,B23           ; |62| 

           MV      .L2X    A10,B30
||         ZERO    .S2     B18               ; |62| 
||         ZERO    .D2     B24               ; |62| 

           ZERO    .L2     B28               ; |62| 
||         ZERO    .S2     B26               ; |62| 
||         ZERO    .D2     B22               ; |62| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/rsqrtdp/rsqrtdp_d.c
;*      Loop source line                 : 115
;*      Loop opening brace source line   : 115
;*      Loop closing brace source line   : 117
;*      Known Minimum Trip Count         : 10                    
;*      Known Maximum Trip Count         : 10                    
;*      Known Max Trip Count Factor      : 10
;*      Loop Carried Dependency Bound(^) : 53
;*      Unpartitioned Resource Bound     : 6
;*      Partitioned Resource Bound(*)    : 12
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     1        0     
;*      .S units                     3        2     
;*      .D units                     0        2     
;*      .M units                     0       12*    
;*      .X cross paths               2        0     
;*      .T address paths             0        2     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        4     (.L or .S unit)
;*      Addition ops (.LSD)          0        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             2        3     
;*      Bound(.L .S .D .LS .LSD)     2        3     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 53 Did not find schedule
;*         ii = 54 Did not find schedule
;*         ii = 55 Did not find schedule
;*         ii = 57 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: | *                              |**                **************|
;*       1: | *                              |**                **************|
;*       2: | *                              |**                **************|
;*       3: | *                              |**                **************|
;*       4: | *                              |**                **************|
;*       5: | *                              |**              ****************|
;*       6: | *                              |**              ****************|
;*       7: | *                              |**      **      ****************|
;*       8: | *                              |**      **      ****************|
;*       9: | *                              |**      **      ****************|
;*      10: | *                              |**      **      ****************|
;*      11: | *                              |**  **  **      ****************|
;*      12: | *                              |**  ******      ****************|
;*      13: | *                              |**      **      ****************|
;*      14: | *                              |**      **      ****************|
;*      15: | *                              |**      **      ****************|
;*      16: | *                              |**  **  **      ****************|
;*      17: | *                              |**      **      ****************|
;*      18: | *                              |**      **      ****************|
;*      19: | *                              |**  **  **      ****************|
;*      20: | *                              |**              ****************|
;*      21: | *                              |**              ****************|
;*      22: | *                              |**              ****************|
;*      23: | *                              |**  **          ****************|
;*      24: | *                              |**  **          ****************|
;*      25: | *                              |**  **          ****************|
;*      26: | *                              |**  **          ****************|
;*      27: | *                              |**  **  **      ****************|
;*      28: | *                              |**  ******      ****************|
;*      29: | *                              |**  **          ****************|
;*      30: | *                              |**  **          ****************|
;*      31: | *                              |**  **          ****************|
;*      32: | *                              |**  ****        ****************|
;*      33: | *                              |**  **          ****************|
;*      34: | *                              |**  **          ****************|
;*      35: | *                              |**  ****        ****************|
;*      36: | *                              |**              ****************|
;*      37: | *                              |**              ****************|
;*      38: | *                              |**              ****************|
;*      39: | *                              |**      **      ****************|
;*      40: | *                              |**      **      ****************|
;*      41: | *                              |**      **      ****************|
;*      42: | *                              |**      **      ****************|
;*      43: | *                              |**  **  **      ****************|
;*      44: | *                              |**  ******      ****************|
;*      45: | *                              |**      **      ****************|
;*      46: | *                              |**      **      ****************|
;*      47: | *                              |**      **      ****************|
;*      48: | *  **                          |**  **  **      ****************|
;*      49: | *  **                          |**      **      ****************|
;*      50: |**                              |**      **        **************|
;*      51: |**                              |**  **  **        **************|
;*      52: |**                              |**                **************|
;*      53: |**                              |**                **************|
;*      54: |**                              |**                **************|
;*      55: | *                              |**  **            **************|
;*      56: |                                |                                |
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
;*      Total cycles (est.)         : -1 + min_trip_cnt * 57 = 569        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A1,1,A1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C113:
;*   0              LDDW    .D2T2   *B0++,B17:B16     ; |62|  ^ 
;*   1              NOP             4
;*   5              RSQRDP  .S2     B17:B16,B9:B8     ; |62|  ^ 
;*   6              NOP             1
;*   7              FMPYDP  .M2     B9:B8,B17:B16,B5:B4 ; |62|  ^ 
;*   8              FMPYDP  .M2     B27:B26,B9:B8,B7:B6 ; |62|  ^ 
;*   9              NOP             3
;*  12              FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |62|  ^ 
;*  13              NOP             3
;*  16              FSUBDP  .L2     B29:B28,B5:B4,B5:B4 ; |62|  ^ 
;*  17              NOP             2
;*  19              FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |62|  ^ 
;*  20              NOP             3
;*  23              FMPYDP  .M2     B23:B22,B5:B4,B9:B8 ; |62|  ^ 
;*  24              FMPYDP  .M2     B5:B4,B17:B16,B7:B6 ; |62|  ^ 
;*  25              NOP             3
;*  28              FMPYDP  .M2     B9:B8,B7:B6,B7:B6 ; |62|  ^ 
;*  29              NOP             3
;*  32              FSUBDP  .L2     B25:B24,B7:B6,B7:B6 ; |62|  ^ 
;*  33              NOP             2
;*  35              FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |62|  ^ 
;*  36              NOP             3
;*  39              FMPYDP  .M2     B9:B8,B17:B16,B5:B4 ; |62|  ^ 
;*  40              FMPYDP  .M2     B19:B18,B9:B8,B7:B6 ; |62|  ^ 
;*  41              NOP             3
;*  44              FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |62|  ^ 
;*  45              NOP             2
;*  47              ZERO    .L1     A5:A4             ; |62| 
;*  48              CMPLTDP .S1X    B17:B16,A5:A4,A0  ; |62| 
;*     ||           FSUBDP  .L2     B21:B20,B5:B4,B5:B4 ; |62|  ^ 
;*  49              NOP             1
;*  50      [ A1]   BDEC    .S1     $C$C113,A1        ; |115| 
;*  51      [!A0]   FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |62|  ^ 
;*  52              NOP             2
;*  54      [ A0]   DADD    .L2     0,B31:B30,B5:B4   ; |62| 
;*  55              STDW    .D2T2   B5:B4,*B1++       ; |62|  ^ 
;*  56              ; BRANCHCC OCCURS {$C$C113}       ; |115| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 57
           LDDW    .D2T2   *B0++,B17:B16     ; |62| <0,0>  ^ 
           NOP             4
           RSQRDP  .S2     B17:B16,B9:B8     ; |62| <0,5>  ^ 
           NOP             1
           FMPYDP  .M2     B9:B8,B17:B16,B5:B4 ; |62| <0,7>  ^ 
           FMPYDP  .M2     B27:B26,B9:B8,B7:B6 ; |62| <0,8>  ^ 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |62| <0,12>  ^ 
           NOP             3
           FSUBDP  .L2     B29:B28,B5:B4,B5:B4 ; |62| <0,16>  ^ 
           NOP             2
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |62| <0,19>  ^ 
           NOP             3
           FMPYDP  .M2     B23:B22,B5:B4,B9:B8 ; |62| <0,23>  ^ 
           FMPYDP  .M2     B5:B4,B17:B16,B7:B6 ; |62| <0,24>  ^ 
           NOP             3
           FMPYDP  .M2     B9:B8,B7:B6,B7:B6 ; |62| <0,28>  ^ 
           NOP             3
           FSUBDP  .L2     B25:B24,B7:B6,B7:B6 ; |62| <0,32>  ^ 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |62| <0,35>  ^ 
           NOP             3
           FMPYDP  .M2     B9:B8,B17:B16,B5:B4 ; |62| <0,39>  ^ 
           FMPYDP  .M2     B19:B18,B9:B8,B7:B6 ; |62| <0,40>  ^ 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |62| <0,44>  ^ 
           NOP             2
           ZERO    .L1     A5:A4             ; |62| <0,47> 

           CMPLTDP .S1X    B17:B16,A5:A4,A0  ; |62| <0,48> 
||         FSUBDP  .L2     B21:B20,B5:B4,B5:B4 ; |62| <0,48>  ^ 

           NOP             1
   [ A1]   BDEC    .S1     $C$L5,A1          ; |115| <0,50> 
   [!A0]   FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |62| <0,51>  ^ 
           NOP             2
   [ A0]   DADD    .L2     0,B31:B30,B5:B4   ; |62| <0,54> 
           STDW    .D2T2   B5:B4,*B1++       ; |62| <0,55>  ^ 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MV      .L2X    A15,B13
||         MV      .L1X    B30,A10
||         RINT                              ; interrupts on

           CALLP   .S2     rsqrtdp_v,B3
||         LDW     .D2T2   *+B13(16),B4      ; |118| 
||         MV      .L1     A12,A4            ; |118| 
||         MVK     .S1     0xa,A6            ; |118| 
||         MV      .D1X    B31,A11

$C$RL4:    ; CALL OCCURS {rsqrtdp_v} {0}     ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B13,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B12
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B12
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B12(4)       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .L1     0xa,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B12(8)       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           ADDAD   .D2     B10,1,B4
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B12(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *B4,B4            ; |69| 
||         LDW     .D1T1   *A15,A4           ; |69| 
||         MVK     .L1     0xa,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L1X    4,B12,A12
           LDW     .D1T1   *A12,A0           ; |72| 
           STW     .D2T1   A4,*+B12(16)      ; |69| 
           ADD     .L2     8,B12,B4
           STW     .D2T2   B4,*+SP(16)       ; |69| 
           NOP             1

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |122| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   ZERO    .L2     B4                ; |72| 
   [!A0]   MVKH    .S1     all_pass,A3
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
           CALL    .S1     print_test_results ; |122| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |122| 
||         STW     .D1T2   B4,*A3            ; |72| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |122| 

$C$RL9:    ; CALL OCCURS {print_test_results} {0}  ; |122| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S1     a_sc,A3
           MVKH    .S1     a_sc,A3
           MVK     .L2     0x7,B31

           ZERO    .L2     B9
||         MV      .S2X    A3,B4             ; |129| 
||         ZERO    .L1     A17:A16           ; |129| 
||         STW     .D2T2   B31,*+SP(12)      ; |130| 

           ZERO    .L1     A7
||         SET     .S2     B9,0x14,0x1d,B9
||         ZERO    .L2     B8                ; |134| 
||         STDW    .D2T1   A17:A16,*B4       ; |129| 

           ZERO    .L2     B17
||         MVKH    .S1     0xfff00000,A7
||         ZERO    .L1     A6                ; |134| 
||         STDW    .D2T2   B9:B8,*+B4(32)    ; |133| 

           ZERO    .L1     A9
||         SET     .S2     B17,0x14,0x1e,B17
||         ZERO    .L2     B16               ; |134| 
||         STDW    .D2T1   A7:A6,*+B4(24)    ; |132| 

           MVK     .L2     0xffffffff,B7     ; |135| 
||         MVKH    .S1     0x80000000,A9
||         ZERO    .L1     A8                ; |134| 
||         STDW    .D2T2   B17:B16,*+B4(16)  ; |131| 

           ZERO    .L1     A5
||         MV      .L2     B7,B6             ; |135| 
||         STDW    .D2T1   A9:A8,*+B4(8)     ; |130| 

           MVKH    .S1     0xbff00000,A5
||         ZERO    .L1     A4                ; |134| 
||         STDW    .D2T2   B7:B6,*+B4(48)    ; |135| 

           STDW    .D2T1   A5:A4,*+B4(40)    ; |134| 
||         MV      .L1     A3,A13            ; |130| 
||         CALL    .S1     rsqrt             ; |137| 

           LDDW    .D1T1   *A13,A5:A4        ; |137| 
           ZERO    .L1     A14               ; |134| 
           NOP             2
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL10,B3,0      ; |137| 
$C$RL10:   ; CALL OCCURS {rsqrt} {0}         ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A3            ; |137| 
           ZERO    .L1     A7:A6             ; |138| 
           NOP             3
           ADD     .L1     A14,A3,A3         ; |137| 
           STDW    .D1T1   A5:A4,*A3         ; |137| 
           LDDW    .D1T1   *A13,A5:A4        ; |138| 
           NOP             4
           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |138| 
           NOP             1
   [!A0]   B       .S1     $C$L9             ; |138| 
   [ A0]   CALL    .S1     rsqrtdp           ; |138| 
   [!A0]   CALL    .S1     rsqrt             ; |138| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L9}         ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL11,B3,0      ; |138| 
$C$RL11:   ; CALL OCCURS {rsqrtdp} {0}       ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L10            ; |138| 
||         MVKL    .S2     output+4,B13

           MVKH    .S2     output+4,B13
           LDW     .D2T2   *B13,B6           ; |138| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |138| 
           NOP             2
           ; BRANCH OCCURS {$C$L10}          ; |138| 
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL12,B3,1      ; |138| 
$C$RL12:   ; CALL OCCURS {rsqrt} {0}         ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           MVKL    .S2     output+4,B13
           MVKH    .S2     output+4,B13
           LDW     .D2T2   *B13,B6           ; |138| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |138| 
           NOP             2
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             1
           ADD     .L2X    A14,B6,B6         ; |138| 

           STDW    .D2T2   B5:B4,*B6         ; |138| 
||         CALL    .S1     rsqrtdp_c         ; |139| 

           LDDW    .D1T1   *A13,A5:A4        ; |139| 
           ADDKPC  .S2     $C$RL13,B3,3      ; |139| 
$C$RL13:   ; CALL OCCURS {rsqrtdp_c} {0}     ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 73
           LDW     .D2T2   *+B13(4),B4       ; |139| 
           ZERO    .L2     B5
           SET     .S2     B5,0x15,0x1d,B5
           ZERO    .L1     A31
           ZERO    .L2     B31
           ADD     .L2X    A14,B4,B4         ; |139| 
           STDW    .D2T1   A5:A4,*B4         ; |139| 
           LDDW    .D1T1   *A13++,A7:A6      ; |62| 
           ZERO    .L2     B4                ; |62| 
           ZERO    .L1     A30
           ZERO    .L2     B30
           MVK     .S1     8,A3
           RSQRDP  .S1     A7:A6,A5:A4       ; |62| 
           ZERO    .L2     B7
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |62| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |62| 
           ZERO    .L2     B6                ; |62| 
           SET     .S2     B7,0x13,0x1d,B7
           ADD     .L1X    B13,A3,A3
           LDW     .D1T1   *A3,A29           ; |140| 
           FMPYDP  .M1X    B5:B4,A9:A8,A17:A16 ; |62| 
           ZERO    .L1     A8                ; |62| 
           SET     .S1     A31,0x13,0x1d,A9
           ZERO    .L2     B4                ; |62| 
           FSUBDP  .L1     A9:A8,A17:A16,A9:A8 ; |62| 
           SET     .S2     B31,0x15,0x1d,B5
           ADD     .S1     A14,A29,A28       ; |140| 
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |62| 
           ADD     .L1     8,A14,A14         ; |136| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |62| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |62| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |62| 
           ZERO    .L1     A8                ; |62| 
           SET     .S1     A30,0x13,0x1d,A9
           NOP             2
           FSUBDP  .L1X    A9:A8,B5:B4,A9:A8 ; |62| 
           ZERO    .L2     B4                ; |62| 
           SET     .S2     B30,0x15,0x1d,B5
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |62| 
           NOP             3
           FMPYDP  .M1     A9:A8,A7:A6,A5:A4 ; |62| 
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |62| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |62| 
           NOP             3
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |62| 
           NOP             3

           FMPYDP  .M1X    A9:A8,B5:B4,A5:A4 ; |62| 
||         LDW     .D2T2   *+SP(12),B4       ; |65| 

           ZERO    .L1     A9:A8             ; |64| 
           CMPLTDP .S1     A7:A6,A9:A8,A0    ; |64| 
           NOP             1
   [ A0]   DADD    .L1     0,A11:A10,A5:A4   ; |65| 

           SUB     .L1X    B4,1,A0           ; |136| 
||         STDW    .D1T1   A5:A4,*A28        ; |140| 
||         SUB     .L2     B4,1,B4           ; |136| 

   [ A0]   B       .S1     $C$L8             ; |136| 
|| [ A0]   LDDW    .D1T1   *A13,A5:A4        ; |137| 
||         STW     .D2T2   B4,*+SP(12)       ; |140| 

   [ A0]   CALL    .S1     rsqrt             ; |137| 
   [!A0]   CALL    .S1     rsqrtdp_v         ; |142| 
   [!A0]   LDW     .D1T2   *+A3(4),B4        ; |142| 
   [!A0]   MVKL    .S1     a_sc,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L8}         ; |136| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S1     a_sc,A4

           MVK     .L1     0x7,A6            ; |142| 
||         ADDKPC  .S2     $C$RL14,B3,0      ; |142| 

$C$RL14:   ; CALL OCCURS {rsqrtdp_v} {0}     ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T1   *A15,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |66| 
||         MV      .L2     B12,B4            ; |67| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         STW     .D2T1   A3,*+B4(4)        ; |66| 
||         LDW     .D1T2   *+A15(8),B4       ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |67| 
||         MV      .L2     B12,B4            ; |68| 
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         STW     .D2T1   A3,*+B4(8)        ; |67| 
||         LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           MV      .L2     B12,B4            ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           ADD     .L1X    -4,B13,A3
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         LDW     .D1T2   *+A15(16),B4      ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL18:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MV      .L2X    A12,B13           ; |69| 
           LDW     .D2T2   *B13,B0           ; |72| 
           LDW     .D2T2   *+SP(16),B12
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 

   [!B0]   MVKL    .S1     all_pass,A3
|| [!B0]   B       .S2     $C$L11            ; |72| 
|| [!B0]   ZERO    .L1     A4                ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |146| 
|| [!B0]   MVKH    .S1     all_pass,A3
|| [ B0]   LDW     .D2T2   *B12,B0           ; |72| 

   [ B1]   ADD     .L2     4,B12,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
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
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |146| 
||         ADDKPC  .S2     $C$RL19,B3,0      ; |146| 

$C$RL19:   ; CALL OCCURS {print_test_results} {0}  ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     a_ext,A3
           MVKH    .S1     a_ext,A3

           ZERO    .L1     A5
||         MVK     .S2     0x777,B31

           MV      .L2X    A3,B4             ; |149| 
||         SET     .S1     A5,0x14,0x14,A5
||         ZERO    .L1     A4                ; |149| 
||         STW     .D2T2   B31,*+SP(12)      ; |149| 

           STDW    .D2T1   A5:A4,*B4         ; |149| 
||         MV      .L1     A3,A13            ; |149| 
||         CALL    .S1     rsqrt             ; |151| 

           LDDW    .D1T1   *A13,A5:A4        ; |151| 
           ZERO    .L1     A14               ; |149| 
           NOP             2
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL20,B3,0      ; |151| 
$C$RL20:   ; CALL OCCURS {rsqrt} {0}         ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A3            ; |151| 
           ZERO    .L1     A7:A6             ; |152| 
           NOP             3
           ADD     .L1     A14,A3,A3         ; |151| 
           STDW    .D1T1   A5:A4,*A3         ; |151| 
           LDDW    .D1T1   *A13,A5:A4        ; |152| 
           NOP             4
           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |152| 
           NOP             1
   [!A0]   B       .S1     $C$L13            ; |152| 
   [ A0]   CALL    .S1     rsqrtdp           ; |152| 
   [!A0]   CALL    .S1     rsqrt             ; |152| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L13}        ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL21,B3,0      ; |152| 
$C$RL21:   ; CALL OCCURS {rsqrtdp} {0}       ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S2     $C$L14            ; |152| 
||         MVKL    .S1     output+4,A15

           MVKH    .S1     output+4,A15
           LDW     .D1T1   *A15,A3           ; |152| 
           NOP             3
           ; BRANCH OCCURS {$C$L14}          ; |152| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 8
           ADDKPC  .S2     $C$RL22,B3,1      ; |152| 
$C$RL22:   ; CALL OCCURS {rsqrt} {0}         ; |152| 
           MVKL    .S1     output+4,A15
           MVKH    .S1     output+4,A15
           LDW     .D1T1   *A15,A3           ; |152| 
           NOP             3
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             1
           ADD     .L1     A14,A3,A3         ; |152| 

           STDW    .D1T1   A5:A4,*A3         ; |152| 
||         CALL    .S1     rsqrtdp_c         ; |153| 

           LDDW    .D1T1   *A13,A5:A4        ; |153| 
           ADDKPC  .S2     $C$RL23,B3,3      ; |153| 
$C$RL23:   ; CALL OCCURS {rsqrtdp_c} {0}     ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 84
           LDW     .D1T1   *+A15(4),A3       ; |153| 
           ZERO    .L2     B4                ; |62| 
           ZERO    .L2     B5
           SET     .S2     B5,0x15,0x1d,B5
           ZERO    .L1     A16               ; |62| 
           ADD     .L1     A14,A3,A3         ; |153| 
           STDW    .D1T1   A5:A4,*A3         ; |153| 
           LDDW    .D1T1   *A13,A9:A8        ; |62| 
           ZERO    .L1     A17
           SET     .S1     A17,0x13,0x1d,A17
           ZERO    .L2     B31
           ZERO    .L2     B30
           RSQRDP  .S1     A9:A8,A5:A4       ; |62| 
           ZERO    .L2     B6                ; |62| 
           FMPYDP  .M1     A5:A4,A9:A8,A7:A6 ; |62| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |62| 
           ADDAD   .D1     A15,1,A3
           LDW     .D1T1   *A3,A31           ; |154| 
           MV      .L2X    A17,B7            ; |62| 
           NOP             1
           FMPYDP  .M1X    B5:B4,A7:A6,A7:A6 ; |62| 
           ZERO    .L2     B4                ; |62| 
           SET     .S2     B31,0x15,0x1d,B5
           ADD     .L1     A14,A31,A30       ; |154| 
           FSUBDP  .L1     A17:A16,A7:A6,A7:A6 ; |62| 
           ADD     .L1     8,A14,A14         ; |150| 
           NOP             1
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |62| 
           NOP             3
           FMPYDP  .M1     A5:A4,A9:A8,A7:A6 ; |62| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |62| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |62| 
           MV      .L1     A16,A6            ; |62| 
           MV      .L1     A17,A7            ; |62| 
           NOP             2
           FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |62| 
           SET     .S2     B30,0x15,0x1d,B5
           MV      .L2X    A16,B4            ; |62| 
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |62| 
           NOP             3
           FMPYDP  .M1     A5:A4,A9:A8,A7:A6 ; |62| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |62| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |62| 
           ZERO    .L1     A7:A6             ; |64| 
           CMPLTDP .S1     A9:A8,A7:A6,A0    ; |64| 
           NOP             1
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |62| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |62| 
           MVKL    .S2     0xcccccccd,B4
           MVKL    .S2     0xc000cccc,B5
           MVKH    .S2     0xcccccccd,B4
   [ A0]   DADD    .L1     0,A11:A10,A5:A4   ; |65| 
           STDW    .D1T1   A5:A4,*A30        ; |154| 
           LDDW    .D1T1   *A13,A5:A4        ; |155| 
           MVKH    .S2     0xc000cccc,B5
           NOP             3

           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |155| 
||         LDW     .D2T2   *+SP(12),B4

           NOP             3
           STDW    .D1T1   A5:A4,*++A13      ; |155| 

           SUB     .L1X    B4,1,A0           ; |150| 
||         SUB     .L2     B4,1,B4           ; |150| 

   [ A0]   B       .S1     $C$L12            ; |150| 
|| [ A0]   LDDW    .D1T1   *A13,A5:A4        ; |151| 
||         STW     .D2T2   B4,*+SP(12)       ; |155| 

   [ A0]   CALL    .S1     rsqrt             ; |151| 
   [!A0]   CALL    .S1     rsqrtdp_v         ; |157| 
   [!A0]   LDW     .D1T2   *+A3(4),B4        ; |157| 
   [!A0]   MVKL    .S1     a_ext,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L12}        ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S1     a_ext,A4

           MVK     .S1     0x777,A6          ; |157| 
||         ADDKPC  .S2     $C$RL24,B3,0      ; |157| 

$C$RL24:   ; CALL OCCURS {rsqrtdp_v} {0}     ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           ADD     .L1     -4,A15,A13
||         MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T1   *A13,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A13(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A13,A4           ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         STW     .D2T1   A5,*+B4(4)        ; |66| 
||         LDW     .D1T2   *+A13(8),B4       ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A13,A4           ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         STW     .D2T1   A3,*+B4(8)        ; |67| 
||         LDW     .D1T2   *+A13(12),B4      ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A13,A3            ; |68| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         LDW     .D1T2   *+A13(16),B4      ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL28:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *B13,B0           ; |72| 
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           NOP             1

   [!B0]   MVKL    .S1     all_pass,A4
|| [!B0]   B       .S2     $C$L15            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [!B0]   ZERO    .L1     A3                ; |72| 

   [!B0]   CALL    .S2     print_test_results ; |161| 
|| [!B0]   MVKH    .S1     all_pass,A4
|| [ B0]   LDW     .D2T2   *B12,B0           ; |72| 

   [ B1]   ADD     .L2     4,B12,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L15}        ; |72| 
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
           CALL    .S1     print_test_results ; |161| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |161| 
||         ADDKPC  .S2     $C$RL29,B3,0      ; |161| 

$C$RL29:   ; CALL OCCURS {print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           ZERO    .L2     B5                ; |114| 

           ZERO    .L2     B4                ; |114| 
||         STW     .D2T2   B5,*+SP(24)       ; |114| 

           STW     .D2T2   B4,*+SP(28)       ; |114| 
           LDDW    .D2T2   *+SP(24),B5:B4    ; |114| 
           MVKL    .S1     cycle_counts+24,A3
           MVKH    .S1     cycle_counts+24,A3
           ZERO    .L2     B6                ; |114| 
           NOP             1

           STDW    .D1T2   B5:B4,*A3         ; |114| 
||         MVC     .S2     B6,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           CALL    .S1     gimme_random      ; |171| 
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         ZERO    .L2     B5
||         MVK     .S1     0x80,A31

           MVKH    .S2     0xbff00000,B5
||         ZERO    .L2     B4                ; |171| 
||         STW     .D2T1   A31,*+SP(12)      ; |117| 
||         MVKL    .S1     0x408f4800,A5
||         ZERO    .L1     A15
||         ZERO    .D1     A4                ; |171| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1

           ADDKPC  .S2     $C$RL30,B3,0      ; |171| 
||         MVKH    .S1     0x408f4800,A5

$C$RL30:   ; CALL OCCURS {gimme_random} {0}  ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 82
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |171| 
           NOP             4
           ADD     .L1     A15,A3,A3         ; |171| 

           STDW    .D1T1   A5:A4,*A3         ; |171| 
||         MVC     .S2     TSCL,B8           ; |122| 

           MVC     .S2     TSCH,B4           ; |122| 

           RSQRDP  .S1     A5:A4,A7:A6       ; |61| 
||         ZERO    .L2     B7
||         ZERO    .S2     B6                ; |61| 
||         ZERO    .L1     A17
||         ZERO    .D1     A16               ; |61| 
||         ZERO    .D2     B31

           SET     .S2     B7,0x15,0x1d,B7
||         ZERO    .L2     B16               ; |61| 
||         ZERO    .D2     B13

           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |61| 
||         SET     .S1     A17,0x13,0x1d,A17
||         SET     .S2     B13,0x15,0x1d,B13
||         ZERO    .L2     B12               ; |61| 
||         MV      .D2     B4,B9             ; |122| 

           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |61| 
||         MVKL    .S1     output+12,A3

           MV      .L2X    A17,B17           ; |61| 
||         MVKH    .S1     output+12,A3

           LDW     .D1T1   *A3,A3            ; |175| 
||         MVKL    .S1     t_start,A14

           MVKH    .S1     t_start,A14
           STDW    .D1T2   B9:B8,*A14

           FMPYDP  .M1X    B7:B6,A9:A8,A9:A8 ; |61| 
||         ZERO    .L2     B6                ; |61| 
||         SET     .S2     B31,0x15,0x1d,B7

           NOP             1
           ADD     .L1     A15,A3,A3         ; |175| 
           NOP             1
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |61| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |61| 
           NOP             3
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |61| 
           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |61| 
           NOP             3
           FMPYDP  .M2X    B7:B6,A9:A8,B7:B6 ; |61| 
           NOP             3
           FSUBDP  .L2     B17:B16,B7:B6,B7:B6 ; |61| 
           NOP             3
           FMPYDP  .M1X    A7:A6,B7:B6,A7:A6 ; |61| 
           NOP             3
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |62| 
           FMPYDP  .M2X    B13:B12,A7:A6,B7:B6 ; |62| 
           NOP             4

           FMPYDP  .M1X    B7:B6,A9:A8,A9:A8 ; |62| 
||         ZERO    .L2     B7:B6             ; |64| 

           CMPLTDP .S2X    A5:A4,B7:B6,B0    ; |64| 
           NOP             2
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |62| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |62| 
           NOP             3
   [ B0]   DADD    .L1     0,A11:A10,A7:A6   ; |65| 

           STDW    .D1T1   A7:A6,*A3         ; |175| 
||         MVC     .S2     TSCL,B18          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     t_offset,B12
||         MVKL    .S1     cycle_counts+24,A3
||         LDW     .D2T1   *+SP(12),A31      ; |128| 
||         MV      .L2     B4,B19            ; |128| 

           MVKH    .S2     t_offset,B12
||         MVKH    .S1     cycle_counts+24,A3

           LDDW    .D2T2   *B12,B7:B6        ; |130| 
||         LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         MV      .L1     A3,A13            ; |130| 
||         MVKL    .S2     t_stop,B30

           MVKH    .S2     t_stop,B30
           STDW    .D2T2   B19:B18,*B30      ; |128| 
           SUB     .L1     A31,1,A0          ; |169| 
           STW     .D2T1   A0,*+SP(12)       ; |130| 
           ADDU    .L2     B6,B8,B17:B16     ; |130| 

           ADD     .S2     B17,B7,B5         ; |130| 
||         SUBU    .L2     B18,B16,B7:B6     ; |130| 

           ADD     .L2     B5,B9,B4          ; |130| 
||         EXT     .S2     B7,24,24,B7       ; |130| 

           ADDU    .L2X    A4,B6,B5:B4       ; |130| 
||         SUB     .S2     B19,B4,B6         ; |130| 
|| [ A0]   B       .S1     $C$L16            ; |169| 

           ADD     .L2     B6,B7,B6          ; |130| 
|| [ A0]   CALL    .S1     gimme_random      ; |171| 

           ADD     .L1X    B5,A5,A3          ; |130| 
|| [ A0]   ZERO    .L2     B5

           ADD     .L1X    A3,B6,A5          ; |130| 
|| [ A0]   MVKH    .S2     0xbff00000,B5

           MV      .L1X    B4,A4             ; |130| 
||         ADD     .S1     8,A15,A15         ; |169| 
|| [ A0]   ZERO    .L2     B4                ; |171| 

           STDW    .D1T1   A5:A4,*A13        ; |130| 
|| [ A0]   MVKL    .S1     0x408f4800,A5
|| [ A0]   ZERO    .L1     A4                ; |171| 

           ; BRANCHCC OCCURS {$C$L16}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALLP   .S2     __c6xabi_fltllif,B3
||         LDDW    .D1T1   *A13,A5:A4        ; |135| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A15
           SET     .S1     A15,0x1a,0x1d,A15
           MPYSP   .M1     A15,A4,A3         ; |135| 
           ZERO    .L1     A10               ; |135| 
           MV      .L1X    B13,A11           ; |135| 
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL32:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           LDDW    .D2T2   *+SP(24),B5:B4
           MV      .L2X    A13,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B13
           MV      .L2X    A10,B31           ; |114| 

           STDW    .D2T2   B5:B4,*B13        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVKL    .S1     input,A13

           STDW    .D2T2   B5:B4,*B12        ; |117| 
||         MVKH    .S1     input,A13

           LDW     .D1T1   *A13,A3           ; |183| 
           MVK     .S2     0x80,B30
           STW     .D2T2   B30,*+SP(12)      ; |117| 
           NOP             2

           CALL    .S1     rsqrt             ; |183| 
||         ADD     .L1     A10,A3,A3         ; |183| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A3,A5:A4         ; |183| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |183| 
$C$RL33:   ; CALL OCCURS {rsqrt} {0}         ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |183| 
           NOP             4

           ADD     .L1X    A10,B4,A3         ; |183| 
||         LDW     .D2T2   *+SP(12),B4       ; |183| 

           ADD     .L1     8,A10,A10         ; |182| 
           STDW    .D1T1   A5:A4,*A3         ; |183| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |182| 
||         SUB     .L2     B4,1,B4           ; |182| 

   [ A0]   BNOP    .S1     $C$L17,4          ; |182| 
|| [ A0]   LDW     .D1T1   *A13,A3           ; |183| 
||         STW     .D2T2   B4,*+SP(12)       ; |183| 

   [ A0]   CALL    .S1     rsqrt             ; |183| 
||         ADD     .L1     A10,A3,A3         ; |183| 

           ; BRANCHCC OCCURS {$C$L17}        ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 

           MV      .L2     B4,B9             ; |128| 
           LDDW    .D2T2   *B13,B5:B4        ; |130| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A4          ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B7:B6       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B7,24,24,B16      ; |130| 
||         ADDU    .L2     B4,B6,B7:B6       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 

           ADD     .L2     B7,B5,B4          ; |130| 
||         ADD     .S2     B4,B16,B5         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     t_stop,B4

           MVKH    .S2     t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL34,B3,0      ; |130| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A15,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL35:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(24),B5:B4    ; |130| 
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B13(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A14        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B6,B4,B9:B8       ; |117| 

           EXT     .S2     B9,24,24,B6       ; |117| 
||         SUB     .L2     B7,B5,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MV      .S2     B8,B4             ; |117| 

           STDW    .D2T2   B5:B4,*B12        ; |117| 
           LDW     .D1T1   *A13,A3           ; |191| 
           MVK     .S2     0x80,B30
           STW     .D2T2   B30,*+SP(12)      ; |117| 
           NOP             2

           CALL    .S1     rsqrtdp           ; |191| 
||         ADD     .L1     A10,A3,A3         ; |191| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A3,A5:A4         ; |191| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |191| 
$C$RL36:   ; CALL OCCURS {rsqrtdp} {0}       ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *B11,B4           ; |191| 
           NOP             4

           ADD     .L1X    A10,B4,A3         ; |191| 
||         LDW     .D2T2   *+SP(12),B4       ; |191| 

           ADD     .L1     8,A10,A10         ; |190| 
           STDW    .D1T1   A5:A4,*A3         ; |191| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |190| 
||         SUB     .L2     B4,1,B4           ; |190| 

   [ A0]   BNOP    .S1     $C$L18,4          ; |190| 
|| [ A0]   LDW     .D1T1   *A13,A3           ; |191| 
||         STW     .D2T2   B4,*+SP(12)       ; |191| 

   [ A0]   CALL    .S1     rsqrtdp           ; |191| 
||         ADD     .L1     A10,A3,A3         ; |191| 

           ; BRANCHCC OCCURS {$C$L18}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MV      .L2     B12,B4            ; |128| 
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           MV      .L2     B5,B9             ; |128| 
           NOP             3
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 

           ADD     .L1X    A7,B7,A4          ; |130| 
||         LDDW    .D2T2   *+B13(8),B7:B6    ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B9,A3,B17         ; |130| 
           CALL    .S1     __c6xabi_fltllif  ; |130| 
           ADDU    .L2     B6,B4,B5:B4       ; |130| 

           MV      .L2     B4,B6             ; |130| 
||         ADD     .S2     B5,B7,B4          ; |130| 
||         ADD     .D2     B17,B16,B5        ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     t_stop,B4

           MVKH    .S2     t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL37,B3,0      ; |130| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A15,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(24),B5:B4
           ADDAD   .D2     B13,1,B11
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B11        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B13(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 

           STDW    .D1T2   B7:B6,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 
           STDW    .D2T2   B5:B4,*B12        ; |117| 
           LDW     .D1T1   *A13,A3           ; |199| 
           MVK     .S2     0x80,B29
           STW     .D2T2   B29,*+SP(12)      ; |117| 
           NOP             2

           CALL    .S1     rsqrtdp_c         ; |199| 
||         ADD     .L1     A10,A3,A3         ; |199| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A3,A5:A4         ; |199| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |199| 
$C$RL39:   ; CALL OCCURS {rsqrtdp_c} {0}     ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *B10,B4           ; |199| 
           NOP             4

           ADD     .L1X    A10,B4,A3         ; |199| 
||         LDW     .D2T2   *+SP(12),B4       ; |199| 

           ADD     .L1     8,A10,A10         ; |198| 
           STDW    .D1T1   A5:A4,*A3         ; |199| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |198| 
||         SUB     .L2     B4,1,B4           ; |198| 

   [ A0]   BNOP    .S1     $C$L19,4          ; |198| 
|| [ A0]   LDW     .D1T1   *A13,A3           ; |199| 
||         STW     .D2T2   B4,*+SP(12)       ; |199| 

   [ A0]   CALL    .S1     rsqrtdp_c         ; |199| 
||         ADD     .L1     A10,A3,A3         ; |199| 

           ; BRANCHCC OCCURS {$C$L19}        ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MV      .L2     B12,B4            ; |128| 
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           LDDW    .D2T2   *+B13(16),B17:B16 ; |130| 
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
||         ADDKPC  .S2     $C$RL40,B3,0      ; |130| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 105
           MPYSP   .M1     A15,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL41:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(24),B5:B4
           ADDAD   .D2     B11,1,B12
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B13(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A14        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     t_offset,A3

           MV      .S2X    A13,B9            ; |206| 
||         SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKH    .S1     t_offset,A3

           LDW     .D2T1   *B9,A4            ; |206| 
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           LDW     .D2T2   *+B10(8),B4       ; |206| 
||         MV      .L2X    A3,B11            ; |117| 
||         ADD     .S2     B5,B7,B7          ; |117| 

           CALLP   .S2     rsqrtdp_v,B3
||         STDW    .D2T2   B7:B6,*B11        ; |117| 
||         MVK     .S1     0x80,A6           ; |206| 

$C$RL42:   ; CALL OCCURS {rsqrtdp_v} {0}     ; |206| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A9:A8        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S1     16,A13
           ADD     .L1X    B12,A13,A13
           LDDW    .D1T1   *A13,A17:A16      ; |130| 
           MV      .L2     B4,B9             ; |128| 
           ADDU    .L1X    B6,A8,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A3          ; |130| 
           SUBU    .L1X    B8,A6,A5:A4       ; |130| 

           ADD     .L1     A3,A9,A3          ; |130| 
||         EXT     .S1     A5,24,24,A6       ; |130| 

           SUB     .S1X    B9,A3,A3          ; |130| 
||         ADDU    .L1     A16,A4,A5:A4      ; |130| 
||         MVKL    .S2     t_stop,B4

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A3,A6,A5          ; |130| 
||         MVKH    .S2     t_stop,B4

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           MPYSP   .M1     A15,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL44:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0xd9d7bdbb,B6

           MVKL    .S1     output,A10
||         MVKL    .S2     0x3ddb7cdf,B7

           MVKH    .S1     output,A10
||         STDW    .D1T1   A5:A4,*A13        ; |130| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T1   *A10,A4           ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A10(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A11
||         MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A11
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A11(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           MVKH    .S2     0x3ddb7cdf,B7
||         STW     .D1T1   A3,*+A11(8)       ; |67| 

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL47:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2X    A10,B4            ; |68| 
||         STW     .D1T1   A4,*+A11(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *+A10(16),B4      ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL48:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           LDW     .D1T1   *A12,A0           ; |72| 
||         LDW     .D2T2   *+SP(16),B4

           STW     .D1T1   A4,*+A11(16)      ; |69| 
           NOP             3

   [!A0]   BNOP    .S1     $C$L20,5          ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 
|| [ A0]   ADD     .L2     4,B4,B4

           ; BRANCHCC OCCURS {$C$L20}        ; |72| 
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
   [ A0]   B       .S1     $C$L21            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |212| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L21}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |212| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           ZERO    .L1     A3                ; |72| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |212| 
||         ADDKPC  .S2     $C$RL49,B3,0      ; |212| 

$C$RL49:   ; CALL OCCURS {print_test_results} {0}  ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |213| 

$C$RL50:   ; CALL OCCURS {printf} {0}        ; |213| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |213| 

$C$RL51:   ; CALL OCCURS {printf} {0}        ; |213| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |220| 

$C$RL52:   ; CALL OCCURS {print_profile_results} {0}  ; |220| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |223| 

$C$RL53:   ; CALL OCCURS {print_memory_results} {0}  ; |223| 
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
$C$SL1:	.string	"rsqrtDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	rsqrt
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	rsqrtdp
	.global	rsqrtdp_c
	.global	rsqrtdp_v
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
