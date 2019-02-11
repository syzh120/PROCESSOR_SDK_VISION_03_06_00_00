;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:42:43 2013                                *
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
	.elfsym	a,SYM_SIZE(804)
a:
	.word	0b4000001h		; a[0] @ 0
	.word	03edd9cabh		; a[1] @ 32
	.word	0bf5d9cabh		; a[2] @ 64
	.word	03fa63583h		; a[3] @ 96
	.word	0bfdd9ca6h		; a[4] @ 128
	.word	0400a81e9h		; a[5] @ 160
	.word	0c026357eh		; a[6] @ 192
	.word	04041e914h		; a[7] @ 224
	.word	0c05d9caah		; a[8] @ 256
	.word	040795040h		; a[9] @ 288
	.word	0c08a81e9h		; a[10] @ 320
	.word	040985bb4h		; a[11] @ 352
	.word	0c0a6357eh		; a[12] @ 384
	.word	040b40f49h		; a[13] @ 416
	.word	0c0c1e912h		; a[14] @ 448
	.word	040cfc2ddh		; a[15] @ 480
	.word	0c0dd9ca8h		; a[16] @ 512
	.word	040eb7673h		; a[17] @ 544
	.word	0c0f9503eh		; a[18] @ 576
	.word	041039504h		; a[19] @ 608
	.word	0c10a81e9h		; a[20] @ 640
	.word	041116eceh		; a[21] @ 672
	.word	0c1185bb4h		; a[22] @ 704
	.word	0411f4899h		; a[23] @ 736
	.word	0c126357eh		; a[24] @ 768
	.word	0412d2268h		; a[25] @ 800
	.word	0c1340f47h		; a[26] @ 832
	.word	0413afc31h		; a[27] @ 864
	.word	0c141e910h		; a[28] @ 896
	.word	04148d5fah		; a[29] @ 928
	.word	0c14fc2d9h		; a[30] @ 960
	.word	04156afc2h		; a[31] @ 992
	.word	0c15d9cach		; a[32] @ 1024
	.word	04164898bh		; a[33] @ 1056
	.word	0c16b7675h		; a[34] @ 1088
	.word	041726354h		; a[35] @ 1120
	.word	0c179503eh		; a[36] @ 1152
	.word	041801e94h		; a[37] @ 1184
	.word	0c1839503h		; a[38] @ 1216
	.word	041870b78h		; a[39] @ 1248
	.word	0c18a81e8h		; a[40] @ 1280
	.word	0418df85ch		; a[41] @ 1312
	.word	0c1916ecch		; a[42] @ 1344
	.word	04194e541h		; a[43] @ 1376
	.word	0c1985bb6h		; a[44] @ 1408
	.word	0419bd225h		; a[45] @ 1440
	.word	0c19f489ah		; a[46] @ 1472
	.word	041a2bf0ah		; a[47] @ 1504
	.word	0c1a6357eh		; a[48] @ 1536
	.word	041a9abf3h		; a[49] @ 1568
	.word	0c1ad2263h		; a[50] @ 1600
	.word	041b098d8h		; a[51] @ 1632
	.word	0c1b40f47h		; a[52] @ 1664
	.word	041b785bch		; a[53] @ 1696
	.word	0c1bafc2ch		; a[54] @ 1728
	.word	041be72a0h		; a[55] @ 1760
	.word	0c1c1e915h		; a[56] @ 1792
	.word	041c55f85h		; a[57] @ 1824
	.word	0c1c8d5fah		; a[58] @ 1856
	.word	041cc4c69h		; a[59] @ 1888
	.word	0c1cfc2deh		; a[60] @ 1920
	.word	041d3394eh		; a[61] @ 1952
	.word	0c1d6afc2h		; a[62] @ 1984
	.word	041da2637h		; a[63] @ 2016
	.word	0c1dd9ca7h		; a[64] @ 2048
	.word	041e1131ch		; a[65] @ 2080
	.word	0c1e4898bh		; a[66] @ 2112
	.word	041e834d7h		; a[67] @ 2144
	.word	0c1eb7675h		; a[68] @ 2176
	.word	041eeece4h		; a[69] @ 2208
	.word	0c1f26359h		; a[70] @ 2240
	.word	041f5d9c9h		; a[71] @ 2272
	.word	0c1f9503eh		; a[72] @ 2304
	.word	041fcc6b2h		; a[73] @ 2336
	.word	0c2001e91h		; a[74] @ 2368
	.word	04201d9cbh		; a[75] @ 2400
	.word	0c2039503h		; a[76] @ 2432
	.word	04205503eh		; a[77] @ 2464
	.word	0c2070b75h		; a[78] @ 2496
	.word	04208c6b0h		; a[79] @ 2528
	.word	0c20a81eah		; a[80] @ 2560
	.word	0420c3d22h		; a[81] @ 2592
	.word	0c20df85ch		; a[82] @ 2624
	.word	0420fb394h		; a[83] @ 2656
	.word	0c2116ecfh		; a[84] @ 2688
	.word	042132a09h		; a[85] @ 2720
	.word	0c214e541h		; a[86] @ 2752
	.word	04216a07bh		; a[87] @ 2784
	.word	0c2185bb3h		; a[88] @ 2816
	.word	0421a16edh		; a[89] @ 2848
	.word	0c21bd225h		; a[90] @ 2880
	.word	0421d8d60h		; a[91] @ 2912
	.word	0c21f489ah		; a[92] @ 2944
	.word	0422103d2h		; a[93] @ 2976
	.word	0c222bf0ch		; a[94] @ 3008
	.word	042247a44h		; a[95] @ 3040
	.word	0c226357eh		; a[96] @ 3072
	.word	04227f0b6h		; a[97] @ 3104
	.word	0c229abf1h		; a[98] @ 3136
	.word	0422b672bh		; a[99] @ 3168
	.word	0c22d2263h		; a[100] @ 3200
	.word	0422edd9dh		; a[101] @ 3232
	.word	0c23098d5h		; a[102] @ 3264
	.word	04232540fh		; a[103] @ 3296
	.word	0c2340f4ah		; a[104] @ 3328
	.word	04235ca82h		; a[105] @ 3360
	.word	0c23785bch		; a[106] @ 3392
	.word	0423940f4h		; a[107] @ 3424
	.word	0c23afc2eh		; a[108] @ 3456
	.word	0423cb766h		; a[109] @ 3488
	.word	0c23e72a0h		; a[110] @ 3520
	.word	042402ddbh		; a[111] @ 3552
	.word	0c241e913h		; a[112] @ 3584
	.word	04243a44dh		; a[113] @ 3616
	.word	0c2455f85h		; a[114] @ 3648
	.word	042471abfh		; a[115] @ 3680
	.word	0c248d5f7h		; a[116] @ 3712
	.word	0424a9131h		; a[117] @ 3744
	.word	0c24c4c6ch		; a[118] @ 3776
	.word	0424e07a4h		; a[119] @ 3808
	.word	0c24fc2deh		; a[120] @ 3840
	.word	042517e16h		; a[121] @ 3872
	.word	0c2533950h		; a[122] @ 3904
	.word	04254f48bh		; a[123] @ 3936
	.word	0c256afc2h		; a[124] @ 3968
	.word	042586afdh		; a[125] @ 4000
	.word	0c25a2637h		; a[126] @ 4032
	.word	0425be16fh		; a[127] @ 4064
	.word	0c25d9ca7h		; a[128] @ 4096
	.word	0425f57e1h		; a[129] @ 4128
	.word	0c261131ch		; a[130] @ 4160
	.word	04262ce53h		; a[131] @ 4192
	.word	0c264898eh		; a[132] @ 4224
	.word	0426644c8h		; a[133] @ 4256
	.word	0c2680292h		; a[134] @ 4288
	.word	04269bb38h		; a[135] @ 4320
	.word	0c26b7672h		; a[136] @ 4352
	.word	0426d31adh		; a[137] @ 4384
	.word	0c26eece4h		; a[138] @ 4416
	.word	04270a81fh		; a[139] @ 4448
	.word	0c2726359h		; a[140] @ 4480
	.word	042741e91h		; a[141] @ 4512
	.word	0c275d9cbh		; a[142] @ 4544
	.word	042779503h		; a[143] @ 4576
	.word	0c279503eh		; a[144] @ 4608
	.word	0427b0b75h		; a[145] @ 4640
	.word	0c27cc6b0h		; a[146] @ 4672
	.word	0427e81eah		; a[147] @ 4704
	.word	0c2801e91h		; a[148] @ 4736
	.word	04280fc2eh		; a[149] @ 4768
	.word	0c281d9cbh		; a[150] @ 4800
	.word	04282b767h		; a[151] @ 4832
	.word	0c2839505h		; a[152] @ 4864
	.word	0428472a0h		; a[153] @ 4896
	.word	0c285503eh		; a[154] @ 4928
	.word	042862dd9h		; a[155] @ 4960
	.word	0c2870b75h		; a[156] @ 4992
	.word	04287e913h		; a[157] @ 5024
	.word	0c288c6b0h		; a[158] @ 5056
	.word	04289a44ch		; a[159] @ 5088
	.word	0c28a81e9h		; a[160] @ 5120
	.word	0428b5f86h		; a[161] @ 5152
	.word	0c28c3d22h		; a[162] @ 5184
	.word	0428d1abfh		; a[163] @ 5216
	.word	0c28df85ch		; a[164] @ 5248
	.word	0428ed5f8h		; a[165] @ 5280
	.word	0c28fb396h		; a[166] @ 5312
	.word	042909131h		; a[167] @ 5344
	.word	0c2916ecfh		; a[168] @ 5376
	.word	042924c6ah		; a[169] @ 5408
	.word	0c2932a08h		; a[170] @ 5440
	.word	0429407a4h		; a[171] @ 5472
	.word	0c294e541h		; a[172] @ 5504
	.word	04295c2deh		; a[173] @ 5536
	.word	0c296a07ah		; a[174] @ 5568
	.word	042977e17h		; a[175] @ 5600
	.word	0c2985bb4h		; a[176] @ 5632
	.word	042993950h		; a[177] @ 5664
	.word	0c29a16edh		; a[178] @ 5696
	.word	0429af48bh		; a[179] @ 5728
	.word	0c29bd227h		; a[180] @ 5760
	.word	0429cafc2h		; a[181] @ 5792
	.word	0c29d8d60h		; a[182] @ 5824
	.word	0429e6afbh		; a[183] @ 5856
	.word	0c29f4899h		; a[184] @ 5888
	.word	042a02636h		; a[185] @ 5920
	.word	0c2a103d2h		; a[186] @ 5952
	.word	042a1e16fh		; a[187] @ 5984
	.word	0c2a2bf0bh		; a[188] @ 6016
	.word	042a39ca8h		; a[189] @ 6048
	.word	0c2a47a45h		; a[190] @ 6080
	.word	042a557e1h		; a[191] @ 6112
	.word	0c2a6357eh		; a[192] @ 6144
	.word	042a7131ch		; a[193] @ 6176
	.word	0c2a7f0b8h		; a[194] @ 6208
	.word	042a8ce53h		; a[195] @ 6240
	.word	0c2a9abf1h		; a[196] @ 6272
	.word	042aa898ch		; a[197] @ 6304
	.word	0c2ab672ah		; a[198] @ 6336
	.word	042ac44c7h		; a[199] @ 6368
	.word	0c2ad2263h		; a[200] @ 6400

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\156922 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\156924 
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
;*   Local Frame Size  : 8 Args + 60 Auto + 56 Save = 124 byte                *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |122| 
           STW     .D2T1   A10,*SP--(8)      ; |122| 
           STDW    .D2T2   B13:B12,*SP--     ; |122| 
           STDW    .D2T2   B11:B10,*SP--     ; |122| 
           STDW    .D2T1   A15:A14,*SP--     ; |122| 

           STDW    .D2T1   A13:A12,*SP--     ; |122| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(80)      ; |122| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |131| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     0xc9,B4
||         MVKL    .S1     a,A11

           MVKH    .S1     a,A11

           CALL    .S1     expf              ; |140| 
||         MV      .L1     A11,A12
||         MV      .D1X    B4,A10
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |140| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |140| 
$C$RL1:    ; CALL OCCURS {expf} {0}          ; |140| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A10,1,A0          ; |139| 
||         SUB     .S1     A10,1,A10         ; |139| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |140| 
   [ A0]   BNOP    .S1     $C$L1,3           ; |139| 

           ADD     .L2     B10,B4,B4         ; |140| 
||         ADD     .S2     4,B10,B10         ; |139| 

   [ A0]   CALL    .S1     expf              ; |140| 
||         STW     .D2T1   A4,*B4            ; |140| 
|| [!A0]   MVKL    .S2     output,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           ZERO    .L2     B10
||         MVKH    .S2     output,B4

           ADD     .L2     4,B4,B11
||         MVK     .S2     0xc9,B4

           MV      .L1     A11,A15

           MV      .L1X    B4,A10
||         CALL    .S1     expsp             ; |143| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |143| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |143| 
$C$RL2:    ; CALL OCCURS {expsp} {0}         ; |143| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |143| 
||         SUB     .L1     A10,1,A0          ; |142| 
||         SUB     .S1     A10,1,A10         ; |142| 

   [ A0]   BNOP    .S1     $C$L2,3           ; |142| 

           ADD     .L2     B10,B4,B4         ; |143| 
||         ADD     .S2     4,B10,B10         ; |142| 

   [ A0]   CALL    .S1     expsp             ; |143| 
||         STW     .D2T1   A4,*B4            ; |143| 
|| [!A0]   MVK     .S2     0xc9,B4

           ; BRANCHCC OCCURS {$C$L2}         ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           ZERO    .L2     B10
||         MV      .L1     A15,A11
||         ADD     .S2     4,B11,B11

           MV      .L1X    B4,A10
||         CALL    .S1     expsp_c           ; |146| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |146| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |146| 
$C$RL3:    ; CALL OCCURS {expsp_c} {0}       ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |146| 
||         SUB     .L1     A10,1,A0          ; |145| 
||         SUB     .S1     A10,1,A10         ; |145| 

   [!A0]   MVKL    .S1     kTable,A10
|| [!A0]   ZERO    .L1     A5
|| [!A0]   ZERO    .D1     A14
|| [!A0]   ZERO    .L2     B5
|| [ A0]   B       .S2     $C$L3             ; |145| 

   [!A0]   MVKL    .S1     0x3e2aab29,A11
|| [!A0]   MVKL    .S2     0x3f00010f,B7

   [!A0]   MVKL    .S2     0xfef2e4e7,B31
   [!A0]   MVKL    .S2     jTable,B6

           ADD     .L2     B10,B4,B4         ; |146| 
||         ADD     .D2     4,B10,B10         ; |145| 
|| [!A0]   MVKL    .S2     0x42b17218,B12

           STW     .D2T1   A4,*B4            ; |146| 
|| [!A0]   MVKL    .S1     0xc2aeac50,A4
|| [ A0]   CALL    .S2     expsp_c           ; |146| 

           ; BRANCHCC OCCURS {$C$L3}         ; |145| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           SET     .S2     B5,0x17,0x1d,B16
||         MVKL    .S1     0x7f7fffff,A31
||         ZERO    .L2     B5
||         ZERO    .D2     B30

           MVKL    .S2     0x41b8aa3b,B4
||         MVKH    .S1     kTable,A10
||         ADD     .L2     4,B11,B11
||         STW     .D2T2   B30,*+SP(24)

           MVKL    .S2     0x3fa62e42,B8
||         MVKH    .S1     0xfff00000,A14
||         LDW     .D2T1   *B11,A3
||         MV      .L2     B16,B25

           MVKH    .S2     0x3f00010f,B7
||         SET     .S1     A5,0x18,0x1d,A5
||         MV      .L2X    A10,B20
||         ZERO    .D2     B18

           MVKH    .S2     0xfef2e4e7,B31
||         MVKH    .S1     0x3e2aab29,A11
||         STW     .D2T2   B7,*+SP(12)
||         MV      .L2X    A14,B19

           MVKH    .S2     jTable,B6
||         MVKH    .S1     0x7f7fffff,A31
||         STW     .D2T2   B31,*+SP(32)      ; |98| 
||         MV      .L1X    B7,A9
||         MV      .L2X    A5,B22

           MVKH    .S2     0x42b17218,B12
||         MVK     .S1     0xc9,A7
||         MV      .L1     A31,A16
||         STW     .D2T1   A31,*+SP(28)
||         MV      .L2X    A11,B21

           MVKH    .S2     0xbf000000,B5
||         MVKH    .S1     0xc2aeac50,A4
||         MV      .L1X    B6,A8
||         STW     .D2T2   B6,*+SP(20)
||         SUB     .D1     A7,1,A1
||         MV      .L2X    A15,B17

           MVKH    .S2     0x41b8aa3b,B4
||         MV      .L1X    B12,A6
||         STW     .D2T2   B5,*+SP(16)
||         MV      .S1     A4,A7
||         MV      .L2     B5,B24

           MVKH    .S2     0x3fa62e42,B8
||         MV      .L2     B4,B23

           STW     .D2T2   B8,*+SP(36)       ; |98| 
||         MV      .L2     B8,B9
||         DINT                              ; interrupts off

           LDW     .D2T2   *+SP(32),B8
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/expsp/expsp_d.c
;*      Loop source line                 : 148
;*      Loop opening brace source line   : 148
;*      Loop closing brace source line   : 150
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 60
;*      Unpartitioned Resource Bound     : 5
;*      Partitioned Resource Bound(*)    : 8
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     1        4     
;*      .S units                     3        5     
;*      .D units                     2        2     
;*      .M units                     2        6     
;*      .X cross paths               6        3     
;*      .T address paths             1        3     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        5     (.L or .S unit)
;*      Addition ops (.LSD)          3        6     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             2        7     
;*      Bound(.L .S .D .LS .LSD)     3        8*    
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 60 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: | * *  ****      *               |        **       *********      |
;*       1: | * *  ****      *               |        **       *********      |
;*       2: | * *  ****      *               |        **       *********      |
;*       3: | * *  ****      *               |        **       *********      |
;*       4: | * *  ****      *               |        **       *********      |
;*       5: | * *  ****      *               |        **       **********     |
;*       6: | * *  ****      *               |        **       **********     |
;*       7: | * *  ****      *               |        **       **********     |
;*       8: | * *  ****      *               |        **       **********     |
;*       9: | * *  ****      *               |     *  **       **********     |
;*      10: | * *  ****      *               |     *  **       **********     |
;*      11: | * *  ****      *               |     *  **       **********     |
;*      12: | * *  ****      *               |    **  **       **********     |
;*      13: | * *  ****      *               |     *  **       **********     |
;*      14: | * *  ****      *               |     *  **       **********     |
;*      15: | * *  ****      *               |     *  **       **********     |
;*      16: | * *  ****      *               |    **  **       **********     |
;*      17: | * *  ****      *               |    **  **       **********     |
;*      18: | * *  ****      *               |    **  **      ***********     |
;*      19: | * ** ****      *               |    *   **      ***********     |
;*      20: | * ** ****      *               |        **      ************    |
;*      21: | * ** ****      *               |        **      ************    |
;*      22: | * ** ****      *               |    **  **      ************    |
;*      23: | * ** ****      *               |        **      ************    |
;*      24: | * ** ****      *               |        **      ************    |
;*      25: | * ** ****      *               |        **      ************    |
;*      26: | * ** ****      *               |    ******      ************    |
;*      27: | * ** ****      *               |        **      ************    |
;*      28: | * ** ****      *               |        **      ************    |
;*      29: | * ** ****      *               |    **  **      ************    |
;*      30: | * ** ****      *               |        **      ************    |
;*      31: | * ** ****      *               |        **      ************    |
;*      32: | * ** ****      *               |        **      ************    |
;*      33: | * ** ****      *               |      * **      ************    |
;*      34: | * ** ****      *               |      * **      ************    |
;*      35: | * ** ****      *               |      * **      ************    |
;*      36: | * ** ****      *               |      * **      ************    |
;*      37: | * ** ****      *               |    * * **      ************    |
;*      38: | * ** ****      *               |    * * **      ************    |
;*      39: | * ** ****      *               |      * **      ************    |
;*      40: | * *  ****      *               |      * **       ***********    |
;*      41: | * *  ****      *               |    * * **       ***********    |
;*      42: | * *  ****      **              |      * **       ***********    |
;*      43: | * *  ****      **              |      * **       ***********    |
;*      44: | * *******      **              |    *** **       ***********    |
;*      45: | * *  ****      **              |    * * **       ***********    |
;*      46: | * *  ****      *               |      * **       ***********    |
;*      47: | * *  ****      *               |      * **       ***********    |
;*      48: | * *******      *               |    * * **       ***********    |
;*      49: | * *******      *               |        **       **********     |
;*      50: | * *  ****      *               |        **       **********     |
;*      51: | * *  ****      *               |    *   **       **********     |
;*      52: | * *  ****      *               |        **       **********     |
;*      53: | * ** ****      *               |        **       **********     |
;*      54: |** ** ****      *               |    *   **       **********     |
;*      55: | * *  ****      *               |    *   **       **********     |
;*      56: | * *  ****      *               |    *   **       **********     |
;*      57: | * *  ****      *               |    *   **       **********     |
;*      58: |** *  ****      *               |    *   **       *********      |
;*      59: | * *  ****      *               |    **  **       *********      |
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
;*      Effective ii                : { min 60.00, est 60.25, max 61.00 }
;*
;*
;*      Total cycles (est.)         : 0 + min_trip_cnt * 60 = 12060        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A1,1,A1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C103:
;*   0              LDW     .D2T2   *B17++,B26        ; |98|  ^ 
;*   1              NOP             4
;*   5              MPYSP   .M2     B23,B26,B5        ; |98|  ^ 
;*   6              NOP             3
;*   9              FADDSP  .L2     B22,B5,B4         ; |98|  ^ 
;*  10              NOP             2
;*  12              SPTRUNC .L2     B4,B5             ; |98|  ^ 
;*  13              NOP             2
;*  15              CMPLTSP .S2     B5,B24,B4         ; |98| 
;*  16              SUB     .S2     B5,B4,B4          ; |98|  ^ 
;*     ||           SUB     .L2     B5,B4,B5          ; |98| 
;*  17              INTDP   .L2     B4,B5:B4          ; |98|  ^ 
;*     ||           EXTU    .S2     B4,28,30,B16      ; |98| 
;*  18              AND     .L1X    3,B4,A4           ; |98| 
;*     ||           SHL     .S2     B5,16,B4          ; |98| 
;*  19              AND     .L2     B19,B4,B27        ; |98| 
;*  20              NOP             2
;*  22              FMPYDP  .M2     B9:B8,B5:B4,B7:B6 ; |98|  ^ 
;*  23              NOP             1
;*  24              SPDP    .S2     B26,B5:B4         ; |98| 
;*  25              NOP             1
;*  26              FSUBDP  .L2     B5:B4,B7:B6,B5:B4 ; |98|  ^ 
;*  27              NOP             2
;*  29              DPSP    .L2     B5:B4,B6          ; |98|  ^ 
;*  30              NOP             3
;*  33              MPYSP   .M2     B6,B6,B4          ; |98|  ^ 
;*  34              NOP             3
;*  37              MPYSP   .M2     B4,B6,B4          ; |98|  ^ 
;*  38              MPYSP   .M1X    A9,B4,A17         ; |98| 
;*  39              LDDW    .D2T2   *+B20[B16],B5:B4  ; |98| 
;*     ||           LDDW    .D1T1   *+A8[A4],A5:A4    ; |98| 
;*  40              NOP             1
;*  41              MPYSP   .M2     B21,B4,B4         ; |98|  ^ 
;*  42              NOP             2
;*  44              FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |98| 
;*  45              FADDSP  .L2X    A17,B4,B4         ; |98|  ^ 
;*  46              NOP             2
;*  48              ADD     .L1X    B27,A5,A5         ; |98| 
;*     ||           FADDSP  .L2     B4,B6,B4          ; |98|  ^ 
;*  49              DPSP    .L1     A5:A4,A4          ; |98| 
;*  50              NOP             1
;*  51              FADDSP  .L2     B25,B4,B4         ; |98|  ^ 
;*  52              NOP             1
;*  53              CMPLTSP .S1X    B26,A7,A0         ; |98| 
;*  54      [ A0]   MV      .L2     B18,B4            ; |98| 
;*     ||   [!A0]   MPYSP   .M2X    B4,A4,B4          ; |98|  ^ 
;*     ||   [ A1]   BDEC    .S1     $C$C103,A1        ; |148| 
;*  55              NOP             2
;*  57              CMPGTSP .S1X    B26,A6,A0         ; |98| 
;*  58      [!A0]   MV      .S2     B4,B5             ; |98|  ^ 
;*     ||   [ A0]   MV      .L2X    A16,B5            ; |98| Define a twin register
;*  59              STW     .D1T2   B5,*A3++          ; |98|  ^ 
;*  60              ; BRANCHCC OCCURS {$C$C103}       ; |148| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 60
           LDW     .D2T2   *B17++,B26        ; |98| <0,0>  ^ 
           NOP             4
           MPYSP   .M2     B23,B26,B5        ; |98| <0,5>  ^ 
           NOP             3
           FADDSP  .L2     B22,B5,B4         ; |98| <0,9>  ^ 
           NOP             2
           SPTRUNC .L2     B4,B5             ; |98| <0,12>  ^ 
           NOP             2
           CMPLTSP .S2     B5,B24,B4         ; |98| <0,15> 

           SUB     .L2     B5,B4,B5          ; |98| <0,16> 
||         SUB     .S2     B5,B4,B4          ; |98| <0,16>  ^ 

           EXTU    .S2     B4,28,30,B16      ; |98| <0,17> 
||         INTDP   .L2     B4,B5:B4          ; |98| <0,17>  ^ 

           SHL     .S2     B5,16,B4          ; |98| <0,18> 
||         AND     .L1X    3,B4,A4           ; |98| <0,18> 

           AND     .L2     B19,B4,B27        ; |98| <0,19> 
           NOP             2
           FMPYDP  .M2     B9:B8,B5:B4,B7:B6 ; |98| <0,22>  ^ 
           NOP             1
           SPDP    .S2     B26,B5:B4         ; |98| <0,24> 
           NOP             1
           FSUBDP  .L2     B5:B4,B7:B6,B5:B4 ; |98| <0,26>  ^ 
           NOP             2
           DPSP    .L2     B5:B4,B6          ; |98| <0,29>  ^ 
           NOP             3
           MPYSP   .M2     B6,B6,B4          ; |98| <0,33>  ^ 
           NOP             3
           MPYSP   .M2     B4,B6,B4          ; |98| <0,37>  ^ 
           MPYSP   .M1X    A9,B4,A17         ; |98| <0,38> 

           LDDW    .D2T2   *+B20[B16],B5:B4  ; |98| <0,39> 
||         LDDW    .D1T1   *+A8[A4],A5:A4    ; |98| <0,39> 

           NOP             1
           MPYSP   .M2     B21,B4,B4         ; |98| <0,41>  ^ 
           NOP             2
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |98| <0,44> 
           FADDSP  .L2X    A17,B4,B4         ; |98| <0,45>  ^ 
           NOP             2

           ADD     .L1X    B27,A5,A5         ; |98| <0,48> 
||         FADDSP  .L2     B4,B6,B4          ; |98| <0,48>  ^ 

           DPSP    .L1     A5:A4,A4          ; |98| <0,49> 
           NOP             1
           FADDSP  .L2     B25,B4,B4         ; |98| <0,51>  ^ 
           NOP             1
           CMPLTSP .S1X    B26,A7,A0         ; |98| <0,53> 

   [ A0]   MV      .L2     B18,B4            ; |98| <0,54> 
|| [ A1]   BDEC    .S1     $C$L5,A1          ; |148| <0,54> 
|| [!A0]   MPYSP   .M2X    B4,A4,B4          ; |98| <0,54>  ^ 

           NOP             2
           CMPGTSP .S1X    B26,A6,A0         ; |98| <0,57> 

   [ A0]   MV      .L2X    A16,B5            ; |98| <0,58> Define a twin register
|| [!A0]   MV      .S2     B4,B5             ; |98| <0,58>  ^ 

           STW     .D1T2   B5,*A3++          ; |98| <0,59>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           STW     .D2T2   B18,*+SP(24)
           STW     .D2T1   A16,*+SP(28)
           STW     .D2T2   B9,*+SP(36)

           MV      .L1X    B19,A14
||         STW     .D2T2   B8,*+SP(32)

           MVKL    .S2     output,B4
||         MV      .L1X    B20,A10
||         STW     .D2T1   A9,*+SP(12)

           MVKH    .S2     output,B4
||         MV      .L2X    A6,B12
||         MV      .L1X    B21,A11
||         STW     .D2T1   A8,*+SP(20)

           MV      .L2X    A7,B13
||         MV      .L1X    B22,A12
||         STW     .D2T2   B24,*+SP(16)
||         RINT                              ; interrupts on

           CALLP   .S2     expsp_v,B3
||         LDW     .D2T2   *+B4(16),B4       ; |151| 
||         MVK     .S1     0xc9,A6           ; |151| 
||         MV      .L1     A15,A4            ; |151| 
||         MV      .D1X    B23,A13
||         MV      .L2     B25,B10

$C$RL4:    ; CALL OCCURS {expsp_v} {0}       ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           MVKL    .S2     output,B4
           MVKL    .S2     output,B5
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     output,B4
           MVKH    .S2     output,B5
           MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B4(4),B4        ; |66| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     output,B4
           MVKL    .S2     0xa0b5ed8d,B6

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0x3eb0c6f7,B7

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     output,B4

           STW     .D1T1   A4,*+A3(4)        ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D2T1   *B4,A4            ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B4(8),B4        ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S1     output,A3

           MVKL    .S1     fcn_pass,A5
||         MVKL    .S2     0x3eb0c6f7,B7

           MVKH    .S1     output,A3
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     fcn_pass,A5
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L2X    A3,B4             ; |66| 
||         STW     .D1T1   A4,*+A5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B4(12),B4       ; |68| 
||         LDW     .D1T1   *A3,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 

           MVKL    .S1     fcn_pass,A5
||         MVKL    .S2     0x3eb0c6f7,B7

           MVKL    .S1     output,A3
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     fcn_pass,A5
||         ADD     .L2     4,B11,B4
||         MVKH    .S2     0x3eb0c6f7,B7

           MVKH    .S1     output,A3
||         STW     .D1T1   A4,*+A5(12)       ; |68| 
||         STW     .D2T2   B4,*+SP(40)
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         LDW     .D2T2   *B4,B4            ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S2     fcn_pass,B4
||         MVKL    .S1     fcn_pass,A3

           MVKH    .S2     fcn_pass,B4
||         MVKH    .S1     fcn_pass,A3

           ADD     .L2     4,B4,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D1T1   A4,*+A3(16)       ; |69| 
           STW     .D2T2   B4,*+SP(44)
           ADD     .L2X    8,A3,B4
           STW     .D2T2   B4,*+SP(48)       ; |69| 

   [!B0]   B       .S2     $C$L7             ; |72| 
|| [!B0]   MVKL    .S1     all_pass,A3
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [!B0]   ZERO    .D2     B4                ; |72| 

   [!B0]   CALL    .S2     print_test_results ; |157| 
|| [!B0]   MVKH    .S1     all_pass,A3
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
           CALL    .S1     print_test_results ; |157| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |157| 
||         STW     .D1T2   B4,*A3            ; |72| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |157| 

$C$RL9:    ; CALL OCCURS {print_test_results} {0}  ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T1   *+SP(32),A31
           LDW     .D2T1   *+SP(36),A3

           LDW     .D2T1   *+SP(24),A6
||         MVK     .L2     0x8,B31
||         MVKL    .S2     a_sc,B6

           STW     .D2T2   B11,*+SP(52)
||         MVKH    .S2     a_sc,B6
||         ZERO    .L2     B5

           STW     .D2T2   B31,*+SP(32)      ; |167| 
||         MVKH    .S2     0xbf800000,B5
||         MV      .L2     B10,B4            ; |169| 

           STDW    .D2T2   B5:B4,*+B6(16)    ; |169| 
||         ZERO    .L1     A7

           STW     .D2T1   A31,*+SP(64)
||         MVKH    .S1     0x80000000,A7

           STW     .D2T1   A3,*+SP(68)
||         ADD     .L1     -1,A7,A8
||         MVKL    .S1     0x7f7fffff,A30
||         MVK     .D1     -1,A9             ; |171| 

           STDW    .D2T1   A9:A8,*+B6(24)    ; |171| 
||         MVKH    .S1     0x7f7fffff,A30
||         ZERO    .L1     A5

           STDW    .D2T1   A7:A6,*B6         ; |165| 
||         MV      .L2     B6,B4
||         ADD     .L1     1,A30,A4
||         MVKH    .S1     0xff800000,A5

           CALL    .S1     expf              ; |174| 
||         STDW    .D2T1   A5:A4,*+B4(8)     ; |167| 
||         MV      .L1X    B6,A15            ; |165| 
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
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A15,A4           ; |174| 
           ADDKPC  .S2     $C$RL10,B3,3      ; |174| 
$C$RL10:   ; CALL OCCURS {expf} {0}          ; |174| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A3            ; |174| 
           NOP             4
           ADD     .L2X    B11,A3,B4         ; |174| 
           STW     .D2T1   A4,*B4            ; |174| 

           CALLP   .S2     expsp,B3
||         LDW     .D1T1   *A15,A4           ; |175| 

$C$RL11:   ; CALL OCCURS {expsp} {0}         ; |175| 
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *+A3(4),A3        ; |175| 
           NOP             4
           ADD     .L2X    B11,A3,B4         ; |175| 
           STW     .D2T1   A4,*B4            ; |175| 

           CALLP   .S2     expsp_c,B3
||         LDW     .D1T1   *A15,A4           ; |176| 

$C$RL12:   ; CALL OCCURS {expsp_c} {0}       ; |176| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 71
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *+A3(8),A3        ; |176| 
           LDW     .D2T2   *+SP(16),B31
           LDDW    .D2T1   *+SP(64),A7:A6
           LDW     .D2T2   *+SP(20),B30      ; |100| 
           LDW     .D2T2   *+SP(12),B6       ; |100| 
           ADD     .L2X    B11,A3,B4         ; |176| 
           STW     .D2T1   A4,*B4            ; |176| 
           LDW     .D1T1   *A15++,A8         ; |177| 
           LDW     .D2T2   *+SP(52),B29      ; |100| 
           NOP             3
           MPYSP   .M1     A13,A8,A4         ; |79| 
           CMPLTSP .S2X    A8,B13,B1         ; |103| 
           CMPGTSP .S2X    A8,B12,B2         ; |108| 
           NOP             1
           FADDSP  .L1     A12,A4,A3         ; |79| 
           CMPLTSP .S2X    A4,B31,B0         ; |80| 
           NOP             1
           SPTRUNC .L1     A3,A3             ; |79| 
           NOP             3
   [ B0]   SUB     .L1     A3,1,A3           ; |81| 
           INTDP   .L1     A3,A5:A4          ; |100| 
           EXTU    .S1     A3,28,30,A31      ; |100| 
           AND     .L2X    3,A3,B5           ; |100| 
           LDDW    .D2T2   *+B30[B5],B5:B4   ; |100| 
           SHL     .S1     A3,16,A30         ; |100| 
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |100| 
           SPDP    .S1     A8,A5:A4          ; |100| 
           AND     .L1     A14,A30,A3        ; |100| 
           NOP             1
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |100| 
           NOP             2
           DPSP    .L1     A5:A4,A6          ; |100| 
           LDDW    .D1T1   *+A10[A31],A5:A4  ; |100| 
           NOP             2
           MPYSP   .M1     A6,A6,A7          ; |100| 
           NOP             1
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |100| 
           NOP             1
           MPYSP   .M1     A7,A6,A9          ; |100| 
           MPYSP   .M2X    B6,A7,B6          ; |100| 
           ADD     .L2X    A3,B5,B5          ; |100| 

           DPSP    .L2     B5:B4,B5          ; |100| 
||         LDW     .D2T2   *B29,B4           ; |177| 

           MPYSP   .M1     A11,A9,A9         ; |100| 
           NOP             3

           ADD     .L2     B11,B4,B28        ; |177| 
||         LDW     .D2T2   *+SP(32),B4       ; |109| 

           FADDSP  .L2X    B6,A9,B6          ; |100| 
           ADD     .L2     4,B11,B11         ; |173| 
           NOP             1
           FADDSP  .L2X    B6,A6,B6          ; |100| 

           SUB     .L1X    B4,1,A0           ; |173| 
||         SUB     .L2     B4,1,B4           ; |173| 

           STW     .D2T2   B4,*+SP(32)       ; |177| 
           FADDSP  .L2     B10,B6,B6         ; |100| 
   [!A0]   MVKL    .S2     output,B11
   [!A0]   MVKH    .S2     output,B11

           MPYSP   .M2     B6,B5,B5          ; |100| 
|| [ B1]   LDW     .D2T2   *+SP(24),B5       ; |108| 

   [ A0]   BNOP    .S1     $C$L8,4           ; |173| 
|| [ B2]   LDW     .D2T2   *+SP(28),B5       ; |104| 

   [ A0]   CALL    .S1     expf              ; |174| 
||         STW     .D2T2   B5,*B28           ; |177| 

           ; BRANCHCC OCCURS {$C$L8}         ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     expsp_v           ; |179| 
           LDW     .D2T2   *+B11(16),B4      ; |179| 
           MVKL    .S1     a_sc,A4
           MVKH    .S1     a_sc,A4
           ADDKPC  .S2     $C$RL13,B3,0      ; |179| 
           MVK     .L1     0x8,A6            ; |179| 
$C$RL13:   ; CALL OCCURS {expsp_v} {0}       ; |179| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .L1     0x8,A6            ; |66| 
||         MVK     .S1     0x9,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .L1     0x8,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1X    B11,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .L1     0x8,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4

           LDW     .D2T1   *+SP(40),A3       ; |68| 
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B4

           MV      .L1X    B11,A5            ; |68| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D1T1   *A5,A4            ; |69| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         STW     .D2T1   A3,*+SP(36)       ; |68| 
||         MVK     .L1     0x8,A6            ; |69| 
||         MVK     .S1     0x9,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(44),A3       ; |69| 
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           NOP             1
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A3,*+SP(52)       ; |69| 
           LDW     .D2T1   *+SP(48),A3
           NOP             2

   [!A0]   B       .S1     $C$L9             ; |72| 
|| [!A0]   MVKL    .S2     all_pass,B5
|| [!A0]   ZERO    .L2     B4                ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |183| 
|| [!A0]   MVKH    .S2     all_pass,B5

   [ A0]   MV      .L2X    A3,B4
   [ A0]   LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T1   A3,*+SP(56)       ; |72| 
   [ A0]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           NOP             3
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   ZERO    .L2     B4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |183| 
           MVKL    .S2     all_pass,B5
           MVKH    .S2     all_pass,B5
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x3,A4            ; |183| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |183| 

$C$RL18:   ; CALL OCCURS {print_test_results} {0}  ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           MVKL    .S1     a_ext,A3
           MVKH    .S1     a_ext,A3

           MVK     .S1     0xed,A31
||         ZERO    .L1     A4

           MV      .L2X    A3,B4             ; |186| 
||         STW     .D2T1   A31,*+SP(32)      ; |186| 
||         SET     .S1     A4,0x17,0x17,A4

           CALL    .S1     expf              ; |188| 
||         STW     .D2T1   A4,*B4            ; |186| 
||         MV      .L1     A3,A15            ; |186| 

           LDW     .D1T1   *A15,A4           ; |188| 
           ZERO    .L2     B11
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 3
           ADDKPC  .S2     $C$RL19,B3,2      ; |188| 
$C$RL19:   ; CALL OCCURS {expf} {0}          ; |188| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A3            ; |188| 
           ZERO    .L1     A31
           MVKH    .S1     0xc3800000,A31
           NOP             2
           ADD     .L2X    B11,A3,B4         ; |188| 
           STW     .D2T1   A4,*B4            ; |188| 
           LDW     .D1T1   *A15,A4           ; |189| 
           NOP             4
           CMPGTSP .S1     A4,A31,A0         ; |189| 
   [!A0]   B       .S1     $C$L11            ; |189| 
   [ A0]   CALL    .S1     expsp             ; |189| 
   [!A0]   CALL    .S1     expf              ; |189| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L11}        ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL20,B3,0      ; |189| 
$C$RL20:   ; CALL OCCURS {expsp} {0}         ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L12            ; |189| 
||         MVKL    .S2     output,B4

           MVKH    .S2     output,B4
           LDW     .D2T1   *+B4(4),A3        ; |189| 
           NOP             3
           ; BRANCH OCCURS {$C$L12}          ; |189| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 8
           ADDKPC  .S2     $C$RL21,B3,1      ; |189| 
$C$RL21:   ; CALL OCCURS {expf} {0}          ; |189| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T1   *+B4(4),A3        ; |189| 
           NOP             3
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             1
           ADD     .L1X    B11,A3,A3         ; |189| 

           STW     .D1T1   A4,*A3            ; |189| 
||         CALL    .S1     expsp_c           ; |190| 

           LDW     .D1T1   *A15,A4           ; |190| 
           ADDKPC  .S2     $C$RL22,B3,3      ; |190| 
$C$RL22:   ; CALL OCCURS {expsp_c} {0}       ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 90
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |190| 
           LDW     .D2T1   *+SP(16),A31
           MVKL    .S1     0x3fa62e42,A7
           MVKL    .S1     0xfef2e4e7,A6
           MVKH    .S1     0x3fa62e42,A7
           ADD     .L2     B11,B4,B4         ; |190| 
           STW     .D2T1   A4,*B4            ; |190| 
           LDW     .D1T1   *A15,A3           ; |191| 
           MVKH    .S1     0xfef2e4e7,A6
           LDW     .D2T2   *+SP(20),B31      ; |100| 
           MVKL    .S2     output+12,B30
           LDW     .D2T2   *+SP(12),B6       ; |100| 
           MPYSP   .M1     A13,A3,A5         ; |79| 
           MVKH    .S2     output+12,B30
           CMPLTSP .S1X    A3,B13,A1         ; |103| 
           CMPGTSP .S1X    A3,B12,A2         ; |108| 
           FADDSP  .L1     A12,A5,A4         ; |79| 
           CMPLTSP .S1     A5,A31,A0         ; |80| 
           LDW     .D2T1   *+SP(32),A28
           SPTRUNC .L1     A4,A8             ; |79| 
           NOP             3
   [ A0]   SUB     .L1     A8,1,A8           ; |81| 
           INTDP   .L1     A8,A5:A4          ; |100| 
           EXTU    .S1     A8,28,30,A30      ; |100| 
           AND     .L2X    3,A8,B5           ; |100| 
           LDDW    .D2T2   *+B31[B5],B5:B4   ; |100| 
           SHL     .S1     A8,16,A29         ; |100| 
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |100| 
           SPDP    .S1     A3,A5:A4          ; |100| 
           NOP             2
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |100| 
           NOP             2
           DPSP    .L1     A5:A4,A6          ; |100| 
           LDDW    .D1T1   *+A10[A30],A5:A4  ; |100| 
           NOP             2
           MPYSP   .M1     A6,A6,A7          ; |100| 
           NOP             3
           MPYSP   .M1     A7,A6,A9          ; |100| 
           MPYSP   .M2X    B6,A7,B6          ; |100| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |100| 
           AND     .L1     A14,A29,A4        ; |100| 
           MPYSP   .M1     A11,A9,A9         ; |100| 
           NOP             4
           FADDSP  .L2X    B6,A9,B6          ; |100| 
           ADD     .L2X    A4,B5,B5          ; |100| 
           DPSP    .L2     B5:B4,B4          ; |100| 
           FADDSP  .S2X    B6,A6,B6          ; |100| 
           LDW     .D2T2   *B30,B5           ; |191| 
           NOP             1
           FADDSP  .L2     B10,B6,B6         ; |100| 
           NOP             2

           MPYSP   .M2     B6,B4,B4          ; |100| 
|| [ A1]   LDW     .D2T2   *+SP(24),B4       ; |108| 

   [ A2]   LDW     .D2T2   *+SP(28),B4       ; |104| 
           ADD     .L2     B11,B5,B5         ; |191| 
           ADD     .L2     4,B11,B11         ; |187| 
           SUB     .L1     A28,1,A1          ; |187| 
   [!A1]   MVKL    .S2     output,B11
           STW     .D2T2   B4,*B5            ; |191| 
           LDW     .D1T2   *A15,B6           ; |192| 
           MVKL    .S2     0xcccccccd,B4
           MVKL    .S2     0xc000cccc,B5
           MVKH    .S2     0xcccccccd,B4
           MVKH    .S2     0xc000cccc,B5
           MPYSPDP .M2     B6,B5:B4,B5:B4    ; |192| 
   [!A1]   MVKH    .S2     output,B11
           NOP             5
           DPSP    .L2     B5:B4,B4          ; |192| 
   [ A1]   BNOP    .S1     $C$L10,2          ; |187| 

   [ A1]   CALL    .S1     expf              ; |188| 
||         STW     .D1T2   B4,*++A15         ; |192| 

   [ A1]   LDW     .D1T1   *A15,A4           ; |188| 

   [!A1]   CALL    .S1     expsp_v           ; |194| 
||         STW     .D2T1   A1,*+SP(32)       ; |192| 

           ; BRANCHCC OCCURS {$C$L10}        ; |187| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B11(16),B4      ; |194| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           MVK     .S1     0xed,A6           ; |194| 
           ADDKPC  .S2     $C$RL23,B3,0      ; |194| 
$C$RL23:   ; CALL OCCURS {expsp_v} {0}       ; |194| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T2   *B11,B5           ; |66| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7
           MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MV      .L1X    B5,A4             ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .D1     0x9,A8            ; |66| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6

           LDW     .D2T2   *B11,B5           ; |67| 
||         MVKL    .S2     0x3eb0c6f7,B7

           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MV      .L1X    B5,A4             ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .D1     0x9,A8            ; |67| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1X    B11,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4

           LDW     .D2T1   *+SP(36),A3       ; |68| 
||         MVKL    .S2     0x3eb0c6f7,B7

           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L2     B11,B5            ; |68| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(52),A3       ; |69| 
           LDW     .D2T2   *+SP(56),B5
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [ A0]   ADD     .L2     4,B5,B4
|| [!A0]   B       .S1     $C$L13            ; |72| 
|| [ A0]   LDW     .D2T2   *B5,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |198| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
   [!A0]   ZERO    .L2     B4                ; |72| 
   [!A0]   MV      .L2X    A3,B5
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
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   ZERO    .L2     B4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |198| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             1
           MV      .L2X    A3,B5
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x4,A4            ; |198| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL28,B3,0      ; |198| 

$C$RL28:   ; CALL OCCURS {print_test_results} {0}  ; |198| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           ZERO    .L1     A4                ; |114| 

           ZERO    .L1     A3                ; |114| 
||         STW     .D2T1   A4,*+SP(64)       ; |114| 

           STW     .D2T1   A3,*+SP(68)       ; |114| 
           LDDW    .D2T1   *+SP(64),A5:A4    ; |114| 
           MVKL    .S2     cycle_counts+24,B5
           MVKH    .S2     cycle_counts+24,B5
           ZERO    .L2     B4                ; |114| 
           NOP             1

           STDW    .D2T1   A5:A4,*B5         ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B5:B4,*A3         ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         CALL    .S2     gimme_random      ; |208| 
||         MVK     .S1     0x80,A3

           MVKL    .S1     t_offset,A5
||         SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKH    .S1     t_offset,A5
||         ZERO    .L1     A4

           STDW    .D1T2   B7:B6,*A5         ; |117| 
||         ZERO    .L2     B4
||         STW     .D2T1   A3,*+SP(32)       ; |117| 
||         MVKH    .S1     0x43480000,A4
||         ZERO    .S2     B11

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
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S2     0xc2c80000,B4
           ADDKPC  .S2     $C$RL29,B3,0      ; |208| 
$C$RL29:   ; CALL OCCURS {gimme_random} {0}  ; |208| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 82
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |208| 
           NOP             4
           ADD     .L1X    B11,A3,A3         ; |208| 

           STW     .D1T1   A4,*A3            ; |208| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B7           ; |122| 
           MPYSP   .M1     A13,A4,A5         ; |79| 
           LDW     .D2T2   *+SP(16),B4
           MVKL    .S1     0x3fa62e42,A9
           MVKL    .S1     0xfef2e4e7,A8
           FADDSP  .L1     A12,A5,A3         ; |79| 
           MVKH    .S1     0x3fa62e42,A9
           CMPLTSP .S2X    A5,B4,B0          ; |80| 
           SPTRUNC .L1     A3,A3             ; |79| 
           MVKH    .S1     0xfef2e4e7,A8
           MVKL    .S2     output+12,B31
           LDW     .D2T2   *+SP(20),B5       ; |100| 
   [ B0]   SUB     .L1     A3,1,A3           ; |81| 
           INTDP   .L1     A3,A7:A6          ; |100| 
           LDW     .D2T2   *+SP(12),B8       ; |100| 
           EXTU    .S1     A3,28,30,A31      ; |100| 
           AND     .L2X    3,A3,B4           ; |100| 
           LDDW    .D2T2   *+B5[B4],B5:B4    ; |100| 
           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |100| 
           SPDP    .S1     A4,A7:A6          ; |100| 
           MVKH    .S2     output+12,B31
           CMPLTSP .S2X    A4,B13,B1         ; |103| 
           FSUBDP  .L1     A7:A6,A9:A8,A7:A6 ; |100| 
           SHL     .S1     A3,16,A30         ; |100| 
           AND     .S1     A14,A30,A3        ; |100| 
           DPSP    .L1     A7:A6,A8          ; |100| 
           LDDW    .D1T1   *+A10[A31],A7:A6  ; |100| 
           CMPGTSP .S2X    A4,B12,B2         ; |108| 
           MVKL    .S1     t_start,A29
           MPYSP   .M1     A8,A8,A5          ; |100| 
           MVKH    .S1     t_start,A29
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |100| 
           STDW    .D1T2   B7:B6,*A29
           MPYSP   .M1     A5,A8,A9          ; |100| 
           MPYSP   .M2X    B8,A5,B8          ; |100| 
           ADD     .L2X    A3,B5,B5          ; |100| 
           DPSP    .L2     B5:B4,B4          ; |100| 
           MPYSP   .M1     A11,A9,A9         ; |100| 
           LDW     .D2T2   *B31,B5           ; |212| 
           NOP             3
           FADDSP  .L2X    B8,A9,B8          ; |100| 
           ADD     .L2     B11,B5,B5         ; |212| 
           NOP             1
           FADDSP  .L2X    B8,A8,B8          ; |100| 
           NOP             2
           FADDSP  .L2     B10,B8,B8         ; |100| 
           NOP             2

           MPYSP   .M2     B8,B4,B4          ; |100| 
|| [ B1]   LDW     .D2T2   *+SP(24),B4       ; |212| 

   [ B2]   LDW     .D2T2   *+SP(28),B4       ; |104| 
           NOP             4

           STW     .D2T2   B4,*B5            ; |212| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S1     t_offset,A15
||         LDW     .D2T1   *+SP(32),A28      ; |130| 
||         MVKL    .S2     t_stop,B16
||         ADD     .L2     4,B11,B11         ; |206| 

           MVKH    .S1     t_offset,A15
||         MVKH    .S2     t_stop,B16

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         MVKL    .S1     cycle_counts+24,A3
||         STDW    .D2T2   B9:B8,*B16        ; |128| 

           MVKH    .S1     cycle_counts+24,A3
           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           SUB     .L1     A28,1,A0          ; |206| 
           STW     .D2T1   A0,*+SP(32)       ; |130| 

           ADDU    .L2X    A4,B6,B5:B4       ; |130| 
|| [ A0]   ZERO    .L1     A4

           ADD     .D2X    B5,A5,B6          ; |130| 
|| [ A0]   B       .S2     $C$L14            ; |206| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 
|| [ A0]   MVKH    .S1     0x43480000,A4

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

   [ A0]   CALL    .S1     gimme_random      ; |208| 
||         SUB     .L2     B9,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         MV      .S2X    A3,B6             ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B6         ; |130| 
|| [!A0]   MV      .L2     B6,B4
|| [ A0]   ZERO    .S2     B4

           ; BRANCHCC OCCURS {$C$L14}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D2T1   *B4,A5:A4         ; |135| 
           ADDKPC  .S2     $C$RL30,B3,3      ; |135| 
$C$RL30:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A10
           SET     .S1     A10,0x1a,0x1d,A10
           MPYSP   .M1     A10,A4,A3         ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           ZERO    .L1     A12               ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         LDDW    .D2T1   *+SP(64),A7:A6

           MVK     .S1     24,A31
           MV      .L2X    A3,B4
           MV      .L2X    A12,B5            ; |114| 

           STDW    .D2T1   A5:A4,*B4         ; |135| 
||         SUB     .L1X    B4,A31,A3

           STDW    .D1T1   A7:A6,*A3         ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B6,B5,B9:B8       ; |117| 

           EXT     .S2     B9,24,24,B6       ; |117| 
||         SUB     .L2     B7,B4,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MV      .S2     B8,B4             ; |117| 

           STDW    .D1T2   B5:B4,*A15        ; |117| 
||         MVK     .S1     0x80,A14

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |221| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |221| 
||         CALL    .S1     expf              ; |221| 

           LDW     .D1T1   *A3,A4            ; |221| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |221| 
$C$RL32:   ; CALL OCCURS {expf} {0}          ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output,B13
           MVKH    .S2     output,B13
           LDW     .D2T2   *B13,B4           ; |221| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |221| 

           STW     .D1T1   A4,*A3            ; |221| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     t_start,B5
||         MV      .L1     A15,A11           ; |128| 
||         MVKL    .S1     cycle_counts,A3
||         SUB     .D1     A14,1,A0          ; |219| 
||         MV      .L2     B4,B17            ; |128| 

           MVKH    .S2     t_start,B5
||         LDDW    .D1T1   *A11,A5:A4        ; |130| 
||         MVKH    .S1     cycle_counts,A3
||         SUB     .L1     A14,1,A14         ; |219| 

           LDDW    .D2T2   *B5,B7:B6         ; |130| 
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S2     cycle_counts,B4
||         MVKL    .S1     t_stop,A31
||         ADD     .L1     4,A12,A12         ; |219| 

           MVKH    .S1     t_stop,A31
           MVKH    .S2     cycle_counts,B4
           STDW    .D1T2   B17:B16,*A31      ; |128| 
   [!A0]   MV      .L1X    B4,A15
           ADDU    .L2X    A4,B6,B9:B8       ; |130| 

           ADD     .S2X    B9,A5,B5          ; |130| 
|| [ A0]   B       .S1     $C$L15            ; |219| 
||         SUBU    .L2     B16,B8,B9:B8      ; |130| 

           ADD     .D2     B5,B7,B5          ; |130| 
||         ADDU    .L2X    A6,B8,B7:B6       ; |130| 
||         EXT     .S2     B9,24,24,B8       ; |130| 

           SUB     .L2     B17,B5,B5         ; |130| 

           ADD     .L2X    B7,A7,B5          ; |130| 
||         ADD     .S2     B5,B8,B7          ; |130| 

           ADD     .L2     B5,B7,B7          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B7:B6,*B4         ; |130| 

           ; BRANCHCC OCCURS {$C$L15}        ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A15,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |135| 
$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A10,A4,A3         ; |135| 
           ZERO    .L1     A12               ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           LDDW    .D2T1   *+SP(64),A7:A6    ; |135| 
           MV      .L2X    A12,B4            ; |114| 
           STDW    .D1T1   A5:A4,*A15        ; |135| 
           NOP             2

           STDW    .D1T1   A7:A6,*+A15(8)    ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B9           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B9,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MV      .S2X    A11,B8            ; |117| 

           STDW    .D2T2   B7:B6,*B8         ; |117| 
||         MV      .L1     A12,A11           ; |117| 
||         MVK     .S1     0x80,A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |230| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A11,A3,A3         ; |230| 
||         CALL    .S1     expsp             ; |230| 

           LDW     .D1T1   *A3,A4            ; |230| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |230| 
$C$RL35:   ; CALL OCCURS {expsp} {0}         ; |230| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ADD     .L2     4,B13,B4
           LDW     .D2T2   *B4,B4            ; |230| 
           NOP             4
           ADD     .L1X    A11,B4,A3         ; |230| 

           STW     .D1T1   A4,*A3            ; |230| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S1     t_offset,A10
||         MVKL    .S2     t_start,B4
||         ADDAD   .D1     A15,1,A3
||         SUB     .L1     A12,1,A0          ; |228| 
||         MV      .L2     B6,B9             ; |128| 

           MVKH    .S1     t_offset,A10
||         MVKH    .S2     t_start,B4
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         SUB     .L1     A12,1,A12         ; |228| 

           MVKL    .S1     t_stop,A31
||         ADD     .L1     4,A11,A11         ; |228| 
||         LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B4,B17:B16       ; |130| 

           MVK     .S2     8,B10
           MVKH    .S1     t_stop,A31
           ADD     .L2X    A15,B10,B10
           STDW    .D1T2   B9:B8,*A31        ; |128| 
           ADDU    .L2X    A4,B16,B5:B4      ; |130| 

   [ A0]   B       .S1     $C$L16            ; |228| 
||         ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2     B6,B17,B6         ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B10        ; |130| 

           ; BRANCHCC OCCURS {$C$L16}        ; |228| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A15(8),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |135| 
$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A12               ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           LDDW    .D2T1   *+SP(64),A7:A6    ; |135| 
           MV      .L2X    A12,B4            ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |135| 
           NOP             2

           STDW    .D1T1   A7:A6,*+A15(16)   ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         MVK     .S1     0x80,A3
||         SUB     .L2     B8,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 

           STDW    .D1T2   B7:B6,*A10        ; |117| 
||         MV      .L2X    A3,B11            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A14
           MVKH    .S1     input,A14
           LDW     .D1T1   *A14,A3           ; |239| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |239| 
||         CALL    .S1     expsp_c           ; |239| 

           LDW     .D1T1   *A3,A4            ; |239| 
           ADDKPC  .S2     $C$RL38,B3,3      ; |239| 
$C$RL38:   ; CALL OCCURS {expsp_c} {0}       ; |239| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ADDAD   .D2     B13,1,B4
           LDW     .D2T2   *B4,B4            ; |239| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |239| 

           STW     .D1T1   A4,*A3            ; |239| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S2     t_start,B10
||         LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         SUB     .L1X    B11,1,A0          ; |237| 
||         MV      .L2     B6,B17            ; |128| 
||         MVKL    .S1     t_stop,A11
||         SUB     .D2     B11,1,B11         ; |237| 

           MVKH    .S1     t_stop,A11
||         ADD     .L1     4,A12,A12         ; |237| 
||         MVKH    .S2     t_start,B10

           LDDW    .D2T2   *B10,B9:B8        ; |130| 
           ADDAD   .D1     A15,2,A3
           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           STDW    .D1T2   B17:B16,*A11      ; |128| 
           MV      .L2X    A3,B12            ; |128| 
           ADDU    .L2X    A4,B8,B5:B4       ; |130| 

   [ A0]   B       .S1     $C$L17            ; |237| 
||         ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B6,B9,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B6         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B12        ; |130| 

           ; BRANCHCC OCCURS {$C$L17}        ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A15(16),A5:A4   ; |135| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |135| 
$C$RL39:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 110
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A12               ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
           LDDW    .D2T1   *+SP(64),A7:A6    ; |135| 
           MV      .L1X    B12,A12           ; |135| 
           ZERO    .L2     B4                ; |115| 
           STDW    .D1T1   A5:A4,*A12        ; |135| 
           NOP             1

           STDW    .D1T1   A7:A6,*+A15(32)   ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D2T2   B5:B4,*B10        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 

           MV      .L2X    A14,B9            ; |246| 
||         MV      .L1X    B13,A15           ; |117| 
||         STDW    .D1T2   B7:B6,*A10        ; |117| 

           CALLP   .S2     expsp_v,B3
||         LDW     .D1T2   *+A15(16),B4      ; |246| 
||         LDW     .D2T1   *B9,A4            ; |246| 
||         MVK     .S1     0x80,A6           ; |246| 

$C$RL41:   ; CALL OCCURS {expsp_v} {0}       ; |246| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 
||         MVK     .S2     16,B10

           ADD     .L2X    A12,B10,B10

           MV      .L2     B4,B9             ; |128| 
||         LDDW    .D2T2   *B10,B5:B4        ; |130| 

           NOP             2
           ADDU    .L1X    A4,B6,A7:A6       ; |130| 

           ADD     .S1     A7,A5,A3          ; |130| 
||         SUBU    .L1X    B8,A6,A5:A4       ; |130| 

           ADDU    .L1X    B4,A4,A7:A6       ; |130| 

           ADD     .L2X    A3,B7,B4          ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           SUB     .L2     B9,B4,B7          ; |130| 
||         ADD     .S2X    A7,B5,B5          ; |130| 

           ADD     .L2X    B7,A3,B7          ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 
||         MV      .S2X    A6,B4             ; |130| 

           MV      .L2X    A11,B6            ; |128| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         STDW    .D2T2   B9:B8,*B6         ; |128| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STDW    .D2T1   A5:A4,*B10        ; |130| 
||         LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A15(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A10
||         MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A10
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6

           STW     .D1T1   A4,*+A10(8)       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T2   *+SP(40),B4       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STW     .D1T1   A4,*+A10(12)      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *B4,B4            ; |69| 
||         LDW     .D1T1   *A15,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL47:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(44),B4       ; |69| 
           STW     .D1T1   A4,*+A10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(48),B4
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
           MVK     .L1     0x1,A4            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L19            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |252| 
   [ A0]   MVKL    .S1     all_pass,A3
   [ A0]   MVKH    .S1     all_pass,A3
           NOP             2
           ; BRANCHCC OCCURS {$C$L19}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |252| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           MV      .L1     A12,A4
           NOP             1
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x2,A4            ; |252| 
||         ADDKPC  .S2     $C$RL48,B3,0      ; |252| 

$C$RL48:   ; CALL OCCURS {print_test_results} {0}  ; |252| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |253| 

$C$RL49:   ; CALL OCCURS {printf} {0}        ; |253| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |253| 

$C$RL50:   ; CALL OCCURS {printf} {0}        ; |253| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |260| 

$C$RL51:   ; CALL OCCURS {print_profile_results} {0}  ; |260| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |263| 

$C$RL52:   ; CALL OCCURS {print_memory_results} {0}  ; |263| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(80),B3      ; |264| 
           LDDW    .D2T1   *++SP,A13:A12     ; |264| 
           LDDW    .D2T1   *++SP,A15:A14     ; |264| 
           LDDW    .D2T2   *++SP,B11:B10     ; |264| 
           LDDW    .D2T2   *++SP,B13:B12     ; |264| 

           LDW     .D2T1   *++SP(8),A10      ; |264| 
||         RET     .S2     B3                ; |264| 

           LDW     .D2T1   *++SP(8),A11      ; |264| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |264| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"expSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	expf
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	expsp
	.global	expsp_c
	.global	expsp_v
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
