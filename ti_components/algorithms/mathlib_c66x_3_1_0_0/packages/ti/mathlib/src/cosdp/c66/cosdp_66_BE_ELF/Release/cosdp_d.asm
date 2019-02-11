;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:26:22 2013                                *
;******************************************************************************
	.compiler_opts --abi=eabi --c64p_l1d_workaround=off --endian=big --hll_source=on --long_precision_bits=32 --mem_model:code=near --mem_model:const=data --mem_model:data=far --object_format=elf --silicon_version=6600 --symdebug:none 

;******************************************************************************
;* GLOBAL FILE PARAMETERS                                                     *
;*                                                                            *
;*   Architecture      : TMS320C66xx                                          *
;*   Optimization      : Enabled at level 3                                   *
;*   Optimizing for    : Speed                                                *
;*                       Based on options: -o3, no -ms                        *
;*   Endian            : Big                                                  *
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
	.word	04045b0adh,0a76d97b3h		; a[0] @ 0
	.word	0c04f7873h,05993f00ch		; a[1] @ 64
	.word	0c03ab1a4h,0f369ef88h		; a[2] @ 128
	.word	0c048c446h,0f65e968eh		; a[3] @ 192
	.word	04043f155h,0a7d24181h		; a[4] @ 256
	.word	0400dc01dh,0d4fd1cf7h		; a[5] @ 320
	.word	0c030ad3eh,055a624c2h		; a[6] @ 384
	.word	04053431bh,0357b0c10h		; a[7] @ 448
	.word	04051da23h,0c5012671h		; a[8] @ 512
	.word	0c03cff35h,0ceeee5fch		; a[9] @ 576

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\170522 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\170524 
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
;*   Local Frame Size  : 8 Args + 212 Auto + 56 Save = 276 byte               *
;******************************************************************************
main:
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
||         ADDK    .S2     -224,SP           ; |90| 

           CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |98| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     a,A10
           MVKL    .S1     output,A3
           MVKH    .S1     a,A10
           MVKH    .S1     output,A3

           MV      .L1     A10,A13
||         CALL    .S1     cos               ; |107| 
||         LDW     .D1T1   *A3,A12

           LDDW    .D1T1   *A13++,A5:A4      ; |107| 
           MVK     .L2     0xa,B4
           NOP             1
           MV      .L1X    B4,A11
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL1,B3,0       ; |107| 
$C$RL1:    ; CALL OCCURS {cos} {0}           ; |107| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A11,1,A0          ; |106| 
||         STDW    .D1T1   A5:A4,*A12++      ; |107| 
||         SUB     .S1     A11,1,A11         ; |106| 

   [ A0]   B       .S2     $C$L1             ; |106| 
|| [!A0]   MVKL    .S1     output,A3
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |107| 
|| [!A0]   ZERO    .L2     B10
|| [!A0]   MV      .L1     A10,A11

   [ A0]   CALL    .S1     cos               ; |107| 
   [!A0]   MVKH    .S1     output,A3
   [!A0]   MVK     .L1     0xa,A12
   [!A0]   ADD     .L2X    4,A3,B4
   [!A0]   STW     .D2T2   B4,*+SP(16)
           ; BRANCHCC OCCURS {$C$L1}         ; |106| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     cosdp             ; |110| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |110| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |110| 
$C$RL2:    ; CALL OCCURS {cosdp} {0}         ; |110| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(16),B4       ; |110| 
           SUB     .L1     A12,1,A0          ; |109| 
           SUB     .L1     A12,1,A12         ; |109| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |110| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |109| 

           ADD     .L2     B10,B4,B4         ; |110| 
||         ADD     .S2     8,B10,B10         ; |109| 

   [ A0]   CALL    .S1     cosdp             ; |110| 
||         STDW    .D2T1   A5:A4,*B4         ; |110| 

           ; BRANCHCC OCCURS {$C$L2}         ; |109| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(16),B4
           ZERO    .L2     B10
           MV      .L1     A10,A11
           MVK     .L1     0xa,A12
           NOP             1
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(20)
||         CALL    .S1     cosdp_c           ; |113| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |113| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |113| 
$C$RL3:    ; CALL OCCURS {cosdp_c} {0}       ; |113| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(20),B4       ; |113| 
           SUB     .L1     A12,1,A0          ; |112| 
           SUB     .L1     A12,1,A12         ; |112| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |113| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |112| 

           ADD     .L2     B10,B4,B4         ; |113| 
||         ADD     .S2     8,B10,B10         ; |112| 

   [ A0]   CALL    .S1     cosdp_c           ; |113| 
||         STDW    .D2T1   A5:A4,*B4         ; |113| 

           ; BRANCHCC OCCURS {$C$L3}         ; |112| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 31

           MVKL    .S2     0x111110b0,B4
||         LDW     .D2T2   *+SP(20),B5
||         MVKL    .S1     0x55555555,A13
||         ZERO    .L1     A27
||         ZERO    .D1     A24               ; |116| 
||         MVK     .L2     9,B0

           MVKH    .S2     0x111110b0,B4
||         MVKH    .S1     0x55555555,A13
||         ZERO    .L1     A20               ; |116| 

           STW     .D2T2   B4,*+SP(76)       ; |116| 
||         MVKL    .S2     0xbf2a01a0,B10
||         MVKL    .S1     0x3de6123c,A14

           MV      .L1X    B4,A18
||         MVKL    .S2     0x686ad430,B4
||         MVKL    .S1     0x3ec71de3,A15
||         MV      .L2X    A13,B18

           MVKH    .S2     0x686ad430,B4
||         MVKL    .S1     0x3f811111,A11

           STW     .D2T2   B4,*+SP(84)       ; |116| 
||         MVKL    .S2     0xbfc55555,B12
||         MVKL    .S1     0x3ce880ff,A12
||         ADD     .L2     4,B5,B11

           MV      .L1X    B4,A8
||         MVKL    .S2     0x54442d18,B4
||         MVKL    .S1     0xa524f063,A3
||         LDW     .D2T2   *B11,B22

           MVKH    .S2     0x54442d18,B4
||         MVKL    .S1     0x6993df95,A31

           MVKL    .S2     0xdc08499c,B27
||         MVKL    .S1     0x40092200,A30
||         STW     .D2T2   B4,*+SP(24)       ; |116| 

           MVKL    .S2     0xbd6ae420,B28
||         MVKL    .S1     0x3fd45f30,A29

           MVKL    .S2     0x1a013e1a,B31
||         MVKL    .S1     0x3ff921fb,A26

           MVKL    .S2     0x4b5dc0ab,B29
||         MVKL    .S1     0x6dc9c883,A28

           MVKL    .S2     0x4b9ee59e,B25
||         MVKH    .S1     0x3de6123c,A14

           MVKL    .S2     0xbee2aeef,B26
||         MVKH    .S1     0x3ec71de3,A15
||         MV      .L1     A14,A9

           MVKL    .S2     0xbe5ae645,B30
||         MVKH    .S1     0x3f811111,A11
||         MV      .L1     A15,A17

           MVKH    .S2     0xbf2a01a0,B10
||         MVKH    .S1     0x3ce880ff,A12
||         MV      .L1     A11,A19

           MVKH    .S2     0xbfc55555,B12
||         MVKH    .S1     0xa524f063,A3
||         MV      .L1     A12,A7
||         MV      .L2     B10,B17

           MVKH    .S2     0xdc08499c,B27
||         MVKH    .S1     0x6993df95,A31
||         STW     .D2T1   A3,*+SP(80)       ; |116| 
||         MV      .L1     A3,A16
||         MV      .D1     A10,A3
||         MV      .L2     B12,B19

           MVKH    .S2     0xbd6ae420,B28
||         MVKH    .S1     0x40092200,A30
||         STW     .D2T2   B27,*+SP(68)      ; |116| 
||         MV      .L1     A31,A6
||         MV      .L2     B27,B6

           MVKH    .S2     0x1a013e1a,B31
||         MVKH    .S1     0x3fd45f30,A29
||         STW     .D2T1   A30,*+SP(44)      ; |116| 
||         MV      .L1     A30,A21
||         MV      .D1X    B4,A30
||         MV      .L2     B28,B7

           MVKH    .S2     0x4b5dc0ab,B29
||         MVKH    .S1     0x3ff921fb,A26
||         STW     .D2T2   B28,*+SP(72)      ; |116| 
||         MV      .L1     A29,A23
||         MV      .L2     B31,B16

           MVKH    .S2     0x4b9ee59e,B25
||         MVKH    .S1     0x6dc9c883,A28
||         STW     .D2T2   B31,*+SP(56)      ; |116| 
||         MV      .L2     B29,B8

           MVKH    .S2     0xbee2aeef,B26
||         MVKH    .S1     0x41d00000,A27
||         STW     .D2T2   B29,*+SP(60)      ; |116| 
||         MV      .L1     A28,A22
||         MV      .L2     B25,B20

           MVKH    .S2     0xbe5ae645,B30
||         STW     .D2T2   B25,*+SP(48)      ; |116| 
||         MV      .L1     A27,A25
||         MV      .L2     B26,B21

           STW     .D2T1   A31,*+SP(88)      ; |116| 
||         MV      .L1     A26,A31
||         MV      .L2     B30,B9
||         DINT                              ; interrupts off

           STW     .D2T2   B26,*+SP(52)      ; |116| 
           STW     .D2T1   A29,*+SP(40)      ; |116| 
           STW     .D2T1   A26,*+SP(28)      ; |116| 
           STW     .D2T2   B30,*+SP(64)      ; |116| 
           STW     .D2T1   A28,*+SP(36)      ; |116| 
           STW     .D2T1   A27,*+SP(32)      ; |116| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/cosdp/cosdp_d.c
;*      Loop source line                 : 115
;*      Loop opening brace source line   : 115
;*      Loop closing brace source line   : 117
;*      Known Minimum Trip Count         : 10                    
;*      Known Maximum Trip Count         : 10                    
;*      Known Max Trip Count Factor      : 10
;*      Loop Carried Dependency Bound(^) : 86
;*      Unpartitioned Resource Bound     : 8
;*      Partitioned Resource Bound(*)    : 8
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        3     
;*      .S units                     5        5     
;*      .D units                     1        1     
;*      .M units                     8*       7     
;*      .X cross paths               5        6     
;*      .T address paths             1        1     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           8        4     (.L or .S unit)
;*      Addition ops (.LSD)          5        2     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             7        6     
;*      Bound(.L .S .D .LS .LSD)     7        5     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 86 Did not find schedule
;*         ii = 87 Did not find schedule
;*         ii = 89 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |   *  ****      **********    **|*     ****      *******         |
;*       1: |   *  ****      **********    **|*     ****      *******         |
;*       2: |   *  ****      **********    **|*     ****      *******         |
;*       3: |   *  ****      **********    **|*     ****      *******         |
;*       4: |   *  ****      **********    **|*     ****      *******         |
;*       5: |   *******      **********    **|*     ****      *******         |
;*       6: |   *  ****      **********    **|*     ****      *******         |
;*       7: |   *******      **********    **|*     ****      *******         |
;*       8: |   *  ****      **********    **|*     ****      *******         |
;*       9: |   *  ****      **********    **|*     ****      *******         |
;*      10: |   *******      **********    **|*     ****      *******         |
;*      11: |   *******      **********    **|*     ****      *******         |
;*      12: |*  *******      **********    **|*     ****      *******         |
;*      13: |*  *******      **********    **|*     ****      *******         |
;*      14: |*  *******      **********    **|*     ****      *******         |
;*      15: |*  *******      **********    **|*     ****      *******         |
;*      16: |   *******      **********    **|*     ****      *******         |
;*      17: |   *******      **********    **|*     ****      *******         |
;*      18: |   *******      **********    **|*     ****      *******         |
;*      19: |   *******      **********    **|*     ****      *******         |
;*      20: |   *******      ************  **|*     ****      *******         |
;*      21: |   *******      **********    **|*     ****      *******         |
;*      22: |   *******      **********    **|*     ****      *******         |
;*      23: |   *******      **********    **|*     ****      *******         |
;*      24: |  ********      **********    **|*     ****      *******         |
;*      25: |  ********      **********    **|*     ****      *******         |
;*      26: |  ********      **********    **|*     ****      *******         |
;*      27: |  ********      **********    **|*     ****      *******         |
;*      28: |  ********      **********    **|*     ****      *******         |
;*      29: |  ********      ************  **|*     ****      *******         |
;*      30: |  ********      ************  **|*     ****      *******         |
;*      31: |  ********      ************  **|*     ****      *******         |
;*      32: |  ********      **********    **|*     ****      *******         |
;*      33: |  ********      ************  **|*     ****      *******         |
;*      34: |  **  ****      **********    **|*     ****      *******         |
;*      35: |  **  ****      **********    **|*   ******      *******         |
;*      36: |  ********      **********    **|*   ******      *******         |
;*      37: |  **  ****      **********    **|*     ****      *******         |
;*      38: |  **  ****      **********    **|*     ****      *******         |
;*      39: |  ********      **********    **|*     ****      *******         |
;*      40: |  ********      **********    **|*     ****      *******         |
;*      41: |  ********      **********    **|*     ****      *******         |
;*      42: |  ********      **********    **|*     ****      *******         |
;*      43: |  ********      **********  ****|*     ****      *******         |
;*      44: |  ********      **********  ****|*     ****      *******         |
;*      45: |  ********      **********  ****|*     ****      *******         |
;*      46: |  ********      **********  ****|*     ****      *******         |
;*      47: |**********      **********  ****|*     ****      *******         |
;*      48: |**********      **********  ****|*     ****      *******         |
;*      49: |**********      **********  ****|*     ****      *******         |
;*      50: |**********      **********  ****|*     ****      *******         |
;*      51: |**********      ****************|*     ****      *******         |
;*      52: |**********      **********  ****|*   ******      *******         |
;*      53: |**********      **********  ****|*     ****      *******         |
;*      54: |**********      ****************|*     ****      *******         |
;*      55: |**********      **********  ****|*   ******      *******         |
;*      56: |**********      **********  ****|*     ****      *******         |
;*      57: |**********      **********  ****|*     ****      *******         |
;*      58: |**********      ****************|*     ****      *******         |
;*      59: |**********      **********  ****|*   ******      *******         |
;*      60: |**********      **********  ****|*     ****      *******         |
;*      61: |**********      ****************|*     ****      *******         |
;*      62: |**********      **********  ****|*   ******      *******         |
;*      63: |**********      **********  ****|*     ****      *******         |
;*      64: |**********      **********  ****|*     ****      *******         |
;*      65: |**********      ****************|*     ****      *******         |
;*      66: |**********      **********  ****|*   ******      *******         |
;*      67: |**********      **********  ****|*     ****      *******         |
;*      68: |**********      ****************|*     ****      *******         |
;*      69: |  ********      **********  ****|*   ******      *******         |
;*      70: |  ********      **********    **|*     ****      *******         |
;*      71: |  ********      **********    **|*     ****      *******         |
;*      72: |  ********      ************  **|*     ****      *******         |
;*      73: |  ********      ************  **|*   ******      *******         |
;*      74: |  ********      **********    **|*     ****      *******         |
;*      75: |  ********      **********    **|*     ****      *******         |
;*      76: |  ********      **********    **|*   ******      *******         |
;*      77: |  ********      **********    **|*     ****      *******         |
;*      78: |  ********      **********    **|*     ****      *******         |
;*      79: |*  *******      **********    **|*     ****      *******         |
;*      80: |*  *******      **********    **|*   ******      *******  *      |
;*      81: |*  *  ****      **********    **|*     ****      *******  *      |
;*      82: |*  *  ****      **********    **|*     ****      ******* **      |
;*      83: |   *  ****      **********    **|*   ******      ******* **      |
;*      84: |   *  ****      **********    **|*     ****      *******         |
;*      85: |   *  ****      **********    **|*     ****      *******         |
;*      86: |   *  ****      **********    **|*     ****      *******         |
;*      87: |   *  ****      **********    **|*   ******      *******         |
;*      88: |                                |                                |
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
;*      Total cycles (est.)         : -1 + min_trip_cnt * 89 = 889        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             B0,1,B0
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C91:
;*   0              LDDW    .D1T1   *A3++,A5:A4       ; |116|  ^ 
;*   1              NOP             4
;*   5              ABSDP   .S1     A5:A4,A5:A4       ; |116|  ^ 
;*   6              NOP             1
;*   7              FADDDP  .L1     A31:A30,A5:A4,A5:A4 ; |116|  ^ 
;*   8              NOP             2
;*  10              CMPGTDP .S1     A5:A4,A25:A24,A0  ; |116|  ^ 
;*  11              NOP             1
;*  12      [ A0]   MVKL    .S1     0x3ff921fb,A5     ;  ^ 
;*  13      [ A0]   MVKH    .S1     0x3ff921fb,A5     ;  ^ 
;*  14      [ A0]   MVKL    .S1     0x54442d18,A4     ;  ^ 
;*  15      [ A0]   MVKH    .S1     0x54442d18,A4     ;  ^ 
;*  16              FMPYDP  .M1     A23:A22,A5:A4,A27:A26 ; |116|  ^ 
;*  17              NOP             3
;*  20              DPINT   .L1     A27:A26,A2        ; |116|  ^ 
;*  21              NOP             3
;*  24              INTDP   .L1     A2,A27:A26        ; |116|  ^ 
;*  25              NOP             4
;*  29              FMPYDP  .M1     A21:A20,A27:A26,A27:A26 ; |116|  ^ 
;*  30              NOP             1
;*  31              FMPYDP  .M2X    B21:B20,A27:A26,B5:B4 ; |116| 
;*  32              NOP             1
;*  33              FSUBDP  .L1     A5:A4,A27:A26,A5:A4 ; |116|  ^ 
;*  34              NOP             2
;*  36              FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |116|  ^ 
;*  37              NOP             2
;*  39              FMPYDP  .M1     A5:A4,A5:A4,A29:A28 ; |116|  ^ 
;*  40              NOP             3
;*  43              FMPYDP  .M1     A29:A28,A29:A28,A1:A0 ; |116|  ^ 
;*  44              NOP             3
;*  47              FMPYDP  .M1     A7:A6,A1:A0,A27:A26 ; |116|  ^ 
;*  48              FMPYDP  .M2X    B7:B6,A1:A0,B5:B4 ; |116|  ^ 
;*  49              NOP             2
;*  51              FADDDP  .L1     A9:A8,A27:A26,A27:A26 ; |116|  ^ 
;*  52              FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |116|  ^ 
;*  53              NOP             1
;*  54              FMPYDP  .M1     A1:A0,A27:A26,A27:A26 ; |116|  ^ 
;*  55              FMPYDP  .M2X    A1:A0,B5:B4,B5:B4 ; |116|  ^ 
;*  56              NOP             2
;*  58              FADDDP  .L1     A17:A16,A27:A26,A27:A26 ; |116|  ^ 
;*  59              FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |116|  ^ 
;*  60              NOP             1
;*  61              FMPYDP  .M1     A1:A0,A27:A26,A27:A26 ; |116|  ^ 
;*  62              FMPYDP  .M2X    A1:A0,B5:B4,B5:B4 ; |116|  ^ 
;*  63              NOP             2
;*  65              FADDDP  .L1     A19:A18,A27:A26,A27:A26 ; |116|  ^ 
;*  66              FADDDP  .L2     B19:B18,B5:B4,B5:B4 ; |116|  ^ 
;*  67              NOP             1
;*  68              FMPYDP  .M1     A1:A0,A27:A26,A27:A26 ; |116|  ^ 
;*  69              FMPYDP  .M2X    A29:A28,B5:B4,B5:B4 ; |116|  ^ 
;*  70              NOP             3
;*  73              FADDDP  .L2X    B5:B4,A27:A26,B5:B4 ; |116|  ^ 
;*  74              NOP             2
;*  76              FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |116|  ^ 
;*  77              NOP             1
;*  78              AND     .L1     1,A2,A0           ; |116| 
;*  79      [!A0]   ZERO    .L2     B25
;*  80              FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |116|  ^ 
;*     ||   [ A0]   ZERO    .D2     B25
;*     ||   [!A0]   SET     .S2     B25,0x14,0x1d,B25
;*  81      [ A0]   MVKH    .S2     0xbff00000,B25
;*     ||   [!A0]   ZERO    .L2     B24               ; |116| 
;*  82      [ A0]   ZERO    .D2     B24               ; |116| 
;*     ||   [ B0]   BDEC    .S2     $C$C91,B0         ; |115| 
;*  83              FMPYDP  .M2     B25:B24,B5:B4,B5:B4 ; |116|  ^ 
;*  84              NOP             3
;*  87              STDW    .D2T2   B5:B4,*B22++      ; |116|  ^ 
;*  88              ; BRANCHCC OCCURS {$C$C91}        ; |115| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 89
           LDDW    .D1T1   *A3++,A5:A4       ; |116| <0,0>  ^ 
           NOP             4
           ABSDP   .S1     A5:A4,A5:A4       ; |116| <0,5>  ^ 
           NOP             1
           FADDDP  .L1     A31:A30,A5:A4,A5:A4 ; |116| <0,7>  ^ 
           NOP             2
           CMPGTDP .S1     A5:A4,A25:A24,A0  ; |116| <0,10>  ^ 
           NOP             1
   [ A0]   MVKL    .S1     0x3ff921fb,A5     ; <0,12>  ^ 
   [ A0]   MVKH    .S1     0x3ff921fb,A5     ; <0,13>  ^ 
   [ A0]   MVKL    .S1     0x54442d18,A4     ; <0,14>  ^ 
   [ A0]   MVKH    .S1     0x54442d18,A4     ; <0,15>  ^ 
           FMPYDP  .M1     A23:A22,A5:A4,A27:A26 ; |116| <0,16>  ^ 
           NOP             3
           DPINT   .L1     A27:A26,A2        ; |116| <0,20>  ^ 
           NOP             3
           INTDP   .L1     A2,A27:A26        ; |116| <0,24>  ^ 
           NOP             4
           FMPYDP  .M1     A21:A20,A27:A26,A27:A26 ; |116| <0,29>  ^ 
           NOP             1
           FMPYDP  .M2X    B21:B20,A27:A26,B5:B4 ; |116| <0,31> 
           NOP             1
           FSUBDP  .L1     A5:A4,A27:A26,A5:A4 ; |116| <0,33>  ^ 
           NOP             2
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |116| <0,36>  ^ 
           NOP             2
           FMPYDP  .M1     A5:A4,A5:A4,A29:A28 ; |116| <0,39>  ^ 
           NOP             3
           FMPYDP  .M1     A29:A28,A29:A28,A1:A0 ; |116| <0,43>  ^ 
           NOP             3
           FMPYDP  .M1     A7:A6,A1:A0,A27:A26 ; |116| <0,47>  ^ 
           FMPYDP  .M2X    B7:B6,A1:A0,B5:B4 ; |116| <0,48>  ^ 
           NOP             2
           FADDDP  .L1     A9:A8,A27:A26,A27:A26 ; |116| <0,51>  ^ 
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |116| <0,52>  ^ 
           NOP             1
           FMPYDP  .M1     A1:A0,A27:A26,A27:A26 ; |116| <0,54>  ^ 
           FMPYDP  .M2X    A1:A0,B5:B4,B5:B4 ; |116| <0,55>  ^ 
           NOP             2
           FADDDP  .L1     A17:A16,A27:A26,A27:A26 ; |116| <0,58>  ^ 
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |116| <0,59>  ^ 
           NOP             1
           FMPYDP  .M1     A1:A0,A27:A26,A27:A26 ; |116| <0,61>  ^ 
           FMPYDP  .M2X    A1:A0,B5:B4,B5:B4 ; |116| <0,62>  ^ 
           NOP             2
           FADDDP  .L1     A19:A18,A27:A26,A27:A26 ; |116| <0,65>  ^ 
           FADDDP  .L2     B19:B18,B5:B4,B5:B4 ; |116| <0,66>  ^ 
           NOP             1
           FMPYDP  .M1     A1:A0,A27:A26,A27:A26 ; |116| <0,68>  ^ 
           FMPYDP  .M2X    A29:A28,B5:B4,B5:B4 ; |116| <0,69>  ^ 
           NOP             3
           FADDDP  .L2X    B5:B4,A27:A26,B5:B4 ; |116| <0,73>  ^ 
           NOP             2
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |116| <0,76>  ^ 
           NOP             1
           AND     .L1     1,A2,A0           ; |116| <0,78> 
   [!A0]   ZERO    .L2     B25               ; <0,79> 

   [ A0]   ZERO    .D2     B25               ; <0,80> 
|| [!A0]   SET     .S2     B25,0x14,0x1d,B25 ; <0,80> 
||         FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |116| <0,80>  ^ 

   [!A0]   ZERO    .L2     B24               ; |116| <0,81> 
|| [ A0]   MVKH    .S2     0xbff00000,B25    ; <0,81> 

   [ A0]   ZERO    .D2     B24               ; |116| <0,82> 
|| [ B0]   BDEC    .S2     $C$L5,B0          ; |115| <0,82> 

           FMPYDP  .M2     B25:B24,B5:B4,B5:B4 ; |116| <0,83>  ^ 
           NOP             3
           STDW    .D2T2   B5:B4,*B22++      ; |116| <0,87>  ^ 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           STW     .D2T1   A6,*+SP(88)
           STW     .D2T2   B16,*+SP(56)
           STW     .D2T1   A31,*+SP(28)
           STW     .D2T1   A30,*+SP(24)
           STW     .D2T1   A25,*+SP(32)
           STW     .D2T1   A23,*+SP(40)
           STW     .D2T1   A22,*+SP(36)
           STW     .D2T1   A21,*+SP(44)
           STW     .D2T1   A18,*+SP(76)
           STW     .D2T1   A16,*+SP(80)
           STW     .D2T2   B9,*+SP(64)
           STW     .D2T2   B8,*+SP(60)
           STW     .D2T2   B7,*+SP(72)
           STW     .D2T2   B6,*+SP(68)

           MVKL    .S2     output,B13
||         STW     .D2T1   A8,*+SP(84)

           MV      .L1     A7,A12
||         STW     .D2T2   B20,*+SP(48)
||         RINT                              ; interrupts on

           MVKH    .S2     output,B13
||         MV      .L1     A9,A14
||         MV      .S1     A17,A15
||         MV      .L2     B17,B10
||         STW     .D2T2   B21,*+SP(52)
||         MV      .D1     A10,A4            ; |118| 

           CALLP   .S2     cosdp_v,B3
||         LDW     .D2T2   *+B13(16),B4      ; |118| 
||         MVK     .L1     0xa,A6            ; |118| 
||         MV      .S1     A19,A11
||         MV      .D1X    B18,A13
||         MV      .L2     B19,B12

$C$RL4:    ; CALL OCCURS {cosdp_v} {0}       ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |66| 
||         MVK     .L1     0xa,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .L1     0xa,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1X    B13,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .L1     0xa,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B4

           ADD     .L1X    4,B11,A5
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           MV      .L2     B13,B31           ; |69| 
||         STW     .D2T1   A5,*+SP(92)
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A5,B4            ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0xa,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     fcn_pass,B5

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     fcn_pass,B5

           ADD     .L1     4,A3,A3
           LDW     .D1T1   *A3,A0            ; |72| 
           ADD     .L2     8,B5,B4
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           STW     .D2T2   B4,*+SP(100)      ; |69| 
           STW     .D2T1   A3,*+SP(96)

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
;          EXCLUSIVE CPU CYCLES: 55
           LDW     .D2T1   *+SP(28),A9       ; |74| 
           LDW     .D2T1   *+SP(56),A3       ; |86| 
           LDW     .D2T1   *+SP(64),A31      ; |86| 
           LDW     .D2T1   *+SP(60),A30      ; |86| 
           LDW     .D2T1   *+SP(72),A29      ; |86| 
           LDW     .D2T1   *+SP(68),A28      ; |86| 
           LDW     .D2T1   *+SP(76),A27      ; |86| 
           LDW     .D2T1   *+SP(80),A26      ; |86| 
           LDW     .D2T1   *+SP(84),A25      ; |86| 
           LDW     .D2T1   *+SP(88),A24      ; |86| 
           LDW     .D2T1   *+SP(44),A23      ; |86| 
           LDW     .D2T1   *+SP(52),A22      ; |86| 
           LDW     .D2T1   *+SP(48),A21      ; |74| 
           LDW     .D2T1   *+SP(40),A20      ; |74| 
           LDW     .D2T1   *+SP(36),A19      ; |74| 
           LDW     .D2T1   *+SP(32),A18      ; |74| 
           LDW     .D2T1   *+SP(24),A2
           STW     .D2T1   A12,*+SP(216)     ; |86| 
           STW     .D2T1   A14,*+SP(208)     ; |86| 
           STW     .D2T1   A15,*+SP(200)     ; |86| 
           STW     .D2T1   A11,*+SP(192)     ; |86| 
           STW     .D2T2   B10,*+SP(168)     ; |86| 
           STW     .D2T1   A13,*+SP(164)     ; |86| 
           STW     .D2T2   B12,*+SP(160)     ; |86| 

           STW     .D2T1   A9,*+SP(120)
||         ZERO    .L1     A4                ; |134| 

           MVK     .L2     0x7,B31
||         STW     .D2T1   A4,*+SP(148)      ; |130| 

           ZERO    .L1     A1                ; |134| 
||         STW     .D2T2   B31,*+SP(12)      ; |130| 

           STW     .D2T1   A1,*+SP(132)      ; |130| 
           STW     .D2T1   A3,*+SP(172)      ; |86| 
           STW     .D2T1   A31,*+SP(176)     ; |86| 
           STW     .D2T1   A30,*+SP(180)     ; |86| 
           STW     .D2T1   A29,*+SP(184)     ; |86| 
           STW     .D2T1   A28,*+SP(188)     ; |86| 
           STW     .D2T1   A27,*+SP(196)     ; |86| 
           STW     .D2T1   A26,*+SP(204)     ; |86| 
           STW     .D2T1   A25,*+SP(212)     ; |86| 
           STW     .D2T1   A24,*+SP(220)     ; |86| 
           STW     .D2T1   A23,*+SP(144)     ; |86| 
           STW     .D2T1   A22,*+SP(152)     ; |74| 
           STW     .D2T1   A21,*+SP(156)     ; |74| 
           STW     .D2T1   A20,*+SP(136)     ; |74| 
           STW     .D2T1   A19,*+SP(140)     ; |74| 

           MVKL    .S2     a_sc,B6
||         MVK     .L2     0xffffffff,B5     ; |135| 
||         STW     .D2T1   A18,*+SP(128)     ; |74| 

           MVKH    .S2     a_sc,B6
||         MV      .L2     B5,B4             ; |135| 
||         ZERO    .L1     A5
||         STW     .D2T1   A2,*+SP(124)

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

           MV      .L1X    B6,A10            ; |129| 
||         ZERO    .L2     B6                ; |134| 
||         SET     .S2     B7,0x14,0x1d,B7
||         STDW    .D2T1   A9:A8,*+B4(8)     ; |130| 

           STDW    .D2T2   B7:B6,*+B4(32)    ; |133| 
||         CALL    .S1     cos               ; |137| 

           LDDW    .D1T1   *A10,A5:A4        ; |137| 
           ZERO    .L2     B13               ; |134| 
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
$C$RL10:   ; CALL OCCURS {cos} {0}           ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A3            ; |137| 
           NOP             4
           ADD     .L2X    B13,A3,B4         ; |137| 
           STDW    .D2T1   A5:A4,*B4         ; |137| 

           CALLP   .S2     cosdp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |138| 

$C$RL11:   ; CALL OCCURS {cosdp} {0}         ; |138| 
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *+A3(4),A3        ; |138| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |138| 
           STDW    .D1T1   A5:A4,*A3         ; |138| 

           CALLP   .S2     cosdp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |139| 

$C$RL12:   ; CALL OCCURS {cosdp_c} {0}       ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 112
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *+A3(8),A3        ; |139| 
           LDDW    .D2T2   *+SP(152),B5:B4
           LDW     .D2T2   *B11,B8           ; |140| 
           NOP             2
           ADD     .L1X    B13,A3,A3         ; |139| 
           STDW    .D1T1   A5:A4,*A3         ; |139| 
           LDDW    .D1T1   *A10++,A5:A4      ; |72| 
           ADD     .L2     B13,B8,B31        ; |140| 
           ADD     .L2     8,B13,B13         ; |136| 
           NOP             2

           ABSDP   .S1     A5:A4,A7:A6       ; |72| 
||         LDDW    .D2T1   *+SP(120),A5:A4

           NOP             4

           FADDDP  .L1     A5:A4,A7:A6,A7:A6 ; |72| 
||         LDDW    .D2T1   *+SP(128),A5:A4

           NOP             4
           CMPGTDP .S1     A7:A6,A5:A4,A0    ; |74| 
           LDDW    .D2T1   *+SP(136),A5:A4
   [ A0]   MVKL    .S1     0x3ff921fb,A7
   [ A0]   MVKL    .S1     0x54442d18,A6
   [ A0]   MVKH    .S1     0x3ff921fb,A7
   [ A0]   MVKH    .S1     0x54442d18,A6
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |80| 
           NOP             3
           DPINT   .L1     A5:A4,A3          ; |80| 
           LDDW    .D2T1   *+SP(144),A5:A4
           NOP             2
           INTDP   .L1     A3,A9:A8          ; |80| 
           AND     .L1     1,A3,A0           ; |83| 
           NOP             3
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |86| 
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |86| 
           NOP             2
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |86| 
           NOP             2
           FSUBDP  .L1X    A5:A4,B5:B4,A9:A8 ; |86| 
           LDDW    .D2T1   *+SP(216),A5:A4
           LDDW    .D2T2   *+SP(184),B5:B4   ; |140| 
           FMPYDP  .M1     A9:A8,A9:A8,A17:A16 ; |140| 
           NOP             3
           FMPYDP  .M1     A17:A16,A17:A16,A7:A6 ; |140| 
           NOP             3

           FMPYDP  .M1     A5:A4,A7:A6,A19:A18 ; |140| 
||         LDDW    .D2T1   *+SP(208),A5:A4

           FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |140| 
           LDDW    .D2T2   *+SP(176),B5:B4   ; |140| 
           NOP             2
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |140| 
           NOP             1
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |140| 

           FMPYDP  .M1     A7:A6,A5:A4,A19:A18 ; |140| 
||         LDDW    .D2T1   *+SP(200),A5:A4

           LDDW    .D2T2   *+SP(168),B7:B6   ; |140| 
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |140| 
           NOP             2
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |140| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |140| 
           LDDW    .D2T2   *+SP(160),B7:B6   ; |140| 

           FMPYDP  .M1     A7:A6,A5:A4,A19:A18 ; |140| 
||         LDDW    .D2T1   *+SP(192),A5:A4

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
||         LDW     .D2T2   *+SP(12),B7       ; |140| 

           NOP             3
           STDW    .D2T2   B5:B4,*B31        ; |140| 

           SUB     .L1X    B7,1,A0           ; |136| 
||         SUB     .L2     B7,1,B4           ; |136| 

   [ A0]   B       .S1     $C$L8             ; |136| 
|| [!A0]   MVKL    .S2     output,B13
|| [ A0]   LDDW    .D1T1   *A10,A5:A4        ; |137| 
||         STW     .D2T2   B4,*+SP(12)       ; |140| 

   [ A0]   CALL    .S1     cos               ; |137| 
|| [!A0]   MVKH    .S2     output,B13

   [!A0]   CALL    .S1     cosdp_v           ; |142| 
   [!A0]   LDW     .D2T2   *+B13(16),B4      ; |142| 
   [!A0]   MVKL    .S1     a_sc,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L8}         ; |136| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S1     a_sc,A4

           MVK     .L1     0x7,A6            ; |142| 
||         ADDKPC  .S2     $C$RL13,B3,0      ; |142| 

$C$RL13:   ; CALL OCCURS {cosdp_v} {0}       ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B13,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1X    B13,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4

           LDW     .D2T1   *+SP(92),A3       ; |68| 
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B4

           MV      .L1X    B13,A31           ; |69| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T1   *A31,A4           ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         STW     .D2T1   A3,*+SP(104)      ; |68| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(96),A3       ; |69| 
           MVKL    .S2     fcn_pass,B31
           MVKH    .S2     fcn_pass,B31
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           NOP             1

           MV      .L2X    A3,B4             ; |69| 
||         STW     .D2T1   A3,*+SP(108)      ; |69| 

           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T1   *+SP(100),A3
           NOP             3

   [!B0]   B       .S2     $C$L9             ; |72| 
|| [!B0]   MVKL    .S1     all_pass,A4
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |146| 
|| [ B0]   MV      .L2X    A3,B4
|| [!B0]   MVKH    .S1     all_pass,A4
||         STW     .D2T1   A3,*+SP(112)      ; |72| 
|| [!B0]   ZERO    .L1     A3                ; |72| 

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             2
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           CMPEQ   .L1     A4,0,A3           ; |72| 
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           NOP             2
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   ZERO    .L1     A3                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |146| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x3,A4            ; |146| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |146| 

$C$RL18:   ; CALL OCCURS {print_test_results} {0}  ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           STW     .D2T1   A13,*+SP(140)     ; |86| 
           STW     .D2T1   A11,*+SP(168)     ; |86| 
           LDW     .D2T1   *+SP(24),A19
           LDW     .D2T1   *+SP(28),A20      ; |74| 
           LDW     .D2T1   *+SP(36),A21      ; |74| 
           LDW     .D2T1   *+SP(40),A22      ; |74| 
           LDW     .D2T1   *+SP(88),A23      ; |86| 
           LDW     .D2T1   *+SP(84),A24      ; |86| 
           LDW     .D2T1   *+SP(80),A25      ; |86| 
           LDW     .D2T1   *+SP(76),A26      ; |86| 
           LDW     .D2T1   *+SP(68),A27      ; |86| 
           LDW     .D2T1   *+SP(72),A28      ; |86| 
           LDW     .D2T1   *+SP(60),A29      ; |86| 
           LDW     .D2T1   *+SP(64),A30      ; |86| 
           LDW     .D2T1   *+SP(56),A31      ; |86| 
           STW     .D2T1   A14,*+SP(184)     ; |86| 
           STW     .D2T2   B12,*+SP(136)     ; |86| 
           STW     .D2T1   A15,*+SP(176)     ; |86| 
           STW     .D2T1   A12,*+SP(192)     ; |86| 

           STW     .D2T2   B10,*+SP(144)     ; |86| 
||         ZERO    .L1     A17               ; |149| 

           STW     .D2T1   A17,*+SP(204)     ; |149| 
||         MVK     .S1     0x6f4,A18

           STW     .D2T1   A18,*+SP(12)
           LDW     .D2T2   *+SP(52),B13      ; |86| 

           LDW     .D2T1   *+SP(44),A13      ; |86| 
||         ZERO    .L1     A3

           LDW     .D2T1   *+SP(32),A11      ; |74| 
||         MVKH    .S1     0xbff80000,A3

           STW     .D2T1   A3,*+SP(200)      ; |155| 
           STW     .D2T1   A19,*+SP(124)
           STW     .D2T1   A20,*+SP(120)
           STW     .D2T1   A21,*+SP(132)     ; |74| 
           STW     .D2T1   A22,*+SP(128)     ; |74| 
           STW     .D2T1   A23,*+SP(196)     ; |86| 
           STW     .D2T1   A24,*+SP(188)     ; |86| 
           STW     .D2T1   A25,*+SP(180)     ; |86| 
           STW     .D2T1   A26,*+SP(172)     ; |86| 
           STW     .D2T1   A27,*+SP(164)     ; |86| 
           STW     .D2T1   A28,*+SP(160)     ; |86| 

           STW     .D2T1   A29,*+SP(156)     ; |86| 
||         MVKL    .S2     a_ext,B4

           STW     .D2T1   A30,*+SP(152)     ; |86| 
||         MVKH    .S2     a_ext,B4
||         ZERO    .L1     A5

           STW     .D2T1   A31,*+SP(148)     ; |86| 
||         SET     .S1     A5,0x14,0x14,A5
||         ZERO    .L1     A4                ; |149| 

           CALL    .S1     cos               ; |151| 
||         STDW    .D2T1   A5:A4,*B4         ; |149| 
||         MV      .L1X    B4,A14            ; |149| 

           LDDW    .D1T1   *A14,A5:A4        ; |151| 
||         LDW     .D2T2   *+SP(48),B12      ; |74| 

           ZERO    .L2     B10               ; |149| 
||         ZERO    .L1     A12               ; |149| 
||         ZERO    .S1     A10               ; |149| 

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
$C$RL19:   ; CALL OCCURS {cos} {0}           ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |151| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |151| 
           STDW    .D2T1   A5:A4,*B4         ; |151| 

           CALLP   .S2     cosdp,B3
||         LDDW    .D1T1   *A14,A5:A4        ; |152| 

$C$RL20:   ; CALL OCCURS {cosdp} {0}         ; |152| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |152| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |152| 
           STDW    .D2T1   A5:A4,*B4         ; |152| 

           CALLP   .S2     cosdp_c,B3
||         LDDW    .D1T1   *A14,A5:A4        ; |153| 

$C$RL21:   ; CALL OCCURS {cosdp_c} {0}       ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 112
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |153| 
           LDDW    .D2T1   *+SP(120),A7:A6
           LDDW    .D2T1   *+SP(184),A19:A18
           LDW     .D2T2   *B11,B8           ; |154| 
           LDW     .D2T1   *+SP(12),A31
           ADD     .L2     B10,B4,B4         ; |153| 
           STDW    .D2T1   A5:A4,*B4         ; |153| 
           LDDW    .D1T1   *A14,A5:A4        ; |72| 
           ADD     .L2     B10,B8,B31        ; |154| 
           ADD     .L2     8,B10,B10         ; |150| 
           SUB     .L1     A31,1,A2          ; |150| 
   [!A2]   MVKL    .S2     output,B10
           ABSDP   .S1     A5:A4,A5:A4       ; |72| 
   [!A2]   MVKH    .S2     output,B10
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |72| 
           LDDW    .D2T1   *+SP(128),A7:A6
           NOP             1
           CMPGTDP .S1     A5:A4,A11:A10,A0  ; |74| 
           NOP             1
   [ A0]   MVKL    .S1     0x3ff921fb,A5
   [ A0]   MVKL    .S1     0x54442d18,A4
   [ A0]   MVKH    .S1     0x3ff921fb,A5
   [ A0]   MVKH    .S1     0x54442d18,A4
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |80| 
           NOP             3
           DPINT   .L1     A7:A6,A3          ; |80| 
           NOP             3
           INTDP   .L1     A3,A7:A6          ; |80| 
           AND     .L1     1,A3,A0           ; |83| 
           NOP             3
           FMPYDP  .M1     A13:A12,A7:A6,A9:A8 ; |86| 
           FMPYDP  .M2X    B13:B12,A7:A6,B5:B4 ; |86| 
           NOP             2
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |86| 
           NOP             2
           FSUBDP  .L1X    A5:A4,B5:B4,A9:A8 ; |86| 
           LDDW    .D2T2   *+SP(160),B5:B4   ; |154| 
           LDDW    .D2T1   *+SP(192),A5:A4
           FMPYDP  .M1     A9:A8,A9:A8,A17:A16 ; |154| 
           NOP             3
           FMPYDP  .M1     A17:A16,A17:A16,A7:A6 ; |154| 
           NOP             3
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |154| 

           FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |154| 
||         LDDW    .D2T2   *+SP(152),B5:B4   ; |154| 

           NOP             2
           FADDDP  .L1     A19:A18,A5:A4,A5:A4 ; |154| 
           NOP             1
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |154| 

           FMPYDP  .M1     A7:A6,A5:A4,A19:A18 ; |154| 
||         LDDW    .D2T1   *+SP(176),A5:A4

           NOP             1

           FMPYDP  .M2X    A7:A6,B5:B4,B7:B6 ; |154| 
||         LDDW    .D2T2   *+SP(144),B5:B4   ; |154| 

           NOP             2
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |154| 
           NOP             1
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |154| 
           FMPYDP  .M1     A7:A6,A5:A4,A19:A18 ; |154| 
           LDDW    .D2T1   *+SP(168),A5:A4

           FMPYDP  .M2X    A7:A6,B5:B4,B7:B6 ; |154| 
||         LDDW    .D2T2   *+SP(136),B5:B4   ; |154| 

           NOP             3
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |154| 
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |154| 
   [ A0]   ZERO    .L2     B7
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |154| 
           FMPYDP  .M2X    A17:A16,B5:B4,B5:B4 ; |154| 
   [!A0]   ZERO    .L2     B7
   [ A0]   MV      .L2X    A12,B6            ; |154| 
   [ A0]   MVKH    .S2     0xbff00000,B7
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |154| 
   [!A0]   MV      .L2X    A12,B6            ; |154| 
   [!A0]   SET     .S2     B7,0x14,0x1d,B7
           FMPYDP  .M2X    A9:A8,B5:B4,B5:B4 ; |154| 
           LDDW    .D2T1   *+SP(200),A5:A4
           NOP             2
           FADDDP  .L2X    B5:B4,A9:A8,B5:B4 ; |154| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |154| 
           NOP             3
           STDW    .D2T2   B5:B4,*B31        ; |154| 
           LDDW    .D1T1   *A14,A7:A6        ; |155| 
           NOP             4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |155| 
   [ A2]   BNOP    .S1     $C$L10,2          ; |150| 

   [ A2]   CALL    .S1     cos               ; |151| 
||         STDW    .D1T1   A5:A4,*++A14      ; |155| 

   [ A2]   LDDW    .D1T1   *A14,A5:A4        ; |151| 

   [!A2]   CALL    .S1     cosdp_v           ; |157| 
||         STW     .D2T1   A2,*+SP(12)       ; |155| 

           ; BRANCHCC OCCURS {$C$L10}        ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B10(16),B4      ; |157| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           MVK     .S1     0x6f4,A6          ; |157| 
           ADDKPC  .S2     $C$RL22,B3,0      ; |157| 
$C$RL22:   ; CALL OCCURS {cosdp_v} {0}       ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0x6f4,A6          ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL23:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B11
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B11
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B11(4)       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0x6f4,A6          ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1X    B10,A3            ; |67| 
||         STW     .D2T1   A4,*+B11(8)       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0x6f4,A6          ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(92),A3       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2     B10,B4            ; |68| 
||         STW     .D2T1   A4,*+B11(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x6f4,A6          ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(96),A3       ; |69| 
           LDW     .D2T2   *+SP(100),B4
           STW     .D2T1   A4,*+B11(16)      ; |69| 
           NOP             2
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |161| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MV      .L1     A10,A3
   [!A0]   MVKL    .S1     all_pass,A4
   [!A0]   MVKH    .S1     all_pass,A4
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

   [!A0]   MV      .L1     A10,A3
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |161| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |161| 
||         ADDKPC  .S2     $C$RL27,B3,0      ; |161| 

$C$RL27:   ; CALL OCCURS {print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           MV      .L2X    A10,B6            ; |114| 

           MV      .L2X    A10,B5            ; |114| 
||         STW     .D2T2   B6,*+SP(124)      ; |114| 

           STW     .D2T2   B5,*+SP(120)      ; |114| 
           LDDW    .D2T2   *+SP(120),B7:B6   ; |114| 
           MVKL    .S1     cycle_counts+24,A3
           MVKH    .S1     cycle_counts+24,A3
           MV      .L2X    A10,B4            ; |114| 
           NOP             1

           STDW    .D1T2   B7:B6,*A3         ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     t_start,A3

           MVKH    .S1     t_start,A3
||         MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B8,B7,B6          ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MVKL    .S1     input,A3

           MVKH    .S1     input,A3
||         CALL    .S2     gimme_random      ; |171| 

           LDW     .D1T1   *A3,A10           ; |171| 

           ZERO    .L1     A5
||         MVK     .S1     0x80,A13

           ZERO    .L2     B4                ; |171| 
||         ZERO    .S2     B5
||         MVKH    .S1     0x40690000,A5
||         ZERO    .L1     A4                ; |171| 

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
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S2     0xc0590000,B5
           ADDKPC  .S2     $C$RL28,B3,0      ; |171| 
$C$RL28:   ; CALL OCCURS {gimme_random} {0}  ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           ADD     .L1     A10,A12,A3        ; |171| 

           STDW    .D1T1   A5:A4,*A3         ; |171| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B7           ; |122| 

           ADD     .L1     A10,A12,A3        ; |74| 
||         MVKL    .S1     0x54442d18,A16
||         MVKL    .S2     0x3ff921fb,B5
||         ZERO    .L2     B8                ; |74| 

           LDDW    .D1T1   *A3,A7:A6         ; |74| 
||         MVKH    .S1     0x54442d18,A16
||         MVKH    .S2     0x3ff921fb,B5

           ABSDP   .S1     A5:A4,A5:A4       ; |72| 
||         MVKL    .S2     0x40092200,B9

           MV      .L2X    A16,B4            ; |74| 
||         MV      .L1X    B5,A17            ; |74| 
||         MVKH    .S2     0x40092200,B9

           MVKL    .S1     0xbfc55555,A23
           FADDDP  .L1     A17:A16,A5:A4,A5:A4 ; |72| 

           ZERO    .L1     A6                ; |74| 
||         ABSDP   .S1     A7:A6,A9:A8       ; |74| 

           ZERO    .D1     A7

           MVKL    .S2     0x6dc9c883,B4
||         FADDDP  .L1X    B5:B4,A9:A8,A9:A8 ; |74| 

           MVKH    .S1     0x41d00000,A7
           MVKL    .S2     0x3fd45f30,B5
           CMPGTDP .S1     A9:A8,A7:A6,A0    ; |74| 
           MVKH    .S2     0x6dc9c883,B4

   [ A0]   MV      .L1     A17,A5            ; |72| 
|| [ A0]   MV      .S1     A16,A4            ; |80| 

           MVKH    .S2     0x3fd45f30,B5
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |80| 
           MVKL    .S2     0xdc08499c,B16
           MVKL    .S1     0x55555555,A22
           MVKL    .S2     0xbd6ae420,B17
           DPINT   .L2     B5:B4,B18         ; |80| 
           MVKH    .S2     0xdc08499c,B16
           MVKH    .S2     0xbd6ae420,B17
           MVKH    .S1     0xbfc55555,A23
           INTDP   .L2     B18,B5:B4         ; |80| 
           MVKH    .S1     0x55555555,A22
           MVKL    .S1     0xbee2aeef,A7
           MVKL    .S1     0x4b9ee59e,A6
           MVKH    .S1     0xbee2aeef,A7
           FMPYDP  .M2     B9:B8,B5:B4,B9:B8 ; |86| 
           MVKH    .S1     0x4b9ee59e,A6
           MVKL    .S1     0xbe5ae645,A17
           MVKL    .S1     0x4b5dc0ab,A16
           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |86| 
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |86| 
           MVKH    .S1     0xbe5ae645,A17
           MVKH    .S1     0x4b5dc0ab,A16
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |86| 
           MVKL    .S2     0x6993df95,B4
           MVKL    .S2     0x3ce880ff,B5
           FMPYDP  .M1     A7:A6,A7:A6,A9:A8 ; |175| 
           MVKH    .S2     0x6993df95,B4
           MVKH    .S2     0x3ce880ff,B5
           MVKL    .S2     0x686ad430,B8
           FMPYDP  .M1     A9:A8,A9:A8,A5:A4 ; |175| 
           MVKL    .S2     0x3de6123c,B9
           MVKH    .S2     0x686ad430,B8
           MVKH    .S2     0x3de6123c,B9

           FMPYDP  .M1X    B17:B16,A5:A4,A19:A18 ; |175| 
||         MVKL    .S2     0x1a013e1a,B16

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |175| 
||         MVKL    .S2     0xbf2a01a0,B17

           MVKH    .S2     0x1a013e1a,B16
           MVKH    .S2     0xbf2a01a0,B17
           FADDDP  .L1     A17:A16,A19:A18,A17:A16 ; |175| 

           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |175| 
||         MVKL    .S2     0xa524f063,B8

           MVKL    .S2     0x3ec71de3,B9
           FMPYDP  .M1     A5:A4,A17:A16,A19:A18 ; |175| 
           MVKH    .S2     0xa524f063,B8
           FMPYDP  .M1X    A5:A4,B5:B4,A17:A16 ; |175| 
           MVKH    .S2     0x3ec71de3,B9
           FADDDP  .L1X    B17:B16,A19:A18,A21:A20 ; |175| 
           MVKL    .S1     0x111110b0,A18
           FADDDP  .L1X    B9:B8,A17:A16,A17:A16 ; |175| 
           MVKL    .S1     0x3f811111,A19
           FMPYDP  .M1     A5:A4,A21:A20,A21:A20 ; |175| 
           FMPYDP  .M1     A5:A4,A17:A16,A17:A16 ; |175| 
           MVKH    .S1     0x111110b0,A18
           MVKH    .S1     0x3f811111,A19
           FADDDP  .L1     A23:A22,A21:A20,A21:A20 ; |175| 
           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |175| 
           MVKL    .S2     t_start,B13
           FMPYDP  .M1     A9:A8,A21:A20,A9:A8 ; |175| 
           FMPYDP  .M1     A5:A4,A17:A16,A5:A4 ; |175| 
           MVK     .S1     12,A31
           ADD     .L1X    B10,A31,A3
           LDW     .D1T1   *A3,A3            ; |175| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |175| 
           AND     .L2     1,B18,B0          ; |83| 
   [!B0]   ZERO    .L2     B4                ; |83| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |175| 
   [ B0]   ZERO    .L2     B5
   [!B0]   ZERO    .L2     B5
   [ B0]   ZERO    .L2     B4                ; |83| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |175| 
   [ B0]   MVKH    .S2     0xbff00000,B5
   [!B0]   SET     .S2     B5,0x14,0x1d,B5
           MVKH    .S2     t_start,B13
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |175| 
           STDW    .D2T2   B7:B6,*B13
           ADD     .L1     A12,A3,A3         ; |175| 
           NOP             1

           STDW    .D1T2   B5:B4,*A3         ; |175| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B8           ; |128| 

           MVKL    .S1     t_offset,A3
||         SUB     .L1     A13,1,A0          ; |169| 
||         MVKL    .S2     t_stop,B12
||         MV      .L2     B8,B17            ; |128| 
||         SUB     .D1     A13,1,A13         ; |169| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     t_stop,B12
||         ADD     .L1     8,A12,A12         ; |169| 

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         MVKL    .S1     cycle_counts+24,A30
||         STDW    .D2T2   B17:B16,*B12      ; |128| 

           MVKH    .S1     cycle_counts+24,A30

           LDDW    .D1T1   *A30,A7:A6        ; |130| 
|| [ A0]   MVKL    .S1     input,A3
||         MV      .L1     A30,A11           ; |128| 

   [ A0]   MVKH    .S1     input,A3
   [ A0]   LDW     .D1T1   *A3,A10           ; |171| 

           ADDU    .L2X    A4,B6,B5:B4       ; |130| 
|| [ A0]   ZERO    .L1     A4                ; |171| 

           ADD     .S2X    B5,A5,B6          ; |130| 
|| [ A0]   B       .S1     $C$L12            ; |169| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 
|| [ A0]   ZERO    .L1     A5

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 
|| [ A0]   MVKH    .S1     0x40690000,A5

   [ A0]   CALL    .S1     gimme_random      ; |171| 
||         SUB     .L2     B8,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T2   B5:B4,*A11        ; |130| 
|| [ A0]   ZERO    .L2     B5
|| [ A0]   ZERO    .S2     B4                ; |171| 

           ; BRANCHCC OCCURS {$C$L12}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |135| 
$C$RL29:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL30:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(120),B7:B6
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
           SUBU    .L2X    B5,A14,B7:B6      ; |117| 

           SUB     .L1X    B4,A12,A4         ; |117| 
||         EXT     .S2     B7,24,24,B4       ; |117| 
||         MVKL    .S1     output,A3

           MVKH    .S1     output,A3

           LDW     .D1T1   *A3,A11
||         ADD     .L1X    A4,B4,A3          ; |117| 

           STW     .D2T1   A3,*+SP(12)       ; |117| 
||         CALL    .S1     cos               ; |183| 

           LDDW    .D1T1   *A10++,A5:A4      ; |183| 
           MV      .L1X    B6,A15            ; |117| 
           MVK     .S2     0x80,B11
           NOP             1
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL31,B3,0      ; |183| 
$C$RL31:   ; CALL OCCURS {cos} {0}           ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1X    B11,1,A0          ; |182| 
||         STDW    .D1T1   A5:A4,*A11++      ; |183| 

   [ A0]   B       .S1     $C$L13            ; |182| 
   [ A0]   CALL    .S1     cos               ; |183| 
   [ A0]   LDDW    .D1T1   *A10++,A5:A4      ; |183| 
           SUB     .L2     B11,1,B11         ; |182| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L13}        ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 
           LDW     .D2T1   *+SP(12),A3       ; |128| 
           MV      .L2     B4,B7             ; |128| 
           LDDW    .D2T2   *B10,B5:B4        ; |130| 
           ADDU    .L1     A15,A14,A5:A4     ; |130| 
           STDW    .D2T2   B7:B6,*B12        ; |128| 

           ADD     .S1     A5,A3,A3          ; |130| 
||         SUBU    .L1X    B6,A4,A5:A4       ; |130| 
||         CALL    .S2     __c6xabi_fltllif  ; |130| 

           ADD     .L1     A3,A12,A3         ; |130| 
||         EXT     .S1     A5,24,24,A31      ; |130| 

           ADDU    .L2X    B4,A4,B9:B8       ; |130| 
||         SUB     .L1X    B7,A3,A3          ; |130| 

           ADD     .L2     B9,B5,B4          ; |130| 
||         ADD     .L1     A3,A31,A3         ; |130| 

           MV      .L1X    B8,A4             ; |130| 

           ADD     .L1X    B4,A3,A5          ; |130| 
||         ADDKPC  .S2     $C$RL32,B3,0      ; |130| 

$C$RL32:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(120),B5:B4   ; |130| 
           ZERO    .L1     A10
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           SET     .S1     A10,0x1a,0x1d,A10

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MV      .L1X    B13,A15           ; |116| 

           STDW    .D1T2   B7:B6,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S2     t_offset,B13

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B8,B7,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S2     t_offset,B13

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MVKL    .S1     input,A14

           MV      .L1X    B4,A11            ; |117| 
||         MVKH    .S1     input,A14
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
||         CALL    .S1     cosdp             ; |191| 

           LDDW    .D1T1   *A3,A5:A4         ; |191| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |191| 
$C$RL34:   ; CALL OCCURS {cosdp} {0}         ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |191| 
||         SUB     .L1     A11,1,A0          ; |190| 
||         SUB     .S1     A11,1,A11         ; |190| 

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
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           LDDW    .D2T2   *+B10(8),B17:B16  ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A3          ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
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

$C$RL35:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A10,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(120),B5:B4
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

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1     A12,A11

           MV      .L1X    B4,A12            ; |117| 
||         LDW     .D2T2   *+SP(20),B12      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A14,A3           ; |199| 
           NOP             4

           ADD     .L1     A11,A3,A3         ; |199| 
||         CALL    .S1     cosdp_c           ; |199| 

           LDDW    .D1T1   *A3,A5:A4         ; |199| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |199| 
$C$RL37:   ; CALL OCCURS {cosdp_c} {0}       ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |199| 
||         SUB     .L1     A12,1,A0          ; |198| 
||         SUB     .S1     A12,1,A12         ; |198| 

   [ A0]   BNOP    .S1     $C$L15,3          ; |198| 

           ADD     .L1X    A11,B4,A3         ; |199| 
||         ADD     .S1     8,A11,A11         ; |198| 

           STDW    .D1T1   A5:A4,*A3         ; |199| 
           ; BRANCHCC OCCURS {$C$L15}        ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MV      .L1     A15,A11           ; |128| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           LDDW    .D1T1   *A11,A5:A4        ; |130| 
           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .L2X    B6,A5,B6          ; |130| 
||         CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .S2     B9,B6,B4          ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 

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
;          EXCLUSIVE CPU CYCLES: 108
           MPYSP   .M1     A10,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(120),B5:B4
           ADDAD   .D2     B11,1,B12
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
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

           MVKL    .S1     output,A11
||         ADD     .L2     B6,B5,B5          ; |117| 

           MVKH    .S1     output,A11
||         MV      .L2X    A14,B9            ; |206| 
||         STDW    .D2T2   B5:B4,*B13        ; |117| 

           CALLP   .S2     cosdp_v,B3
||         LDW     .D1T2   *+A11(16),B4      ; |206| 
||         LDW     .D2T1   *B9,A4            ; |206| 
||         MVK     .S1     0x80,A6           ; |206| 

$C$RL40:   ; CALL OCCURS {cosdp_v} {0}       ; |206| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MVK     .S1     16,A14
           ADD     .L1X    B12,A14,A14
           LDDW    .D1T1   *A14,A9:A8        ; |130| 
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
           MPYSP   .M1     A10,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STDW    .D1T1   A5:A4,*A14        ; |130| 
||         MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A11,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL43:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     fcn_pass,B10
           MVKH    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S2     fcn_pass,B10

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A11(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(104),A3      ; |68| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T1   *A11,A4           ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(108),B4      ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(112),B4
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
           MV      .L1     A12,A3
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
;          EXCLUSIVE CPU CYCLES: 12
           ADDK    .S2     224,SP            ; |224| 
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
$C$SL1:	.string	"cosDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	cos
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	cosdp
	.global	cosdp_c
	.global	cosdp_v
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
