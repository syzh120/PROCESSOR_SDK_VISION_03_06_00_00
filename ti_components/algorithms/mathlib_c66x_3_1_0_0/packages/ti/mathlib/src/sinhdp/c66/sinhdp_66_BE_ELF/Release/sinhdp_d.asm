;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 23:00:26 2013                                *
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
	.word	0bcafffffh,0f4178da3h		; a[0] @ 0
	.word	03cb3c733h,091833afah		; a[1] @ 64
	.word	0bcb872cah,04ea8c7feh		; a[2] @ 128
	.word	03cbe38b2h,081032491h		; a[3] @ 192
	.word	0bcc2adcbh,028cba780h		; a[4] @ 256
	.word	03cc716eeh,0fd5ad3a1h		; a[5] @ 320
	.word	0bccc8ab3h,0325f3490h		; a[6] @ 384
	.word	03cd1a406h,0d847e7ddh		; a[7] @ 448
	.word	0bcd5ce68h,0b64f2a37h		; a[8] @ 512
	.word	03cdaf499h,07aaf3da9h		; a[9] @ 576
	.word	0bce0a907h,0baab8567h		; a[10] @ 640
	.word	03ce49825h,0759a19ddh		; a[11] @ 704
	.word	0bce97512h,0c1f80b97h		; a[12] @ 768
	.word	03cef77f8h,0475020f3h		; a[13] @ 832
	.word	0bcf37320h,024bf278fh		; a[14] @ 896
	.word	03cf80adch,06f7ae299h		; a[15] @ 960
	.word	0bcfdb83ah,01d254e41h		; a[16] @ 1024
	.word	03d025e63h,0f07ed8f5h		; a[17] @ 1088
	.word	0bd06b4c8h,047f721c4h		; a[18] @ 1152
	.word	03d0c115eh,0b7778b76h		; a[19] @ 1216
	.word	0bd115909h,04db44ac8h		; a[20] @ 1280
	.word	03d1571b6h,0ac4967f6h		; a[21] @ 1344
	.word	0bd1a8203h,0e8d71bfeh		; a[22] @ 1408
	.word	03d206235h,0751b448dh		; a[23] @ 1472
	.word	0bd244099h,09fe36970h		; a[24] @ 1536
	.word	03d2908dbh,01189a1b3h		; a[25] @ 1600
	.word	0bd2ef232h,0a2d50c04h		; a[26] @ 1664
	.word	03d332072h,00471105fh		; a[27] @ 1728
	.word	0bd37a4a8h,062a5146fh		; a[28] @ 1792
	.word	03d3d39e4h,02ce2cee2h		; a[29] @ 1856
	.word	0bd42104eh,09164a44bh		; a[30] @ 1920
	.word	03d465441h,0c2b8357ch		; a[31] @ 1984
	.word	0bd4b9a0dh,0dc2664e2h		; a[32] @ 2048
	.word	03d510f4ah,0b89f3d85h		; a[33] @ 2112
	.word	0bd55168eh,010e5872ch		; a[34] @ 2176
	.word	03d5a1154h,0cc85c453h		; a[35] @ 2240
	.word	0bd601c8fh,0f10193d4h		; a[36] @ 2304
	.word	03d63ea82h,00de439b7h		; a[37] @ 2368
	.word	0bd689e6fh,041b3e6a7h		; a[38] @ 2432
	.word	03d6e6ea5h,0b4e8fbe0h		; a[39] @ 2496
	.word	0bd72cf22h,0d985278ah		; a[40] @ 2560
	.word	03d774026h,0a2d84effh		; a[41] @ 2624
	.word	0bd7cbda6h,0fdaf58cah		; a[42] @ 2688
	.word	03d81c384h,0cb8cf82dh		; a[43] @ 2752
	.word	0bd85f556h,035e563c2h		; a[44] @ 2816
	.word	03d8b24b8h,090bf2b8bh		; a[45] @ 2880
	.word	0bd90c6c5h,0aff6ceb2h		; a[46] @ 2944
	.word	03d94bce8h,0e00e9907h		; a[47] @ 3008
	.word	0bd99a284h,0a57fc089h		; a[48] @ 3072
	.word	03d9fb025h,05f2cadcdh		; a[49] @ 3136
	.word	0bda395d8h,07c12ab0bh		; a[50] @ 3200
	.word	03da835c7h,0d6f45158h		; a[51] @ 3264
	.word	0bdaded48h,0181759a5h		; a[52] @ 3328
	.word	03db27f2eh,02b6607cfh		; a[53] @ 3392
	.word	0bdb6dd50h,07a063f28h		; a[54] @ 3456
	.word	03dbc4379h,0870f0f39h		; a[55] @ 3520
	.word	0bdc17801h,066640b6ch		; a[56] @ 3584
	.word	03dc597feh,078a05728h		; a[57] @ 3648
	.word	0bdcab155h,0ec807b19h		; a[58] @ 3712
	.word	03dd07f74h,0be348237h		; a[59] @ 3776
	.word	0bdd464c0h,0e7b78b8dh		; a[60] @ 3840
	.word	03dd9358bh,0b16ca45fh		; a[61] @ 3904
	.word	0bddf2971h,0b4abbc7ch		; a[62] @ 3968
	.word	03de34297h,012c543f8h		; a[63] @ 4032
	.word	0bde7ceddh,09a091a32h		; a[64] @ 4096
	.word	03ded6e10h,09567eb85h		; a[65] @ 4160
	.word	0bdf2308dh,099e8b4a8h		; a[66] @ 4224
	.word	03df67c1eh,08a00ebdah		; a[67] @ 4288
	.word	0bdfbcb54h,01a95add1h		; a[68] @ 4352
	.word	03e012dbfh,01ed70e0eh		; a[69] @ 4416
	.word	0be053c33h,03a90dcfbh		; a[70] @ 4480
	.word	03e0a3fddh,0a9449850h		; a[71] @ 4544
	.word	0be103953h,0020a12f2h		; a[72] @ 4608
	.word	03e140e0fh,04199c785h		; a[73] @ 4672
	.word	0be18ca61h,090c97398h		; a[74] @ 4736
	.word	03e1ea4f8h,0b328279bh		; a[75] @ 4800
	.word	0be22f0b7h,06ee94228h		; a[76] @ 4864
	.word	03e2769a8h,0649e9b03h		; a[77] @ 4928
	.word	0be2cf0f5h,03c203caeh		; a[78] @ 4992
	.word	03e31e33ah,0c2c90641h		; a[79] @ 5056
	.word	0be361c89h,05b3d1b07h		; a[80] @ 5120
	.word	03e3b552dh,03268f5b9h		; a[81] @ 5184
	.word	0be40e4b8h,07b3bef3fh		; a[82] @ 5248
	.word	03e44e1eeh,013af1016h		; a[83] @ 5312
	.word	0be49d047h,07f6616bah		; a[84] @ 5376
	.word	03e4fe8b6h,0312537beh		; a[85] @ 5440
	.word	0be53b8cfh,0180c0639h		; a[86] @ 5504
	.word	03e5860ffh,098afb4f3h		; a[87] @ 5568
	.word	0be5e22b4h,0f3b4059fh		; a[88] @ 5632
	.word	03e62a033h,083668af5h		; a[89] @ 5696
	.word	0be670621h,0a1477bc1h		; a[90] @ 5760
	.word	03e6c75eeh,027c198f2h		; a[91] @ 5824
	.word	0be719730h,0a7b9bf33h		; a[92] @ 5888
	.word	03e75be8ah,0ccacf285h		; a[93] @ 5952
	.word	0be7ae0fbh,0fa168a5eh		; a[94] @ 6016
	.word	03e809ce8h,0548f0887h		; a[95] @ 6080
	.word	0be848929h,004cb0e8eh		; a[96] @ 6144
	.word	03e89628bh,0f1711a3ch		; a[97] @ 6208
	.word	0be8f6111h,0db05597ah		; a[98] @ 6272
	.word	03e9364f8h,0cd899e77h		; a[99] @ 6336
	.word	0be97f95dh,09cc013b4h		; a[100] @ 6400
	.word	03e9da299h,0dcd4f4dah		; a[101] @ 6464
	.word	0bea25106h,00f76c1e3h		; a[102] @ 6528
	.word	03ea6a441h,0f5828c0fh		; a[103] @ 6592
	.word	0beabfcf2h,0302c5badh		; a[104] @ 6656
	.word	03eb14c69h,0743cafb5h		; a[105] @ 6720
	.word	0beb5621bh,08cd119c6h		; a[106] @ 6784
	.word	03eba6eb9h,0ab485979h		; a[107] @ 6848
	.word	0bec05649h,063f58bbfh		; a[108] @ 6912
	.word	03ec431dch,0e527705fh		; a[109] @ 6976
	.word	0bec8f6a3h,07baf3722h		; a[110] @ 7040
	.word	03ecedbadh,0fe3a090fh		; a[111] @ 7104
	.word	0bed31287h,00479812ah		; a[112] @ 7168
	.word	03ed79374h,0120f7780h		; a[113] @ 7232
	.word	0bedd249fh,097a0500bh		; a[114] @ 7296
	.word	03ee20329h,066209a08h		; a[115] @ 7360
	.word	0bee64401h,0bd0f849eh		; a[116] @ 7424
	.word	03eeb85f8h,0111b1dcfh		; a[117] @ 7488
	.word	0bef102e0h,070cac3b5h		; a[118] @ 7552
	.word	03ef50735h,012db48c1h		; a[119] @ 7616
	.word	0bef9fe5ch,0a87eba1ch		; a[120] @ 7680
	.word	03f0010d6h,07e5cc060h		; a[121] @ 7744
	.word	0bf03dc04h,010189b94h		; a[122] @ 7808
	.word	03f088c85h,006541fefh		; a[123] @ 7872
	.word	0bf0e5880h,080b6214eh		; a[124] @ 7936
	.word	03f12c173h,08956d9c0h		; a[125] @ 8000
	.word	0bf172f3bh,095cefd07h		; a[126] @ 8064
	.word	03f1ca8bch,0a9117c6ch		; a[127] @ 8128
	.word	0bf21b697h,0c9634a78h		; a[128] @ 8192
	.word	03f25e55bh,0c433e787h		; a[129] @ 8256
	.word	0bf2b10f8h,056db8764h		; a[130] @ 8320
	.word	03f30ba90h,05bc3a550h		; a[131] @ 8384
	.word	0bf34add1h,0a8e25e70h		; a[132] @ 8448
	.word	03f398fddh,03b009d64h		; a[133] @ 8512
	.word	0bf3f9916h,074b31ba6h		; a[134] @ 8576
	.word	03f438798h,02c8a8c30h		; a[135] @ 8640
	.word	0bf482429h,0db0ebcaeh		; a[136] @ 8704
	.word	03f4dd781h,024bb72c9h		; a[137] @ 8768
	.word	0bf5271b8h,0903b074eh		; a[138] @ 8832
	.word	03f56ccadh,00eb8ccddh		; a[139] @ 8896
	.word	0bf5c2ee8h,0536e9a9bh		; a[140] @ 8960
	.word	03f616b4bh,038c9b14bh		; a[141] @ 9024
	.word	0bf658847h,0b7a49c82h		; a[142] @ 9088
	.word	03f6a9de9h,03d237f95h		; a[143] @ 9152
	.word	0bf707373h,047d3dcbfh		; a[144] @ 9216
	.word	03f7455e9h,0db3f4529h		; a[145] @ 9280
	.word	0bf792333h,0bf52c451h		; a[146] @ 9344
	.word	03f7f12c4h,016b49131h		; a[147] @ 9408
	.word	0bf833492h,0fc1302deh		; a[148] @ 9472
	.word	03f87bd8ah,08f908142h		; a[149] @ 9536
	.word	0bf8d58a6h,009698b34h		; a[150] @ 9600
	.word	03f922351h,03de0355fh		; a[151] @ 9664
	.word	0bf966bc1h,06f209f32h		; a[152] @ 9728
	.word	03f9bb71ah,05dfa3134h		; a[153] @ 9792
	.word	0bfa1213eh,0e9f5a78ch		; a[154] @ 9856
	.word	03fa52cbfh,050b85445h		; a[155] @ 9920
	.word	0bfaa2cc3h,0d85c77fbh		; a[156] @ 9984
	.word	03fb02d84h,0c87c3027h		; a[157] @ 10048
	.word	0bfb3ff77h,0c4dd951ch		; a[158] @ 10112
	.word	03fb8b857h,0cac23092h		; a[159] @ 10176
	.word	0bfbe8eabh,0ffcdab19h		; a[160] @ 10240
	.word	03fc2e2eeh,077417ffdh		; a[161] @ 10304
	.word	0bfc7589eh,0fd86a8fch		; a[162] @ 10368
	.word	03fccdbe6h,04543d6efh		; a[163] @ 10432
	.word	0bfd1d636h,06d7a56deh		; a[164] @ 10496
	.word	03fd60c72h,069a9e7c5h		; a[165] @ 10560
	.word	0bfdb4149h,0766b9728h		; a[166] @ 10624
	.word	03fe0d86dh,07f5f5bb0h		; a[167] @ 10688
	.word	0bfe4d2bbh,0fa16b1f3h		; a[168] @ 10752
	.word	03fe9bd7fh,01c3fd1a7h		; a[169] @ 10816
	.word	0bfefd17eh,0ad8508e9h		; a[170] @ 10880
	.word	03ff3aa75h,089efd86bh		; a[171] @ 10944
	.word	0bff84f41h,0f212d773h		; a[172] @ 11008
	.word	03ffe0cc6h,0822ff089h		; a[173] @ 11072
	.word	0c00292a5h,0a469d734h		; a[174] @ 11136
	.word	04006f560h,084a515cfh		; a[175] @ 11200
	.word	0c00c6138h,079c4113ch		; a[176] @ 11264
	.word	040118a63h,0b688bda9h		; a[177] @ 11328
	.word	0c015aeb8h,00ecfa69ch		; a[178] @ 11392
	.word	0401acd6dh,07e889c1bh		; a[179] @ 11456
	.word	0c02090d1h,073fb7a5fh		; a[180] @ 11520
	.word	040247a36h,0e2eb1c43h		; a[181] @ 11584
	.word	0c0295013h,0a92a3055h		; a[182] @ 11648
	.word	0402f4a3ch,021187e7ch		; a[183] @ 11712
	.word	0c03356dbh,0b59ddc1eh		; a[184] @ 11776
	.word	04037e7ebh,0af102364h		; a[185] @ 11840
	.word	0c03d8d09h,017d6b65bh		; a[186] @ 11904
	.word	0404243b2h,0031ceaf2h		; a[187] @ 11968
	.word	0c04693c7h,0f77af640h		; a[188] @ 12032
	.word	0404be894h,01c8216c6h		; a[189] @ 12096
	.word	0c0513fd3h,0458cd20bh		; a[190] @ 12160
	.word	04055528ch,03f3e0371h		; a[191] @ 12224
	.word	0c05a5b7eh,090ff9724h		; a[192] @ 12288
	.word	040604a66h,066666666h		; a[193] @ 12352
	.word	0c064232bh,0020c49bah		; a[194] @ 12416
	.word	04068e479h,03dd97f63h		; a[195] @ 12480
	.word	0c06ec539h,0c0ebedfah		; a[196] @ 12544
	.word	0407304a5h,0e353f7cfh		; a[197] @ 12608
	.word	0c077824ch,02f837b4ah		; a[198] @ 12672
	.word	0407d0f6ah,07ef9db23h		; a[199] @ 12736
	.word	0c081f60dh,0ed288ce7h		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\094042 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\094044 
	.sect	".text:optci"
	.clink

;******************************************************************************
;* FUNCTION NAME: expdp_sinhdp_i                                              *
;*                                                                            *
;*   Regs Modified     : A3,A4,A5,A6,A7,A8,A9,B0,B4,B5,B6,B7,B8,B9,A16,A17,   *
;*                           B16,B17                                          *
;*   Regs Used         : A3,A4,A5,A6,A7,A8,A9,B0,B3,B4,B5,B6,B7,B8,B9,A16,A17,*
;*                           B16,B17                                          *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
expdp_sinhdp_i:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 112
           MVKL    .S1     0x3ff71547,A7
           MVKL    .S1     0x652b82fe,A6
           MVKH    .S1     0x3ff71547,A7
           MVKH    .S1     0x652b82fe,A6
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |100| 
           MVKL    .S2     0x3fe63000,B5
           MVKL    .S2     0xbf2bd010,B7
           MVKH    .S2     0x3fe63000,B5
           DPINT   .L1     A7:A6,A3          ; |100| 
           ZERO    .L2     B4                ; |105| 
           MVKL    .S2     0x5c610ca8,B6
           MVKH    .S2     0xbf2bd010,B7
           INTDP   .L1     A3,A7:A6          ; |105| 
           MVKH    .S2     0x5c610ca8,B6
           MVKL    .S1     0x3ef152a4,A9
           MVKL    .S1     0x6f58dc1c,A8
           MVKH    .S1     0x3ef152a4,A9
           MVKH    .S1     0x6f58dc1c,A8
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |105| 
           FMPYDP  .M1X    B7:B6,A7:A6,A7:A6 ; |105| 
           MVKL    .S2     0x6fb3f6e0,B6
           MVKL    .S2     0x3f7c70e4,B7
           MVKH    .S2     0x6fb3f6e0,B6
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |105| 
           MVKL    .S2     0x6fde3809,B4
           MVKL    .S2     0x3f403f99,B5
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |105| 
           MVKH    .S2     0x6fde3809,B4
           MVKH    .S2     0x3f403f99,B5
           FMPYDP  .M1     A7:A6,A7:A6,A5:A4 ; |105| 
           MVKH    .S2     0x3f7c70e4,B7
           ZERO    .L2     B17
           SET     .S2     B17,0x1e,0x1e,B17
           FMPYDP  .M1     A9:A8,A5:A4,A17:A16 ; |105| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |106| 
           MVKL    .S1     0x3fac718e,A9
           MVKL    .S1     0x714251b3,A8
           MVKH    .S1     0x3fac718e,A9
           FADDDP  .L2X    B7:B6,A17:A16,B7:B6 ; |105| 
           ZERO    .L1     A17
           MVKH    .S1     0x714251b3,A8
           FMPYDP  .M2X    A5:A4,B7:B6,B7:B6 ; |105| 
           FADDDP  .L1X    A9:A8,B5:B4,A9:A8 ; |106| 

           MVKH    .S1     0x3fd00000,A17
||         ZERO    .L1     A16               ; |105| 

           ZERO    .L2     B16               ; |105| 
           FADDDP  .L2X    A17:A16,B7:B6,B5:B4 ; |105| 
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |106| 
           ZERO    .L1     A9
           FMPYDP  .M2X    A7:A6,B5:B4,B9:B8 ; |105| 

           SET     .S1     A9,0x15,0x1d,A9
||         MV      .L1     A16,A8            ; |105| 

           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |106| 
           NOP             2
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |106| 
           NOP             2
           RCPDP   .S1     A5:A4,A7:A6       ; |67| 
           NOP             1
           FMPYDP  .M1     A5:A4,A7:A6,A17:A16 ; |67| 
           NOP             4
           FSUBDP  .L2X    B17:B16,A17:A16,B5:B4 ; |67| 
           NOP             2
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |67| 
           MVK     .S1     1022,A6           ; |120| 
           ADD     .L1     A6,A3,A3          ; |120| 
           SHL     .S1     A3,20,A7          ; |120| 
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |67| 
           ZERO    .L1     A6                ; |120| 
           NOP             2
           FSUBDP  .L2     B17:B16,B7:B6,B7:B6 ; |67| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |67| 
           MV      .L2     B17,B5            ; |67| 
           MV      .L2     B16,B4            ; |67| 
           NOP             2
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |67| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |67| 
           ZERO    .L1     A5:A4             ; |70| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |67| 
           CMPEQDP .S2X    B9:B8,A5:A4,B0    ; |70| 
           MV      .L1     A9,A5             ; |120| 
           ZERO    .L1     A4                ; |120| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |67| 
           NOP             3
   [ B0]   ZERO    .L2     B5:B4             ; |71| 
           NOP             1
           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |120| 
           ZERO    .L2     B5
           MVKH    .S2     0x40100000,B5
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |120| 
           ZERO    .L2     B4                ; |120| 
           NOP             1
           RETNOP  .S2     B3,1              ; |121| 
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |120| 
           NOP             3
           ; BRANCH OCCURS {B3}              ; |121| 
;**	Parameter deleted: req_flags == 9;
;**	Parameter deleted: tol == 1e-12;
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
||         MVKL    .S2     0x812dea11,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     output,A11
||         MVKL    .S2     0x3d719799,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     output,A11
||         MVKH    .S2     0x812dea11,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3d719799,B7
||         MVK     .S1     0x9,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {isequal} {0}       ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3d719799,B7
           MVKL    .S2     0x812dea11,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A12
||         MVKH    .S2     0x3d719799,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A12
||         MVKH    .S2     0x812dea11,B6

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x812dea11,B6
           MVKL    .S2     0x3d719799,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0x812dea11,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3d719799,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3d719799,B7
           MVKL    .S2     0x812dea11,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3d719799,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0x812dea11,B6

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
;*   Local Frame Size  : 8 Args + 0 Auto + 56 Save = 64 byte                  *
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

           STW     .D2T2   B3,*SP--(16)      ; |122| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     a,A12
||         MVKL    .S2     output,B10

           MVKH    .S1     a,A12
||         MVKH    .S2     output,B10

           MV      .L1     A12,A13
||         CALL    .S1     sinh              ; |139| 
||         LDW     .D2T1   *B10,A11

           LDDW    .D1T1   *A13++,A5:A4      ; |139| 
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
           ADDKPC  .S2     $C$RL5,B3,0       ; |139| 
$C$RL5:    ; CALL OCCURS {sinh} {0}          ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |138| 
||         STDW    .D1T1   A5:A4,*A11++      ; |139| 
||         SUB     .S1     A10,1,A10         ; |138| 

   [ A0]   B       .S1     $C$L3             ; |138| 
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |139| 
|| [!A0]   ADD     .L2     4,B10,B11

   [ A0]   CALL    .S1     sinh              ; |139| 
   [!A0]   MV      .L1     A12,A10
   [!A0]   ZERO    .L2     B10
   [!A0]   MVK     .S1     0xc9,A3
   [!A0]   MV      .L1     A3,A11
           ; BRANCHCC OCCURS {$C$L3}         ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     sinhdp            ; |142| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |142| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |142| 
$C$RL6:    ; CALL OCCURS {sinhdp} {0}        ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |142| 
||         SUB     .L1     A11,1,A0          ; |141| 
||         SUB     .S1     A11,1,A11         ; |141| 

   [ A0]   BNOP    .S2     $C$L4,2           ; |141| 
|| [!A0]   MVK     .S1     0xc9,A3
|| [!A0]   ADD     .L2     4,B11,B11
|| [!A0]   MV      .L1     A12,A11

   [!A0]   MV      .L1     A3,A10

           ADD     .L2     B10,B4,B4         ; |142| 
||         ADD     .S2     8,B10,B10         ; |141| 

   [ A0]   CALL    .S1     sinhdp            ; |142| 
|| [!A0]   ZERO    .L2     B10
||         STDW    .D2T1   A5:A4,*B4         ; |142| 

           ; BRANCHCC OCCURS {$C$L4}         ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     sinhdp_c          ; |145| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |145| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |145| 
$C$RL7:    ; CALL OCCURS {sinhdp_c} {0}      ; |145| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |145| 
||         SUB     .L1     A10,1,A0          ; |144| 
||         SUB     .S1     A10,1,A10         ; |144| 

   [ A0]   BNOP    .S2     $C$L5,1           ; |144| 
|| [!A0]   ZERO    .L1     A11
|| [!A0]   ZERO    .L2     B20
|| [!A0]   MVK     .S1     0xc9,A1
|| [!A0]   SUB     .D2X    A12,8,B21
|| [!A0]   ZERO    .D1     A30

   [!A0]   ZERO    .L1     A10
   [!A0]   SET     .S1     A11,0x14,0x1e,A11

           ADD     .L2     B10,B4,B4         ; |145| 
||         ADD     .S2     8,B10,B10         ; |144| 

   [ A0]   CALL    .S1     sinhdp_c          ; |145| 
||         STDW    .D2T1   A5:A4,*B4         ; |145| 

           ; BRANCHCC OCCURS {$C$L5}         ; |144| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 15
           LDDW    .D2T2   *++B21,B5:B4      ; |200| 
           ZERO    .L1     A5:A4             ; |203| 
           ZERO    .L2     B6                ; |207| 
           ZERO    .L2     B7
           MVKH    .S2     0x40390000,B7

           ABSDP   .S2     B5:B4,B19:B18     ; |200| 
||         CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |203| 

           ZERO    .L2     B5

           CMPGTDP .S2     B19:B18,B7:B6,B0  ; |207| 
|| [ A0]   ZERO    .L1     A19
|| [!A0]   ZERO    .S1     A19
|| [ A0]   ZERO    .D1     A18               ; |203| 

   [!A0]   SET     .S1     A19,0x14,0x1d,A19
|| [!A0]   ZERO    .L1     A18               ; |203| 

   [ B0]   B       .S1     $C$L8             ; |207| 
|| [!B0]   ZERO    .L2     B4                ; |211| 
||         SET     .S2     B5,0x14,0x1d,B5
||         MV      .D2     B0,B1             ; guard predicate rewrite

           MV      .L2     B0,B2             ; branch predicate copy
||         CMPGTDP .S2     B19:B18,B5:B4,B0  ; |211| 

   [ A0]   MVKH    .S1     0xbff00000,A19

   [ B1]   MVK     .L2     0x1,B0            ; |211| nullify predicate
|| [ B2]   MVKL    .S2     0xfefa39ec,B4

   [ B2]   MVKH    .S2     0xfefa39ec,B4

   [!B0]   B       .S1     $C$L7             ; |211| 
|| [ B2]   MVKL    .S2     0x3fe62e42,B5

           ; BRANCHCC OCCURS {$C$L8}         ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

   [!B0]   FMPYDP  .M2     B19:B18,B19:B18,B5:B4 ; |167| 
|| [!B0]   MVKL    .S1     0x3ec71de3,A9
|| [ B0]   CALL    .S2     expdp_sinhdp_i    ; |215| 

   [!B0]   MVKL    .S1     0xa556c736,A8
   [!B0]   MVKH    .S1     0x3ec71de3,A9
   [!B0]   MVKH    .S1     0xa556c736,A8
   [!B0]   FMPYDP  .M2     B5:B4,B5:B4,B17:B16 ; |167| 
           ; BRANCHCC OCCURS {$C$L7}         ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           DADD    .L1X    0,B19:B18,A5:A4   ; |215| 
||         ADDKPC  .S2     $C$RL8,B3,0       ; |215| 

$C$RL8:    ; CALL OCCURS {expdp_sinhdp_i} {0}  ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 41
           RCPDP   .S1     A5:A4,A7:A6       ; |217| 
           ZERO    .L1     A16               ; |217| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           ZERO    .L1     A17
           SET     .S1     A17,0x1e,0x1e,A17
           ZERO    .L2     B4                ; |217| 
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |217| 
           MV      .L2X    A17,B5            ; |217| 
           MVKL    .S2     output+12,B29
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |217| 
           ZERO    .L2     B8                ; |217| 
           MVKH    .S2     output+12,B29
           LDW     .D2T1   *B29,A3
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           SUB     .L1     A1,1,A1           ; |147| 
           ZERO    .L1     A31
           MV      .L2X    A17,B9            ; |217| 
           ADD     .L1X    B20,A3,A3
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |217| 
           ADD     .L2     8,B20,B20         ; |147| 
           NOP             1
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |217| 
           ZERO    .L1     A6                ; |217| 
           SET     .S1     A31,0x15,0x1d,A7
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |217| 
           NOP             3
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |217| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |217| 
           NOP             2
           BNOP    .S1     $C$L9,1           ; |217| 

           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |217| 
||         MVKL    .S2     0x8fb9f87e,B4

           MVKL    .S2     0x408633ce,B5
           MVKH    .S2     0x8fb9f87e,B4

           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |217| 
||         MVKH    .S2     0x408633ce,B5

           ; BRANCH OCCURS {$C$L9}           ; |217| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 31

           FMPYDP  .M1X    A9:A8,B5:B4,A9:A8 ; |167| 
||         MVKL    .S2     0x3f2a01a0,B23
||         MVKL    .S1     0x55555561,A6

           MVKL    .S2     0x1a01a00b,B22
||         MVKL    .S1     0x3fc55555,A7

           MVKH    .S2     0x3f2a01a0,B23
||         MVKH    .S1     0x55555561,A6

           FMPYDP  .M2     B5:B4,B17:B16,B7:B6 ; |167| 
||         MVKH    .S2     0x1a01a00b,B22
||         MVKH    .S1     0x3fc55555,A7

           MVKL    .S2     0x3de61246,B9
||         MVKL    .S1     0x3e5ae645,A5
||         FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |167| 

           MVKL    .S2     0x13a86d04,B8
||         MVKL    .S1     0x67f544de,A4
||         FADDDP  .L1X    B23:B22,A9:A8,A9:A8 ; |167| 

           MVKH    .S2     0x3de61246,B9
||         MVKH    .S1     0x3e5ae645,A5

           MVKH    .S2     0x13a86d04,B8
||         MVKH    .S1     0x67f544de,A4

           MVKL    .S2     0x3f811111,B25
||         FMPYDP  .M2     B9:B8,B7:B6,B23:B22 ; |167| 
||         FMPYDP  .M1X    A5:A4,B17:B16,A5:A4 ; |167| 
||         MVKL    .S1     output+12,A3

           MVKH    .S1     output+12,A3
||         MVKL    .S2     0x1111110f,B24

           MVKH    .S2     0x3f811111,B25
           MVKH    .S2     0x1111110f,B24
           FMPYDP  .M2     B25:B24,B17:B16,B5:B4 ; |167| 
           FMPYDP  .M2X    B7:B6,A9:A8,B9:B8 ; |167| 
           LDW     .D1T1   *A3,A3
           FADDDP  .L1X    B23:B22,A5:A4,A5:A4 ; |167| 
           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |167| 
           SUB     .S1     A1,1,A1           ; |147| 
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |167| 
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |167| 
           ADD     .L1X    B20,A3,A3
           ADD     .S2     8,B20,B20         ; |147| 
           NOP             1

           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |167| 
||         MVKL    .S2     0x8fb9f87e,B4

           MVKL    .S2     0x408633ce,B5
           B       .S1     $C$L10            ; |167| 
           FMPYDP  .M1X    B19:B18,A5:A4,A5:A4 ; |167| 
           MVKH    .S2     0x8fb9f87e,B4
           MVKH    .S2     0x408633ce,B5
           CMPGTDP .S2     B19:B18,B5:B4,B0  ; |220| 
           FADDDP  .L1X    B19:B18,A5:A4,A5:A4 ; |167| 
           ; BRANCH OCCURS {$C$L10}          ; |167| 
;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 107

           MVKH    .S2     0x3fe62e42,B5
||         MVKL    .S1     0x652b82fe,A4

           FSUBDP  .L2     B19:B18,B5:B4,B5:B4 ; |100| 
           MVKL    .S1     0x3ff71547,A5
           MVKH    .S1     0x652b82fe,A4
           MVKH    .S1     0x3ff71547,A5
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |100| 
           ZERO    .L2     B31
           ZERO    .L1     A6                ; |105| 
           MVKL    .S2     0xbf2bd010,B7
           DPINT   .L1     A5:A4,A3          ; |100| 
           MVKL    .S2     0x5c610ca8,B6
           MVKH    .S2     0xbf2bd010,B7
           MVKH    .S2     0x5c610ca8,B6
           INTDP   .L1     A3,A5:A4          ; |105| 
           MVKL    .S1     0x3fe63000,A7
           MVKH    .S1     0x3fe63000,A7
           MVKL    .S2     0x6fb3f6e0,B16
           MVKL    .S2     0x3f7c70e4,B17
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |105| 
           MVKH    .S2     0x6fb3f6e0,B16
           FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |105| 
           MVKH    .S2     0x3f7c70e4,B17
           MVKL    .S1     0x3ef152a4,A5
           FSUBDP  .L2X    B5:B4,A7:A6,B5:B4 ; |105| 
           MVKL    .S1     0x6f58dc1c,A4
           MVKH    .S1     0x3ef152a4,A5
           FSUBDP  .L2     B5:B4,B7:B6,B7:B6 ; |105| 
           MVKH    .S1     0x6f58dc1c,A4
           ZERO    .L1     A6                ; |105| 
           FMPYDP  .M2     B7:B6,B7:B6,B5:B4 ; |105| 
           ZERO    .L1     A7
           MVKH    .S1     0x3fd00000,A7
           ZERO    .L1     A31

           FMPYDP  .M2X    A5:A4,B5:B4,B9:B8 ; |105| 
||         MVKL    .S1     0x3f403f99,A5

           MVKL    .S1     0x6fde3809,A4
           MVKH    .S1     0x3f403f99,A5
           MVKH    .S1     0x6fde3809,A4

           MVKL    .S2     0x714251b3,B16
||         FADDDP  .L2     B17:B16,B9:B8,B9:B8 ; |105| 

           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |106| 
           MVKL    .S2     0x3fac718e,B17
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |105| 
           MVKH    .S2     0x714251b3,B16
           MVKH    .S2     0x3fac718e,B17
           FADDDP  .L2X    B17:B16,A5:A4,B17:B16 ; |106| 
           ZERO    .L1     A16               ; |67| 
           FADDDP  .L1X    A7:A6,B9:B8,A5:A4 ; |105| 
           FMPYDP  .M2     B5:B4,B17:B16,B5:B4 ; |106| 
           ZERO    .L2     B8                ; |106| 
           FMPYDP  .M1X    B7:B6,A5:A4,A7:A6 ; |105| 
           SET     .S2     B31,0x15,0x1d,B9
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |106| 
           ZERO    .L1     A4                ; |67| 
           SET     .S1     A31,0x1e,0x1e,A5
           FSUBDP  .L2X    B5:B4,A7:A6,B7:B6 ; |106| 
           ZERO    .L1     A17
           SET     .S1     A17,0x1e,0x1e,A17
           RCPDP   .S2     B7:B6,B5:B4       ; |67| 
           SUB     .L1     A1,1,A1           ; |147| 
           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |67| 
           MVK     .S2     0x3fe,B29
           MVKL    .S2     output+12,B30
           MVKH    .S2     output+12,B30
           LDW     .D2T1   *B30,A29
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |67| 
           NOP             2
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |67| 
           NOP             3
           FMPYDP  .M1X    B7:B6,A5:A4,A9:A8 ; |67| 
           NOP             3
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |67| 
           NOP             2
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |67| 
           ZERO    .L1     A8                ; |120| 
           SET     .S1     A30,0x15,0x1d,A9
           NOP             2
           FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |67| 
           ZERO    .L2     B6                ; |67| 
           MV      .L2X    A17,B7            ; |67| 
           NOP             1
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |67| 
           NOP             3

           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |67| 
||         ZERO    .L2     B5:B4             ; |70| 

           NOP             1
           CMPEQDP .S1X    A7:A6,B5:B4,A0    ; |70| 
           ADD     .L2X    B29,A3,B4         ; |120| 

           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |67| 
||         SHL     .S2     B4,20,B5          ; |120| 
||         ADD     .L1X    B20,A29,A3

           ADD     .L2     8,B20,B20         ; |147| 
           ZERO    .L1     A6                ; |120| 
           ZERO    .L1     A7
   [ A0]   ZERO    .L1     A5:A4             ; |71| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |120| 
           ZERO    .L2     B4                ; |120| 
           MVKH    .S1     0x40100000,A7

           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |120| 
||         MVKL    .S2     0x408633ce,B5

           MVKL    .S2     0x8fb9f87e,B4
           MVKH    .S2     0x408633ce,B5
           MVKH    .S2     0x8fb9f87e,B4
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |120| 
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1
           CMPGTDP .S2     B19:B18,B5:B4,B0  ; |220| 
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 8
   [!A1]   ADDAD   .D2     B11,1,B10
           NOP             1

   [ B0]   DADD    .L1     0,A11:A10,A5:A4   ; |221| 
|| [ A1]   B       .S1     $C$L6             ; |147| 

           FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |148| 
           NOP             3

   [!A1]   CALL    .S1     sinhdp_v          ; |150| 
||         STDW    .D1T1   A5:A4,*A3         ; |148| 

           ; BRANCHCC OCCURS {$C$L6}         ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *B10,B4           ; |150| 
           MV      .L1     A12,A4            ; |150| 
           ADDKPC  .S2     $C$RL9,B3,1       ; |150| 
           MVK     .S1     0xc9,A6           ; |150| 
$C$RL9:    ; CALL OCCURS {sinhdp_v} {0}      ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0xc9,A4           ; |155| 

$C$RL10:   ; CALL OCCURS {allequal} {0}      ; |155| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |156| 

$C$RL11:   ; CALL OCCURS {print_test_results} {0}  ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
           MVKL    .S1     a_sc,A13

           MVKH    .S1     a_sc,A13
||         ZERO    .L2     B5

           STDW    .D1T1   A11:A10,*+A13(16) ; |165| 
||         MVKH    .S2     0x80000000,B5
||         MVK     .L1     0xffffffff,A4     ; |170| 
||         ZERO    .L2     B4                ; |164| 

           STDW    .D1T2   B5:B4,*+A13(8)    ; |164| 
||         MV      .L1     A4,A5             ; |170| 
||         ZERO    .L2     B9

           STDW    .D1T1   A5:A4,*+A13(56)   ; |170| 
||         SET     .S2     B9,0x14,0x1d,B9
||         ZERO    .L1     A8                ; |166| 
||         ZERO    .S1     A9
||         ZERO    .L2     B8                ; |167| 

           STDW    .D1T2   B9:B8,*+A13(32)   ; |167| 
||         MVKH    .S1     0xfff00000,A9
||         ZERO    .L1     A7

           STDW    .D1T1   A9:A8,*+A13(24)   ; |166| 
||         MVKH    .S1     0xbff00000,A7
||         ZERO    .L1     A6                ; |168| 

           MVK     .L2     0x8,B4
||         STDW    .D1T1   A7:A6,*+A13(40)   ; |168| 
||         ADD     .S2     -1,B5,B7
||         MV      .D2X    A4,B6

           ZERO    .L1     A5:A4             ; |163| 
||         STDW    .D1T2   B7:B6,*+A13(48)   ; |169| 

           STDW    .D1T1   A5:A4,*A13        ; |163| 
||         MV      .L1X    B4,A14            ; |164| 
||         SUB     .L2X    A13,8,B11
||         ZERO    .S1     A12

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
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     sinh              ; |173| 
||         LDDW    .D2T2   *++B11,B5:B4      ; |173| 

           ADDKPC  .S2     $C$RL12,B3,3      ; |173| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |173| 
$C$RL12:   ; CALL OCCURS {sinh} {0}          ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 33
           MVKL    .S1     output,A15
           MVKH    .S1     output,A15
           LDW     .D1T2   *A15,B4           ; |173| 
           NOP             4
           ADD     .L2X    A12,B4,B4         ; |173| 
           STDW    .D2T1   A5:A4,*B4         ; |173| 

           CALLP   .S2     sinhdp,B3
||         LDDW    .D2T1   *B11,A5:A4        ; |174| 

$C$RL13:   ; CALL OCCURS {sinhdp} {0}        ; |174| 
           LDW     .D1T2   *+A15(4),B4       ; |174| 
           NOP             4
           ADD     .L2X    A12,B4,B4         ; |174| 
           STDW    .D2T1   A5:A4,*B4         ; |174| 
           LDDW    .D2T2   *B11,B5:B4        ; |175| 
           NOP             4

           CALLP   .S2     sinhdp_c,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |175| 

$C$RL14:   ; CALL OCCURS {sinhdp_c} {0}      ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           LDW     .D1T1   *+A15(8),A3       ; |175| 
           ZERO    .L2     B6                ; |207| 
           ZERO    .L2     B7
           MVKH    .S2     0x40390000,B7
           NOP             1
           ADD     .L1     A12,A3,A3         ; |175| 
           STDW    .D1T1   A5:A4,*A3         ; |175| 
           LDDW    .D2T2   *B11,B5:B4        ; |200| 
           ZERO    .L1     A5:A4             ; |203| 
           NOP             3

           ABSDP   .S2     B5:B4,B19:B18     ; |200| 
||         CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |203| 

           ZERO    .L2     B5

           CMPGTDP .S2     B19:B18,B7:B6,B0  ; |207| 
|| [ A0]   ZERO    .L1     A19
|| [!A0]   ZERO    .S1     A19
|| [ A0]   ZERO    .D1     A18               ; |203| 

   [!A0]   SET     .S1     A19,0x14,0x1d,A19
|| [!A0]   ZERO    .L1     A18               ; |203| 

   [ B0]   B       .S1     $C$L13            ; |207| 
|| [!B0]   ZERO    .L2     B4                ; |211| 
||         SET     .S2     B5,0x14,0x1d,B5
||         MV      .D2     B0,B1             ; guard predicate rewrite

           MV      .L2     B0,B2             ; branch predicate copy
||         CMPGTDP .S2     B19:B18,B5:B4,B0  ; |211| 

   [ A0]   MVKH    .S1     0xbff00000,A19

   [ B1]   MVK     .L2     0x1,B0            ; |211| nullify predicate
|| [ B2]   MVKL    .S2     0xfefa39ec,B4

   [ B2]   MVKL    .S2     0x3fe62e42,B5

   [!B0]   B       .S1     $C$L12            ; |211| 
|| [ B2]   MVKH    .S2     0xfefa39ec,B4

           ; BRANCHCC OCCURS {$C$L13}        ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

   [!B0]   FMPYDP  .M2     B19:B18,B19:B18,B5:B4 ; |167| 
|| [!B0]   MVKL    .S1     0x3ec71de3,A7
|| [ B0]   CALL    .S2     expdp_sinhdp_i    ; |215| 

   [!B0]   MVKL    .S1     0xa556c736,A6
   [!B0]   MVKH    .S1     0x3ec71de3,A7
   [!B0]   MVKH    .S1     0xa556c736,A6
   [!B0]   FMPYDP  .M2     B5:B4,B5:B4,B7:B6 ; |167| 
           ; BRANCHCC OCCURS {$C$L12}        ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           DADD    .L1X    0,B19:B18,A5:A4   ; |215| 
||         ADDKPC  .S2     $C$RL15,B3,0      ; |215| 

$C$RL15:   ; CALL OCCURS {expdp_sinhdp_i} {0}  ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 41
           RCPDP   .S1     A5:A4,A7:A6       ; |217| 
           ZERO    .L1     A16               ; |217| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           ZERO    .L1     A17
           SET     .S1     A17,0x1e,0x1e,A17
           ZERO    .L2     B4                ; |217| 
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |217| 
           MV      .L2X    A17,B5            ; |217| 
           ZERO    .L2     B8                ; |217| 
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |217| 
           ZERO    .L1     A31
           ADDAW   .D1     A15,3,A3
           LDW     .D1T1   *A3,A3            ; |176| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           SUB     .L1     A14,1,A0          ; |172| 
           SUB     .L1     A14,1,A14         ; |172| 
           MV      .L2X    A17,B9            ; |217| 
           ADD     .L1     A12,A3,A3         ; |176| 
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |217| 
           ADD     .L1     8,A12,A12         ; |172| 
           NOP             1
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |217| 
           ZERO    .L1     A6                ; |217| 
           SET     .S1     A31,0x15,0x1d,A7
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |217| 
           NOP             3
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |217| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |217| 
           NOP             2
           BNOP    .S1     $C$L14,1          ; |217| 

           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |217| 
||         MVKL    .S2     0x8fb9f87e,B4

           MVKL    .S2     0x408633ce,B5
           MVKH    .S2     0x8fb9f87e,B4

           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |217| 
||         MVKH    .S2     0x408633ce,B5

           ; BRANCH OCCURS {$C$L14}          ; |217| 
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 31

           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |167| 
||         MVKL    .S2     0x3f2a01a0,B21
||         MVKL    .S1     0x55555561,A4

           MVKL    .S2     0x1a01a00b,B20
||         MVKL    .S1     0x3fc55555,A5

           MVKH    .S2     0x3f2a01a0,B21
||         MVKH    .S1     0x55555561,A4

           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |167| 
||         MVKH    .S2     0x1a01a00b,B20
||         MVKH    .S1     0x3fc55555,A5

           MVKL    .S2     0x3de61246,B23
||         MVKL    .S1     0x3e5ae645,A9
||         FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |167| 

           MVKL    .S2     0x13a86d04,B22
||         MVKL    .S1     0x67f544de,A8
||         FADDDP  .L1X    B21:B20,A7:A6,A7:A6 ; |167| 

           MVKH    .S2     0x3de61246,B23
||         MVKH    .S1     0x3e5ae645,A9

           MVKH    .S2     0x13a86d04,B22
||         MVKH    .S1     0x67f544de,A8

           MVKL    .S2     0x3f811111,B17
||         FMPYDP  .M2     B23:B22,B9:B8,B5:B4 ; |167| 
||         FMPYDP  .M1X    A9:A8,B7:B6,A9:A8 ; |167| 

           MVKL    .S2     0x1111110f,B16
           MVKH    .S2     0x3f811111,B17
           MVKH    .S2     0x1111110f,B16
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |167| 
           ADDAW   .D1     A15,3,A3
           LDW     .D1T1   *A3,A3            ; |176| 
           FMPYDP  .M2X    B9:B8,A7:A6,B17:B16 ; |167| 

           FADDDP  .L1X    B5:B4,A9:A8,A5:A4 ; |167| 
||         FADDDP  .L2X    B7:B6,A5:A4,B5:B4 ; |167| 

           SUB     .L1     A14,1,A0          ; |172| 
           SUB     .S1     A14,1,A14         ; |172| 

           FMPYDP  .M1X    B9:B8,A5:A4,A5:A4 ; |167| 
||         FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |167| 

           ADD     .L1     A12,A3,A3         ; |176| 
           ADD     .L1     8,A12,A12         ; |172| 
           NOP             1

           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |167| 
||         MVKL    .S2     0x8fb9f87e,B4

           MVKL    .S2     0x408633ce,B5
           B       .S1     $C$L15            ; |167| 
           FMPYDP  .M1X    B19:B18,A5:A4,A5:A4 ; |167| 
           MVKH    .S2     0x8fb9f87e,B4
           MVKH    .S2     0x408633ce,B5
           CMPGTDP .S2     B19:B18,B5:B4,B0  ; |220| 
           FADDDP  .L1X    B19:B18,A5:A4,A5:A4 ; |167| 
           ; BRANCH OCCURS {$C$L15}          ; |167| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 107

           MVKH    .S2     0x3fe62e42,B5
||         MVKL    .S1     0x652b82fe,A4

           FSUBDP  .L2     B19:B18,B5:B4,B5:B4 ; |100| 
           MVKL    .S1     0x3ff71547,A5
           MVKH    .S1     0x652b82fe,A4
           MVKH    .S1     0x3ff71547,A5
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |100| 
           ZERO    .L2     B31
           ZERO    .L1     A6                ; |105| 
           MVKL    .S2     0xbf2bd010,B7
           DPINT   .L1     A5:A4,A3          ; |100| 
           MVKL    .S2     0x5c610ca8,B6
           MVKH    .S2     0xbf2bd010,B7
           MVKH    .S2     0x5c610ca8,B6
           INTDP   .L1     A3,A5:A4          ; |105| 
           MVKL    .S1     0x3fe63000,A7
           MVKH    .S1     0x3fe63000,A7
           MVKL    .S2     0x6fb3f6e0,B16
           MVKL    .S2     0x3f7c70e4,B17
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |105| 
           MVKH    .S2     0x6fb3f6e0,B16
           FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |105| 
           MVKH    .S2     0x3f7c70e4,B17
           MVKL    .S1     0x3ef152a4,A5
           FSUBDP  .L2X    B5:B4,A7:A6,B5:B4 ; |105| 
           MVKL    .S1     0x6f58dc1c,A4
           MVKH    .S1     0x3ef152a4,A5
           FSUBDP  .L2     B5:B4,B7:B6,B7:B6 ; |105| 
           MVKH    .S1     0x6f58dc1c,A4
           ZERO    .L1     A6                ; |105| 
           FMPYDP  .M2     B7:B6,B7:B6,B5:B4 ; |105| 
           ZERO    .L1     A7
           MVKH    .S1     0x3fd00000,A7
           ZERO    .L1     A31

           FMPYDP  .M2X    A5:A4,B5:B4,B9:B8 ; |105| 
||         MVKL    .S1     0x3f403f99,A5

           MVKL    .S1     0x6fde3809,A4
           MVKH    .S1     0x3f403f99,A5
           MVKH    .S1     0x6fde3809,A4

           MVKL    .S2     0x3fac718e,B9
||         FADDDP  .L2     B17:B16,B9:B8,B17:B16 ; |105| 

           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |106| 
           MVKL    .S2     0x714251b3,B8
           FMPYDP  .M2     B5:B4,B17:B16,B17:B16 ; |105| 
           MVKH    .S2     0x3fac718e,B9
           MVKH    .S2     0x714251b3,B8
           FADDDP  .L2X    B9:B8,A5:A4,B9:B8 ; |106| 
           ZERO    .L1     A30
           FADDDP  .L1X    A7:A6,B17:B16,A5:A4 ; |105| 
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |106| 
           ZERO    .L2     B8                ; |106| 
           FMPYDP  .M1X    B7:B6,A5:A4,A9:A8 ; |105| 
           SET     .S2     B31,0x15,0x1d,B9
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |106| 
           ZERO    .L1     A4                ; |67| 
           SET     .S1     A31,0x1e,0x1e,A5
           FSUBDP  .L2X    B5:B4,A9:A8,B7:B6 ; |106| 
           ZERO    .L1     A6                ; |67| 
           SET     .S1     A30,0x1e,0x1e,A7
           RCPDP   .S2     B7:B6,B9:B8       ; |67| 
           ZERO    .L2     B30
           FMPYDP  .M2     B7:B6,B9:B8,B5:B4 ; |67| 
           ZERO    .L1     A29
           MVK     .S2     0x3fe,B29
           NOP             2
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |67| 
           NOP             2
           FMPYDP  .M1X    B9:B8,A5:A4,A5:A4 ; |67| 
           NOP             3
           FMPYDP  .M1X    B7:B6,A5:A4,A17:A16 ; |67| 
           NOP             3
           FSUBDP  .L1     A7:A6,A17:A16,A7:A6 ; |67| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |67| 
           ZERO    .L1     A6                ; |120| 
           SET     .S1     A29,0x15,0x1d,A7
           NOP             2
           FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |67| 
           ZERO    .L2     B6                ; |67| 
           SET     .S2     B30,0x1e,0x1e,B7
           NOP             1
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |67| 
           NOP             3

           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |67| 
||         ZERO    .L2     B5:B4             ; |70| 

           NOP             1
           CMPEQDP .S1X    A9:A8,B5:B4,A0    ; |70| 

           ADD     .L2X    B29,A3,B4         ; |120| 
||         ADDAW   .D1     A15,3,A3

           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |67| 
           LDW     .D1T1   *A3,A3            ; |176| 
           SHL     .S2     B4,20,B5          ; |120| 
           ZERO    .L2     B4                ; |120| 

   [ A0]   ZERO    .L1     A5:A4             ; |71| 
||         SUB     .S1     A14,1,A0          ; |172| 
||         SUB     .D1     A14,1,A14         ; |172| 

           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |120| 
||         ZERO    .S1     A7
||         ZERO    .D1     A6                ; |120| 

           ADD     .L1     A12,A3,A3         ; |176| 
||         ADD     .S1     8,A12,A12         ; |172| 

           MVKH    .S1     0x40100000,A7

           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |120| 
||         MVKL    .S2     0x408633ce,B5

           MVKL    .S2     0x8fb9f87e,B4
           MVKH    .S2     0x408633ce,B5
           MVKH    .S2     0x8fb9f87e,B4
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |120| 
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1
           CMPGTDP .S2     B19:B18,B5:B4,B0  ; |220| 
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             2

   [ B0]   DADD    .L1     0,A11:A10,A5:A4   ; |221| 
|| [ A0]   B       .S1     $C$L11            ; |172| 

           FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |176| 
           NOP             3

   [!A0]   CALL    .S1     sinhdp_v          ; |178| 
||         STDW    .D1T1   A5:A4,*A3         ; |176| 

           ; BRANCHCC OCCURS {$C$L11}        ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *B10,B4           ; |178| 
           MV      .L1     A13,A4
           ADDKPC  .S2     $C$RL16,B3,1      ; |178| 
           MVK     .L1     0x8,A6            ; |178| 
$C$RL16:   ; CALL OCCURS {sinhdp_v} {0}      ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .L1     0x8,A4            ; |181| 

$C$RL17:   ; CALL OCCURS {allequal} {0}      ; |181| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x3,A4            ; |182| 

$C$RL18:   ; CALL OCCURS {print_test_results} {0}  ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

           MVKL    .S1     a_ext,A13
||         ZERO    .L2     B5

           MVKH    .S1     a_ext,A13
||         SET     .S2     B5,0x14,0x14,B5
||         MV      .L2X    A10,B4            ; |185| 

           STDW    .D1T2   B5:B4,*A13        ; |185| 
||         MVK     .S2     0x3c5,B4

           MV      .L1     A13,A12           ; |185| 

           MV      .L2X    A10,B11
||         CALL    .S1     sinh              ; |187| 
||         MV      .L1X    B4,A15            ; |185| 

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
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A12,A5:A4        ; |187| 
           ADDKPC  .S2     $C$RL19,B3,3      ; |187| 
$C$RL19:   ; CALL OCCURS {sinh} {0}          ; |187| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 28
           MVKL    .S1     output,A14
           MVKH    .S1     output,A14
           LDW     .D1T1   *A14,A3           ; |187| 
           NOP             4
           ADD     .L1X    B11,A3,A3         ; |187| 
           STDW    .D1T1   A5:A4,*A3         ; |187| 

           CALLP   .S2     sinhdp,B3
||         LDDW    .D1T1   *A12,A5:A4        ; |188| 

$C$RL20:   ; CALL OCCURS {sinhdp} {0}        ; |188| 
           LDW     .D1T1   *+A14(4),A3       ; |188| 
           NOP             4
           ADD     .L1X    B11,A3,A3         ; |188| 
           STDW    .D1T1   A5:A4,*A3         ; |188| 

           CALLP   .S2     sinhdp_c,B3
||         LDDW    .D1T1   *A12,A5:A4        ; |189| 

$C$RL21:   ; CALL OCCURS {sinhdp_c} {0}      ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           LDW     .D1T1   *+A14(8),A3       ; |189| 
           ZERO    .L2     B6                ; |207| 
           ZERO    .L2     B7
           MVKH    .S2     0x40390000,B7
           NOP             1
           ADD     .L2X    B11,A3,B4         ; |189| 
           STDW    .D2T1   A5:A4,*B4         ; |189| 
           LDDW    .D1T2   *A12,B5:B4        ; |200| 
           ZERO    .L1     A5:A4             ; |203| 
           NOP             3

           ABSDP   .S2     B5:B4,B19:B18     ; |200| 
||         CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |203| 

           ZERO    .L2     B5

           CMPGTDP .S2     B19:B18,B7:B6,B0  ; |207| 
|| [ A0]   ZERO    .L1     A19
|| [!A0]   ZERO    .S1     A19
|| [ A0]   ZERO    .D1     A18               ; |203| 

   [!A0]   SET     .S1     A19,0x14,0x1d,A19
|| [!A0]   ZERO    .L1     A18               ; |203| 

   [ B0]   B       .S1     $C$L18            ; |207| 
|| [!B0]   ZERO    .L2     B4                ; |211| 
||         SET     .S2     B5,0x14,0x1d,B5
||         MV      .D2     B0,B1             ; guard predicate rewrite

           MV      .L2     B0,B2             ; branch predicate copy
||         CMPGTDP .S2     B19:B18,B5:B4,B0  ; |211| 

   [ A0]   MVKH    .S1     0xbff00000,A19

   [ B1]   MVK     .L2     0x1,B0            ; |211| nullify predicate
|| [ B2]   MVKL    .S2     0xfefa39ec,B4

   [ B2]   MVKL    .S2     0x3fe62e42,B5

   [!B0]   B       .S1     $C$L17            ; |211| 
|| [ B2]   MVKH    .S2     0xfefa39ec,B4

           ; BRANCHCC OCCURS {$C$L18}        ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

   [!B0]   FMPYDP  .M2     B19:B18,B19:B18,B5:B4 ; |167| 
|| [!B0]   MVKL    .S1     0x3ec71de3,A5
|| [ B0]   CALL    .S2     expdp_sinhdp_i    ; |215| 

   [!B0]   MVKL    .S1     0xa556c736,A4
   [!B0]   MVKH    .S1     0x3ec71de3,A5
   [!B0]   MVKH    .S1     0xa556c736,A4
   [!B0]   FMPYDP  .M2     B5:B4,B5:B4,B17:B16 ; |167| 
           ; BRANCHCC OCCURS {$C$L17}        ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           DADD    .L1X    0,B19:B18,A5:A4   ; |215| 
||         ADDKPC  .S2     $C$RL22,B3,0      ; |215| 

$C$RL22:   ; CALL OCCURS {expdp_sinhdp_i} {0}  ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 41
           RCPDP   .S1     A5:A4,A7:A6       ; |217| 
           ZERO    .L1     A16               ; |217| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           ZERO    .L1     A17
           SET     .S1     A17,0x1e,0x1e,A17
           ZERO    .L2     B4                ; |217| 
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |217| 
           MV      .L2X    A17,B5            ; |217| 
           ZERO    .L2     B8                ; |217| 
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |217| 
           SUB     .L1     A15,1,A0          ; |186| 
           MV      .L2X    A17,B9            ; |217| 
           ZERO    .L1     A31
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           SUB     .L1     A15,1,A15         ; |186| 
           NOP             3
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |217| 
           NOP             2
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |217| 
           NOP             3
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |217| 
           NOP             3
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |217| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |217| 
           MVK     .S2     12,B6
           ADD     .L2X    A14,B6,B6
           BNOP    .S1     $C$L19,1          ; |217| 

           FSUBDP  .L1X    A5:A4,B5:B4,A7:A6 ; |217| 
||         SET     .S1     A31,0x15,0x1d,A5
||         ZERO    .D1     A4                ; |217| 
||         MVKL    .S2     0x8fb9f87e,B4

           MVKL    .S2     0x408633ce,B5
           MVKH    .S2     0x8fb9f87e,B4

           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |217| 
||         MVKL    .S1     0xcccccccd,A6
||         MVKH    .S2     0x408633ce,B5

           ; BRANCH OCCURS {$C$L19}          ; |217| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 31

           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |167| 
||         MVKL    .S2     0x3f2a01a0,B23
||         MVKL    .S1     0x55555561,A6
||         SUB     .L1     A15,1,A0          ; |186| 

           MVKL    .S2     0x1a01a00b,B22
||         MVKL    .S1     0x3fc55555,A7

           MVKH    .S2     0x3f2a01a0,B23
||         MVKH    .S1     0x55555561,A6

           FMPYDP  .M2     B5:B4,B17:B16,B7:B6 ; |167| 
||         MVKH    .S2     0x1a01a00b,B22
||         MVKH    .S1     0x3fc55555,A7

           MVKL    .S2     0x3de61246,B9
||         MVKL    .S1     0x3e5ae645,A17
||         FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |167| 

           MVKL    .S2     0x13a86d04,B8
||         MVKL    .S1     0x67f544de,A16
||         FADDDP  .L1X    B23:B22,A5:A4,A9:A8 ; |167| 

           MVKH    .S2     0x3de61246,B9
||         MVKH    .S1     0x3e5ae645,A17

           MVKH    .S2     0x13a86d04,B8
||         MVKH    .S1     0x67f544de,A16

           MVKL    .S2     0x3f811111,B21
||         FMPYDP  .M2     B9:B8,B7:B6,B9:B8 ; |167| 
||         FMPYDP  .M1X    A17:A16,B17:B16,A5:A4 ; |167| 

           MVKL    .S2     0x1111110f,B20
           MVKH    .S2     0x3f811111,B21
           MVKH    .S2     0x1111110f,B20
           FMPYDP  .M2     B21:B20,B17:B16,B5:B4 ; |167| 
           SUB     .L1     A15,1,A15         ; |186| 
           FADDDP  .L1X    B9:B8,A5:A4,A5:A4 ; |167| 
           FMPYDP  .M2X    B7:B6,A9:A8,B17:B16 ; |167| 
           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |167| 
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |167| 
           MVKL    .S1     0xcccccccd,A6
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |167| 
           MVK     .S2     12,B6
           MVKL    .S1     0xc000cccc,A7
           ADD     .L2X    A14,B6,B6

           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |167| 
||         MVKL    .S2     0x8fb9f87e,B4

           MVKL    .S2     0x408633ce,B5

           B       .S1     $C$L20            ; |167| 
||         MVKH    .S2     0x8fb9f87e,B4

           FMPYDP  .M1X    B19:B18,A5:A4,A5:A4 ; |167| 
||         MVKH    .S2     0x408633ce,B5

           CMPGTDP .S2     B19:B18,B5:B4,B0  ; |220| 
||         LDW     .D2T2   *B6,B4            ; |190| 

           MVKH    .S1     0xcccccccd,A6
           MVKH    .S1     0xc000cccc,A7
           FADDDP  .L1X    B19:B18,A5:A4,A5:A4 ; |167| 
           ; BRANCH OCCURS {$C$L20}          ; |167| 
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 107

           MVKH    .S2     0x3fe62e42,B5
||         MVKL    .S1     0x652b82fe,A4

           FSUBDP  .L2     B19:B18,B5:B4,B5:B4 ; |100| 
           MVKL    .S1     0x3ff71547,A5
           MVKH    .S1     0x652b82fe,A4
           MVKH    .S1     0x3ff71547,A5
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |100| 
           ZERO    .L2     B31
           ZERO    .L1     A6                ; |105| 
           MVKL    .S2     0xbf2bd010,B7
           DPINT   .L1     A5:A4,A3          ; |100| 
           MVKL    .S2     0x5c610ca8,B6
           MVKH    .S2     0xbf2bd010,B7
           MVKH    .S2     0x5c610ca8,B6
           INTDP   .L1     A3,A5:A4          ; |105| 
           MVKL    .S1     0x3fe63000,A7
           MVKL    .S2     0x6fb3f6e0,B16
           MVKH    .S1     0x3fe63000,A7
           MVKL    .S2     0x3f7c70e4,B17
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |105| 
           MVKH    .S2     0x6fb3f6e0,B16
           MVKH    .S2     0x3f7c70e4,B17
           FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |105| 
           MVKL    .S2     0x3fac718e,B21
           FSUBDP  .L2X    B5:B4,A7:A6,B5:B4 ; |105| 
           MVKL    .S2     0x714251b3,B20
           MVKL    .S1     0x3ef152a4,A5
           FSUBDP  .L2     B5:B4,B7:B6,B7:B6 ; |105| 
           MVKL    .S1     0x6f58dc1c,A4
           MVKH    .S1     0x3ef152a4,A5
           FMPYDP  .M2     B7:B6,B7:B6,B9:B8 ; |105| 
           MVKH    .S1     0x6f58dc1c,A4
           MVKH    .S2     0x3fac718e,B21
           MVKH    .S2     0x714251b3,B20

           FMPYDP  .M2X    A5:A4,B9:B8,B5:B4 ; |105| 
||         MVKL    .S1     0x3f403f99,A5

           MVKL    .S1     0x6fde3809,A4
           MVKH    .S1     0x3f403f99,A5
           MVKH    .S1     0x6fde3809,A4
           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |105| 
           FMPYDP  .M1X    A5:A4,B9:B8,A5:A4 ; |106| 
           ZERO    .L1     A6                ; |105| 
           FMPYDP  .M2     B9:B8,B5:B4,B17:B16 ; |105| 
           ZERO    .L1     A7
           MVKH    .S1     0x3fd00000,A7
           FADDDP  .L2X    B21:B20,A5:A4,B5:B4 ; |106| 
           ZERO    .L1     A31
           FADDDP  .L1X    A7:A6,B17:B16,A5:A4 ; |105| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |106| 
           ZERO    .L2     B8                ; |106| 
           FMPYDP  .M1X    B7:B6,A5:A4,A7:A6 ; |105| 
           SET     .S2     B31,0x15,0x1d,B9
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |106| 
           ZERO    .L1     A4                ; |67| 
           SET     .S1     A31,0x1e,0x1e,A5
           FSUBDP  .L2X    B5:B4,A7:A6,B5:B4 ; |106| 
           ZERO    .L1     A16               ; |67| 
           ZERO    .L1     A17
           RCPDP   .S2     B5:B4,B7:B6       ; |67| 
           SET     .S1     A17,0x1e,0x1e,A17
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |67| 
           ZERO    .L1     A30
           MVK     .S2     0x3fe,B30
           NOP             2
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |67| 
           NOP             2
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |67| 
           ZERO    .L2     B6                ; |67| 
           MV      .L2X    A17,B7            ; |67| 
           NOP             1
           FMPYDP  .M1X    B5:B4,A5:A4,A9:A8 ; |67| 
           NOP             3
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |67| 
           NOP             2
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |67| 
           ZERO    .L1     A8                ; |120| 
           SET     .S1     A30,0x15,0x1d,A9
           NOP             2
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |67| 
           NOP             3
           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |67| 
           MVK     .S2     12,B6
           ADD     .S2X    A14,B6,B6
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |67| 
           ZERO    .L2     B5:B4             ; |70| 
           NOP             1
           CMPEQDP .S1X    A7:A6,B5:B4,A0    ; |70| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |67| 
           ADD     .L2X    B30,A3,B4         ; |120| 
           SHL     .S2     B4,20,B5          ; |120| 
           ZERO    .L2     B4                ; |120| 
   [ A0]   ZERO    .L1     A5:A4             ; |71| 
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |120| 
           SUB     .L1     A15,1,A0          ; |186| 
           SUB     .S1     A15,1,A15         ; |186| 

           FMPYDP  .M1X    B5:B4,A5:A4,A7:A6 ; |120| 
||         ZERO    .L1     A5
||         ZERO    .S1     A4                ; |120| 
||         MVKL    .S2     0x408633ce,B5

           MVKH    .S1     0x40100000,A5
||         MVKL    .S2     0x8fb9f87e,B4

           MVKH    .S2     0x408633ce,B5
           MVKH    .S2     0x8fb9f87e,B4

           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |120| 
||         MVKL    .S1     0xcccccccd,A6

;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 4

           CMPGTDP .S2     B19:B18,B5:B4,B0  ; |220| 
||         LDW     .D2T2   *B6,B4            ; |190| 

           MVKL    .S1     0xc000cccc,A7
           MVKH    .S1     0xc000cccc,A7
           MVKH    .S1     0xcccccccd,A6
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 18
           NOP             2
   [ B0]   DADD    .L1     0,A11:A10,A5:A4   ; |221| 
           FMPYDP  .M1     A19:A18,A5:A4,A5:A4 ; |190| 
           ADD     .L2     B11,B4,B4         ; |190| 
           ADD     .L2     8,B11,B11         ; |186| 
           NOP             1
           STDW    .D2T1   A5:A4,*B4         ; |190| 
           LDDW    .D1T1   *A12,A5:A4        ; |191| 
           NOP             3
   [ A0]   B       .S1     $C$L16            ; |186| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |191| 
           NOP             3

   [ A0]   CALL    .S1     sinh              ; |187| 
||         STDW    .D1T1   A5:A4,*++A12      ; |191| 

           ; BRANCHCC OCCURS {$C$L16}        ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     sinhdp_v          ; |193| 
           LDW     .D2T2   *B10,B4           ; |193| 
           ADDKPC  .S2     $C$RL23,B3,2      ; |193| 

           MV      .L1     A13,A4
||         MVK     .S1     0x3c5,A6          ; |193| 

$C$RL23:   ; CALL OCCURS {sinhdp_v} {0}      ; |193| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0x3c5,A4          ; |196| 

$C$RL24:   ; CALL OCCURS {allequal} {0}      ; |196| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x4,A4            ; |197| 

$C$RL25:   ; CALL OCCURS {print_test_results} {0}  ; |197| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         MV      .L2X    A10,B4            ; |114| 
||         MV      .L1     A10,A12           ; |114| 
||         MV      .D1     A10,A13           ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A13:A12,*A3       ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           MVC     .S2     TSCL,B6           ; |117| 
||         STDW    .D1T2   B5:B4,*A3         ; |116| 

           MVC     .S2     TSCH,B7           ; |117| 

           MVKL    .S1     t_offset,A3
||         SUBU    .L2     B6,B4,B9:B8       ; |117| 

           CALL    .S1     gimme_random      ; |207| 
||         EXT     .S2     B9,24,24,B6       ; |117| 
||         SUB     .L2     B7,B5,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MV      .S2     B8,B4             ; |117| 
||         MVKH    .S1     t_offset,A3

           MVK     .S1     0x80,A3
||         STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MV      .L2X    A10,B12

           MV      .L2X    A10,B4            ; |207| 
||         MVKL    .S2     0xc0863000,B5
||         MVKL    .S1     0x40963000,A5

           MV      .L2X    A3,B11            ; |117| 
||         MVKH    .S2     0xc0863000,B5
||         MVKH    .S1     0x40963000,A5
||         MV      .L1     A12,A4            ; |207| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL26,B3,0      ; |207| 
$C$RL26:   ; CALL OCCURS {gimme_random} {0}  ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |207| 
           NOP             4
           ADD     .L2X    B12,A3,B4         ; |207| 

           STDW    .D2T1   A5:A4,*B4         ; |207| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A18            ; |122| Define a twin register
||         MVC     .S2     TSCH,B4           ; |122| 

           ABSDP   .S1     A5:A4,A21:A20     ; |200| 
||         ZERO    .L2     B7
||         ZERO    .S2     B6                ; |207| 
||         ZERO    .L1     A7:A6             ; |203| 

           MVKH    .S2     0x40390000,B7
||         CMPLTDP .S1     A5:A4,A7:A6,A0    ; |203| 

           ZERO    .L1     A5

           CMPGTDP .S2X    A21:A20,B7:B6,B0  ; |207| 
|| [ A0]   ZERO    .L1     A23
|| [!A0]   ZERO    .D1     A23
||         SET     .S1     A5,0x14,0x1d,A5

   [!A0]   SET     .S1     A23,0x14,0x1d,A23
|| [ A0]   ZERO    .L1     A22               ; |203| 
|| [!A0]   ZERO    .D1     A22               ; |203| 

   [!B0]   ZERO    .L1     A4                ; |211| 
|| [ B0]   B       .S2     $C$L23            ; |207| 
|| [ A0]   MVKH    .S1     0xbff00000,A23

           CMPGTDP .S1     A21:A20,A5:A4,A0  ; |211| 
           MV      .L1X    B4,A19            ; |122| 

   [ B0]   MVK     .L1     0x1,A0            ; |211| nullify predicate
||         MVKL    .S1     0xfefa39ec,A4

   [!A0]   B       .S2     $C$L22            ; |211| 
||         MVKL    .S1     0x3fe62e42,A5

           MVKH    .S1     0x3fe62e42,A5
           ; BRANCHCC OCCURS {$C$L23}        ; |207| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

   [ A0]   CALL    .S1     expdp_sinhdp_i    ; |215| 
|| [!A0]   FMPYDP  .M1     A21:A20,A21:A20,A5:A4 ; |167| 

           NOP             3
           ; BRANCHCC OCCURS {$C$L22}        ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL27,B3,0      ; |215| 
           DADD    .L1     0,A21:A20,A5:A4   ; |215| 
$C$RL27:   ; CALL OCCURS {expdp_sinhdp_i} {0}  ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 41
           RCPDP   .S1     A5:A4,A7:A6       ; |217| 
           ZERO    .L1     A16               ; |217| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           ZERO    .L1     A17
           SET     .S1     A17,0x1e,0x1e,A17
           ZERO    .L2     B4                ; |217| 
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |217| 
           MV      .L2X    A17,B5            ; |217| 
           ZERO    .L2     B8                ; |217| 
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |217| 
           ZERO    .L1     A31
           MVKL    .S1     t_start,A3
           MV      .L2X    A17,B9            ; |217| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |217| 
           MVKH    .S1     t_start,A3
           STDW    .D1T1   A19:A18,*A3
           NOP             2
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |217| 
           NOP             2
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |217| 
           NOP             3
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |217| 
           NOP             3
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |217| 
           NOP             2

           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |217| 
||         MVK     .S2     12,B6

           ADD     .L2X    A14,B6,B6
           LDW     .D2T2   *B6,B31           ; |211| 
           BNOP    .S1     $C$L24,1          ; |217| 

           FSUBDP  .L1X    A5:A4,B5:B4,A7:A6 ; |217| 
||         SET     .S1     A31,0x15,0x1d,A5
||         ZERO    .D1     A4                ; |217| 
||         MVKL    .S2     0x408633ce,B5

           MVKL    .S2     0x8fb9f87e,B4
           MVKH    .S2     0x408633ce,B5

           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |217| 
||         MVKH    .S2     0x8fb9f87e,B4

           ; BRANCH OCCURS {$C$L24}          ; |217| 
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 32

           FMPYDP  .M1     A5:A4,A5:A4,A17:A16 ; |167| 
||         MVKL    .S2     0xa556c736,B4
||         MVKL    .S1     0x3de61246,A7

           MVKL    .S2     0x3ec71de3,B5
||         MVKL    .S1     0x13a86d04,A6

           MVKH    .S2     0xa556c736,B4
||         MVKH    .S1     0x3de61246,A7

           MVKH    .S2     0x3ec71de3,B5
||         MVKH    .S1     0x13a86d04,A6

           FMPYDP  .M1     A5:A4,A17:A16,A9:A8 ; |167| 
||         FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |167| 
||         MVKL    .S2     0x3fc55555,B7
||         MVKL    .S1     0x1a01a00b,A26

           MVKL    .S2     0x55555561,B6
||         MVKL    .S1     0x3f2a01a0,A27

           MVKH    .S2     0x3fc55555,B7
||         MVKH    .S1     0x1a01a00b,A26

           MVKH    .S2     0x55555561,B6
||         MVKH    .S1     0x3f2a01a0,A27

           MVKL    .S2     0x67f544de,B8
||         FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |167| 
||         FMPYDP  .M1     A7:A6,A9:A8,A5:A4 ; |167| 
||         MVKL    .S1     0x1111110f,A24

           MVKL    .S2     0x3e5ae645,B9
||         MVKL    .S1     0x3f811111,A25

           MVKH    .S2     0x67f544de,B8
||         MVKH    .S1     0x1111110f,A24

           MVKH    .S2     0x3e5ae645,B9
||         MVKH    .S1     0x3f811111,A25

           MVKL    .S1     t_start,A3
||         FMPYDP  .M2X    B9:B8,A17:A16,B17:B16 ; |167| 

           FADDDP  .L2X    A27:A26,B5:B4,B9:B8 ; |167| 
           FMPYDP  .M1     A25:A24,A17:A16,A7:A6 ; |167| 
           MVKH    .S1     t_start,A3
           FADDDP  .L2X    A5:A4,B17:B16,B5:B4 ; |167| 
           FMPYDP  .M1X    A9:A8,B9:B8,A5:A4 ; |167| 
           FADDDP  .L1X    A7:A6,B7:B6,A7:A6 ; |167| 
           FMPYDP  .M2X    A9:A8,B5:B4,B5:B4 ; |167| 
           MVK     .S2     12,B6
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |167| 
           ADD     .L2X    A14,B6,B6
           LDW     .D2T2   *B6,B31           ; |211| 

           FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |167| 
||         MVKL    .S2     0x408633ce,B5

           MVKL    .S2     0x8fb9f87e,B4

           B       .S1     $C$L25            ; |167| 
||         MVKH    .S2     0x408633ce,B5

           FMPYDP  .M1     A21:A20,A5:A4,A5:A4 ; |167| 
||         MVKH    .S2     0x8fb9f87e,B4

           STDW    .D1T1   A19:A18,*A3
           CMPGTDP .S1X    A21:A20,B5:B4,A0  ; |220| 
           ADD     .L2     B12,B31,B4        ; |211| 
           FADDDP  .L1     A21:A20,A5:A4,A5:A4 ; |167| 
           ; BRANCH OCCURS {$C$L25}          ; |167| 
;** --------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 111

           MVKH    .S1     0xfefa39ec,A4
||         MVKL    .S2     0x652b82fe,B4

           FSUBDP  .L1     A21:A20,A5:A4,A5:A4 ; |100| 
           MVKL    .S2     0x3ff71547,B5
           MVKH    .S2     0x652b82fe,B4
           MVKH    .S2     0x3ff71547,B5
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |100| 
           ZERO    .L1     A31
           ZERO    .L2     B6                ; |105| 
           MVKL    .S1     0x5c610ca8,A6
           DPINT   .L2     B5:B4,B16         ; |100| 
           MVKL    .S1     0xbf2bd010,A7
           MVKH    .S1     0x5c610ca8,A6
           MVKH    .S1     0xbf2bd010,A7
           INTDP   .L2     B16,B5:B4         ; |105| 
           MVKL    .S2     0x3fe63000,B7
           MVKH    .S2     0x3fe63000,B7
           MVKL    .S1     0x6fb3f6e0,A8
           MVKL    .S1     0x3f7c70e4,A9
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |105| 
           MVKH    .S1     0x6fb3f6e0,A8
           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |105| 
           MVKH    .S1     0x3f7c70e4,A9
           MVKL    .S2     0x3ef152a4,B5
           FSUBDP  .L1X    A5:A4,B7:B6,A5:A4 ; |105| 
           MVKL    .S2     0x6f58dc1c,B4
           MVKH    .S2     0x3ef152a4,B5
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |105| 
           MVKH    .S2     0x6f58dc1c,B4
           ZERO    .L2     B6                ; |105| 
           FMPYDP  .M1     A7:A6,A7:A6,A5:A4 ; |105| 
           ZERO    .L2     B7
           MVKH    .S2     0x3fd00000,B7
           ZERO    .L2     B31

           FMPYDP  .M1X    B5:B4,A5:A4,A17:A16 ; |105| 
||         MVKL    .S2     0x3f403f99,B5

           MVKL    .S2     0x6fde3809,B4
           MVKH    .S2     0x3f403f99,B5
           MVKH    .S2     0x6fde3809,B4

           MVKL    .S1     0x714251b3,A8
||         FADDDP  .L1     A9:A8,A17:A16,A17:A16 ; |105| 

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |106| 
           MVKL    .S1     0x3fac718e,A9
           FMPYDP  .M1     A5:A4,A17:A16,A17:A16 ; |105| 
           MVKH    .S1     0x714251b3,A8
           MVKH    .S1     0x3fac718e,A9
           FADDDP  .L1X    A9:A8,B5:B4,A9:A8 ; |106| 
           ZERO    .L2     B18               ; |67| 
           FADDDP  .L2X    B7:B6,A17:A16,B5:B4 ; |105| 
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |106| 
           ZERO    .L1     A4                ; |106| 
           FMPYDP  .M2X    A7:A6,B5:B4,B9:B8 ; |105| 
           SET     .S1     A31,0x15,0x1d,A5
           FADDDP  .L1     A5:A4,A9:A8,A5:A4 ; |106| 
           ZERO    .L2     B4                ; |67| 
           SET     .S2     B31,0x1e,0x1e,B5
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |106| 
           ZERO    .L2     B19
           SET     .S2     B19,0x1e,0x1e,B19
           RCPDP   .S1     A5:A4,A7:A6       ; |67| 
           ZERO    .L2     B30
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |67| 
           MVK     .S1     0x3fe,A3
           ADD     .L1X    A3,B16,A3         ; |120| 
           NOP             2
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |67| 
           NOP             2
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |67| 
           ZERO    .L1     A6                ; |67| 
           MV      .L1X    B19,A7            ; |67| 
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |67| 
           NOP             3
           FSUBDP  .L2     B19:B18,B7:B6,B7:B6 ; |67| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |67| 
           ZERO    .L2     B6                ; |120| 
           SET     .S2     B30,0x15,0x1d,B7
           NOP             2
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |67| 
           NOP             3
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |67| 
           NOP             3

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |67| 
||         ZERO    .L1     A5:A4             ; |70| 

           NOP             1
           CMPEQDP .S2X    B9:B8,A5:A4,B0    ; |70| 
           ZERO    .L1     A4                ; |120| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |67| 
           SHL     .S1     A3,20,A5          ; |120| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3
   [ B0]   ZERO    .L2     B5:B4             ; |71| 
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |120| 
           STDW    .D1T1   A19:A18,*A3
           MVK     .S2     12,B6
           ADD     .L2X    A14,B6,B6

           ZERO    .L2     B4                ; |120| 
||         FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |120| 

           ZERO    .L2     B5
           MVKH    .S2     0x40100000,B5
           LDW     .D2T2   *B6,B31           ; |211| 

           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |120| 
||         MVKL    .S2     0x408633ce,B5

           MVKL    .S2     0x8fb9f87e,B4
           MVKH    .S2     0x408633ce,B5
           MVKH    .S2     0x8fb9f87e,B4
;** --------------------------------------------------------------------------*
$C$L24:    
;          EXCLUSIVE CPU CYCLES: 3
           NOP             1
           CMPGTDP .S1X    A21:A20,B5:B4,A0  ; |220| 
           ADD     .L2     B12,B31,B4        ; |211| 
;** --------------------------------------------------------------------------*
$C$L25:    
;          EXCLUSIVE CPU CYCLES: 24
           NOP             2
   [ A0]   DADD    .L1     0,A11:A10,A5:A4   ; |221| 
           FMPYDP  .M1     A23:A22,A5:A4,A5:A4 ; |211| 
           NOP             3

           STDW    .D2T1   A5:A4,*B4         ; |211| 
||         MVC     .S2     TSCL,B6           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A3
||         MVKL    .S2     cycle_counts+24,B5
||         MV      .L2     B4,B7             ; |128| 
||         SUB     .L1X    B11,1,A0          ; |205| 
||         ADD     .D2     8,B12,B12         ; |205| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     cycle_counts+24,B5
||         SUB     .L2     B11,1,B11         ; |205| 

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B5,B5:B4         ; |130| 
||         MVKL    .S1     cycle_counts+24,A15

           MVKL    .S1     t_stop,A31
           MVKH    .S1     t_stop,A31
           STDW    .D1T2   B7:B6,*A31        ; |128| 
           MVKH    .S1     cycle_counts+24,A15
           ADDU    .L1     A6,A18,A5:A4      ; |130| 
           ADD     .L1     A5,A7,A5          ; |130| 

           SUBU    .L2X    B6,A4,B9:B8       ; |130| 
||         ADD     .L1     A5,A19,A4         ; |130| 
|| [ A0]   B       .S2     $C$L21            ; |205| 
|| [ A0]   MVKL    .S1     0x40963000,A5

   [ A0]   CALL    .S1     gimme_random      ; |207| 
||         EXT     .S2     B9,24,24,B16      ; |130| 
||         ADDU    .L2     B4,B8,B9:B8       ; |130| 

           SUB     .L2X    B7,A4,B4          ; |130| 
|| [ A0]   MV      .L1     A12,A4            ; |207| 
|| [ A0]   MVKH    .S1     0x40963000,A5

           ADD     .L2     B9,B5,B4          ; |130| 
||         ADD     .S2     B4,B16,B5         ; |130| 

           ADD     .L2     B4,B5,B9          ; |130| 
|| [ A0]   MVKL    .S2     0xc0863000,B5
|| [ A0]   MV      .D2X    A10,B4            ; |207| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T2   B9:B8,*A15        ; |130| 
|| [ A0]   MVKH    .S2     0xc0863000,B5

           ; BRANCHCC OCCURS {$C$L21}        ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A15,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL28,B3,3      ; |135| 
$C$RL28:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A11
           SET     .S1     A11,0x15,0x1d,A11
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL29:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MV      .L2X    A15,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           SUBAW   .D2     B4,6,B5
||         MV      .L2X    A10,B31           ; |114| 

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T1   A13:A12,*B5       ; |114| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B7           ; |117| 
           MVC     .S2     TSCH,B6           ; |117| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3

           SUBU    .L2     B7,B5,B9:B8       ; |117| 
||         MV      .L1     A14,A4            ; |117| 
||         MVKL    .S1     t_offset,A31

           EXT     .S2     B9,24,24,B5       ; |117| 
||         MV      .L2X    A3,B16
||         LDW     .D1T1   *A4,A10
||         SUB     .D2     B6,B4,B4          ; |117| 
||         MVK     .S1     0x80,A30

           ADD     .L2     B4,B5,B9          ; |117| 
||         LDW     .D2T1   *B16,A14
||         MVKH    .S1     t_offset,A31

           STDW    .D1T2   B9:B8,*A31        ; |117| 
||         MV      .L1     A30,A15           ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L26:    
;          EXCLUSIVE CPU CYCLES: 8
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           CALL    .S1     sinh              ; |220| 
           LDDW    .D1T1   *A14++,A5:A4      ; |220| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           ADDKPC  .S2     $C$RL30,B3,0      ; |220| 
$C$RL30:   ; CALL OCCURS {sinh} {0}          ; |220| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20

           STDW    .D1T1   A5:A4,*A10++      ; |220| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_start,A3
||         MVKL    .S2     t_offset,B11
||         SUB     .L1     A15,1,A0          ; |218| 
||         MV      .L2     B4,B9             ; |128| 
||         SUB     .D1     A15,1,A15         ; |218| 

           MVKH    .S1     t_start,A3
||         MVKH    .S2     t_offset,B11

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 
||         MVKL    .S1     cycle_counts,A31
||         MVKL    .S2     cycle_counts,B4

           MVKH    .S1     cycle_counts,A31
||         MVKH    .S2     cycle_counts,B4

           MVKL    .S1     t_stop,A30

           MVKH    .S1     t_stop,A30
|| [!A0]   MV      .L1X    B4,A14

           STDW    .D1T2   B9:B8,*A30        ; |128| 
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
           ADD     .L1X    A5,B7,A6          ; |130| 

           SUBU    .L2X    B8,A4,B7:B6       ; |130| 
||         LDDW    .D1T1   *A31,A5:A4        ; |130| 
||         ADD     .L1     A6,A7,A6          ; |130| 

           MV      .L2     B6,B5             ; |130| 
||         EXT     .S2     B7,24,24,B6       ; |130| 

           SUB     .L2X    B9,A6,B31         ; |130| 

   [ A0]   BNOP    .S1     $C$L26,1          ; |218| 
||         ADD     .L2     B31,B6,B6         ; |130| 

           ADDU    .L2X    A4,B5,B17:B16     ; |130| 
           ADD     .L2X    B17,A5,B5         ; |130| 
           ADD     .L2     B5,B6,B17         ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B17:B16,*B4       ; |130| 

           ; BRANCHCC OCCURS {$C$L26}        ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL31,B3,3      ; |135| 
$C$RL31:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A12,A10           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL32:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A13:A12,*+A14(16) ; |114| 
||         MV      .L2X    A13,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A14        ; |135| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B8,B4,B4          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B4,B5,B7          ; |117| 

           MV      .L2X    A3,B11            ; |117| 
||         STDW    .D2T2   B7:B6,*B11        ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L27:    
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

           ADD     .L1     A10,A3,A3         ; |229| 
||         CALL    .S1     sinhdp_c          ; |229| 

           LDDW    .D1T1   *A3,A5:A4         ; |229| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |229| 
$C$RL33:   ; CALL OCCURS {sinhdp_c} {0}      ; |229| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+8,B4
           MVKH    .S2     output+8,B4
           LDW     .D2T2   *B4,B4            ; |229| 
           NOP             4
           ADD     .L1X    A10,B4,A3         ; |229| 

           STDW    .D1T1   A5:A4,*A3         ; |229| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A15
||         MVKL    .S2     t_start,B5
||         ADDAD   .D1     A14,2,A3
||         SUB     .L1X    B11,1,A0          ; |227| 
||         MV      .L2     B4,B17            ; |128| 
||         SUB     .D2     B11,1,B11         ; |227| 

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

   [ A0]   B       .S1     $C$L27            ; |227| 
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
||         ADD     .L1     8,A10,A10         ; |227| 

           ; BRANCHCC OCCURS {$C$L27}        ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(16),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |135| 
$C$RL34:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A12,A10           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL35:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           MV      .L1     A14,A3            ; |135| 
||         STDW    .D2T1   A5:A4,*B12        ; |135| 
||         MV      .L2X    A13,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A13:A12,*+A3(8)   ; |114| 

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
$C$L28:    
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

           ADD     .L1     A10,A3,A3         ; |238| 
||         CALL    .S1     sinhdp            ; |238| 

           LDDW    .D1T1   *A3,A5:A4         ; |238| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |238| 
$C$RL36:   ; CALL OCCURS {sinhdp} {0}        ; |238| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+4,B4
           MVKH    .S2     output+4,B4
           LDW     .D2T2   *B4,B4            ; |238| 
           NOP             4
           ADD     .L1X    A10,B4,A3         ; |238| 

           STDW    .D1T1   A5:A4,*A3         ; |238| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     t_start,B12
||         MVKL    .S1     t_offset,A14
||         SUB     .L1X    B11,1,A0          ; |236| 
||         MV      .L2     B4,B17            ; |128| 
||         ADD     .D1     8,A10,A10         ; |236| 
||         SUB     .D2     B11,1,B11         ; |236| 

           MVKH    .S2     t_start,B12
||         MVKH    .S1     t_offset,A14

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B9:B8        ; |130| 
||         MVKL    .S1     cycle_counts+8,A3

           MVKH    .S1     cycle_counts+8,A3

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     t_stop,A15

           MV      .L2X    A3,B13            ; |128| 
||         MVKH    .S1     t_stop,A15

   [!A0]   MVKL    .S1     cycle_counts,A3
||         STDW    .D1T2   B17:B16,*A15      ; |128| 

           ADDU    .L2X    A4,B8,B7:B6       ; |130| 
|| [!A0]   MVKH    .S1     cycle_counts,A3

           SUBU    .L2     B16,B6,B5:B4      ; |130| 
||         ADD     .S2X    B7,A5,B6          ; |130| 
|| [ A0]   B       .S1     $C$L28            ; |236| 

           ADD     .D2     B6,B9,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B6         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B13        ; |130| 

           ; BRANCHCC OCCURS {$C$L28}        ; |236| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(8),A5:A4     ; |135| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |135| 
$C$RL37:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 109
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A12,A10           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
           MV      .L1X    B13,A10           ; |135| 
           SUBAW   .D1     A10,2,A3

           MV      .L2X    A13,B4            ; |114| 
||         STDW    .D1T1   A5:A4,*A10        ; |135| 

           STDW    .D1T1   A13:A12,*+A3(32)  ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D2T2   B9:B8,*B12        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B7           ; |117| 

           MVKL    .S1     input,A3
||         SUBU    .L2     B4,B8,B5:B4       ; |117| 

           MVKH    .S1     input,A3
||         EXT     .S2     B5,24,24,B7       ; |117| 
||         SUB     .L2     B7,B9,B5          ; |117| 

           MVKL    .S1     output,A12
||         ADD     .L2     B5,B7,B5          ; |117| 

           MV      .L2X    A3,B6             ; |245| 
||         MVKH    .S1     output,A12
||         STDW    .D1T2   B5:B4,*A14        ; |117| 

           CALLP   .S2     sinhdp_v,B3
||         LDW     .D2T1   *B6,A4            ; |245| 
||         LDW     .D1T2   *+A12(16),B4      ; |245| 
||         MVK     .S1     0x80,A6           ; |245| 

$C$RL39:   ; CALL OCCURS {sinhdp_v} {0}      ; |245| 
           MVC     .S2     TSCL,B16          ; |128| 
           MVC     .S2     TSCH,B6           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B12,B5:B4        ; |130| 

           MVK     .S2     24,B11
           ADD     .L2X    A10,B11,B11
           MV      .L2     B6,B17            ; |128| 
           LDDW    .D2T2   *B11,B7:B6        ; |130| 
           ADDU    .L1X    A6,B4,A5:A4       ; |130| 
           ADD     .L1     A5,A7,A3          ; |130| 
           SUBU    .L1X    B16,A4,A5:A4      ; |130| 

           ADD     .L2X    A3,B5,B4          ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
||         SUB     .L2     B17,B4,B4         ; |130| 

           ADD     .L2X    B4,A3,B5          ; |130| 
           ADD     .L2X    A7,B7,B4          ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MV      .S2X    A6,B6             ; |130| 

           MV      .L2X    A15,B8            ; |128| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         STDW    .D2T2   B17:B16,*B8       ; |128| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1     A13,A10           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL41:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x812dea11,B6
           MVKL    .S2     0x3d719799,B7
           MVKH    .S2     0x812dea11,B6

           DADD    .L1     0,A5:A4,A7:A6     ; |130| 
||         LDW     .D1T1   *A12,A4           ; |66| 
||         MVKH    .S2     0x3d719799,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A12(4),B4       ; |66| 
||         STDW    .D2T1   A7:A6,*B11        ; |130| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL42:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x812dea11,B6
           MVKL    .S2     0x3d719799,B7

           LDW     .D1T2   *+A12(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A10
||         MVKH    .S2     0x812dea11,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A12,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A10
||         MVKH    .S2     0x3d719799,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A5,*+A10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL43:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3d719799,B7
           MVKL    .S2     0x812dea11,B6

           STW     .D1T1   A4,*+A10(8)       ; |67| 
||         MVKH    .S2     0x3d719799,B7

           LDW     .D1T2   *+A12(12),B4      ; |68| 
||         MVKH    .S2     0x812dea11,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3d719799,B7
           MVKL    .S2     0x812dea11,B6
           MVKH    .S2     0x3d719799,B7

           STW     .D1T1   A4,*+A10(12)      ; |68| 
||         MVKH    .S2     0x812dea11,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |69| 
||         LDW     .D2T2   *B10,B4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2X    4,A10,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D1T1   A4,*+A10(16)      ; |69| 
           ADD     .L2X    8,A10,B4
           NOP             2

   [!B0]   BNOP    .S1     $C$L29,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L29}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A13,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L30            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |251| 
   [ A0]   MVKL    .S1     all_pass,A3
   [ A0]   MVKH    .S1     all_pass,A3
           NOP             2
           ; BRANCHCC OCCURS {$C$L30}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L29:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |251| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           MV      .L1     A13,A4
           NOP             1
;** --------------------------------------------------------------------------*
$C$L30:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x2,A4            ; |251| 
||         ADDKPC  .S2     $C$RL46,B3,0      ; |251| 

$C$RL46:   ; CALL OCCURS {print_test_results} {0}  ; |251| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL47:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL48:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |259| 

$C$RL49:   ; CALL OCCURS {print_profile_results} {0}  ; |259| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |262| 

$C$RL50:   ; CALL OCCURS {print_memory_results} {0}  ; |262| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(16),B3      ; |263| 
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
$C$SL1:	.string	"sinhDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	sinh
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	sinhdp_c
	.global	sinhdp
	.global	sinhdp_v
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
