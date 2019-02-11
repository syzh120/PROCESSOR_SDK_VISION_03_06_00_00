;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:48:55 2013                                *
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
	.elfsym	a,SYM_SIZE(1608)
a:
	.word	05be02646h,0412af0e3h		; a[0] @ 0
	.word	020423b0eh,04121197ah		; a[1] @ 64
	.word	066ce505bh,040fdd968h		; a[2] @ 128
	.word	0bb561764h,0411dd368h		; a[3] @ 192
	.word	09b258ad4h,040ed382dh		; a[4] @ 256
	.word	09d3b8af1h,04121d565h		; a[5] @ 320
	.word	0357bd563h,04116dda3h		; a[6] @ 384
	.word	0dfabcffdh,0412bd534h		; a[7] @ 448
	.word	09ea2edd6h,04129b83fh		; a[8] @ 512
	.word	0f33d2956h,0411316d3h		; a[9] @ 576
	.word	0dea31975h,0412616dbh		; a[10] @ 640
	.word	0442a927bh,04128999fh		; a[11] @ 704
	.word	0f4b223d4h,040ff1162h		; a[12] @ 768
	.word	048aef7d0h,0412c7afbh		; a[13] @ 832
	.word	02e682152h,041172716h		; a[14] @ 896
	.word	024213a0ch,041027270h		; a[15] @ 960
	.word	038de59bdh,041197540h		; a[16] @ 1024
	.word	07a42ff59h,041093db2h		; a[17] @ 1088
	.word	005c96031h,041008b60h		; a[18] @ 1152
	.word	05caf84bdh,0411ec7d7h		; a[19] @ 1216
	.word	09a7f221fh,041283555h		; a[20] @ 1280
	.word	0d3cf04b5h,0411eac9bh		; a[21] @ 1344
	.word	039f9c122h,04116eaf8h		; a[22] @ 1408
	.word	0a6c4fb47h,040e6e078h		; a[23] @ 1472
	.word	03822eae7h,0412d5011h		; a[24] @ 1536
	.word	0bfeef292h,04127c24ah		; a[25] @ 1600
	.word	09f912a5fh,040f71020h		; a[26] @ 1664
	.word	0ca0f4d7bh,0411f93ddh		; a[27] @ 1728
	.word	0dd928fbah,0410697d4h		; a[28] @ 1792
	.word	0409807c9h,04122381ah		; a[29] @ 1856
	.word	0117bc141h,0412a26cbh		; a[30] @ 1920
	.word	047531048h,04110c1a9h		; a[31] @ 1984
	.word	03d9fb898h,0411513c1h		; a[32] @ 2048
	.word	0c0d5984dh,040f7c32ah		; a[33] @ 2112
	.word	098b47263h,04129bddbh		; a[34] @ 2176
	.word	08969a0aeh,0410ff548h		; a[35] @ 2240
	.word	006488758h,0412b9a46h		; a[36] @ 2304
	.word	006eb412ch,040d6a8f9h		; a[37] @ 2368
	.word	0be2003ach,04128c59dh		; a[38] @ 2432
	.word	04b40db92h,040d69449h		; a[39] @ 2496
	.word	0e4d6eb34h,0412c62c5h		; a[40] @ 2560
	.word	02aca361ah,0412575b2h		; a[41] @ 2624
	.word	06a712282h,040fe2defh		; a[42] @ 2688
	.word	0b2c9696bh,04124bc73h		; a[43] @ 2752
	.word	03d4e0978h,040f240cfh		; a[44] @ 2816
	.word	0d6f2a5a4h,040f30c52h		; a[45] @ 2880
	.word	04f937238h,04126276dh		; a[46] @ 2944
	.word	0403d3ca1h,0412d4cc8h		; a[47] @ 3008
	.word	06b23eac1h,041220aeeh		; a[48] @ 3072
	.word	03dc66326h,041243069h		; a[49] @ 3136
	.word	0775cb5e3h,04104bdf4h		; a[50] @ 3200
	.word	093161a1eh,04106d07ch		; a[51] @ 3264
	.word	03d990951h,041131ff5h		; a[52] @ 3328
	.word	073e56473h,04121564bh		; a[53] @ 3392
	.word	08c2a7e59h,041220d47h		; a[54] @ 3456
	.word	01d64f2c9h,04110086bh		; a[55] @ 3520
	.word	0fcdb6a1fh,04124d9ech		; a[56] @ 3584
	.word	0387d4e09h,0411f4735h		; a[57] @ 3648
	.word	05dbb6aa5h,0412631a5h		; a[58] @ 3712
	.word	05f922963h,04125ad41h		; a[59] @ 3776
	.word	07feab368h,04126368dh		; a[60] @ 3840
	.word	013f65dc0h,041283cbfh		; a[61] @ 3904
	.word	0c21bd8a4h,0412ba7f5h		; a[62] @ 3968
	.word	058c2140ch,04122db3ch		; a[63] @ 4032
	.word	06f2ae07eh,040f23957h		; a[64] @ 4096
	.word	0b2319e08h,04113223bh		; a[65] @ 4160
	.word	01f05ea25h,040e2d284h		; a[66] @ 4224
	.word	0a346a352h,04124ed79h		; a[67] @ 4288
	.word	09c435844h,0412cad97h		; a[68] @ 4352
	.word	059ad2136h,041212e6dh		; a[69] @ 4416
	.word	0d7dd68fch,04123ba2eh		; a[70] @ 4480
	.word	0412a5f4fh,041084c18h		; a[71] @ 4544
	.word	0911cb03ah,041001909h		; a[72] @ 4608
	.word	0ee15d123h,041230cd6h		; a[73] @ 4672
	.word	01ae865b0h,041298aa9h		; a[74] @ 4736
	.word	00b3b67b5h,040e15eefh		; a[75] @ 4800
	.word	08183c36eh,040ed7e79h		; a[76] @ 4864
	.word	05f865d7dh,04105633eh		; a[77] @ 4928
	.word	036c8853fh,0411326bfh		; a[78] @ 4992
	.word	00ec980e8h,04124ad32h		; a[79] @ 5056
	.word	0c2aa0522h,04125f43eh		; a[80] @ 5120
	.word	0cf0f1daah,0411db3d4h		; a[81] @ 5184
	.word	028c4d80ch,0411689beh		; a[82] @ 5248
	.word	090e0a84ch,041076d08h		; a[83] @ 5312
	.word	062055e0eh,0412577bfh		; a[84] @ 5376
	.word	01b8179e8h,0411a39cdh		; a[85] @ 5440
	.word	0efac710dh,0412b3befh		; a[86] @ 5504
	.word	0aa0dd5ach,0410d19ddh		; a[87] @ 5568
	.word	0415aebdfh,041086339h		; a[88] @ 5632
	.word	0f8ac555eh,0411c1878h		; a[89] @ 5696
	.word	02a353c22h,04116bd96h		; a[90] @ 5760
	.word	05a908a26h,040f3c7c4h		; a[91] @ 5824
	.word	0936c2d50h,0412e4754h		; a[92] @ 5888
	.word	0380614edh,04123426bh		; a[93] @ 5952
	.word	023a73995h,0412abd5eh		; a[94] @ 6016
	.word	080f58cdfh,041211d7eh		; a[95] @ 6080
	.word	0e8e1932dh,0411b2e12h		; a[96] @ 6144
	.word	0a6f7d30bh,0412228b9h		; a[97] @ 6208
	.word	094cf4a56h,040f4f620h		; a[98] @ 6272
	.word	06e9f4fbch,040ff0d6eh		; a[99] @ 6336
	.word	04aedb4a4h,041203e1dh		; a[100] @ 6400
	.word	0f32a355eh,04121e2c6h		; a[101] @ 6464
	.word	09083f69ah,0410f6359h		; a[102] @ 6528
	.word	07ee9325eh,04128d96eh		; a[103] @ 6592
	.word	0ad5e071ch,04128dc5eh		; a[104] @ 6656
	.word	0231b65b7h,0411b02fch		; a[105] @ 6720
	.word	0b7215c71h,0410e86bch		; a[106] @ 6784
	.word	0fef72134h,0410fd030h		; a[107] @ 6848
	.word	0c94b167fh,0411b47a9h		; a[108] @ 6912
	.word	0c0512c42h,041222bafh		; a[109] @ 6976
	.word	0a5044509h,0411f9324h		; a[110] @ 7040
	.word	04a7c2515h,04124ed13h		; a[111] @ 7104
	.word	0bebbe29ah,041058158h		; a[112] @ 7168
	.word	0a6f5a2afh,040ed87f3h		; a[113] @ 7232
	.word	09db7d69ch,040fa6616h		; a[114] @ 7296
	.word	0b8770d7eh,0412bc170h		; a[115] @ 7360
	.word	04cf0d18fh,041155a32h		; a[116] @ 7424
	.word	0180f0557h,0411bf2d0h		; a[117] @ 7488
	.word	01f78897fh,041240945h		; a[118] @ 7552
	.word	069d44490h,04115082bh		; a[119] @ 7616
	.word	0565f3af9h,0412b5ab0h		; a[120] @ 7680
	.word	0e860b7d1h,0412e6a58h		; a[121] @ 7744
	.word	0fcfe6c82h,041183cbfh		; a[122] @ 7808
	.word	0ea2b8265h,040580f5dh		; a[123] @ 7872
	.word	0b738609ah,0411545a8h		; a[124] @ 7936
	.word	08263736dh,0411d6d9ah		; a[125] @ 8000
	.word	0d5c34b44h,041032985h		; a[126] @ 8064
	.word	0a32d905ch,0411cedc7h		; a[127] @ 8128
	.word	048bdf315h,04129812dh		; a[128] @ 8192
	.word	038776816h,041129a29h		; a[129] @ 8256
	.word	036283177h,04115f77ah		; a[130] @ 8320
	.word	0cab1df0bh,0412d6f9fh		; a[131] @ 8384
	.word	0dd9b3652h,040f0ab74h		; a[132] @ 8448
	.word	0eb1cb542h,0411c807fh		; a[133] @ 8512
	.word	0358298cch,040cc3746h		; a[134] @ 8576
	.word	0889019beh,0410ea824h		; a[135] @ 8640
	.word	013570245h,04116058dh		; a[136] @ 8704
	.word	05f3962f8h,041207ebah		; a[137] @ 8768
	.word	07784a292h,0412662dfh		; a[138] @ 8832
	.word	0de42e481h,04126032bh		; a[139] @ 8896
	.word	0a9843584h,04122f0bah		; a[140] @ 8960
	.word	029e55f6bh,04125c376h		; a[141] @ 9024
	.word	056059063h,04125d212h		; a[142] @ 9088
	.word	06f709b74h,04115aedeh		; a[143] @ 9152
	.word	0472cf95dh,04114828dh		; a[144] @ 9216
	.word	02c63d669h,041271e58h		; a[145] @ 9280
	.word	0a8c63503h,04127393ah		; a[146] @ 9344
	.word	01bb27533h,04125ad0eh		; a[147] @ 9408
	.word	039424448h,04122c68ch		; a[148] @ 9472
	.word	04f9350aah,040de77b6h		; a[149] @ 9536
	.word	056818ee1h,0410f12b9h		; a[150] @ 9600
	.word	086d34ec7h,0412d2addh		; a[151] @ 9664
	.word	08800218eh,041009132h		; a[152] @ 9728
	.word	0e4cb0b2ch,0411e8200h		; a[153] @ 9792
	.word	01dc69220h,041065c4eh		; a[154] @ 9856
	.word	09e73c199h,04129d164h		; a[155] @ 9920
	.word	07add6678h,04105e20ch		; a[156] @ 9984
	.word	02ca08cd3h,04125e94ch		; a[157] @ 10048
	.word	046177136h,040fd155fh		; a[158] @ 10112
	.word	0d08bc317h,0412673fah		; a[159] @ 10176
	.word	09eb862b2h,04122b1d8h		; a[160] @ 10240
	.word	0ebcbdc0ch,041292d49h		; a[161] @ 10304
	.word	05ccdd93ch,0410cb5f4h		; a[162] @ 10368
	.word	08cb62698h,041215912h		; a[163] @ 10432
	.word	0375d38c0h,0412bca10h		; a[164] @ 10496
	.word	07c47c668h,04121963fh		; a[165] @ 10560
	.word	0abfd5022h,041125a31h		; a[166] @ 10624
	.word	0a8e9e93dh,0412abe7fh		; a[167] @ 10688
	.word	099d3b0edh,04100ba0bh		; a[168] @ 10752
	.word	08f901df0h,04111db71h		; a[169] @ 10816
	.word	0db7a94f2h,04124335eh		; a[170] @ 10880
	.word	063604692h,0412869a2h		; a[171] @ 10944
	.word	0275455c3h,0412cd115h		; a[172] @ 11008
	.word	0f44a2fcfh,0412bac92h		; a[173] @ 11072
	.word	0bb38d60ah,041112c55h		; a[174] @ 11136
	.word	0bb729cd6h,040e9d28ch		; a[175] @ 11200
	.word	0e795266dh,04121bdbfh		; a[176] @ 11264
	.word	081c81400h,0412cf1f6h		; a[177] @ 11328
	.word	055e6d084h,041258dd1h		; a[178] @ 11392
	.word	09ec9e8edh,0412d71a7h		; a[179] @ 11456
	.word	0887ecc8fh,0412b096bh		; a[180] @ 11520
	.word	024b6dbcah,0411fbf65h		; a[181] @ 11584
	.word	0985a3429h,040efab9fh		; a[182] @ 11648
	.word	0c486cebch,0411b02a0h		; a[183] @ 11712
	.word	09c87f603h,0411215f1h		; a[184] @ 11776
	.word	0bb6df902h,04114c8b2h		; a[185] @ 11840
	.word	00bcabed6h,040f8c07fh		; a[186] @ 11904
	.word	088fce091h,0412e4faeh		; a[187] @ 11968
	.word	09732c478h,04129daddh		; a[188] @ 12032
	.word	0782c17b6h,04125c370h		; a[189] @ 12096
	.word	0a624dd2fh,0410045f7h		; a[190] @ 12160
	.word	0fa3cb817h,041261c92h		; a[191] @ 12224
	.word	0f824b9f4h,041035079h		; a[192] @ 12288
	.word	0427dd94ah,041204d21h		; a[193] @ 12352
	.word	060e42b8eh,040f5106fh		; a[194] @ 12416
	.word	0a67f9e46h,041135db2h		; a[195] @ 12480
	.word	09e395663h,0411b30a1h		; a[196] @ 12544
	.word	038aae445h,04111d92bh		; a[197] @ 12608
	.word	026e8f953h,0411d3709h		; a[198] @ 12672
	.word	0aa1130aah,040f1a205h		; a[199] @ 12736
	.word	0c7b2788eh,04120292bh		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\059642 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\059644 
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
allequal:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STW     .D2T1   A11,*SP--(8)      ; |63| 
||         MVKL    .S2     0xe2308c3a,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     output,A11
||         MVKL    .S2     0x3e45798e,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     output,A11
||         MVKH    .S2     0xe2308c3a,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3e45798e,B7
||         MVK     .S1     0x9,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {isequal} {0}       ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A12
||         MVKH    .S2     0x3e45798e,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A12
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xe2308c3a,B6
           MVKL    .S2     0x3e45798e,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3e45798e,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3e45798e,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xe2308c3a,B6

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
;*   Local Frame Size  : 8 Args + 196 Auto + 56 Save = 260 byte               *
;******************************************************************************
main:
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

           CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     a,A12
           MVKL    .S1     output,A3
           MVKH    .S1     a,A12
           MVKH    .S1     output,A3

           MV      .L1     A12,A13
||         CALL    .S1     log               ; |146| 
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
$C$RL5:    ; CALL OCCURS {log} {0}           ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |145| 
||         STDW    .D1T1   A5:A4,*A11++      ; |146| 
||         SUB     .S1     A10,1,A10         ; |145| 

   [ A0]   B       .S2     $C$L3             ; |145| 
|| [!A0]   MVKL    .S1     output,A3
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |146| 
|| [!A0]   ZERO    .L2     B10

   [ A0]   CALL    .S1     log               ; |146| 
   [!A0]   MVKH    .S1     output,A3
   [!A0]   MVK     .S1     0xc9,A10
   [!A0]   ADD     .L2X    4,A3,B4
   [!A0]   STW     .D2T2   B4,*+SP(16)
           ; BRANCHCC OCCURS {$C$L3}         ; |145| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     logdp             ; |149| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A12++,A5:A4      ; |149| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |149| 
$C$RL6:    ; CALL OCCURS {logdp} {0}         ; |149| 
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

   [ A0]   CALL    .S1     logdp             ; |149| 
||         STDW    .D2T1   A5:A4,*B4         ; |149| 

           ; BRANCHCC OCCURS {$C$L4}         ; |148| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(16),B4
           ZERO    .L2     B10
           MVKL    .S1     a,A10
           MVKH    .S1     a,A10
           MVK     .S1     0xc9,A11
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(20)
||         CALL    .S1     logdp_c           ; |152| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |152| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |152| 
$C$RL7:    ; CALL OCCURS {logdp_c} {0}       ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(20),B4       ; |152| 
||         SUB     .L1     A11,1,A0          ; |151| 
||         SUB     .S1     A11,1,A11         ; |151| 

   [!A0]   MVK     .S1     0xfffffc01,A20
|| [!A0]   LDW     .D2T1   *+SP(20),A3

   [!A0]   MVKL    .S2     a,B8
   [!A0]   ZERO    .L2     B9                ; |102| 
   [!A0]   MV      .L2     B9,B12            ; |108| 
           LDW     .D2T2   *B4,B4            ; |152| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |151| 
|| [!A0]   ADD     .L1     4,A3,A15

           ADD     .L2     B10,B4,B4         ; |152| 
||         ADD     .S2     8,B10,B10         ; |151| 

   [ A0]   CALL    .S1     logdp_c           ; |152| 
||         STDW    .D2T1   A5:A4,*B4         ; |152| 

           ; BRANCHCC OCCURS {$C$L5}         ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           MVKH    .S2     a,B8
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
||         STW     .D2T2   B9,*+SP(40)       ; |102| 

           MVKH    .S2     0x3fe6a09e,B6

           MVKH    .S2     0x667f3bcd,B31
||         STW     .D2T2   B6,*+SP(36)       ; |97| 

           STW     .D2T2   B31,*+SP(32)      ; |97| 

           CLR     .S2     B5,20,31,B6       ; |91| 
||         LDDW    .D2T2   *+SP(32),B17:B16  ; |97| 

           EXTU    .S2     B5,1,21,B1        ; |86| 

           OR      .S1X    A4,B6,A8          ; |91| 
|| [!B1]   ZERO    .L1     A5:A4             ; |91| 
||         SET     .S2     B30,0x15,0x1d,B6

           ZERO    .L1     A8                ; |102| 
|| [ B1]   MV      .S1     A8,A5             ; |91| 
|| [ B1]   MV      .D1X    B4,A4             ; |91| 

           STW     .D2T2   B6,*+SP(44)       ; |102| 
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
           STW     .D2T2   B30,*+SP(48)      ; |55| 
           MVKH    .S2     0xc041d580,B31
           STW     .D2T2   B31,*+SP(52)      ; |55| 
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
           STW     .D2T2   B28,*+SP(56)      ; |114| 
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

           STW     .D2T2   B6,*+SP(60)       ; |114| 
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
|| [!B2]   CALL    .S1     logdp_v           ; |157| 

           ; BRANCHCC OCCURS {$C$L6}         ; |154| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A14,B4           ; |157| 
           MVKL    .S1     a,A4
           MVKH    .S1     a,A4
           ADDKPC  .S2     $C$RL8,B3,0       ; |157| 
           MVK     .S1     0xc9,A6           ; |157| 
$C$RL8:    ; CALL OCCURS {logdp_v} {0}       ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0xc9,A4           ; |160| 

$C$RL9:    ; CALL OCCURS {allequal} {0}      ; |160| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |161| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           STW     .D2T1   A12,*+SP(104)     ; |108| 
           STW     .D2T1   A13,*+SP(108)     ; |108| 
           LDW     .D2T1   *+SP(48),A22      ; |108| 
           STW     .D2T1   A11,*+SP(116)     ; |108| 
           LDW     .D2T1   *+SP(60),A26      ; |55| 
           LDW     .D2T1   *+SP(32),A12

           LDW     .D2T1   *+SP(52),A23      ; |108| 
||         ZERO    .L2     B26               ; |108| 

           STW     .D2T2   B26,*+SP(96)      ; |169| 
           STW     .D2T1   A10,*+SP(112)     ; |108| 
           STW     .D2T1   A15,*+SP(24)      ; |119| 
           STW     .D2T2   B11,*+SP(196)     ; |119| 
           STW     .D2T2   B13,*+SP(140)     ; |108| 
           STW     .D2T2   B13,*+SP(132)     ; |108| 
           STW     .D2T2   B13,*+SP(100)     ; |108| 

           STW     .D2T2   B13,*+SP(92)      ; |108| 
||         MVKL    .S2     0x3fe63000,B4

           STW     .D2T2   B13,*+SP(84)      ; |108| 
||         MVKH    .S2     0x3fe63000,B4

           STW     .D2T2   B4,*+SP(172)      ; |114| 

           LDW     .D2T1   *+SP(36),A13      ; |102| 
||         ZERO    .L2     B25               ; |114| 

           STW     .D2T2   B25,*+SP(168)     ; |169| 
||         ZERO    .L1     A1                ; |116| 

           STW     .D2T1   A1,*+SP(184)      ; |169| 
||         MVKL    .S1     0xb356bd29,A24
||         ZERO    .L1     A8                ; |55| 

           STW     .D2T1   A8,*+SP(136)      ; |171| 
||         MVKL    .S1     0xbfe94415,A25
||         ZERO    .L2     B27               ; |108| 

           STW     .D2T2   B27,*+SP(80)      ; |171| 
||         MVKL    .S1     0x2016afed,A27
||         ZERO    .L2     B28               ; |108| 

           STW     .D2T2   B28,*+SP(88)      ; |171| 
||         MVKL    .S1     0x4030624a,A28
||         ZERO    .L1     A16               ; |55| 

           STW     .D2T1   A16,*+SP(128)     ; |172| 
||         MVKL    .S1     0x12b3b59a,A29
||         ZERO    .L2     B30               ; |98| 

           STW     .D2T2   B30,*+SP(64)      ; |172| 
||         MVKL    .S1     0xc05007ff,A30
||         ZERO    .L1     A19               ; |98| 

           STW     .D2T1   A19,*+SP(56)      ; |173| 
||         MVKL    .S1     0x5c610ca8,A31
||         MVK     .L2     0x6,B31

           STW     .D2T2   B31,*+SP(12)      ; |173| 
||         MVKL    .S1     0xbf2bd010,A3
||         ZERO    .L1     A18               ; |103| 

           STW     .D2T1   A18,*+SP(48)      ; |173| 
||         MVKH    .S1     0xb356bd29,A24

           STW     .D2T1   A24,*+SP(160)     ; |55| 
||         MVKH    .S1     0xbfe94415,A25

           STW     .D2T1   A25,*+SP(164)     ; |55| 
||         MVKH    .S1     0x2016afed,A27

           STW     .D2T1   A27,*+SP(152)     ; |55| 
||         MVKH    .S1     0x4030624a,A28

           STW     .D2T1   A28,*+SP(156)     ; |55| 
||         MVKH    .S1     0x12b3b59a,A29

           STW     .D2T1   A29,*+SP(144)     ; |55| 
||         MVKH    .S1     0xc05007ff,A30
||         MVKL    .S2     a_sc,B16

           STW     .D2T1   A30,*+SP(148)     ; |55| 
||         MVKH    .S2     a_sc,B16
||         MVKH    .S1     0x5c610ca8,A31

           STW     .D2T1   A31,*+SP(176)     ; |114| 
||         MVKH    .S1     0xbf2bd010,A3
||         MV      .L1X    B13,A11           ; |108| 
||         ZERO    .D1     A5
||         ADD     .L2     1,B11,B9

           STW     .D2T1   A3,*+SP(180)      ; |114| 
||         MV      .L1X    B16,A21
||         ZERO    .S1     A7
||         ZERO    .L2     B29               ; |103| 
||         ZERO    .D1     A4                ; |171| 
||         MV      .S2     B12,B8

           STDW    .D1T2   B9:B8,*+A21(16)   ; |170| 
||         STW     .D2T1   A26,*+SP(188)     ; |116| 
||         MV      .L1X    B16,A9            ; |172| 
||         MVKH    .S1     0xfff00000,A5
||         ZERO    .L2     B6                ; |172| 
||         ZERO    .S2     B7

           STDW    .D1T1   A5:A4,*+A9(24)    ; |171| 
||         MV      .L1X    B16,A17           ; |173| 
||         STW     .D2T2   B29,*+SP(32)      ; |172| 
||         SET     .S2     B7,0x14,0x1d,B7
||         ZERO    .L2     B5
||         ZERO    .S1     A6                ; |173| 

           STDW    .D1T2   B7:B6,*+A17(32)   ; |172| 
||         ADD     .L2     -7,B31,B26
||         STW     .D2T1   A23,*+SP(124)     ; |108| 
||         MV      .L1X    B16,A20           ; |171| 
||         MVKH    .S1     0xbff00000,A7
||         MVKL    .S2     output,B10

           STDW    .D1T1   A7:A6,*+A20(40)   ; |173| 
||         STW     .D2T2   B26,*+SP(192)     ; |169| 
||         ZERO    .L2     B4                ; |169| 
||         MV      .L1X    B16,A2            ; |171| 
||         MVKH    .S2     0x80000000,B5

           ZERO    .L2     B9:B8             ; |168| 
||         ZERO    .L1     A9                ; |99| 
||         STDW    .D1T2   B5:B4,*+A2(8)     ; |169| 
||         STW     .D2T1   A22,*+SP(120)     ; |108| 
||         ZERO    .S1     A10               ; |55| 
||         ZERO    .S2     B12               ; |99| 

           CALL    .S1     log               ; |175| 
||         STDW    .D1T2   B9:B8,*A21        ; |168| 
||         STW     .D2T1   A9,*+SP(72)       ; |172| 
||         SUB     .L1X    B16,8,A15
||         ZERO    .L2     B11
||         MVKH    .S2     output,B10

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
$C$RL11:   ; CALL OCCURS {log} {0}           ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D2T2   *B10,B4           ; |175| 
           NOP             4

           ADD     .L2     B11,B4,B6         ; |175| 
||         DADD    .S2X    0,A5:A4,B5:B4     ; |175| 

           STDW    .D2T2   B5:B4,*B6         ; |175| 

           CALLP   .S2     logdp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |176| 

$C$RL12:   ; CALL OCCURS {logdp} {0}         ; |176| 
           LDW     .D2T2   *+B10(4),B4       ; |176| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |176| 
           STDW    .D2T1   A5:A4,*B4         ; |176| 

           CALLP   .S2     logdp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |177| 

$C$RL13:   ; CALL OCCURS {logdp_c} {0}       ; |177| 
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
|| [ A0]   STW     .D2T1   A3,*+SP(76)       ; |99| 

   [!A0]   STW     .D2T1   A3,*+SP(52)       ; |103| 
   [ A0]   LDDW    .D2T1   *+SP(72),A7:A6    ; |103| 

   [!A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |102| 
|| [!A0]   LDDW    .D2T1   *+SP(48),A7:A6    ; |99| 

   [!A0]   SET     .S2     B4,0x15,0x1d,B4
   [!A0]   STW     .D2T2   B4,*+SP(36)       ; |103| 
   [!A0]   LDDW    .D2T2   *+SP(32),B5:B4    ; |99| 
   [ A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |99| 
   [!A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |103| 
   [ A0]   ZERO    .L2     B13
   [ A0]   SET     .S2     B13,0x15,0x1d,B13
   [ A0]   ZERO    .L1     A3
   [ A0]   FADDDP  .L2X    B13:B12,A7:A6,B7:B6 ; |99| 
   [!A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |103| 
   [ A0]   SET     .S1     A3,0x15,0x1d,A3
   [ A0]   STW     .D2T1   A3,*+SP(60)       ; |98| 
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
   [ A0]   STW     .D2T2   B8,*+SP(68)       ; |98| 
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

   [ A2]   CALL    .S1     log               ; |175| 
||         STDW    .D2T2   B5:B4,*B6         ; |178| 

           ; BRANCHCC OCCURS {$C$L9}         ; |174| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     logdp_v           ; |180| 
           LDW     .D1T2   *A14,B4           ; |180| 
           MVKL    .S1     a_sc,A4
           MVKH    .S1     a_sc,A4
           ADDKPC  .S2     $C$RL14,B3,0      ; |180| 
           MVK     .L1     0x6,A6            ; |180| 
$C$RL14:   ; CALL OCCURS {logdp_v} {0}       ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .L1     0x6,A4            ; |183| 

$C$RL15:   ; CALL OCCURS {allequal} {0}      ; |183| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x3,A4            ; |184| 

$C$RL16:   ; CALL OCCURS {print_test_results} {0}  ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T1   *+SP(120),A19     ; |108| 
           LDW     .D2T1   *+SP(124),A20     ; |108| 
           LDW     .D2T1   *+SP(160),A25     ; |55| 
           LDW     .D2T1   *+SP(164),A26     ; |55| 
           LDW     .D2T1   *+SP(44),A18      ; |103| 
           LDW     .D2T1   *+SP(104),A23     ; |108| 
           LDW     .D2T1   *+SP(108),A24     ; |55| 
           LDW     .D2T1   *+SP(144),A29     ; |55| 

           LDW     .D2T1   *+SP(148),A30     ; |55| 
||         MVK     .L1     0xffffffff,A17    ; |119| 

           STW     .D2T1   A17,*+SP(192)     ; |187| 
           LDW     .D2T1   *+SP(112),A21     ; |108| 
           LDW     .D2T1   *+SP(116),A22     ; |108| 
           LDW     .D2T1   *+SP(152),A27     ; |55| 
           LDW     .D2T1   *+SP(156),A28     ; |55| 

           LDW     .D2T2   *+SP(188),B5      ; |193| 
||         MV      .L2     B12,B4            ; |108| 

           STW     .D2T2   B4,*+SP(168)      ; |187| 
||         MV      .L1     A10,A16           ; |119| 

           STW     .D2T1   A16,*+SP(184)     ; |187| 
||         MV      .L2     B12,B31           ; |108| 

           STW     .D2T2   B31,*+SP(88)      ; |187| 
||         MV      .L2X    A11,B13           ; |108| 

           STW     .D2T2   B13,*+SP(132)     ; |108| 
           STW     .D2T2   B13,*+SP(92)      ; |108| 
           STW     .D2T2   B13,*+SP(84)      ; |108| 

           STW     .D2T2   B13,*+SP(76)      ; |108| 
||         MV      .L2     B12,B8            ; |108| 

           STW     .D2T2   B8,*+SP(80)
||         MVK     .S2     0x777,B7

           STW     .D2T2   B7,*+SP(12)
||         MV      .L1     A10,A4            ; |102| 

           STW     .D2T1   A4,*+SP(120)

           STW     .D2T2   B13,*+SP(124)     ; |108| 
||         MVKL    .S1     0xcccccccd,A31
||         MV      .L1     A10,A5            ; |119| 

           STW     .D2T1   A5,*+SP(160)      ; |187| 
||         MVKL    .S1     0xc000cccc,A3

           STW     .D2T2   B13,*+SP(164)     ; |108| 
||         MVKH    .S1     0xcccccccd,A31

           STW     .D2T1   A31,*+SP(200)     ; |193| 
||         MVKH    .S1     0xc000cccc,A3

           STW     .D2T1   A3,*+SP(204)      ; |193| 
           STW     .D2T1   A18,*+SP(36)      ; |102| 
           STW     .D2T1   A23,*+SP(96)      ; |108| 
           STW     .D2T1   A24,*+SP(100)     ; |108| 
           STW     .D2T1   A29,*+SP(136)     ; |55| 

           STW     .D2T1   A30,*+SP(140)     ; |55| 
||         MV      .L1     A10,A17           ; |102| 

           STW     .D2T1   A17,*+SP(128)
           STW     .D2T1   A19,*+SP(112)     ; |108| 
           STW     .D2T1   A20,*+SP(116)     ; |108| 
           STW     .D2T1   A21,*+SP(104)     ; |108| 
           STW     .D2T1   A22,*+SP(108)     ; |108| 
           STW     .D2T1   A25,*+SP(152)     ; |55| 

           STW     .D2T1   A26,*+SP(156)     ; |55| 
||         MVKL    .S2     a_ext,B6

           STW     .D2T1   A27,*+SP(144)     ; |55| 
||         MVKH    .S2     a_ext,B6

           STW     .D2T1   A28,*+SP(148)     ; |55| 

           STDW    .D2T2   B5:B4,*B6         ; |187| 
||         MV      .L1X    B6,A15            ; |187| 

           CALL    .S1     log               ; |189| 
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
$C$RL17:   ; CALL OCCURS {log} {0}           ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |189| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |189| 
           STDW    .D2T1   A5:A4,*B4         ; |189| 

           CALLP   .S2     logdp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |190| 

$C$RL18:   ; CALL OCCURS {logdp} {0}         ; |190| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T1   *+B4(4),A3        ; |190| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |190| 
           NOP             3
           ADD     .L1X    B10,A3,A3         ; |190| 
           STDW    .D1T2   B5:B4,*A3         ; |190| 

           CALLP   .S2     logdp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |191| 

$C$RL19:   ; CALL OCCURS {logdp_c} {0}       ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 193
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
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

   [!A0]   STW     .D2T1   A3,*+SP(52)       ; |103| 
   [ A0]   FMPYDP  .M1     A11:A10,A5:A4,A7:A6 ; |99| 

   [!A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |102| 
|| [!A0]   LDDW    .D2T1   *+SP(48),A7:A6    ; |99| 

   [ A0]   STW     .D2T2   B4,*+SP(68)       ; |99| 
   [!A0]   STW     .D2T2   B4,*+SP(44)       ; |103| 
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
   [ A0]   STW     .D2T2   B6,*+SP(60)       ; |98| 
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
|| [!A0]   MVKL    .S2     output,B11

   [!A0]   MVKH    .S2     output,B11

           STDW    .D1T1   A5:A4,*++A15      ; |193| 
||         STW     .D2T2   B4,*+SP(12)       ; |193| 
|| [!A0]   MVKL    .S1     a_ext,A4

   [ A0]   CALL    .S1     log               ; |189| 
|| [ A0]   LDDW    .D1T2   *A15,B5:B4        ; |189| 

   [!A0]   CALL    .S1     logdp_v           ; |195| 
|| [!A0]   LDW     .D2T2   *+B11(16),B4      ; |195| 

           ; BRANCHCC OCCURS {$C$L10}        ; |188| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           MVKH    .S1     a_ext,A4
           MVK     .S1     0x777,A6          ; |195| 
           ADDKPC  .S2     $C$RL20,B3,2      ; |195| 
$C$RL20:   ; CALL OCCURS {logdp_v} {0}       ; |195| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL21:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B10
           MVKL    .S2     0x3e45798e,B7
           MVKH    .S2     fcn_pass,B10
           MVKL    .S2     0xe2308c3a,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3e45798e,B7

           STW     .D2T1   A4,*+B10(4)       ; |66| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL22:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         MVKH    .S2     0x3e45798e,B7

           MV      .L2     B11,B5            ; |67| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL23:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           MV      .L1     A14,A5            ; |68| 
||         MV      .L2     B11,B4            ; |68| 
||         STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A5,B4            ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2     4,B10,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           STW     .D2T2   B4,*+SP(24)
           ADD     .L2     8,B10,B4
           STW     .D2T2   B4,*+SP(28)       ; |69| 

   [!B0]   MVKL    .S1     all_pass,A3
|| [!B0]   B       .S2     $C$L11            ; |72| 
|| [!B0]   MV      .L1     A10,A4
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |199| 
|| [!B0]   MVKH    .S1     all_pass,A3
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
           CALL    .S1     print_test_results ; |199| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |199| 
||         ADDKPC  .S2     $C$RL25,B3,0      ; |199| 

$C$RL25:   ; CALL OCCURS {print_test_results} {0}  ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         MV      .L2     B12,B11           ; |114| 
||         MV      .S2     B12,B10           ; |114| 
||         MV      .D2     B12,B4            ; |114| 

           STDW    .D1T2   B11:B10,*A3       ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B5:B4,*A3         ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKL    .S2     input,B4
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B7:B6,*A3         ; |117| 
||         MVKH    .S2     input,B4
||         CALL    .S1     gimme_random      ; |209| 

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
$C$RL26:   ; CALL OCCURS {gimme_random} {0}  ; |209| 
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
||         MVKL    .S2     output+12,B31

           MVKH    .S1     0x667f3bcd,A8
||         MVKH    .S2     output+12,B31

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

           MVKL    .S1     t_start,A15

   [ A0]   FADDDP  .L2X    B9:B8,A9:A8,B5:B4 ; |99| 
||         SET     .S1     A31,0x1e,0x1e,A9
||         MV      .L1     A10,A8            ; |108| 

           MVKH    .S1     t_start,A15

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

           MVKL    .S2     t_offset,B4
||         MVKL    .S1     t_stop,A13
||         ADD     .L2     8,B13,B13         ; |207| 

           MVKH    .S2     t_offset,B4
||         MVKL    .S1     cycle_counts+24,A12

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
||         MVKL    .S2     cycle_counts+24,B30
||         MVKH    .S1     t_stop,A13

           MVKH    .S2     cycle_counts+24,B30
||         MVKH    .S1     cycle_counts+24,A12
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
||         MVKL    .S2     input,B4
|| [ A0]   ZERO    .L2     B5
|| [ A0]   MV      .L1     A10,A4            ; |209| 
|| [ A0]   B       .S1     $C$L12            ; |207| 
|| [!A0]   LDDW    .D1T1   *A12,A5:A4        ; |135| 

   [ A0]   CALL    .S1     gimme_random      ; |209| 
||         MVKH    .S2     input,B4

   [ A0]   LDW     .D2T2   *B4,B12           ; |209| 
|| [!A0]   CALL    .S2     __c6xabi_fltllif  ; |135| 
|| [ A0]   MVKL    .S1     0x412e8482,A5
|| [ A0]   MV      .L2     B10,B4            ; |209| 

   [ A0]   MVKH    .S1     0x412e8482,A5
|| [ A0]   MVKH    .S2     0xbff00000,B5

           NOP             2
           ; BRANCHCC OCCURS {$C$L12}        ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL27,B3,1      ; |135| 
$C$RL27:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL28:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
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
||         MVKL    .S2     t_offset,B31

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B4,B9,B4          ; |117| 
||         MVKL    .S1     output,A3

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKH    .S2     t_offset,B31
||         MVKH    .S1     output,A3

           STDW    .D2T2   B7:B6,*B31        ; |117| 
||         MV      .L1X    B12,A10
||         CALL    .S1     log               ; |221| 
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
$C$RL29:   ; CALL OCCURS {log} {0}           ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1X    B12,1,A0          ; |220| 
||         STDW    .D1T1   A5:A4,*A12++      ; |221| 

   [ A0]   B       .S1     $C$L13            ; |220| 
   [ A0]   CALL    .S1     log               ; |221| 
   [ A0]   LDDW    .D1T1   *A10++,A5:A4      ; |221| 
           SUB     .L2     B12,1,B12         ; |220| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L13}        ; |220| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S2     t_offset,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           MVKH    .S2     t_offset,B4
           LDDW    .D2T2   *B4,B5:B4         ; |130| 
           LDDW    .D2T2   *B13,B9:B8        ; |130| 
           NOP             3
           ADDU    .L1X    B4,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B5,A3          ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B6,A6,B5:B4       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
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

$C$RL30:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A10           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
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
||         MVKL    .S2     t_offset,B30

           EXT     .S2     B5,24,24,B7       ; |117| 

           MVK     .S2     0x80,B4
||         MV      .L2     B4,B6             ; |117| 
||         SUB     .D2     B6,B9,B31         ; |117| 

           ADD     .L2     B31,B7,B7         ; |117| 
||         MVKH    .S2     t_offset,B30
||         LDW     .D2T2   *+SP(16),B12      ; |117| 
||         MVKL    .S1     input,A12

           STDW    .D2T2   B7:B6,*B30        ; |117| 
||         MV      .L1X    B4,A10            ; |117| 
||         MVKH    .S1     input,A12
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
||         CALL    .S1     logdp             ; |229| 

           LDDW    .D1T1   *A3,A5:A4         ; |229| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |229| 
$C$RL32:   ; CALL OCCURS {logdp} {0}         ; |229| 
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

           MVKL    .S2     t_offset,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           MVKH    .S2     t_offset,B4
           LDDW    .D2T2   *B4,B5:B4         ; |130| 
           MV      .L2     B13,B12           ; |130| 
           LDDW    .D2T2   *+B12(8),B7:B6    ; |130| 
           NOP             2
           ADDU    .L1X    B4,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B5,A4          ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B5,24,24,B16      ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 

           SUB     .L2X    B9,A3,B17         ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         ADD     .D2     B5,B7,B4          ; |130| 

           ADD     .L2     B17,B16,B5        ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     t_stop,B4

           MVKH    .S2     t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL33,B3,0      ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A10           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
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
           MVKL    .S2     t_offset,B31

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B4,B9,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVK     .S2     0x80,B4

           MVKH    .S2     t_offset,B31
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
||         CALL    .S1     logdp_c           ; |237| 

           LDDW    .D1T1   *A3,A5:A4         ; |237| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |237| 
$C$RL35:   ; CALL OCCURS {logdp_c} {0}       ; |237| 
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

           MVKL    .S2     t_offset,B5
||         MV      .L1     A15,A13           ; |128| 

           MVKH    .S2     t_offset,B5
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
||         ADDKPC  .S2     $C$RL36,B3,0      ; |130| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 109
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A10           ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 

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
           MVKL    .S1     t_offset,A3
           MVKL    .S1     output,A10

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKH    .S1     t_offset,A3

           MVKH    .S1     output,A10
||         MV      .L2X    A12,B9            ; |244| 
||         SUB     .D2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         LDW     .D1T2   *+A10(16),B4      ; |244| 
||         LDW     .D2T1   *B9,A4            ; |244| 
||         MV      .S2X    A3,B10            ; |117| 

           CALLP   .S2     logdp_v,B3
||         STDW    .D2T2   B7:B6,*B10        ; |117| 
||         MVK     .S1     0x80,A6           ; |244| 

$C$RL38:   ; CALL OCCURS {logdp_v} {0}       ; |244| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           MVK     .S1     16,A12
           ADD     .L1X    B12,A12,A12
           LDDW    .D1T1   *A12,A17:A16      ; |130| 
           MVKL    .S1     t_stop,A3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           MVKH    .S1     t_stop,A3
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

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1X    B11,A4            ; |130| 
           MV      .L1     A11,A5            ; |130| 
           NOP             2
           SPDP    .S1     A3,A7:A6          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |130| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           STDW    .D1T1   A5:A4,*A12        ; |130| 
||         MVKH    .S2     0x3e45798e,B7

           LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL41:   ; CALL OCCURS {isequal} {0}       ; |66| 

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xe2308c3a,B6

           MVKH    .S1     fcn_pass,A3
||         MVKL    .S2     0x3e45798e,B7

           MVKH    .S2     0xe2308c3a,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MV      .L2X    A3,B10            ; |66| 
||         MVKH    .S2     0x3e45798e,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A10(8),B4       ; |67| 
||         STW     .D2T1   A5,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL42:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL43:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *A14,B4           ; |69| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |69| 
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
   [ A0]   CALL    .S1     print_test_results ; |250| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |250| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1X    B11,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |250| 
||         ADDKPC  .S2     $C$RL45,B3,0      ; |250| 

$C$RL45:   ; CALL OCCURS {print_test_results} {0}  ; |250| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |251| 

$C$RL46:   ; CALL OCCURS {printf} {0}        ; |251| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |251| 

$C$RL47:   ; CALL OCCURS {printf} {0}        ; |251| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |258| 

$C$RL48:   ; CALL OCCURS {print_profile_results} {0}  ; |258| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |261| 

$C$RL49:   ; CALL OCCURS {print_memory_results} {0}  ; |261| 
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
	.global	printf
	.global	log
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	logdp
	.global	logdp_c
	.global	logdp_v
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
