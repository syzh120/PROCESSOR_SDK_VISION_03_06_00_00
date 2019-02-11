;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 23:05:51 2013                                *
;******************************************************************************
	.compiler_opts --abi=coffabi --c64p_l1d_workaround=off --endian=big --hll_source=on --long_precision_bits=40 --mem_model:code=near --mem_model:const=data --mem_model:data=far --object_format=coff --silicon_version=6600 --symdebug:none 

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

;*****************************************************************************
;* CINIT RECORDS                                                             *
;*****************************************************************************
	.sect	".cinit"
	.align	8
	.field  	$C$IR_1,32
	.field  	_a+0,32
	.word	0c13fa464h,000000000h		; _a[0] @ 0
	.word	03f2d4b6ah,0619da9cah		; _a[1] @ 64
	.word	0bf305e4ch,02f9139bah		; _a[2] @ 128
	.word	03f324aa8h,0974ec0cch		; _a[3] @ 192
	.word	0bf3470deh,0e70af974h		; _a[4] @ 256
	.word	03f36d7bbh,0ded5f343h		; _a[5] @ 320
	.word	0bf3986d7h,065a623cbh		; _a[6] @ 384
	.word	03f3c86afh,09844c10bh		; _a[7] @ 448
	.word	0bf3fe0c0h,0689e20a8h		; _a[8] @ 512
	.word	03f41cfd1h,0ea0c0599h		; _a[9] @ 576
	.word	0bf43e799h,043edc76dh		; _a[10] @ 640
	.word	03f463e54h,0d6446578h		; _a[11] @ 704
	.word	0bf48db6ah,047bd1b0dh		; _a[12] @ 768
	.word	03f4bc71dh,0f0b2ae5eh		; _a[13] @ 832
	.word	0bf4f0aach,0324bcd4bh		; _a[14] @ 896
	.word	03f515834h,015fe9162h		; _a[15] @ 960
	.word	0bf5361edh,0c1f61557h		; _a[16] @ 1024
	.word	03f55a8f4h,02a89c15fh		; _a[17] @ 1088
	.word	0bf58347bh,0fff814c7h		; _a[18] @ 1152
	.word	03f5b0c92h,0d7d5e1c1h		; _a[19] @ 1216
	.word	0bf5e3a35h,0b97dee20h		; _a[20] @ 1280
	.word	03f60e3b9h,0bd1461d1h		; _a[21] @ 1344
	.word	0bf62dfc3h,040ff4613h		; _a[22] @ 1408
	.word	03f65177eh,0ccb9ac8ah		; _a[23] @ 1472
	.word	0bf6791efh,0ac1fd90eh		; _a[24] @ 1536
	.word	03f6a56ech,028904a99h		; _a[25] @ 1600
	.word	0bf6d6f37h,04dfd9779h		; _a[26] @ 1664
	.word	03f70724dh,0580024c7h		; _a[27] @ 1728
	.word	0bf726103h,0501698c9h		; _a[28] @ 1792
	.word	03f7489dah,0005e6c13h		; _a[29] @ 1856
	.word	0bf76f3a6h,0443bb2f8h		; _a[30] @ 1920
	.word	03f79a609h,0c8087578h		; _a[31] @ 1984
	.word	0bf7ca98bh,0fffdfc9bh		; _a[32] @ 2048
	.word	03f8003dah,0c4cbe637h		; _a[33] @ 2112
	.word	0bf81e596h,04febae42h		; _a[34] @ 2176
	.word	03f83ffech,0ac329ad4h		; _a[35] @ 2240
	.word	0bf865983h,05407ea04h		; _a[36] @ 2304
	.word	03f88f9cah,0b1bf8033h		; _a[37] @ 2368
	.word	0bf8be910h,0a53ebe57h		; _a[38] @ 2432
	.word	03f8f309bh,07e4b3487h		; _a[39] @ 2496
	.word	0bf916d66h,05fdb5cddh		; _a[40] @ 2560
	.word	03f93799dh,04fdc8c32h		; _a[41] @ 2624
	.word	0bf95c36ch,0d1ba7257h		; _a[42] @ 2688
	.word	03f985211h,019d8c427h		; _a[43] @ 2752
	.word	0bf9b2da1h,022fad6cbh		; _a[44] @ 2816
	.word	03f9e5f26h,0d7045e34h		; _a[45] @ 2880
	.word	0bfa0f85dh,09f427afah		; _a[46] @ 2944
	.word	03fa2f6d4h,00753b158h		; _a[47] @ 3008
	.word	0bfa53145h,0475ce0d7h		; _a[48] @ 3072
	.word	03fa7aebdh,098267cech		; _a[49] @ 3136
	.word	0bfaa771ch,0970f7b9eh		; _a[50] @ 3200
	.word	03fad9330h,01dfff03bh		; _a[51] @ 3264
	.word	0bfb08666h,0b6ee3e37h		; _a[52] @ 3328
	.word	03fb27779h,03347ab0fh		; _a[53] @ 3392
	.word	0bfb4a2f3h,0b56ee236h		; _a[54] @ 3456
	.word	03fb70fb2h,0d0775145h		; _a[55] @ 3520
	.word	0bfb9c562h,075401dfdh		; _a[56] @ 3584
	.word	03fbccc93h,0c1e943fch		; _a[57] @ 3648
	.word	0bfc0176dh,0040f5939h		; _a[58] @ 3712
	.word	03fc1fb75h,056c431f4h		; _a[59] @ 3776
	.word	0bfc4185dh,0c4d73506h		; _a[60] @ 3840
	.word	03fc674d3h,0e7734140h		; _a[61] @ 3904
	.word	0bfc91851h,02f9d7c7dh		; _a[62] @ 3968
	.word	03fcc0b2ch,083ec892bh		; _a[63] @ 4032
	.word	0bfcf56bah,020f89e0ch		; _a[64] @ 4096
	.word	03fd182b2h,0cd474610h		; _a[65] @ 4160
	.word	0bfd3916ah,0202f4a70h		; _a[66] @ 4224
	.word	03fd5de05h,06ed4c9f1h		; _a[67] @ 4288
	.word	0bfd86fcah,027d6de9fh		; _a[68] @ 4352
	.word	03fdb4ed8h,03fc7962ch		; _a[69] @ 4416
	.word	0bfde8444h,09dbec248h		; _a[70] @ 4480
	.word	03fe10d1ah,0d065de81h		; _a[71] @ 4544
	.word	0bfe30e01h,04a82db11h		; _a[72] @ 4608
	.word	03fe54b2bh,0ad2cf455h		; _a[73] @ 4672
	.word	0bfe7cbaeh,0f54b7118h		; _a[74] @ 4736
	.word	03fea9774h,090cb94beh		; _a[75] @ 4800
	.word	0bfedb754h,0cb336f99h		; _a[76] @ 4864
	.word	03ff09a98h,0676a7265h		; _a[77] @ 4928
	.word	0bff28e0ah,084be4042h		; _a[78] @ 4992
	.word	03ff4bc2bh,094d94079h		; _a[79] @ 5056
	.word	0bff72be1h,0650a45d4h		; _a[80] @ 5120
	.word	03ff9e4e0h,054690de1h		; _a[81] @ 5184
	.word	0bffcefc5h,08ab92c06h		; _a[82] @ 5248
	.word	040002b17h,08b370047h		; _a[83] @ 5312
	.word	0c002116fh,04384ba0fh		; _a[84] @ 5376
	.word	0400430ech,0b74ddf87h		; _a[85] @ 5440
	.word	0c0069045h,0fe111277h		; _a[86] @ 5504
	.word	0400936fch,0158fb43eh		; _a[87] @ 5568
	.word	0c00c2d71h,0f36262cch		; _a[88] @ 5632
	.word	0400f7d06h,0bbdbe3c1h		; _a[89] @ 5696
	.word	0c0119819h,008e581cfh		; _a[90] @ 5760
	.word	04013a954h,021c04428h		; _a[91] @ 5824
	.word	0c015f8beh,0f8ceb357h		; _a[92] @ 5888
	.word	040188da7h,02a7bd48dh		; _a[93] @ 5952
	.word	0c01b7037h,09314445bh		; _a[94] @ 6016
	.word	0401ea990h,029ae4f33h		; _a[95] @ 6080
	.word	0c02121f1h,08c9fb613h		; _a[96] @ 6144
	.word	04023254ah,0a10e0221h		; _a[97] @ 6208
	.word	0c0256531h,011f0c34ch		; _a[98] @ 6272
	.word	04027e8c3h,0f3e0370dh		; _a[99] @ 6336
	.word	0c02ab7f3h,08c5436b9h		; _a[100] @ 6400
	.word	0402ddba5h,0e353f7cfh		; _a[101] @ 6464
	.word	0c030aee3h,092e1ef74h		; _a[102] @ 6528
	.word	04032a4b7h,0d41743e9h		; _a[103] @ 6592
	.word	0c034d582h,0fd75e204h		; _a[104] @ 6656
	.word	040374833h,01e3a7daah		; _a[105] @ 6720
	.word	0c03a0486h,005681ecdh		; _a[106] @ 6784
	.word	0403d1322h,0291fb3fah		; _a[107] @ 6848
	.word	0c0403edah,0122fad6dh		; _a[108] @ 6912
	.word	040422784h,0230fcf81h		; _a[109] @ 6976
	.word	0c0444999h,09999999ah		; _a[110] @ 7040
	.word	04046abd9h,0018e7579h		; _a[111] @ 7104
	.word	0c04955cch,0b7d41744h		; _a[112] @ 7168
	.word	0404c4fe1h,086983516h		; _a[113] @ 7232
	.word	0c04fa381h,0d7dbf488h		; _a[114] @ 7296
	.word	04051ad99h,06fa82e88h		; _a[115] @ 7360
	.word	0c053c15bh,081301648h		; _a[116] @ 7424
	.word	040561398h,0f1d3ed52h		; _a[117] @ 7488
	.word	0c058aba8h,0d64d7f0fh		; _a[118] @ 7552
	.word	0405b91bfh,0487fcb92h		; _a[119] @ 7616
	.word	0c05ecf08h,09a027525h		; _a[120] @ 7680
	.word	0406136e1h,047ae147bh		; _a[121] @ 7744
	.word	0c0633cb0h,020c49ba6h		; _a[122] @ 7808
	.word	040657f57h,03eab367ah		; _a[123] @ 7872
	.word	0c06805fbh,0e76c8b44h		; _a[124] @ 7936
	.word	0406ad89ah,0d42c3c9fh		; _a[125] @ 8000
	.word	0c06e0023h,039c0ebeeh		; _a[126] @ 8064
	.word	04070c346h,0dc5d6388h		; _a[127] @ 8128
	.word	0c072bb80h,0346dc5d6h		; _a[128] @ 8192
	.word	04074eef9h,0096bb98ch		; _a[129] @ 8256
	.word	0c07764a7h,01de69ad4h		; _a[130] @ 8320
	.word	0407a2451h,0eb851eb8h		; _a[131] @ 8384
	.word	0c07d36aah,0cd9e83e4h		; _a[132] @ 8448
	.word	0408052b4h,06dc5d639h		; _a[133] @ 8512
	.word	0c0823db3h,0d07c84b6h		; _a[134] @ 8576
	.word	040846264h,08e8a71deh		; _a[135] @ 8640
	.word	0c086c78dh,0ed288ce7h		; _a[136] @ 8704
	.word	0408974c2h,0f837b4a2h		; _a[137] @ 8768
	.word	0c08c727bh,015b573ebh		; _a[138] @ 8832
	.word	0408fca2dh,00e560419h		; _a[139] @ 8896
	.word	0c091c334h,039581062h		; _a[140] @ 8960
	.word	04093d980h,000000000h		; _a[141] @ 9024
	.word	0c0962e93h,074bc6a7fh		; _a[142] @ 9088
	.word	04098c9ceh,0d916872bh		; _a[143] @ 9152
	.word	0c09bb371h,0a9fbe76dh		; _a[144] @ 9216
	.word	0409ef4b0h,020c49ba6h		; _a[145] @ 9280
	.word	0c0a14bebh,0020c49bah		; _a[146] @ 9344
	.word	040a35433h,033333333h		; _a[147] @ 9408
	.word	0c0a5999ch,0ac083127h		; _a[148] @ 9472
	.word	040a82357h,08d4fdf3bh		; _a[149] @ 9536
	.word	0c0aaf969h,0fbe76c8bh		; _a[150] @ 9600
	.word	040ae24cch,0cccccccdh		; _a[151] @ 9664
	.word	0c0b0d7c3h,053f7ced9h		; _a[152] @ 9728
	.word	040b2d265h,01eb851ech		; _a[153] @ 9792
	.word	0c0b5088eh,056041893h		; _a[154] @ 9856
	.word	040b7813dh,0b22d0e56h		; _a[155] @ 9920
	.word	0c0ba4444h,05a1cac08h		; _a[156] @ 9984
	.word	040bd5a5eh,076c8b439h		; _a[157] @ 10048
	.word	0c0c066a7h,04bc6a7f0h		; _a[158] @ 10112
	.word	040c253feh,0b851eb85h		; _a[159] @ 10176
	.word	0c0c47b4eh,0147ae148h		; _a[160] @ 10240
	.word	040c6e365h,01eb851ech		; _a[161] @ 10304
	.word	0c0c993deh,0b851eb85h		; _a[162] @ 10368
	.word	040cc953eh,0b851eb85h		; _a[163] @ 10432
	.word	0c0cff106h,066666666h		; _a[164] @ 10496
	.word	040d1d8e9h,09999999ah		; _a[165] @ 10560
	.word	0c0d3f1c2h,08f5c28f6h		; _a[166] @ 10624
	.word	040d649afh,05c28f5c3h		; _a[167] @ 10688
	.word	0c0d8e81ah,03d70a3d7h		; _a[168] @ 10752
	.word	040dbd54bh,0851eb852h		; _a[169] @ 10816
	.word	0c0df1a84h,07ae147aeh		; _a[170] @ 10880
	.word	040e1610eh,066666666h		; _a[171] @ 10944
	.word	0c0e36bd2h,03d70a3d7h		; _a[172] @ 11008
	.word	040e5b402h,08f5c28f6h		; _a[173] @ 11072
	.word	0c0e840d7h,05c28f5c3h		; _a[174] @ 11136
	.word	040eb1a61h,047ae147bh		; _a[175] @ 11200
	.word	0c0ee49a3h,0d70a3d71h		; _a[176] @ 11264
	.word	040f0ec58h,0a3d70a3dh		; _a[177] @ 11328
	.word	0c0f2e965h,09999999ah		; _a[178] @ 11392
	.word	040f52242h,0b851eb85h		; _a[179] @ 11456
	.word	0c0f79df7h,05c28f5c3h		; _a[180] @ 11520
	.word	040fa645eh,066666666h		; _a[181] @ 11584
	.word	0c0fd7e3eh,066666666h		; _a[182] @ 11648
	.word	041007ab2h,066666666h		; _a[183] @ 11712
	.word	0c1026a64h,0cccccccdh		; _a[184] @ 11776
	.word	041049455h,09999999ah		; _a[185] @ 11840
	.word	0c106ff5dh,09999999ah		; _a[186] @ 11904
	.word	04109b321h,09999999ah		; _a[187] @ 11968
	.word	0c10cb82dh,09999999ah		; _a[188] @ 12032
	.word	041100c07h,09999999ah		; _a[189] @ 12096
	.word	0c111eeb9h,033333333h		; _a[190] @ 12160
	.word	041140a22h,000000000h		; _a[191] @ 12224
	.word	0c11664ech,066666666h		; _a[192] @ 12288
	.word	04119068ah,0cccccccdh		; _a[193] @ 12352
	.word	0c11bf74fh,09999999ah		; _a[194] @ 12416
	.word	0411f4087h,09999999ah		; _a[195] @ 12480
	.word	0c121764bh,0cccccccdh		; _a[196] @ 12544
	.word	04123838eh,033333333h		; _a[197] @ 12608
	.word	0c125ce88h,09999999ah		; _a[198] @ 12672
	.word	041285e7bh,033333333h		; _a[199] @ 12736
	.word	0c12b3b80h,09999999ah		; _a[200] @ 12800
$C$IR_1:	.set	1608

	.global	_a
_a:	.usect	".far",1608,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\106082 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\106084 
;**	Parameter deleted: req_flags == 1;
;**	Parameter deleted: tol == 1e-09;
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
_allequal:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STW     .D2T1   A11,*SP--(8)      ; |63| 
||         MVKL    .S2     0xe826d695,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     _output,A11
||         MVKL    .S2     0x3e112e0b,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     _output,A11
||         MVKH    .S2     0xe826d695,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3e112e0b,B7
||         MVK     .S1     0x1,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     _isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {_isequal} {0}      ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     _fcn_pass,A12
||         MVKH    .S2     0x3e112e0b,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     _fcn_pass,A12
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3e112e0b,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MV      .L1     A10,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL3:    ; CALL OCCURS {_isequal} {0}      ; |69| 
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
||         MVKL    .S1     _all_pass,A3

   [ A0]   B       .S2     $C$L2             ; |72| 
||         MVKH    .S1     _all_pass,A3
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
           MVKL    .S1     _all_pass,A3

           MVKH    .S1     _all_pass,A3
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
;*   Local Frame Size  : 8 Args + 16 Auto + 56 Save = 80 byte                 *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |122| 
           STW     .D2T1   A10,*SP--(8)      ; |122| 
           STDW    .D2T2   B13:B12,*SP--     ; |122| 
           STDW    .D2T2   B11:B10,*SP--     ; |122| 
           STDW    .D2T1   A15:A14,*SP--     ; |122| 

           STDW    .D2T1   A13:A12,*SP--     ; |122| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(32)      ; |122| 
||         CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {_driver_init} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     _a,A10
||         MVKL    .S2     _output,B10

           MVKH    .S1     _a,A10
||         MVKH    .S2     _output,B10

           MV      .L1     A10,A13
||         CALL    .S1     _tan              ; |139| 
||         LDW     .D2T1   *B10,A12

           LDDW    .D1T1   *A13++,A5:A4      ; |139| 
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
           ADDKPC  .S2     $C$RL5,B3,0       ; |139| 
$C$RL5:    ; CALL OCCURS {_tan} {0}          ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A11,1,A0          ; |138| 
||         STDW    .D1T1   A5:A4,*A12++      ; |139| 
||         SUB     .S1     A11,1,A11         ; |138| 

   [ A0]   B       .S1     $C$L3             ; |138| 
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |139| 
|| [!A0]   ADD     .L2     4,B10,B11

   [ A0]   CALL    .S1     _tan              ; |139| 
   [!A0]   MV      .L1     A10,A11
   [!A0]   ZERO    .L2     B10
   [!A0]   MVK     .S1     0xc9,A3
   [!A0]   MV      .L1     A3,A12
           ; BRANCHCC OCCURS {$C$L3}         ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _tandp            ; |142| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |142| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |142| 
$C$RL6:    ; CALL OCCURS {_tandp} {0}        ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |142| 
||         SUB     .L1     A12,1,A0          ; |141| 
||         SUB     .S1     A12,1,A12         ; |141| 

   [ A0]   BNOP    .S2     $C$L4,2           ; |141| 
|| [!A0]   MVK     .S1     0xc9,A3
|| [!A0]   ADD     .L2     4,B11,B11
|| [!A0]   MV      .L1     A10,A11

   [!A0]   MV      .L1     A3,A12

           ADD     .L2     B10,B4,B4         ; |142| 
||         ADD     .S2     8,B10,B10         ; |141| 

   [ A0]   CALL    .S1     _tandp            ; |142| 
|| [!A0]   ZERO    .L2     B10
||         STDW    .D2T1   A5:A4,*B4         ; |142| 

           ; BRANCHCC OCCURS {$C$L4}         ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _tandp_c          ; |145| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |145| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |145| 
$C$RL7:    ; CALL OCCURS {_tandp_c} {0}      ; |145| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |145| 
||         SUB     .L1     A12,1,A0          ; |144| 
||         SUB     .S1     A12,1,A12         ; |144| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |144| 
|| [!A0]   ADD     .L1X    4,B11,A29

           ADD     .L2     B10,B4,B4         ; |145| 
||         ADD     .S2     8,B10,B10         ; |144| 

   [ A0]   CALL    .S1     _tandp_c          ; |145| 
||         STDW    .D2T1   A5:A4,*B4         ; |145| 

           ; BRANCHCC OCCURS {$C$L5}         ; |144| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           MV      .L1     A10,A28
||         MVK     .S2     0xc9,B1
||         ZERO    .L2     B31
||         LDW     .D1T1   *A29,A3

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 48
           LDDW    .D1T1   *A28++,A7:A6      ; |171| 
           MVKL    .S1     0x3fd45f30,A5
           MVKL    .S1     0x6dc9c889,A4
           MVKH    .S1     0x3fd45f30,A5
           MVKH    .S1     0x6dc9c889,A4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |171| 
           MVK     .L1     0xfffffffc,A8     ; |171| 
           MVKL    .S2     0x400921fb,B5
           ZERO    .L1     A31               ; |176| 
           DPINT   .L1     A5:A4,A4          ; |171| 
           MVKL    .S2     0x54442c46,B4
           MVKH    .S2     0x400921fb,B5
           MVKH    .S2     0x54442c46,B4
           INTDP   .L1     A4,A5:A4          ; |171| 
           MVKL    .S2     0x3ff921fb,B7
           MVKL    .S1     0x3d3a3fff,A9
           MVKL    .S2     0x54442b65,B6
           MVKH    .S1     0x3d3a3fff,A9
           MVKH    .S2     0x3ff921fb,B7
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |171| 
           MVKH    .S2     0x54442b65,B6
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |171| 
           SET     .S1     A31,31,31,A8      ; |176| 
           NOP             1
           FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |171| 
           MVKL    .S2     0x400921fb,B5
           MVKL    .S2     0x54442d18,B4
           FSUBDP  .L1     A7:A6,A5:A4,A7:A6 ; |171| 
           MVKH    .S2     0x400921fb,B5
           MVKH    .S2     0x54442d18,B4
           MVKL    .S1     0x54442d18,A4
           CMPGTDP .S2X    A7:A6,B7:B6,B0    ; |171| 
           MVKL    .S1     0x3fe921fb,A5
   [ B0]   FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |171| 
           MVKH    .S1     0x54442d18,A4
           ZERO    .L2     B5:B4             ; |174| 
           MVKH    .S1     0x3fe921fb,A5
           CMPLTDP .S2X    A7:A6,B5:B4,B0    ; |174| 
           NOP             1
   [ B0]   XOR     .L1     A7,A8,A7          ; |176| 
           CMPGTDP .S1     A7:A6,A5:A4,A0    ; |180| 

   [!B0]   ZERO    .L1     A5
|| [ B0]   ZERO    .D1     A5

   [ A0]   B       .S1     $C$L7             ; |180| 
|| [ A0]   MV      .L1X    B7,A9
|| [ A0]   MVKL    .S2     0x3b981c8c,B4
|| [!B0]   ZERO    .D1     A4                ; |160| 

   [ A0]   MV      .L1X    B6,A8
|| [ A0]   MVKL    .S2     0x3d3b3226,B5
|| [!B0]   SET     .S1     A5,0x14,0x1d,A5
|| [ B0]   ZERO    .D1     A4                ; |175| 

   [ A0]   FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |183| 
   [ B0]   MVKH    .S1     0xbff00000,A5
   [ A0]   MVKH    .S2     0x3b981c8c,B4
   [ A0]   MVKH    .S2     0x3d3b3226,B5
           ; BRANCHCC OCCURS {$C$L7}         ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 51

           FMPYDP  .M1     A7:A6,A7:A6,A17:A16 ; |129| 
||         MVKL    .S2     0x3f25bf32,B5
||         MVKL    .S1     0x452b75eb,A24

           MVKL    .S2     0x422069f7,B4
||         MVKL    .S1     0x3f57da36,A25

           MVKL    .S2     0x3f2c5e5f,B9
||         MVKH    .S1     0x452b75eb,A24

           MVKL    .S2     0x63a94b17,B8
||         MVKH    .S1     0x3f57da36,A25

           FMPYDP  .M1     A17:A16,A17:A16,A19:A18 ; |129| 
||         MVKH    .S2     0x3f25bf32,B5
||         MVKL    .S1     0x3f9664f4,A9

           MVKH    .S2     0x422069f7,B4
||         MVKL    .S1     0x882c10f9,A8

           MVKH    .S2     0x3f2c5e5f,B9
||         MVKH    .S1     0x3f9664f4,A9

           MVKH    .S2     0x63a94b17,B8
||         MVKH    .S1     0x882c10f9,A8

           FMPYDP  .M1     A19:A18,A17:A16,A23:A22 ; |129| 
||         MVKL    .S2     0xe157ddd,B6
||         FMPYDP  .M2X    B9:B8,A17:A16,B9:B8 ; |129| 

           FMPYDP  .M1     A19:A18,A19:A18,A21:A20 ; |129| 
||         MVKL    .S2     0x3f6d6d3d,B7

           MVKL    .S2     0x3f435582,B17
||         FMPYDP  .M1X    B5:B4,A19:A18,A31:A30 ; |129| 

           MVKL    .S2     0x48036744,B16

           MVKL    .S2     0x3f8226e3,B23
||         FMPYDP  .M1     A25:A24,A23:A22,A25:A24 ; |129| 

           MVKL    .S2     0x55e6c23f,B22
||         FMPYDP  .M1     A9:A8,A21:A20,A9:A8 ; |129| 

           MVKH    .S2     0xe157ddd,B6
||         FADDDP  .L1X    A31:A30,B9:B8,A31:A30 ; |129| 

           MVKH    .S2     0x3f6d6d3d,B7

           MVKH    .S2     0x3f435582,B17
||         FMPYDP  .M2X    B7:B6,A19:A18,B7:B6 ; |129| 

           MVKH    .S2     0x48036744,B16
           MVKH    .S2     0x3f8226e3,B23

           MVKH    .S2     0x55e6c23f,B22
||         FMPYDP  .M1X    B17:B16,A21:A20,A27:A26 ; |129| 

           FMPYDP  .M2X    B23:B22,A17:A16,B5:B4 ; |129| 
||         MVKL    .S2     0x3fd55555,B21

           MVKL    .S2     0x5555554f,B20
           MVKH    .S2     0x3fd55555,B21
           MVKH    .S2     0x5555554f,B20

           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |129| 
||         FMPYDP  .M2X    B21:B20,A17:A16,B7:B6 ; |129| 
||         FADDDP  .L1     A27:A26,A25:A24,A17:A16 ; |129| 
||         MVKL    .S2     0x3faba1ba,B17

           MVKL    .S2     0x1ba1ba20,B16
           MVKL    .S2     0x11111105,B18
           MVKL    .S2     0x3fc11111,B19
           MVKH    .S2     0x3faba1ba,B17
           MVKH    .S2     0x1ba1ba20,B16

           MVKH    .S2     0x11111105,B18
||         FMPYDP  .M2X    B17:B16,A23:A22,B17:B16 ; |129| 

           MVKH    .S2     0x3fc11111,B19

           FMPYDP  .M2X    B19:B18,A19:A18,B9:B8 ; |129| 
||         FMPYDP  .M1     A21:A20,A31:A30,A19:A18 ; |129| 

           FADDDP  .L1X    A17:A16,B5:B4,A17:A16 ; |129| 
           NOP             2

           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |129| 
||         FADDDP  .L2     B7:B6,B9:B8,B5:B4 ; |129| 

           FADDDP  .L1X    B17:B16,A9:A8,A9:A8 ; |129| 
           NOP             1
           FMPYDP  .M1     A21:A20,A17:A16,A17:A16 ; |129| 
           FADDDP  .L1X    B5:B4,A9:A8,A9:A8 ; |129| 
           NOP             2
           FADDDP  .L1     A17:A16,A9:A8,A9:A8 ; |129| 
           NOP             1
           B       .S1     $C$L8             ; |129| 
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |129| 
           NOP             3
           FADDDP  .L1     A7:A6,A9:A8,A7:A6 ; |129| 
           ; BRANCH OCCURS {$C$L8}           ; |129| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 90

           FADDDP  .L2X    B5:B4,A7:A6,B9:B8 ; |183| 
||         MVKL    .S1     0x48036744,A26
||         MVKL    .S2     0x3f57da36,B23

           MVKL    .S1     0x3f435582,A27
||         MVKL    .S2     0x452b75eb,B22

           MVKH    .S1     0x48036744,A26
||         MVKH    .S2     0x3f57da36,B23

           FMPYDP  .M2     B9:B8,B9:B8,B5:B4 ; |183| 
||         MVKH    .S1     0x3f435582,A27
||         MVKH    .S2     0x452b75eb,B22

           MVKL    .S1     0x63a94b17,A24
           MVKL    .S1     0x3f2c5e5f,A25
           MVKL    .S1     0x422069f7,A8

           FMPYDP  .M2     B5:B4,B5:B4,B7:B6 ; |183| 
||         MVKL    .S1     0x3f25bf32,A9

           MVKH    .S1     0x63a94b17,A24
           MVKH    .S1     0x3f2c5e5f,A25

           MVKH    .S1     0x422069f7,A8
||         FMPYDP  .M1X    A25:A24,B5:B4,A25:A24 ; |183| 

           FMPYDP  .M2     B7:B6,B5:B4,B19:B18 ; |183| 
||         MVKH    .S1     0x3f25bf32,A9

           FMPYDP  .M2     B7:B6,B7:B6,B17:B16 ; |183| 
||         MVKL    .S1     0x3f8226e3,A21

           MVKL    .S1     0x55e6c23f,A20
           MVKL    .S1     0x3f6d6d3d,A23

           MVKL    .S1     0xe157ddd,A22
||         FMPYDP  .M2     B23:B22,B19:B18,B23:B22 ; |183| 

           FMPYDP  .M2X    A27:A26,B17:B16,B21:B20 ; |183| 
||         FMPYDP  .M1X    A9:A8,B7:B6,A27:A26 ; |183| 
||         MVKH    .S1     0x3f8226e3,A21

           MVKH    .S1     0x55e6c23f,A20

           MVKH    .S1     0x3f6d6d3d,A23
||         FMPYDP  .M1X    A21:A20,B5:B4,A21:A20 ; |183| 

           MVKH    .S1     0xe157ddd,A22

           FMPYDP  .M1X    A23:A22,B7:B6,A23:A22 ; |183| 
||         FADDDP  .L2     B21:B20,B23:B22,B21:B20 ; |183| 
||         FADDDP  .L1     A27:A26,A25:A24,A25:A24 ; |183| 
||         MVKL    .S1     0x11111105,A16

           MVKL    .S1     0x3fc11111,A17
           MVKH    .S1     0x11111105,A16
           MVKH    .S1     0x3fc11111,A17

           FADDDP  .L1     A23:A22,A21:A20,A21:A20 ; |183| 
||         MVKL    .S1     0x3f9664f4,A7

           MVKL    .S1     0x882c10f9,A6
||         FMPYDP  .M2X    A17:A16,B7:B6,B7:B6 ; |183| 
||         FMPYDP  .M1X    B17:B16,A25:A24,A17:A16 ; |183| 

           MVKL    .S1     0x1ba1ba20,A8
           MVKL    .S1     0x3faba1ba,A9
           MVKH    .S1     0x3f9664f4,A7
           MVKH    .S1     0x882c10f9,A6
           MVKL    .S1     0x5555554f,A18

           MVKL    .S1     0x3fd55555,A19
||         FADDDP  .L1X    B21:B20,A21:A20,A7:A6 ; |183| 
||         FMPYDP  .M2X    A7:A6,B17:B16,B21:B20 ; |183| 

           MVKH    .S1     0x1ba1ba20,A8
           MVKH    .S1     0x3faba1ba,A9
           MVKH    .S1     0x5555554f,A18
           MVKH    .S1     0x3fd55555,A19
           FMPYDP  .M2X    A9:A8,B19:B18,B19:B18 ; |183| 
           FMPYDP  .M2X    A19:A18,B5:B4,B5:B4 ; |183| 
           FADDDP  .L1     A17:A16,A7:A6,A7:A6 ; |183| 
           ZERO    .L1     A31
           NOP             1

           FADDDP  .L2     B5:B4,B7:B6,B7:B6 ; |183| 
||         FADDDP  .S2     B19:B18,B21:B20,B5:B4 ; |183| 

           FMPYDP  .M2X    B17:B16,A7:A6,B17:B16 ; |183| 
           ZERO    .L1     A6                ; |67| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |183| 
           SET     .S1     A31,0x1e,0x1e,A7
           NOP             1
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |183| 
           ZERO    .L2     B16               ; |67| 
           SET     .S2     B31,0x1e,0x1e,B17
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |183| 
           NOP             3
           FADDDP  .L2     B9:B8,B5:B4,B9:B8 ; |183| 
           NOP             2
           RCPDP   .S2     B9:B8,B5:B4       ; |67| 
           NOP             1
           FMPYDP  .M2     B9:B8,B5:B4,B7:B6 ; |67| 
           NOP             3
           FSUBDP  .L2     B17:B16,B7:B6,B7:B6 ; |67| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |67| 
           NOP             3
           FMPYDP  .M2     B9:B8,B5:B4,B7:B6 ; |67| 
           NOP             3
           FSUBDP  .L2     B17:B16,B7:B6,B7:B6 ; |67| 
           ZERO    .L2     B16
           MVKL    .S2     0x47efffff,B17
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |67| 
           MVKH    .S2     0x47efffff,B17
           MVKH    .S2     0xe0000000,B16
           NOP             1
           FMPYDP  .M2     B9:B8,B5:B4,B7:B6 ; |67| 
           ABSDP   .S2     B9:B8,B9:B8       ; |67| 
           NOP             3
           FSUBDP  .L1X    A7:A6,B7:B6,A7:A6 ; |67| 
           CMPGTDP .S2     B9:B8,B17:B16,B0  ; |67| 
           NOP             1

   [!B0]   FMPYDP  .M1X    B5:B4,A7:A6,A7:A6 ; |67| 
|| [ B0]   ZERO    .L1     A7:A6             ; |67| 

;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 8
           SUB     .L2     B1,1,B1           ; |147| 
   [!B1]   ADD     .S1     4,A29,A12
   [ B1]   B       .S1     $C$L6             ; |147| 
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |148| 
           NOP             3

   [!B1]   CALL    .S1     _tandp_v          ; |150| 
||         STDW    .D1T1   A5:A4,*A3++       ; |148| 

           ; BRANCHCC OCCURS {$C$L6}         ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A12,B4           ; |150| 
           MV      .L1     A10,A4            ; |150| 
           MVK     .S1     0xc9,A6           ; |150| 
           ADDKPC  .S2     $C$RL8,B3,1       ; |150| 
$C$RL8:    ; CALL OCCURS {_tandp_v} {0}      ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     _allequal,B3
||         MVK     .S1     0xc9,A4           ; |155| 

$C$RL9:    ; CALL OCCURS {_allequal} {0}     ; |155| 

           CALLP   .S2     _print_test_results,B3
||         MVK     .L1     0x1,A4            ; |156| 

$C$RL10:   ; CALL OCCURS {_print_test_results} {0}  ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           MVKL    .S1     _a_sc,A13
||         ZERO    .L2     B5

           MVKH    .S1     _a_sc,A13
||         MVKH    .S2     0x80000000,B5
||         MVK     .L2     0xffffffff,B7     ; |170| 
||         ZERO    .D2     B4                ; |168| 

           STDW    .D1T2   B5:B4,*+A13(8)    ; |164| 
||         MV      .L2     B7,B6             ; |170| 
||         ZERO    .L1     A7

           STDW    .D1T2   B7:B6,*+A13(56)   ; |170| 
||         SET     .S1     A7,0x14,0x1d,A7
||         ZERO    .L2     B17
||         ZERO    .L1     A6                ; |168| 

           STDW    .D1T1   A7:A6,*+A13(32)   ; |167| 
||         MVKH    .S2     0xfff00000,B17
||         ZERO    .L1     A9
||         ZERO    .L2     B16               ; |168| 

           STDW    .D1T2   B17:B16,*+A13(24) ; |166| 
||         SET     .S1     A9,0x14,0x1e,A9
||         ZERO    .L2     B9
||         ZERO    .L1     A8                ; |168| 

           STDW    .D1T1   A9:A8,*+A13(16)   ; |165| 
||         MVKH    .S2     0xbff00000,B9
||         ZERO    .L2     B8                ; |168| 

           MVK     .L2     0x8,B4
||         STDW    .D1T2   B9:B8,*+A13(40)   ; |168| 
||         ZERO    .L1     A5:A4             ; |163| 

           ADD     .L2     -1,B5,B7
||         STDW    .D1T1   A5:A4,*A13        ; |163| 
||         ZERO    .L1     A10               ; |168| 

           STDW    .D1T2   B7:B6,*+A13(48)   ; |169| 
||         MV      .L1X    B4,A14            ; |164| 
||         SUB     .S1     A13,8,A11

;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _tan              ; |173| 
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
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *++A11,A5:A4      ; |173| 
           ADDKPC  .S2     $C$RL11,B3,3      ; |173| 
$C$RL11:   ; CALL OCCURS {_tan} {0}          ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 29
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           MV      .L1     A3,A15            ; |173| 
           LDW     .D1T1   *A15,A3           ; |173| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |173| 
           NOP             3
           ADD     .L1     A10,A3,A3         ; |173| 
           STDW    .D1T2   B5:B4,*A3         ; |173| 

           CALLP   .S2     _tandp,B3
||         LDDW    .D1T1   *A11,A5:A4        ; |174| 

$C$RL12:   ; CALL OCCURS {_tandp} {0}        ; |174| 
           LDW     .D1T1   *+A15(4),A3       ; |174| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |174| 
           NOP             3
           ADD     .L1     A10,A3,A3         ; |174| 
           STDW    .D1T2   B5:B4,*A3         ; |174| 

           CALLP   .S2     _tandp_c,B3
||         LDDW    .D1T1   *A11,A5:A4        ; |175| 

$C$RL13:   ; CALL OCCURS {_tandp_c} {0}      ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 55
           LDW     .D1T1   *+A15(8),A3       ; |175| 
           MVK     .L1     0xfffffffc,A8     ; |168| 
           MVKL    .S1     0x3d3a3fff,A9
           MVKL    .S2     0x400921fb,B5
           ZERO    .L1     A31               ; |176| 
           ADD     .L1     A10,A3,A3         ; |175| 
           STDW    .D1T1   A5:A4,*A3         ; |175| 
           LDDW    .D1T1   *A11,A7:A6        ; |168| 
           MVKL    .S1     0x3fd45f30,A5
           MVKL    .S1     0x6dc9c889,A4
           MVKH    .S1     0x3fd45f30,A5
           MVKH    .S1     0x6dc9c889,A4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |168| 
           MVKH    .S1     0x3d3a3fff,A9
           MVKL    .S2     0x54442c46,B4
           MVKH    .S2     0x400921fb,B5
           DPINT   .L1     A5:A4,A3          ; |168| 
           MVKH    .S2     0x54442c46,B4
           MVKL    .S2     0x3ff921fb,B7
           MVKL    .S2     0x54442b65,B6
           INTDP   .L1     A3,A5:A4          ; |168| 
           MVKH    .S2     0x3ff921fb,B7
           MVKH    .S2     0x54442b65,B6
           SET     .S1     A31,31,31,A3      ; |176| 
           NOP             2
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |168| 
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |168| 
           NOP             3
           FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |168| 
           MVKL    .S2     0x400921fb,B5
           MVKL    .S2     0x54442d18,B4
           FSUBDP  .L1     A7:A6,A5:A4,A17:A16 ; |168| 
           MVKH    .S2     0x400921fb,B5
           MVKH    .S2     0x54442d18,B4
           MVKL    .S1     0x54442d18,A4
           CMPGTDP .S2X    A17:A16,B7:B6,B0  ; |170| 
           MVKL    .S1     0x3fe921fb,A5
   [ B0]   FSUBDP  .L1X    A17:A16,B5:B4,A17:A16 ; |171| 
           MVKH    .S1     0x54442d18,A4
           ZERO    .L2     B5:B4             ; |174| 
           MVKH    .S1     0x3fe921fb,A5
           CMPLTDP .S2X    A17:A16,B5:B4,B0  ; |174| 
           NOP             1

   [ B0]   XOR     .L1     A17,A3,A17        ; |176| 
|| [ B0]   ZERO    .S1     A7
|| [!B0]   ZERO    .D1     A7

           CMPGTDP .S1     A17:A16,A5:A4,A0  ; |180| 
|| [ B0]   ZERO    .L1     A6                ; |175| 
|| [!B0]   ZERO    .D1     A6                ; |160| 

           MV      .L1X    B7,A5

   [!A0]   B       .S1     $C$L10            ; |180| 
||         MV      .L1X    B6,A4
|| [ A0]   MVKL    .S2     0x3d3b3226,B5

           FSUBDP  .L1     A5:A4,A17:A16,A5:A4 ; |181| 
|| [ A0]   MVKL    .S2     0x3b981c8c,B4
|| [!B0]   SET     .S1     A7,0x14,0x1d,A7

   [ B0]   MVKH    .S1     0xbff00000,A7
   [ A0]   MVKH    .S2     0x3d3b3226,B5
   [ A0]   MVKH    .S2     0x3b981c8c,B4
           FADDDP  .L2X    B5:B4,A5:A4,B17:B16 ; |181| 
           ; BRANCHCC OCCURS {$C$L10}        ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 95

           MVKL    .S1     0x3f435582,A25
||         MVKL    .S2     0x452b75eb,B20

           MVKL    .S1     0x48036744,A24
||         MVKL    .S2     0x3f57da36,B21

           FMPYDP  .M2     B17:B16,B17:B16,B7:B6 ; |183| 
||         MVKH    .S1     0x3f435582,A25
||         MVKH    .S2     0x452b75eb,B20

           MVKH    .S1     0x48036744,A24
||         MVKH    .S2     0x3f57da36,B21

           MVKL    .S1     0x3f2c5e5f,A9
           MVKL    .S1     0x63a94b17,A8

           FMPYDP  .M2     B7:B6,B7:B6,B9:B8 ; |183| 
||         MVKL    .S1     0x422069f7,A16

           MVKL    .S1     0x3f25bf32,A17
           MVKH    .S1     0x3f2c5e5f,A9
           MVKH    .S1     0x63a94b17,A8

           FMPYDP  .M2     B9:B8,B9:B8,B5:B4 ; |183| 
||         MVKH    .S1     0x422069f7,A16
||         FMPYDP  .M1X    A9:A8,B7:B6,A27:A26 ; |183| 

           FMPYDP  .M2     B9:B8,B7:B6,B19:B18 ; |183| 
||         MVKH    .S1     0x3f25bf32,A17

           MVKL    .S1     0xe157ddd,A4
           MVKL    .S1     0x3f6d6d3d,A5

           MVKL    .S1     0x3f8226e3,A23
||         FMPYDP  .M2X    A25:A24,B5:B4,B23:B22 ; |183| 
||         FMPYDP  .M1X    A17:A16,B9:B8,A25:A24 ; |183| 

           MVKL    .S1     0x55e6c23f,A22
||         FMPYDP  .M2     B21:B20,B19:B18,B21:B20 ; |183| 

           MVKH    .S1     0xe157ddd,A4
           MVKH    .S1     0x3f6d6d3d,A5

           MVKH    .S1     0x3f8226e3,A23
||         FMPYDP  .M1X    A5:A4,B9:B8,A5:A4 ; |183| 
||         FADDDP  .L1     A25:A24,A27:A26,A25:A24 ; |183| 

           MVKH    .S1     0x55e6c23f,A22
||         FADDDP  .L2     B23:B22,B21:B20,B21:B20 ; |183| 

           FMPYDP  .M1X    A23:A22,B7:B6,A23:A22 ; |183| 
||         MVKL    .S1     0x3fc11111,A19

           MVKL    .S1     0x11111105,A18
           MVKH    .S1     0x3fc11111,A19
           MVKH    .S1     0x11111105,A18

           FADDDP  .L1     A5:A4,A23:A22,A5:A4 ; |183| 
||         MVKL    .S1     0x1ba1ba20,A16

           MVKL    .S1     0x3faba1ba,A17
||         FMPYDP  .M2X    A19:A18,B9:B8,B23:B22 ; |183| 
||         FMPYDP  .M1X    B5:B4,A25:A24,A19:A18 ; |183| 

           MVKL    .S1     0x3f9664f4,A9

           MVKL    .S1     0x882c10f9,A8
||         FADDDP  .L1X    B21:B20,A5:A4,A5:A4 ; |183| 

           MVKL    .S1     0x3fd55555,A21
           MVKL    .S1     0x5555554f,A20
           MVKH    .S1     0x1ba1ba20,A16
           MVKH    .S1     0x3faba1ba,A17
           MVKH    .S1     0x3f9664f4,A9

           MVKH    .S1     0x882c10f9,A8
||         FMPYDP  .M2X    A17:A16,B19:B18,B19:B18 ; |183| 

           MVKH    .S1     0x3fd55555,A21
           MVKH    .S1     0x5555554f,A20
           FMPYDP  .M2X    A9:A8,B5:B4,B9:B8 ; |183| 
           FMPYDP  .M2X    A21:A20,B7:B6,B7:B6 ; |183| 
           FADDDP  .L1     A19:A18,A5:A4,A5:A4 ; |183| 
           ZERO    .L2     B31
           ADDAW   .D1     A15,3,A3

           FADDDP  .L2     B19:B18,B9:B8,B7:B6 ; |183| 
||         FADDDP  .S2     B7:B6,B23:B22,B9:B8 ; |183| 

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |183| 
           LDW     .D1T1   *A3,A3            ; |176| 
           FADDDP  .L2     B9:B8,B7:B6,B7:B6 ; |183| 
           SUB     .L1     A14,1,A0          ; |172| 
           ZERO    .S2     B30
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |183| 
           SUB     .L1     A14,1,A14         ; |172| 
           ADD     .L1     A10,A3,A3         ; |176| 
           FMPYDP  .M2     B17:B16,B5:B4,B5:B4 ; |183| 
           ZERO    .L2     B18               ; |67| 
           SET     .S2     B30,0x1e,0x1e,B19
           ADD     .L1     8,A10,A10         ; |172| 
           FADDDP  .L2     B17:B16,B5:B4,B7:B6 ; |183| 
           ZERO    .L2     B16               ; |67| 
           SET     .S2     B31,0x1e,0x1e,B17
           RCPDP   .S2     B7:B6,B5:B4       ; |67| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |67| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |67| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |67| 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |67| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |67| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |67| 
           MVKL    .S2     0x47efffff,B9
           ZERO    .L2     B8
           MVKH    .S2     0x47efffff,B9
           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |67| 
           ABSDP   .S2     B7:B6,B7:B6       ; |69| 
           NOP             2
           FSUBDP  .L2     B19:B18,B17:B16,B17:B16 ; |67| 
           MVKH    .S2     0xe0000000,B8
           CMPGTDP .S2     B7:B6,B9:B8,B0    ; |69| 
           FMPYDP  .M2     B5:B4,B17:B16,B5:B4 ; |67| 
           BNOP    .S1     $C$L11,2          ; |73| 
   [ B0]   ZERO    .L2     B5:B4             ; |70| 
           NOP             1

   [ A0]   B       .S1     $C$L9             ; |172| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |73| 

           ; BRANCH OCCURS {$C$L11}          ; |73| 
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 53

           FMPYDP  .M1     A17:A16,A17:A16,A5:A4 ; |129| 
||         MVKL    .S2     0x3f25bf32,B23
||         MVKL    .S1     0x452b75eb,A24

           MVKL    .S2     0x422069f7,B22
||         MVKL    .S1     0x3f57da36,A25

           MVKL    .S2     0x3f2c5e5f,B9
||         MVKH    .S1     0x452b75eb,A24

           MVKL    .S2     0x63a94b17,B8
||         MVKH    .S1     0x3f57da36,A25

           FMPYDP  .M1     A5:A4,A5:A4,A9:A8 ; |129| 
||         MVKH    .S2     0x3f25bf32,B23
||         MVKL    .S1     0x3f9664f4,A23

           MVKH    .S2     0x422069f7,B22
||         MVKL    .S1     0x882c10f9,A22

           MVKH    .S2     0x3f2c5e5f,B9
||         MVKH    .S1     0x3f9664f4,A23

           MVKH    .S2     0x63a94b17,B8
||         MVKH    .S1     0x882c10f9,A22

           FMPYDP  .M1     A9:A8,A5:A4,A21:A20 ; |129| 
||         MVKL    .S2     0x3f8226e3,B5
||         FMPYDP  .M2X    B9:B8,A5:A4,B9:B8 ; |129| 

           FMPYDP  .M1     A9:A8,A9:A8,A19:A18 ; |129| 
||         MVKL    .S2     0x55e6c23f,B4

           MVKL    .S2     0x3f6d6d3d,B7
||         FMPYDP  .M1X    B23:B22,A9:A8,A29:A28 ; |129| 

           MVKL    .S2     0xe157ddd,B6

           MVKL    .S2     0x3f435582,B19
||         FMPYDP  .M1     A25:A24,A21:A20,A25:A24 ; |129| 

           MVKL    .S2     0x48036744,B18

           MVKH    .S2     0x3f8226e3,B5
||         FADDDP  .L1X    A29:A28,B9:B8,A29:A28 ; |129| 

           MVKH    .S2     0x55e6c23f,B4

           MVKH    .S2     0x3f6d6d3d,B7
||         FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |129| 

           MVKH    .S2     0xe157ddd,B6

           MVKH    .S2     0x3f435582,B19
||         FMPYDP  .M2X    B7:B6,A9:A8,B7:B6 ; |129| 

           MVKH    .S2     0x48036744,B18
           MVKL    .S2     0x3fd55555,B17

           FMPYDP  .M1X    B19:B18,A19:A18,A27:A26 ; |129| 
||         MVKL    .S2     0x5555554f,B16

           FADDDP  .L2     B7:B6,B5:B4,B7:B6 ; |129| 
||         MVKH    .S2     0x3fd55555,B17

           MVKH    .S2     0x5555554f,B16

           FMPYDP  .M2X    B17:B16,A5:A4,B9:B8 ; |129| 
||         MVKL    .S2     0x3faba1ba,B19

           FADDDP  .L1     A27:A26,A25:A24,A5:A4 ; |129| 
||         MVKL    .S2     0x1ba1ba20,B18

           MVKL    .S2     0x11111105,B20
           MVKL    .S2     0x3fc11111,B21
           MVKH    .S2     0x3faba1ba,B19
           MVKH    .S2     0x1ba1ba20,B18

           MVKH    .S2     0x11111105,B20
||         FMPYDP  .M2X    B19:B18,A21:A20,B5:B4 ; |129| 
||         FADDDP  .L1X    A5:A4,B7:B6,A21:A20 ; |129| 

           MVKH    .S2     0x3fc11111,B21

           FMPYDP  .M2X    B21:B20,A9:A8,B17:B16 ; |129| 
||         FMPYDP  .M1     A19:A18,A29:A28,A9:A8 ; |129| 

           FMPYDP  .M1     A23:A22,A19:A18,A5:A4 ; |129| 
           ADDAW   .D1     A15,3,A3
           LDW     .D1T1   *A3,A3            ; |176| 

           FADDDP  .L1     A9:A8,A21:A20,A9:A8 ; |129| 
||         FADDDP  .L2     B9:B8,B17:B16,B7:B6 ; |129| 

           FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |129| 
           SUB     .S1     A14,1,A0          ; |172| 
           FMPYDP  .M1     A19:A18,A9:A8,A9:A8 ; |129| 
           FADDDP  .L1X    B7:B6,A5:A4,A5:A4 ; |129| 
           SUB     .L1     A14,1,A14         ; |172| 
           ADD     .S1     A10,A3,A3         ; |176| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |129| 
           ADD     .L1     8,A10,A10         ; |172| 
           NOP             1
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |129| 
           NOP             3
           FADDDP  .L1     A17:A16,A5:A4,A5:A4 ; |129| 
           NOP             1
   [ A0]   B       .S1     $C$L9             ; |172| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 5
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |176| 
           NOP             3

   [ A0]   CALL    .S1     _tan              ; |173| 
||         STDW    .D1T1   A5:A4,*A3         ; |176| 

           ; BRANCHCC OCCURS {$C$L9}         ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           MV      .L1     A12,A3            ; |178| 
||         CALL    .S1     _tandp_v          ; |178| 

           LDW     .D1T2   *A3,B4            ; |178| 
           ADDKPC  .S2     $C$RL14,B3,2      ; |178| 

           MV      .L1     A13,A4
||         STW     .D2T1   A12,*+SP(24)      ; |178| 
||         MVK     .S1     0x8,A6            ; |178| 

$C$RL14:   ; CALL OCCURS {_tandp_v} {0}      ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     _allequal,B3
||         MVK     .L1     0x8,A4            ; |181| 

$C$RL15:   ; CALL OCCURS {_allequal} {0}     ; |181| 

           CALLP   .S2     _print_test_results,B3
||         MVK     .L1     0x3,A4            ; |182| 

$C$RL16:   ; CALL OCCURS {_print_test_results} {0}  ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

           MVKL    .S1     _a_ext,A11
||         ZERO    .L2     B5

           MVKH    .S1     _a_ext,A11
||         SET     .S2     B5,0x14,0x14,B5
||         ZERO    .L2     B4                ; |185| 

           STDW    .D1T2   B5:B4,*A11        ; |185| 
||         MVK     .S2     0x6f4,B4

           MV      .L1     A11,A10           ; |185| 

           ZERO    .L2     B10
||         CALL    .S1     _tan              ; |187| 
||         MV      .L1X    B4,A13            ; |185| 

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
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10,A5:A4        ; |187| 
           ADDKPC  .S2     $C$RL17,B3,3      ; |187| 
$C$RL17:   ; CALL OCCURS {_tan} {0}          ; |187| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 28
           MV      .L1     A15,A3            ; |187| 
           LDW     .D1T1   *A3,A3            ; |187| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |187| 
           NOP             3
           ADD     .L2X    B10,A3,B6         ; |187| 
           STDW    .D2T2   B5:B4,*B6         ; |187| 

           CALLP   .S2     _tandp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |188| 

$C$RL18:   ; CALL OCCURS {_tandp} {0}        ; |188| 
           MV      .L1     A15,A3            ; |188| 
           LDW     .D1T1   *+A3(4),A3        ; |188| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |188| 
           NOP             3
           ADD     .L2X    B10,A3,B6         ; |188| 
           STDW    .D2T2   B5:B4,*B6         ; |188| 

           CALLP   .S2     _tandp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |189| 

$C$RL19:   ; CALL OCCURS {_tandp_c} {0}      ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 56
           MV      .L1     A15,A3            ; |189| 
           LDW     .D1T1   *+A3(8),A3        ; |189| 
           MVK     .L1     0xfffffffc,A8     ; |168| 
           MVKL    .S1     0x3d3a3fff,A9
           MVKL    .S2     0x400921fb,B5
           ZERO    .L1     A31               ; |176| 
           ADD     .L2X    B10,A3,B4         ; |189| 
           STDW    .D2T1   A5:A4,*B4         ; |189| 
           LDDW    .D1T1   *A10,A7:A6        ; |168| 
           MVKL    .S1     0x3fd45f30,A5
           MVKL    .S1     0x6dc9c889,A4
           MVKH    .S1     0x3fd45f30,A5
           MVKH    .S1     0x6dc9c889,A4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |168| 
           MVKH    .S1     0x3d3a3fff,A9
           MVKH    .S2     0x400921fb,B5
           MVKL    .S2     0x54442b65,B6
           DPINT   .L1     A5:A4,A3          ; |168| 
           MVKL    .S2     0x3ff921fb,B7
           MVKH    .S2     0x54442b65,B6
           MVKL    .S2     0x54442c46,B4
           INTDP   .L1     A3,A5:A4          ; |168| 
           MVKH    .S2     0x54442c46,B4
           MVKH    .S2     0x3ff921fb,B7
           SET     .S1     A31,31,31,A3      ; |176| 
           NOP             2
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |168| 
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |168| 
           MV      .L1X    B7,A9
           MV      .L1X    B6,A8
           NOP             1
           FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |168| 
           MVKL    .S2     0x400921fb,B5
           MVKL    .S2     0x54442d18,B4
           FSUBDP  .L1     A7:A6,A5:A4,A7:A6 ; |168| 
           MVKH    .S2     0x400921fb,B5
           MVKH    .S2     0x54442d18,B4
           MVKL    .S1     0x54442d18,A4
           CMPGTDP .S2X    A7:A6,B7:B6,B0    ; |170| 
           MVKL    .S1     0x3fe921fb,A5
   [ B0]   FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |171| 
           MVKH    .S1     0x54442d18,A4
           ZERO    .L2     B5:B4             ; |174| 
           MVKH    .S1     0x3fe921fb,A5
           CMPLTDP .S2X    A7:A6,B5:B4,B0    ; |174| 
           NOP             1

   [ B0]   XOR     .L1     A7,A3,A7          ; |176| 
|| [ B0]   ZERO    .L2     B25
|| [!B0]   ZERO    .S2     B25
|| [ B0]   ZERO    .D2     B24               ; |175| 

   [!B0]   ZERO    .L2     B24               ; |160| 
||         CMPGTDP .S1     A7:A6,A5:A4,A0    ; |180| 

   [!B0]   SET     .S2     B25,0x14,0x1d,B25

   [!A0]   B       .S1     $C$L13            ; |180| 
|| [!A0]   FMPYDP  .M1     A7:A6,A7:A6,A9:A8 ; |129| 
|| [ A0]   FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |181| 
|| [ A0]   MVKL    .S2     0x3d3b3226,B5

   [ A0]   MVKL    .S2     0x3b981c8c,B4
   [ A0]   MVKH    .S2     0x3d3b3226,B5
   [ A0]   MVKH    .S2     0x3b981c8c,B4

           FADDDP  .L2X    B5:B4,A7:A6,B9:B8 ; |181| 
||         FMPYDP  .M1     A9:A8,A9:A8,A17:A16 ; |129| 

   [ B0]   MVKH    .S2     0xbff00000,B25
           ; BRANCHCC OCCURS {$C$L13}        ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 93

           MVKL    .S1     0x3f435582,A23
||         MVKL    .S2     0x452b75eb,B20

           FMPYDP  .M2     B9:B8,B9:B8,B5:B4 ; |183| 
||         MVKL    .S1     0x48036744,A22
||         MVKL    .S2     0x3f57da36,B21

           MVKH    .S1     0x3f435582,A23
||         MVKH    .S2     0x452b75eb,B20

           MVKH    .S1     0x48036744,A22
||         MVKH    .S2     0x3f57da36,B21

           MVKL    .S1     0x422069f7,A6

           FMPYDP  .M2     B5:B4,B5:B4,B7:B6 ; |183| 
||         MVKL    .S1     0x3f25bf32,A7

           MVKL    .S1     0x3f2c5e5f,A5
           MVKL    .S1     0x63a94b17,A4
           MVKH    .S1     0x422069f7,A6

           FMPYDP  .M2     B7:B6,B5:B4,B19:B18 ; |183| 
||         MVKH    .S1     0x3f25bf32,A7

           FMPYDP  .M2     B7:B6,B7:B6,B17:B16 ; |183| 
||         MVKH    .S1     0x3f2c5e5f,A5

           MVKH    .S1     0x63a94b17,A4

           MVKL    .S1     0x3f6d6d3d,A21
||         FMPYDP  .M1X    A5:A4,B5:B4,A25:A24 ; |183| 

           MVKL    .S1     0xe157ddd,A20
||         FMPYDP  .M2     B21:B20,B19:B18,B21:B20 ; |183| 

           MVKL    .S1     0x3f8226e3,A19
||         FMPYDP  .M2X    A23:A22,B17:B16,B23:B22 ; |183| 
||         FMPYDP  .M1X    A7:A6,B7:B6,A23:A22 ; |183| 

           MVKL    .S1     0x55e6c23f,A18
           MVKH    .S1     0x3f6d6d3d,A21
           MVKH    .S1     0xe157ddd,A20

           MVKH    .S1     0x3f8226e3,A19
||         FMPYDP  .M1X    A21:A20,B7:B6,A21:A20 ; |183| 
||         FADDDP  .L2     B23:B22,B21:B20,B21:B20 ; |183| 
||         FADDDP  .L1     A23:A22,A25:A24,A23:A22 ; |183| 

           MVKH    .S1     0x55e6c23f,A18

           FMPYDP  .M1X    A19:A18,B5:B4,A19:A18 ; |183| 
||         MVKL    .S1     0x11111105,A8

           MVKL    .S1     0x3fc11111,A9
           MVKL    .S1     0x3f9664f4,A5
           MVKL    .S1     0x882c10f9,A4

           FADDDP  .L1     A21:A20,A19:A18,A19:A18 ; |183| 
||         MVKH    .S1     0x11111105,A8

           MVKH    .S1     0x3fc11111,A9
           MVKL    .S1     0x1ba1ba20,A6

           MVKL    .S1     0x3faba1ba,A7
||         FMPYDP  .M2X    A9:A8,B7:B6,B23:B22 ; |183| 
||         FMPYDP  .M1X    B17:B16,A23:A22,A9:A8 ; |183| 

           MVKH    .S1     0x3f9664f4,A5
           MVKH    .S1     0x882c10f9,A4
           MVKL    .S1     0x3fd55555,A17

           MVKL    .S1     0x5555554f,A16
||         FMPYDP  .M2X    A5:A4,B17:B16,B7:B6 ; |183| 
||         FADDDP  .L1X    B21:B20,A19:A18,A5:A4 ; |183| 

           MVKH    .S1     0x1ba1ba20,A6
           MVKH    .S1     0x3faba1ba,A7
           MVKH    .S1     0x3fd55555,A17
           MVKH    .S1     0x5555554f,A16
           FMPYDP  .M2X    A7:A6,B19:B18,B19:B18 ; |183| 
           FMPYDP  .M2X    A17:A16,B5:B4,B5:B4 ; |183| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |183| 
           ZERO    .L2     B31
           SUB     .S1     A13,1,A0          ; |186| 

           FADDDP  .L2     B19:B18,B7:B6,B5:B4 ; |183| 
||         FADDDP  .S2     B5:B4,B23:B22,B7:B6 ; |183| 

           FMPYDP  .M2X    B17:B16,A5:A4,B17:B16 ; |183| 
           ZERO    .D2     B18
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |183| 
           MVKL    .S2     0x47efffff,B19
           MVKH    .S2     0xe0000000,B18
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |183| 
           ZERO    .L2     B16               ; |67| 
           SET     .S2     B31,0x1e,0x1e,B17
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |183| 
           MVKH    .S2     0x47efffff,B19
           SUB     .L1     A13,1,A13         ; |186| 
           ZERO    .L1     A4                ; |191| 
           FADDDP  .L2     B9:B8,B5:B4,B7:B6 ; |183| 
           ZERO    .L1     A5
           MVKH    .S1     0xbff80000,A5
           RCPDP   .S2     B7:B6,B5:B4       ; |67| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |67| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |67| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |67| 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |67| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |67| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |67| 
           NOP             3

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |67| 
||         ABSDP   .S2     B7:B6,B7:B6       ; |69| 

           NOP             1
           CMPGTDP .S2     B7:B6,B19:B18,B0  ; |69| 
           NOP             1

           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |67| 
||         MVK     .S2     12,B6

           ADD     .L2X    A15,B6,B6

           LDW     .D2T2   *B6,B6            ; |190| 
||         B       .S1     $C$L14            ; |73| 

           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |67| 
           NOP             3

   [ B0]   ZERO    .L2     B5:B4             ; |70| 
||         ADD     .S2     B10,B6,B6         ; |190| 
||         ADD     .D2     8,B10,B10         ; |186| 

           ; BRANCH OCCURS {$C$L14}          ; |73| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 53

           MVKL    .S2     0x3f25bf32,B23
||         MVKL    .S1     0x3f57da36,A21

           MVKL    .S2     0x3f2c5e5f,B9
||         MVKL    .S1     0x452b75eb,A20

           FMPYDP  .M1     A17:A16,A17:A16,A5:A4 ; |129| 
||         MVKL    .S2     0x63a94b17,B8
||         MVKH    .S1     0x3f57da36,A21

           FMPYDP  .M1     A17:A16,A9:A8,A19:A18 ; |129| 
||         MVKL    .S2     0x422069f7,B22
||         MVKH    .S1     0x452b75eb,A20

           MVKH    .S2     0x3f2c5e5f,B9
           MVKH    .S2     0x63a94b17,B8

           MVKH    .S2     0x3f25bf32,B23
||         FMPYDP  .M2X    B9:B8,A9:A8,B9:B8 ; |129| 

           MVKH    .S2     0x422069f7,B22
||         FMPYDP  .M1     A21:A20,A19:A18,A23:A22 ; |129| 
||         MVKL    .S1     0x3f9664f4,A21

           MVKL    .S2     0x3f8226e3,B5
||         MVKL    .S1     0x882c10f9,A20

           MVKL    .S2     0x55e6c23f,B4
||         FMPYDP  .M1X    B23:B22,A17:A16,A27:A26 ; |129| 
||         MVKH    .S1     0x3f9664f4,A21

           MVKL    .S2     0xe157ddd,B6
||         MVKH    .S1     0x882c10f9,A20

           MVKL    .S2     0x3f6d6d3d,B7
           MVKL    .S2     0x3f435582,B17

           MVKL    .S2     0x48036744,B16
||         FADDDP  .L1X    A27:A26,B9:B8,A27:A26 ; |129| 

           MVKH    .S2     0x3f8226e3,B5
           MVKH    .S2     0x55e6c23f,B4

           MVKH    .S2     0xe157ddd,B6
||         FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |129| 

           MVKH    .S2     0x3f6d6d3d,B7

           MVKH    .S2     0x3f435582,B17
||         FMPYDP  .M2X    B7:B6,A17:A16,B7:B6 ; |129| 

           MVKH    .S2     0x48036744,B16
           MVKL    .S2     0x11111105,B18

           FMPYDP  .M1X    B17:B16,A5:A4,A25:A24 ; |129| 
||         MVKL    .S2     0x3fc11111,B19

           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |129| 
||         MVKL    .S2     0x3fd55555,B21

           MVKL    .S2     0x5555554f,B20
           MVKH    .S2     0x11111105,B18

           FADDDP  .L1     A25:A24,A23:A22,A25:A24 ; |129| 
||         MVKH    .S2     0x3fc11111,B19

           MVKH    .S2     0x3fd55555,B21
           MVKH    .S2     0x5555554f,B20

           MVKL    .S2     0x3faba1ba,B17
||         FADDDP  .L1X    A25:A24,B5:B4,A21:A20 ; |129| 
||         FMPYDP  .M1     A21:A20,A5:A4,A25:A24 ; |129| 

           FMPYDP  .M1X    B21:B20,A9:A8,A23:A22 ; |129| 
||         MVKL    .S2     0x1ba1ba20,B16

           FMPYDP  .M1X    B19:B18,A17:A16,A9:A8 ; |129| 
||         MVKH    .S2     0x3faba1ba,B17

           FMPYDP  .M1     A5:A4,A27:A26,A17:A16 ; |129| 
           MVKH    .S2     0x1ba1ba20,B16
           FMPYDP  .M2X    B17:B16,A19:A18,B5:B4 ; |129| 
           FADDDP  .L1     A23:A22,A9:A8,A9:A8 ; |129| 
           FADDDP  .L1     A17:A16,A21:A20,A17:A16 ; |129| 
           MVK     .S2     12,B6
           FADDDP  .L2X    B5:B4,A25:A24,B5:B4 ; |129| 
           FMPYDP  .M1     A5:A4,A17:A16,A5:A4 ; |129| 
           ADD     .S2X    A15,B6,B6
           FADDDP  .L2X    A9:A8,B5:B4,B5:B4 ; |129| 
           LDW     .D2T2   *B6,B6            ; |190| 
           SUB     .L1     A13,1,A0          ; |186| 
           FADDDP  .L2X    A5:A4,B5:B4,B5:B4 ; |129| 
           SUB     .L1     A13,1,A13         ; |186| 
           ZERO    .L1     A4                ; |191| 
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |129| 
           ADD     .L2     B10,B6,B6         ; |190| 
           ADD     .L2     8,B10,B10         ; |186| 
           ZERO    .L1     A5
           FADDDP  .L2X    A7:A6,B5:B4,B5:B4 ; |129| 
           MVKH    .S1     0xbff80000,A5
           NOP             1
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 15
           FMPYDP  .M2     B25:B24,B5:B4,B5:B4 ; |190| 
           NOP             3
           STDW    .D2T2   B5:B4,*B6         ; |190| 
           LDDW    .D1T1   *A10,A7:A6        ; |191| 
           NOP             3
   [ A0]   B       .S1     $C$L12            ; |186| 
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |191| 
           NOP             3

   [ A0]   CALL    .S1     _tan              ; |187| 
||         STDW    .D1T1   A5:A4,*++A10      ; |191| 

           ; BRANCHCC OCCURS {$C$L12}        ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     _tandp_v          ; |193| 
           LDW     .D1T2   *A12,B4           ; |193| 
           ADDKPC  .S2     $C$RL20,B3,2      ; |193| 

           MV      .L1     A11,A4
||         MVK     .S1     0x6f4,A6          ; |193| 

$C$RL20:   ; CALL OCCURS {_tandp_v} {0}      ; |193| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     _allequal,B3
||         MVK     .S1     0x6f4,A4          ; |196| 

$C$RL21:   ; CALL OCCURS {_allequal} {0}     ; |196| 

           CALLP   .S2     _print_test_results,B3
||         MVK     .L1     0x4,A4            ; |197| 

$C$RL22:   ; CALL OCCURS {_print_test_results} {0}  ; |197| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S1     _cycle_counts+24,A3

           MVKH    .S1     _cycle_counts+24,A3
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .L1     A10               ; |114| 
||         ZERO    .D1     A11               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*A3       ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           MVC     .S2     TSCL,B6           ; |117| 
||         STDW    .D1T2   B5:B4,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B4       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 
||         MVKL    .S1     _t_offset,A3

           ADD     .L2     B5,B4,B7          ; |117| 
||         MVKH    .S1     _t_offset,A3

           MVKL    .S1     _input,A3
||         STDW    .D1T2   B7:B6,*A3         ; |117| 

           CALL    .S2     _gimme_random     ; |207| 
||         MVKH    .S1     _input,A3

           LDW     .D1T1   *A3,A15           ; |207| 
||         MV      .L2X    A11,B10           ; |117| 
||         MVK     .S1     0x80,A12
||         ZERO    .L1     A5

           MV      .L2X    A11,B4            ; |207| 
||         ZERO    .S2     B5
||         MVKH    .S1     0x40690000,A5
||         MV      .L1     A10,A4            ; |207| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 3
           MVKH    .S2     0xc0590000,B5
           ADDKPC  .S2     $C$RL23,B3,1      ; |207| 
$C$RL23:   ; CALL OCCURS {_gimme_random} {0}  ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 53
           ADD     .L1X    A15,B10,A3        ; |207| 

           STDW    .D1T1   A5:A4,*A3         ; |207| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A6             ; |122| Define a twin register
||         MVC     .S2     TSCH,B18          ; |122| 

           ADD     .L2X    A15,B10,B4        ; |170| 
||         MVKL    .S2     0x3fd45f30,B5
||         MVKL    .S1     0x3fd45f30,A9
||         MVK     .D2     0xfffffffc,B16    ; |170| 

           LDDW    .D2T2   *B4,B7:B6         ; |170| 
||         MVKL    .S2     0x6dc9c889,B4
||         MVKH    .S1     0x3fd45f30,A9
||         MVK     .L2     0xfffffffc,B8     ; |168| 
||         MV      .L1X    B18,A7            ; |122| 

           MVKL    .S1     0x400921fb,A17
||         ZERO    .L2     B31               ; |176| 

           MVKH    .S2     0x6dc9c889,B4
           MVKH    .S2     0x3fd45f30,B5
           MV      .L1X    B4,A8             ; |170| 
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |170| 
           MVKL    .S1     0x54442c46,A16
           FMPYDP  .M1     A9:A8,A5:A4,A9:A8 ; |168| 
           MVKL    .S2     0x3d3a3fff,B17
           DPINT   .L2     B5:B4,B4          ; |170| 
           MVKH    .S1     0x400921fb,A17
           DPINT   .L1     A9:A8,A3          ; |168| 
           MVKH    .S2     0x3d3a3fff,B17
           INTDP   .L2     B4,B5:B4          ; |170| 
           MVKH    .S1     0x54442c46,A16
           INTDP   .L1     A3,A19:A18        ; |168| 
           MV      .S2     B17,B9            ; |170| 
           MV      .L1     A16,A8            ; |168| 
           MV      .S1     A17,A9            ; |168| 
           FMPYDP  .M1X    A17:A16,B5:B4,A21:A20 ; |170| 
           FMPYDP  .M1     A9:A8,A19:A18,A17:A16 ; |168| 
           FMPYDP  .M2     B17:B16,B5:B4,B5:B4 ; |170| 
           MVKL    .S1     0x54442b65,A8
           MVKH    .S1     0x54442b65,A8

           FSUBDP  .L2X    B7:B6,A21:A20,B17:B16 ; |170| 
||         FSUBDP  .L1     A5:A4,A17:A16,A5:A4 ; |168| 
||         MVKL    .S2     0x54442d18,B6

           MV      .L2X    A9,B7             ; |170| 
||         MVKL    .S1     0x3ff921fb,A9
||         MVKH    .S2     0x54442d18,B6

           MVKH    .S1     0x3ff921fb,A9
           FSUBDP  .L2     B17:B16,B5:B4,B5:B4 ; |170| 
           FMPYDP  .M2X    B9:B8,A19:A18,B17:B16 ; |168| 
           DADD    .S2X    0,A5:A4,B9:B8     ; |168| Define a twin register
           ZERO    .L1     A5:A4             ; |174| 
           CMPGTDP .S1X    B5:B4,A9:A8,A0    ; |170| 
           FSUBDP  .L2     B9:B8,B17:B16,B25:B24 ; |168| 
   [ A0]   FSUBDP  .L2     B5:B4,B7:B6,B25:B24 ; |171| 
           MVKL    .S2     0x3fe921fb,B5
           MV      .S2     B6,B4             ; |174| 
           SET     .S2     B31,31,31,B6      ; |176| 
           CMPLTDP .S1X    B25:B24,A5:A4,A0  ; |174| 
           MVKH    .S2     0x3fe921fb,B5

   [ A0]   XOR     .L2     B25,B6,B25        ; |176| 
|| [ A0]   ZERO    .S2     B27
|| [!A0]   ZERO    .D2     B27

   [ A0]   ZERO    .L2     B26               ; |175| 
||         CMPGTDP .S2     B25:B24,B5:B4,B0  ; |180| 

   [!A0]   ZERO    .L2     B26               ; |160| 

   [!B0]   BNOP    .S1     $C$L16,4          ; |180| 
|| [!A0]   SET     .S2     B27,0x14,0x1d,B27

   [ A0]   MVKH    .S2     0xbff00000,B27
           ; BRANCHCC OCCURS {$C$L16}        ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 95

           MV      .L2X    A8,B4
||         MVKL    .S1     0x3b981c8c,A4
||         MVKL    .S2     0x422069f7,B16

           MV      .L2X    A9,B5
||         MVKL    .S1     0x3d3b3226,A5
||         MVKL    .S2     0x3f25bf32,B17

           FSUBDP  .L2     B5:B4,B25:B24,B5:B4 ; |181| 
||         MVKH    .S1     0x3b981c8c,A4
||         MVKL    .S2     0x3f2c5e5f,B9

           MVKH    .S1     0x3d3b3226,A5
||         MVKL    .S2     0x63a94b17,B8

           MVKH    .S2     0x422069f7,B16
||         MVKL    .S1     0x452b75eb,A22

           MVKH    .S2     0x3f25bf32,B17
||         MVKL    .S1     0x3f57da36,A23

           FADDDP  .L1X    A5:A4,B5:B4,A17:A16 ; |181| 
||         MVKL    .S2     0xe157ddd,B4
||         MVKH    .S1     0x452b75eb,A22

           MVKL    .S2     0x3f6d6d3d,B5
||         MVKH    .S1     0x3f57da36,A23

           MVKH    .S2     0x3f2c5e5f,B9

           FMPYDP  .M1     A17:A16,A17:A16,A5:A4 ; |183| 
||         MVKH    .S2     0x63a94b17,B8

           MVKL    .S2     0x48036744,B28
           MVKL    .S2     0x3f435582,B29
           MVKL    .S2     0x3f8226e3,B7

           FMPYDP  .M1     A5:A4,A5:A4,A9:A8 ; |183| 
||         MVKL    .S2     0x55e6c23f,B6

           FMPYDP  .M2X    B9:B8,A5:A4,B9:B8 ; |183| 
||         MVKH    .S2     0xe157ddd,B4

           MVKH    .S2     0x3f6d6d3d,B5
           MVKH    .S2     0x48036744,B28

           FMPYDP  .M1     A9:A8,A5:A4,A21:A20 ; |183| 
||         MVKH    .S2     0x3f435582,B29

           FMPYDP  .M1     A9:A8,A9:A8,A19:A18 ; |183| 
||         FMPYDP  .M2X    B17:B16,A9:A8,B17:B16 ; |183| 
||         MVKH    .S2     0x3f8226e3,B7

           MVKH    .S2     0x55e6c23f,B6
||         FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |183| 

           FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |183| 
||         MVKL    .S2     0x1ba1ba20,B18

           FMPYDP  .M1     A23:A22,A21:A20,A23:A22 ; |183| 
||         MVKL    .S2     0x3faba1ba,B19

           FMPYDP  .M1X    B29:B28,A19:A18,A25:A24 ; |183| 
||         FADDDP  .L2     B17:B16,B9:B8,B9:B8 ; |183| 
||         MVKL    .S2     0x3fd55555,B25

           MVKL    .S2     0x5555554f,B24

           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |183| 
||         MVKH    .S2     0x1ba1ba20,B18

           MVKH    .S2     0x3faba1ba,B19

           FADDDP  .L1     A25:A24,A23:A22,A27:A26 ; |183| 
||         MVKL    .S2     0x3f9664f4,B21

           MVKL    .S2     0x882c10f9,B20
||         FMPYDP  .M1X    B19:B18,A21:A20,A25:A24 ; |183| 

           MVKL    .S2     0x3fc11111,B23
||         FMPYDP  .M1X    A19:A18,B9:B8,A21:A20 ; |183| 

           MVKL    .S2     0x11111105,B22
||         FADDDP  .L1X    A27:A26,B5:B4,A27:A26 ; |183| 

           MVKH    .S2     0x3fd55555,B25
           MVKH    .S2     0x5555554f,B24
           MVKH    .S2     0x3f9664f4,B21

           MVKH    .S2     0x882c10f9,B20
||         FMPYDP  .M1X    B25:B24,A5:A4,A5:A4 ; |183| 

           MVKH    .S2     0x3fc11111,B23
           MVKH    .S2     0x11111105,B22
           FMPYDP  .M1X    B21:B20,A19:A18,A23:A22 ; |183| 
           FMPYDP  .M1X    B23:B22,A9:A8,A9:A8 ; |183| 
           FADDDP  .L1     A21:A20,A27:A26,A21:A20 ; |183| 
           ZERO    .L1     A31
           MVKL    .S1     _t_start,A3

           FADDDP  .L1     A5:A4,A9:A8,A9:A8 ; |183| 
||         FADDDP  .S1     A25:A24,A23:A22,A5:A4 ; |183| 

           FMPYDP  .M1     A19:A18,A21:A20,A19:A18 ; |183| 
           ZERO    .D1     A20
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |183| 
           MVKH    .S1     _t_start,A3
           STDW    .D1T1   A7:A6,*A3
           FADDDP  .L1     A19:A18,A5:A4,A5:A4 ; |183| 
           ZERO    .L1     A18               ; |67| 
           SET     .S1     A31,0x1e,0x1e,A19
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |183| 
           MVKL    .S1     0x47efffff,A21
           MVKL    .S2     _output+12,B6
           MVKH    .S1     0x47efffff,A21
           FADDDP  .L1     A17:A16,A5:A4,A9:A8 ; |183| 
           MVKH    .S2     _output+12,B6
           LDW     .D2T2   *B6,B6            ; |211| 
           RCPDP   .S1     A9:A8,A5:A4       ; |67| 
           NOP             1
           FMPYDP  .M1     A9:A8,A5:A4,A17:A16 ; |67| 
           MVKH    .S1     0xe0000000,A20
           ADD     .L2     B10,B6,B6         ; |211| 
           NOP             1
           FSUBDP  .L1     A19:A18,A17:A16,A17:A16 ; |67| 
           ZERO    .L1     A18               ; |67| 
           NOP             1
           FMPYDP  .M1     A5:A4,A17:A16,A5:A4 ; |67| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A17:A16 ; |67| 
           NOP             3
           FSUBDP  .L1     A19:A18,A17:A16,A17:A16 ; |67| 
           ZERO    .L1     A18               ; |67| 
           NOP             1
           FMPYDP  .M1     A5:A4,A17:A16,A5:A4 ; |67| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A17:A16 ; |67| 
           ABSDP   .S1     A9:A8,A9:A8       ; |69| 
           NOP             2
           FSUBDP  .L1     A19:A18,A17:A16,A17:A16 ; |67| 
           CMPGTDP .S1     A9:A8,A21:A20,A0  ; |69| 
           NOP             1
           FMPYDP  .M1     A5:A4,A17:A16,A5:A4 ; |67| 
           BNOP    .S1     $C$L17,2          ; |73| 
   [ A0]   ZERO    .L1     A5:A4             ; |70| 
           NOP             1
           DADD    .L2X    0,A5:A4,B5:B4     ; |73| 
           ; BRANCH OCCURS {$C$L17}          ; |73| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 53

           FMPYDP  .M2     B25:B24,B25:B24,B5:B4 ; |129| 
||         MVKL    .S1     0x3f435582,A21
||         MVKL    .S2     0x452b75eb,B18

           MVKL    .S1     0x48036744,A20
||         MVKL    .S2     0x3f57da36,B19

           MVKL    .S1     0x3f25bf32,A19
||         MVKH    .S2     0x452b75eb,B18

           MVKL    .S1     0x422069f7,A18
||         MVKH    .S2     0x3f57da36,B19

           FMPYDP  .M2     B5:B4,B5:B4,B7:B6 ; |129| 
||         MVKL    .S1     0x3f2c5e5f,A9
||         MVKL    .S2     0x3f9664f4,B29

           MVKL    .S1     0x63a94b17,A8
||         MVKL    .S2     0x882c10f9,B28

           MVKH    .S1     0x3f435582,A21
||         MVKH    .S2     0x3f9664f4,B29

           MVKH    .S1     0x48036744,A20
||         MVKH    .S2     0x882c10f9,B28

           FMPYDP  .M2     B7:B6,B7:B6,B9:B8 ; |129| 
||         MVKH    .S1     0x3f25bf32,A19

           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |129| 
||         MVKH    .S1     0x422069f7,A18

           MVKH    .S1     0x3f2c5e5f,A9

           MVKH    .S1     0x63a94b17,A8
||         FMPYDP  .M2X    A19:A18,B7:B6,B23:B22 ; |129| 

           MVKL    .S1     0x3f6d6d3d,A5
||         FMPYDP  .M1X    A9:A8,B5:B4,A23:A22 ; |129| 
||         FMPYDP  .M2X    A21:A20,B9:B8,B21:B20 ; |129| 

           MVKL    .S1     0xe157ddd,A4
||         FMPYDP  .M2     B19:B18,B17:B16,B19:B18 ; |129| 

           MVKL    .S1     0x3f8226e3,A25
           MVKL    .S1     0x55e6c23f,A24
           MVKH    .S1     0x3f6d6d3d,A5

           MVKH    .S1     0xe157ddd,A4
||         FADDDP  .L2X    B23:B22,A23:A22,B23:B22 ; |129| 

           MVKH    .S1     0x3f8226e3,A25
||         FMPYDP  .M1X    A5:A4,B7:B6,A21:A20 ; |129| 

           MVKH    .S1     0x55e6c23f,A24

           FMPYDP  .M1X    A25:A24,B5:B4,A19:A18 ; |129| 
||         MVKL    .S1     0x3fd55555,A17

           MVKL    .S1     0x5555554f,A16
           MVKH    .S1     0x3fd55555,A17
           MVKH    .S1     0x5555554f,A16

           FADDDP  .L1     A21:A20,A19:A18,A19:A18 ; |129| 
||         MVKL    .S1     0x3faba1ba,A5
||         FMPYDP  .M1X    A17:A16,B5:B4,A17:A16 ; |129| 
||         FADDDP  .L2     B21:B20,B19:B18,B5:B4 ; |129| 

           MVKL    .S1     0x1ba1ba20,A4
           MVKL    .S1     0x3fc11111,A9
           MVKL    .S1     0x11111105,A8
           MVKH    .S1     0x3faba1ba,A5
           MVKH    .S1     0x1ba1ba20,A4

           MVKH    .S1     0x3fc11111,A9
||         FMPYDP  .M1X    A5:A4,B17:B16,A21:A20 ; |129| 
||         FADDDP  .L2X    B5:B4,A19:A18,B17:B16 ; |129| 

           MVKH    .S1     0x11111105,A8

           FMPYDP  .M1X    A9:A8,B7:B6,A9:A8 ; |129| 
||         FMPYDP  .M2     B9:B8,B23:B22,B7:B6 ; |129| 

           FMPYDP  .M2     B29:B28,B9:B8,B5:B4 ; |129| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           FADDDP  .L2     B7:B6,B17:B16,B7:B6 ; |129| 
||         FADDDP  .L1     A17:A16,A9:A8,A5:A4 ; |129| 

           FADDDP  .L2X    A21:A20,B5:B4,B5:B4 ; |129| 
           STDW    .D1T1   A7:A6,*A3
           FMPYDP  .M2     B9:B8,B7:B6,B7:B6 ; |129| 
           FADDDP  .L2X    A5:A4,B5:B4,B5:B4 ; |129| 
           NOP             2
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |129| 
           MVKL    .S2     _output+12,B6
           MVKH    .S2     _output+12,B6
           FMPYDP  .M2     B25:B24,B5:B4,B5:B4 ; |129| 
           LDW     .D2T2   *B6,B6            ; |211| 
           NOP             2
           FADDDP  .L2     B25:B24,B5:B4,B5:B4 ; |129| 
           NOP             1
           ADD     .S2     B10,B6,B6         ; |211| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 21
           FMPYDP  .M2     B27:B26,B5:B4,B5:B4 ; |211| 
           NOP             3

           STDW    .D2T2   B5:B4,*B6         ; |211| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     _t_offset,A3
||         MVKL    .S2     _cycle_counts+24,B5
||         SUB     .L1     A12,1,A0          ; |205| 
||         MV      .L2     B4,B9             ; |128| 
||         ADD     .D2     8,B10,B10         ; |205| 
||         SUB     .D1     A12,1,A12         ; |205| 

           MVKH    .S1     _t_offset,A3
||         MVKH    .S2     _cycle_counts+24,B5

           MVKL    .S1     _t_stop,A31
||         LDDW    .D1T1   *A3,A9:A8         ; |130| 

           LDDW    .D2T2   *B5,B7:B6         ; |130| 
           MVKH    .S1     _t_stop,A31
           MV      .L1X    B5,A14            ; |130| 
           STDW    .D1T2   B9:B8,*A31        ; |128| 
           ADDU    .L1     A8,A6,A5:A4       ; |130| 

           ADD     .L1     A5,A9,A3          ; |130| 
|| [ A0]   ZERO    .S1     A5

           ADD     .L1     A3,A7,A3          ; |130| 
|| [ A0]   B       .S2     $C$L15            ; |205| 
||         SUBU    .L2X    B8,A4,B5:B4       ; |130| 
|| [ A0]   MVKH    .S1     0x40690000,A5
|| [ A0]   MV      .D1     A10,A4            ; |207| 

           EXT     .S2     B5,24,24,B16      ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 

           SUB     .L2X    B9,A3,B6          ; |130| 
|| [ A0]   MVKL    .S1     _input,A3
||         ADD     .S2     B5,B7,B5          ; |130| 

   [ A0]   CALL    .S2     _gimme_random     ; |207| 
|| [ A0]   MVKH    .S1     _input,A3
||         ADD     .L2     B6,B16,B6         ; |130| 

   [ A0]   LDW     .D1T1   *A3,A15           ; |207| 
||         ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D1T2   B5:B4,*A14        ; |130| 
|| [ A0]   ZERO    .L2     B5
|| [ A0]   MV      .S2X    A11,B4            ; |207| 

           ; BRANCHCC OCCURS {$C$L15}        ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL24,B3,3      ; |135| 
$C$RL24:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           MV      .L1     A11,A12           ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL25:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           MV      .L2X    A14,B4
           MVK     .S1     24,A14

           SUB     .L1X    B4,A14,A14
||         STDW    .D2T1   A5:A4,*B4         ; |135| 
||         MV      .L2X    A10,B5            ; |114| 

           MVC     .S2     B5,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*A14      ; |114| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 
           MVK     .S1     0x80,A30

           EXT     .S2     B7,24,24,B4       ; |117| 
||         SUB     .L2     B8,B4,B5          ; |117| 
||         MV      .L1X    B6,A3             ; |117| 
||         STW     .D2T1   A30,*+SP(12)      ; |117| 
||         MVKL    .S1     _output,A31

           ADD     .L2     B5,B4,B4          ; |117| 
||         STW     .D2T1   A3,*+SP(16)       ; |117| 
||         MVKH    .S1     _output,A31
||         MV      .S2X    A10,B11

           STW     .D2T2   B4,*+SP(20)       ; |117| 
||         LDW     .D1T1   *A31,A12
||         MV      .L2X    A10,B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 8
           MVC     .S2     TSCL,B12          ; |122| 
           MVC     .S2     TSCH,B13          ; |122| 
           CALL    .S1     _tan              ; |220| 
           LDDW    .D1T1   *A15++,A5:A4      ; |220| 
           ADDKPC  .S2     $C$RL26,B3,3      ; |220| 
$C$RL26:   ; CALL OCCURS {_tan} {0}          ; |220| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           STDW    .D1T1   A5:A4,*A12++      ; |220| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 
           LDW     .D2T1   *+SP(12),A3       ; |130| 
           LDW     .D2T2   *+SP(16),B4       ; |128| 
           LDW     .D2T2   *+SP(20),B31      ; |130| 
           NOP             2
           SUB     .L1     A3,1,A0           ; |218| 

   [ A0]   B       .S2     $C$L18            ; |218| 
||         ADDU    .L2     B4,B12,B7:B6      ; |130| 
|| [!A0]   MVKL    .S1     _t_stop,A3
||         STW     .D2T1   A0,*+SP(12)       ; |130| 

           ADD     .S2     B7,B31,B4         ; |130| 
||         SUBU    .L2     B8,B6,B7:B6       ; |130| 
|| [!A0]   MVKH    .S1     _t_stop,A3

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         ADD     .D2     B4,B13,B4         ; |130| 
||         EXT     .S2     B7,24,24,B9       ; |130| 
||         ADDU    .L2     B10,B6,B7:B6      ; |130| 

           SUB     .L2     B5,B4,B4          ; |130| 
||         MV      .S2     B6,B10            ; |130| 

           ADD     .L2     B4,B9,B7          ; |130| 
||         ADD     .S2     B7,B11,B4         ; |130| 
||         MV      .D2     B5,B9             ; |128| 

           ADD     .L2     B4,B7,B11         ; |130| 
           ; BRANCHCC OCCURS {$C$L18}        ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           STDW    .D1T2   B9:B8,*A3

           ADDKPC  .S2     $C$RL27,B3,0      ; |135| 
||         DADD    .L1X    0,B11:B10,A5:A4   ; |135| 

$C$RL27:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL28:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           MV      .L2X    A11,B4            ; |114| 
||         STDW    .D1T1   A11:A10,*+A14(16) ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A14        ; |135| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           MVKL    .S1     _t_offset,A3
           MVKH    .S1     _t_offset,A3
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           MVK     .S1     0x80,A3
||         MV      .L2X    A3,B8             ; |117| 
||         EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .D2     B7,B6,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 

           STDW    .D2T2   B5:B4,*B8         ; |117| 
||         MV      .L2X    A3,B10            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T1   *A3,A3            ; |229| 
           MVKL    .S2     _t_start,B6
           MVKH    .S2     _t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |229| 
||         CALL    .S1     _tandp_c          ; |229| 

           LDDW    .D1T1   *A3,A5:A4         ; |229| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |229| 
$C$RL29:   ; CALL OCCURS {_tandp_c} {0}      ; |229| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     _output+8,B4
           MVKH    .S2     _output+8,B4
           LDW     .D2T2   *B4,B4            ; |229| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |229| 

           STDW    .D1T1   A5:A4,*A3         ; |229| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S2     _t_start,B11
||         MVKL    .S1     _t_offset,A15
||         SUB     .L1X    B10,1,A0          ; |227| 
||         MV      .L2     B6,B17            ; |128| 
||         ADD     .D1     8,A12,A12         ; |227| 
||         SUB     .D2     B10,1,B10         ; |227| 

           MVKH    .S2     _t_start,B11
||         MVKH    .S1     _t_offset,A15

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B11,B9:B8        ; |130| 
||         MVKL    .S1     _cycle_counts+16,A3

           MVKH    .S1     _cycle_counts+16,A3

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     _t_stop,A31

           MV      .L2X    A3,B12            ; |128| 
||         MVKH    .S1     _t_stop,A31

           STDW    .D1T2   B17:B16,*A31      ; |128| 
           ADDU    .L2X    A4,B8,B5:B4       ; |130| 

   [ A0]   B       .S1     $C$L19            ; |227| 
||         ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B6,B9,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B6         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D2T2   B5:B4,*B12        ; |130| 

           ; BRANCHCC OCCURS {$C$L19}        ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A14(16),A5:A4   ; |135| 
           ADDKPC  .S2     $C$RL30,B3,3      ; |135| 
$C$RL30:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 67
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A11,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL31:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 

           MV      .L2X    A10,B4            ; |114| 
||         MV      .L1X    B12,A12           ; |135| 
||         STDW    .D1T1   A11:A10,*+A14(32) ; |114| 

           STDW    .D1T1   A5:A4,*A12        ; |135| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D2T2   B5:B4,*B11        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           LDW     .D2T1   *+SP(24),A3       ; |117| 

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKL    .S1     _input,A4

           EXT     .S2     B7,24,24,B4       ; |117| 
||         MVKH    .S1     _input,A4
||         SUB     .L2     B8,B5,B5          ; |117| 

           ADD     .L2     B5,B4,B7          ; |117| 
||         LDW     .D1T1   *A4,A4            ; |236| 

           STDW    .D1T2   B7:B6,*A15        ; |117| 

           CALLP   .S2     _tandp_v,B3
||         LDW     .D1T2   *A3,B4            ; |236| 
||         MVK     .S1     0x80,A6           ; |236| 

$C$RL32:   ; CALL OCCURS {_tandp_v} {0}      ; |236| 
           MVC     .S2     TSCL,B4           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           LDDW    .D2T2   *B11,B9:B8        ; |130| 
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           MVK     .S2     16,B10
           ADD     .L2X    A12,B10,B10
           LDDW    .D2T2   *B10,B7:B6        ; |130| 
           MVKL    .S1     _t_stop,A31
           ADDU    .L1X    A4,B8,A7:A6       ; |130| 

           MV      .L1     A6,A3             ; |130| 
||         ADD     .S1     A7,A5,A6          ; |130| 

           SUBU    .L1X    B4,A3,A5:A4       ; |130| 

           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
||         ADD     .L2X    A6,B9,B6          ; |130| 

           EXT     .S1     A5,24,24,A3       ; |130| 

           ADD     .L2X    A7,B7,B7          ; |130| 
||         SUB     .S2     B5,B6,B9          ; |130| 

           ADD     .L2X    B9,A3,B9          ; |130| 
||         MVKH    .S1     _t_stop,A31

           ADD     .L2     B7,B9,B7          ; |130| 
||         MV      .S2X    A6,B6             ; |130| 

           MV      .L2X    A31,B8            ; |128| 

           CALLP   .S2     __fltllif,B3
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         STDW    .D2T2   B5:B4,*B8         ; |128| 

$C$RL33:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1     A11,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           MV      .L2X    A10,B4            ; |114| 
||         STDW    .D1T1   A11:A10,*+A14(8)  ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A5:A4,*B10        ; |130| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B4,B31         ; |117| 

           ADD     .L2     B31,B5,B5         ; |117| 
||         MV      .S2     B6,B4             ; |117| 

           STDW    .D1T2   B5:B4,*A15        ; |117| 
||         MVK     .S1     0x80,A10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T1   *A3,A3            ; |245| 
           MV      .L2     B11,B6            ; |245| 
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             2

           ADD     .L1     A11,A3,A3         ; |245| 
||         CALL    .S1     _tandp            ; |245| 

           LDDW    .D1T1   *A3,A5:A4         ; |245| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |245| 
$C$RL35:   ; CALL OCCURS {_tandp} {0}        ; |245| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           MVKL    .S2     _output+4,B4
           MVKH    .S2     _output+4,B4
           LDW     .D2T2   *B4,B4            ; |245| 
           NOP             4
           ADD     .L1X    A11,B4,A3         ; |245| 

           STDW    .D1T1   A5:A4,*A3         ; |245| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MV      .L2     B11,B4            ; |128| 
||         MV      .L1     A15,A3            ; |128| 
||         MVK     .S1     8,A31
||         SUB     .D1     A10,1,A0          ; |243| 
||         SUBAW   .D2     B12,2,B10

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B4,B7:B6         ; |130| 
||         SUB     .L1X    B12,A31,A3
||         MVKL    .S1     _t_stop,A30

           MVKH    .S1     _t_stop,A30
||         SUB     .L1     A10,1,A10         ; |243| 

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
           ADD     .L1     8,A11,A11         ; |243| 
           STDW    .D1T2   B9:B8,*A30        ; |128| 
           ADDU    .L2X    A6,B6,B5:B4       ; |130| 

           ADD     .S2X    B5,A7,B6          ; |130| 
|| [ A0]   B       .S1     $C$L20            ; |243| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A4,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B6,B6          ; |130| 
||         ADD     .S2X    B5,A5,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D2T2   B5:B4,*B10        ; |130| 
|| [!A0]   MV      .L2     B10,B4

           ; BRANCHCC OCCURS {$C$L20}        ; |243| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D2T1   *B4,A5:A4         ; |135| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |135| 
$C$RL36:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 54
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL37:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 

           MVKL    .S1     _output,A3
||         MVKL    .S2     0xe826d695,B6

           MVKH    .S1     _output,A3
||         MVKL    .S2     0x3e112e0b,B7

           MV      .L1     A3,A11            ; |135| 
||         DADD    .S1     0,A5:A4,A7:A6     ; |135| 
||         MVKH    .S2     0xe826d695,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         STDW    .D2T1   A7:A6,*B10        ; |135| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A11,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL38:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0xe826d695,B6

           MVKL    .S1     _fcn_pass,A10
||         MVKL    .S2     0x3e112e0b,B7

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKH    .S1     _fcn_pass,A10
||         MVKH    .S2     0xe826d695,B6

           STW     .D1T1   A5,*+A10(4)       ; |66| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL39:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           STW     .D1T1   A3,*+A10(8)       ; |67| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL40:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     0x3e112e0b,B7

           MV      .L2X    A11,B5            ; |68| 
||         STW     .D1T1   A4,*+A10(12)      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL41:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2X    4,A10,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D1T1   A4,*+A10(16)      ; |69| 
           ADD     .L2X    8,A10,B4
           NOP             2

   [!B0]   BNOP    .S1     $C$L21,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L21}        ; |72| 
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
   [ A0]   B       .S1     $C$L22            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |252| 
   [ A0]   MVKL    .S1     _all_pass,A3
   [ A0]   MVKH    .S1     _all_pass,A3
           NOP             2
           ; BRANCHCC OCCURS {$C$L22}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |252| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           MV      .L1     A12,A4
           NOP             1
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x2,A4            ; |252| 
||         ADDKPC  .S2     $C$RL42,B3,0      ; |252| 

$C$RL42:   ; CALL OCCURS {_print_test_results} {0}  ; |252| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |253| 

$C$RL43:   ; CALL OCCURS {_printf} {0}       ; |253| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |253| 

$C$RL44:   ; CALL OCCURS {_printf} {0}       ; |253| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |260| 

$C$RL45:   ; CALL OCCURS {_print_profile_results} {0}  ; |260| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |263| 

$C$RL46:   ; CALL OCCURS {_print_memory_results} {0}  ; |263| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(32),B3      ; |264| 
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
$C$SL1:	.string	"tanDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_tan
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_tandp_c
	.global	_tandp
	.global	_tandp_v
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
