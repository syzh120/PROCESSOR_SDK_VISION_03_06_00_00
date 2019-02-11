;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:21:18 2013                                *
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
	.elfsym	a,SYM_SIZE(1608)
a:
	.word	04012be3bh,0d3eba4ffh		; a[0] @ 0
	.word	0c0118e22h,0e5de15cah		; a[1] @ 64
	.word	0c018e341h,0da95e32ch		; a[2] @ 128
	.word	04007c988h,0aa5e0cfch		; a[3] @ 192
	.word	0c00b2c74h,067b0e941h		; a[4] @ 256
	.word	0400d1c1eh,086d3c438h		; a[5] @ 320
	.word	0bffcc101h,0520f974dh		; a[6] @ 384
	.word	0c015dba4h,050acc0beh		; a[7] @ 448
	.word	0c00fe2b5h,0f295b432h		; a[8] @ 512
	.word	0bfe1dff2h,0437edad1h		; a[9] @ 576
	.word	0400f1eb3h,0c239cbd4h		; a[10] @ 640
	.word	0bff511feh,0b57d24efh		; a[11] @ 704
	.word	0c015c11eh,05db918bbh		; a[12] @ 768
	.word	0c00e1edch,0f7bd3b5fh		; a[13] @ 832
	.word	04012b693h,07669e9a9h		; a[14] @ 896
	.word	0bfddbe83h,0c94dbc4bh		; a[15] @ 960
	.word	03ff0abcch,036a4d7bbh		; a[16] @ 1024
	.word	0bff0953ah,074701465h		; a[17] @ 1088
	.word	0bff33957h,08a2a90cdh		; a[18] @ 1152
	.word	0c001654ah,07f8012e0h		; a[19] @ 1216
	.word	04008f424h,05f5ad96ah		; a[20] @ 1280
	.word	0401162eeh,02d6fa4d4h		; a[21] @ 1344
	.word	03ff4a838h,0e9559990h		; a[22] @ 1408
	.word	0bff459a8h,0628a38d4h		; a[23] @ 1472
	.word	04015a9a1h,0fd1569f5h		; a[24] @ 1536
	.word	03fea9c35h,08afc47e5h		; a[25] @ 1600
	.word	0c0183d45h,0ba1e745fh		; a[26] @ 1664
	.word	0bfe83bcah,01059ea57h		; a[27] @ 1728
	.word	04011e76ah,04a20b582h		; a[28] @ 1792
	.word	0c018b4e2h,08ed5f139h		; a[29] @ 1856
	.word	03fd7eac9h,0a275e12eh		; a[30] @ 1920
	.word	03fe07ff6h,0fb748005h		; a[31] @ 1984
	.word	03fefc3a7h,0bfcd0a09h		; a[32] @ 2048
	.word	04016595fh,02b08c246h		; a[33] @ 2112
	.word	0bff9aadfh,0dd4ac952h		; a[34] @ 2176
	.word	0c011ba7ch,0540e750eh		; a[35] @ 2240
	.word	03fa8d10fh,051ac9afeh		; a[36] @ 2304
	.word	0bfc9683fh,0847a4da4h		; a[37] @ 2368
	.word	0c012db94h,0aa469007h		; a[38] @ 2432
	.word	0c016e1bah,093e524b2h		; a[39] @ 2496
	.word	0bffa4da8h,0445747e5h		; a[40] @ 2560
	.word	0c014fe19h,0fc2a886ah		; a[41] @ 2624
	.word	04003c142h,07d5311f6h		; a[42] @ 2688
	.word	0bffbdcfch,0c5b8dc55h		; a[43] @ 2752
	.word	0c00644c0h,04bb50a38h		; a[44] @ 2816
	.word	03fe329bch,091ec262eh		; a[45] @ 2880
	.word	0bffbd0a7h,04ce08363h		; a[46] @ 2944
	.word	03fee0a37h,05bb6dffbh		; a[47] @ 3008
	.word	03fffa80eh,0a762aff9h		; a[48] @ 3072
	.word	0c0180018h,0032c046bh		; a[49] @ 3136
	.word	04005cb3ah,0fc555094h		; a[50] @ 3200
	.word	0bf64d28ah,07bef64a7h		; a[51] @ 3264
	.word	0c00536bdh,0032b2dabh		; a[52] @ 3328
	.word	040191314h,051c69c31h		; a[53] @ 3392
	.word	040054a9ch,0c16c467ah		; a[54] @ 3456
	.word	0c0052445h,04c3a6b36h		; a[55] @ 3520
	.word	0c0051ebeh,01650a45dh		; a[56] @ 3584
	.word	0c003dd43h,0c2cd6f8ah		; a[57] @ 3648
	.word	03ffe246ch,05b72ed5dh		; a[58] @ 3712
	.word	0bfde2b04h,0fbe8434bh		; a[59] @ 3776
	.word	0c01293b0h,0b6ec90b7h		; a[60] @ 3840
	.word	0c0134a00h,0127476cah		; a[61] @ 3904
	.word	0c0114303h,0b9c8e40ah		; a[62] @ 3968
	.word	040123604h,09ecb31c2h		; a[63] @ 4032
	.word	03ff7d55ch,0889712d7h		; a[64] @ 4096
	.word	04016ca59h,07693db14h		; a[65] @ 4160
	.word	0c00b845dh,0851654d6h		; a[66] @ 4224
	.word	040019657h,0173e0a27h		; a[67] @ 4288
	.word	040147f36h,0b9d070c6h		; a[68] @ 4352
	.word	04002e959h,0f3915cb4h		; a[69] @ 4416
	.word	0c010818fh,0605ab3abh		; a[70] @ 4480
	.word	0bfe6b2ach,090166319h		; a[71] @ 4544
	.word	0bfc0f889h,0e9f92d7eh		; a[72] @ 4608
	.word	03fd09c78h,0712ae587h		; a[73] @ 4672
	.word	04000bd4eh,0b7f3f7b4h		; a[74] @ 4736
	.word	0c0171014h,04383e34fh		; a[75] @ 4800
	.word	0c00cee02h,08ca23a52h		; a[76] @ 4864
	.word	0c018b38ah,005a7dfadh		; a[77] @ 4928
	.word	04006c536h,0501e2585h		; a[78] @ 4992
	.word	04003ec84h,0b5dcc63fh		; a[79] @ 5056
	.word	0c008aa52h,0ef911cf3h		; a[80] @ 5120
	.word	0c017260ah,07e08439bh		; a[81] @ 5184
	.word	04004351fh,01645bca3h		; a[82] @ 5248
	.word	0401811a4h,0667c35dch		; a[83] @ 5312
	.word	0c011a838h,026b7faaeh		; a[84] @ 5376
	.word	04012001bh,0ff3a0763h		; a[85] @ 5440
	.word	0c004d307h,06c050bd8h		; a[86] @ 5504
	.word	0400d71e9h,0bcc79c0bh		; a[87] @ 5568
	.word	0400af2a0h,0a958537eh		; a[88] @ 5632
	.word	0c017284ah,0d794a6ech		; a[89] @ 5696
	.word	03fe446eeh,0d1da52c7h		; a[90] @ 5760
	.word	0bff5bcfbh,01839b2a9h		; a[91] @ 5824
	.word	0c002134dh,06a161e4fh		; a[92] @ 5888
	.word	03fd27a8fh,07db6e504h		; a[93] @ 5952
	.word	040118011h,0e78910b5h		; a[94] @ 6016
	.word	0bff7fe18h,0d4e31bc4h		; a[95] @ 6080
	.word	0bffa255fh,0f1015f7ch		; a[96] @ 6144
	.word	03feb0917h,035a6aafah		; a[97] @ 6208
	.word	04015fb87h,030e1495ch		; a[98] @ 6272
	.word	040044bffh,0624b4eb3h		; a[99] @ 6336
	.word	040101417h,0d78d1a2fh		; a[100] @ 6400
	.word	0400db163h,0ad4e8244h		; a[101] @ 6464
	.word	04012b080h,03da8013bh		; a[102] @ 6528
	.word	03ffb582eh,07a66ce6bh		; a[103] @ 6592
	.word	04014d299h,0524bfd2fh		; a[104] @ 6656
	.word	0c01174ach,07a46edfbh		; a[105] @ 6720
	.word	0c014cbfdh,0dd1010efh		; a[106] @ 6784
	.word	0400f0fb7h,02d285737h		; a[107] @ 6848
	.word	0c009747dh,0ebbe299ch		; a[108] @ 6912
	.word	04016cedah,0dede4749h		; a[109] @ 6976
	.word	0c0005877h,0fbba2022h		; a[110] @ 7040
	.word	0c00d5ae7h,0ad22e35ah		; a[111] @ 7104
	.word	040096d79h,0222acd33h		; a[112] @ 7168
	.word	040113b89h,0cff7fa78h		; a[113] @ 7232
	.word	04006e2a2h,07f1b6912h		; a[114] @ 7296
	.word	0c0122b28h,09c007c27h		; a[115] @ 7360
	.word	0400516aah,015e89f91h		; a[116] @ 7424
	.word	0400df96ah,0e2cce952h		; a[117] @ 7488
	.word	040056102h,05113180bh		; a[118] @ 7552
	.word	0c007661ch,0871f4392h		; a[119] @ 7616
	.word	04007562eh,009fe8683h		; a[120] @ 7680
	.word	0c0112172h,0c010fca8h		; a[121] @ 7744
	.word	0c01501e6h,097792de9h		; a[122] @ 7808
	.word	03ff3066bh,089bbd605h		; a[123] @ 7872
	.word	0400dc4c2h,08cd7ea37h		; a[124] @ 7936
	.word	03ff4bd9dh,0d5687cc1h		; a[125] @ 8000
	.word	040181249h,064cddff2h		; a[126] @ 8064
	.word	0bfd47510h,04d551d69h		; a[127] @ 8128
	.word	0c00dc5f2h,0d8d0104eh		; a[128] @ 8192
	.word	0c011a5fbh,0069bfb74h		; a[129] @ 8256
	.word	04012e74bh,0762017cdh		; a[130] @ 8320
	.word	03ff31234h,0803a4d03h		; a[131] @ 8384
	.word	03ff70fc2h,0b5f295b4h		; a[132] @ 8448
	.word	0c010d957h,0eed45e92h		; a[133] @ 8512
	.word	03ff5aaafh,01b0b1e41h		; a[134] @ 8576
	.word	04018c46dh,04d0a74ceh		; a[135] @ 8640
	.word	0c018395dh,0ce11706bh		; a[136] @ 8704
	.word	0bffd89a3h,0edb07223h		; a[137] @ 8768
	.word	0c000ab34h,0033ccb62h		; a[138] @ 8832
	.word	0c016f5cbh,0d04d8acdh		; a[139] @ 8896
	.word	0400a33ach,0ad729472h		; a[140] @ 8960
	.word	0400b1588h,085751f67h		; a[141] @ 9024
	.word	03fed4830h,085d9c935h		; a[142] @ 9088
	.word	0bfd12cf0h,08e72f4eah		; a[143] @ 9152
	.word	03fd26973h,0cc8076b3h		; a[144] @ 9216
	.word	0400e17b3h,0cb740739h		; a[145] @ 9280
	.word	0c00fe130h,0c4c3e9cfh		; a[146] @ 9344
	.word	0bffbe376h,0922d948eh		; a[147] @ 9408
	.word	0c00098bah,0ef54b711h		; a[148] @ 9472
	.word	0c00eced5h,0786cf928h		; a[149] @ 9536
	.word	0bffd7566h,099920cddh		; a[150] @ 9600
	.word	0c0142820h,0df73987eh		; a[151] @ 9664
	.word	03fe9ec8ch,085b4e047h		; a[152] @ 9728
	.word	0c0177d0eh,02054335eh		; a[153] @ 9792
	.word	03ffbee4ch,043a5713eh		; a[154] @ 9856
	.word	0bfe151d5h,04a49d02eh		; a[155] @ 9920
	.word	04015f22ch,0c48428efh		; a[156] @ 9984
	.word	04007a58eh,0574637f3h		; a[157] @ 10048
	.word	04015156fh,083459a3eh		; a[158] @ 10112
	.word	03fcdc4ceh,0d189caefh		; a[159] @ 10176
	.word	03fa03a21h,063fdd65ah		; a[160] @ 10240
	.word	0c014e11fh,0ced2608bh		; a[161] @ 10304
	.word	0bfeb12c6h,040c1912fh		; a[162] @ 10368
	.word	04007bce1h,0edc64198h		; a[163] @ 10432
	.word	04000c348h,0a4b47fcfh		; a[164] @ 10496
	.word	0c00fe667h,057fdedd7h		; a[165] @ 10560
	.word	04008bf55h,02fdd3d5dh		; a[166] @ 10624
	.word	04013b5fdh,0c08a9f2bh		; a[167] @ 10688
	.word	0c0105072h,0a96ac7f5h		; a[168] @ 10752
	.word	0bfc2883eh,02782fbc8h		; a[169] @ 10816
	.word	0400d05a0h,0d928fba2h		; a[170] @ 10880
	.word	0c0132dd3h,0c86990bdh		; a[171] @ 10944
	.word	0c012e244h,07dde5230h		; a[172] @ 11008
	.word	0400f9c5eh,0e8c3a358h		; a[173] @ 11072
	.word	0400f47e9h,060814a17h		; a[174] @ 11136
	.word	0401387c4h,02055e0ddh		; a[175] @ 11200
	.word	0401611d7h,09f8ea621h		; a[176] @ 11264
	.word	0c0049673h,066ffe95ah		; a[177] @ 11328
	.word	0bfec52afh,064dcf96bh		; a[178] @ 11392
	.word	0c0183efdh,0d07ad737h		; a[179] @ 11456
	.word	0bff3966ah,055087011h		; a[180] @ 11520
	.word	0bfef17a1h,0dd34f9ddh		; a[181] @ 11584
	.word	03ff081adh,0ea897636h		; a[182] @ 11648
	.word	04000be2ch,005418861h		; a[183] @ 11712
	.word	03ffcd609h,0f7d08696h		; a[184] @ 11776
	.word	0c0179ab0h,01358a259h		; a[185] @ 11840
	.word	03ff00d80h,0bc530206h		; a[186] @ 11904
	.word	0c00050aah,0b54ad008h		; a[187] @ 11968
	.word	0c0134b26h,0da5f5c87h		; a[188] @ 12032
	.word	0c004be35h,0c5b4aa97h		; a[189] @ 12096
	.word	0c016e828h,00e3c02e6h		; a[190] @ 12160
	.word	0401341b0h,0ab2e1694h		; a[191] @ 12224
	.word	03ffaaee1h,094daedf8h		; a[192] @ 12288
	.word	04007d8c5h,01b27a3b3h		; a[193] @ 12352
	.word	040176c65h,0915450bah		; a[194] @ 12416
	.word	0bfa7bddch,06f013f9bh		; a[195] @ 12480
	.word	0bffe0ec0h,0f88333fdh		; a[196] @ 12544
	.word	0c00c9497h,081916518h		; a[197] @ 12608
	.word	04000a1bbh,05682c394h		; a[198] @ 12672
	.word	040056159h,066a3a308h		; a[199] @ 12736
	.word	0400a3953h,0a8f48070h		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\015162 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\015164 
;**	Parameter deleted: req_flags == 1;
	.sect	".text"
	.clink

;******************************************************************************
;* FUNCTION NAME: allequal                                                    *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B10,B11,B12,B13,SP,A16,A17,A18,   *
;*                           A19,A20,A21,A22,A23,A24,A25,A26,A27,A28,A29,A30, *
;*                           A31,B16,B17,B18,B19,B20,B21,B22,B23,B24,B25,B26, *
;*                           B27,B28,B29,B30,B31                              *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B10,B11,B12,B13,DP,SP,A16,A17,A18,*
;*                           A19,A20,A21,A22,A23,A24,A25,A26,A27,A28,A29,A30, *
;*                           A31,B16,B17,B18,B19,B20,B21,B22,B23,B24,B25,B26, *
;*                           B27,B28,B29,B30,B31                              *
;*   Local Frame Size  : 0 Args + 0 Auto + 32 Save = 32 byte                  *
;******************************************************************************
allequal:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           STW     .D2T1   A11,*SP--(8)      ; |63| 
           STDW    .D2T2   B13:B12,*SP--     ; |63| 

           STDW    .D2T2   B11:B10,*SP--     ; |63| 
||         MVKL    .S1     output,A11

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     output,A11

           DADD    .L2     0,B5:B4,B11:B10   ; |63| 
||         LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 

           MV      .D2     B3,B13            ; |63| 
||         CALLP   .S2     isequal,B3
||         MV      .L1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 
||         DADD    .L2     0,B11:B10,B7:B6   ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL0:    ; CALL OCCURS {isequal} {0}       ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           MVKL    .S2     fcn_pass,B12

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S2     fcn_pass,B12

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A11(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         DADD    .L2     0,B11:B10,B7:B6   ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {isequal} {0}       ; |67| 

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A11(12),B4      ; |68| 
||         STW     .D2T1   A3,*+B12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 
||         DADD    .L2     0,B11:B10,B7:B6   ; |68| 

$C$RL2:    ; CALL OCCURS {isequal} {0}       ; |68| 

           MV      .L1     A11,A3            ; |66| 
||         STW     .D2T1   A4,*+B12(12)      ; |68| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MV      .L1     A10,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 
||         DADD    .L2     0,B11:B10,B7:B6   ; |69| 

$C$RL3:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2     4,B12,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T1   A4,*+B12(16)      ; |69| 
           ADD     .L2     8,B12,B4
           NOP             2

   [!B0]   BNOP    .S1     $C$L1,4           ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L1}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .S1     0x1,A3            ; |72| 

   [ A0]   STW     .D1T1   A3,*A4            ; |72| 
|| [ A0]   B       .S1     $C$L2             ; |72| 
|| [ A0]   MV      .L2     B13,B3            ; |74| 

   [ A0]   LDW     .D2T1   *++SP(8),A10      ; |74| 
   [ A0]   LDDW    .D2T2   *++SP,B11:B10     ; |74| 

   [ A0]   RET     .S2     B3                ; |74| 
|| [ A0]   LDDW    .D2T2   *++SP,B13:B12     ; |74| 

   [ A0]   LDW     .D2T1   *++SP(8),A11      ; |74| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L2}         ; |72| 
;** --------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S1     all_pass,A4

           MVKH    .S1     all_pass,A4
||         ZERO    .L1     A3                ; |72| 

           STW     .D1T1   A3,*A4            ; |72| 
           LDW     .D2T1   *++SP(8),A10      ; |74| 

           LDDW    .D2T2   *++SP,B11:B10     ; |74| 
||         MV      .L2     B13,B3            ; |74| 

           LDDW    .D2T2   *++SP,B13:B12     ; |74| 
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
;*   Local Frame Size  : 8 Args + 20 Auto + 56 Save = 84 byte                 *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |110| 
           STW     .D2T1   A10,*SP--(8)      ; |110| 
           STDW    .D2T2   B13:B12,*SP--     ; |110| 
           STDW    .D2T2   B11:B10,*SP--     ; |110| 
           STDW    .D2T1   A15:A14,*SP--     ; |110| 

           STDW    .D2T1   A13:A12,*SP--     ; |110| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(40)      ; |110| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     a,A10
||         MVKL    .S2     output,B10

           MVKH    .S1     a,A10
||         MVKH    .S2     output,B10

           MV      .L1     A10,A13
||         CALL    .S1     atan              ; |127| 
||         LDW     .D2T1   *B10,A12

           LDDW    .D1T1   *A13++,A5:A4      ; |127| 
           MVK     .S2     0xc9,B4
           NOP             1
           MV      .L1X    B4,A11
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL5,B3,0       ; |127| 
$C$RL5:    ; CALL OCCURS {atan} {0}          ; |127| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A11,1,A0          ; |126| 
||         STDW    .D1T1   A5:A4,*A12++      ; |127| 
||         SUB     .S1     A11,1,A11         ; |126| 

   [ A0]   B       .S1     $C$L3             ; |126| 
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |127| 
|| [!A0]   ADD     .L2     4,B10,B11

   [ A0]   CALL    .S1     atan              ; |127| 
   [!A0]   MV      .L1     A10,A11
   [!A0]   ZERO    .L2     B10
   [!A0]   MVK     .S1     0xc9,A3
   [!A0]   MV      .L1     A3,A12
           ; BRANCHCC OCCURS {$C$L3}         ; |126| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     atandp            ; |130| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |130| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |130| 
$C$RL6:    ; CALL OCCURS {atandp} {0}        ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |130| 
||         SUB     .L1     A12,1,A0          ; |129| 
||         SUB     .S1     A12,1,A12         ; |129| 

   [ A0]   BNOP    .S2     $C$L4,2           ; |129| 
|| [!A0]   MVK     .S1     0xc9,A3
|| [!A0]   ZERO    .L2     B12
|| [!A0]   MV      .L1     A10,A11

   [!A0]   MV      .L1     A3,A12

           ADD     .L2     B10,B4,B4         ; |130| 
||         ADD     .S2     8,B10,B10         ; |129| 

   [ A0]   CALL    .S1     atandp            ; |130| 
|| [!A0]   ADD     .L2     4,B11,B10
||         STDW    .D2T1   A5:A4,*B4         ; |130| 

           ; BRANCHCC OCCURS {$C$L4}         ; |129| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     atandp_c          ; |133| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |133| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |133| 
$C$RL7:    ; CALL OCCURS {atandp_c} {0}      ; |133| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B10,B4           ; |133| 
||         SUB     .L1     A12,1,A0          ; |132| 
||         SUB     .S1     A12,1,A12         ; |132| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |132| 

           ADD     .L2     B12,B4,B4         ; |133| 
||         ADD     .S2     8,B12,B12         ; |132| 

   [ A0]   CALL    .S1     atandp_c          ; |133| 
||         STDW    .D2T1   A5:A4,*B4         ; |133| 

           ; BRANCHCC OCCURS {$C$L5}         ; |132| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           ZERO    .L2     B13
||         ZERO    .L1     A8                ; |171| 
||         MVKL    .S1     V,A11
||         ADD     .D1X    4,B10,A6
||         MVK     .S2     0xc9,B0
||         ZERO    .D2     B31

           SET     .S2     B13,0x14,0x1d,B13
||         SET     .S1     A8,31,31,A31      ; |171| 
||         LDW     .D1T1   *A6,A3
||         ZERO    .L1     A5:A4             ; |170| 
||         ZERO    .L2     B12               ; |171| 
||         MV      .D2X    A10,B18

           MVKH    .S1     V,A11
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 18
           LDDW    .D2T2   *B18++,B7:B6      ; |167| 
           NOP             4
           DADD    .L2     0,B7:B6,B5:B4     ; |170| 
           NOP             1
           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |170| 
           NOP             1

   [ A0]   XOR     .L2X    B5,A31,B7         ; |171| 
|| [ A0]   MV      .S2     B4,B6             ; |171| 

           CMPGTDP .S2     B7:B6,B13:B12,B1  ; |175| 

   [ A0]   ZERO    .L1     A0                ; |172| 
|| [!A0]   MVK     .S1     0xffffffff,A0     ; |166| 

   [!B1]   B       .S1     $C$L7
||         RCPDP   .S2     B7:B6,B5:B4       ; |55| 
|| [ B1]   ZERO    .L1     A5
|| [ B1]   MV      .D1     A8,A4             ; |55| 

   [ B1]   SET     .S1     A5,0x1e,0x1e,A5
|| [!B1]   MV      .L1     A8,A7             ; |175| 

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
|| [!B1]   MVKL    .S2     0x5e9ecd56,B4

   [!B1]   MVKL    .S2     0x3fd12614,B5
   [!B1]   MVKH    .S2     0x5e9ecd56,B4
   [!B1]   MVKH    .S2     0x3fd12614,B5
           ; BRANCHCC OCCURS {$C$L7}  
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 32
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |55| 
           MV      .L2     B12,B16           ; |55| 
           ZERO    .L2     B17
           SET     .S2     B17,0x1e,0x1e,B17
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |55| 
           MV      .L1     A8,A4             ; |55| 
           MV      .L1X    B17,A5            ; |55| 
           MVK     .L1     0x2,A7            ; |177| 
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |55| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |55| 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |55| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B7:B6,A5:A4 ; |55| 
           NOP             3

           FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |55| 
||         MVKL    .S2     0x5e9ecd56,B4

           MVKL    .S2     0x3fd12614,B5
           MVKH    .S2     0x5e9ecd56,B4
           MVKH    .S2     0x3fd12614,B5
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 8
           CMPGTDP .S2     B7:B6,B5:B4,B1    ; |180| 
           NOP             1

   [!B1]   B       .S1     $C$L8             ; |180| 
||         MVKL    .S2     0x3ffbb67a,B5

           MVKL    .S2     0xe8584caa,B4
           MVKH    .S2     0x3ffbb67a,B5
           MVKH    .S2     0xe8584caa,B4
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |55| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L8}         ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 39
           MV      .L1     A8,A4             ; |55| 
           RCPDP   .S2     B5:B4,B9:B8       ; |55| 
           ZERO    .L1     A5
           FMPYDP  .M2     B9:B8,B5:B4,B17:B16 ; |55| 
           SET     .S1     A5,0x1e,0x1e,A5
           ZERO    .L1     A17
           MV      .L1X    B12,A16           ; |55| 
           SET     .S1     A17,0x1e,0x1e,A17
           FSUBDP  .L1X    A5:A4,B17:B16,A5:A4 ; |55| 
           ADD     .L1     1,A7,A7           ; |181| 
           NOP             1
           FMPYDP  .M1X    B9:B8,A5:A4,A5:A4 ; |55| 
           MV      .L2     B12,B8            ; |55| 
           MV      .L2X    A17,B9            ; |55| 
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A9:A8 ; |55| 
           NOP             3
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |55| 
           NOP             2
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |55| 
           MVKL    .S1     0xe8584caa,A8
           MVKL    .S1     0x3ffbb67a,A9
           MVKH    .S1     0xe8584caa,A8
           MVKH    .S1     0x3ffbb67a,A9
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |55| 
           NOP             3

           FSUBDP  .L2     B9:B8,B5:B4,B7:B6 ; |55| 
||         FMPYDP  .M2X    A9:A8,B7:B6,B5:B4 ; |55| 

           MV      .L1X    B13,A9            ; |55| 
           MV      .L1     A16,A8            ; |55| 
           FMPYDP  .M2X    A5:A4,B7:B6,B7:B6 ; |55| 
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |55| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |55| 
;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 13
           MVKL    .S2     0x3e4fffff,B9
           MVKH    .S2     0x3e4fffff,B9
           MVK     .S2     0xffffedec,B8     ; |191| 
           ABSDP   .S2     B7:B6,B5:B4       ; |191| 
           NOP             1
           CMPGTDP .S2     B5:B4,B9:B8,B1    ; |191| 
           FMPYDP  .M2     B5:B4,B5:B4,B5:B4 ; |55| 

   [!B1]   B       .S1     $C$L9             ; |191| 
|| [ B1]   MVKL    .S2     0x402e0c49,B9
|| [!B1]   LDDW    .D1T1   *+A11[A7],A5:A4   ; |206| 
|| [!B1]   CMPLT   .L1     A7,2,A1           ; |206| 

   [ B1]   MVKL    .S2     0xe14ac710,B8
   [ B1]   MVKH    .S2     0x402e0c49,B9
   [ B1]   MVKH    .S2     0xe14ac710,B8

           FADDDP  .L2     B9:B8,B5:B4,B9:B8 ; |55| 
|| [!B1]   MV      .S2     B12,B4            ; |206| 

   [!B1]   SET     .S2     B4,31,31,B5       ; |206| 
           ; BRANCHCC OCCURS {$C$L9}         ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 72

           MV      .L1X    B12,A18           ; |55| 
||         MVKL    .S1     0x320da3d7,A4

           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
||         MVKL    .S1     0x404dca0a,A5

           MVKH    .S1     0x320da3d7,A4
           MVKH    .S1     0x404dca0a,A5
           ZERO    .L1     A19
           FADDDP  .L2X    A5:A4,B9:B8,B9:B8 ; |55| 
           MVKL    .S2     0x40b6da5,B16
           ZERO    .L1     A31
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
           MVKL    .S2     0x40558a12,B17
           MVKH    .S2     0x40b6da5,B16
           MVKH    .S2     0x40558a12,B17
           FADDDP  .L2     B17:B16,B9:B8,B9:B8 ; |55| 
           MVKL    .S2     0xc034817f,B21
           SET     .S1     A19,0x1e,0x1e,A19
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
           MVKL    .S1     0xbcc495a9,A4
           MVKL    .S1     0x4044887c,A5
           MVKH    .S1     0xbcc495a9,A4
           MVKH    .S1     0x4044887c,A5
           FADDDP  .L1X    A5:A4,B9:B8,A5:A4 ; |55| 
           MVKL    .S2     0xb9e2bccb,B20
           MVKH    .S2     0xc034817f,B21
           RCPDP   .S1     A5:A4,A9:A8       ; |55| 
           MVKH    .S2     0xb9e2bccb,B20
           FMPYDP  .M1     A9:A8,A5:A4,A17:A16 ; |55| 
           MV      .L2     B12,B16           ; |55| 
           MVKL    .S2     0xd9b187bd,B8
           MVKL    .S2     0xbfeacd7a,B9
           FSUBDP  .L1     A19:A18,A17:A16,A17:A16 ; |55| 
           MVKH    .S2     0xd9b187bd,B8
           MVKH    .S2     0xbfeacd7a,B9
           FMPYDP  .M1     A9:A8,A17:A16,A9:A8 ; |55| 
           FMPYDP  .M2     B9:B8,B5:B4,B9:B8 ; |55| 
           MVKL    .S1     0xc020fd3f,A17
           MVKL    .S1     0x5c8d6a63,A16
           FMPYDP  .M1     A9:A8,A5:A4,A19:A18 ; |55| 
           MVKH    .S1     0xc020fd3f,A17
           MVKH    .S1     0x5c8d6a63,A16
           SET     .S2     B31,0x1e,0x1e,B17
           FADDDP  .L2X    A17:A16,B9:B8,B9:B8 ; |55| 
           FSUBDP  .L2X    B17:B16,A19:A18,B17:B16 ; |55| 
           SET     .S1     A31,0x1e,0x1e,A17
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
           MV      .L1X    B12,A16           ; |55| 
           FMPYDP  .M1X    A9:A8,B17:B16,A9:A8 ; |55| 
           MVKL    .S1     0x51061ce2,A18
           FADDDP  .L2     B21:B20,B9:B8,B9:B8 ; |55| 
           MVKL    .S1     0xc02b60a6,A19
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |55| 
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
           MVKH    .S1     0x51061ce2,A18
           MVKH    .S1     0xc02b60a6,A19
           FSUBDP  .S1     A17:A16,A5:A4,A5:A4 ; |55| 
           FADDDP  .L2X    A19:A18,B9:B8,B9:B8 ; |55| 
           CMPLT   .L1     A7,2,A1           ; |206| 
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |55| 
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |55| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |55| 
           LDDW    .D1T1   *+A11[A7],A5:A4   ; |206| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |55| 
           NOP             3
           FADDDP  .L2     B5:B4,B7:B6,B7:B6 ; |55| 
           MV      .L2     B12,B4            ; |206| 
           SET     .S2     B4,31,31,B5       ; |206| 
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 8

           SUB     .S2     B0,1,B0           ; |135| 
|| [!A1]   XOR     .D2     B7,B5,B5          ; |206| 
|| [!A0]   MV      .L1X    B12,A8            ; |206| 

   [ B0]   ZERO    .L2     B13
|| [!B0]   ADD     .L1     4,A6,A12
|| [!A1]   MV      .D2     B6,B4             ; |206| 
|| [ A1]   DADD    .S2     0,B7:B6,B5:B4     ; |206| 

   [ B0]   B       .S1     $C$L6             ; |135| 
           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |206| 
   [!A0]   SET     .S1     A8,31,31,A8       ; |206| 
   [ B0]   SET     .S2     B13,0x14,0x1d,B13

   [!A0]   XOR     .L1     A5,A8,A5          ; |206| 
|| [ B0]   ZERO    .S1     A8                ; |171| 

   [!B0]   CALL    .S2     atandp_v          ; |138| 
|| [ B0]   SET     .S1     A8,31,31,A31      ; |171| 
||         STDW    .D1T1   A5:A4,*A3++       ; |206| 
|| [ B0]   ZERO    .L1     A5:A4             ; |170| 

           ; BRANCHCC OCCURS {$C$L6}         ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A12,B4           ; |138| 
           MV      .L1     A10,A4            ; |138| 
           MVK     .S1     0xc9,A6           ; |138| 
           ADDKPC  .S2     $C$RL8,B3,1       ; |138| 
$C$RL8:    ; CALL OCCURS {atandp_v} {0}      ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S2     0x3e112e0b,B5
           MVKL    .S2     0xe826d695,B4
           MVKH    .S2     0x3e112e0b,B5
           MVKH    .S2     0xe826d695,B4

           CALLP   .S2     allequal,B3
||         MVK     .S1     0xc9,A4           ; |141| 

$C$RL9:    ; CALL OCCURS {allequal} {0}      ; |141| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |142| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     a_sc,A10

           MVKH    .S1     a_sc,A10
||         MVK     .L2     0xffffffff,B5     ; |155| 

           STDW    .D1T2   B13:B12,*+A10(32) ; |153| 
||         MV      .L2     B5,B4             ; |155| 
||         ZERO    .S2     B9

           STDW    .D1T2   B5:B4,*+A10(48)   ; |155| 
||         MVKH    .S2     0xfff00000,B9
||         ZERO    .L1     A5
||         ZERO    .L2     B8                ; |152| 

           STDW    .D1T2   B9:B8,*+A10(24)   ; |152| 
||         SET     .S1     A5,0x14,0x1e,A5
||         ZERO    .L2     B7
||         ZERO    .L1     A4                ; |151| 

           STDW    .D1T1   A5:A4,*+A10(16)   ; |151| 
||         MVKH    .S2     0xbff00000,B7
||         ZERO    .L2     B17
||         ZERO    .D2     B6                ; |154| 

           MVK     .L2     0x7,B4
||         STDW    .D1T2   B7:B6,*+A10(40)   ; |154| 
||         MVKH    .S2     0x80000000,B17
||         ZERO    .D2     B16               ; |150| 

           STDW    .D1T2   B17:B16,*+A10(8)  ; |150| 
||         ZERO    .L1     A7:A6             ; |149| 

           MV      .L1X    B4,A13            ; |150| 
||         STDW    .D1T1   A7:A6,*A10        ; |149| 
||         SUB     .L2X    A10,8,B13
||         ZERO    .S2     B12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     atan              ; |157| 
||         LDDW    .D2T2   *++B13,B5:B4      ; |157| 

           ADDKPC  .S2     $C$RL11,B3,3      ; |157| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |157| 
$C$RL11:   ; CALL OCCURS {atan} {0}          ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 33
           MVKL    .S1     output,A15
           MVKH    .S1     output,A15
           LDW     .D1T1   *A15,A3           ; |157| 
           NOP             4
           ADD     .L1X    B12,A3,A3         ; |157| 
           STDW    .D1T1   A5:A4,*A3         ; |157| 

           CALLP   .S2     atandp,B3
||         LDDW    .D2T1   *B13,A5:A4        ; |158| 

$C$RL12:   ; CALL OCCURS {atandp} {0}        ; |158| 
           LDW     .D1T1   *+A15(4),A3       ; |158| 
           NOP             4
           ADD     .L1X    B12,A3,A3         ; |158| 
           STDW    .D1T1   A5:A4,*A3         ; |158| 
           LDDW    .D2T2   *B13,B5:B4        ; |159| 
           NOP             4

           CALLP   .S2     atandp_c,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |159| 

$C$RL13:   ; CALL OCCURS {atandp_c} {0}      ; |159| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 25
           LDW     .D1T1   *+A15(8),A3       ; |159| 
           ZERO    .L2     B9
           ZERO    .L2     B8                ; |171| 
           SET     .S2     B8,31,31,B8       ; |171| 
           SET     .S2     B9,0x14,0x1d,B9
           ADD     .L2X    B12,A3,B4         ; |159| 
           STDW    .D2T1   A5:A4,*B4         ; |159| 
           LDDW    .D2T2   *B13,B7:B6        ; |167| 
           ZERO    .L1     A5:A4             ; |170| 
           NOP             3
           DADD    .L2     0,B7:B6,B5:B4     ; |170| 
           NOP             1
           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |170| 
           NOP             1

   [ A0]   XOR     .L2     B5,B8,B7          ; |171| 
|| [ A0]   MV      .S2     B4,B6             ; |171| 
||         ZERO    .D2     B8                ; |175| 

   [!A0]   MVK     .L2     0xffffffff,B0     ; |166| 
||         CMPGTDP .S2     B7:B6,B9:B8,B1    ; |175| 

   [ A0]   ZERO    .L2     B0                ; |175| 

   [!B1]   B       .S1     $C$L11
||         RCPDP   .S2     B7:B6,B5:B4       ; |55| 
|| [!B1]   MV      .L1X    B8,A14            ; |175| 
|| [ B1]   ZERO    .D1     A5

   [ B1]   SET     .S1     A5,0x1e,0x1e,A5
|| [ B1]   ZERO    .L1     A4                ; |55| 

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
|| [!B1]   MVKL    .S2     0x3fd12614,B5

   [!B1]   MVKL    .S2     0x5e9ecd56,B4
   [!B1]   MVKH    .S2     0x3fd12614,B5
   [!B1]   MVKH    .S2     0x5e9ecd56,B4
           ; BRANCHCC OCCURS {$C$L11}  
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 32
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |55| 
           ZERO    .L2     B16               ; |55| 
           ZERO    .L2     B17
           SET     .S2     B17,0x1e,0x1e,B17
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |55| 
           ZERO    .L1     A4                ; |55| 
           MV      .L1X    B17,A5            ; |55| 
           MVK     .L1     0x2,A14           ; |177| 
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |55| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |55| 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |55| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B7:B6,A5:A4 ; |55| 
           NOP             3

           FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |55| 
||         MVKL    .S2     0x5e9ecd56,B4

           MVKL    .S2     0x3fd12614,B5
           MVKH    .S2     0x5e9ecd56,B4
           MVKH    .S2     0x3fd12614,B5
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 8
           CMPGTDP .S2     B7:B6,B5:B4,B1    ; |180| 
           NOP             1

   [!B1]   B       .S1     $C$L12            ; |180| 
||         MVKL    .S2     0x3ffbb67a,B5

           MVKL    .S2     0xe8584caa,B4
           MVKH    .S2     0x3ffbb67a,B5
           MVKH    .S2     0xe8584caa,B4
           FADDDP  .L2     B5:B4,B7:B6,B9:B8 ; |55| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L12}        ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 39
           ZERO    .L1     A4                ; |55| 
           RCPDP   .S2     B9:B8,B5:B4       ; |55| 
           ZERO    .L1     A5
           FMPYDP  .M2     B5:B4,B9:B8,B17:B16 ; |55| 
           SET     .S1     A5,0x1e,0x1e,A5
           ZERO    .L1     A9
           ZERO    .L1     A8                ; |55| 
           SET     .S1     A9,0x1e,0x1e,A9
           FSUBDP  .L1X    A5:A4,B17:B16,A5:A4 ; |55| 
           ZERO    .L1     A31
           ADD     .S1     1,A14,A14         ; |181| 
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |55| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B9:B8,A7:A6 ; |55| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |55| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |55| 
           MVKL    .S1     0x3ffbb67a,A7
           MVKL    .S1     0xe8584caa,A6
           MVKH    .S1     0x3ffbb67a,A7
           MVKH    .S1     0xe8584caa,A6
           FMPYDP  .M2X    A5:A4,B9:B8,B5:B4 ; |55| 
           MV      .L2X    A9,B9             ; |55| 
           MV      .L2X    A8,B8             ; |55| 
           FMPYDP  .M2X    A7:A6,B7:B6,B7:B6 ; |55| 
           FSUBDP  .L2     B9:B8,B5:B4,B5:B4 ; |55| 
           SET     .S1     A31,0x14,0x1d,A7
           MV      .L1     A8,A6             ; |55| 
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |55| 
           FSUBDP  .L2X    B7:B6,A7:A6,B7:B6 ; |55| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |55| 
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 16

           ZERO    .L1     A5:A4             ; |187| 
||         ZERO    .S1     A3                ; |188| 

           MVKL    .S2     0x3e4fffff,B9
           SET     .S1     A3,31,31,A3       ; |188| 
           DADD    .L2     0,B7:B6,B5:B4     ; |185| 
           MVKH    .S2     0x3e4fffff,B9
           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |187| 
           MVK     .S2     0xffffedec,B8     ; |191| 
   [ A0]   XOR     .L2X    B5,A3,B5          ; |188| 
           CMPGTDP .S2     B5:B4,B9:B8,B1    ; |191| 
           FMPYDP  .M2     B5:B4,B5:B4,B9:B8 ; |55| 

   [!B1]   B       .S1     $C$L13            ; |191| 
|| [ B1]   MVKL    .S2     0x402e0c49,B5

   [ B1]   MVKL    .S2     0xe14ac710,B4
   [ B1]   MVKH    .S2     0x402e0c49,B5
   [ B1]   MVKH    .S2     0xe14ac710,B4
           FADDDP  .L2     B5:B4,B9:B8,B5:B4 ; |55| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L13}        ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 70

           ZERO    .D2     B31
||         MVKL    .S2     0xc034817f,B19
||         MVKL    .S1     0x404dca0a,A5

           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |55| 
||         MVKL    .S1     0x320da3d7,A4

           MVKH    .S1     0x404dca0a,A5
           MVKH    .S1     0x320da3d7,A4
           ZERO    .L1     A16               ; |55| 
           FADDDP  .L2X    A5:A4,B5:B4,B17:B16 ; |55| 
           ZERO    .L1     A17
           MVKL    .S2     0x40558a12,B5
           FMPYDP  .M2     B9:B8,B17:B16,B17:B16 ; |55| 
           MVKL    .S2     0x40b6da5,B4
           MVKH    .S2     0x40558a12,B5
           MVKH    .S2     0x40b6da5,B4
           FADDDP  .L2     B5:B4,B17:B16,B5:B4 ; |55| 
           ZERO    .L1     A31
           MVKL    .S2     0xb9e2bccb,B18
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |55| 
           MVKL    .S1     0x4044887c,A5
           MVKL    .S1     0xbcc495a9,A4
           MVKH    .S1     0x4044887c,A5
           MVKH    .S1     0xbcc495a9,A4
           FADDDP  .L1X    A5:A4,B5:B4,A9:A8 ; |55| 
           MVKH    .S2     0xc034817f,B19
           SET     .S1     A17,0x1e,0x1e,A17
           RCPDP   .S1     A9:A8,A5:A4       ; |55| 
           MVKH    .S2     0xb9e2bccb,B18
           FMPYDP  .M1     A5:A4,A9:A8,A7:A6 ; |55| 
           ZERO    .L2     B16               ; |55| 
           MVKL    .S2     0xbfeacd7a,B5
           MVKL    .S2     0xd9b187bd,B4
           FSUBDP  .L1     A17:A16,A7:A6,A7:A6 ; |55| 
           MVKH    .S2     0xbfeacd7a,B5
           MVKH    .S2     0xd9b187bd,B4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |55| 
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |55| 
           MVKL    .S1     0x5c8d6a63,A6
           MVKL    .S1     0xc020fd3f,A7
           FMPYDP  .M1     A5:A4,A9:A8,A17:A16 ; |55| 
           MVKH    .S1     0x5c8d6a63,A6
           MVKH    .S1     0xc020fd3f,A7
           SET     .S2     B31,0x1e,0x1e,B17
           FADDDP  .L2X    A7:A6,B5:B4,B5:B4 ; |55| 
           FSUBDP  .L2X    B17:B16,A17:A16,B17:B16 ; |55| 
           MVKL    .S1     0x51061ce2,A18
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |55| 
           MVKL    .S1     0xc02b60a6,A19
           FMPYDP  .M1X    B17:B16,A5:A4,A17:A16 ; |55| 
           MVKH    .S1     0x51061ce2,A18
           FADDDP  .L2     B19:B18,B5:B4,B5:B4 ; |55| 
           MVKH    .S1     0xc02b60a6,A19
           FMPYDP  .M1     A17:A16,A9:A8,A5:A4 ; |55| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |55| 
           ZERO    .L1     A6                ; |55| 
           SET     .S1     A31,0x1e,0x1e,A7
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |55| 
           FADDDP  .L2X    A19:A18,B5:B4,B5:B4 ; |55| 
           NOP             1
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |55| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |55| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |55| 
           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |196| 
           NOP             3
           FADDDP  .L2     B5:B4,B7:B6,B7:B6 ; |196| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 10

           LDDW    .D1T1   *+A11[A14],A5:A4  ; |203| 
||         CMPLT   .L1     A14,2,A0          ; |199| 
||         SUB     .S1     A13,1,A2          ; |156| 

           SUB     .L1     A13,1,A13         ; |156| 
||         ZERO    .D2     B4                ; |200| 
||         MVK     .S2     12,B5

           SET     .S2     B4,31,31,B4       ; |200| 
||         ADD     .L2X    A15,B5,B5

   [!A0]   XOR     .L2     B7,B4,B7          ; |200| 
||         LDW     .D2T2   *B5,B4            ; |160| 

   [ A2]   B       .S1     $C$L10            ; |156| 
           FADDDP  .L1X    A5:A4,B7:B6,A5:A4 ; |203| 
   [!B0]   ZERO    .L1     A3                ; |206| 
   [!B0]   SET     .S1     A3,31,31,A3       ; |206| 

           ADD     .L2     B12,B4,B5         ; |160| 
|| [!B0]   XOR     .L1     A5,A3,A5          ; |206| 
|| [!A2]   MV      .S1     A12,A3            ; |162| 
||         ADD     .S2     8,B12,B12         ; |156| 

   [!A2]   CALL    .S1     atandp_v          ; |162| 
||         STDW    .D2T1   A5:A4,*B5         ; |160| 

           ; BRANCHCC OCCURS {$C$L10}        ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

           LDW     .D1T2   *A3,B4            ; |162| 
||         STW     .D2T1   A12,*+SP(16)      ; |162| 

           MV      .L1     A10,A4
           MVK     .L1     0x7,A6            ; |162| 
           ADDKPC  .S2     $C$RL14,B3,1      ; |162| 
$C$RL14:   ; CALL OCCURS {atandp_v} {0}      ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S2     0x3e112e0b,B5
           MVKL    .S2     0xe826d695,B4
           MVKH    .S2     0x3e112e0b,B5
           MVKH    .S2     0xe826d695,B4

           CALLP   .S2     allequal,B3
||         MVK     .L1     0x7,A4            ; |165| 

$C$RL15:   ; CALL OCCURS {allequal} {0}      ; |165| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x3,A4            ; |166| 

$C$RL16:   ; CALL OCCURS {print_test_results} {0}  ; |166| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKL    .S1     a_ext,A13

           MVK     .S1     0x777,A3
||         ZERO    .L2     B5

           SET     .S2     B5,0x14,0x14,B5
||         MVKH    .S1     a_ext,A13
||         ZERO    .L2     B4                ; |169| 

           CALL    .S1     atan              ; |171| 
||         STDW    .D1T2   B5:B4,*A13        ; |169| 
||         MV      .L1     A13,A10           ; |169| 
||         MV      .L2X    A3,B12            ; |169| 
||         ZERO    .S2     B13               ; |169| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10,A5:A4        ; |171| 
           ADDKPC  .S2     $C$RL17,B3,3      ; |171| 
$C$RL17:   ; CALL OCCURS {atan} {0}          ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D1T1   *A15,A3           ; |171| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |171| 
           STDW    .D1T1   A5:A4,*A3         ; |171| 

           CALLP   .S2     atandp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |172| 

$C$RL18:   ; CALL OCCURS {atandp} {0}        ; |172| 
           LDW     .D1T1   *+A15(4),A3       ; |172| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |172| 
           STDW    .D1T1   A5:A4,*A3         ; |172| 

           CALLP   .S2     atandp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |173| 

$C$RL19:   ; CALL OCCURS {atandp_c} {0}      ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 25
           LDW     .D1T1   *+A15(8),A3       ; |173| 
           ZERO    .L2     B9
           ZERO    .L2     B8                ; |171| 
           SET     .S2     B8,31,31,B8       ; |171| 
           SET     .S2     B9,0x14,0x1d,B9
           ADD     .L2X    B13,A3,B4         ; |173| 
           STDW    .D2T1   A5:A4,*B4         ; |173| 
           LDDW    .D1T2   *A10,B7:B6        ; |167| 
           ZERO    .L1     A5:A4             ; |170| 
           NOP             3
           DADD    .L2     0,B7:B6,B5:B4     ; |170| 
           NOP             1
           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |170| 
           NOP             1

   [ A0]   XOR     .L2     B5,B8,B7          ; |171| 
|| [ A0]   MV      .S2     B4,B6             ; |171| 
||         ZERO    .D2     B8                ; |175| 

   [!A0]   MVK     .L2     0xffffffff,B0     ; |166| 
||         CMPGTDP .S2     B7:B6,B9:B8,B1    ; |175| 

   [ A0]   ZERO    .L2     B0                ; |175| 

   [!B1]   B       .S1     $C$L15
||         RCPDP   .S2     B7:B6,B5:B4       ; |55| 
|| [!B1]   MV      .L1X    B8,A14            ; |175| 
|| [ B1]   ZERO    .D1     A5

   [ B1]   SET     .S1     A5,0x1e,0x1e,A5
|| [ B1]   ZERO    .L1     A4                ; |55| 

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
|| [!B1]   MVKL    .S2     0x3fd12614,B5

   [!B1]   MVKL    .S2     0x5e9ecd56,B4
   [!B1]   MVKH    .S2     0x3fd12614,B5
   [!B1]   MVKH    .S2     0x5e9ecd56,B4
           ; BRANCHCC OCCURS {$C$L15}  
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 32
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |55| 
           ZERO    .L2     B16               ; |55| 
           ZERO    .L2     B17
           SET     .S2     B17,0x1e,0x1e,B17
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |55| 
           ZERO    .L1     A4                ; |55| 
           MV      .L1X    B17,A5            ; |55| 
           MVK     .L1     0x2,A14           ; |177| 
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |55| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |55| 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |55| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B7:B6,A5:A4 ; |55| 
           NOP             3

           FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |55| 
||         MVKL    .S2     0x5e9ecd56,B4

           MVKL    .S2     0x3fd12614,B5
           MVKH    .S2     0x5e9ecd56,B4
           MVKH    .S2     0x3fd12614,B5
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 8
           CMPGTDP .S2     B7:B6,B5:B4,B1    ; |180| 
           NOP             1

   [!B1]   B       .S1     $C$L16            ; |180| 
||         MVKL    .S2     0x3ffbb67a,B5

           MVKL    .S2     0xe8584caa,B4
           MVKH    .S2     0x3ffbb67a,B5
           MVKH    .S2     0xe8584caa,B4
           FADDDP  .L2     B5:B4,B7:B6,B9:B8 ; |55| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L16}        ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 39
           ZERO    .L1     A4                ; |55| 
           RCPDP   .S2     B9:B8,B5:B4       ; |55| 
           ZERO    .L1     A5
           FMPYDP  .M2     B5:B4,B9:B8,B17:B16 ; |55| 
           SET     .S1     A5,0x1e,0x1e,A5
           ZERO    .L1     A9
           ZERO    .L1     A8                ; |55| 
           SET     .S1     A9,0x1e,0x1e,A9
           FSUBDP  .L1X    A5:A4,B17:B16,A5:A4 ; |55| 
           ZERO    .L1     A31
           ADD     .S1     1,A14,A14         ; |181| 
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |55| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B9:B8,A7:A6 ; |55| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |55| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |55| 
           MVKL    .S1     0xe8584caa,A6
           MVKL    .S1     0x3ffbb67a,A7
           MVKH    .S1     0xe8584caa,A6
           MVKH    .S1     0x3ffbb67a,A7
           FMPYDP  .M2X    A5:A4,B9:B8,B5:B4 ; |55| 
           MV      .L2X    A9,B9             ; |55| 
           MV      .L2X    A8,B8             ; |55| 
           NOP             1

           FSUBDP  .L2     B9:B8,B5:B4,B7:B6 ; |55| 
||         FMPYDP  .M2X    A7:A6,B7:B6,B5:B4 ; |55| 

           SET     .S1     A31,0x14,0x1d,A7
           MV      .L1     A8,A6             ; |55| 
           FMPYDP  .M2X    A5:A4,B7:B6,B7:B6 ; |55| 
           FSUBDP  .L2X    B5:B4,A7:A6,B5:B4 ; |55| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |55| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 17

           ZERO    .L1     A5:A4             ; |187| 
||         ZERO    .S1     A3                ; |188| 

           MVKL    .S2     0x3e4fffff,B9
           SET     .S1     A3,31,31,A3       ; |188| 
           DADD    .L2     0,B7:B6,B5:B4     ; |185| 
           MVKH    .S2     0x3e4fffff,B9
           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |187| 
           MVK     .S2     0xffffedec,B8     ; |191| 
   [ A0]   XOR     .L2X    B5,A3,B5          ; |188| 
           CMPGTDP .S2     B5:B4,B9:B8,B1    ; |191| 
           FMPYDP  .M2     B5:B4,B5:B4,B5:B4 ; |55| 

   [ B1]   MVKL    .S2     0x402e0c49,B9
|| [!B1]   LDDW    .D1T1   *+A11[A14],A5:A4  ; |203| 

   [!B1]   B       .S1     $C$L17            ; |191| 
|| [ B1]   MVKL    .S2     0xe14ac710,B8

   [ B1]   MVKH    .S2     0x402e0c49,B9
   [ B1]   MVKH    .S2     0xe14ac710,B8

           FADDDP  .L2     B9:B8,B5:B4,B9:B8 ; |55| 
|| [!B1]   MVK     .S2     12,B4
|| [!B1]   ZERO    .D2     B5                ; |200| 

   [!B1]   ADD     .L2X    A15,B4,B4

   [!B1]   LDW     .D2T2   *B4,B8            ; |174| 
|| [!B1]   SET     .S2     B5,31,31,B31      ; |200| 
|| [!B1]   CMPLT   .L1     A14,2,A0          ; |199| 
|| [!B1]   MVKL    .S1     0xc000cccc,A7

           ; BRANCHCC OCCURS {$C$L17}        ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 72

           ZERO    .L2     B31
||         MVKL    .S2     0xc034817f,B19
||         FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
||         MVKL    .S1     0x320da3d7,A4

           MVKL    .S1     0x404dca0a,A5
           MVKH    .S1     0x320da3d7,A4
           MVKH    .S1     0x404dca0a,A5
           ZERO    .L1     A16               ; |55| 
           FADDDP  .L2X    A5:A4,B9:B8,B17:B16 ; |55| 
           ZERO    .L1     A17
           MVKL    .S2     0x40b6da5,B8
           FMPYDP  .M2     B5:B4,B17:B16,B17:B16 ; |55| 
           MVKL    .S2     0x40558a12,B9
           MVKH    .S2     0x40b6da5,B8
           MVKH    .S2     0x40558a12,B9
           FADDDP  .L2     B9:B8,B17:B16,B9:B8 ; |55| 
           ZERO    .L1     A31
           MVKL    .S2     0xb9e2bccb,B18
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
           MVKL    .S1     0xbcc495a9,A4
           MVKL    .S1     0x4044887c,A5
           MVKH    .S1     0xbcc495a9,A4
           MVKH    .S1     0x4044887c,A5
           FADDDP  .L1X    A5:A4,B9:B8,A5:A4 ; |55| 
           MVKH    .S2     0xc034817f,B19
           SET     .S1     A17,0x1e,0x1e,A17
           RCPDP   .S1     A5:A4,A7:A6       ; |55| 
           MVKH    .S2     0xb9e2bccb,B18
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |55| 
           ZERO    .L2     B16               ; |55| 
           MVKL    .S2     0xd9b187bd,B8
           MVKL    .S2     0xbfeacd7a,B9
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |55| 
           MVKH    .S2     0xd9b187bd,B8
           MVKH    .S2     0xbfeacd7a,B9
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |55| 
           FMPYDP  .M2     B9:B8,B5:B4,B9:B8 ; |55| 
           MVKL    .S1     0xc020fd3f,A9
           MVKL    .S1     0x5c8d6a63,A8
           FMPYDP  .M1     A7:A6,A5:A4,A17:A16 ; |55| 
           MVKH    .S1     0xc020fd3f,A9
           MVKH    .S1     0x5c8d6a63,A8
           SET     .S2     B31,0x1e,0x1e,B17
           FADDDP  .L2X    A9:A8,B9:B8,B9:B8 ; |55| 
           FSUBDP  .L2X    B17:B16,A17:A16,B17:B16 ; |55| 
           SET     .S1     A31,0x1e,0x1e,A9
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
           ZERO    .L1     A8                ; |55| 
           FMPYDP  .M1X    B17:B16,A7:A6,A7:A6 ; |55| 
           MVKL    .S1     0x51061ce2,A16
           FADDDP  .L2     B19:B18,B9:B8,B9:B8 ; |55| 
           MVKL    .S1     0xc02b60a6,A17
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |55| 
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |55| 
           MVKH    .S1     0x51061ce2,A16
           MVKH    .S1     0xc02b60a6,A17
           FSUBDP  .S1     A9:A8,A5:A4,A5:A4 ; |55| 
           FADDDP  .L2X    A17:A16,B9:B8,B9:B8 ; |55| 
           CMPLT   .L1     A14,2,A0          ; |199| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |55| 
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |55| 
           MVKL    .S1     0xc000cccc,A7
           NOP             2
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |55| 
           LDDW    .D1T1   *+A11[A14],A5:A4  ; |203| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |196| 
           NOP             3

           FADDDP  .L2     B5:B4,B7:B6,B7:B6 ; |196| 
||         MVK     .S2     12,B4
||         ZERO    .D2     B5                ; |200| 

           ADD     .L2X    A15,B4,B4
||         SET     .S2     B5,31,31,B31      ; |200| 

           LDW     .D2T2   *B4,B8            ; |174| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 16

           SUB     .L1X    B12,1,A2          ; |170| 
|| [!A0]   XOR     .L2     B7,B31,B7         ; |200| 

           FADDDP  .L2X    A5:A4,B7:B6,B5:B4 ; |203| 
   [!B0]   ZERO    .L2     B6                ; |206| 
   [!B0]   SET     .S2     B6,31,31,B6       ; |206| 

   [!B0]   XOR     .L2     B5,B6,B5          ; |206| 
||         ADD     .S2     B13,B8,B30        ; |174| 

           STDW    .D2T2   B5:B4,*B30        ; |174| 
           LDDW    .D1T1   *A10,A5:A4        ; |175| 
           MVKL    .S1     0xcccccccd,A6
           MVKH    .S1     0xcccccccd,A6
           MVKH    .S1     0xc000cccc,A7
   [ A2]   B       .S1     $C$L14            ; |170| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |175| 
           SUB     .L2     B12,1,B12         ; |170| 
           ADD     .L2     8,B13,B13         ; |170| 
           NOP             1

   [ A2]   CALL    .S1     atan              ; |171| 
||         STDW    .D1T1   A5:A4,*++A10      ; |175| 

           ; BRANCHCC OCCURS {$C$L14}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     atandp_v          ; |177| 
           LDW     .D1T2   *A12,B4           ; |177| 
           ADDKPC  .S2     $C$RL20,B3,2      ; |177| 

           MV      .L1     A13,A4
||         MVK     .S1     0x777,A6          ; |177| 

$C$RL20:   ; CALL OCCURS {atandp_v} {0}      ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S2     0x3e5240ec,B5
           MVKL    .S2     0xa6a943fe,B4
           MVKH    .S2     0x3e5240ec,B5
           MVKH    .S2     0xa6a943fe,B4

           CALLP   .S2     allequal,B3
||         MVK     .S1     0x777,A4          ; |183| 

$C$RL21:   ; CALL OCCURS {allequal} {0}      ; |183| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x4,A4            ; |184| 

$C$RL22:   ; CALL OCCURS {print_test_results} {0}  ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
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

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B5:B4,*A3         ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKL    .S1     0x402921fb,A5

           EXT     .S2     B7,24,24,B4       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B5,B4,B7          ; |117| 
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B7:B6,*A3         ; |117| 
||         MVKL    .S1     input,A3
||         MVK     .S2     0x80,B12

           MVKH    .S1     input,A3
||         CALL    .S2     gimme_random      ; |194| 

           LDW     .D1T1   *A3,A10           ; |194| 
||         MVKL    .S2     0x3fa6defc,B4
||         MVKH    .S1     0x402921fb,A5
||         ZERO    .L1     A13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 4
           MVKL    .S2     0xc01921fb,B5
           MVKH    .S2     0x3fa6defc,B4
           MVKH    .S2     0xc01921fb,B5

           MV      .L1X    B4,A4             ; |194| 
||         ADDKPC  .S2     $C$RL23,B3,0      ; |194| 

$C$RL23:   ; CALL OCCURS {gimme_random} {0}  ; |194| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           ADD     .L1     A10,A13,A3        ; |194| 

           STDW    .D1T1   A5:A4,*A3         ; |194| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A16            ; |122| Define a twin register
||         MVC     .S2     TSCH,B4           ; |122| 

           ZERO    .L1     A9
||         ZERO    .S1     A8                ; |175| 
||         ADD     .D1     A10,A13,A3        ; |170| 

           LDDW    .D1T1   *A3,A7:A6         ; |170| 
           ZERO    .L2     B5                ; |171| 
           ZERO    .L2     B7:B6             ; |170| 
           SET     .S2     B5,31,31,B5       ; |171| 
           MV      .L1X    B4,A17            ; |122| 
           CMPLTDP .S2X    A7:A6,B7:B6,B0    ; |170| 
           SET     .S1     A9,0x14,0x1d,A9

   [ B0]   XOR     .L1X    A7,B5,A5          ; |171| 
|| [ B0]   MV      .S1     A6,A4             ; |171| 

           CMPGTDP .S1     A5:A4,A9:A8,A0    ; |175| 

   [ B0]   ZERO    .L2     B0                ; |172| 
|| [!B0]   MVK     .S2     0xffffffff,B0     ; |166| 

   [!A0]   B       .S2     $C$L19
||         RCPDP   .S1     A5:A4,A7:A6       ; |55| 
|| [!A0]   MV      .L1     A8,A12            ; |122| 
|| [ A0]   ZERO    .L2     B5
|| [ A0]   ZERO    .D2     B4                ; |55| 

   [ A0]   SET     .S2     B5,0x1e,0x1e,B5

           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |55| 
|| [!A0]   MVKL    .S1     0x3fd12614,A7

   [!A0]   MVKL    .S1     0x5e9ecd56,A6
   [!A0]   MVKH    .S1     0x3fd12614,A7
   [!A0]   MVKH    .S1     0x5e9ecd56,A6
           ; BRANCHCC OCCURS {$C$L19}  
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 32
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |55| 
           ZERO    .L1     A18               ; |55| 
           ZERO    .L1     A19
           SET     .S1     A19,0x1e,0x1e,A19
           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |55| 
           ZERO    .L2     B4                ; |55| 
           MV      .L2X    A19,B5            ; |55| 
           MVK     .L1     0x2,A12           ; |177| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |55| 
           NOP             3
           FSUBDP  .L1     A19:A18,A9:A8,A9:A8 ; |55| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |55| 
           NOP             3
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |55| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |55| 
           NOP             3

           FMPYDP  .M1X    A7:A6,B5:B4,A5:A4 ; |55| 
||         MVKL    .S1     0x5e9ecd56,A6

           MVKL    .S1     0x3fd12614,A7
           MVKH    .S1     0x5e9ecd56,A6
           MVKH    .S1     0x3fd12614,A7
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 8
           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |180| 
           NOP             1

   [!A0]   B       .S2     $C$L20            ; |180| 
||         MVKL    .S1     0x3ffbb67a,A7

           MVKL    .S1     0xe8584caa,A6
           MVKH    .S1     0x3ffbb67a,A7
           MVKH    .S1     0xe8584caa,A6
           FADDDP  .L1     A7:A6,A5:A4,A9:A8 ; |55| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L20}        ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 39
           ZERO    .L2     B4                ; |55| 
           RCPDP   .S1     A9:A8,A7:A6       ; |55| 
           ZERO    .L2     B5
           FMPYDP  .M1     A7:A6,A9:A8,A19:A18 ; |55| 
           SET     .S2     B5,0x1e,0x1e,B5
           ZERO    .L2     B9
           ZERO    .L2     B8                ; |55| 
           SET     .S2     B9,0x1e,0x1e,B9
           FSUBDP  .L2X    B5:B4,A19:A18,B5:B4 ; |55| 
           ZERO    .L2     B31
           ADD     .L1     1,A12,A12         ; |181| 
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |55| 
           ZERO    .L1     A6                ; |55| 
           MV      .L1X    B9,A7             ; |55| 
           NOP             1
           FMPYDP  .M2X    B5:B4,A9:A8,B7:B6 ; |55| 
           NOP             3
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |55| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |55| 
           MVKL    .S2     0x3ffbb67a,B7
           MVKL    .S2     0xe8584caa,B6
           MVKH    .S2     0x3ffbb67a,B7
           MVKH    .S2     0xe8584caa,B6
           FMPYDP  .M1X    B5:B4,A9:A8,A9:A8 ; |55| 
           NOP             3

           FSUBDP  .L1     A7:A6,A9:A8,A5:A4 ; |55| 
||         FMPYDP  .M1X    B7:B6,A5:A4,A7:A6 ; |55| 

           SET     .S2     B31,0x14,0x1d,B7
           MV      .L2     B8,B6             ; |55| 
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |55| 
           FSUBDP  .L1X    A7:A6,B7:B6,A7:A6 ; |55| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |55| 
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 16

           ZERO    .S1     A3                ; |188| 
||         MVKL    .S2     0x3e4fffff,B5

           SET     .S1     A3,31,31,A3       ; |188| 
           ZERO    .L1     A9:A8             ; |187| 
           DADD    .L1     0,A5:A4,A7:A6     ; |185| 
           CMPLTDP .S1     A7:A6,A9:A8,A0    ; |187| 
           MVKH    .S2     0x3e4fffff,B5
   [ A0]   XOR     .L1     A7,A3,A7          ; |188| 
           MVK     .S2     0xffffedec,B4     ; |191| 
           CMPGTDP .S2X    A7:A6,B5:B4,B1    ; |191| 
           FMPYDP  .M1     A7:A6,A7:A6,A7:A6 ; |55| 

   [!B1]   B       .S2     $C$L21            ; |191| 
|| [ B1]   MVKL    .S1     0x402e0c49,A9
|| [!B1]   ZERO    .D1     A3                ; |200| 
|| [!B1]   CMPLT   .L1     A12,2,A0          ; |199| 

   [!B1]   MVK     .S2     12,B4
|| [ B1]   MVKL    .S1     0xe14ac710,A8

   [!B1]   ADD     .L2X    A15,B4,B4
|| [ B1]   MVKH    .S1     0x402e0c49,A9

   [!B1]   LDW     .D2T2   *B4,B4            ; |198| 
|| [ B1]   MVKH    .S1     0xe14ac710,A8

           FADDDP  .L1     A9:A8,A7:A6,A9:A8 ; |55| 
|| [!B1]   LDDW    .D1T1   *+A11[A12],A9:A8  ; |203| 

   [!B1]   SET     .S1     A3,31,31,A6       ; |200| 
           ; BRANCHCC OCCURS {$C$L21}        ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 72

           ZERO    .S1     A31
||         MVKL    .S2     0x404dca0a,B5

           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |55| 
||         MVKL    .S2     0x320da3d7,B4

           MVKH    .S2     0x404dca0a,B5
           MVKH    .S2     0x320da3d7,B4
           ZERO    .L2     B16               ; |55| 
           FADDDP  .L1X    B5:B4,A9:A8,A19:A18 ; |55| 
           ZERO    .L2     B17
           MVKL    .S1     0x40b6da5,A8
           FMPYDP  .M1     A7:A6,A19:A18,A19:A18 ; |55| 
           MVKL    .S1     0x40558a12,A9
           MVKH    .S1     0x40b6da5,A8
           MVKH    .S1     0x40558a12,A9
           FADDDP  .L1     A9:A8,A19:A18,A9:A8 ; |55| 
           ZERO    .L2     B31
           SET     .S2     B17,0x1e,0x1e,B17
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |55| 
           MVKL    .S2     0x4044887c,B5
           MVKL    .S2     0xbcc495a9,B4
           MVKH    .S2     0x4044887c,B5
           MVKH    .S2     0xbcc495a9,B4
           FADDDP  .L2X    B5:B4,A9:A8,B5:B4 ; |55| 
           ZERO    .L1     A18               ; |55| 
           MVKL    .S1     0xd9b187bd,A8
           RCPDP   .S2     B5:B4,B7:B6       ; |55| 
           MVKL    .S1     0xbfeacd7a,A9
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
           MVKH    .S1     0xd9b187bd,A8
           MVKH    .S1     0xbfeacd7a,A9
           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |55| 

           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |55| 
||         MVKL    .S2     0xc020fd3f,B17

           MVKL    .S2     0x5c8d6a63,B16
           MVKH    .S2     0xc020fd3f,B17
           FMPYDP  .M2     B7:B6,B9:B8,B7:B6 ; |55| 
           MVKH    .S2     0x5c8d6a63,B16
           SET     .S1     A31,0x1e,0x1e,A19
           FADDDP  .L1X    B17:B16,A9:A8,A9:A8 ; |55| 
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
           MVKL    .S2     0xc02b60a6,B17
           MVKL    .S2     0x51061ce2,B16
           MVKH    .S2     0xc02b60a6,B17
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |55| 
           FSUBDP  .L1X    A19:A18,B9:B8,A21:A20 ; |55| 
           MVKL    .S1     0xc034817f,A19
           MVKL    .S1     0xb9e2bccb,A18
           MVKH    .S1     0xc034817f,A19
           FMPYDP  .M2X    A21:A20,B7:B6,B7:B6 ; |55| 
           MVKH    .S1     0xb9e2bccb,A18
           FADDDP  .L1     A19:A18,A9:A8,A9:A8 ; |55| 
           MVKH    .S2     0x51061ce2,B16
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |55| 
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |55| 
           ZERO    .L2     B8                ; |55| 
           SET     .S2     B31,0x1e,0x1e,B9
           FSUBDP  .L2     B9:B8,B5:B4,B5:B4 ; |55| 
           FADDDP  .L1X    B17:B16,A9:A8,A9:A8 ; |55| 
           ZERO    .L1     A3                ; |200| 
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |55| 
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |55| 
           CMPLT   .L1     A12,2,A0          ; |199| 
           LDDW    .D1T1   *+A11[A12],A9:A8  ; |203| 
           NOP             1
           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |55| 
           MVK     .S2     12,B4
           ADD     .L2X    A15,B4,B4
           LDW     .D2T2   *B4,B4            ; |198| 
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |196| 
           NOP             3
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |196| 
           SET     .S1     A3,31,31,A6       ; |200| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 24

   [!A0]   XOR     .D1     A5,A6,A5          ; |200| 
|| [!B0]   ZERO    .L2     B5                ; |200| 
||         MVKL    .S1     t_start,A31

           MVKH    .S1     t_start,A31
   [!B0]   SET     .S2     B5,31,31,B5       ; |206| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |203| 
           STDW    .D1T1   A17:A16,*A31
           ADD     .S1X    A13,B4,A6         ; |198| 
   [!B0]   XOR     .L1X    A5,B5,A5          ; |206| 

           STDW    .D1T1   A5:A4,*A6         ; |198| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A3
||         MVKL    .S2     cycle_counts+24,B5
||         SUB     .L1X    B12,1,A0          ; |192| 
||         MV      .L2     B4,B9             ; |128| 
||         ADD     .D1     8,A13,A13         ; |192| 
||         SUB     .D2     B12,1,B12         ; |192| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     cycle_counts+24,B5

           MVKL    .S1     t_stop,A30
||         LDDW    .D1T1   *A3,A5:A4         ; |130| 

           LDDW    .D2T2   *B5,B7:B6         ; |130| 
           MVKH    .S1     t_stop,A30
           MV      .L1X    B5,A14            ; |130| 
           STDW    .D1T2   B9:B8,*A30        ; |128| 
           ADDU    .L1     A4,A16,A7:A6      ; |130| 

           ADD     .L1     A7,A5,A3          ; |130| 
|| [ A0]   MVKL    .S1     0x402921fb,A5

           ADD     .L1     A3,A17,A3         ; |130| 
|| [ A0]   B       .S2     $C$L18            ; |192| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 
|| [ A0]   MVKH    .S1     0x402921fb,A5

           EXT     .S2     B5,24,24,B16      ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 

           SUB     .L2X    B9,A3,B6          ; |130| 
||         ADD     .S2     B5,B7,B5          ; |130| 
|| [ A0]   MVKL    .S1     input,A3

           ADD     .L2     B6,B16,B6         ; |130| 
|| [ A0]   MVKH    .S1     input,A3

   [ A0]   CALL    .S1     gimme_random      ; |194| 
||         ADD     .L2     B5,B6,B5          ; |130| 
|| [ A0]   LDW     .D1T1   *A3,A10           ; |194| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T2   B5:B4,*A14        ; |130| 
|| [ A0]   MVKL    .S2     0x3fa6defc,B4

           ; BRANCHCC OCCURS {$C$L18}        ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL24,B3,3      ; |135| 
$C$RL24:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

$C$RL25:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(24),B5:B4
           MV      .L2X    A14,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B12
           MV      .L2X    A12,B31           ; |114| 

           STDW    .D2T2   B5:B4,*B12        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

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
||         CALL    .S1     atan              ; |206| 

           LDDW    .D1T1   *A10++,A5:A4      ; |206| 
           MV      .L1X    B6,A15            ; |117| 
           MVK     .S2     0x80,B13
           NOP             1
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL26,B3,0      ; |206| 
$C$RL26:   ; CALL OCCURS {atan} {0}          ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1X    B13,1,A0          ; |205| 
||         STDW    .D1T1   A5:A4,*A11++      ; |206| 

   [ A0]   B       .S1     $C$L22            ; |205| 
   [ A0]   CALL    .S1     atan              ; |206| 
   [ A0]   LDDW    .D1T1   *A10++,A5:A4      ; |206| 
           SUB     .L2     B13,1,B13         ; |205| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L22}        ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 
           LDW     .D2T1   *+SP(12),A3       ; |128| 
           MV      .L2     B4,B9             ; |128| 
           LDDW    .D2T2   *B12,B5:B4        ; |130| 
           ADDU    .L1     A15,A14,A5:A4     ; |130| 
           NOP             1

           ADD     .S1     A5,A3,A3          ; |130| 
||         SUBU    .L1X    B8,A4,A5:A4       ; |130| 
||         CALL    .S2     __c6xabi_fltllif  ; |130| 

           ADD     .L1     A3,A12,A3         ; |130| 
||         EXT     .S1     A5,24,24,A31      ; |130| 

           ADDU    .L2X    B4,A4,B7:B6       ; |130| 
||         SUB     .L1X    B9,A3,A3          ; |130| 
||         MVKL    .S2     t_stop,B4

           ADD     .L2     B7,B5,B5          ; |130| 
||         ADD     .L1     A3,A31,A3         ; |130| 
||         MVKH    .S2     t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         MV      .L1X    B6,A4             ; |130| 

           ADD     .L1X    B5,A3,A5          ; |130| 
||         ADDKPC  .S2     $C$RL27,B3,0      ; |130| 

$C$RL27:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
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

$C$RL28:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           LDDW    .D2T2   *+SP(24),B5:B4    ; |130| 
           ZERO    .L1     A10
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           SET     .S1     A10,0x1a,0x1d,A10

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T2   B5:B4,*+B12(8)    ; |114| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     t_start,A15

           MVKH    .S1     t_start,A15
||         MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 

           SUBU    .L2     B4,B8,B5:B4       ; |117| 
||         MVKL    .S2     t_offset,B13

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B6,B9,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S2     t_offset,B13

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MVKL    .S1     input,A14

           MV      .L1X    B4,A11            ; |117| 
||         MVKH    .S1     input,A14

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A14,A3           ; |214| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |214| 
||         CALL    .S1     atandp            ; |214| 

           LDDW    .D1T1   *A3,A5:A4         ; |214| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |214| 
$C$RL29:   ; CALL OCCURS {atandp} {0}        ; |214| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |214| 
||         SUB     .L1     A11,1,A0          ; |213| 
||         SUB     .S1     A11,1,A11         ; |213| 

   [ A0]   BNOP    .S1     $C$L23,3          ; |213| 

           ADD     .L1X    A12,B4,A3         ; |214| 
||         ADD     .S1     8,A12,A12         ; |213| 

           STDW    .D1T1   A5:A4,*A3         ; |214| 
           ; BRANCHCC OCCURS {$C$L23}        ; |213| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MV      .L2     B4,B9             ; |128| 
           LDDW    .D2T2   *+B12(8),B5:B4    ; |130| 
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
||         ADDKPC  .S2     $C$RL30,B3,0      ; |130| 

$C$RL30:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A10,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDDW    .D2T2   *+SP(24),B5:B4
           ADDAD   .D2     B12,1,B11
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B11        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B12(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 

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
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L24:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A14,A3           ; |222| 
           NOP             4

           ADD     .L1     A11,A3,A3         ; |222| 
||         CALL    .S1     atandp_c          ; |222| 

           LDDW    .D1T1   *A3,A5:A4         ; |222| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |222| 
$C$RL32:   ; CALL OCCURS {atandp_c} {0}      ; |222| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B10,B4           ; |222| 
||         SUB     .L1     A12,1,A0          ; |221| 
||         SUB     .S1     A12,1,A12         ; |221| 

   [ A0]   BNOP    .S1     $C$L24,3          ; |221| 

           ADD     .L1X    A11,B4,A3         ; |222| 
||         ADD     .S1     8,A11,A11         ; |221| 

           STDW    .D1T1   A5:A4,*A3         ; |222| 
           ; BRANCHCC OCCURS {$C$L24}        ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MV      .L1     A15,A11           ; |128| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           LDDW    .D1T1   *A11,A5:A4        ; |130| 
           LDDW    .D2T2   *+B12(16),B17:B16 ; |130| 
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
||         ADDKPC  .S2     $C$RL33,B3,0      ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 106
           MPYSP   .M1     A10,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(24),B5:B4
           ADDAD   .D2     B11,1,B10
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B12(32)   ; |114| 
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
||         MV      .L2X    A14,B9            ; |229| 
||         STDW    .D2T2   B5:B4,*B13        ; |117| 

           CALLP   .S2     atandp_v,B3
||         LDW     .D1T2   *+A11(16),B4      ; |229| 
||         LDW     .D2T1   *B9,A4            ; |229| 
||         MVK     .S1     0x80,A6           ; |229| 

$C$RL35:   ; CALL OCCURS {atandp_v} {0}      ; |229| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MVK     .S1     16,A14
           ADD     .L1X    B10,A14,A14
           MVKL    .S1     t_stop,A3

           LDDW    .D1T1   *A14,A17:A16      ; |130| 
||         MVKH    .S1     t_stop,A3

           ADDU    .L1X    B6,A6,A9:A8       ; |130| 

           MV      .L2     B4,B9             ; |128| 
||         MV      .S2X    A3,B4             ; |128| 
||         ADD     .L1X    A9,B7,A3          ; |130| 

           SUBU    .L1X    B8,A8,A5:A4       ; |130| 

           ADD     .L1     A3,A7,A5          ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           SUB     .S1X    B9,A5,A6          ; |130| 
||         ADDU    .L1     A16,A4,A5:A4      ; |130| 

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A6,A3,A5          ; |130| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           MPYSP   .M1     A10,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MVKH    .S2     0xe826d695,B6

           DADD    .L1     0,A5:A4,A7:A6     ; |130| 
||         LDW     .D1T1   *A11,A4           ; |66| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     isequal,B3
||         STDW    .D1T1   A7:A6,*A14        ; |130| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL38:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A10
||         MVKH    .S2     0xe826d695,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A10
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A5,*+A10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL39:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6

           STW     .D1T1   A4,*+A10(8)       ; |67| 
||         MVKH    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL40:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(16),A3       ; |68| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           MV      .L1     A11,A5            ; |68| 
||         STW     .D1T1   A4,*+A10(12)      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           LDW     .D1T1   *A5,A4            ; |69| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL41:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2X    4,A10,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D1T1   A4,*+A10(16)      ; |69| 
           ADD     .L2X    8,A10,B4
           NOP             2

   [!B0]   BNOP    .S1     $C$L25,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L25}        ; |72| 
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
   [ A0]   B       .S1     $C$L26            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |235| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L26}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L25:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |235| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L26:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |235| 
||         ADDKPC  .S2     $C$RL42,B3,0      ; |235| 

$C$RL42:   ; CALL OCCURS {print_test_results} {0}  ; |235| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |236| 

$C$RL43:   ; CALL OCCURS {printf} {0}        ; |236| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |236| 

$C$RL44:   ; CALL OCCURS {printf} {0}        ; |236| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |243| 

$C$RL45:   ; CALL OCCURS {print_profile_results} {0}  ; |243| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |246| 

$C$RL46:   ; CALL OCCURS {print_memory_results} {0}  ; |246| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(40),B3      ; |247| 
           LDDW    .D2T1   *++SP,A13:A12     ; |247| 
           LDDW    .D2T1   *++SP,A15:A14     ; |247| 
           LDDW    .D2T2   *++SP,B11:B10     ; |247| 
           LDDW    .D2T2   *++SP,B13:B12     ; |247| 

           LDW     .D2T1   *++SP(8),A10      ; |247| 
||         RET     .S2     B3                ; |247| 

           LDW     .D2T1   *++SP(8),A11      ; |247| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |247| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"atanDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	atan
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	atandp
	.global	atandp_c
	.global	atandp_v
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
	.global	V
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
