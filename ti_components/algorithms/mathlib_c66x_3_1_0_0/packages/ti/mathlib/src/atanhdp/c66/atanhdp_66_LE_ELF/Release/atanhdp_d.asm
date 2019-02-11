;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:22:14 2013                                *
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
	.word	099301ad8h,03f6ab441h		; a[0] @ 0
	.word	0adfa0a03h,03f7460cbh		; a[1] @ 64
	.word	0d05621d3h,0bf8460cbh		; a[2] @ 128
	.word	0403edf64h,03f8e9131h		; a[3] @ 192
	.word	0f2b239a4h,0bf9460cbh		; a[4] @ 256
	.word	099788c84h,03f9978feh		; a[5] @ 320
	.word	0ec0b5675h,0bf9e9131h		; a[6] @ 384
	.word	04968d4abh,03fa1d4b2h		; a[7] @ 448
	.word	09ccbfe1bh,0bfa460cbh		; a[8] @ 512
	.word	046156314h,03fa6ece5h		; a[9] @ 576
	.word	099788c84h,0bfa978feh		; a[10] @ 640
	.word	042c1f17dh,03fac0518h		; a[11] @ 704
	.word	096251aedh,0bfae9131h		; a[12] @ 768
	.word	09fb73ff3h,03fb08ea5h		; a[13] @ 832
	.word	04968d4abh,0bfb1d4b2h		; a[14] @ 896
	.word	0f31a6963h,03fb31abeh		; a[15] @ 960
	.word	0c7bf1bdfh,0bfb460cbh		; a[16] @ 1024
	.word	07170b097h,03fb5a6d8h		; a[17] @ 1088
	.word	046156314h,0bfb6ece5h		; a[18] @ 1152
	.word	0efc6f7cch,03fb832f1h		; a[19] @ 1216
	.word	0c46baa48h,0bfb978feh		; a[20] @ 1280
	.word	0432a213ch,03fbabf0bh		; a[21] @ 1344
	.word	096f57a6bh,0bfbc0517h		; a[22] @ 1408
	.word	0983ffd46h,03fbd4b25h		; a[23] @ 1472
	.word	0ec0b5675h,0bfbe9131h		; a[24] @ 1536
	.word	03fd6afa5h,03fbfd73eh		; a[25] @ 1600
	.word	049d1046ah,0bfc08ea5h		; a[26] @ 1664
	.word	04a7645d7h,03fc131ach		; a[27] @ 1728
	.word	0745bf26fh,0bfc1d4b2h		; a[28] @ 1792
	.word	09e419f07h,03fc277b8h		; a[29] @ 1856
	.word	0c8274b9eh,0bfc31abeh		; a[30] @ 1920
	.word	0c8cc8d0ch,03fc3bdc5h		; a[31] @ 1984
	.word	0f2b239a4h,0bfc460cbh		; a[32] @ 2048
	.word	01c97e63bh,03fc503d2h		; a[33] @ 2112
	.word	0467d92d3h,0bfc5a6d8h		; a[34] @ 2176
	.word	04722d440h,03fc649dfh		; a[35] @ 2240
	.word	0710880d8h,0bfc6ece5h		; a[36] @ 2304
	.word	09aee2d70h,03fc78febh		; a[37] @ 2368
	.word	0c4d3da07h,0bfc832f1h		; a[38] @ 2432
	.word	0c5791b75h,03fc8d5f8h		; a[39] @ 2496
	.word	0ef5ec80ch,0bfc978feh		; a[40] @ 2560
	.word	0194474a4h,03fca1c05h		; a[41] @ 2624
	.word	0432a213ch,0bfcabf0bh		; a[42] @ 2688
	.word	043cf62a9h,03fcb6212h		; a[43] @ 2752
	.word	06db50f41h,0bfcc0518h		; a[44] @ 2816
	.word	0979abbd9h,03fcca81eh		; a[45] @ 2880
	.word	0c1806870h,0bfcd4b24h		; a[46] @ 2944
	.word	0eb661508h,03fcdee2ah		; a[47] @ 3008
	.word	0ec0b5675h,0bfce9131h		; a[48] @ 3072
	.word	015f1030dh,03fcf3438h		; a[49] @ 3136
	.word	03fd6afa5h,0bfcfd73eh		; a[50] @ 3200
	.word	034de2e1eh,03fd03d22h		; a[51] @ 3264
	.word	0b530ced5h,0bfd08ea5h		; a[52] @ 3328
	.word	0ca23a521h,03fd0e028h		; a[53] @ 3392
	.word	0df167b6dh,0bfd131abh		; a[54] @ 3456
	.word	0f40951b8h,03fd1832eh		; a[55] @ 3520
	.word	0745bf26fh,0bfd1d4b2h		; a[56] @ 3584
	.word	0894ec8bbh,03fd22635h		; a[57] @ 3648
	.word	09e419f07h,0bfd277b8h		; a[58] @ 3712
	.word	0b3347553h,03fd2c93bh		; a[59] @ 3776
	.word	033871609h,0bfd31abfh		; a[60] @ 3840
	.word	04879ec55h,03fd36c42h		; a[61] @ 3904
	.word	05d6cc2a1h,0bfd3bdc5h		; a[62] @ 3968
	.word	0725f98edh,03fd40f48h		; a[63] @ 4032
	.word	0f2b239a4h,0bfd460cbh		; a[64] @ 4096
	.word	007a50fefh,03fd4b24fh		; a[65] @ 4160
	.word	01c97e63bh,0bfd503d2h		; a[66] @ 4224
	.word	0318abc87h,03fd55555h		; a[67] @ 4288
	.word	0b1dd5d3eh,0bfd5a6d8h		; a[68] @ 4352
	.word	0c6d0338ah,03fd5f85bh		; a[69] @ 4416
	.word	0dbc309d5h,0bfd649deh		; a[70] @ 4480
	.word	0f0b5e021h,03fd69b61h		; a[71] @ 4544
	.word	0710880d8h,0bfd6ece5h		; a[72] @ 4608
	.word	085fb5724h,03fd73e68h		; a[73] @ 4672
	.word	09aee2d70h,0bfd78febh		; a[74] @ 4736
	.word	0afe103bbh,03fd7e16eh		; a[75] @ 4800
	.word	03033a472h,0bfd832f2h		; a[76] @ 4864
	.word	045267abeh,03fd88475h		; a[77] @ 4928
	.word	05a19510ah,0bfd8d5f8h		; a[78] @ 4992
	.word	06f0c2756h,03fd9277bh		; a[79] @ 5056
	.word	0ef5ec80ch,0bfd978feh		; a[80] @ 5120
	.word	004519e58h,03fd9ca82h		; a[81] @ 5184
	.word	0194474a4h,0bfda1c05h		; a[82] @ 5248
	.word	02e374af0h,03fda6d88h		; a[83] @ 5312
	.word	0ae89eba7h,0bfdabf0bh		; a[84] @ 5376
	.word	0c37cc1f2h,03fdb108eh		; a[85] @ 5440
	.word	0d86f983eh,0bfdb6211h		; a[86] @ 5504
	.word	0ed626e8ah,03fdbb394h		; a[87] @ 5568
	.word	06db50f41h,0bfdc0518h		; a[88] @ 5632
	.word	082a7e58dh,03fdc569bh		; a[89] @ 5696
	.word	0979abbd9h,0bfdca81eh		; a[90] @ 5760
	.word	0ac8d9224h,03fdcf9a1h		; a[91] @ 5824
	.word	0c1806870h,0bfdd4b24h		; a[92] @ 5888
	.word	041d30927h,03fdd9ca8h		; a[93] @ 5952
	.word	056c5df73h,0bfddee2bh		; a[94] @ 6016
	.word	06bb8b5bfh,03fde3faeh		; a[95] @ 6080
	.word	080ab8c0ah,0bfde9131h		; a[96] @ 6144
	.word	000fe2cc1h,03fdee2b5h		; a[97] @ 6208
	.word	015f1030dh,0bfdf3438h		; a[98] @ 6272
	.word	02ae3d959h,03fdf85bbh		; a[99] @ 6336
	.word	03fd6afa5h,0bfdfd73eh		; a[100] @ 6400
	.word	0aa64c2f8h,03fe01460h		; a[101] @ 6464
	.word	06a8e1354h,0bfe03d22h		; a[102] @ 6528
	.word	0f5077e7ah,03fe065e3h		; a[103] @ 6592
	.word	0b530ced5h,0bfe08ea5h		; a[104] @ 6656
	.word	009fa54c5h,03fe0b767h		; a[105] @ 6720
	.word	0ca23a521h,0bfe0e028h		; a[106] @ 6784
	.word	0549d1047h,03fe108eah		; a[107] @ 6848
	.word	014c660a2h,0bfe131ach		; a[108] @ 6912
	.word	0698fe692h,03fe15a6dh		; a[109] @ 6976
	.word	029b936eeh,0bfe1832fh		; a[110] @ 7040
	.word	0b432a214h,03fe1abf0h		; a[111] @ 7104
	.word	03eac0d3ah,0bfe1d4b2h		; a[112] @ 7168
	.word	0c9257860h,03fe1fd73h		; a[113] @ 7232
	.word	0894ec8bbh,0bfe22635h		; a[114] @ 7296
	.word	013c833e1h,03fe24ef7h		; a[115] @ 7360
	.word	09e419f07h,0bfe277b8h		; a[116] @ 7424
	.word	028bb0a2dh,03fe2a07ah		; a[117] @ 7488
	.word	0e8e45a88h,0bfe2c93bh		; a[118] @ 7552
	.word	0735dc5aeh,03fe2f1fdh		; a[119] @ 7616
	.word	0fdd730d4h,0bfe31abeh		; a[120] @ 7680
	.word	088509bfah,03fe34380h		; a[121] @ 7744
	.word	04879ec55h,0bfe36c42h		; a[122] @ 7808
	.word	0d2f3577bh,03fe39503h		; a[123] @ 7872
	.word	05d6cc2a1h,0bfe3bdc5h		; a[124] @ 7936
	.word	0e7e62dc7h,03fe3e686h		; a[125] @ 8000
	.word	0a80f7e22h,0bfe40f48h		; a[126] @ 8064
	.word	03288e948h,03fe4380ah		; a[127] @ 8128
	.word	0bd02546eh,0bfe460cbh		; a[128] @ 8192
	.word	0477bbf94h,03fe4898dh		; a[129] @ 8256
	.word	007a50fefh,0bfe4b24fh		; a[130] @ 8320
	.word	0921e7b15h,03fe4db10h		; a[131] @ 8384
	.word	01c97e63bh,0bfe503d2h		; a[132] @ 8448
	.word	0a7115161h,03fe52c93h		; a[133] @ 8512
	.word	0673aa1bch,0bfe55555h		; a[134] @ 8576
	.word	0f1b40ce2h,03fe57e16h		; a[135] @ 8640
	.word	07c2d7808h,0bfe5a6d8h		; a[136] @ 8704
	.word	006a6e32eh,03fe5cf9ah		; a[137] @ 8768
	.word	0c6d0338ah,0bfe5f85bh		; a[138] @ 8832
	.word	051499eb0h,03fe6211dh		; a[139] @ 8896
	.word	0dbc309d5h,0bfe649deh		; a[140] @ 8960
	.word	0663c74fbh,03fe672a0h		; a[141] @ 9024
	.word	02665c557h,0bfe69b62h		; a[142] @ 9088
	.word	0b0df307dh,03fe6c423h		; a[143] @ 9152
	.word	03b589ba3h,0bfe6ece5h		; a[144] @ 9216
	.word	0c5d206c8h,03fe715a6h		; a[145] @ 9280
	.word	085fb5724h,0bfe73e68h		; a[146] @ 9344
	.word	01074c24ah,03fe7672ah		; a[147] @ 9408
	.word	09aee2d70h,0bfe78febh		; a[148] @ 9472
	.word	025679896h,03fe7b8adh		; a[149] @ 9536
	.word	0afe103bbh,0bfe7e16eh		; a[150] @ 9600
	.word	0700a5417h,03fe80a30h		; a[151] @ 9664
	.word	0fa83bf3dh,0bfe832f1h		; a[152] @ 9728
	.word	0baad0f98h,03fe85bb3h		; a[153] @ 9792
	.word	00f769589h,0bfe88475h		; a[154] @ 9856
	.word	0cf9fe5e4h,03fe8ad36h		; a[155] @ 9920
	.word	05a19510ah,0bfe8d5f8h		; a[156] @ 9984
	.word	01a42a165h,03fe8febah		; a[157] @ 10048
	.word	06f0c2756h,0bfe9277bh		; a[158] @ 10112
	.word	02f3577b1h,03fe9503dh		; a[159] @ 10176
	.word	0b9aee2d7h,0bfe978feh		; a[160] @ 10240
	.word	079d83332h,03fe9a1c0h		; a[161] @ 10304
	.word	0cea1b923h,0bfe9ca81h		; a[162] @ 10368
	.word	08ecb097eh,03fe9f343h		; a[163] @ 10432
	.word	0194474a4h,0bfea1c05h		; a[164] @ 10496
	.word	0a3bddfcah,03fea44c6h		; a[165] @ 10560
	.word	02e374af0h,0bfea6d88h		; a[166] @ 10624
	.word	0ee609b4bh,03fea9649h		; a[167] @ 10688
	.word	078da0671h,0bfeabf0bh		; a[168] @ 10752
	.word	003537197h,03feae7cdh		; a[169] @ 10816
	.word	08dccdcbdh,0bfeb108eh		; a[170] @ 10880
	.word	04df62d18h,03feb3950h		; a[171] @ 10944
	.word	0d86f983eh,0bfeb6211h		; a[172] @ 11008
	.word	062e90364h,03feb8ad3h		; a[173] @ 11072
	.word	0ed626e8ah,0bfebb394h		; a[174] @ 11136
	.word	0ad8bbee6h,03febdc56h		; a[175] @ 11200
	.word	038052a0bh,0bfec0518h		; a[176] @ 11264
	.word	0c27e9531h,03fec2dd9h		; a[177] @ 11328
	.word	04cf80057h,0bfec569bh		; a[178] @ 11392
	.word	00d2150b3h,03fec7f5dh		; a[179] @ 11456
	.word	0979abbd9h,0bfeca81eh		; a[180] @ 11520
	.word	0221426feh,03fecd0e0h		; a[181] @ 11584
	.word	0ac8d9224h,0bfecf9a1h		; a[182] @ 11648
	.word	06cb6e280h,03fed2263h		; a[183] @ 11712
	.word	0f7304da6h,0bfed4b24h		; a[184] @ 11776
	.word	081a9b8cch,03fed73e6h		; a[185] @ 11840
	.word	00c2323f1h,0bfed9ca8h		; a[186] @ 11904
	.word	0cc4c744dh,03fedc569h		; a[187] @ 11968
	.word	056c5df73h,0bfedee2bh		; a[188] @ 12032
	.word	0e13f4a99h,03fee16ech		; a[189] @ 12096
	.word	06bb8b5bfh,0bfee3faeh		; a[190] @ 12160
	.word	02be2061ah,03fee6870h		; a[191] @ 12224
	.word	0b65b7140h,0bfee9131h		; a[192] @ 12288
	.word	040d4dc66h,03feeb9f3h		; a[193] @ 12352
	.word	0cb4e478ch,0bfeee2b4h		; a[194] @ 12416
	.word	08b7797e7h,03fef0b76h		; a[195] @ 12480
	.word	015f1030dh,0bfef3438h		; a[196] @ 12544
	.word	0a06a6e33h,03fef5cf9h		; a[197] @ 12608
	.word	02ae3d959h,0bfef85bbh		; a[198] @ 12672
	.word	0eb0d29b4h,03fefae7ch		; a[199] @ 12736
	.word	0758694dah,0bfefd73eh		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\134682 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\134684 
	.sect	".text:optci"
	.clink

;******************************************************************************
;* FUNCTION NAME: logdp_atanhdp_i                                             *
;*                                                                            *
;*   Regs Modified     : A0,A1,A3,A4,A5,A6,A7,A8,A9,B0,B4,B5,B6,B7,B8,B9,A16, *
;*                           A17,A18,A19,A20,A21,A22,A23,A24,A25,B16,B17,B18, *
;*                           B19                                              *
;*   Regs Used         : A0,A1,A3,A4,A5,A6,A7,A8,A9,B0,B3,B4,B5,B6,B7,B8,B9,  *
;*                           A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,B16,B17, *
;*                           B18,B19                                          *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
logdp_atanhdp_i:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 138
           EXTU    .S1     A5,1,21,A1        ; |108| 

           CLR     .S1     A5,20,31,A3       ; |113| 
||         ZERO    .L2     B7

           SET     .S2     B7,0x15,0x1d,B7
||         ZERO    .L2     B6                ; |124| 
||         SET     .S1     A3,21,29,A5       ; |113| 

   [!A1]   ZERO    .L1     A5:A4             ; |116| 
           FSUBDP  .L1X    A5:A4,B7:B6,A7:A6 ; |124| 
           MV      .L2     B7,B5             ; |125| 
           ZERO    .L2     B4                ; |124| 
           MVKL    .S1     0x667f3bcd,A8

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |125| 
||         MV      .L2     B7,B9             ; |125| 
||         ZERO    .S2     B8                ; |124| 
||         MVKL    .S1     0x3fe6a09e,A9

           FMPYDP  .M2X    B9:B8,A5:A4,B9:B8 ; |121| 
||         MVKH    .S1     0x667f3bcd,A8

           MVKH    .S1     0x3fe6a09e,A9

           MV      .L1X    B7,A17            ; |125| 
||         CMPGTDP .S1     A5:A4,A9:A8,A0    ; |119| 
||         ZERO    .D1     A16               ; |124| 

           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |125| 
   [ A0]   FADDDP  .L2X    A17:A16,B9:B8,B5:B4 ; |121| 
           ZERO    .S2     B9
           SET     .S2     B9,0x1e,0x1e,B9
           RCPDP   .S2     B5:B4,B17:B16     ; |68| 
           MV      .L2     B6,B8             ; |68| 
           FMPYDP  .M2     B5:B4,B17:B16,B19:B18 ; |68| 
           MV      .L1X    B7,A9             ; |125| 
           ZERO    .L1     A8                ; |124| 
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |120| 
           FSUBDP  .L2     B9:B8,B19:B18,B19:B18 ; |68| 
           MVKL    .S1     0xc041d580,A9
   [ A0]   FSUBDP  .L1X    A5:A4,B7:B6,A7:A6 ; |120| 
           FMPYDP  .M2     B17:B16,B19:B18,B17:B16 ; |68| 
           MVKL    .S1     0x4b67ce0f,A8
           MVKH    .S1     0xc041d580,A9
           MVKH    .S1     0x4b67ce0f,A8
           FMPYDP  .M2     B5:B4,B17:B16,B19:B18 ; |68| 
           MV      .L1X    B9,A21            ; |68| 
           ZERO    .L1     A20               ; |66| 
           MVKL    .S1     0xc05007ff,A25
           FSUBDP  .L2     B9:B8,B19:B18,B19:B18 ; |68| 
           MVKL    .S1     0x12b3b59a,A24
           MVKH    .S1     0xc05007ff,A25
           FMPYDP  .M2     B17:B16,B19:B18,B17:B16 ; |68| 
           MVKH    .S1     0x12b3b59a,A24
           NOP             2
           FMPYDP  .M2     B5:B4,B17:B16,B5:B4 ; |68| 
           NOP             3
           FSUBDP  .L2     B9:B8,B5:B4,B5:B4 ; |68| 
           ZERO    .L2     B8                ; |66| 
           NOP             1
           FMPYDP  .M2     B17:B16,B5:B4,B5:B4 ; |68| 
           NOP             4
           FMPYDP  .M1X    A7:A6,B5:B4,A5:A4 ; |68| 
           ZERO    .L2     B5:B4             ; |70| 
           CMPEQDP .S2X    A7:A6,B5:B4,B0    ; |70| 
           NOP             1
   [ B0]   ZERO    .L1     A5:A4             ; |71| 
           DADD    .L1     0,A5:A4,A19:A18   ; |74| 
           FMPYDP  .M1     A19:A18,A19:A18,A7:A6 ; |130| 
           MVKL    .S2     0x40738083,B5
           MVKL    .S2     0xfa15267e,B4
           MVKH    .S2     0x40738083,B5
           FADDDP  .L1     A9:A8,A7:A6,A5:A4 ; |66| 
           MVKH    .S2     0xfa15267e,B4
           NOP             1
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |66| 
           NOP             3
           FADDDP  .L1X    B5:B4,A5:A4,A9:A8 ; |66| 
           MVKL    .S1     0xc0880bfe,A5
           MVKL    .S1     0x9c0d9077,A4
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |66| 
           MVKH    .S1     0xc0880bfe,A5
           MVKH    .S1     0x9c0d9077,A4
           MVKL    .S2     0xbfe94415,B5
           FADDDP  .L1     A5:A4,A9:A8,A5:A4 ; |66| 
           MVKL    .S2     0xb356bd29,B4
           MVKH    .S2     0xbfe94415,B5
           RCPDP   .S1     A5:A4,A9:A8       ; |66| 
           MVKH    .S2     0xb356bd29,B4
           FMPYDP  .M1     A9:A8,A5:A4,A17:A16 ; |66| 
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |68| 
           NOP             2
           FSUBDP  .L1     A21:A20,A17:A16,A17:A16 ; |66| 
           NOP             2
           FMPYDP  .M1     A9:A8,A17:A16,A9:A8 ; |66| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A17:A16 ; |66| 
           NOP             4
           FSUBDP  .L2X    B9:B8,A17:A16,B7:B6 ; |66| 
           MVKL    .S1     0x2016afed,A16
           MVKL    .S1     0x4030624a,A17
           MVKH    .S1     0x2016afed,A16
           FMPYDP  .M1X    A9:A8,B7:B6,A21:A20 ; |66| 
           MVKH    .S1     0x4030624a,A17
           FADDDP  .L1X    A17:A16,B5:B4,A23:A22 ; |68| 
           MV      .L1X    B9,A17            ; |68| 
           FMPYDP  .M1     A21:A20,A5:A4,A9:A8 ; |68| 
           ZERO    .L1     A16               ; |68| 
           FMPYDP  .M1     A7:A6,A23:A22,A5:A4 ; |68| 
           ZERO    .L2     B5:B4             ; |70| 
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |68| 
           MVKL    .S2     0xbf2bd010,B7
           MVKL    .S2     0x5c610ca8,B6

           FMPYDP  .M1     A21:A20,A9:A8,A5:A4 ; |68| 
||         FADDDP  .L1     A25:A24,A5:A4,A9:A8 ; |68| 

           MVKH    .S2     0xbf2bd010,B7
           MVKH    .S2     0x5c610ca8,B6
           NOP             1
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |68| 
           CMPEQDP .S2X    A9:A8,B5:B4,B0    ; |70| 
           NOP             1
           MVK     .S2     1022,B4           ; |108| 

   [ B0]   ZERO    .L1     A5:A4             ; |71| 
||         SUB     .L2X    A1,B4,B4          ; |108| 

           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |138| 
|| [!A0]   SUB     .L2     B4,1,B4           ; |126| 

           INTDP   .L2     B4,B5:B4          ; |138| 
           MVKL    .S1     0x3fe63000,A7
           MVKH    .S1     0x3fe63000,A7
           FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |138| 
           ZERO    .L1     A6                ; |138| 
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |138| 
           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |138| 
           FADDDP  .L1     A5:A4,A19:A18,A5:A4 ; |138| 
           NOP             2

           RETNOP  .S2     B3,2              ; |139| 
||         FADDDP  .L1X    A5:A4,B7:B6,A5:A4 ; |138| 

           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |138| 
           NOP             2
           ; BRANCH OCCURS {B3}              ; |139| 
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
;*   Local Frame Size  : 8 Args + 12 Auto + 56 Save = 76 byte                 *
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

           STW     .D2T2   B3,*SP--(32)      ; |122| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKL    .S1     a,A14
           MVK     .S1     0xc9,A3

           MVKH    .S1     a,A14
||         MVKL    .S2     output,B10

           CALL    .S1     atanh             ; |139| 
||         MV      .L1     A14,A10
||         MV      .D1     A3,A11
||         MVKH    .S2     output,B10
||         ZERO    .L2     B11

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |139| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |139| 
$C$RL1:    ; CALL OCCURS {atanh} {0}         ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B10,B4           ; |139| 
||         SUB     .L1     A11,1,A0          ; |138| 
||         SUB     .S1     A11,1,A11         ; |138| 

   [ A0]   BNOP    .S2     $C$L1,2           ; |138| 
|| [!A0]   MVK     .S1     0xc9,A3
|| [!A0]   ADD     .L2     4,B10,B12
|| [!A0]   MV      .L1     A14,A10

   [!A0]   MV      .L1     A3,A11

           ADD     .L2     B11,B4,B4         ; |139| 
||         ADD     .S2     8,B11,B11         ; |138| 

   [ A0]   CALL    .S1     atanh             ; |139| 
|| [!A0]   ZERO    .L2     B11
||         STDW    .D2T1   A5:A4,*B4         ; |139| 

           ; BRANCHCC OCCURS {$C$L1}         ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     atanhdp           ; |142| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |142| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |142| 
$C$RL2:    ; CALL OCCURS {atanhdp} {0}       ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |142| 
||         SUB     .L1     A11,1,A0          ; |141| 
||         SUB     .S1     A11,1,A11         ; |141| 

   [ A0]   BNOP    .S2     $C$L2,2           ; |141| 
|| [!A0]   MVK     .S1     0xc9,A3
|| [!A0]   ADD     .L2     4,B12,B12
|| [!A0]   MV      .L1     A14,A11

   [!A0]   MV      .L1     A3,A10

           ADD     .L2     B11,B4,B4         ; |142| 
||         ADD     .S2     8,B11,B11         ; |141| 

   [ A0]   CALL    .S1     atanhdp           ; |142| 
|| [!A0]   ZERO    .L2     B11
||         STDW    .D2T1   A5:A4,*B4         ; |142| 

           ; BRANCHCC OCCURS {$C$L2}         ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     atanhdp_c         ; |145| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |145| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |145| 
$C$RL3:    ; CALL OCCURS {atanhdp_c} {0}     ; |145| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |145| 
||         SUB     .L1     A10,1,A0          ; |144| 
||         SUB     .S1     A10,1,A10         ; |144| 

   [ A0]   BNOP    .S1     $C$L3,2           ; |144| 
|| [!A0]   ZERO    .L2     B5

   [!A0]   SET     .S2     B5,0x0,0x1e,B5

           ADD     .L2     B11,B4,B4         ; |145| 
||         ADD     .S2     8,B11,B11         ; |144| 

   [ A0]   CALL    .S1     atanhdp_c         ; |145| 
||         STDW    .D2T1   A5:A4,*B4         ; |145| 
|| [!A0]   ZERO    .L1     A5
|| [!A0]   MVK     .L2     0xffffffff,B4

           ; BRANCHCC OCCURS {$C$L3}         ; |144| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           ZERO    .L1     A4
||         SET     .S1     A5,0x14,0x1e,A5
||         ZERO    .D1     A31
||         ZERO    .L2     B22
||         MVK     .S2     0xc9,B1
||         SUB     .D2X    A14,8,B23

           DADD    .L1X    0,B5:B4,A13:A12
||         STDW    .D2T1   A5:A4,*+SP(16)
||         ZERO    .S1     A10               ; |205| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 15

           ZERO    .L1     A5:A4             ; |180| 
||         LDDW    .D2T2   *++B23,B5:B4      ; |148| 

           MVKL    .S2     0x3fb99999,B7
           MVKL    .S2     0x9999999a,B6
           MVKH    .S2     0x3fb99999,B7
           MVKH    .S2     0x9999999a,B6

           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |180| 
||         ABSDP   .S2     B5:B4,B21:B20     ; |177| 

           NOP             1

           CMPGTDP .S2     B21:B20,B7:B6,B0  ; |184| 
|| [ A0]   ZERO    .L1     A27
|| [!A0]   ZERO    .S1     A27
|| [ A0]   ZERO    .D1     A26               ; |180| 

   [!A0]   ZERO    .L1     A26               ; |180| 

   [ B0]   ZERO    .L2     B5
|| [!B0]   B       .S1     $C$L5             ; |184| 
|| [ B0]   ZERO    .S2     B4                ; |68| 

   [ B0]   SET     .S2     B5,0x14,0x1d,B5
   [ B0]   FSUBDP  .L2     B5:B4,B21:B20,B5:B4 ; |68| 
   [!A0]   SET     .S1     A27,0x14,0x1d,A27
   [ A0]   MVKH    .S1     0xbff00000,A27

           RCPDP   .S2     B5:B4,B7:B6       ; |68| 
|| [!B0]   FMPYDP  .M2     B5:B4,B5:B4,B5:B4 ; |193| 

           ; BRANCHCC OCCURS {$C$L5}         ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           ZERO    .L1     A4                ; |68| 
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |68| 
           ZERO    .L1     A5
           SET     .S1     A5,0x1e,0x1e,A5
           ZERO    .L1     A9
           ZERO    .L1     A8                ; |68| 
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |68| 
           SET     .S1     A9,0x1e,0x1e,A9
           NOP             1
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |68| 
           ZERO    .L2     B6                ; |68| 
           MV      .L2X    A9,B7             ; |68| 
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A7:A6 ; |68| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |68| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |68| 
           SET     .S1     A31,0x14,0x1d,A7
           MV      .L1     A8,A6             ; |68| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |68| 
           NOP             3
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |68| 
           FADDDP  .L2X    A7:A6,B21:B20,B7:B6 ; |68| 
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |68| 
           ZERO    .L1     A5:A4             ; |70| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |68| 
           CALL    .S1     logdp_atanhdp_i   ; |201| 
           CMPEQDP .S2X    B7:B6,A5:A4,B0    ; |70| 
           NOP             1
   [ B0]   ZERO    .L2     B5:B4             ; |71| 
           ADDKPC  .S2     $C$RL4,B3,0       ; |201| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |201| 
$C$RL4:    ; CALL OCCURS {logdp_atanhdp_i} {0}  ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           ZERO    .L1     A11
||         ADDAW   .D2     B10,3,B4
||         ZERO    .S1     A7
||         ZERO    .D1     A6                ; |202| 

           LDW     .D2T1   *B4,A3
||         SET     .S1     A11,0x14,0x1d,A11
||         B       .S2     $C$L6             ; |202| 
||         ZERO    .L2     B4                ; |205| 

           SET     .S1     A7,0x15,0x1d,A7

           MV      .L2X    A11,B5            ; |205| 
||         FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |202| 
||         CMPGTDP .S1X    B21:B20,A11:A10,A0 ; |205| 

           CMPEQDP .S2     B21:B20,B5:B4,B0  ; |209| 
           SUB     .L2     B1,1,B1           ; |147| 

   [ B0]   LDDW    .D2T1   *+SP(16),A5:A4    ; |206| 
||         ADD     .L2     8,B22,B22         ; |147| 
||         ADD     .L1X    B22,A3,A3

           ; BRANCH OCCURS {$C$L6}           ; |202| 
;** --------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 26

           MVKL    .S1     0x7f12091,A6
||         ADDAW   .D2     B10,3,B31

           MVKL    .S1     0x3fc9992a,A7
||         MVKL    .S2     0xb81d48c0,B16
||         LDW     .D2T1   *B31,A3

           MVKL    .S1     0x3fd55555,A5
||         MVKL    .S2     0x3fc2914f,B17

           FMPYDP  .M2     B5:B4,B5:B4,B7:B6 ; |193| 
||         MVKL    .S1     0x6f13a03b,A4
||         MVKH    .S2     0xb81d48c0,B16

           MVKH    .S1     0x7f12091,A6
           MVKH    .S1     0x3fc9992a,A7
           MVKH    .S1     0x3fd55555,A5

           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |193| 
||         MVKH    .S1     0x6f13a03b,A4

           FMPYDP  .M1X    A7:A6,B7:B6,A7:A6 ; |193| 
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |193| 
           MVKH    .S2     0x3fc2914f,B17
           FMPYDP  .M2     B17:B16,B9:B8,B5:B4 ; |193| 
           SUB     .L2     B1,1,B1           ; |147| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |193| 
           ZERO    .L1     A11
           ADD     .S1X    B22,A3,A3
           FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |193| 
           ADD     .L2     8,B22,B22         ; |147| 
           SET     .S1     A11,0x14,0x1d,A11
           FMPYDP  .M1X    B21:B20,A5:A4,A5:A4 ; |193| 
           ZERO    .L2     B4                ; |205| 
           MV      .L2X    A11,B5            ; |205| 
           CMPEQDP .S2     B21:B20,B5:B4,B0  ; |209| 
           FADDDP  .L1X    B21:B20,A5:A4,A7:A6 ; |193| 
           CMPGTDP .S1X    B21:B20,A11:A10,A0 ; |205| 
   [ B0]   LDDW    .D2T1   *+SP(16),A5:A4    ; |206| 
;** --------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 10
   [ A0]   DADD    .L1     0,A13:A12,A7:A6   ; |206| 
           NOP             3

   [ B0]   DADD    .L1     0,A5:A4,A7:A6     ; |210| 
|| [ B1]   B       .S1     $C$L4             ; |147| 

           FMPYDP  .M1     A27:A26,A7:A6,A5:A4 ; |148| 
           NOP             3

   [!B1]   CALL    .S1     atanhdp_v         ; |150| 
||         STDW    .D1T1   A5:A4,*A3         ; |148| 

           ; BRANCHCC OCCURS {$C$L4}         ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B10(16),B4      ; |150| 
           MV      .L1     A14,A4            ; |150| 
           MVK     .S1     0xc9,A6           ; |150| 
           ADDKPC  .S2     $C$RL5,B3,1       ; |150| 
$C$RL5:    ; CALL OCCURS {atanhdp_v} {0}     ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
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

           MVKL    .S1     fcn_pass,A10
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     fcn_pass,A10
||         MVKL    .S2     0x3ddb7cdf,B7

           MV      .L1     A10,A3            ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           STW     .D1T1   A4,*+A3(4)        ; |66| 
||         LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           MV      .L1     A10,A3
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2     B10,B11
||         STW     .D1T1   A4,*+A3(8)        ; |67| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0xd9d7bdbb,B6

           MVK     .S1     16,A14
||         MV      .L1     A10,A3            ; |69| 
||         MVKL    .S2     0x3ddb7cdf,B7

           ADD     .L1X    B11,A14,A14
||         STW     .D1T1   A4,*+A3(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1X    B10,A3            ; |69| 
||         LDW     .D1T2   *A14,B4           ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL9:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L1     4,A10,A15
           LDW     .D1T1   *A15,A0           ; |72| 
           MV      .L1     A10,A3            ; |72| 
           ADD     .L2X    8,A10,B12
           STW     .D1T1   A4,*+A3(16)       ; |69| 
           NOP             1

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B12,B0           ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |156| 
   [ A0]   ADD     .L2     4,B12,B4
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
           CALL    .S1     print_test_results ; |156| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |156| 
||         STW     .D1T2   B4,*A3            ; |72| 
||         ADDKPC  .S2     $C$RL10,B3,0      ; |156| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
           MVKL    .S2     a_sc,B13

           LDDW    .D2T1   *+SP(16),A5:A4    ; |169| 
||         MVKH    .S2     a_sc,B13

           STDW    .D2T1   A13:A12,*+B13(48) ; |169| 
||         MVK     .L2     0xffffffff,B4     ; |170| 
||         ZERO    .L1     A10               ; |167| 

           STDW    .D2T1   A11:A10,*+B13(32) ; |167| 
||         MV      .L2     B4,B5             ; |170| 
||         ZERO    .L1     A9

           STDW    .D2T2   B5:B4,*+B13(56)   ; |170| 
||         MVKH    .S1     0x80000000,A9
||         ZERO    .L2     B7
||         ZERO    .L1     A8                ; |164| 

           STDW    .D2T1   A9:A8,*+B13(8)    ; |164| 
||         MVKH    .S2     0xfff00000,B7
||         ZERO    .L1     A7
||         ZERO    .L2     B6                ; |166| 

           STDW    .D2T2   B7:B6,*+B13(24)   ; |166| 
||         MVKH    .S1     0xbff00000,A7
||         ZERO    .L1     A6                ; |168| 

           STDW    .D2T1   A7:A6,*+B13(40)   ; |168| 

           STDW    .D2T1   A5:A4,*+B13(16)   ; |165| 
||         ZERO    .L2     B5:B4             ; |163| 

           STDW    .D2T2   B5:B4,*B13        ; |163| 
||         ZERO    .L1     A10
||         SUB     .L2     B13,8,B10
||         MVK     .S2     0x8,B11

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
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     atanh             ; |173| 
||         LDDW    .D2T2   *++B10,B5:B4      ; |173| 

           ADDKPC  .S2     $C$RL11,B3,3      ; |173| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |173| 
$C$RL11:   ; CALL OCCURS {atanh} {0}         ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 33
           MVKL    .S1     output,A11
           MVKH    .S1     output,A11
           LDW     .D1T2   *A11,B4           ; |173| 
           NOP             4
           ADD     .L2X    A10,B4,B4         ; |173| 
           STDW    .D2T1   A5:A4,*B4         ; |173| 

           CALLP   .S2     atanhdp,B3
||         LDDW    .D2T1   *B10,A5:A4        ; |174| 

$C$RL12:   ; CALL OCCURS {atanhdp} {0}       ; |174| 
           LDW     .D1T2   *+A11(4),B4       ; |174| 
           NOP             4
           ADD     .L2X    A10,B4,B4         ; |174| 
           STDW    .D2T1   A5:A4,*B4         ; |174| 
           LDDW    .D2T2   *B10,B5:B4        ; |175| 
           NOP             4

           CALLP   .S2     atanhdp_c,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |175| 

$C$RL13:   ; CALL OCCURS {atanhdp_c} {0}     ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           LDW     .D1T1   *+A11(8),A3       ; |175| 
           MVKL    .S2     0x3fb99999,B7
           MVKL    .S2     0x9999999a,B6
           MVKH    .S2     0x3fb99999,B7
           MVKH    .S2     0x9999999a,B6
           ADD     .L1     A10,A3,A3         ; |175| 
           STDW    .D1T1   A5:A4,*A3         ; |175| 
           LDDW    .D2T2   *B10,B5:B4        ; |176| 
           ZERO    .L1     A5:A4             ; |180| 
           NOP             3

           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |180| 
||         ABSDP   .S2     B5:B4,B21:B20     ; |177| 

           NOP             1

           CMPGTDP .S2     B21:B20,B7:B6,B0  ; |184| 
|| [ A0]   ZERO    .L1     A27
|| [!A0]   ZERO    .S1     A27
|| [ A0]   ZERO    .D1     A26               ; |180| 

   [!A0]   ZERO    .L1     A26               ; |180| 

   [!B0]   B       .S1     $C$L9             ; |184| 
|| [ B0]   ZERO    .L2     B5
|| [ B0]   ZERO    .S2     B4                ; |68| 

   [ B0]   SET     .S2     B5,0x14,0x1d,B5
   [ B0]   FSUBDP  .L2     B5:B4,B21:B20,B5:B4 ; |68| 
   [!A0]   SET     .S1     A27,0x14,0x1d,A27
   [ A0]   MVKH    .S1     0xbff00000,A27

           RCPDP   .S2     B5:B4,B7:B6       ; |68| 
|| [!B0]   FMPYDP  .M2     B5:B4,B5:B4,B7:B6 ; |193| 

           ; BRANCHCC OCCURS {$C$L9}         ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           ZERO    .L1     A4                ; |68| 
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |68| 
           ZERO    .L1     A5
           SET     .S1     A5,0x1e,0x1e,A5
           ZERO    .L1     A9
           ZERO    .L1     A8                ; |68| 
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |68| 
           SET     .S1     A9,0x1e,0x1e,A9
           ZERO    .S1     A31
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |68| 
           ZERO    .L2     B6                ; |68| 
           MV      .L2X    A9,B7             ; |68| 
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A7:A6 ; |68| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |68| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |68| 
           SET     .S1     A31,0x14,0x1d,A7
           MV      .L1     A8,A6             ; |68| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |68| 
           NOP             3
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |68| 
           FADDDP  .L2X    A7:A6,B21:B20,B7:B6 ; |68| 
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |68| 
           ZERO    .L1     A5:A4             ; |70| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |68| 
           CALL    .S1     logdp_atanhdp_i   ; |201| 
           CMPEQDP .S2X    B7:B6,A5:A4,B0    ; |70| 
           NOP             1
   [ B0]   ZERO    .L2     B5:B4             ; |71| 
           ADDKPC  .S2     $C$RL14,B3,0      ; |201| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |201| 
$C$RL14:   ; CALL OCCURS {logdp_atanhdp_i} {0}  ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S2     $C$L10            ; |202| 
||         ADDAW   .D1     A11,3,A3
||         ZERO    .L1     A7
||         ZERO    .S1     A6                ; |202| 
||         ZERO    .L2     B4                ; |205| 

           LDW     .D1T1   *A3,A3            ; |176| 
||         SET     .S1     A7,0x15,0x1d,A7
||         SUB     .L1X    B11,1,A0          ; |172| 
||         SUB     .L2     B11,1,B11         ; |172| 

           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |202| 
||         ZERO    .L1     A5

           SET     .S1     A5,0x14,0x1d,A5
           ZERO    .L1     A4                ; |205| 
           MV      .L2X    A5,B5             ; |205| 
           ; BRANCH OCCURS {$C$L10}          ; |202| 
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 27
           MVKL    .S1     0x7f12091,A6

           MVKL    .S1     0x3fc9992a,A7
||         MVKL    .S2     0xb81d48c0,B16

           MVKL    .S1     0x6f13a03b,A4
||         MVKL    .S2     0x3fc2914f,B17

           FMPYDP  .M2     B7:B6,B7:B6,B5:B4 ; |193| 
||         MVKL    .S1     0x3fd55555,A5
||         MVKH    .S2     0xb81d48c0,B16

           MVKH    .S1     0x7f12091,A6
           MVKH    .S1     0x3fc9992a,A7
           MVKH    .S1     0x6f13a03b,A4

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |193| 
||         MVKH    .S1     0x3fd55555,A5

           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |193| 
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |193| 
           MVKH    .S2     0x3fc2914f,B17
           FMPYDP  .M2     B17:B16,B9:B8,B5:B4 ; |193| 
           SUB     .L1X    B11,1,A0          ; |172| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |193| 
           SUB     .L2     B11,1,B11         ; |172| 
           ADDAW   .D1     A11,3,A3
           FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |193| 
           LDW     .D1T1   *A3,A3            ; |176| 
           ZERO    .L2     B4                ; |205| 
           FMPYDP  .M1X    B21:B20,A5:A4,A5:A4 ; |193| 
           NOP             3

           FADDDP  .L1X    B21:B20,A5:A4,A7:A6 ; |193| 
||         ZERO    .S1     A5

           SET     .S1     A5,0x14,0x1d,A5
           ZERO    .S1     A4                ; |205| 
           MV      .L2X    A5,B5             ; |205| 
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 13
           CMPEQDP .S2     B21:B20,B5:B4,B0  ; |209| 
           ADD     .L1     A10,A3,A3         ; |176| 

           CMPGTDP .S2X    B21:B20,A5:A4,B1  ; |205| 
|| [ B0]   LDDW    .D2T1   *+SP(16),A5:A4    ; |206| 

           ADD     .L1     8,A10,A10         ; |172| 
   [ B1]   DADD    .L1     0,A13:A12,A7:A6   ; |206| 
   [!A0]   MV      .L2X    A11,B10
           NOP             1

   [ B0]   DADD    .L1     0,A5:A4,A7:A6     ; |210| 
|| [ A0]   B       .S1     $C$L8             ; |172| 

           FMPYDP  .M1     A27:A26,A7:A6,A5:A4 ; |176| 
           NOP             3

   [!A0]   CALL    .S1     atanhdp_v         ; |178| 
||         STDW    .D1T1   A5:A4,*A3         ; |176| 

           ; BRANCHCC OCCURS {$C$L8}         ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B10(16),B4      ; |178| 
           MV      .L1X    B13,A4
           MVK     .L1     0x8,A6            ; |178| 
           ADDKPC  .S2     $C$RL15,B3,1      ; |178| 
$C$RL15:   ; CALL OCCURS {atanhdp_v} {0}     ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .L1     0x8,A6            ; |66| 
||         MVK     .S1     0x9,A8            ; |66| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3ddb7cdf,B7

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D1T1   A4,*+A3(4)        ; |66| 
||         LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .L1     0x8,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2X    A11,B5            ; |67| 
||         STW     .D1T1   A4,*+A3(8)        ; |67| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .L1     0x8,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL18:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0xd9d7bdbb,B6

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0x3ddb7cdf,B7

           MVKH    .S1     fcn_pass,A3
||         LDW     .D1T2   *A14,B4           ; |69| 
||         MVKH    .S2     0xd9d7bdbb,B6

           STW     .D1T1   A4,*+A3(12)       ; |68| 
||         MV      .L1     A11,A3            ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .L1     0x8,A6            ; |69| 
||         MVK     .S1     0x9,A8            ; |69| 

$C$RL19:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A15,A0           ; |72| 
           MVKL    .S1     fcn_pass,A3
           MVKH    .S1     fcn_pass,A3
           STW     .D1T1   A4,*+A3(16)       ; |69| 
           NOP             1

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B12,B0           ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |182| 
   [ A0]   ADD     .L2     4,B12,B4
   [!A0]   ZERO    .L1     A4                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
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
           CALL    .S1     print_test_results ; |182| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |182| 
||         ADDKPC  .S2     $C$RL20,B3,0      ; |182| 

$C$RL20:   ; CALL OCCURS {print_test_results} {0}  ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKL    .S2     a_ext,B11

           MVKH    .S2     a_ext,B11
||         MVK     .S1     0x6d6,A3
||         ZERO    .L1     A5

           SET     .S1     A5,0x14,0x14,A5
||         ZERO    .L1     A4                ; |185| 

           CALL    .S1     atanh             ; |187| 
||         STDW    .D2T1   A5:A4,*B11        ; |185| 
||         MV      .L1X    B11,A10           ; |185| 
||         MV      .L2X    A3,B10            ; |185| 
||         ZERO    .S2     B13               ; |185| 

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
           ADDKPC  .S2     $C$RL21,B3,3      ; |187| 
$C$RL21:   ; CALL OCCURS {atanh} {0}         ; |187| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D1T1   *A11,A3           ; |187| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |187| 
           STDW    .D1T1   A5:A4,*A3         ; |187| 

           CALLP   .S2     atanhdp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |188| 

$C$RL22:   ; CALL OCCURS {atanhdp} {0}       ; |188| 
           LDW     .D1T1   *+A11(4),A3       ; |188| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |188| 
           STDW    .D1T1   A5:A4,*A3         ; |188| 

           CALLP   .S2     atanhdp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |189| 

$C$RL23:   ; CALL OCCURS {atanhdp_c} {0}     ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           LDW     .D1T1   *+A11(8),A3       ; |189| 
           ZERO    .L2     B7:B6             ; |180| 
           MVKL    .S2     0x3fb99999,B5
           MVKH    .S2     0x3fb99999,B5
           NOP             1
           ADD     .L2X    B13,A3,B4         ; |189| 
           STDW    .D2T1   A5:A4,*B4         ; |189| 
           LDDW    .D1T1   *A10,A5:A4        ; |190| 
           MVKL    .S2     0x9999999a,B4
           MVKH    .S2     0x9999999a,B4
           NOP             2

           ABSDP   .S1     A5:A4,A27:A26     ; |177| 
||         CMPLTDP .S2X    A5:A4,B7:B6,B0    ; |180| 

           NOP             1

   [ B0]   ZERO    .L2     B21
|| [!B0]   ZERO    .S2     B21
|| [ B0]   ZERO    .D2     B20               ; |180| 

           CMPGTDP .S2X    A27:A26,B5:B4,B1  ; |184| 
   [!B0]   ZERO    .L2     B20               ; |180| 

   [!B1]   B       .S1     $C$L13            ; |184| 
|| [ B1]   ZERO    .L1     A5
|| [ B1]   ZERO    .D1     A4                ; |68| 

   [ B1]   SET     .S1     A5,0x14,0x1d,A5
   [ B1]   FSUBDP  .L1     A5:A4,A27:A26,A5:A4 ; |68| 
   [!B0]   SET     .S2     B21,0x14,0x1d,B21
   [ B0]   MVKH    .S2     0xbff00000,B21

           RCPDP   .S1     A5:A4,A7:A6       ; |68| 
|| [!B1]   FMPYDP  .M1     A5:A4,A5:A4,A5:A4 ; |193| 

           ; BRANCHCC OCCURS {$C$L13}        ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 41
           ZERO    .L2     B4                ; |68| 
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |68| 
           ZERO    .L2     B5
           SET     .S2     B5,0x1e,0x1e,B5
           ZERO    .L2     B9
           ZERO    .L2     B8                ; |68| 
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |68| 
           SET     .S2     B9,0x1e,0x1e,B9
           ZERO    .S2     B31
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |68| 
           ZERO    .L1     A6                ; |68| 
           MV      .L1X    B9,A7             ; |68| 
           NOP             1
           FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |68| 
           NOP             3
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |68| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |68| 
           SET     .S2     B31,0x14,0x1d,B7
           MV      .L2     B8,B6             ; |68| 
           NOP             2
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |68| 
           NOP             3
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |68| 
           FADDDP  .L1X    B7:B6,A27:A26,A7:A6 ; |68| 
           NOP             1
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |68| 
           ZERO    .L2     B5:B4             ; |70| 
           NOP             1
           CALL    .S1     logdp_atanhdp_i   ; |201| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |68| 
           CMPEQDP .S1X    A7:A6,B5:B4,A0    ; |70| 
           ADDKPC  .S2     $C$RL24,B3,1      ; |201| 
   [ A0]   ZERO    .L1     A5:A4             ; |71| 
$C$RL24:   ; CALL OCCURS {logdp_atanhdp_i} {0}  ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L14            ; |202| 
||         ZERO    .L2     B7
||         ZERO    .S2     B5
||         ZERO    .D2     B4                ; |202| 
||         ZERO    .L1     A7
||         SUB     .D1X    B10,1,A2          ; |186| 

           ZERO    .L1     A6                ; |191| 
||         SET     .S2     B7,0x14,0x1d,B7
||         ZERO    .L2     B6                ; |205| 
||         MVKH    .S1     0xbff80000,A7

           SET     .S2     B5,0x15,0x1d,B5

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |202| 
||         MV      .L1X    B7,A5
||         ZERO    .S1     A4                ; |205| 
||         MVK     .S2     12,B8

           CMPGTDP .S2X    A27:A26,B7:B6,B0  ; |205| 
||         CMPEQDP .S1     A27:A26,A5:A4,A0  ; |209| 

           SUB     .L2     B10,1,B10         ; |186| 
           ; BRANCH OCCURS {$C$L14}          ; |202| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 25

           MVKL    .S2     0x6f13a03b,B4
||         SUB     .L1X    B10,1,A2          ; |186| 
||         SUB     .L2     B10,1,B10         ; |186| 

           MVKL    .S2     0x3fd55555,B5
||         MVKL    .S1     0xb81d48c0,A16

           MVKL    .S2     0x7f12091,B6
||         MVKL    .S1     0x3fc2914f,A17

           FMPYDP  .M1     A5:A4,A5:A4,A7:A6 ; |193| 
||         MVKL    .S2     0x3fc9992a,B7
||         MVKH    .S1     0xb81d48c0,A16

           MVKH    .S2     0x6f13a03b,B4
||         MVKH    .S1     0x3fc2914f,A17

           MVKH    .S2     0x3fd55555,B5

           MVKH    .S2     0x7f12091,B6
||         FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |193| 

           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |193| 
||         MVKH    .S2     0x3fc9992a,B7

           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |193| 
           MVK     .S2     12,B8
           ZERO    .L1     A6                ; |191| 
           FMPYDP  .M1     A17:A16,A9:A8,A5:A4 ; |193| 
           FADDDP  .S2     B7:B6,B5:B4,B5:B4 ; |193| 
           ZERO    .L2     B6                ; |205| 
           ZERO    .L2     B7
           SET     .S2     B7,0x14,0x1d,B7
           FADDDP  .L2X    A5:A4,B5:B4,B5:B4 ; |193| 
           CMPGTDP .S2X    A27:A26,B7:B6,B0  ; |205| 
           ZERO    .L1     A7
           FMPYDP  .M2X    A27:A26,B5:B4,B5:B4 ; |193| 
           ZERO    .L1     A4                ; |205| 
           MV      .L1X    B7,A5
           CMPEQDP .S1     A27:A26,A5:A4,A0  ; |209| 
           FADDDP  .S2X    A27:A26,B5:B4,B5:B4 ; |193| 
           MVKH    .S1     0xbff80000,A7
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 21
   [ A0]   LDDW    .D2T1   *+SP(16),A5:A4    ; |206| 
           ADD     .L2X    A11,B8,B8
           LDW     .D2T2   *B8,B6            ; |190| 
   [ B0]   DADD    .L2X    0,A13:A12,B5:B4   ; |206| 
           NOP             1
   [ A0]   DADD    .L2X    0,A5:A4,B5:B4     ; |210| 
           FMPYDP  .M2     B21:B20,B5:B4,B5:B4 ; |190| 
           ADD     .L2     B13,B6,B6         ; |190| 
           ADD     .L2     8,B13,B13         ; |186| 
           NOP             1
           STDW    .D2T2   B5:B4,*B6         ; |190| 
           LDDW    .D1T1   *A10,A5:A4        ; |191| 
           NOP             3
   [ A2]   B       .S1     $C$L12            ; |186| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |191| 
           NOP             3

   [ A2]   CALL    .S1     atanh             ; |187| 
||         STDW    .D1T1   A5:A4,*++A10      ; |191| 

           ; BRANCHCC OCCURS {$C$L12}        ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     atanhdp_v         ; |193| 
||         MV      .L2X    A11,B10

           LDW     .D2T2   *+B10(16),B4      ; |193| 
           ADDKPC  .S2     $C$RL25,B3,2      ; |193| 

           MV      .L1X    B11,A4
||         MVK     .S1     0x6d6,A6          ; |193| 

$C$RL25:   ; CALL OCCURS {atanhdp_v} {0}     ; |193| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0x6d6,A6          ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3ddb7cdf,B7

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D1T1   A4,*+A3(4)        ; |66| 
||         LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0x6d6,A6          ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2X    A11,B5            ; |67| 
||         STW     .D1T1   A4,*+A3(8)        ; |67| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0x6d6,A6          ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL28:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0xd9d7bdbb,B6

           MVKL    .S1     fcn_pass,A5
||         MVKL    .S2     0x3ddb7cdf,B7

           MVKH    .S1     fcn_pass,A5
||         LDW     .D1T2   *A14,B4           ; |69| 
||         MVKH    .S2     0xd9d7bdbb,B6
||         STW     .D2T1   A14,*+SP(12)      ; |68| 

           MV      .L1     A11,A3            ; |68| 
||         STW     .D1T1   A4,*+A5(12)       ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0x6d6,A6          ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL29:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A15,A0           ; |72| 
           MVKL    .S1     fcn_pass,A3
           MVKH    .S1     fcn_pass,A3
           STW     .D1T1   A4,*+A3(16)       ; |69| 
           NOP             1

   [!A0]   B       .S1     $C$L15            ; |72| 
|| [ A0]   LDW     .D2T2   *B12,B0           ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |197| 
   [ A0]   ADD     .L2     4,B12,B4
   [!A0]   ZERO    .L1     A4                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
           ; BRANCHCC OCCURS {$C$L15}        ; |72| 
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
           CALL    .S1     print_test_results ; |197| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |197| 
||         ADDKPC  .S2     $C$RL30,B3,0      ; |197| 

$C$RL30:   ; CALL OCCURS {print_test_results} {0}  ; |197| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .L1     A10               ; |114| 
||         ZERO    .D1     A11               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*A3       ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           MVC     .S2     TSCL,B6           ; |117| 
||         STDW    .D1T2   B5:B4,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 

           CALL    .S1     gimme_random      ; |207| 
||         SUBU    .L2     B6,B4,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B5,B4          ; |117| 

           MVK     .S2     0x80,B4
||         ADD     .L2     B4,B5,B7          ; |117| 
||         MVKL    .S1     t_offset,A3

           ZERO    .L2     B5
||         MVKH    .S1     t_offset,A3
||         MV      .S2X    A11,B10           ; |117| 
||         MV      .L1     A10,A4            ; |207| 
||         ZERO    .D1     A5

           MV      .L2X    A11,B4            ; |207| 
||         MV      .L1X    B4,A14            ; |117| 
||         MVKH    .S2     0xbfe00000,B5
||         STDW    .D1T2   B7:B6,*A3         ; |117| 
||         SET     .S1     A5,0x14,0x1d,A5

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL31,B3,0      ; |207| 
$C$RL31:   ; CALL OCCURS {gimme_random} {0}  ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 25
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |207| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |207| 

           STDW    .D1T1   A5:A4,*A3         ; |207| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A26            ; |122| Define a twin register
||         MVC     .S2     TSCH,B6           ; |122| 

           DADD    .L2X    0,A5:A4,B5:B4     ; |211| 
||         MVKL    .S2     0x3fb99999,B9
||         ZERO    .L1     A5:A4             ; |180| 

           ABSDP   .S2     B5:B4,B21:B20     ; |177| 
||         MV      .L1X    B6,A27            ; |122| 

           CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |180| 
           MVKL    .S2     0x9999999a,B8

           MVKH    .S2     0x3fb99999,B9
|| [ A0]   ZERO    .L1     A29
|| [!A0]   ZERO    .S1     A29
|| [ A0]   ZERO    .D1     A28               ; |180| 

           MVKH    .S2     0x9999999a,B8
           CMPGTDP .S2     B21:B20,B9:B8,B0  ; |184| 
   [!A0]   ZERO    .L1     A28               ; |180| 

   [!B0]   B       .S1     $C$L17            ; |184| 
|| [ B0]   ZERO    .L2     B5
|| [ B0]   ZERO    .S2     B4                ; |68| 

   [ B0]   SET     .S2     B5,0x14,0x1d,B5

           FSUBDP  .L2     B5:B4,B21:B20,B7:B6 ; |68| 
|| [!B0]   FMPYDP  .M2     B5:B4,B5:B4,B5:B4 ; |193| 

   [!A0]   SET     .S1     A29,0x14,0x1d,A29
   [ A0]   MVKH    .S1     0xbff00000,A29
   [ B0]   RCPDP   .S2     B7:B6,B5:B4       ; |68| 
           ; BRANCHCC OCCURS {$C$L17}        ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           ZERO    .L1     A4                ; |68| 
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |68| 
           ZERO    .L1     A5
           SET     .S1     A5,0x1e,0x1e,A5
           ZERO    .L1     A9
           ZERO    .L1     A8                ; |68| 
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |68| 
           SET     .S1     A9,0x1e,0x1e,A9
           ZERO    .S1     A31
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |68| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B7:B6,A7:A6 ; |68| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |68| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |68| 
           ZERO    .L1     A6                ; |68| 
           SET     .S1     A31,0x14,0x1d,A7
           NOP             2
           FMPYDP  .M2X    A5:A4,B7:B6,B5:B4 ; |68| 
           ZERO    .L2     B6                ; |68| 
           MV      .L2X    A9,B7             ; |68| 
           NOP             1
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |68| 
           FADDDP  .L2X    A7:A6,B21:B20,B7:B6 ; |68| 
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |68| 
           ZERO    .L1     A5:A4             ; |70| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |68| 
           CALL    .S1     logdp_atanhdp_i   ; |201| 
           CMPEQDP .S2X    B7:B6,A5:A4,B0    ; |70| 
           NOP             1
   [ B0]   ZERO    .L2     B5:B4             ; |71| 
           ADDKPC  .S2     $C$RL32,B3,0      ; |201| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |201| 
$C$RL32:   ; CALL OCCURS {logdp_atanhdp_i} {0}  ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           ZERO    .L2     B5
||         MV      .D2X    A10,B4            ; |205| 
||         ZERO    .L1     A7
||         ZERO    .D1     A6                ; |202| 
||         MVKL    .S2     output+12,B6
||         B       .S1     $C$L18            ; |202| 

           SET     .S2     B5,0x14,0x1d,B5
||         SET     .S1     A7,0x15,0x1d,A7

           CMPEQDP .S2     B21:B20,B5:B4,B0  ; |209| 
||         FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |202| 
||         MV      .L1     A11,A6
||         MVKL    .S1     t_start,A3

           MV      .L1X    B5,A7             ; |209| 
||         MVKH    .S1     t_start,A3

           CMPGTDP .S1X    B21:B20,A7:A6,A0  ; |205| 
|| [ B0]   LDDW    .D2T1   *+SP(16),A7:A6    ; |206| 
||         MVKH    .S2     output+12,B6

           LDW     .D2T2   *B6,B4            ; |211| 
||         STDW    .D1T1   A27:A26,*A3

           ; BRANCH OCCURS {$C$L18}          ; |202| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 25

           FMPYDP  .M2     B5:B4,B5:B4,B7:B6 ; |193| 
||         MVKL    .S1     0x7f12091,A6

           MVKL    .S1     0x3fc9992a,A7
||         MVKL    .S2     0xb81d48c0,B16

           MVKL    .S1     0x6f13a03b,A4
||         MVKL    .S2     0x3fc2914f,B17

           MVKL    .S1     0x3fd55555,A5
||         MVKH    .S2     0xb81d48c0,B16

           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |193| 
||         MVKH    .S1     0x7f12091,A6
||         MVKH    .S2     0x3fc2914f,B17

           MVKH    .S1     0x3fc9992a,A7

           MVKH    .S1     0x6f13a03b,A4
||         FMPYDP  .M1X    A7:A6,B7:B6,A7:A6 ; |193| 
||         MVKL    .S2     output+12,B6

           MVKH    .S1     0x3fd55555,A5
||         MVKH    .S2     output+12,B6

           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |193| 
           MVKL    .S1     t_start,A3
           FMPYDP  .M2     B17:B16,B9:B8,B5:B4 ; |193| 
           MVKH    .S1     t_start,A3
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |193| 
           STDW    .D1T1   A27:A26,*A3
           MV      .S1     A11,A6

           MV      .L2X    A10,B4            ; |205| 
||         FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |193| 

           ZERO    .L2     B5
           SET     .S2     B5,0x14,0x1d,B5
           FMPYDP  .M1X    B21:B20,A5:A4,A5:A4 ; |193| 
           MV      .L1X    B5,A7             ; |209| 
           CMPGTDP .S1X    B21:B20,A7:A6,A0  ; |205| 
           CMPEQDP .S2     B21:B20,B5:B4,B0  ; |209| 
           FADDDP  .L1X    B21:B20,A5:A4,A5:A4 ; |193| 
   [ B0]   LDDW    .D2T1   *+SP(16),A7:A6    ; |206| 
           LDW     .D2T2   *B6,B4            ; |211| 
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 27
   [ A0]   DADD    .L1     0,A13:A12,A5:A4   ; |206| 
           NOP             2
   [ B0]   DADD    .L1     0,A7:A6,A5:A4     ; |210| 
           FMPYDP  .M1     A29:A28,A5:A4,A5:A4 ; |211| 
           ADD     .L2     B10,B4,B4         ; |211| 
           NOP             2

           STDW    .D2T1   A5:A4,*B4         ; |211| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A3
||         MVKL    .S2     cycle_counts+24,B5
||         SUB     .L1     A14,1,A0          ; |205| 
||         MV      .L2     B4,B17            ; |128| 
||         SUB     .D1     A14,1,A14         ; |205| 
||         ADD     .D2     8,B10,B10         ; |205| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     cycle_counts+24,B5

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           MVKL    .S1     t_stop,A31
           LDDW    .D2T2   *B5,B7:B6         ; |130| 
           MVKH    .S1     t_stop,A31
           STDW    .D1T2   B17:B16,*A31      ; |128| 
           ADDU    .L1     A6,A26,A5:A4      ; |130| 
           ADD     .L1     A5,A7,A5          ; |130| 

           ADD     .L1     A5,A27,A3         ; |130| 
|| [ A0]   ZERO    .S1     A5

   [ A0]   SET     .S1     A5,0x14,0x1d,A5

   [ A0]   B       .S2     $C$L16            ; |205| 
||         SUB     .L2X    B4,A3,B9          ; |130| 
||         MVKL    .S1     cycle_counts+24,A3

   [ A0]   CALL    .S2     gimme_random      ; |207| 
||         SUBU    .L2X    B16,A4,B5:B4      ; |130| 
||         MVKH    .S1     cycle_counts+24,A3
|| [ A0]   MV      .L1     A10,A4            ; |207| 

           EXT     .S2     B5,24,24,B8       ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 
|| [!A0]   MV      .L1     A3,A4

           MV      .L2     B4,B6             ; |130| 
||         ADD     .S2     B5,B7,B4          ; |130| 
||         ADD     .D2     B9,B8,B5          ; |130| 
|| [!A0]   SUBAW   .D1     A4,6,A14

           ADD     .L2     B4,B5,B7          ; |130| 
|| [ A0]   ZERO    .S2     B5
|| [ A0]   MV      .D2X    A11,B4            ; |207| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T2   B7:B6,*A3         ; |130| 
|| [ A0]   MVKH    .S2     0xbfe00000,B5

           ; BRANCHCC OCCURS {$C$L16}        ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A14(24),A5:A4   ; |135| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |135| 
$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         STDW    .D1T1   A11:A10,*+A14(8)  ; |114| 
||         MV      .L2X    A10,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A3         ; |135| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B9           ; |117| 
           MVKL    .S1     t_offset,A3
           MVKH    .S1     t_offset,A3
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           MVK     .S1     0x80,A3
||         MV      .L2X    A3,B8             ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .D2     B9,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 

           STDW    .D2T2   B7:B6,*B8         ; |117| 
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
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |220| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |220| 
||         CALL    .S1     atanhdp           ; |220| 

           LDDW    .D1T1   *A3,A5:A4         ; |220| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |220| 
$C$RL35:   ; CALL OCCURS {atanhdp} {0}       ; |220| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+4,B4
           MVKH    .S2     output+4,B4
           LDW     .D2T2   *B4,B4            ; |220| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |220| 

           STDW    .D1T1   A5:A4,*A3         ; |220| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B8           ; |128| 

           MVKL    .S2     t_start,B4
||         MVKL    .S1     t_offset,A3
||         SUB     .L1X    B10,1,A0          ; |218| 
||         MV      .L2     B8,B17            ; |128| 
||         ADD     .D1     8,A12,A12         ; |218| 
||         SUB     .D2     B10,1,B10         ; |218| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     t_start,B4

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         LDDW    .D2T2   *B4,B7:B6         ; |130| 
||         MVKL    .S1     cycle_counts+8,A31
||         MVKL    .S2     cycle_counts+8,B11

           MVKH    .S1     cycle_counts+8,A31
||         MVKH    .S2     cycle_counts+8,B11

           LDDW    .D1T1   *A31,A7:A6        ; |130| 
||         MVKL    .S1     t_stop,A30

           MVKH    .S1     t_stop,A30
           STDW    .D1T2   B17:B16,*A30      ; |128| 
           ADDU    .L2X    A4,B6,B5:B4       ; |130| 

           ADD     .S2X    B5,A5,B6          ; |130| 
|| [ A0]   B       .S1     $C$L19            ; |218| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B8,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B11        ; |130| 

           ; BRANCHCC OCCURS {$C$L19}        ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A14(8),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |135| 
$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A11,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           MV      .L2X    A10,B4            ; |114| 
||         STDW    .D1T1   A11:A10,*+A14(16) ; |114| 

           STDW    .D2T1   A5:A4,*B11        ; |135| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MVK     .S1     0x80,A3

           NOP             1
           MV      .L2X    A3,B10            ; |117| 
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
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |229| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |229| 
||         CALL    .S1     atanhdp_c         ; |229| 

           LDDW    .D1T1   *A3,A5:A4         ; |229| 
           ADDKPC  .S2     $C$RL38,B3,3      ; |229| 
$C$RL38:   ; CALL OCCURS {atanhdp_c} {0}     ; |229| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+8,B4
           MVKH    .S2     output+8,B4
           LDW     .D2T2   *B4,B4            ; |229| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |229| 

           STDW    .D1T1   A5:A4,*A3         ; |229| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B8           ; |128| 

           MVKL    .S2     t_start,B4
||         MVKL    .S1     t_offset,A3
||         SUB     .L1X    B10,1,A0          ; |227| 
||         ADDAD   .D2     B11,1,B13
||         MV      .L2     B8,B17            ; |128| 
||         ADD     .D1     8,A12,A12         ; |227| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     t_start,B4
||         SUB     .L2     B10,1,B10         ; |227| 

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         LDDW    .D2T2   *B4,B7:B6         ; |130| 
||         MVK     .S1     8,A31

           ADD     .L1X    B11,A31,A3
||         MVKL    .S1     t_stop,A30

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           MVKH    .S1     t_stop,A30
           STDW    .D1T2   B17:B16,*A30      ; |128| 
           ADDU    .L2X    A4,B6,B5:B4       ; |130| 

           ADD     .S2X    B5,A5,B6          ; |130| 
|| [ A0]   B       .S1     $C$L20            ; |227| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B8,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B13        ; |130| 

           ; BRANCHCC OCCURS {$C$L20}        ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D2T1   *B13,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |135| 
$C$RL39:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A11,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A11:A10,*A14      ; |114| 
||         MV      .L2X    A10,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A5:A4,*B13        ; |135| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B4,B4          ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B7:B6,*A3         ; |117| 
||         MVK     .S1     0x80,A12
||         MV      .L1     A12,A14           ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |238| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A14,A3,A3         ; |238| 
||         CALL    .S1     atanh             ; |238| 

           LDDW    .D1T1   *A3,A5:A4         ; |238| 
           ADDKPC  .S2     $C$RL41,B3,3      ; |238| 
$C$RL41:   ; CALL OCCURS {atanh} {0}         ; |238| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output,B11
           MVKH    .S2     output,B11
           LDW     .D2T2   *B11,B4           ; |238| 
           NOP             4
           ADD     .L1X    A14,B4,A3         ; |238| 

           STDW    .D1T1   A5:A4,*A3         ; |238| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S2     t_start,B10
||         MVKL    .S1     t_offset,A3
||         SUB     .L1     A12,1,A0          ; |236| 
||         MV      .L2     B6,B17            ; |128| 
||         SUB     .D1     A12,1,A12         ; |236| 

           MVKH    .S2     t_start,B10
||         MVKH    .S1     t_offset,A3
||         ADD     .L1     8,A14,A14         ; |236| 

           LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         LDDW    .D2T2   *B10,B9:B8        ; |130| 
||         MVK     .S1     16,A31

           SUB     .L1X    B13,A31,A3
||         MVKL    .S1     t_stop,A30

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKH    .S1     t_stop,A30

           MV      .L2X    A3,B6             ; |128| 
           STDW    .D1T2   B17:B16,*A30      ; |128| 

           ADDU    .L2X    A4,B8,B5:B4       ; |130| 
|| [!A0]   MV      .L1X    B6,A14

           ADD     .S2X    B5,A5,B7          ; |130| 
|| [ A0]   B       .S1     $C$L21            ; |236| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B7,B9,B7          ; |130| 
||         EXT     .S2     B5,24,24,B8       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B7,B7         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B7,B8,B7          ; |130| 
           ADD     .L2     B5,B7,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B6         ; |130| 

           ; BRANCHCC OCCURS {$C$L21}        ; |236| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL42,B3,3      ; |135| 
$C$RL42:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 105
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A11,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 

           MV      .L2X    A10,B4            ; |114| 
||         STDW    .D1T1   A11:A10,*+A14(32) ; |114| 

           STDW    .D1T1   A5:A4,*A14        ; |135| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D2T2   B5:B4,*B10        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           MVKL    .S1     t_offset,A3
||         SUBU    .L2     B6,B4,B7:B6       ; |117| 

           MVKH    .S1     t_offset,A3
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           MV      .L1     A3,A10            ; |117| 
||         MVKL    .S1     input,A3
||         ADD     .L2     B5,B7,B7          ; |117| 

           MVKH    .S1     input,A3
||         STDW    .D1T2   B7:B6,*A10        ; |117| 

           CALLP   .S2     atanhdp_v,B3
||         LDW     .D1T1   *A3,A4            ; |245| 
||         LDW     .D2T2   *+B11(16),B4      ; |245| 
||         MVK     .S1     0x80,A6           ; |245| 

$C$RL44:   ; CALL OCCURS {atanhdp_v} {0}     ; |245| 
           MVC     .S2     TSCL,B4           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           ADDAD   .D2     B13,2,B10
           LDDW    .D2T2   *B10,B9:B8        ; |130| 
           MVKL    .S1     t_stop,A3
           MVKH    .S1     t_stop,A3
           ADDU    .L1X    A4,B6,A7:A6       ; |130| 

           ADD     .S1     A7,A5,A6          ; |130| 
||         SUBU    .L1X    B4,A6,A5:A4       ; |130| 

           STDW    .D1T2   B5:B4,*A3         ; |128| 

           ADD     .L2X    A6,B7,B6          ; |130| 
||         EXT     .S1     A5,24,24,A6       ; |130| 

           SUB     .L2     B5,B6,B6          ; |130| 

           ADD     .L2X    B6,A6,B6          ; |130| 
||         ADDU    .L1X    B8,A4,A5:A4       ; |130| 

           ADD     .L1X    A5,B9,A5          ; |130| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1X    A5,B6,A5          ; |130| 

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
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STDW    .D2T1   A5:A4,*B10        ; |130| 
||         MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 

$C$RL47:   ; CALL OCCURS {isequal} {0}       ; |66| 

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     fcn_pass,A3
||         MVKL    .S2     0x3ddb7cdf,B7

           MV      .L1     A3,A10            ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           STW     .D1T1   A4,*+A10(4)       ; |66| 
||         LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL48:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1X    B11,A3            ; |68| 
||         STW     .D1T1   A4,*+A10(8)       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL49:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(12),A3       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D1T1   A4,*+A10(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B11,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL50:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A15,A0           ; |72| 
           STW     .D1T1   A4,*+A10(16)      ; |69| 
           NOP             3

   [!A0]   BNOP    .S1     $C$L22,5          ; |72| 
|| [ A0]   LDW     .D2T2   *B12,B0           ; |72| 
|| [ A0]   ADD     .L2     4,B12,B4

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
   [ A0]   CALL    .S1     print_test_results ; |251| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L23}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |251| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A11,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |251| 
||         ADDKPC  .S2     $C$RL51,B3,0      ; |251| 

$C$RL51:   ; CALL OCCURS {print_test_results} {0}  ; |251| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL52:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL53:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |259| 

$C$RL54:   ; CALL OCCURS {print_profile_results} {0}  ; |259| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |262| 

$C$RL55:   ; CALL OCCURS {print_memory_results} {0}  ; |262| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(32),B3      ; |263| 
           LDDW    .D2T1   *++SP,A13:A12     ; |263| 
           LDDW    .D2T1   *++SP,A15:A14     ; |263| 
           LDDW    .D2T2   *++SP,B11:B10     ; |263| 
           LDDW    .D2T2   *++SP,B13:B12     ; |263| 

           LDW     .D2T1   *++SP(8),A10      ; |263| 
||         RET     .S2     B3                ; |263| 

           LDW     .D2T1   *++SP(8),A11      ; |263| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |263| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"atanhDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	atanh
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	atanhdp_c
	.global	atanhdp
	.global	atanhdp_v
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
