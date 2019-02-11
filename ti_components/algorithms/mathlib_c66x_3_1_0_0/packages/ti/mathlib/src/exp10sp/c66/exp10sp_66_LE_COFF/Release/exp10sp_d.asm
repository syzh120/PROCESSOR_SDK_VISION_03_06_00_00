;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:34:50 2013                                *
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
	.word	040e82d54h		; _a[0] @ 0
	.word	04102fb66h		; _a[1] @ 32
	.word	040f804eeh		; _a[2] @ 64
	.word	0409c28bfh		; _a[3] @ 96
	.word	0c1167ad8h		; _a[4] @ 128
	.word	0bff75d35h		; _a[5] @ 160
	.word	03f377935h		; _a[6] @ 192
	.word	0c02ffa57h		; _a[7] @ 224
	.word	04088cb73h		; _a[8] @ 256
	.word	0c04db04ah		; _a[9] @ 288
	.word	0c087bb7bh		; _a[10] @ 320
	.word	040587300h		; _a[11] @ 352
	.word	040bbc2dbh		; _a[12] @ 384
	.word	0406a62ddh		; _a[13] @ 416
	.word	0410eca12h		; _a[14] @ 448
	.word	0c10bbbeah		; _a[15] @ 480
	.word	0c11de6b0h		; _a[16] @ 512
	.word	0c0a10d6bh		; _a[17] @ 544
	.word	0c0d92ce3h		; _a[18] @ 576
	.word	040b10b3fh		; _a[19] @ 608
	.word	04103a16eh		; _a[20] @ 640
	.word	0407106eeh		; _a[21] @ 672
	.word	0bfb665efh		; _a[22] @ 704
	.word	040f8519ch		; _a[23] @ 736
	.word	0410a870eh		; _a[24] @ 768
	.word	03e9e4b19h		; _a[25] @ 800
	.word	0c10675cah		; _a[26] @ 832
	.word	0c06155b6h		; _a[27] @ 864
	.word	0c060d11bh		; _a[28] @ 896
	.word	0c10bfb4fh		; _a[29] @ 928
	.word	0c080e0a5h		; _a[30] @ 960
	.word	040ddf5b3h		; _a[31] @ 992
	.word	0c0c62e19h		; _a[32] @ 1024
	.word	03f022d4eh		; _a[33] @ 1056
	.word	0c0f9da22h		; _a[34] @ 1088
	.word	0c10bfab2h		; _a[35] @ 1120
	.word	0bed697efh		; _a[36] @ 1152
	.word	04108f50ah		; _a[37] @ 1184
	.word	0c0187f0eh		; _a[38] @ 1216
	.word	0bf98cf35h		; _a[39] @ 1248
	.word	04117d722h		; _a[40] @ 1280
	.word	0c0dddf4ah		; _a[41] @ 1312
	.word	040cf6b29h		; _a[42] @ 1344
	.word	0c09895b5h		; _a[43] @ 1376
	.word	0c07065a7h		; _a[44] @ 1408
	.word	04106858eh		; _a[45] @ 1440
	.word	0411d07b8h		; _a[46] @ 1472
	.word	0405ae65ah		; _a[47] @ 1504
	.word	04116ca5ah		; _a[48] @ 1536
	.word	040b83852h		; _a[49] @ 1568
	.word	0c087fbbeh		; _a[50] @ 1600
	.word	04048d43ch		; _a[51] @ 1632
	.word	0c092f3ach		; _a[52] @ 1664
	.word	0c0d5e2a6h		; _a[53] @ 1696
	.word	0410e8488h		; _a[54] @ 1728
	.word	0c10fa14ch		; _a[55] @ 1760
	.word	0c0199a0dh		; _a[56] @ 1792
	.word	0c07ac68eh		; _a[57] @ 1824
	.word	0c10ad817h		; _a[58] @ 1856
	.word	03edc3c05h		; _a[59] @ 1888
	.word	0c07d33cfh		; _a[60] @ 1920
	.word	0c07ff335h		; _a[61] @ 1952
	.word	03fadb7bfh		; _a[62] @ 1984
	.word	03fdf0fa8h		; _a[63] @ 2016
	.word	040fc7d16h		; _a[64] @ 2048
	.word	0c1057550h		; _a[65] @ 2080
	.word	0c0ab8faeh		; _a[66] @ 2112
	.word	04003e433h		; _a[67] @ 2144
	.word	040ddaddch		; _a[68] @ 2176
	.word	0bf824b98h		; _a[69] @ 2208
	.word	0405b84bch		; _a[70] @ 2240
	.word	040b2e380h		; _a[71] @ 2272
	.word	04081a34ch		; _a[72] @ 2304
	.word	0c11b2e3fh		; _a[73] @ 2336
	.word	0c03e7723h		; _a[74] @ 2368
	.word	0c0d7d8b0h		; _a[75] @ 2400
	.word	040dbee43h		; _a[76] @ 2432
	.word	0c0a34675h		; _a[77] @ 2464
	.word	03fc111a2h		; _a[78] @ 2496
	.word	04031656fh		; _a[79] @ 2528
	.word	0bd36f2c0h		; _a[80] @ 2560
	.word	0bf433b17h		; _a[81] @ 2592
	.word	0bda3b86ch		; _a[82] @ 2624
	.word	04110b06bh		; _a[83] @ 2656
	.word	04099faadh		; _a[84] @ 2688
	.word	040cd979bh		; _a[85] @ 2720
	.word	0c0ff8c9bh		; _a[86] @ 2752
	.word	0405812a4h		; _a[87] @ 2784
	.word	0bea7eb9bh		; _a[88] @ 2816
	.word	0c0640f30h		; _a[89] @ 2848
	.word	0c0adaaeeh		; _a[90] @ 2880
	.word	0c0b02532h		; _a[91] @ 2912
	.word	0bee18446h		; _a[92] @ 2944
	.word	040c66f63h		; _a[93] @ 2976
	.word	03f9649aah		; _a[94] @ 3008
	.word	040f0fddeh		; _a[95] @ 3040
	.word	0c04f455eh		; _a[96] @ 3072
	.word	0411707aeh		; _a[97] @ 3104
	.word	04016206eh		; _a[98] @ 3136
	.word	0409988a2h		; _a[99] @ 3168
	.word	03dffb408h		; _a[100] @ 3200
	.word	0c055359dh		; _a[101] @ 3232
	.word	040afa340h		; _a[102] @ 3264
	.word	040aa6fabh		; _a[103] @ 3296
	.word	0c0942985h		; _a[104] @ 3328
	.word	0c08a9ecbh		; _a[105] @ 3360
	.word	0c0a679bch		; _a[106] @ 3392
	.word	040a32183h		; _a[107] @ 3424
	.word	040a5570fh		; _a[108] @ 3456
	.word	0c114cba9h		; _a[109] @ 3488
	.word	0c10a8e00h		; _a[110] @ 3520
	.word	0c0471593h		; _a[111] @ 3552
	.word	04114b063h		; _a[112] @ 3584
	.word	0403e79d3h		; _a[113] @ 3616
	.word	0c0dbaddah		; _a[114] @ 3648
	.word	0c1192e98h		; _a[115] @ 3680
	.word	0407178b0h		; _a[116] @ 3712
	.word	0c115722bh		; _a[117] @ 3744
	.word	0c09b2c0ah		; _a[118] @ 3776
	.word	0c0f39eaeh		; _a[119] @ 3808
	.word	0400d53e9h		; _a[120] @ 3840
	.word	0410dd45ah		; _a[121] @ 3872
	.word	0410c2bcah		; _a[122] @ 3904
	.word	040c2c63ah		; _a[123] @ 3936
	.word	0c0aa3a34h		; _a[124] @ 3968
	.word	04116b6e2h		; _a[125] @ 4000
	.word	0403f716dh		; _a[126] @ 4032
	.word	0c10215bch		; _a[127] @ 4064
	.word	041025083h		; _a[128] @ 4096
	.word	03f734c8bh		; _a[129] @ 4128
	.word	0404c7700h		; _a[130] @ 4160
	.word	040de7f2ch		; _a[131] @ 4192
	.word	040d7bcd0h		; _a[132] @ 4224
	.word	0411581a9h		; _a[133] @ 4256
	.word	0c107b876h		; _a[134] @ 4288
	.word	040ab241ch		; _a[135] @ 4320
	.word	0c10e825fh		; _a[136] @ 4352
	.word	0c046e591h		; _a[137] @ 4384
	.word	040ee5798h		; _a[138] @ 4416
	.word	0bfdfd8d4h		; _a[139] @ 4448
	.word	0bf9327f6h		; _a[140] @ 4480
	.word	0404988e3h		; _a[141] @ 4512
	.word	040de9ca1h		; _a[142] @ 4544
	.word	0c0d796e1h		; _a[143] @ 4576
	.word	04093aa24h		; _a[144] @ 4608
	.word	04089d8a4h		; _a[145] @ 4640
	.word	0404ca19ah		; _a[146] @ 4672
	.word	0c09f9efch		; _a[147] @ 4704
	.word	0be0fb748h		; _a[148] @ 4736
	.word	0c0cd208ah		; _a[149] @ 4768
	.word	040b9dbabh		; _a[150] @ 4800
	.word	040ac7b58h		; _a[151] @ 4832
	.word	0c0e4a48fh		; _a[152] @ 4864
	.word	03f5ab869h		; _a[153] @ 4896
	.word	03fd82149h		; _a[154] @ 4928
	.word	040276dfah		; _a[155] @ 4960
	.word	0410bd89eh		; _a[156] @ 4992
	.word	0c0ddcaffh		; _a[157] @ 5024
	.word	0c0b670b6h		; _a[158] @ 5056
	.word	04005ec9eh		; _a[159] @ 5088
	.word	04119bdd6h		; _a[160] @ 5120
	.word	0c0c02d93h		; _a[161] @ 5152
	.word	040891e1ah		; _a[162] @ 5184
	.word	0c08476deh		; _a[163] @ 5216
	.word	0c0b769bbh		; _a[164] @ 5248
	.word	0408af5e6h		; _a[165] @ 5280
	.word	0410d9de5h		; _a[166] @ 5312
	.word	0c0d650b2h		; _a[167] @ 5344
	.word	0bfb8f5b3h		; _a[168] @ 5376
	.word	03fc543f8h		; _a[169] @ 5408
	.word	04018dcb0h		; _a[170] @ 5440
	.word	03e0223fch		; _a[171] @ 5472
	.word	0c097c3f8h		; _a[172] @ 5504
	.word	0bcfabbbeh		; _a[173] @ 5536
	.word	0c084e0c0h		; _a[174] @ 5568
	.word	0bf45f0f1h		; _a[175] @ 5600
	.word	0c0c660d6h		; _a[176] @ 5632
	.word	0c111f2e1h		; _a[177] @ 5664
	.word	0c02dbf0dh		; _a[178] @ 5696
	.word	0c11a1d93h		; _a[179] @ 5728
	.word	03f23d70ch		; _a[180] @ 5760
	.word	0402318e4h		; _a[181] @ 5792
	.word	0c105e383h		; _a[182] @ 5824
	.word	0c11f7d18h		; _a[183] @ 5856
	.word	0bf65de85h		; _a[184] @ 5888
	.word	0bdd10808h		; _a[185] @ 5920
	.word	03f0899a3h		; _a[186] @ 5952
	.word	0c1059100h		; _a[187] @ 5984
	.word	04114eebch		; _a[188] @ 6016
	.word	040997607h		; _a[189] @ 6048
	.word	040259326h		; _a[190] @ 6080
	.word	040b89428h		; _a[191] @ 6112
	.word	041068dd6h		; _a[192] @ 6144
	.word	0c080851dh		; _a[193] @ 6176
	.word	0c0d51988h		; _a[194] @ 6208
	.word	0bf2d582dh		; _a[195] @ 6240
	.word	0c11e232ch		; _a[196] @ 6272
	.word	0411275b1h		; _a[197] @ 6304
	.word	040a1d7d0h		; _a[198] @ 6336
	.word	0c05e76a8h		; _a[199] @ 6368
	.word	040acdd59h		; _a[200] @ 6400
$C$IR_1:	.set	804

	.global	_a
_a:	.usect	".far",804,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\147482 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\147484 
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
;*   Local Frame Size  : 8 Args + 84 Auto + 56 Save = 148 byte                *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |109| 
           STW     .D2T1   A10,*SP--(8)      ; |109| 
           STDW    .D2T2   B13:B12,*SP--     ; |109| 
           STDW    .D2T2   B11:B10,*SP--     ; |109| 
           STDW    .D2T1   A15:A14,*SP--     ; |109| 

           STDW    .D2T1   A13:A12,*SP--     ; |109| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(104)     ; |109| 
||         CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |117| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     0xc9,B4
||         MVKL    .S1     _a,A10

           MVKH    .S1     _a,A10

           CALL    .S1     _exp10f           ; |126| 
||         MV      .L1     A10,A13
||         MV      .D1X    B4,A12
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A13++,A4         ; |126| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |126| 
$C$RL1:    ; CALL OCCURS {_exp10f} {0}       ; |126| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     _output,B4
||         SUB     .L1     A12,1,A0          ; |125| 
||         SUB     .S1     A12,1,A12         ; |125| 

           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |126| 
   [ A0]   BNOP    .S1     $C$L1,3           ; |125| 

           ADD     .L2     B10,B4,B4         ; |126| 
||         ADD     .S2     4,B10,B10         ; |125| 

   [ A0]   CALL    .S1     _exp10f           ; |126| 
||         STW     .D2T1   A4,*B4            ; |126| 
|| [!A0]   MVKL    .S2     _output,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |125| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           MVK     .S2     0xc9,B5
||         ZERO    .L2     B10
||         MV      .L1     A10,A11

           MVKH    .S2     _output,B4

           ADD     .L2     4,B4,B4
||         MV      .L1X    B5,A12

           STW     .D2T2   B4,*+SP(56)
||         CALL    .S1     _exp10sp          ; |129| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A10++,A4         ; |129| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |129| 
$C$RL2:    ; CALL OCCURS {_exp10sp} {0}      ; |129| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(56),B4       ; |129| 
           SUB     .L1     A12,1,A0          ; |128| 
           SUB     .L1     A12,1,A12         ; |128| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |129| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |128| 

           ADD     .L2     B10,B4,B4         ; |129| 
||         ADD     .S2     4,B10,B10         ; |128| 

   [ A0]   CALL    .S1     _exp10sp          ; |129| 
||         STW     .D2T1   A4,*B4            ; |129| 

           ; BRANCHCC OCCURS {$C$L2}         ; |128| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(56),B4
           MVK     .S2     0xc9,B5
           ZERO    .L2     B10
           MV      .L1     A11,A12
           MV      .L1X    B5,A10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(60)
||         CALL    .S1     _exp10sp_c        ; |132| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |132| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |132| 
$C$RL3:    ; CALL OCCURS {_exp10sp_c} {0}    ; |132| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(60),B4       ; |132| 
||         SUB     .L1     A10,1,A0          ; |131| 
||         SUB     .S1     A10,1,A10         ; |131| 

   [!A0]   MVKL    .S1     0x40135d8e,A3
|| [!A0]   ZERO    .L1     A7

   [!A0]   LDW     .D2T2   *+SP(60),B6
   [!A0]   MVKH    .S1     0x40135d8e,A3
   [!A0]   MVKL    .S1     0x3d317000,A5
           LDW     .D2T2   *B4,B4            ; |132| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |131| 

           ADD     .L2     B10,B4,B4         ; |132| 
||         ADD     .S2     4,B10,B10         ; |131| 

   [ A0]   CALL    .S2     _exp10sp_c        ; |132| 
||         STW     .D2T1   A4,*B4            ; |132| 
|| [!A0]   MVKL    .S1     _kTable,A4

           ; BRANCHCC OCCURS {$C$L3}         ; |131| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           STW     .D2T1   A7,*+SP(44)
||         MVKL    .S2     _jTable,B4
||         MVKL    .S1     0x42549a78,A6
||         ZERO    .L1     A7
||         ZERO    .D1     A15
||         MV      .L2X    A3,B24

           STW     .D2T1   A3,*+SP(32)
||         MVKL    .S1     0x7f7fffff,A3
||         MVKL    .S2     0x3605fdf4,B5
||         ZERO    .L2     B7

           MVKL    .S1     0x3effffff,A12
||         MVKL    .S2     0x42b17218,B10
||         ADD     .L2     4,B6,B12
||         ZERO    .D2     B19

           MVKH    .S1     0x3d317000,A5
||         MVKH    .S2     _jTable,B4
||         LDW     .D2T2   *B12,B16

           SET     .S1     A7,0x17,0x1d,A7
||         MVKH    .S2     0x3605fdf4,B5
||         STW     .D2T1   A5,*+SP(28)

           MVKH    .S1     0x7f7fffff,A3
||         MVKH    .S2     0x42b17218,B10
||         MV      .L2X    A5,B25
||         MV      .L1X    B4,A9
||         STW     .D2T2   B4,*+SP(36)

           MVKH    .S1     0x42549a78,A6
||         MVKL    .S2     0xc2aeac50,B11
||         ADD     .L1     -2,A7,A7
||         MV      .D1X    B5,A16
||         STW     .D2T1   A3,*+SP(48)
||         MV      .L2X    A7,B21

           MVKH    .S1     0x3effffff,A12
||         MVKL    .S2     0x3e2abce4,B13
||         STW     .D2T1   A6,*+SP(20)
||         MV      .L1X    B10,A3
||         MV      .L2X    A3,B17

           MVKH    .S1     0xfff00000,A15
||         MVKH    .S2     0xc2aeac50,B11
||         ADD     .L1     1,A12,A5
||         STW     .D2T2   B5,*+SP(12)
||         MV      .L2X    A6,B27

           MVKH    .S1     _kTable,A4
||         MVKH    .S2     0x3e2abce4,B13
||         STW     .D2T1   A5,*+SP(24)
||         ADD     .L2X    1,A12,B26

           MVKH    .S2     0xbf000000,B7
||         MVK     .S1     0x72,A13
||         STW     .D2T1   A4,*+SP(40)
||         MV      .L2X    A15,B22

           MVK     .S1     0xc9,A8
||         MV      .L1     A13,A6
||         STW     .D2T2   B7,*+SP(16)
||         MV      .L2X    A4,B23
||         MV      .S2     B13,B20

           SUB     .L1     A8,1,A1
||         MV      .S1     A12,A8
||         MV      .L2     B11,B18
||         MV      .S2     B7,B28
||         MV      .D2X    A11,B7

           DINT                              ; interrupts off
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/exp10sp/exp10sp_d.c
;*      Loop source line                 : 134
;*      Loop opening brace source line   : 134
;*      Loop closing brace source line   : 136
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 66
;*      Unpartitioned Resource Bound     : 7
;*      Partitioned Resource Bound(*)    : 10
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     1        2     
;*      .S units                     2        5     
;*      .D units                     1        3     
;*      .M units                     4        8     
;*      .X cross paths               7        5     
;*      .T address paths             1        3     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        8     (.L or .S unit)
;*      Addition ops (.LSD)          1        9     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             2        8     
;*      Bound(.L .S .D .LS .LSD)     2        9     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 66 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: | * *  ****      *               |       *        *************   |
;*       1: | * *  ****      *               |       *        *************   |
;*       2: | * *  ****      *               |       *        *************   |
;*       3: | * *  ****      *               |       *        *************   |
;*       4: | * *  ****      *               |       *        *************   |
;*       5: | * *  ****      *               |    *  *        *************   |
;*       6: | * *  ****      *               |    *  *        *************   |
;*       7: | * *  ****      *               |       *        *************   |
;*       8: | * *  ****      *               |       *        *************   |
;*       9: | * *  ****      *               |    *  *        *************   |
;*      10: | * *  ****      *               |     * *        ************* * |
;*      11: | * *  ****      *               |     * *        *************** |
;*      12: | * *  ****      *               |    ** *        *************** |
;*      13: | * *  ****      *               |     * *        *************** |
;*      14: | * *  ****      *               |     * *        *************** |
;*      15: | * *  ****      *               |     * *        *************** |
;*      16: | * *  ****      *               |    ** *        *************** |
;*      17: | * *  ****      *               |    ** *        *************** |
;*      18: | * *  ****      *               |    ** *        *************** |
;*      19: | * ** ****      *               |    ** *        *************** |
;*      20: | * *  ****      *               |    *  *        *************** |
;*      21: | * *  ****      *               |    ** *        *************** |
;*      22: | * *  ****      *               |    ** *        *************** |
;*      23: | * *  ****      *               |    *  *        *************** |
;*      24: | * *******      *               |    *  ***      *************** |
;*      25: | * *  ****      *               |    ** *        *************** |
;*      26: | * *  ****      **              |    *  *        *************** |
;*      27: | * *  ****      **              |    *  *        *************** |
;*      28: | * *******      **              |    ** *        *************** |
;*      29: | * *******      *               |    *  *        *************** |
;*      30: | * ** ****      *               |     * *        *************** |
;*      31: | * ** ****      *               |    ** *        *************** |
;*      32: | * ** ****      *               |    ** *        *************** |
;*      33: | * ** ****      *               |    ** *        *************** |
;*      34: | * ** ****      *               |    ** *        *************** |
;*      35: | * ** ****      *               |    ****        *************** |
;*      36: | * *******      *               |     ***        *************** |
;*      37: | * *******      *               |     * *        *************** |
;*      38: | * *******      *               |     * *        *************** |
;*      39: | * *******      *               |    ** *        *************** |
;*      40: | * *******      **              |     * *        *************** |
;*      41: | * *******      **              |     * *        *************** |
;*      42: | * *******      **              |     * *        *************** |
;*      43: | * *******      **              |    ** *        *************** |
;*      44: | * *******      *               |     * *        *************** |
;*      45: | * *******      *               |     * *        *************** |
;*      46: | * *******      *               |    ** *        *************** |
;*      47: | * ** ****      *               |     * *        *************** |
;*      48: | * ** ****      *               |     * *        *************** |
;*      49: | * ** ****      *               |    ** *        *************** |
;*      50: | * ** ****      *               |     * *        *************** |
;*      51: | * ** ****      *               |     * *        *************** |
;*      52: | * *  ****      *               |    ****        *************** |
;*      53: | * *  ****      *               |    ****        *************** |
;*      54: | * *  ****      *               |       *        *************** |
;*      55: | * *  ****      *               |       *        *************** |
;*      56: | * *  ****      *               |       *        *************** |
;*      57: | * *  ****      *               |       *        *************** |
;*      58: | * *  ****      *               |       *        *************** |
;*      59: |** *  ****      *               |    ** *        ************* * |
;*      60: | * *  ****      *               |       *        ************* * |
;*      61: | * *  ****      *               |       *        ************* * |
;*      62: | * *  ****      *               |    *  *        ************* * |
;*      63: | * *  ****      *               |*   *  *        ************* * |
;*      64: |** *  ****      *               |    ** *        *************   |
;*      65: | * *  ****      *               |    ****        *************   |
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
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.250, max 1.000 }
;*      Mem bank perf. penalty (est.) : 0.4%
;*
;*      Effective ii                : { min 66.00, est 66.25, max 67.00 }
;*
;*
;*      Total cycles (est.)         : 0 + min_trip_cnt * 66 = 13266        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A1,1,A1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C119:
;*   0              LDW     .D2T2   *B7++,B4          ; |92|  ^ 
;*   1              NOP             4
;*   5              MPYSP   .M2     B27,B4,B4         ; |92|  ^ 
;*   6              MPYSP   .M2     B24,B4,B30        ; |92| 
;*   7              NOP             2
;*   9              CMPLTSP .S2     B4,B28,B5         ; |92| 
;*     ||           FADDSP  .L2     B26,B4,B4         ; |92|  ^ 
;*  10              EXTU    .S2     B30,1,24,B29      ; |104| 
;*  11              NOP             1
;*  12              SPTRUNC .L2     B4,B4             ; |92|  ^ 
;*  13              NOP             3
;*  16              SUB     .S2     B4,B5,B5          ; |92|  ^ 
;*     ||           SUB     .L2     B4,B5,B4          ; |104| 
;*  17              INTSP   .L2     B5,B5             ; |92|  ^ 
;*     ||           SHL     .S2     B4,16,B4          ; |104| 
;*  18              EXTU    .S2     B5,28,30,B5       ; |104| 
;*     ||           AND     .L1X    3,B5,A4           ; |104| 
;*     ||           AND     .L2     B22,B4,B4         ; |104| 
;*  19              LDDW    .D2T2   *+B23[B5],B9:B8   ; |104| 
;*     ||           LDDW    .D1T1   *+A9[A4],A5:A4    ; |104| 
;*  20              NOP             1
;*  21              MPYSP   .M2     B25,B5,B5         ; |92|  ^ 
;*  22              MPYSP   .M1X    A16,B5,A17        ; |92| 
;*  23              NOP             1
;*  24              FMPYDP  .M1X    A5:A4,B9:B8,A5:A4 ; |104| 
;*  25              FSUBSP  .L2     B30,B5,B5         ; |92|  ^ 
;*  26              NOP             2
;*  28              FSUBSP  .L2X    B5,A17,B4         ; |92|  ^ 
;*  29              ADD     .L2X    B4,A5,B5          ; |104| 
;*  30              NOP             1
;*  31              MPYSP   .M2     B4,B4,B6          ; |92|  ^ 
;*  32              MPYSP   .M1X    A7,B4,A5          ; |104| 
;*  33              NOP             2
;*  35              MPYSP   .M2     B6,B4,B4          ; |104|  ^ 
;*  36              MPYSP   .M1X    A8,B6,A17         ; |104| 
;*  37              NOP             2
;*  39              MPYSP   .M2     B20,B4,B4         ; |104|  ^ 
;*  40              NOP             3
;*  43              FADDSP  .L2X    A17,B4,B4         ; |104|  ^ 
;*  44              NOP             2
;*  46              FADDSP  .L2X    B4,A5,B4          ; |104|  ^ 
;*  47              NOP             2
;*  49              FADDSP  .L2     B21,B4,B6         ; |104|  ^ 
;*  50              NOP             1
;*  51              MV      .S2X    A4,B4             ; |104| 
;*  52              MPYSPDP .M2     B6,B5:B4,B5:B4    ; |104|  ^ 
;*  53              NOP             5
;*  58              CMPLTU  .L1X    B29,A6,A0         ; |104| 
;*  59      [ A0]   FADDSP  .S2     B21,B30,B4        ; |104| 
;*     ||   [!A0]   DPSP    .L2     B5:B4,B4          ; |104|  ^ 
;*  60      [ A1]   BDEC    .S1     $C$C119,A1        ; |134| 
;*  61              NOP             1
;*  62              CMPLTSP .S2     B30,B18,B0        ; |104| 
;*  63      [!B0]   MV      .S2     B4,B5             ; |104|  ^ 
;*     ||   [ B0]   MV      .L2     B19,B5            ; |104| 
;*     ||           CMPGTSP .S1X    B30,A3,A0         ; |104| 
;*  64      [!A0]   MV      .S2     B5,B6             ; |104|  ^ 
;*     ||   [ A0]   MV      .L2     B17,B6            ; |104| 
;*  65              STW     .D2T2   B6,*B16++         ; |104|  ^ 
;*  66              ; BRANCHCC OCCURS {$C$C119}       ; |134| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 66
           LDW     .D2T2   *B7++,B4          ; |92| <0,0>  ^ 
           NOP             4
           MPYSP   .M2     B27,B4,B4         ; |92| <0,5>  ^ 
           MPYSP   .M2     B24,B4,B30        ; |92| <0,6> 
           NOP             2

           CMPLTSP .S2     B4,B28,B5         ; |92| <0,9> 
||         FADDSP  .L2     B26,B4,B4         ; |92| <0,9>  ^ 

           EXTU    .S2     B30,1,24,B29      ; |104| <0,10> 
           NOP             1
           SPTRUNC .L2     B4,B4             ; |92| <0,12>  ^ 
           NOP             3

           SUB     .L2     B4,B5,B4          ; |104| <0,16> 
||         SUB     .S2     B4,B5,B5          ; |92| <0,16>  ^ 

           SHL     .S2     B4,16,B4          ; |104| <0,17> 
||         INTSP   .L2     B5,B5             ; |92| <0,17>  ^ 

           AND     .L2     B22,B4,B4         ; |104| <0,18> 
||         EXTU    .S2     B5,28,30,B5       ; |104| <0,18> 
||         AND     .L1X    3,B5,A4           ; |104| <0,18> 

           LDDW    .D2T2   *+B23[B5],B9:B8   ; |104| <0,19> 
||         LDDW    .D1T1   *+A9[A4],A5:A4    ; |104| <0,19> 

           NOP             1
           MPYSP   .M2     B25,B5,B5         ; |92| <0,21>  ^ 
           MPYSP   .M1X    A16,B5,A17        ; |92| <0,22> 
           NOP             1
           FMPYDP  .M1X    A5:A4,B9:B8,A5:A4 ; |104| <0,24> 
           FSUBSP  .L2     B30,B5,B5         ; |92| <0,25>  ^ 
           NOP             2
           FSUBSP  .L2X    B5,A17,B4         ; |92| <0,28>  ^ 
           ADD     .L2X    B4,A5,B5          ; |104| <0,29> 
           NOP             1
           MPYSP   .M2     B4,B4,B6          ; |92| <0,31>  ^ 
           MPYSP   .M1X    A7,B4,A5          ; |104| <0,32> 
           NOP             2
           MPYSP   .M2     B6,B4,B4          ; |104| <0,35>  ^ 
           MPYSP   .M1X    A8,B6,A17         ; |104| <0,36> 
           NOP             2
           MPYSP   .M2     B20,B4,B4         ; |104| <0,39>  ^ 
           NOP             3
           FADDSP  .L2X    A17,B4,B4         ; |104| <0,43>  ^ 
           NOP             2
           FADDSP  .L2X    B4,A5,B4          ; |104| <0,46>  ^ 
           NOP             2
           FADDSP  .L2     B21,B4,B6         ; |104| <0,49>  ^ 
           NOP             1
           MV      .S2X    A4,B4             ; |104| <0,51> 
           MPYSPDP .M2     B6,B5:B4,B5:B4    ; |104| <0,52>  ^ 
           NOP             5
           CMPLTU  .L1X    B29,A6,A0         ; |104| <0,58> 

   [ A0]   FADDSP  .S2     B21,B30,B4        ; |104| <0,59> 
|| [!A0]   DPSP    .L2     B5:B4,B4          ; |104| <0,59>  ^ 

   [ A1]   BDEC    .S1     $C$L5,A1          ; |134| <0,60> 
           NOP             1
           CMPLTSP .S2     B30,B18,B0        ; |104| <0,62> 

           CMPGTSP .S1X    B30,A3,A0         ; |104| <0,63> 
|| [ B0]   MV      .L2     B19,B5            ; |104| <0,63> 
|| [!B0]   MV      .S2     B4,B5             ; |104| <0,63>  ^ 

   [ A0]   MV      .L2     B17,B6            ; |104| <0,64> 
|| [!A0]   MV      .S2     B5,B6             ; |104| <0,64>  ^ 

           STW     .D2T2   B6,*B16++         ; |104| <0,65>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           STW     .D2T2   B26,*+SP(24)
           STW     .D2T2   B25,*+SP(28)
           STW     .D2T2   B24,*+SP(32)
           STW     .D2T2   B23,*+SP(40)
           STW     .D2T2   B19,*+SP(44)
           STW     .D2T2   B17,*+SP(48)
           STW     .D2T1   A16,*+SP(12)

           MVKL    .S2     _output,B4
||         STW     .D2T1   A9,*+SP(36)

           MV      .L1     A6,A13
||         MV      .L2X    A3,B10
||         STW     .D2T2   B27,*+SP(20)
||         RINT                              ; interrupts on

           MVKH    .S2     _output,B4
||         MV      .L1     A7,A14
||         MV      .L2     B18,B11
||         MV      .S1X    B21,A10
||         STW     .D2T2   B28,*+SP(16)
||         MV      .D1     A11,A4            ; |137| 

           CALLP   .S2     _exp10sp_v,B3
||         LDW     .D2T2   *+B4(16),B4       ; |137| 
||         MVK     .S1     0xc9,A6           ; |137| 
||         MV      .L1     A8,A12
||         MV      .L2     B20,B13
||         MV      .D1X    B22,A15

$C$RL4:    ; CALL OCCURS {_exp10sp_v} {0}    ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 56
           MVKL    .S2     _output,B5
           MVKL    .S2     _output,B4
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _output,B5
           MVKH    .S2     _output,B4
           MVKH    .S2     0x88e368f1,B6

           LDW     .D2T1   *B5,A4            ; |66| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B4(4),B4        ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _output,B4
           MVKL    .S2     _fcn_pass,B6
           MVKH    .S2     _output,B4

           LDW     .D2T2   *B4,B5            ; |67| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B4(8),B4        ; |67| 
||         MV      .L1X    B5,A4             ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _output,B5
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _output,B5
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L2     B5,B4             ; |126| 
||         STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B4(12),B4       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     _output,B4
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     _output,B4

           ADD     .L1X    4,B12,A3
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           STW     .D2T1   A3,*+SP(64)
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S2     _fcn_pass,B4
           MVKH    .S2     _fcn_pass,B4

           ADD     .L2     4,B4,B4
||         MVKL    .S2     _fcn_pass,B5

           LDW     .D2T2   *B4,B0            ; |72| 
||         MVKH    .S2     _fcn_pass,B5

           STW     .D2T2   B4,*+SP(68)
           ADD     .L2     8,B5,B4
           STW     .D2T2   B4,*+SP(72)       ; |69| 
           STW     .D2T1   A4,*+B5(16)       ; |69| 

   [!B0]   MVKL    .S1     _all_pass,A3
|| [!B0]   B       .S2     $C$L7             ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [!B0]   ZERO    .D2     B4                ; |72| 

   [!B0]   CALL    .S2     _print_test_results ; |141| 
|| [!B0]   MVKH    .S1     _all_pass,A3
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
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
           CALL    .S1     _print_test_results ; |141| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |141| 
||         STW     .D1T2   B4,*A3            ; |72| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |141| 

$C$RL9:    ; CALL OCCURS {_print_test_results} {0}  ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T1   *+SP(44),A6       ; |149| 
||         MVKL    .S2     _a_sc,B4

           STW     .D2T2   B12,*+SP(76)
||         MVKL    .S2     0x7f7fffff,B31
||         MVK     .L2     0x7,B29

           STW     .D2T2   B29,*+SP(52)      ; |149| 
||         MVKH    .S2     _a_sc,B4
||         ZERO    .L1     A5
||         MVK     .L2     -1,B6             ; |154| 

           MV      .L2     B4,B6             ; |154| 
||         STW     .D2T2   B6,*+B4(24)       ; |154| 
||         MVKH    .S1     0xbf800000,A5
||         ZERO    .S2     B5
||         ZERO    .L1     A7
||         MV      .D1     A10,A4            ; |153| 

           STDW    .D2T1   A5:A4,*+B6(16)    ; |153| 
||         MV      .L2     B6,B30            ; |151| 
||         MVKH    .S2     0x7f7fffff,B31
||         MVKH    .S1     0x80000000,A7

           STDW    .D2T1   A7:A6,*B30        ; |149| 
||         ADD     .L2     1,B31,B4
||         MV      .L1X    B4,A11            ; |149| 
||         MVKH    .S2     0xff800000,B5

           STDW    .D2T2   B5:B4,*+B6(8)     ; |151| 
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
           LDW     .D1T1   *A11,A3           ; |156| 
           CALL    .S1     _exp10            ; |156| 
           ADDKPC  .S2     $C$RL10,B3,2      ; |156| 
           SPDP    .S1     A3,A5:A4          ; |156| 
           NOP             1
$C$RL10:   ; CALL OCCURS {_exp10} {0}        ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |156| 
           DPSP    .L1     A5:A4,A3          ; |156| 
           NOP             3
           ADD     .L2     B12,B4,B4         ; |156| 
           STW     .D2T1   A3,*B4            ; |156| 

           CALLP   .S2     _exp10sp,B3
||         LDW     .D1T1   *A11,A4           ; |157| 

$C$RL11:   ; CALL OCCURS {_exp10sp} {0}      ; |157| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(4),B4        ; |157| 
           NOP             4
           ADD     .L2     B12,B4,B4         ; |157| 
           STW     .D2T1   A4,*B4            ; |157| 

           CALLP   .S2     _exp10sp_c,B3
||         LDW     .D1T1   *A11,A4           ; |158| 

$C$RL12:   ; CALL OCCURS {_exp10sp_c} {0}    ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 79
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |158| 
           LDW     .D2T1   *+SP(20),A3
           LDW     .D2T1   *+SP(24),A31
           LDW     .D2T1   *+SP(16),A30
           LDW     .D2T1   *+SP(28),A29
           ADD     .L2     B12,B4,B4         ; |158| 
           STW     .D2T1   A4,*B4            ; |158| 
           LDW     .D1T1   *A11++,A5         ; |82| 
           LDW     .D2T2   *+SP(32),B31      ; |106| 
           LDW     .D2T2   *+SP(12),B30
           LDW     .D2T1   *+SP(40),A27      ; |106| 
           LDW     .D2T2   *+SP(36),B28      ; |106| 
           MPYSP   .M1     A3,A5,A4          ; |85| 
           MPYSP   .M2X    B31,A5,B6         ; |82| 
           LDW     .D2T2   *+SP(76),B27
           NOP             1
           FADDSP  .L1     A31,A4,A3         ; |85| 
           CMPLTSP .S1     A4,A30,A0         ; |86| 
           EXTU    .S2     B6,1,24,B26       ; |109| 
           SPTRUNC .L1     A3,A6             ; |85| 
           CMPLTSP .S2     B6,B11,B1         ; |114| 
           CMPLTU  .L2X    B26,A13,B0        ; |109| 
           CMPGTSP .S2     B6,B10,B2         ; |119| 
   [ A0]   SUB     .L1     A6,1,A6           ; |87| 
           INTSP   .L1     A6,A4             ; |106| 
           EXTU    .S1     A6,28,30,A28      ; |106| 
           AND     .L2X    3,A6,B29          ; |106| 
           SHL     .S1     A6,16,A26         ; |106| 
           MPYSP   .M1     A29,A4,A3         ; |106| 
           MPYSP   .M2X    B30,A4,B4         ; |106| 
           LDDW    .D1T1   *+A27[A28],A5:A4  ; |106| 
           NOP             2
           FSUBSP  .L2X    B6,A3,B5          ; |106| 
           NOP             2
           FSUBSP  .L2     B5,B4,B7          ; |106| 
           NOP             2
           MPYSP   .M2     B7,B7,B4          ; |106| 
           MPYSP   .M1X    A14,B7,A3         ; |106| 
           NOP             2
           MPYSP   .M2     B4,B7,B5          ; |106| 
           MPYSP   .M1X    A12,B4,A7         ; |106| 
           NOP             2

           MPYSP   .M2     B13,B5,B8         ; |106| 
||         LDDW    .D2T2   *+B28[B29],B5:B4  ; |106| 

           NOP             4

           FADDSP  .L1X    A7,B8,A7          ; |106| 
||         FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |106| 

           AND     .L1     A15,A26,A5        ; |106| 
           NOP             1
           FADDSP  .L1     A7,A3,A3          ; |106| 
           NOP             1

           MV      .S1X    B4,A4             ; |106| 
||         LDW     .D2T2   *B27,B4           ; |159| 

           FADDSP  .L1     A10,A3,A3         ; |106| 
           ADD     .L1X    A5,B5,A5          ; |106| 
           NOP             1
           MPYSPDP .M1     A3,A5:A4,A5:A4    ; |106| 

           ADD     .L2     B12,B4,B5         ; |159| 
||         LDW     .D2T2   *+SP(52),B4       ; |120| 

           ADD     .L2     4,B12,B12         ; |155| 
           NOP             3

           SUB     .L1X    B4,1,A0           ; |155| 
||         SUB     .L2     B4,1,B4           ; |155| 

           DPSP    .L1     A5:A4,A3          ; |106| 
|| [!A0]   MVKL    .S2     _output,B12
||         STW     .D2T2   B4,*+SP(52)       ; |159| 

   [!A0]   MVKH    .S2     _output,B12

   [ B0]   FADDSP  .L1X    A10,B6,A3         ; |110| 
|| [ B1]   LDW     .D2T1   *+SP(44),A3       ; |119| 

   [ A0]   BNOP    .S1     $C$L8,4           ; |155| 
|| [ B2]   LDW     .D2T1   *+SP(48),A3       ; |115| 

   [!A0]   CALL    .S1     _exp10sp_v        ; |161| 
||         STW     .D2T1   A3,*B5            ; |159| 

           ; BRANCHCC OCCURS {$C$L8}         ; |155| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B12(16),B4      ; |161| 
           MVKL    .S1     _a_sc,A4
           MVKH    .S1     _a_sc,A4
           MVK     .L1     0x7,A6            ; |161| 
           ADDKPC  .S2     $C$RL13,B3,0      ; |161| 
$C$RL13:   ; CALL OCCURS {_exp10sp_v} {0}    ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
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
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B5
           MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B12,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |68| 

           LDW     .D2T1   *+SP(64),A3       ; |68| 
||         MVKL    .S2     _fcn_pass,B4

           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           MV      .L2     B12,B5            ; |68| 
||         STW     .D2T1   A3,*+SP(76)       ; |68| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(68),A3       ; |69| 
           MVKL    .S2     _fcn_pass,B4
           MVKH    .S2     _fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           NOP             1
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A3,*+SP(80)       ; |69| 
           LDW     .D2T1   *+SP(72),A3
           NOP             2

   [!A0]   B       .S1     $C$L9             ; |72| 
|| [!A0]   ZERO    .L1     A4                ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |165| 

   [ A0]   MV      .L2X    A3,B4
||         STW     .D2T1   A3,*+SP(84)       ; |72| 
|| [!A0]   MVKL    .S1     _all_pass,A3

   [ A0]   LDW     .D2T2   *B4,B0            ; |72| 
   [!A0]   MVKH    .S1     _all_pass,A3
   [ A0]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
           NOP             2
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   ZERO    .L1     A4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |165| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |165| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |165| 

$C$RL18:   ; CALL OCCURS {_print_test_results} {0}  ; |165| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           MVKL    .S1     _a_ext,A3
           MVKH    .S1     _a_ext,A3

           ZERO    .L1     A4
||         MVK     .S2     0xed,B31

           MV      .L2X    A3,B4             ; |168| 
||         SET     .S1     A4,0x17,0x17,A4
||         STW     .D2T2   B31,*+SP(52)      ; |168| 

           STW     .D2T1   A4,*B4            ; |168| 
||         MV      .L1     A3,A11            ; |168| 

           LDW     .D1T1   *A11,A3           ; |170| 
           CALL    .S1     _exp10            ; |170| 
           ZERO    .L2     B12
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |170| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL19,B3,0      ; |170| 
$C$RL19:   ; CALL OCCURS {_exp10} {0}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |170| 
           DPSP    .L1     A5:A4,A3          ; |170| 
           ZERO    .L2     B31
           MVKH    .S2     0xc3800000,B31
           NOP             1
           ADD     .L2     B12,B4,B4         ; |170| 
           STW     .D2T1   A3,*B4            ; |170| 
           LDW     .D1T1   *A11,A4           ; |171| 
           NOP             4
           CMPGTSP .S2X    A4,B31,B0         ; |171| 
   [!B0]   B       .S1     $C$L11            ; |171| 
   [ B0]   CALL    .S1     _exp10sp          ; |171| 
   [!B0]   CALL    .S1     _exp10            ; |171| 
   [!B0]   SPDP    .S1     A4,A5:A4          ; |171| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L11}        ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL20,B3,0      ; |171| 
$C$RL20:   ; CALL OCCURS {_exp10sp} {0}      ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8

           SPDP    .S1     A4,A5:A4          ; |171| 
||         MVKL    .S2     _output,B4

           MVKH    .S2     _output,B4

           BNOP    .S1     $C$L12,4          ; |171| 
||         DPSP    .L1     A5:A4,A3          ; |171| 
||         LDW     .D2T2   *+B4(4),B4        ; |171| 

           MV      .L2X    A3,B5             ; |171| 
||         ADD     .S2     B12,B4,B4         ; |171| 

           ; BRANCH OCCURS {$C$L12}          ; |171| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL21,B3,1      ; |171| 
$C$RL21:   ; CALL OCCURS {_exp10} {0}        ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4

           LDW     .D2T2   *+B4(4),B4        ; |171| 
||         DPSP    .L1     A5:A4,A3          ; |171| 

           NOP             4

           ADD     .L2     B12,B4,B4         ; |171| 
||         MV      .S2X    A3,B5             ; |171| 

;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     _exp10sp_c        ; |172| 
||         STW     .D2T2   B5,*B4            ; |171| 

           LDW     .D1T1   *A11,A4           ; |172| 
           ADDKPC  .S2     $C$RL22,B3,3      ; |172| 
$C$RL22:   ; CALL OCCURS {_exp10sp_c} {0}    ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 103
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |172| 
           LDW     .D2T1   *+SP(20),A3
           LDW     .D2T1   *+SP(24),A31
           LDW     .D2T1   *+SP(16),A30
           LDW     .D2T1   *+SP(28),A29
           ADD     .L2     B12,B4,B4         ; |172| 
           STW     .D2T1   A4,*B4            ; |172| 
           LDW     .D1T1   *A11,A4           ; |82| 
           LDW     .D2T2   *+SP(32),B31      ; |106| 
           LDW     .D2T2   *+SP(12),B30
           LDW     .D2T1   *+SP(40),A28      ; |106| 
           LDW     .D2T2   *+SP(36),B28      ; |106| 
           MPYSP   .M1     A3,A4,A5          ; |85| 
           MPYSP   .M2X    B31,A4,B6         ; |82| 
           MVKL    .S2     _output+12,B27
           MVKH    .S2     _output+12,B27
           FADDSP  .L1     A31,A5,A3         ; |85| 
           CMPLTSP .S1     A5,A30,A0         ; |86| 
           EXTU    .S2     B6,1,24,B26       ; |109| 
           SPTRUNC .L1     A3,A6             ; |85| 
           CMPLTSP .S2     B6,B11,B1         ; |114| 
           CMPLTU  .L2X    B26,A13,B0        ; |109| 
           CMPGTSP .S2     B6,B10,B2         ; |119| 
   [ A0]   SUB     .L1     A6,1,A6           ; |87| 
           INTSP   .L1     A6,A5             ; |106| 
           EXTU    .S1     A6,28,30,A4       ; |106| 
           AND     .L2X    3,A6,B29          ; |106| 
           SHL     .S1     A6,16,A27         ; |106| 
           MPYSP   .M1     A29,A5,A3         ; |106| 
           MPYSP   .M2X    B30,A5,B4         ; |106| 
           LDDW    .D1T1   *+A28[A4],A5:A4   ; |106| 
           NOP             2
           FSUBSP  .L2X    B6,A3,B5          ; |106| 
           NOP             2
           FSUBSP  .L2     B5,B4,B7          ; |106| 
           NOP             2
           MPYSP   .M2     B7,B7,B4          ; |106| 
           MPYSP   .M1X    A14,B7,A3         ; |106| 
           NOP             2
           MPYSP   .M2     B4,B7,B5          ; |106| 
           MPYSP   .M1X    A12,B4,A7         ; |106| 
           NOP             2
           MPYSP   .M2     B13,B5,B8         ; |106| 
           LDDW    .D2T2   *+B28[B29],B5:B4  ; |106| 
           NOP             3
           FADDSP  .L1X    A7,B8,A7          ; |106| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |106| 
           NOP             1
           FADDSP  .L1     A7,A3,A4          ; |106| 
           AND     .L1     A15,A27,A3        ; |106| 
           NOP             1
           FADDSP  .L1     A10,A4,A6         ; |106| 
           ADD     .L1X    A3,B5,A5          ; |106| 
           MV      .S1X    B4,A4             ; |106| 
           MPYSPDP .M1     A6,A5:A4,A5:A4    ; |106| 
           LDW     .D2T2   *B27,B5           ; |173| 
           NOP             5
           DPSP    .L1     A5:A4,A4          ; |106| 
           ADD     .L2     B12,B5,B4         ; |173| 

   [ B0]   FADDSP  .L1X    A10,B6,A4         ; |110| 
|| [ B1]   LDW     .D2T1   *+SP(44),A4       ; |174| 

   [ B2]   LDW     .D2T1   *+SP(48),A4       ; |115| 
           MVKL    .S1     0xc000cccc,A5
           MVKH    .S1     0xc000cccc,A5
           ADD     .L2     4,B12,B12         ; |169| 
           NOP             1
           STW     .D2T1   A4,*B4            ; |173| 
           LDW     .D1T2   *A11,B4           ; |174| 
           MVKL    .S1     0xcccccccd,A4
           MVKH    .S1     0xcccccccd,A4
           NOP             2
           MPYSPDP .M2X    B4,A5:A4,B5:B4    ; |174| 
           NOP             6

           DPSP    .L2     B5:B4,B5          ; |174| 
||         LDW     .D2T2   *+SP(52),B4

           NOP             3
           STW     .D1T2   B5,*++A11         ; |174| 

           SUB     .L1X    B4,1,A0           ; |169| 
||         SUB     .L2     B4,1,B4           ; |169| 

   [ A0]   B       .S1     $C$L10            ; |169| 
|| [ A0]   LDW     .D1T1   *A11,A3           ; |170| 
|| [!A0]   MVKL    .S2     _output,B12
||         STW     .D2T2   B4,*+SP(52)       ; |174| 

   [ A0]   CALL    .S1     _exp10            ; |170| 
   [!A0]   MVKH    .S2     _output,B12
   [!A0]   LDW     .D2T2   *+B12(16),B4      ; |176| 
   [!A0]   CALL    .S1     _exp10sp_v        ; |176| 
           SPDP    .S1     A3,A5:A4          ; |170| 
           ; BRANCHCC OCCURS {$C$L10}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL23,B3,0      ; |176| 
           MVKL    .S1     _a_ext,A4
           MVKH    .S1     _a_ext,A4
           MVK     .S1     0xed,A6           ; |176| 
$C$RL23:   ; CALL OCCURS {_exp10sp_v} {0}    ; |176| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T2   *B12,B5           ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7
           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MV      .L1X    B5,A4             ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .D1     0x1,A8            ; |66| 

$C$RL24:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6

           LDW     .D2T2   *B12,B5           ; |67| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MV      .L1X    B5,A4             ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL25:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B12,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B4

           LDW     .D2T1   *+SP(76),A3       ; |68| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     _fcn_pass,B4
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L2     B12,B5            ; |68| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL27:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(80),A3       ; |69| 
           LDW     .D2T2   *+SP(84),B5
           MVKL    .S2     _fcn_pass,B4
           MVKH    .S2     _fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L13            ; |72| 
|| [ A0]   LDW     .D2T2   *B5,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |180| 
   [ A0]   ADD     .L2     4,B5,B4
   [!A0]   ZERO    .L1     A3                ; |72| 
   [!A0]   MVKL    .S1     _all_pass,A4
   [!A0]   MVKH    .S1     _all_pass,A4
           ; BRANCHCC OCCURS {$C$L13}        ; |72| 
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
           CALL    .S1     _print_test_results ; |180| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |180| 
||         ADDKPC  .S2     $C$RL28,B3,0      ; |180| 

$C$RL28:   ; CALL OCCURS {_print_test_results} {0}  ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           ZERO    .L2     B5                ; |114| 

           ZERO    .L2     B4                ; |114| 
||         STW     .D2T2   B5,*+SP(92)       ; |114| 

           STW     .D2T2   B4,*+SP(88)       ; |114| 
           LDDW    .D2T2   *+SP(88),B5:B4    ; |114| 
           MVKL    .S2     _cycle_counts+24,B7
           MVKH    .S2     _cycle_counts+24,B7
           ZERO    .L2     B6                ; |114| 
           NOP             1

           STDW    .D2T2   B5:B4,*B7         ; |114| 
||         MVC     .S2     B6,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           STDW    .D1T2   B5:B4,*A3         ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           CALL    .S1     _gimme_random     ; |190| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         ZERO    .L1     A11
||         MVKL    .S1     _t_offset,A4
||         MVK     .S2     0x80,B31

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 
||         MVKH    .S1     0x41a00000,A11

           ADD     .L2     B4,B5,B7          ; |117| 
||         ZERO    .S2     B4
||         MVKH    .S1     _t_offset,A4
||         STW     .D2T2   B31,*+SP(52)      ; |117| 

           STDW    .D1T2   B7:B6,*A4         ; |117| 
||         MV      .L1     A11,A4            ; |190| 
||         MVKH    .S2     0xc1200000,B4
||         ZERO    .L2     B12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL29,B3,0      ; |190| 
$C$RL29:   ; CALL OCCURS {_gimme_random} {0}  ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 105
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T1   *A3,A3            ; |190| 
           NOP             4
           ADD     .L1X    B12,A3,A3         ; |190| 

           STW     .D1T1   A4,*A3            ; |190| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B7           ; |122| 

           LDW     .D2T1   *+SP(20),A3       ; |122| 
||         MVKL    .S2     _output+12,B28
||         MVKL    .S1     _t_start,A26

           LDW     .D2T1   *+SP(24),A31
||         MVKH    .S2     _output+12,B28
||         MVKH    .S1     _t_start,A26

           LDW     .D2T1   *+SP(16),A30
||         STDW    .D1T2   B7:B6,*A26

           LDW     .D2T1   *+SP(28),A29
           LDW     .D2T2   *+SP(32),B4       ; |106| 

           MPYSP   .M1     A3,A4,A5          ; |85| 
||         LDW     .D2T2   *+SP(12),B31

           LDW     .D2T1   *+SP(40),A28      ; |106| 
           LDW     .D2T2   *+SP(36),B29      ; |106| 
           NOP             1

           FADDSP  .L1     A31,A5,A3         ; |85| 
||         CMPLTSP .S1     A5,A30,A0         ; |86| 
||         MPYSP   .M2X    B4,A4,B8          ; |82| 

           NOP             2
           SPTRUNC .L1     A3,A6             ; |85| 
           EXTU    .S2     B8,1,24,B27       ; |109| 
           CMPLTSP .S2     B8,B11,B1         ; |114| 
           CMPGTSP .S2     B8,B10,B0         ; |119| 

   [ A0]   SUB     .S1     A6,1,A6           ; |87| 
||         CMPLTU  .L1X    B27,A13,A0        ; |109| 

           INTSP   .L1     A6,A5             ; |106| 
||         EXTU    .S1     A6,28,30,A4       ; |106| 

           AND     .L2X    3,A6,B30          ; |106| 
||         SHL     .S1     A6,16,A27         ; |106| 

           NOP             2
           MPYSP   .M1     A29,A5,A3         ; |106| 

           MPYSP   .M2X    B31,A5,B4         ; |106| 
||         LDDW    .D1T1   *+A28[A4],A5:A4   ; |106| 

           NOP             3
           FSUBSP  .L2X    B8,A3,B5          ; |106| 
           NOP             2
           FSUBSP  .L2     B5,B4,B9          ; |106| 
           NOP             2
           MPYSP   .M2     B9,B9,B4          ; |106| 
           MPYSP   .M1X    A14,B9,A3         ; |106| 
           NOP             2
           MPYSP   .M2     B4,B9,B5          ; |106| 
           MPYSP   .M1X    A12,B4,A7         ; |106| 
           NOP             2

           MPYSP   .M2     B13,B5,B16        ; |106| 
||         LDDW    .D2T2   *+B29[B30],B5:B4  ; |106| 

           NOP             4

           FADDSP  .L1X    A7,B16,A7         ; |106| 
||         FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |106| 
||         AND     .S1     A15,A27,A5        ; |106| 

           NOP             2
           FADDSP  .L1     A7,A3,A3          ; |106| 
           NOP             1
           ADD     .S1X    A5,B5,A5          ; |106| 

           FADDSP  .L1     A10,A3,A3         ; |106| 
||         MV      .S1X    B4,A4             ; |106| 
||         LDW     .D2T2   *B28,B4           ; |194| 

           NOP             2
           MPYSPDP .M1     A3,A5:A4,A5:A4    ; |106| 
           NOP             1
           ADD     .L2     B12,B4,B4         ; |194| 
           NOP             4
           DPSP    .L1     A5:A4,A3          ; |106| 
           NOP             1

   [ A0]   FADDSP  .L1X    A10,B8,A3         ; |110| 
|| [ B1]   LDW     .D2T1   *+SP(44),A3       ; |194| 

   [ B0]   LDW     .D2T1   *+SP(48),A3       ; |115| 
           NOP             4

           STW     .D2T1   A3,*B4            ; |194| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S1     _t_offset,A3
||         MVKL    .S2     _t_stop,B26
||         ADD     .L2     4,B12,B12         ; |188| 

           MVKH    .S1     _t_offset,A3
||         MVKH    .S2     _t_stop,B26

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         MVKL    .S1     _cycle_counts+24,A3
||         STDW    .D2T2   B9:B8,*B26        ; |128| 

           MVKH    .S1     _cycle_counts+24,A3
           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           NOP             2
           ADDU    .L2X    A4,B6,B5:B4       ; |130| 

           ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         LDW     .D2T2   *+SP(52),B6       ; |130| 

           STDW    .D1T2   B5:B4,*A3         ; |130| 
           NOP             3

           SUB     .L1X    B6,1,A0           ; |188| 
||         SUB     .L2     B6,1,B4           ; |188| 

           STW     .D2T2   B4,*+SP(52)       ; |130| 
|| [ A0]   ZERO    .L2     B4
|| [ A0]   MV      .L1     A11,A4            ; |190| 
|| [ A0]   B       .S1     $C$L14            ; |188| 
|| [!A0]   LDDW    .D1T1   *A3,A5:A4         ; |135| 

   [ A0]   CALL    .S1     _gimme_random     ; |190| 
|| [ A0]   MVKH    .S2     0xc1200000,B4

   [!A0]   CALL    .S1     __fltllif         ; |135| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L14}        ; |188| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL30,B3,1      ; |135| 
$C$RL30:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
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

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL31:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVKL    .S1     _cycle_counts+24,A3

           LDDW    .D2T2   *+SP(88),B5:B4
||         MVKH    .S1     _cycle_counts+24,A3

           MV      .L2X    A12,B31           ; |114| 
           MV      .L2X    A3,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B10

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     _t_start,A14
           MVKH    .S1     _t_start,A14

           STDW    .D1T2   B7:B6,*A14        ; |116| 
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

           MVKL    .S1     _input,A10

           MV      .L1X    B4,A15            ; |117| 
||         MVKH    .S1     _input,A10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A10,A3           ; |202| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |202| 
||         CALL    .S1     _exp10f           ; |202| 

           LDW     .D1T1   *A3,A4            ; |202| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |202| 
$C$RL32:   ; CALL OCCURS {_exp10f} {0}       ; |202| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     _output,B4
||         SUB     .L1     A15,1,A0          ; |201| 
||         SUB     .S1     A15,1,A15         ; |201| 

           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |202| 
   [ A0]   BNOP    .S1     $C$L15,3          ; |201| 

           ADD     .L1X    A12,B4,A3         ; |202| 
||         ADD     .S1     4,A12,A12         ; |201| 

           STW     .D1T1   A4,*A3            ; |202| 
           ; BRANCHCC OCCURS {$C$L15}        ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
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
||         ADDKPC  .S2     $C$RL33,B3,0      ; |130| 

$C$RL33:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(88),B5:B4    ; |130| 
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

           STDW    .D2T2   B5:B4,*B11        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1     A12,A15

           MV      .L1X    B4,A12            ; |117| 
||         LDW     .D2T2   *+SP(56),B13      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A10,A3           ; |210| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |210| 
||         CALL    .S1     _exp10sp          ; |210| 

           LDW     .D1T1   *A3,A4            ; |210| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |210| 
$C$RL35:   ; CALL OCCURS {_exp10sp} {0}      ; |210| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |210| 
||         SUB     .L1     A12,1,A0          ; |209| 
||         SUB     .S1     A12,1,A12         ; |209| 

   [ A0]   BNOP    .S1     $C$L16,3          ; |209| 

           ADD     .L1X    A15,B4,A3         ; |210| 
||         ADD     .S1     4,A15,A15         ; |209| 

           STW     .D1T1   A4,*A3            ; |210| 
           ; BRANCHCC OCCURS {$C$L16}        ; |209| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
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
||         ADDKPC  .S2     $C$RL36,B3,0      ; |130| 

$C$RL36:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(88),B5:B4
           ADDAD   .D2     B10,1,B12
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
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

           STDW    .D2T2   B5:B4,*B11        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1     A12,A15

           MV      .L1X    B4,A12            ; |117| 
||         LDW     .D2T2   *+SP(60),B13      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A10,A3           ; |218| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |218| 
||         CALL    .S1     _exp10sp_c        ; |218| 

           LDW     .D1T1   *A3,A4            ; |218| 
           ADDKPC  .S2     $C$RL38,B3,3      ; |218| 
$C$RL38:   ; CALL OCCURS {_exp10sp_c} {0}    ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |218| 
||         SUB     .L1     A12,1,A0          ; |217| 
||         SUB     .S1     A12,1,A12         ; |217| 

   [ A0]   BNOP    .S1     $C$L17,3          ; |217| 

           ADD     .L1X    A15,B4,A3         ; |218| 
||         ADD     .S1     4,A15,A15         ; |217| 

           STW     .D1T1   A4,*A3            ; |218| 
           ; BRANCHCC OCCURS {$C$L17}        ; |217| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
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
||         ADDKPC  .S2     $C$RL39,B3,0      ; |130| 

$C$RL39:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL40:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           LDDW    .D2T2   *+SP(88),B5:B4
           ADDAD   .D2     B12,1,B13
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
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           MVKL    .S1     _output,A15
||         ADD     .L2     B4,B5,B7          ; |117| 

           MVKH    .S1     _output,A15
||         MV      .L2X    A10,B9            ; |225| 
||         STDW    .D2T2   B7:B6,*B11        ; |117| 

           CALLP   .S2     _exp10sp_v,B3
||         LDW     .D1T2   *+A15(16),B4      ; |225| 
||         LDW     .D2T1   *B9,A4            ; |225| 
||         MVK     .S1     0x80,A6           ; |225| 

$C$RL41:   ; CALL OCCURS {_exp10sp_v} {0}    ; |225| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A17:A16      ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S1     16,A10
           ADD     .L1X    B13,A10,A10
           MVKL    .S1     _t_stop,A3

           LDDW    .D1T1   *A10,A9:A8        ; |130| 
||         MVKH    .S1     _t_stop,A3

           ADDU    .L1X    B6,A16,A7:A6      ; |130| 

           MV      .L2     B4,B9             ; |128| 
||         MV      .S2X    A3,B4             ; |128| 
||         ADD     .L1X    A7,B7,A3          ; |130| 

           SUBU    .L1X    B8,A6,A5:A4       ; |130| 

           ADD     .L1     A3,A17,A5         ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           SUB     .S1X    B9,A5,A6          ; |130| 
||         ADDU    .L1     A8,A4,A5:A4       ; |130| 

           ADD     .L1     A5,A9,A3          ; |130| 
||         ADD     .S1     A6,A3,A5          ; |130| 

           CALLP   .S2     __fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL42:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           MPYSP   .M1     A11,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL43:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6

           STDW    .D1T1   A5:A4,*A10        ; |130| 
||         MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL44:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     _fcn_pass,B10
           MVKH    .S2     0x3ee4f8b5,B7
           MVKH    .S2     0x88e368f1,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S2     _fcn_pass,B10

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A15(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL45:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL46:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(64),A3       ; |68| 
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           LDW     .D1T1   *A15,A4           ; |69| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL47:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(68),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(72),B4
           NOP             3

   [!B0]   B       .S1     $C$L18            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L18}        ; |72| 
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
   [ A0]   B       .S1     $C$L19            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |231| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L19}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |231| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |231| 
||         ADDKPC  .S2     $C$RL48,B3,0      ; |231| 

$C$RL48:   ; CALL OCCURS {_print_test_results} {0}  ; |231| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |232| 

$C$RL49:   ; CALL OCCURS {_printf} {0}       ; |232| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |232| 

$C$RL50:   ; CALL OCCURS {_printf} {0}       ; |232| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |239| 

$C$RL51:   ; CALL OCCURS {_print_profile_results} {0}  ; |239| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |242| 

$C$RL52:   ; CALL OCCURS {_print_memory_results} {0}  ; |242| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(104),B3     ; |243| 
           LDDW    .D2T1   *++SP,A13:A12     ; |243| 
           LDDW    .D2T1   *++SP,A15:A14     ; |243| 
           LDDW    .D2T2   *++SP,B11:B10     ; |243| 
           LDDW    .D2T2   *++SP,B13:B12     ; |243| 

           LDW     .D2T1   *++SP(8),A10      ; |243| 
||         RET     .S2     B3                ; |243| 

           LDW     .D2T1   *++SP(8),A11      ; |243| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |243| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"exp10SP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_exp10f
	.global	_exp10
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_exp10sp
	.global	_exp10sp_c
	.global	_exp10sp_v
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
	.global	_kTable
	.global	_jTable
	.global	__fltllif
	.global	__fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
