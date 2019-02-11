;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:53:02 2013                                *
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
	.elfsym	a,SYM_SIZE(400)
a:
	.word	0c0c88f0bh		; a[0] @ 0
	.word	0c10f4415h		; a[1] @ 32
	.word	041103c61h		; a[2] @ 64
	.word	04105432ah		; a[3] @ 96
	.word	03fdf7976h		; a[4] @ 128
	.word	040e81574h		; a[5] @ 160
	.word	0bf089013h		; a[6] @ 192
	.word	0bf9a739dh		; a[7] @ 224
	.word	0c05750feh		; a[8] @ 256
	.word	0be9f123ch		; a[9] @ 288
	.word	0c10b2fb9h		; a[10] @ 320
	.word	041143c22h		; a[11] @ 352
	.word	0404b1992h		; a[12] @ 384
	.word	040e14267h		; a[13] @ 416
	.word	0c10d76b9h		; a[14] @ 448
	.word	0c11aa46eh		; a[15] @ 480
	.word	0c1195bf9h		; a[16] @ 512
	.word	0c1032356h		; a[17] @ 544
	.word	0c117d3f9h		; a[18] @ 576
	.word	0c0479718h		; a[19] @ 608
	.word	0c0fd136bh		; a[20] @ 640
	.word	03f9e315ch		; a[21] @ 672
	.word	040a1260eh		; a[22] @ 704
	.word	0410248eah		; a[23] @ 736
	.word	040b7fc0fh		; a[24] @ 768
	.word	040d47288h		; a[25] @ 800
	.word	0c0a73791h		; a[26] @ 832
	.word	040fe9e5fh		; a[27] @ 864
	.word	0c0c2696eh		; a[28] @ 896
	.word	0407a7dd2h		; a[29] @ 928
	.word	040892e82h		; a[30] @ 960
	.word	04086b386h		; a[31] @ 992
	.word	0404ceb5eh		; a[32] @ 1024
	.word	0c0d09585h		; a[33] @ 1056
	.word	04010bd12h		; a[34] @ 1088
	.word	04114ec1ch		; a[35] @ 1120
	.word	0408e6755h		; a[36] @ 1152
	.word	0be887722h		; a[37] @ 1184
	.word	03ff3f4b7h		; a[38] @ 1216
	.word	03e345961h		; a[39] @ 1248
	.word	0c0db991dh		; a[40] @ 1280
	.word	0c1043584h		; a[41] @ 1312
	.word	03f4a301ah		; a[42] @ 1344
	.word	0c0036602h		; a[43] @ 1376
	.word	041117e53h		; a[44] @ 1408
	.word	0403109d2h		; a[45] @ 1440
	.word	03f8a6a33h		; a[46] @ 1472
	.word	04101d280h		; a[47] @ 1504
	.word	0c069574dh		; a[48] @ 1536
	.word	0c114ec7dh		; a[49] @ 1568
	.word	0410c35deh		; a[50] @ 1600
	.word	03f08cf59h		; a[51] @ 1632
	.word	04063613eh		; a[52] @ 1664
	.word	0c01f0a39h		; a[53] @ 1696
	.word	0c0a3ad1dh		; a[54] @ 1728
	.word	041195b5fh		; a[55] @ 1760
	.word	0405ce50ch		; a[56] @ 1792
	.word	0411c0b7ah		; a[57] @ 1824
	.word	0c0bb04aeh		; a[58] @ 1856
	.word	0c0c4d891h		; a[59] @ 1888
	.word	0c0d2e3f4h		; a[60] @ 1920
	.word	0bfe54969h		; a[61] @ 1952
	.word	040c8b3b2h		; a[62] @ 1984
	.word	0c05ab649h		; a[63] @ 2016
	.word	0c0a03c69h		; a[64] @ 2048
	.word	0bfefb6d9h		; a[65] @ 2080
	.word	0c09e20dbh		; a[66] @ 2112
	.word	0409e12cah		; a[67] @ 2144
	.word	0c0bbe202h		; a[68] @ 2176
	.word	0411458cch		; a[69] @ 2208
	.word	04108c21bh		; a[70] @ 2240
	.word	0c1118a07h		; a[71] @ 2272
	.word	03fabf9ffh		; a[72] @ 2304
	.word	0c093ebb7h		; a[73] @ 2336
	.word	0bef3d259h		; a[74] @ 2368
	.word	0c1169c85h		; a[75] @ 2400
	.word	0c108d85ch		; a[76] @ 2432
	.word	0409b5c67h		; a[77] @ 2464
	.word	04097d474h		; a[78] @ 2496
	.word	0408c53deh		; a[79] @ 2528
	.word	040583bdah		; a[80] @ 2560
	.word	0c1171ac0h		; a[81] @ 2592
	.word	040b21353h		; a[82] @ 2624
	.word	0c0233db8h		; a[83] @ 2656
	.word	03f548bc3h		; a[84] @ 2688
	.word	041175d7ch		; a[85] @ 2720
	.word	040f8f0aah		; a[86] @ 2752
	.word	0bf828742h		; a[87] @ 2784
	.word	0c1060d57h		; a[88] @ 2816
	.word	0404e5167h		; a[89] @ 2848
	.word	03fbbe6a3h		; a[90] @ 2880
	.word	0402298a8h		; a[91] @ 2912
	.word	040fdfadfh		; a[92] @ 2944
	.word	0c021b015h		; a[93] @ 2976
	.word	03f6b0ae5h		; a[94] @ 3008
	.word	040c94dc8h		; a[95] @ 3040
	.word	040d1ca61h		; a[96] @ 3072
	.word	04025d1e3h		; a[97] @ 3104
	.word	040a2e7c3h		; a[98] @ 3136
	.word	0c0ea5a46h		; a[99] @ 3168

	.global	b
	.sect	".fardata:b", RW
	.clink
	.align	8
	.elfsym	b,SYM_SIZE(400)
b:
	.word	041c80000h		; b[0] @ 0
	.word	041c00000h		; b[1] @ 32
	.word	041c80000h		; b[2] @ 64
	.word	0c1c80000h		; b[3] @ 96
	.word	000000000h		; b[4] @ 128
	.word	041c80000h		; b[5] @ 160
	.word	041c80000h		; b[6] @ 192
	.word	041c80000h		; b[7] @ 224
	.word	041c80000h		; b[8] @ 256
	.word	041c80000h		; b[9] @ 288
	.word	041c80000h		; b[10] @ 320
	.word	041c00000h		; b[11] @ 352
	.word	041c80000h		; b[12] @ 384
	.word	0c1c80000h		; b[13] @ 416
	.word	000000000h		; b[14] @ 448
	.word	041c80000h		; b[15] @ 480
	.word	041c80000h		; b[16] @ 512
	.word	041c80000h		; b[17] @ 544
	.word	041c80000h		; b[18] @ 576
	.word	041c80000h		; b[19] @ 608
	.word	041c80000h		; b[20] @ 640
	.word	041c00000h		; b[21] @ 672
	.word	041c80000h		; b[22] @ 704
	.word	0c1c80000h		; b[23] @ 736
	.word	000000000h		; b[24] @ 768
	.word	041c80000h		; b[25] @ 800
	.word	041c80000h		; b[26] @ 832
	.word	041c80000h		; b[27] @ 864
	.word	041c80000h		; b[28] @ 896
	.word	041c80000h		; b[29] @ 928
	.word	041c80000h		; b[30] @ 960
	.word	041c00000h		; b[31] @ 992
	.word	041c80000h		; b[32] @ 1024
	.word	0c1c80000h		; b[33] @ 1056
	.word	000000000h		; b[34] @ 1088
	.word	041c80000h		; b[35] @ 1120
	.word	041c80000h		; b[36] @ 1152
	.word	041c80000h		; b[37] @ 1184
	.word	041c80000h		; b[38] @ 1216
	.word	041c80000h		; b[39] @ 1248
	.word	041c80000h		; b[40] @ 1280
	.word	041c00000h		; b[41] @ 1312
	.word	041c80000h		; b[42] @ 1344
	.word	0c1c80000h		; b[43] @ 1376
	.word	000000000h		; b[44] @ 1408
	.word	041c80000h		; b[45] @ 1440
	.word	041c80000h		; b[46] @ 1472
	.word	041c80000h		; b[47] @ 1504
	.word	041c80000h		; b[48] @ 1536
	.word	041c80000h		; b[49] @ 1568
	.word	041c80000h		; b[50] @ 1600
	.word	041c00000h		; b[51] @ 1632
	.word	041c80000h		; b[52] @ 1664
	.word	0c1c80000h		; b[53] @ 1696
	.word	000000000h		; b[54] @ 1728
	.word	041c80000h		; b[55] @ 1760
	.word	041c80000h		; b[56] @ 1792
	.word	041c80000h		; b[57] @ 1824
	.word	041c80000h		; b[58] @ 1856
	.word	041c80000h		; b[59] @ 1888
	.word	041c80000h		; b[60] @ 1920
	.word	041c00000h		; b[61] @ 1952
	.word	041c80000h		; b[62] @ 1984
	.word	0c1c80000h		; b[63] @ 2016
	.word	000000000h		; b[64] @ 2048
	.word	041c80000h		; b[65] @ 2080
	.word	041c80000h		; b[66] @ 2112
	.word	041c80000h		; b[67] @ 2144
	.word	041c80000h		; b[68] @ 2176
	.word	041c80000h		; b[69] @ 2208
	.word	041c80000h		; b[70] @ 2240
	.word	041c00000h		; b[71] @ 2272
	.word	041c80000h		; b[72] @ 2304
	.word	0c1c80000h		; b[73] @ 2336
	.word	000000000h		; b[74] @ 2368
	.word	041c80000h		; b[75] @ 2400
	.word	041c80000h		; b[76] @ 2432
	.word	041c80000h		; b[77] @ 2464
	.word	041c80000h		; b[78] @ 2496
	.word	041c80000h		; b[79] @ 2528
	.word	041c80000h		; b[80] @ 2560
	.word	041c00000h		; b[81] @ 2592
	.word	041c80000h		; b[82] @ 2624
	.word	0c1c80000h		; b[83] @ 2656
	.word	000000000h		; b[84] @ 2688
	.word	041c80000h		; b[85] @ 2720
	.word	041c80000h		; b[86] @ 2752
	.word	041c80000h		; b[87] @ 2784
	.word	041c80000h		; b[88] @ 2816
	.word	041c80000h		; b[89] @ 2848
	.word	041c80000h		; b[90] @ 2880
	.word	041c00000h		; b[91] @ 2912
	.word	041c80000h		; b[92] @ 2944
	.word	0c1c80000h		; b[93] @ 2976
	.word	000000000h		; b[94] @ 3008
	.word	041c80000h		; b[95] @ 3040
	.word	041c80000h		; b[96] @ 3072
	.word	041c80000h		; b[97] @ 3104
	.word	041c80000h		; b[98] @ 3136
	.word	041c80000h		; b[99] @ 3168

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\149922 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\149924 
;**	Parameter deleted: req_flags == 9;
;**	Parameter deleted: tol == 0.0001;
	.sect	".text"
	.clink

;******************************************************************************
;* FUNCTION NAME: allequal                                                    *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,B0,B1, *
;*                           B2,B3,B4,B5,B6,B7,B8,B9,SP,A16,A17,A18,A19,A20,  *
;*                           A21,A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16, *
;*                           B17,B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28, *
;*                           B29,B30,B31                                      *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,B0,B1, *
;*                           B2,B3,B4,B5,B6,B7,B8,B9,DP,SP,A16,A17,A18,A19,   *
;*                           A20,A21,A22,A23,A24,A25,A26,A27,A28,A29,A30,A31, *
;*                           B16,B17,B18,B19,B20,B21,B22,B23,B24,B25,B26,B27, *
;*                           B28,B29,B30,B31                                  *
;*   Local Frame Size  : 0 Args + 0 Auto + 24 Save = 24 byte                  *
;******************************************************************************
allequal:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STW     .D2T1   A11,*SP--(8)      ; |63| 
||         MVKL    .S2     0xeb1c432d,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     output,A11
||         MVKL    .S2     0x3f1a36e2,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     output,A11
||         MVKH    .S2     0xeb1c432d,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3f1a36e2,B7
||         MVK     .S1     0x9,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {isequal} {0}       ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A12
||         MVKH    .S2     0x3f1a36e2,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A12
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xeb1c432d,B6
           MVKL    .S2     0x3f1a36e2,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3f1a36e2,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3f1a36e2,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MV      .L1     A10,A6            ; |69| 
||         MVK     .S1     0x9,A8            ; |69| 

$C$RL3:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2X    4,A12,B4
           LDW     .D2T1   *B4,A0            ; |72| 
           STW     .D1T1   A4,*+A12(16)      ; |69| 
           ADD     .L2X    8,A12,B4
           NOP             2

   [!A0]   BNOP    .S1     $C$L1,5           ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 
|| [ A0]   ADD     .L2     4,B4,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVKL    .S1     all_pass,A3

   [ A0]   B       .S2     $C$L2             ; |72| 
||         MVKH    .S1     all_pass,A3
|| [ A0]   MV      .L2X    A13,B3            ; |74| 

   [ A0]   STW     .D1T1   A4,*A3            ; |72| 
   [ A0]   LDW     .D2T1   *++SP(8),A10      ; |74| 

   [ A0]   RET     .S2     B3                ; |74| 
|| [ A0]   LDDW    .D2T1   *++SP,A13:A12     ; |74| 

   [ A0]   LDW     .D2T1   *++SP(8),A11      ; |74| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L2}         ; |72| 
;** --------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 7
           MVKL    .S1     all_pass,A3

           MVKH    .S1     all_pass,A3
||         ZERO    .L1     A4                ; |72| 

           STW     .D1T1   A4,*A3            ; |72| 

           LDW     .D2T1   *++SP(8),A10      ; |74| 
||         MV      .L2X    A13,B3            ; |74| 

           LDDW    .D2T1   *++SP,A13:A12     ; |74| 
||         RET     .S2     B3                ; |74| 

           LDW     .D2T1   *++SP(8),A11      ; |74| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 3
           NOP             3
           ; BRANCH OCCURS {B3}              ; |74| 
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
;*   Local Frame Size  : 8 Args + 44 Auto + 56 Save = 108 byte                *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |111| 
           STW     .D2T1   A10,*SP--(8)      ; |111| 
           STDW    .D2T2   B13:B12,*SP--     ; |111| 
           STDW    .D2T2   B11:B10,*SP--     ; |111| 
           STDW    .D2T1   A15:A14,*SP--     ; |111| 

           STDW    .D2T1   A13:A12,*SP--     ; |111| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(64)      ; |111| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |120| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           MVKL    .S2     b,B10
||         MVKL    .S1     a,A10

           MVK     .S1     0x64,A11
||         MVKL    .S2     output,B13

           MVKH    .S2     b,B10
||         MVKH    .S1     a,A10

           CALL    .S1     powf              ; |129| 
||         MV      .L2     B10,B12
||         MV      .L1     A10,A12
||         MVKH    .S2     output,B13
||         ZERO    .D2     B11

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5

           LDW     .D1T1   *A12++,A4         ; |129| 
||         LDW     .D2T2   *B12++,B4         ; |129| 

           ADDKPC  .S2     $C$RL5,B3,3       ; |129| 
$C$RL5:    ; CALL OCCURS {powf} {0}          ; |129| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |129| 
||         SUB     .L1     A11,1,A0          ; |128| 
||         SUB     .S1     A11,1,A11         ; |128| 

   [ A0]   BNOP    .S1     $C$L3,3           ; |128| 

           ADD     .L2     B11,B4,B4         ; |129| 
||         ADD     .S2     4,B11,B11         ; |128| 

   [ A0]   CALL    .S1     powf              ; |129| 
||         STW     .D2T1   A4,*B4            ; |129| 
|| [!A0]   ADD     .L2     4,B13,B4

           ; BRANCHCC OCCURS {$C$L3}         ; |128| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           CALL    .S2     powsp             ; |132| 
||         ZERO    .L2     B11
||         MV      .L1X    B10,A12
||         MV      .D1     A10,A11
||         MVK     .S1     0x64,A13
||         STW     .D2T2   B4,*+SP(20)

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5

           LDW     .D2T2   *B10++,B4         ; |132| 
||         LDW     .D1T1   *A11++,A4         ; |132| 

           ADDKPC  .S2     $C$RL6,B3,3       ; |132| 
$C$RL6:    ; CALL OCCURS {powsp} {0}         ; |132| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(20),B4       ; |132| 
           SUB     .L1     A13,1,A0          ; |131| 
           SUB     .L1     A13,1,A13         ; |131| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |132| 
   [ A0]   BNOP    .S1     $C$L4,3           ; |131| 

           ADD     .L2     B11,B4,B4         ; |132| 
||         ADD     .S2     4,B11,B11         ; |131| 

   [ A0]   CALL    .S1     powsp             ; |132| 
||         STW     .D2T1   A4,*B4            ; |132| 

           ; BRANCHCC OCCURS {$C$L4}         ; |131| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(20),B4
           MV      .L2X    A12,B11
           MV      .L1     A10,A13
           MVK     .S1     0x64,A11
           ZERO    .L2     B10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(24)
||         CALL    .S1     powsp_c           ; |135| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5

           LDW     .D1T1   *A13++,A4         ; |135| 
||         LDW     .D2T2   *B11++,B4         ; |135| 

           ADDKPC  .S2     $C$RL7,B3,3       ; |135| 
$C$RL7:    ; CALL OCCURS {powsp_c} {0}       ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(24),B4       ; |135| 
||         SUB     .L1     A11,1,A0          ; |134| 
||         SUB     .S1     A11,1,A11         ; |134| 

   [!A0]   LDW     .D2T1   *+SP(24),A3
|| [!A0]   ZERO    .L2     B13
|| [!A0]   MVKL    .S1     0x3effffff,A20
|| [!A0]   ZERO    .L1     A19
|| [!A0]   MVKL    .S2     0x3f7ffffe,B16

   [!A0]   MVKH    .S1     0xbf000000,A19
   [!A0]   SET     .S2     B13,0x17,0x1e,B13
   [!A0]   MVKH    .S1     0x3effffff,A20
           LDW     .D2T2   *B4,B4            ; |135| 
   [ A0]   BNOP    .S1     $C$L5,3           ; |134| 

           ADD     .L2     B10,B4,B4         ; |135| 
||         ADD     .S2     4,B10,B10         ; |134| 

   [ A0]   CALL    .S1     powsp_c           ; |135| 
||         STW     .D2T1   A4,*B4            ; |135| 
|| [!A0]   SPDP    .S2     B13,B5:B4

           ; BRANCHCC OCCURS {$C$L5}         ; |134| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     0xfefa39ec,A4
||         ADD     .L2X    3,A19,B6
||         ZERO    .L1     A7
||         ADD     .D1     4,A3,A17
||         ADD     .D2     -1,B13,B11

           MVKL    .S1     0xc2aeac50,A13
||         MVKH    .S2     0x3f7ffffe,B16
||         STDW    .D2T2   B5:B4,*+SP(40)
||         LDW     .D1T1   *A17,A3
||         MV      .L2X    A12,B20
||         MV      .L1     A10,A16

           MVKL    .S1     0x3fe62e42,A5
||         ADD     .L2     2,B16,B10
||         STW     .D2T2   B6,*+SP(12)
||         MVK     .S2     0x64,B1
||         ZERO    .L1     A6                ; |83| 
||         ZERO    .D1     A18               ; |83| 

           MVKH    .S1     0xfefa39ec,A4
||         ADD     .L2X    1,A20,B12

           MVKH    .S1     0xc2aeac50,A13
           MVKH    .S1     0x3fe62e42,A5
           SET     .S1     A7,0x14,0x1d,A7
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Disqualified loop: Did not find partition
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A16++,A24        ; |83| 
           NOP             4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 131

           ABSSP   .S1     A24,A25           ; |83| 
||         MVKL    .S2     0x3e436581,B4
||         LDW     .D2T2   *+SP(12),B31
||         ZERO    .L2     B29

           LDW     .D2T2   *B20++,B21        ; |83| 
||         ZERO    .L2     B23
||         SPDP    .S1     A25,A9:A8         ; |83| 

           MVKH    .S2     0x3e436581,B4
           RCPDP   .S1     A9:A8,A9:A8       ; |83| 
           MVKL    .S2     0xbe804d66,B5
           CLR     .S1     A9,0,16,A19       ; |83| 
           MPYSPDP .M1     A25,A19:A18,A9:A8 ; |83| 
           MVKH    .S2     0xbe804d66,B5
           MVKL    .S2     0x41b8aa3b,B30
           MVKH    .S2     0x41b8aa3b,B30
           MVKH    .S2     0xbf000000,B29
           MVKL    .S1     0xbe6bd0fc,A31
           MVKL    .S2     0x3d317000,B28
           FSUBDP  .L1     A9:A8,A7:A6,A21:A20 ; |83| 
           MVKH    .S1     0xbe6bd0fc,A31
           EXTU    .S1     A19,1,21,A30      ; |83| 
           DPSP    .L1     A21:A20,A8        ; |83| 
           MVK     .S1     0xfffffc01,A23
           MVKL    .S1     0x3eaaa872,A29
           MVKH    .S1     0x3eaaa872,A29
           MPYSP   .M1     A8,A8,A26         ; |83| 
           MVKL    .S1     logtable,A28
           MPYSP   .M2X    B4,A8,B4          ; |83| 
           MVKH    .S1     logtable,A28
           MPYSP   .M1     A31,A26,A22       ; |83| 

           MPYSP   .M1     A26,A8,A23        ; |83| 
||         ADD     .L1     A23,A30,A8        ; |83| 

           FADDSP  .L2     B5,B4,B4          ; |83| 
           MPYSP   .M1     A26,A26,A27       ; |83| 
           INTDP   .L1     A8,A9:A8          ; |83| 

           FADDSP  .L2X    A22,B4,B4         ; |83| 
||         EXTU    .S1     A19,12,29,A22     ; |83| 

           MPYSP   .M1     A29,A23,A19       ; |83| 
           LDDW    .D1T1   *+A28[A22],A23:A22 ; |83| 
           MPYSP   .M2X    A27,B4,B5         ; |83| 
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |83| 
           MVKH    .S2     0x3d317000,B28
           MPYSP   .M2X    B31,A26,B4        ; |83| 
           FADDSP  .L2X    B5,A19,B5         ; |83| 
           FSUBDP  .L1     A23:A22,A9:A8,A9:A8 ; |83| 
           MVKL    .S2     0x3e2abce4,B27
           FADDSP  .L2     B5,B4,B4          ; |83| 
           FADDDP  .L1     A9:A8,A21:A20,A9:A8 ; |83| 
           MVKH    .S2     0x3e2abce4,B27
           SPDP    .S2     B4,B5:B4          ; |83| 
           SUB     .L2     B1,1,B1           ; |137| 
           FADDDP  .L2X    B5:B4,A9:A8,B5:B4 ; |83| 
           MVKL    .S2     kTable,B25
           CMPGTSP .S1X    A25,B11,A1        ; |83| 
           DPSP    .L2     B5:B4,B9          ; |83| 
           MVKL    .S1     0x42b17218,A8
           MVKH    .S1     0x42b17218,A8
           CMPEQSP .S1X    A25,B10,A0        ; |83| 
   [ A1]   MV      .L2X    A8,B9             ; |83| 
   [!A0]   MPYSP   .M2     B21,B9,B8         ; |83| 
           MVKH    .S2     kTable,B25
           MVKH    .S2     0xfff00000,B23
   [ A0]   MV      .L2X    A6,B8             ; |83| 
           MPYSP   .M2     B30,B8,B4         ; |135| 
           MVK     .S2     0x72,B18
           MVKL    .S1     0x3605fdf4,A2
           MVKH    .S1     0x3605fdf4,A2
           FADDSP  .L2     B12,B4,B5         ; |135| 
           MVKL    .S1     0x3effffff,A31
           MVKH    .S1     0x3effffff,A31
           SPTRUNC .L2     B5,B7             ; |135| 
           MVKL    .S1     0x3f7ffffe,A30
           MVKH    .S1     0x3f7ffffe,A30
           CMPLTSP .S2     B4,B29,B6         ; |135| 
           SUB     .L2     B7,B6,B16         ; |135| 
           INTSP   .L2     B16,B4            ; |135| 
           MVKL    .S1     jTable,A29
           MVKH    .S1     jTable,A29
           ZERO    .L1     A27
           MPYSP   .M2     B28,B4,B5         ; |135| 
           MVKL    .S2     0x42b17218,B9
           MPYSP   .M1X    A2,B4,A8          ; |135| 
           MVKH    .S2     0x42b17218,B9
           FSUBSP  .L2     B8,B5,B4          ; |135| 
           EXTU    .S2     B8,1,24,B22       ; |135| 
           CMPLTSP .S1X    B8,A13,A0         ; |135| 
           FSUBSP  .L2X    B4,A8,B4          ; |135| 
           CMPLTU  .L2     B22,B18,B0        ; |135| 
           SUB     .S2     B7,B6,B26         ; |135| 
           MPYSP   .M2     B4,B4,B5          ; |135| 
           MPYSP   .M1X    A30,B4,A19        ; |135| 
           AND     .L1X    3,B16,A30         ; |135| 
           LDDW    .D1T1   *+A29[A30],A9:A8  ; |135| 

           MPYSP   .M2     B5,B4,B17         ; |135| 
||         EXTU    .S2     B26,28,30,B4      ; |135| 

           MPYSP   .M1X    A31,B5,A20        ; |135| 
||         LDDW    .D2T2   *+B25[B4],B5:B4   ; |135| 

           SPINT   .L2     B21,B22           ; |135| 
   [ A0]   ZERO    .L1     A22
           MPYSP   .M2     B27,B17,B17       ; |135| 
           SHL     .S2     B16,16,B24        ; |135| 

           FMPYDP  .M1X    A9:A8,B5:B4,A9:A8 ; |135| 
||         AND     .L2     B23,B24,B5        ; |135| 
||         INTSP   .S2     B22,B23           ; |135| 

   [ B0]   FADDSP  .L2     B10,B8,B18        ; |135| 
           FADDSP  .L2X    A20,B17,B6        ; |135| 
           AND     .D2     1,B22,B2          ; |135| 
           CMPEQSP .S2     B21,B23,B26       ; |135| 

   [!B2]   MVK     .L1     0x1,A19           ; |135| 
||         CMPEQSP .S2     B21,B23,B31       ; |135| 
||         FADDSP  .L2X    B6,A19,B17        ; |135| 

           MV      .L2X    A8,B4             ; |135| 
           ADD     .S2X    B5,A9,B5          ; |135| 

           FADDSP  .L2     B10,B17,B16       ; |135| 
||         SPDP    .S2X    A24,B7:B6         ; |135| 

   [ B2]   MVK     .L1     0xffffffff,A19    ; |135| 
           ZERO    .L1     A9:A8             ; |135| 

   [!B0]   MPYSPDP .M2     B16,B5:B4,B19:B18 ; |135| 
||         CMPEQDP .S1X    B7:B6,A9:A8,A8    ; |135| 

           ZERO    .L2     B17:B16           ; |135| 
||         SPDP    .S2     B21,B5:B4         ; |135| 

           CMPLTDP .S2     B7:B6,B17:B16,B24 ; |135| 
           ZERO    .L2     B17:B16           ; |135| 

           AND     .L2     B24,B26,B2        ; |135| 
||         CMPLTDP .S2     B5:B4,B17:B16,B25 ; |135| 

   [ B2]   MV      .L1     A19,A9            ; |135| 
|| [!B2]   MVK     .S1     0x1,A9            ; |135| 
||         ZERO    .L2     B17:B16           ; |135| 

           INTSP   .L1     A9,A9             ; |135| 
||         XOR     .L2     1,B25,B7          ; |135| 

   [!B0]   DPSP    .L2     B19:B18,B18       ; |135| 
||         CMPGTSP .S2     B8,B9,B2          ; |135| 
||         ZERO    .D2     B8

           CMPLTDP .S2     B5:B4,B17:B16,B6  ; |135| 
|| [ B2]   MV      .L2     B11,B8            ; |135| 
||         AND     .L1X    A8,B7,A1          ; |135| 

           XOR     .L2     1,B31,B16         ; |135| 
|| [ A1]   ZERO    .S1     A20

           AND     .S2     B24,B16,B0        ; |135| 
           AND     .L1X    A8,B6,A2          ; |135| 
   [!A0]   MV      .L1X    B18,A22           ; |135| 
           ZERO    .L2     B7:B6             ; |135| 
   [!B2]   MV      .L2X    A22,B8            ; |135| 
           SET     .S1     A27,0x0,0x1e,A8
   [!B0]   MPYSP   .M1X    B8,A9,A23         ; |135| 
   [ B0]   MV      .L1     A8,A23            ; |135| 
   [ A2]   LDDW    .D2T1   *+SP(40),A9:A8    ; |135| 
           CMPEQDP .S2     B5:B4,B7:B6,B2    ; |135| 
   [!A1]   MV      .L1     A23,A20           ; |135| 
   [!A2]   SPDP    .S1     A20,A9:A8         ; |135| 
   [ B1]   B       .S2     $C$L6             ; |137| 
   [!B2]   DPSP    .L1     A9:A8,A21         ; |135| 
   [!B1]   ADD     .L1     4,A17,A11
   [ B2]   MV      .L1X    B10,A21           ; |135| 
           NOP             1

   [!B1]   CALL    .S1     powsp_v           ; |140| 
||         STW     .D1T1   A21,*A3++         ; |135| 

           ; BRANCHCC OCCURS {$C$L6}         ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11,A6           ; |140| 
           MVK     .S2     0x64,B6           ; |140| 
           MV      .L2X    A12,B4            ; |140| 
           MV      .L1     A10,A4            ; |140| 
           ADDKPC  .S2     $C$RL8,B3,0       ; |140| 
$C$RL8:    ; CALL OCCURS {powsp_v} {0}       ; |140| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0x64,A4           ; |143| 

$C$RL9:    ; CALL OCCURS {allequal} {0}      ; |143| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |144| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |144| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     b_sc,A12
||         MVKL    .S2     a_sc,B5
||         ZERO    .L1     A4

           MVKH    .S1     0xbf800000,A4
||         MVKH    .S2     a_sc,B5
||         ZERO    .L2     B18

           ADD     .D2     B5,24,B7
||         MVKH    .S1     b_sc,A12
||         ZERO    .L2     B4
||         MV      .S2     B13,B19           ; |154| 
||         MV      .L1X    B10,A5            ; |156| 

           STDW    .D2T1   A5:A4,*+B5(16)    ; |156| 
||         MVKH    .S2     0xff800000,B18
||         ZERO    .L2     B17

           STDW    .D2T2   B19:B18,*+B5(8)   ; |154| 
||         MV      .L2X    A12,B8            ; |152| 
||         SET     .S2     B4,0x0,0x1e,B4

           STDW    .D2T2   B19:B18,*+B8(8)   ; |154| 
||         MVK     .L2     0x6,B4            ; |159| 
||         ADD     .S2     1,B4,B16
||         MVK     .L1     0x5,A1            ; |158| 

           STDW    .D2T2   B17:B16,*B8       ; |152| 
||         MVC     .S2     B4,RILC
||         SUB     .L1     A1,1,A1           ; |158| 
||         MVK     .L2     5,B9              ; |159| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/powsp/powsp_d.c
;*      Loop source line                 : 159
;*      Loop opening brace source line   : 159
;*      Loop closing brace source line   : 163
;*      Known Minimum Trip Count         : 6                    
;*      Known Maximum Trip Count         : 6                    
;*      Known Max Trip Count Factor      : 6
;*      Loop Carried Dependency Bound(^) : 6
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 4
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     1        0     
;*      .S units                     1        0     
;*      .D units                     1        3     
;*      .M units                     0        0     
;*      .X cross paths               0        0     
;*      .T address paths             0        4*    
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        0     (.L or .S unit)
;*      Addition ops (.LSD)          6        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        0     
;*      Bound(.L .S .D .LS .LSD)     3        1     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 6  Schedule found with 2 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |   ****                         |     ***                        |
;*       1: |   *****                        |     ***                        |
;*       2: |*  ****                         |    ****                        |
;*       3: |   *****                        |     ***                        |
;*       4: |   *****                        |    ****                        |
;*       5: |   *****                        |     ***                        |
;*          +-----------------------------------------------------------------+
;*
;*      Done
;*
;*      Loop will be splooped
;*      Collapsed epilog stages       : 0
;*      Collapsed prolog stages       : 0
;*      Minimum required memory pad   : 0 bytes
;*
;*      Minimum safe trip count       : 1
;*      Min. prof. trip count  (est.) : 2
;*
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.000, max 0.000 }
;*      Mem bank perf. penalty (est.) : 0.0%
;*
;*
;*      Total cycles (est.)         : 6 + min_trip_cnt * 6 = 42        
;*----------------------------------------------------------------------------*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C176:
;*   0              ADD     .L1     A4,A3,A7          ; |161| 
;*   1              CMPLT   .L1     A7,6,A0           ; |161| 
;*   2      [!A0]   MVK     .S1     0xffffffe8,A7     ; |161| 
;*     ||   [ A0]   ZERO    .D1     A7                ; |161| 
;*   3              LDW     .D2T2   *B5++,B4          ; |160|  ^ 
;*     ||           ADD     .L1     A5,A7,A7          ; |161| 
;*   4              ADD     .L1     A6,A7,A7          ; |161| 
;*   5              LDW     .D1T2   *A7,B4            ; |161|  ^ 
;*     ||           ADD     .L1     1,A4,A4           ; |159| 
;*   6              NOP             2
;*   8              STW     .D2T2   B4,*B7++          ; |160|  ^ 
;*     ||           ADD     .L1     4,A5,A5           ; |159| 
;*   9              NOP             1
;*  10              STW     .D2T2   B4,*B6++          ; |161|  ^ 
;*     ||           SPBR            $C$C176
;*  11              NOP             1
;*  12              ; BRANCHCC OCCURS {$C$C176}       ; |159| 
;*----------------------------------------------------------------------------*
$C$L7:    ; PIPED LOOP PROLOG
;          EXCLUSIVE CPU CYCLES: 7

   [ A1]   SPLOOPD 6       ;12               ; SPRELOAD
||         MVK     .L1     0x1,A3            ; |158| 
||         STDW    .D2T1   A5:A4,*+B8(16)    ; |156| 
||         ZERO    .S1     A4                ; |159| 
||         MVC     .S2     B9,ILC

;** --------------------------------------------------------------------------*
$C$L8:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 6

           SPMASK          L2,D2
||         ADD     .D2     B8,24,B6
||         MVK     .L2     0x4,B8
||         ADD     .L1     A4,A3,A7          ; |161| (P) <0,0> 

           SPMASK          S2,D2
||         STDW    .D2T2   B17:B16,*B5       ; |152| 
||         MVKL    .S2     a_sc,B5
||         CMPLT   .L1     A7,6,A0           ; |161| (P) <0,1> 

           SPMASK          L1,S2
||         MVKH    .S2     a_sc,B5
||         MV      .L1X    B8,A5
|| [ A0]   ZERO    .D1     A7                ; |161| (P) <0,2> 
|| [!A0]   MVK     .S1     0xffffffe8,A7     ; |161| (P) <0,2> 

           SPMASK          S1
||         MV      .S1     A12,A6
||         LDW     .D2T2   *B5++,B4          ; |160| (P) <0,3>  ^ 
||         ADD     .L1     A5,A7,A7          ; |161| (P) <0,3> 

           ADD     .L1     A6,A7,A7          ; |161| (P) <0,4> 

           ADD     .L1     1,A4,A4           ; |159| (P) <0,5> 
||         LDW     .D1T2   *A7,B4            ; |161| (P) <0,5>  ^ 

           NOP             2

           STW     .D2T2   B4,*B7++          ; |160| <0,8>  ^ 
||         ADD     .L1     4,A5,A5           ; |159| <0,8> 

           NOP             1

           SPKERNEL 0,0
||         STW     .D2T2   B4,*B6++          ; |161| <0,10>  ^ 

;** --------------------------------------------------------------------------*
$C$L9:    ; PIPED LOOP EPILOG AND PROLOG
;          EXCLUSIVE CPU CYCLES: 9
           NOP             2

           SPMASKR         ;$C$L9
||         ADD     .S1     1,A3,A3           ; |158| 
||         ZERO    .D1     A4                ; |159| 

           ADD     .L2     4,B8,B8           ; |158| 
|| [ A1]   B       .S2     $C$L9             ; |158| 

           MV      .S1     A6,A12
||         MVKL    .S2     a_sc,B5
||         SUB     .D1     A1,1,A1           ; |158| 

           MVKH    .S2     a_sc,B5
||         MV      .L1X    B8,A5

           MV      .S1     A12,A6
||         MVK     .L2     0x6,B4            ; |159| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L9}         ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKL    .S1     a_sc,A3
           MVK     .S1     0x24,A31          ; |166| 
           MVKH    .S1     a_sc,A3

           SUB     .L1     A3,4,A10
||         STW     .D2T1   A31,*+SP(16)
||         ZERO    .S1     A15
||         SUB     .L2X    A12,4,B13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *++B13,B4         ; |168| 
||         LDW     .D1T1   *++A10,A3         ; |168| 

           CALL    .S1     pow               ; |168| 
           ADDKPC  .S2     $C$RL11,B3,2      ; |168| 

           SPDP    .S1     A3,A5:A4          ; |168| 
||         SPDP    .S2     B4,B5:B4          ; |168| 

           NOP             1
$C$RL11:   ; CALL OCCURS {pow} {0}           ; |168| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |168| 
           DPSP    .L1     A5:A4,A3          ; |168| 
           ZERO    .L1     A5
           MVKH    .S1     0x38100000,A5
           NOP             1
           ADD     .L1X    A15,B4,A4         ; |168| 
           STW     .D1T1   A3,*A4            ; |168| 
           LDW     .D2T2   *B13,B4           ; |169| 
           MVKL    .S1     0xa639b,A4
           MVKH    .S1     0xa639b,A4
           NOP             2
           SPDP    .S2     B4,B7:B6          ; |169| 
           NOP             1
           CMPGTDP .S2X    B7:B6,A5:A4,B0    ; |169| 
           NOP             1

   [!B0]   B       .S1     $C$L11            ; |169| 
|| [!B0]   LDW     .D1T1   *A10,A3           ; |169| 

   [ B0]   CALL    .S1     powsp             ; |169| 
|| [ B0]   LDW     .D1T1   *A10,A4           ; |169| 

   [!B0]   CALL    .S1     pow               ; |169| 
           NOP             2
   [!B0]   SPDP    .S1     A3,A5:A4          ; |169| 
           ; BRANCHCC OCCURS {$C$L11}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL12,B3,0      ; |169| 
$C$RL12:   ; CALL OCCURS {powsp} {0}         ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S2     $C$L12            ; |169| 
||         MVKL    .S1     output,A14

           SPDP    .S1     A4,A5:A4          ; |169| 
           NOP             1

           MVKH    .S1     output,A14
||         DPSP    .L1     A5:A4,A3          ; |169| 

           LDW     .D1T1   *+A14(4),A4       ; |169| 
           NOP             1
           ; BRANCH OCCURS {$C$L12}          ; |169| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 2
           DADD    .L2     0,B7:B6,B5:B4     ; |169| 
           ADDKPC  .S2     $C$RL13,B3,0      ; |169| 
$C$RL13:   ; CALL OCCURS {pow} {0}           ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKL    .S1     output,A14
           MVKH    .S1     output,A14

           DPSP    .L1     A5:A4,A3          ; |169| 
||         LDW     .D1T1   *+A14(4),A4       ; |169| 

           NOP             1
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 10
           NOP             3
           ADD     .L1     A15,A4,A4         ; |169| 

           STW     .D1T1   A3,*A4            ; |169| 
||         CALL    .S1     powsp_c           ; |170| 

           LDW     .D1T1   *A10,A4           ; |170| 
||         LDW     .D2T2   *B13,B4           ; |170| 

           ADDKPC  .S2     $C$RL14,B3,3      ; |170| 
$C$RL14:   ; CALL OCCURS {powsp_c} {0}       ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 144

           ZERO    .L2     B27
||         ZERO    .S2     B22
||         LDW     .D1T2   *+A14(8),B4       ; |170| 

           MVKL    .S2     0x3e436581,B31
           ZERO    .L1     A6                ; |83| 
           ZERO    .L1     A7
           LDW     .D2T2   *+SP(12),B29
           ADD     .L2X    A15,B4,B4         ; |170| 
           STW     .D2T1   A4,*B4            ; |170| 
           LDW     .D1T1   *A10,A8           ; |171| 
           MVKH    .S2     0x3e436581,B31
           SET     .S1     A7,0x14,0x1d,A7
           MVKL    .S1     0xbe6bd0fc,A30
           MVKH    .S1     0xbe6bd0fc,A30
           ABSSP   .S1     A8,A9             ; |176| 
           SPDP    .S1     A9,A5:A4          ; |83| 
           MVKL    .S2     0xbe804d66,B30
           RCPDP   .S1     A5:A4,A5:A4       ; |83| 
           MVKH    .S2     0xbe804d66,B30

           CLR     .S1     A5,0,16,A19       ; |83| 
||         ZERO    .L1     A4                ; |83| 

           MV      .L1     A19,A5            ; |83| 
           MPYSPDP .M1     A9,A5:A4,A5:A4    ; |83| 
           MVKL    .S2     0x3fe62e42,B7
           MVK     .S1     0xfffffc01,A3
           MVKL    .S2     0xfefa39ec,B6
           MVKL    .S1     0x3eaaa872,A29
           MVKH    .S2     0x3fe62e42,B7
           MVKH    .S1     0x3eaaa872,A29
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |83| 
           MVKH    .S2     0xfefa39ec,B6
           MVKL    .S1     logtable,A27
           DPSP    .L1     A5:A4,A16         ; |83| 
           MVKH    .S1     logtable,A27
           EXTU    .S1     A19,1,21,A31      ; |83| 
           ADD     .S1     A3,A31,A6         ; |83| 
           MPYSP   .M1     A16,A16,A18       ; |83| 
           INTDP   .L1     A6,A7:A6          ; |83| 
           MPYSP   .M2X    B31,A16,B5        ; |83| 
           EXTU    .S1     A19,12,29,A28     ; |83| 
           MPYSP   .M1     A30,A18,A3        ; |83| 
           MPYSP   .M1     A18,A18,A17       ; |83| 
           FADDSP  .L2     B30,B5,B4         ; |83| 
           MPYSP   .M1     A18,A16,A16       ; |83| 
           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |83| 
           FADDSP  .L2X    A3,B4,B4          ; |83| 
           LDDW    .D1T1   *+A27[A28],A7:A6  ; |83| 
           MPYSP   .M1     A29,A16,A16       ; |83| 
           MPYSP   .M2X    A17,B4,B5         ; |83| 
           ZERO    .L1     A21
           LDW     .D2T1   *+SP(16),A1       ; |192| 
           MPYSP   .M2X    B29,A18,B4        ; |83| 
           FADDSP  .L2X    B5,A16,B5         ; |83| 
           FSUBDP  .L1X    A7:A6,B7:B6,A7:A6 ; |83| 
           LDW     .D2T2   *B13,B17          ; |171| 
           FADDSP  .L2     B5,B4,B4          ; |83| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |83| 
           MVKL    .S2     0x41b8aa3b,B28
           SPDP    .S2     B4,B5:B4          ; |83| 
           MVKL    .S1     0x3605fdf4,A26
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |83| 
           MVKH    .S2     0x41b8aa3b,B28
           MVKH    .S1     0x3605fdf4,A26
           DPSP    .L2     B5:B4,B4          ; |83| 
           MVKL    .S1     0x42b17218,A3
           MVKH    .S1     0x42b17218,A3
           CMPGTSP .S1X    A9,B11,A0         ; |85| 
   [ A0]   MV      .L2X    A3,B4             ; |86| 
           MPYSP   .M2     B17,B4,B16        ; |177| 
           MVKH    .S2     0xbf000000,B27
           MVKL    .S1     0x3effffff,A25
           CMPEQSP .S2X    A9,B10,B0         ; |178| 
   [ B0]   ZERO    .L2     B16
           MPYSP   .M2     B28,B16,B5        ; |116| 
           MVKL    .S2     0x3d317000,B26
           SPINT   .L2     B17,B20           ; |168| 
           MVKH    .S2     0x3d317000,B26
           FADDSP  .L2     B12,B5,B4         ; |116| 
           MVKL    .S2     0x3e2abce4,B25
           MVKH    .S2     0x3e2abce4,B25
           SPTRUNC .L2     B4,B18            ; |116| 
           MVKL    .S2     kTable,B23
           INTSP   .L1X    B20,A22           ; |170| 
           CMPLTSP .S2     B5,B27,B0         ; |117| 
   [ B0]   SUB     .L2     B18,1,B18         ; |118| 
           INTSP   .L2     B18,B5            ; |137| 
           MVKH    .S2     kTable,B23
           MVKH    .S2     0xfff00000,B22
           SPDP    .S2X    A8,B9:B8          ; |170| 
           MPYSP   .M2     B26,B5,B4         ; |137| 
           MVK     .S2     0x72,B2
           MPYSP   .M1X    A26,B5,A3         ; |137| 
           MVKH    .S1     0x3effffff,A25
           FSUBSP  .L2     B16,B4,B4         ; |137| 
           MVKL    .S2     0x42b17218,B1
           MVKL    .S1     0x3f7ffffe,A24
           FSUBSP  .L2X    B4,A3,B5          ; |137| 
           MVKH    .S2     0x42b17218,B1
           MVKH    .S1     0x3f7ffffe,A24
           MPYSP   .M2     B5,B5,B6          ; |137| 
           MVKL    .S1     jTable,A23
           MVKH    .S1     jTable,A23
           INTSP   .L2     B20,B30           ; |183| 
           MPYSP   .M2     B6,B5,B7          ; |137| 
           CMPLTSP .S1X    B16,A13,A0        ; |145| 
           EXTU    .S2     B18,28,30,B24     ; |137| 
           SHL     .S2     B18,16,B21        ; |137| 
           MPYSP   .M2     B25,B7,B4         ; |137| 
           MPYSP   .M1X    A25,B6,A5         ; |137| 
           AND     .L1X    3,B18,A4          ; |137| 
           AND     .L2     B22,B21,B18       ; |137| 
           MPYSP   .M1X    A24,B5,A6         ; |137| 

           FADDSP  .L1X    A5,B4,A7          ; |137| 
||         LDDW    .D2T2   *+B23[B24],B5:B4  ; |137| 
||         LDDW    .D1T1   *+A23[A4],A5:A4   ; |137| 

           EXTU    .S2     B20,31,31,B22     ; |170| 
           EXTU    .S2     B16,1,24,B24      ; |140| 
           FADDSP  .L1     A7,A6,A3          ; |137| 
           ZERO    .L1     A7:A6             ; |183| 

           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |137| 
||         SPDP    .S1X    B17,A5:A4         ; |187| 
||         ZERO    .L2     B5:B4             ; |170| 

           CMPLTDP .S2     B9:B8,B5:B4,B23   ; |170| 

           FADDSP  .L2X    B10,A3,B19        ; |137| 
||         CMPEQSP .S1X    B17,A22,A3        ; |170| 

           ZERO    .L2     B9:B8             ; |187| 
||         SPDP    .S2     B17,B5:B4         ; |187| 

           ADD     .D2     B18,B7,B7         ; |137| 
||         CMPLTDP .S2X    A5:A4,B9:B8,B21   ; |187| 

           SPDP    .S1     A8,A5:A4          ; |183| 
||         MPYSPDP .M2     B19,B7:B6,B19:B18 ; |137| 

           SPDP    .S2X    A8,B7:B6          ; |183| 
           ZERO    .L2     B9:B8             ; |188| 

           MVK     .L1     0x1,A3            ; |166| 
||         AND     .L2X    A3,B23,B23        ; |170| 

           AND     .L2     B22,B23,B0        ; |170| 
||         CMPLTDP .S2X    B7:B6,A7:A6,B31   ; |183| 

   [ B0]   ADD     .S1     -2,A3,A3
||         CMPLTU  .L2     B24,B2,B0         ; |140| 
||         ZERO    .L1     A7:A6             ; |187| 
||         XOR     .D2     1,B21,B7          ; |187| 

           INTSP   .L1     A3,A8             ; |181| 
||         CMPEQDP .S1     A5:A4,A7:A6,A3    ; |187| 
||         CMPEQSP .S2     B17,B30,B6        ; |183| 

           CMPLTDP .S2     B5:B4,B9:B8,B18   ; |188| 
||         DPSP    .L2     B19:B18,B9        ; |137| 
||         XOR     .D2     1,B6,B6           ; |183| 

           AND     .L1X    A3,B7,A2          ; |187| 

   [ B0]   FADDSP  .L2     B10,B16,B9        ; |141| 
||         CMPGTSP .S2     B16,B1,B0         ; |150| 
||         AND     .D2X    A3,B18,B1         ; |188| 
||         SET     .S1     A21,0x0,0x1e,A3

           ADDAW   .D1     A14,3,A21
           LDW     .D1T1   *A21,A20          ; |171| 

   [ A0]   ZERO    .L2     B9
||         SUB     .L1     A1,1,A0           ; |166| 

   [ B0]   MV      .L2     B11,B9            ; |151| 
||         AND     .S2     B6,B31,B0         ; |183| 
|| [ B1]   LDDW    .D2T2   *+SP(40),B7:B6    ; |188| 

           MPYSP   .M2X    B9,A8,B8          ; |181| 
           STW     .D2T1   A0,*+SP(16)       ; |171| 
           ADD     .L1     A15,A20,A4        ; |171| 
   [!A0]   MV      .L2X    A14,B13
   [ B0]   MV      .L2X    A3,B8             ; |184| 

   [ A2]   ZERO    .S2     B8
|| [ B1]   DPSP    .L2     B7:B6,B8          ; |188| 
|| [ A0]   B       .S1     $C$L10            ; |166| 

           ZERO    .L2     B7:B6             ; |191| 
           CMPEQDP .S2     B5:B4,B7:B6,B0    ; |191| 
           ADD     .L1     4,A15,A15         ; |172| 
   [ B0]   MV      .L2     B10,B8            ; |192| 

   [!A0]   CALL    .S1     powsp_v           ; |175| 
||         STW     .D1T2   B8,*A4            ; |171| 

           ; BRANCHCC OCCURS {$C$L10}        ; |166| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T1   *+B13(16),A6      ; |175| 
           MVKL    .S1     a_sc,A4
           MVKH    .S1     a_sc,A4
           MVK     .S2     0x24,B6           ; |175| 

           MV      .L2X    A12,B4            ; |175| 
||         ADDKPC  .S2     $C$RL15,B3,0      ; |175| 

$C$RL15:   ; CALL OCCURS {powsp_v} {0}       ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           LDW     .D2T1   *B13,A4           ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVK     .S1     0x24,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0xeb1c432d,B6

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .S1     0x24,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A14,A4           ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .S1     0x24,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL18:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xeb1c432d,B6
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0xeb1c432d,B6

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         LDW     .D1T2   *A11,B4           ; |69| 
||         MVKH    .S2     0x3f1a36e2,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A14,A4           ; |69| 
||         MVK     .S1     0x24,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL19:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4

           ADD     .L2     4,B4,B4
||         MVKL    .S2     fcn_pass,B5

           LDW     .D2T2   *B4,B0            ; |72| 
           MVKH    .S2     fcn_pass,B5
           STW     .D2T2   B4,*+SP(28)
           ADD     .L2     8,B5,B4
           STW     .D2T1   A4,*+B5(16)       ; |69| 

   [!B0]   MVKL    .S1     all_pass,A3
|| [!B0]   B       .S2     $C$L13            ; |72| 
|| [!B0]   ZERO    .L1     A4                ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |179| 
|| [!B0]   MVKH    .S1     all_pass,A3
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

           STW     .D2T2   B4,*+SP(32)       ; |69| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             2
           ; BRANCHCC OCCURS {$C$L13}        ; |72| 
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
           CALL    .S1     print_test_results ; |179| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |179| 
||         ADDKPC  .S2     $C$RL20,B3,0      ; |179| 

$C$RL20:   ; CALL OCCURS {print_test_results} {0}  ; |179| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     b_ext,A3
           MVKH    .S1     b_ext,A3
           ZERO    .L1     A4
           MV      .L2X    A3,B4             ; |183| 

           MV      .L2X    A3,B13            ; |183| 
||         MVKL    .S1     a_ext,A3

           MVKH    .S1     a_ext,A3
           SET     .S1     A4,0x17,0x17,A4

           MV      .L2X    A3,B5             ; |182| 
||         STW     .D2T1   A4,*B4            ; |183| 

           STW     .D2T1   A4,*B5            ; |182| 
||         MV      .L1     A3,A10            ; |182| 
||         ZERO    .D1     A15
||         MVK     .S1     0xed,A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |185| 
||         LDW     .D1T1   *A10,A3           ; |185| 

           CALL    .S1     pow               ; |185| 
           ADDKPC  .S2     $C$RL21,B3,2      ; |185| 

           SPDP    .S1     A3,A5:A4          ; |185| 
||         SPDP    .S2     B4,B5:B4          ; |185| 

           NOP             1
$C$RL21:   ; CALL OCCURS {pow} {0}           ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           MV      .L2X    A14,B4            ; |185| 
           LDW     .D2T2   *B4,B4            ; |185| 
           DPSP    .L1     A5:A4,A3          ; |185| 
           ZERO    .L1     A5
           MVKH    .S1     0x38100000,A5
           NOP             1
           ADD     .L1X    A15,B4,A4         ; |185| 
           STW     .D1T1   A3,*A4            ; |185| 
           LDW     .D2T2   *B13,B6           ; |186| 
           MVKL    .S1     0xa639b,A4
           MVKH    .S1     0xa639b,A4
           NOP             2
           SPDP    .S2     B6,B5:B4          ; |186| 
           NOP             1
           CMPGTDP .S2X    B5:B4,A5:A4,B0    ; |186| 
           NOP             1

   [!B0]   B       .S1     $C$L15            ; |186| 
|| [!B0]   LDW     .D1T1   *A10,A3           ; |186| 

   [ B0]   CALL    .S1     powsp             ; |186| 
|| [ B0]   LDW     .D1T1   *A10,A4           ; |186| 

   [!B0]   CALL    .S1     pow               ; |186| 
           NOP             2
   [!B0]   SPDP    .S1     A3,A5:A4          ; |186| 
           ; BRANCHCC OCCURS {$C$L15}        ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           MV      .L2     B6,B4             ; |186| 
||         ADDKPC  .S2     $C$RL22,B3,0      ; |186| 

$C$RL22:   ; CALL OCCURS {powsp} {0}         ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           BNOP    .S2     $C$L16,1          ; |186| 
||         SPDP    .S1     A4,A5:A4          ; |186| 

           DPSP    .L1     A5:A4,A3          ; |186| 
||         LDW     .D1T1   *+A14(4),A4       ; |186| 

           NOP             3
           ; BRANCH OCCURS {$C$L16}          ; |186| 
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL23,B3,1      ; |186| 
$C$RL23:   ; CALL OCCURS {pow} {0}           ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           DPSP    .L1     A5:A4,A3          ; |186| 
||         LDW     .D1T1   *+A14(4),A4       ; |186| 

           NOP             3
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             1
           ADD     .L1     A15,A4,A4         ; |186| 

           STW     .D1T1   A3,*A4            ; |186| 
||         CALL    .S1     powsp_c           ; |187| 

           LDW     .D1T1   *A10,A4           ; |187| 
||         LDW     .D2T2   *B13,B4           ; |187| 

           ADDKPC  .S2     $C$RL24,B3,3      ; |187| 
$C$RL24:   ; CALL OCCURS {powsp_c} {0}       ; |187| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 165

           MVKL    .S2     0x3e436581,B4
||         LDW     .D2T2   *+SP(12),B30
||         ZERO    .L2     B28
||         LDW     .D1T1   *+A14(8),A3       ; |187| 

           ZERO    .L1     A6                ; |83| 
           ZERO    .L1     A7
           ZERO    .L2     B22
           MVKH    .S2     0x3e436581,B4
           ADD     .L1     A15,A3,A3         ; |187| 
           STW     .D1T1   A4,*A3            ; |187| 
           LDW     .D1T1   *A10,A3           ; |188| 
           SET     .S1     A7,0x14,0x1d,A7
           MVKL    .S2     0xbe804d66,B31
           MVKL    .S1     0xbe6bd0fc,A31
           MVKH    .S1     0xbe6bd0fc,A31
           ABSSP   .S1     A3,A8             ; |176| 
           SPDP    .S1     A8,A5:A4          ; |83| 
           MVKH    .S2     0xbe804d66,B31
           RCPDP   .S1     A5:A4,A5:A4       ; |83| 
           MVKL    .S2     0x3fe62e42,B7

           CLR     .S1     A5,0,16,A16       ; |83| 
||         ZERO    .L1     A4                ; |83| 

           MV      .L1     A16,A5            ; |83| 
           MPYSPDP .M1     A8,A5:A4,A5:A4    ; |83| 
           MVK     .S1     0xfffffc01,A30
           MVKL    .S2     0xfefa39ec,B6
           MVKL    .S1     0x3eaaa872,A29
           MVKH    .S2     0x3fe62e42,B7
           MVKH    .S1     0x3eaaa872,A29
           LDW     .D2T2   *B13,B19          ; |188| 
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |83| 
           MVKH    .S2     0xfefa39ec,B6
           MVKL    .S1     logtable,A27
           DPSP    .L1     A7:A6,A9          ; |83| 
           MVKL    .S2     0x41b8aa3b,B29
           MVKH    .S1     logtable,A27
           EXTU    .S1     A16,1,21,A18      ; |83| 
           MPYSP   .M1     A9,A9,A17         ; |83| 
           ADD     .L1     A30,A18,A4        ; |83| 
           MPYSP   .M2X    B4,A9,B5          ; |83| 
           INTDP   .L1     A4,A5:A4          ; |83| 
           MPYSP   .M1     A31,A17,A20       ; |83| 
           MPYSP   .M1     A17,A9,A19        ; |83| 
           FADDSP  .L2     B31,B5,B4         ; |83| 
           MPYSP   .M1     A17,A17,A18       ; |83| 
           EXTU    .S1     A16,12,29,A28     ; |83| 

           FADDSP  .L2X    A20,B4,B8         ; |83| 
||         MPYSP   .M1     A29,A19,A9        ; |83| 

           FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |83| 
           LDDW    .D1T1   *+A27[A28],A5:A4  ; |83| 
           MPYSP   .M2X    A18,B8,B7         ; |83| 
           MVKL    .S1     0x3605fdf4,A26
           MVKH    .S2     0x41b8aa3b,B29
           MPYSP   .M2X    B30,A17,B6        ; |83| 
           FADDSP  .L2X    B7,A9,B7          ; |83| 
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |83| 
           MVKH    .S1     0x3605fdf4,A26
           FADDSP  .L2     B7,B6,B4          ; |83| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |83| 
           MVKH    .S2     0xbf000000,B28
           SPDP    .S2     B4,B5:B4          ; |83| 
           MVKL    .S1     0x3effffff,A25
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |83| 
           MVKL    .S2     0x3d317000,B27
           SPINT   .L2     B19,B20           ; |168| 
           DPSP    .L2     B5:B4,B4          ; |83| 
           MVKL    .S1     0x42b17218,A4
           MVKH    .S1     0x42b17218,A4
           CMPGTSP .S1X    A8,B11,A0         ; |85| 
   [ A0]   MV      .L2X    A4,B4             ; |86| 
           MPYSP   .M2     B19,B4,B18        ; |177| 
           MVKH    .S2     0x3d317000,B27
           MVKL    .S2     0x3e2abce4,B26
           CMPEQSP .S1X    A8,B10,A2         ; |178| 
   [ A2]   ZERO    .L2     B18
           MPYSP   .M2     B29,B18,B5        ; |116| 
           MVKH    .S2     0x3e2abce4,B26
           MVKL    .S2     kTable,B24
           MVKH    .S2     kTable,B24
           FADDSP  .L2     B12,B5,B4         ; |116| 
           INTSP   .L1X    B20,A22           ; |170| 
           MVKH    .S2     0xfff00000,B22
           SPTRUNC .L2     B4,B6             ; |116| 
           EXTU    .S2     B20,31,31,B21     ; |170| 
           MVK     .S2     0x72,B1
           CMPLTSP .S2     B5,B28,B0         ; |117| 
   [ B0]   SUB     .L2     B6,1,B6           ; |118| 
           INTSP   .L2     B6,B5             ; |137| 
           MVKH    .S1     0x3effffff,A25
           MVKL    .S1     0x3f7ffffe,A24
           MVKH    .S1     0x3f7ffffe,A24
           MPYSP   .M2     B27,B5,B4         ; |137| 
           MVKL    .S1     jTable,A23
           MPYSP   .M1X    A26,B5,A4         ; |137| 
           MVKH    .S1     jTable,A23
           FSUBSP  .L2     B18,B4,B4         ; |137| 
           ZERO    .L1     A30
           CMPEQSP .S1X    B19,A22,A1        ; |170| 
           FSUBSP  .L2X    B4,A4,B5          ; |137| 
           MVKL    .S2     0x42b17218,B31
           MVKH    .S2     0x42b17218,B31
           MPYSP   .M2     B5,B5,B7          ; |137| 
           INTSP   .L2     B20,B30           ; |183| 
           EXTU    .S2     B18,1,24,B2       ; |140| 
           CMPLTSP .S1X    B18,A13,A2        ; |145| 
           MPYSP   .M2     B7,B5,B8          ; |137| 
           CMPLTU  .L2     B2,B1,B0          ; |140| 
           CMPGTSP .S2     B18,B31,B2        ; |150| 
           EXTU    .S2     B6,28,30,B25      ; |137| 
           MPYSP   .M2     B26,B8,B4         ; |137| 
           MPYSP   .M1X    A25,B7,A7         ; |137| 
           AND     .L1X    3,B6,A5           ; |137| 
           LDDW    .D1T1   *+A23[A5],A5:A4   ; |137| 
           MPYSP   .M1X    A24,B5,A6         ; |137| 

           FADDSP  .L1X    A7,B4,A7          ; |137| 
||         LDDW    .D2T2   *+B24[B25],B5:B4  ; |137| 

           SHL     .S2     B6,16,B23         ; |137| 
           SPDP    .S2X    A3,B9:B8          ; |170| 
           FADDSP  .L1     A7,A6,A6          ; |137| 
           AND     .L2     B22,B23,B6        ; |137| 
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |137| 
           SPDP    .S1     A3,A5:A4          ; |183| 

           FADDSP  .L2X    B10,A6,B16        ; |137| 
||         ZERO    .L1     A7:A6             ; |170| 

           CMPLTDP .S1X    B9:B8,A7:A6,A21   ; |170| 

           ADD     .D2     B6,B5,B5          ; |137| 
||         ZERO    .L1     A7:A6             ; |187| 
||         SPDP    .S2     B19,B7:B6         ; |187| 

           MPYSPDP .M2     B16,B5:B4,B17:B16 ; |137| 
||         CMPEQDP .S1     A5:A4,A7:A6,A6    ; |187| 
||         ZERO    .L2     B9:B8             ; |187| 

           SPDP    .S2X    A3,B5:B4          ; |183| 
||         AND     .L1     A1,A21,A3         ; |170| 

           AND     .L1X    B21,A3,A0         ; |170| 
||         MVK     .S1     0x1,A3            ; |166| 
||         CMPLTDP .S2     B7:B6,B9:B8,B22   ; |187| 

   [ A0]   ADD     .L1     -2,A3,A3
||         ZERO    .L2     B7:B6             ; |183| 

           SPDP    .S2     B19,B9:B8         ; |187| 
           CMPLTDP .S2     B5:B4,B7:B6,B6    ; |183| 
           INTSP   .L1     A3,A4             ; |181| 

           DPSP    .L2     B17:B16,B16       ; |137| 
||         CMPEQSP .S2     B19,B30,B4        ; |183| 

           XOR     .L2     1,B4,B5           ; |183| 
||         XOR     .S2     1,B22,B4          ; |187| 

           AND     .L2     B5,B6,B1          ; |183| 
|| [ B0]   FADDSP  .S2     B10,B18,B16       ; |141| 

           AND     .S2X    A6,B4,B0          ; |187| 
           ZERO    .L2     B7:B6             ; |191| 
   [ A2]   ZERO    .L2     B16
   [ B2]   MV      .L2     B11,B16           ; |151| 

           MPYSP   .M2X    B16,A4,B16        ; |181| 
||         ZERO    .L1     A5:A4             ; |188| 

           CMPLTDP .S1X    B9:B8,A5:A4,A3    ; |188| 
           CMPEQDP .S2     B9:B8,B7:B6,B2    ; |191| 

           AND     .L1     A6,A3,A0          ; |188| 
||         SET     .S1     A30,0x0,0x1e,A3

   [ A0]   LDDW    .D2T2   *+SP(40),B5:B4    ; |188| 
           ADDAW   .D1     A14,3,A30
           LDW     .D1T1   *A30,A31          ; |188| 
   [ B1]   MV      .L2X    A3,B16            ; |184| 
   [ B0]   ZERO    .L2     B16
   [ A0]   DPSP    .L2     B5:B4,B16         ; |188| 
           MVKL    .S2     0xc000cccc,B5
           ADD     .L1     A15,A31,A3        ; |188| 
           MVKL    .S2     0xcccccccd,B4
   [ B2]   MV      .L2     B10,B16           ; |192| 
           STW     .D1T2   B16,*A3           ; |188| 
           LDW     .D1T1   *A10,A3           ; |189| 
           MVKH    .S2     0xc000cccc,B5
           MVKH    .S2     0xcccccccd,B4
           LDW     .D2T2   *B13,B29          ; |190| 
           ZERO    .L2     B28
           MPYSPDP .M1X    A3,B5:B4,A5:A4    ; |189| 
           MVKH    .S2     0xbfc00000,B28
           SUB     .L1     A12,1,A1          ; |184| 
           SUB     .L1     A12,1,A12         ; |184| 
           MPYSP   .M2     B28,B29,B4        ; |190| 
           ADD     .L1     4,A15,A15         ; |184| 
   [ A1]   B       .S1     $C$L14            ; |184| 
           DPSP    .L1     A5:A4,A3          ; |189| 
           STW     .D2T2   B4,*++B13         ; |190| 
   [!A1]   MV      .L2X    A14,B13           ; |192| 
           NOP             1
           STW     .D1T1   A3,*++A10         ; |189| 
           ; BRANCHCC OCCURS {$C$L14}        ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           LDW     .D2T2   *+B13(16),B5      ; |192| 
||         CALL    .S1     powsp_v           ; |192| 
||         MVKL    .S2     b_ext,B4

           MVKH    .S2     b_ext,B4
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           MVK     .S2     0xed,B6           ; |192| 

           MV      .L1X    B5,A6             ; |192| 
||         ADDKPC  .S2     $C$RL25,B3,0      ; |192| 

$C$RL25:   ; CALL OCCURS {powsp_v} {0}       ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T2   *B13,B5           ; |66| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7
           MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MV      .L1X    B5,A4             ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .D1     0x9,A8            ; |66| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     fcn_pass,B5

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A14,A4           ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL28:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xeb1c432d,B6
           MVKL    .S2     0x3f1a36e2,B7
           MVKH    .S2     fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           MV      .L1     A11,A3            ; |68| 
||         LDW     .D1T1   *A14,A4           ; |69| 
||         MVKH    .S2     0x3f1a36e2,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL29:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(28),A3       ; |69| 
           LDW     .D2T2   *+SP(32),B5
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L17            ; |72| 
|| [ A0]   LDW     .D2T2   *B5,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |196| 
   [ A0]   ADD     .L2     4,B5,B4
   [!A0]   ZERO    .L1     A4                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
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
           CALL    .S1     print_test_results ; |196| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |196| 
||         ADDKPC  .S2     $C$RL30,B3,0      ; |196| 

$C$RL30:   ; CALL OCCURS {print_test_results} {0}  ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15

           ZERO    .L2     B5                ; |114| 
||         MVKL    .S2     cycle_counts+24,B7

           MVKH    .S2     cycle_counts+24,B7
||         ZERO    .L2     B6                ; |114| 
||         ZERO    .D2     B4                ; |114| 

           MVC     .S2     B6,TSCL           ; |115| 
||         STDW    .D2T2   B5:B4,*B7         ; |114| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVKL    .S1     t_start,A3

           MVKH    .S1     t_start,A3
||         MV      .L2     B6,B9             ; |116| 

           MVC     .S2     TSCL,B6           ; |117| 
||         STDW    .D1T2   B9:B8,*A3         ; |116| 

           MVC     .S2     TSCH,B16          ; |117| 
           ZERO    .L1     A5

           CALL    .S2     gimme_random      ; |206| 
||         MVKH    .S1     0x41a00000,A5

           SUBU    .L2     B6,B8,B7:B6       ; |117| 
||         MVKL    .S1     t_offset,A4

           SUB     .L2     B16,B9,B8         ; |117| 
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         MV      .D2X    A5,B13
||         MVK     .S1     0x80,A3

           ADD     .L2     B8,B7,B7          ; |117| 
||         ZERO    .S2     B4
||         MVKH    .S1     t_offset,A4
||         STDW    .D2T2   B5:B4,*+SP(48)    ; |117| 
||         MV      .L1X    B5,A12

           MV      .L1X    B13,A4            ; |206| 
||         STDW    .D1T2   B7:B6,*A4         ; |117| 
||         MVKH    .S2     0xc1200000,B4
||         STW     .D2T1   A3,*+SP(16)       ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL31,B3,0      ; |206| 
$C$RL31:   ; CALL OCCURS {gimme_random} {0}  ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVKL    .S2     input,B4
           MVKH    .S2     input,B4
           NOP             1
           MV      .L1X    B4,A10            ; |206| 
           LDW     .D1T2   *A10,B4           ; |206| 
           NOP             4
           ADD     .L2X    A12,B4,B4         ; |206| 

           STW     .D2T1   A4,*B4            ; |206| 
||         ZERO    .L2     B4

           MVKH    .S2     0xc1200000,B4

           CALLP   .S2     gimme_random,B3
||         MV      .L1X    B13,A4            ; |207| 

$C$RL32:   ; CALL OCCURS {gimme_random} {0}  ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 166
           LDW     .D1T2   *+A10(4),B4       ; |207| 
           NOP             4
           ADD     .L2X    A12,B4,B4         ; |207| 

           STW     .D2T1   A4,*B4            ; |207| 
||         MVC     .S2     TSCL,B16          ; |122| 

           MVC     .S2     TSCH,B17          ; |122| 

           MV      .D1     A10,A15           ; |122| 
||         ZERO    .L2     B5
||         ZERO    .D2     B4                ; |83| 
||         MVKL    .S2     0x3e436581,B31
||         MVKL    .S1     0xbe6bd0fc,A31
||         SPINT   .L1     A4,A1             ; |168| 

           LDW     .D1T1   *A15,A3           ; |211| 
||         SET     .S2     B5,0x14,0x1d,B5
||         MVKH    .S1     0xbe6bd0fc,A31
||         LDW     .D2T2   *+SP(12),B29
||         ZERO    .L2     B27

           MVKH    .S2     0x3e436581,B31
||         MVK     .S1     0xfffffc01,A19
||         ZERO    .L2     B21

           MVKL    .S2     0xbe804d66,B30
||         MVKL    .S1     0x3eaaa872,A29

           MVKH    .S2     0xbe804d66,B30
||         MVKH    .S1     0x3eaaa872,A29

           MVKL    .S1     logtable,A27
||         MVKL    .S2     0x41b8aa3b,B28
||         INTSP   .L2X    A1,B2             ; |183| 

           ADD     .L1     A12,A3,A3         ; |211| 
||         MVKH    .S1     logtable,A27
||         MVKH    .S2     0x41b8aa3b,B28

           LDW     .D1T1   *A3,A5            ; |211| 
||         MVKL    .S1     0x3fe62e42,A17
||         MVKH    .S2     0xbf000000,B27

           MVKL    .S1     0xfefa39ec,A16
||         MVKL    .S2     0x3d317000,B26

           MVKH    .S1     0x3fe62e42,A17
||         MVKH    .S2     0x3d317000,B26

           MVKH    .S1     0xfefa39ec,A16
||         MVKL    .S2     0x3e2abce4,B25

           MVKL    .S1     0x3605fdf4,A26
||         MVKH    .S2     0x3e2abce4,B25

           ABSSP   .S1     A5,A3             ; |176| 
||         MVKL    .S2     kTable,B23

           SPDP    .S1     A3,A7:A6          ; |83| 
||         MVKH    .S2     kTable,B23

           CMPEQSP .S2X    A3,B10,B0         ; |178| 

           RCPDP   .S1     A7:A6,A7:A6       ; |83| 
||         MVKH    .S2     0xfff00000,B21

           NOP             1

           CLR     .S1     A7,0,16,A18       ; |83| 
||         ZERO    .L1     A6                ; |83| 

           MV      .L1     A18,A7            ; |83| 
||         EXTU    .S1     A18,1,21,A30      ; |83| 

           MPYSPDP .M1     A3,A7:A6,A7:A6    ; |83| 
||         EXTU    .S1     A18,12,29,A28     ; |83| 

           CMPGTSP .S1X    A3,B11,A0         ; |85| 
           MVKH    .S1     0x3605fdf4,A26
           MVKL    .S1     0x3effffff,A25
           MVKH    .S1     0x3effffff,A25
           MVKL    .S1     0x3f7ffffe,A2
           MVKH    .S1     0x3f7ffffe,A2

           FSUBDP  .L1X    A7:A6,B5:B4,A9:A8 ; |83| 
||         MVKL    .S1     jTable,A23

           MVKH    .S1     jTable,A23
           MVKL    .S1     t_start,A14

           DPSP    .L1     A9:A8,A6          ; |83| 
||         MVKH    .S1     t_start,A14

           STDW    .D1T2   B17:B16,*A14
           NOP             2
           MPYSP   .M1     A6,A6,A20         ; |83| 

           MPYSP   .M2X    B31,A6,B4         ; |83| 
||         MVK     .S2     0x72,B31

           NOP             2

           MPYSP   .M1     A31,A20,A22       ; |83| 
||         ZERO    .L1     A31

           FADDSP  .L2     B30,B4,B4         ; |83| 
||         MPYSP   .M1     A20,A6,A19        ; |83| 
||         ADD     .L1     A19,A30,A6        ; |83| 

           MPYSP   .M1     A20,A20,A21       ; |83| 
||         INTDP   .L1     A6,A7:A6          ; |83| 

           NOP             2

           FADDSP  .L2X    A22,B4,B4         ; |83| 
||         MPYSP   .M1     A29,A19,A22       ; |83| 
||         LDDW    .D1T1   *+A27[A28],A19:A18 ; |83| 

           NOP             1
           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |83| 
           MPYSP   .M2X    A21,B4,B5         ; |83| 
           MPYSP   .M2X    B29,A20,B4        ; |83| 
           CMPEQSP .S2X    A4,B2,B29         ; |183| 

           FSUBDP  .L1     A19:A18,A7:A6,A7:A6 ; |83| 
||         MVKL    .S2     output+12,B2

           FADDSP  .L2X    B5,A22,B5         ; |83| 
||         MVKH    .S2     output+12,B2

           NOP             1
           FADDDP  .L1     A7:A6,A9:A8,A7:A6 ; |83| 
           FADDSP  .L2     B5,B4,B4          ; |83| 
           NOP             2
           SPDP    .S2     B4,B5:B4          ; |83| 
           NOP             1

           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |83| 
||         MVKL    .S1     0x42b17218,A6

           MVKH    .S1     0x42b17218,A6
           NOP             1
           DPSP    .L2     B5:B4,B4          ; |83| 
           NOP             3
   [ A0]   MV      .L2X    A6,B4             ; |86| 
           MPYSP   .M2X    A4,B4,B22         ; |177| 
           NOP             3
   [ B0]   ZERO    .L2     B22

           MPYSP   .M2     B28,B22,B5        ; |116| 
||         EXTU    .S2     B22,1,24,B1       ; |140| 

           MVKL    .S2     0x42b17218,B28
           MVKH    .S2     0x42b17218,B28
           NOP             1

           FADDSP  .L2     B12,B5,B4         ; |116| 
||         CMPLTSP .S2     B5,B27,B0         ; |117| 

           NOP             2
           SPTRUNC .L2     B4,B18            ; |116| 
           NOP             3

   [ B0]   SUB     .S2     B18,1,B18         ; |118| 
||         CMPLTU  .L2     B1,B31,B0         ; |140| 

           INTSP   .L2     B18,B5            ; |137| 
||         EXTU    .S2     B18,28,30,B24     ; |137| 

           AND     .L1X    3,B18,A24         ; |137| 
||         SHL     .S2     B18,16,B20        ; |137| 

           LDDW    .D1T1   *+A23[A24],A7:A6  ; |137| 
||         AND     .L2     B21,B20,B18       ; |137| 

           NOP             1
           MPYSP   .M2     B26,B5,B4         ; |137| 
           MPYSP   .M1X    A26,B5,A3         ; |137| 
           NOP             2
           FSUBSP  .L2     B22,B4,B4         ; |137| 
           NOP             2
           FSUBSP  .L2X    B4,A3,B5          ; |137| 
           NOP             2
           MPYSP   .M2     B5,B5,B4          ; |137| 
           MPYSP   .M1X    A2,B5,A3          ; |137| 
           CMPLTSP .S1X    B22,A13,A2        ; |145| 
           NOP             1
           MPYSP   .M2     B4,B5,B6          ; |137| 

           MPYSP   .M1X    A25,B4,A8         ; |137| 
||         SPDP    .S2X    A5,B5:B4          ; |170| 

           NOP             2

           MPYSP   .M2     B25,B6,B8         ; |137| 
||         LDDW    .D2T2   *+B23[B24],B7:B6  ; |137| 

           NOP             3
           FADDSP  .L2X    A8,B8,B19         ; |137| 

           FMPYDP  .M2X    A7:A6,B7:B6,B9:B8 ; |137| 
||         ZERO    .L1     A7:A6             ; |170| 

           NOP             1
           FADDSP  .L2X    B19,A3,B19        ; |137| 

           INTSP   .L1     A1,A6             ; |170| 
||         CMPLTDP .S2X    B5:B4,A7:A6,B23   ; |170| 

           ADD     .D2     B18,B9,B9         ; |137| 

           SPDP    .S2X    A4,B7:B6          ; |187| 
||         FADDSP  .L2     B10,B19,B19       ; |137| 

           NOP             1

           CMPEQSP .S1     A4,A6,A8          ; |170| 
||         ZERO    .L1     A7:A6             ; |188| 
||         SPDP    .S2X    A4,B5:B4          ; |187| 

           MPYSPDP .M2     B19,B9:B8,B21:B20 ; |137| 
||         AND     .L1X    A8,B23,A3         ; |170| 
||         EXTU    .S1     A1,31,31,A8       ; |170| 

           ZERO    .L2     B19:B18           ; |187| 
||         AND     .L1     A8,A3,A0          ; |170| 
||         MVK     .D1     0x1,A3            ; |166| 
||         SPDP    .S2X    A5,B9:B8          ; |183| 
||         SPDP    .S1     A5,A5:A4          ; |183| 

           CMPLTDP .S2     B7:B6,B19:B18,B24 ; |187| 
|| [ A0]   ADD     .L1     -2,A3,A3
||         LDW     .D2T2   *B2,B18           ; |211| 

           ZERO    .L2     B7:B6             ; |183| 
           CMPLTDP .S2X    B5:B4,A7:A6,B30   ; |188| 
           ZERO    .L1     A7:A6             ; |187| 

           INTSP   .L2X    A3,B23            ; |181| 
||         CMPLTDP .S1X    A5:A4,B7:B6,A3    ; |183| 

           DPSP    .L2     B21:B20,B19       ; |137| 
||         CMPEQDP .S2X    B9:B8,A7:A6,B8    ; |187| 
||         XOR     .D2     1,B29,B21         ; |183| 

           XOR     .D2     1,B24,B9          ; |187| 
||         ZERO    .L2     B7:B6             ; |191| 

   [ B0]   FADDSP  .L2     B10,B22,B19       ; |141| 
||         CMPGTSP .S2     B22,B28,B0        ; |150| 
||         AND     .D2     B8,B9,B1          ; |187| 
||         AND     .L1X    B21,A3,A0         ; |183| 
||         SET     .S1     A31,0x0,0x1e,A3

           CMPEQDP .S2     B5:B4,B7:B6,B2    ; |191| 
||         ADD     .D2X    A12,B18,B27       ; |211| 

           NOP             1
   [ A2]   ZERO    .L2     B19

   [ B0]   MV      .L2     B11,B19           ; |151| 
||         AND     .S2     B8,B30,B0         ; |188| 

           MPYSP   .M2     B19,B23,B19       ; |181| 
|| [ B0]   LDDW    .D2T2   *+SP(40),B9:B8    ; |188| 

           NOP             3
   [ A0]   MV      .L2X    A3,B19            ; |184| 

   [ B1]   ZERO    .S2     B19
|| [ B0]   DPSP    .L2     B9:B8,B19         ; |188| 

           NOP             3
   [ B2]   MV      .L2     B10,B19           ; |192| 

           STW     .D2T2   B19,*B27          ; |211| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S1     t_offset,A3
||         LDW     .D2T1   *+SP(16),A29      ; |128| 
||         MVKL    .S2     t_stop,B26

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     t_stop,B26

           LDDW    .D1T2   *A3,B7:B6         ; |130| 
||         MVKL    .S1     cycle_counts+24,A30

           MVKH    .S1     cycle_counts+24,A30
||         STDW    .D2T2   B9:B8,*B26        ; |128| 

           LDDW    .D1T1   *A30,A7:A6        ; |130| 
||         MV      .L1     A30,A10           ; |130| 

           SUB     .L1     A29,1,A0          ; |204| 
           STW     .D2T1   A0,*+SP(16)       ; |130| 
           ADDU    .L2     B6,B16,B5:B4      ; |130| 

           ADD     .S2     B5,B7,B7          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .L2     B7,B17,B6         ; |130| 
|| [ A0]   B       .S1     $C$L18            ; |204| 

           SUB     .L2     B9,B6,B5          ; |130| 
||         EXT     .S2     B5,24,24,B6       ; |130| 
|| [ A0]   CALL    .S1     gimme_random      ; |206| 
||         ADDU    .L1X    A6,B4,A5:A4       ; |130| 

           ADD     .L2     B5,B6,B4          ; |130| 
||         ADD     .L1     A5,A7,A3          ; |130| 

           NOP             1

           ADD     .L1X    A3,B4,A5          ; |130| 
|| [ A0]   ZERO    .L2     B4

           STDW    .D1T1   A5:A4,*A10        ; |130| 
||         ADD     .L1     4,A12,A12         ; |204| 
|| [ A0]   MV      .S1X    B13,A4            ; |206| 
|| [ A0]   MVKH    .S2     0xc1200000,B4

           ; BRANCHCC OCCURS {$C$L18}        ; |204| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALLP   .S2     __c6xabi_fltllif,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |135| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(48),B5:B4
           MV      .L2X    A10,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B10
           MV      .L2X    A12,B31           ; |114| 

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S2     t_offset,B13

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 
||         MVKH    .S2     t_offset,B13

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L2X    A15,B12

           ADD     .L1     4,A15,A10
||         MV      .S1X    B4,A15            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 11

           LDW     .D2T2   *B12,B4           ; |219| 
||         LDW     .D1T1   *A10,A3           ; |219| 

           NOP             4

           ADD     .L2X    A12,B4,B4         ; |219| 
||         ADD     .L1     A12,A3,A3         ; |219| 
||         CALL    .S1     powf              ; |219| 

           LDW     .D2T1   *B4,A4            ; |219| 
||         LDW     .D1T2   *A3,B4            ; |219| 

           ADDKPC  .S2     $C$RL35,B3,3      ; |219| 
$C$RL35:   ; CALL OCCURS {powf} {0}          ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S1     output,A3
||         SUB     .L1     A15,1,A0          ; |218| 
||         SUB     .D1     A15,1,A15         ; |218| 

           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A3            ; |219| 
   [ A0]   BNOP    .S1     $C$L19,3          ; |218| 

           ADD     .L1     A12,A3,A3         ; |219| 
||         ADD     .S1     4,A12,A12         ; |218| 

           STW     .D1T1   A4,*A3            ; |219| 
           ; BRANCHCC OCCURS {$C$L19}        ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B9:B8        ; |130| 

           MVKL    .S2     t_stop,B11
           MV      .L2     B4,B7             ; |128| 
           MVKH    .S2     t_stop,B11
           NOP             1
           ADDU    .L1X    B8,A4,A7:A6       ; |130| 

           ADD     .L1X    A7,B9,A31         ; |130| 
||         LDDW    .D2T2   *B10,B9:B8        ; |130| 
||         MV      .S1     A6,A3             ; |130| 

           STDW    .D2T2   B7:B6,*B11        ; |128| 

           SUBU    .L2X    B6,A3,B5:B4       ; |130| 
||         ADD     .L1     A31,A5,A3         ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         SUB     .L2X    B7,A3,B31         ; |130| 

           ADDU    .L2     B8,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B8        ; |130| 

           ADD     .L2     B5,B9,B5          ; |130| 
           ADD     .L2     B5,B8,B5          ; |130| 
           ADDKPC  .S2     $C$RL36,B3,0      ; |130| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
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

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(48),B5:B4    ; |130| 
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 
           STDW    .D2T2   B5:B4,*B13        ; |117| 

           LDW     .D1T1   *A10,A3           ; |227| 
||         LDW     .D2T2   *B12,B4           ; |227| 

           MVK     .S2     0x80,B29
           LDW     .D2T1   *+SP(20),A12      ; |117| 
           STW     .D2T2   B29,*+SP(12)      ; |117| 
           ZERO    .L1     A15
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 10
           NOP             4

           CALL    .S1     powsp             ; |227| 
||         ADD     .L2X    A15,B4,B4         ; |227| 
||         ADD     .L1     A15,A3,A3         ; |227| 

           LDW     .D1T2   *A3,B4            ; |227| 
||         LDW     .D2T1   *B4,A4            ; |227| 

           NOP             3
           ADDKPC  .S2     $C$RL38,B3,0      ; |227| 
$C$RL38:   ; CALL OCCURS {powsp} {0}         ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(12),B4       ; |227| 
||         LDW     .D1T1   *A12,A3           ; |227| 

           NOP             4

           SUB     .L1X    B4,1,A0           ; |226| 
||         SUB     .L2     B4,1,B4           ; |226| 
||         ADD     .S1     A15,A3,A3         ; |227| 
||         ADD     .D1     4,A15,A15         ; |226| 

   [ A0]   BNOP    .S1     $C$L20,3          ; |226| 
||         STW     .D2T2   B4,*+SP(12)       ; |227| 
||         STW     .D1T1   A4,*A3            ; |227| 

   [ A0]   LDW     .D1T1   *A10,A3           ; |227| 
   [ A0]   LDW     .D2T2   *B12,B4           ; |227| 
           ; BRANCHCC OCCURS {$C$L20}        ; |226| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
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
||         MV      .S2     B11,B4            ; |130| 

           ADD     .L2     B31,B5,B7         ; |130| 
           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL39,B3,0      ; |130| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
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

$C$RL40:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(48),B5:B4
           ADDAD   .D2     B10,1,B11
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B11        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A14        ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 
           SUBU    .L2     B5,B6,B9:B8       ; |117| 

           EXT     .S2     B9,24,24,B5       ; |117| 
||         SUB     .L2     B4,B7,B4          ; |117| 

           ADD     .L2     B4,B5,B9          ; |117| 
           STDW    .D2T2   B9:B8,*B13        ; |117| 

           LDW     .D1T1   *A10,A3           ; |235| 
||         LDW     .D2T2   *B12,B4           ; |235| 

           MVK     .S2     0x80,B30
           LDW     .D2T1   *+SP(24),A12      ; |117| 
           STW     .D2T2   B30,*+SP(12)      ; |117| 
           ZERO    .L1     A15
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 10
           NOP             4

           CALL    .S1     powsp_c           ; |235| 
||         ADD     .L2X    A15,B4,B4         ; |235| 
||         ADD     .L1     A15,A3,A3         ; |235| 

           LDW     .D1T2   *A3,B4            ; |235| 
||         LDW     .D2T1   *B4,A4            ; |235| 

           NOP             3
           ADDKPC  .S2     $C$RL41,B3,0      ; |235| 
$C$RL41:   ; CALL OCCURS {powsp_c} {0}       ; |235| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(12),B4       ; |235| 
||         LDW     .D1T1   *A12,A3           ; |235| 

           NOP             4

           SUB     .L1X    B4,1,A0           ; |234| 
||         SUB     .L2     B4,1,B4           ; |234| 
||         ADD     .S1     A15,A3,A3         ; |235| 
||         ADD     .D1     4,A15,A15         ; |234| 

   [ A0]   BNOP    .S1     $C$L21,3          ; |234| 
||         STW     .D2T2   B4,*+SP(12)       ; |235| 
||         STW     .D1T1   A4,*A3            ; |235| 

   [ A0]   LDW     .D1T1   *A10,A3           ; |235| 
   [ A0]   LDW     .D2T2   *B12,B4           ; |235| 
           ; BRANCHCC OCCURS {$C$L21}        ; |234| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MV      .L2     B13,B4            ; |128| 
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B9:B8         ; |130| 
           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           MV      .L2     B5,B7             ; |128| 
           NOP             2
           ADDU    .L2X    B8,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B9,B8          ; |130| 
||         SUBU    .L2     B6,B4,B5:B4       ; |130| 

           ADD     .D2X    B8,A5,B8          ; |130| 
||         CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B5,24,24,B9       ; |130| 
||         ADDU    .L2     B16,B4,B5:B4      ; |130| 

           SUB     .L2     B7,B8,B8          ; |130| 
||         ADD     .S2     B5,B17,B5         ; |130| 

           ADD     .L2     B8,B9,B8          ; |130| 

           ADD     .L2     B5,B8,B5          ; |130| 
||         MVKL    .S2     t_stop,B8

           MVKH    .S2     t_stop,B8

           STDW    .D2T2   B7:B6,*B8         ; |128| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL42,B3,0      ; |130| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 112
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(48),B5:B4
           ADDAD   .D2     B11,1,B13
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A14        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     t_offset,A3

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKH    .S1     t_offset,A3

           EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           MVKL    .S1     output,A15
||         LDW     .D2T1   *B12,A4           ; |242| 
||         MV      .L2X    A3,B10            ; |117| 
||         ADD     .S2     B5,B7,B7          ; |117| 

           MVKH    .S1     output,A15
||         MV      .L2X    A10,B9            ; |117| 
||         STDW    .D2T2   B7:B6,*B10        ; |117| 
||         MVK     .S2     0x80,B6           ; |242| 

           CALLP   .S2     powsp_v,B3
||         LDW     .D1T1   *+A15(16),A6      ; |242| 
||         LDW     .D2T2   *B9,B4            ; |242| 

$C$RL44:   ; CALL OCCURS {powsp_v} {0}       ; |242| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A9:A8        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           MVK     .S1     16,A10
           ADD     .L1X    B13,A10,A10
           MVKL    .S1     t_stop,A3

           LDDW    .D1T1   *A10,A17:A16      ; |130| 
||         MVKH    .S1     t_stop,A3

           ADDU    .L1X    B6,A8,A7:A6       ; |130| 

           MV      .L2     B4,B9             ; |128| 
||         MV      .S2X    A3,B4             ; |128| 
||         ADD     .L1X    A7,B7,A3          ; |130| 

           SUBU    .L1X    B8,A6,A5:A4       ; |130| 

           ADD     .L1     A3,A9,A5          ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           SUB     .S1X    B9,A5,A6          ; |130| 
||         ADDU    .L1     A16,A4,A5:A4      ; |130| 

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A6,A3,A5          ; |130| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL45:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL46:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6

           STDW    .D1T1   A5:A4,*A10        ; |130| 
||         MVKH    .S2     0x3f1a36e2,B7

           LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL47:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKL    .S2     fcn_pass,B10
           MVKH    .S2     0x3f1a36e2,B7
           MVKH    .S2     0xeb1c432d,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S2     fcn_pass,B10

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A15(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL48:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL49:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3f1a36e2,B7
           MVKL    .S2     0xeb1c432d,B6
           MVKH    .S2     0x3f1a36e2,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *A11,B4           ; |69| 
||         MVKH    .S2     0xeb1c432d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL50:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(28),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(32),B4
           NOP             3

   [!B0]   B       .S1     $C$L22            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L22}        ; |72| 
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
   [ A0]   B       .S1     $C$L23            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |248| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L23}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |248| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |248| 
||         ADDKPC  .S2     $C$RL51,B3,0      ; |248| 

$C$RL51:   ; CALL OCCURS {print_test_results} {0}  ; |248| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |249| 

$C$RL52:   ; CALL OCCURS {printf} {0}        ; |249| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |249| 

$C$RL53:   ; CALL OCCURS {printf} {0}        ; |249| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |256| 

$C$RL54:   ; CALL OCCURS {print_profile_results} {0}  ; |256| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |259| 

$C$RL55:   ; CALL OCCURS {print_memory_results} {0}  ; |259| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(64),B3      ; |260| 
           LDDW    .D2T1   *++SP,A13:A12     ; |260| 
           LDDW    .D2T1   *++SP,A15:A14     ; |260| 
           LDDW    .D2T2   *++SP,B11:B10     ; |260| 
           LDDW    .D2T2   *++SP,B13:B12     ; |260| 

           LDW     .D2T1   *++SP(8),A10      ; |260| 
||         RET     .S2     B3                ; |260| 

           LDW     .D2T1   *++SP(8),A11      ; |260| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |260| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"powSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	pow
	.global	powf
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	powsp
	.global	powsp_c
	.global	powsp_v
	.global	t_start
	.global	t_stop
	.global	t_offset
	.global	cycle_counts
	.global	fcn_pass
	.global	all_pass
	.global	a_ext
	.global	b_ext
	.global	a_sc
	.global	b_sc
	.global	output
	.global	input
	.global	logtable
	.global	kTable
	.global	jTable
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
