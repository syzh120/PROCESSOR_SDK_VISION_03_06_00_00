;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:17:47 2013                                *
;******************************************************************************
	.compiler_opts --abi=coffabi --c64p_l1d_workaround=off --endian=little --hll_source=on --long_precision_bits=40 --mem_model:code=near --mem_model:const=data --mem_model:data=far --object_format=coff --silicon_version=6600 --symdebug:none 

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

;*****************************************************************************
;* CINIT RECORDS                                                             *
;*****************************************************************************
	.sect	".cinit"
	.align	8
	.field  	$C$IR_1,32
	.field  	_a+0,32
	.word	0436c665bh,040028220h		; _a[0] @ 0
	.word	0dd18746bh,03ffe598bh		; _a[1] @ 64
	.word	00510e0f9h,0bfb35f8eh		; _a[2] @ 128
	.word	044000a11h,03fec60b0h		; _a[3] @ 192
	.word	0ac99509eh,0bfef5c9bh		; _a[4] @ 256
	.word	081bc2d42h,03fc761b8h		; _a[5] @ 320
	.word	0bf147d66h,0bff1d973h		; _a[6] @ 384
	.word	09c0229a6h,0bff0c5deh		; _a[7] @ 448
	.word	0577e6c17h,03ffa585fh		; _a[8] @ 512
	.word	08f359289h,0bfeba768h		; _a[9] @ 576
	.word	0bb40b34eh,0bfeb4a43h		; _a[10] @ 640
	.word	000713f07h,0bfff1efdh		; _a[11] @ 704
	.word	0595281adh,0c0051cb9h		; _a[12] @ 768
	.word	0841fb4d1h,03fe0b5dbh		; _a[13] @ 832
	.word	033ccb627h,040069340h		; _a[14] @ 896
	.word	09a9b2159h,0bfef61bah		; _a[15] @ 960
	.word	0eec1ea1bh,0c0091385h		; _a[16] @ 1024
	.word	0d01e90e5h,0bffe81e3h		; _a[17] @ 1088
	.word	021f1c250h,0c002914dh		; _a[18] @ 1152
	.word	0f904633ch,03ff06f7eh		; _a[19] @ 1216
	.word	040aaeafbh,04006962dh		; _a[20] @ 1280
	.word	0595281adh,040051cb9h		; _a[21] @ 1344
	.word	0fc0096ffh,03ff20a53h		; _a[22] @ 1408
	.word	0bb3f05cfh,03ff5978dh		; _a[23] @ 1472
	.word	07d8c1cd9h,0c0074d6eh		; _a[24] @ 1536
	.word	0f06a60c7h,0bfff7163h		; _a[25] @ 1600
	.word	061a2b247h,0c004838ch		; _a[26] @ 1664
	.word	0b0a62599h,03ffe47f7h		; _a[27] @ 1728
	.word	0b81585a3h,0c0027386h		; _a[28] @ 1792
	.word	0f19feaech,0c0010d8eh		; _a[29] @ 1856
	.word	036c8132ah,03fdf14bah		; _a[30] @ 1920
	.word	0486d571bh,04005ffedh		; _a[31] @ 1984
	.word	0638e44d2h,03ffeaddah		; _a[32] @ 2048
	.word	0dd93c46eh,03ff508cch		; _a[33] @ 2112
	.word	0e8e1d649h,0c0063d2ah		; _a[34] @ 2176
	.word	058c238f5h,040020395h		; _a[35] @ 2240
	.word	0a33cb08ah,0bff14408h		; _a[36] @ 2304
	.word	086e3b470h,0bfddcddfh		; _a[37] @ 2368
	.word	041d58d66h,0bffee8b9h		; _a[38] @ 2432
	.word	0606092e8h,0c0087b0ch		; _a[39] @ 2496
	.word	0b0a11d1ch,03ff6cfd5h		; _a[40] @ 2560
	.word	09c403d07h,03fe99a2ch		; _a[41] @ 2624
	.word	0b796daa2h,0bfef4ed9h		; _a[42] @ 2688
	.word	03afaa7d1h,03fdf9515h		; _a[43] @ 2752
	.word	02af4a050h,03ff5e0d7h		; _a[44] @ 2816
	.word	0433863f5h,0bff00e16h		; _a[45] @ 2880
	.word	0572c36c0h,03fe44389h		; _a[46] @ 2944
	.word	0ebb418a1h,0bfd64439h		; _a[47] @ 3008
	.word	0b8503e06h,03ff91268h		; _a[48] @ 3072
	.word	01f03d146h,0bff21583h		; _a[49] @ 3136
	.word	055fbb518h,03ffaaf80h		; _a[50] @ 3200
	.word	0daf5847ch,0bffce5c7h		; _a[51] @ 3264
	.word	0e873f240h,040084399h		; _a[52] @ 3328
	.word	02110f1c0h,0c007c609h		; _a[53] @ 3392
	.word	0500a038fh,0bfed84aeh		; _a[54] @ 3456
	.word	0e7ad22e3h,0bffc4a5ah		; _a[55] @ 3520
	.word	0ed51a793h,0bff3d878h		; _a[56] @ 3584
	.word	09fe5e3f5h,03fefb6cfh		; _a[57] @ 3648
	.word	0023711e5h,03fe7344ch		; _a[58] @ 3712
	.word	03c40222fh,03fb10301h		; _a[59] @ 3776
	.word	0e2386edch,0bff3217fh		; _a[60] @ 3840
	.word	0fbfc6541h,0c0037b8ch		; _a[61] @ 3904
	.word	0ebbba55dh,03fb5c86ch		; _a[62] @ 3968
	.word	0cd35a858h,04001ae3bh		; _a[63] @ 4032
	.word	0d5e727c2h,0bff1724ah		; _a[64] @ 4096
	.word	0ac215b9ah,0c00842c6h		; _a[65] @ 4160
	.word	082a48a8eh,03ff6512fh		; _a[66] @ 4224
	.word	0f965b20ch,03ff5ccbah		; _a[67] @ 4288
	.word	092b4a30ah,0bfe635b1h		; _a[68] @ 4352
	.word	0017a5383h,03ff5ab51h		; _a[69] @ 4416
	.word	0ca8e2e2ch,03fec144dh		; _a[70] @ 4480
	.word	038cbf968h,0bff1de57h		; _a[71] @ 4544
	.word	04d940789h,0bff8a2b9h		; _a[72] @ 4608
	.word	019b258adh,0bff75596h		; _a[73] @ 4672
	.word	0b6177ea2h,0bfe76b66h		; _a[74] @ 4736
	.word	078798e61h,03fdfbb2ah		; _a[75] @ 4800
	.word	0c94f69cbh,0bfe33139h		; _a[76] @ 4864
	.word	0b600d86dh,0bfd11ecdh		; _a[77] @ 4928
	.word	0e051e4cfh,03ffdcf53h		; _a[78] @ 4992
	.word	02334b86eh,0c0022328h		; _a[79] @ 5056
	.word	00f0a5effh,0c007dd9ah		; _a[80] @ 5120
	.word	093b04b8dh,03ffcac55h		; _a[81] @ 5184
	.word	0ffac1d2ah,0bfe01873h		; _a[82] @ 5248
	.word	0b85da9ffh,0bfeea818h		; _a[83] @ 5312
	.word	06697e48eh,0c0074e5fh		; _a[84] @ 5376
	.word	0d30e2f6eh,0bfca0063h		; _a[85] @ 5440
	.word	0fd9e25f0h,03fce9e92h		; _a[86] @ 5504
	.word	0bac2084eh,0bff45596h		; _a[87] @ 5568
	.word	05d0fa58fh,0c005cf50h		; _a[88] @ 5632
	.word	0338dcc06h,0bfd8e597h		; _a[89] @ 5696
	.word	0d52205e4h,0c0026bc1h		; _a[90] @ 5760
	.word	0a301f828h,03ffbd526h		; _a[91] @ 5824
	.word	0d8d36b4ch,0bfc60b5eh		; _a[92] @ 5888
	.word	07ba9c48ah,0bfebba09h		; _a[93] @ 5952
	.word	06e1c3d4dh,0400583d1h		; _a[94] @ 6016
	.word	0a464ceb7h,0bff4ba83h		; _a[95] @ 6080
	.word	05569bee0h,0bff1d3a6h		; _a[96] @ 6144
	.word	021583f5ch,03fe4e140h		; _a[97] @ 6208
	.word	07df4f865h,0bff00eddh		; _a[98] @ 6272
	.word	0fbc2839eh,0c0044605h		; _a[99] @ 6336
	.word	0fdb09a67h,0bfe34c64h		; _a[100] @ 6400
	.word	0c02e58d9h,0bff7c0e3h		; _a[101] @ 6464
	.word	07285589ah,03fc7a447h		; _a[102] @ 6528
	.word	085a84b0dh,0c0026037h		; _a[103] @ 6592
	.word	00445dfdeh,0bffba788h		; _a[104] @ 6656
	.word	0fa998eb2h,0c001562fh		; _a[105] @ 6720
	.word	05493d60bh,0bfed5201h		; _a[106] @ 6784
	.word	04fae93fdh,0c00588efh		; _a[107] @ 6848
	.word	0bafd9770h,0c008bdd3h		; _a[108] @ 6912
	.word	0bf45fb8dh,03ffe716ch		; _a[109] @ 6976
	.word	01e1594bdh,0bfe3b48fh		; _a[110] @ 7040
	.word	02e5654a0h,0bff377afh		; _a[111] @ 7104
	.word	0a0217317h,03ff4ff0ch		; _a[112] @ 7168
	.word	046d175a9h,0bfcf0e64h		; _a[113] @ 7232
	.word	0c640c191h,04007e892h		; _a[114] @ 7296
	.word	0389217c5h,0400658d0h		; _a[115] @ 7360
	.word	0f13e9c1dh,040081052h		; _a[116] @ 7424
	.word	0782e0f07h,0c004412ch		; _a[117] @ 7488
	.word	0af17b020h,0c003ec1eh		; _a[118] @ 7552
	.word	0fe9e0031h,03fffd3fdh		; _a[119] @ 7616
	.word	0cb8d31ach,0bffd305dh		; _a[120] @ 7680
	.word	0c1490b0ch,0bfe441aeh		; _a[121] @ 7744
	.word	0a212e4dfh,03fbffad7h		; _a[122] @ 7808
	.word	0bc24081dh,0bfcec198h		; _a[123] @ 7872
	.word	033ca31e8h,0bf8d872fh		; _a[124] @ 7936
	.word	0e757928eh,03ffb9018h		; _a[125] @ 8000
	.word	07491a254h,03ff3eb72h		; _a[126] @ 8064
	.word	0ca1dc5e4h,0c0015eabh		; _a[127] @ 8128
	.word	0d39a4668h,03ff04ac0h		; _a[128] @ 8192
	.word	082bb30c3h,0bfef7dc8h		; _a[129] @ 8256
	.word	0ce131deah,03ffe5413h		; _a[130] @ 8320
	.word	0c2e33effh,040031081h		; _a[131] @ 8384
	.word	059f4681ch,0bff95a54h		; _a[132] @ 8448
	.word	0c33b5393h,04006b6d4h		; _a[133] @ 8512
	.word	0e88eca33h,03ff82ef9h		; _a[134] @ 8576
	.word	0aae79fb7h,0bff1a7d4h		; _a[135] @ 8640
	.word	04cddff24h,03fa0a496h		; _a[136] @ 8704
	.word	074312a44h,0c0010791h		; _a[137] @ 8768
	.word	07ba30e8dh,0c002df31h		; _a[138] @ 8832
	.word	0f0d18ed3h,04005a01ch		; _a[139] @ 8896
	.word	042162505h,0bfe14918h		; _a[140] @ 8960
	.word	099440944h,0bff8bf57h		; _a[141] @ 9024
	.word	033d36c23h,0bff41e18h		; _a[142] @ 9088
	.word	02f166e01h,040006616h		; _a[143] @ 9152
	.word	0282ac175h,03ff19756h		; _a[144] @ 9216
	.word	0b1407f4ch,0bffb015fh		; _a[145] @ 9280
	.word	0f047fc18h,0bff361d0h		; _a[146] @ 9344
	.word	02e9da23dh,04002c2e6h		; _a[147] @ 9408
	.word	08169212ch,03ff31387h		; _a[148] @ 9472
	.word	0cef317bah,03fff65fch		; _a[149] @ 9536
	.word	08c840761h,040057d36h		; _a[150] @ 9600
	.word	030347b32h,03feeac4dh		; _a[151] @ 9664
	.word	054d97628h,03fe46a82h		; _a[152] @ 9728
	.word	0325d4a5eh,0bfde118eh		; _a[153] @ 9792
	.word	02f0e0a85h,03fee8888h		; _a[154] @ 9856
	.word	0b6d6c142h,0bfd1c072h		; _a[155] @ 9920
	.word	07f081ddch,0bff8cb75h		; _a[156] @ 9984
	.word	05baf533fh,0bffb2604h		; _a[157] @ 10048
	.word	07dabfd49h,03ff330f0h		; _a[158] @ 10112
	.word	031cc2ae6h,0bff44f0fh		; _a[159] @ 10176
	.word	0e6347cdfh,0bffbf1bfh		; _a[160] @ 10240
	.word	0f9ca5bd9h,0c0038f62h		; _a[161] @ 10304
	.word	0bf104ba8h,04007eaach		; _a[162] @ 10368
	.word	097d8cf3ah,040054c6ch		; _a[163] @ 10432
	.word	088eaf5adh,03ffdbce8h		; _a[164] @ 10496
	.word	0b124d09ah,03fef1ca4h		; _a[165] @ 10560
	.word	067798bddh,0c001c2feh		; _a[166] @ 10624
	.word	0bb6ed677h,03ffb5cd0h		; _a[167] @ 10688
	.word	08b9fdbd3h,040081c86h		; _a[168] @ 10752
	.word	01f2a67b3h,0c00093ddh		; _a[169] @ 10816
	.word	038433d6ch,03fe05966h		; _a[170] @ 10880
	.word	09a657174h,0c007fafah		; _a[171] @ 10944
	.word	09e4275c6h,0bfa73113h		; _a[172] @ 11008
	.word	0ffe6d58dh,03ff2e755h		; _a[173] @ 11072
	.word	0c41b4d63h,0bfeba8bdh		; _a[174] @ 11136
	.word	01a9e10f8h,03fd9ea79h		; _a[175] @ 11200
	.word	0255a2c9ch,03ffe02fdh		; _a[176] @ 11264
	.word	0f2b08c24h,040076e15h		; _a[177] @ 11328
	.word	075b8e9c1h,0bff54892h		; _a[178] @ 11392
	.word	06327ed85h,0c008d87ch		; _a[179] @ 11456
	.word	03a406daeh,0c006e82bh		; _a[180] @ 11520
	.word	000607810h,0bfc943e1h		; _a[181] @ 11584
	.word	09fe288f7h,040035163h		; _a[182] @ 11648
	.word	02d9b43beh,03ff1c16ah		; _a[183] @ 11712
	.word	0fe2cc129h,0c0032500h		; _a[184] @ 11776
	.word	0fdc08a9fh,0bfe80e25h		; _a[185] @ 11840
	.word	0ed4009dbh,0bfe3c401h		; _a[186] @ 11904
	.word	05d31337fh,03fe8d588h		; _a[187] @ 11968
	.word	0acc26b4ah,03fe89706h		; _a[188] @ 12032
	.word	0233fa029h,03fe64cc7h		; _a[189] @ 12096
	.word	011b386abh,03ffcca3eh		; _a[190] @ 12160
	.word	0489dfe83h,03fe5ce8bh		; _a[191] @ 12224
	.word	0950408a3h,04002e94ch		; _a[192] @ 12288
	.word	0b6cd8707h,03ffca989h		; _a[193] @ 12352
	.word	0b1be538dh,03ff79cb1h		; _a[194] @ 12416
	.word	069e72467h,0c0036765h		; _a[195] @ 12480
	.word	028035448h,040052fa1h		; _a[196] @ 12544
	.word	0515f6e25h,0bffa345bh		; _a[197] @ 12608
	.word	0964db4bfh,03fe9f5ffh		; _a[198] @ 12672
	.word	0d6890e31h,0bfeeafe5h		; _a[199] @ 12736
	.word	0d39614aah,03fb04bf9h		; _a[200] @ 12800
$C$IR_1:	.set	1608

	.sect	".cinit"
	.align	8
	.field  	$C$IR_2,32
	.field  	_b+0,32
	.word	088cd997bh,0c056d077h		; _b[0] @ 0
	.word	08c7ba3e5h,04032bda8h		; _b[1] @ 64
	.word	0c4b24c18h,0c04aeeb9h		; _b[2] @ 128
	.word	06cbf45fch,0c052f071h		; _b[3] @ 192
	.word	0bb63eebdh,0405813b1h		; _b[4] @ 256
	.word	0efc5f619h,0c01e6fb7h		; _b[5] @ 320
	.word	0dfb0d520h,0c0333513h		; _b[6] @ 384
	.word	0fb8978bah,040568659h		; _b[7] @ 448
	.word	02aa341b9h,04021a95ch		; _b[8] @ 512
	.word	0bbbb2c91h,0404d0929h		; _b[9] @ 576
	.word	08c30248bh,0c04b93aah		; _b[10] @ 640
	.word	044383e35h,040548c81h		; _b[11] @ 704
	.word	0ce63a5c2h,04056b2b3h		; _b[12] @ 768
	.word	0e76427c8h,04051996dh		; _b[13] @ 832
	.word	09c3702cch,0404b3243h		; _b[14] @ 896
	.word	073ad76c6h,0403beec2h		; _b[15] @ 960
	.word	05e7d63d9h,0c051b74ch		; _b[16] @ 1024
	.word	0157689cah,0403cc652h		; _b[17] @ 1088
	.word	0553840b9h,04050ffadh		; _b[18] @ 1152
	.word	025fc130bh,0c0119898h		; _b[19] @ 1216
	.word	0c4a332a0h,0404c3153h		; _b[20] @ 1280
	.word	01e166b7ch,040522eeah		; _b[21] @ 1344
	.word	0a1e3eaf7h,0405672efh		; _b[22] @ 1408
	.word	07164c72ah,03fe4d1ffh		; _b[23] @ 1472
	.word	0cb6192c2h,0c04aa0e1h		; _b[24] @ 1536
	.word	05113180bh,04056a002h		; _b[25] @ 1600
	.word	0de1c8069h,0c04131bdh		; _b[26] @ 1664
	.word	0ca940d69h,03fc7e5cah		; _b[27] @ 1728
	.word	0cc48428fh,040326aa2h		; _b[28] @ 1792
	.word	0fcff9a7fh,0c05664e3h		; _b[29] @ 1856
	.word	0ad6f3974h,0405583c0h		; _b[30] @ 1920
	.word	0022c2a2ah,04058082dh		; _b[31] @ 1984
	.word	075d2eaf4h,04040d297h		; _b[32] @ 2048
	.word	0d8ce62cfh,0c057653ch		; _b[33] @ 2112
	.word	037fd9d4fh,0c02ae4e5h		; _b[34] @ 2176
	.word	02ea6dc78h,0c05065cfh		; _b[35] @ 2240
	.word	07afcf660h,0c058f04fh		; _b[36] @ 2304
	.word	043201041h,0c01166c7h		; _b[37] @ 2368
	.word	08d045fe1h,0c04c4c99h		; _b[38] @ 2432
	.word	0f3b56ee2h,0c05857a2h		; _b[39] @ 2496
	.word	06d670ba8h,04050bb89h		; _b[40] @ 2560
	.word	07ef82da4h,04043a5b4h		; _b[41] @ 2624
	.word	0c8d5c747h,0c033f0aeh		; _b[42] @ 2688
	.word	0b4e11dbdh,0c0504ee0h		; _b[43] @ 2752
	.word	01e4c1b62h,0c052012ah		; _b[44] @ 2816
	.word	02a67b297h,040447f1fh		; _b[45] @ 2880
	.word	07f5118f7h,0404f3862h		; _b[46] @ 2944
	.word	0014b599bh,0c0576269h		; _b[47] @ 3008
	.word	048de9623h,0403428eah		; _b[48] @ 3072
	.word	090ad61cdh,0c048a1a8h		; _b[49] @ 3136
	.word	029040548h,0405855e7h		; _b[50] @ 3200
	.word	050184648h,0404314b9h		; _b[51] @ 3264
	.word	08f1c6816h,04038febeh		; _b[52] @ 3328
	.word	0c71a0565h,0404ceda3h		; _b[53] @ 3392
	.word	0c348bf8ch,0c04ddc84h		; _b[54] @ 3456
	.word	03dbc2331h,040579488h		; _b[55] @ 3520
	.word	03bd746a3h,0c040bf92h		; _b[56] @ 3584
	.word	0097e2e03h,03fff2ecbh		; _b[57] @ 3648
	.word	09f44d445h,0c02a468fh		; _b[58] @ 3712
	.word	0c59677a6h,0c0315969h		; _b[59] @ 3776
	.word	066e0dfa9h,0402fa44ch		; _b[60] @ 3840
	.word	0f56b5188h,0c0443330h		; _b[61] @ 3904
	.word	0569cc4c7h,0c035b1c0h		; _b[62] @ 3968
	.word	00c3d2524h,0c04759adh		; _b[63] @ 4032
	.word	0279f813ah,04054dbd4h		; _b[64] @ 4096
	.word	07551bbb4h,0404c0cd9h		; _b[65] @ 4160
	.word	07c4e2f38h,0bfeea3b5h		; _b[66] @ 4224
	.word	0b3ac6a57h,0400c9310h		; _b[67] @ 4288
	.word	06f0c2756h,0403a2d7bh		; _b[68] @ 4352
	.word	081bd0402h,0c0452f13h		; _b[69] @ 4416
	.word	09e774eech,04052fdf8h		; _b[70] @ 4480
	.word	07b1c0011h,04051e9f6h		; _b[71] @ 4544
	.word	02af8d20eh,04045ac9eh		; _b[72] @ 4608
	.word	0ff609dd0h,040529975h		; _b[73] @ 4672
	.word	07368ad69h,0c031a79ch		; _b[74] @ 4736
	.word	02f789390h,0404446adh		; _b[75] @ 4800
	.word	083997d14h,04053c27bh		; _b[76] @ 4864
	.word	08954a7f8h,0c04284b2h		; _b[77] @ 4928
	.word	0cac58b90h,0404028c3h		; _b[78] @ 4992
	.word	07224e08ah,0c05012e6h		; _b[79] @ 5056
	.word	08023a6ceh,040355d9bh		; _b[80] @ 5120
	.word	0848387dfh,0c053cda8h		; _b[81] @ 5184
	.word	000390ae4h,04055cc2ch		; _b[82] @ 5248
	.word	01862cd55h,0c05228e6h		; _b[83] @ 5312
	.word	06e7bde9eh,0c058c657h		; _b[84] @ 5376
	.word	0efde49cdh,0c0254f06h		; _b[85] @ 5440
	.word	026bc2c6ch,0c049d0ffh		; _b[86] @ 5504
	.word	0545acb28h,0c0512955h		; _b[87] @ 5568
	.word	0082c1e6ch,04057408ah		; _b[88] @ 5632
	.word	093972119h,0c0468aabh		; _b[89] @ 5696
	.word	0e8a13eaah,0c04295cbh		; _b[90] @ 5760
	.word	00148d55ch,04014c358h		; _b[91] @ 5824
	.word	0079d8333h,0c054ec9ch		; _b[92] @ 5888
	.word	05fc059f8h,0c04a1a27h		; _b[93] @ 5952
	.word	0200ce5c2h,0403597d7h		; _b[94] @ 6016
	.word	059070253h,0c04996bbh		; _b[95] @ 6080
	.word	0b0b615d1h,040404fb8h		; _b[96] @ 6144
	.word	0fcc5b8dch,040445ddch		; _b[97] @ 6208
	.word	054782759h,0c0448d46h		; _b[98] @ 6272
	.word	0ae7ba8eeh,0c0570c80h		; _b[99] @ 6336
	.word	02684cf07h,04047ea89h		; _b[100] @ 6400
	.word	0b08ea8a5h,04049a403h		; _b[101] @ 6464
	.word	050e0c324h,0c0477eaeh		; _b[102] @ 6528
	.word	092ca727fh,0c03b86efh		; _b[103] @ 6592
	.word	0134988e0h,0c055d9cah		; _b[104] @ 6656
	.word	0bb659c3ch,0c04de2e7h		; _b[105] @ 6720
	.word	0e47e9a3ah,0c052a4b1h		; _b[106] @ 6784
	.word	00af1cb8ah,0c039f144h		; _b[107] @ 6848
	.word	078b87882h,0c05399d3h		; _b[108] @ 6912
	.word	042975445h,04028c1d6h		; _b[109] @ 6976
	.word	0a2cd1f02h,0c04d2ac1h		; _b[110] @ 7040
	.word	0810a569bh,04056585ch		; _b[111] @ 7104
	.word	0a1cac083h,0c0566645h		; _b[112] @ 7168
	.word	0bfd99f43h,0c05571fch		; _b[113] @ 7232
	.word	0d66fe3beh,040281b3bh		; _b[114] @ 7296
	.word	0824264ffh,040440798h		; _b[115] @ 7360
	.word	0c2f405f7h,0404ede9dh		; _b[116] @ 7424
	.word	0f640639dh,04044777ah		; _b[117] @ 7488
	.word	0ad299956h,04055f2bfh		; _b[118] @ 7552
	.word	07f0b78dah,040562661h		; _b[119] @ 7616
	.word	0a0854625h,0c058ce59h		; _b[120] @ 7680
	.word	0f05f790ch,0c0526f44h		; _b[121] @ 7744
	.word	0b02c8316h,04050cf6ch		; _b[122] @ 7808
	.word	0b48d3ae7h,040458c54h		; _b[123] @ 7872
	.word	09513f8dbh,04057658dh		; _b[124] @ 7936
	.word	00918ad76h,040498ac8h		; _b[125] @ 8000
	.word	0a23cd64ah,0c021929dh		; _b[126] @ 8064
	.word	05f7403deh,0404bd3ceh		; _b[127] @ 8128
	.word	0ad7af7eeh,0404b783ah		; _b[128] @ 8192
	.word	089b0ee4ah,04042facch		; _b[129] @ 8256
	.word	0163baba8h,04044b4dbh		; _b[130] @ 8320
	.word	0af5847c0h,040359e7dh		; _b[131] @ 8384
	.word	0053d56a3h,0c04d5b65h		; _b[132] @ 8448
	.word	0b81a8e21h,0404abaa8h		; _b[133] @ 8512
	.word	059ba8679h,0c04917cdh		; _b[134] @ 8576
	.word	0cb2be2ddh,0c0353321h		; _b[135] @ 8640
	.word	089eacfedh,04049c453h		; _b[136] @ 8704
	.word	0bc027a2eh,040250b60h		; _b[137] @ 8768
	.word	024122e00h,0c02d3d00h		; _b[138] @ 8832
	.word	0b26b21b7h,0c0565aebh		; _b[139] @ 8896
	.word	03315d702h,0403c99c2h		; _b[140] @ 8960
	.word	01a3a3de9h,0c042e72ch		; _b[141] @ 9024
	.word	0252a5bf4h,0c041e4bah		; _b[142] @ 9088
	.word	0715908b0h,0c04bd305h		; _b[143] @ 9152
	.word	022050d86h,0404ee37ah		; _b[144] @ 9216
	.word	059b8d8fah,0c0573917h		; _b[145] @ 9280
	.word	0d8680b82h,040479bdeh		; _b[146] @ 9344
	.word	0f1bc705eh,0c04965a4h		; _b[147] @ 9408
	.word	002cab59bh,04054815ch		; _b[148] @ 9472
	.word	01d54a49dh,0c0282ccdh		; _b[149] @ 9536
	.word	068ac91c4h,0c0502598h		; _b[150] @ 9600
	.word	07ad736b3h,0c04e1ad0h		; _b[151] @ 9664
	.word	08b46f07fh,0c04303d8h		; _b[152] @ 9728
	.word	0ef9db22dh,040566da7h		; _b[153] @ 9792
	.word	09a2eeacfh,040530adfh		; _b[154] @ 9856
	.word	0f090f734h,040524e3dh		; _b[155] @ 9920
	.word	02d82194ah,0c0531040h		; _b[156] @ 9984
	.word	0ea8da7f4h,040453574h		; _b[157] @ 10048
	.word	02b5a20deh,0404e72dah		; _b[158] @ 10112
	.word	05de085e7h,04049b5d3h		; _b[159] @ 10176
	.word	0a501aca8h,0c051fe7ch		; _b[160] @ 10240
	.word	0bc54af85h,04033f236h		; _b[161] @ 10304
	.word	01ebe3129h,04036a902h		; _b[162] @ 10368
	.word	0eede6f8ch,0c0541e1bh		; _b[163] @ 10432
	.word	008d66857h,040541133h		; _b[164] @ 10496
	.word	0fe5fecd0h,0c04e45afh		; _b[165] @ 10560
	.word	090a6abd1h,0404472d0h		; _b[166] @ 10624
	.word	0d5629d84h,04050ae20h		; _b[167] @ 10688
	.word	0c75ecec2h,0403f8ac9h		; _b[168] @ 10752
	.word	062ce2b72h,0404e4873h		; _b[169] @ 10816
	.word	0b960df3eh,0c04fa3efh		; _b[170] @ 10880
	.word	072332343h,0403a2f71h		; _b[171] @ 10944
	.word	02bc804e7h,0c038a66bh		; _b[172] @ 11008
	.word	01ef15ccfh,0c0257bb1h		; _b[173] @ 11072
	.word	0f5756283h,0405301f4h		; _b[174] @ 11136
	.word	0b2d4d402h,040526435h		; _b[175] @ 11200
	.word	0ce4ead0ch,040489c50h		; _b[176] @ 11264
	.word	015b9a5a9h,040524bc2h		; _b[177] @ 11328
	.word	016659d13h,0c04066a1h		; _b[178] @ 11392
	.word	06aa9c206h,0403e17ddh		; _b[179] @ 11456
	.word	005ab3aach,0c0505376h		; _b[180] @ 11520
	.word	0ddb6291ch,04013305fh		; _b[181] @ 11584
	.word	098d1f37dh,040500affh		; _b[182] @ 11648
	.word	05a1016ceh,0404cf00fh		; _b[183] @ 11712
	.word	07490cb95h,0404be517h		; _b[184] @ 11776
	.word	014f483cbh,040349239h		; _b[185] @ 11840
	.word	061a45fc6h,0c041ef42h		; _b[186] @ 11904
	.word	046eaa01ch,04050ef8eh		; _b[187] @ 11968
	.word	062a1b5c8h,0c032b39ch		; _b[188] @ 12032
	.word	0746d9026h,04058a9a9h		; _b[189] @ 12096
	.word	0a5467606h,0401adf22h		; _b[190] @ 12160
	.word	0290eed03h,0c056bb06h		; _b[191] @ 12224
	.word	012315aech,04038d190h		; _b[192] @ 12288
	.word	07cc6243ch,0c0423a8ah		; _b[193] @ 12352
	.word	0cfdb7506h,0405349f3h		; _b[194] @ 12416
	.word	0794ea077h,0c0372d74h		; _b[195] @ 12480
	.word	012dace17h,040446d5eh		; _b[196] @ 12544
	.word	09f5c513ah,040548e03h		; _b[197] @ 12608
	.word	0f06e9285h,04002b02ah		; _b[198] @ 12672
	.word	0a70d1fa3h,040270dcch		; _b[199] @ 12736
	.word	04ff5e199h,0403f0a26h		; _b[200] @ 12800
$C$IR_2:	.set	1608

	.global	_a
_a:	.usect	".far",1608,8
	.global	_b
_b:	.usect	".far",1608,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\133082 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\133084 
	.sect	".text:optci"
	.clink

;******************************************************************************
;* FUNCTION NAME: atandpMod_atan2dpi                                          *
;*                                                                            *
;*   Regs Modified     : A0,A1,A3,A4,A5,A6,A7,A8,A9,B0,B1,B4,B5,B6,B7,B8,B9,  *
;*                           A16,A17,A18,A19,A20,A21,A22,A23,B16,B17          *
;*   Regs Used         : A0,A1,A3,A4,A5,A6,A7,A8,A9,B0,B1,B3,B4,B5,B6,B7,B8,  *
;*                           B9,A16,A17,A18,A19,A20,A21,A22,A23,B16,B17       *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
_atandpMod_atan2dpi:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 173
           ZERO    .L2     B5:B4             ; |87| 

           CMPLTDP .S2X    A5:A4,B5:B4,B0    ; |87| 
||         ZERO    .L1     A3                ; |88| 

           SET     .S1     A3,31,31,A3       ; |88| 
   [ B0]   XOR     .L1     A5,A3,A5          ; |88| 
           RCPDP   .S1     A5:A4,A7:A6       ; |57| 
           ZERO    .L2     B5
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |57| 
           SET     .S2     B5,0x1e,0x1e,B5
           ZERO    .L2     B4                ; |57| 
           ZERO    .L1     A17
           SET     .S1     A17,0x14,0x1d,A17
           FSUBDP  .L2X    B5:B4,A9:A8,B7:B6 ; |57| 
           MV      .L1X    B4,A8             ; |57| 
           MV      .L1X    B5,A9             ; |57| 
           FMPYDP  .M2X    A7:A6,B7:B6,B7:B6 ; |57| 
           ZERO    .L1     A16               ; |57| 
           CMPGTDP .S1     A5:A4,A17:A16,A1  ; |92| 
           MV      .L1X    B5,A21            ; |57| 
           FMPYDP  .M2X    A5:A4,B7:B6,B9:B8 ; |57| 
           ZERO    .L1     A20               ; |57| 
           MV      .L1X    B5,A23            ; |57| 
           ZERO    .L1     A22               ; |57| 
           FSUBDP  .L2     B5:B4,B9:B8,B9:B8 ; |57| 
           ZERO    .L1     A3                ; |57| 
   [ A1]   MVK     .L1     0x2,A3            ; |94| 
           FMPYDP  .M2     B7:B6,B9:B8,B7:B6 ; |57| 
           MVKL    .S2     0x3ffbb67a,B9
           MVKL    .S2     0xe8584caa,B8
           MVKH    .S2     0x3ffbb67a,B9
           MVKH    .S2     0xe8584caa,B8
           FMPYDP  .M1X    A5:A4,B7:B6,A7:A6 ; |57| 
           MVK     .L2     0xffffffff,B1     ; |83| 
   [ B0]   MV      .L2X    A22,B1            ; |83| 
           NOP             1
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |57| 
           NOP             2
   [ A1]   FMPYDP  .M1X    B7:B6,A7:A6,A5:A4 ; |57| 
           NOP             3
           FADDDP  .L1X    B9:B8,A5:A4,A7:A6 ; |57| 
           NOP             2
           RCPDP   .S1     A7:A6,A9:A8       ; |57| 
           NOP             1
           FMPYDP  .M1     A9:A8,A7:A6,A19:A18 ; |57| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A19:A18,B7:B6 ; |57| 
           NOP             2
           FMPYDP  .M2X    A9:A8,B7:B6,B7:B6 ; |57| 
           NOP             4
           FMPYDP  .M1X    B7:B6,A7:A6,A9:A8 ; |57| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A9:A8,B17:B16 ; |57| 
           MVKL    .S1     0x404dca0a,A9
           MVKL    .S1     0x320da3d7,A8
           FMPYDP  .M2     B7:B6,B17:B16,B7:B6 ; |57| 
           FMPYDP  .M2X    B9:B8,A5:A4,B17:B16 ; |57| 
           MVKH    .S1     0x404dca0a,A9
           MVKH    .S1     0x320da3d7,A8
           NOP             1
           FMPYDP  .M1X    B7:B6,A7:A6,A7:A6 ; |57| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A7:A6,B9:B8 ; |57| 
           MVKL    .S1     0x3fd12614,A7
           MVKL    .S1     0x5e9ecd56,A6
           FMPYDP  .M2     B7:B6,B9:B8,B7:B6 ; |57| 
           FSUBDP  .L2X    B17:B16,A17:A16,B9:B8 ; |57| 
           MVKH    .S1     0x3fd12614,A7
           MVKH    .S1     0x5e9ecd56,A6
           FMPYDP  .M2     B9:B8,B7:B6,B7:B6 ; |57| 
           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |97| 
           MVKL    .S2     0xb9e2bccb,B8
           MVKL    .S2     0xc034817f,B9
           MVKH    .S2     0xb9e2bccb,B8
   [ A0]   DADD    .L1X    0,B7:B6,A5:A4     ; |57| 
           ABSDP   .S1     A5:A4,A7:A6       ; |57| 
           MVKL    .S2     0x402e0c49,B7

           FMPYDP  .M1     A7:A6,A7:A6,A17:A16 ; |57| 
||         MVKL    .S2     0xe14ac710,B6

           MVKH    .S2     0x402e0c49,B7
           MVKH    .S2     0xe14ac710,B6
           MVKH    .S2     0xc034817f,B9
           FADDDP  .L1X    B7:B6,A17:A16,A7:A6 ; |57| 
           MVKL    .S2     0x40558a12,B7
           MVKL    .S2     0x40b6da5,B6
           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |57| 
           MVKH    .S2     0x40558a12,B7
           MVKH    .S2     0x40b6da5,B6
   [ A0]   ADD     .L1     1,A3,A3           ; |98| 
           FADDDP  .L1     A9:A8,A7:A6,A7:A6 ; |57| 
           CMPLT   .L1     A3,2,A0           ; |113| 
           NOP             1
           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |57| 
           NOP             3
           FADDDP  .L1X    B7:B6,A7:A6,A9:A8 ; |57| 
           MVKL    .S1     0x4044887c,A7
           MVKL    .S1     0xbcc495a9,A6
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |57| 
           MVKH    .S1     0x4044887c,A7
           MVKH    .S1     0xbcc495a9,A6
           MVKL    .S2     0xbfeacd7a,B7
           FADDDP  .L1     A7:A6,A9:A8,A9:A8 ; |57| 
           MVKL    .S2     0xd9b187bd,B6
           MVKH    .S2     0xbfeacd7a,B7
           RCPDP   .S1     A9:A8,A7:A6       ; |57| 
           MVKH    .S2     0xd9b187bd,B6
           FMPYDP  .M1     A7:A6,A9:A8,A19:A18 ; |57| 
           FMPYDP  .M2X    B7:B6,A17:A16,B7:B6 ; |57| 
           NOP             2
           FSUBDP  .L1     A21:A20,A19:A18,A19:A18 ; |57| 
           MVKL    .S1     0x5c8d6a63,A20
           MVKL    .S1     0xc020fd3f,A21
           FMPYDP  .M1     A7:A6,A19:A18,A19:A18 ; |57| 
           MVKH    .S1     0x5c8d6a63,A20
           MVKH    .S1     0xc020fd3f,A21
           FADDDP  .L1X    A21:A20,B7:B6,A7:A6 ; |57| 
           FMPYDP  .M1     A19:A18,A9:A8,A21:A20 ; |57| 
           NOP             2
           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |57| 
           FSUBDP  .L1     A23:A22,A21:A20,A21:A20 ; |57| 
           NOP             2

           FMPYDP  .M1     A21:A20,A19:A18,A19:A18 ; |57| 
||         FADDDP  .L1X    B9:B8,A7:A6,A7:A6 ; |57| 

           MVKL    .S1     0xc02b60a6,A21
           MVKL    .S1     0x51061ce2,A20
           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |57| 
           FMPYDP  .M1     A19:A18,A9:A8,A9:A8 ; |57| 
           MVKH    .S1     0xc02b60a6,A21
           MVKH    .S1     0x51061ce2,A20
           FADDDP  .L1     A21:A20,A7:A6,A7:A6 ; |57| 
           NOP             1
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |57| 
           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |57| 
           NOP             1
           FMPYDP  .M2X    A19:A18,B5:B4,B5:B4 ; |57| 
           NOP             3
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |57| 
           MVKL    .S1     _V,A6
           MVKH    .S1     _V,A6
           LDDW    .D1T1   *+A6[A3],A7:A6    ; |117| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |110| 
           NOP             4

           MV      .L2X    A22,B4            ; |110| 
||         FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |110| 

           SET     .S2     B4,31,31,B4       ; |114| 
           RET     .S2     B3                ; |124| 
   [!A0]   XOR     .L1X    A5,B4,A5          ; |114| 

           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |117| 
||         MV      .L2X    A22,B4            ; |117| 

           SET     .S2     B4,31,31,B4       ; |120| 
           NOP             1
   [!B1]   XOR     .L1X    A5,B4,A5          ; |120| 
           ; BRANCH OCCURS {B3}              ; |124| 
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
;*   Local Frame Size  : 8 Args + 84 Auto + 56 Save = 148 byte                *
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

           STW     .D2T2   B3,*SP--(104)     ; |133| 
||         CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _a,A10

           MVKL    .S2     _b,B13
||         MVKL    .S1     _output,A15

           MVKH    .S1     _a,A10
||         MVK     .S2     0xc9,B4

           MVKH    .S2     _b,B13
||         MVKH    .S1     _output,A15

           MV      .L2     B13,B10
||         MV      .L1     A10,A12
||         CALL    .S1     _atan2            ; |151| 
||         LDW     .D1T1   *A15,A11

           LDDW    .D1T1   *A12++,A5:A4      ; |151| 
||         MV      .L1X    B4,A13
||         LDDW    .D2T2   *B10++,B5:B4      ; |151| 

           NOP             3
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL1,B3,0       ; |151| 
$C$RL1:    ; CALL OCCURS {_atan2} {0}        ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A13,1,A0          ; |150| 
||         STDW    .D1T1   A5:A4,*A11++      ; |151| 
||         SUB     .S1     A13,1,A13         ; |150| 

   [!A0]   MV      .L2     B13,B10
|| [ A0]   B       .S1     $C$L1             ; |150| 
|| [ A0]   LDDW    .D2T2   *B10++,B5:B4      ; |151| 
|| [ A0]   LDDW    .D1T1   *A12++,A5:A4      ; |151| 

   [ A0]   CALL    .S1     _atan2            ; |151| 
   [!A0]   MV      .L1     A10,A14
   [!A0]   MVK     .S1     0xc9,A11
   [!A0]   ADD     .L2X    4,A15,B12
   [!A0]   ZERO    .L2     B11
           ; BRANCHCC OCCURS {$C$L1}         ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _atan2dp          ; |154| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D2T2   *B10++,B5:B4      ; |154| 
||         LDDW    .D1T1   *A10++,A5:A4      ; |154| 

           ADDKPC  .S2     $C$RL2,B3,3       ; |154| 
$C$RL2:    ; CALL OCCURS {_atan2dp} {0}      ; |154| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |154| 
||         SUB     .L1     A11,1,A0          ; |153| 
||         SUB     .S1     A11,1,A11         ; |153| 

   [ A0]   BNOP    .S2     $C$L2,3           ; |153| 
|| [!A0]   ZERO    .L2     B10
|| [!A0]   ADD     .D2     4,B12,B12
|| [!A0]   MVK     .S1     0xc9,A11
|| [!A0]   MV      .L1     A14,A10

           ADD     .L2     B11,B4,B4         ; |154| 
||         ADD     .S2     8,B11,B11         ; |153| 

   [ A0]   CALL    .S1     _atan2dp          ; |154| 
|| [!A0]   MV      .L2     B13,B11
||         STDW    .D2T1   A5:A4,*B4         ; |154| 

           ; BRANCHCC OCCURS {$C$L2}         ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _atan2dp_c        ; |157| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D2T2   *B11++,B5:B4      ; |157| 
||         LDDW    .D1T1   *A10++,A5:A4      ; |157| 

           ADDKPC  .S2     $C$RL3,B3,3       ; |157| 
$C$RL3:    ; CALL OCCURS {_atan2dp_c} {0}    ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |157| 
||         SUB     .L1     A11,1,A0          ; |156| 
||         SUB     .S1     A11,1,A11         ; |156| 

   [!A0]   MVKL    .S1     0x54442d18,A31
|| [!A0]   ZERO    .L1     A13
|| [!A0]   ZERO    .D1     A30               ; |57| 
|| [ A0]   B       .S2     $C$L3             ; |156| 

   [!A0]   MVKL    .S1     0x400921fb,A3
|| [!A0]   MVKL    .S2     0xffefffff,B11

   [!A0]   MVKH    .S1     0x54442d18,A31
   [!A0]   SET     .S1     A13,0x1e,0x1e,A13

           ADD     .L2     B10,B4,B4         ; |157| 
||         ADD     .S2     8,B10,B10         ; |156| 
|| [!A0]   MVKH    .S1     0x400921fb,A3

           STDW    .D2T1   A5:A4,*B4         ; |157| 
|| [!A0]   MVK     .L2     0xffffffff,B10    ; |161| 
|| [!A0]   ADD     .S2     4,B12,B4
|| [ A0]   CALL    .S1     _atan2dp_c        ; |157| 

           ; BRANCHCC OCCURS {$C$L3}         ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

           MVKL    .S1     0x7fefffff,A11
||         STW     .D2T1   A30,*+SP(56)
||         SUB     .L1X    B13,8,A28
||         ZERO    .D1     A26               ; |57| 
||         MVK     .S2     0xc9,B2
||         SUB     .L2X    A14,8,B23

           MV      .L1X    B10,A10           ; |161| 
||         MVKH    .S1     0x7fefffff,A11
||         STW     .D2T1   A13,*+SP(60)      ; |57| 
||         ZERO    .D1     A12               ; |57| 
||         MVKH    .S2     0xffefffff,B11
||         ZERO    .L2     B22               ; |57| 

           STW     .D2T1   A3,*+SP(68)       ; |148| 
||         MV      .L1     A13,A27           ; |57| 

           STW     .D2T1   A31,*+SP(64)      ; |148| 
           STW     .D2T2   B4,*+SP(16)
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 47
           LDDW    .D1T1   *++A28,A25:A24    ; |140| 
           LDDW    .D2T1   *+SP(56),A9:A8
           LDDW    .D2T2   *++B23,B19:B18    ; |139| 
           NOP             2
           RCPDP   .S1     A25:A24,A5:A4     ; |57| 
           NOP             1
           FMPYDP  .M1     A5:A4,A25:A24,A7:A6 ; |57| 
           NOP             3
           FSUBDP  .L1     A13:A12,A7:A6,A7:A6 ; |57| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |57| 
           NOP             3
           FMPYDP  .M1     A5:A4,A25:A24,A7:A6 ; |57| 
           NOP             3
           FSUBDP  .L1     A27:A26,A7:A6,A7:A6 ; |57| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |57| 
           NOP             3
           FMPYDP  .M1     A5:A4,A25:A24,A7:A6 ; |57| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |57| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |57| 
           NOP             4

           FMPYDP  .M2X    B19:B18,A5:A4,B21:B20 ; |57| 
||         CALL    .S1     _atandpMod_atan2dpi ; |142| 

           ADDKPC  .S2     $C$RL4,B3,3       ; |142| 
           DADD    .L1X    0,B21:B20,A5:A4   ; |142| 
$C$RL4:    ; CALL OCCURS {_atandpMod_atan2dpi} {0}  ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 37

           ZERO    .L2     B5:B4             ; |145| 
||         DADD    .L1     0,A5:A4,A7:A6     ; |143| 
||         LDW     .D2T2   *+SP(16),B27      ; |159| 
||         CMPGTDP .S1X    B21:B20,A11:A10,A0 ; |158| 
||         SUB     .S2     B2,1,B2           ; |159| 

           CMPLTDP .S2X    A25:A24,B5:B4,B0  ; |145| 
||         ZERO    .L2     B7:B6             ; |152| 

           ZERO    .L2     B5:B4             ; |147| 

   [ B0]   CMPGTDP .S2X    A5:A4,B5:B4,B1    ; |147| 
|| [ B0]   MVKL    .S1     0x54442d18,A8
|| [!B0]   ZERO    .L2     B1                ; |147| 

   [ B0]   MVKL    .S1     0x400921fb,A9
||         ZERO    .L2     B5:B4             ; |152| 

   [ B0]   MVKH    .S1     0x54442d18,A8
||         CMPGTDP .S2     B19:B18,B7:B6,B6  ; |152| 

   [ B0]   MVKH    .S1     0x400921fb,A9

   [ B0]   FADDDP  .L1     A9:A8,A7:A6,A7:A6 ; |146| 
|| [ B1]   LDDW    .D2T1   *+SP(64),A9:A8    ; |146| 

           XOR     .L2     1,B6,B29          ; |152| 
           CMPEQDP .S2X    A25:A24,B5:B4,B4  ; |152| 
           ZERO    .L2     B7:B6             ; |155| 
           CMPLTDP .S2X    A25:A24,B7:B6,B28 ; |155| 

   [ B1]   FSUBDP  .S1     A5:A4,A9:A8,A7:A6 ; |148| 
||         ZERO    .L1     A5:A4             ; |153| 

           AND     .L2     B4,B29,B1         ; |152| 
           CMPGTDP .S2X    B19:B18,A5:A4,B5  ; |153| 

           ZERO    .L1     A5:A4             ; |155| 
|| [ B1]   MVKL    .S1     0xbff921fb,A7

   [ B1]   MVKL    .S1     0x54442d18,A6
   [ B1]   MVKH    .S1     0xbff921fb,A7

   [ B1]   MVKH    .S1     0x54442d18,A6
||         AND     .L2     B4,B5,B1          ; |153| 
||         CMPEQDP .S2X    B19:B18,A5:A4,B4  ; |155| 
||         XOR     .D2     1,B28,B5          ; |155| 

   [ B1]   MVKL    .S1     0x3ff921fb,A7

   [ B1]   MVKL    .S1     0x54442d18,A6
||         AND     .L2     B0,B4,B0          ; |156| 

   [ B1]   MVKH    .S1     0x3ff921fb,A7

   [ B1]   MVKH    .S1     0x54442d18,A6
||         AND     .L2     B4,B5,B1          ; |155| 
||         LDW     .D2T2   *B27,B4           ; |160| 

   [ B1]   ZERO    .L1     A7:A6             ; |156| 
||         CMPLTDP .S2     B21:B20,B11:B10,B1 ; |161| 

   [ B0]   MVKL    .S1     0x54442d18,A6
|| [!B2]   MV      .L2X    A15,B10

   [ B0]   MVKL    .S1     0x400921fb,A7
   [ B0]   MVKH    .S1     0x54442d18,A6

   [ B0]   MVKH    .S1     0x400921fb,A7
||         ADD     .L2     B22,B4,B4         ; |160| 
||         ADD     .S2     8,B22,B22         ; |159| 

   [ A0]   MVKL    .S1     0x54442d18,A6
   [ A0]   MVKL    .S1     0x3ff921fb,A7
   [ A0]   MVKH    .S1     0x54442d18,A6

   [ B2]   B       .S2     $C$L4             ; |159| 
|| [ A0]   MVKH    .S1     0x3ff921fb,A7

   [ B1]   MVKL    .S1     0x54442d18,A6
   [ B1]   MVKL    .S1     0xbff921fb,A7
   [ B1]   MVKH    .S1     0x54442d18,A6
   [ B1]   MVKH    .S1     0xbff921fb,A7

   [!B2]   CALL    .S1     _atan2dp_v        ; |162| 
||         STDW    .D2T1   A7:A6,*B4         ; |160| 

           ; BRANCHCC OCCURS {$C$L4}         ; |159| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T1   *+B10(16),A6      ; |162| 
           MVK     .S2     0xc9,B6           ; |162| 
           MV      .L2     B13,B4            ; |162| 
           MV      .L1     A14,A4            ; |162| 
           ADDKPC  .S2     $C$RL5,B3,0       ; |162| 
$C$RL5:    ; CALL OCCURS {_atan2dp_v} {0}    ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     0x3e112e0b,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3e112e0b,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3e112e0b,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xe826d695,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3e112e0b,B7

           STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL8:    ; CALL OCCURS {_isequal} {0}      ; |68| 

           LDW     .D2T1   *+SP(16),A3       ; |68| 
||         MVKL    .S2     _fcn_pass,B4

           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7
           MVKH    .S2     _fcn_pass,B4

           MV      .L1     A15,A31           ; |69| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xe826d695,B6

           ADD     .L1     4,A3,A3
||         LDW     .D1T1   *A31,A4           ; |69| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         STW     .D2T1   A3,*+SP(20)
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL9:    ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     _fcn_pass,B4

           MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     _fcn_pass,B4

           ADD     .L1     4,A3,A3
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           ADD     .L2     8,B4,B4
           STW     .D2T2   B4,*+SP(28)       ; |69| 
           STW     .D2T1   A3,*+SP(24)

   [!A0]   B       .S1     $C$L5             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |166| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S2     _all_pass,B5
   [!A0]   MV      .L2X    A12,B4
   [!A0]   MVKH    .S2     _all_pass,B5
           ; BRANCHCC OCCURS {$C$L5}         ; |72| 
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
           CALL    .S1     _print_test_results ; |166| 
           MVKL    .S2     _all_pass,B5
           MVKH    .S2     _all_pass,B5
           NOP             2
;** --------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |166| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL10,B3,0      ; |166| 

$C$RL10:   ; CALL OCCURS {_print_test_results} {0}  ; |166| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S1     _a_sc,A3

           MVKH    .S1     _a_sc,A3
||         MVKL    .S2     _b_sc,B5

           MVKH    .S2     _b_sc,B5

           ADDAD   .D2     B5,5,B6
||         MV      .L2X    A3,B4             ; |173| 

           ADDAD   .D2     B4,5,B7
||         ZERO    .L1     A5
||         MV      .S1     A12,A6            ; |176| 
||         ADD     .D1     1,A11,A7

           STDW    .D2T1   A7:A6,*+B5(16)    ; |175| 
||         MVKH    .S1     0x80000000,A5
||         ZERO    .L2     B17
||         MV      .L1     A12,A4            ; |176| 

           STDW    .D2T1   A5:A4,*+B5(8)     ; |174| 
||         SET     .S2     B17,0x14,0x1d,B17
||         ZERO    .L2     B16               ; |177| 

           STDW    .D2T2   B17:B16,*+B5(32)  ; |177| 

           STDW    .D2T2   B17:B16,*+B4(32)  ; |177| 
||         MV      .L2X    A12,B8
||         ADD     .S2     1,B11,B9

           STDW    .D2T1   A5:A4,*+B4(8)     ; |174| 

           STDW    .D2T1   A7:A6,*+B4(16)    ; |175| 
||         DADD    .L1X    0,B9:B8,A9:A8     ; |176| 

           STDW    .D2T1   A9:A8,*+B4(24)    ; |176| 
||         MVK     .L2     0x4,B31           ; |179| 

           STDW    .D2T1   A9:A8,*+B5(24)    ; |176| 
||         ZERO    .L2     B9:B8             ; |173| 

           MVK     .L2     0x5,B4            ; |180| 
||         STDW    .D2T2   B9:B8,*B4         ; |173| 
||         MV      .L1X    B31,A1            ; |179| 

           MVC     .S2     B4,RILC
||         MVK     .L2     4,B5              ; |180| 
||         STDW    .D2T2   B9:B8,*B5         ; |173| 
||         SUB     .L1     A1,1,A1           ; |179| 
||         MV      .S1X    B5,A14            ; |173| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/atan2dp/atan2dp_d.c
;*      Loop source line                 : 180
;*      Loop opening brace source line   : 180
;*      Loop closing brace source line   : 184
;*      Known Minimum Trip Count         : 5                    
;*      Known Maximum Trip Count         : 5                    
;*      Known Max Trip Count Factor      : 5
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
;*      Total cycles (est.)         : 6 + min_trip_cnt * 6 = 36        
;*----------------------------------------------------------------------------*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C113:
;*   0              ADD     .L1     A4,A3,A7          ; |182| 
;*   1              CMPGT   .L1     A7,4,A0           ; |182| 
;*   2      [ A0]   MVK     .S1     0xffffffd8,A7     ; |182| 
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
;*     ||           SPBR            $C$C113
;*  11              NOP             1
;*  12              ; BRANCHCC OCCURS {$C$C113}       ; |180| 
;*----------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP PROLOG
;          EXCLUSIVE CPU CYCLES: 7

   [ A1]   SPLOOPD 6       ;12               ; SPRELOAD
||         MVK     .L1     0x1,A3            ; |179| 
||         ZERO    .S1     A4                ; |180| 
||         MVC     .S2     B5,ILC

;** --------------------------------------------------------------------------*
$C$L7:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 6

           SPMASK          L2
||         MVK     .L2     0x8,B9
||         ADD     .L1     A4,A3,A7          ; |182| (P) <0,0> 

           SPMASK          S2
||         MVKL    .S2     _a_sc,B8
||         CMPGT   .L1     A7,4,A0           ; |182| (P) <0,1> 

           SPMASK          L1,S2,D2
||         STDW    .D2T2   B17:B16,*+SP(48)  ; |177| 
||         MVKH    .S2     _a_sc,B8
||         MV      .L1X    B9,A5
|| [!A0]   ZERO    .D1     A7                ; |182| (P) <0,2> 
|| [ A0]   MVK     .S1     0xffffffd8,A7     ; |182| (P) <0,2> 

           SPMASK          S1
||         MV      .S1     A14,A6
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
$C$L8:    ; PIPED LOOP EPILOG AND PROLOG
;          EXCLUSIVE CPU CYCLES: 9
           NOP             2

           SPMASKR         ;$C$L8
||         ZERO    .S1     A4                ; |180| 
||         ADD     .D1     1,A3,A3           ; |179| 

           ADD     .L2     8,B9,B9           ; |179| 
|| [ A1]   B       .S2     $C$L8             ; |179| 

           MV      .S1     A6,A14
||         MVKL    .S2     _a_sc,B8
||         SUB     .D1     A1,1,A1           ; |179| 

           MVKH    .S2     _a_sc,B8
||         MV      .L1X    B9,A5

           MV      .S1     A14,A6
||         MVK     .L2     0x5,B4            ; |180| 
||         MVK     .S2     4,B5              ; |180| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L8}         ; |179| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           LDW     .D2T1   *+SP(64),A30      ; |57| 
           LDW     .D2T1   *+SP(68),A31      ; |158| 
           LDW     .D2T1   *+SP(16),A3

           STW     .D2T1   A13,*+SP(84)      ; |57| 
||         ZERO    .L1     A28               ; |57| 

           STW     .D2T1   A28,*+SP(72)

           STW     .D2T1   A28,*+SP(80)
||         MV      .L1     A13,A29           ; |57| 

           STW     .D2T1   A29,*+SP(76)      ; |57| 
||         MVK     .S2     0x19,B31          ; |187| 

           STW     .D2T2   B31,*+SP(12)

           STW     .D2T1   A30,*+SP(88)      ; |57| 
||         MVKL    .S2     _a_sc,B4

           STW     .D2T1   A31,*+SP(92)      ; |57| 
||         MVKH    .S2     _a_sc,B4

           STW     .D2T1   A3,*+SP(32)       ; |161| 
||         SUB     .L2     B4,8,B13
||         MVK     .S2     0xffffffff,B10    ; |161| 
||         SUB     .L1     A14,8,A15

           CALL    .S1     _atan2            ; |189| 
||         LDDW    .D2T2   *++B13,B5:B4      ; |189| 
||         LDDW    .D1T1   *++A15,A5:A4      ; |189| 

           MV      .L1X    B10,A10           ; |161| 
||         ZERO    .S1     A12               ; |57| 
||         ZERO    .L2     B12               ; |57| 

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
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL11,B3,2      ; |189| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |189| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |189| 

$C$RL11:   ; CALL OCCURS {_atan2} {0}        ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 96
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           LDW     .D1T1   *A3,A3            ; |189| 
           NOP             4
           ADD     .L1X    B12,A3,A3         ; |189| 
           STDW    .D1T1   A5:A4,*A3         ; |189| 
           LDDW    .D2T2   *B13,B7:B6        ; |190| 
           LDDW    .D1T2   *A15,B5:B4        ; |190| 
           NOP             3

           DADD    .L1X    0,B7:B6,A5:A4     ; |190| 
||         CALLP   .S2     _atan2dp,B3

$C$RL12:   ; CALL OCCURS {_atan2dp} {0}      ; |190| 
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           LDW     .D1T1   *+A3(4),A3        ; |190| 
           NOP             4
           ADD     .L2X    B12,A3,B4         ; |190| 
           STDW    .D2T1   A5:A4,*B4         ; |190| 

           CALLP   .S2     _atan2dp_c,B3
||         LDDW    .D1T2   *A15,B5:B4        ; |191| 
||         LDDW    .D2T1   *B13,A5:A4        ; |191| 

$C$RL13:   ; CALL OCCURS {_atan2dp_c} {0}    ; |191| 
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           LDW     .D1T1   *+A3(8),A3        ; |191| 
           NOP             4
           ADD     .L1X    B12,A3,A3         ; |191| 
           STDW    .D1T1   A5:A4,*A3         ; |191| 
           LDDW    .D1T1   *A15,A25:A24      ; |140| 
           LDDW    .D2T1   *+SP(72),A5:A4
           LDDW    .D2T2   *B13,B21:B20      ; |139| 
           NOP             2
           RCPDP   .S1     A25:A24,A7:A6     ; |57| 
           NOP             1
           FMPYDP  .M1     A7:A6,A25:A24,A9:A8 ; |57| 
           NOP             3
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |57| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |57| 
           NOP             3
           FMPYDP  .M1     A5:A4,A25:A24,A7:A6 ; |57| 
           NOP             3
           FSUBDP  .L1     A13:A12,A7:A6,A7:A6 ; |57| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |57| 
           LDDW    .D2T1   *+SP(80),A7:A6
           NOP             2
           FMPYDP  .M1     A5:A4,A25:A24,A9:A8 ; |57| 
           NOP             3
           FSUBDP  .L1     A7:A6,A9:A8,A7:A6 ; |57| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |57| 
           NOP             4
           FMPYDP  .M2X    B21:B20,A5:A4,B19:B18 ; |57| 
           NOP             4

           CALLP   .S2     _atandpMod_atan2dpi,B3
||         DADD    .L1X    0,B19:B18,A5:A4   ; |142| 

$C$RL14:   ; CALL OCCURS {_atandpMod_atan2dpi} {0}  ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 39

           ZERO    .L1     A7:A6             ; |145| 
||         ZERO    .L2     B5:B4             ; |147| 
||         LDW     .D2T2   *+SP(32),B28      ; |159| 

           CMPLTDP .S1     A25:A24,A7:A6,A0  ; |145| 
||         ZERO    .L2     B7:B6             ; |152| 

           DADD    .L1     0,A5:A4,A7:A6     ; |143| 

   [ A0]   CMPGTDP .S2X    A5:A4,B5:B4,B0    ; |147| 
|| [ A0]   MVKL    .S1     0x54442d18,A8
|| [!A0]   ZERO    .L2     B0                ; |147| 

   [ A0]   MVKL    .S1     0x400921fb,A9
||         ZERO    .L2     B5:B4             ; |152| 

   [ A0]   MVKH    .S1     0x54442d18,A8
||         CMPGTDP .S2     B21:B20,B7:B6,B6  ; |152| 

   [ A0]   MVKH    .S1     0x400921fb,A9

           XOR     .L2     1,B6,B29          ; |152| 
||         CMPGTDP .S1X    B19:B18,A11:A10,A1 ; |158| 
|| [ A0]   FADDDP  .L1     A9:A8,A7:A6,A7:A6 ; |146| 
|| [ B0]   LDDW    .D2T1   *+SP(88),A9:A8    ; |146| 

           CMPEQDP .S2X    A25:A24,B5:B4,B7  ; |152| 
           ZERO    .L2     B5:B4             ; |155| 
           CMPLTDP .S2X    A25:A24,B5:B4,B5  ; |155| 
           AND     .L2     B7,B29,B2         ; |152| 

   [ B0]   FSUBDP  .S1     A5:A4,A9:A8,A7:A6 ; |148| 
||         ZERO    .L1     A5:A4             ; |153| 

           XOR     .L2     1,B5,B5           ; |155| 
           CMPGTDP .S2X    B21:B20,A5:A4,B6  ; |153| 

           ZERO    .L1     A5:A4             ; |155| 
|| [ B2]   MVKL    .S1     0xbff921fb,A7

   [ B2]   MVKL    .S1     0x54442d18,A6
||         AND     .L2     B7,B6,B0          ; |153| 

           CMPEQDP .S2X    B21:B20,A5:A4,B4  ; |155| 
|| [ B2]   MVKH    .S1     0xbff921fb,A7

   [ B2]   MVKH    .S1     0x54442d18,A6

   [ B0]   MVKL    .S1     0x3ff921fb,A7
||         AND     .L2X    A0,B4,B1          ; |156| 
||         CMPLTDP .S2     B19:B18,B11:B10,B2 ; |161| 

   [ B0]   MVKL    .S1     0x54442d18,A6
   [ B0]   MVKH    .S1     0x3ff921fb,A7

   [ B0]   MVKH    .S1     0x54442d18,A6
||         AND     .L2     B4,B5,B0          ; |155| 
||         LDW     .D2T2   *B28,B4           ; |192| 

   [ B0]   ZERO    .L1     A7:A6             ; |156| 
   [ B1]   MVKL    .S1     0x54442d18,A6
   [ B1]   MVKL    .S1     0x400921fb,A7
   [ B1]   MVKH    .S1     0x54442d18,A6

           ADD     .L2     B12,B4,B5         ; |192| 
||         LDW     .D2T2   *+SP(12),B4       ; |192| 
|| [ B1]   MVKH    .S1     0x400921fb,A7
||         ADD     .S2     8,B12,B12         ; |193| 

   [ A1]   MVKL    .S1     0x54442d18,A6
   [ A1]   MVKL    .S1     0x3ff921fb,A7
   [ A1]   MVKH    .S1     0x54442d18,A6
   [ A1]   MVKH    .S1     0x3ff921fb,A7

           SUB     .L1X    B4,1,A0           ; |187| 
|| [ B2]   MVKL    .S1     0x54442d18,A6
||         SUB     .L2     B4,1,B4           ; |187| 

   [ A0]   B       .S2     $C$L9             ; |187| 
|| [ B2]   MVKL    .S1     0xbff921fb,A7
||         STW     .D2T2   B4,*+SP(12)       ; |192| 

   [ B2]   MVKH    .S1     0x54442d18,A6
   [ B2]   MVKH    .S1     0xbff921fb,A7

   [!A0]   MVKL    .S1     _output,A10
||         STDW    .D2T1   A7:A6,*B5         ; |192| 

   [ A0]   CALL    .S2     _atan2            ; |189| 
|| [!A0]   MVKH    .S1     _output,A10
|| [ A0]   LDDW    .D2T2   *++B13,B5:B4      ; |189| 
|| [ A0]   LDDW    .D1T1   *++A15,A5:A4      ; |189| 

   [!A0]   CALL    .S2     _atan2dp_v        ; |196| 
|| [!A0]   LDW     .D1T1   *+A10(16),A6      ; |196| 
|| [!A0]   MVKL    .S1     _a_sc,A4

           ; BRANCHCC OCCURS {$C$L9}         ; |187| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           MVK     .S2     0x19,B6           ; |196| 
           MV      .L2X    A14,B4            ; |196| 
           ADDKPC  .S2     $C$RL15,B3,1      ; |196| 
           MVKH    .S1     _a_sc,A4
$C$RL15:   ; CALL OCCURS {_atan2dp_v} {0}    ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     0x3e112e0b,B7

           LDW     .D1T1   *A10,A4           ; |66| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVK     .S1     0x19,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A10(8),B4       ; |67| 
||         MVKL    .S1     _fcn_pass,A3
||         MVKH    .S2     0xe826d695,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A5,*+A3(4)        ; |66| 
||         MVK     .S1     0x19,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3e112e0b,B7

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     0xe826d695,B6

           MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     0x3e112e0b,B7

           MV      .L2X    A10,B4            ; |67| 
||         STW     .D1T1   A4,*+A3(8)        ; |67| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |68| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVK     .S1     0x19,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL18:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(20),A3       ; |68| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S1     _fcn_pass,A5
           MVKL    .S2     0x3e112e0b,B7
           MVKH    .S1     _fcn_pass,A5

           MVKH    .S2     0xe826d695,B6
||         STW     .D2T1   A3,*+SP(32)       ; |68| 

           MV      .L2X    A3,B4             ; |66| 
||         MV      .L1     A10,A3            ; |69| 
||         STW     .D1T1   A4,*+A5(12)       ; |68| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *B4,B4            ; |69| 
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MVK     .S1     0x19,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL19:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(24),A3       ; |69| 
           MVKL    .S1     _fcn_pass,A30
           LDW     .D2T1   *+SP(28),A31
           MVKH    .S1     _fcn_pass,A30
           STW     .D1T1   A4,*+A30(16)      ; |69| 
           MV      .L2X    A3,B4             ; |69| 
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T1   A3,*+SP(36)       ; |69| 
           STW     .D2T1   A31,*+SP(40)      ; |72| 
           NOP             2

   [!B0]   MV      .L1     A12,A4
|| [!B0]   B       .S1     $C$L10            ; |72| 
|| [ B0]   LDW     .D2T2   *+SP(40),B4

   [!B0]   CALL    .S1     _print_test_results ; |200| 
   [!B0]   MVKL    .S1     _all_pass,A3
           MV      .L2     B0,B1             ; guard predicate rewrite
   [!B0]   MVKH    .S1     _all_pass,A3

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
|| [ B1]   ADD     .L2     4,B4,B4

           ; BRANCHCC OCCURS {$C$L10}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
           NOP             1
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
           NOP             3
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   MV      .L1     A12,A4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |200| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |200| 
||         ADDKPC  .S2     $C$RL20,B3,0      ; |200| 

$C$RL20:   ; CALL OCCURS {_print_test_results} {0}  ; |200| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDW     .D2T1   *+SP(64),A12      ; |57| 

           LDW     .D2T1   *+SP(60),A3       ; |57| 
||         MVKL    .S2     0x4000cccc,B4

           MVKH    .S2     0x4000cccc,B4
||         LDW     .D2T1   *+SP(68),A13      ; |158| 

           STW     .D2T2   B4,*+SP(84)       ; |210| 
||         ZERO    .L1     A31               ; |203| 

           MVK     .S2     0x777,B28
||         STW     .D2T1   A31,*+SP(72)      ; |203| 

           MVKL    .S2     _b_ext,B6
||         STW     .D2T1   A31,*+SP(56)      ; |204| 

           MVKH    .S2     _b_ext,B6
||         ZERO    .L1     A30               ; |203| 
||         STW     .D2T2   B28,*+SP(12)      ; |203| 

           MVKL    .S2     0xcccccccd,B31
||         STW     .D2T1   A30,*+SP(64)      ; |204| 

           MV      .L1X    B6,A14            ; |204| 
||         MV      .L2     B6,B30            ; |204| 
||         LDDW    .D2T2   *+SP(48),B7:B6    ; |203| 
||         MVKL    .S1     _a_ext,A4
||         MVKH    .S2     0xcccccccd,B31

           MVKH    .S1     _a_ext,A4
||         ZERO    .L2     B5
||         STW     .D2T2   B31,*+SP(80)      ; |210| 

           SET     .S2     B5,0x14,0x14,B5
||         STW     .D2T1   A3,*+SP(76)       ; |57| 

           MV      .L2X    A4,B29            ; |203| 
||         ZERO    .S2     B4                ; |203| 
||         STW     .D2T1   A3,*+SP(68)       ; |57| 

           STDW    .D2T2   B5:B4,*B29        ; |203| 

           STDW    .D2T2   B7:B6,*B30        ; |204| 
||         MV      .L2X    A4,B12            ; |203| 

           LDDW    .D2T2   *B12,B7:B6        ; |206| 
           CALL    .S1     _atan2            ; |206| 
           LDDW    .D1T2   *A14,B5:B4        ; |206| 
           MV      .L1     A10,A15           ; |57| 
           MV      .L1X    B10,A10

           DADD    .L1X    0,B7:B6,A5:A4     ; |206| 
||         ZERO    .L2     B13               ; |203| 

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
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL21,B3,0      ; |206| 
$C$RL21:   ; CALL OCCURS {_atan2} {0}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 85
           LDW     .D1T1   *A15,A3           ; |206| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |206| 
           STDW    .D1T1   A5:A4,*A3         ; |206| 

           CALLP   .S2     _atan2dp,B3
||         LDDW    .D1T2   *A14,B5:B4        ; |207| 
||         LDDW    .D2T1   *B12,A5:A4        ; |207| 

$C$RL22:   ; CALL OCCURS {_atan2dp} {0}      ; |207| 
           LDW     .D1T1   *+A15(4),A3       ; |207| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |207| 
           STDW    .D1T1   A5:A4,*A3         ; |207| 

           CALLP   .S2     _atan2dp_c,B3
||         LDDW    .D2T1   *B12,A5:A4        ; |208| 
||         LDDW    .D1T2   *A14,B5:B4        ; |208| 

$C$RL23:   ; CALL OCCURS {_atan2dp_c} {0}    ; |208| 
           LDW     .D1T1   *+A15(8),A3       ; |208| 
           LDDW    .D2T1   *+SP(56),A9:A8
           NOP             3
           ADD     .L1X    B13,A3,A3         ; |208| 
           STDW    .D1T1   A5:A4,*A3         ; |208| 
           LDDW    .D1T1   *A14,A25:A24      ; |140| 
           LDDW    .D2T2   *B12,B21:B20      ; |139| 
           NOP             3
           RCPDP   .S1     A25:A24,A5:A4     ; |57| 
           NOP             1
           FMPYDP  .M1     A5:A4,A25:A24,A7:A6 ; |57| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |57| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |57| 
           LDDW    .D2T1   *+SP(64),A7:A6
           NOP             2
           FMPYDP  .M1     A5:A4,A25:A24,A9:A8 ; |57| 
           NOP             3
           FSUBDP  .L1     A7:A6,A9:A8,A7:A6 ; |57| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |57| 
           LDDW    .D2T1   *+SP(72),A5:A4
           NOP             2
           FMPYDP  .M1     A7:A6,A25:A24,A9:A8 ; |57| 
           NOP             3
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |57| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |57| 
           NOP             4
           FMPYDP  .M2X    B21:B20,A5:A4,B19:B18 ; |57| 
           NOP             4

           CALLP   .S2     _atandpMod_atan2dpi,B3
||         DADD    .L1X    0,B19:B18,A5:A4   ; |142| 

$C$RL24:   ; CALL OCCURS {_atandpMod_atan2dpi} {0}  ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 53

           ZERO    .L1     A7:A6             ; |145| 
||         ZERO    .L2     B5:B4             ; |147| 
||         LDW     .D2T2   *+SP(16),B28      ; |159| 
||         CMPLTDP .S2     B19:B18,B11:B10,B1 ; |161| 

           CMPLTDP .S1     A25:A24,A7:A6,A0  ; |145| 
||         ZERO    .L2     B7:B6             ; |152| 

           DADD    .L1     0,A5:A4,A7:A6     ; |143| 

   [ A0]   MVKL    .S1     0x54442d18,A8
|| [ A0]   CMPGTDP .S2X    A5:A4,B5:B4,B0    ; |147| 
|| [!A0]   ZERO    .L2     B0                ; |147| 

   [ A0]   MVKL    .S1     0x400921fb,A9
||         ZERO    .L2     B5:B4             ; |152| 

   [ A0]   MVKH    .S1     0x54442d18,A8
||         CMPGTDP .S2     B21:B20,B7:B6,B6  ; |152| 

   [ A0]   MVKH    .S1     0x400921fb,A9

   [ A0]   FADDDP  .L1     A9:A8,A7:A6,A7:A6 ; |146| 
||         CMPEQDP .S2X    A25:A24,B5:B4,B7  ; |152| 
||         XOR     .L2     1,B6,B29          ; |152| 

   [ B0]   FSUBDP  .S1     A5:A4,A13:A12,A7:A6 ; |148| 
||         ZERO    .L1     A5:A4             ; |153| 
||         ZERO    .L2     B5:B4             ; |155| 

           AND     .L2     B7,B29,B0         ; |152| 
           CMPGTDP .S2X    B21:B20,A5:A4,B6  ; |153| 

           ZERO    .L1     A5:A4             ; |155| 
|| [ B0]   MVKL    .S1     0xbff921fb,A7

   [ B0]   MVKL    .S1     0x54442d18,A6
||         CMPLTDP .S2X    A25:A24,B5:B4,B5  ; |155| 

   [ B0]   MVKH    .S1     0xbff921fb,A7

           CMPEQDP .S2X    B21:B20,A5:A4,B4  ; |155| 
|| [ B0]   MVKH    .S1     0x54442d18,A6
||         AND     .L2     B7,B6,B0          ; |153| 
||         XOR     .D2     1,B5,B5           ; |155| 

   [ B0]   MVKL    .S1     0x3ff921fb,A7

   [ B0]   MVKL    .S1     0x54442d18,A6
||         AND     .L2X    A0,B4,B2          ; |156| 

   [ B0]   MVKH    .S1     0x3ff921fb,A7

   [ B0]   MVKH    .S1     0x54442d18,A6
||         AND     .L2     B4,B5,B0          ; |155| 
||         LDW     .D2T2   *B28,B4           ; |209| 

   [ B0]   ZERO    .L1     A7:A6             ; |156| 
   [ B2]   MVKL    .S1     0x400921fb,A7
   [ B2]   MVKL    .S1     0x54442d18,A6
           CMPGTDP .S1X    B19:B18,A11:A10,A1 ; |158| 
           ADD     .L2     B13,B4,B4         ; |209| 
   [ B2]   MVKH    .S1     0x400921fb,A7
   [ B2]   MVKH    .S1     0x54442d18,A6
   [ A1]   MVKL    .S1     0x3ff921fb,A7
   [ A1]   MVKL    .S1     0x54442d18,A6
   [ A1]   MVKH    .S1     0x3ff921fb,A7
   [ A1]   MVKH    .S1     0x54442d18,A6
   [ B1]   MVKL    .S1     0xbff921fb,A7
   [ B1]   MVKL    .S1     0x54442d18,A6
   [ B1]   MVKH    .S1     0xbff921fb,A7
   [ B1]   MVKH    .S1     0x54442d18,A6
           STDW    .D2T1   A7:A6,*B4         ; |209| 
           LDDW    .D2T2   *B12,B7:B6        ; |210| 
           LDDW    .D2T2   *+SP(80),B5:B4
           LDDW    .D1T1   *A14,A5:A4        ; |211| 
           ZERO    .L1     A3                ; |211| 
           SET     .S1     A3,31,31,A3       ; |211| 
           ADD     .L2     8,B13,B13         ; |205| 

           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |210| 
||         LDW     .D2T2   *+SP(12),B6       ; |211| 

           XOR     .L1     A5,A3,A5          ; |211| 
           STDW    .D1T1   A5:A4,*++A14      ; |211| 
           NOP             1
           STDW    .D2T2   B5:B4,*++B12      ; |210| 

           SUB     .L1X    B6,1,A0           ; |205| 
||         SUB     .L2     B6,1,B4           ; |205| 

   [ A0]   B       .S2     $C$L11            ; |205| 
|| [ A0]   LDDW    .D2T2   *B12,B7:B6        ; |206| 
|| [!A0]   MV      .L2X    A15,B11           ; |213| 
|| [!A0]   MVKL    .S1     _a_ext,A4

   [ A0]   CALL    .S1     _atan2            ; |206| 
||         STW     .D2T2   B4,*+SP(12)       ; |210| 
|| [!A0]   MVKL    .S2     _b_ext,B4

   [ A0]   LDDW    .D1T2   *A14,B5:B4        ; |206| 
   [!A0]   CALL    .S1     _atan2dp_v        ; |213| 
   [!A0]   LDW     .D2T1   *+B11(16),A6      ; |213| 
   [ A0]   DADD    .L1X    0,B7:B6,A5:A4     ; |206| 
           ; BRANCHCC OCCURS {$C$L11}        ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           MVKH    .S2     _b_ext,B4
           ADDKPC  .S2     $C$RL25,B3,0      ; |213| 

           MVK     .S2     0x777,B6          ; |213| 
||         MVKH    .S1     _a_ext,A4

$C$RL25:   ; CALL OCCURS {_atan2dp_v} {0}    ; |213| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     0x3e112e0b,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B10
           MVKL    .S2     0x3e112e0b,B7
           MVKH    .S2     _fcn_pass,B10
           MVKL    .S2     0xe826d695,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3e112e0b,B7

           STW     .D2T1   A4,*+B10(4)       ; |66| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL27:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     0x3e112e0b,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL28:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(20),A3       ; |68| 
           MVKL    .S2     0xe826d695,B6
           MVKL    .S2     0x3e112e0b,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           LDW     .D1T1   *A15,A4           ; |69| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL29:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(24),A3       ; |69| 
           LDW     .D2T2   *+SP(28),B4
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             2
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [ A0]   ADD     .L2     4,B4,B4
|| [!A0]   B       .S1     $C$L12            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |217| 
   [!A0]   MVKL    .S1     _all_pass,A3
   [!A0]   MVKH    .S1     _all_pass,A3
   [!A0]   ZERO    .L2     B4                ; |72| 
   [!A0]   MV      .L2X    A3,B5
           ; BRANCHCC OCCURS {$C$L12}        ; |72| 
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
           CALL    .S1     _print_test_results ; |217| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             1
           MV      .L2X    A3,B5
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x4,A4            ; |217| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL30,B3,0      ; |217| 

$C$RL30:   ; CALL OCCURS {_print_test_results} {0}  ; |217| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S1     _cycle_counts+24,A3

           MVKH    .S1     _cycle_counts+24,A3
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .L1     A10               ; |114| 
||         ZERO    .D1     A11               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*A3       ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     _t_start,A3

           MVKH    .S1     _t_start,A3
||         MV      .L2     B4,B7             ; |116| 

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B7:B6,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKL    .S1     _t_offset,A3

           CALL    .S2     _gimme_random     ; |227| 
||         ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     _t_offset,A3

           MVKL    .S2     0x3fa6defc,B4
||         STDW    .D1T2   B5:B4,*A3         ; |117| 

           MVKH    .S2     0x3fa6defc,B4

           MVKL    .S2     0xc01921fb,B5
||         MVKL    .S1     0x402921fb,A5

           MV      .L1X    B4,A4             ; |227| 
||         MVKH    .S2     0xc01921fb,B5
||         MV      .D1     A10,A12           ; |117| 
||         MVK     .S1     0x80,A13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1

           ADDKPC  .S2     $C$RL31,B3,0      ; |227| 
||         MVKH    .S1     0x402921fb,A5

$C$RL31:   ; CALL OCCURS {_gimme_random} {0}  ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 73
           MVKL    .S2     _input,B10
           MVKH    .S2     _input,B10
           LDW     .D2T2   *B10,B6           ; |227| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |227| 
           MVKL    .S1     0x402921fb,A5
           MVKH    .S1     0x402921fb,A5
           NOP             1
           ADD     .L2X    A12,B6,B6         ; |227| 

           STDW    .D2T2   B5:B4,*B6         ; |227| 
||         MVKL    .S2     0x3fa6defc,B4

           MVKL    .S2     0xc01921fb,B5
           MVKH    .S2     0x3fa6defc,B4
           MVKH    .S2     0xc01921fb,B5

           CALLP   .S2     _gimme_random,B3
||         MV      .L1X    B4,A4             ; |228| 

$C$RL32:   ; CALL OCCURS {_gimme_random} {0}  ; |228| 
           LDW     .D2T2   *+B10(4),B4       ; |228| 
           DADD    .L1     0,A5:A4,A25:A24   ; |228| 
           NOP             3
           ADD     .L2X    A12,B4,B4         ; |228| 

           STDW    .D2T1   A25:A24,*B4       ; |228| 
||         MVC     .S2     TSCL,B20          ; |122| 

           MVC     .S2     TSCH,B6           ; |122| 
           RCPDP   .S1     A25:A24,A5:A4     ; |57| 
           ZERO    .L1     A9
           FMPYDP  .M1     A5:A4,A25:A24,A7:A6 ; |57| 
           SET     .S1     A9,0x1e,0x1e,A9
           MV      .L1     A10,A8            ; |57| 
           MV      .L2X    A11,B4            ; |57| 
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |57| 
           MV      .L2X    A9,B5             ; |57| 
           MV      .S1X    B10,A15           ; |57| 
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |57| 
           LDW     .D1T1   *A15,A3           ; |139| 
           MV      .L2X    A11,B16           ; |139| 
           MV      .L2X    A9,B17            ; |139| 
           FMPYDP  .M1     A5:A4,A25:A24,A7:A6 ; |57| 
           MV      .L2     B6,B21            ; |122| 
           ADD     .L1     A12,A3,A3         ; |139| 
           LDDW    .D1T1   *A3,A27:A26       ; |139| 
           MVKL    .S1     _t_start,A3
           FSUBDP  .L2X    B5:B4,A7:A6,B5:B4 ; |57| 
           MVKH    .S1     _t_start,A3
           STDW    .D1T2   B21:B20,*A3       ; |122| 
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |57| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A25:A24,B9:B8 ; |57| 
           NOP             3
           FSUBDP  .L2     B17:B16,B9:B8,B9:B8 ; |57| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B5:B4 ; |57| 
           NOP             3
           FMPYDP  .M2X    A27:A26,B5:B4,B19:B18 ; |57| 
           NOP             4

           CALLP   .S2     _atandpMod_atan2dpi,B3
||         DADD    .L1X    0,B19:B18,A5:A4   ; |142| 

$C$RL33:   ; CALL OCCURS {_atandpMod_atan2dpi} {0}  ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46

           ZERO    .L2     B5:B4             ; |145| 
||         DADD    .L1     0,A5:A4,A9:A8     ; |143| 
||         MVKL    .S1     0x400921fb,A7
||         ADDAW   .D2     B11,3,B27

           CMPLTDP .S2X    A25:A24,B5:B4,B0  ; |145| 
||         ZERO    .L2     B7:B6             ; |152| 
||         MVKL    .S1     0x54442d18,A6
||         LDW     .D2T2   *B27,B26          ; |232| 

           ZERO    .L2     B5:B4             ; |147| 
||         MVKH    .S1     0x400921fb,A7

   [ B0]   MVKL    .S2     0x400921fb,B9
|| [!B0]   ZERO    .L2     B1                ; |147| 
||         MVKH    .S1     0x54442d18,A6

   [ B0]   MVKL    .S2     0x54442d18,B8
   [ B0]   MVKH    .S2     0x400921fb,B9

   [ B0]   MVKH    .S2     0x54442d18,B8
||         ADD     .L1X    A12,B26,A3        ; |232| 

   [ B0]   CMPGTDP .S2X    A5:A4,B5:B4,B1    ; |147| 

   [ B0]   FADDDP  .L1X    B9:B8,A9:A8,A9:A8 ; |146| 
||         ZERO    .L2     B5:B4             ; |152| 

           CMPGTDP .S2X    A27:A26,B7:B6,B6  ; |152| 
|| [ B1]   FSUBDP  .L1     A5:A4,A7:A6,A9:A8 ; |148| 
||         ZERO    .L2     B9:B8             ; |155| 
||         MVKL    .S1     0x7fefffff,A5
||         MVK     .D1     0xffffffff,A4     ; |158| 

           MVKH    .S1     0x7fefffff,A5

           CMPGTDP .S1X    B19:B18,A5:A4,A0  ; |158| 
||         CMPEQDP .S2X    A25:A24,B5:B4,B4  ; |152| 
||         XOR     .L2     1,B6,B29          ; |152| 

           ZERO    .L2     B7:B6             ; |153| 

           CMPGTDP .S2X    A27:A26,B7:B6,B5  ; |153| 
||         AND     .L2     B4,B29,B1         ; |152| 

   [ B1]   MVKL    .S1     0xbff921fb,A9
|| [ B1]   MV      .L1     A6,A8             ; |152| 

           AND     .D2     B4,B5,B2          ; |153| 
||         ZERO    .L2     B5:B4             ; |155| 
||         CMPLTDP .S2X    A25:A24,B9:B8,B6  ; |155| 
|| [ B1]   MVKH    .S1     0xbff921fb,A9

   [ B2]   MVKL    .S1     0x3ff921fb,A9
|| [ B2]   MV      .L1     A6,A8             ; |155| 

   [ B2]   MVKH    .S1     0x3ff921fb,A9
||         CMPEQDP .S2X    A27:A26,B5:B4,B4  ; |155| 

           XOR     .L2     1,B6,B28          ; |155| 

           AND     .L2     B4,B28,B1         ; |155| 
||         AND     .D2     B0,B4,B0          ; |156| 
||         MVKL    .S2     0xffefffff,B5

   [ B1]   ZERO    .L1     A9:A8             ; |156| 
||         MV      .L2X    A4,B4             ; |156| 
||         MVKH    .S2     0xffefffff,B5

   [ B0]   MV      .L1     A7,A9             ; |161| 
|| [ B0]   MV      .S1     A6,A8             ; |156| 
||         CMPLTDP .S2     B19:B18,B5:B4,B0  ; |161| 

   [ A0]   MVKL    .S1     0x3ff921fb,A9
|| [ A0]   MV      .L1     A6,A8

   [ A0]   MVKH    .S1     0x3ff921fb,A9
|| [ B0]   MV      .L1     A6,A8             ; |159| 

   [ B0]   MVKL    .S1     0xbff921fb,A9
   [ B0]   MVKH    .S1     0xbff921fb,A9

           STDW    .D1T1   A9:A8,*A3         ; |232| 
||         MVC     .S2     TSCL,B4           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     _t_start,B6
||         SUB     .L1     A13,1,A0          ; |225| 
||         MVKL    .S1     _cycle_counts+24,A14
||         ADD     .D1     8,A12,A12         ; |225| 

           MVKL    .S2     _t_offset,B10
||         MVKH    .S1     _cycle_counts+24,A14
||         SUB     .L1     A13,1,A13         ; |225| 

           MVKH    .S2     _t_start,B6

           MVKH    .S2     _t_offset,B10
||         LDDW    .D2T2   *B6,B9:B8         ; |130| 

           LDDW    .D2T1   *B10,A5:A4        ; |130| 
||         MVKL    .S2     _cycle_counts+24,B25

           MVKH    .S2     _cycle_counts+24,B25

           LDDW    .D2T2   *B25,B17:B16      ; |130| 
||         MVKL    .S2     _t_stop,B24

           MVKH    .S2     _t_stop,B24
           STDW    .D2T2   B5:B4,*B24        ; |128| 
           ADDU    .L1X    A4,B8,A7:A6       ; |130| 

           ADD     .S1     A7,A5,A4          ; |130| 
||         SUBU    .L1X    B4,A6,A7:A6       ; |130| 
|| [ A0]   MVKL    .S2     0x3fa6defc,B4

           EXT     .S1     A7,24,24,A31      ; |130| 
||         MV      .L1     A6,A3             ; |130| 
|| [ A0]   MVKH    .S2     0x3fa6defc,B4

           ADD     .L2X    A4,B9,B7          ; |130| 
|| [ A0]   B       .S1     $C$L13            ; |225| 
||         ADDU    .L1X    B16,A3,A5:A4      ; |130| 

   [ A0]   CALL    .S1     _gimme_random     ; |227| 
||         SUB     .L2     B5,B7,B7          ; |130| 
||         ADD     .L1X    A5,B17,A30        ; |130| 
|| [ A0]   MVKL    .S2     0xc01921fb,B5

           ADD     .L2X    B7,A31,B7         ; |130| 
   [ A0]   MVKH    .S2     0xc01921fb,B5
           ADD     .L1X    A30,B7,A5         ; |130| 

   [!A0]   CALL    .S2     __fltllif         ; |135| 
||         STDW    .D1T1   A5:A4,*A14        ; |130| 
|| [ A0]   MV      .L1X    B4,A4             ; |227| 
|| [ A0]   MVKL    .S1     0x402921fb,A5

           ; BRANCHCC OCCURS {$C$L13}        ; |225| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |135| 
$C$RL34:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           MV      .L1     A10,A12           ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL35:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
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
           MVC     .S2     TSCH,B9           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           SUB     .L2     B9,B4,B5          ; |117| 
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         LDW     .D1T1   *A15,A14

           MV      .L2     B6,B4             ; |117| 
||         ADD     .S2     B5,B7,B5          ; |117| 
||         LDW     .D1T2   *+A15(4),B10
||         MV      .L1X    B11,A3            ; |117| 
||         MV      .D2     B10,B8            ; |117| 

           STDW    .D2T2   B5:B4,*B8         ; |117| 
||         MVK     .S1     0x80,A15
||         LDW     .D1T1   *A3,A12

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
;          EXCLUSIVE CPU CYCLES: 8
           MVC     .S2     TSCL,B6           ; |122| 
           MVC     .S2     TSCH,B7           ; |122| 
           CALL    .S1     _atan2            ; |241| 

           LDDW    .D2T2   *B10++,B5:B4      ; |241| 
||         LDDW    .D1T1   *A14++,A5:A4      ; |241| 

           MVKL    .S2     _t_start,B8
           MVKH    .S2     _t_start,B8
           STDW    .D2T2   B7:B6,*B8         ; |122| 
           ADDKPC  .S2     $C$RL36,B3,0      ; |241| 
$C$RL36:   ; CALL OCCURS {_atan2} {0}        ; |241| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20

           STDW    .D1T1   A5:A4,*A12++      ; |241| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     _t_start,A3
||         MVKL    .S2     _t_offset,B11
||         SUB     .L1     A15,1,A0          ; |239| 
||         MV      .L2     B4,B9             ; |128| 
||         SUB     .D1     A15,1,A15         ; |239| 

           MVKH    .S1     _t_start,A3
||         MVKH    .S2     _t_offset,B11

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 
||         MVKL    .S1     _cycle_counts,A31
||         MVKL    .S2     _cycle_counts,B4

           MVKH    .S1     _cycle_counts,A31
||         MVKH    .S2     _cycle_counts,B4

           MVKL    .S1     _t_stop,A30

           MVKH    .S1     _t_stop,A30
|| [!A0]   MV      .L1X    B4,A14

           STDW    .D1T2   B9:B8,*A30        ; |128| 
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
           ADD     .L1X    A5,B7,A6          ; |130| 

           SUBU    .L2X    B8,A4,B17:B16     ; |130| 
||         LDDW    .D1T1   *A31,A5:A4        ; |130| 
||         ADD     .L1     A6,A7,A6          ; |130| 

           EXT     .S2     B17,24,24,B31     ; |130| 
           SUB     .L2X    B9,A6,B5          ; |130| 
   [ A0]   BNOP    .S1     $C$L14,1          ; |239| 
           ADDU    .L2X    A4,B16,B7:B6      ; |130| 

           ADD     .L2X    B7,A5,B5          ; |130| 
||         ADD     .S2     B5,B31,B7         ; |130| 

           ADD     .L2     B5,B7,B7          ; |130| 

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D2T2   B7:B6,*B4         ; |130| 

           ; BRANCHCC OCCURS {$C$L14}        ; |239| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |135| 
$C$RL37:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
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

$C$RL38:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A11:A10,*+A14(8)  ; |114| 
||         MV      .L2X    A11,B4            ; |114| 

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

           STDW    .D2T2   B5:B4,*B11        ; |117| 
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
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     _input+4,A3
           MVKH    .S1     _input+4,A3
           LDW     .D1T1   *A3,A31           ; |250| 
           ADD     .L2X    -4,A3,B6
           LDW     .D2T2   *B6,B6            ; |250| 
           NOP             2
           ADD     .L1     A12,A31,A3        ; |250| 
           LDDW    .D1T1   *A3,A5:A4         ; |250| 
           ADD     .L2X    A12,B6,B6         ; |250| 

           LDDW    .D2T2   *B6,B7:B6         ; |250| 
||         CALL    .S1     _atan2dp          ; |250| 

           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3
           STDW    .D1T2   B5:B4,*A3         ; |122| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |250| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |250| 
||         ADDKPC  .S2     $C$RL39,B3,0      ; |250| 

$C$RL39:   ; CALL OCCURS {_atan2dp} {0}      ; |250| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 28
           MVKL    .S2     _output+4,B4
           MVKH    .S2     _output+4,B4
           LDW     .D2T2   *B4,B4            ; |250| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |250| 

           STDW    .D1T1   A5:A4,*A3         ; |250| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S1     _t_start,A3
||         LDDW    .D2T2   *B11,B5:B4        ; |130| 
||         ADDAD   .D1     A14,1,A31
||         SUB     .L1X    B10,1,A0          ; |248| 
||         MV      .L2     B6,B9             ; |128| 
||         MVKL    .S2     _t_stop,B6

           SUB     .L2     B10,1,B10         ; |248| 
||         MVKH    .S1     _t_start,A3

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           ADD     .L1     8,A12,A12         ; |248| 
           ADDAD   .D1     A14,1,A15
           MVKH    .S2     _t_stop,B6
           STDW    .D2T2   B9:B8,*B6         ; |128| 
           ADDU    .L1X    B4,A6,A5:A4       ; |130| 
           ADD     .L1X    A5,B5,A3          ; |130| 

           SUBU    .L2X    B8,A4,B5:B4       ; |130| 
||         LDDW    .D1T1   *A31,A5:A4        ; |130| 
||         ADD     .L1     A3,A7,A3          ; |130| 

           EXT     .S2     B5,24,24,B7       ; |130| 
           SUB     .L1X    B9,A3,A3          ; |130| 

   [ A0]   BNOP    .S1     $C$L15,1          ; |248| 
||         ADD     .L1X    A3,B7,A3          ; |130| 

           ADDU    .L2X    A4,B4,B5:B4       ; |130| 
           ADD     .L2X    B5,A5,B5          ; |130| 

           ADD     .L2X    B5,A3,B5          ; |130| 
|| [!A0]   MV      .L1     A14,A3

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D1T2   B5:B4,*A15        ; |130| 

           ; BRANCHCC OCCURS {$C$L15}        ; |248| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(8),A5:A4     ; |135| 
           ADDKPC  .S2     $C$RL40,B3,3      ; |135| 
$C$RL40:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
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

$C$RL41:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           MV      .L2X    A15,B4            ; |135| 
||         MV      .L1     A14,A3            ; |135| 

           STDW    .D1T1   A11:A10,*+A3(16)  ; |114| 
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

           STDW    .D2T2   B7:B6,*B11        ; |117| 
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
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S2     _input,B13
           MVKH    .S2     _input,B13
           LDW     .D2T2   *B13,B6           ; |259| 
           ADD     .L1X    4,B13,A3
           LDW     .D1T1   *A3,A3            ; |259| 
           NOP             2
           ADD     .L2X    A12,B6,B6         ; |259| 
           LDDW    .D2T2   *B6,B7:B6         ; |259| 
           ADD     .L1     A12,A3,A3         ; |259| 

           LDDW    .D1T1   *A3,A5:A4         ; |259| 
||         CALL    .S1     _atan2dp_c        ; |259| 

           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3
           STDW    .D1T2   B5:B4,*A3         ; |122| 
           ADDKPC  .S2     $C$RL42,B3,0      ; |259| 

           DADD    .L2X    0,A5:A4,B5:B4     ; |259| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |259| 

$C$RL42:   ; CALL OCCURS {_atan2dp_c} {0}    ; |259| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 28
           MVKL    .S2     _output+8,B4
           MVKH    .S2     _output+8,B4
           LDW     .D2T2   *B4,B4            ; |259| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |259| 

           STDW    .D1T1   A5:A4,*A3         ; |259| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S1     _t_start,A14
||         LDDW    .D2T2   *B11,B5:B4        ; |130| 
||         SUB     .L1X    B10,1,A0          ; |257| 
||         MVKL    .S2     _t_stop,B12
||         MV      .L2     B6,B9             ; |128| 
||         ADD     .D1     8,A12,A12         ; |257| 

           MVKH    .S1     _t_start,A14
||         MVKH    .S2     _t_stop,B12
||         SUB     .L2     B10,1,B10         ; |257| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
           STDW    .D2T2   B9:B8,*B12        ; |128| 
           MVKL    .S1     _cycle_counts+16,A3
           MVKH    .S1     _cycle_counts+16,A3
           MVKL    .S1     _cycle_counts+16,A15
           ADDU    .L1X    B4,A6,A5:A4       ; |130| 
           MVKH    .S1     _cycle_counts+16,A15

           ADD     .L1X    A5,B5,A3          ; |130| 
||         SUBU    .L2X    B8,A4,B5:B4       ; |130| 
||         LDDW    .D1T1   *A3,A5:A4         ; |130| 

           EXT     .S2     B5,24,24,B31      ; |130| 
||         ADD     .L1     A3,A7,A3          ; |130| 

           SUB     .L1X    B6,A3,A3          ; |130| 

   [ A0]   BNOP    .S1     $C$L16,1          ; |257| 
||         ADD     .L1X    A3,B31,A3         ; |130| 

           ADDU    .L2X    A4,B4,B5:B4       ; |130| 
           ADD     .L2X    B5,A5,B5          ; |130| 

           ADD     .L2X    B5,A3,B5          ; |130| 
|| [!A0]   SUBAW   .D1     A15,4,A3

   [!A0]   CALL    .S1     __fltllif         ; |135| 
||         STDW    .D1T2   B5:B4,*A15        ; |130| 

           ; BRANCHCC OCCURS {$C$L16}        ; |257| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(16),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL43,B3,3      ; |135| 
$C$RL43:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 109
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MV      .L2X    A4,B4             ; |135| 
           MPYSP   .M2X    A3,B4,B4          ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S2     B4,B5:B4          ; |135| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |135| 

$C$RL44:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
           SUBAW   .D1     A15,4,A3

           MV      .L2X    A11,B4            ; |114| 
||         STDW    .D1T1   A5:A4,*A15        ; |135| 

           STDW    .D1T1   A11:A10,*+A3(32)  ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B16          ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B17            ; |116| 

           STDW    .D1T2   B17:B16,*A14      ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 
           SUBU    .L2     B5,B16,B7:B6      ; |117| 

           SUB     .L2     B4,B17,B5         ; |117| 
||         EXT     .S2     B7,24,24,B7       ; |117| 

           MVKL    .S1     _output,A10
||         LDW     .D2T1   *B13,A4           ; |266| 
||         ADD     .L2     B5,B7,B7          ; |117| 

           MVKH    .S1     _output,A10
||         ADD     .L2     4,B13,B8
||         STDW    .D2T2   B7:B6,*B11        ; |117| 
||         MVK     .S2     0x80,B6           ; |266| 

           CALLP   .S2     _atan2dp_v,B3
||         LDW     .D1T1   *+A10(16),A6      ; |266| 
||         LDW     .D2T2   *B8,B4            ; |266| 

$C$RL45:   ; CALL OCCURS {_atan2dp_v} {0}    ; |266| 
           MVC     .S2     TSCL,B16          ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D2T2   *B11,B9:B8        ; |130| 
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           MVK     .S2     16,B10
           ADD     .L2X    A15,B10,B10
           LDDW    .D2T2   *B10,B7:B6        ; |130| 
           MV      .L2     B4,B17            ; |128| 
           ADDU    .L1X    B8,A4,A9:A8       ; |130| 
           ADD     .L1X    A9,B9,A3          ; |130| 
           SUBU    .L1X    B16,A8,A7:A6      ; |130| 

           ADD     .S1     A3,A5,A3          ; |130| 
||         ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           SUB     .L1X    B4,A3,A3          ; |130| 

           EXT     .S1     A7,24,24,A31      ; |130| 
||         ADD     .L2X    A5,B7,B4          ; |130| 

           ADD     .L1     A3,A31,A3         ; |130| 

           CALLP   .S2     __fltllif,B3
||         ADD     .L1X    B4,A3,A5          ; |130| 
||         STDW    .D2T2   B17:B16,*B12      ; |128| 

$C$RL46:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL47:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     0x3e112e0b,B7

           STDW    .D2T1   A5:A4,*B10        ; |130| 
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL48:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0xe826d695,B6

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A10(8),B4       ; |67| 
||         MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     0xe826d695,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MV      .S1     A3,A11            ; |66| 
||         MVKH    .S2     0x3e112e0b,B7

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A5,*+A11(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL49:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6

           STW     .D1T1   A4,*+A11(8)       ; |67| 
||         MVKH    .S2     0x3e112e0b,B7

           LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL50:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T2   *+SP(32),B4       ; |68| 
           MVKL    .S2     0x3e112e0b,B7
           MVKL    .S2     0xe826d695,B6
           MVKH    .S2     0x3e112e0b,B7

           STW     .D1T1   A4,*+A11(12)      ; |68| 
||         MVKH    .S2     0xe826d695,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *B4,B4            ; |69| 
||         LDW     .D1T1   *A10,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL51:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(36),B4       ; |69| 
           STW     .D1T1   A4,*+A11(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(40),B4
           NOP             3

   [!B0]   B       .S1     $C$L17            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
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
   [ A0]   B       .S1     $C$L18            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |272| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L18}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |272| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |272| 
||         ADDKPC  .S2     $C$RL52,B3,0      ; |272| 

$C$RL52:   ; CALL OCCURS {_print_test_results} {0}  ; |272| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |273| 

$C$RL53:   ; CALL OCCURS {_printf} {0}       ; |273| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |273| 

$C$RL54:   ; CALL OCCURS {_printf} {0}       ; |273| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |280| 

$C$RL55:   ; CALL OCCURS {_print_profile_results} {0}  ; |280| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |283| 

$C$RL56:   ; CALL OCCURS {_print_memory_results} {0}  ; |283| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(104),B3     ; |284| 
           LDDW    .D2T1   *++SP,A13:A12     ; |284| 
           LDDW    .D2T1   *++SP,A15:A14     ; |284| 
           LDDW    .D2T2   *++SP,B11:B10     ; |284| 
           LDDW    .D2T2   *++SP,B13:B12     ; |284| 

           LDW     .D2T1   *++SP(8),A10      ; |284| 
||         RET     .S2     B3                ; |284| 

           LDW     .D2T1   *++SP(8),A11      ; |284| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |284| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"atan2DP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_atan2
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_atan2dp
	.global	_atan2dp_c
	.global	_atan2dp_v
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
	.global	_V
	.global	__fltllif
	.global	__fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
