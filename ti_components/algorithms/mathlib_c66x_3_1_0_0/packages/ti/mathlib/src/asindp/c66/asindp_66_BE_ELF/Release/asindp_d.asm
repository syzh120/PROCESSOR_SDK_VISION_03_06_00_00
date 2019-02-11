;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:13:51 2013                                *
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
	.word	03f6ab441h,099301ad8h		; a[0] @ 0
	.word	03f7460cbh,0adfa0a03h		; a[1] @ 64
	.word	0bf8460cbh,0d05621d3h		; a[2] @ 128
	.word	03f8e9131h,0403edf64h		; a[3] @ 192
	.word	0bf9460cbh,0f2b239a4h		; a[4] @ 256
	.word	03f9978feh,099788c84h		; a[5] @ 320
	.word	0bf9e9131h,0ec0b5675h		; a[6] @ 384
	.word	03fa1d4b2h,04968d4abh		; a[7] @ 448
	.word	0bfa460cbh,09ccbfe1bh		; a[8] @ 512
	.word	03fa6ece5h,046156314h		; a[9] @ 576
	.word	0bfa978feh,099788c84h		; a[10] @ 640
	.word	03fac0518h,042c1f17dh		; a[11] @ 704
	.word	0bfae9131h,096251aedh		; a[12] @ 768
	.word	03fb08ea5h,09fb73ff3h		; a[13] @ 832
	.word	0bfb1d4b2h,04968d4abh		; a[14] @ 896
	.word	03fb31abeh,0f31a6963h		; a[15] @ 960
	.word	0bfb460cbh,0c7bf1bdfh		; a[16] @ 1024
	.word	03fb5a6d8h,07170b097h		; a[17] @ 1088
	.word	0bfb6ece5h,046156314h		; a[18] @ 1152
	.word	03fb832f1h,0efc6f7cch		; a[19] @ 1216
	.word	0bfb978feh,0c46baa48h		; a[20] @ 1280
	.word	03fbabf0bh,0432a213ch		; a[21] @ 1344
	.word	0bfbc0517h,096f57a6bh		; a[22] @ 1408
	.word	03fbd4b25h,0983ffd46h		; a[23] @ 1472
	.word	0bfbe9131h,0ec0b5675h		; a[24] @ 1536
	.word	03fbfd73eh,03fd6afa5h		; a[25] @ 1600
	.word	0bfc08ea5h,049d1046ah		; a[26] @ 1664
	.word	03fc131ach,04a7645d7h		; a[27] @ 1728
	.word	0bfc1d4b2h,0745bf26fh		; a[28] @ 1792
	.word	03fc277b8h,09e419f07h		; a[29] @ 1856
	.word	0bfc31abeh,0c8274b9eh		; a[30] @ 1920
	.word	03fc3bdc5h,0c8cc8d0ch		; a[31] @ 1984
	.word	0bfc460cbh,0f2b239a4h		; a[32] @ 2048
	.word	03fc503d2h,01c97e63bh		; a[33] @ 2112
	.word	0bfc5a6d8h,0467d92d3h		; a[34] @ 2176
	.word	03fc649dfh,04722d440h		; a[35] @ 2240
	.word	0bfc6ece5h,0710880d8h		; a[36] @ 2304
	.word	03fc78febh,09aee2d70h		; a[37] @ 2368
	.word	0bfc832f1h,0c4d3da07h		; a[38] @ 2432
	.word	03fc8d5f8h,0c5791b75h		; a[39] @ 2496
	.word	0bfc978feh,0ef5ec80ch		; a[40] @ 2560
	.word	03fca1c05h,0194474a4h		; a[41] @ 2624
	.word	0bfcabf0bh,0432a213ch		; a[42] @ 2688
	.word	03fcb6212h,043cf62a9h		; a[43] @ 2752
	.word	0bfcc0518h,06db50f41h		; a[44] @ 2816
	.word	03fcca81eh,0979abbd9h		; a[45] @ 2880
	.word	0bfcd4b24h,0c1806870h		; a[46] @ 2944
	.word	03fcdee2ah,0eb661508h		; a[47] @ 3008
	.word	0bfce9131h,0ec0b5675h		; a[48] @ 3072
	.word	03fcf3438h,015f1030dh		; a[49] @ 3136
	.word	0bfcfd73eh,03fd6afa5h		; a[50] @ 3200
	.word	03fd03d22h,034de2e1eh		; a[51] @ 3264
	.word	0bfd08ea5h,0b530ced5h		; a[52] @ 3328
	.word	03fd0e028h,0ca23a521h		; a[53] @ 3392
	.word	0bfd131abh,0df167b6dh		; a[54] @ 3456
	.word	03fd1832eh,0f40951b8h		; a[55] @ 3520
	.word	0bfd1d4b2h,0745bf26fh		; a[56] @ 3584
	.word	03fd22635h,0894ec8bbh		; a[57] @ 3648
	.word	0bfd277b8h,09e419f07h		; a[58] @ 3712
	.word	03fd2c93bh,0b3347553h		; a[59] @ 3776
	.word	0bfd31abfh,033871609h		; a[60] @ 3840
	.word	03fd36c42h,04879ec55h		; a[61] @ 3904
	.word	0bfd3bdc5h,05d6cc2a1h		; a[62] @ 3968
	.word	03fd40f48h,0725f98edh		; a[63] @ 4032
	.word	0bfd460cbh,0f2b239a4h		; a[64] @ 4096
	.word	03fd4b24fh,007a50fefh		; a[65] @ 4160
	.word	0bfd503d2h,01c97e63bh		; a[66] @ 4224
	.word	03fd55555h,0318abc87h		; a[67] @ 4288
	.word	0bfd5a6d8h,0b1dd5d3eh		; a[68] @ 4352
	.word	03fd5f85bh,0c6d0338ah		; a[69] @ 4416
	.word	0bfd649deh,0dbc309d5h		; a[70] @ 4480
	.word	03fd69b61h,0f0b5e021h		; a[71] @ 4544
	.word	0bfd6ece5h,0710880d8h		; a[72] @ 4608
	.word	03fd73e68h,085fb5724h		; a[73] @ 4672
	.word	0bfd78febh,09aee2d70h		; a[74] @ 4736
	.word	03fd7e16eh,0afe103bbh		; a[75] @ 4800
	.word	0bfd832f2h,03033a472h		; a[76] @ 4864
	.word	03fd88475h,045267abeh		; a[77] @ 4928
	.word	0bfd8d5f8h,05a19510ah		; a[78] @ 4992
	.word	03fd9277bh,06f0c2756h		; a[79] @ 5056
	.word	0bfd978feh,0ef5ec80ch		; a[80] @ 5120
	.word	03fd9ca82h,004519e58h		; a[81] @ 5184
	.word	0bfda1c05h,0194474a4h		; a[82] @ 5248
	.word	03fda6d88h,02e374af0h		; a[83] @ 5312
	.word	0bfdabf0bh,0ae89eba7h		; a[84] @ 5376
	.word	03fdb108eh,0c37cc1f2h		; a[85] @ 5440
	.word	0bfdb6211h,0d86f983eh		; a[86] @ 5504
	.word	03fdbb394h,0ed626e8ah		; a[87] @ 5568
	.word	0bfdc0518h,06db50f41h		; a[88] @ 5632
	.word	03fdc569bh,082a7e58dh		; a[89] @ 5696
	.word	0bfdca81eh,0979abbd9h		; a[90] @ 5760
	.word	03fdcf9a1h,0ac8d9224h		; a[91] @ 5824
	.word	0bfdd4b24h,0c1806870h		; a[92] @ 5888
	.word	03fdd9ca8h,041d30927h		; a[93] @ 5952
	.word	0bfddee2bh,056c5df73h		; a[94] @ 6016
	.word	03fde3faeh,06bb8b5bfh		; a[95] @ 6080
	.word	0bfde9131h,080ab8c0ah		; a[96] @ 6144
	.word	03fdee2b5h,000fe2cc1h		; a[97] @ 6208
	.word	0bfdf3438h,015f1030dh		; a[98] @ 6272
	.word	03fdf85bbh,02ae3d959h		; a[99] @ 6336
	.word	0bfdfd73eh,03fd6afa5h		; a[100] @ 6400
	.word	03fe01460h,0aa64c2f8h		; a[101] @ 6464
	.word	0bfe03d22h,06a8e1354h		; a[102] @ 6528
	.word	03fe065e3h,0f5077e7ah		; a[103] @ 6592
	.word	0bfe08ea5h,0b530ced5h		; a[104] @ 6656
	.word	03fe0b767h,009fa54c5h		; a[105] @ 6720
	.word	0bfe0e028h,0ca23a521h		; a[106] @ 6784
	.word	03fe108eah,0549d1047h		; a[107] @ 6848
	.word	0bfe131ach,014c660a2h		; a[108] @ 6912
	.word	03fe15a6dh,0698fe692h		; a[109] @ 6976
	.word	0bfe1832fh,029b936eeh		; a[110] @ 7040
	.word	03fe1abf0h,0b432a214h		; a[111] @ 7104
	.word	0bfe1d4b2h,03eac0d3ah		; a[112] @ 7168
	.word	03fe1fd73h,0c9257860h		; a[113] @ 7232
	.word	0bfe22635h,0894ec8bbh		; a[114] @ 7296
	.word	03fe24ef7h,013c833e1h		; a[115] @ 7360
	.word	0bfe277b8h,09e419f07h		; a[116] @ 7424
	.word	03fe2a07ah,028bb0a2dh		; a[117] @ 7488
	.word	0bfe2c93bh,0e8e45a88h		; a[118] @ 7552
	.word	03fe2f1fdh,0735dc5aeh		; a[119] @ 7616
	.word	0bfe31abeh,0fdd730d4h		; a[120] @ 7680
	.word	03fe34380h,088509bfah		; a[121] @ 7744
	.word	0bfe36c42h,04879ec55h		; a[122] @ 7808
	.word	03fe39503h,0d2f3577bh		; a[123] @ 7872
	.word	0bfe3bdc5h,05d6cc2a1h		; a[124] @ 7936
	.word	03fe3e686h,0e7e62dc7h		; a[125] @ 8000
	.word	0bfe40f48h,0a80f7e22h		; a[126] @ 8064
	.word	03fe4380ah,03288e948h		; a[127] @ 8128
	.word	0bfe460cbh,0bd02546eh		; a[128] @ 8192
	.word	03fe4898dh,0477bbf94h		; a[129] @ 8256
	.word	0bfe4b24fh,007a50fefh		; a[130] @ 8320
	.word	03fe4db10h,0921e7b15h		; a[131] @ 8384
	.word	0bfe503d2h,01c97e63bh		; a[132] @ 8448
	.word	03fe52c93h,0a7115161h		; a[133] @ 8512
	.word	0bfe55555h,0673aa1bch		; a[134] @ 8576
	.word	03fe57e16h,0f1b40ce2h		; a[135] @ 8640
	.word	0bfe5a6d8h,07c2d7808h		; a[136] @ 8704
	.word	03fe5cf9ah,006a6e32eh		; a[137] @ 8768
	.word	0bfe5f85bh,0c6d0338ah		; a[138] @ 8832
	.word	03fe6211dh,051499eb0h		; a[139] @ 8896
	.word	0bfe649deh,0dbc309d5h		; a[140] @ 8960
	.word	03fe672a0h,0663c74fbh		; a[141] @ 9024
	.word	0bfe69b62h,02665c557h		; a[142] @ 9088
	.word	03fe6c423h,0b0df307dh		; a[143] @ 9152
	.word	0bfe6ece5h,03b589ba3h		; a[144] @ 9216
	.word	03fe715a6h,0c5d206c8h		; a[145] @ 9280
	.word	0bfe73e68h,085fb5724h		; a[146] @ 9344
	.word	03fe7672ah,01074c24ah		; a[147] @ 9408
	.word	0bfe78febh,09aee2d70h		; a[148] @ 9472
	.word	03fe7b8adh,025679896h		; a[149] @ 9536
	.word	0bfe7e16eh,0afe103bbh		; a[150] @ 9600
	.word	03fe80a30h,0700a5417h		; a[151] @ 9664
	.word	0bfe832f1h,0fa83bf3dh		; a[152] @ 9728
	.word	03fe85bb3h,0baad0f98h		; a[153] @ 9792
	.word	0bfe88475h,00f769589h		; a[154] @ 9856
	.word	03fe8ad36h,0cf9fe5e4h		; a[155] @ 9920
	.word	0bfe8d5f8h,05a19510ah		; a[156] @ 9984
	.word	03fe8febah,01a42a165h		; a[157] @ 10048
	.word	0bfe9277bh,06f0c2756h		; a[158] @ 10112
	.word	03fe9503dh,02f3577b1h		; a[159] @ 10176
	.word	0bfe978feh,0b9aee2d7h		; a[160] @ 10240
	.word	03fe9a1c0h,079d83332h		; a[161] @ 10304
	.word	0bfe9ca81h,0cea1b923h		; a[162] @ 10368
	.word	03fe9f343h,08ecb097eh		; a[163] @ 10432
	.word	0bfea1c05h,0194474a4h		; a[164] @ 10496
	.word	03fea44c6h,0a3bddfcah		; a[165] @ 10560
	.word	0bfea6d88h,02e374af0h		; a[166] @ 10624
	.word	03fea9649h,0ee609b4bh		; a[167] @ 10688
	.word	0bfeabf0bh,078da0671h		; a[168] @ 10752
	.word	03feae7cdh,003537197h		; a[169] @ 10816
	.word	0bfeb108eh,08dccdcbdh		; a[170] @ 10880
	.word	03feb3950h,04df62d18h		; a[171] @ 10944
	.word	0bfeb6211h,0d86f983eh		; a[172] @ 11008
	.word	03feb8ad3h,062e90364h		; a[173] @ 11072
	.word	0bfebb394h,0ed626e8ah		; a[174] @ 11136
	.word	03febdc56h,0ad8bbee6h		; a[175] @ 11200
	.word	0bfec0518h,038052a0bh		; a[176] @ 11264
	.word	03fec2dd9h,0c27e9531h		; a[177] @ 11328
	.word	0bfec569bh,04cf80057h		; a[178] @ 11392
	.word	03fec7f5dh,00d2150b3h		; a[179] @ 11456
	.word	0bfeca81eh,0979abbd9h		; a[180] @ 11520
	.word	03fecd0e0h,0221426feh		; a[181] @ 11584
	.word	0bfecf9a1h,0ac8d9224h		; a[182] @ 11648
	.word	03fed2263h,06cb6e280h		; a[183] @ 11712
	.word	0bfed4b24h,0f7304da6h		; a[184] @ 11776
	.word	03fed73e6h,081a9b8cch		; a[185] @ 11840
	.word	0bfed9ca8h,00c2323f1h		; a[186] @ 11904
	.word	03fedc569h,0cc4c744dh		; a[187] @ 11968
	.word	0bfedee2bh,056c5df73h		; a[188] @ 12032
	.word	03fee16ech,0e13f4a99h		; a[189] @ 12096
	.word	0bfee3faeh,06bb8b5bfh		; a[190] @ 12160
	.word	03fee6870h,02be2061ah		; a[191] @ 12224
	.word	0bfee9131h,0b65b7140h		; a[192] @ 12288
	.word	03feeb9f3h,040d4dc66h		; a[193] @ 12352
	.word	0bfeee2b4h,0cb4e478ch		; a[194] @ 12416
	.word	03fef0b76h,08b7797e7h		; a[195] @ 12480
	.word	0bfef3438h,015f1030dh		; a[196] @ 12544
	.word	03fef5cf9h,0a06a6e33h		; a[197] @ 12608
	.word	0bfef85bbh,02ae3d959h		; a[198] @ 12672
	.word	03fefae7ch,0eb0d29b4h		; a[199] @ 12736
	.word	0bfefd73eh,0758694dah		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\118402 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\118404 
	.sect	".text:optci"
	.clink

;******************************************************************************
;* FUNCTION NAME: pol_est_asindp_i                                            *
;*                                                                            *
;*   Regs Modified     : A4,A5,A6,A7,A8,A9,B4,B5,B6,B7,B8,B9,A16,A17,A18,A19, *
;*                           A20,A21,A22,A23,A24,A25,A26,A27,B16,B17,B18,B19  *
;*   Regs Used         : A4,A5,A6,A7,A8,A9,B3,B4,B5,B6,B7,B8,B9,A16,A17,A18,  *
;*                           A19,A20,A21,A22,A23,A24,A25,A26,A27,B16,B17,B18, *
;*                           B19                                              *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
pol_est_asindp_i:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3f8e21a3,B17
           MVKL    .S2     0xc62a3037,B16
           MVKL    .S2     0x3fb3333c,B19
           MVKL    .S2     0x67ff42f2,B18

           FMPYDP  .M1     A5:A4,A5:A4,A17:A16 ; |124| 
||         MVKL    .S2     0x3f9f218e,B5

           MVKH    .S2     0x3f8e21a3,B17
           MVKL    .S2     0x2d6e8923,B4

           MVKL    .S1     0x3f8a6331,A7
||         MVKL    .S2     0x3fa6daed,B7

           FMPYDP  .M1     A17:A16,A17:A16,A9:A8 ; |124| 
||         MVKL    .S1     0xb088e0d4,A6
||         MVKH    .S2     0xc62a3037,B16

           MVKL    .S1     0x3fc55555,A21
||         MVKL    .S2     0x7e834e0f,B6

           MVKH    .S1     0x3f8a6331,A7
||         MVKL    .S2     0x3f92080d,B9

           MVKH    .S1     0xb088e0d4,A6
||         MVKL    .S2     0x726cfcda,B8

           FMPYDP  .M1     A7:A6,A9:A8,A23:A22 ; |124| 
||         MVKH    .S2     0x3fb3333c,B19
||         MVKL    .S1     0x20991e58,A20

           FMPYDP  .M2X    B17:B16,A17:A16,B17:B16 ; |124| 
||         FMPYDP  .M1     A9:A8,A9:A8,A19:A18 ; |124| 
||         MVKH    .S2     0x67ff42f2,B18
||         MVKH    .S1     0x3fc55555,A21

           FMPYDP  .M1     A9:A8,A17:A16,A7:A6 ; |124| 
||         MVKH    .S1     0x20991e58,A20
||         MVKH    .S2     0x3f9f218e,B5

           FMPYDP  .M1     A21:A20,A17:A16,A27:A26 ; |130| 
||         MVKH    .S2     0x2d6e8923,B4

           FMPYDP  .M1X    B19:B18,A9:A8,A21:A20 ; |130| 
||         MVKH    .S2     0x3fa6daed,B7

           FADDDP  .L2X    B17:B16,A23:A22,B17:B16 ; |124| 
||         FMPYDP  .M1     A9:A8,A19:A18,A17:A16 ; |124| 
||         MVKH    .S2     0x7e834e0f,B6

           FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |124| 
||         FMPYDP  .M2X    B5:B4,A19:A18,B5:B4 ; |130| 
||         MVKH    .S2     0x3f92080d,B9
||         MVKL    .S1     0x3f96c6e8,A25

           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |130| 
||         MVKH    .S2     0x726cfcda,B8
||         MVKL    .S1     0xcead24b0,A24

           FADDDP  .L2     B9:B8,B17:B16,B9:B8 ; |124| 
||         MVKH    .S1     0x3f96c6e8,A25

           MVKH    .S1     0xcead24b0,A24
           FMPYDP  .M1     A25:A24,A9:A8,A7:A6 ; |124| 

           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |130| 
||         FMPYDP  .M2X    A17:A16,B9:B8,B7:B6 ; |124| 

           FADDDP  .L1     A27:A26,A21:A20,A9:A8 ; |130| 
           NOP             2
           FADDDP  .L2X    A7:A6,B7:B6,B7:B6 ; |124| 
           FADDDP  .L2X    A9:A8,B5:B4,B5:B4 ; |130| 
           NOP             2
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |130| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B5:B4,A7:A6 ; |130| 
           RETNOP  .S2     B3,2              ; |131| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |130| 
           NOP             2
           ; BRANCH OCCURS {B3}              ; |131| 
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
allequal:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STW     .D2T1   A11,*SP--(8)      ; |63| 
||         MVKL    .S2     0xe826d695,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     output,A11
||         MVKL    .S2     0x3e112e0b,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     output,A11
||         MVKH    .S2     0xe826d695,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3e112e0b,B7
||         MVK     .S1     0x1,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {isequal} {0}       ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A12
||         MVKH    .S2     0x3e112e0b,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A12
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3e112e0b,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MV      .L1     A10,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

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
;*   Local Frame Size  : 8 Args + 0 Auto + 56 Save = 64 byte                  *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |121| 
           STW     .D2T1   A10,*SP--(8)      ; |121| 
           STDW    .D2T2   B13:B12,*SP--     ; |121| 
           STDW    .D2T2   B11:B10,*SP--     ; |121| 
           STDW    .D2T1   A15:A14,*SP--     ; |121| 

           STDW    .D2T1   A13:A12,*SP--     ; |121| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(16)      ; |121| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |129| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     a,A12
||         MVKL    .S2     output,B10

           MVKH    .S1     a,A12
||         MVKH    .S2     output,B10

           MV      .L1     A12,A13
||         CALL    .S1     asin              ; |138| 
||         LDW     .D2T1   *B10,A11

           LDDW    .D1T1   *A13++,A5:A4      ; |138| 
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
           ADDKPC  .S2     $C$RL5,B3,0       ; |138| 
$C$RL5:    ; CALL OCCURS {asin} {0}          ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |137| 
||         STDW    .D1T1   A5:A4,*A11++      ; |138| 
||         SUB     .S1     A10,1,A10         ; |137| 

   [ A0]   B       .S1     $C$L3             ; |137| 
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |138| 
|| [!A0]   ADD     .L2     4,B10,B11

   [ A0]   CALL    .S1     asin              ; |138| 
   [!A0]   MV      .L1     A12,A10
   [!A0]   ZERO    .L2     B10
   [!A0]   MVK     .S1     0xc9,A3
   [!A0]   MV      .L1     A3,A11
           ; BRANCHCC OCCURS {$C$L3}         ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     asindp            ; |141| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A12++,A5:A4      ; |141| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |141| 
$C$RL6:    ; CALL OCCURS {asindp} {0}        ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |141| 
||         SUB     .L1     A11,1,A0          ; |140| 
||         SUB     .S1     A11,1,A11         ; |140| 

   [ A0]   BNOP    .S2     $C$L4,2           ; |140| 
|| [!A0]   MVK     .S1     0xc9,A3
|| [!A0]   ADD     .L2     4,B11,B11
|| [!A0]   MV      .L1     A10,A11

   [!A0]   MV      .L1     A3,A12

           ADD     .L2     B10,B4,B4         ; |141| 
||         ADD     .S2     8,B10,B10         ; |140| 

   [ A0]   CALL    .S1     asindp            ; |141| 
|| [!A0]   ZERO    .L2     B10
||         STDW    .D2T1   A5:A4,*B4         ; |141| 

           ; BRANCHCC OCCURS {$C$L4}         ; |140| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     asindp_c          ; |144| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |144| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |144| 
$C$RL7:    ; CALL OCCURS {asindp_c} {0}      ; |144| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |144| 
||         SUB     .L1     A12,1,A0          ; |143| 
||         SUB     .S1     A12,1,A12         ; |143| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |143| 
|| [!A0]   ADD     .L1X    4,B11,A30

           ADD     .L2     B10,B4,B4         ; |144| 
||         ADD     .S2     8,B10,B10         ; |143| 

   [ A0]   CALL    .S1     asindp_c          ; |144| 
||         STDW    .D2T1   A5:A4,*B4         ; |144| 

           ; BRANCHCC OCCURS {$C$L5}         ; |143| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .S2     0xc9,B1
||         SUB     .L2X    A10,8,B22
||         ZERO    .L1     A31
||         ZERO    .D2     B23
||         LDW     .D1T1   *A30,A3

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 15

           ZERO    .L2     B9
||         ZERO    .L1     A29
||         LDDW    .D2T2   *++B22,B21:B20    ; |147| 
||         MVKL    .S2     0x3fe6a09e,B7

           MVKL    .S2     0x667f3bcd,B6
           MVKH    .S2     0x3fe6a09e,B7
           MVKH    .S2     0x667f3bcd,B6
           SET     .S2     B9,0x15,0x1d,B9
           ABSDP   .S2     B21:B20,B5:B4     ; |166| 
           ZERO    .L1     A28               ; |163| 
           CMPGTDP .S2     B5:B4,B7:B6,B0    ; |169| 
           SET     .S1     A29,0x14,0x1d,A29

   [!B0]   MV      .L2X    A28,B8            ; |183| 
|| [ B0]   B       .S1     $C$L8             ; |169| 
||         MV      .S2     B0,B2             ; guard predicate rewrite

           MV      .L1X    B0,A0             ; branch predicate copy
||         CMPGTDP .S2     B5:B4,B9:B8,B0    ; |183| 

           FMPYDP  .M2     B21:B20,B21:B20,B7:B6 ; |167| 

   [ B2]   ZERO    .L2     B0                ; |183| nullify predicate
|| [ A0]   MVKL    .S2     0xe8584caa,B8

   [ B0]   B       .S1     $C$L7             ; |183| 
|| [ A0]   MVKH    .S2     0xe8584caa,B8

           MVKL    .S2     0x3febb67a,B9
           ; BRANCHCC OCCURS {$C$L8}         ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

   [ B0]   MV      .L2     B8,B6             ; |185| 
|| [!B0]   CALL    .S1     pol_est_asindp_i  ; |189| 
|| [ B0]   FADDDP  .S2     B7:B6,B7:B6,B5:B4 ; |185| 

   [ B0]   MV      .L2X    A29,B7            ; |185| 
   [ B0]   CALL    .S1     pol_est_asindp_i  ; |185| 
   [ B0]   FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |185| 
           ; BRANCHCC OCCURS {$C$L7}         ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL8,B3,0       ; |189| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |189| 
$C$RL8:    ; CALL OCCURS {pol_est_asindp_i} {0}  ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L11            ; |189| 
||         ZERO    .L2     B5:B4             ; |193| 

           CMPLTDP .S2     B21:B20,B5:B4,B0  ; |193| 
           SUB     .L2     B1,1,B1           ; |146| 

   [ B0]   ZERO    .L1     A29
|| [ B0]   ZERO    .S1     A28               ; |194| 

   [ B1]   B       .S2     $C$L6             ; |146| 
|| [ B0]   MVKH    .S1     0xbff00000,A29

           FMPYDP  .M1     A29:A28,A5:A4,A5:A4 ; |147| 
           ; BRANCH OCCURS {$C$L11}          ; |189| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL9,B3,2       ; |185| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |185| 
$C$RL9:    ; CALL OCCURS {pol_est_asindp_i} {0}  ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8

           MVKL    .S1     0x3ff921fb,A7
||         ZERO    .L2     B5
||         MV      .S2X    A28,B4            ; |186| 

           MVKL    .S1     0x54442d18,A6

           B       .S2     $C$L10            ; |187| 
||         MVKH    .S1     0x3ff921fb,A7

           MVKH    .S1     0x54442d18,A6
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |186| 
           SET     .S2     B5,0x15,0x1d,B5
           SUB     .L2     B1,1,B1           ; |146| 

           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |186| 
||         ZERO    .L2     B5:B4             ; |193| 

           ; BRANCH OCCURS {$C$L10}          ; |187| 
;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 9
           MVKH    .S2     0x3febb67a,B9
           CMPGTDP .S2     B5:B4,B9:B8,B0    ; |170| 
           MV      .L2X    A29,B5

   [!B0]   B       .S1     $C$L9             ; |170| 
||         MV      .L2X    A28,B4

   [ B0]   FSUBDP  .L2     B5:B4,B7:B6,B7:B6 ; |67| 
   [!B0]   MV      .L2X    A28,B8            ; |179| 
   [!B0]   MV      .S2X    A29,B9
           RSQRDP  .S2     B7:B6,B5:B4       ; |67| 
   [!B0]   FADDDP  .L2     B7:B6,B7:B6,B5:B4 ; |179| 
           ; BRANCHCC OCCURS {$C$L9}         ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 101
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |67| 
           ZERO    .L1     A7
           MV      .L1     A28,A4            ; |67| 
           ZERO    .L1     A5
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |67| 
           SET     .S1     A5,0x15,0x1d,A5
           MVKL    .S2     0x20991e58,B30
           MV      .L1     A28,A6            ; |67| 
           SET     .S1     A7,0x13,0x1d,A7
           FMPYDP  .M1X    A5:A4,B9:B8,A5:A4 ; |67| 
           MV      .L2X    A28,B16           ; |67| 
           ZERO    .L2     B31
           MVKL    .S2     0x726cfcda,B26
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |67| 
           ZERO    .L1     A9
           MVKL    .S2     0x3f92080d,B27
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |67| 
           MV      .L1     A28,A8            ; |67| 
           MVKH    .S2     0x20991e58,B30
           SET     .S1     A9,0x13,0x1d,A9
           MVKH    .S2     0x726cfcda,B26
           FMPYDP  .M2X    A5:A4,B7:B6,B5:B4 ; |67| 
           MVKL    .S1     0x3f8a6331,A17
           MVKH    .S2     0x3f92080d,B27
           MVKL    .S1     0xb088e0d4,A16
           MV      .L2X    A9,B17            ; |67| 
           FMPYDP  .M1X    A5:A4,B5:B4,A7:A6 ; |67| 
           MV      .L2X    A28,B4            ; |67| 
           SET     .S2     B31,0x15,0x1d,B5
           MVKL    .S2     0xcead24b0,B28
           FMPYDP  .M1X    B5:B4,A7:A6,A7:A6 ; |67| 
           MVKH    .S1     0x3f8a6331,A17
           MVKL    .S2     0x3f96c6e8,B29
           MVKH    .S1     0xb088e0d4,A16
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |67| 
           MVKH    .S2     0xcead24b0,B28
           MVKH    .S2     0x3f96c6e8,B29
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |67| 
           MVKL    .S2     0x3fc55555,B31
           MVKH    .S2     0x3fc55555,B31
           MVKL    .S1     0x3fb3333c,A9
           MVKH    .S1     0x3fb3333c,A9
           FMPYDP  .M2X    A5:A4,B7:B6,B5:B4 ; |67| 
           MVKL    .S1     0x3f8e21a3,A7
           MVKL    .S1     0xc62a3037,A6
           MVKH    .S1     0x3f8e21a3,A7
           FMPYDP  .M2X    A5:A4,B5:B4,B9:B8 ; |67| 
           SET     .S1     A31,0x15,0x1d,A5
           MV      .L1     A8,A4             ; |67| 
           MVKH    .S1     0xc62a3037,A6
           FMPYDP  .M2X    A5:A4,B9:B8,B9:B8 ; |67| 
           MVKL    .S1     0x67ff42f2,A8
           ZERO    .L1     A5:A4             ; |69| 
           MVKH    .S1     0x67ff42f2,A8
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |67| 
           CMPGTDP .S2X    B7:B6,A5:A4,B0    ; |69| 
           MVKL    .S1     0x2d6e8923,A4
           FMPYDP  .M2     B5:B4,B9:B8,B17:B16 ; |67| 
           MVKL    .S1     0x3f9f218e,A5
           MVKH    .S1     0x2d6e8923,A4
           MVKH    .S1     0x3f9f218e,A5
   [!B0]   ZERO    .L2     B17:B16           ; |70| 
           FMPYDP  .M2     B17:B16,B17:B16,B19:B18 ; |174| 
           SUB     .L2     B1,1,B1           ; |146| 
           NOP             2
           FMPYDP  .M2     B19:B18,B19:B18,B9:B8 ; |174| 

           FMPYDP  .M1X    A7:A6,B19:B18,A19:A18 ; |174| 
||         MVKL    .S1     0x3fa6daed,A7

           MVKL    .S1     0x7e834e0f,A6
           MVKH    .S1     0x3fa6daed,A7

           FMPYDP  .M2     B9:B8,B19:B18,B7:B6 ; |174| 
||         MVKH    .S1     0x7e834e0f,A6

           FMPYDP  .M1X    A17:A16,B9:B8,A17:A16 ; |174| 
           FMPYDP  .M2     B9:B8,B9:B8,B5:B4 ; |174| 
           FMPYDP  .M1X    A9:A8,B9:B8,A9:A8 ; |174| 
           FMPYDP  .M2     B9:B8,B7:B6,B25:B24 ; |174| 

           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |174| 
||         FMPYDP  .M1X    A7:A6,B7:B6,A7:A6 ; |174| 

           FMPYDP  .M2     B31:B30,B19:B18,B7:B6 ; |174| 
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |174| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |174| 
           FADDDP  .L2X    B27:B26,A17:A16,B9:B8 ; |174| 
           FMPYDP  .M2     B29:B28,B25:B24,B19:B18 ; |174| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |174| 
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |174| 
           FADDDP  .L2X    B7:B6,A9:A8,B7:B6 ; |174| 
           NOP             2

           FADDDP  .L2     B19:B18,B5:B4,B7:B6 ; |174| 
||         FADDDP  .S2X    B7:B6,A5:A4,B5:B4 ; |174| 

           MVKL    .S1     0x54442d18,A4
           MVKL    .S1     0x3ff921fb,A5
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |174| 
           MVKH    .S1     0x54442d18,A4
           MVKH    .S1     0x3ff921fb,A5
           FMPYDP  .M2     B17:B16,B5:B4,B5:B4 ; |174| 
           NOP             2
           B       .S1     $C$L10            ; |175| 
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |174| 
           NOP             3

           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |174| 
||         ZERO    .L2     B5:B4             ; |193| 

           ; BRANCH OCCURS {$C$L10}          ; |175| 
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 48

           MVKL    .S1     0xb088e0d4,A6
||         MVKL    .S2     0x20991e58,B26

           MVKL    .S1     0x3f8a6331,A7
||         MVKL    .S2     0x3fc55555,B27

           FSUBDP  .L2     B5:B4,B9:B8,B9:B8 ; |179| 
||         MVKL    .S1     0xc62a3037,A4
||         MVKL    .S2     0x726cfcda,B30

           MVKL    .S1     0x3f8e21a3,A5
||         MVKL    .S2     0x3f92080d,B31

           MVKH    .S1     0xb088e0d4,A6
||         MVKH    .S2     0x20991e58,B26

           FMPYDP  .M2     B9:B8,B9:B8,B7:B6 ; |179| 
||         MVKH    .S1     0x3f8a6331,A7
||         MVKH    .S2     0x3fc55555,B27

           MVKH    .S1     0xc62a3037,A4
||         MVKH    .S2     0x726cfcda,B30

           MVKH    .S1     0x3f8e21a3,A5
||         MVKH    .S2     0x3f92080d,B31

           MVKL    .S1     0x67ff42f2,A16
||         MVKL    .S2     0xcead24b0,B2

           FMPYDP  .M2     B7:B6,B7:B6,B5:B4 ; |179| 
||         MVKL    .S1     0x3fb3333c,A17
||         MVKL    .S2     0x3f96c6e8,B3

           FMPYDP  .M1X    A5:A4,B7:B6,A19:A18 ; |179| 
||         MVKL    .S1     0x2d6e8923,A4
||         MVKH    .S2     0xcead24b0,B2

           MVKL    .S1     0x3f9f218e,A5
||         MVKH    .S2     0x3f96c6e8,B3

           MVKH    .S1     0x67ff42f2,A16

           FMPYDP  .M2     B5:B4,B7:B6,B17:B16 ; |179| 
||         MVKH    .S1     0x3fb3333c,A17

           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |179| 
||         FMPYDP  .M2     B5:B4,B5:B4,B19:B18 ; |179| 
||         MVKL    .S1     0x7e834e0f,A8

           MVKL    .S1     0x3fa6daed,A9
||         FMPYDP  .M2X    A17:A16,B5:B4,B25:B24 ; |179| 

           MVKH    .S1     0x2d6e8923,A4
||         FMPYDP  .M2     B27:B26,B7:B6,B7:B6 ; |179| 

           MVKH    .S1     0x3f9f218e,A5
||         FMPYDP  .M2     B5:B4,B17:B16,B29:B28 ; |179| 

           FADDDP  .L1     A19:A18,A7:A6,A7:A6 ; |179| 
||         MVKH    .S1     0x7e834e0f,A8

           MVKH    .S1     0x3fa6daed,A9
||         FMPYDP  .M1X    A5:A4,B19:B18,A5:A4 ; |179| 

           FMPYDP  .M1X    A9:A8,B17:B16,A9:A8 ; |179| 
           FMPYDP  .M2     B5:B4,B19:B18,B5:B4 ; |179| 
           FADDDP  .L2X    B31:B30,A7:A6,B17:B16 ; |179| 
           FMPYDP  .M2     B3:B2,B29:B28,B19:B18 ; |179| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |179| 

           FMPYDP  .M2     B5:B4,B17:B16,B17:B16 ; |179| 
||         FADDDP  .L2     B7:B6,B25:B24,B5:B4 ; |179| 

           SUB     .L2     B1,1,B1           ; |146| 
           NOP             1
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |179| 
           FADDDP  .L2     B19:B18,B17:B16,B7:B6 ; |179| 
           MVKL    .S1     0x54442d18,A4
           MVKL    .S1     0x3fe921fb,A5
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |179| 
           MV      .L2X    A28,B6            ; |179| 
           SET     .S2     B23,0x15,0x1d,B7
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |179| 
           MVKH    .S1     0x54442d18,A4
           MVKH    .S1     0x3fe921fb,A5
           NOP             1
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |179| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |179| 
           NOP             4

           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |179| 
||         ZERO    .L2     B5:B4             ; |193| 

;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 5
           CMPLTDP .S2     B21:B20,B5:B4,B0  ; |193| 
           NOP             1
   [ B0]   ZERO    .L1     A29

   [ B0]   MVKH    .S1     0xbff00000,A29
|| [ B0]   ZERO    .L1     A28               ; |194| 
|| [ B1]   B       .S2     $C$L6             ; |146| 

           FMPYDP  .M1     A29:A28,A5:A4,A5:A4 ; |147| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 4
   [!B1]   ADD     .L1     4,A30,A11
           NOP             2

   [!B1]   CALL    .S1     asindp_v          ; |149| 
||         STDW    .D1T1   A5:A4,*A3++       ; |147| 

           ; BRANCHCC OCCURS {$C$L6}         ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A11,B4           ; |149| 
           MV      .L1     A10,A4            ; |149| 
           ADDKPC  .S2     $C$RL10,B3,1      ; |149| 
           MVK     .S1     0xc9,A6           ; |149| 
$C$RL10:   ; CALL OCCURS {asindp_v} {0}      ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0xc9,A4           ; |154| 

$C$RL11:   ; CALL OCCURS {allequal} {0}      ; |154| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |155| 

$C$RL12:   ; CALL OCCURS {print_test_results} {0}  ; |155| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           MVKL    .S1     a_sc,A12
||         MVK     .L2     0xffffffff,B5     ; |169| 

           MVKH    .S1     a_sc,A12
||         MV      .L2     B5,B4             ; |169| 
||         ZERO    .L1     A9

           STDW    .D1T2   B5:B4,*+A12(56)   ; |169| 
||         SET     .S1     A9,0x14,0x1d,A9
||         ZERO    .L2     B17
||         ZERO    .L1     A8                ; |167| 

           STDW    .D1T1   A9:A8,*+A12(32)   ; |166| 
||         MVKH    .S2     0xfff00000,B17
||         ZERO    .L1     A7
||         ZERO    .L2     B7
||         ZERO    .D2     B16               ; |167| 

           STDW    .D1T2   B17:B16,*+A12(24) ; |165| 
||         MVKH    .S2     0x80000000,B7
||         SET     .S1     A7,0x14,0x1e,A7
||         ZERO    .L2     B9
||         ZERO    .L1     A6                ; |167| 

           STDW    .D1T1   A7:A6,*+A12(16)   ; |164| 
||         MVKH    .S2     0xbff00000,B9
||         ZERO    .L2     B8                ; |167| 

           ADD     .L2     -1,B7,B5
||         STDW    .D1T2   B9:B8,*+A12(40)   ; |167| 

           MVK     .L2     0x8,B4
||         STDW    .D1T2   B5:B4,*+A12(48)   ; |168| 
||         ZERO    .S2     B6                ; |167| 

           STDW    .D1T2   B7:B6,*+A12(8)    ; |163| 
||         ZERO    .L1     A5:A4             ; |162| 

           MV      .L1X    B4,A13            ; |163| 
||         STDW    .D1T1   A5:A4,*A12        ; |162| 
||         SUB     .L2X    A12,8,B10
||         ZERO    .S1     A10               ; |167| 

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
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     asin              ; |172| 
||         LDDW    .D2T2   *++B10,B5:B4      ; |172| 

           ADDKPC  .S2     $C$RL13,B3,3      ; |172| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |172| 
$C$RL13:   ; CALL OCCURS {asin} {0}          ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 33
           MVKL    .S1     output,A14
           MVKH    .S1     output,A14
           LDW     .D1T2   *A14,B4           ; |172| 
           NOP             4
           ADD     .L2X    A10,B4,B4         ; |172| 
           STDW    .D2T1   A5:A4,*B4         ; |172| 

           CALLP   .S2     asindp,B3
||         LDDW    .D2T1   *B10,A5:A4        ; |173| 

$C$RL14:   ; CALL OCCURS {asindp} {0}        ; |173| 
           LDW     .D1T2   *+A14(4),B4       ; |173| 
           NOP             4
           ADD     .L2X    A10,B4,B4         ; |173| 
           STDW    .D2T1   A5:A4,*B4         ; |173| 
           LDDW    .D2T2   *B10,B5:B4        ; |174| 
           NOP             4

           CALLP   .S2     asindp_c,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |174| 

$C$RL15:   ; CALL OCCURS {asindp_c} {0}      ; |174| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           LDW     .D1T1   *+A14(8),A3       ; |174| 
           ZERO    .L2     B21
           ZERO    .L1     A9
           ZERO    .L2     B20               ; |163| 
           MVKL    .S2     0x3fe6a09e,B5
           ADD     .L1     A10,A3,A3         ; |174| 
           STDW    .D1T1   A5:A4,*A3         ; |174| 
           LDDW    .D2T1   *B10,A29:A28      ; |175| 
           MVKL    .S2     0x667f3bcd,B4
           MVKH    .S2     0x3fe6a09e,B5
           MVKH    .S2     0x667f3bcd,B4
           SET     .S2     B21,0x14,0x1d,B21
           ABSDP   .S1     A29:A28,A5:A4     ; |166| 
           FMPYDP  .M1     A29:A28,A29:A28,A7:A6 ; |167| 
           SET     .S1     A9,0x15,0x1d,A9
           CMPGTDP .S2X    A5:A4,B5:B4,B0    ; |169| 
           NOP             1

   [ B0]   B       .S1     $C$L14            ; |169| 
|| [!B0]   MV      .L1X    B20,A8            ; |183| 

           CMPGTDP .S1     A5:A4,A9:A8,A0    ; |183| 
           NOP             1

   [ B0]   ZERO    .L1     A0                ; |183| nullify predicate
|| [ B0]   MVKL    .S1     0xe8584caa,A8

   [ A0]   B       .S2     $C$L13            ; |183| 
||         MVKL    .S1     0x3febb67a,A9

   [ B0]   MVKH    .S1     0xe8584caa,A8
           ; BRANCHCC OCCURS {$C$L14}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
   [!A0]   CALL    .S1     pol_est_asindp_i  ; |189| 

   [ A0]   CALL    .S1     pol_est_asindp_i  ; |185| 
|| [ A0]   FADDDP  .L1     A7:A6,A7:A6,A5:A4 ; |185| 

   [ A0]   MV      .L1X    B21,A7            ; |185| 
   [ A0]   MV      .S1     A8,A6             ; |185| 
           ; BRANCHCC OCCURS {$C$L13}        ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL16,B3,1      ; |189| 
$C$RL16:   ; CALL OCCURS {pol_est_asindp_i} {0}  ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L16            ; |189| 
||         ADDAW   .D1     A14,3,A3

           LDW     .D1T1   *A3,A3            ; |175| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |189| 
           ZERO    .L1     A5:A4             ; |193| 
           SUB     .L1     A13,1,A2          ; |171| 
           SUB     .L1     A13,1,A13         ; |171| 
           ; BRANCH OCCURS {$C$L16}          ; |189| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 3
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |185| 
           ADDKPC  .S2     $C$RL17,B3,1      ; |185| 
$C$RL17:   ; CALL OCCURS {pol_est_asindp_i} {0}  ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8

           MVKL    .S2     0x3ff921fb,B5
||         ZERO    .L1     A7
||         MV      .S1X    B20,A6            ; |186| 
||         ADDAW   .D1     A14,3,A3

           MVKL    .S2     0x54442d18,B4
||         SET     .S1     A7,0x15,0x1d,A7
||         LDW     .D1T1   *A3,A3            ; |175| 
||         SUB     .L1     A13,1,A2          ; |171| 

           MVKH    .S2     0x3ff921fb,B5
||         B       .S1     $C$L18            ; |187| 
||         SUB     .L1     A13,1,A13         ; |171| 

           MVKH    .S2     0x54442d18,B4

           FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |186| 
||         ZERO    .L1     A5:A4             ; |193| 

           CMPLTDP .S1     A29:A28,A5:A4,A0  ; |193| 

           ADD     .L1     A10,A3,A3         ; |175| 
||         ADD     .D1     8,A10,A10         ; |171| 

           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |186| 
|| [ A0]   ZERO    .L2     B21
|| [ A0]   ZERO    .S2     B20               ; |194| 

           ; BRANCH OCCURS {$C$L18}          ; |187| 
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 9
           MVKH    .S1     0x3febb67a,A9
           CMPGTDP .S1     A5:A4,A9:A8,A0    ; |170| 
           MV      .L1X    B21,A5

   [!A0]   B       .S1     $C$L15            ; |170| 
||         MV      .L1X    B20,A4

   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |67| 
           NOP             2
           RSQRDP  .S1     A7:A6,A5:A4       ; |67| 
   [!A0]   FADDDP  .L1     A7:A6,A7:A6,A7:A6 ; |179| 
           ; BRANCHCC OCCURS {$C$L15}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 101
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |67| 
           ZERO    .L2     B7
           MV      .L2     B20,B4            ; |67| 
           ZERO    .L2     B5
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |67| 
           SET     .S2     B5,0x15,0x1d,B5
           ZERO    .L1     A31
           MV      .L2     B20,B6            ; |67| 
           SET     .S2     B7,0x13,0x1d,B7
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |67| 
           MV      .L1X    B20,A16           ; |67| 
           ZERO    .L1     A17
           MV      .L2     B20,B8            ; |67| 
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |67| 
           SET     .S1     A17,0x15,0x1d,A17
           MVKL    .S1     0x20991e58,A20
           MVKL    .S1     0x3fc55555,A21
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |67| 
           MVKL    .S2     0x2d6e8923,B18
           MV      .L2X    A17,B9            ; |67| 
           MVKL    .S1     0x3f92080d,A23
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |67| 
           MVKL    .S2     0x3f9f218e,B19
           MVKL    .S1     0x726cfcda,A22
           MVKL    .S2     0x67ff42f2,B22
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |67| 
           MVKH    .S1     0x20991e58,A20
           MVKL    .S2     0x3fb3333c,B23
           MV      .L2     B6,B4             ; |67| 
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |67| 
           MV      .L2     B7,B5             ; |67| 
           MVKH    .S1     0x3fc55555,A21
           MVKL    .S2     0x7e834e0f,B16
           MVKH    .S1     0x3f92080d,A23
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |67| 
           MVKL    .S2     0x3fa6daed,B17
           MVKH    .S1     0x726cfcda,A22
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |67| 
           MVKH    .S2     0x2d6e8923,B18
           MVKL    .S1     0xcead24b0,A26
           MVKH    .S2     0x3f9f218e,B19
           FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |67| 
           MVKL    .S1     0x3f96c6e8,A27
           MVKH    .S2     0x67ff42f2,B22
           MVKH    .S1     0xcead24b0,A26
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |67| 
           MVKH    .S2     0x3fb3333c,B23
           MVKH    .S1     0x3f96c6e8,A27
           MV      .L1     A16,A4            ; |67| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |67| 
           SET     .S1     A31,0x13,0x1d,A5
           MVKH    .S2     0x7e834e0f,B16
           MVKH    .S2     0x3fa6daed,B17
           ADDAW   .D1     A14,3,A3
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |67| 
           MVKL    .S2     0xb088e0d4,B4
           MVKL    .S2     0x3f8a6331,B5
           FMPYDP  .M1X    B7:B6,A5:A4,A9:A8 ; |67| 
           ZERO    .L1     A5:A4             ; |69| 
           CMPGTDP .S1     A7:A6,A5:A4,A0    ; |69| 
           MVKH    .S2     0xb088e0d4,B4
   [!A0]   ZERO    .L1     A9:A8             ; |70| 
           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |174| 
           MVKL    .S2     0x3f8e21a3,B7
           MVKL    .S2     0xc62a3037,B6
           MVKH    .S2     0x3f8e21a3,B7
           FMPYDP  .M1     A7:A6,A7:A6,A5:A4 ; |174| 
           MVKH    .S2     0xc62a3037,B6
           MVKH    .S2     0x3f8a6331,B5
           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |174| 
           FMPYDP  .M1     A5:A4,A7:A6,A17:A16 ; |174| 

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |174| 
||         FMPYDP  .M1     A5:A4,A5:A4,A19:A18 ; |174| 

           LDW     .D1T1   *A3,A3            ; |175| 
           SUB     .L1     A13,1,A2          ; |171| 
           FMPYDP  .M1     A5:A4,A17:A16,A25:A24 ; |174| 

           FADDDP  .L2     B7:B6,B5:B4,B9:B8 ; |174| 
||         FMPYDP  .M2X    B23:B22,A5:A4,B7:B6 ; |174| 
||         FMPYDP  .M1     A5:A4,A19:A18,A5:A4 ; |174| 

           FMPYDP  .M2X    B19:B18,A19:A18,B5:B4 ; |174| 
           FMPYDP  .M2X    B17:B16,A17:A16,B17:B16 ; |174| 
           FMPYDP  .M1     A21:A20,A7:A6,A17:A16 ; |174| 
           FADDDP  .L1X    A23:A22,B9:B8,A7:A6 ; |174| 
           FMPYDP  .M1     A27:A26,A25:A24,A19:A18 ; |174| 
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |174| 
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |174| 
           FADDDP  .L1X    A17:A16,B7:B6,A7:A6 ; |174| 
           SUB     .L1     A13,1,A13         ; |171| 
           ADD     .S1     A10,A3,A3         ; |175| 

           FADDDP  .L1     A19:A18,A5:A4,A7:A6 ; |174| 
||         FADDDP  .S1X    A7:A6,B5:B4,A5:A4 ; |174| 

           ADD     .L1     8,A10,A10         ; |171| 
           MVKL    .S2     0x54442d18,B4
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |174| 
           MVKL    .S2     0x3ff921fb,B5
           MVKH    .S2     0x54442d18,B4
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |174| 
           MVKH    .S2     0x3ff921fb,B5
           NOP             1
           B       .S1     $C$L17            ; |175| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |174| 
           NOP             3

           FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |174| 
||         ZERO    .L1     A5:A4             ; |193| 

           ; BRANCH OCCURS {$C$L17}          ; |175| 
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 48

           MV      .L1X    B21,A5
||         MVKL    .S2     0xb088e0d4,B6
||         MVKL    .S1     0x20991e58,A22

           MV      .D1X    B20,A4            ; |179| 
||         MVKL    .S2     0x3f8a6331,B7
||         MVKL    .S1     0x3fc55555,A23

           FSUBDP  .L1     A7:A6,A5:A4,A9:A8 ; |179| 
||         MVKL    .S2     0x3f8e21a3,B9
||         MVKL    .S1     0x726cfcda,A24

           MVKL    .S2     0xc62a3037,B8
||         MVKL    .S1     0x3f92080d,A25

           MVKH    .S2     0xb088e0d4,B6
||         MVKH    .S1     0x20991e58,A22

           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |179| 
||         MVKH    .S2     0x3f8a6331,B7
||         MVKH    .S1     0x3fc55555,A23

           MVKH    .S2     0x3f8e21a3,B9
||         MVKH    .S1     0x726cfcda,A24

           MVKH    .S2     0xc62a3037,B8
||         MVKH    .S1     0x3f92080d,A25

           MVKL    .S2     0x67ff42f2,B4
||         MVKL    .S1     0xcead24b0,A30

           FMPYDP  .M1     A7:A6,A7:A6,A5:A4 ; |179| 
||         MVKL    .S2     0x3fb3333c,B5
||         MVKL    .S1     0x3f96c6e8,A31

           FMPYDP  .M2X    B9:B8,A7:A6,B9:B8 ; |179| 
||         MVKH    .S2     0x67ff42f2,B4
||         MVKH    .S1     0xcead24b0,A30

           MVKH    .S2     0x3fb3333c,B5
||         MVKH    .S1     0x3f96c6e8,A31

           MVKL    .S2     0x7e834e0f,B18

           FMPYDP  .M1     A5:A4,A7:A6,A17:A16 ; |179| 
||         MVKL    .S2     0x3fa6daed,B19

           FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |179| 
||         FMPYDP  .M1     A5:A4,A5:A4,A19:A18 ; |179| 
||         MVKL    .S2     0x2d6e8923,B16

           MVKL    .S2     0x3f9f218e,B17
||         FMPYDP  .M1X    B5:B4,A5:A4,A21:A20 ; |179| 

           MVKH    .S2     0x7e834e0f,B18

           MVKH    .S2     0x3fa6daed,B19
||         FMPYDP  .M1     A5:A4,A17:A16,A27:A26 ; |179| 

           FADDDP  .L2     B9:B8,B7:B6,B7:B6 ; |179| 
||         MVKH    .S2     0x2d6e8923,B16
||         FMPYDP  .M2X    B19:B18,A17:A16,B9:B8 ; |179| 
||         FMPYDP  .M1     A5:A4,A19:A18,A5:A4 ; |179| 

           MVKH    .S2     0x3f9f218e,B17
           FMPYDP  .M2X    B17:B16,A19:A18,B5:B4 ; |179| 
           FMPYDP  .M1     A23:A22,A7:A6,A17:A16 ; |179| 
           FADDDP  .L1X    A25:A24,B7:B6,A7:A6 ; |179| 
           FMPYDP  .M1     A31:A30,A27:A26,A19:A18 ; |179| 
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |179| 

           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |179| 
||         FADDDP  .L1     A17:A16,A21:A20,A5:A4 ; |179| 

           ZERO    .L1     A3
           SUB     .S1     A13,1,A2          ; |171| 
           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |179| 
           FADDDP  .L1     A19:A18,A7:A6,A7:A6 ; |179| 
           SUB     .S1     A13,1,A13         ; |171| 
           MVKL    .S2     0x54442d18,B4
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |179| 
           MV      .L1X    B20,A6            ; |179| 
           SET     .S1     A3,0x15,0x1d,A7
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |179| 
           ADDAW   .D1     A14,3,A3
           LDW     .D1T1   *A3,A3            ; |175| 
           MVKL    .S2     0x3fe921fb,B5
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |179| 
           MVKH    .S2     0x54442d18,B4
           MVKH    .S2     0x3fe921fb,B5
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |179| 
           NOP             4

           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |179| 
||         ZERO    .L1     A5:A4             ; |193| 

;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1

           ADD     .L1     A10,A3,A3         ; |175| 
||         ADD     .S1     8,A10,A10         ; |171| 

;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 3
           CMPLTDP .S1     A29:A28,A5:A4,A0  ; |193| 
           NOP             1

   [ A0]   ZERO    .L2     B20               ; |194| 
|| [ A0]   ZERO    .S2     B21

;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 8
   [ A0]   MVKH    .S2     0xbff00000,B21
   [!A2]   MV      .L2X    A11,B11           ; |177| 
   [ A2]   B       .S1     $C$L12            ; |171| 
           FMPYDP  .M2     B21:B20,B5:B4,B7:B6 ; |175| 
           NOP             3

   [!A2]   CALL    .S1     asindp_v          ; |177| 
||         STDW    .D1T2   B7:B6,*A3         ; |175| 

           ; BRANCHCC OCCURS {$C$L12}        ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *B11,B4           ; |177| 
           ADDKPC  .S2     $C$RL18,B3,2      ; |177| 

           MVK     .L1     0x8,A6            ; |177| 
||         MV      .S1     A12,A4

$C$RL18:   ; CALL OCCURS {asindp_v} {0}      ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .L1     0x8,A4            ; |180| 

$C$RL19:   ; CALL OCCURS {allequal} {0}      ; |180| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x3,A4            ; |181| 

$C$RL20:   ; CALL OCCURS {print_test_results} {0}  ; |181| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

           MVKL    .S1     a_ext,A12
||         ZERO    .L2     B5

           MVKH    .S1     a_ext,A12
||         SET     .S2     B5,0x14,0x14,B5
||         ZERO    .L2     B4                ; |184| 

           STDW    .D1T2   B5:B4,*A12        ; |184| 
||         MVK     .S2     0x6d6,B4

           MV      .L1     A12,A10           ; |184| 

           ZERO    .L2     B10
||         CALL    .S1     asin              ; |186| 
||         MV      .L1X    B4,A13            ; |184| 

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
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10,A5:A4        ; |186| 
           ADDKPC  .S2     $C$RL21,B3,3      ; |186| 
$C$RL21:   ; CALL OCCURS {asin} {0}          ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 28
           MV      .L1     A14,A3            ; |186| 
           LDW     .D1T1   *A3,A3            ; |186| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |186| 
           STDW    .D1T1   A5:A4,*A3         ; |186| 

           CALLP   .S2     asindp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |187| 

$C$RL22:   ; CALL OCCURS {asindp} {0}        ; |187| 
           MV      .L1     A14,A3            ; |187| 
           LDW     .D1T1   *+A3(4),A3        ; |187| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |187| 
           STDW    .D1T1   A5:A4,*A3         ; |187| 

           CALLP   .S2     asindp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |188| 

$C$RL23:   ; CALL OCCURS {asindp_c} {0}      ; |188| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MV      .L1     A14,A3            ; |188| 
           LDW     .D1T1   *+A3(8),A3        ; |188| 
           ZERO    .L2     B21
           ZERO    .L1     A9
           ZERO    .L2     B20               ; |163| 
           MVKL    .S2     0x3fe6a09e,B5
           ADD     .L2X    B10,A3,B4         ; |188| 
           STDW    .D2T1   A5:A4,*B4         ; |188| 
           LDDW    .D1T1   *A10,A29:A28      ; |189| 
           MVKH    .S2     0x3fe6a09e,B5
           SET     .S2     B21,0x14,0x1d,B21
           MVKL    .S2     0x667f3bcd,B4
           MVKH    .S2     0x667f3bcd,B4
           ABSDP   .S1     A29:A28,A5:A4     ; |166| 
           FMPYDP  .M1     A29:A28,A29:A28,A7:A6 ; |167| 
           SET     .S1     A9,0x15,0x1d,A9
           CMPGTDP .S2X    A5:A4,B5:B4,B0    ; |169| 
           NOP             1

   [ B0]   B       .S1     $C$L21            ; |169| 
|| [!B0]   MV      .L1X    B20,A8            ; |183| 

           CMPGTDP .S1     A5:A4,A9:A8,A0    ; |183| 
           NOP             1

   [ B0]   ZERO    .L1     A0                ; |183| nullify predicate
|| [ B0]   MVKL    .S1     0xe8584caa,A8

   [ A0]   B       .S2     $C$L20            ; |183| 
||         MVKL    .S1     0x3febb67a,A9

   [ B0]   MVKH    .S1     0xe8584caa,A8
           ; BRANCHCC OCCURS {$C$L21}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
   [!A0]   CALL    .S1     pol_est_asindp_i  ; |189| 

   [ A0]   CALL    .S1     pol_est_asindp_i  ; |185| 
|| [ A0]   FADDDP  .L1     A7:A6,A7:A6,A5:A4 ; |185| 

   [ A0]   MV      .L1X    B21,A7            ; |185| 
   [ A0]   MV      .S1     A8,A6             ; |185| 
           ; BRANCHCC OCCURS {$C$L20}        ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL24,B3,1      ; |189| 
$C$RL24:   ; CALL OCCURS {pol_est_asindp_i} {0}  ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L23            ; |189| 
||         ZERO    .L2     B7:B6             ; |193| 
||         MVK     .S2     12,B8
||         SUB     .L1     A13,1,A2          ; |185| 
||         SUB     .D1     A13,1,A13         ; |185| 

           ADD     .L2X    A14,B8,B8

           ZERO    .L1     A5
||         CMPLTDP .S1X    A29:A28,B7:B6,A0  ; |193| 
||         LDW     .D2T2   *B8,B6            ; |189| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |189| 

           ZERO    .L1     A4                ; |190| 
   [ A0]   ZERO    .L2     B21
   [ A0]   MVKH    .S2     0xbff00000,B21
           ; BRANCH OCCURS {$C$L23}          ; |189| 
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 3
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |185| 
           ADDKPC  .S2     $C$RL25,B3,1      ; |185| 
$C$RL25:   ; CALL OCCURS {pol_est_asindp_i} {0}  ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           MVKL    .S2     0x3ff921fb,B5
||         ZERO    .L2     B7:B6             ; |193| 
||         ZERO    .L1     A7
||         MV      .S1X    B20,A6            ; |186| 
||         SUB     .D1     A13,1,A2          ; |185| 

           MVKL    .S2     0x54442d18,B4
||         SET     .S1     A7,0x15,0x1d,A7
||         SUB     .L1     A13,1,A13         ; |185| 

           MVKH    .S2     0x3ff921fb,B5
||         CMPLTDP .S1X    A29:A28,B7:B6,A0  ; |193| 

           MVKH    .S2     0x54442d18,B4

           ZERO    .L1     A5
||         ZERO    .S1     A4                ; |190| 
||         FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |186| 
||         MVK     .S2     12,B8

           ADD     .L2X    A14,B8,B8

           LDW     .D2T2   *B8,B6            ; |189| 
||         B       .S1     $C$L25            ; |187| 

           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |186| 
   [ A0]   ZERO    .L2     B21
           MVKH    .S1     0xbff80000,A5
   [ A0]   MVKH    .S2     0xbff00000,B21

           FMPYDP  .M2     B21:B20,B5:B4,B5:B4 ; |189| 
||         ADD     .L2     B10,B6,B6         ; |189| 
||         ADD     .S2     8,B10,B10         ; |185| 

           ; BRANCH OCCURS {$C$L25}          ; |187| 
;** --------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 9
           MVKH    .S1     0x3febb67a,A9
           CMPGTDP .S1     A5:A4,A9:A8,A0    ; |170| 
           MV      .L1X    B21,A5

   [!A0]   B       .S1     $C$L22            ; |170| 
||         MV      .L1X    B20,A4

   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |67| 
           NOP             2
           RSQRDP  .S1     A7:A6,A5:A4       ; |67| 
   [!A0]   FADDDP  .L1     A7:A6,A7:A6,A7:A6 ; |179| 
           ; BRANCHCC OCCURS {$C$L22}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 101
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |67| 
           MV      .L2     B20,B4            ; |67| 
           ZERO    .L2     B5
           MVKL    .S1     0x20991e58,A20
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |67| 
           ZERO    .L1     A30
           ZERO    .L1     A31
           SET     .S2     B5,0x15,0x1d,B5
           ZERO    .L2     B7
           FMPYDP  .M2X    B5:B4,A9:A8,B5:B4 ; |67| 
           MV      .L2     B20,B6            ; |67| 
           SET     .S2     B7,0x13,0x1d,B7
           SUB     .L1     A13,1,A2          ; |185| 
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |67| 
           MVKL    .S1     0x3fc55555,A21
           ZERO    .S2     B9
           SUB     .L1     A13,1,A13         ; |185| 
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |67| 
           MVKL    .S1     0x726cfcda,A22
           MV      .L2     B20,B8            ; |67| 
           MVKL    .S1     0x3f92080d,A23
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |67| 
           SET     .S2     B9,0x15,0x1d,B9
           MVKH    .S1     0x20991e58,A20
           MVKL    .S2     0x3fa6daed,B17
           FMPYDP  .M1     A5:A4,A9:A8,A17:A16 ; |67| 
           MV      .L1X    B20,A8            ; |67| 
           SET     .S1     A31,0x15,0x1d,A9
           MVKH    .S1     0x3fc55555,A21
           FMPYDP  .M1     A9:A8,A17:A16,A9:A8 ; |67| 
           MVKL    .S2     0x2d6e8923,B18
           MV      .L2     B6,B4             ; |67| 
           MV      .L2     B7,B5             ; |67| 
           MVKH    .S1     0x726cfcda,A22
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |67| 
           MVKL    .S2     0x3f9f218e,B19
           MVKH    .S1     0x3f92080d,A23
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |67| 
           MVKL    .S2     0x7e834e0f,B16
           MVKL    .S1     0xcead24b0,A26
           MVKH    .S2     0x3fa6daed,B17
           FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |67| 
           MVKL    .S1     0x3f96c6e8,A27
           MVKH    .S2     0x2d6e8923,B18
           MVKH    .S1     0xcead24b0,A26
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |67| 
           MVKH    .S2     0x3f9f218e,B19
           MVKH    .S1     0x3f96c6e8,A27
           MVKH    .S2     0x7e834e0f,B16
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |67| 
           ZERO    .L1     A9:A8             ; |69| 
           MV      .L1X    B20,A4            ; |67| 
           SET     .S1     A30,0x13,0x1d,A5
           CMPGTDP .S1     A7:A6,A9:A8,A0    ; |69| 
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |67| 
           MVKL    .S2     0x3fb3333c,B9
           MVKL    .S2     0xb088e0d4,B4
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |67| 
           MVKL    .S2     0x3f8a6331,B5
           MVKH    .S2     0xb088e0d4,B4
           MVKL    .S2     0x3f8e21a3,B7
   [!A0]   ZERO    .L1     A5:A4             ; |70| 
           FMPYDP  .M1     A5:A4,A5:A4,A7:A6 ; |174| 
           MVKL    .S2     0xc62a3037,B6
           MVKH    .S2     0x3f8e21a3,B7
           MVKH    .S2     0xc62a3037,B6
           FMPYDP  .M1     A7:A6,A7:A6,A19:A18 ; |174| 
           MVKH    .S2     0x3f8a6331,B5
           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |174| 
           MVKL    .S2     0x67ff42f2,B8
           FMPYDP  .M1     A19:A18,A19:A18,A17:A16 ; |174| 

           FMPYDP  .M2X    B5:B4,A19:A18,B5:B4 ; |174| 
||         FMPYDP  .M1     A19:A18,A7:A6,A9:A8 ; |174| 

           MVKH    .S2     0x3fb3333c,B9
           MVKH    .S2     0x67ff42f2,B8
           NOP             1

           FADDDP  .L2     B7:B6,B5:B4,B7:B6 ; |174| 
||         FMPYDP  .M2X    B9:B8,A19:A18,B5:B4 ; |174| 
||         FMPYDP  .M1     A19:A18,A9:A8,A25:A24 ; |174| 

           FMPYDP  .M2X    B19:B18,A17:A16,B9:B8 ; |174| 

           FMPYDP  .M2X    B17:B16,A9:A8,B17:B16 ; |174| 
||         FMPYDP  .M1     A19:A18,A17:A16,A9:A8 ; |174| 

           FMPYDP  .M1     A21:A20,A7:A6,A17:A16 ; |174| 
           FADDDP  .L1X    A23:A22,B7:B6,A7:A6 ; |174| 
           FMPYDP  .M1     A27:A26,A25:A24,A19:A18 ; |174| 

           FADDDP  .L2     B17:B16,B9:B8,B7:B6 ; |174| 
||         MVK     .S2     12,B8

           FMPYDP  .M1     A9:A8,A7:A6,A7:A6 ; |174| 
||         FADDDP  .L1X    A17:A16,B5:B4,A9:A8 ; |174| 

           MVKL    .S2     0x54442d18,B4
           ADD     .L2X    A14,B8,B8
           MVKL    .S2     0x3ff921fb,B5

           FADDDP  .L1     A19:A18,A7:A6,A9:A8 ; |174| 
||         FADDDP  .S1X    A9:A8,B7:B6,A7:A6 ; |174| 

           MVKH    .S2     0x54442d18,B4
           ZERO    .L2     B7:B6             ; |193| 
           FADDDP  .L1     A9:A8,A7:A6,A7:A6 ; |174| 
           MVKH    .S2     0x3ff921fb,B5
           CMPLTDP .S1X    A29:A28,B7:B6,A0  ; |193| 
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |174| 
           LDW     .D2T2   *B8,B6            ; |189| 
   [ A0]   ZERO    .L2     B21
           B       .S1     $C$L24            ; |175| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |174| 
   [ A0]   MVKH    .S2     0xbff00000,B21
           ADD     .L2     B10,B6,B6         ; |189| 
           ADD     .L2     8,B10,B10         ; |185| 

           FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |174| 
||         ZERO    .L1     A4                ; |190| 
||         ZERO    .S1     A5

           ; BRANCH OCCURS {$C$L24}          ; |175| 
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 49

           MV      .L1X    B21,A5
||         MVKL    .S2     0xb088e0d4,B4
||         MVKL    .S1     0x20991e58,A16
||         ZERO    .D1     A3

           MV      .D1X    B20,A4            ; |179| 
||         MVKL    .S2     0x3f8a6331,B5
||         MVKL    .S1     0x3fc55555,A17

           FSUBDP  .L1     A7:A6,A5:A4,A9:A8 ; |179| 
||         MVKL    .S2     0x3f8e21a3,B7
||         MVKL    .S1     0x726cfcda,A22

           MVKL    .S2     0xc62a3037,B6
||         MVKL    .S1     0x3f92080d,A23

           MVKH    .S2     0xb088e0d4,B4
||         MVKH    .S1     0x20991e58,A16

           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |179| 
||         MVKH    .S2     0x3f8a6331,B5
||         MVKH    .S1     0x3fc55555,A17

           MVKH    .S2     0x3f8e21a3,B7
||         MVKH    .S1     0x726cfcda,A22

           MVKH    .S2     0xc62a3037,B6
||         MVKH    .S1     0x3f92080d,A23

           MVKL    .S2     0x67ff42f2,B18
||         MVKL    .S1     0xcead24b0,A24

           FMPYDP  .M1     A7:A6,A7:A6,A5:A4 ; |179| 
||         MVKL    .S2     0x3fb3333c,B19
||         MVKL    .S1     0x3f96c6e8,A25

           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |179| 
||         MVKH    .S2     0x67ff42f2,B18
||         MVKH    .S1     0xcead24b0,A24

           MVKH    .S2     0x3fb3333c,B19
           MVKL    .S2     0x7e834e0f,B16

           FMPYDP  .M1     A5:A4,A7:A6,A19:A18 ; |179| 
||         MVKL    .S2     0x3fa6daed,B17

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |179| 
||         FMPYDP  .M1     A5:A4,A5:A4,A21:A20 ; |179| 
||         MVKL    .S2     0x2d6e8923,B8

           MVKL    .S2     0x3f9f218e,B9
||         FMPYDP  .M1X    B19:B18,A5:A4,A27:A26 ; |179| 

           MVKH    .S2     0x7e834e0f,B16
||         FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |179| 

           MVKH    .S2     0x3fa6daed,B17
||         FMPYDP  .M1     A5:A4,A19:A18,A31:A30 ; |179| 

           FADDDP  .L2     B7:B6,B5:B4,B7:B6 ; |179| 
||         MVKH    .S2     0x2d6e8923,B8
||         FMPYDP  .M1     A5:A4,A21:A20,A5:A4 ; |179| 

           MVKH    .S2     0x3f9f218e,B9
           FMPYDP  .M2X    B9:B8,A21:A20,B5:B4 ; |179| 
           FMPYDP  .M2X    B17:B16,A19:A18,B9:B8 ; |179| 
           FADDDP  .L1X    A23:A22,B7:B6,A17:A16 ; |179| 
           MVKH    .S1     0x3f96c6e8,A25
           FMPYDP  .M1     A25:A24,A31:A30,A19:A18 ; |179| 

           FMPYDP  .M1     A5:A4,A17:A16,A17:A16 ; |179| 
||         FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |179| 

           FADDDP  .L1     A7:A6,A27:A26,A5:A4 ; |179| 
           SUB     .S1     A13,1,A2          ; |185| 
           ZERO    .L2     B7:B6             ; |193| 

           FADDDP  .L1X    A5:A4,B5:B4,A7:A6 ; |179| 
||         FADDDP  .S1     A19:A18,A17:A16,A5:A4 ; |179| 

           SUB     .L1     A13,1,A13         ; |185| 
           CMPLTDP .S1X    A29:A28,B7:B6,A0  ; |193| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |179| 
           MVK     .S2     12,B8
   [ A0]   ZERO    .L2     B21
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |179| 
           ADD     .L2X    A14,B8,B8
   [ A0]   MVKH    .S2     0xbff00000,B21
           LDW     .D2T2   *B8,B6            ; |189| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |179| 
           MV      .L1X    B20,A6            ; |179| 
           SET     .S1     A3,0x15,0x1d,A7
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |179| 
           MVKL    .S2     0x54442d18,B4
           MVKL    .S2     0x3fe921fb,B5
           MVKH    .S2     0x54442d18,B4
           MVKH    .S2     0x3fe921fb,B5

           ZERO    .L1     A5
||         FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |179| 

           ZERO    .L1     A4                ; |190| 
;** --------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 2
           NOP             1

           ADD     .L2     B10,B6,B6         ; |189| 
||         ADD     .S2     8,B10,B10         ; |185| 

;** --------------------------------------------------------------------------*
$C$L24:    
;          EXCLUSIVE CPU CYCLES: 3
           MVKH    .S1     0xbff80000,A5
           NOP             1
           FMPYDP  .M2     B21:B20,B5:B4,B5:B4 ; |189| 
;** --------------------------------------------------------------------------*
$C$L25:    
;          EXCLUSIVE CPU CYCLES: 14
           NOP             3
           STDW    .D2T2   B5:B4,*B6         ; |189| 
           LDDW    .D1T1   *A10,A7:A6        ; |190| 
           NOP             3
   [ A2]   B       .S1     $C$L19            ; |185| 
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |190| 
           NOP             3

   [ A2]   CALL    .S1     asin              ; |186| 
||         STDW    .D1T1   A5:A4,*++A10      ; |190| 

           ; BRANCHCC OCCURS {$C$L19}        ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     asindp_v          ; |192| 
           LDW     .D1T2   *A11,B4           ; |192| 
           ADDKPC  .S2     $C$RL26,B3,2      ; |192| 

           MV      .L1     A12,A4
||         MVK     .S1     0x6d6,A6          ; |192| 

$C$RL26:   ; CALL OCCURS {asindp_v} {0}      ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0x6d6,A4          ; |195| 

$C$RL27:   ; CALL OCCURS {allequal} {0}      ; |195| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x4,A4            ; |196| 

$C$RL28:   ; CALL OCCURS {print_test_results} {0}  ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .L1     A10               ; |114| 
||         ZERO    .D1     A11               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*A3       ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     t_start,A3

           MVKH    .S1     t_start,A3
||         MV      .L2     B4,B7             ; |116| 

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B7:B6,*A3         ; |116| 

           MVC     .S2     TSCH,B5           ; |117| 
           SUBU    .L2     B4,B6,B9:B8       ; |117| 

           EXT     .S2     B9,24,24,B6       ; |117| 
||         SUB     .L2     B5,B7,B5          ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B5,B6,B5          ; |117| 
||         MV      .S2     B8,B4             ; |117| 
||         MVKH    .S1     t_offset,A3

           MVKL    .S1     input,A3
||         STDW    .D1T2   B5:B4,*A3         ; |117| 

           CALL    .S2     gimme_random      ; |206| 
||         MVKH    .S1     input,A3

           LDW     .D1T1   *A3,A12           ; |206| 
||         MV      .L2X    A11,B12           ; |117| 
||         MVK     .S1     0x80,A13
||         ZERO    .L1     A5

           MV      .L2X    A11,B4            ; |206| 
||         ZERO    .S2     B5
||         SET     .S1     A5,0x1e,0x1e,A5
||         MV      .L1     A10,A4            ; |206| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L26:    
;          EXCLUSIVE CPU CYCLES: 3
           MVKH    .S2     0xbff00000,B5
           ADDKPC  .S2     $C$RL29,B3,1      ; |206| 
$C$RL29:   ; CALL OCCURS {gimme_random} {0}  ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           ADD     .L1X    A12,B12,A3        ; |206| 

           STDW    .D1T1   A5:A4,*A3         ; |206| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A28            ; |122| Define a twin register
||         MVC     .S2     TSCH,B6           ; |122| 

           ADD     .L2X    A12,B12,B4        ; |169| 
||         MVKL    .S2     0x667f3bcd,B8
||         ZERO    .L1     A31
||         MV      .S1     A10,A30           ; |167| 

           LDDW    .D2T2   *B4,B5:B4         ; |169| 
||         MVKL    .S2     0x3fe6a09e,B9

           SET     .S1     A31,0x14,0x1d,A31
           MV      .L1X    B6,A29            ; |122| 
           MVKH    .S2     0x667f3bcd,B8
           MVKH    .S2     0x3fe6a09e,B9
           ABSDP   .S2     B5:B4,B5:B4       ; |169| 
           DADD    .L2X    0,A5:A4,B21:B20   ; |210| 
           CMPGTDP .S2     B5:B4,B9:B8,B0    ; |169| 
           FMPYDP  .M2     B21:B20,B21:B20,B7:B6 ; |167| 

   [ B0]   BNOP    .S1     $C$L28,1          ; |169| 
||         ABSDP   .S2     B21:B20,B9:B8     ; |166| 

   [!B0]   ZERO    .L2     B9
|| [!B0]   MV      .S2X    A10,B8            ; |183| 

   [!B0]   SET     .S2     B9,0x15,0x1d,B9
           CMPGTDP .S2     B5:B4,B9:B8,B0    ; |183| 
           MV      .L2X    A12,B10           ; |169| 
           ; BRANCHCC OCCURS {$C$L28}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

   [ B0]   B       .S1     $C$L27            ; |183| 
|| [ B0]   FADDDP  .L2     B7:B6,B7:B6,B5:B4 ; |185| 

   [!B0]   CALL    .S1     pol_est_asindp_i  ; |189| 

   [ B0]   MV      .S2     B8,B6             ; |185| 
|| [ B0]   CALL    .S1     pol_est_asindp_i  ; |185| 

   [ B0]   MV      .L2X    A31,B7            ; |185| 
   [ B0]   FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |185| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L27}        ; |183| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           DADD    .L1X    0,B5:B4,A5:A4     ; |189| 
||         ADDKPC  .S2     $C$RL30,B3,0      ; |189| 

$C$RL30:   ; CALL OCCURS {pol_est_asindp_i} {0}  ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           ZERO    .L2     B5:B4             ; |193| 
||         MVKL    .S2     output+12,B6
||         B       .S1     $C$L31            ; |189| 

           CMPLTDP .S2     B21:B20,B5:B4,B0  ; |193| 
||         MVKL    .S1     t_start,A3

           MVKH    .S1     t_start,A3

           MVKH    .S2     output+12,B6
|| [ B0]   ZERO    .L1     A31
|| [ B0]   ZERO    .S1     A30               ; |194| 
||         STDW    .D1T1   A29:A28,*A3

           LDW     .D2T2   *B6,B4            ; |210| 
|| [ B0]   MVKH    .S1     0xbff00000,A31

           FMPYDP  .M1     A31:A30,A5:A4,A5:A4 ; |210| 
           ; BRANCH OCCURS {$C$L31}          ; |189| 
;** --------------------------------------------------------------------------*
$C$L27:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL31,B3,0      ; |185| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |185| 
$C$RL31:   ; CALL OCCURS {pol_est_asindp_i} {0}  ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8

           MVKL    .S1     0x3ff921fb,A7
||         ZERO    .L2     B5
||         MV      .D2X    A10,B4            ; |186| 
||         MVKL    .S2     output+12,B6

           MVKL    .S1     0x54442d18,A6
||         SET     .S2     B5,0x15,0x1d,B5

           MVKH    .S1     0x3ff921fb,A7
||         B       .S2     $C$L30            ; |187| 

           MVKH    .S1     0x54442d18,A6
||         MVKH    .S2     output+12,B6

           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |186| 
||         MVKL    .S1     t_start,A3

           MVKH    .S1     t_start,A3
           STDW    .D1T1   A29:A28,*A3

           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |186| 
||         ZERO    .L2     B5:B4             ; |193| 

           ; BRANCH OCCURS {$C$L30}          ; |187| 
;** --------------------------------------------------------------------------*
$C$L28:    
;          EXCLUSIVE CPU CYCLES: 12
           MVKL    .S2     0x3febb67a,B5
           MVKL    .S2     0xe8584caa,B4
           MVKH    .S2     0x3febb67a,B5
           MVKH    .S2     0xe8584caa,B4
           CMPGTDP .S2     B9:B8,B5:B4,B0    ; |170| 
           MV      .L2X    A31,B5

   [!B0]   B       .S1     $C$L29            ; |170| 
||         MV      .L2X    A10,B4

           FSUBDP  .L2     B5:B4,B7:B6,B5:B4 ; |67| 
|| [!B0]   MV      .S2X    A10,B8            ; |179| 

   [!B0]   FADDDP  .L2     B7:B6,B7:B6,B5:B4 ; |179| 
   [!B0]   MV      .S2X    A31,B9
   [ B0]   RSQRDP  .S2     B5:B4,B7:B6       ; |67| 
   [!B0]   FSUBDP  .L2     B5:B4,B9:B8,B9:B8 ; |179| 
           ; BRANCHCC OCCURS {$C$L29}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 101
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |67| 
           ZERO    .L1     A7
           MV      .L1     A30,A4            ; |67| 
           ZERO    .L1     A5
           FMPYDP  .M2     B7:B6,B9:B8,B9:B8 ; |67| 
           MVKL    .S2     0x20991e58,B26
           SET     .S1     A5,0x15,0x1d,A5
           MV      .L2X    A10,B16           ; |67| 
           MV      .L1     A30,A6            ; |67| 
           FMPYDP  .M1X    A5:A4,B9:B8,A5:A4 ; |67| 
           SET     .S1     A7,0x13,0x1d,A7
           ZERO    .L2     B31
           MVKL    .S2     0x3fc55555,B27
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |67| 
           ZERO    .L1     A9
           MVKL    .S2     0x726cfcda,B28
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |67| 
           ZERO    .L1     A27
           MV      .L1     A30,A8            ; |67| 
           MVKL    .S2     0x3f92080d,B29
           SET     .S1     A9,0x13,0x1d,A9
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |67| 
           MVKH    .S2     0x20991e58,B26
           MVKL    .S1     0x3f8a6331,A17
           MVKH    .S2     0x3fc55555,B27
           MVKL    .S1     0xb088e0d4,A16
           FMPYDP  .M1X    A5:A4,B7:B6,A7:A6 ; |67| 
           MV      .L2X    A10,B6            ; |67| 
           SET     .S2     B31,0x15,0x1d,B7
           MV      .L2X    A9,B17            ; |67| 
           FMPYDP  .M1X    B7:B6,A7:A6,A7:A6 ; |67| 
           MVKH    .S2     0x726cfcda,B28
           MVKH    .S1     0x3f8a6331,A17
           MVKH    .S2     0x3f92080d,B29
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |67| 
           MVKH    .S1     0xb088e0d4,A16
           MVKL    .S2     0xcead24b0,B24
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |67| 
           MVKL    .S2     0x3f96c6e8,B25
           MVKH    .S2     0xcead24b0,B24
           MVKH    .S2     0x3f96c6e8,B25
           MVKL    .S1     0x3fb3333c,A9
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |67| 
           MVKH    .S1     0x3fb3333c,A9
           MVKL    .S1     0x3f8e21a3,A7
           MVKL    .S1     0xc62a3037,A6
           FMPYDP  .M2X    A5:A4,B7:B6,B9:B8 ; |67| 
           SET     .S1     A27,0x15,0x1d,A5
           MV      .L1     A8,A4             ; |67| 
           MVKH    .S1     0x3f8e21a3,A7
           FMPYDP  .M2X    A5:A4,B9:B8,B9:B8 ; |67| 
           MVKH    .S1     0xc62a3037,A6
           MVKL    .S1     0x67ff42f2,A8
           ZERO    .L1     A5:A4             ; |69| 
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |67| 
           MVKH    .S1     0x67ff42f2,A8
           CMPGTDP .S2X    B5:B4,A5:A4,B0    ; |69| 
           FMPYDP  .M2     B7:B6,B9:B8,B7:B6 ; |67| 
           MVKL    .S1     0x2d6e8923,A4
           MVKL    .S1     0x3f9f218e,A5
           MVKH    .S1     0x2d6e8923,A4
   [!B0]   ZERO    .L2     B7:B6             ; |70| 
           FMPYDP  .M2     B7:B6,B7:B6,B17:B16 ; |174| 
           MVKH    .S1     0x3f9f218e,A5
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3
           FMPYDP  .M2     B17:B16,B17:B16,B9:B8 ; |174| 

           FMPYDP  .M1X    A7:A6,B17:B16,A19:A18 ; |174| 
||         MVKL    .S1     0x3fa6daed,A7

           MVKL    .S1     0x7e834e0f,A6
           MVKH    .S1     0x3fa6daed,A7

           FMPYDP  .M2     B9:B8,B17:B16,B5:B4 ; |174| 
||         MVKH    .S1     0x7e834e0f,A6

           FMPYDP  .M1X    A17:A16,B9:B8,A17:A16 ; |174| 
           FMPYDP  .M2     B9:B8,B9:B8,B19:B18 ; |174| 
           FMPYDP  .M1X    A9:A8,B9:B8,A9:A8 ; |174| 
           FMPYDP  .M2     B9:B8,B5:B4,B23:B22 ; |174| 

           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |174| 
||         FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |174| 

           FMPYDP  .M2     B9:B8,B19:B18,B5:B4 ; |174| 
           FMPYDP  .M1X    A5:A4,B19:B18,A5:A4 ; |174| 
           FMPYDP  .M2     B27:B26,B17:B16,B9:B8 ; |174| 
           FADDDP  .L2X    B29:B28,A17:A16,B17:B16 ; |174| 
           FMPYDP  .M2     B25:B24,B23:B22,B19:B18 ; |174| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |174| 

           FMPYDP  .M2     B5:B4,B17:B16,B17:B16 ; |174| 
||         FADDDP  .L2X    B9:B8,A9:A8,B5:B4 ; |174| 

           STDW    .D1T1   A29:A28,*A3
           NOP             1
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |174| 
           FADDDP  .L2     B19:B18,B17:B16,B9:B8 ; |174| 
           MVKL    .S1     0x54442d18,A4
           MVKL    .S1     0x3ff921fb,A5
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |174| 
           MVKH    .S1     0x54442d18,A4
           MVKH    .S1     0x3ff921fb,A5
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |174| 
           NOP             2
           B       .S1     $C$L30            ; |175| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |174| 
           MVKL    .S2     output+12,B6
           MVKH    .S2     output+12,B6
           NOP             1

           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |174| 
||         ZERO    .L2     B5:B4             ; |193| 

           ; BRANCH OCCURS {$C$L30}          ; |175| 
;** --------------------------------------------------------------------------*
$C$L29:    
;          EXCLUSIVE CPU CYCLES: 48

           MVKL    .S1     0x3f8a6331,A9
||         MVKL    .S2     0x20991e58,B26

           MVKL    .S1     0xb088e0d4,A8
||         MVKL    .S2     0x3fc55555,B27

           FMPYDP  .M2     B9:B8,B9:B8,B7:B6 ; |179| 
||         MVKL    .S1     0xc62a3037,A4
||         MVKL    .S2     0x726cfcda,B30

           MVKL    .S1     0x3f8e21a3,A5
||         MVKL    .S2     0x3f92080d,B31

           MVKH    .S1     0x3f8a6331,A9
||         MVKH    .S2     0x20991e58,B26

           MVKH    .S1     0xb088e0d4,A8
||         MVKH    .S2     0x3fc55555,B27

           FMPYDP  .M2     B7:B6,B7:B6,B5:B4 ; |179| 
||         MVKH    .S1     0xc62a3037,A4
||         MVKH    .S2     0x726cfcda,B30

           MVKH    .S1     0x3f8e21a3,A5
||         MVKH    .S2     0x3f92080d,B31

           FMPYDP  .M1X    A5:A4,B7:B6,A19:A18 ; |179| 
||         MVKL    .S1     0x2d6e8923,A4
||         MVKL    .S2     0xcead24b0,B28

           MVKL    .S1     0x3f9f218e,A5
||         MVKL    .S2     0x3f96c6e8,B29

           FMPYDP  .M2     B5:B4,B7:B6,B17:B16 ; |179| 
||         MVKL    .S1     0x7e834e0f,A6
||         MVKH    .S2     0xcead24b0,B28

           FMPYDP  .M1X    A9:A8,B5:B4,A9:A8 ; |179| 
||         FMPYDP  .M2     B5:B4,B5:B4,B19:B18 ; |179| 
||         MVKL    .S1     0x3fa6daed,A7
||         MVKH    .S2     0x3f96c6e8,B29

           MVKL    .S1     0x67ff42f2,A16
           MVKL    .S1     0x3fb3333c,A17

           MVKH    .S1     0x2d6e8923,A4
||         FMPYDP  .M2     B5:B4,B17:B16,B25:B24 ; |179| 

           FADDDP  .L1     A19:A18,A9:A8,A9:A8 ; |179| 
||         MVKH    .S1     0x3f9f218e,A5

           MVKH    .S1     0x7e834e0f,A6
||         FMPYDP  .M1X    A5:A4,B19:B18,A5:A4 ; |179| 

           MVKH    .S1     0x3fa6daed,A7

           MVKH    .S1     0x67ff42f2,A16
||         FMPYDP  .M1X    A7:A6,B17:B16,A7:A6 ; |179| 

           MVKH    .S1     0x3fb3333c,A17
           FMPYDP  .M2     B5:B4,B19:B18,B17:B16 ; |179| 
           FMPYDP  .M2X    A17:A16,B5:B4,B23:B22 ; |179| 

           FMPYDP  .M2     B27:B26,B7:B6,B5:B4 ; |179| 
||         FADDDP  .L2X    B31:B30,A9:A8,B7:B6 ; |179| 

           FMPYDP  .M2     B29:B28,B25:B24,B19:B18 ; |179| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |179| 
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |179| 
           FADDDP  .L2     B5:B4,B23:B22,B5:B4 ; |179| 
           ZERO    .L2     B2
           MVKL    .S1     t_start,A3

           FADDDP  .L2     B19:B18,B7:B6,B7:B6 ; |179| 
||         FADDDP  .S2X    B5:B4,A5:A4,B5:B4 ; |179| 

           MVKH    .S1     t_start,A3
           STDW    .D1T1   A29:A28,*A3
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |179| 
           MVKL    .S1     0x54442d18,A4
           MVKL    .S1     0x3fe921fb,A5
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |179| 
           MV      .L2X    A10,B6            ; |179| 
           SET     .S2     B2,0x15,0x1d,B7
           MVKH    .S1     0x54442d18,A4
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |179| 
           MVKH    .S1     0x3fe921fb,A5
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |179| 
           MVKL    .S2     output+12,B6
           MVKH    .S2     output+12,B6
           NOP             2

           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |179| 
||         ZERO    .L2     B5:B4             ; |193| 

;** --------------------------------------------------------------------------*
$C$L30:    
;          EXCLUSIVE CPU CYCLES: 5
           CMPLTDP .S2     B21:B20,B5:B4,B0  ; |193| 
           LDW     .D2T2   *B6,B4            ; |210| 
   [ B0]   ZERO    .L1     A31

   [ B0]   MVKH    .S1     0xbff00000,A31
|| [ B0]   ZERO    .L1     A30               ; |194| 

           FMPYDP  .M1     A31:A30,A5:A4,A5:A4 ; |210| 
;** --------------------------------------------------------------------------*
$C$L31:    
;          EXCLUSIVE CPU CYCLES: 21
           NOP             3
           ADD     .L2     B12,B4,B4         ; |210| 

           STDW    .D2T1   A5:A4,*B4         ; |210| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A15
||         MVKL    .S2     cycle_counts+24,B5
||         SUB     .L1     A13,1,A0          ; |204| 
||         MV      .L2     B4,B17            ; |128| 
||         ADD     .D2     8,B12,B12         ; |204| 
||         SUB     .D1     A13,1,A13         ; |204| 

           MVKH    .S1     t_offset,A15
||         MVKH    .S2     cycle_counts+24,B5

           MVKL    .S2     t_stop,B8
||         LDDW    .D1T1   *A15,A7:A6        ; |130| 

           LDDW    .D2T2   *B5,B7:B6         ; |130| 
           MVKH    .S2     t_stop,B8
           MV      .L1X    B5,A14            ; |128| 
           STDW    .D2T2   B17:B16,*B8       ; |128| 
           ADDU    .L1     A6,A28,A5:A4      ; |130| 

           ADD     .L1     A5,A7,A3          ; |130| 
|| [ A0]   ZERO    .S1     A5

           ADD     .L1     A3,A29,A3         ; |130| 
|| [ A0]   B       .S2     $C$L26            ; |204| 
||         SUBU    .L2X    B16,A4,B5:B4      ; |130| 
|| [ A0]   SET     .S1     A5,0x1e,0x1e,A5
|| [ A0]   MV      .D1     A10,A4            ; |206| 

           EXT     .S2     B5,24,24,B9       ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 

           SUB     .L2X    B17,A3,B6         ; |130| 
|| [ A0]   MVKL    .S1     input,A3
||         ADD     .S2     B5,B7,B5          ; |130| 

   [ A0]   CALL    .S2     gimme_random      ; |206| 
|| [ A0]   MVKH    .S1     input,A3
||         ADD     .L2     B6,B9,B6          ; |130| 

   [ A0]   LDW     .D1T1   *A3,A12           ; |206| 
||         ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T2   B5:B4,*A14        ; |130| 
|| [ A0]   ZERO    .L2     B5
|| [ A0]   MV      .S2X    A11,B4            ; |206| 

           ; BRANCHCC OCCURS {$C$L26}        ; |204| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |135| 
$C$RL32:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

$C$RL33:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           MV      .L2X    A14,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           SUBAW   .D2     B4,6,B5
||         MV      .L2X    A10,B31           ; |114| 

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T1   A11:A10,*B5       ; |114| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     output,A3

           MVKH    .S1     output,A3
||         SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MV      .S2X    A3,B9             ; |117| 
||         MVK     .S1     0x80,A31

           MV      .L1     A31,A15           ; |117| 
||         STDW    .D1T2   B7:B6,*A15        ; |117| 
||         LDW     .D2T1   *B9,A14
||         MV      .S1X    B10,A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L32:    
;          EXCLUSIVE CPU CYCLES: 8
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           CALL    .S1     asin              ; |219| 
           LDDW    .D1T1   *A12++,A5:A4      ; |219| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           ADDKPC  .S2     $C$RL34,B3,0      ; |219| 
$C$RL34:   ; CALL OCCURS {asin} {0}          ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20

           STDW    .D1T1   A5:A4,*A14++      ; |219| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_start,A3
||         MVKL    .S2     t_offset,B10
||         MV      .L2     B4,B9             ; |128| 
||         SUB     .L1     A15,1,A0          ; |217| 
||         SUB     .D1     A15,1,A15         ; |217| 

           MVKH    .S1     t_start,A3
||         MVKH    .S2     t_offset,B10

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 
||         MVKL    .S1     cycle_counts,A31

           MVKH    .S1     cycle_counts,A31
           MVKL    .S1     t_stop,A30
           MVKH    .S1     t_stop,A30
           STDW    .D1T2   B9:B8,*A30        ; |128| 

           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
||         MVKL    .S2     cycle_counts,B6

           ADD     .L1X    A5,B7,A6          ; |130| 
||         MVKH    .S2     cycle_counts,B6

           SUBU    .L2X    B8,A4,B5:B4       ; |130| 
||         LDDW    .D1T1   *A31,A5:A4        ; |130| 
||         ADD     .L1     A6,A7,A6          ; |130| 

           EXT     .S2     B5,24,24,B5       ; |130| 
|| [!A0]   MV      .L1X    B6,A14

           SUB     .L2X    B9,A6,B31         ; |130| 

   [ A0]   BNOP    .S1     $C$L32,1          ; |217| 
||         ADD     .L2     B31,B5,B5         ; |130| 

           ADDU    .L2X    A4,B4,B17:B16     ; |130| 
           ADD     .L2X    B17,A5,B4         ; |130| 
           ADD     .L2     B4,B5,B17         ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B17:B16,*B6       ; |130| 

           ; BRANCHCC OCCURS {$C$L32}        ; |217| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |135| 
$C$RL35:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

$C$RL36:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A11:A10,*+A14(16) ; |114| 
||         MV      .L2X    A10,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A14        ; |135| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B5,B6,B5          ; |117| 

           MV      .L2X    A3,B10            ; |117| 
||         STDW    .D2T2   B5:B4,*B10        ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L33:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |228| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |228| 
||         CALL    .S1     asindp_c          ; |228| 

           LDDW    .D1T1   *A3,A5:A4         ; |228| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |228| 
$C$RL37:   ; CALL OCCURS {asindp_c} {0}      ; |228| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+8,B4
           MVKH    .S2     output+8,B4
           LDW     .D2T2   *B4,B4            ; |228| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |228| 

           STDW    .D1T1   A5:A4,*A3         ; |228| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A15
||         MVKL    .S2     t_start,B5
||         ADDAD   .D1     A14,2,A3
||         SUB     .L1X    B10,1,A0          ; |226| 
||         MV      .L2     B4,B17            ; |128| 
||         SUB     .D2     B10,1,B10         ; |226| 

           MVKH    .S1     t_offset,A15
||         MVKH    .S2     t_start,B5
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
|| [!A0]   MV      .L1     A14,A3

           MVKL    .S1     t_stop,A31
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B5,B9:B8         ; |130| 

           MVK     .S2     16,B12
           MVKH    .S1     t_stop,A31
           ADD     .L2X    A14,B12,B12
           STDW    .D1T2   B17:B16,*A31      ; |128| 
           ADDU    .L2X    A4,B8,B7:B6       ; |130| 

   [ A0]   B       .S1     $C$L33            ; |226| 
||         SUBU    .L2     B16,B6,B5:B4      ; |130| 
||         ADD     .S2X    B7,A5,B6          ; |130| 

           ADD     .D2     B6,B9,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B6         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B12        ; |130| 
||         ADD     .L1     8,A12,A12         ; |226| 

           ; BRANCHCC OCCURS {$C$L33}        ; |226| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(16),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL38,B3,3      ; |135| 
$C$RL38:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

$C$RL39:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           MV      .L1     A14,A3            ; |135| 
||         STDW    .D2T1   A5:A4,*B12        ; |135| 
||         MV      .L2X    A10,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*+A3(8)   ; |114| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B4,B4          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B4,B5,B7          ; |117| 

           STDW    .D1T2   B7:B6,*A15        ; |117| 
||         MV      .L2X    A3,B13            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L34:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |237| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |237| 
||         CALL    .S1     asindp            ; |237| 

           LDDW    .D1T1   *A3,A5:A4         ; |237| 
           ADDKPC  .S2     $C$RL40,B3,3      ; |237| 
$C$RL40:   ; CALL OCCURS {asindp} {0}        ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+4,B4
           MVKH    .S2     output+4,B4
           LDW     .D2T2   *B4,B4            ; |237| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |237| 

           STDW    .D1T1   A5:A4,*A3         ; |237| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S2     t_start,B12
||         MVKL    .S1     t_offset,A14
||         SUB     .L1X    B13,1,A0          ; |235| 
||         ADD     .D1     8,A12,A12         ; |235| 
||         SUB     .L2     B13,1,B13         ; |235| 

           MVKH    .S2     t_start,B12
||         MVKH    .S1     t_offset,A14

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 
||         MVKL    .S1     cycle_counts+8,A3

           MVKH    .S1     cycle_counts+8,A3

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     t_stop,A15

           MV      .L2X    A3,B10            ; |128| 
||         MVKH    .S1     t_stop,A15

   [!A0]   MVKL    .S1     cycle_counts,A3
||         STDW    .D1T2   B9:B8,*A15        ; |128| 

           ADDU    .L2X    A4,B6,B5:B4       ; |130| 
|| [!A0]   MVKH    .S1     cycle_counts,A3

           ADD     .S2X    B5,A5,B6          ; |130| 
|| [ A0]   B       .S1     $C$L34            ; |235| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .S2     B9,B6,B4          ; |130| 
||         ADDU    .L2X    A6,B4,B7:B6       ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2X    B7,A7,B4          ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B7:B6,*B10        ; |130| 

           ; BRANCHCC OCCURS {$C$L34}        ; |235| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(8),A5:A4     ; |135| 
           ADDKPC  .S2     $C$RL41,B3,3      ; |135| 
$C$RL41:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 110
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A11,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
           MV      .L1X    B10,A12           ; |135| 
           SUBAW   .D1     A12,2,A3

           MV      .L2X    A10,B4            ; |114| 
||         STDW    .D1T1   A5:A4,*A12        ; |135| 

           STDW    .D1T1   A11:A10,*+A3(32)  ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D2T2   B9:B8,*B12        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B5           ; |117| 

           MVKL    .S1     input,A3
||         SUBU    .L2     B4,B8,B7:B6       ; |117| 

           MVKH    .S1     input,A3
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B5,B9,B5          ; |117| 

           LDW     .D1T1   *A3,A4            ; |244| 
||         LDW     .D2T2   *B11,B4           ; |244| 
||         ADD     .L2     B5,B7,B7          ; |117| 

           CALLP   .S2     asindp_v,B3
||         STDW    .D1T2   B7:B6,*A14        ; |117| 
||         MVK     .S1     0x80,A6           ; |244| 

$C$RL43:   ; CALL OCCURS {asindp_v} {0}      ; |244| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B6           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B12,B5:B4        ; |130| 

           MVK     .S2     24,B10
           ADD     .L2X    A12,B10,B10
           MV      .L2     B6,B9             ; |128| 
           LDDW    .D2T2   *B10,B7:B6        ; |130| 
           ADDU    .L1X    A6,B4,A5:A4       ; |130| 
           ADD     .L1     A5,A7,A3          ; |130| 
           SUBU    .L1X    B8,A4,A5:A4       ; |130| 

           ADD     .L2X    A3,B5,B4          ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
||         SUB     .L2     B9,B4,B4          ; |130| 

           ADD     .L2X    B4,A3,B5          ; |130| 
           ADD     .L2X    A7,B7,B4          ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MV      .S2X    A6,B6             ; |130| 

           STDW    .D1T2   B9:B8,*A15        ; |128| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 

$C$RL44:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1     A11,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL45:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 

           CALLP   .S2     allequal,B3
||         STDW    .D2T1   A5:A4,*B10        ; |130| 
||         MVK     .S1     0x80,A4           ; |249| 

$C$RL46:   ; CALL OCCURS {allequal} {0}      ; |249| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x2,A4            ; |250| 

$C$RL47:   ; CALL OCCURS {print_test_results} {0}  ; |250| 
           MVKL    .S1     $C$SL2+0,A3
           MVKH    .S1     $C$SL2+0,A3

           CALLP   .S2     printf,B3
||         STW     .D2T1   A3,*+SP(4)        ; |251| 

$C$RL48:   ; CALL OCCURS {printf} {0}        ; |251| 
           MVKL    .S1     $C$SL3+0,A3
           MVKH    .S1     $C$SL3+0,A3

           CALLP   .S2     printf,B3
||         STW     .D2T1   A3,*+SP(4)        ; |251| 

$C$RL49:   ; CALL OCCURS {printf} {0}        ; |251| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |258| 

$C$RL50:   ; CALL OCCURS {print_profile_results} {0}  ; |258| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |261| 

$C$RL51:   ; CALL OCCURS {print_memory_results} {0}  ; |261| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(16),B3      ; |262| 
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
$C$SL1:	.string	"asinDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	asin
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	asindp_c
	.global	asindp
	.global	asindp_v
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
