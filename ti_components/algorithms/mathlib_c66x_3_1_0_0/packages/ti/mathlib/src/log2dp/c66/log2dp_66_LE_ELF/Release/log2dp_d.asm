;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:46:26 2013                                *
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
	.word	0aa9ea49bh,040a37287h		; a[0] @ 0
	.word	06600e5d9h,040c271a7h		; a[1] @ 64
	.word	089f33369h,040bb2b7fh		; a[2] @ 128
	.word	06bf1c0a2h,0409e340ah		; a[3] @ 192
	.word	0a1dd34fah,040a4936fh		; a[4] @ 256
	.word	0be5cc781h,040b25f34h		; a[5] @ 320
	.word	0bbbf5e4fh,040808b90h		; a[6] @ 384
	.word	0584032f6h,040a2ed38h		; a[7] @ 448
	.word	00f66a551h,040c34f04h		; a[8] @ 512
	.word	09eff3428h,04055e88eh		; a[9] @ 576
	.word	0836d076ah,040a21c78h		; a[10] @ 640
	.word	058d5842bh,040b983d6h		; a[11] @ 704
	.word	08fe5bbb1h,040b399b6h		; a[12] @ 768
	.word	04e1cc385h,040c06922h		; a[13] @ 832
	.word	0f20b4ab7h,040b33846h		; a[14] @ 896
	.word	04b0c6dcdh,040ad5151h		; a[15] @ 960
	.word	011c2a023h,040a10a00h		; a[16] @ 1024
	.word	08ae09932h,040b737deh		; a[17] @ 1088
	.word	08e523dbah,040b03afdh		; a[18] @ 1152
	.word	02f42e3aah,040bc1753h		; a[19] @ 1216
	.word	0be5bf0c2h,040c19f1bh		; a[20] @ 1280
	.word	0a3ef5df1h,040a39643h		; a[21] @ 1344
	.word	0859bb5d4h,040c2644fh		; a[22] @ 1408
	.word	0be751b35h,040a9b4b9h		; a[23] @ 1472
	.word	04628d93dh,040b97c1dh		; a[24] @ 1536
	.word	0dd68fc43h,0409287d3h		; a[25] @ 1600
	.word	03d79de12h,040ab73a7h		; a[26] @ 1664
	.word	04478d5d5h,0409ddd00h		; a[27] @ 1728
	.word	0b78f4de6h,040c22249h		; a[28] @ 1792
	.word	032144f42h,040c0e3cfh		; a[29] @ 1856
	.word	04d6c9a5dh,040a3fa80h		; a[30] @ 1920
	.word	0a86ff632h,040b8bb43h		; a[31] @ 1984
	.word	0d30270f4h,040b44e63h		; a[32] @ 2048
	.word	0e6695605h,040b31ee6h		; a[33] @ 2112
	.word	0f5c5ea5ah,040b87cbch		; a[34] @ 2176
	.word	045df0762h,040aa4095h		; a[35] @ 2240
	.word	0a8c30249h,040b61994h		; a[36] @ 2304
	.word	03efa10d3h,040ab18b5h		; a[37] @ 2368
	.word	0bed30f06h,040be42ddh		; a[38] @ 2432
	.word	0cb3298dah,040a984c5h		; a[39] @ 2496
	.word	0aaa8b596h,040b53635h		; a[40] @ 2560
	.word	08853f6f8h,04093755ch		; a[41] @ 2624
	.word	02353c21fh,040abb4c3h		; a[42] @ 2688
	.word	039fc7b10h,040c2c841h		; a[43] @ 2752
	.word	0d50f916dh,040a60597h		; a[44] @ 2816
	.word	0f1729e83h,040c0a4bdh		; a[45] @ 2880
	.word	058b7513bh,040ac2186h		; a[46] @ 2944
	.word	0091e8cb3h,040c292e3h		; a[47] @ 3008
	.word	00374ff86h,040c29038h		; a[48] @ 3072
	.word	0aca940d7h,040c20c39h		; a[49] @ 3136
	.word	0ef749782h,040944914h		; a[50] @ 3200
	.word	0a00e27e1h,040ab0e7bh		; a[51] @ 3264
	.word	0bc8f67e7h,040822e58h		; a[52] @ 3328
	.word	02ed1a4a3h,040808e20h		; a[53] @ 3392
	.word	0169f7eb6h,040ab85e4h		; a[54] @ 3456
	.word	02953b660h,040b4fd2ah		; a[55] @ 3520
	.word	07f1a9252h,040b2259bh		; a[56] @ 3584
	.word	0d9620685h,040a82990h		; a[57] @ 3648
	.word	01f4ccc61h,04080b820h		; a[58] @ 3712
	.word	04765f01fh,040a524a3h		; a[59] @ 3776
	.word	0eda081ebh,040ac9eb6h		; a[60] @ 3840
	.word	070db346fh,040905563h		; a[61] @ 3904
	.word	0c52f499ah,040b7a4bah		; a[62] @ 3968
	.word	09aa10096h,040b87e25h		; a[63] @ 4032
	.word	0a3486f05h,040a7ea4ah		; a[64] @ 4096
	.word	090f4af6ah,0409d6e97h		; a[65] @ 4160
	.word	02368bad4h,040bc2870h		; a[66] @ 4224
	.word	0befc29b2h,040745904h		; a[67] @ 4288
	.word	0b73b6b10h,0409b7c0ah		; a[68] @ 4352
	.word	0168801c2h,040ba3adah		; a[69] @ 4416
	.word	0d4bbae97h,040b216e1h		; a[70] @ 4480
	.word	05edd0529h,040a44066h		; a[71] @ 4544
	.word	00bfa0946h,040a00e0dh		; a[72] @ 4608
	.word	0637bd05bh,040c3324ch		; a[73] @ 4672
	.word	0d69b82a8h,040a27bcfh		; a[74] @ 4736
	.word	0360143cdh,040b04555h		; a[75] @ 4800
	.word	015a8deb1h,040c2e056h		; a[76] @ 4864
	.word	01fcaa0a3h,040c1d318h		; a[77] @ 4928
	.word	09e3e4408h,040be9d16h		; a[78] @ 4992
	.word	0eeee5fc5h,040c2d1eeh		; a[79] @ 5056
	.word	0ed0db4f4h,040adf3a5h		; a[80] @ 5120
	.word	02d8f8544h,040b72680h		; a[81] @ 5184
	.word	06ed5a0b1h,0409e0550h		; a[82] @ 5248
	.word	04f582ce8h,040bb88e0h		; a[83] @ 5312
	.word	0885aacf5h,040bbf08ah		; a[84] @ 5376
	.word	066ea19e5h,040b31711h		; a[85] @ 5440
	.word	0d8f6a6bbh,040c1b872h		; a[86] @ 5504
	.word	02b3969aeh,040be9615h		; a[87] @ 5568
	.word	077b395c4h,040b6450eh		; a[88] @ 5632
	.word	0897a67a5h,040b0dc63h		; a[89] @ 5696
	.word	0e36c4b83h,040bb59e6h		; a[90] @ 5760
	.word	0dd8805f3h,040baf1aeh		; a[91] @ 5824
	.word	05f3ca679h,040c17633h		; a[92] @ 5888
	.word	012896f80h,040b648e7h		; a[93] @ 5952
	.word	07996c4d3h,040bb04b0h		; a[94] @ 6016
	.word	07f47debch,040a39ae9h		; a[95] @ 6080
	.word	0a18372e7h,040c33031h		; a[96] @ 6144
	.word	046bfd7f2h,040b06229h		; a[97] @ 6208
	.word	096f4a3abh,040ab2f8ch		; a[98] @ 6272
	.word	0545d4f66h,040b98828h		; a[99] @ 6336
	.word	02058651ch,040b29affh		; a[100] @ 6400
	.word	008ede54bh,040bffb19h		; a[101] @ 6464
	.word	08c4e577ch,040b2f1e8h		; a[102] @ 6528
	.word	0a167c434h,040b00a61h		; a[103] @ 6592
	.word	07bf11226h,040ab64f8h		; a[104] @ 6656
	.word	00167df0ch,040c2b63fh		; a[105] @ 6720
	.word	0ef69afc7h,040a36695h		; a[106] @ 6784
	.word	0afc1fa0bh,040ae5af7h		; a[107] @ 6848
	.word	09096bb99h,040c23cfah		; a[108] @ 6912
	.word	0517a4617h,040ae0777h		; a[109] @ 6976
	.word	014636453h,04094d482h		; a[110] @ 7040
	.word	040ba0473h,040beeb3fh		; a[111] @ 7104
	.word	02c669058h,040c17de3h		; a[112] @ 7168
	.word	0442fdab9h,040c2f6c0h		; a[113] @ 7232
	.word	0970ea4deh,040c33bb1h		; a[114] @ 7296
	.word	0a44c7b03h,0409ba8dch		; a[115] @ 7360
	.word	05d3b447ah,040a35968h		; a[116] @ 7424
	.word	027d028a2h,040c25cdch		; a[117] @ 7488
	.word	042d63e66h,040c34fedh		; a[118] @ 7552
	.word	08dadd30dh,040b10e99h		; a[119] @ 7616
	.word	00ac3a861h,040ab24c3h		; a[120] @ 7680
	.word	07db02f07h,040c0cd02h		; a[121] @ 7744
	.word	0fba6d4ebh,040ba28f2h		; a[122] @ 7808
	.word	0678cd713h,040bfb0b1h		; a[123] @ 7872
	.word	002645e4eh,040c16116h		; a[124] @ 7936
	.word	02967d856h,040b92fd0h		; a[125] @ 8000
	.word	0871d9613h,040c19a17h		; a[126] @ 8064
	.word	0f61dfeefh,040c12db7h		; a[127] @ 8128
	.word	0dc39515ah,040c207adh		; a[128] @ 8192
	.word	05257bba9h,040b54df1h		; a[129] @ 8256
	.word	0643be9bbh,040c1793fh		; a[130] @ 8320
	.word	005da3494h,040b66778h		; a[131] @ 8384
	.word	06a400fbbh,040c047e6h		; a[132] @ 8448
	.word	0b34a44c8h,040997729h		; a[133] @ 8512
	.word	0ef284168h,040a0c813h		; a[134] @ 8576
	.word	0b03b9c8eh,04098e192h		; a[135] @ 8640
	.word	0424879ech,040ab915ch		; a[136] @ 8704
	.word	003f55806h,040b10beeh		; a[137] @ 8768
	.word	0702f3d04h,040bddc3eh		; a[138] @ 8832
	.word	06787ce96h,040a3b305h		; a[139] @ 8896
	.word	05ef62f9dh,040b5d05ah		; a[140] @ 8960
	.word	0629d840ah,040b962f3h		; a[141] @ 9024
	.word	04c8ca08dh,040bec3a5h		; a[142] @ 9088
	.word	005242c2fh,040bf9dc5h		; a[143] @ 9152
	.word	0ccc39291h,040c0d2feh		; a[144] @ 9216
	.word	03a0e18c7h,040b13b23h		; a[145] @ 9280
	.word	098e10cf6h,040c12663h		; a[146] @ 9344
	.word	0655e28aah,040957605h		; a[147] @ 9408
	.word	0ec09a8f6h,04072d49bh		; a[148] @ 9472
	.word	00e3c02e6h,040be3baeh		; a[149] @ 9536
	.word	0792c3bc8h,040c2e539h		; a[150] @ 9600
	.word	068d17ab1h,040c1202ah		; a[151] @ 9664
	.word	0752da986h,0409abab0h		; a[152] @ 9728
	.word	00e842742h,040c302a5h		; a[153] @ 9792
	.word	086594af5h,040a9fd94h		; a[154] @ 9856
	.word	0989df117h,04060e3b5h		; a[155] @ 9920
	.word	0cb252ce0h,040bc7237h		; a[156] @ 9984
	.word	0f5b44ca3h,040bb4441h		; a[157] @ 10048
	.word	0f8b9baa1h,040b7752bh		; a[158] @ 10112
	.word	0ecdc36cdh,040c1405ch		; a[159] @ 10176
	.word	070931013h,040b3ca85h		; a[160] @ 10240
	.word	0016c10cah,040c29ab8h		; a[161] @ 10304
	.word	0a1ac8d92h,040bc6a2bh		; a[162] @ 10368
	.word	0bfc57d4dh,0409ab074h		; a[163] @ 10432
	.word	088d0f47ah,040b89bf3h		; a[164] @ 10496
	.word	04346a6adh,04088aaa1h		; a[165] @ 10560
	.word	0cabdfed4h,04075d1b0h		; a[166] @ 10624
	.word	054f01c5dh,040c12e64h		; a[167] @ 10688
	.word	0100be6beh,040b71261h		; a[168] @ 10752
	.word	00efc1c46h,040be8069h		; a[169] @ 10816
	.word	08be2f7b1h,0409a17eeh		; a[170] @ 10880
	.word	032b55ef2h,040ae7231h		; a[171] @ 10944
	.word	039ffd60fh,040a02df0h		; a[172] @ 11008
	.word	017ec85d0h,0408a1777h		; a[173] @ 11072
	.word	055227144h,0409379a7h		; a[174] @ 11136
	.word	09ba435d5h,040aee5cah		; a[175] @ 11200
	.word	05517898ah,040b99990h		; a[176] @ 11264
	.word	0c8d419c8h,040ad3578h		; a[177] @ 11328
	.word	01a21ea36h,040a2f8e1h		; a[178] @ 11392
	.word	00718f8f5h,040c2d5d5h		; a[179] @ 11456
	.word	04f4186b3h,040b1133bh		; a[180] @ 11520
	.word	08ce55631h,040ad19deh		; a[181] @ 11584
	.word	04084548eh,040a10277h		; a[182] @ 11648
	.word	057173e0ah,040b28374h		; a[183] @ 11712
	.word	08428184dh,040b03ba1h		; a[184] @ 11776
	.word	002bef721h,04096bb9ah		; a[185] @ 11840
	.word	0ad4cd4c5h,04083e55dh		; a[186] @ 11904
	.word	0eabca1dch,040ba5ef4h		; a[187] @ 11968
	.word	03909360ah,040bec4b2h		; a[188] @ 12032
	.word	089e419f0h,04090f803h		; a[189] @ 12096
	.word	03a01838eh,0409909c2h		; a[190] @ 12160
	.word	099cf497fh,040b953c3h		; a[191] @ 12224
	.word	03def4ed8h,0408f2cc7h		; a[192] @ 12288
	.word	09d08b9e3h,0405c5ba1h		; a[193] @ 12352
	.word	04be5b1a0h,040a18deah		; a[194] @ 12416
	.word	0060857bdh,040bfe193h		; a[195] @ 12480
	.word	0a9790aaeh,040a2c1b1h		; a[196] @ 12544
	.word	0c2480e8dh,040c2889eh		; a[197] @ 12608
	.word	084612331h,040a8610dh		; a[198] @ 12672
	.word	0c892ab69h,040c28f15h		; a[199] @ 12736
	.word	0f554ab53h,040b0f8c1h		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\068242 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\068244 
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
;*   Local Frame Size  : 8 Args + 204 Auto + 56 Save = 268 byte               *
;******************************************************************************
main:
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

           CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           MVKL    .S1     a,A10
           MVKH    .S1     a,A10

           CALL    .S2     log2              ; |147| 
||         MV      .L1     A10,A11
||         ZERO    .L2     B10
||         MVK     .S1     0xc9,A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |147| 
           ADDKPC  .S2     $C$RL5,B3,3       ; |147| 
$C$RL5:    ; CALL OCCURS {log2} {0}          ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A12,1,A0          ; |146| 
||         SUB     .S1     A12,1,A12         ; |146| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |147| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |146| 

           ADD     .L2     B10,B4,B4         ; |147| 
||         ADD     .S2     8,B10,B10         ; |146| 

   [ A0]   CALL    .S1     log2              ; |147| 
||         STDW    .D2T1   A5:A4,*B4         ; |147| 
|| [!A0]   MVKL    .S2     output,B4

           ; BRANCHCC OCCURS {$C$L3}         ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVKH    .S2     output,B4
||         ZERO    .L2     B10
||         MVK     .S1     0xc9,A11

           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(16)
||         CALL    .S1     log2dp            ; |150| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |150| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |150| 
$C$RL6:    ; CALL OCCURS {log2dp} {0}        ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(16),B4       ; |150| 
           SUB     .L1     A11,1,A0          ; |149| 
           SUB     .L1     A11,1,A11         ; |149| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |150| 
   [ A0]   BNOP    .S1     $C$L4,3           ; |149| 

           ADD     .L2     B10,B4,B4         ; |150| 
||         ADD     .S2     8,B10,B10         ; |149| 

   [ A0]   CALL    .S1     log2dp            ; |150| 
||         STDW    .D2T1   A5:A4,*B4         ; |150| 

           ; BRANCHCC OCCURS {$C$L4}         ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(16),B4
           ZERO    .L2     B10
           MVKL    .S1     a,A10
           MVKH    .S1     a,A10
           MVK     .S1     0xc9,A11
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(20)
||         CALL    .S1     log2dp_c          ; |153| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10++,A5:A4      ; |153| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |153| 
$C$RL7:    ; CALL OCCURS {log2dp_c} {0}      ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(20),B4       ; |153| 
||         SUB     .L1     A11,1,A0          ; |152| 
||         SUB     .S1     A11,1,A11         ; |152| 

   [!A0]   LDW     .D2T1   *+SP(20),A3
   [!A0]   MVKL    .S2     a,B8
   [!A0]   ZERO    .L2     B9                ; |103| 
   [!A0]   MV      .L2     B9,B12            ; |109| 
           LDW     .D2T2   *B4,B4            ; |153| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |152| 
|| [!A0]   ADD     .L1     4,A3,A15

           ADD     .L2     B10,B4,B4         ; |153| 
||         ADD     .S2     8,B10,B10         ; |152| 

   [ A0]   CALL    .S1     log2dp_c          ; |153| 
||         STDW    .D2T1   A5:A4,*B4         ; |153| 

           ; BRANCHCC OCCURS {$C$L5}         ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           MVKH    .S2     a,B8
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
           FMPYDP  .M1X    A5:A4,B7:B6,A9:A8 ; |109| 
           MV      .L2     B12,B6            ; |109| 
           MV      .L2     B13,B7            ; |109| 
           MVKL    .S1     0xfa15267e,A10
           FMPYDP  .M1     A17:A16,A9:A8,A5:A4 ; |109| 
           MVKH    .S1     0x40738083,A11
           MVKH    .S1     0xfa15267e,A10
           MVKL    .S1     0xc0880bfe,A13
           FSUBDP  .L1     A19:A18,A5:A4,A5:A4 ; |109| 
           MVKL    .S1     0x9c0d9077,A12
           MVKH    .S1     0xc0880bfe,A13
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |109| 
           MVKH    .S1     0x9c0d9077,A12
           STW     .D2T2   B28,*+SP(56)      ; |115| 
           MV      .L2     B13,B27           ; |55| 
           FMPYDP  .M1     A17:A16,A5:A4,A9:A8 ; |109| 
           NOP             4
           FSUBDP  .L2X    B7:B6,A9:A8,B7:B6 ; |109| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B7:B6,B7:B6 ; |109| 
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
           NOP             3
           FADDDP  .L1X    B7:B6,A5:A4,A7:A6 ; |115| 
           MVKL    .S1     0x652b82fe,A4
           MVKL    .S1     0x3ff71547,A5
           FADDDP  .L1X    B17:B16,A7:A6,A7:A6 ; |115| 
           MVKH    .S1     0x652b82fe,A4
           MVKH    .S1     0x3ff71547,A5
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |115| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 6

   [ B2]   B       .S1     $C$L6             ; |155| 
||         MVKH    .S2     0x7fefffff,B11

           CMPGTDP .S2     B5:B4,B11:B10,B0  ; |115| 
   [!B2]   ADD     .L1     4,A15,A14

   [ B0]   ZERO    .L1     A5
|| [!B0]   DADD    .S1     0,A7:A6,A5:A4     ; |115| 
|| [ B0]   MV      .D1X    B26,A4            ; |115| 

   [ B0]   MVKH    .S1     0x40900000,A5

   [!B2]   CALL    .S1     log2dp_v          ; |158| 
||         STDW    .D1T1   A5:A4,*A3++       ; |115| 

           ; BRANCHCC OCCURS {$C$L6}         ; |155| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T2   *A14,B4           ; |158| 
           MVKL    .S1     a,A4
           MVKH    .S1     a,A4
           ADDKPC  .S2     $C$RL8,B3,0       ; |158| 
           MVK     .S1     0xc9,A6           ; |158| 
$C$RL8:    ; CALL OCCURS {log2dp_v} {0}      ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0xc9,A4           ; |161| 

$C$RL9:    ; CALL OCCURS {allequal} {0}      ; |161| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |162| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           STW     .D2T1   A12,*+SP(112)     ; |109| 
           STW     .D2T1   A13,*+SP(116)     ; |109| 

           LDW     .D2T1   *+SP(48),A12      ; |109| 
||         ZERO    .L2     B25               ; |109| 

           STW     .D2T2   B25,*+SP(104)     ; |170| 
           STW     .D2T1   A11,*+SP(124)     ; |109| 
           LDW     .D2T1   *+SP(60),A28      ; |55| 
           STW     .D2T1   A15,*+SP(24)      ; |121| 
           STW     .D2T1   A10,*+SP(120)     ; |109| 
           STW     .D2T2   B13,*+SP(92)      ; |109| 
           STW     .D2T2   B11,*+SP(204)     ; |121| 
           STW     .D2T2   B13,*+SP(140)     ; |109| 
           STW     .D2T2   B13,*+SP(132)     ; |109| 

           STW     .D2T2   B13,*+SP(108)     ; |109| 
||         MVKL    .S2     0x3ff71547,B4

           STW     .D2T2   B13,*+SP(100)     ; |109| 
||         MVKH    .S2     0x3ff71547,B4

           STW     .D2T2   B4,*+SP(172)      ; |115| 

           LDW     .D2T1   *+SP(52),A13      ; |109| 
||         ZERO    .L2     B24               ; |115| 

           STW     .D2T2   B24,*+SP(176)     ; |170| 
||         ZERO    .L1     A16               ; |55| 

           STW     .D2T1   A16,*+SP(136)     ; |172| 
||         ZERO    .L2     B26               ; |109| 

           STW     .D2T2   B26,*+SP(88)      ; |172| 
||         MVKL    .S1     0xbfe94415,A25
||         ZERO    .L2     B27               ; |109| 

           STW     .D2T2   B27,*+SP(96)      ; |172| 
||         MVKL    .S1     0x2016afed,A26
||         ZERO    .L1     A18               ; |55| 

           STW     .D2T1   A18,*+SP(128)     ; |173| 
||         MVKL    .S1     0x4030624a,A27
||         ZERO    .L2     B29               ; |99| 

           STW     .D2T2   B29,*+SP(72)      ; |173| 
||         MVKL    .S1     0x12b3b59a,A29
||         ZERO    .L1     A20               ; |104| 

           STW     .D2T1   A20,*+SP(56)      ; |174| 
||         MVKL    .S1     0xc05007ff,A30
||         MVKL    .S2     0x3fe63000,B30
||         ZERO    .L1     A21               ; |99| 

           STW     .D2T1   A21,*+SP(64)      ; |174| 
||         MVKL    .S1     0x5c610ca8,A31
||         MVKL    .S2     0x652b82fe,B31
||         MVK     .L1     0x6,A8

           STW     .D2T1   A8,*+SP(12)       ; |169| 
||         MVKH    .S2     0x3fe63000,B30
||         MVKL    .S1     0xbf2bd010,A3

           STW     .D2T2   B30,*+SP(180)     ; |115| 
||         MVKH    .S2     0x652b82fe,B31
||         MVKL    .S1     0xb356bd29,A24

           STW     .D2T2   B31,*+SP(168)     ; |115| 
||         MVKH    .S1     0xbfe94415,A25

           STW     .D2T1   A25,*+SP(164)     ; |55| 
||         MVKH    .S1     0x2016afed,A26

           STW     .D2T1   A26,*+SP(152)     ; |55| 
||         MVKH    .S1     0x4030624a,A27

           STW     .D2T1   A27,*+SP(156)     ; |55| 
||         MVKH    .S1     0x12b3b59a,A29

           STW     .D2T1   A29,*+SP(144)     ; |55| 
||         MVKH    .S1     0xc05007ff,A30
||         MVKL    .S2     a_sc,B8

           STW     .D2T1   A30,*+SP(148)     ; |55| 
||         MVKH    .S2     a_sc,B8
||         MVKH    .S1     0x5c610ca8,A31
||         ZERO    .L1     A7

           STW     .D2T1   A31,*+SP(184)     ; |115| 
||         MVKH    .S1     0xbf2bd010,A3
||         ZERO    .L1     A5
||         ZERO    .D1     A6                ; |172| 

           STW     .D2T1   A3,*+SP(188)      ; |115| 
||         MV      .L1X    B8,A23
||         MVKH    .S1     0xb356bd29,A24
||         ZERO    .D1     A4                ; |174| 
||         MV      .L2     B12,B16
||         ADD     .S2     1,B11,B17

           STDW    .D1T2   B17:B16,*+A23(16) ; |171| 
||         MV      .L1X    B8,A17            ; |173| 
||         STW     .D2T1   A24,*+SP(160)     ; |55| 
||         MVKH    .S1     0xfff00000,A7
||         ZERO    .L2     B7
||         ZERO    .S2     B28               ; |104| 

           STDW    .D1T1   A7:A6,*+A17(24)   ; |172| 
||         MV      .L1X    B8,A19            ; |174| 
||         STW     .D2T2   B28,*+SP(48)      ; |173| 
||         ADD     .S1     -7,A8,A2
||         SET     .S2     B7,0x14,0x1d,B7
||         ZERO    .L2     B6                ; |173| 

           STDW    .D1T2   B7:B6,*+A19(32)   ; |173| 
||         ZERO    .L2     B25               ; |118| 
||         MV      .L1X    B8,A22            ; |169| 
||         STW     .D2T1   A2,*+SP(200)      ; |170| 
||         MVKH    .S1     0xbff00000,A5
||         ZERO    .S2     B5

           STDW    .D1T1   A5:A4,*+A22(40)   ; |174| 
||         STW     .D2T2   B25,*+SP(192)     ; |170| 
||         ZERO    .L2     B4                ; |170| 
||         MV      .L1X    B8,A9             ; |172| 
||         MVKH    .S2     0x80000000,B5

           ZERO    .L2     B17:B16           ; |169| 
||         ZERO    .L1     A17               ; |100| 
||         STDW    .D1T2   B5:B4,*+A9(8)     ; |170| 
||         STW     .D2T1   A28,*+SP(196)     ; |118| 
||         MV      .S1X    B13,A11           ; |109| 
||         ZERO    .S2     B10

           CALL    .S2     log2              ; |176| 
||         STDW    .D1T2   B17:B16,*A23      ; |169| 
||         STW     .D2T1   A17,*+SP(80)      ; |173| 
||         SUB     .L1X    B8,8,A15
||         ZERO    .S1     A10               ; |55| 
||         ZERO    .L2     B12               ; |100| 

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
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *++A15,A5:A4      ; |176| 
           ADDKPC  .S2     $C$RL11,B3,3      ; |176| 
$C$RL11:   ; CALL OCCURS {log2} {0}          ; |176| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |176| 
           NOP             4

           ADD     .L2     B10,B4,B6         ; |176| 
||         DADD    .S2X    0,A5:A4,B5:B4     ; |176| 

           STDW    .D2T2   B5:B4,*B6         ; |176| 

           CALLP   .S2     log2dp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |177| 

$C$RL12:   ; CALL OCCURS {log2dp} {0}        ; |177| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |177| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |177| 
           STDW    .D2T1   A5:A4,*B4         ; |177| 

           CALLP   .S2     log2dp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |178| 

$C$RL13:   ; CALL OCCURS {log2dp_c} {0}      ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 185
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |178| 
           ZERO    .L1     A31
           LDDW    .D2T2   *+SP(88),B7:B6
           MVK     .S1     0xfffffc02,A30
           LDW     .D2T1   *+SP(12),A29      ; |122| 
           ADD     .L2     B10,B4,B4         ; |178| 
           STDW    .D2T1   A5:A4,*B4         ; |178| 
           LDDW    .D1T1   *A15,A17:A16      ; |85| 
           SET     .S1     A31,0x15,0x1d,A5
           LDDW    .D2T2   *+SP(32),B5:B4
           LDW     .D2T2   *+SP(24),B31      ; |118| 
           SUB     .L1     A29,1,A2          ; |175| 

           CLR     .S1     A17,20,31,A3      ; |92| 
||         MV      .L1     A16,A4            ; |92| 

           OR      .L1     A5,A3,A5          ; |92| 
||         EXTU    .S1     A17,1,21,A0       ; |87| 

   [!A0]   ZERO    .L1     A5:A4             ; |95| 
           STW     .D2T1   A2,*+SP(12)       ; |179| 
           CMPGTDP .S2X    A5:A4,B5:B4,B0    ; |98| 
           NOP             1

   [!B0]   LDDW    .D2T1   *+SP(40),A7:A6    ; |100| 
|| [!B0]   ZERO    .L1     A3
|| [ B0]   ZERO    .S1     A3
|| [!B0]   ZERO    .L2     B4

   [ B0]   SET     .S1     A3,0x15,0x1d,A3

   [!B0]   SET     .S1     A3,0x15,0x1d,A3
|| [ B0]   STW     .D2T1   A3,*+SP(84)       ; |100| 

   [!B0]   STW     .D2T1   A3,*+SP(60)       ; |104| 
   [ B0]   LDDW    .D2T1   *+SP(80),A7:A6    ; |104| 

   [!B0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |103| 
|| [!B0]   LDDW    .D2T1   *+SP(56),A7:A6    ; |100| 

   [!B0]   SET     .S2     B4,0x15,0x1d,B4
   [!B0]   STW     .D2T2   B4,*+SP(52)       ; |104| 
   [!B0]   LDDW    .D2T2   *+SP(48),B5:B4    ; |100| 
   [ B0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |100| 
   [!B0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |104| 
   [ B0]   ZERO    .L2     B13
   [ B0]   SET     .S2     B13,0x15,0x1d,B13
   [ B0]   ZERO    .L1     A3
   [ B0]   FADDDP  .L2X    B13:B12,A7:A6,B9:B8 ; |100| 
   [!B0]   FADDDP  .L2X    B5:B4,A7:A6,B9:B8 ; |104| 
   [ B0]   SET     .S1     A3,0x15,0x1d,A3
   [ B0]   STW     .D2T1   A3,*+SP(68)       ; |99| 
           RCPDP   .S2     B9:B8,B5:B4       ; |109| 
   [ B0]   LDDW    .D2T1   *+SP(64),A7:A6    ; |99| 
           FMPYDP  .M2     B9:B8,B5:B4,B17:B16 ; |109| 
           ADD     .L1     A30,A0,A3         ; |87| 
   [!B0]   SUB     .L1     A3,1,A3           ; |105| 
           NOP             1
           FSUBDP  .L2     B7:B6,B17:B16,B7:B6 ; |109| 
   [ B0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |99| 
           NOP             1
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |109| 
           LDDW    .D2T2   *+SP(96),B5:B4
           NOP             2
           FMPYDP  .M2     B9:B8,B7:B6,B17:B16 ; |109| 
           NOP             3
           FSUBDP  .L2     B5:B4,B17:B16,B5:B4 ; |109| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |109| 
           LDDW    .D2T2   *+SP(104),B7:B6   ; |99| 
           NOP             2
           FMPYDP  .M2     B9:B8,B5:B4,B9:B8 ; |109| 
           NOP             3

           FSUBDP  .L2     B7:B6,B9:B8,B7:B6 ; |109| 
|| [ B0]   ZERO    .S2     B8

   [ B0]   SET     .S2     B8,0x15,0x1d,B8
   [ B0]   STW     .D2T2   B8,*+SP(76)       ; |99| 
   [ B0]   LDDW    .D2T1   *+SP(72),A7:A6
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |109| 
           NOP             3
   [ B0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |99| 
           LDDW    .D2T1   *+SP(120),A7:A6
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A19:A18 ; |109| 
           LDDW    .D2T2   *+SP(176),B5:B4
           NOP             2
           FMPYDP  .M1     A19:A18,A19:A18,A9:A8 ; |109| 
           NOP             3
           FADDDP  .L1     A13:A12,A9:A8,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |55| 
           NOP             3
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |55| 
           NOP             2

           FMPYDP  .M1     A9:A8,A5:A4,A7:A6 ; |55| 
||         LDDW    .D2T1   *+SP(112),A5:A4

           NOP             4
           FADDDP  .L1     A5:A4,A7:A6,A7:A6 ; |55| 
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

           LDDW    .D2T1   *+SP(200),A5:A4   ; |118| 
           NOP             3

           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |115| 
||         LDDW    .D2T2   *+SP(192),B7:B6   ; |115| 

           CMPGTDP .S1     A17:A16,A5:A4,A0  ; |121| 
           NOP             3

           CMPLTDP .S2X    A17:A16,B7:B6,B0  ; |118| 
||         LDW     .D2T2   *B31,B6           ; |179| 

   [ A2]   B       .S1     $C$L8             ; |175| 

   [ B0]   MVKL    .S2     0xffefffff,B5
|| [ B0]   MVK     .L2     0xffffffff,B4     ; |119| 

   [ B0]   MVKH    .S2     0xffefffff,B5
|| [ A0]   MV      .L2     B12,B4            ; |119| 

   [ A0]   ZERO    .L2     B5

   [ A0]   MVKH    .S2     0x40900000,B5
||         ADD     .L2     B10,B6,B6         ; |179| 
||         ADD     .D2     8,B10,B10         ; |175| 

   [ A2]   CALL    .S1     log2              ; |176| 
||         STDW    .D2T2   B5:B4,*B6         ; |179| 

           ; BRANCHCC OCCURS {$C$L8}         ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     log2dp_v          ; |181| 
           LDW     .D1T2   *A14,B4           ; |181| 
           MVKL    .S1     a_sc,A4
           MVKH    .S1     a_sc,A4
           ADDKPC  .S2     $C$RL14,B3,0      ; |181| 
           MVK     .L1     0x6,A6            ; |181| 
$C$RL14:   ; CALL OCCURS {log2dp_v} {0}      ; |181| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .L1     0x6,A4            ; |184| 

$C$RL15:   ; CALL OCCURS {allequal} {0}      ; |184| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x3,A4            ; |185| 

$C$RL16:   ; CALL OCCURS {print_test_results} {0}  ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 35
           STW     .D2T1   A12,*+SP(128)     ; |109| 
           LDW     .D2T1   *+SP(180),A28     ; |115| 
           LDW     .D2T1   *+SP(148),A27     ; |55| 
           LDW     .D2T1   *+SP(144),A26     ; |55| 
           LDW     .D2T1   *+SP(32),A12
           LDW     .D2T1   *+SP(168),A29     ; |115| 
           LDW     .D2T1   *+SP(172),A30     ; |121| 
           LDW     .D2T2   *+SP(204),B13     ; |121| 
           LDW     .D2T2   *+SP(196),B5      ; |194| 
           STW     .D2T1   A11,*+SP(140)     ; |109| 
           STW     .D2T1   A11,*+SP(108)     ; |109| 
           STW     .D2T1   A11,*+SP(100)     ; |109| 
           STW     .D2T1   A11,*+SP(92)      ; |109| 
           STW     .D2T1   A13,*+SP(132)     ; |109| 
           STW     .D2T1   A11,*+SP(180)     ; |109| 
           STW     .D2T1   A11,*+SP(148)     ; |109| 

           LDW     .D2T2   *+SP(24),B11      ; |194| 
||         MV      .L2     B12,B4            ; |109| 

           STW     .D2T2   B4,*+SP(200)      ; |188| 
||         MV      .L1     A10,A23

           STW     .D2T1   A23,*+SP(176)     ; |188| 
||         MVK     .S1     0x777,A24

           STW     .D2T1   A24,*+SP(12)
||         MV      .L2     B12,B9            ; |109| 

           STW     .D2T2   B9,*+SP(88)
||         MV      .L2     B12,B8            ; |109| 

           STW     .D2T2   B8,*+SP(96)
||         MV      .L2     B12,B7            ; |109| 

           STW     .D2T2   B7,*+SP(104)
||         MV      .L1     A10,A4

           STW     .D2T1   A4,*+SP(136)
||         MVKL    .S1     0xcccccccd,A31

           STW     .D2T1   A4,*+SP(144)      ; |188| 
||         MVKL    .S1     0xc000cccc,A3
||         MV      .L1     A10,A25

           STW     .D2T1   A25,*+SP(32)
||         MVKH    .S1     0xcccccccd,A31

           STW     .D2T1   A31,*+SP(208)     ; |194| 
||         MVKH    .S1     0xc000cccc,A3

           STW     .D2T1   A3,*+SP(212)      ; |194| 
           STW     .D2T1   A29,*+SP(192)     ; |115| 
           STW     .D2T1   A26,*+SP(168)     ; |55| 

           STW     .D2T1   A27,*+SP(172)     ; |55| 
||         MVKL    .S2     a_ext,B6

           STW     .D2T1   A28,*+SP(204)     ; |115| 
||         MVKH    .S2     a_ext,B6

           STW     .D2T1   A30,*+SP(196)     ; |115| 

           STDW    .D2T2   B5:B4,*B6         ; |188| 
||         MV      .L1X    B6,A15            ; |188| 

           CALL    .S1     log2              ; |190| 
||         LDDW    .D1T2   *A15,B5:B4        ; |190| 
||         MV      .L1X    B5,A11
||         MVK     .L2     0xffffffff,B12    ; |121| 
||         LDW     .D2T1   *+SP(36),A13      ; |103| 
||         MV      .S2     B12,B10           ; |109| 

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
           ADDKPC  .S2     $C$RL17,B3,3      ; |190| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |190| 
$C$RL17:   ; CALL OCCURS {log2} {0}          ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |190| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |190| 
           STDW    .D2T1   A5:A4,*B4         ; |190| 

           CALLP   .S2     log2dp,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |191| 

$C$RL18:   ; CALL OCCURS {log2dp} {0}        ; |191| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T1   *+B4(4),A3        ; |191| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |191| 
           NOP             3
           ADD     .L1X    B10,A3,A3         ; |191| 
           STDW    .D1T2   B5:B4,*A3         ; |191| 

           CALLP   .S2     log2dp_c,B3
||         LDDW    .D1T1   *A15,A5:A4        ; |192| 

$C$RL19:   ; CALL OCCURS {log2dp_c} {0}      ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 197
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |192| 
           ZERO    .L1     A31
           LDDW    .D2T2   *+SP(88),B9:B8
           LDDW    .D2T1   *+SP(136),A9:A8
           MVK     .S1     0xfffffc02,A30
           ADD     .L2     B10,B4,B4         ; |192| 
           STDW    .D2T1   A5:A4,*B4         ; |192| 
           LDDW    .D1T1   *A15,A19:A18      ; |85| 
           SET     .S1     A31,0x15,0x1d,A5
           LDW     .D2T2   *B11,B31          ; |193| 
           LDW     .D2T1   *+SP(12),A29
           NOP             1

           CLR     .S1     A19,20,31,A3      ; |92| 
||         MV      .L1     A18,A4            ; |92| 

           OR      .L1     A5,A3,A5          ; |92| 
||         EXTU    .S1     A19,1,21,A1       ; |87| 

   [!A1]   ZERO    .L1     A5:A4             ; |95| 
           CMPGTDP .S1     A5:A4,A13:A12,A0  ; |98| 
           NOP             1

   [!A0]   LDDW    .D2T1   *+SP(40),A7:A6    ; |100| 
|| [!A0]   ZERO    .L2     B4
|| [ A0]   ZERO    .S2     B4
|| [!A0]   ZERO    .L1     A3
|| [ A0]   ZERO    .S1     A3

   [ A0]   SET     .S1     A3,0x15,0x1d,A3
|| [ A0]   SET     .S2     B4,0x15,0x1d,B4

   [!A0]   SET     .S1     A3,0x15,0x1d,A3
|| [ A0]   STW     .D2T1   A3,*+SP(84)       ; |100| 
|| [!A0]   SET     .S2     B4,0x15,0x1d,B4

   [!A0]   STW     .D2T1   A3,*+SP(36)       ; |104| 
   [ A0]   LDDW    .D2T1   *+SP(80),A7:A6    ; |104| 

   [!A0]   FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |103| 
|| [!A0]   LDDW    .D2T1   *+SP(32),A7:A6    ; |100| 

   [ A0]   STW     .D2T2   B4,*+SP(76)       ; |100| 
   [!A0]   STW     .D2T2   B4,*+SP(52)       ; |104| 
   [ A0]   LDDW    .D2T2   *+SP(72),B5:B4    ; |104| 

   [ A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |100| 
|| [!A0]   LDDW    .D2T2   *+SP(48),B5:B4    ; |100| 

   [!A0]   FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |104| 
           ADD     .L1     A30,A1,A3         ; |87| 
   [!A0]   SUB     .L1     A3,1,A3           ; |105| 
           CMPLTDP .S1     A19:A18,A11:A10,A2 ; |118| 
   [ A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |100| 
   [!A0]   FADDDP  .L2X    B5:B4,A7:A6,B7:B6 ; |104| 
           CMPGTDP .S2X    A19:A18,B13:B12,B0 ; |121| 
           SUB     .L1     A29,1,A1          ; |189| 
           RCPDP   .S2     B7:B6,B5:B4       ; |109| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |109| 
   [!A1]   MVKL    .S2     output,B11
   [!A1]   MVKH    .S2     output,B11
           NOP             1
           FSUBDP  .L2     B9:B8,B17:B16,B9:B8 ; |109| 
           NOP             2
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |109| 
           LDDW    .D2T2   *+SP(96),B5:B4
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
           LDDW    .D2T2   *+SP(104),B7:B6   ; |99| 
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
           LDDW    .D2T1   *+SP(120),A7:A6
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A21:A20 ; |109| 
           LDDW    .D2T1   *+SP(128),A5:A4
           LDDW    .D2T2   *+SP(200),B5:B4
           NOP             1
           FMPYDP  .M1     A21:A20,A21:A20,A17:A16 ; |109| 
           NOP             3
           FADDDP  .L1     A5:A4,A17:A16,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |55| 
           NOP             3
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |55| 
           LDDW    .D2T1   *+SP(112),A7:A6
           NOP             1
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |55| 
           NOP             3
           FADDDP  .L1     A7:A6,A5:A4,A23:A22 ; |55| 
           NOP             2
           RCPDP   .S1     A23:A22,A5:A4     ; |55| 
           NOP             1
           FMPYDP  .M1     A5:A4,A23:A22,A7:A6 ; |55| 
           NOP             3
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |55| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |55| 
           LDDW    .D2T1   *+SP(144),A5:A4
           NOP             2
           FMPYDP  .M1     A7:A6,A23:A22,A9:A8 ; |55| 
           NOP             3
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |55| 
           NOP             2

           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |55| 
||         LDDW    .D2T1   *+SP(160),A5:A4   ; |55| 

           NOP             4

           FMPYDP  .M1     A5:A4,A17:A16,A9:A8 ; |55| 
||         LDDW    .D2T1   *+SP(152),A5:A4   ; |55| 

           FMPYDP  .M1     A7:A6,A23:A22,A23:A22 ; |55| 
           NOP             3

           FADDDP  .L1     A5:A4,A9:A8,A9:A8 ; |55| 
||         LDDW    .D2T1   *+SP(176),A5:A4

           NOP             4
           FSUBDP  .L1     A5:A4,A23:A22,A5:A4 ; |55| 
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |55| 
           NOP             1

           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |55| 
||         LDDW    .D2T1   *+SP(168),A5:A4   ; |55| 

           NOP             4
           FADDDP  .L1     A5:A4,A9:A8,A5:A4 ; |55| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |55| 
           INTDP   .L1     A3,A7:A6          ; |115| 
           NOP             2
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |115| 
           NOP             3

           FMPYDP  .M1     A21:A20,A5:A4,A9:A8 ; |115| 
||         LDDW    .D2T1   *+SP(184),A5:A4

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |115| 
           NOP             3
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |115| 
           FADDDP  .L1     A9:A8,A21:A20,A9:A8 ; |115| 
           NOP             2
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |115| 
           NOP             3

           FADDDP  .L2X    B5:B4,A5:A4,B7:B6 ; |115| 
||         LDDW    .D2T2   *+SP(192),B5:B4

           LDDW    .D2T1   *+SP(208),A5:A4
           NOP             3
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |115| 
           ADD     .L2     B10,B31,B6        ; |193| 
           ADD     .L2     8,B10,B10         ; |189| 
           NOP             1

   [ A2]   MVKL    .S2     0xffefffff,B5
|| [ A2]   MV      .L2     B12,B4            ; |122| 

   [ A2]   MVKH    .S2     0xffefffff,B5
|| [ B0]   MV      .L2X    A10,B4            ; |122| 

   [ B0]   ZERO    .L2     B5
   [ B0]   MVKH    .S2     0x40900000,B5
           STDW    .D2T2   B5:B4,*B6         ; |193| 
           LDDW    .D1T1   *A15,A7:A6        ; |194| 
           NOP             4

   [ A1]   BNOP    .S1     $C$L9,3           ; |189| 
||         FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |194| 

           STDW    .D1T1   A5:A4,*++A15      ; |194| 

   [ A1]   CALL    .S1     log2              ; |190| 
|| [ A1]   LDDW    .D1T2   *A15,B5:B4        ; |190| 
||         STW     .D2T1   A1,*+SP(12)       ; |194| 

           ; BRANCHCC OCCURS {$C$L9}         ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     log2dp_v          ; |196| 
           LDW     .D2T2   *+B11(16),B4      ; |196| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           ADDKPC  .S2     $C$RL20,B3,0      ; |196| 
           MVK     .S1     0x777,A6          ; |196| 
$C$RL20:   ; CALL OCCURS {log2dp_v} {0}      ; |196| 
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
           ADD     .L2     8,B10,B11
           STW     .D2T2   B4,*+SP(24)
           NOP             1

   [!B0]   MVKL    .S1     all_pass,A3
|| [!B0]   B       .S2     $C$L10            ; |72| 
|| [!B0]   MV      .L1     A10,A4
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |200| 
|| [!B0]   MVKH    .S1     all_pass,A3
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
           CALL    .S1     print_test_results ; |200| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |200| 
||         ADDKPC  .S2     $C$RL25,B3,0      ; |200| 

$C$RL25:   ; CALL OCCURS {print_test_results} {0}  ; |200| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MV      .L2X    A10,B5            ; |114| 
           STW     .D2T2   B5,*+SP(36)       ; |114| 
           LDDW    .D2T2   *+SP(32),B5:B4    ; |114| 
           MVKL    .S1     cycle_counts+24,A3
           MVKH    .S1     cycle_counts+24,A3
           MV      .L2X    A10,B6            ; |114| 
           NOP             1

           STDW    .D1T2   B5:B4,*A3         ; |114| 
||         MVC     .S2     B6,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           CALL    .S1     gimme_random      ; |210| 
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B5:B4,*A3         ; |117| 
||         ZERO    .L2     B5
||         MVKL    .S1     0x40c38880,A5
||         MVK     .S2     0x80,B30
||         MV      .D2X    A10,B10

           MVKH    .S2     0xbff00000,B5
||         MV      .L2X    A10,B4            ; |210| 
||         STW     .D2T2   B30,*+SP(12)      ; |117| 
||         MVKH    .S1     0x40c38880,A5
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
$C$RL26:   ; CALL OCCURS {gimme_random} {0}  ; |210| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 192
           MVKL    .S2     input,B13
           MVKH    .S2     input,B13
           LDW     .D2T2   *B13,B4           ; |210| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |210| 

           STDW    .D2T1   A5:A4,*B4         ; |210| 
||         MVC     .S2     TSCL,B16          ; |122| 

           MVC     .S2     TSCH,B17          ; |122| 

           ZERO    .L1     A3
||         CLR     .S1     A5,20,31,A7       ; |92| 
||         MV      .D1     A4,A6             ; |92| 
||         MV      .L2X    A10,B4            ; |100| 
||         ZERO    .D2     B19
||         MVKL    .S2     output+12,B31

           SET     .S1     A3,0x15,0x1d,A3
||         MV      .L2X    A10,B8            ; |100| 
||         ZERO    .L1     A31
||         SET     .S2     B19,0x1e,0x1e,B19
||         ZERO    .D1     A30

           MVKL    .S1     0x667f3bcd,A8
||         OR      .L1     A3,A7,A7          ; |92| 
||         MV      .D1     A3,A11            ; |98| 
||         MV      .L2X    A10,B18           ; |109| 
||         MVKH    .S2     output+12,B31

           MVKL    .S1     0x3fe6a09e,A9
||         ZERO    .L1     A29
||         ZERO    .D1     A27
||         LDW     .D2T2   *B31,B30          ; |214| 

           EXTU    .S1     A5,1,21,A1        ; |87| 

   [!A1]   ZERO    .L1     A7:A6             ; |95| 
||         MVKH    .S1     0x667f3bcd,A8

           MVKH    .S1     0x3fe6a09e,A9
           CMPGTDP .S1     A7:A6,A9:A8,A0    ; |98| 
           MV      .L1     A10,A8            ; |103| 

   [ A0]   MV      .D1     A3,A9             ; |98| 
|| [!A0]   MV      .L2X    A3,B5             ; |98| 
||         MVKL    .S1     0x40738083,A19
|| [!A0]   FSUBDP  .L1     A7:A6,A11:A10,A7:A6 ; |103| 

   [ A0]   FMPYDP  .M1     A9:A8,A7:A6,A9:A8 ; |100| 
|| [!A0]   MV      .L2X    A3,B9             ; |104| 
||         MVKL    .S1     0xfa15267e,A18

   [ A0]   MV      .L2X    A3,B5             ; |103| 
||         MVKH    .S1     0x40738083,A19

           MVKH    .S1     0xfa15267e,A18

   [!A0]   FMPYDP  .M2X    B5:B4,A7:A6,B7:B6 ; |104| 
||         MVK     .S1     0xfffffc02,A28

           MVKL    .S1     t_start,A13

   [ A0]   FADDDP  .L2X    B5:B4,A9:A8,B5:B4 ; |100| 
||         SET     .S1     A31,0x1e,0x1e,A9
||         MV      .L1     A10,A8            ; |109| 

           MVKH    .S1     t_start,A13

   [!A0]   FADDDP  .L2     B9:B8,B7:B6,B5:B4 ; |104| 
||         STDW    .D1T2   B17:B16,*A13

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
||         ADD     .L1     A28,A1,A3         ; |87| 

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
           NOP             3
           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |109| 
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
||         MVKL    .S1     0xbf2bd010,A19

           MVKL    .S1     0x5c610ca8,A18
           MVKH    .S1     0xbf2bd010,A19

           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |55| 
||         MVKH    .S1     0x5c610ca8,A18
||         MVKL    .S2     0x3ff71547,B7

           MVKL    .S2     0x652b82fe,B6
           MVKH    .S2     0x3ff71547,B7
           MVKH    .S2     0x652b82fe,B6
           NOP             1

           FMPYDP  .M1X    A7:A6,B5:B4,A17:A16 ; |115| 
||         INTDP   .L1     A3,A7:A6          ; |115| 
||         MVKL    .S2     0x3fe63000,B5
||         MV      .L2X    A10,B4            ; |115| 

           MVKH    .S2     0x3fe63000,B5
           NOP             2
           FMPYDP  .M1     A9:A8,A17:A16,A17:A16 ; |115| 
           FMPYDP  .M1     A19:A18,A7:A6,A19:A18 ; |115| 

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |115| 
||         MVKL    .S1     0x7fefffff,A7
||         MVK     .L1     0xffffffff,A6     ; |121| 

           MVKH    .S1     0x7fefffff,A7

           FADDDP  .L1     A17:A16,A9:A8,A9:A8 ; |115| 
||         CMPGTDP .S1     A5:A4,A7:A6,A1    ; |121| 

           NOP             2

           FADDDP  .L1     A9:A8,A19:A18,A17:A16 ; |115| 
||         SET     .S1     A27,0x14,0x14,A9
||         MV      .D1     A10,A8            ; |115| 

           CMPLTDP .S1     A5:A4,A9:A8,A0    ; |118| 
           NOP             2
           FADDDP  .L2X    B5:B4,A17:A16,B5:B4 ; |115| 
           NOP             2

           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |115| 
||         ADD     .L2     B10,B30,B6        ; |214| 

           NOP             3

   [ A0]   MVKL    .S2     0xffefffff,B5
|| [ A0]   MV      .L2X    A6,B4             ; |122| 

   [ A0]   MVKH    .S2     0xffefffff,B5
|| [ A1]   MV      .L2X    A10,B4            ; |122| 

   [ A1]   ZERO    .L2     B5
   [ A1]   MVKH    .S2     0x40900000,B5

           STDW    .D2T2   B5:B4,*B6         ; |214| 
||         MVC     .S2     TSCL,B6           ; |128| 

           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S2     t_offset,B12
||         MVKL    .S1     t_stop,A15
||         ADD     .L2     8,B10,B10         ; |208| 

           MVKH    .S2     t_offset,B12
||         MVKL    .S1     cycle_counts+24,A12

           LDDW    .D2T2   *B12,B19:B18      ; |130| 
||         MVKL    .S2     cycle_counts+24,B4
||         MVKH    .S1     t_stop,A15

           MVKH    .S2     cycle_counts+24,B4
||         MVKH    .S1     cycle_counts+24,A12
||         STDW    .D1T2   B7:B6,*A15        ; |128| 

           LDDW    .D2T2   *B4,B9:B8         ; |130| 
           NOP             2
           ADDU    .L2     B18,B16,B5:B4     ; |130| 

           ADD     .S2     B5,B19,B16        ; |130| 
||         SUBU    .L2     B6,B4,B5:B4       ; |130| 

           ADD     .L2     B16,B17,B16       ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           ADDU    .L2     B8,B4,B17:B16     ; |130| 
||         SUB     .S2     B7,B16,B4         ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B17,B9,B4         ; |130| 

           ADD     .L2     B4,B5,B17         ; |130| 
||         LDW     .D2T2   *+SP(12),B4       ; |128| 

           STDW    .D1T2   B17:B16,*A12      ; |130| 
           NOP             3

           SUB     .L1X    B4,1,A0           ; |208| 
||         SUB     .L2     B4,1,B4           ; |208| 

           STW     .D2T2   B4,*+SP(12)       ; |130| 
|| [ A0]   MVKL    .S1     0x40c38880,A5
|| [ A0]   ZERO    .L2     B5
|| [ A0]   MV      .L1     A10,A4            ; |210| 
|| [ A0]   B       .S2     $C$L11            ; |208| 
|| [!A0]   LDDW    .D1T1   *A12,A5:A4        ; |135| 

   [ A0]   CALL    .S2     gimme_random      ; |210| 
|| [ A0]   MVKH    .S1     0x40c38880,A5
|| [ A0]   MV      .L2X    A10,B4            ; |210| 

   [ A0]   MVKH    .S2     0xbff00000,B5
|| [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 

           NOP             3
           ; BRANCHCC OCCURS {$C$L11}        ; |208| 
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
           LDDW    .D2T2   *+SP(32),B5:B4
           MV      .L2X    A12,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B10
           MV      .L2X    A10,B31           ; |114| 

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A13        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 

           STDW    .D2T2   B5:B4,*B12        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1X    B13,A3
           MV      .L1X    B4,A12            ; |117| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A3,A3            ; |222| 
           NOP             4

           ADD     .L1     A10,A3,A3         ; |222| 
||         CALL    .S1     log2              ; |222| 

           LDDW    .D1T1   *A3,A5:A4         ; |222| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |222| 
$C$RL29:   ; CALL OCCURS {log2} {0}          ; |222| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A12,1,A0          ; |221| 
||         SUB     .S1     A12,1,A12         ; |221| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |222| 
   [ A0]   BNOP    .S1     $C$L12,3          ; |221| 

           ADD     .L1X    A10,B4,A3         ; |222| 
||         ADD     .S1     8,A10,A10         ; |221| 

           STDW    .D1T1   A5:A4,*A3         ; |222| 
|| [ A0]   MV      .L1X    B13,A3

           ; BRANCHCC OCCURS {$C$L12}        ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A13,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B7:B6        ; |130| 

           MV      .L2     B4,B9             ; |128| 
           LDDW    .D2T2   *B10,B5:B4        ; |130| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A3          ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B7:B6       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B7,24,24,B16      ; |130| 
||         ADDU    .L2     B4,B6,B7:B6       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 

           ADD     .L2     B7,B5,B4          ; |130| 
||         ADD     .S2     B4,B16,B5         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MV      .S2X    A15,B4            ; |130| 

           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL30,B3,0      ; |130| 

$C$RL30:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(32),B5:B4    ; |130| 
           ZERO    .L1     A12
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           SET     .S1     A12,0x1a,0x1d,A12

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A13        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 

           STDW    .D2T2   B5:B4,*B12        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1     A10,A15

           MV      .L1X    B4,A10            ; |117| 
||         MVKL    .S1     input,A3
||         LDW     .D2T2   *+SP(16),B13      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 12
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |230| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |230| 
||         CALL    .S1     log2dp            ; |230| 

           LDDW    .D1T1   *A3,A5:A4         ; |230| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |230| 
$C$RL32:   ; CALL OCCURS {log2dp} {0}        ; |230| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |230| 
||         SUB     .L1     A10,1,A0          ; |229| 
||         SUB     .S1     A10,1,A10         ; |229| 

   [ A0]   BNOP    .S1     $C$L13,3          ; |229| 

           ADD     .L1X    A15,B4,A3         ; |230| 
||         ADD     .S1     8,A15,A15         ; |229| 

           STDW    .D1T1   A5:A4,*A3         ; |230| 
|| [ A0]   MVKL    .S1     input,A3

           ; BRANCHCC OCCURS {$C$L13}        ; |229| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MV      .L2     B12,B4            ; |128| 
||         LDDW    .D1T1   *A13,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B9:B8         ; |130| 
           MV      .L2     B5,B7             ; |128| 
           NOP             3
           ADDU    .L1X    B8,A4,A7:A6       ; |130| 

           ADD     .L1X    A7,B9,A4          ; |130| 
||         LDDW    .D2T2   *+B10(8),B9:B8    ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B6,A6,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B7,A3,B31         ; |130| 
           CALL    .S1     __c6xabi_fltllif  ; |130| 

           ADDU    .L2     B8,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B8        ; |130| 

           ADD     .L2     B5,B9,B5          ; |130| 

           ADD     .L2     B5,B8,B5          ; |130| 
||         MVKL    .S2     t_stop,B8

           MVKH    .S2     t_stop,B8

           STDW    .D2T2   B7:B6,*B8         ; |128| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL33,B3,0      ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A12,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDDW    .D2T2   *+SP(32),B5:B4
           ADDAD   .D2     B10,1,B12
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A13        ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 

           SUBU    .L2     B5,B6,B9:B8       ; |117| 
||         MVKL    .S2     t_offset,B30

           EXT     .S2     B9,24,24,B5       ; |117| 
||         SUB     .L2     B4,B7,B4          ; |117| 

           ADD     .L2     B4,B5,B9          ; |117| 
||         MVK     .S2     0x80,B4

           MVKH    .S2     t_offset,B30
||         LDW     .D2T2   *+SP(20),B13      ; |117| 

           STDW    .D2T2   B9:B8,*B30        ; |117| 
||         MV      .L1     A10,A15
||         MV      .D1X    B4,A10            ; |117| 
||         MVKL    .S1     input,A3

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 12
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |238| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |238| 
||         CALL    .S1     log2dp_c          ; |238| 

           LDDW    .D1T1   *A3,A5:A4         ; |238| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |238| 
$C$RL35:   ; CALL OCCURS {log2dp_c} {0}      ; |238| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B13,B4           ; |238| 
||         SUB     .L1     A10,1,A0          ; |237| 
||         SUB     .S1     A10,1,A10         ; |237| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |237| 

           ADD     .L1X    A15,B4,A3         ; |238| 
||         ADD     .S1     8,A15,A15         ; |237| 

           STDW    .D1T1   A5:A4,*A3         ; |238| 
|| [ A0]   MVKL    .S1     input,A3

           ; BRANCHCC OCCURS {$C$L14}        ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     t_offset,B4
||         LDDW    .D1T1   *A13,A5:A4        ; |130| 

           MVKH    .S2     t_offset,B4
           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           MV      .L2     B5,B9             ; |128| 
           NOP             2
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2X    B6,A5,B6          ; |130| 
||         CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2     B16,B4,B5:B4      ; |130| 

           SUB     .L2     B9,B6,B6          ; |130| 
||         ADD     .S2     B5,B17,B5         ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         MVKL    .S2     t_stop,B6

           MVKH    .S2     t_stop,B6

           STDW    .D2T2   B9:B8,*B6         ; |128| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL36,B3,0      ; |130| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 107
           MPYSP   .M1     A12,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(32),B5:B4
           ADDAD   .D2     B12,1,B13
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A13        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S2     input,B9
           MVKL    .S2     t_offset,B10

           MVKL    .S1     output,A15
||         SUBU    .L2     B6,B4,B7:B6       ; |117| 
||         MVKH    .S2     input,B9

           MVKH    .S1     output,A15
||         SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         LDW     .D1T2   *+A15(16),B4      ; |245| 
||         LDW     .D2T1   *B9,A4            ; |245| 
||         MVKH    .S2     t_offset,B10

           CALLP   .S2     log2dp_v,B3
||         STDW    .D2T2   B7:B6,*B10        ; |117| 
||         MVK     .S1     0x80,A6           ; |245| 

$C$RL38:   ; CALL OCCURS {log2dp_v} {0}      ; |245| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A13,A7:A6        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           MVK     .S1     16,A13
           ADD     .L1X    B13,A13,A13
           LDDW    .D1T1   *A13,A17:A16      ; |130| 
           MV      .L2     B4,B9             ; |128| 
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
           MV      .L1     A4,A3             ; |130| 

           SUBU    .L1X    B8,A3,A9:A8       ; |130| 
||         MVKL    .S1     t_stop,A3

           MVKH    .S1     t_stop,A3
||         ADD     .L1X    A5,B7,A4          ; |130| 

           MV      .L1     A8,A31            ; |130| 
||         ADD     .D1     A4,A7,A4          ; |130| 
||         EXT     .S1     A9,24,24,A6       ; |130| 

           MV      .L2X    A3,B4             ; |128| 
||         SUB     .S1X    B9,A4,A3          ; |130| 
||         ADDU    .L1     A16,A31,A5:A4     ; |130| 

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A3,A6,A5          ; |130| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           MPYSP   .M1     A12,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6

           STDW    .D1T1   A5:A4,*A13        ; |130| 
||         MVKH    .S2     0x3e45798e,B7

           LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL41:   ; CALL OCCURS {isequal} {0}       ; |66| 

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xe2308c3a,B6

           MVKH    .S1     fcn_pass,A3
||         MVKL    .S2     0x3e45798e,B7

           MVKH    .S2     0xe2308c3a,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MV      .L2X    A3,B10            ; |66| 
||         MVKH    .S2     0x3e45798e,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A15(8),B4       ; |67| 
||         STW     .D2T1   A5,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL42:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3e45798e,B7
           MVKL    .S2     0xe2308c3a,B6
           MVKH    .S2     0x3e45798e,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0xe2308c3a,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
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
||         LDW     .D1T1   *A15,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |69| 
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
   [ A0]   CALL    .S1     print_test_results ; |251| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L16}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |251| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A10,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |251| 
||         ADDKPC  .S2     $C$RL45,B3,0      ; |251| 

$C$RL45:   ; CALL OCCURS {print_test_results} {0}  ; |251| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL46:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL47:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |259| 

$C$RL48:   ; CALL OCCURS {print_profile_results} {0}  ; |259| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |262| 

$C$RL49:   ; CALL OCCURS {print_memory_results} {0}  ; |262| 
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
$C$SL1:	.string	"log2DP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	log2
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	log2dp
	.global	log2dp_c
	.global	log2dp_v
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
