;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:15:04 2013                                *
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
	.word	0412af0e3h,05be02646h		; a[0] @ 0
	.word	04121197ah,020423b0eh		; a[1] @ 64
	.word	040fdd968h,066ce505bh		; a[2] @ 128
	.word	0411dd368h,0bb561764h		; a[3] @ 192
	.word	040ed382dh,09b258ad4h		; a[4] @ 256
	.word	04121d565h,09d3b8af1h		; a[5] @ 320
	.word	04116dda3h,0357bd563h		; a[6] @ 384
	.word	0412bd534h,0dfabcffdh		; a[7] @ 448
	.word	04129b83fh,09ea2edd6h		; a[8] @ 512
	.word	0411316d3h,0f33d2956h		; a[9] @ 576
	.word	0412616dbh,0dea31975h		; a[10] @ 640
	.word	04128999fh,0442a927bh		; a[11] @ 704
	.word	040ff1162h,0f4b223d4h		; a[12] @ 768
	.word	0412c7afbh,048aef7d0h		; a[13] @ 832
	.word	041172716h,02e682152h		; a[14] @ 896
	.word	041027270h,024213a0ch		; a[15] @ 960
	.word	041197540h,038de59bdh		; a[16] @ 1024
	.word	041093db2h,07a42ff59h		; a[17] @ 1088
	.word	041008b60h,005c96031h		; a[18] @ 1152
	.word	0411ec7d7h,05caf84bdh		; a[19] @ 1216
	.word	041283555h,09a7f221fh		; a[20] @ 1280
	.word	0411eac9bh,0d3cf04b5h		; a[21] @ 1344
	.word	04116eaf8h,039f9c122h		; a[22] @ 1408
	.word	040e6e078h,0a6c4fb47h		; a[23] @ 1472
	.word	0412d5011h,03822eae7h		; a[24] @ 1536
	.word	04127c24ah,0bfeef292h		; a[25] @ 1600
	.word	040f71020h,09f912a5fh		; a[26] @ 1664
	.word	0411f93ddh,0ca0f4d7bh		; a[27] @ 1728
	.word	0410697d4h,0dd928fbah		; a[28] @ 1792
	.word	04122381ah,0409807c9h		; a[29] @ 1856
	.word	0412a26cbh,0117bc141h		; a[30] @ 1920
	.word	04110c1a9h,047531048h		; a[31] @ 1984
	.word	0411513c1h,03d9fb898h		; a[32] @ 2048
	.word	040f7c32ah,0c0d5984dh		; a[33] @ 2112
	.word	04129bddbh,098b47263h		; a[34] @ 2176
	.word	0410ff548h,08969a0aeh		; a[35] @ 2240
	.word	0412b9a46h,006488758h		; a[36] @ 2304
	.word	040d6a8f9h,006eb412ch		; a[37] @ 2368
	.word	04128c59dh,0be2003ach		; a[38] @ 2432
	.word	040d69449h,04b40db92h		; a[39] @ 2496
	.word	0412c62c5h,0e4d6eb34h		; a[40] @ 2560
	.word	0412575b2h,02aca361ah		; a[41] @ 2624
	.word	040fe2defh,06a712282h		; a[42] @ 2688
	.word	04124bc73h,0b2c9696bh		; a[43] @ 2752
	.word	040f240cfh,03d4e0978h		; a[44] @ 2816
	.word	040f30c52h,0d6f2a5a4h		; a[45] @ 2880
	.word	04126276dh,04f937238h		; a[46] @ 2944
	.word	0412d4cc8h,0403d3ca1h		; a[47] @ 3008
	.word	041220aeeh,06b23eac1h		; a[48] @ 3072
	.word	041243069h,03dc66326h		; a[49] @ 3136
	.word	04104bdf4h,0775cb5e3h		; a[50] @ 3200
	.word	04106d07ch,093161a1eh		; a[51] @ 3264
	.word	041131ff5h,03d990951h		; a[52] @ 3328
	.word	04121564bh,073e56473h		; a[53] @ 3392
	.word	041220d47h,08c2a7e59h		; a[54] @ 3456
	.word	04110086bh,01d64f2c9h		; a[55] @ 3520
	.word	04124d9ech,0fcdb6a1fh		; a[56] @ 3584
	.word	0411f4735h,0387d4e09h		; a[57] @ 3648
	.word	0412631a5h,05dbb6aa5h		; a[58] @ 3712
	.word	04125ad41h,05f922963h		; a[59] @ 3776
	.word	04126368dh,07feab368h		; a[60] @ 3840
	.word	041283cbfh,013f65dc0h		; a[61] @ 3904
	.word	0412ba7f5h,0c21bd8a4h		; a[62] @ 3968
	.word	04122db3ch,058c2140ch		; a[63] @ 4032
	.word	040f23957h,06f2ae07eh		; a[64] @ 4096
	.word	04113223bh,0b2319e08h		; a[65] @ 4160
	.word	040e2d284h,01f05ea25h		; a[66] @ 4224
	.word	04124ed79h,0a346a352h		; a[67] @ 4288
	.word	0412cad97h,09c435844h		; a[68] @ 4352
	.word	041212e6dh,059ad2136h		; a[69] @ 4416
	.word	04123ba2eh,0d7dd68fch		; a[70] @ 4480
	.word	041084c18h,0412a5f4fh		; a[71] @ 4544
	.word	041001909h,0911cb03ah		; a[72] @ 4608
	.word	041230cd6h,0ee15d123h		; a[73] @ 4672
	.word	041298aa9h,01ae865b0h		; a[74] @ 4736
	.word	040e15eefh,00b3b67b5h		; a[75] @ 4800
	.word	040ed7e79h,08183c36eh		; a[76] @ 4864
	.word	04105633eh,05f865d7dh		; a[77] @ 4928
	.word	0411326bfh,036c8853fh		; a[78] @ 4992
	.word	04124ad32h,00ec980e8h		; a[79] @ 5056
	.word	04125f43eh,0c2aa0522h		; a[80] @ 5120
	.word	0411db3d4h,0cf0f1daah		; a[81] @ 5184
	.word	0411689beh,028c4d80ch		; a[82] @ 5248
	.word	041076d08h,090e0a84ch		; a[83] @ 5312
	.word	0412577bfh,062055e0eh		; a[84] @ 5376
	.word	0411a39cdh,01b8179e8h		; a[85] @ 5440
	.word	0412b3befh,0efac710dh		; a[86] @ 5504
	.word	0410d19ddh,0aa0dd5ach		; a[87] @ 5568
	.word	041086339h,0415aebdfh		; a[88] @ 5632
	.word	0411c1878h,0f8ac555eh		; a[89] @ 5696
	.word	04116bd96h,02a353c22h		; a[90] @ 5760
	.word	040f3c7c4h,05a908a26h		; a[91] @ 5824
	.word	0412e4754h,0936c2d50h		; a[92] @ 5888
	.word	04123426bh,0380614edh		; a[93] @ 5952
	.word	0412abd5eh,023a73995h		; a[94] @ 6016
	.word	041211d7eh,080f58cdfh		; a[95] @ 6080
	.word	0411b2e12h,0e8e1932dh		; a[96] @ 6144
	.word	0412228b9h,0a6f7d30bh		; a[97] @ 6208
	.word	040f4f620h,094cf4a56h		; a[98] @ 6272
	.word	040ff0d6eh,06e9f4fbch		; a[99] @ 6336
	.word	041203e1dh,04aedb4a4h		; a[100] @ 6400
	.word	04121e2c6h,0f32a355eh		; a[101] @ 6464
	.word	0410f6359h,09083f69ah		; a[102] @ 6528
	.word	04128d96eh,07ee9325eh		; a[103] @ 6592
	.word	04128dc5eh,0ad5e071ch		; a[104] @ 6656
	.word	0411b02fch,0231b65b7h		; a[105] @ 6720
	.word	0410e86bch,0b7215c71h		; a[106] @ 6784
	.word	0410fd030h,0fef72134h		; a[107] @ 6848
	.word	0411b47a9h,0c94b167fh		; a[108] @ 6912
	.word	041222bafh,0c0512c42h		; a[109] @ 6976
	.word	0411f9324h,0a5044509h		; a[110] @ 7040
	.word	04124ed13h,04a7c2515h		; a[111] @ 7104
	.word	041058158h,0bebbe29ah		; a[112] @ 7168
	.word	040ed87f3h,0a6f5a2afh		; a[113] @ 7232
	.word	040fa6616h,09db7d69ch		; a[114] @ 7296
	.word	0412bc170h,0b8770d7eh		; a[115] @ 7360
	.word	041155a32h,04cf0d18fh		; a[116] @ 7424
	.word	0411bf2d0h,0180f0557h		; a[117] @ 7488
	.word	041240945h,01f78897fh		; a[118] @ 7552
	.word	04115082bh,069d44490h		; a[119] @ 7616
	.word	0412b5ab0h,0565f3af9h		; a[120] @ 7680
	.word	0412e6a58h,0e860b7d1h		; a[121] @ 7744
	.word	041183cbfh,0fcfe6c82h		; a[122] @ 7808
	.word	040580f5dh,0ea2b8265h		; a[123] @ 7872
	.word	0411545a8h,0b738609ah		; a[124] @ 7936
	.word	0411d6d9ah,08263736dh		; a[125] @ 8000
	.word	041032985h,0d5c34b44h		; a[126] @ 8064
	.word	0411cedc7h,0a32d905ch		; a[127] @ 8128
	.word	04129812dh,048bdf315h		; a[128] @ 8192
	.word	041129a29h,038776816h		; a[129] @ 8256
	.word	04115f77ah,036283177h		; a[130] @ 8320
	.word	0412d6f9fh,0cab1df0bh		; a[131] @ 8384
	.word	040f0ab74h,0dd9b3652h		; a[132] @ 8448
	.word	0411c807fh,0eb1cb542h		; a[133] @ 8512
	.word	040cc3746h,0358298cch		; a[134] @ 8576
	.word	0410ea824h,0889019beh		; a[135] @ 8640
	.word	04116058dh,013570245h		; a[136] @ 8704
	.word	041207ebah,05f3962f8h		; a[137] @ 8768
	.word	0412662dfh,07784a292h		; a[138] @ 8832
	.word	04126032bh,0de42e481h		; a[139] @ 8896
	.word	04122f0bah,0a9843584h		; a[140] @ 8960
	.word	04125c376h,029e55f6bh		; a[141] @ 9024
	.word	04125d212h,056059063h		; a[142] @ 9088
	.word	04115aedeh,06f709b74h		; a[143] @ 9152
	.word	04114828dh,0472cf95dh		; a[144] @ 9216
	.word	041271e58h,02c63d669h		; a[145] @ 9280
	.word	04127393ah,0a8c63503h		; a[146] @ 9344
	.word	04125ad0eh,01bb27533h		; a[147] @ 9408
	.word	04122c68ch,039424448h		; a[148] @ 9472
	.word	040de77b6h,04f9350aah		; a[149] @ 9536
	.word	0410f12b9h,056818ee1h		; a[150] @ 9600
	.word	0412d2addh,086d34ec7h		; a[151] @ 9664
	.word	041009132h,08800218eh		; a[152] @ 9728
	.word	0411e8200h,0e4cb0b2ch		; a[153] @ 9792
	.word	041065c4eh,01dc69220h		; a[154] @ 9856
	.word	04129d164h,09e73c199h		; a[155] @ 9920
	.word	04105e20ch,07add6678h		; a[156] @ 9984
	.word	04125e94ch,02ca08cd3h		; a[157] @ 10048
	.word	040fd155fh,046177136h		; a[158] @ 10112
	.word	0412673fah,0d08bc317h		; a[159] @ 10176
	.word	04122b1d8h,09eb862b2h		; a[160] @ 10240
	.word	041292d49h,0ebcbdc0ch		; a[161] @ 10304
	.word	0410cb5f4h,05ccdd93ch		; a[162] @ 10368
	.word	041215912h,08cb62698h		; a[163] @ 10432
	.word	0412bca10h,0375d38c0h		; a[164] @ 10496
	.word	04121963fh,07c47c668h		; a[165] @ 10560
	.word	041125a31h,0abfd5022h		; a[166] @ 10624
	.word	0412abe7fh,0a8e9e93dh		; a[167] @ 10688
	.word	04100ba0bh,099d3b0edh		; a[168] @ 10752
	.word	04111db71h,08f901df0h		; a[169] @ 10816
	.word	04124335eh,0db7a94f2h		; a[170] @ 10880
	.word	0412869a2h,063604692h		; a[171] @ 10944
	.word	0412cd115h,0275455c3h		; a[172] @ 11008
	.word	0412bac92h,0f44a2fcfh		; a[173] @ 11072
	.word	041112c55h,0bb38d60ah		; a[174] @ 11136
	.word	040e9d28ch,0bb729cd6h		; a[175] @ 11200
	.word	04121bdbfh,0e795266dh		; a[176] @ 11264
	.word	0412cf1f6h,081c81400h		; a[177] @ 11328
	.word	041258dd1h,055e6d084h		; a[178] @ 11392
	.word	0412d71a7h,09ec9e8edh		; a[179] @ 11456
	.word	0412b096bh,0887ecc8fh		; a[180] @ 11520
	.word	0411fbf65h,024b6dbcah		; a[181] @ 11584
	.word	040efab9fh,0985a3429h		; a[182] @ 11648
	.word	0411b02a0h,0c486cebch		; a[183] @ 11712
	.word	0411215f1h,09c87f603h		; a[184] @ 11776
	.word	04114c8b2h,0bb6df902h		; a[185] @ 11840
	.word	040f8c07fh,00bcabed6h		; a[186] @ 11904
	.word	0412e4faeh,088fce091h		; a[187] @ 11968
	.word	04129daddh,09732c478h		; a[188] @ 12032
	.word	04125c370h,0782c17b6h		; a[189] @ 12096
	.word	0410045f7h,0a624dd2fh		; a[190] @ 12160
	.word	041261c92h,0fa3cb817h		; a[191] @ 12224
	.word	041035079h,0f824b9f4h		; a[192] @ 12288
	.word	041204d21h,0427dd94ah		; a[193] @ 12352
	.word	040f5106fh,060e42b8eh		; a[194] @ 12416
	.word	041135db2h,0a67f9e46h		; a[195] @ 12480
	.word	0411b30a1h,09e395663h		; a[196] @ 12544
	.word	04111d92bh,038aae445h		; a[197] @ 12608
	.word	0411d3709h,026e8f953h		; a[198] @ 12672
	.word	040f1a205h,0aa1130aah		; a[199] @ 12736
	.word	04120292bh,0c7b2788eh		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\173162 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\173164 
	.sect	".text:optci"
	.clink

;******************************************************************************
;* FUNCTION NAME: logdp_asinhdp_i                                             *
;*                                                                            *
;*   Regs Modified     : A0,A3,A4,A5,A6,A7,A8,A9,B0,B1,B4,B5,B6,B7,B8,B9,A16, *
;*                           A17,A18,A19,A20,A21,A22,A23,A24,A25,B16,B17      *
;*   Regs Used         : A0,A3,A4,A5,A6,A7,A8,A9,B0,B1,B3,B4,B5,B6,B7,B8,B9,  *
;*                           A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,B16,B17  *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
logdp_asinhdp_i:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 149
           CLR     .S1     A5,20,31,A3       ; |114| 

           ZERO    .L2     B5
||         EXTU    .S1     A5,1,21,A0        ; |109| 

           SET     .S2     B5,0x15,0x1d,B5
||         SET     .S1     A3,21,29,A9       ; |114| 
||         MV      .L1     A4,A8             ; |114| 
||         ZERO    .L2     B4                ; |120| 

   [!A0]   ZERO    .L1     A9:A8             ; |117| 
           FSUBDP  .L1X    A9:A8,B5:B4,A7:A6 ; |120| 
           MVKL    .S2     0x3fe6a09e,B7
           MVKL    .S2     0x667f3bcd,B6

           FSUBDP  .L1X    A7:A6,B5:B4,A17:A16 ; |120| 
||         MVKH    .S2     0x3fe6a09e,B7

           MVKH    .S2     0x667f3bcd,B6
           CMPGTDP .S2X    A9:A8,B7:B6,B0    ; |126| 

           MV      .L1X    B5,A19            ; |120| 
||         ZERO    .S1     A18               ; |120| 

   [!B0]   DADD    .L1     0,A7:A6,A17:A16   ; |127| 
||         FMPYDP  .M1     A19:A18,A9:A8,A7:A6 ; |121| 

           MV      .L2     B5,B7             ; |120| 
   [!B0]   FMPYDP  .M2X    B5:B4,A17:A16,B9:B8 ; |128| 
           ZERO    .L2     B6                ; |120| 
           MVKL    .S1     0xc041d580,A9
           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |121| 
   [!B0]   FADDDP  .L2     B7:B6,B9:B8,B5:B4 ; |128| 
           ZERO    .S2     B9
           SET     .S2     B9,0x1e,0x1e,B9
           RCPDP   .S2     B5:B4,B7:B6       ; |68| 
           MV      .L2X    A18,B8            ; |68| 
           FMPYDP  .M2     B5:B4,B7:B6,B17:B16 ; |68| 
           MVKL    .S1     0x4b67ce0f,A8
           MVKH    .S1     0xc041d580,A9
           MVKH    .S1     0x4b67ce0f,A8
           FSUBDP  .L2     B9:B8,B17:B16,B17:B16 ; |68| 
           MV      .L1X    B9,A21            ; |68| 
           ZERO    .L1     A20               ; |66| 
           FMPYDP  .M2     B7:B6,B17:B16,B7:B6 ; |68| 
           MVK     .S1     1022,A3           ; |109| 
           SUB     .L1     A0,A3,A3          ; |109| 
   [!B0]   SUB     .L1     A3,1,A3           ; |129| 
           FMPYDP  .M2     B5:B4,B7:B6,B17:B16 ; |68| 
           NOP             3
           FSUBDP  .L2     B9:B8,B17:B16,B17:B16 ; |68| 
           NOP             2
           FMPYDP  .M2     B7:B6,B17:B16,B7:B6 ; |68| 
           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |68| 
           NOP             3
           FSUBDP  .L2     B9:B8,B5:B4,B5:B4 ; |68| 
           ZERO    .L2     B8                ; |66| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |68| 
           MVKL    .S2     0xb356bd29,B6
           MVKL    .S2     0xbfe94415,B7
           MVKH    .S2     0xb356bd29,B6
           MVKH    .S2     0xbfe94415,B7
           FMPYDP  .M1X    A17:A16,B5:B4,A7:A6 ; |68| 
           ZERO    .L2     B5:B4             ; |70| 
           CMPEQDP .S2X    A17:A16,B5:B4,B1  ; |70| 
           MVKL    .S1     0xc0880bfe,A17
   [ B1]   ZERO    .L1     A7:A6             ; |71| 
           DADD    .L1     0,A7:A6,A19:A18   ; |74| 
           FMPYDP  .M1     A19:A18,A19:A18,A7:A6 ; |133| 
           MVKL    .S2     0x40738083,B5
           MVKL    .S2     0xfa15267e,B4
           MVKH    .S2     0x40738083,B5
           FADDDP  .L1     A9:A8,A7:A6,A9:A8 ; |66| 
           MVKH    .S2     0xfa15267e,B4
           MVKL    .S1     0x9c0d9077,A16
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |66| 
           MVKH    .S1     0xc0880bfe,A17
           MVKH    .S1     0x9c0d9077,A16
           NOP             1
           FADDDP  .L1X    B5:B4,A9:A8,A9:A8 ; |66| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |66| 
           NOP             3
           FADDDP  .L1     A17:A16,A9:A8,A25:A24 ; |66| 
           NOP             2
           RCPDP   .S1     A25:A24,A9:A8     ; |66| 
           NOP             1
           FMPYDP  .M1     A9:A8,A25:A24,A17:A16 ; |66| 
           NOP             3
           FSUBDP  .L1     A21:A20,A17:A16,A17:A16 ; |66| 
           MVKL    .S1     0x2016afed,A20
           MVKL    .S1     0x4030624a,A21
           FMPYDP  .M1     A9:A8,A17:A16,A9:A8 ; |66| 
           MVKH    .S1     0x2016afed,A20
           MVKH    .S1     0x4030624a,A21
           NOP             1
           FMPYDP  .M1     A9:A8,A25:A24,A17:A16 ; |66| 
           NOP             4
           FSUBDP  .L2X    B9:B8,A17:A16,B5:B4 ; |66| 
           FMPYDP  .M1X    B7:B6,A7:A6,A17:A16 ; |68| 
           ZERO    .S2     B8                ; |68| 
           MVKL    .S2     0x12b3b59a,B6
           FMPYDP  .M1X    A9:A8,B5:B4,A23:A22 ; |66| 
           FADDDP  .L1     A21:A20,A17:A16,A17:A16 ; |68| 
           MVKL    .S2     0xc05007ff,B7
           MVKH    .S2     0x12b3b59a,B6
           FMPYDP  .M1     A23:A22,A25:A24,A9:A8 ; |68| 
           FMPYDP  .M1     A7:A6,A17:A16,A17:A16 ; |68| 
           MVKH    .S2     0xc05007ff,B7
           NOP             2
           FSUBDP  .L2X    B9:B8,A9:A8,B5:B4 ; |68| 
           FADDDP  .L2X    B7:B6,A17:A16,B7:B6 ; |68| 
           ZERO    .L1     A9:A8             ; |70| 
           FMPYDP  .M2X    A23:A22,B5:B4,B5:B4 ; |68| 
           CMPEQDP .S2X    B7:B6,A9:A8,B1    ; |70| 
           INTDP   .L1     A3,A17:A16        ; |139| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |68| 
           NOP             3
   [ B1]   ZERO    .L2     B5:B4             ; |71| 
           NOP             1
           FMPYDP  .M1X    A7:A6,B5:B4,A9:A8 ; |139| 
           MVKL    .S1     0xbf2bd010,A7
           MVKL    .S1     0x5c610ca8,A6
           MVKH    .S1     0xbf2bd010,A7
           FMPYDP  .M1     A19:A18,A9:A8,A9:A8 ; |139| 
           MVKH    .S1     0x5c610ca8,A6
           FMPYDP  .M1     A7:A6,A17:A16,A7:A6 ; |139| 
           MVKL    .S2     0x3fe63000,B5
           FADDDP  .L1     A9:A8,A19:A18,A9:A8 ; |139| 

           MVKH    .S2     0x3fe63000,B5
||         ZERO    .L2     B4                ; |139| 

           NOP             1
           FMPYDP  .M1X    B5:B4,A17:A16,A17:A16 ; |139| 
           FADDDP  .L1     A9:A8,A7:A6,A9:A8 ; |139| 
           MVKL    .S1     0x7fefffff,A7

           MVKH    .S1     0x7fefffff,A7
||         MVK     .D1     0xffffffff,A6     ; |141| 

           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |141| 
||         FADDDP  .L1     A17:A16,A9:A8,A5:A4 ; |139| 

           RETNOP  .S2     B3,1              ; |146| 
   [ A0]   MVKL    .S1     0xfefa39ef,A4
   [ A0]   MVKL    .S1     0x40862e42,A5
   [ A0]   MVKH    .S1     0xfefa39ef,A4
   [ A0]   MVKH    .S1     0x40862e42,A5
           ; BRANCH OCCURS {B3}              ; |146| 
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
;*   Local Frame Size  : 8 Args + 140 Auto + 56 Save = 204 byte               *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           STW     .D2T1   A11,*SP--(8)      ; |141| 
           STW     .D2T1   A10,*SP--(8)      ; |141| 
           STDW    .D2T2   B13:B12,*SP--     ; |141| 
           STDW    .D2T2   B11:B10,*SP--     ; |141| 
           STDW    .D2T1   A15:A14,*SP--     ; |141| 
           STDW    .D2T1   A13:A12,*SP--     ; |141| 
           STW     .D2T2   B3,*SP--(8)       ; |141| 

           MVKL    .S1     $C$SL1+0,A4
||         ADDK    .S2     -152,SP           ; |141| 

           CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           MVKL    .S1     a,A10
           MVKH    .S1     a,A10

           CALL    .S2     asinh             ; |158| 
||         MV      .L1     A10,A11
||         ZERO    .L2     B10
||         MVK     .S1     0xc9,A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |158| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |158| 
$C$RL1:    ; CALL OCCURS {asinh} {0}         ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A12,1,A0          ; |157| 
||         SUB     .S1     A12,1,A12         ; |157| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |158| 
   [ A0]   BNOP    .S1     $C$L1,3           ; |157| 

           ADD     .L2     B10,B4,B4         ; |158| 
||         ADD     .S2     8,B10,B10         ; |157| 

   [ A0]   CALL    .S1     asinh             ; |158| 
||         STDW    .D2T1   A5:A4,*B4         ; |158| 
|| [!A0]   MVKL    .S2     output,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           MVKH    .S2     output,B4
||         ZERO    .L2     B10
||         MV      .L1     A10,A14
||         MVK     .S1     0xc9,A11

           ADD     .L2     4,B4,B11
||         CALL    .S1     asinhdp           ; |161| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |161| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |161| 
$C$RL2:    ; CALL OCCURS {asinhdp} {0}       ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |161| 
||         SUB     .L1     A11,1,A0          ; |160| 
||         SUB     .S1     A11,1,A11         ; |160| 

   [ A0]   BNOP    .S2     $C$L2,3           ; |160| 
|| [!A0]   MVK     .S1     0xc9,A10
|| [!A0]   MV      .L1     A14,A11

           ADD     .L2     B10,B4,B4         ; |161| 
||         ADD     .S2     8,B10,B10         ; |160| 

   [ A0]   CALL    .S1     asinhdp           ; |161| 
|| [!A0]   ADD     .L2     4,B11,B10
|| [!A0]   ZERO    .S2     B11
||         STDW    .D2T1   A5:A4,*B4         ; |161| 

           ; BRANCHCC OCCURS {$C$L2}         ; |160| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     asinhdp_c         ; |164| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |164| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |164| 
$C$RL3:    ; CALL OCCURS {asinhdp_c} {0}     ; |164| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B10,B4           ; |164| 
||         SUB     .L1     A10,1,A0          ; |163| 
||         SUB     .S1     A10,1,A10         ; |163| 

   [ A0]   BNOP    .S1     $C$L3,3           ; |163| 

           ADD     .L2     B11,B4,B4         ; |164| 
||         ADD     .S2     8,B11,B11         ; |163| 

   [ A0]   CALL    .S1     asinhdp_c         ; |164| 
||         STDW    .D2T1   A5:A4,*B4         ; |164| 

           ; BRANCHCC OCCURS {$C$L3}         ; |163| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23

           ZERO    .L1     A4
||         ZERO    .D1     A3
||         MVKL    .S1     0x3fd33333,A5
||         MVKL    .S2     0x3fb3335d,B4
||         ZERO    .L2     B24               ; |173| 
||         ZERO    .D2     B20               ; |173| 

           SET     .S1     A4,0x15,0x1d,A4
||         MVKL    .S2     0x9b04cad8,B31
||         ZERO    .L1     A7                ; |173| 
||         ZERO    .D1     A13
||         ZERO    .L2     B28               ; |173| 
||         ZERO    .D2     B18               ; |173| 

           SET     .S1     A3,0x13,0x1d,A3
||         MVKL    .S2     0xbfc55555,B30
||         ZERO    .L1     A22               ; |173| 
||         STW     .D2T1   A4,*+SP(40)       ; |173| 
||         MV      .D1     A4,A11            ; |173| 
||         ZERO    .L2     B22               ; |173| 

           MVKL    .S1     0x33333333,A31
||         MVKL    .S2     0x8d02093f,B27
||         STW     .D2T1   A3,*+SP(32)       ; |173| 
||         MV      .L2X    A4,B25            ; |173| 
||         ZERO    .L1     A10               ; |173| 
||         ZERO    .D1     A12               ; |173| 

           MVKL    .S1     0x3fe62e42,A30
||         MVKH    .S2     0x3fb3335d,B4
||         STW     .D2T1   A7,*+SP(36)       ; |173| 
||         MV      .L2X    A4,B21            ; |173| 
||         MV      .L1     A14,A1

           MVKL    .S1     0xfefa39ec,A29
||         MVKH    .S2     0x9b04cad8,B31
||         STW     .D2T2   B4,*+SP(72)       ; |241| 
||         MV      .L2X    A4,B19            ; |173| 

           MVKL    .S1     0xbf978498,A28
||         MVKH    .S2     0xbfc55555,B30
||         STW     .D2T2   B31,*+SP(76)      ; |241| 
||         MV      .L2X    A3,B29

           MVKL    .S1     0x92c0541a,A27
||         MVKH    .S2     0x8d02093f,B27
||         STW     .D2T2   B30,*+SP(80)      ; |241| 
||         MV      .L2X    A3,B23

           MVKL    .S1     0x3f9fd78f,A26
||         STW     .D2T2   B27,*+SP(84)      ; |241| 
||         MVK     .S2     0xc9,B2
||         ZERO    .L2     B26               ; |173| 

           MVKL    .S1     0x2884c094,A25
||         STW     .D2T1   A22,*+SP(44)      ; |173| 
||         ADD     .L2     4,B10,B11

           MVKL    .S1     0xbfa6e4ec,A24
           MVKL    .S1     0x93a79b50,A23
           MVKH    .S1     0x3fd33333,A5

           MVKH    .S1     0x33333333,A31
||         STW     .D2T1   A5,*+SP(96)       ; |250| 

           MVKH    .S1     0x3fe62e42,A30
||         STW     .D2T1   A31,*+SP(100)     ; |250| 

           MVKH    .S1     0xfefa39ec,A29
||         STW     .D2T1   A30,*+SP(88)      ; |247| 

           MVKH    .S1     0xbf978498,A28
||         STW     .D2T1   A29,*+SP(92)      ; |247| 

           MVKH    .S1     0x92c0541a,A27
||         STW     .D2T1   A28,*+SP(48)      ; |241| 

           MVKH    .S1     0x3f9fd78f,A26
||         STW     .D2T1   A27,*+SP(52)      ; |241| 

           MVKH    .S1     0x2884c094,A25
||         STW     .D2T1   A26,*+SP(56)      ; |241| 

           MVKH    .S1     0xbfa6e4ec,A24
||         STW     .D2T1   A25,*+SP(60)      ; |241| 

           MVKH    .S1     0x93a79b50,A23
||         STW     .D2T1   A24,*+SP(64)      ; |241| 

           STW     .D2T1   A23,*+SP(68)      ; |241| 
||         SET     .S1     A13,0x14,0x1d,A13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 81
           LDDW    .D1T1   *A1++,A29:A28     ; |167| 
           NOP             4
           FMPYDP  .M1     A29:A28,A29:A28,A31:A30 ; |230| 
           ABSDP   .S1     A29:A28,A27:A26   ; |223| 
           NOP             2
           FADDDP  .L1     A13:A12,A31:A30,A5:A4 ; |173| 
           NOP             2
           RSQRDP  .S1     A5:A4,A9:A8       ; |173| 
           NOP             1
           FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |173| 
           NOP             3

           FMPYDP  .M1     A9:A8,A7:A6,A17:A16 ; |173| 
||         LDDW    .D2T1   *+SP(40),A7:A6

           NOP             4

           FMPYDP  .M1     A7:A6,A17:A16,A17:A16 ; |173| 
||         LDDW    .D2T1   *+SP(32),A7:A6

           NOP             4
           FSUBDP  .L1     A7:A6,A17:A16,A7:A6 ; |173| 
           DADD    .L1X    0,B25:B24,A17:A16
           NOP             1
           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |173| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |173| 
           NOP             3
           FMPYDP  .M1     A9:A8,A7:A6,A7:A6 ; |173| 
           NOP             3
           FMPYDP  .M1     A17:A16,A7:A6,A17:A16 ; |173| 
           DADD    .L1X    0,B29:B28,A7:A6
           NOP             2
           FSUBDP  .L1     A7:A6,A17:A16,A7:A6 ; |173| 
           DADD    .L1X    0,B21:B20,A17:A16
           NOP             1
           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |173| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |174| 
           NOP             3
           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |174| 
           NOP             3
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |174| 
           DADD    .L1X    0,B23:B22,A17:A16 ; |223| 
           NOP             2

           FSUBDP  .L1     A17:A16,A9:A8,A17:A16 ; |174| 
||         FMPYDP  .M1     A27:A26,A27:A26,A9:A8 ; |176| 

           NOP             2
           FMPYDP  .M1     A7:A6,A17:A16,A7:A6 ; |174| 
           CMPEQDP .S1     A5:A4,A9:A8,A0    ; |176| 
           FMPYDP  .M1     A11:A10,A27:A26,A5:A4 ; |247| 
           DADD    .L1X    0,B19:B18,A9:A8   ; |177| 
   [ A0]   DADD    .L1     0,A27:A26,A7:A6   ; |177| 
           FMPYDP  .M1     A9:A8,A7:A6,A7:A6 ; |247| 
           CALL    .S1     logdp_asinhdp_i   ; |247| 
           ADDKPC  .S2     $C$RL4,B3,1       ; |247| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |247| 
           NOP             2
$C$RL4:    ; CALL OCCURS {logdp_asinhdp_i} {0}  ; |247| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 37
           FMPYDP  .M1     A31:A30,A31:A30,A9:A8 ; |231| 
           LDDW    .D2T2   *+SP(80),B5:B4    ; |241| 
           LDDW    .D2T1   *+SP(56),A7:A6
           SUB     .L2     B2,1,B2           ; |166| 
           FMPYDP  .M1     A9:A8,A9:A8,A19:A18 ; |233| 
           FMPYDP  .M1     A31:A30,A9:A8,A17:A16 ; |232| 
           FMPYDP  .M2X    B5:B4,A31:A30,B7:B6 ; |241| 
           LDDW    .D2T2   *+SP(72),B5:B4    ; |241| 

           FMPYDP  .M1     A7:A6,A19:A18,A19:A18 ; |241| 
||         LDDW    .D2T1   *+SP(64),A7:A6    ; |241| 

   [!B2]   MVKL    .S2     output,B10
           LDW     .D2T2   *B11,B27          ; |167| 
   [!B2]   MVKH    .S2     output,B10
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |241| 
           FMPYDP  .M1     A7:A6,A17:A16,A7:A6 ; |241| 
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |234| 
           LDDW    .D2T1   *+SP(48),A17:A16
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |241| 
           FADDDP  .L1     A19:A18,A7:A6,A7:A6 ; |241| 
           LDDW    .D2T1   *+SP(96),A19:A18
           ZERO    .L2     B7:B6             ; |226| 
           NOP             1

           FMPYDP  .M1     A17:A16,A9:A8,A7:A6 ; |241| 
||         FADDDP  .L2X    A7:A6,B5:B4,B5:B4 ; |241| 

           CMPLTDP .S2X    A29:A28,B7:B6,B0  ; |226| 
           CMPGTDP .S1     A27:A26,A19:A18,A0 ; |250| 
           LDDW    .D2T1   *+SP(88),A17:A16

           FADDDP  .L1X    A7:A6,B5:B4,A9:A8 ; |241| 
|| [ B0]   ZERO    .S1     A7
|| [!B0]   MV      .D1     A13,A7            ; |226| 

   [!B0]   ZERO    .L1     A6                ; |226| 
   [ B0]   MVKH    .S1     0xbff00000,A7
           FMPYDP  .M1     A29:A28,A9:A8,A9:A8 ; |241| 
           FADDDP  .L1     A17:A16,A5:A4,A5:A4 ; |247| 
   [ B0]   ZERO    .L1     A6                ; |226| 
   [ B2]   B       .S1     $C$L4             ; |166| 

           FADDDP  .L1     A29:A28,A9:A8,A9:A8 ; |241| 
|| [ A0]   FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |251| 

           ADD     .L2     B26,B27,B4        ; |167| 
           ADD     .L2     8,B26,B26         ; |166| 
           NOP             1

   [!B2]   CALL    .S1     asinhdp_v         ; |169| 
||         STDW    .D2T1   A9:A8,*B4         ; |167| 

           ; BRANCHCC OCCURS {$C$L4}         ; |166| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B10(16),B4      ; |169| 
           MVK     .S1     0xc9,A6           ; |169| 
           MV      .L1     A14,A4            ; |169| 
           ADDKPC  .S2     $C$RL5,B3,1       ; |169| 
$C$RL5:    ; CALL OCCURS {asinhdp_v} {0}     ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0xd9d7bdbb,B6

           MV      .L2     B10,B5            ; |67| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           ADD     .L1X    4,B11,A15
||         MV      .L2     B10,B4
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A15,B4           ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL9:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S1     fcn_pass,A3
           MVKH    .S1     fcn_pass,A3
           ADD     .L1     4,A3,A14
           LDW     .D1T1   *A14,A0           ; |72| 
           MV      .L2X    A3,B5             ; |72| 
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           ADD     .L2X    8,A3,B4
           STW     .D2T2   B4,*+SP(16)       ; |69| 

   [!A0]   B       .S1     $C$L5             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |173| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S2     all_pass,B5
   [!A0]   MV      .L2X    A10,B4
   [!A0]   MVKH    .S2     all_pass,B5
           ; BRANCHCC OCCURS {$C$L5}         ; |72| 
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
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   MV      .L2X    A10,B4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |173| 
           MVKL    .S2     all_pass,B5
           MVKH    .S2     all_pass,B5
           NOP             2
;** --------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |173| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL10,B3,0      ; |173| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           MVKL    .S2     a_sc,B4

           MVKH    .S2     a_sc,B4
||         MVK     .L2     0xffffffff,B7     ; |187| 

           STDW    .D2T1   A13:A12,*+B4(32)  ; |184| 
||         MV      .L2     B7,B6             ; |187| 
||         ZERO    .S2     B9

           STDW    .D2T2   B7:B6,*+B4(56)    ; |187| 
||         MVKH    .S2     0xbff00000,B9
||         ZERO    .L1     A9
||         ZERO    .L2     B8                ; |185| 

           STDW    .D2T2   B9:B8,*+B4(40)    ; |185| 
||         MVKH    .S1     0xfff00000,A9
||         ZERO    .L2     B17
||         ZERO    .L1     A8                ; |183| 

           STDW    .D2T1   A9:A8,*+B4(24)    ; |183| 
||         SET     .S2     B17,0x14,0x1e,B17
||         ZERO    .L1     A5
||         ZERO    .L2     B16               ; |182| 

           STDW    .D2T2   B17:B16,*+B4(16)  ; |182| 
||         MVKH    .S1     0x80000000,A5
||         ZERO    .L1     A4                ; |181| 

           STDW    .D2T1   A5:A4,*+B4(8)     ; |181| 
||         ADD     .L1     -1,A5,A7
||         MV      .S1X    B7,A6
||         ZERO    .D1     A10               ; |189| 

           ZERO    .L2     B7:B6             ; |180| 
||         STDW    .D2T1   A7:A6,*+B4(48)    ; |186| 

           CMPEQ   .L2X    A10,3,B4          ; |191| 
||         STDW    .D2T2   B7:B6,*B4         ; |180| 
||         MV      .L1X    B4,A11            ; |182| 

           CMPEQ   .L1     A10,2,A3          ; |191| 
           OR      .L1X    B4,A3,A0          ; |191| 
   [!A0]   B       .S1     $C$L7             ; |191| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 5

   [ A0]   CALL    .S1     asinhdp_c         ; |191| 
|| [ A0]   LDDW    .D1T1   *A11,A5:A4        ; |191| 

   [!A0]   CALL    .S1     asinh             ; |191| 
   [!A0]   LDDW    .D1T1   *A11,A5:A4        ; |191| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L7}         ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL11,B3,0      ; |191| 
$C$RL11:   ; CALL OCCURS {asinhdp_c} {0}     ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           BNOP    .S1     $C$L8,4           ; |191| 
||         LDW     .D2T1   *B10,A3           ; |191| 

           CALL    .S1     asinhdp           ; |192| 
||         STDW    .D1T1   A5:A4,*+A3[A10]   ; |191| 

           ; BRANCH OCCURS {$C$L8}           ; |191| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 8
           ADDKPC  .S2     $C$RL12,B3,1      ; |191| 
$C$RL12:   ; CALL OCCURS {asinh} {0}         ; |191| 
           LDW     .D2T1   *B10,A3           ; |191| 
           NOP             4

           STDW    .D1T1   A5:A4,*+A3[A10]   ; |191| 
||         CALL    .S1     asinhdp           ; |192| 

;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11,A5:A4        ; |192| 
           ADDKPC  .S2     $C$RL13,B3,3      ; |192| 
$C$RL13:   ; CALL OCCURS {asinhdp} {0}       ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 104
           LDW     .D2T1   *+B10(4),A3       ; |192| 
           NOP             4
           STDW    .D1T1   A5:A4,*+A3[A10]   ; |192| 

           CALLP   .S2     asinhdp_c,B3
||         LDDW    .D1T1   *A11,A5:A4        ; |193| 

$C$RL14:   ; CALL OCCURS {asinhdp_c} {0}     ; |193| 
           LDW     .D2T1   *+B10(8),A3       ; |193| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |193| 
           MV      .L1     A13,A5            ; |230| 
           MV      .L1     A12,A4            ; |230| 
           ZERO    .L2     B31
           STDW    .D1T2   B5:B4,*+A3[A10]   ; |193| 
           LDDW    .D1T1   *A11++,A29:A28    ; |194| 
           SET     .S2     B31,0x15,0x1d,B5
           MV      .L2X    A12,B4            ; |173| 
           ZERO    .L2     B7
           SET     .S2     B7,0x13,0x1d,B7
           FMPYDP  .M1     A29:A28,A29:A28,A31:A30 ; |230| 
           MV      .L2X    A12,B6            ; |173| 
           ZERO    .L1     A27
           ZERO    .L1     A26
           FADDDP  .L1     A5:A4,A31:A30,A5:A4 ; |173| 
           ZERO    .L2     B9
           SET     .S2     B9,0x15,0x1d,B9
           RSQRDP  .S1     A5:A4,A7:A6       ; |173| 
           MV      .L2X    A12,B8            ; |174| 
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |173| 
           ZERO    .L2     B30
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |173| 
           NOP             4
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |173| 
           SET     .S1     A26,0x13,0x1d,A9
           MV      .L1     A12,A8            ; |173| 
           NOP             1
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |173| 
           NOP             2
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |173| 
           SET     .S1     A27,0x15,0x1d,A7
           MV      .L1     A12,A6            ; |173| 
           ABSDP   .S1     A29:A28,A27:A26   ; |223| 
           FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |173| 
           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |173| 
           NOP             4
           FMPYDP  .M1X    A7:A6,B7:B6,A7:A6 ; |173| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |173| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |173| 
           FMPYDP  .M1     A27:A26,A27:A26,A7:A6 ; |176| 
           NOP             2
           FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |174| 
           CMPEQDP .S1     A5:A4,A7:A6,A0    ; |176| 
           MV      .L1     A8,A4             ; |247| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |174| 
           NOP             3
           FMPYDP  .M2     B9:B8,B7:B6,B7:B6 ; |174| 
           MV      .L2X    A9,B9             ; |174| 
           NOP             2
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |174| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |174| 
           SET     .S2     B30,0x15,0x1d,B7
           MV      .L2     B8,B6             ; |177| 
           MV      .L1X    B7,A5             ; |247| 
   [ A0]   DADD    .L2X    0,A27:A26,B5:B4   ; |177| 
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |247| 
           FMPYDP  .M1     A5:A4,A27:A26,A5:A4 ; |247| 
           NOP             3

           CALLP   .S2     logdp_asinhdp_i,B3
||         FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |247| 

$C$RL15:   ; CALL OCCURS {logdp_asinhdp_i} {0}  ; |247| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42

           FMPYDP  .M1     A31:A30,A31:A30,A7:A6 ; |231| 
||         MVKL    .S2     0x8d02093f,B4
||         MVKL    .S1     0x2884c094,A18

           MVKL    .S2     0xbfc55555,B5
||         MVKL    .S1     0x3f9fd78f,A19

           MVKH    .S2     0x8d02093f,B4
||         MVKH    .S1     0x2884c094,A18

           MVKH    .S2     0xbfc55555,B5
||         MVKH    .S1     0x3f9fd78f,A19

           FMPYDP  .M1     A31:A30,A7:A6,A9:A8 ; |232| 
||         MVKL    .S2     0x93a79b50,B8
||         MVK     .S1     12,A3

           FMPYDP  .M1     A7:A6,A7:A6,A21:A20 ; |233| 
||         MVKL    .S2     0xbfa6e4ec,B9
||         ADD     .L1X    B10,A3,A3

           MVKH    .S2     0x93a79b50,B8
||         FMPYDP  .M1X    B5:B4,A31:A30,A17:A16 ; |241| 

           MVKH    .S2     0xbfa6e4ec,B9
           MVKL    .S2     0x3fb3335d,B7

           FMPYDP  .M2X    B9:B8,A9:A8,B5:B4 ; |241| 
||         MVKL    .S2     0x9b04cad8,B6
||         FMPYDP  .M1     A19:A18,A21:A20,A19:A18 ; |241| 
||         MVKL    .S1     0xbf978498,A21

           MVKH    .S2     0x3fb3335d,B7
||         MVKL    .S1     0x92c0541a,A20

           MVKH    .S2     0x9b04cad8,B6
||         MVKH    .S1     0xbf978498,A21

           MVKH    .S1     0x92c0541a,A20
           FMPYDP  .M1X    B7:B6,A7:A6,A23:A22 ; |241| 

           FADDDP  .L1X    A19:A18,B5:B4,A9:A8 ; |241| 
||         FMPYDP  .M1     A9:A8,A7:A6,A19:A18 ; |234| 
||         ZERO    .L2     B5:B4             ; |226| 
||         MVKL    .S1     0xfefa39ec,A6

           CMPLTDP .S2X    A29:A28,B5:B4,B0  ; |226| 
||         MVKL    .S1     0x3fe62e42,A7

           MVKH    .S1     0xfefa39ec,A6

           FADDDP  .L1     A23:A22,A17:A16,A17:A16 ; |241| 
||         MVKH    .S1     0x3fe62e42,A7
|| [ B0]   ZERO    .L2     B13
|| [!B0]   ZERO    .S2     B12               ; |226| 
|| [ B0]   ZERO    .D2     B12               ; |226| 

   [!B0]   MV      .L2X    A13,B13           ; |241| 
||         FMPYDP  .M1     A21:A20,A19:A18,A19:A18 ; |241| 

   [ B0]   MVKH    .S2     0xbff00000,B13
           FADDDP  .L1     A9:A8,A17:A16,A17:A16 ; |241| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |247| 
           MVKL    .S1     0x33333333,A8
           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |241| 
           MVKL    .S1     0x3fd33333,A9
           MVKH    .S1     0x33333333,A8
           FMPYDP  .M1     A29:A28,A17:A16,A17:A16 ; |241| 
           MVKH    .S1     0x3fd33333,A9
           CMPGTDP .S1     A27:A26,A9:A8,A0  ; |250| 
           LDW     .D1T1   *A3,A3            ; |194| 

           FADDDP  .L1     A29:A28,A17:A16,A7:A6 ; |241| 
|| [ A0]   FMPYDP  .M1X    B13:B12,A5:A4,A7:A6 ; |251| 

           NOP             3

           STDW    .D1T1   A7:A6,*+A3[A10]   ; |194| 
||         ADD     .L1     1,A10,A10         ; |189| 

           CMPLT   .L1     A10,8,A0          ; |189| 

   [ A0]   BNOP    .S1     $C$L6,2           ; |189| 
||         CMPEQ   .L2X    A10,3,B4          ; |191| 
|| [ A0]   CMPEQ   .L1     A10,2,A3          ; |191| 
||         MV      .D1     A0,A1             ; guard predicate rewrite

           OR      .L1X    B4,A3,A0          ; |191| 
   [!A1]   MVK     .L1     0x1,A0            ; |191| nullify predicate
   [!A0]   B       .S1     $C$L7             ; |191| 
           ; BRANCHCC OCCURS {$C$L6}         ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           MVKL    .S1     a_sc,A4

           CALLP   .S2     asinhdp_v,B3
||         LDW     .D2T2   *+B10(16),B4      ; |196| 
||         MVKH    .S1     a_sc,A4
||         MVK     .L1     0x8,A6            ; |196| 

$C$RL16:   ; CALL OCCURS {asinhdp_v} {0}     ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .L1     0x8,A6            ; |66| 
||         MVK     .S1     0x9,A8            ; |66| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .L1     0x8,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL18:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1X    B10,A3            ; |196| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .L1     0x8,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL19:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     fcn_pass,B4

           MVKH    .S2     0x3ddb7cdf,B7
||         STW     .D2T1   A15,*+SP(20)      ; |68| 

           MV      .L1     A15,A3            ; |196| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .L1     0x8,A6            ; |69| 
||         MVK     .S1     0x9,A8            ; |69| 

$C$RL20:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           MV      .L2X    A14,B4            ; |69| 
||         LDW     .D2T1   *+SP(16),A3
||         MVKL    .S2     fcn_pass,B31

           LDW     .D2T2   *B4,B0            ; |72| 
           MVKH    .S2     fcn_pass,B31
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           STW     .D2T2   B4,*+SP(24)       ; |69| 
           STW     .D2T1   A3,*+SP(28)       ; |72| 

   [!B0]   B       .S2     $C$L9             ; |72| 
|| [!B0]   MVKL    .S1     all_pass,A3
|| [ B0]   MV      .L2X    A3,B4
|| [!B0]   MV      .L1     A12,A4
||         MV      .D2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |200| 
|| [!B0]   MVKH    .S1     all_pass,A3
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   MV      .L1     A12,A4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |200| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |200| 
||         ADDKPC  .S2     $C$RL21,B3,0      ; |200| 

$C$RL21:   ; CALL OCCURS {print_test_results} {0}  ; |200| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 44
           LDW     .D2T1   *+SP(68),A23      ; |174| 
           LDW     .D2T1   *+SP(52),A27      ; |174| 
           LDW     .D2T1   *+SP(60),A25      ; |174| 
           LDW     .D2T1   *+SP(88),A30      ; |247| 
           LDW     .D2T1   *+SP(92),A29      ; |247| 
           LDW     .D2T1   *+SP(64),A24      ; |174| 
           LDW     .D2T1   *+SP(72),A22      ; |174| 
           LDW     .D2T1   *+SP(76),A21      ; |174| 
           LDW     .D2T1   *+SP(40),A19      ; |173| 
           LDW     .D2T1   *+SP(48),A28      ; |247| 
           LDW     .D2T2   *+SP(96),B13      ; |247| 
           LDW     .D2T1   *+SP(56),A26      ; |174| 

           LDW     .D2T2   *+SP(100),B12     ; |247| 
||         MV      .L1     A12,A7            ; |209| 

           LDW     .D2T1   *+SP(32),A20      ; |174| 
||         MV      .L1     A7,A18            ; |203| 

           STW     .D2T1   A18,*+SP(68)      ; |203| 
||         MV      .L1     A12,A4            ; |209| 

           STW     .D2T1   A4,*+SP(132)      ; |203| 

           STW     .D2T1   A7,*+SP(36)       ; |173| 
||         MVK     .S2     0x777,B31

           STW     .D2T2   B31,*+SP(12)      ; |203| 
||         MVKL    .S1     0xc000cccc,A3
||         MV      .L1     A12,A6            ; |209| 

           STW     .D2T1   A6,*+SP(52)       ; |173| 
||         MVKL    .S1     0xcccccccd,A31

           STW     .D2T1   A6,*+SP(60)       ; |173| 
||         MVKH    .S1     0xc000cccc,A3

           STW     .D2T1   A3,*+SP(144)      ; |209| 
||         MVKH    .S1     0xcccccccd,A31

           STW     .D2T1   A31,*+SP(148)     ; |209| 
           STW     .D2T1   A30,*+SP(120)     ; |247| 
           STW     .D2T1   A29,*+SP(124)     ; |247| 
           STW     .D2T1   A24,*+SP(104)     ; |174| 
           STW     .D2T1   A23,*+SP(108)     ; |174| 
           STW     .D2T1   A22,*+SP(112)     ; |174| 
           STW     .D2T1   A21,*+SP(116)     ; |174| 
           STW     .D2T1   A19,*+SP(128)     ; |173| 
           STW     .D2T1   A19,*+SP(136)     ; |173| 
           STW     .D2T1   A28,*+SP(88)      ; |174| 
           STW     .D2T1   A27,*+SP(92)      ; |174| 
           STW     .D2T1   A26,*+SP(96)      ; |174| 
           STW     .D2T1   A25,*+SP(100)     ; |174| 
           STW     .D2T1   A20,*+SP(64)      ; |173| 
           STW     .D2T1   A20,*+SP(48)      ; |173| 

           STW     .D2T1   A19,*+SP(56)      ; |173| 
||         MVKL    .S2     a_ext,B4
||         ZERO    .L1     A5

           STW     .D2T1   A19,*+SP(72)      ; |173| 
||         SET     .S1     A5,0x14,0x14,A5
||         MVKH    .S2     a_ext,B4

           STDW    .D2T1   A5:A4,*B4         ; |203| 
||         MV      .L1     A12,A18           ; |209| 

           STW     .D2T1   A18,*+SP(140)     ; |203| 
           STW     .D2T1   A18,*+SP(44)      ; |173| 

           CALL    .S1     asinh             ; |205| 
||         STW     .D2T1   A18,*+SP(76)      ; |173| 
||         MV      .L1X    B4,A10            ; |203| 

           LDDW    .D1T1   *A10,A5:A4        ; |205| 
           MV      .L2X    A12,B10
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 3
           ADDKPC  .S2     $C$RL22,B3,2      ; |205| 
$C$RL22:   ; CALL OCCURS {asinh} {0}         ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 133
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |205| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |205| 
           STDW    .D2T1   A5:A4,*B4         ; |205| 

           CALLP   .S2     asinhdp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |206| 

$C$RL23:   ; CALL OCCURS {asinhdp} {0}       ; |206| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |206| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |206| 
           STDW    .D2T1   A5:A4,*B4         ; |206| 

           CALLP   .S2     asinhdp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |207| 

$C$RL24:   ; CALL OCCURS {asinhdp_c} {0}     ; |207| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |207| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |207| 
           STDW    .D2T1   A5:A4,*B4         ; |207| 
           LDDW    .D1T1   *A10,A29:A28      ; |208| 
           NOP             4
           FMPYDP  .M1     A29:A28,A29:A28,A31:A30 ; |230| 
           ABSDP   .S1     A29:A28,A27:A26   ; |223| 
           NOP             2
           FADDDP  .L1     A13:A12,A31:A30,A5:A4 ; |173| 
           NOP             2
           RSQRDP  .S1     A5:A4,A9:A8       ; |173| 
           NOP             1
           FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |173| 
           NOP             3

           FMPYDP  .M1     A9:A8,A7:A6,A17:A16 ; |173| 
||         LDDW    .D2T1   *+SP(40),A7:A6

           NOP             4

           FMPYDP  .M1     A7:A6,A17:A16,A17:A16 ; |173| 
||         LDDW    .D2T1   *+SP(32),A7:A6

           NOP             4
           FSUBDP  .L1     A7:A6,A17:A16,A7:A6 ; |173| 
           NOP             2
           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |173| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |173| 
           NOP             3

           FMPYDP  .M1     A9:A8,A7:A6,A17:A16 ; |173| 
||         LDDW    .D2T1   *+SP(56),A7:A6

           NOP             4

           FMPYDP  .M1     A7:A6,A17:A16,A17:A16 ; |173| 
||         LDDW    .D2T1   *+SP(48),A7:A6

           NOP             4
           FSUBDP  .L1     A7:A6,A17:A16,A7:A6 ; |173| 
           NOP             2
           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |173| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |174| 
           NOP             3

           FMPYDP  .M1     A9:A8,A7:A6,A17:A16 ; |174| 
||         LDDW    .D2T1   *+SP(72),A9:A8

           NOP             4

           FMPYDP  .M1     A9:A8,A17:A16,A17:A16 ; |174| 
||         LDDW    .D2T1   *+SP(64),A9:A8    ; |223| 

           NOP             4

           FSUBDP  .L1     A9:A8,A17:A16,A17:A16 ; |174| 
||         FMPYDP  .M1     A27:A26,A27:A26,A9:A8 ; |176| 

           NOP             3

           CMPEQDP .S1     A5:A4,A9:A8,A0    ; |176| 
||         LDDW    .D2T1   *+SP(136),A5:A4

           FMPYDP  .M1     A7:A6,A17:A16,A7:A6 ; |174| 
           NOP             3

           FMPYDP  .M1     A5:A4,A27:A26,A9:A8 ; |247| 
||         LDDW    .D2T1   *+SP(128),A5:A4   ; |177| 

   [ A0]   DADD    .L1     0,A27:A26,A7:A6   ; |177| 
           NOP             3
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |247| 
           NOP             3

           CALLP   .S2     logdp_asinhdp_i,B3
||         FADDDP  .L1     A5:A4,A9:A8,A5:A4 ; |247| 

$C$RL25:   ; CALL OCCURS {logdp_asinhdp_i} {0}  ; |247| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 53
           FMPYDP  .M1     A31:A30,A31:A30,A9:A8 ; |231| 
           LDDW    .D2T1   *+SP(96),A7:A6
           LDDW    .D2T2   *+SP(80),B5:B4    ; |241| 
           LDDW    .D2T2   *+SP(112),B7:B6   ; |241| 
           FMPYDP  .M1     A9:A8,A9:A8,A19:A18 ; |233| 
           FMPYDP  .M1     A31:A30,A9:A8,A17:A16 ; |232| 
           CMPGTDP .S2X    A27:A26,B13:B12,B1 ; |250| 
           LDW     .D2T2   *B11,B29          ; |208| 

           FMPYDP  .M1     A7:A6,A19:A18,A19:A18 ; |241| 
||         LDDW    .D2T1   *+SP(104),A7:A6   ; |241| 

           FMPYDP  .M2X    B5:B4,A31:A30,B5:B4 ; |241| 
           FMPYDP  .M2X    B7:B6,A9:A8,B7:B6 ; |241| 
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |234| 
           NOP             1
           FMPYDP  .M1     A7:A6,A17:A16,A7:A6 ; |241| 
           LDDW    .D2T1   *+SP(88),A17:A16
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |241| 
           NOP             1
           FADDDP  .L1     A19:A18,A7:A6,A7:A6 ; |241| 
           NOP             3

           FADDDP  .L2X    A7:A6,B5:B4,B7:B6 ; |241| 
||         FMPYDP  .M1     A17:A16,A9:A8,A7:A6 ; |241| 

           ZERO    .L2     B5:B4             ; |226| 
           CMPLTDP .S2X    A29:A28,B5:B4,B0  ; |226| 
           ADD     .L2     B10,B29,B4        ; |208| 
           FADDDP  .L1X    A7:A6,B7:B6,A7:A6 ; |241| 
   [!B0]   MV      .L1     A13,A9            ; |241| 
   [ B0]   ZERO    .S1     A9

           FMPYDP  .M1     A29:A28,A7:A6,A17:A16 ; |241| 
||         LDDW    .D2T1   *+SP(120),A7:A6   ; |226| 

   [ B0]   ZERO    .L1     A8                ; |226| 
   [!B0]   ZERO    .L1     A8                ; |226| 
   [ B0]   MVKH    .S1     0xbff00000,A9
           ADD     .L2     8,B10,B10         ; |204| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |247| 
           FADDDP  .L1     A29:A28,A17:A16,A7:A6 ; |241| 
           NOP             1
   [ B1]   FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |251| 
           LDDW    .D2T1   *+SP(144),A5:A4
           NOP             2
           STDW    .D2T1   A7:A6,*B4         ; |208| 

           LDDW    .D1T1   *A10,A7:A6        ; |209| 
||         LDW     .D2T2   *+SP(12),B4

           NOP             4

           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |209| 
||         SUB     .L1X    B4,1,A0           ; |204| 
||         SUB     .L2     B4,1,B4           ; |204| 

   [ A0]   BNOP    .S1     $C$L10,1          ; |204| 
|| [!A0]   MVKL    .S2     output,B10

   [!A0]   MVKH    .S2     output,B10

   [ A0]   CALL    .S2     asinh             ; |205| 
||         STDW    .D1T1   A5:A4,*++A10      ; |209| 
||         STW     .D2T2   B4,*+SP(12)       ; |209| 
|| [!A0]   MVKL    .S1     a_ext,A4

   [!A0]   CALL    .S1     asinhdp_v         ; |211| 
|| [ A0]   LDDW    .D1T1   *A10,A5:A4        ; |205| 

   [!A0]   LDW     .D2T2   *+B10(16),B4      ; |211| 
           ; BRANCHCC OCCURS {$C$L10}        ; |204| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S1     a_ext,A4
           MVK     .S1     0x777,A6          ; |211| 
           ADDKPC  .S2     $C$RL26,B3,1      ; |211| 
$C$RL26:   ; CALL OCCURS {asinhdp_v} {0}     ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |66| 
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
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL28:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1X    B10,A3            ; |67| 
||         STW     .D2T1   A4,*+B11(8)       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL29:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2     B10,B4            ; |68| 
||         STW     .D2T1   A4,*+B11(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A15,B4           ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL30:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           LDW     .D1T1   *A14,A0           ; |72| 
||         LDW     .D2T2   *+SP(16),B4

           STW     .D2T1   A4,*+B11(16)      ; |69| 
           NOP             3

   [ A0]   ADD     .L2     4,B4,B4
|| [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |217| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
   [!A0]   MV      .L2X    A12,B4
   [!A0]   MV      .L2X    A3,B5
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   MV      .L2X    A12,B4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |217| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             1
           MV      .L2X    A3,B5
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x4,A4            ; |217| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL31,B3,0      ; |217| 

$C$RL31:   ; CALL OCCURS {print_test_results} {0}  ; |217| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         MV      .L2X    A12,B4            ; |114| 
||         MV      .L1     A12,A10           ; |114| 
||         MV      .D1     A12,A11           ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*A3       ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     t_start,A3

           MVKH    .S1     t_start,A3
||         MV      .L2     B4,B7             ; |116| 

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B7:B6,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 

           MVKL    .S1     t_offset,A3
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 

           CALL    .S1     gimme_random      ; |227| 
||         EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A3

           MVK     .S2     0x80,B4
||         STDW    .D1T2   B5:B4,*A3         ; |117| 

           MVKL    .S2     0xc0b38800,B5
||         MV      .L2X    A12,B12

           MV      .L2X    A11,B4            ; |227| 
||         MV      .L1X    B4,A12            ; |117| 
||         MVKH    .S2     0xc0b38800,B5
||         MV      .D1     A10,A4            ; |227| 
||         MVKL    .S1     0x412e8482,A5

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1

           ADDKPC  .S2     $C$RL32,B3,0      ; |227| 
||         MVKH    .S1     0x412e8482,A5

$C$RL32:   ; CALL OCCURS {gimme_random} {0}  ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 94
           MVKL    .S2     input,B4
           MVKH    .S2     input,B4
           LDW     .D2T2   *B4,B4            ; |227| 
           DADD    .L1     0,A5:A4,A29:A28   ; |227| 
           NOP             3
           ADD     .L2     B12,B4,B4         ; |227| 

           STDW    .D2T1   A29:A28,*B4       ; |227| 
||         MVC     .S2     TSCL,B18          ; |122| 

           MVC     .S2     TSCH,B19          ; |122| 
           FMPYDP  .M1     A29:A28,A29:A28,A31:A30 ; |230| 
           MV      .L1     A13,A5            ; |230| 
           MV      .L1     A10,A4            ; |230| 
           ZERO    .L2     B5
           FADDDP  .L1     A5:A4,A31:A30,A7:A6 ; |173| 
           SET     .S2     B5,0x15,0x1d,B5
           MV      .L2X    A11,B4            ; |173| 
           RSQRDP  .S1     A7:A6,A5:A4       ; |173| 
           ZERO    .L2     B7
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |173| 
           SET     .S2     B7,0x13,0x1d,B7
           MV      .L2X    A11,B6            ; |173| 
           ZERO    .L1     A27
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |173| 
           ZERO    .L2     B9
           SET     .S2     B9,0x13,0x1d,B9
           MV      .L2X    A11,B8            ; |173| 
           ZERO    .L1     A17
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |173| 
           SET     .S1     A17,0x15,0x1d,A17
           MV      .L1     A10,A16           ; |174| 
           ZERO    .L2     B31
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |173| 
           MV      .L2X    A11,B10           ; |173| 
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |173| 
           MV      .L1     A10,A4            ; |173| 
           SET     .S1     A27,0x15,0x1d,A5
           ABSDP   .S1     A29:A28,A27:A26   ; |223| 
           FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |173| 
           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |173| 
           NOP             3
           FMPYDP  .M2X    A5:A4,B7:B6,B7:B6 ; |173| 
           NOP             3
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |173| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |173| 
           NOP             4
           FMPYDP  .M1X    B5:B4,A7:A6,A5:A4 ; |174| 
           NOP             3
           FMPYDP  .M1X    B5:B4,A5:A4,A9:A8 ; |174| 
           SET     .S2     B31,0x15,0x1d,B5
           MV      .L2     B8,B4             ; |177| 
           MV      .L2     B5,B11            ; |176| 
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |174| 
           MV      .L1X    B9,A17            ; |174| 
           FMPYDP  .M2X    B5:B4,A27:A26,B5:B4 ; |247| 
           NOP             1
           FSUBDP  .L1     A17:A16,A9:A8,A17:A16 ; |174| 
           FMPYDP  .M1     A27:A26,A27:A26,A9:A8 ; |176| 
           NOP             1
           FMPYDP  .M1     A5:A4,A17:A16,A5:A4 ; |174| 
           NOP             1
           CMPEQDP .S1     A7:A6,A9:A8,A0    ; |176| 
           NOP             1
   [ A0]   DADD    .L1     0,A27:A26,A5:A4   ; |177| 
           NOP             1
           FMPYDP  .M2X    B11:B10,A5:A4,B7:B6 ; |247| 
           NOP             3
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |247| 
           NOP             3

           CALLP   .S2     logdp_asinhdp_i,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |247| 

$C$RL33:   ; CALL OCCURS {logdp_asinhdp_i} {0}  ; |247| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 51

           FMPYDP  .M1     A31:A30,A31:A30,A9:A8 ; |231| 
||         MVKL    .S1     0x2884c094,A18
||         MVKL    .S2     0xbfa6e4ec,B9
||         ZERO    .L2     B17:B16           ; |226| 

           MVKL    .S1     0x3f9fd78f,A19
||         MVKL    .S2     0x93a79b50,B8

           MVKH    .S1     0x2884c094,A18
||         MVKL    .S2     0x9b04cad8,B6

           MVKH    .S1     0x3f9fd78f,A19
||         MVKL    .S2     0x3fb3335d,B7

           FMPYDP  .M1     A31:A30,A9:A8,A17:A16 ; |232| 
||         MVKL    .S2     0x8d02093f,B4
||         CMPLTDP .S1X    A29:A28,B17:B16,A0 ; |226| 

           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |233| 
||         MVKL    .S2     0xbfc55555,B5

           MVKH    .S2     0xbfa6e4ec,B9
||         MVKL    .S1     t_start,A3

           MVKH    .S2     0x93a79b50,B8
||         MVKH    .S1     t_start,A3

           MVKH    .S2     0x9b04cad8,B6
||         STDW    .D1T2   B19:B18,*A3

           FMPYDP  .M1     A19:A18,A7:A6,A19:A18 ; |241| 
||         MVKH    .S2     0x3fb3335d,B7
||         FMPYDP  .M2X    B9:B8,A17:A16,B9:B8 ; |241| 
||         MVKL    .S1     0xbf978498,A7

           MVKH    .S2     0x8d02093f,B4
||         FMPYDP  .M2X    B7:B6,A9:A8,B7:B6 ; |241| 
||         FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |234| 
||         MVKL    .S1     0x92c0541a,A6

           MVKH    .S2     0xbfc55555,B5
||         MVKH    .S1     0xbf978498,A7

           FMPYDP  .M2X    B5:B4,A31:A30,B5:B4 ; |241| 
||         MVKH    .S1     0x92c0541a,A6
||         MVKL    .S2     output+12,B29

           MVKH    .S2     output+12,B29

           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |241| 
||         MVKL    .S1     0x3fd33333,A7

           MVKL    .S1     0x33333333,A6

           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |241| 
||         FADDDP  .S2X    A19:A18,B9:B8,B7:B6 ; |241| 
||         MVKH    .S1     0x3fd33333,A7

           MVKH    .S1     0x33333333,A6
           CMPGTDP .S1     A27:A26,A7:A6,A1  ; |250| 

           MVKL    .S2     0x3fe62e42,B5
||         FADDDP  .L2     B7:B6,B5:B4,B7:B6 ; |241| 

           MVKL    .S2     0xfefa39ec,B4
           MVKH    .S2     0x3fe62e42,B5
           MVKH    .S2     0xfefa39ec,B4

           FADDDP  .L1X    A9:A8,B7:B6,A17:A16 ; |241| 
|| [ A0]   ZERO    .S1     A9
|| [!A0]   ZERO    .D1     A8                ; |226| 

           FADDDP  .L1X    B5:B4,A5:A4,A7:A6 ; |247| 
||         LDW     .D2T2   *B29,B4           ; |231| 
|| [ A0]   MVKH    .S1     0xbff00000,A9
|| [ A0]   ZERO    .D1     A8                ; |226| 

   [!A0]   MV      .S1     A13,A9            ; |247| 
           FMPYDP  .M1     A29:A28,A17:A16,A17:A16 ; |241| 
           NOP             2
           ADD     .L2     B12,B4,B4         ; |231| 

           FADDDP  .L1     A29:A28,A17:A16,A5:A4 ; |241| 
|| [ A1]   FMPYDP  .M1     A9:A8,A7:A6,A5:A4 ; |251| 

           NOP             3

           STDW    .D2T1   A5:A4,*B4         ; |231| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S2     t_offset,B10
||         MV      .L2     B6,B17            ; |128| 
||         SUB     .L1     A12,1,A0          ; |225| 
||         MVKL    .S1     t_stop,A3

           MVKH    .S2     t_offset,B10
||         MVKH    .S1     t_stop,A3

           LDDW    .D2T2   *B10,B5:B4        ; |130| 
||         MVKL    .S2     cycle_counts+24,B7

           MVKH    .S2     cycle_counts+24,B7
||         STDW    .D1T2   B17:B16,*A3       ; |128| 

           LDDW    .D2T1   *B7,A7:A6         ; |130| 
           MV      .L1X    B7,A14            ; |130| 
           NOP             1
           ADDU    .L2     B4,B18,B9:B8      ; |130| 

           ADD     .S2     B9,B5,B6          ; |130| 
||         SUBU    .L2     B16,B8,B5:B4      ; |130| 

           ADD     .L2     B6,B19,B6         ; |130| 
|| [ A0]   B       .S1     $C$L12            ; |225| 

           SUB     .L2     B17,B6,B5         ; |130| 
||         EXT     .S2     B5,24,24,B6       ; |130| 
|| [ A0]   CALL    .S1     gimme_random      ; |227| 
||         ADDU    .L1X    A6,B4,A5:A4       ; |130| 

           ADD     .L2     B5,B6,B4          ; |130| 
||         ADD     .L1     A5,A7,A5          ; |130| 
|| [ A0]   MVKL    .S2     0xc0b38800,B5

   [ A0]   MVKH    .S2     0xc0b38800,B5

           ADD     .L1X    A5,B4,A5          ; |130| 
||         SUB     .S1     A12,1,A12         ; |225| 
|| [ A0]   MV      .L2X    A11,B4            ; |227| 

           STDW    .D1T1   A5:A4,*A14        ; |130| 
|| [ A0]   MVKL    .S1     0x412e8482,A5
||         ADD     .L2     8,B12,B12         ; |225| 
|| [ A0]   MV      .L1     A10,A4            ; |227| 

           ; BRANCHCC OCCURS {$C$L12}        ; |225| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALLP   .S2     __c6xabi_fltllif,B3
||         LDDW    .D1T1   *A14,A5:A4        ; |135| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A15
           SET     .S1     A15,0x1a,0x1d,A15
           MPYSP   .M1     A15,A4,A3         ; |135| 
           MV      .L1     A10,A12           ; |135| 
           MV      .L1X    B11,A13           ; |135| 
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL35:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           MV      .L2X    A14,B4
||         SUBAW   .D1     A14,6,A3

           STDW    .D1T1   A11:A10,*A3       ; |114| 
||         MV      .L2X    A11,B5            ; |114| 

           MVC     .S2     B5,TSCL           ; |115| 
||         STDW    .D2T1   A5:A4,*B4         ; |135| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B4,B4          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B4,B5,B7          ; |117| 

           STDW    .D2T2   B7:B6,*B10        ; |117| 
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
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |240| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |240| 
||         CALL    .S1     asinh             ; |240| 

           LDDW    .D1T1   *A3,A5:A4         ; |240| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |240| 
$C$RL36:   ; CALL OCCURS {asinh} {0}         ; |240| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 25
           MVKL    .S2     output,B10
           MVKH    .S2     output,B10
           LDW     .D2T2   *B10,B4           ; |240| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |240| 

           STDW    .D1T1   A5:A4,*A3         ; |240| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A14
||         MVKL    .S2     t_start,B5
||         SUB     .L1X    B11,1,A0          ; |238| 
||         MV      .L2     B4,B9             ; |128| 
||         ADD     .D1     8,A12,A12         ; |238| 
||         SUB     .D2     B11,1,B11         ; |238| 

           MVKH    .S1     t_offset,A14
||         MVKH    .S2     t_start,B5

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B5,B7:B6         ; |130| 
||         MVKL    .S1     cycle_counts,A3
||         MVKL    .S2     cycle_counts,B4

           MVKH    .S1     cycle_counts,A3
||         MVKH    .S2     cycle_counts,B4

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     t_stop,A31

           MVKH    .S1     t_stop,A31
           STDW    .D1T2   B9:B8,*A31        ; |128| 
           ADDU    .L2X    A4,B6,B17:B16     ; |130| 
           MV      .L2     B16,B5            ; |130| 

           ADD     .S2X    B17,A5,B5         ; |130| 
||         SUBU    .L2     B8,B5,B17:B16     ; |130| 
|| [ A0]   B       .S1     $C$L13            ; |238| 

           ADD     .D2     B5,B7,B5          ; |130| 
||         ADDU    .L2X    A6,B16,B7:B6      ; |130| 
||         EXT     .S2     B17,24,24,B16     ; |130| 

           SUB     .L2     B9,B5,B5          ; |130| 

           ADD     .L2X    B7,A7,B5          ; |130| 
||         ADD     .S2     B5,B16,B7         ; |130| 

           ADD     .L2     B5,B7,B7          ; |130| 
           STDW    .D2T2   B7:B6,*B4         ; |130| 
           ; BRANCHCC OCCURS {$C$L13}        ; |238| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           MV      .L1X    B4,A3

           CALLP   .S2     __c6xabi_fltllif,B3
||         LDDW    .D1T1   *A3,A5:A4         ; |135| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A15,A4,A3         ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MVKL    .S1     cycle_counts,A3
           MVKH    .S1     cycle_counts,A3

           STDW    .D1T1   A11:A10,*+A3(8)   ; |114| 
||         MV      .L2X    A11,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A3         ; |135| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B9           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B9,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MV      .S2X    A14,B8            ; |117| 

           STDW    .D2T2   B7:B6,*B8         ; |117| 
||         MVK     .S1     0x80,A15

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |249| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |249| 
||         CALL    .S1     asinhdp           ; |249| 

           LDDW    .D1T1   *A3,A5:A4         ; |249| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |249| 
$C$RL39:   ; CALL OCCURS {asinhdp} {0}       ; |249| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ADD     .L2     4,B10,B4
           LDW     .D2T2   *B4,B4            ; |249| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |249| 

           STDW    .D1T1   A5:A4,*A3         ; |249| 
||         MVC     .S2     TSCL,B6           ; |128| 

           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S2     t_start,B11
||         MVKL    .S1     t_offset,A3
||         SUB     .L1     A15,1,A0          ; |247| 
||         SUB     .D1     A15,1,A15         ; |247| 

           MVKH    .S2     t_start,B11
||         MVKH    .S1     t_offset,A3
||         ADD     .L1     8,A12,A12         ; |247| 

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         LDDW    .D2T2   *B11,B9:B8        ; |130| 
||         MVKL    .S1     cycle_counts+8,A3

           MVKH    .S1     cycle_counts+8,A3

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     t_stop,A14

           MV      .L2X    A3,B12            ; |128| 
||         MVKH    .S1     t_stop,A14

   [!A0]   MVKL    .S1     cycle_counts,A3
||         STDW    .D1T2   B7:B6,*A14        ; |128| 

           ADDU    .L2X    A4,B8,B5:B4       ; |130| 
|| [!A0]   MVKH    .S1     cycle_counts,A3

           ADD     .S2X    B5,A5,B8          ; |130| 
|| [ A0]   B       .S1     $C$L14            ; |247| 
||         SUBU    .L2     B6,B4,B5:B4       ; |130| 

           ADD     .D2     B8,B9,B8          ; |130| 
||         EXT     .S2     B5,24,24,B31      ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B7,B8,B9          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B9,B31,B8         ; |130| 
           ADD     .L2     B5,B8,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B12        ; |130| 

           ; BRANCHCC OCCURS {$C$L14}        ; |247| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(8),A5:A4     ; |135| 
           ADDKPC  .S2     $C$RL40,B3,3      ; |135| 
$C$RL40:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 72
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL41:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
           MV      .L1X    B12,A15           ; |135| 
           SUBAW   .D1     A15,2,A3

           MV      .L2X    A11,B4            ; |114| 
||         STDW    .D1T1   A5:A4,*A15        ; |135| 

           STDW    .D1T1   A11:A10,*+A3(32)  ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D2T2   B5:B4,*B11        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           LDW     .D2T1   *+SP(20),A4       ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 
           MVKL    .S1     input,A3
           SUB     .L2     B8,B5,B4          ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         MVKL    .S1     t_offset,A12

           ADD     .L2     B4,B5,B7          ; |117| 
||         LDW     .D1T2   *A4,B4            ; |256| 
||         MVKH    .S1     t_offset,A12

           MVKH    .S1     input,A3
||         STDW    .D1T2   B7:B6,*A12        ; |117| 

           CALLP   .S2     asinhdp_v,B3
||         LDW     .D1T1   *A3,A4            ; |256| 
||         MVK     .S1     0x80,A6           ; |256| 

$C$RL42:   ; CALL OCCURS {asinhdp_v} {0}     ; |256| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 
           MV      .L1     A12,A3            ; |128| 

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S2     24,B11
           ADD     .L2X    A15,B11,B11

           MV      .L2     B4,B9             ; |128| 
||         LDDW    .D2T2   *B11,B5:B4        ; |130| 

           NOP             1
           ADDU    .L1X    A4,B6,A7:A6       ; |130| 

           ADD     .S1     A7,A5,A4          ; |130| 
||         SUBU    .L1X    B8,A6,A7:A6       ; |130| 

           MV      .L1     A6,A3             ; |130| 

           ADDU    .L1X    B4,A3,A5:A4       ; |130| 
||         ADD     .L2X    A4,B7,B4          ; |130| 

           EXT     .S1     A7,24,24,A3       ; |130| 

           SUB     .L2     B9,B4,B7          ; |130| 
||         ADD     .S2X    A5,B5,B5          ; |130| 

           ADD     .L2X    B7,A3,B7          ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 
||         MV      .S2X    A4,B4             ; |130| 

           MV      .L2X    A14,B6            ; |128| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         STDW    .D2T2   B9:B8,*B6         ; |128| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1     A10,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL44:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           SUBAW   .D1     A15,2,A3
||         MV      .L2X    A11,B4            ; |114| 
||         STDW    .D2T1   A5:A4,*B11        ; |130| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*+A3(16)  ; |114| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B6,B5,B7:B6       ; |117| 
||         MVK     .S1     0x80,A31

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B4,B4          ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B7:B6,*A3         ; |117| 
||         MV      .L1     A31,A11           ; |117| 

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
           LDW     .D1T1   *A3,A3            ; |264| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A10,A3,A3         ; |264| 
||         CALL    .S1     asinhdp_c         ; |264| 

           LDDW    .D1T1   *A3,A5:A4         ; |264| 
           ADDKPC  .S2     $C$RL45,B3,3      ; |264| 
$C$RL45:   ; CALL OCCURS {asinhdp_c} {0}     ; |264| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ADDAD   .D2     B10,1,B4
           LDW     .D2T2   *B4,B4            ; |264| 
           NOP             4
           ADD     .L1X    A10,B4,A3         ; |264| 

           STDW    .D1T1   A5:A4,*A3         ; |264| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     t_start,B5
||         MVKL    .S1     t_offset,A3
||         ADDAD   .D1     A15,1,A31
||         SUB     .L1     A11,1,A0          ; |262| 
||         MV      .L2     B4,B17            ; |128| 
||         ADDAD   .D2     B12,1,B11

           MV      .L1     A14,A30           ; |128| 
||         MVKH    .S1     t_offset,A3
||         MVKH    .S2     t_start,B5

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B5,B9:B8         ; |130| 

           LDDW    .D1T1   *A31,A5:A4        ; |130| 
           SUB     .L1     A11,1,A11         ; |262| 
           ADD     .L1     8,A10,A10         ; |262| 
           STDW    .D1T2   B17:B16,*A30      ; |128| 
           ADDU    .L2X    A6,B8,B7:B6       ; |130| 

   [ A0]   B       .S1     $C$L15            ; |262| 
||         SUBU    .L2     B16,B6,B5:B4      ; |130| 
||         ADD     .S2X    B7,A7,B6          ; |130| 

           ADD     .D2     B6,B9,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A4,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B6         ; |130| 
||         ADD     .S2X    B5,A5,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B11        ; |130| 

           ; BRANCHCC OCCURS {$C$L15}        ; |262| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D2T1   *B11,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL46,B3,3      ; |135| 
$C$RL46:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 56
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL47:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           MV      .L1X    B10,A10           ; |135| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A10(4),B4       ; |66| 
||         STDW    .D2T1   A5:A4,*B11        ; |135| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL48:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B11
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     fcn_pass,B11

           MV      .L1     A4,A3             ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A10(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B11(4)       ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL49:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           MV      .L1     A4,A3             ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A10(12),B4      ; |68| 
||         STW     .D2T1   A3,*+B11(8)       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL50:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B11(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A10(16),B4      ; |69| 
||         LDW     .D2T1   *B10,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL51:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(24),B4       ; |69| 
           STW     .D2T1   A4,*+B11(16)      ; |69| 
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
   [!B0]   MV      .L1     A12,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L17            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |271| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |271| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |271| 
||         ADDKPC  .S2     $C$RL52,B3,0      ; |271| 

$C$RL52:   ; CALL OCCURS {print_test_results} {0}  ; |271| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |272| 

$C$RL53:   ; CALL OCCURS {printf} {0}        ; |272| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |272| 

$C$RL54:   ; CALL OCCURS {printf} {0}        ; |272| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |279| 

$C$RL55:   ; CALL OCCURS {print_profile_results} {0}  ; |279| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |282| 

$C$RL56:   ; CALL OCCURS {print_memory_results} {0}  ; |282| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADDK    .S2     152,SP            ; |283| 
           LDW     .D2T2   *++SP(8),B3       ; |283| 
           LDDW    .D2T1   *++SP,A13:A12     ; |283| 
           LDDW    .D2T1   *++SP,A15:A14     ; |283| 
           LDDW    .D2T2   *++SP,B11:B10     ; |283| 
           LDDW    .D2T2   *++SP,B13:B12     ; |283| 

           LDW     .D2T1   *++SP(8),A10      ; |283| 
||         RET     .S2     B3                ; |283| 

           LDW     .D2T1   *++SP(8),A11      ; |283| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |283| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"asinhDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	asinh
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	asinhdp_c
	.global	asinhdp
	.global	asinhdp_v
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
