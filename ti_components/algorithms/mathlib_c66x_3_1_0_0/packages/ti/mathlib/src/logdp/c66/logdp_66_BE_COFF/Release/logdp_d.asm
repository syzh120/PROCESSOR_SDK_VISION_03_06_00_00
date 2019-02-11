;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:48:36 2013                                *
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
	.word	0412af0e3h,05be02646h		; _a[0] @ 0
	.word	04121197ah,020423b0eh		; _a[1] @ 64
	.word	040fdd968h,066ce505bh		; _a[2] @ 128
	.word	0411dd368h,0bb561764h		; _a[3] @ 192
	.word	040ed382dh,09b258ad4h		; _a[4] @ 256
	.word	04121d565h,09d3b8af1h		; _a[5] @ 320
	.word	04116dda3h,0357bd563h		; _a[6] @ 384
	.word	0412bd534h,0dfabcffdh		; _a[7] @ 448
	.word	04129b83fh,09ea2edd6h		; _a[8] @ 512
	.word	0411316d3h,0f33d2956h		; _a[9] @ 576
	.word	0412616dbh,0dea31975h		; _a[10] @ 640
	.word	04128999fh,0442a927bh		; _a[11] @ 704
	.word	040ff1162h,0f4b223d4h		; _a[12] @ 768
	.word	0412c7afbh,048aef7d0h		; _a[13] @ 832
	.word	041172716h,02e682152h		; _a[14] @ 896
	.word	041027270h,024213a0ch		; _a[15] @ 960
	.word	041197540h,038de59bdh		; _a[16] @ 1024
	.word	041093db2h,07a42ff59h		; _a[17] @ 1088
	.word	041008b60h,005c96031h		; _a[18] @ 1152
	.word	0411ec7d7h,05caf84bdh		; _a[19] @ 1216
	.word	041283555h,09a7f221fh		; _a[20] @ 1280
	.word	0411eac9bh,0d3cf04b5h		; _a[21] @ 1344
	.word	04116eaf8h,039f9c122h		; _a[22] @ 1408
	.word	040e6e078h,0a6c4fb47h		; _a[23] @ 1472
	.word	0412d5011h,03822eae7h		; _a[24] @ 1536
	.word	04127c24ah,0bfeef292h		; _a[25] @ 1600
	.word	040f71020h,09f912a5fh		; _a[26] @ 1664
	.word	0411f93ddh,0ca0f4d7bh		; _a[27] @ 1728
	.word	0410697d4h,0dd928fbah		; _a[28] @ 1792
	.word	04122381ah,0409807c9h		; _a[29] @ 1856
	.word	0412a26cbh,0117bc141h		; _a[30] @ 1920
	.word	04110c1a9h,047531048h		; _a[31] @ 1984
	.word	0411513c1h,03d9fb898h		; _a[32] @ 2048
	.word	040f7c32ah,0c0d5984dh		; _a[33] @ 2112
	.word	04129bddbh,098b47263h		; _a[34] @ 2176
	.word	0410ff548h,08969a0aeh		; _a[35] @ 2240
	.word	0412b9a46h,006488758h		; _a[36] @ 2304
	.word	040d6a8f9h,006eb412ch		; _a[37] @ 2368
	.word	04128c59dh,0be2003ach		; _a[38] @ 2432
	.word	040d69449h,04b40db92h		; _a[39] @ 2496
	.word	0412c62c5h,0e4d6eb34h		; _a[40] @ 2560
	.word	0412575b2h,02aca361ah		; _a[41] @ 2624
	.word	040fe2defh,06a712282h		; _a[42] @ 2688
	.word	04124bc73h,0b2c9696bh		; _a[43] @ 2752
	.word	040f240cfh,03d4e0978h		; _a[44] @ 2816
	.word	040f30c52h,0d6f2a5a4h		; _a[45] @ 2880
	.word	04126276dh,04f937238h		; _a[46] @ 2944
	.word	0412d4cc8h,0403d3ca1h		; _a[47] @ 3008
	.word	041220aeeh,06b23eac1h		; _a[48] @ 3072
	.word	041243069h,03dc66326h		; _a[49] @ 3136
	.word	04104bdf4h,0775cb5e3h		; _a[50] @ 3200
	.word	04106d07ch,093161a1eh		; _a[51] @ 3264
	.word	041131ff5h,03d990951h		; _a[52] @ 3328
	.word	04121564bh,073e56473h		; _a[53] @ 3392
	.word	041220d47h,08c2a7e59h		; _a[54] @ 3456
	.word	04110086bh,01d64f2c9h		; _a[55] @ 3520
	.word	04124d9ech,0fcdb6a1fh		; _a[56] @ 3584
	.word	0411f4735h,0387d4e09h		; _a[57] @ 3648
	.word	0412631a5h,05dbb6aa5h		; _a[58] @ 3712
	.word	04125ad41h,05f922963h		; _a[59] @ 3776
	.word	04126368dh,07feab368h		; _a[60] @ 3840
	.word	041283cbfh,013f65dc0h		; _a[61] @ 3904
	.word	0412ba7f5h,0c21bd8a4h		; _a[62] @ 3968
	.word	04122db3ch,058c2140ch		; _a[63] @ 4032
	.word	040f23957h,06f2ae07eh		; _a[64] @ 4096
	.word	04113223bh,0b2319e08h		; _a[65] @ 4160
	.word	040e2d284h,01f05ea25h		; _a[66] @ 4224
	.word	04124ed79h,0a346a352h		; _a[67] @ 4288
	.word	0412cad97h,09c435844h		; _a[68] @ 4352
	.word	041212e6dh,059ad2136h		; _a[69] @ 4416
	.word	04123ba2eh,0d7dd68fch		; _a[70] @ 4480
	.word	041084c18h,0412a5f4fh		; _a[71] @ 4544
	.word	041001909h,0911cb03ah		; _a[72] @ 4608
	.word	041230cd6h,0ee15d123h		; _a[73] @ 4672
	.word	041298aa9h,01ae865b0h		; _a[74] @ 4736
	.word	040e15eefh,00b3b67b5h		; _a[75] @ 4800
	.word	040ed7e79h,08183c36eh		; _a[76] @ 4864
	.word	04105633eh,05f865d7dh		; _a[77] @ 4928
	.word	0411326bfh,036c8853fh		; _a[78] @ 4992
	.word	04124ad32h,00ec980e8h		; _a[79] @ 5056
	.word	04125f43eh,0c2aa0522h		; _a[80] @ 5120
	.word	0411db3d4h,0cf0f1daah		; _a[81] @ 5184
	.word	0411689beh,028c4d80ch		; _a[82] @ 5248
	.word	041076d08h,090e0a84ch		; _a[83] @ 5312
	.word	0412577bfh,062055e0eh		; _a[84] @ 5376
	.word	0411a39cdh,01b8179e8h		; _a[85] @ 5440
	.word	0412b3befh,0efac710dh		; _a[86] @ 5504
	.word	0410d19ddh,0aa0dd5ach		; _a[87] @ 5568
	.word	041086339h,0415aebdfh		; _a[88] @ 5632
	.word	0411c1878h,0f8ac555eh		; _a[89] @ 5696
	.word	04116bd96h,02a353c22h		; _a[90] @ 5760
	.word	040f3c7c4h,05a908a26h		; _a[91] @ 5824
	.word	0412e4754h,0936c2d50h		; _a[92] @ 5888
	.word	04123426bh,0380614edh		; _a[93] @ 5952
	.word	0412abd5eh,023a73995h		; _a[94] @ 6016
	.word	041211d7eh,080f58cdfh		; _a[95] @ 6080
	.word	0411b2e12h,0e8e1932dh		; _a[96] @ 6144
	.word	0412228b9h,0a6f7d30bh		; _a[97] @ 6208
	.word	040f4f620h,094cf4a56h		; _a[98] @ 6272
	.word	040ff0d6eh,06e9f4fbch		; _a[99] @ 6336
	.word	041203e1dh,04aedb4a4h		; _a[100] @ 6400
	.word	04121e2c6h,0f32a355eh		; _a[101] @ 6464
	.word	0410f6359h,09083f69ah		; _a[102] @ 6528
	.word	04128d96eh,07ee9325eh		; _a[103] @ 6592
	.word	04128dc5eh,0ad5e071ch		; _a[104] @ 6656
	.word	0411b02fch,0231b65b7h		; _a[105] @ 6720
	.word	0410e86bch,0b7215c71h		; _a[106] @ 6784
	.word	0410fd030h,0fef72134h		; _a[107] @ 6848
	.word	0411b47a9h,0c94b167fh		; _a[108] @ 6912
	.word	041222bafh,0c0512c42h		; _a[109] @ 6976
	.word	0411f9324h,0a5044509h		; _a[110] @ 7040
	.word	04124ed13h,04a7c2515h		; _a[111] @ 7104
	.word	041058158h,0bebbe29ah		; _a[112] @ 7168
	.word	040ed87f3h,0a6f5a2afh		; _a[113] @ 7232
	.word	040fa6616h,09db7d69ch		; _a[114] @ 7296
	.word	0412bc170h,0b8770d7eh		; _a[115] @ 7360
	.word	041155a32h,04cf0d18fh		; _a[116] @ 7424
	.word	0411bf2d0h,0180f0557h		; _a[117] @ 7488
	.word	041240945h,01f78897fh		; _a[118] @ 7552
	.word	04115082bh,069d44490h		; _a[119] @ 7616
	.word	0412b5ab0h,0565f3af9h		; _a[120] @ 7680
	.word	0412e6a58h,0e860b7d1h		; _a[121] @ 7744
	.word	041183cbfh,0fcfe6c82h		; _a[122] @ 7808
	.word	040580f5dh,0ea2b8265h		; _a[123] @ 7872
	.word	0411545a8h,0b738609ah		; _a[124] @ 7936
	.word	0411d6d9ah,08263736dh		; _a[125] @ 8000
	.word	041032985h,0d5c34b44h		; _a[126] @ 8064
	.word	0411cedc7h,0a32d905ch		; _a[127] @ 8128
	.word	04129812dh,048bdf315h		; _a[128] @ 8192
	.word	041129a29h,038776816h		; _a[129] @ 8256
	.word	04115f77ah,036283177h		; _a[130] @ 8320
	.word	0412d6f9fh,0cab1df0bh		; _a[131] @ 8384
	.word	040f0ab74h,0dd9b3652h		; _a[132] @ 8448
	.word	0411c807fh,0eb1cb542h		; _a[133] @ 8512
	.word	040cc3746h,0358298cch		; _a[134] @ 8576
	.word	0410ea824h,0889019beh		; _a[135] @ 8640
	.word	04116058dh,013570245h		; _a[136] @ 8704
	.word	041207ebah,05f3962f8h		; _a[137] @ 8768
	.word	0412662dfh,07784a292h		; _a[138] @ 8832
	.word	04126032bh,0de42e481h		; _a[139] @ 8896
	.word	04122f0bah,0a9843584h		; _a[140] @ 8960
	.word	04125c376h,029e55f6bh		; _a[141] @ 9024
	.word	04125d212h,056059063h		; _a[142] @ 9088
	.word	04115aedeh,06f709b74h		; _a[143] @ 9152
	.word	04114828dh,0472cf95dh		; _a[144] @ 9216
	.word	041271e58h,02c63d669h		; _a[145] @ 9280
	.word	04127393ah,0a8c63503h		; _a[146] @ 9344
	.word	04125ad0eh,01bb27533h		; _a[147] @ 9408
	.word	04122c68ch,039424448h		; _a[148] @ 9472
	.word	040de77b6h,04f9350aah		; _a[149] @ 9536
	.word	0410f12b9h,056818ee1h		; _a[150] @ 9600
	.word	0412d2addh,086d34ec7h		; _a[151] @ 9664
	.word	041009132h,08800218eh		; _a[152] @ 9728
	.word	0411e8200h,0e4cb0b2ch		; _a[153] @ 9792
	.word	041065c4eh,01dc69220h		; _a[154] @ 9856
	.word	04129d164h,09e73c199h		; _a[155] @ 9920
	.word	04105e20ch,07add6678h		; _a[156] @ 9984
	.word	04125e94ch,02ca08cd3h		; _a[157] @ 10048
	.word	040fd155fh,046177136h		; _a[158] @ 10112
	.word	0412673fah,0d08bc317h		; _a[159] @ 10176
	.word	04122b1d8h,09eb862b2h		; _a[160] @ 10240
	.word	041292d49h,0ebcbdc0ch		; _a[161] @ 10304
	.word	0410cb5f4h,05ccdd93ch		; _a[162] @ 10368
	.word	041215912h,08cb62698h		; _a[163] @ 10432
	.word	0412bca10h,0375d38c0h		; _a[164] @ 10496
	.word	04121963fh,07c47c668h		; _a[165] @ 10560
	.word	041125a31h,0abfd5022h		; _a[166] @ 10624
	.word	0412abe7fh,0a8e9e93dh		; _a[167] @ 10688
	.word	04100ba0bh,099d3b0edh		; _a[168] @ 10752
	.word	04111db71h,08f901df0h		; _a[169] @ 10816
	.word	04124335eh,0db7a94f2h		; _a[170] @ 10880
	.word	0412869a2h,063604692h		; _a[171] @ 10944
	.word	0412cd115h,0275455c3h		; _a[172] @ 11008
	.word	0412bac92h,0f44a2fcfh		; _a[173] @ 11072
	.word	041112c55h,0bb38d60ah		; _a[174] @ 11136
	.word	040e9d28ch,0bb729cd6h		; _a[175] @ 11200
	.word	04121bdbfh,0e795266dh		; _a[176] @ 11264
	.word	0412cf1f6h,081c81400h		; _a[177] @ 11328
	.word	041258dd1h,055e6d084h		; _a[178] @ 11392
	.word	0412d71a7h,09ec9e8edh		; _a[179] @ 11456
	.word	0412b096bh,0887ecc8fh		; _a[180] @ 11520
	.word	0411fbf65h,024b6dbcah		; _a[181] @ 11584
	.word	040efab9fh,0985a3429h		; _a[182] @ 11648
	.word	0411b02a0h,0c486cebch		; _a[183] @ 11712
	.word	0411215f1h,09c87f603h		; _a[184] @ 11776
	.word	04114c8b2h,0bb6df902h		; _a[185] @ 11840
	.word	040f8c07fh,00bcabed6h		; _a[186] @ 11904
	.word	0412e4faeh,088fce091h		; _a[187] @ 11968
	.word	04129daddh,09732c478h		; _a[188] @ 12032
	.word	04125c370h,0782c17b6h		; _a[189] @ 12096
	.word	0410045f7h,0a624dd2fh		; _a[190] @ 12160
	.word	041261c92h,0fa3cb817h		; _a[191] @ 12224
	.word	041035079h,0f824b9f4h		; _a[192] @ 12288
	.word	041204d21h,0427dd94ah		; _a[193] @ 12352
	.word	040f5106fh,060e42b8eh		; _a[194] @ 12416
	.word	041135db2h,0a67f9e46h		; _a[195] @ 12480
	.word	0411b30a1h,09e395663h		; _a[196] @ 12544
	.word	04111d92bh,038aae445h		; _a[197] @ 12608
	.word	0411d3709h,026e8f953h		; _a[198] @ 12672
	.word	040f1a205h,0aa1130aah		; _a[199] @ 12736
	.word	04120292bh,0c7b2788eh		; _a[200] @ 12800
$C$IR_1:	.set	1608

	.global	_a
_a:	.usect	".far",1608,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\138122 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\138124 
;**	Parameter deleted: req_flags == 9;
;**	Parameter deleted: tol == 1e-08;
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
||         MVKL    .S2     0xe2308c3a,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     _output,A11
||         MVKL    .S2     0x3e45798e,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     _output,A11
||         MVKH    .S2     0xe2308c3a,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3e45798e,B7
||         MVK     .S1     0x9,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     _isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {_isequal} {0}      ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     _fcn_pass,A12
||         MVKH    .S2     0x3e45798e,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     _fcn_pass,A12
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0xe2308c3a,B6
           MVKL    .S2     0x3e45798e,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3e45798e,B7

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3e45798e,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MV      .L1     A10,A6            ; |69| 
||         MVK     .S1     0x9,A8            ; |69| 

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
;*   Local Frame Size  : 8 Args + 196 Auto + 56 Save = 260 byte               *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           STW     .D2T1   A11,*SP--(8)      ; |129| 
           STW     .D2T1   A10,*SP--(8)      ; |129| 
           STDW    .D2T2   B13:B12,*SP--     ; |129| 
           STDW    .D2T2   B11:B10,*SP--     ; |129| 
           STDW    .D2T1   A15:A14,*SP--     ; |129| 
           STDW    .D2T1   A13:A12,*SP--     ; |129| 
           STW     .D2T2   B3,*SP--(8)       ; |129| 

           MVKL    .S1     $C$SL1+0,A4
||         ADDK    .S2     -208,SP           ; |129| 

           CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {_driver_init} {0}  ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _a,A12
           MVKL    .S1     _output,A3
           MVKH    .S1     _a,A12
           MVKH    .S1     _output,A3

           MV      .L1     A12,A13
||         CALL    .S1     _log              ; |146| 
||         LDW     .D1T1   *A3,A11

           LDDW    .D1T1   *A13++,A5:A4      ; |146| 
           MVK     .S2     0xc9,B4
           NOP             1
           MV      .L1X    B4,A10
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL5,B3,0       ; |146| 
$C$RL5:    ; CALL OCCURS {_log} {0}          ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |145| 
||         STDW    .D1T1   A5:A4,*A11++      ; |146| 
||         SUB     .S1     A10,1,A10         ; |145| 

   [ A0]   B       .S2     $C$L3             ; |145| 
|| [!A0]   MVKL    .S1     _output,A3
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |146| 
|| [!A0]   ZERO    .L2     B10

   [ A0]   CALL    .S1     _log              ; |146| 
   [!A0]   MVKH    .S1     _output,A3
   [!A0]   MVK     .S1     0xc9,A10
   [!A0]   ADD     .L2X    4,A3,B4
   [!A0]   STW     .D2T2   B4,*+SP(16)
           ; BRANCHCC OCCURS {$C$L3}         ; |145| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _logdp            ; |149| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A12++,A5:A4      ; |149| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |149| 
$C$RL6:    ; CALL OCCURS {_logdp} {0}        ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(16),B4       ; |149| 
           SUB     .L1     A10,1,A0          ; |148| 
           SUB     .L1     A10,1,A10         ; |148| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |149| 
   [ A0]   BNOP    .S1     $C$L4,3           ; |148| 

           ADD     .L2     B10,B4,B4         ; |149| 
||         ADD     .S2     8,B10,B10         ; |148| 

   [ A0]   CALL    .S1     _logdp            ; |149| 
||         STDW    .D2T1   A5:A4,*B4         ; |149| 

           ; BRANCHCC OCCURS {$C$L4}         ; |148| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(16),B4
           ZERO    .L2     B10
           MVKL    .S1     _a,A10
           MVKH    .S1     _a,A10
           MVK     .S1     0xc9,A11
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(20)
||         CALL    .S1     _logdp_c          ; |152| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |152| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |152| 
$C$RL7:    ; CALL OCCURS {_logdp_c} {0}      ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(20),B4       ; |152| 
||         SUB     .L1     A11,1,A0          ; |151| 
||         SUB     .S1     A11,1,A11         ; |151| 

   [!A0]   MVK     .S1     0xfffffc01,A20
|| [!A0]   LDW     .D2T1   *+SP(20),A3

   [!A0]   MVKL    .S2     _a,B8
   [!A0]   ZERO    .L2     B9                ; |102| 
   [!A0]   MV      .L2     B9,B12            ; |108| 
           LDW     .D2T2   *B4,B4            ; |152| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |151| 
|| [!A0]   ADD     .L1     4,A3,A15

           ADD     .L2     B10,B4,B4         ; |152| 
||         ADD     .S2     8,B10,B10         ; |151| 

   [ A0]   CALL    .S1     _logdp_c          ; |152| 
||         STDW    .D2T1   A5:A4,*B4         ; |152| 

           ; BRANCHCC OCCURS {$C$L5}         ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           MVKH    .S2     _a,B8
||         MV      .L2     B9,B26            ; |108| 
||         ZERO    .D2     B29
||         ADD     .L1     1,A20,A31
||         LDW     .D1T1   *A15,A3

           MV      .L2     B12,B28           ; |55| 
||         MVK     .D2     0xffffffff,B10    ; |114| 
||         MVK     .S2     0xc9,B2

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 27

           LDDW    .D2T2   *B8++,B5:B4       ; |84| 
||         MVKL    .S2     0x3fe6a09e,B6
||         ZERO    .L1     A4
||         ZERO    .L2     B30

           MVKL    .S2     0x667f3bcd,B31
||         SET     .S1     A4,0x15,0x1d,A4
||         STW     .D2T2   B9,*+SP(44)       ; |102| 

           MVKH    .S2     0x3fe6a09e,B6

           MVKH    .S2     0x667f3bcd,B31
||         STW     .D2T2   B6,*+SP(32)       ; |97| 

           STW     .D2T2   B31,*+SP(36)      ; |97| 

           CLR     .S2     B5,20,31,B6       ; |91| 
||         LDDW    .D2T2   *+SP(32),B17:B16  ; |97| 

           EXTU    .S2     B5,1,21,B1        ; |86| 

           OR      .S1X    A4,B6,A8          ; |91| 
|| [!B1]   ZERO    .L1     A5:A4             ; |91| 
||         SET     .S2     B30,0x15,0x1d,B6

           ZERO    .L1     A8                ; |102| 
|| [ B1]   MV      .S1     A8,A5             ; |91| 
|| [ B1]   MV      .D1X    B4,A4             ; |91| 

           STW     .D2T2   B6,*+SP(40)       ; |102| 
           DADD    .L2X    0,A5:A4,B7:B6     ; |97| 
           CMPGTDP .S2     B7:B6,B17:B16,B0  ; |97| 
           ADD     .L1X    A31,B1,A21        ; |86| 

   [ B0]   ZERO    .L1     A17
|| [ B0]   MV      .L2     B9,B16            ; |99| 
|| [!B0]   ADD     .S1X    A20,B1,A21        ; |104| 
|| [!B0]   LDDW    .D2T2   *+SP(40),B17:B16  ; |102| 

   [!B0]   ZERO    .L1     A9
   [!B0]   SET     .S1     A9,0x15,0x1d,A9
   [ B0]   SET     .S1     A17,0x15,0x1d,A17
   [ B0]   MV      .L1     A17,A9            ; |98| 
   [!B0]   FSUBDP  .L2     B7:B6,B17:B16,B19:B18 ; |102| 
   [ B0]   MV      .L2X    A17,B17           ; |98| 
   [ B0]   MV      .S2X    A17,B19           ; |98| 
   [!B0]   B       .S1     $C$L7             ; |104| 

   [!B0]   FMPYDP  .M1X    A9:A8,B19:B18,A19:A18 ; |103| 
|| [!B0]   ZERO    .L1     A9

           MV      .L1X    B9,A8             ; |86| 
|| [!B0]   SET     .S1     A9,0x15,0x1d,A9

   [ B0]   MV      .L1     A8,A16            ; |98| 

   [ B0]   FSUBDP  .L1     A5:A4,A17:A16,A17:A16 ; |98| 
|| [ B0]   FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |99| 

   [!B0]   FADDDP  .L1     A9:A8,A19:A18,A17:A16 ; |103| 
           ; BRANCHCC OCCURS {$C$L7}         ; |104| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           MV      .L2     B9,B18            ; |99| 
           NOP             2

           DADD    .L2X    0,A17:A16,B7:B6   ; |98| Define a twin register
||         FADDDP  .L1X    B17:B16,A5:A4,A17:A16 ; |99| 

           FSUBDP  .L2     B7:B6,B19:B18,B19:B18 ; |98| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 91
           ZERO    .L2     B13
           SET     .S2     B13,0x1e,0x1e,B13
           RCPDP   .S1     A17:A16,A5:A4     ; |108| 
           MV      .L1X    B9,A18            ; |108| 
           FMPYDP  .M1     A17:A16,A5:A4,A9:A8 ; |108| 
           MV      .L1X    B13,A19           ; |108| 
           MVKL    .S2     0x4b67ce0f,B30
           MVKL    .S2     0xc041d580,B31
           MVKH    .S2     0x4b67ce0f,B30
           FSUBDP  .L2X    B13:B12,A9:A8,B7:B6 ; |108| 
           STW     .D2T2   B30,*+SP(52)      ; |55| 
           MVKH    .S2     0xc041d580,B31
           STW     .D2T2   B31,*+SP(48)      ; |55| 
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |108| 
           MV      .L2     B12,B6            ; |108| 
           MV      .L2     B13,B7            ; |108| 
           MVKL    .S1     0x40738083,A11
           FMPYDP  .M1     A17:A16,A5:A4,A9:A8 ; |108| 
           MVKL    .S1     0xfa15267e,A10
           MVKH    .S1     0x40738083,A11
           MVKH    .S1     0xfa15267e,A10
           FSUBDP  .L1     A19:A18,A9:A8,A9:A8 ; |108| 
           MVKL    .S1     0xc0880bfe,A13
           MVKL    .S1     0x9c0d9077,A12
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |108| 
           MVKH    .S1     0xc0880bfe,A13
           MVKH    .S1     0x9c0d9077,A12
           STW     .D2T2   B28,*+SP(60)      ; |114| 
           FMPYDP  .M1     A17:A16,A5:A4,A9:A8 ; |108| 
           MV      .L2     B13,B27           ; |55| 
           NOP             3
           FSUBDP  .L2X    B7:B6,A9:A8,B7:B6 ; |108| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B7:B6,B7:B6 ; |108| 
           NOP             3
           FMPYDP  .M2     B19:B18,B7:B6,B21:B20 ; |108| 
           LDDW    .D2T2   *+SP(48),B7:B6
           NOP             2
           FMPYDP  .M2     B21:B20,B21:B20,B17:B16 ; |108| 
           NOP             3
           FADDDP  .L2     B7:B6,B17:B16,B7:B6 ; |55| 
           NOP             2
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |55| 
           NOP             4
           FADDDP  .L1X    A11:A10,B7:B6,A5:A4 ; |55| 
           MV      .L2     B12,B6            ; |55| 
           MV      .L2     B13,B7            ; |55| 
           FMPYDP  .M1X    B17:B16,A5:A4,A5:A4 ; |55| 
           NOP             3
           FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |55| 
           NOP             2
           RCPDP   .S1     A5:A4,A9:A8       ; |55| 
           NOP             1
           FMPYDP  .M1     A9:A8,A5:A4,A19:A18 ; |55| 
           NOP             4
           FSUBDP  .L2X    B7:B6,A19:A18,B7:B6 ; |55| 
           INTDP   .L1     A21,A19:A18       ; |114| 
           NOP             1

           FMPYDP  .M2X    A9:A8,B7:B6,B23:B22 ; |55| 
||         SET     .S2     B29,0x14,0x14,B6

           STW     .D2T2   B6,*+SP(56)       ; |114| 
           LDDW    .D2T2   *+SP(56),B7:B6    ; |114| 
           NOP             1
           FMPYDP  .M2X    B23:B22,A5:A4,B25:B24 ; |55| 
           NOP             2
           CMPLTDP .S2     B5:B4,B7:B6,B0    ; |114| 
           FSUBDP  .L2     B27:B26,B25:B24,B7:B6 ; |55| 

   [ B0]   B       .S2     $C$L8             ; |114| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   MVKL    .S1     0xffefffff,A7
|| [ B0]   MVK     .L1     0xffffffff,A6     ; |114| 

   [ B0]   MVKH    .S1     0xffefffff,A7
|| [ B1]   SUB     .D2     B2,1,B2           ; |154| 
|| [ B0]   MVKL    .S2     0x7fefffff,B11

           FMPYDP  .M2     B23:B22,B7:B6,B23:B22 ; |55| 
|| [!B0]   MVKL    .S2     0xbfe94415,B7

   [!B0]   MVKL    .S2     0xb356bd29,B6
   [!B0]   MVKH    .S2     0xbfe94415,B7
   [!B0]   MVKH    .S2     0xb356bd29,B6
           ; BRANCHCC OCCURS {$C$L8}         ; |114| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 35

           FMPYDP  .M2     B7:B6,B17:B16,B7:B6 ; |114| 
||         MVKL    .S1     0x4030624a,A9
||         FMPYDP  .M1X    B23:B22,A5:A4,A5:A4 ; |114| 
||         MVKL    .S2     0x12b3b59a,B24

           MVKL    .S2     0xc05007ff,B25
||         MVKL    .S1     0x2016afed,A8

           MVKH    .S1     0x4030624a,A9
           MVKH    .S1     0x2016afed,A8
           MV      .L1X    B13,A7            ; |114| 
           FADDDP  .L2X    A9:A8,B7:B6,B7:B6 ; |114| 
           MV      .L1X    B9,A6             ; |114| 
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |114| 
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |114| 
           MVKH    .S2     0x12b3b59a,B24
           MVKH    .S2     0xc05007ff,B25
           FMPYDP  .M2X    B23:B22,A5:A4,B23:B22 ; |114| 
           FADDDP  .L2     B25:B24,B7:B6,B7:B6 ; |114| 
           MVKL    .S1     0xbf2bd010,A5
           MVKL    .S1     0x5c610ca8,A4
           FMPYDP  .M2     B7:B6,B23:B22,B7:B6 ; |114| 
           MVKH    .S1     0xbf2bd010,A5
           MVKH    .S1     0x5c610ca8,A4
           FMPYDP  .M1     A5:A4,A19:A18,A5:A4 ; |114| 
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |114| 
           MV      .L2     B26,B16           ; |114| 
           MVKL    .S2     0x3fe63000,B17
           MVKH    .S2     0x3fe63000,B17
           FMPYDP  .M2     B21:B20,B7:B6,B7:B6 ; |114| 
           FMPYDP  .M2X    B17:B16,A19:A18,B17:B16 ; |114| 
           SUB     .L2     B2,1,B2           ; |154| 
           MVKL    .S2     0x7fefffff,B11
           FADDDP  .L2     B7:B6,B21:B20,B7:B6 ; |114| 
           NOP             3
           FADDDP  .L1X    B7:B6,A5:A4,A5:A4 ; |114| 
           NOP             2
           FADDDP  .L1X    B17:B16,A5:A4,A7:A6 ; |114| 
;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 8

           MVKH    .S2     0x7fefffff,B11
|| [!B2]   ADD     .L1     4,A15,A14

           CMPGTDP .S2     B5:B4,B11:B10,B0  ; |114| 
   [ B2]   B       .S1     $C$L6             ; |154| 

   [ B0]   MVKL    .S1     0xfefa39ef,A4
|| [!B0]   DADD    .L1     0,A7:A6,A5:A4     ; |114| 

   [ B0]   MVKL    .S1     0x40862e42,A5
   [ B0]   MVKH    .S1     0xfefa39ef,A4
   [ B0]   MVKH    .S1     0x40862e42,A5

           STDW    .D1T1   A5:A4,*A3++       ; |114| 
|| [!B2]   CALL    .S1     _logdp_v          ; |157| 

           ; BRANCHCC OCCURS {$C$L6}         ; |154| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A14,B4           ; |157| 
           MVKL    .S1     _a,A4
           MVKH    .S1     _a,A4
           ADDKPC  .S2     $C$RL8,B3,0       ; |157| 
           MVK     .S1     0xc9,A6           ; |157| 
$C$RL8:    ; CALL OCCURS {_logdp_v} {0}      ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     _allequal,B3
||         MVK     .S1     0xc9,A4           ; |160| 

$C$RL9:    ; CALL OCCURS {_allequal} {0}     ; |160| 

           CALLP   .S2     _print_test_results,B3
||         MVK     .L1     0x1,A4            ; |161| 

$C$RL10:   ; CALL OCCURS {_print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           STW     .D2T1   A12,*+SP(108)     ; |108| 
           STW     .D2T1   A13,*+SP(104)     ; |108| 
           LDW     .D2T1   *+SP(52),A22      ; |108| 
           STW     .D2T1   A11,*+SP(112)     ; |108| 
           LDW     .D2T1   *+SP(56),A26      ; |55| 
           LDW     .D2T1   *+SP(36),A12

           LDW     .D2T1   *+SP(48),A23      ; |108| 
||         ZERO    .L2     B26               ; |108| 

           STW     .D2T2   B26,*+SP(100)     ; |169| 
           STW     .D2T1   A10,*+SP(116)     ; |108| 
           STW     .D2T1   A15,*+SP(24)      ; |119| 
           STW     .D2T2   B11,*+SP(192)     ; |119| 
           STW     .D2T2   B13,*+SP(136)     ; |108| 
           STW     .D2T2   B13,*+SP(128)     ; |108| 
           STW     .D2T2   B13,*+SP(96)      ; |108| 

           STW     .D2T2   B13,*+SP(88)      ; |108| 
||         MVKL    .S2     0x3fe63000,B4

           STW     .D2T2   B13,*+SP(80)      ; |108| 
||         MVKH    .S2     0x3fe63000,B4

           STW     .D2T2   B4,*+SP(168)      ; |114| 

           LDW     .D2T1   *+SP(32),A13      ; |102| 
||         ZERO    .L2     B25               ; |114| 

           STW     .D2T2   B25,*+SP(172)     ; |169| 
||         ZERO    .L1     A1                ; |116| 

           STW     .D2T1   A1,*+SP(188)      ; |169| 
||         MVKL    .S1     0xb356bd29,A24
||         ZERO    .L1     A8                ; |55| 

           STW     .D2T1   A8,*+SP(140)      ; |171| 
||         MVKL    .S1     0xbfe94415,A25
||         ZERO    .L2     B27               ; |108| 

           STW     .D2T2   B27,*+SP(84)      ; |171| 
||         MVKL    .S1     0x2016afed,A27
||         ZERO    .L2     B28               ; |108| 

           STW     .D2T2   B28,*+SP(92)      ; |171| 
||         MVKL    .S1     0x4030624a,A28
||         ZERO    .L1     A16               ; |55| 

           STW     .D2T1   A16,*+SP(132)     ; |172| 
||         MVKL    .S1     0x12b3b59a,A29
||         ZERO    .L2     B30               ; |98| 

           STW     .D2T2   B30,*+SP(68)      ; |172| 
||         MVKL    .S1     0xc05007ff,A30
||         ZERO    .L1     A19               ; |98| 

           STW     .D2T1   A19,*+SP(60)      ; |173| 
||         MVKL    .S1     0x5c610ca8,A31
||         MVK     .L2     0x6,B31

           STW     .D2T2   B31,*+SP(12)      ; |173| 
||         MVKL    .S1     0xbf2bd010,A3
||         ZERO    .L1     A18               ; |103| 

           STW     .D2T1   A18,*+SP(52)      ; |173| 
||         MVKH    .S1     0xb356bd29,A24

           STW     .D2T1   A24,*+SP(164)     ; |55| 
||         MVKH    .S1     0xbfe94415,A25

           STW     .D2T1   A25,*+SP(160)     ; |55| 
||         MVKH    .S1     0x2016afed,A27

           STW     .D2T1   A27,*+SP(156)     ; |55| 
||         MVKH    .S1     0x4030624a,A28

           STW     .D2T1   A28,*+SP(152)     ; |55| 
||         MVKH    .S1     0x12b3b59a,A29

           STW     .D2T1   A29,*+SP(148)     ; |55| 
||         MVKH    .S1     0xc05007ff,A30
||         MVKL    .S2     _a_sc,B16

           STW     .D2T1   A30,*+SP(144)     ; |55| 
||         MVKH    .S2     _a_sc,B16
||         MVKH    .S1     0x5c610ca8,A31

           STW     .D2T1   A31,*+SP(180)     ; |114| 
||         MVKH    .S1     0xbf2bd010,A3
||         MV      .L1X    B13,A11           ; |108| 
||         ZERO    .D1     A5
||         ADD     .L2     1,B11,B9

           STW     .D2T1   A3,*+SP(176)      ; |114| 
||         MV      .L1X    B16,A21
||         ZERO    .S1     A7
||         ZERO    .L2     B29               ; |103| 
||         ZERO    .D1     A4                ; |171| 
||         MV      .S2     B12,B8

           STDW    .D1T2   B9:B8,*+A21(16)   ; |170| 
||         STW     .D2T1   A26,*+SP(184)     ; |116| 
||         MV      .L1X    B16,A9            ; |172| 
||         MVKH    .S1     0xfff00000,A5
||         ZERO    .L2     B6                ; |172| 
||         ZERO    .S2     B7

           STDW    .D1T1   A5:A4,*+A9(24)    ; |171| 
||         MV      .L1X    B16,A17           ; |173| 
||         STW     .D2T2   B29,*+SP(36)      ; |172| 
||         SET     .S2     B7,0x14,0x1d,B7
||         ZERO    .L2     B5
||         ZERO    .S1     A6                ; |173| 

           STDW    .D1T2   B7:B6,*+A17(32)   ; |172| 
||         ADD     .L2     -7,B31,B26
||         STW     .D2T1   A23,*+SP(120)     ; |108| 
||         MV      .L1X    B16,A20           ; |171| 
||         MVKH    .S1     0xbff00000,A7
||         MVKL    .S2     _output,B10

           STDW    .D1T1   A7:A6,*+A20(40)   ; |173| 
||         STW     .D2T2   B26,*+SP(196)     ; |169| 
||         ZERO    .L2     B4                ; |169| 
||         MV      .L1X    B16,A2            ; |171| 
||         MVKH    .S2     0x80000000,B5

           ZERO    .L2     B9:B8             ; |168| 
||         ZERO    .L1     A9                ; |99| 
||         STDW    .D1T2   B5:B4,*+A2(8)     ; |169| 
||         STW     .D2T1   A22,*+SP(124)     ; |108| 
||         ZERO    .S1     A10               ; |55| 
||         ZERO    .S2     B12               ; |99| 

           CALL    .S1     _log              ; |175| 
||         STDW    .D1T2   B9:B8,*A21        ; |168| 
||         STW     .D2T1   A9,*+SP(76)       ; |172| 
||         SUB     .L1X    B16,8,A15
||         ZERO    .L2     B11
||         MVKH    .S2     _output,B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *++A15,A5:A4      ; |175| 
           ADDKPC  .S2     $C$RL11,B3,3      ; |175| 
$C$RL11:   ; CALL OCCURS {_log} {0}          ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D2T2   *B10,B4           ; |175| 
           NOP             4

           ADD     .L2     B11,B4,B6         ; |175| 
||         DADD    .S2X    0,A5:A4,B5:B4     ; |175| 

           STDW    .D2T2   B5:B4,*B6         ; |175| 

           CALLP   .S2     _logdp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |176| 

$C$RL12:   ; CALL OCCURS {_logdp} {0}        ; |176| 
           LDW     .D2T2   *+B10(4),B4       ; |176| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |176| 
           STDW    .D2T1   A5:A4,*B4         ; |176| 

           CALLP   .S2     _logdp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |177| 

$C$RL13:   ; CALL OCCURS {_logdp_c} {0}      ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 175
           LDW     .D2T2   *+B10(8),B4       ; |177| 
           ZERO    .L1     A31
           LDDW    .D2T2   *+SP(80),B9:B8
           MVK     .S1     0xfffffc02,A30
           LDW     .D2T2   *+SP(24),B31      ; |114| 
           ADD     .L2     B11,B4,B4         ; |177| 
           STDW    .D2T1   A5:A4,*B4         ; |177| 
           LDDW    .D1T1   *A15,A17:A16      ; |84| 
           SET     .S1     A31,0x15,0x1d,A5
           NOP             3

           CLR     .S1     A17,20,31,A3      ; |91| 
||         MV      .L1     A16,A4            ; |91| 

           OR      .L1     A5,A3,A5          ; |91| 
||         EXTU    .S1     A17,1,21,A1       ; |86| 

   [!A1]   ZERO    .L1     A5:A4             ; |94| 
           CMPGTDP .S1     A5:A4,A13:A12,A0  ; |97| 
           NOP             1

   [!A0]   LDDW    .D2T1   *+SP(40),A7:A6    ; |99| 
|| [!A0]   ZERO    .L1     A3
|| [ A0]   ZERO    .S1     A3
|| [!A0]   ZERO    .L2     B4

   [ A0]   SET     .S1     A3,0x15,0x1d,A3

   [!A0]   SET     .S1     A3,0x15,0x1d,A3
|| [ A0]   STW     .D2T1   A3,*+SP(72)       ; |99| 

   [!A0]   STW     .D2T1   A3,*+SP(48)       ; |103| 
   [ A0]   LDDW    .D2T1   *+SP(72),A7:A6    ; |103| 

   [!A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |102| 
|| [!A0]   LDDW    .D2T1   *+SP(48),A7:A6    ; |99| 

   [!A0]   SET     .S2     B4,0x15,0x1d,B4
   [!A0]   STW     .D2T2   B4,*+SP(32)       ; |103| 
   [!A0]   LDDW    .D2T2   *+SP(32),B5:B4    ; |99| 
   [ A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |99| 
   [!A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |103| 
   [ A0]   ZERO    .L2     B13
   [ A0]   SET     .S2     B13,0x15,0x1d,B13
   [ A0]   ZERO    .L1     A3
   [ A0]   FADDDP  .L2X    B13:B12,A7:A6,B7:B6 ; |99| 
   [!A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |103| 
   [ A0]   SET     .S1     A3,0x15,0x1d,A3
   [ A0]   STW     .D2T1   A3,*+SP(56)       ; |98| 
           RCPDP   .S2     B7:B6,B5:B4       ; |108| 
   [ A0]   LDDW    .D2T1   *+SP(56),A7:A6    ; |98| 
           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |108| 
           ADD     .L1     A30,A1,A3         ; |86| 
   [!A0]   SUB     .L1     A3,1,A3           ; |104| 
           NOP             1
           FSUBDP  .L2     B9:B8,B17:B16,B9:B8 ; |108| 
   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |98| 
           NOP             1
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |108| 
           LDDW    .D2T2   *+SP(88),B5:B4
           NOP             2
           FMPYDP  .M2     B7:B6,B9:B8,B17:B16 ; |108| 
           NOP             3
           FSUBDP  .L2     B5:B4,B17:B16,B5:B4 ; |108| 
           NOP             2
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |108| 
           NOP             3

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |108| 
||         LDDW    .D2T2   *+SP(96),B7:B6    ; |98| 

           NOP             4

           FSUBDP  .L2     B7:B6,B9:B8,B7:B6 ; |108| 
|| [ A0]   ZERO    .S2     B8

   [ A0]   SET     .S2     B8,0x15,0x1d,B8
   [ A0]   STW     .D2T2   B8,*+SP(64)       ; |98| 
   [ A0]   LDDW    .D2T1   *+SP(64),A7:A6
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |108| 
           LDDW    .D2T2   *+SP(192),B7:B6
           NOP             2
   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |98| 
           LDDW    .D2T1   *+SP(112),A7:A6
           CMPGTDP .S2X    A17:A16,B7:B6,B0  ; |119| 
           FMPYDP  .M1X    A5:A4,B5:B4,A19:A18 ; |108| 
           LDDW    .D2T1   *+SP(120),A5:A4
           LDW     .D2T2   *+SP(12),B7       ; |178| 
           LDDW    .D2T2   *+SP(168),B5:B4
           FMPYDP  .M1     A19:A18,A19:A18,A9:A8 ; |108| 
           LDW     .D2T2   *B31,B6           ; |178| 
           NOP             2
           FADDDP  .L1     A5:A4,A9:A8,A5:A4 ; |55| 
           SUB     .L2     B7,1,B30          ; |174| 
           SUB     .S1X    B7,1,A2           ; |174| 
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |55| 
           ADD     .L2     B11,B6,B6         ; |178| 
           ADD     .L2     8,B11,B11         ; |174| 
           STW     .D2T2   B30,*+SP(12)      ; |178| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |55| 
           LDDW    .D2T1   *+SP(104),A7:A6
           NOP             1
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |55| 
           NOP             3
           FADDDP  .L1     A7:A6,A5:A4,A7:A6 ; |55| 
           LDDW    .D2T1   *+SP(128),A5:A4
           NOP             1
           RCPDP   .S1     A7:A6,A21:A20     ; |55| 
           NOP             1
           FMPYDP  .M1     A21:A20,A7:A6,A23:A22 ; |55| 
           NOP             3
           FSUBDP  .L1     A5:A4,A23:A22,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A21:A20,A5:A4,A21:A20 ; |55| 
           LDDW    .D2T1   *+SP(136),A5:A4
           NOP             2
           FMPYDP  .M1     A21:A20,A7:A6,A23:A22 ; |55| 
           NOP             3
           FSUBDP  .L1     A5:A4,A23:A22,A5:A4 ; |55| 
           NOP             2

           FMPYDP  .M1     A21:A20,A5:A4,A21:A20 ; |55| 
||         LDDW    .D2T1   *+SP(160),A5:A4   ; |55| 

           NOP             4

           FMPYDP  .M1     A5:A4,A9:A8,A23:A22 ; |55| 
||         LDDW    .D2T1   *+SP(152),A5:A4   ; |55| 

           FMPYDP  .M1     A21:A20,A7:A6,A7:A6 ; |55| 
           NOP             3
           FADDDP  .L1     A5:A4,A23:A22,A5:A4 ; |55| 
           NOP             2

           FSUBDP  .L1     A11:A10,A7:A6,A5:A4 ; |55| 
||         FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |55| 

           NOP             2

           FMPYDP  .M1     A21:A20,A5:A4,A21:A20 ; |55| 
||         LDDW    .D2T1   *+SP(144),A5:A4   ; |55| 

           NOP             4
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |55| 
           INTDP   .L1     A3,A7:A6          ; |114| 
           NOP             1
           FMPYDP  .M1     A5:A4,A21:A20,A5:A4 ; |55| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |114| 
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |114| 
           NOP             2

           FMPYDP  .M1     A19:A18,A5:A4,A9:A8 ; |114| 
||         LDDW    .D2T1   *+SP(176),A5:A4

           NOP             4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |114| 
           FADDDP  .L1     A9:A8,A19:A18,A9:A8 ; |114| 
           NOP             2

           FADDDP  .L1     A9:A8,A5:A4,A7:A6 ; |114| 
||         LDDW    .D2T1   *+SP(184),A5:A4

           NOP             3
           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |114| 
           CMPLTDP .S1     A17:A16,A5:A4,A0  ; |116| 
           NOP             1

   [ A0]   MVKL    .S2     0xffefffff,B5
|| [ A0]   MVK     .L2     0xffffffff,B4     ; |117| 

   [ A2]   B       .S1     $C$L9             ; |174| 
|| [ A0]   MVKH    .S2     0xffefffff,B5

   [ B0]   MVKL    .S2     0x40862e42,B5
   [ B0]   MVKL    .S2     0xfefa39ef,B4
   [ B0]   MVKH    .S2     0x40862e42,B5
   [ B0]   MVKH    .S2     0xfefa39ef,B4

   [ A2]   CALL    .S1     _log              ; |175| 
||         STDW    .D2T2   B5:B4,*B6         ; |178| 

           ; BRANCHCC OCCURS {$C$L9}         ; |174| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     _logdp_v          ; |180| 
           LDW     .D1T2   *A14,B4           ; |180| 
           MVKL    .S1     _a_sc,A4
           MVKH    .S1     _a_sc,A4
           ADDKPC  .S2     $C$RL14,B3,0      ; |180| 
           MVK     .L1     0x6,A6            ; |180| 
$C$RL14:   ; CALL OCCURS {_logdp_v} {0}      ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     _allequal,B3
||         MVK     .L1     0x6,A4            ; |183| 

$C$RL15:   ; CALL OCCURS {_allequal} {0}     ; |183| 

           CALLP   .S2     _print_test_results,B3
||         MVK     .L1     0x3,A4            ; |184| 

$C$RL16:   ; CALL OCCURS {_print_test_results} {0}  ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T1   *+SP(124),A19     ; |108| 
           LDW     .D2T1   *+SP(120),A20     ; |108| 
           LDW     .D2T1   *+SP(164),A25     ; |55| 
           LDW     .D2T1   *+SP(160),A26     ; |55| 
           LDW     .D2T1   *+SP(40),A18      ; |103| 
           LDW     .D2T1   *+SP(108),A23     ; |108| 
           LDW     .D2T1   *+SP(104),A24     ; |55| 
           LDW     .D2T1   *+SP(148),A29     ; |55| 

           LDW     .D2T1   *+SP(144),A30     ; |55| 
||         MVK     .L1     0xffffffff,A17    ; |119| 

           STW     .D2T1   A17,*+SP(196)     ; |187| 
           LDW     .D2T1   *+SP(116),A21     ; |108| 
           LDW     .D2T1   *+SP(112),A22     ; |108| 
           LDW     .D2T1   *+SP(156),A27     ; |55| 
           LDW     .D2T1   *+SP(152),A28     ; |55| 

           LDW     .D2T2   *+SP(184),B5      ; |193| 
||         MV      .L2     B12,B4            ; |108| 

           STW     .D2T2   B4,*+SP(172)      ; |187| 
||         MV      .L1     A10,A16           ; |119| 

           STW     .D2T1   A16,*+SP(188)     ; |187| 
||         MV      .L2     B12,B31           ; |108| 

           STW     .D2T2   B31,*+SP(92)      ; |187| 
||         MV      .L2X    A11,B13           ; |108| 

           STW     .D2T2   B13,*+SP(128)     ; |108| 
           STW     .D2T2   B13,*+SP(88)      ; |108| 
           STW     .D2T2   B13,*+SP(80)      ; |108| 

           STW     .D2T2   B13,*+SP(72)      ; |108| 
||         MV      .L2     B12,B8            ; |108| 

           STW     .D2T2   B8,*+SP(84)
||         MVK     .S2     0x777,B7

           STW     .D2T2   B7,*+SP(12)
||         MV      .L1     A10,A4            ; |102| 

           STW     .D2T1   A4,*+SP(124)

           STW     .D2T2   B13,*+SP(120)     ; |108| 
||         MVKL    .S1     0xcccccccd,A31
||         MV      .L1     A10,A5            ; |119| 

           STW     .D2T1   A5,*+SP(164)      ; |187| 
||         MVKL    .S1     0xc000cccc,A3

           STW     .D2T2   B13,*+SP(160)     ; |108| 
||         MVKH    .S1     0xcccccccd,A31

           STW     .D2T1   A31,*+SP(204)     ; |193| 
||         MVKH    .S1     0xc000cccc,A3

           STW     .D2T1   A3,*+SP(200)      ; |193| 
           STW     .D2T1   A18,*+SP(32)      ; |102| 
           STW     .D2T1   A23,*+SP(100)     ; |108| 
           STW     .D2T1   A24,*+SP(96)      ; |108| 
           STW     .D2T1   A29,*+SP(140)     ; |55| 

           STW     .D2T1   A30,*+SP(136)     ; |55| 
||         MV      .L1     A10,A17           ; |102| 

           STW     .D2T1   A17,*+SP(132)
           STW     .D2T1   A19,*+SP(116)     ; |108| 
           STW     .D2T1   A20,*+SP(112)     ; |108| 
           STW     .D2T1   A21,*+SP(108)     ; |108| 
           STW     .D2T1   A22,*+SP(104)     ; |108| 
           STW     .D2T1   A25,*+SP(156)     ; |55| 

           STW     .D2T1   A26,*+SP(152)     ; |55| 
||         MVKL    .S2     _a_ext,B6

           STW     .D2T1   A27,*+SP(148)     ; |55| 
||         MVKH    .S2     _a_ext,B6

           STW     .D2T1   A28,*+SP(144)     ; |55| 

           STDW    .D2T2   B5:B4,*B6         ; |187| 
||         MV      .L1X    B6,A15            ; |187| 

           CALL    .S1     _log              ; |189| 
||         LDDW    .D1T2   *A15,B5:B4        ; |189| 

           LDW     .D2T2   *+SP(24),B11      ; |193| 
||         MV      .L2     B12,B10           ; |108| 

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
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL17,B3,2      ; |189| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |189| 
$C$RL17:   ; CALL OCCURS {_log} {0}          ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |189| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |189| 
           STDW    .D2T1   A5:A4,*B4         ; |189| 

           CALLP   .S2     _logdp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |190| 

$C$RL18:   ; CALL OCCURS {_logdp} {0}        ; |190| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T1   *+B4(4),A3        ; |190| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |190| 
           NOP             3
           ADD     .L1X    B10,A3,A3         ; |190| 
           STDW    .D1T2   B5:B4,*A3         ; |190| 

           CALLP   .S2     _logdp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |191| 

$C$RL19:   ; CALL OCCURS {_logdp_c} {0}      ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 193
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |191| 
           ZERO    .L1     A31
           LDDW    .D2T2   *+SP(72),B9:B8
           LDDW    .D2T1   *+SP(104),A9:A8
           MVK     .S1     0xfffffc02,A30
           ADD     .L2     B10,B4,B4         ; |191| 
           STDW    .D2T1   A5:A4,*B4         ; |191| 
           LDDW    .D1T1   *A15,A17:A16      ; |84| 
           SET     .S1     A31,0x15,0x1d,A5
           LDW     .D2T2   *B11,B31          ; |192| 
           NOP             2

           CLR     .S1     A17,20,31,A3      ; |91| 
||         MV      .L1     A16,A4            ; |91| 

           OR      .L1     A5,A3,A5          ; |91| 
||         EXTU    .S1     A17,1,21,A1       ; |86| 

   [!A1]   ZERO    .L1     A5:A4             ; |94| 
           CMPGTDP .S1     A5:A4,A13:A12,A0  ; |97| 
           NOP             1

   [!A0]   LDDW    .D2T1   *+SP(32),A7:A6    ; |99| 
|| [!A0]   ZERO    .L1     A3
|| [!A0]   ZERO    .L2     B4
|| [ A0]   ZERO    .S2     B4
|| [ A0]   ZERO    .S1     A11

   [!A0]   SET     .S1     A3,0x15,0x1d,A3
|| [ A0]   SET     .S2     B4,0x15,0x1d,B4

   [!A0]   SET     .S2     B4,0x15,0x1d,B4
|| [ A0]   SET     .S1     A11,0x15,0x1d,A11

   [!A0]   STW     .D2T1   A3,*+SP(48)       ; |103| 
   [ A0]   FMPYDP  .M1     A11:A10,A5:A4,A7:A6 ; |99| 

   [!A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |102| 
|| [!A0]   LDDW    .D2T1   *+SP(48),A7:A6    ; |99| 

   [ A0]   STW     .D2T2   B4,*+SP(64)       ; |99| 
   [!A0]   STW     .D2T2   B4,*+SP(40)       ; |103| 
   [ A0]   LDDW    .D2T2   *+SP(64),B5:B4    ; |103| 
   [!A0]   LDDW    .D2T2   *+SP(40),B5:B4    ; |99| 
   [!A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |103| 
   [ A0]   ZERO    .L2     B13
   [ A0]   SET     .S2     B13,0x15,0x1d,B13
   [ A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |99| 
           ADD     .L1     A30,A1,A3         ; |86| 
   [!A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |103| 
   [!A0]   SUB     .L1     A3,1,A3           ; |104| 
           NOP             1
           RCPDP   .S2     B7:B6,B5:B4       ; |108| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |108| 
           NOP             3
           FSUBDP  .L2     B9:B8,B17:B16,B9:B8 ; |108| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |108| 
           LDDW    .D2T2   *+SP(80),B5:B4
           NOP             2
           FMPYDP  .M2     B7:B6,B9:B8,B17:B16 ; |108| 
           NOP             3
           FSUBDP  .L2     B5:B4,B17:B16,B5:B4 ; |108| 
           NOP             2
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |108| 
           NOP             3

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |108| 
|| [ A0]   ZERO    .L2     B6

   [ A0]   SET     .S2     B6,0x15,0x1d,B6
   [ A0]   STW     .D2T2   B6,*+SP(56)       ; |98| 
           LDDW    .D2T2   *+SP(88),B7:B6    ; |98| 
   [ A0]   LDDW    .D2T1   *+SP(56),A7:A6    ; |98| 
           NOP             3
           FSUBDP  .L2     B7:B6,B9:B8,B7:B6 ; |108| 
   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |98| 
           LDDW    .D2T1   *+SP(112),A7:A6
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |108| 
   [ A0]   FSUBDP  .L1X    A5:A4,B13:B12,A5:A4 ; |98| 
           ADD     .L2     B10,B31,B6        ; |192| 
           ADD     .L2     8,B10,B10         ; |188| 
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A21:A20 ; |108| 
           LDDW    .D2T2   *+SP(168),B5:B4
           NOP             2
           FMPYDP  .M1     A21:A20,A21:A20,A5:A4 ; |108| 
           NOP             3
           FADDDP  .L1     A7:A6,A5:A4,A7:A6 ; |55| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |55| 
           NOP             3
           FADDDP  .L1     A9:A8,A7:A6,A7:A6 ; |55| 
           LDDW    .D2T1   *+SP(96),A9:A8
           NOP             1
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |55| 
           NOP             3
           FADDDP  .L1     A9:A8,A7:A6,A19:A18 ; |55| 
           LDDW    .D2T1   *+SP(120),A9:A8
           NOP             1
           RCPDP   .S1     A19:A18,A7:A6     ; |55| 
           NOP             1
           FMPYDP  .M1     A7:A6,A19:A18,A23:A22 ; |55| 
           NOP             3
           FSUBDP  .L1     A9:A8,A23:A22,A9:A8 ; |55| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |55| 
           LDDW    .D2T1   *+SP(128),A7:A6
           NOP             2
           FMPYDP  .M1     A9:A8,A19:A18,A23:A22 ; |55| 
           NOP             3
           FSUBDP  .L1     A7:A6,A23:A22,A7:A6 ; |55| 
           NOP             2

           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |55| 
||         LDDW    .D2T1   *+SP(152),A7:A6   ; |55| 

           NOP             4

           FMPYDP  .M1     A7:A6,A5:A4,A23:A22 ; |55| 
||         LDDW    .D2T1   *+SP(144),A7:A6   ; |55| 

           FMPYDP  .M1     A9:A8,A19:A18,A19:A18 ; |55| 
           NOP             3

           FADDDP  .L1     A7:A6,A23:A22,A7:A6 ; |55| 
||         LDDW    .D2T1   *+SP(160),A23:A22

           NOP             4

           FSUBDP  .L1     A23:A22,A19:A18,A7:A6 ; |55| 
||         FMPYDP  .M1     A5:A4,A7:A6,A19:A18 ; |55| 

           NOP             2

           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |55| 
||         LDDW    .D2T1   *+SP(136),A7:A6   ; |55| 

           NOP             4
           FADDDP  .L1     A7:A6,A19:A18,A7:A6 ; |55| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |55| 
           NOP             3
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |114| 
           INTDP   .L1     A3,A7:A6          ; |114| 
           NOP             2

           FMPYDP  .M1     A21:A20,A5:A4,A9:A8 ; |114| 
||         LDDW    .D2T1   *+SP(176),A5:A4

           NOP             4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |114| 
           FADDDP  .L1     A9:A8,A21:A20,A9:A8 ; |114| 
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |114| 
           LDDW    .D2T1   *+SP(184),A7:A6
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |114| 
           NOP             3

           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |114| 
||         LDDW    .D2T1   *+SP(192),A5:A4   ; |114| 

           CMPLTDP .S1     A17:A16,A7:A6,A0  ; |116| 
           NOP             1

   [ A0]   MVKL    .S2     0xffefffff,B5
|| [ A0]   MVK     .L2     0xffffffff,B4     ; |117| 

   [ A0]   MVKH    .S2     0xffefffff,B5
           CMPGTDP .S1     A17:A16,A5:A4,A1  ; |119| 
           LDDW    .D2T1   *+SP(200),A5:A4
   [ A1]   MVKL    .S2     0xfefa39ef,B4
   [ A1]   MVKL    .S2     0x40862e42,B5
   [ A1]   MVKH    .S2     0xfefa39ef,B4
   [ A1]   MVKH    .S2     0x40862e42,B5
           STDW    .D2T2   B5:B4,*B6         ; |192| 

           LDDW    .D1T1   *A15,A7:A6        ; |193| 
||         LDW     .D2T2   *+SP(12),B4

           NOP             4

           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |193| 
||         SUB     .L1X    B4,1,A0           ; |188| 
||         SUB     .L2     B4,1,B4           ; |188| 

   [ A0]   BNOP    .S1     $C$L10,1          ; |188| 
|| [!A0]   MVKL    .S2     _output,B11

   [!A0]   MVKH    .S2     _output,B11

           STDW    .D1T1   A5:A4,*++A15      ; |193| 
||         STW     .D2T2   B4,*+SP(12)       ; |193| 
|| [!A0]   MVKL    .S1     _a_ext,A4

   [ A0]   CALL    .S1     _log              ; |189| 
|| [ A0]   LDDW    .D1T2   *A15,B5:B4        ; |189| 

   [!A0]   CALL    .S1     _logdp_v          ; |195| 
|| [!A0]   LDW     .D2T2   *+B11(16),B4      ; |195| 

           ; BRANCHCC OCCURS {$C$L10}        ; |188| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           MVKH    .S1     _a_ext,A4
           MVK     .S1     0x777,A6          ; |195| 
           ADDKPC  .S2     $C$RL20,B3,2      ; |195| 
$C$RL20:   ; CALL OCCURS {_logdp_v} {0}      ; |195| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL21:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B10
           MVKL    .S2     0x3e45798e,B7
           MVKH    .S2     _fcn_pass,B10
           MVKL    .S2     0xe2308c3a,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3e45798e,B7

           STW     .D2T1   A4,*+B10(4)       ; |66| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL22:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         MVKH    .S2     0x3e45798e,B7

           MV      .L2     B11,B5            ; |67| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL23:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           MV      .L1     A14,A5            ; |68| 
||         MV      .L2     B11,B4            ; |68| 
||         STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A5,B4            ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL24:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2     4,B10,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           STW     .D2T2   B4,*+SP(24)
           ADD     .L2     8,B10,B4
           STW     .D2T2   B4,*+SP(28)       ; |69| 

   [!B0]   MVKL    .S1     _all_pass,A3
|| [!B0]   B       .S2     $C$L11            ; |72| 
|| [!B0]   MV      .L1     A10,A4
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     _print_test_results ; |199| 
|| [!B0]   MVKH    .S1     _all_pass,A3
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [!B0]   MV      .L1     A10,A0            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   MV      .L1     A10,A4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |199| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |199| 
||         ADDKPC  .S2     $C$RL25,B3,0      ; |199| 

$C$RL25:   ; CALL OCCURS {_print_test_results} {0}  ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVKL    .S1     _cycle_counts+24,A3

           MVKH    .S1     _cycle_counts+24,A3
||         MV      .L2     B12,B11           ; |114| 
||         MV      .S2     B12,B10           ; |114| 
||         MV      .D2     B12,B4            ; |114| 

           STDW    .D1T2   B11:B10,*A3       ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           STDW    .D1T2   B5:B4,*A3         ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 
||         MVKL    .S1     _t_offset,A3

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKL    .S2     _input,B4
||         MVKH    .S1     _t_offset,A3

           STDW    .D1T2   B7:B6,*A3         ; |117| 
||         MVKH    .S2     _input,B4
||         CALL    .S1     _gimme_random     ; |209| 

           LDW     .D2T2   *B4,B12           ; |209| 
           ZERO    .L2     B5

           MVKL    .S1     0x412e8482,A5
||         MVK     .S2     0x80,B31
||         MV      .L2     B10,B13           ; |117| 

           MV      .L2     B10,B4            ; |209| 
||         MVKH    .S2     0xbff00000,B5
||         STW     .D2T2   B31,*+SP(12)      ; |117| 
||         MVKH    .S1     0x412e8482,A5
||         MV      .L1     A10,A4            ; |209| 

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
           ADDKPC  .S2     $C$RL26,B3,0      ; |209| 
$C$RL26:   ; CALL OCCURS {_gimme_random} {0}  ; |209| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 184
           ADD     .L2     B12,B13,B4        ; |209| 

           STDW    .D2T1   A5:A4,*B4         ; |209| 
||         MVC     .S2     TSCL,B16          ; |122| 

           MVC     .S2     TSCH,B17          ; |122| 

           ADD     .L2     B12,B13,B4        ; |93| 
||         ZERO    .L1     A3
||         CLR     .S1     A5,20,31,A16      ; |91| 
||         MV      .S2     B10,B8            ; |103| 
||         MV      .D2     B10,B6            ; |103| 
||         ZERO    .D1     A31

           LDDW    .D2T1   *B4,A7:A6         ; |93| 
||         SET     .S1     A3,0x15,0x1d,A3
||         MV      .L2     B10,B4            ; |99| 
||         ZERO    .S2     B19
||         ZERO    .L1     A30
||         ZERO    .D1     A29

           MVKL    .S1     0x667f3bcd,A8
||         MV      .L1     A3,A11            ; |97| 
||         SET     .S2     B19,0x1e,0x1e,B19
||         MV      .L2     B10,B18           ; |108| 
||         ZERO    .D1     A26

           MVKL    .S1     0x3fe6a09e,A9
||         MVKL    .S2     _output+12,B31

           MVKH    .S1     0x667f3bcd,A8
||         MVKH    .S2     _output+12,B31

           MVKH    .S1     0x3fe6a09e,A9

           MV      .L1     A4,A6             ; |91| 
||         EXTU    .S1     A7,1,21,A0        ; |93| 
||         OR      .D1     A3,A16,A7         ; |91| 

   [!A0]   ZERO    .L1     A7:A6             ; |94| 
||         MVKL    .S1     0x40738083,A19

           CMPGTDP .S1     A7:A6,A9:A8,A0    ; |97| 
           MV      .L1     A10,A8            ; |102| 

   [ A0]   MV      .D1     A3,A9             ; |97| 
|| [!A0]   MV      .L2X    A3,B5             ; |97| 
||         MVKL    .S1     0xfa15267e,A18
|| [!A0]   FSUBDP  .L1     A7:A6,A11:A10,A7:A6 ; |102| 

   [ A0]   FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |99| 
|| [ A0]   MV      .L2X    A3,B9             ; |102| 
||         MVKH    .S1     0x40738083,A19

   [!A0]   MV      .L2X    A3,B7             ; |103| 
||         MVKH    .S1     0xfa15267e,A18

           MVK     .S1     0xfffffc02,A27

   [!A0]   FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |103| 
||         EXTU    .S1     A5,1,21,A28       ; |86| 

           MVKL    .S1     _t_start,A15

   [ A0]   FADDDP  .L2X    B9:B8,A9:A8,B5:B4 ; |99| 
||         SET     .S1     A31,0x1e,0x1e,A9
||         MV      .L1     A10,A8            ; |108| 

           MVKH    .S1     _t_start,A15

   [!A0]   FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |103| 
||         STDW    .D1T2   B17:B16,*A15

           NOP             2
           RCPDP   .S2     B5:B4,B7:B6       ; |108| 
           NOP             1
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |108| 
           NOP             4
           FSUBDP  .L1X    A9:A8,B9:B8,A9:A8 ; |108| 
           NOP             3

           FMPYDP  .M2X    B7:B6,A9:A8,B7:B6 ; |108| 
||         MV      .L1X    B19,A9            ; |108| 
||         MV      .S1     A10,A8            ; |98| 

           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |108| 
           NOP             3
           FSUBDP  .L2     B19:B18,B9:B8,B9:B8 ; |108| 
           NOP             2

           FMPYDP  .M2     B7:B6,B9:B8,B7:B6 ; |108| 
|| [ A0]   MV      .L2X    A3,B9             ; |108| 
||         MV      .S2     B18,B8            ; |108| 
||         ADD     .L1     A27,A28,A3        ; |86| 

   [!A0]   SUB     .L1     A3,1,A3           ; |104| 
   [ A0]   FSUBDP  .L1X    A7:A6,B9:B8,A7:A6 ; |98| 
           NOP             1
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |108| 
           NOP             4

           FSUBDP  .L1X    A9:A8,B5:B4,A17:A16 ; |108| 
|| [ A0]   MV      .S1     A11,A9            ; |108| 
||         MVKL    .S2     0xc041d580,B5

   [ A0]   FSUBDP  .L1     A7:A6,A9:A8,A7:A6 ; |98| 
||         MVKL    .S2     0x4b67ce0f,B4

           MVKH    .S2     0xc041d580,B5

           FMPYDP  .M1X    B7:B6,A17:A16,A17:A16 ; |108| 
||         MVKH    .S2     0x4b67ce0f,B4

           NOP             3
           FMPYDP  .M1     A7:A6,A17:A16,A9:A8 ; |108| 
           NOP             3
           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |108| 
           NOP             3

           FADDDP  .L1X    B5:B4,A7:A6,A17:A16 ; |55| 
||         MVKL    .S2     0xc0880bfe,B5

           MVKL    .S2     0x9c0d9077,B4
           MVKH    .S2     0xc0880bfe,B5

           FMPYDP  .M1     A7:A6,A17:A16,A17:A16 ; |55| 
||         MVKH    .S2     0x9c0d9077,B4

           NOP             3
           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |55| 
           NOP             2
           FMPYDP  .M1     A7:A6,A17:A16,A17:A16 ; |55| 
           NOP             4

           FADDDP  .L2X    B5:B4,A17:A16,B5:B4 ; |55| 
||         MV      .L1X    B19,A17           ; |55| 
||         MV      .S1     A10,A16           ; |55| 

           NOP             2
           RCPDP   .S2     B5:B4,B7:B6       ; |55| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |55| 
           NOP             4

           FSUBDP  .L1X    A17:A16,B9:B8,A17:A16 ; |55| 
||         MVKL    .S2     0xbfe94415,B9

           MVKL    .S2     0xb356bd29,B8
           MVKH    .S2     0xbfe94415,B9
           MVKH    .S2     0xb356bd29,B8

           FMPYDP  .M2X    B7:B6,A17:A16,B19:B18 ; |55| 
||         SET     .S1     A30,0x1e,0x1e,A17
||         MV      .L1     A10,A16           ; |55| 

           FMPYDP  .M2X    B9:B8,A7:A6,B9:B8 ; |55| 
           NOP             2
           FMPYDP  .M2     B19:B18,B5:B4,B7:B6 ; |55| 
           NOP             4
           FSUBDP  .L1X    A17:A16,B7:B6,A17:A16 ; |55| 
           NOP             3

           FMPYDP  .M2X    B19:B18,A17:A16,B7:B6 ; |55| 
||         MVKL    .S1     0x2016afed,A16

           MVKL    .S1     0x4030624a,A17
           MVKH    .S1     0x2016afed,A16
           MVKH    .S1     0x4030624a,A17

           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |55| 
||         FADDDP  .L1X    A17:A16,B9:B8,A19:A18 ; |55| 
||         SET     .S1     A29,0x1e,0x1e,A17
||         MV      .D1     A10,A16           ; |55| 
||         MVKL    .S2     0x12b3b59a,B8

           MVKL    .S2     0xc05007ff,B9
           MVKH    .S2     0x12b3b59a,B8

           FMPYDP  .M1     A7:A6,A19:A18,A19:A18 ; |55| 
||         MVKH    .S2     0xc05007ff,B9

           NOP             1
           FSUBDP  .L1X    A17:A16,B5:B4,A17:A16 ; |55| 
           NOP             3
           FMPYDP  .M2X    B7:B6,A17:A16,B5:B4 ; |55| 

           FADDDP  .L2X    B9:B8,A19:A18,B7:B6 ; |55| 
||         INTDP   .L1     A3,A19:A18        ; |114| 

           NOP             2

           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |55| 
||         LDW     .D2T2   *B31,B6           ; |213| 

           NOP             4

           FMPYDP  .M1X    A7:A6,B5:B4,A17:A16 ; |114| 
||         MVKL    .S1     0xbf2bd010,A7
||         MVKL    .S2     0x3fe63000,B5
||         MV      .L2     B10,B4            ; |116| 
||         ADD     .D2     B13,B6,B6         ; |213| 

           MVKL    .S1     0x5c610ca8,A6
||         MVKH    .S2     0x3fe63000,B5

           MVKH    .S1     0xbf2bd010,A7
||         FMPYDP  .M2X    B5:B4,A19:A18,B5:B4 ; |114| 

           MVKH    .S1     0x5c610ca8,A6
           FMPYDP  .M1     A9:A8,A17:A16,A21:A20 ; |114| 
           FMPYDP  .M1     A7:A6,A19:A18,A17:A16 ; |114| 
           NOP             2

           FADDDP  .L1     A21:A20,A9:A8,A7:A6 ; |114| 
||         SET     .S1     A26,0x14,0x14,A9
||         MV      .D1     A10,A8            ; |114| 

           CMPLTDP .S1     A5:A4,A9:A8,A1    ; |116| 
           NOP             1

           FADDDP  .L1     A7:A6,A17:A16,A17:A16 ; |114| 
||         MVKL    .S1     0x7fefffff,A7
||         MVK     .D1     0xffffffff,A6     ; |119| 

           MVKH    .S1     0x7fefffff,A7
           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |119| 
           NOP             1
           FADDDP  .L2X    B5:B4,A17:A16,B5:B4 ; |114| 
           NOP             2

   [ A1]   MVKL    .S2     0xffefffff,B5
|| [ A1]   MV      .L2X    A6,B4             ; |120| 

   [ A1]   MVKH    .S2     0xffefffff,B5
   [ A0]   MVKL    .S2     0x40862e42,B5
   [ A0]   MVKL    .S2     0xfefa39ef,B4
   [ A0]   MVKH    .S2     0x40862e42,B5
   [ A0]   MVKH    .S2     0xfefa39ef,B4

           STDW    .D2T2   B5:B4,*B6         ; |213| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S2     _t_offset,B4
||         MVKL    .S1     _t_stop,A13
||         ADD     .L2     8,B13,B13         ; |207| 

           MVKH    .S2     _t_offset,B4
||         MVKL    .S1     _cycle_counts+24,A12

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
||         MVKL    .S2     _cycle_counts+24,B30
||         MVKH    .S1     _t_stop,A13

           MVKH    .S2     _cycle_counts+24,B30
||         MVKH    .S1     _cycle_counts+24,A12
||         STDW    .D1T2   B9:B8,*A13        ; |128| 

           LDDW    .D2T2   *B30,B19:B18      ; |130| 
           NOP             2
           ADDU    .L2     B6,B16,B5:B4      ; |130| 

           ADD     .S2     B5,B7,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .L2     B6,B17,B6         ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           ADDU    .L2     B18,B4,B7:B6      ; |130| 
||         SUB     .S2     B9,B6,B4          ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B7,B19,B4         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         LDW     .D2T2   *+SP(12),B4       ; |128| 

           STDW    .D1T2   B7:B6,*A12        ; |130| 
           NOP             3

           SUB     .L1X    B4,1,A0           ; |207| 
||         SUB     .L2     B4,1,B4           ; |207| 

           STW     .D2T2   B4,*+SP(12)       ; |130| 
||         MVKL    .S2     _input,B4
|| [ A0]   ZERO    .L2     B5
|| [ A0]   MV      .L1     A10,A4            ; |209| 
|| [ A0]   B       .S1     $C$L12            ; |207| 
|| [!A0]   LDDW    .D1T1   *A12,A5:A4        ; |135| 

   [ A0]   CALL    .S1     _gimme_random     ; |209| 
||         MVKH    .S2     _input,B4

   [ A0]   LDW     .D2T2   *B4,B12           ; |209| 
|| [!A0]   CALL    .S2     __fltllif         ; |135| 
|| [ A0]   MVKL    .S1     0x412e8482,A5
|| [ A0]   MV      .L2     B10,B4            ; |209| 

   [ A0]   MVKH    .S1     0x412e8482,A5
|| [ A0]   MVKH    .S2     0xbff00000,B5

           NOP             2
           ; BRANCHCC OCCURS {$C$L12}        ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL27,B3,1      ; |135| 
$C$RL27:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL28:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MV      .L2X    A12,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           SUBAW   .D2     B4,6,B13
||         MV      .L2     B10,B5            ; |114| 

           STDW    .D2T2   B11:B10,*B13      ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 

           SUBU    .L2     B5,B8,B7:B6       ; |117| 
||         MVKL    .S2     _t_offset,B31

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B4,B9,B4          ; |117| 
||         MVKL    .S1     _output,A3

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKH    .S2     _t_offset,B31
||         MVKH    .S1     _output,A3

           STDW    .D2T2   B7:B6,*B31        ; |117| 
||         MV      .L1X    B12,A10
||         CALL    .S1     _log              ; |221| 
||         LDW     .D1T1   *A3,A12

           LDDW    .D1T1   *A10++,A5:A4      ; |221| 
           MVK     .S2     0x80,B12
           NOP             2
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL29,B3,0      ; |221| 
$C$RL29:   ; CALL OCCURS {_log} {0}          ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1X    B12,1,A0          ; |220| 
||         STDW    .D1T1   A5:A4,*A12++      ; |221| 

   [ A0]   B       .S1     $C$L13            ; |220| 
   [ A0]   CALL    .S1     _log              ; |221| 
   [ A0]   LDDW    .D1T1   *A10++,A5:A4      ; |221| 
           SUB     .L2     B12,1,B12         ; |220| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L13}        ; |220| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S2     _t_offset,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           MVKH    .S2     _t_offset,B4
           LDDW    .D2T2   *B4,B5:B4         ; |130| 
           LDDW    .D2T2   *B13,B9:B8        ; |130| 
           NOP             3
           ADDU    .L1X    B4,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B5,A3          ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B6,A6,B5:B4       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B5,24,24,B16      ; |130| 
||         ADDU    .L2     B8,B4,B5:B4       ; |130| 

           SUB     .L2X    B7,A3,B17         ; |130| 
||         MV      .S2     B4,B8             ; |130| 
||         ADD     .D2     B5,B9,B4          ; |130| 

           ADD     .L2     B17,B16,B5        ; |130| 

           ADD     .L2     B4,B5,B9          ; |130| 
||         MV      .S2X    A13,B4            ; |130| 

           STDW    .D2T2   B7:B6,*B4         ; |128| 

           DADD    .L1X    0,B9:B8,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL30,B3,0      ; |130| 

$C$RL30:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A10           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL31:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           MV      .L2     B10,B4            ; |114| 
||         STDW    .D2T2   B11:B10,*+B13(8)  ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A5:A4,*B13        ; |130| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B9:B8,*A15        ; |116| 

           MVC     .S2     TSCH,B6           ; |117| 

           SUBU    .L2     B4,B8,B5:B4       ; |117| 
||         MVKL    .S2     _t_offset,B30

           EXT     .S2     B5,24,24,B7       ; |117| 

           MVK     .S2     0x80,B4
||         MV      .L2     B4,B6             ; |117| 
||         SUB     .D2     B6,B9,B31         ; |117| 

           ADD     .L2     B31,B7,B7         ; |117| 
||         MVKH    .S2     _t_offset,B30
||         LDW     .D2T2   *+SP(16),B12      ; |117| 
||         MVKL    .S1     _input,A12

           STDW    .D2T2   B7:B6,*B30        ; |117| 
||         MV      .L1X    B4,A10            ; |117| 
||         MVKH    .S1     _input,A12
||         MV      .D1     A10,A13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A12,A3           ; |229| 
           NOP             4

           ADD     .L1     A13,A3,A3         ; |229| 
||         CALL    .S1     _logdp            ; |229| 

           LDDW    .D1T1   *A3,A5:A4         ; |229| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |229| 
$C$RL32:   ; CALL OCCURS {_logdp} {0}        ; |229| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |229| 
||         SUB     .L1     A10,1,A0          ; |228| 
||         SUB     .S1     A10,1,A10         ; |228| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |228| 

           ADD     .L1X    A13,B4,A3         ; |229| 
||         ADD     .S1     8,A13,A13         ; |228| 

           STDW    .D1T1   A5:A4,*A3         ; |229| 
           ; BRANCHCC OCCURS {$C$L14}        ; |228| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S2     _t_offset,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           MVKH    .S2     _t_offset,B4
           LDDW    .D2T2   *B4,B5:B4         ; |130| 
           MV      .L2     B13,B12           ; |130| 
           LDDW    .D2T2   *+B12(8),B7:B6    ; |130| 
           NOP             2
           ADDU    .L1X    B4,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B5,A4          ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B5,24,24,B16      ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 

           SUB     .L2X    B9,A3,B17         ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         ADD     .D2     B5,B7,B4          ; |130| 

           ADD     .L2     B17,B16,B5        ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     _t_stop,B4

           MVKH    .S2     _t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL33,B3,0      ; |130| 

$C$RL33:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A10           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           STDW    .D2T2   B11:B10,*+B12(16) ; |114| 

           ADDAD   .D2     B12,1,B13
||         MV      .L2     B10,B4            ; |114| 

           STDW    .D2T1   A5:A4,*B13        ; |130| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 
           LDW     .D2T1   *+SP(20),A3       ; |117| 
           SUBU    .L2     B5,B8,B7:B6       ; |117| 
           MVKL    .S2     _t_offset,B31

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B4,B9,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVK     .S2     0x80,B4

           MVKH    .S2     _t_offset,B31
||         STW     .D2T1   A3,*+SP(12)

           STDW    .D2T2   B7:B6,*B31        ; |117| 
||         MV      .L1     A10,A13
||         MV      .S1X    B4,A10            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A12,A3           ; |237| 
           NOP             4

           ADD     .L1     A13,A3,A3         ; |237| 
||         CALL    .S1     _logdp_c          ; |237| 

           LDDW    .D1T1   *A3,A5:A4         ; |237| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |237| 
$C$RL35:   ; CALL OCCURS {_logdp_c} {0}      ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(12),B4       ; |237| 
           SUB     .L1     A10,1,A0          ; |236| 
           SUB     .L1     A10,1,A10         ; |236| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |237| 
   [ A0]   BNOP    .S1     $C$L15,3          ; |236| 

           ADD     .L1X    A13,B4,A3         ; |237| 
||         ADD     .S1     8,A13,A13         ; |236| 

           STDW    .D1T1   A5:A4,*A3         ; |237| 
           ; BRANCHCC OCCURS {$C$L15}        ; |236| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     _t_offset,B5
||         MV      .L1     A15,A13           ; |128| 

           MVKH    .S2     _t_offset,B5
||         LDDW    .D1T1   *A13,A5:A4        ; |130| 

           LDDW    .D2T2   *B5,B7:B6         ; |130| 
           MV      .L2     B4,B9             ; |128| 
           MV      .L2     B12,B4            ; |130| 
           LDDW    .D2T2   *+B4(16),B17:B16  ; |130| 
           MV      .L1X    B12,A15           ; |130| 
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
||         ADDKPC  .S2     $C$RL36,B3,0      ; |130| 

$C$RL36:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 109
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A10           ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 

           ADDAD   .D2     B13,1,B12
||         MV      .L2X    A15,B4

           MV      .L2     B10,B31           ; |114| 
||         STDW    .D2T2   B11:B10,*+B4(32)  ; |114| 

           STDW    .D2T1   A5:A4,*B12        ; |130| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MV      .L1     A13,A15           ; |116| 

           STDW    .D1T2   B5:B4,*A15        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     _t_offset,A3
           MVKL    .S1     _output,A10

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKH    .S1     _t_offset,A3

           MVKH    .S1     _output,A10
||         MV      .L2X    A12,B9            ; |244| 
||         SUB     .D2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         LDW     .D1T2   *+A10(16),B4      ; |244| 
||         LDW     .D2T1   *B9,A4            ; |244| 
||         MV      .S2X    A3,B10            ; |117| 

           CALLP   .S2     _logdp_v,B3
||         STDW    .D2T2   B7:B6,*B10        ; |117| 
||         MVK     .S1     0x80,A6           ; |244| 

$C$RL38:   ; CALL OCCURS {_logdp_v} {0}      ; |244| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           MVK     .S1     16,A12
           ADD     .L1X    B12,A12,A12
           LDDW    .D1T1   *A12,A17:A16      ; |130| 
           MVKL    .S1     _t_stop,A3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           MVKH    .S1     _t_stop,A3
||         SUBU    .L1X    B8,A4,A9:A8       ; |130| 

           ADD     .L1X    A5,B7,A4          ; |130| 
||         MV      .L2     B4,B9             ; |128| 

           ADD     .L1     A4,A7,A4          ; |130| 
||         MV      .L2X    A3,B4             ; |128| 
||         MV      .D1     A8,A3             ; |130| 
||         EXT     .S1     A9,24,24,A6       ; |130| 

           SUB     .S1X    B9,A4,A3          ; |130| 
||         ADDU    .L1     A16,A3,A5:A4      ; |130| 

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A3,A6,A5          ; |130| 

           CALLP   .S2     __fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL39:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A4            ; |130| 
           MV      .L1     A11,A5            ; |130| 
           NOP             2
           SPDP    .S1     A3,A7:A6          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |130| 

$C$RL40:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           STDW    .D1T1   A5:A4,*A12        ; |130| 
||         MVKH    .S2     0x3e45798e,B7

           LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL41:   ; CALL OCCURS {_isequal} {0}      ; |66| 

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     0xe2308c3a,B6

           MVKH    .S1     _fcn_pass,A3
||         MVKL    .S2     0x3e45798e,B7

           MVKH    .S2     0xe2308c3a,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MV      .L2X    A3,B10            ; |66| 
||         MVKH    .S2     0x3e45798e,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A10(8),B4       ; |67| 
||         STW     .D2T1   A5,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL42:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL43:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *A14,B4           ; |69| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL44:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(24),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(28),B4
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
   [!B0]   MV      .L1X    B11,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L17            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |250| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |250| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1X    B11,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |250| 
||         ADDKPC  .S2     $C$RL45,B3,0      ; |250| 

$C$RL45:   ; CALL OCCURS {_print_test_results} {0}  ; |250| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |251| 

$C$RL46:   ; CALL OCCURS {_printf} {0}       ; |251| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |251| 

$C$RL47:   ; CALL OCCURS {_printf} {0}       ; |251| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |258| 

$C$RL48:   ; CALL OCCURS {_print_profile_results} {0}  ; |258| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |261| 

$C$RL49:   ; CALL OCCURS {_print_memory_results} {0}  ; |261| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADDK    .S2     208,SP            ; |262| 
           LDW     .D2T2   *++SP(8),B3       ; |262| 
           LDDW    .D2T1   *++SP,A13:A12     ; |262| 
           LDDW    .D2T1   *++SP,A15:A14     ; |262| 
           LDDW    .D2T2   *++SP,B11:B10     ; |262| 
           LDDW    .D2T2   *++SP,B13:B12     ; |262| 

           LDW     .D2T1   *++SP(8),A10      ; |262| 
||         RET     .S2     B3                ; |262| 

           LDW     .D2T1   *++SP(8),A11      ; |262| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |262| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"logDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_log
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_logdp
	.global	_logdp_c
	.global	_logdp_v
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
