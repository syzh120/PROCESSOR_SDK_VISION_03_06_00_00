;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:30:40 2013                                *
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
	.word	040028220h,0436c665bh		; _a[0] @ 0
	.word	03ffe598bh,0dd18746bh		; _a[1] @ 64
	.word	0bfb35f8eh,00510e0f9h		; _a[2] @ 128
	.word	03fec60b0h,044000a11h		; _a[3] @ 192
	.word	0bfef5c9bh,0ac99509eh		; _a[4] @ 256
	.word	03fc761b8h,081bc2d42h		; _a[5] @ 320
	.word	0bff1d973h,0bf147d66h		; _a[6] @ 384
	.word	0bff0c5deh,09c0229a6h		; _a[7] @ 448
	.word	03ffa585fh,0577e6c17h		; _a[8] @ 512
	.word	0bfeba768h,08f359289h		; _a[9] @ 576
	.word	0bfeb4a43h,0bb40b34eh		; _a[10] @ 640
	.word	0bfff1efdh,000713f07h		; _a[11] @ 704
	.word	0c0051cb9h,0595281adh		; _a[12] @ 768
	.word	03fe0b5dbh,0841fb4d1h		; _a[13] @ 832
	.word	040069340h,033ccb627h		; _a[14] @ 896
	.word	0bfef61bah,09a9b2159h		; _a[15] @ 960
	.word	0c0091385h,0eec1ea1bh		; _a[16] @ 1024
	.word	0bffe81e3h,0d01e90e5h		; _a[17] @ 1088
	.word	0c002914dh,021f1c250h		; _a[18] @ 1152
	.word	03ff06f7eh,0f904633ch		; _a[19] @ 1216
	.word	04006962dh,040aaeafbh		; _a[20] @ 1280
	.word	040051cb9h,0595281adh		; _a[21] @ 1344
	.word	03ff20a53h,0fc0096ffh		; _a[22] @ 1408
	.word	03ff5978dh,0bb3f05cfh		; _a[23] @ 1472
	.word	0c0074d6eh,07d8c1cd9h		; _a[24] @ 1536
	.word	0bfff7163h,0f06a60c7h		; _a[25] @ 1600
	.word	0c004838ch,061a2b247h		; _a[26] @ 1664
	.word	03ffe47f7h,0b0a62599h		; _a[27] @ 1728
	.word	0c0027386h,0b81585a3h		; _a[28] @ 1792
	.word	0c0010d8eh,0f19feaech		; _a[29] @ 1856
	.word	03fdf14bah,036c8132ah		; _a[30] @ 1920
	.word	04005ffedh,0486d571bh		; _a[31] @ 1984
	.word	03ffeaddah,0638e44d2h		; _a[32] @ 2048
	.word	03ff508cch,0dd93c46eh		; _a[33] @ 2112
	.word	0c0063d2ah,0e8e1d649h		; _a[34] @ 2176
	.word	040020395h,058c238f5h		; _a[35] @ 2240
	.word	0bff14408h,0a33cb08ah		; _a[36] @ 2304
	.word	0bfddcddfh,086e3b470h		; _a[37] @ 2368
	.word	0bffee8b9h,041d58d66h		; _a[38] @ 2432
	.word	0c0087b0ch,0606092e8h		; _a[39] @ 2496
	.word	03ff6cfd5h,0b0a11d1ch		; _a[40] @ 2560
	.word	03fe99a2ch,09c403d07h		; _a[41] @ 2624
	.word	0bfef4ed9h,0b796daa2h		; _a[42] @ 2688
	.word	03fdf9515h,03afaa7d1h		; _a[43] @ 2752
	.word	03ff5e0d7h,02af4a050h		; _a[44] @ 2816
	.word	0bff00e16h,0433863f5h		; _a[45] @ 2880
	.word	03fe44389h,0572c36c0h		; _a[46] @ 2944
	.word	0bfd64439h,0ebb418a1h		; _a[47] @ 3008
	.word	03ff91268h,0b8503e06h		; _a[48] @ 3072
	.word	0bff21583h,01f03d146h		; _a[49] @ 3136
	.word	03ffaaf80h,055fbb518h		; _a[50] @ 3200
	.word	0bffce5c7h,0daf5847ch		; _a[51] @ 3264
	.word	040084399h,0e873f240h		; _a[52] @ 3328
	.word	0c007c609h,02110f1c0h		; _a[53] @ 3392
	.word	0bfed84aeh,0500a038fh		; _a[54] @ 3456
	.word	0bffc4a5ah,0e7ad22e3h		; _a[55] @ 3520
	.word	0bff3d878h,0ed51a793h		; _a[56] @ 3584
	.word	03fefb6cfh,09fe5e3f5h		; _a[57] @ 3648
	.word	03fe7344ch,0023711e5h		; _a[58] @ 3712
	.word	03fb10301h,03c40222fh		; _a[59] @ 3776
	.word	0bff3217fh,0e2386edch		; _a[60] @ 3840
	.word	0c0037b8ch,0fbfc6541h		; _a[61] @ 3904
	.word	03fb5c86ch,0ebbba55dh		; _a[62] @ 3968
	.word	04001ae3bh,0cd35a858h		; _a[63] @ 4032
	.word	0bff1724ah,0d5e727c2h		; _a[64] @ 4096
	.word	0c00842c6h,0ac215b9ah		; _a[65] @ 4160
	.word	03ff6512fh,082a48a8eh		; _a[66] @ 4224
	.word	03ff5ccbah,0f965b20ch		; _a[67] @ 4288
	.word	0bfe635b1h,092b4a30ah		; _a[68] @ 4352
	.word	03ff5ab51h,0017a5383h		; _a[69] @ 4416
	.word	03fec144dh,0ca8e2e2ch		; _a[70] @ 4480
	.word	0bff1de57h,038cbf968h		; _a[71] @ 4544
	.word	0bff8a2b9h,04d940789h		; _a[72] @ 4608
	.word	0bff75596h,019b258adh		; _a[73] @ 4672
	.word	0bfe76b66h,0b6177ea2h		; _a[74] @ 4736
	.word	03fdfbb2ah,078798e61h		; _a[75] @ 4800
	.word	0bfe33139h,0c94f69cbh		; _a[76] @ 4864
	.word	0bfd11ecdh,0b600d86dh		; _a[77] @ 4928
	.word	03ffdcf53h,0e051e4cfh		; _a[78] @ 4992
	.word	0c0022328h,02334b86eh		; _a[79] @ 5056
	.word	0c007dd9ah,00f0a5effh		; _a[80] @ 5120
	.word	03ffcac55h,093b04b8dh		; _a[81] @ 5184
	.word	0bfe01873h,0ffac1d2ah		; _a[82] @ 5248
	.word	0bfeea818h,0b85da9ffh		; _a[83] @ 5312
	.word	0c0074e5fh,06697e48eh		; _a[84] @ 5376
	.word	0bfca0063h,0d30e2f6eh		; _a[85] @ 5440
	.word	03fce9e92h,0fd9e25f0h		; _a[86] @ 5504
	.word	0bff45596h,0bac2084eh		; _a[87] @ 5568
	.word	0c005cf50h,05d0fa58fh		; _a[88] @ 5632
	.word	0bfd8e597h,0338dcc06h		; _a[89] @ 5696
	.word	0c0026bc1h,0d52205e4h		; _a[90] @ 5760
	.word	03ffbd526h,0a301f828h		; _a[91] @ 5824
	.word	0bfc60b5eh,0d8d36b4ch		; _a[92] @ 5888
	.word	0bfebba09h,07ba9c48ah		; _a[93] @ 5952
	.word	0400583d1h,06e1c3d4dh		; _a[94] @ 6016
	.word	0bff4ba83h,0a464ceb7h		; _a[95] @ 6080
	.word	0bff1d3a6h,05569bee0h		; _a[96] @ 6144
	.word	03fe4e140h,021583f5ch		; _a[97] @ 6208
	.word	0bff00eddh,07df4f865h		; _a[98] @ 6272
	.word	0c0044605h,0fbc2839eh		; _a[99] @ 6336
	.word	0bfe34c64h,0fdb09a67h		; _a[100] @ 6400
	.word	0bff7c0e3h,0c02e58d9h		; _a[101] @ 6464
	.word	03fc7a447h,07285589ah		; _a[102] @ 6528
	.word	0c0026037h,085a84b0dh		; _a[103] @ 6592
	.word	0bffba788h,00445dfdeh		; _a[104] @ 6656
	.word	0c001562fh,0fa998eb2h		; _a[105] @ 6720
	.word	0bfed5201h,05493d60bh		; _a[106] @ 6784
	.word	0c00588efh,04fae93fdh		; _a[107] @ 6848
	.word	0c008bdd3h,0bafd9770h		; _a[108] @ 6912
	.word	03ffe716ch,0bf45fb8dh		; _a[109] @ 6976
	.word	0bfe3b48fh,01e1594bdh		; _a[110] @ 7040
	.word	0bff377afh,02e5654a0h		; _a[111] @ 7104
	.word	03ff4ff0ch,0a0217317h		; _a[112] @ 7168
	.word	0bfcf0e64h,046d175a9h		; _a[113] @ 7232
	.word	04007e892h,0c640c191h		; _a[114] @ 7296
	.word	0400658d0h,0389217c5h		; _a[115] @ 7360
	.word	040081052h,0f13e9c1dh		; _a[116] @ 7424
	.word	0c004412ch,0782e0f07h		; _a[117] @ 7488
	.word	0c003ec1eh,0af17b020h		; _a[118] @ 7552
	.word	03fffd3fdh,0fe9e0031h		; _a[119] @ 7616
	.word	0bffd305dh,0cb8d31ach		; _a[120] @ 7680
	.word	0bfe441aeh,0c1490b0ch		; _a[121] @ 7744
	.word	03fbffad7h,0a212e4dfh		; _a[122] @ 7808
	.word	0bfcec198h,0bc24081dh		; _a[123] @ 7872
	.word	0bf8d872fh,033ca31e8h		; _a[124] @ 7936
	.word	03ffb9018h,0e757928eh		; _a[125] @ 8000
	.word	03ff3eb72h,07491a254h		; _a[126] @ 8064
	.word	0c0015eabh,0ca1dc5e4h		; _a[127] @ 8128
	.word	03ff04ac0h,0d39a4668h		; _a[128] @ 8192
	.word	0bfef7dc8h,082bb30c3h		; _a[129] @ 8256
	.word	03ffe5413h,0ce131deah		; _a[130] @ 8320
	.word	040031081h,0c2e33effh		; _a[131] @ 8384
	.word	0bff95a54h,059f4681ch		; _a[132] @ 8448
	.word	04006b6d4h,0c33b5393h		; _a[133] @ 8512
	.word	03ff82ef9h,0e88eca33h		; _a[134] @ 8576
	.word	0bff1a7d4h,0aae79fb7h		; _a[135] @ 8640
	.word	03fa0a496h,04cddff24h		; _a[136] @ 8704
	.word	0c0010791h,074312a44h		; _a[137] @ 8768
	.word	0c002df31h,07ba30e8dh		; _a[138] @ 8832
	.word	04005a01ch,0f0d18ed3h		; _a[139] @ 8896
	.word	0bfe14918h,042162505h		; _a[140] @ 8960
	.word	0bff8bf57h,099440944h		; _a[141] @ 9024
	.word	0bff41e18h,033d36c23h		; _a[142] @ 9088
	.word	040006616h,02f166e01h		; _a[143] @ 9152
	.word	03ff19756h,0282ac175h		; _a[144] @ 9216
	.word	0bffb015fh,0b1407f4ch		; _a[145] @ 9280
	.word	0bff361d0h,0f047fc18h		; _a[146] @ 9344
	.word	04002c2e6h,02e9da23dh		; _a[147] @ 9408
	.word	03ff31387h,08169212ch		; _a[148] @ 9472
	.word	03fff65fch,0cef317bah		; _a[149] @ 9536
	.word	040057d36h,08c840761h		; _a[150] @ 9600
	.word	03feeac4dh,030347b32h		; _a[151] @ 9664
	.word	03fe46a82h,054d97628h		; _a[152] @ 9728
	.word	0bfde118eh,0325d4a5eh		; _a[153] @ 9792
	.word	03fee8888h,02f0e0a85h		; _a[154] @ 9856
	.word	0bfd1c072h,0b6d6c142h		; _a[155] @ 9920
	.word	0bff8cb75h,07f081ddch		; _a[156] @ 9984
	.word	0bffb2604h,05baf533fh		; _a[157] @ 10048
	.word	03ff330f0h,07dabfd49h		; _a[158] @ 10112
	.word	0bff44f0fh,031cc2ae6h		; _a[159] @ 10176
	.word	0bffbf1bfh,0e6347cdfh		; _a[160] @ 10240
	.word	0c0038f62h,0f9ca5bd9h		; _a[161] @ 10304
	.word	04007eaach,0bf104ba8h		; _a[162] @ 10368
	.word	040054c6ch,097d8cf3ah		; _a[163] @ 10432
	.word	03ffdbce8h,088eaf5adh		; _a[164] @ 10496
	.word	03fef1ca4h,0b124d09ah		; _a[165] @ 10560
	.word	0c001c2feh,067798bddh		; _a[166] @ 10624
	.word	03ffb5cd0h,0bb6ed677h		; _a[167] @ 10688
	.word	040081c86h,08b9fdbd3h		; _a[168] @ 10752
	.word	0c00093ddh,01f2a67b3h		; _a[169] @ 10816
	.word	03fe05966h,038433d6ch		; _a[170] @ 10880
	.word	0c007fafah,09a657174h		; _a[171] @ 10944
	.word	0bfa73113h,09e4275c6h		; _a[172] @ 11008
	.word	03ff2e755h,0ffe6d58dh		; _a[173] @ 11072
	.word	0bfeba8bdh,0c41b4d63h		; _a[174] @ 11136
	.word	03fd9ea79h,01a9e10f8h		; _a[175] @ 11200
	.word	03ffe02fdh,0255a2c9ch		; _a[176] @ 11264
	.word	040076e15h,0f2b08c24h		; _a[177] @ 11328
	.word	0bff54892h,075b8e9c1h		; _a[178] @ 11392
	.word	0c008d87ch,06327ed85h		; _a[179] @ 11456
	.word	0c006e82bh,03a406daeh		; _a[180] @ 11520
	.word	0bfc943e1h,000607810h		; _a[181] @ 11584
	.word	040035163h,09fe288f7h		; _a[182] @ 11648
	.word	03ff1c16ah,02d9b43beh		; _a[183] @ 11712
	.word	0c0032500h,0fe2cc129h		; _a[184] @ 11776
	.word	0bfe80e25h,0fdc08a9fh		; _a[185] @ 11840
	.word	0bfe3c401h,0ed4009dbh		; _a[186] @ 11904
	.word	03fe8d588h,05d31337fh		; _a[187] @ 11968
	.word	03fe89706h,0acc26b4ah		; _a[188] @ 12032
	.word	03fe64cc7h,0233fa029h		; _a[189] @ 12096
	.word	03ffcca3eh,011b386abh		; _a[190] @ 12160
	.word	03fe5ce8bh,0489dfe83h		; _a[191] @ 12224
	.word	04002e94ch,0950408a3h		; _a[192] @ 12288
	.word	03ffca989h,0b6cd8707h		; _a[193] @ 12352
	.word	03ff79cb1h,0b1be538dh		; _a[194] @ 12416
	.word	0c0036765h,069e72467h		; _a[195] @ 12480
	.word	040052fa1h,028035448h		; _a[196] @ 12544
	.word	0bffa345bh,0515f6e25h		; _a[197] @ 12608
	.word	03fe9f5ffh,0964db4bfh		; _a[198] @ 12672
	.word	0bfeeafe5h,0d6890e31h		; _a[199] @ 12736
	.word	03fb04bf9h,0d39614aah		; _a[200] @ 12800
$C$IR_1:	.set	1608

	.sect	".cinit"
	.align	8
	.field  	$C$IR_2,32
	.field  	_b+0,32
	.word	0c056d077h,088cd997bh		; _b[0] @ 0
	.word	04032bda8h,08c7ba3e5h		; _b[1] @ 64
	.word	0c04aeeb9h,0c4b24c18h		; _b[2] @ 128
	.word	0c052f071h,06cbf45fch		; _b[3] @ 192
	.word	0405813b1h,0bb63eebdh		; _b[4] @ 256
	.word	0c01e6fb7h,0efc5f619h		; _b[5] @ 320
	.word	0c0333513h,0dfb0d520h		; _b[6] @ 384
	.word	040568659h,0fb8978bah		; _b[7] @ 448
	.word	04021a95ch,02aa341b9h		; _b[8] @ 512
	.word	0404d0929h,0bbbb2c91h		; _b[9] @ 576
	.word	0c04b93aah,08c30248bh		; _b[10] @ 640
	.word	040548c81h,044383e35h		; _b[11] @ 704
	.word	04056b2b3h,0ce63a5c2h		; _b[12] @ 768
	.word	04051996dh,0e76427c8h		; _b[13] @ 832
	.word	0404b3243h,09c3702cch		; _b[14] @ 896
	.word	0403beec2h,073ad76c6h		; _b[15] @ 960
	.word	0c051b74ch,05e7d63d9h		; _b[16] @ 1024
	.word	0403cc652h,0157689cah		; _b[17] @ 1088
	.word	04050ffadh,0553840b9h		; _b[18] @ 1152
	.word	0c0119898h,025fc130bh		; _b[19] @ 1216
	.word	0404c3153h,0c4a332a0h		; _b[20] @ 1280
	.word	040522eeah,01e166b7ch		; _b[21] @ 1344
	.word	0405672efh,0a1e3eaf7h		; _b[22] @ 1408
	.word	03fe4d1ffh,07164c72ah		; _b[23] @ 1472
	.word	0c04aa0e1h,0cb6192c2h		; _b[24] @ 1536
	.word	04056a002h,05113180bh		; _b[25] @ 1600
	.word	0c04131bdh,0de1c8069h		; _b[26] @ 1664
	.word	03fc7e5cah,0ca940d69h		; _b[27] @ 1728
	.word	040326aa2h,0cc48428fh		; _b[28] @ 1792
	.word	0c05664e3h,0fcff9a7fh		; _b[29] @ 1856
	.word	0405583c0h,0ad6f3974h		; _b[30] @ 1920
	.word	04058082dh,0022c2a2ah		; _b[31] @ 1984
	.word	04040d297h,075d2eaf4h		; _b[32] @ 2048
	.word	0c057653ch,0d8ce62cfh		; _b[33] @ 2112
	.word	0c02ae4e5h,037fd9d4fh		; _b[34] @ 2176
	.word	0c05065cfh,02ea6dc78h		; _b[35] @ 2240
	.word	0c058f04fh,07afcf660h		; _b[36] @ 2304
	.word	0c01166c7h,043201041h		; _b[37] @ 2368
	.word	0c04c4c99h,08d045fe1h		; _b[38] @ 2432
	.word	0c05857a2h,0f3b56ee2h		; _b[39] @ 2496
	.word	04050bb89h,06d670ba8h		; _b[40] @ 2560
	.word	04043a5b4h,07ef82da4h		; _b[41] @ 2624
	.word	0c033f0aeh,0c8d5c747h		; _b[42] @ 2688
	.word	0c0504ee0h,0b4e11dbdh		; _b[43] @ 2752
	.word	0c052012ah,01e4c1b62h		; _b[44] @ 2816
	.word	040447f1fh,02a67b297h		; _b[45] @ 2880
	.word	0404f3862h,07f5118f7h		; _b[46] @ 2944
	.word	0c0576269h,0014b599bh		; _b[47] @ 3008
	.word	0403428eah,048de9623h		; _b[48] @ 3072
	.word	0c048a1a8h,090ad61cdh		; _b[49] @ 3136
	.word	0405855e7h,029040548h		; _b[50] @ 3200
	.word	0404314b9h,050184648h		; _b[51] @ 3264
	.word	04038febeh,08f1c6816h		; _b[52] @ 3328
	.word	0404ceda3h,0c71a0565h		; _b[53] @ 3392
	.word	0c04ddc84h,0c348bf8ch		; _b[54] @ 3456
	.word	040579488h,03dbc2331h		; _b[55] @ 3520
	.word	0c040bf92h,03bd746a3h		; _b[56] @ 3584
	.word	03fff2ecbh,0097e2e03h		; _b[57] @ 3648
	.word	0c02a468fh,09f44d445h		; _b[58] @ 3712
	.word	0c0315969h,0c59677a6h		; _b[59] @ 3776
	.word	0402fa44ch,066e0dfa9h		; _b[60] @ 3840
	.word	0c0443330h,0f56b5188h		; _b[61] @ 3904
	.word	0c035b1c0h,0569cc4c7h		; _b[62] @ 3968
	.word	0c04759adh,00c3d2524h		; _b[63] @ 4032
	.word	04054dbd4h,0279f813ah		; _b[64] @ 4096
	.word	0404c0cd9h,07551bbb4h		; _b[65] @ 4160
	.word	0bfeea3b5h,07c4e2f38h		; _b[66] @ 4224
	.word	0400c9310h,0b3ac6a57h		; _b[67] @ 4288
	.word	0403a2d7bh,06f0c2756h		; _b[68] @ 4352
	.word	0c0452f13h,081bd0402h		; _b[69] @ 4416
	.word	04052fdf8h,09e774eech		; _b[70] @ 4480
	.word	04051e9f6h,07b1c0011h		; _b[71] @ 4544
	.word	04045ac9eh,02af8d20eh		; _b[72] @ 4608
	.word	040529975h,0ff609dd0h		; _b[73] @ 4672
	.word	0c031a79ch,07368ad69h		; _b[74] @ 4736
	.word	0404446adh,02f789390h		; _b[75] @ 4800
	.word	04053c27bh,083997d14h		; _b[76] @ 4864
	.word	0c04284b2h,08954a7f8h		; _b[77] @ 4928
	.word	0404028c3h,0cac58b90h		; _b[78] @ 4992
	.word	0c05012e6h,07224e08ah		; _b[79] @ 5056
	.word	040355d9bh,08023a6ceh		; _b[80] @ 5120
	.word	0c053cda8h,0848387dfh		; _b[81] @ 5184
	.word	04055cc2ch,000390ae4h		; _b[82] @ 5248
	.word	0c05228e6h,01862cd55h		; _b[83] @ 5312
	.word	0c058c657h,06e7bde9eh		; _b[84] @ 5376
	.word	0c0254f06h,0efde49cdh		; _b[85] @ 5440
	.word	0c049d0ffh,026bc2c6ch		; _b[86] @ 5504
	.word	0c0512955h,0545acb28h		; _b[87] @ 5568
	.word	04057408ah,0082c1e6ch		; _b[88] @ 5632
	.word	0c0468aabh,093972119h		; _b[89] @ 5696
	.word	0c04295cbh,0e8a13eaah		; _b[90] @ 5760
	.word	04014c358h,00148d55ch		; _b[91] @ 5824
	.word	0c054ec9ch,0079d8333h		; _b[92] @ 5888
	.word	0c04a1a27h,05fc059f8h		; _b[93] @ 5952
	.word	0403597d7h,0200ce5c2h		; _b[94] @ 6016
	.word	0c04996bbh,059070253h		; _b[95] @ 6080
	.word	040404fb8h,0b0b615d1h		; _b[96] @ 6144
	.word	040445ddch,0fcc5b8dch		; _b[97] @ 6208
	.word	0c0448d46h,054782759h		; _b[98] @ 6272
	.word	0c0570c80h,0ae7ba8eeh		; _b[99] @ 6336
	.word	04047ea89h,02684cf07h		; _b[100] @ 6400
	.word	04049a403h,0b08ea8a5h		; _b[101] @ 6464
	.word	0c0477eaeh,050e0c324h		; _b[102] @ 6528
	.word	0c03b86efh,092ca727fh		; _b[103] @ 6592
	.word	0c055d9cah,0134988e0h		; _b[104] @ 6656
	.word	0c04de2e7h,0bb659c3ch		; _b[105] @ 6720
	.word	0c052a4b1h,0e47e9a3ah		; _b[106] @ 6784
	.word	0c039f144h,00af1cb8ah		; _b[107] @ 6848
	.word	0c05399d3h,078b87882h		; _b[108] @ 6912
	.word	04028c1d6h,042975445h		; _b[109] @ 6976
	.word	0c04d2ac1h,0a2cd1f02h		; _b[110] @ 7040
	.word	04056585ch,0810a569bh		; _b[111] @ 7104
	.word	0c0566645h,0a1cac083h		; _b[112] @ 7168
	.word	0c05571fch,0bfd99f43h		; _b[113] @ 7232
	.word	040281b3bh,0d66fe3beh		; _b[114] @ 7296
	.word	040440798h,0824264ffh		; _b[115] @ 7360
	.word	0404ede9dh,0c2f405f7h		; _b[116] @ 7424
	.word	04044777ah,0f640639dh		; _b[117] @ 7488
	.word	04055f2bfh,0ad299956h		; _b[118] @ 7552
	.word	040562661h,07f0b78dah		; _b[119] @ 7616
	.word	0c058ce59h,0a0854625h		; _b[120] @ 7680
	.word	0c0526f44h,0f05f790ch		; _b[121] @ 7744
	.word	04050cf6ch,0b02c8316h		; _b[122] @ 7808
	.word	040458c54h,0b48d3ae7h		; _b[123] @ 7872
	.word	04057658dh,09513f8dbh		; _b[124] @ 7936
	.word	040498ac8h,00918ad76h		; _b[125] @ 8000
	.word	0c021929dh,0a23cd64ah		; _b[126] @ 8064
	.word	0404bd3ceh,05f7403deh		; _b[127] @ 8128
	.word	0404b783ah,0ad7af7eeh		; _b[128] @ 8192
	.word	04042facch,089b0ee4ah		; _b[129] @ 8256
	.word	04044b4dbh,0163baba8h		; _b[130] @ 8320
	.word	040359e7dh,0af5847c0h		; _b[131] @ 8384
	.word	0c04d5b65h,0053d56a3h		; _b[132] @ 8448
	.word	0404abaa8h,0b81a8e21h		; _b[133] @ 8512
	.word	0c04917cdh,059ba8679h		; _b[134] @ 8576
	.word	0c0353321h,0cb2be2ddh		; _b[135] @ 8640
	.word	04049c453h,089eacfedh		; _b[136] @ 8704
	.word	040250b60h,0bc027a2eh		; _b[137] @ 8768
	.word	0c02d3d00h,024122e00h		; _b[138] @ 8832
	.word	0c0565aebh,0b26b21b7h		; _b[139] @ 8896
	.word	0403c99c2h,03315d702h		; _b[140] @ 8960
	.word	0c042e72ch,01a3a3de9h		; _b[141] @ 9024
	.word	0c041e4bah,0252a5bf4h		; _b[142] @ 9088
	.word	0c04bd305h,0715908b0h		; _b[143] @ 9152
	.word	0404ee37ah,022050d86h		; _b[144] @ 9216
	.word	0c0573917h,059b8d8fah		; _b[145] @ 9280
	.word	040479bdeh,0d8680b82h		; _b[146] @ 9344
	.word	0c04965a4h,0f1bc705eh		; _b[147] @ 9408
	.word	04054815ch,002cab59bh		; _b[148] @ 9472
	.word	0c0282ccdh,01d54a49dh		; _b[149] @ 9536
	.word	0c0502598h,068ac91c4h		; _b[150] @ 9600
	.word	0c04e1ad0h,07ad736b3h		; _b[151] @ 9664
	.word	0c04303d8h,08b46f07fh		; _b[152] @ 9728
	.word	040566da7h,0ef9db22dh		; _b[153] @ 9792
	.word	040530adfh,09a2eeacfh		; _b[154] @ 9856
	.word	040524e3dh,0f090f734h		; _b[155] @ 9920
	.word	0c0531040h,02d82194ah		; _b[156] @ 9984
	.word	040453574h,0ea8da7f4h		; _b[157] @ 10048
	.word	0404e72dah,02b5a20deh		; _b[158] @ 10112
	.word	04049b5d3h,05de085e7h		; _b[159] @ 10176
	.word	0c051fe7ch,0a501aca8h		; _b[160] @ 10240
	.word	04033f236h,0bc54af85h		; _b[161] @ 10304
	.word	04036a902h,01ebe3129h		; _b[162] @ 10368
	.word	0c0541e1bh,0eede6f8ch		; _b[163] @ 10432
	.word	040541133h,008d66857h		; _b[164] @ 10496
	.word	0c04e45afh,0fe5fecd0h		; _b[165] @ 10560
	.word	0404472d0h,090a6abd1h		; _b[166] @ 10624
	.word	04050ae20h,0d5629d84h		; _b[167] @ 10688
	.word	0403f8ac9h,0c75ecec2h		; _b[168] @ 10752
	.word	0404e4873h,062ce2b72h		; _b[169] @ 10816
	.word	0c04fa3efh,0b960df3eh		; _b[170] @ 10880
	.word	0403a2f71h,072332343h		; _b[171] @ 10944
	.word	0c038a66bh,02bc804e7h		; _b[172] @ 11008
	.word	0c0257bb1h,01ef15ccfh		; _b[173] @ 11072
	.word	0405301f4h,0f5756283h		; _b[174] @ 11136
	.word	040526435h,0b2d4d402h		; _b[175] @ 11200
	.word	040489c50h,0ce4ead0ch		; _b[176] @ 11264
	.word	040524bc2h,015b9a5a9h		; _b[177] @ 11328
	.word	0c04066a1h,016659d13h		; _b[178] @ 11392
	.word	0403e17ddh,06aa9c206h		; _b[179] @ 11456
	.word	0c0505376h,005ab3aach		; _b[180] @ 11520
	.word	04013305fh,0ddb6291ch		; _b[181] @ 11584
	.word	040500affh,098d1f37dh		; _b[182] @ 11648
	.word	0404cf00fh,05a1016ceh		; _b[183] @ 11712
	.word	0404be517h,07490cb95h		; _b[184] @ 11776
	.word	040349239h,014f483cbh		; _b[185] @ 11840
	.word	0c041ef42h,061a45fc6h		; _b[186] @ 11904
	.word	04050ef8eh,046eaa01ch		; _b[187] @ 11968
	.word	0c032b39ch,062a1b5c8h		; _b[188] @ 12032
	.word	04058a9a9h,0746d9026h		; _b[189] @ 12096
	.word	0401adf22h,0a5467606h		; _b[190] @ 12160
	.word	0c056bb06h,0290eed03h		; _b[191] @ 12224
	.word	04038d190h,012315aech		; _b[192] @ 12288
	.word	0c0423a8ah,07cc6243ch		; _b[193] @ 12352
	.word	0405349f3h,0cfdb7506h		; _b[194] @ 12416
	.word	0c0372d74h,0794ea077h		; _b[195] @ 12480
	.word	040446d5eh,012dace17h		; _b[196] @ 12544
	.word	040548e03h,09f5c513ah		; _b[197] @ 12608
	.word	04002b02ah,0f06e9285h		; _b[198] @ 12672
	.word	040270dcch,0a70d1fa3h		; _b[199] @ 12736
	.word	0403f0a26h,04ff5e199h		; _b[200] @ 12800
$C$IR_2:	.set	1608

	.global	_a
_a:	.usect	".far",1608,8
	.global	_b
_b:	.usect	".far",1608,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\074122 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\074124 
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
;*   Local Frame Size  : 8 Args + 44 Auto + 56 Save = 108 byte                *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |133| 
           STW     .D2T1   A10,*SP--(8)      ; |133| 
           STDW    .D2T2   B13:B12,*SP--     ; |133| 
           STDW    .D2T2   B11:B10,*SP--     ; |133| 
           STDW    .D2T1   A15:A14,*SP--     ; |133| 

           STDW    .D2T1   A13:A12,*SP--     ; |133| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(64)      ; |133| 
||         CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _a,A12

           MVKL    .S2     _b,B10
||         MVKL    .S1     _output,A14

           MVKH    .S1     _a,A12
||         MVK     .S2     0xc9,B4

           MVKH    .S2     _b,B10
||         MVKH    .S1     _output,A14

           MV      .L2     B10,B11
||         MV      .L1     A12,A11
||         CALL    .S1     __divd            ; |149| 
||         LDW     .D1T1   *A14,A10

           LDDW    .D1T1   *A11++,A5:A4      ; |149| 
||         MV      .L1X    B4,A13
||         LDDW    .D2T2   *B11++,B5:B4      ; |149| 

           NOP             3
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL1,B3,0       ; |149| 
$C$RL1:    ; CALL OCCURS {__divd} {0}        ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A13,1,A0          ; |148| 
||         STDW    .D1T1   A5:A4,*A10++      ; |149| 
||         SUB     .S1     A13,1,A13         ; |148| 

   [ A0]   LDDW    .D1T1   *A11++,A5:A4      ; |149| 
|| [!A0]   ADD     .L2X    4,A14,B4
|| [!A0]   MV      .L1     A12,A10
|| [!A0]   MVK     .S1     0xc9,A13
|| [ A0]   B       .S2     $C$L1             ; |148| 

   [ A0]   CALL    .S1     __divd            ; |149| 
   [ A0]   LDDW    .D2T2   *B11++,B5:B4      ; |149| 
   [!A0]   MV      .L1X    B10,A11
   [!A0]   ZERO    .L2     B11
   [!A0]   STW     .D2T2   B4,*+SP(20)
           ; BRANCHCC OCCURS {$C$L1}         ; |148| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _divdp            ; |152| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D2T2   *B10++,B5:B4      ; |152| 
||         LDDW    .D1T1   *A12++,A5:A4      ; |152| 

           ADDKPC  .S2     $C$RL2,B3,3       ; |152| 
$C$RL2:    ; CALL OCCURS {_divdp} {0}        ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(20),B4       ; |152| 
           SUB     .L1     A13,1,A0          ; |151| 
           SUB     .L1     A13,1,A13         ; |151| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |152| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |151| 

           ADD     .L2     B11,B4,B4         ; |152| 
||         ADD     .S2     8,B11,B11         ; |151| 

   [ A0]   CALL    .S1     _divdp            ; |152| 
||         STDW    .D2T1   A5:A4,*B4         ; |152| 

           ; BRANCHCC OCCURS {$C$L2}         ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(20),B4
           MV      .L2X    A11,B11
           MV      .L1     A10,A12
           MVK     .S1     0xc9,A13
           ZERO    .L2     B10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(24)
||         CALL    .S1     _divdp_c          ; |155| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D2T2   *B11++,B5:B4      ; |155| 
||         LDDW    .D1T1   *A12++,A5:A4      ; |155| 

           ADDKPC  .S2     $C$RL3,B3,3       ; |155| 
$C$RL3:    ; CALL OCCURS {_divdp_c} {0}      ; |155| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(24),B4       ; |155| 
           SUB     .L1     A13,1,A0          ; |154| 
           SUB     .L1     A13,1,A13         ; |154| 
   [!A0]   ZERO    .L1     A3
           NOP             1
           LDW     .D2T2   *B4,B4            ; |155| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |154| 

           ADD     .L2     B10,B4,B4         ; |155| 
||         ADD     .S2     8,B10,B10         ; |154| 

   [ A0]   CALL    .S2     _divdp_c          ; |155| 
||         STDW    .D2T1   A5:A4,*B4         ; |155| 
|| [!A0]   SET     .S1     A3,0x1e,0x1e,A4

           ; BRANCHCC OCCURS {$C$L3}         ; |154| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S1     0xc9,A5
||         DINT                              ; interrupts off
||         LDW     .D1T2   *+A14(12),B17
||         STW     .D2T1   A4,*+SP(16)       ; |61| 
||         MV      .L1     A11,A3
||         ZERO    .L2     B6                ; |61| 

           SUB     .L1     A5,1,A0
||         MV      .L2X    A4,B7
||         ZERO    .S1     A16               ; |61| 
||         MV      .D1     A4,A17            ; |61| 

           MV      .L1     A4,A19
||         ZERO    .S1     A18               ; |61| 
||         MV      .L2X    A10,B16

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/divdp/divdp_d.c
;*      Loop source line                 : 157
;*      Loop opening brace source line   : 157
;*      Loop closing brace source line   : 159
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 46
;*      Unpartitioned Resource Bound     : 4
;*      Partitioned Resource Bound(*)    : 5
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     1        0     
;*      .S units                     2        3     
;*      .D units                     2        1     
;*      .M units                     4        3     
;*      .X cross paths               3        0     
;*      .T address paths             2        1     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           2        1     (.L or .S unit)
;*      Addition ops (.LSD)          2        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             3        2     
;*      Bound(.L .S .D .LS .LSD)     3        2     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 46 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |*  *            ****            |      **        **              |
;*       1: |*  *            ****            |      **        **              |
;*       2: |*  *            ****            |      **        **              |
;*       3: |*  *            ****            |      **        **              |
;*       4: |*  *            ****            |      **        **              |
;*       5: |*  *  **        ****            |      **        **              |
;*       6: |*  *  **        ****            |    ****        **              |
;*       7: |*  *  ****      ****            |    ****        **              |
;*       8: |*  *  ****      ****            |    ****        **              |
;*       9: |*  *  ****      ****            |    ****        **              |
;*      10: |*  *  ****      ****            |    ****        **              |
;*      11: |*  *******      ****            |    ****        **              |
;*      12: |*  *  ****      ****            |    ****        **              |
;*      13: |*  *  ****      ****            |    ****        **              |
;*      14: |*  *******      ****            |    ****        **              |
;*      15: |*  *  **        ****            |    ****        **              |
;*      16: |*  *  **        ****            |    ****        **              |
;*      17: |*  *  **        ****            |    ****        **              |
;*      18: |*  *****        ****            |    ****        **              |
;*      19: |*  ***          ****            |    ****        **              |
;*      20: |*  ***          ****            |    ****        **              |
;*      21: |*  ***          ****            |    ****        **              |
;*      22: |*  *****        ****            |    ****        **              |
;*      23: |*  ***          ****            |    ****        **              |
;*      24: |*  ***          ****            |    ****        **              |
;*      25: |*  *****        ****            |    ****        **              |
;*      26: |*  *            ****            |    ****        **              |
;*      27: |*  *            ****            |    ****        **              |
;*      28: |*  *            ****            |    ****        **              |
;*      29: |*  ***          ****            |    ****        **              |
;*      30: |*  ***          ****            |    ****        **              |
;*      31: |*  ***          ****            |      **        **              |
;*      32: |*  ***          ****            |      **        **              |
;*      33: |*  ***          ****            |      **        **              |
;*      34: |*  ***          ****            |    ****        **              |
;*      35: |*  ***          ****            |      **        **              |
;*      36: |*  ***          ****            |      **        **              |
;*      37: |*  ***          ****            |    ****        **              |
;*      38: |*  ***          ****            |      **        **              |
;*      39: |*  ***          ****            |      ****      **              |
;*      40: |*  ***          ****            |      ****      **              |
;*      41: |*  *            ****            |*   ******      **              |
;*      42: |*  *            ****            |*     **        **              |
;*      43: |*  *            ****            |*     **        **              |
;*      44: |*  *            ****            |*     **        **              |
;*      45: |*  *            ****            |    ****        **              |
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
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.000, max 0.000 }
;*      Mem bank perf. penalty (est.) : 0.0%
;*
;*
;*      Total cycles (est.)         : 0 + min_trip_cnt * 46 = 9246        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A0,1,A0
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C114:
;*   0              LDDW    .D1T1   *A3++,A7:A6       ; |61|  ^ 
;*   1              NOP             4
;*   5              DADD    .L2X    0,A7:A6,B5:B4     ; |61| Define a twin register
;*     ||           RCPDP   .S1     A7:A6,A9:A8       ; |61|  ^ 
;*   6              NOP             1
;*   7              FMPYDP  .M1     A9:A8,A7:A6,A5:A4 ; |61|  ^ 
;*   8              NOP             3
;*  11              FSUBDP  .L1     A19:A18,A5:A4,A5:A4 ; |61|  ^ 
;*  12              NOP             2
;*  14              FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |61|  ^ 
;*  15              NOP             3
;*  18              FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |61|  ^ 
;*  19              NOP             3
;*  22              FSUBDP  .L1     A17:A16,A7:A6,A7:A6 ; |61|  ^ 
;*  23              NOP             2
;*  25              FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |61|  ^ 
;*  26              NOP             4
;*  30              FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |61|  ^ 
;*  31              NOP             3
;*  34              LDDW    .D2T2   *B16++,B9:B8      ; |61| 
;*     ||           FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |61|  ^ 
;*  35              NOP             2
;*  37              ZERO    .L1     A5:A4             ; |61| 
;*     ||           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |61|  ^ 
;*  38              NOP             1
;*  39              CMPEQDP .S2X    B9:B8,A5:A4,B0    ; |61| 
;*  40      [ A0]   BDEC    .S1     $C$C114,A0        ; |157| 
;*  41      [!B0]   FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |61|  ^ 
;*  42              NOP             2
;*  44      [ B0]   ZERO    .L2     B5:B4             ; |61| 
;*  45              STDW    .D2T2   B5:B4,*B17++      ; |61|  ^ 
;*  46              ; BRANCHCC OCCURS {$C$C114}       ; |157| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 46
           LDDW    .D1T1   *A3++,A7:A6       ; |61| <0,0>  ^ 
           NOP             4

           DADD    .L2X    0,A7:A6,B5:B4     ; |61| <0,5> Define a twin register
||         RCPDP   .S1     A7:A6,A9:A8       ; |61| <0,5>  ^ 

           NOP             1
           FMPYDP  .M1     A9:A8,A7:A6,A5:A4 ; |61| <0,7>  ^ 
           NOP             3
           FSUBDP  .L1     A19:A18,A5:A4,A5:A4 ; |61| <0,11>  ^ 
           NOP             2
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |61| <0,14>  ^ 
           NOP             3
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |61| <0,18>  ^ 
           NOP             3
           FSUBDP  .L1     A17:A16,A7:A6,A7:A6 ; |61| <0,22>  ^ 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |61| <0,25>  ^ 
           NOP             4
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |61| <0,30>  ^ 
           NOP             3

           LDDW    .D2T2   *B16++,B9:B8      ; |61| <0,34> 
||         FSUBDP  .L2     B7:B6,B5:B4,B5:B4 ; |61| <0,34>  ^ 

           NOP             2

           ZERO    .L1     A5:A4             ; |61| <0,37> 
||         FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |61| <0,37>  ^ 

           NOP             1
           CMPEQDP .S2X    B9:B8,A5:A4,B0    ; |61| <0,39> 
   [ A0]   BDEC    .S1     $C$L5,A0          ; |157| <0,40> 
   [!B0]   FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |61| <0,41>  ^ 
           NOP             2
   [ B0]   ZERO    .L2     B5:B4             ; |61| <0,44> 
           STDW    .D2T2   B5:B4,*B17++      ; |61| <0,45>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           RINT                              ; interrupts on

           MV      .L2X    A14,B10
||         STW     .D2T2   B7,*+SP(16)
||         MVK     .S2     0xc9,B6           ; |160| 

           CALLP   .S2     _divdp_v,B3
||         LDW     .D2T1   *+B10(16),A6      ; |160| 
||         MV      .L2X    A11,B4            ; |160| 
||         MV      .L1     A10,A4            ; |160| 
||         MV      .S1     A19,A13

$C$RL4:    ; CALL OCCURS {_divdp_v} {0}      ; |160| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 49
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B5
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A14,A3
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T2   *+SP(24),B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6
           MVKL    .S1     _output,A3
           ADDAD   .D2     B4,1,B5

           LDW     .D2T2   *B5,B4            ; |69| 
||         MVKL    .S2     _fcn_pass,B5

           MVKH    .S2     _fcn_pass,B5

           MVKH    .S1     _output,A3
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
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

           STW     .D2T2   B4,*+SP(28)
           ADD     .L2     8,B5,B4
           STW     .D2T2   B4,*+SP(32)       ; |69| 
           STW     .D2T1   A4,*+B5(16)       ; |69| 

   [!B0]   MVKL    .S1     _all_pass,A3
|| [!B0]   B       .S2     $C$L7             ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [!B0]   ZERO    .D2     B4                ; |72| 

   [!B0]   CALL    .S2     _print_test_results ; |164| 
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
           CALL    .S1     _print_test_results ; |164| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |164| 
||         STW     .D1T2   B4,*A3            ; |72| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |164| 

$C$RL9:    ; CALL OCCURS {_print_test_results} {0}  ; |164| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19

           MVKL    .S2     _b_sc,B5
||         ZERO    .L2     B17

           SET     .S2     B17,0x14,0x1e,B17

           MVKH    .S2     _b_sc,B5
||         MVK     .L1     0xffffffff,A4     ; |177| 
||         MVKL    .S1     _a_sc,A3
||         ZERO    .L2     B16               ; |173| 

           STDW    .D2T2   B17:B16,*+B5(16)  ; |173| 
||         MVKH    .S1     _a_sc,A3
||         MV      .L1     A4,A5             ; |177| 

           STDW    .D2T1   A5:A4,*+B5(48)    ; |177| 

           ADDAD   .D2     B5,7,B6
||         MV      .L2X    A3,B4             ; |171| 

           STDW    .D2T2   B17:B16,*+B4(16)  ; |173| 

           ADDAD   .D2     B4,7,B7
||         ZERO    .L2     B9

           STDW    .D2T1   A5:A4,*+B4(48)    ; |177| 
||         MVKH    .S2     0xbff00000,B9
||         ZERO    .L1     A7
||         ZERO    .L2     B8                ; |176| 

           STDW    .D2T2   B9:B8,*+B5(40)    ; |176| 
||         SET     .S1     A7,0x14,0x1d,A7
||         ZERO    .L1     A6                ; |175| 

           STDW    .D2T1   A7:A6,*+B5(32)    ; |175| 
           STDW    .D2T1   A7:A6,*+B4(32)    ; |175| 

           ZERO    .L2     B17:B16           ; |171| 
||         STDW    .D2T2   B9:B8,*+B4(40)    ; |176| 
||         ZERO    .L1     A9

           STDW    .D2T2   B17:B16,*B4       ; |171| 
||         MVKH    .S1     0xfff00000,A9
||         ZERO    .L1     A8                ; |174| 

           STDW    .D2T2   B17:B16,*B5       ; |171| 
||         DADD    .L1     0,A9:A8,A5:A4     ; |174| 
||         ZERO    .S1     A17

           STDW    .D2T1   A5:A4,*+B4(24)    ; |174| 
||         MVKH    .S1     0x80000000,A17
||         MVK     .L2     0x6,B31           ; |179| 
||         ZERO    .L1     A16               ; |173| 

           DADD    .L1     0,A17:A16,A5:A4   ; |172| 
||         STDW    .D2T1   A5:A4,*+B5(24)    ; |174| 

           MVK     .L2     0x7,B4            ; |180| 
||         STDW    .D2T1   A5:A4,*+B4(8)     ; |172| 
||         MV      .S2     B5,B13            ; |171| 
||         MV      .L1X    B31,A1            ; |179| 

           MVC     .S2     B4,RILC
||         MVK     .L2     6,B5              ; |180| 
||         STDW    .D2T1   A5:A4,*+B5(8)     ; |172| 
||         SUB     .L1     A1,1,A1           ; |179| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/divdp/divdp_d.c
;*      Loop source line                 : 180
;*      Loop opening brace source line   : 180
;*      Loop closing brace source line   : 184
;*      Known Minimum Trip Count         : 7                    
;*      Known Maximum Trip Count         : 7                    
;*      Known Max Trip Count Factor      : 7
;*      Loop Carried Dependency Bound(^) : 6
;*      Unpartitioned Resource Bound     : 2
;*      Partitioned Resource Bound(*)    : 4
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     1        0     
;*      .S units                     1        0     
;*      .D units                     1        3     
;*      .M units                     0        0     
;*      .X cross paths               0        0     
;*      .T address paths             0        4*    
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        0     (.L or .S unit)
;*      Addition ops (.LSD)          6        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        0     
;*      Bound(.L .S .D .LS .LSD)     3        1     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 6  Schedule found with 2 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |   ****                         |      ***                       |
;*       1: |   *****                        |      ***                       |
;*       2: |*  ****                         |    *****                       |
;*       3: |   *****                        |      ***                       |
;*       4: |   *****                        |    *****                       |
;*       5: |   *****                        |      ***                       |
;*          +-----------------------------------------------------------------+
;*
;*      Done
;*
;*      Loop will be splooped
;*      Collapsed epilog stages       : 0
;*      Collapsed prolog stages       : 0
;*      Minimum required memory pad   : 0 bytes
;*
;*      Minimum safe trip count       : 1
;*      Min. prof. trip count  (est.) : 2
;*
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.000, max 0.000 }
;*      Mem bank perf. penalty (est.) : 0.0%
;*
;*
;*      Total cycles (est.)         : 6 + min_trip_cnt * 6 = 48        
;*----------------------------------------------------------------------------*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C77:
;*   0              ADD     .L1     A4,A3,A7          ; |182| 
;*   1              CMPGT   .L1     A7,6,A0           ; |182| 
;*   2      [ A0]   MVK     .S1     0xffffffc8,A7     ; |182| 
;*     ||   [!A0]   ZERO    .D1     A7                ; |182| 
;*   3              LDDW    .D2T2   *B8++,B5:B4       ; |181|  ^ 
;*     ||           ADD     .L1     A5,A7,A7          ; |182| 
;*   4              ADD     .L1     A6,A7,A7          ; |182| 
;*   5              LDDW    .D1T2   *A7,B5:B4         ; |182|  ^ 
;*     ||           ADD     .L1     1,A4,A4           ; |180| 
;*   6              NOP             2
;*   8              STDW    .D2T2   B5:B4,*B7++       ; |181|  ^ 
;*     ||           ADD     .L1     8,A5,A5           ; |180| 
;*   9              NOP             1
;*  10              STDW    .D2T2   B5:B4,*B6++       ; |182|  ^ 
;*     ||           SPBR            $C$C77
;*  11              NOP             1
;*  12              ; BRANCHCC OCCURS {$C$C77}        ; |180| 
;*----------------------------------------------------------------------------*
$C$L8:    ; PIPED LOOP PROLOG
;          EXCLUSIVE CPU CYCLES: 7

   [ A1]   SPLOOPD 6       ;12               ; SPRELOAD
||         MVK     .L1     0x1,A3            ; |179| 
||         ZERO    .S1     A4                ; |180| 
||         MVC     .S2     B5,ILC

;** --------------------------------------------------------------------------*
$C$L9:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 6

           SPMASK          L2
||         MVK     .L2     0x8,B9
||         ADD     .L1     A4,A3,A7          ; |182| (P) <0,0> 

           SPMASK          S2
||         MVKL    .S2     _a_sc,B8
||         CMPGT   .L1     A7,6,A0           ; |182| (P) <0,1> 

           SPMASK          L1,S2
||         MVKH    .S2     _a_sc,B8
||         MV      .L1X    B9,A5
|| [!A0]   ZERO    .D1     A7                ; |182| (P) <0,2> 
|| [ A0]   MVK     .S1     0xffffffc8,A7     ; |182| (P) <0,2> 

           SPMASK          S1
||         MV      .S1X    B13,A6
||         LDDW    .D2T2   *B8++,B5:B4       ; |181| (P) <0,3>  ^ 
||         ADD     .L1     A5,A7,A7          ; |182| (P) <0,3> 

           ADD     .L1     A6,A7,A7          ; |182| (P) <0,4> 

           ADD     .L1     1,A4,A4           ; |180| (P) <0,5> 
||         LDDW    .D1T2   *A7,B5:B4         ; |182| (P) <0,5>  ^ 

           NOP             2

           STDW    .D2T2   B5:B4,*B7++       ; |181| <0,8>  ^ 
||         ADD     .L1     8,A5,A5           ; |180| <0,8> 

           NOP             1

           SPKERNEL 0,0
||         STDW    .D2T2   B5:B4,*B6++       ; |182| <0,10>  ^ 

;** --------------------------------------------------------------------------*
$C$L10:    ; PIPED LOOP EPILOG AND PROLOG
;          EXCLUSIVE CPU CYCLES: 9
           NOP             2

           SPMASKR         ;$C$L10
||         ZERO    .S1     A4                ; |180| 
||         ADD     .D1     1,A3,A3           ; |179| 

           ADD     .L2     8,B9,B9           ; |179| 
|| [ A1]   B       .S2     $C$L10            ; |179| 

           MV      .L2X    A6,B13
||         MVKL    .S2     _a_sc,B8
||         SUB     .S1     A1,1,A1           ; |179| 

           MVKH    .S2     _a_sc,B8
||         MV      .L1X    B9,A5

           MV      .S1X    B13,A6
||         MVK     .L2     0x7,B4            ; |180| 
||         MVK     .S2     6,B5              ; |180| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L10}        ; |179| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
           LDW     .D2T2   *+SP(24),B4       ; |187| 
           ZERO    .L1     A3

           MVKL    .S2     _a_sc,B10
||         STW     .D2T1   A13,*+SP(48)      ; |61| 

           MVK     .S2     0x31,B31          ; |187| 
||         STW     .D2T1   A3,*+SP(52)

           STW     .D2T2   B31,*+SP(12)
||         MVKH    .S2     _a_sc,B10
||         MV      .L1X    B13,A15

           ADD     .L2     4,B4,B11
||         LDDW    .D2T2   *B10,B5:B4        ; |189| 
||         LDDW    .D1T1   *A15,A5:A4        ; |189| 
||         CALL    .S1     __divd            ; |189| 

           ZERO    .L1     A10
           ZERO    .L1     A12
           ZERO    .L2     B12
           MV      .L1     A13,A11           ; |61| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           ADDKPC  .S2     $C$RL10,B3,0      ; |189| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |189| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |189| 

$C$RL10:   ; CALL OCCURS {__divd} {0}        ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 36
           LDW     .D1T1   *A14,A3           ; |189| 
           NOP             4
           ADD     .L1X    B12,A3,A3         ; |189| 
           STDW    .D1T1   A5:A4,*A3         ; |189| 

           LDDW    .D1T1   *A15,A5:A4        ; |190| 
||         LDDW    .D2T2   *B10,B5:B4        ; |190| 

           NOP             4

           CALLP   .S2     _divdp,B3
||         DADD    .L2X    0,A5:A4,B5:B4     ; |190| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |190| 

$C$RL11:   ; CALL OCCURS {_divdp} {0}        ; |190| 
           LDW     .D1T1   *+A14(4),A3       ; |190| 
           NOP             4
           ADD     .L1X    B12,A3,A3         ; |190| 
           STDW    .D1T1   A5:A4,*A3         ; |190| 

           LDDW    .D2T2   *B10,B5:B4        ; |191| 
||         LDDW    .D1T1   *A15,A5:A4        ; |191| 

           NOP             4

           CALLP   .S2     _divdp_c,B3
||         DADD    .L2X    0,A5:A4,B5:B4     ; |191| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |191| 

$C$RL12:   ; CALL OCCURS {_divdp_c} {0}      ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 60
           LDW     .D1T1   *+A14(8),A3       ; |191| 
           LDW     .D2T2   *B11,B16          ; |192| 
           ZERO    .L2     B9:B8             ; |64| 
           NOP             2
           ADD     .L2X    B12,A3,B4         ; |191| 
           STDW    .D2T1   A5:A4,*B4         ; |191| 
           LDDW    .D1T1   *A15++,A5:A4      ; |61| 
           LDDW    .D2T2   *B10++,B5:B4      ; |61| 
           MV      .L1X    B11,A3            ; |192| 
           ADD     .L2     B12,B16,B31       ; |192| 
           ADD     .L2     8,B12,B12         ; |193| 
           RCPDP   .S1     A5:A4,A7:A6       ; |61| 
           CMPEQDP .S2     B5:B4,B9:B8,B0    ; |64| 
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |61| 
           NOP             3
           FSUBDP  .L1     A13:A12,A9:A8,A9:A8 ; |61| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |61| 
           NOP             3
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |61| 
           NOP             3
           FSUBDP  .L1     A11:A10,A9:A8,A9:A8 ; |61| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |61| 
           LDDW    .D2T1   *+SP(48),A9:A8
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |61| 
           NOP             3
           FSUBDP  .L1     A9:A8,A5:A4,A5:A4 ; |61| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |61| 
           NOP             4

           FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |61| 
||         LDW     .D2T2   *+SP(12),B4       ; |192| 

           NOP             3
   [ B0]   ZERO    .L2     B7:B6             ; |65| 

           SUB     .L1X    B4,1,A0           ; |187| 
||         STDW    .D2T2   B7:B6,*B31        ; |192| 
||         SUB     .L2     B4,1,B4           ; |187| 

   [ A0]   B       .S1     $C$L11            ; |187| 
||         STW     .D2T2   B4,*+SP(12)       ; |192| 
|| [ A0]   LDDW    .D1T1   *A15,A5:A4        ; |189| 

   [ A0]   CALL    .S1     __divd            ; |189| 
|| [ A0]   LDDW    .D2T2   *B10,B5:B4        ; |189| 

   [!A0]   CALL    .S1     _divdp_v          ; |196| 
   [!A0]   LDW     .D1T1   *+A3(4),A6        ; |196| 
   [!A0]   MVKL    .S1     _a_sc,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L11}        ; |187| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVK     .S2     0x31,B6           ; |196| 

           ADDKPC  .S2     $C$RL13,B3,0      ; |196| 
||         MV      .L2     B13,B4            ; |196| 
||         MVKH    .S1     _a_sc,A4

$C$RL13:   ; CALL OCCURS {_divdp_v} {0}      ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T1   *A14,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A14(4),B4       ; |66| 
||         MVK     .S1     0x31,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B4
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A14,A4           ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         STW     .D2T1   A5,*+B4(4)        ; |66| 
||         LDW     .D1T2   *+A14(8),B4       ; |67| 
||         MVK     .S1     0x31,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B4
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A14,A4           ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         STW     .D2T1   A3,*+B4(8)        ; |67| 
||         LDW     .D1T2   *+A14(12),B4      ; |68| 
||         MVK     .S1     0x31,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B4
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B4

           MVKL    .S1     _output,A3
||         MVKH    .S2     0xd9d7bdbb,B6

           MVKH    .S1     _output,A3
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         LDW     .D1T2   *+A14(16),B4      ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0x31,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(28),A3       ; |69| 
           MVKL    .S2     _fcn_pass,B4
           MVKH    .S2     _fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           NOP             1
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A3,*+SP(36)       ; |69| 
           LDW     .D2T1   *+SP(32),A3
           NOP             2

   [!A0]   B       .S1     $C$L12            ; |72| 
|| [!A0]   MV      .L1     A10,A4
||         MV      .D1     A0,A1             ; guard predicate rewrite

   [!A0]   CALL    .S1     _print_test_results ; |200| 

           STW     .D2T1   A3,*+SP(40)       ; |72| 
|| [!A0]   MVKL    .S1     _all_pass,A3

   [ A0]   LDW     .D1T1   *A3,A0            ; |72| 
|| [!A0]   MVKH    .S1     _all_pass,A3

   [ A1]   ADD     .L1     4,A3,A3
           NOP             1
           ; BRANCHCC OCCURS {$C$L12}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           CMPEQ   .L1     A4,0,A4           ; |72| 
           XOR     .L1     1,A4,A4           ; |72| 
   [ A0]   LDW     .D1T1   *A3,A3            ; |72| 
           NOP             4
   [ A0]   CMPEQ   .L1     A3,0,A3           ; |72| 
   [ A0]   XOR     .L1     1,A3,A3           ; |72| 

   [ A0]   AND     .L1     A4,A3,A0          ; |72| 
|| [!A0]   ZERO    .S1     A0                ; |72| 
||         MVK     .D1     0x1,A4            ; |72| 

   [!A0]   MV      .L1     A10,A4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |200| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |200| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |200| 

$C$RL18:   ; CALL OCCURS {_print_test_results} {0}  ; |200| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           LDW     .D2T1   *+SP(16),A11      ; |61| 
           MVKL    .S2     _b_ext,B4
           MV      .L1     A10,A31

           MVKL    .S2     _a_ext,B10
||         MVK     .S1     0x777,A3
||         STW     .D2T1   A31,*+SP(52)      ; |203| 

           MVKH    .S2     _b_ext,B4
||         MVKL    .S1     0x7fefffff,A7
||         STW     .D2T1   A3,*+SP(12)       ; |204| 

           MVKH    .S2     _a_ext,B10
||         ZERO    .L1     A5
||         MVKH    .S1     0x7fefffff,A7
||         MVK     .D1     0xffffffff,A6     ; |204| 
||         STW     .D2T1   A11,*+SP(48)      ; |61| 

           MV      .L2     B10,B31           ; |204| 
||         SET     .S1     A5,0x14,0x14,A5
||         MV      .L1     A10,A4
||         STDW    .D2T1   A7:A6,*B4         ; |204| 

           MV      .L1X    B4,A14            ; |204| 
||         STDW    .D2T1   A5:A4,*B31        ; |203| 

           LDDW    .D2T2   *B10,B5:B4        ; |206| 
||         LDDW    .D1T1   *A14,A5:A4        ; |206| 
||         CALL    .S1     __divd            ; |206| 

           MVKL    .S2     0x4000cccc,B13
           MVKL    .S2     0xcccccccd,B12
           MVKH    .S2     0x4000cccc,B13

           MV      .L1     A11,A13           ; |61| 
||         MVKH    .S2     0xcccccccd,B12
||         MV      .S1X    B11,A15           ; |61| 
||         MV      .L2X    A12,B11           ; |203| 

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
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1

           DADD    .L1X    0,B5:B4,A5:A4     ; |206| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |206| 
||         ADDKPC  .S2     $C$RL19,B3,0      ; |206| 

$C$RL19:   ; CALL OCCURS {__divd} {0}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 113
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           LDW     .D1T1   *A3,A3            ; |206| 
           NOP             4
           ADD     .L1X    B11,A3,A3         ; |206| 
           STDW    .D1T1   A5:A4,*A3         ; |206| 

           LDDW    .D1T1   *A14,A5:A4        ; |207| 
||         LDDW    .D2T2   *B10,B5:B4        ; |207| 

           NOP             4

           CALLP   .S2     _divdp,B3
||         DADD    .L2X    0,A5:A4,B5:B4     ; |207| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |207| 

$C$RL20:   ; CALL OCCURS {_divdp} {0}        ; |207| 
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           LDW     .D1T1   *+A3(4),A3        ; |207| 
           NOP             4
           ADD     .L2X    B11,A3,B4         ; |207| 
           STDW    .D2T1   A5:A4,*B4         ; |207| 

           LDDW    .D2T2   *B10,B5:B4        ; |208| 
||         LDDW    .D1T1   *A14,A5:A4        ; |208| 

           NOP             4

           CALLP   .S2     _divdp_c,B3
||         DADD    .L2X    0,A5:A4,B5:B4     ; |208| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |208| 

$C$RL21:   ; CALL OCCURS {_divdp_c} {0}      ; |208| 
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           LDW     .D1T1   *+A3(8),A3        ; |208| 
           NOP             4
           ADD     .L1X    B11,A3,A3         ; |208| 
           STDW    .D1T1   A5:A4,*A3         ; |208| 
           LDDW    .D1T1   *A14,A7:A6        ; |61| 
           NOP             4
           RCPDP   .S1     A7:A6,A5:A4       ; |61| 
           NOP             1
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |61| 
           NOP             3
           FSUBDP  .L1     A13:A12,A9:A8,A9:A8 ; |61| 
           NOP             2
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |61| 
           NOP             3
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |61| 
           NOP             3
           FSUBDP  .L1     A11:A10,A9:A8,A9:A8 ; |61| 
           NOP             2
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |61| 
           NOP             2
           LDDW    .D2T1   *+SP(48),A5:A4
           FMPYDP  .M1     A9:A8,A7:A6,A7:A6 ; |61| 
           NOP             3
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |61| 
           NOP             2

           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |61| 
||         LDDW    .D2T2   *B10,B5:B4        ; |61| 

           NOP             2
           MV      .L2X    A15,B6            ; |209| 
           LDW     .D2T2   *B6,B8            ; |209| 

           ZERO    .L1     A5:A4             ; |64| 
||         FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |61| 

           NOP             1
           CMPEQDP .S2X    B5:B4,A5:A4,B0    ; |64| 
           NOP             1

   [ B0]   ZERO    .L2     B7:B6             ; |65| 
||         ADD     .S2     B11,B8,B31        ; |209| 

           STDW    .D2T2   B7:B6,*B31        ; |209| 
           LDDW    .D2T2   *B10,B5:B4        ; |210| 
           NOP             4
           FMPYDP  .M2     B13:B12,B5:B4,B5:B4 ; |210| 
           NOP             3

           ZERO    .L2     B5
||         STDW    .D2T2   B5:B4,*++B10      ; |210| 

           MVKH    .S2     0xbff80000,B5

           CALLP   .S2     __divd,B3
||         ZERO    .L2     B4                ; |211| 
||         LDDW    .D1T1   *A14,A5:A4        ; |211| 

$C$RL22:   ; CALL OCCURS {__divd} {0}        ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T1   *+SP(12),A3       ; |209| 
           ADD     .L2     8,B11,B11         ; |205| 
           STDW    .D1T1   A5:A4,*++A14      ; |211| 
           NOP             2
           SUB     .L1     A3,1,A0           ; |205| 

   [ A0]   B       .S2     $C$L13            ; |205| 
|| [ A0]   LDDW    .D1T1   *A14,A5:A4        ; |206| 
|| [ A0]   LDDW    .D2T2   *B10,B5:B4        ; |206| 
|| [!A0]   MVKL    .S1     _a_ext,A4

   [ A0]   CALL    .S1     __divd            ; |206| 
           STW     .D2T1   A0,*+SP(12)       ; |211| 
   [!A0]   CALL    .S1     _divdp_v          ; |213| 
   [!A0]   LDW     .D1T1   *+A15(4),A6       ; |213| 
   [!A0]   MVKL    .S2     _b_ext,B4
           ; BRANCHCC OCCURS {$C$L13}        ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           MVKH    .S2     _b_ext,B4
           ADDKPC  .S2     $C$RL23,B3,0      ; |213| 

           MVK     .S2     0x777,B6          ; |213| 
||         MVKH    .S1     _a_ext,A4

$C$RL23:   ; CALL OCCURS {_divdp_v} {0}      ; |213| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0xd9d7bdbb,B6

           MVKL    .S1     _output,A10
||         MVKL    .S2     0x3ddb7cdf,B7

           MVKH    .S1     _output,A10
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T1   *A10,A4           ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL24:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B10
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B10

           MV      .L1     A4,A3             ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A10(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL25:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           MV      .L1     A4,A3             ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A10(12),B4      ; |68| 
||         STW     .D2T1   A3,*+B10(8)       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A10,A3            ; |68| 
||         LDW     .D1T2   *+A10(16),B4      ; |69| 
||         STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL27:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(28),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T1   *B4,A0            ; |72| 
           LDW     .D2T2   *+SP(32),B4
           NOP             3
   [!A0]   B       .S1     $C$L14            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |217| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   MV      .L1     A12,A3
   [!A0]   MVKL    .S1     _all_pass,A4
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKH    .S1     _all_pass,A4
           ; BRANCHCC OCCURS {$C$L14}        ; |72| 
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
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   MV      .L1     A12,A3
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |217| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |217| 
||         ADDKPC  .S2     $C$RL28,B3,0      ; |217| 

$C$RL28:   ; CALL OCCURS {_print_test_results} {0}  ; |217| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVKL    .S1     _cycle_counts+24,A3

           MVKH    .S1     _cycle_counts+24,A3
||         MV      .L2X    A12,B4            ; |114| 
||         MV      .L1     A12,A4            ; |114| 
||         MV      .D1     A12,A5            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A3         ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     _t_start,A3

           MVKH    .S1     _t_start,A3
||         MV      .L2     B4,B7             ; |116| 

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B7:B6,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           SUB     .L2     B8,B7,B6          ; |117| 
||         EXT     .S2     B5,24,24,B5       ; |117| 
||         MVKL    .S1     _t_offset,A3

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S1     _t_offset,A3

           DADD    .L2X    0,A5:A4,B5:B4     ; |114| 
||         STDW    .D1T2   B5:B4,*A3         ; |117| 

           CALL    .S1     _gimme_random     ; |227| 
||         MVKL    .S2     0xc01921fb,B5
||         STDW    .D2T2   B5:B4,*+SP(48)    ; |117| 

           MVKL    .S2     0x3fa6defc,B4

           MVKH    .S2     0xc01921fb,B5
||         MVK     .S1     0x80,A14

           MVKH    .S2     0x3fa6defc,B4
||         MVKL    .S1     0x402921fb,A5
||         MV      .L1     A12,A11

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL29,B3,0      ; |227| 

           MVKH    .S1     0x402921fb,A5
||         MV      .L1X    B4,A4             ; |227| 

$C$RL29:   ; CALL OCCURS {_gimme_random} {0}  ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           LDW     .D1T2   *A3,B6            ; |227| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |227| 
           MVKL    .S1     0x402921fb,A5
           LDW     .D1T1   *+A3(4),A13       ; |228| 
           MVKH    .S1     0x402921fb,A5
           ADD     .L2X    A11,B6,B6         ; |227| 

           STDW    .D2T2   B5:B4,*B6         ; |227| 
||         MVKL    .S2     0x3fa6defc,B4

           MVKL    .S2     0xc01921fb,B5
           MVKH    .S2     0x3fa6defc,B4
           MVKH    .S2     0xc01921fb,B5

           CALLP   .S2     _gimme_random,B3
||         MV      .L1X    B4,A4             ; |228| 

$C$RL30:   ; CALL OCCURS {_gimme_random} {0}  ; |228| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 71
           ADD     .L1     A13,A11,A3        ; |228| 

           STDW    .D1T1   A5:A4,*A3         ; |228| 
||         MVC     .S2     TSCL,B8           ; |122| 

           MVC     .S2     TSCH,B6           ; |122| 
           ADD     .L1     A13,A11,A3        ; |61| 
           LDDW    .D1T1   *A3,A7:A6         ; |61| 
           ZERO    .L2     B4                ; |61| 
           ZERO    .L2     B5
           SET     .S2     B5,0x1e,0x1e,B5
           ZERO    .L2     B19
           RCPDP   .S1     A7:A6,A5:A4       ; |61| 
           ZERO    .L2     B18               ; |61| 
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |61| 
           SET     .S2     B19,0x1e,0x1e,B19
           MVKL    .S1     _input,A31
           MV      .L2     B6,B9             ; |122| 
           MVKH    .S1     _input,A31
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |61| 
           MV      .L2X    A13,B13           ; |61| 
           LDW     .D1T1   *A31,A12          ; |61| 
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |61| 
           MVK     .S2     12,B7
           MVKL    .S2     _t_start,B12
           ADD     .L2X    A10,B7,B7
           FMPYDP  .M2X    B5:B4,A7:A6,B17:B16 ; |61| 
           MVKH    .S2     _t_start,B12
           ADD     .L1     A12,A11,A3        ; |61| 
           ADD     .L1     A12,A11,A30       ; |64| 
           FSUBDP  .L2     B19:B18,B17:B16,B17:B16 ; |61| 
           LDW     .D2T2   *B7,B6            ; |232| 
           STDW    .D2T2   B9:B8,*B12
           FMPYDP  .M2     B5:B4,B17:B16,B5:B4 ; |61| 
           NOP             4
           FMPYDP  .M1X    B5:B4,A7:A6,A5:A4 ; |61| 
           MV      .L1X    B19,A7            ; |61| 
           MV      .L1X    B18,A6            ; |61| 
           ADD     .L2X    A11,B6,B6         ; |232| 
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |61| 
           LDDW    .D1T1   *A30,A7:A6        ; |64| 
           NOP             2

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |61| 
||         LDDW    .D1T1   *A3,A5:A4         ; |61| 

           NOP             4
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |61| 
           ZERO    .L1     A5:A4             ; |64| 
           CMPEQDP .S1     A7:A6,A5:A4,A0    ; |64| 
           NOP             1
   [ A0]   ZERO    .L2     B5:B4             ; |65| 

           STDW    .D2T2   B5:B4,*B6         ; |232| 
||         MVC     .S2     TSCL,B6           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     _t_offset,A3
||         MVKL    .S2     _cycle_counts+24,B5
||         MV      .L2     B4,B7             ; |128| 
||         SUB     .L1     A14,1,A0          ; |225| 
||         ADD     .D1     8,A11,A11         ; |225| 

           MVKH    .S1     _t_offset,A3
||         MVKH    .S2     _cycle_counts+24,B5
||         SUB     .L1     A14,1,A14         ; |225| 

           MVKL    .S2     _t_stop,B11
||         MVKL    .S1     _cycle_counts+24,A13
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 

           LDDW    .D2T2   *B5,B5:B4         ; |130| 
           MVKH    .S1     _cycle_counts+24,A13
           MVKH    .S2     _t_stop,B11
           STDW    .D2T2   B7:B6,*B11        ; |128| 
           ADDU    .L1X    A6,B8,A5:A4       ; |130| 

           ADD     .S1     A5,A7,A3          ; |130| 
||         SUBU    .L1X    B6,A4,A5:A4       ; |130| 

           EXT     .S1     A5,24,24,A29      ; |130| 
||         ADDU    .L1X    B4,A4,A5:A4       ; |130| 

           ADD     .L2X    A3,B9,B8          ; |130| 
|| [ A0]   B       .S1     $C$L15            ; |225| 
||         ADD     .L1X    A5,B5,A28         ; |130| 
|| [ A0]   MVKL    .S2     0xc01921fb,B5

           SUB     .L2     B7,B8,B8          ; |130| 

   [ A0]   CALL    .S1     _gimme_random     ; |227| 
||         ADD     .L2X    B8,A29,B4         ; |130| 

   [ A0]   MVKH    .S2     0xc01921fb,B5

           ADD     .L1X    A28,B4,A5         ; |130| 
|| [ A0]   MVKL    .S2     0x3fa6defc,B4

   [ A0]   MVKH    .S2     0x3fa6defc,B4
||         STDW    .D1T1   A5:A4,*A13        ; |130| 
|| [ A0]   MVKL    .S1     0x402921fb,A5

           ; BRANCHCC OCCURS {$C$L15}        ; |225| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     __fltllif         ; |135| 
           LDDW    .D1T1   *A13,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL31,B3,3      ; |135| 
$C$RL31:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A11
           SET     .S1     A11,0x15,0x1d,A11
           ZERO    .L1     A10               ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL32:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           LDDW    .D2T2   *+SP(48),B5:B4
           MV      .L2X    A13,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B10
           MV      .L2X    A10,B31           ; |114| 

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MV      .L1X    B4,A14            ; |116| 

           MV      .L1X    B5,A13            ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 

           SUBU    .L2X    B5,A14,B7:B6      ; |117| 
||         MVKL    .S1     _output,A31

           SUB     .L1X    B4,A13,A4         ; |117| 
||         MVK     .S2     0x80,B30
||         MVKH    .S1     _output,A31

           MV      .L1X    B6,A3             ; |117| 
||         EXT     .S2     B7,24,24,B4       ; |117| 
||         STW     .D2T2   B30,*+SP(12)      ; |117| 
||         MV      .S1     A12,A10
||         LDW     .D1T1   *A31,A12

           STW     .D2T1   A3,*+SP(16)       ; |117| 
||         CALL    .S1     __divd            ; |240| 

           ADD     .L1X    A4,B4,A15         ; |117| 
||         LDDW    .D2T2   *B13++,B5:B4      ; |240| 
||         LDDW    .D1T1   *A10++,A5:A4      ; |240| 

           NOP             3
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL33,B3,0      ; |240| 
$C$RL33:   ; CALL OCCURS {__divd} {0}        ; |240| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(12),B4       ; |240| 
           STDW    .D1T1   A5:A4,*A12++      ; |240| 
           NOP             3

           SUB     .L1X    B4,1,A0           ; |239| 
||         SUB     .L2     B4,1,B4           ; |239| 

   [ A0]   B       .S1     $C$L16            ; |239| 
||         STW     .D2T2   B4,*+SP(12)       ; |240| 

   [ A0]   LDDW    .D1T1   *A10++,A5:A4      ; |240| 
|| [ A0]   CALL    .S1     __divd            ; |240| 

   [ A0]   LDDW    .D2T2   *B13++,B5:B4      ; |240| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L16}        ; |239| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 
           LDW     .D2T1   *+SP(16),A3       ; |128| 
           MV      .L2     B4,B7             ; |128| 
           LDDW    .D2T2   *B10,B5:B4        ; |130| 
           STDW    .D2T2   B7:B6,*B11        ; |128| 
           NOP             1
           ADDU    .L1     A3,A14,A5:A4      ; |130| 

           ADD     .S1     A5,A15,A3         ; |130| 
||         SUBU    .L1X    B6,A4,A5:A4       ; |130| 
||         CALL    .S2     __fltllif         ; |130| 

           ADD     .L1     A3,A13,A3         ; |130| 
||         EXT     .S1     A5,24,24,A31      ; |130| 

           ADDU    .L2X    B4,A4,B9:B8       ; |130| 
||         SUB     .L1X    B7,A3,A3          ; |130| 

           ADD     .L2     B9,B5,B4          ; |130| 
||         ADD     .L1     A3,A31,A3         ; |130| 

           MV      .L1X    B8,A4             ; |130| 

           ADD     .L1X    B4,A3,A5          ; |130| 
||         ADDKPC  .S2     $C$RL34,B3,0      ; |130| 

$C$RL34:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL35:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDDW    .D2T2   *+SP(48),B5:B4    ; |130| 
           ZERO    .L1     A12
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           SET     .S1     A12,0x1a,0x1d,A12

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MV      .L1X    B12,A14           ; |116| 

           STDW    .D1T2   B7:B6,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S2     _t_offset,B12

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B8,B7,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 
||         MVKH    .S2     _t_offset,B12

           STDW    .D2T2   B5:B4,*B12        ; |117| 
||         MVKL    .S2     _input,B4

           MVKH    .S2     _input,B4
           LDW     .D2T2   *B4,B4            ; |248| 
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3

           ADD     .L1     4,A3,A13
||         LDW     .D2T1   *+SP(20),A15      ; |117| 
||         MVK     .S2     0x80,B13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D1T1   *A13,A3           ; |248| 
           ADD     .L2X    A10,B4,B4         ; |248| 
           LDDW    .D2T2   *B4,B5:B4         ; |248| 
           NOP             2
           ADD     .L1     A10,A3,A3         ; |248| 

           LDDW    .D1T1   *A3,A5:A4         ; |248| 
||         CALL    .S1     _divdp            ; |248| 

           ADDKPC  .S2     $C$RL36,B3,3      ; |248| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |248| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |248| 

$C$RL36:   ; CALL OCCURS {_divdp} {0}        ; |248| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D1T1   *A15,A3           ; |248| 
||         SUB     .L1X    B13,1,A0          ; |247| 

   [ A0]   MVKL    .S2     _input,B4
|| [ A0]   B       .S1     $C$L17            ; |247| 

   [ A0]   MVKH    .S2     _input,B4
   [ A0]   LDW     .D2T2   *B4,B4            ; |248| 
           SUB     .L2     B13,1,B13         ; |247| 

           ADD     .L1     A10,A3,A3         ; |248| 
||         ADD     .S1     8,A10,A10         ; |247| 

           STDW    .D1T1   A5:A4,*A3         ; |248| 
           ; BRANCHCC OCCURS {$C$L17}        ; |247| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 

           MV      .L2     B4,B9             ; |128| 
           NOP             3
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 

           ADD     .L1X    A7,B7,A3          ; |130| 
||         LDDW    .D2T2   *+B10(8),B7:B6    ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B9,A3,B31         ; |130| 
           CALL    .S1     __fltllif         ; |130| 

           ADDU    .L2     B6,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B6        ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         MV      .S2     B11,B6            ; |130| 

           STDW    .D2T2   B9:B8,*B6         ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL37,B3,0      ; |130| 

$C$RL37:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A12,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL38:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           LDDW    .D2T2   *+SP(48),B5:B4
           ADDAD   .D2     B10,1,B11
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B11        ; |130| 
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

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B6,B9,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 
||         LDW     .D2T1   *+SP(24),A15      ; |117| 

           STDW    .D2T2   B5:B4,*B12        ; |117| 
||         MVKL    .S2     _input,B4
||         MVK     .S1     0x80,A3

           MVKH    .S2     _input,B4
||         STW     .D2T1   A3,*+SP(12)       ; |117| 

           LDW     .D2T2   *B4,B4            ; |256| 
||         LDW     .D1T1   *A13,A3           ; |256| 

           NOP             3
           MV      .L2X    A15,B13           ; |256| 

           ADD     .L2X    A10,B4,B4         ; |256| 
||         ADD     .L1     A10,A3,A3         ; |256| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     _divdp_c          ; |256| 
||         LDDW    .D2T2   *B4,B5:B4         ; |256| 
||         LDDW    .D1T1   *A3,A5:A4         ; |256| 

           ADDKPC  .S2     $C$RL39,B3,3      ; |256| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |256| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |256| 

$C$RL39:   ; CALL OCCURS {_divdp_c} {0}      ; |256| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           LDW     .D2T2   *B13,B4           ; |256| 
           LDW     .D2T1   *+SP(12),A3       ; |256| 
           NOP             3

           ADD     .L1X    A10,B4,A6         ; |256| 
||         MVKL    .S2     _input,B4
||         ADD     .S1     8,A10,A10         ; |255| 

           MVKH    .S2     _input,B4
||         SUB     .L1     A3,1,A0           ; |255| 
||         STDW    .D1T1   A5:A4,*A6         ; |256| 

   [ A0]   BNOP    .S1     $C$L18,3          ; |255| 
|| [ A0]   LDW     .D2T2   *B4,B4            ; |256| 
|| [ A0]   LDW     .D1T1   *A13,A3           ; |256| 

           STW     .D2T1   A0,*+SP(12)       ; |256| 

           ADD     .L2X    A10,B4,B4         ; |256| 
|| [ A0]   ADD     .L1     A10,A3,A3         ; |256| 

           ; BRANCHCC OCCURS {$C$L18}        ; |255| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B9           ; |128| 

           MV      .L2     B12,B4            ; |128| 
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B5:B4         ; |130| 
           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           NOP             3
           ADDU    .L2X    B4,A4,B7:B6       ; |130| 

           ADD     .S2     B7,B5,B4          ; |130| 
||         SUBU    .L2     B8,B6,B7:B6       ; |130| 

           ADD     .L2X    B4,A5,B4          ; |130| 
||         MV      .S2     B6,B5             ; |130| 
||         CALL    .S1     __fltllif         ; |130| 

           ADDU    .L2     B16,B5,B7:B6      ; |130| 
||         EXT     .S2     B7,24,24,B5       ; |130| 
||         SUB     .D2     B9,B4,B4          ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B7,B17,B4         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     _t_stop,B4

           MVKH    .S2     _t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL40,B3,0      ; |130| 

$C$RL40:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 114
           MPYSP   .M1     A12,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL41:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           LDDW    .D2T2   *+SP(48),B5:B4
           ADDAD   .D2     B11,1,B12
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B16          ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B17            ; |116| 

           STDW    .D1T2   B17:B16,*A14      ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 

           MVKL    .S1     _input,A3
||         MV      .D2X    A13,B9            ; |117| 
||         SUBU    .L2     B5,B16,B7:B6      ; |117| 
||         MVKL    .S2     _t_offset,B10

           MVKH    .S1     _input,A3
||         LDW     .D2T1   *+B13(8),A6       ; |263| 
||         SUB     .L2     B4,B17,B30        ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           LDW     .D2T2   *B9,B4            ; |263| 
||         ADD     .L2     B30,B5,B7         ; |117| 
||         MVKH    .S2     _t_offset,B10

           MV      .L2X    A3,B18            ; |263| 
||         STDW    .D2T2   B7:B6,*B10        ; |117| 
||         MVK     .S2     0x80,B6           ; |263| 

           CALLP   .S2     _divdp_v,B3
||         LDW     .D2T1   *B18,A4           ; |263| 

$C$RL42:   ; CALL OCCURS {_divdp_v} {0}      ; |263| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           MVK     .S1     16,A13
           ADD     .L1X    B12,A13,A13
           LDDW    .D1T1   *A13,A17:A16      ; |130| 
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

$C$RL43:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           MPYSP   .M1     A12,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL44:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           MV      .L1     A3,A10            ; |130| 
           LDW     .D1T1   *A10,A3           ; |66| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MVKH    .S2     0xd9d7bdbb,B6
||         STDW    .D1T1   A5:A4,*A13        ; |130| 
||         MVK     .S1     0x80,A6           ; |66| 

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MV      .L1     A3,A4             ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL45:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S1     _fcn_pass,A3
           MVKH    .S1     _fcn_pass,A3
           MVKL    .S2     0xd9d7bdbb,B6

           MV      .L2X    A3,B10            ; |66| 
||         LDW     .D1T1   *+A10(8),A3       ; |67| 

           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6
           MV      .L1     A4,A5             ; |66| 

           LDW     .D1T1   *A10,A4           ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         MV      .L2X    A3,B4             ; |67| 
||         STW     .D2T1   A5,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL46:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           MV      .L1     A4,A3             ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7
||         STW     .D2T1   A3,*+B10(8)       ; |67| 

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL47:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A10,A3            ; |68| 
||         STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *+A10(16),B4      ; |69| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL48:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(36),A3       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D1T1   *A3,A0            ; |72| 
           LDW     .D2T1   *+SP(40),A3
           NOP             3

   [!A0]   B       .S1     $C$L19            ; |72| 
||         MV      .L1     A0,A1             ; guard predicate rewrite

   [ A0]   LDW     .D1T1   *A3,A0            ; |72| 
   [ A1]   ADD     .L1     4,A3,A3
           NOP             3
           ; BRANCHCC OCCURS {$C$L19}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
   [ A0]   LDW     .D1T1   *A3,A3            ; |72| 
           CMPEQ   .L1     A4,0,A4           ; |72| 
           XOR     .L1     1,A4,A4           ; |72| 
           NOP             2
   [ A0]   CMPEQ   .L1     A3,0,A3           ; |72| 
   [ A0]   XOR     .L1     1,A3,A3           ; |72| 

   [ A0]   AND     .L1     A4,A3,A0          ; |72| 
|| [!A0]   ZERO    .S1     A0                ; |72| 

   [ A0]   B       .S1     $C$L20            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |269| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L20}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |269| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           ZERO    .L1     A3                ; |72| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |269| 
||         ADDKPC  .S2     $C$RL49,B3,0      ; |269| 

$C$RL49:   ; CALL OCCURS {_print_test_results} {0}  ; |269| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |270| 

$C$RL50:   ; CALL OCCURS {_printf} {0}       ; |270| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |270| 

$C$RL51:   ; CALL OCCURS {_printf} {0}       ; |270| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |277| 

$C$RL52:   ; CALL OCCURS {_print_profile_results} {0}  ; |277| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |280| 

$C$RL53:   ; CALL OCCURS {_print_memory_results} {0}  ; |280| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(64),B3      ; |281| 
           LDDW    .D2T1   *++SP,A13:A12     ; |281| 
           LDDW    .D2T1   *++SP,A15:A14     ; |281| 
           LDDW    .D2T2   *++SP,B11:B10     ; |281| 
           LDDW    .D2T2   *++SP,B13:B12     ; |281| 

           LDW     .D2T1   *++SP(8),A10      ; |281| 
||         RET     .S2     B3                ; |281| 

           LDW     .D2T1   *++SP(8),A11      ; |281| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |281| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"divDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_divdp
	.global	_divdp_c
	.global	_divdp_v
	.global	_t_start
	.global	_t_stop
	.global	_t_offset
	.global	_cycle_counts
	.global	_fcn_pass
	.global	_all_pass
	.global	_a_ext
	.global	_b_ext
	.global	_a_sc
	.global	_b_sc
	.global	_output
	.global	_input
	.global	__divd
	.global	__fltllif
	.global	__fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
