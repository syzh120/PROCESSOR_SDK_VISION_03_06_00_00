;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:43:20 2013                                *
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
	.word	00343c7d6h,0412c14f1h		; _a[0] @ 0
	.word	0e54f6d26h,041064358h		; _a[1] @ 64
	.word	0adfb3596h,041175396h		; _a[2] @ 128
	.word	0ba20791ch,04111c780h		; _a[3] @ 192
	.word	06d42a597h,041267828h		; _a[4] @ 256
	.word	0fb2e0fdeh,0411935b5h		; _a[5] @ 320
	.word	0b9863030h,04122d449h		; _a[6] @ 384
	.word	02b3ebf58h,04129379dh		; _a[7] @ 448
	.word	0d342825ch,0410525cch		; _a[8] @ 512
	.word	0439b9ca9h,04127ed39h		; _a[9] @ 576
	.word	0c856be53h,0412dc983h		; _a[10] @ 640
	.word	0dc57b9fbh,04116d45eh		; _a[11] @ 704
	.word	014b92db4h,0412a203ch		; _a[12] @ 768
	.word	0003324f0h,041189fefh		; _a[13] @ 832
	.word	006705fe4h,04128dfb9h		; _a[14] @ 896
	.word	0c42c6b99h,0411144bah		; _a[15] @ 960
	.word	0f0ab20abh,0412a9619h		; _a[16] @ 1024
	.word	07cbdf315h,0412a7cffh		; _a[17] @ 1088
	.word	0e1cc6096h,0412d616ch		; _a[18] @ 1152
	.word	041d94d0eh,04116dadfh		; _a[19] @ 1216
	.word	0f8fbeb9eh,04127fa34h		; _a[20] @ 1280
	.word	00628d93dh,0410ad955h		; _a[21] @ 1344
	.word	0049fa8a7h,04125c25dh		; _a[22] @ 1408
	.word	0695809ach,0412c6ca5h		; _a[23] @ 1472
	.word	03eb484d7h,041232b49h		; _a[24] @ 1536
	.word	0018aa1afh,0412e1b17h		; _a[25] @ 1600
	.word	013341e15h,041294babh		; _a[26] @ 1664
	.word	05e14925eh,04125c643h		; _a[27] @ 1728
	.word	0e16a41bdh,0412b1b70h		; _a[28] @ 1792
	.word	03ad5f494h,041030c41h		; _a[29] @ 1856
	.word	0452c88f5h,041208eb1h		; _a[30] @ 1920
	.word	0e53b9f12h,0412cbd88h		; _a[31] @ 1984
	.word	0e01304c0h,041207f6ch		; _a[32] @ 2048
	.word	01845e9efh,041063e34h		; _a[33] @ 2112
	.word	088790ee0h,04120d38ah		; _a[34] @ 2176
	.word	08d79de12h,04112ef68h		; _a[35] @ 2240
	.word	01b40ce26h,040d47fa5h		; _a[36] @ 2304
	.word	01928e780h,0412e8029h		; _a[37] @ 2368
	.word	09f2594e5h,040e05f9dh		; _a[38] @ 2432
	.word	08fddde6dh,0412e16efh		; _a[39] @ 2496
	.word	0c2760972h,0410b2e44h		; _a[40] @ 2560
	.word	04684746eh,0412e8169h		; _a[41] @ 2624
	.word	030d04cb4h,04123101ah		; _a[42] @ 2688
	.word	0a86e5cd5h,041221c2eh		; _a[43] @ 2752
	.word	0b9e8d1e6h,0412037afh		; _a[44] @ 2816
	.word	0169a7638h,040e73ba1h		; _a[45] @ 2880
	.word	085c937edh,04119f8f4h		; _a[46] @ 2944
	.word	097b733deh,0410c90c7h		; _a[47] @ 3008
	.word	07c348bf9h,041280071h		; _a[48] @ 3072
	.word	070082dcch,0411d5fa7h		; _a[49] @ 3136
	.word	06e101373h,040d16b0bh		; _a[50] @ 3200
	.word	0f9fd9ba2h,0411cf328h		; _a[51] @ 3264
	.word	0472ba9d2h,04111d903h		; _a[52] @ 3328
	.word	01945308ch,040f860c3h		; _a[53] @ 3392
	.word	02883e278h,0411b211dh		; _a[54] @ 3456
	.word	03f109c2fh,041159a6ah		; _a[55] @ 3520
	.word	0e2e708b8h,0412958c2h		; _a[56] @ 3584
	.word	0843060f1h,04105e96ah		; _a[57] @ 3648
	.word	03dddbe8dh,0410a8e3eh		; _a[58] @ 3712
	.word	0de2cc129h,04116d18dh		; _a[59] @ 3776
	.word	0c71edb8dh,04123e189h		; _a[60] @ 3840
	.word	0548612d4h,0411b7435h		; _a[61] @ 3904
	.word	044711a1fh,04113a964h		; _a[62] @ 3968
	.word	089c4cd24h,0411f3e51h		; _a[63] @ 4032
	.word	0c84a14f7h,0411c43bch		; _a[64] @ 4096
	.word	0052f2ec2h,040ff823eh		; _a[65] @ 4160
	.word	0a82814f2h,041097435h		; _a[66] @ 4224
	.word	005a45c6bh,04109c546h		; _a[67] @ 4288
	.word	0fd413e8fh,0411c324ch		; _a[68] @ 4352
	.word	0cd17507fh,0412b400bh		; _a[69] @ 4416
	.word	0e2d19737h,041284bd2h		; _a[70] @ 4480
	.word	0d01c7ebch,04117a83fh		; _a[71] @ 4544
	.word	08c8a51feh,04112331eh		; _a[72] @ 4608
	.word	08b391270h,0412b0b87h		; _a[73] @ 4672
	.word	05623ffbah,0411ca923h		; _a[74] @ 4736
	.word	0f9428abfh,0411951ffh		; _a[75] @ 4800
	.word	03f894d1bh,040f6313dh		; _a[76] @ 4864
	.word	0615c0fcbh,04125f01fh		; _a[77] @ 4928
	.word	056dca07fh,040f613edh		; _a[78] @ 4992
	.word	02d4ce231h,04101f732h		; _a[79] @ 5056
	.word	095c556b7h,0411aa0c5h		; _a[80] @ 5120
	.word	0fd3fdae1h,0411da481h		; _a[81] @ 5184
	.word	04e384d4eh,0412e12aeh		; _a[82] @ 5248
	.word	0c092e7cfh,0412b5a54h		; _a[83] @ 5312
	.word	0e8723755h,04117e7a2h		; _a[84] @ 5376
	.word	0d6106e0ch,041264e49h		; _a[85] @ 5440
	.word	01876af8ah,0412d01adh		; _a[86] @ 5504
	.word	048e4176ch,0411bc19fh		; _a[87] @ 5568
	.word	02197b66bh,0411dfecah		; _a[88] @ 5632
	.word	0dc860c1eh,0411d48bbh		; _a[89] @ 5696
	.word	0efe1396bh,0410da195h		; _a[90] @ 5760
	.word	08643e6e0h,040f2a875h		; _a[91] @ 5824
	.word	0922f166eh,0412613e2h		; _a[92] @ 5888
	.word	00ab7b437h,0410b2d0dh		; _a[93] @ 5952
	.word	0008fd347h,04122516ch		; _a[94] @ 6016
	.word	077dd1519h,0411dcbcdh		; _a[95] @ 6080
	.word	01f151e75h,0412118bdh		; _a[96] @ 6144
	.word	05eda4e96h,0412bafach		; _a[97] @ 6208
	.word	0a48a3ddch,0410aa911h		; _a[98] @ 6272
	.word	0b5b6291ch,0412aae5dh		; _a[99] @ 6336
	.word	07dce1826h,0412cac84h		; _a[100] @ 6400
	.word	06daefa54h,0412dd6ebh		; _a[101] @ 6464
	.word	011a57cfdh,041275d7eh		; _a[102] @ 6528
	.word	0bfba55d2h,0412bb32eh		; _a[103] @ 6592
	.word	0f0fa955dh,04110253dh		; _a[104] @ 6656
	.word	0f073de1eh,04113c9afh		; _a[105] @ 6720
	.word	0decc956fh,04117e0d4h		; _a[106] @ 6784
	.word	0f7823c86h,04125d002h		; _a[107] @ 6848
	.word	0656f9768h,041189cach		; _a[108] @ 6912
	.word	01d203021h,0411268cbh		; _a[109] @ 6976
	.word	090bc2763h,041252e4ah		; _a[110] @ 7040
	.word	0fb133135h,0412b3164h		; _a[111] @ 7104
	.word	00130fdcfh,041256395h		; _a[112] @ 7168
	.word	08073a513h,041271f43h		; _a[113] @ 7232
	.word	03ab3d301h,0412700ceh		; _a[114] @ 7296
	.word	02ac9f9b4h,0411f4f0fh		; _a[115] @ 7360
	.word	0ef8264cah,0412d8884h		; _a[116] @ 7424
	.word	08bec537bh,0412e3382h		; _a[117] @ 7488
	.word	03ef78c94h,040fb329eh		; _a[118] @ 7552
	.word	01049fa1fh,040faed8fh		; _a[119] @ 7616
	.word	0e8c88a48h,0411d4349h		; _a[120] @ 7680
	.word	0c4bd9bd7h,041276e3dh		; _a[121] @ 7744
	.word	0c13f0422h,04127d50ah		; _a[122] @ 7808
	.word	035477865h,041250daeh		; _a[123] @ 7872
	.word	0dff33871h,0412e29e7h		; _a[124] @ 7936
	.word	0cb7a3048h,041143b5dh		; _a[125] @ 8000
	.word	0c3116f94h,0410df93eh		; _a[126] @ 8064
	.word	051be497ch,041263428h		; _a[127] @ 8128
	.word	0f96b11c7h,041259ee6h		; _a[128] @ 8192
	.word	09545f684h,04117feebh		; _a[129] @ 8256
	.word	0c6141cedh,0411bae97h		; _a[130] @ 8320
	.word	05661f18dh,041041587h		; _a[131] @ 8384
	.word	0b608794bh,04114295fh		; _a[132] @ 8448
	.word	0d6c00036h,040fdefe2h		; _a[133] @ 8512
	.word	022d2c534h,0412974aah		; _a[134] @ 8576
	.word	00fb3d22ah,041198f1fh		; _a[135] @ 8640
	.word	058a3e11bh,0412e763eh		; _a[136] @ 8704
	.word	0fc02e58eh,04105c5a5h		; _a[137] @ 8768
	.word	00eb7e68ch,041100039h		; _a[138] @ 8832
	.word	08f55f27bh,04116525ah		; _a[139] @ 8896
	.word	07ae26ef6h,04114cfaah		; _a[140] @ 8960
	.word	04fa1c913h,041242885h		; _a[141] @ 9024
	.word	0dad461edh,040fa98bbh		; _a[142] @ 9088
	.word	08a2fa001h,041155bf9h		; _a[143] @ 9152
	.word	05d74dc4bh,0411ba3fbh		; _a[144] @ 9216
	.word	0918cad22h,04104bacah		; _a[145] @ 9280
	.word	0f9cf6457h,041066b21h		; _a[146] @ 9344
	.word	0214544aeh,041088232h		; _a[147] @ 9408
	.word	075b4e3a2h,0412b23d0h		; _a[148] @ 9472
	.word	004b2e672h,04126b95ah		; _a[149] @ 9536
	.word	05fb7acaah,0412849a0h		; _a[150] @ 9600
	.word	08146d755h,0410792dch		; _a[151] @ 9664
	.word	0b8ea549dh,04124b74ah		; _a[152] @ 9728
	.word	0287a728dh,0412bd5b0h		; _a[153] @ 9792
	.word	0f08fbf25h,041258155h		; _a[154] @ 9856
	.word	0e55ab2d4h,040f71540h		; _a[155] @ 9920
	.word	0e5dd2ae9h,04113b51bh		; _a[156] @ 9984
	.word	078602e3eh,0412428e8h		; _a[157] @ 10048
	.word	064658a9eh,04100e48ch		; _a[158] @ 10112
	.word	0cc4b4d05h,040fcdeb4h		; _a[159] @ 10176
	.word	04c3b6383h,04127ef76h		; _a[160] @ 10240
	.word	06542a8f2h,0411b906ah		; _a[161] @ 10304
	.word	0f69c95cdh,041285c65h		; _a[162] @ 10368
	.word	0c456d92bh,0412d7b8dh		; _a[163] @ 10432
	.word	0728027d9h,0411eb0c5h		; _a[164] @ 10496
	.word	0b42b1558h,041095f86h		; _a[165] @ 10560
	.word	0174c0d1fh,0412a5204h		; _a[166] @ 10624
	.word	02a7fa857h,041285505h		; _a[167] @ 10688
	.word	0626dd4f0h,04116ec8eh		; _a[168] @ 10752
	.word	0544a1852h,0411414ffh		; _a[169] @ 10816
	.word	0f28603bbh,0412d42abh		; _a[170] @ 10880
	.word	0cdd575e9h,0410d54edh		; _a[171] @ 10944
	.word	077f87d55h,041280f0dh		; _a[172] @ 11008
	.word	05d142b30h,04124c020h		; _a[173] @ 11072
	.word	041cc532ah,0410864e2h		; _a[174] @ 11136
	.word	0e87a728dh,0411831e1h		; _a[175] @ 11200
	.word	07f1c8cffh,041215afch		; _a[176] @ 11264
	.word	019bce274h,0412225ebh		; _a[177] @ 11328
	.word	00d7f1c40h,04103edb0h		; _a[178] @ 11392
	.word	09e2bf7d6h,04129479bh		; _a[179] @ 11456
	.word	0546a1a50h,040e00917h		; _a[180] @ 11520
	.word	0d6be3484h,0412a9f6ch		; _a[181] @ 11584
	.word	054f8e483h,0412afc0fh		; _a[182] @ 11648
	.word	0302c8316h,04121cf60h		; _a[183] @ 11712
	.word	0b3721343h,0412d3e67h		; _a[184] @ 11776
	.word	0e4340fd2h,041281592h		; _a[185] @ 11840
	.word	02f5ceb93h,0412b2ca7h		; _a[186] @ 11904
	.word	0ecbdc0c0h,04103e659h		; _a[187] @ 11968
	.word	041d6cc2ah,041222c33h		; _a[188] @ 12032
	.word	053081a81h,040f42823h		; _a[189] @ 12096
	.word	0bba9237ah,0410279f0h		; _a[190] @ 12160
	.word	03eed428eh,0412060d3h		; _a[191] @ 12224
	.word	06ec4cfa8h,0412407e4h		; _a[192] @ 12288
	.word	09d090dc6h,0412d630fh		; _a[193] @ 12352
	.word	00b67c287h,040fe8871h		; _a[194] @ 12416
	.word	0df96b915h,041027fc5h		; _a[195] @ 12480
	.word	042ab6f85h,041145bb4h		; _a[196] @ 12544
	.word	0392f108fh,040f8ee7ch		; _a[197] @ 12608
	.word	07c2a5ccbh,041263069h		; _a[198] @ 12672
	.word	015117eaeh,0412c120ah		; _a[199] @ 12736
	.word	066054691h,04111270ah		; _a[200] @ 12800
$C$IR_1:	.set	1608

	.global	_a
_a:	.usect	".far",1608,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\145962 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\145964 
;**	Parameter deleted: req_flags == 9;
;**	Parameter deleted: tol == 1e-10;
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
||         MVKL    .S2     0xd9d7bdbb,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     _output,A11
||         MVKL    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     _output,A11
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3ddb7cdf,B7
||         MVK     .S1     0x9,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     _isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {_isequal} {0}      ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     _fcn_pass,A12
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     _fcn_pass,A12
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xd9d7bdbb,B6

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
;*   Local Frame Size  : 8 Args + 204 Auto + 56 Save = 268 byte               *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           STW     .D2T1   A11,*SP--(8)      ; |130| 
           STW     .D2T1   A10,*SP--(8)      ; |130| 
           STDW    .D2T2   B13:B12,*SP--     ; |130| 
           STDW    .D2T2   B11:B10,*SP--     ; |130| 
           STDW    .D2T1   A15:A14,*SP--     ; |130| 
           STDW    .D2T1   A13:A12,*SP--     ; |130| 
           STW     .D2T2   B3,*SP--(8)       ; |130| 

           MVKL    .S1     $C$SL1+0,A4
||         ADDK    .S2     -216,SP           ; |130| 

           CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {_driver_init} {0}  ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _a,A12
           MVKL    .S1     _output,A3
           MVKH    .S1     _a,A12
           MVKH    .S1     _output,A3

           MV      .L1     A12,A13
||         CALL    .S1     _log10            ; |147| 
||         LDW     .D1T1   *A3,A11

           LDDW    .D1T1   *A13++,A5:A4      ; |147| 
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
           ADDKPC  .S2     $C$RL5,B3,0       ; |147| 
$C$RL5:    ; CALL OCCURS {_log10} {0}        ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |146| 
||         STDW    .D1T1   A5:A4,*A11++      ; |147| 
||         SUB     .S1     A10,1,A10         ; |146| 

   [ A0]   B       .S2     $C$L3             ; |146| 
|| [!A0]   MVKL    .S1     _output,A3
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |147| 
|| [!A0]   ZERO    .L2     B10

   [ A0]   CALL    .S1     _log10            ; |147| 
   [!A0]   MVKH    .S1     _output,A3
   [!A0]   MVK     .S1     0xc9,A10
   [!A0]   ADD     .L2X    4,A3,B4
   [!A0]   STW     .D2T2   B4,*+SP(16)
           ; BRANCHCC OCCURS {$C$L3}         ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _log10dp          ; |150| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A12++,A5:A4      ; |150| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |150| 
$C$RL6:    ; CALL OCCURS {_log10dp} {0}      ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(16),B4       ; |150| 
           SUB     .L1     A10,1,A0          ; |149| 
           SUB     .L1     A10,1,A10         ; |149| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |150| 
   [ A0]   BNOP    .S1     $C$L4,3           ; |149| 

           ADD     .L2     B10,B4,B4         ; |150| 
||         ADD     .S2     8,B10,B10         ; |149| 

   [ A0]   CALL    .S1     _log10dp          ; |150| 
||         STDW    .D2T1   A5:A4,*B4         ; |150| 

           ; BRANCHCC OCCURS {$C$L4}         ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(16),B4
           ZERO    .L2     B10
           MVKL    .S1     _a,A10
           MVKH    .S1     _a,A10
           MVK     .S1     0xc9,A11
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(20)
||         CALL    .S1     _log10dp_c        ; |153| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |153| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |153| 
$C$RL7:    ; CALL OCCURS {_log10dp_c} {0}    ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(20),B4       ; |153| 
||         SUB     .L1     A11,1,A0          ; |152| 
||         SUB     .S1     A11,1,A11         ; |152| 

   [!A0]   LDW     .D2T1   *+SP(20),A3
   [!A0]   MVKL    .S2     _a,B8
   [!A0]   ZERO    .L2     B9                ; |103| 
   [!A0]   MV      .L2     B9,B12            ; |109| 
           LDW     .D2T2   *B4,B4            ; |153| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |152| 
|| [!A0]   ADD     .L1     4,A3,A15

           ADD     .L2     B10,B4,B4         ; |153| 
||         ADD     .S2     8,B10,B10         ; |152| 

   [ A0]   CALL    .S1     _log10dp_c        ; |153| 
||         STDW    .D2T1   A5:A4,*B4         ; |153| 

           ; BRANCHCC OCCURS {$C$L5}         ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           MVKH    .S2     _a,B8
||         MVK     .S1     0xfffffc01,A20
||         MV      .L2     B9,B26            ; |109| 
||         ZERO    .D2     B29
||         LDW     .D1T1   *A15,A3

           MV      .L2     B12,B28           ; |55| 
||         MVK     .D2     0xffffffff,B10    ; |115| 
||         MVK     .S2     0xc9,B2

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 27

           LDDW    .D2T2   *B8++,B5:B4       ; |85| 
||         MVKL    .S2     0x3fe6a09e,B6
||         ZERO    .L1     A4
||         ZERO    .L2     B30
||         ADD     .S1     1,A20,A18

           MVKL    .S2     0x667f3bcd,B31
||         SET     .S1     A4,0x15,0x1d,A4
||         STW     .D2T2   B9,*+SP(40)       ; |103| 

           MVKH    .S2     0x3fe6a09e,B6

           MVKH    .S2     0x667f3bcd,B31
||         STW     .D2T2   B6,*+SP(36)       ; |98| 

           STW     .D2T2   B31,*+SP(32)      ; |98| 

           CLR     .S2     B5,20,31,B6       ; |92| 
||         LDDW    .D2T2   *+SP(32),B17:B16  ; |98| 

           EXTU    .S2     B5,1,21,B1        ; |87| 

           OR      .S1X    A4,B6,A8          ; |92| 
|| [!B1]   ZERO    .L1     A5:A4             ; |92| 
||         SET     .S2     B30,0x15,0x1d,B6

   [ B1]   MV      .L1     A8,A5             ; |92| 
|| [ B1]   MV      .S1X    B4,A4             ; |92| 
||         STW     .D2T2   B6,*+SP(44)       ; |103| 
||         ZERO    .D1     A8                ; |103| 

           ADD     .L1X    A18,B1,A21        ; |87| 
           DADD    .L2X    0,A5:A4,B7:B6     ; |98| 
           CMPGTDP .S2     B7:B6,B17:B16,B0  ; |98| 
           MV      .L1X    B9,A18            ; |87| 

   [!B0]   LDDW    .D2T2   *+SP(40),B17:B16  ; |103| 
|| [ B0]   ZERO    .L1     A17
|| [ B0]   MV      .S1     A18,A16           ; |99| 
|| [!B0]   ZERO    .D1     A9
|| [ B0]   MV      .L2     B9,B16            ; |100| 
|| [ B0]   MV      .S2     B9,B18            ; |100| 

   [ B0]   SET     .S1     A17,0x15,0x1d,A17
|| [ B0]   MV      .L1     A18,A8            ; |99| 
|| [!B0]   ZERO    .D1     A19

   [ B0]   MV      .L1     A17,A9            ; |99| 
|| [!B0]   SET     .S1     A9,0x15,0x1d,A9
|| [!B0]   ADD     .D1X    A20,B1,A21        ; |105| 

   [ B0]   MV      .L2X    A17,B17           ; |99| 
   [ B0]   MV      .L2X    A17,B19           ; |99| 
   [!B0]   FSUBDP  .L2     B7:B6,B17:B16,B19:B18 ; |103| 
   [ B0]   FSUBDP  .L1     A5:A4,A17:A16,A17:A16 ; |99| 
   [!B0]   SET     .S1     A19,0x15,0x1d,A19
   [ B0]   FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |100| 
   [!B0]   FMPYDP  .M1X    A9:A8,B19:B18,A9:A8 ; |104| 
   [ B0]   DADD    .L2X    0,A17:A16,B7:B6   ; |99| Define a twin register
   [ B0]   FSUBDP  .L2     B7:B6,B19:B18,B19:B18 ; |99| 
   [ B0]   FADDDP  .L1X    B17:B16,A5:A4,A17:A16 ; |100| 
   [!B0]   FADDDP  .L1     A19:A18,A9:A8,A17:A16 ; |104| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 91
           ZERO    .L2     B13
           SET     .S2     B13,0x1e,0x1e,B13
           RCPDP   .S1     A17:A16,A5:A4     ; |109| 
           MV      .L1X    B13,A19           ; |109| 
           FMPYDP  .M1     A17:A16,A5:A4,A9:A8 ; |109| 
           MVKL    .S2     0xc041d580,B31
           MVKL    .S2     0x4b67ce0f,B30
           MVKH    .S2     0xc041d580,B31
           STW     .D2T2   B31,*+SP(52)      ; |55| 
           FSUBDP  .L2X    B13:B12,A9:A8,B7:B6 ; |109| 
           MVKH    .S2     0x4b67ce0f,B30
           STW     .D2T2   B30,*+SP(48)      ; |55| 
           MVKL    .S1     0x40738083,A11
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |109| 
           MV      .L2     B12,B6            ; |109| 
           MV      .L2     B13,B7            ; |109| 
           MVKL    .S1     0xfa15267e,A10
           FMPYDP  .M1     A17:A16,A5:A4,A9:A8 ; |109| 
           MVKH    .S1     0x40738083,A11
           MVKH    .S1     0xfa15267e,A10
           MVKL    .S1     0xc0880bfe,A13
           FSUBDP  .L1     A19:A18,A9:A8,A9:A8 ; |109| 
           MVKL    .S1     0x9c0d9077,A12
           MVKH    .S1     0xc0880bfe,A13
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |109| 
           MVKH    .S1     0x9c0d9077,A12
           STW     .D2T2   B28,*+SP(56)      ; |115| 
           MV      .L2     B13,B27           ; |55| 
           FMPYDP  .M1     A17:A16,A9:A8,A5:A4 ; |109| 
           NOP             4
           FSUBDP  .L2X    B7:B6,A5:A4,B7:B6 ; |109| 
           NOP             2
           FMPYDP  .M2X    A9:A8,B7:B6,B7:B6 ; |109| 
           NOP             3
           FMPYDP  .M2     B19:B18,B7:B6,B21:B20 ; |109| 
           LDDW    .D2T2   *+SP(48),B7:B6
           NOP             2
           FMPYDP  .M2     B21:B20,B21:B20,B17:B16 ; |109| 
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
           INTDP   .L1     A21,A19:A18       ; |115| 
           NOP             1

           FMPYDP  .M2X    A9:A8,B7:B6,B23:B22 ; |55| 
||         SET     .S2     B29,0x14,0x14,B6

           STW     .D2T2   B6,*+SP(60)       ; |115| 
           LDDW    .D2T2   *+SP(56),B7:B6    ; |115| 
           NOP             1
           FMPYDP  .M2X    B23:B22,A5:A4,B25:B24 ; |55| 
           NOP             2
           CMPLTDP .S2     B5:B4,B7:B6,B0    ; |115| 
           FSUBDP  .L2     B27:B26,B25:B24,B7:B6 ; |55| 

   [ B0]   B       .S2     $C$L7             ; |115| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   MVKL    .S1     0xffefffff,A7
|| [ B0]   MVK     .L1     0xffffffff,A6     ; |115| 

   [ B0]   MVKH    .S1     0xffefffff,A7
|| [ B1]   SUB     .D2     B2,1,B2           ; |155| 
|| [ B0]   MVKL    .S2     0x7fefffff,B11

           FMPYDP  .M2     B23:B22,B7:B6,B23:B22 ; |55| 
|| [!B0]   MVKL    .S2     0xbfe94415,B7

   [!B0]   MVKL    .S2     0xb356bd29,B6
   [!B0]   MVKH    .S2     0xbfe94415,B7
   [!B0]   MVKH    .S2     0xb356bd29,B6
           ; BRANCHCC OCCURS {$C$L7}         ; |115| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 38

           FMPYDP  .M2     B7:B6,B17:B16,B7:B6 ; |115| 
||         MVKL    .S1     0x4030624a,A9
||         FMPYDP  .M1X    B23:B22,A5:A4,A5:A4 ; |115| 
||         MVKL    .S2     0x12b3b59a,B24

           MVKL    .S2     0xc05007ff,B25
||         MVKL    .S1     0x2016afed,A8

           MVKH    .S1     0x4030624a,A9
           MVKH    .S1     0x2016afed,A8
           MV      .L1X    B13,A7            ; |115| 
           FADDDP  .L2X    A9:A8,B7:B6,B7:B6 ; |115| 
           MV      .L1X    B9,A6             ; |115| 
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |115| 
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |115| 
           MVKH    .S2     0x12b3b59a,B24
           MVKH    .S2     0xc05007ff,B25
           FMPYDP  .M2X    B23:B22,A5:A4,B23:B22 ; |115| 
           FADDDP  .L2     B25:B24,B7:B6,B7:B6 ; |115| 
           SUB     .L2     B2,1,B2           ; |155| 
           MVKL    .S1     0xbf2bd010,A5
           FMPYDP  .M2     B7:B6,B23:B22,B7:B6 ; |115| 
           MVKL    .S1     0x5c610ca8,A4
           MVKH    .S1     0xbf2bd010,A5
           MVKH    .S1     0x5c610ca8,A4
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |115| 
           FMPYDP  .M1     A5:A4,A19:A18,A5:A4 ; |115| 
           MV      .L2     B26,B16           ; |115| 
           MVKL    .S2     0x3fe63000,B17
           FMPYDP  .M2     B21:B20,B7:B6,B7:B6 ; |115| 
           MVKH    .S2     0x3fe63000,B17
           FMPYDP  .M2X    B17:B16,A19:A18,B17:B16 ; |115| 
           MVKL    .S2     0x7fefffff,B11
           FADDDP  .L2     B7:B6,B21:B20,B7:B6 ; |115| 
           MVKL    .S1     0x3fdbcb7b,A7
           MVKL    .S1     0x1526e50e,A6
           MVKH    .S1     0x3fdbcb7b,A7
           FADDDP  .L1X    B7:B6,A5:A4,A5:A4 ; |115| 
           MVKH    .S1     0x1526e50e,A6
           NOP             1
           FADDDP  .L1X    B17:B16,A5:A4,A5:A4 ; |115| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |115| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 8

           MVKH    .S2     0x7fefffff,B11
|| [!B2]   ADD     .L1     4,A15,A14

           CMPGTDP .S2     B5:B4,B11:B10,B0  ; |115| 
   [ B2]   B       .S1     $C$L6             ; |155| 

   [ B0]   MVKL    .S1     0x510ea7e7,A4
|| [!B0]   DADD    .L1     0,A7:A6,A5:A4     ; |115| 

   [ B0]   MVKL    .S1     0x40734413,A5
   [ B0]   MVKH    .S1     0x510ea7e7,A4
   [ B0]   MVKH    .S1     0x40734413,A5

           STDW    .D1T1   A5:A4,*A3++       ; |115| 
|| [!B2]   CALL    .S1     _log10dp_v        ; |158| 

           ; BRANCHCC OCCURS {$C$L6}         ; |155| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A14,B4           ; |158| 
           MVKL    .S1     _a,A4
           MVKH    .S1     _a,A4
           ADDKPC  .S2     $C$RL8,B3,0       ; |158| 
           MVK     .S1     0xc9,A6           ; |158| 
$C$RL8:    ; CALL OCCURS {_log10dp_v} {0}    ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     _allequal,B3
||         MVK     .S1     0xc9,A4           ; |161| 

$C$RL9:    ; CALL OCCURS {_allequal} {0}     ; |161| 

           CALLP   .S2     _print_test_results,B3
||         MVK     .L1     0x1,A4            ; |162| 

$C$RL10:   ; CALL OCCURS {_print_test_results} {0}  ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 48
           STW     .D2T1   A12,*+SP(104)     ; |109| 
           LDW     .D2T1   *+SP(48),A22      ; |109| 
           LDW     .D2T1   *+SP(32),A12

           ZERO    .L2     B24               ; |109| 
||         STW     .D2T1   A13,*+SP(108)     ; |109| 

           STW     .D2T2   B24,*+SP(96)      ; |170| 
           LDW     .D2T1   *+SP(52),A23      ; |109| 
           LDW     .D2T1   *+SP(60),A28      ; |55| 
           STW     .D2T1   A15,*+SP(24)      ; |121| 
           STW     .D2T1   A11,*+SP(116)     ; |109| 
           STW     .D2T2   B11,*+SP(204)     ; |121| 
           STW     .D2T1   A10,*+SP(112)     ; |109| 
           STW     .D2T2   B13,*+SP(92)      ; |109| 
           STW     .D2T2   B13,*+SP(100)     ; |109| 
           STW     .D2T2   B13,*+SP(132)     ; |109| 

           MVKL    .S2     0x3fdbcb7b,B4
||         STW     .D2T2   B13,*+SP(140)     ; |109| 

           MVKH    .S2     0x3fdbcb7b,B4
||         STW     .D2T2   B13,*+SP(84)      ; |109| 

           MVK     .L2     0x6,B29
||         STW     .D2T2   B4,*+SP(172)      ; |115| 

           ZERO    .L1     A19               ; |99| 
||         STW     .D2T2   B29,*+SP(12)      ; |174| 

           MVKL    .S1     0xbf2bd010,A3
||         ZERO    .L2     B28               ; |99| 
||         STW     .D2T1   A19,*+SP(56)      ; |174| 

           MVKL    .S1     0x5c610ca8,A31
||         ZERO    .L1     A16               ; |55| 
||         STW     .D2T2   B28,*+SP(64)      ; |173| 

           MVKL    .S1     0xc05007ff,A30
||         ZERO    .L2     B26               ; |109| 
||         STW     .D2T1   A16,*+SP(128)     ; |173| 

           MVKL    .S1     0x12b3b59a,A29
||         ZERO    .L2     B25               ; |109| 
||         STW     .D2T2   B26,*+SP(88)      ; |172| 

           MVKL    .S1     0x4030624a,A27
||         ZERO    .L1     A8                ; |55| 
||         STW     .D2T2   B25,*+SP(80)      ; |172| 

           MVKL    .S1     0x2016afed,A26
||         ZERO    .L1     A1                ; |118| 
||         STW     .D2T1   A8,*+SP(136)      ; |172| 

           MVKL    .S1     0xbfe94415,A25
||         ZERO    .L2     B23               ; |115| 
||         STW     .D2T1   A1,*+SP(192)      ; |170| 

           MVKL    .S1     0xb356bd29,A24
||         ZERO    .L1     A18               ; |104| 
||         STW     .D2T2   B23,*+SP(176)     ; |170| 

           MVKH    .S1     0xbf2bd010,A3
||         STW     .D2T1   A18,*+SP(48)      ; |174| 

           MVKH    .S1     0x5c610ca8,A31
||         STW     .D2T1   A3,*+SP(188)      ; |115| 

           MVKH    .S1     0xc05007ff,A30
||         STW     .D2T1   A31,*+SP(184)     ; |115| 

           MVKH    .S1     0x12b3b59a,A29
||         STW     .D2T1   A30,*+SP(148)     ; |55| 

           MVKH    .S1     0x4030624a,A27
||         STW     .D2T1   A29,*+SP(144)     ; |55| 

           MVKH    .S1     0x2016afed,A26
||         STW     .D2T1   A27,*+SP(156)     ; |55| 

           MVKL    .S2     0x3fe63000,B30
||         MVKH    .S1     0xbfe94415,A25
||         STW     .D2T1   A26,*+SP(152)     ; |55| 

           MVKL    .S2     _a_sc,B16
||         MVKH    .S1     0xb356bd29,A24
||         STW     .D2T1   A25,*+SP(164)     ; |55| 

           MVKH    .S2     0x3fe63000,B30
||         STW     .D2T1   A24,*+SP(160)     ; |55| 

           MVKH    .S2     _a_sc,B16
||         ZERO    .L2     B27               ; |104| 
||         STW     .D2T2   B30,*+SP(180)     ; |115| 

           ZERO    .L1     A5
||         ZERO    .S1     A4                ; |172| 
||         ADD     .L2     1,B11,B9
||         STW     .D2T2   B27,*+SP(32)      ; |173| 

           MV      .L1X    B16,A21
||         MV      .L2     B12,B8
||         MVKL    .S2     0x1526e50e,B31
||         ZERO    .S1     A7
||         ZERO    .D1     A6                ; |174| 
||         LDW     .D2T1   *+SP(36),A13      ; |103| 

           MV      .L1X    B16,A9            ; |173| 
||         MVKH    .S1     0xfff00000,A5
||         ZERO    .L2     B7
||         STDW    .D1T2   B9:B8,*+A21(16)   ; |171| 
||         MVKH    .S2     0x1526e50e,B31
||         STW     .D2T1   A22,*+SP(120)     ; |109| 

           STDW    .D1T1   A5:A4,*+A9(24)    ; |172| 
||         MV      .L1X    B16,A20           ; |172| 
||         MVKH    .S1     0xbff00000,A7
||         ADD     .L2     -7,B29,B24
||         ZERO    .S2     B6                ; |173| 
||         STW     .D2T2   B31,*+SP(168)     ; |115| 

           ZERO    .L2     B5
||         MV      .L1X    B16,A17           ; |174| 
||         SET     .S2     B7,0x14,0x1d,B7
||         STDW    .D1T1   A7:A6,*+A20(40)   ; |174| 
||         STW     .D2T2   B24,*+SP(200)     ; |170| 

           MV      .L1X    B16,A2            ; |172| 
||         ZERO    .L2     B4                ; |170| 
||         MVKH    .S2     0x80000000,B5
||         STW     .D2T1   A23,*+SP(124)     ; |109| 
||         STDW    .D1T2   B7:B6,*+A17(32)   ; |173| 

           ZERO    .L1     A9                ; |100| 
||         ZERO    .L2     B9:B8             ; |169| 
||         STW     .D2T1   A28,*+SP(196)     ; |118| 
||         STDW    .D1T2   B5:B4,*+A2(8)     ; |170| 

           STDW    .D1T2   B9:B8,*A21        ; |169| 
||         STW     .D2T1   A9,*+SP(72)       ; |173| 
||         CALL    .S1     _log10            ; |176| 
||         SUB     .L1X    B16,8,A15

           LDDW    .D1T1   *++A15,A5:A4      ; |176| 
           MVKL    .S2     _output,B10
           MVKH    .S2     _output,B10

           MV      .L1X    B13,A11           ; |109| 
||         ZERO    .S1     A10               ; |55| 
||         ZERO    .L2     B12               ; |100| 
||         ZERO    .S2     B11

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL11,B3,0      ; |176| 
$C$RL11:   ; CALL OCCURS {_log10} {0}        ; |176| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D2T2   *B10,B4           ; |176| 
           NOP             4

           ADD     .L2     B11,B4,B6         ; |176| 
||         DADD    .S2X    0,A5:A4,B5:B4     ; |176| 

           STDW    .D2T2   B5:B4,*B6         ; |176| 

           CALLP   .S2     _log10dp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |177| 

$C$RL12:   ; CALL OCCURS {_log10dp} {0}      ; |177| 
           LDW     .D2T2   *+B10(4),B4       ; |177| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |177| 
           STDW    .D2T1   A5:A4,*B4         ; |177| 

           CALLP   .S2     _log10dp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |178| 

$C$RL13:   ; CALL OCCURS {_log10dp_c} {0}    ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 187
           LDW     .D2T2   *+B10(8),B4       ; |178| 
           ZERO    .L1     A31
           LDDW    .D2T2   *+SP(80),B9:B8
           MVK     .S1     0xfffffc02,A30
           LDW     .D2T2   *+SP(24),B31      ; |121| 
           ADD     .L2     B11,B4,B4         ; |178| 
           STDW    .D2T1   A5:A4,*B4         ; |178| 
           LDDW    .D1T1   *A15,A17:A16      ; |85| 
           SET     .S1     A31,0x15,0x1d,A5
           NOP             3

           CLR     .S1     A17,20,31,A3      ; |92| 
||         MV      .L1     A16,A4            ; |92| 

           OR      .L1     A5,A3,A5          ; |92| 
||         EXTU    .S1     A17,1,21,A1       ; |87| 

   [!A1]   ZERO    .L1     A5:A4             ; |95| 
           CMPGTDP .S1     A5:A4,A13:A12,A0  ; |98| 
           NOP             1

   [!A0]   LDDW    .D2T1   *+SP(40),A7:A6    ; |100| 
|| [!A0]   ZERO    .L1     A3
|| [ A0]   ZERO    .S1     A3
|| [!A0]   ZERO    .L2     B4

   [ A0]   SET     .S1     A3,0x15,0x1d,A3

   [!A0]   SET     .S1     A3,0x15,0x1d,A3
|| [ A0]   STW     .D2T1   A3,*+SP(76)       ; |100| 

   [!A0]   STW     .D2T1   A3,*+SP(52)       ; |104| 
   [ A0]   LDDW    .D2T1   *+SP(72),A7:A6    ; |104| 

   [!A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |103| 
|| [!A0]   LDDW    .D2T1   *+SP(48),A7:A6    ; |100| 

   [!A0]   SET     .S2     B4,0x15,0x1d,B4
   [!A0]   STW     .D2T2   B4,*+SP(36)       ; |104| 
   [!A0]   LDDW    .D2T2   *+SP(32),B5:B4    ; |100| 
   [ A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |100| 
   [!A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |104| 
   [ A0]   ZERO    .L2     B13
   [ A0]   SET     .S2     B13,0x15,0x1d,B13
   [ A0]   ZERO    .L1     A3
   [ A0]   FADDDP  .L2X    B13:B12,A7:A6,B7:B6 ; |100| 
   [!A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |104| 
   [ A0]   SET     .S1     A3,0x15,0x1d,A3
   [ A0]   STW     .D2T1   A3,*+SP(60)       ; |99| 
           RCPDP   .S2     B7:B6,B5:B4       ; |109| 
   [ A0]   LDDW    .D2T1   *+SP(56),A7:A6    ; |99| 
           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |109| 
           ADD     .L1     A30,A1,A3         ; |87| 
   [!A0]   SUB     .L1     A3,1,A3           ; |105| 
           NOP             1
           FSUBDP  .L2     B9:B8,B17:B16,B9:B8 ; |109| 
   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |99| 
           NOP             1
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |109| 
           LDDW    .D2T2   *+SP(88),B5:B4
           NOP             2
           FMPYDP  .M2     B7:B6,B9:B8,B17:B16 ; |109| 
           NOP             3
           FSUBDP  .L2     B5:B4,B17:B16,B5:B4 ; |109| 
           NOP             2
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |109| 
           NOP             3

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |109| 
||         LDDW    .D2T2   *+SP(96),B7:B6    ; |99| 

           NOP             4

           FSUBDP  .L2     B7:B6,B9:B8,B7:B6 ; |109| 
|| [ A0]   ZERO    .S2     B8

   [ A0]   SET     .S2     B8,0x15,0x1d,B8
   [ A0]   STW     .D2T2   B8,*+SP(68)       ; |99| 
   [ A0]   LDDW    .D2T1   *+SP(64),A7:A6
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |109| 
           NOP             3
   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |99| 
           LDDW    .D2T1   *+SP(112),A7:A6
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A19:A18 ; |109| 
           LDDW    .D2T1   *+SP(120),A5:A4
           LDDW    .D2T2   *+SP(176),B5:B4
           NOP             1
           FMPYDP  .M1     A19:A18,A19:A18,A9:A8 ; |109| 
           NOP             3
           FADDDP  .L1     A5:A4,A9:A8,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |55| 
           NOP             3
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
           INTDP   .L1     A3,A7:A6          ; |115| 
           NOP             1
           FMPYDP  .M1     A5:A4,A21:A20,A5:A4 ; |55| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |115| 
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |115| 
           NOP             2

           FMPYDP  .M1     A19:A18,A5:A4,A9:A8 ; |115| 
||         LDDW    .D2T1   *+SP(184),A5:A4

           NOP             4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |115| 
           FADDDP  .L1     A9:A8,A19:A18,A9:A8 ; |115| 
           NOP             2
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |115| 
           NOP             3

           FADDDP  .L2X    B5:B4,A5:A4,B7:B6 ; |115| 
||         LDDW    .D2T2   *+SP(168),B5:B4

           LDDW    .D2T1   *+SP(192),A5:A4   ; |115| 
           NOP             3

           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |115| 
||         LDDW    .D2T2   *+SP(200),B5:B4   ; |115| 

           CMPLTDP .S1     A17:A16,A5:A4,A0  ; |118| 
           NOP             2

   [ A0]   MVKL    .S2     0xffefffff,B7
|| [ A0]   MVK     .L2     0xffffffff,B6     ; |119| 

           CMPGTDP .S2X    A17:A16,B5:B4,B0  ; |121| 
||         LDW     .D2T2   *+SP(12),B5       ; |179| 

           LDW     .D2T2   *B31,B4           ; |179| 
   [ A0]   MVKH    .S2     0xffefffff,B7
   [ B0]   MVKL    .S2     0x510ea7e7,B6
   [ B0]   MVKL    .S2     0x40734413,B7

           SUB     .L1X    B5,1,A0           ; |175| 
||         SUB     .L2     B5,1,B30          ; |175| 
|| [ B0]   MVKH    .S2     0x510ea7e7,B6

   [ A0]   B       .S1     $C$L8             ; |175| 
||         ADD     .L2     B11,B4,B4         ; |179| 
|| [ B0]   MVKH    .S2     0x40734413,B7
||         STW     .D2T2   B30,*+SP(12)      ; |179| 

   [ A0]   CALL    .S1     _log10            ; |176| 
||         STDW    .D2T2   B7:B6,*B4         ; |179| 

   [!A0]   CALL    .S1     _log10dp_v        ; |181| 
|| [ A0]   LDDW    .D1T1   *++A15,A5:A4      ; |176| 

   [!A0]   LDW     .D1T2   *A14,B4           ; |181| 
           ADD     .L2     8,B11,B11         ; |175| 
   [!A0]   MVKL    .S1     _a_sc,A4
           ; BRANCHCC OCCURS {$C$L8}         ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVK     .L1     0x6,A6            ; |181| 

           ADDKPC  .S2     $C$RL14,B3,0      ; |181| 
||         MVKH    .S1     _a_sc,A4

$C$RL14:   ; CALL OCCURS {_log10dp_v} {0}    ; |181| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     _allequal,B3
||         MVK     .L1     0x6,A4            ; |184| 

$C$RL15:   ; CALL OCCURS {_allequal} {0}     ; |184| 

           CALLP   .S2     _print_test_results,B3
||         MVK     .L1     0x3,A4            ; |185| 

$C$RL16:   ; CALL OCCURS {_print_test_results} {0}  ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 27
           LDW     .D2T1   *+SP(168),A29     ; |115| 
           LDW     .D2T1   *+SP(172),A30     ; |121| 
           LDW     .D2T1   *+SP(44),A28      ; |104| 

           LDW     .D2T2   *+SP(196),B5      ; |194| 
||         MV      .L2     B12,B4            ; |109| 

           STW     .D2T2   B4,*+SP(176)      ; |188| 
||         MVK     .L1     0xffffffff,A26    ; |121| 

           STW     .D2T1   A26,*+SP(200)     ; |188| 
||         MV      .L1     A10,A27           ; |103| 

           STW     .D2T1   A27,*+SP(136)
||         MV      .L2X    A11,B13           ; |109| 

           STW     .D2T2   B13,*+SP(140)     ; |109| 
           STW     .D2T2   B13,*+SP(132)     ; |109| 
           STW     .D2T2   B13,*+SP(100)     ; |109| 
           STW     .D2T2   B13,*+SP(92)      ; |109| 

           STW     .D2T2   B13,*+SP(84)      ; |109| 
||         MV      .L2     B12,B8            ; |109| 

           STW     .D2T2   B8,*+SP(80)
||         MV      .L2     B12,B9            ; |109| 

           STW     .D2T2   B9,*+SP(88)
||         MVK     .S2     0x777,B7

           STW     .D2T2   B7,*+SP(12)
||         MV      .L1     A10,A4            ; |103| 

           STW     .D2T1   A4,*+SP(128)

           STW     .D2T1   A4,*+SP(168)      ; |188| 
||         MVKL    .S1     0xcccccccd,A31

           STW     .D2T2   B13,*+SP(172)     ; |109| 
||         MV      .L2     B9,B31            ; |188| 
||         MVKL    .S1     0xc000cccc,A3

           STW     .D2T2   B31,*+SP(96)      ; |188| 
||         MVKH    .S1     0xcccccccd,A31

           STW     .D2T1   A31,*+SP(208)     ; |194| 
||         MVKH    .S1     0xc000cccc,A3

           STW     .D2T1   A3,*+SP(212)      ; |194| 

           STW     .D2T1   A28,*+SP(36)      ; |103| 
||         MVKL    .S2     _a_ext,B6

           STW     .D2T1   A29,*+SP(192)     ; |115| 
||         MVKH    .S2     _a_ext,B6

           STW     .D2T1   A30,*+SP(196)     ; |115| 

           STDW    .D2T2   B5:B4,*B6         ; |188| 
||         MV      .L1X    B6,A15            ; |188| 

           CALL    .S1     _log10            ; |190| 
||         LDDW    .D1T2   *A15,B5:B4        ; |190| 
||         MV      .L1X    B5,A11

           LDW     .D2T2   *+SP(24),B11      ; |194| 
||         MV      .L2     B12,B10           ; |109| 

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
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL17,B3,2      ; |190| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |190| 
$C$RL17:   ; CALL OCCURS {_log10} {0}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |190| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |190| 
           STDW    .D2T1   A5:A4,*B4         ; |190| 

           CALLP   .S2     _log10dp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |191| 

$C$RL18:   ; CALL OCCURS {_log10dp} {0}      ; |191| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T1   *+B4(4),A3        ; |191| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |191| 
           NOP             3
           ADD     .L1X    B10,A3,A3         ; |191| 
           STDW    .D1T2   B5:B4,*A3         ; |191| 

           CALLP   .S2     _log10dp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |192| 

$C$RL19:   ; CALL OCCURS {_log10dp_c} {0}    ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 200
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |192| 
           ZERO    .L1     A31
           LDDW    .D2T2   *+SP(80),B9:B8
           LDDW    .D2T1   *+SP(112),A19:A18
           MVK     .S1     0xfffffc02,A30
           ADD     .L2     B10,B4,B4         ; |192| 
           STDW    .D2T1   A5:A4,*B4         ; |192| 
           LDDW    .D1T1   *A15,A9:A8        ; |85| 
           SET     .S1     A31,0x15,0x1d,A5
           LDW     .D2T2   *B11,B31          ; |193| 
           NOP             2

           CLR     .S1     A9,20,31,A3       ; |92| 
||         MV      .L1     A8,A4             ; |92| 

           OR      .L1     A5,A3,A5          ; |92| 
||         EXTU    .S1     A9,1,21,A1        ; |87| 

   [!A1]   ZERO    .L1     A5:A4             ; |95| 
           CMPGTDP .S1     A5:A4,A13:A12,A0  ; |98| 
           NOP             1

   [!A0]   LDDW    .D2T1   *+SP(32),A7:A6    ; |100| 
|| [!A0]   ZERO    .L2     B4
|| [!A0]   ZERO    .L1     A3
|| [ A0]   ZERO    .S1     A3

   [ A0]   SET     .S1     A3,0x15,0x1d,A3

   [!A0]   SET     .S1     A3,0x15,0x1d,A3
|| [ A0]   STW     .D2T1   A3,*+SP(76)       ; |100| 

   [!A0]   STW     .D2T1   A3,*+SP(52)       ; |104| 
   [ A0]   LDDW    .D2T1   *+SP(72),A7:A6    ; |104| 

   [!A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |103| 
|| [!A0]   LDDW    .D2T1   *+SP(48),A7:A6    ; |100| 

   [!A0]   SET     .S2     B4,0x15,0x1d,B4
   [!A0]   STW     .D2T2   B4,*+SP(44)       ; |104| 
   [!A0]   LDDW    .D2T2   *+SP(40),B5:B4    ; |100| 
   [ A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |100| 
   [!A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |104| 
   [ A0]   ZERO    .L2     B13
   [ A0]   SET     .S2     B13,0x15,0x1d,B13
           ADD     .L1     A30,A1,A3         ; |87| 
   [ A0]   FADDDP  .L2X    B13:B12,A7:A6,B7:B6 ; |100| 
   [!A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |104| 
   [!A0]   SUB     .L1     A3,1,A3           ; |105| 
           CMPLTDP .S1     A9:A8,A11:A10,A2  ; |118| 
           RCPDP   .S2     B7:B6,B5:B4       ; |109| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |109| 
           NOP             3
           FSUBDP  .L2     B9:B8,B17:B16,B9:B8 ; |109| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |109| 
           LDDW    .D2T2   *+SP(88),B5:B4
           NOP             2
           FMPYDP  .M2     B7:B6,B9:B8,B17:B16 ; |109| 
           NOP             3
           FSUBDP  .L2     B5:B4,B17:B16,B5:B4 ; |109| 
           NOP             2
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |109| 
           NOP             3

           FMPYDP  .M2     B7:B6,B5:B4,B9:B8 ; |109| 
|| [ A0]   ZERO    .L2     B6

   [ A0]   SET     .S2     B6,0x15,0x1d,B6
   [ A0]   STW     .D2T2   B6,*+SP(60)       ; |99| 
           LDDW    .D2T2   *+SP(96),B7:B6    ; |99| 
   [ A0]   LDDW    .D2T1   *+SP(56),A7:A6    ; |99| 
           NOP             3

           FSUBDP  .L2     B7:B6,B9:B8,B7:B6 ; |109| 
|| [ A0]   ZERO    .S2     B8

   [ A0]   SET     .S2     B8,0x15,0x1d,B8
|| [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |99| 

   [ A0]   STW     .D2T2   B8,*+SP(68)       ; |99| 
   [ A0]   LDDW    .D2T1   *+SP(64),A7:A6
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |109| 
           NOP             3
   [ A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |99| 
           NOP             2
           FMPYDP  .M1X    A5:A4,B5:B4,A17:A16 ; |109| 
           LDDW    .D2T1   *+SP(120),A5:A4
           LDDW    .D2T2   *+SP(176),B5:B4
           NOP             1
           FMPYDP  .M1     A17:A16,A17:A16,A7:A6 ; |109| 
           NOP             3
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |55| 
           NOP             3
           FADDDP  .L1     A19:A18,A5:A4,A5:A4 ; |55| 
           LDDW    .D2T1   *+SP(104),A19:A18
           NOP             1
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |55| 
           NOP             3
           FADDDP  .L1     A19:A18,A5:A4,A21:A20 ; |55| 
           LDDW    .D2T1   *+SP(128),A5:A4
           NOP             1
           RCPDP   .S1     A21:A20,A19:A18   ; |55| 
           NOP             1
           FMPYDP  .M1     A19:A18,A21:A20,A23:A22 ; |55| 
           NOP             3
           FSUBDP  .L1     A5:A4,A23:A22,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A19:A18,A5:A4,A19:A18 ; |55| 
           LDDW    .D2T1   *+SP(136),A5:A4
           NOP             2
           FMPYDP  .M1     A19:A18,A21:A20,A23:A22 ; |55| 
           NOP             3
           FSUBDP  .L1     A5:A4,A23:A22,A5:A4 ; |55| 
           NOP             2

           FMPYDP  .M1     A19:A18,A5:A4,A19:A18 ; |55| 
||         LDDW    .D2T1   *+SP(160),A5:A4   ; |55| 

           NOP             4

           FMPYDP  .M1     A5:A4,A7:A6,A23:A22 ; |55| 
||         LDDW    .D2T1   *+SP(152),A5:A4   ; |55| 

           FMPYDP  .M1     A19:A18,A21:A20,A21:A20 ; |55| 
           NOP             3

           FADDDP  .L1     A5:A4,A23:A22,A23:A22 ; |55| 
||         LDDW    .D2T1   *+SP(168),A5:A4

           NOP             4
           FSUBDP  .L1     A5:A4,A21:A20,A5:A4 ; |55| 
           FMPYDP  .M1     A7:A6,A23:A22,A21:A20 ; |55| 
           NOP             1

           FMPYDP  .M1     A19:A18,A5:A4,A19:A18 ; |55| 
||         LDDW    .D2T1   *+SP(144),A5:A4   ; |55| 

           NOP             4
           FADDDP  .L1     A5:A4,A21:A20,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A5:A4,A19:A18,A5:A4 ; |55| 
           NOP             3
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |115| 
           INTDP   .L1     A3,A7:A6          ; |115| 
           NOP             2

           FMPYDP  .M1     A17:A16,A5:A4,A19:A18 ; |115| 
||         LDDW    .D2T1   *+SP(184),A5:A4

           NOP             4
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |115| 
           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |115| 
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |115| 
           NOP             1
           FADDDP  .L1     A17:A16,A5:A4,A5:A4 ; |115| 
           NOP             3

           FADDDP  .L2X    B5:B4,A5:A4,B7:B6 ; |115| 
||         LDDW    .D2T2   *+SP(192),B5:B4

           LDDW    .D2T1   *+SP(200),A5:A4
           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |115| 
           ADD     .L2     B10,B31,B6        ; |193| 
           CMPGTDP .S1     A9:A8,A5:A4,A1    ; |121| 
           LDDW    .D2T1   *+SP(208),A5:A4

   [ A2]   MVKL    .S2     0xffefffff,B5
|| [ A2]   MVK     .L2     0xffffffff,B4     ; |119| 

   [ A2]   MVKH    .S2     0xffefffff,B5
   [ A1]   MVKL    .S2     0x40734413,B5
   [ A1]   MVKL    .S2     0x510ea7e7,B4
   [ A1]   MVKH    .S2     0x40734413,B5
   [ A1]   MVKH    .S2     0x510ea7e7,B4
           STDW    .D2T2   B5:B4,*B6         ; |193| 

           LDDW    .D1T1   *A15,A7:A6        ; |194| 
||         LDW     .D2T2   *+SP(12),B4

           ADD     .L2     8,B10,B10         ; |189| 
           NOP             3

           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |194| 
||         SUB     .L1X    B4,1,A0           ; |189| 

   [ A0]   B       .S2     $C$L9             ; |189| 
|| [!A0]   MVKL    .S1     _output,A3

   [!A0]   MVKH    .S1     _output,A3
           SUB     .L2     B4,1,B4           ; |189| 

           STDW    .D1T1   A5:A4,*++A15      ; |194| 
||         STW     .D2T2   B4,*+SP(12)       ; |194| 
|| [!A0]   MV      .L2X    A3,B11            ; |196| 
|| [!A0]   MVKL    .S1     _a_ext,A4

   [ A0]   CALL    .S1     _log10            ; |190| 
|| [ A0]   LDDW    .D1T2   *A15,B5:B4        ; |190| 

   [!A0]   CALL    .S1     _log10dp_v        ; |196| 
|| [!A0]   LDW     .D2T2   *+B11(16),B4      ; |196| 

           ; BRANCHCC OCCURS {$C$L9}         ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           MVKH    .S1     _a_ext,A4
           MVK     .S1     0x777,A6          ; |196| 
           ADDKPC  .S2     $C$RL20,B3,2      ; |196| 
$C$RL20:   ; CALL OCCURS {_log10dp_v} {0}    ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL21:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B10
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B10
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(4)       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL22:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L2     B11,B5            ; |67| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL23:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A14,A5            ; |68| 
||         MV      .L2     B11,B4            ; |68| 
||         STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

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
           ADD     .L2     8,B10,B11
           STW     .D2T2   B4,*+SP(24)
           NOP             1

   [!B0]   MVKL    .S1     _all_pass,A3
|| [!B0]   B       .S2     $C$L10            ; |72| 
|| [!B0]   MV      .L1     A10,A4
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     _print_test_results ; |200| 
|| [!B0]   MVKH    .S1     _all_pass,A3
|| [ B0]   LDW     .D2T2   *B11,B0           ; |72| 

   [ B1]   ADD     .L2     4,B11,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L10}        ; |72| 
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
           CALL    .S1     _print_test_results ; |200| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |200| 
||         ADDKPC  .S2     $C$RL25,B3,0      ; |200| 

$C$RL25:   ; CALL OCCURS {_print_test_results} {0}  ; |200| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           MV      .L2     B12,B5            ; |114| 
           STW     .D2T2   B5,*+SP(36)       ; |114| 
           LDDW    .D2T2   *+SP(32),B5:B4    ; |114| 
           MVKL    .S1     _cycle_counts+24,A3
           MVKH    .S1     _cycle_counts+24,A3
           MV      .L2     B12,B6            ; |114| 
           NOP             1

           STDW    .D1T2   B5:B4,*A3         ; |114| 
||         MVC     .S2     B6,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           STDW    .D1T2   B5:B4,*A3         ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B6,B4,B9:B8       ; |117| 

           EXT     .S2     B9,24,24,B6       ; |117| 
||         SUB     .L2     B7,B5,B5          ; |117| 
||         MVKL    .S1     _t_offset,A3

           ADD     .L2     B5,B6,B5          ; |117| 
||         MV      .S2     B8,B4             ; |117| 
||         MVKH    .S1     _t_offset,A3

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MVKL    .S2     _input,B4

           MVKH    .S2     _input,B4
||         CALL    .S1     _gimme_random     ; |210| 

           MV      .L2     B12,B10
||         LDW     .D2T2   *B4,B12           ; |210| 

           ZERO    .L2     B5

           MVKL    .S1     0x412e8482,A5
||         MVK     .S2     0x80,B31

           MV      .L2X    A10,B4            ; |210| 
||         MVKH    .S2     0xbff00000,B5
||         STW     .D2T2   B31,*+SP(12)      ; |117| 
||         MVKH    .S1     0x412e8482,A5
||         MV      .L1     A10,A4            ; |210| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL26,B3,0      ; |210| 
$C$RL26:   ; CALL OCCURS {_gimme_random} {0}  ; |210| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 188
           ADD     .L2     B12,B10,B4        ; |210| 

           STDW    .D2T1   A5:A4,*B4         ; |210| 
||         MVC     .S2     TSCL,B16          ; |122| 

           MVC     .S2     TSCH,B17          ; |122| 

           ADD     .L2     B12,B10,B4        ; |94| 
||         ZERO    .L1     A3
||         CLR     .S1     A5,20,31,A16      ; |92| 
||         MV      .S2X    A10,B8            ; |100| 
||         ZERO    .D1     A31
||         ZERO    .D2     B19

           LDDW    .D2T1   *B4,A7:A6         ; |94| 
||         SET     .S1     A3,0x15,0x1d,A3
||         MV      .L2X    A10,B4            ; |100| 
||         SET     .S2     B19,0x1e,0x1e,B19
||         ZERO    .L1     A30
||         ZERO    .D1     A29

           MVKL    .S1     0x667f3bcd,A8
||         MV      .L1     A3,A11            ; |98| 
||         MV      .L2X    A10,B18           ; |109| 
||         ZERO    .D1     A26
||         MVKL    .S2     _output+12,B31

           MVKL    .S1     0x3fe6a09e,A9
||         MVKH    .S2     _output+12,B31

           MVKH    .S1     0x667f3bcd,A8
||         LDW     .D2T2   *B31,B30          ; |214| 

           MVKH    .S1     0x3fe6a09e,A9

           MV      .L1     A4,A6             ; |92| 
||         EXTU    .S1     A7,1,21,A0        ; |94| 
||         OR      .D1     A3,A16,A7         ; |92| 

   [!A0]   ZERO    .L1     A7:A6             ; |95| 
||         MVK     .S1     0xfffffc02,A27

           CMPGTDP .S1     A7:A6,A9:A8,A0    ; |98| 
           MV      .L1     A10,A8            ; |103| 

   [!A0]   FSUBDP  .L1     A7:A6,A11:A10,A7:A6 ; |103| 
|| [ A0]   MV      .D1     A3,A9             ; |98| 
|| [!A0]   MV      .L2X    A3,B5             ; |98| 
||         EXTU    .S1     A5,1,21,A28       ; |87| 

   [ A0]   FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |100| 
|| [ A0]   MV      .L2X    A3,B9             ; |103| 
||         MVKL    .S1     _t_start,A15

           MVKH    .S1     _t_start,A15
           STDW    .D1T2   B17:B16,*A15
   [!A0]   FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |104| 
   [!A0]   MV      .L2X    A3,B5             ; |104| 

   [ A0]   FADDDP  .L2X    B9:B8,A9:A8,B5:B4 ; |100| 
||         SET     .S1     A31,0x1e,0x1e,A9
||         MV      .L1     A10,A8            ; |109| 

           NOP             1
   [!A0]   FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |104| 
           NOP             2
           RCPDP   .S2     B5:B4,B7:B6       ; |109| 
           NOP             1
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |109| 
           NOP             4
           FSUBDP  .L1X    A9:A8,B9:B8,A9:A8 ; |109| 
           NOP             3

           FMPYDP  .M2X    B7:B6,A9:A8,B7:B6 ; |109| 
||         MV      .L1X    B19,A9            ; |109| 
||         MV      .S1     A10,A8            ; |99| 

           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |109| 
           NOP             3
           FSUBDP  .L2     B19:B18,B9:B8,B9:B8 ; |109| 
           NOP             2

           FMPYDP  .M2     B7:B6,B9:B8,B7:B6 ; |109| 
|| [ A0]   MV      .L2X    A3,B9             ; |109| 
||         MV      .S2     B18,B8            ; |109| 
||         ADD     .L1     A27,A28,A3        ; |87| 

   [!A0]   SUB     .L1     A3,1,A3           ; |105| 
   [ A0]   FSUBDP  .L1X    A7:A6,B9:B8,A7:A6 ; |99| 
           NOP             1
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |109| 
           NOP             4

           FSUBDP  .L1X    A9:A8,B5:B4,A17:A16 ; |109| 
|| [ A0]   MV      .S1     A11,A9            ; |109| 
||         MVKL    .S2     0xc041d580,B5

   [ A0]   FSUBDP  .L1     A7:A6,A9:A8,A7:A6 ; |99| 
||         MVKL    .S2     0x4b67ce0f,B4

           MVKH    .S2     0xc041d580,B5

           FMPYDP  .M1X    B7:B6,A17:A16,A17:A16 ; |109| 
||         MVKH    .S2     0x4b67ce0f,B4

           NOP             3

           FMPYDP  .M1     A7:A6,A17:A16,A9:A8 ; |109| 
||         MVKL    .S1     0x40738083,A17

           MVKL    .S1     0xfa15267e,A16
           MVKH    .S1     0x40738083,A17
           MVKH    .S1     0xfa15267e,A16
           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |109| 
           NOP             3

           FADDDP  .L1X    B5:B4,A7:A6,A19:A18 ; |55| 
||         MVKL    .S2     0xc0880bfe,B5

           MVKL    .S2     0x9c0d9077,B4
           MVKH    .S2     0xc0880bfe,B5

           FMPYDP  .M1     A7:A6,A19:A18,A19:A18 ; |55| 
||         MVKH    .S2     0x9c0d9077,B4

           NOP             3
           FADDDP  .L1     A17:A16,A19:A18,A17:A16 ; |55| 
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
||         MVKL    .S1     0xbf2bd010,A17

           FADDDP  .L2X    B9:B8,A19:A18,B7:B6 ; |55| 
||         MVKL    .S1     0x5c610ca8,A16

           MVKH    .S1     0xbf2bd010,A17
           MVKH    .S1     0x5c610ca8,A16

           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |55| 
||         MVKL    .S2     0x3fdbcb7b,B7

           MVKL    .S2     0x1526e50e,B6
           MVKH    .S2     0x3fdbcb7b,B7
           MVKH    .S2     0x1526e50e,B6
           NOP             1

           FMPYDP  .M1X    A7:A6,B5:B4,A19:A18 ; |115| 
||         INTDP   .L1     A3,A7:A6          ; |115| 
||         MVKL    .S2     0x3fe63000,B5
||         MV      .L2X    A10,B4            ; |115| 

           MVKH    .S2     0x3fe63000,B5
           NOP             2
           FMPYDP  .M1     A9:A8,A19:A18,A19:A18 ; |115| 
           FMPYDP  .M1     A17:A16,A7:A6,A17:A16 ; |115| 

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |115| 
||         MVKL    .S1     0x7fefffff,A7
||         MVK     .L1     0xffffffff,A6     ; |121| 

           MVKH    .S1     0x7fefffff,A7

           FADDDP  .L1     A19:A18,A9:A8,A9:A8 ; |115| 
||         CMPGTDP .S1     A5:A4,A7:A6,A0    ; |121| 

           NOP             2

           FADDDP  .L1     A9:A8,A17:A16,A17:A16 ; |115| 
||         SET     .S1     A26,0x14,0x14,A9
||         MV      .D1     A10,A8            ; |115| 

           CMPLTDP .S1     A5:A4,A9:A8,A1    ; |118| 
           NOP             2
           FADDDP  .L2X    B5:B4,A17:A16,B5:B4 ; |115| 
           NOP             2

           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |115| 
||         ADD     .L2     B10,B30,B6        ; |214| 

           NOP             3

   [ A1]   MVKL    .S2     0xffefffff,B5
|| [ A1]   MV      .L2X    A6,B4             ; |122| 

   [ A1]   MVKH    .S2     0xffefffff,B5
   [ A0]   MVKL    .S2     0x40734413,B5
   [ A0]   MVKL    .S2     0x510ea7e7,B4
   [ A0]   MVKH    .S2     0x40734413,B5
   [ A0]   MVKH    .S2     0x510ea7e7,B4

           STDW    .D2T2   B5:B4,*B6         ; |214| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S2     _t_offset,B13
||         MVKL    .S1     _t_stop,A13
||         ADD     .L2     8,B10,B10         ; |208| 

           MVKH    .S2     _t_offset,B13
||         MVKL    .S1     _cycle_counts+24,A12

           LDDW    .D2T2   *B13,B5:B4        ; |130| 
||         MVKL    .S2     _cycle_counts+24,B6
||         MVKH    .S1     _t_stop,A13

           MVKH    .S2     _cycle_counts+24,B6
||         MVKH    .S1     _cycle_counts+24,A12
||         STDW    .D1T2   B9:B8,*A13        ; |128| 

           LDDW    .D2T2   *B6,B7:B6         ; |130| 
           NOP             2
           ADDU    .L2     B4,B16,B19:B18    ; |130| 

           ADD     .S2     B19,B5,B16        ; |130| 
||         SUBU    .L2     B8,B18,B5:B4      ; |130| 

           ADD     .D2     B16,B17,B16       ; |130| 
||         EXT     .S2     B5,24,24,B17      ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B16,B16        ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         ADD     .D2     B5,B7,B4          ; |130| 

           ADD     .L2     B16,B17,B5        ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         LDW     .D2T2   *+SP(12),B4       ; |128| 

           STDW    .D1T2   B7:B6,*A12        ; |130| 
           NOP             3

           SUB     .L1X    B4,1,A0           ; |208| 
||         SUB     .L2     B4,1,B4           ; |208| 

           STW     .D2T2   B4,*+SP(12)       ; |130| 
||         MVKL    .S2     _input,B4
|| [ A0]   ZERO    .L2     B5
|| [ A0]   MV      .L1     A10,A4            ; |210| 
|| [ A0]   B       .S1     $C$L11            ; |208| 
|| [!A0]   LDDW    .D1T1   *A12,A5:A4        ; |135| 

   [ A0]   CALL    .S1     _gimme_random     ; |210| 
||         MVKH    .S2     _input,B4

   [ A0]   LDW     .D2T2   *B4,B12           ; |210| 
|| [!A0]   CALL    .S2     __fltllif         ; |135| 
|| [ A0]   MVKL    .S1     0x412e8482,A5
|| [ A0]   MV      .L2X    A10,B4            ; |210| 

   [ A0]   MVKH    .S1     0x412e8482,A5
|| [ A0]   MVKH    .S2     0xbff00000,B5

           NOP             2
           ; BRANCHCC OCCURS {$C$L11}        ; |208| 
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
;          EXCLUSIVE CPU CYCLES: 19
           LDDW    .D2T2   *+SP(32),B5:B4
           MV      .L2X    A12,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B10
           MV      .L2X    A10,B31           ; |114| 

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 
||         MVKL    .S1     _output,A3

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVKH    .S1     _output,A3

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MV      .L1X    B12,A10
||         CALL    .S1     _log10            ; |222| 
||         LDW     .D1T1   *A3,A12

           LDDW    .D1T1   *A10++,A5:A4      ; |222| 
           MVK     .S2     0x80,B12
           NOP             2
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL29,B3,0      ; |222| 
$C$RL29:   ; CALL OCCURS {_log10} {0}        ; |222| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1X    B12,1,A0          ; |221| 
||         STDW    .D1T1   A5:A4,*A12++      ; |222| 

   [ A0]   B       .S1     $C$L12            ; |221| 
   [ A0]   CALL    .S1     _log10            ; |222| 
   [ A0]   LDDW    .D1T1   *A10++,A5:A4      ; |222| 
           SUB     .L2     B12,1,B12         ; |221| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L12}        ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MV      .L2     B4,B9             ; |128| 
           LDDW    .D2T2   *B10,B5:B4        ; |130| 
           NOP             2
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
           ADD     .L1X    A5,B7,A3          ; |130| 

           ADD     .L1     A3,A7,A3          ; |130| 
||         SUBU    .L2X    B8,A4,B7:B6       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B7,24,24,B16      ; |130| 
||         ADDU    .L2     B4,B6,B7:B6       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 

           ADD     .L2     B7,B5,B4          ; |130| 
||         ADD     .S2     B4,B16,B5         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MV      .S2X    A13,B4            ; |130| 

           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL30,B3,0      ; |130| 

$C$RL30:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
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

$C$RL31:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(32),B5:B4    ; |130| 
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MVKL    .S1     _input,A12

           MVKH    .S1     _input,A12
||         MV      .L1     A10,A13
||         MV      .D1X    B4,A10            ; |117| 
||         LDW     .D2T2   *+SP(16),B12      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A12,A3           ; |230| 
           NOP             4

           ADD     .L1     A13,A3,A3         ; |230| 
||         CALL    .S1     _log10dp          ; |230| 

           LDDW    .D1T1   *A3,A5:A4         ; |230| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |230| 
$C$RL32:   ; CALL OCCURS {_log10dp} {0}      ; |230| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |230| 
||         SUB     .L1     A10,1,A0          ; |229| 
||         SUB     .S1     A10,1,A10         ; |229| 

   [ A0]   BNOP    .S1     $C$L13,3          ; |229| 

           ADD     .L1X    A13,B4,A3         ; |230| 
||         ADD     .S1     8,A13,A13         ; |229| 

           STDW    .D1T1   A5:A4,*A3         ; |230| 
           ; BRANCHCC OCCURS {$C$L13}        ; |229| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MV      .L2     B13,B4            ; |128| 
||         LDDW    .D1T1   *A15,A7:A6        ; |130| 

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           MV      .L2     B5,B9             ; |128| 
           LDDW    .D2T2   *+B10(8),B5:B4    ; |130| 
           NOP             2
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
           ADD     .L1X    A5,B7,A3          ; |130| 

           ADD     .L1     A3,A7,A3          ; |130| 
||         SUBU    .L2X    B8,A4,B7:B6       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B7,24,24,B16      ; |130| 
||         ADDU    .L2     B4,B6,B7:B6       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 

           ADD     .L2     B7,B5,B4          ; |130| 
||         ADD     .S2     B4,B16,B5         ; |130| 

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
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDDW    .D2T2   *+SP(32),B5:B4
           ADDAD   .D2     B10,1,B12
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B5           ; |117| 

           SUBU    .L2     B4,B8,B7:B6       ; |117| 
||         MVKL    .S2     _t_offset,B30

           SUB     .L2     B5,B9,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVK     .S2     0x80,B4

           MVKH    .S2     _t_offset,B30
||         LDW     .D2T2   *+SP(20),B13      ; |117| 

           MV      .L1X    B4,A13            ; |117| 
||         STDW    .D2T2   B7:B6,*B30        ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A12,A3           ; |238| 
           NOP             4

           ADD     .L1     A10,A3,A3         ; |238| 
||         CALL    .S1     _log10dp_c        ; |238| 

           LDDW    .D1T1   *A3,A5:A4         ; |238| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |238| 
$C$RL35:   ; CALL OCCURS {_log10dp_c} {0}    ; |238| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |238| 
||         SUB     .L1     A13,1,A0          ; |237| 
||         SUB     .S1     A13,1,A13         ; |237| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |237| 

           ADD     .L1X    A10,B4,A3         ; |238| 
||         ADD     .S1     8,A10,A10         ; |237| 

           STDW    .D1T1   A5:A4,*A3         ; |238| 
           ; BRANCHCC OCCURS {$C$L14}        ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     _t_offset,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           MVKH    .S2     _t_offset,B4
           LDDW    .D2T2   *B4,B9:B8         ; |130| 
           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           MV      .L2     B5,B7             ; |128| 
           NOP             2
           ADDU    .L2X    B8,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B9,B8          ; |130| 
||         SUBU    .L2     B6,B4,B5:B4       ; |130| 

           ADD     .D2X    B8,A5,B8          ; |130| 
||         CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B5,24,24,B9       ; |130| 
||         ADDU    .L2     B16,B4,B5:B4      ; |130| 

           SUB     .L2     B7,B8,B8          ; |130| 
||         ADD     .S2     B5,B17,B5         ; |130| 

           ADD     .L2     B8,B9,B8          ; |130| 

           ADD     .L2     B5,B8,B5          ; |130| 
||         MVKL    .S2     _t_stop,B8

           MVKH    .S2     _t_stop,B8

           STDW    .D2T2   B7:B6,*B8         ; |128| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL36,B3,0      ; |130| 

$C$RL36:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 111
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           LDDW    .D2T2   *+SP(32),B5:B4
           ADDAD   .D2     B12,1,B13
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A15        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     _t_offset,A3
           MVKL    .S1     _output,A13

           SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKH    .S1     _t_offset,A3

           MVKH    .S1     _output,A13
||         MV      .L2X    A12,B9            ; |245| 
||         SUB     .D2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         LDW     .D1T2   *+A13(16),B4      ; |245| 
||         LDW     .D2T1   *B9,A4            ; |245| 
||         MV      .S2X    A3,B10            ; |117| 

           CALLP   .S2     _log10dp_v,B3
||         STDW    .D2T2   B7:B6,*B10        ; |117| 
||         MVK     .S1     0x80,A6           ; |245| 

$C$RL38:   ; CALL OCCURS {_log10dp_v} {0}    ; |245| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           MVK     .S1     16,A12
           ADD     .L1X    B13,A12,A12
           LDDW    .D1T1   *A12,A17:A16      ; |130| 
           MV      .L2     B4,B9             ; |128| 
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           MV      .L1     A6,A3             ; |130| 

           SUBU    .L1X    B8,A3,A9:A8       ; |130| 
||         MVKL    .S1     _t_stop,A3

           EXT     .S1     A9,24,24,A30      ; |130| 
||         ADD     .L1X    A7,B7,A31         ; |130| 

           MVKH    .S1     _t_stop,A3
||         ADD     .L1     A31,A5,A4         ; |130| 

           SUB     .S1X    B9,A4,A6          ; |130| 
||         ADDU    .L1     A16,A8,A5:A4      ; |130| 

           MV      .L2X    A3,B4             ; |128| 
||         ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A6,A30,A5         ; |130| 

           CALLP   .S2     __fltllif,B3
||         STDW    .D2T2   B9:B8,*B4         ; |128| 
||         ADD     .L1     A3,A5,A5          ; |130| 

$C$RL39:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL40:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STDW    .D1T1   A5:A4,*A12        ; |130| 
||         MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A13(4),B4       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A13,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL41:   ; CALL OCCURS {_isequal} {0}      ; |66| 

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKH    .S1     _fcn_pass,A3
||         MVKL    .S2     0x3ddb7cdf,B7

           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A13,A4           ; |67| 
||         MV      .L2X    A3,B10            ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A13(8),B4       ; |67| 
||         STW     .D2T1   A5,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL42:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A13(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A13,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL43:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *A14,B4           ; |69| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A13,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL44:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(24),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           NOP             4

   [!B0]   BNOP    .S1     $C$L15,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B11,B0           ; |72| 

   [ B1]   ADD     .L2     4,B11,B4
           ; BRANCHCC OCCURS {$C$L15}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A10,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L16            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |251| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L16}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |251| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1     A10,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |251| 
||         ADDKPC  .S2     $C$RL45,B3,0      ; |251| 

$C$RL45:   ; CALL OCCURS {_print_test_results} {0}  ; |251| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL46:   ; CALL OCCURS {_printf} {0}       ; |252| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL47:   ; CALL OCCURS {_printf} {0}       ; |252| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |259| 

$C$RL48:   ; CALL OCCURS {_print_profile_results} {0}  ; |259| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |262| 

$C$RL49:   ; CALL OCCURS {_print_memory_results} {0}  ; |262| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADDK    .S2     216,SP            ; |263| 
           LDW     .D2T2   *++SP(8),B3       ; |263| 
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
$C$SL1:	.string	"log10DP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_log10
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_log10dp
	.global	_log10dp_c
	.global	_log10dp_v
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
