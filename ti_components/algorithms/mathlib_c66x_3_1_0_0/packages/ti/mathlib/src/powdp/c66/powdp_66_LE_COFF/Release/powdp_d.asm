;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:50:45 2013                                *
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
	.word	06d6dc1a4h,0c01911e1h		; _a[0] @ 0
	.word	099a2d3d5h,0c021e882h		; _a[1] @ 64
	.word	02bf2cd12h,04022078ch		; _a[2] @ 128
	.word	040cc78eah,04020a865h		; _a[3] @ 192
	.word	0c1b46ad6h,03ffbef2eh		; _a[4] @ 256
	.word	0734571fah,0401d02aeh		; _a[5] @ 320
	.word	061035017h,0bfe11202h		; _a[6] @ 384
	.word	095f9d1e9h,0bff34e73h		; _a[7] @ 448
	.word	0b67eacaeh,0c00aea1fh		; _a[8] @ 512
	.word	08854cdb8h,0bfd3e247h		; _a[9] @ 576
	.word	02c1be7bdh,0c02165f7h		; _a[10] @ 640
	.word	03de7c21ch,040228784h		; _a[11] @ 704
	.word	0419babc3h,040096332h		; _a[12] @ 768
	.word	0e9bd9e5ch,0401c284ch		; _a[13] @ 832
	.word	01f36262dh,0c021aed7h		; _a[14] @ 896
	.word	0ce8a3c2fh,0c023548dh		; _a[15] @ 960
	.word	021484f24h,0c0232b7fh		; _a[16] @ 1024
	.word	0bebabb52h,0c020646ah		; _a[17] @ 1088
	.word	014b3156ch,0c022fa7fh		; _a[18] @ 1152
	.word	0094f341bh,0c008f2e3h		; _a[19] @ 1216
	.word	0698fe692h,0c01fa26dh		; _a[20] @ 1280
	.word	07853ceb4h,03ff3c62bh		; _a[21] @ 1344
	.word	0ca3a4b55h,0401424c1h		; _a[22] @ 1408
	.word	04deea05ch,04020491dh		; _a[23] @ 1472
	.word	0db36f2dbh,04016ff81h		; _a[24] @ 1536
	.word	0f4e519cbh,0401a8e50h		; _a[25] @ 1600
	.word	02cd8a61fh,0c014e6f2h		; _a[26] @ 1664
	.word	0df670344h,0401fd3cbh		; _a[27] @ 1728
	.word	0cb1465e9h,0c0184d2dh		; _a[28] @ 1792
	.word	0450acc0ch,0400f4fbah		; _a[29] @ 1856
	.word	04bdd4e24h,0401125d0h		; _a[30] @ 1920
	.word	0c7e9383dh,04010d670h		; _a[31] @ 1984
	.word	0c39d7922h,040099d6bh		; _a[32] @ 2048
	.word	0a6fc58ach,0c01a12b0h		; _a[33] @ 2112
	.word	04894c448h,0400217a2h		; _a[34] @ 2176
	.word	072e6a769h,040229d83h		; _a[35] @ 2240
	.word	0945df076h,04011cceah		; _a[36] @ 2304
	.word	033f19f14h,0bfd10ee4h		; _a[37] @ 2368
	.word	0ded4364eh,03ffe7e96h		; _a[38] @ 2432
	.word	0188cbec0h,03fc68b2ch		; _a[39] @ 2496
	.word	0ae5af1beh,0c01b7323h		; _a[40] @ 2560
	.word	088c967bdh,0c02086b0h		; _a[41] @ 2624
	.word	04f3fd934h,03fe94603h		; _a[42] @ 2688
	.word	037931444h,0c0006cc0h		; _a[43] @ 2752
	.word	06af2bd21h,040222fcah		; _a[44] @ 2816
	.word	04f8726d0h,04006213ah		; _a[45] @ 2880
	.word	06f5019f4h,03ff14d46h		; _a[46] @ 2944
	.word	0034d925ah,040203a50h		; _a[47] @ 3008
	.word	09051f23bh,0c00d2ae9h		; _a[48] @ 3072
	.word	0960a98e0h,0c0229d8fh		; _a[49] @ 3136
	.word	0b6fad370h,0402186bbh		; _a[50] @ 3200
	.word	02de0e3dbh,03fe119ebh		; _a[51] @ 3264
	.word	0ce7b22b6h,0400c6c27h		; _a[52] @ 3328
	.word	027dcbddch,0c003e147h		; _a[53] @ 3392
	.word	099cd9c00h,0c01475a3h		; _a[54] @ 3456
	.word	0e6d8e78dh,040232b6bh		; _a[55] @ 3520
	.word	07e6a692ah,0400b9ca1h		; _a[56] @ 3584
	.word	046dfb862h,04023816fh		; _a[57] @ 3648
	.word	0c34b43cbh,0c0176095h		; _a[58] @ 3712
	.word	01759b8d9h,0c0189b12h		; _a[59] @ 3776
	.word	071f5e6a2h,0c01a5c7eh		; _a[60] @ 3840
	.word	01ff3bb4eh,0bffca92dh		; _a[61] @ 3904
	.word	0427c7c52h,040191676h		; _a[62] @ 3968
	.word	02d051bc9h,0c00b56c9h		; _a[63] @ 4032
	.word	013795988h,0c014078dh		; _a[64] @ 4096
	.word	028b02272h,0bffdf6dbh		; _a[65] @ 4160
	.word	054195cc8h,0c013c41bh		; _a[66] @ 4224
	.word	03377fc91h,04013c259h		; _a[67] @ 4288
	.word	03d06f18ch,0c0177c40h		; _a[68] @ 4352
	.word	085e30370h,040228b19h		; _a[69] @ 4416
	.word	0584464b4h,040211843h		; _a[70] @ 4480
	.word	0d9e4e344h,0c0223140h		; _a[71] @ 4544
	.word	0e69fdcaah,03ff57f3fh		; _a[72] @ 4608
	.word	0e107ed34h,0c0127d76h		; _a[73] @ 4672
	.word	01fb902ebh,0bfde7a4bh		; _a[74] @ 4736
	.word	0ae388d0fh,0c022d390h		; _a[75] @ 4800
	.word	089a0fe12h,0c0211b0bh		; _a[76] @ 4864
	.word	0e12472a6h,040136b8ch		; _a[77] @ 4928
	.word	0856960edh,04012fa8eh		; _a[78] @ 4992
	.word	0c06abebbh,040118a7bh		; _a[79] @ 5056
	.word	0395c4220h,0400b077bh		; _a[80] @ 5120
	.word	00148d55ch,0c022e358h		; _a[81] @ 5184
	.word	058636e64h,04016426ah		; _a[82] @ 5248
	.word	0f0c2755bh,0c00467b6h		; _a[83] @ 5312
	.word	062e82ca5h,03fea9178h		; _a[84] @ 5376
	.word	078282fcah,04022ebafh		; _a[85] @ 5440
	.word	03012ed43h,0401f1e15h		; _a[86] @ 5504
	.word	04fe01224h,0bff050e8h		; _a[87] @ 5568
	.word	0d601ffb5h,0c020c1aah		; _a[88] @ 5632
	.word	0df5c1b8ah,04009ca2ch		; _a[89] @ 5696
	.word	066f5019fh,03ff77cd4h		; _a[90] @ 5760
	.word	00dae3e6ch,040045315h		; _a[91] @ 5824
	.word	0df23e766h,0401fbf5bh		; _a[92] @ 5888
	.word	0a0c43046h,0c0043602h		; _a[93] @ 5952
	.word	0a6ca03c5h,03fed615ch		; _a[94] @ 6016
	.word	00ea9e6efh,0401929b9h		; _a[95] @ 6080
	.word	022ee4192h,0401a394ch		; _a[96] @ 6144
	.word	064345cffh,04004ba3ch		; _a[97] @ 6208
	.word	065010b99h,040145cf8h		; _a[98] @ 6272
	.word	0ccf86bb7h,0c01d4b48h		; _a[99] @ 6336
$C$IR_1:	.set	800

	.sect	".cinit"
	.align	8
	.field  	$C$IR_2,32
	.field  	_b+0,32
	.word	000000000h,040390000h		; _b[0] @ 0
	.word	000000000h,040380000h		; _b[1] @ 64
	.word	000000000h,040390000h		; _b[2] @ 128
	.word	000000000h,0c0390000h		; _b[3] @ 192
	.word	000000000h,000000000h		; _b[4] @ 256
	.word	000000000h,040390000h		; _b[5] @ 320
	.word	000000000h,040390000h		; _b[6] @ 384
	.word	000000000h,040390000h		; _b[7] @ 448
	.word	000000000h,040390000h		; _b[8] @ 512
	.word	000000000h,040390000h		; _b[9] @ 576
	.word	000000000h,040390000h		; _b[10] @ 640
	.word	000000000h,040380000h		; _b[11] @ 704
	.word	000000000h,040390000h		; _b[12] @ 768
	.word	000000000h,0c0390000h		; _b[13] @ 832
	.word	000000000h,000000000h		; _b[14] @ 896
	.word	000000000h,040390000h		; _b[15] @ 960
	.word	000000000h,040390000h		; _b[16] @ 1024
	.word	000000000h,040390000h		; _b[17] @ 1088
	.word	000000000h,040390000h		; _b[18] @ 1152
	.word	000000000h,040390000h		; _b[19] @ 1216
	.word	000000000h,040390000h		; _b[20] @ 1280
	.word	000000000h,040380000h		; _b[21] @ 1344
	.word	000000000h,040390000h		; _b[22] @ 1408
	.word	000000000h,0c0390000h		; _b[23] @ 1472
	.word	000000000h,000000000h		; _b[24] @ 1536
	.word	000000000h,040390000h		; _b[25] @ 1600
	.word	000000000h,040390000h		; _b[26] @ 1664
	.word	000000000h,040390000h		; _b[27] @ 1728
	.word	000000000h,040390000h		; _b[28] @ 1792
	.word	000000000h,040390000h		; _b[29] @ 1856
	.word	000000000h,040390000h		; _b[30] @ 1920
	.word	000000000h,040380000h		; _b[31] @ 1984
	.word	000000000h,040390000h		; _b[32] @ 2048
	.word	000000000h,0c0390000h		; _b[33] @ 2112
	.word	000000000h,000000000h		; _b[34] @ 2176
	.word	000000000h,040390000h		; _b[35] @ 2240
	.word	000000000h,040390000h		; _b[36] @ 2304
	.word	000000000h,040390000h		; _b[37] @ 2368
	.word	000000000h,040390000h		; _b[38] @ 2432
	.word	000000000h,040390000h		; _b[39] @ 2496
	.word	000000000h,040390000h		; _b[40] @ 2560
	.word	000000000h,040380000h		; _b[41] @ 2624
	.word	000000000h,040390000h		; _b[42] @ 2688
	.word	000000000h,0c0390000h		; _b[43] @ 2752
	.word	000000000h,000000000h		; _b[44] @ 2816
	.word	000000000h,040390000h		; _b[45] @ 2880
	.word	000000000h,040390000h		; _b[46] @ 2944
	.word	000000000h,040390000h		; _b[47] @ 3008
	.word	000000000h,040390000h		; _b[48] @ 3072
	.word	000000000h,040390000h		; _b[49] @ 3136
	.word	000000000h,040390000h		; _b[50] @ 3200
	.word	000000000h,040380000h		; _b[51] @ 3264
	.word	000000000h,040390000h		; _b[52] @ 3328
	.word	000000000h,0c0390000h		; _b[53] @ 3392
	.word	000000000h,000000000h		; _b[54] @ 3456
	.word	000000000h,040390000h		; _b[55] @ 3520
	.word	000000000h,040390000h		; _b[56] @ 3584
	.word	000000000h,040390000h		; _b[57] @ 3648
	.word	000000000h,040390000h		; _b[58] @ 3712
	.word	000000000h,040390000h		; _b[59] @ 3776
	.word	000000000h,040390000h		; _b[60] @ 3840
	.word	000000000h,040380000h		; _b[61] @ 3904
	.word	000000000h,040390000h		; _b[62] @ 3968
	.word	000000000h,0c0390000h		; _b[63] @ 4032
	.word	000000000h,000000000h		; _b[64] @ 4096
	.word	000000000h,040390000h		; _b[65] @ 4160
	.word	000000000h,040390000h		; _b[66] @ 4224
	.word	000000000h,040390000h		; _b[67] @ 4288
	.word	000000000h,040390000h		; _b[68] @ 4352
	.word	000000000h,040390000h		; _b[69] @ 4416
	.word	000000000h,040390000h		; _b[70] @ 4480
	.word	000000000h,040380000h		; _b[71] @ 4544
	.word	000000000h,040390000h		; _b[72] @ 4608
	.word	000000000h,0c0390000h		; _b[73] @ 4672
	.word	000000000h,000000000h		; _b[74] @ 4736
	.word	000000000h,040390000h		; _b[75] @ 4800
	.word	000000000h,040390000h		; _b[76] @ 4864
	.word	000000000h,040390000h		; _b[77] @ 4928
	.word	000000000h,040390000h		; _b[78] @ 4992
	.word	000000000h,040390000h		; _b[79] @ 5056
	.word	000000000h,040390000h		; _b[80] @ 5120
	.word	000000000h,040380000h		; _b[81] @ 5184
	.word	000000000h,040390000h		; _b[82] @ 5248
	.word	000000000h,0c0390000h		; _b[83] @ 5312
	.word	000000000h,000000000h		; _b[84] @ 5376
	.word	000000000h,040390000h		; _b[85] @ 5440
	.word	000000000h,040390000h		; _b[86] @ 5504
	.word	000000000h,040390000h		; _b[87] @ 5568
	.word	000000000h,040390000h		; _b[88] @ 5632
	.word	000000000h,040390000h		; _b[89] @ 5696
	.word	000000000h,040390000h		; _b[90] @ 5760
	.word	000000000h,040380000h		; _b[91] @ 5824
	.word	000000000h,040390000h		; _b[92] @ 5888
	.word	000000000h,0c0390000h		; _b[93] @ 5952
	.word	000000000h,000000000h		; _b[94] @ 6016
	.word	000000000h,040390000h		; _b[95] @ 6080
	.word	000000000h,040390000h		; _b[96] @ 6144
	.word	000000000h,040390000h		; _b[97] @ 6208
	.word	000000000h,040390000h		; _b[98] @ 6272
	.word	000000000h,040390000h		; _b[99] @ 6336
$C$IR_2:	.set	800

	.global	_a
_a:	.usect	".far",800,8
	.global	_b
_b:	.usect	".far",800,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\119842 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\119844 
	.sect	".text:optci"
	.clink

;******************************************************************************
;* FUNCTION NAME: logdpMod_powdpi                                             *
;*                                                                            *
;*   Regs Modified     : A0,A3,A4,A5,A6,A7,A8,A9,B0,B4,B5,B6,B7,B8,B9,A16,A17,*
;*                           A18,A19,A20,A21,A22,A23,A24,A25,B16,B17,B18,B19, *
;*                           B20,B21                                          *
;*   Regs Used         : A0,A3,A4,A5,A6,A7,A8,A9,B0,B3,B4,B5,B6,B7,B8,B9,A16, *
;*                           A17,A18,A19,A20,A21,A22,A23,A24,A25,B16,B17,B18, *
;*                           B19,B20,B21                                      *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
_logdpMod_powdpi:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 140
           CLR     .S1     A5,20,31,A3       ; |90| 

           ZERO    .L2     B19
||         EXTU    .S1     A5,1,21,A0        ; |85| 

           SET     .S2     B19,0x15,0x1d,B19
||         SET     .S1     A3,21,29,A7       ; |90| 
||         MV      .L1     A4,A6             ; |90| 
||         ZERO    .L2     B18               ; |101| 

   [!A0]   ZERO    .L1     A7:A6             ; |93| 
           FSUBDP  .L1X    A7:A6,B19:B18,A17:A16 ; |101| 
           MV      .L2     B19,B7            ; |102| 
           ZERO    .L2     B6                ; |101| 
           MVKL    .S2     0x667f3bcd,B4

           FMPYDP  .M2X    B7:B6,A17:A16,B9:B8 ; |102| 
||         MVKL    .S2     0x3fe6a09e,B5

           FMPYDP  .M2X    B19:B18,A7:A6,B7:B6 ; |98| 
||         MVKH    .S2     0x667f3bcd,B4

           MVKH    .S2     0x3fe6a09e,B5

           CMPGTDP .S2X    A7:A6,B5:B4,B0    ; |96| 
||         MV      .L1X    B19,A9            ; |102| 
||         MV      .L2     B19,B17           ; |102| 
||         ZERO    .D2     B16               ; |101| 
||         ZERO    .S1     A8                ; |101| 

           FADDDP  .L2     B17:B16,B9:B8,B9:B8 ; |102| 
   [ B0]   FADDDP  .L2X    A9:A8,B7:B6,B9:B8 ; |98| 
           ZERO    .S2     B21
           SET     .S2     B21,0x1e,0x1e,B21
           RCPDP   .S2     B9:B8,B5:B4       ; |107| 
           ZERO    .L2     B20               ; |101| 
           FMPYDP  .M2     B9:B8,B5:B4,B7:B6 ; |107| 
           FSUBDP  .L1     A7:A6,A9:A8,A7:A6 ; |97| 
           MVKL    .S1     0xc041d580,A9
           MVKL    .S1     0x4b67ce0f,A8
           FSUBDP  .L2     B21:B20,B7:B6,B7:B6 ; |107| 
           MVKH    .S1     0xc041d580,A9
           MVKH    .S1     0x4b67ce0f,A8
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |107| 
           MVKL    .S1     0x12b3b59a,A24
           MVKL    .S1     0xc05007ff,A25
           MVKH    .S1     0x12b3b59a,A24
           FMPYDP  .M2     B9:B8,B5:B4,B7:B6 ; |107| 
           MVKH    .S1     0xc05007ff,A25
           NOP             2
           FSUBDP  .L2     B21:B20,B7:B6,B7:B6 ; |107| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |107| 
           NOP             3
           FMPYDP  .M2     B9:B8,B7:B6,B5:B4 ; |107| 
           NOP             3
           FSUBDP  .L2     B21:B20,B5:B4,B9:B8 ; |107| 
           MV      .L2     B19,B5            ; |102| 
           MV      .S2     B20,B4            ; |107| 
           FMPYDP  .M2     B7:B6,B9:B8,B7:B6 ; |107| 
   [ B0]   FSUBDP  .L1X    A7:A6,B5:B4,A17:A16 ; |97| 
           MVKL    .S2     0x40738083,B5
           MVKL    .S2     0xfa15267e,B4
           MVKH    .S2     0x40738083,B5
           FMPYDP  .M1X    A17:A16,B7:B6,A19:A18 ; |107| 
           MVKH    .S2     0xfa15267e,B4
           MVKL    .S1     0xc0880bfe,A17
           MVKL    .S1     0x9c0d9077,A16
           FMPYDP  .M1     A19:A18,A19:A18,A7:A6 ; |107| 
           MVKH    .S1     0xc0880bfe,A17
           MVKH    .S1     0x9c0d9077,A16
           NOP             1
           FADDDP  .L1     A9:A8,A7:A6,A9:A8 ; |55| 
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |55| 
           NOP             3
           FADDDP  .L1X    B5:B4,A9:A8,A9:A8 ; |55| 
           MVKL    .S2     0xb356bd29,B4
           MVKL    .S2     0xbfe94415,B5
           FMPYDP  .M1     A7:A6,A9:A8,A9:A8 ; |55| 
           MVKH    .S2     0xb356bd29,B4
           MVKH    .S2     0xbfe94415,B5
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |55| 
           FADDDP  .L1     A17:A16,A9:A8,A23:A22 ; |55| 
           MV      .L1X    B21,A17           ; |107| 
           MV      .S1X    B18,A16           ; |55| 
           RCPDP   .S1     A23:A22,A9:A8     ; |55| 
           NOP             1
           FMPYDP  .M1     A9:A8,A23:A22,A21:A20 ; |55| 
           NOP             3
           FSUBDP  .L1     A17:A16,A21:A20,A17:A16 ; |55| 
           NOP             2
           FMPYDP  .M1     A9:A8,A17:A16,A9:A8 ; |55| 
           NOP             3
           FMPYDP  .M1     A9:A8,A23:A22,A17:A16 ; |55| 
           NOP             4
           FSUBDP  .L2X    B21:B20,A17:A16,B7:B6 ; |55| 
           MVKL    .S1     0x2016afed,A16
           MVKL    .S1     0x4030624a,A17
           MVKH    .S1     0x2016afed,A16
           FMPYDP  .M1X    A9:A8,B7:B6,A21:A20 ; |55| 
           MVKH    .S1     0x4030624a,A17
           MVKL    .S2     0x3fe63000,B7
           MVKH    .S2     0x3fe63000,B7
           FMPYDP  .M1     A21:A20,A23:A22,A9:A8 ; |55| 
           FADDDP  .L1X    A17:A16,B5:B4,A23:A22 ; |55| 
           MV      .L1X    B18,A16           ; |55| 
           MV      .S1X    B21,A17           ; |107| 

           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |55| 
||         FMPYDP  .M1     A7:A6,A23:A22,A17:A16 ; |55| 

           MVK     .S2     1022,B4           ; |85| 
           MVKL    .S2     0xbf2bd010,B5
           FMPYDP  .M1     A21:A20,A9:A8,A9:A8 ; |55| 
           FADDDP  .L1     A25:A24,A17:A16,A17:A16 ; |55| 
           SUB     .L1X    A0,B4,A3          ; |85| 
   [!B0]   SUB     .S1     A3,1,A3           ; |103| 
           FMPYDP  .M1     A17:A16,A9:A8,A9:A8 ; |55| 
           INTDP   .L1     A3,A17:A16        ; |113| 
           MVKH    .S2     0xbf2bd010,B5
           MVKL    .S2     0x5c610ca8,B4
           FMPYDP  .M1     A7:A6,A9:A8,A7:A6 ; |111| 
           MVKH    .S2     0x5c610ca8,B4
           MV      .L2     B20,B6            ; |111| 
           NOP             1
           FMPYDP  .M1     A19:A18,A7:A6,A9:A8 ; |111| 
           FMPYDP  .M1X    B5:B4,A17:A16,A7:A6 ; |113| 
           FMPYDP  .M2X    B7:B6,A17:A16,B5:B4 ; |113| 
           NOP             1
           FADDDP  .L1     A9:A8,A19:A18,A9:A8 ; |111| 
           NOP             3
           FADDDP  .L1     A9:A8,A7:A6,A9:A8 ; |113| 
           MVKL    .S1     0x7fefffff,A7

           MVKH    .S1     0x7fefffff,A7
||         MVK     .D1     0xffffffff,A6     ; |115| 

           CMPGTDP .S1     A5:A4,A7:A6,A0    ; |115| 
||         FADDDP  .L1X    B5:B4,A9:A8,A5:A4 ; |113| 

           RETNOP  .S2     B3,1              ; |120| 
   [ A0]   MVKL    .S1     0xfefa39ef,A4
   [ A0]   MVKL    .S1     0x40862e42,A5
   [ A0]   MVKH    .S1     0xfefa39ef,A4
   [ A0]   MVKH    .S1     0x40862e42,A5
           ; BRANCH OCCURS {B3}              ; |120| 
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
;*   Local Frame Size  : 8 Args + 188 Auto + 56 Save = 252 byte               *
;******************************************************************************
_main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           STW     .D2T1   A11,*SP--(8)      ; |111| 
           STW     .D2T1   A10,*SP--(8)      ; |111| 
           STDW    .D2T2   B13:B12,*SP--     ; |111| 
           STDW    .D2T2   B11:B10,*SP--     ; |111| 
           STDW    .D2T1   A15:A14,*SP--     ; |111| 
           STDW    .D2T1   A13:A12,*SP--     ; |111| 
           STW     .D2T2   B3,*SP--(8)       ; |111| 

           MVKL    .S1     $C$SL1+0,A4
||         ADDK    .S2     -200,SP           ; |111| 

           CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |120| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _a,A10

           MVKL    .S2     _b,B10
||         MVKL    .S1     _output,A14

           MVKH    .S1     _a,A10
||         MVK     .S2     0x64,B4

           MVKH    .S2     _b,B10
||         MVKH    .S1     _output,A14

           MV      .L2     B10,B11
||         MV      .L1     A10,A12
||         CALL    .S1     _pow              ; |129| 
||         LDW     .D1T1   *A14,A11

           LDDW    .D1T1   *A12++,A5:A4      ; |129| 
||         MV      .L1X    B4,A13
||         LDDW    .D2T2   *B11++,B5:B4      ; |129| 

           NOP             3
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL1,B3,0       ; |129| 
$C$RL1:    ; CALL OCCURS {_pow} {0}          ; |129| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A13,1,A0          ; |128| 
||         STDW    .D1T1   A5:A4,*A11++      ; |129| 
||         SUB     .S1     A13,1,A13         ; |128| 

   [ A0]   LDDW    .D1T1   *A12++,A5:A4      ; |129| 
|| [!A0]   ADD     .L2X    4,A14,B4
|| [!A0]   MV      .L1     A10,A15
|| [!A0]   MV      .S2     B10,B12
|| [ A0]   B       .S1     $C$L1             ; |128| 

   [ A0]   CALL    .S1     _pow              ; |129| 
   [ A0]   LDDW    .D2T2   *B11++,B5:B4      ; |129| 
   [!A0]   MVK     .S1     0x64,A11
   [!A0]   ZERO    .L2     B11
   [!A0]   STW     .D2T2   B4,*+SP(16)
           ; BRANCHCC OCCURS {$C$L1}         ; |128| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     _powdp            ; |132| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D2T2   *B10++,B5:B4      ; |132| 
||         LDDW    .D1T1   *A10++,A5:A4      ; |132| 

           ADDKPC  .S2     $C$RL2,B3,3       ; |132| 
$C$RL2:    ; CALL OCCURS {_powdp} {0}        ; |132| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(16),B4       ; |132| 
           SUB     .L1     A11,1,A0          ; |131| 
           SUB     .L1     A11,1,A11         ; |131| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |132| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |131| 

           ADD     .L2     B11,B4,B4         ; |132| 
||         ADD     .S2     8,B11,B11         ; |131| 

   [ A0]   CALL    .S1     _powdp            ; |132| 
||         STDW    .D2T1   A5:A4,*B4         ; |132| 

           ; BRANCHCC OCCURS {$C$L2}         ; |131| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(16),B4
           MV      .L2     B12,B11
           MV      .L1     A15,A11
           MVK     .S1     0x64,A10
           ZERO    .L2     B10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(20)
||         CALL    .S1     _powdp_c          ; |135| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D2T2   *B11++,B5:B4      ; |135| 
||         LDDW    .D1T1   *A11++,A5:A4      ; |135| 

           ADDKPC  .S2     $C$RL3,B3,3       ; |135| 
$C$RL3:    ; CALL OCCURS {_powdp_c} {0}      ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(20),B4       ; |135| 
||         SUB     .L1     A10,1,A0          ; |134| 
||         SUB     .S1     A10,1,A10         ; |134| 

   [!A0]   ZERO    .L1     A31
   [!A0]   ZERO    .L1     A3
   [!A0]   LDW     .D2T1   *+SP(20),A21      ; |159| 
   [!A0]   SET     .S1     A3,0x15,0x1d,A3
           LDW     .D2T2   *B4,B4            ; |135| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |134| 

           ADD     .L2     B10,B4,B4         ; |135| 
||         ADD     .S2     8,B10,B10         ; |134| 

   [ A0]   CALL    .S1     _powdp_c          ; |135| 
||         STDW    .D2T1   A5:A4,*B4         ; |135| 
|| [!A0]   MVKL    .S2     0xc086232b,B4

           ; BRANCHCC OCCURS {$C$L3}         ; |134| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 27

           STW     .D2T1   A3,*+SP(100)      ; |154| 
||         SET     .S1     A31,0x0,0x1e,A3
||         MVKL    .S2     0xdd7abcd2,B31
||         ZERO    .L1     A11
||         MV      .L2X    A3,B25            ; |159| 
||         ZERO    .D1     A4                ; |196| 

           MVKL    .S1     0x40862e42,A30
||         MVKL    .S2     0x3f7c70e4,B29
||         ZERO    .L2     B30
||         ZERO    .D2     B5
||         ZERO    .L1     A22               ; |196| 
||         MVK     .D1     0xffffffff,A20    ; |203| 

           MVKL    .S1     0xfefa39cc,A29
||         MVKL    .S2     0x6fb3f6e0,B28
||         STW     .D2T1   A3,*+SP(148)      ; |203| 
||         ADD     .L1     4,A21,A3
||         ZERO    .L2     B6                ; |196| 
||         ZERO    .D1     A13

           MVKL    .S1     0x3fac718e,A28
||         MVKL    .S2     0x3fe63000,B27
||         ZERO    .L2     B7                ; |196| 
||         STW     .D2T1   A3,*+SP(24)
||         ZERO    .L1     A12               ; |196| 
||         SUB     .D1     A15,8,A2

           MVKL    .S1     0x714251b3,A27
||         MVKL    .S2     0x3ff71547,B26
||         STW     .D2T1   A4,*+SP(96)
||         ZERO    .L1     A10               ; |196| 
||         ZERO    .D1     A1                ; |196| 

           MVKL    .S1     0x3f403f99,A26
||         MVKL    .S2     0x652b82fe,B24
||         STW     .D2T2   B6,*+SP(64)

           MVKL    .S1     0x6fde3809,A25
||         MVKH    .S2     0xc086232b,B4
||         STW     .D2T2   B7,*+SP(80)

           MVKL    .S1     0xbf2bd010,A24
||         MVKH    .S2     0xdd7abcd2,B31
||         STW     .D2T2   B4,*+SP(140)      ; |167| 
||         ZERO    .L2     B4                ; |196| 

           MVKL    .S1     0x5c610ca8,A23
||         MVKH    .S2     0x3f7c70e4,B29
||         STW     .D2T2   B31,*+SP(136)     ; |167| 

           MVKH    .S1     0x40862e42,A30
||         MVKH    .S2     0x6fb3f6e0,B28
||         STW     .D2T2   B29,*+SP(92)      ; |153| 

           MVKH    .S1     0xfefa39cc,A29
||         MVKH    .S2     0x3fe63000,B27
||         STW     .D2T1   A30,*+SP(132)     ; |162| 
||         ZERO    .L1     A30               ; |196| 

           MVKH    .S1     0x3fac718e,A28
||         MVKH    .S2     0x3ff71547,B26
||         STW     .D2T1   A29,*+SP(128)     ; |162| 

           MVKH    .S1     0x714251b3,A27
||         MVKH    .S2     0x3fd00000,B30
||         STW     .D2T1   A28,*+SP(108)     ; |154| 

           MVKH    .S1     0x3f403f99,A26
||         SET     .S2     B5,0x14,0x1e,B5
||         STW     .D2T1   A27,*+SP(104)     ; |154| 

           MVKH    .S1     0x6fde3809,A25
||         MVKH    .S2     0x652b82fe,B24
||         STW     .D2T1   A26,*+SP(116)     ; |154| 

           MVKH    .S1     0xbf2bd010,A24
||         MVKL    .S2     0x3ef152a4,B11
||         STW     .D2T2   B28,*+SP(88)      ; |153| 
||         SUB     .L2     B12,8,B28

           MVKH    .S1     0x5c610ca8,A23
||         MVKL    .S2     0x6f58dc1c,B10
||         STW     .D2T1   A25,*+SP(112)     ; |154| 

           SET     .S1     A11,0x1e,0x1e,A11
||         STW     .D2T2   B27,*+SP(68)      ; |153| 
||         MVKH    .S2     0x3ef152a4,B11

           MV      .L1     A11,A31           ; |159| 
||         STW     .D2T1   A24,*+SP(76)      ; |153| 
||         MVKH    .S2     0x6f58dc1c,B10
||         SET     .S1     A13,0x14,0x1d,A13

           STW     .D2T2   B26,*+SP(60)      ; |153| 
||         ZERO    .L2     B26               ; |196| 
||         MVK     .S2     0x64,B1

           STW     .D2T2   B30,*+SP(84)      ; |153| 
           STDW    .D2T2   B5:B4,*+SP(48)
           STW     .D2T1   A23,*+SP(72)      ; |153| 

           STW     .D2T2   B24,*+SP(56)      ; |153| 
||         ZERO    .L2     B24               ; |196| 

           STW     .D2T1   A11,*+SP(124)     ; |159| 
           STW     .D2T1   A22,*+SP(120)
           STW     .D2T1   A20,*+SP(144)
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 8
           LDDW    .D1T1   *++A2,A27:A26     ; |138| 
           LDDW    .D2T2   *++B28,B23:B22    ; |138| 
           CALL    .S1     _logdpMod_powdpi  ; |195| 
           ADDKPC  .S2     $C$RL4,B3,1       ; |195| 
           ABSDP   .S1     A27:A26,A29:A28   ; |195| 
           NOP             1
           DADD    .L1     0,A29:A28,A5:A4   ; |195| 
$C$RL4:    ; CALL OCCURS {_logdpMod_powdpi} {0}  ; |195| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 121

           LDDW    .D2T2   *+SP(56),B7:B6    ; |200| 
||         FMPYDP  .M2X    B23:B22,A5:A4,B5:B4 ; |195| 

           CMPEQDP .S1     A29:A28,A13:A12,A0 ; |196| 
           LDDW    .D2T2   *+SP(64),B9:B8
           LDDW    .D2T1   *+SP(72),A5:A4
   [ A0]   ZERO    .L2     B5:B4             ; |197| 
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |153| 
           LDDW    .D2T2   *+SP(88),B17:B16
           MVK     .S2     0x400,B27
           DPINT   .L2     B23:B22,B29       ; |186| 
           DPINT   .L2     B7:B6,B20         ; |153| 
           SUB     .L2     B1,1,B1           ; |137| 
           LDW     .D2T1   *+SP(24),A25
   [!B1]   MV      .S2X    A14,B13
           INTDP   .L2     B20,B7:B6         ; |153| 
           NOP             4
           FMPYDP  .M2     B9:B8,B7:B6,B9:B8 ; |153| 
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |153| 
           NOP             2
           FSUBDP  .L2     B5:B4,B9:B8,B7:B6 ; |153| 
           NOP             2
           FSUBDP  .L2X    B7:B6,A5:A4,B9:B8 ; |153| 
           LDDW    .D2T1   *+SP(112),A5:A4   ; |153| 
           NOP             1
           FMPYDP  .M2     B9:B8,B9:B8,B7:B6 ; |153| 
           NOP             3
           FMPYDP  .M2     B11:B10,B7:B6,B19:B18 ; |153| 
           FMPYDP  .M1X    A5:A4,B7:B6,A7:A6 ; |154| 
           LDDW    .D2T1   *+SP(104),A5:A4
           NOP             1
           FADDDP  .L2     B17:B16,B19:B18,B17:B16 ; |153| 
           LDDW    .D2T2   *+SP(80),B19:B18
           NOP             1
           FMPYDP  .M2     B7:B6,B17:B16,B17:B16 ; |153| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |154| 
           LDDW    .D2T1   *+SP(96),A7:A6
           NOP             1
           FADDDP  .L2     B19:B18,B17:B16,B17:B16 ; |153| 
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |154| 
           NOP             1
           FMPYDP  .M2     B9:B8,B17:B16,B7:B6 ; |153| 
           ADD     .L2     B27,B20,B9        ; |159| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |154| 
           SHL     .S2     B9,20,B27         ; |159| 
           LDDW    .D2T2   *+SP(136),B9:B8   ; |159| 
           FSUBDP  .L1X    A5:A4,B7:B6,A7:A6 ; |154| 
           EXTU    .S2     B29,31,31,B16     ; |188| 
           NOP             1
           RCPDP   .S1     A7:A6,A5:A4       ; |159| 
           NOP             1
           FMPYDP  .M1     A7:A6,A5:A4,A9:A8 ; |159| 
           NOP             3
           FSUBDP  .L1     A11:A10,A9:A8,A9:A8 ; |159| 
           NOP             2
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |159| 
           LDDW    .D2T1   *+SP(120),A5:A4
           NOP             2
           FMPYDP  .M1     A7:A6,A9:A8,A17:A16 ; |159| 
           NOP             3
           FSUBDP  .L1     A5:A4,A17:A16,A5:A4 ; |159| 
           NOP             2
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |159| 
           NOP             3
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |159| 
           NOP             3
           FSUBDP  .L1     A31:A30,A7:A6,A7:A6 ; |159| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |159| 
           NOP             2
           INTDP   .L1X    B29,A5:A4         ; |188| 
           NOP             1

           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |159| 
||         ZERO    .L1     A7:A6             ; |188| 

           CMPLTDP .S1     A27:A26,A7:A6,A3  ; |188| 
           NOP             1
           CMPEQDP .S1X    B23:B22,A5:A4,A4  ; |188| 
           FADDDP  .L2     B25:B24,B7:B6,B7:B6 ; |159| 

           AND     .L1     A4,A3,A3          ; |188| 
||         LDDW    .D2T1   *+SP(128),A5:A4   ; |159| 

           NOP             1

           AND     .S2X    B16,A3,B0         ; |188| 
||         FMPYDP  .M2     B27:B26,B7:B6,B17:B16 ; |159| 
||         MVK     .L1     0x1,A3            ; |184| 
||         INTDP   .L2     B29,B7:B6         ; |202| 

   [ B0]   ADD     .L1     -2,A3,A3
           CMPLTDP .S2     B5:B4,B9:B8,B0    ; |167| 

           CMPGTDP .S1X    B5:B4,A5:A4,A0    ; |162| 
||         INTDP   .L1     A3,A5:A4          ; |200| 
||         LDW     .D1T1   *A25,A3           ; |138| 

           NOP             1

           ZERO    .L2     B5:B4             ; |202| 
|| [ A0]   MVKL    .S2     0x7fefffff,B17
|| [ A0]   MVK     .D2     0xffffffff,B16    ; |163| 

   [ A0]   MVKH    .S2     0x7fefffff,B17

           CMPEQDP .S2     B23:B22,B7:B6,B6  ; |202| 
|| [ B0]   ZERO    .L2     B17:B16           ; |168| 

           ADD     .L1     A1,A3,A3          ; |138| 

           CMPLTDP .S2X    A27:A26,B5:B4,B8  ; |202| 
||         XOR     .L2     1,B6,B6           ; |202| 
||         FMPYDP  .M1X    B17:B16,A5:A4,A7:A6 ; |200| 
||         ZERO    .L1     A5:A4             ; |206| 

           CMPLTDP .S1X    B23:B22,A5:A4,A8  ; |206| 
           AND     .L2     B6,B8,B0          ; |202| 
   [ B0]   LDDW    .D2T1   *+SP(144),A5:A4   ; |202| 
           ZERO    .L2     B5:B4             ; |206| 
           CMPEQDP .S2X    A27:A26,B5:B4,B4  ; |206| 
           ADD     .L1     8,A1,A1           ; |137| 
           AND     .L2X    A8,B4,B2          ; |206| 

   [ B0]   DADD    .L1     0,A5:A4,A7:A6     ; |203| 
|| [ B2]   LDDW    .D2T1   *+SP(48),A5:A4    ; |203| 

   [ B1]   BNOP    .S1     $C$L4,3           ; |137| 
   [ B2]   DADD    .L1     0,A5:A4,A7:A6     ; |207| 

   [!B1]   CALL    .S1     _powdp_v          ; |140| 
||         STDW    .D1T1   A7:A6,*A3         ; |138| 

           ; BRANCHCC OCCURS {$C$L4}         ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T1   *+B13(16),A6      ; |140| 
           MVK     .S2     0x64,B6           ; |140| 
           MV      .L1     A15,A4            ; |140| 
           MV      .L2     B12,B4            ; |140| 
           ADDKPC  .S2     $C$RL5,B3,0       ; |140| 
$C$RL5:    ; CALL OCCURS {_powdp_v} {0}      ; |140| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B13,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVK     .S1     0x64,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .S1     0x64,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A14,A4           ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .S1     0x64,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL8:    ; CALL OCCURS {_isequal} {0}      ; |68| 

           LDW     .D2T1   *+SP(24),A3       ; |68| 
||         MVKL    .S2     _fcn_pass,B4

           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           ADD     .L1     4,A3,A3
||         LDW     .D1T1   *A14,A4           ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         STW     .D2T1   A3,*+SP(28)
||         MVK     .S1     0x64,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL9:    ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S1     _fcn_pass,A3
||         MVKL    .S2     _fcn_pass,B5

           MVKH    .S1     _fcn_pass,A3
||         MVKH    .S2     _fcn_pass,B5

           ADD     .L1     4,A3,A3
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           ADD     .L2     8,B5,B4
           STW     .D2T2   B4,*+SP(36)       ; |69| 
           STW     .D2T1   A3,*+SP(32)

   [!A0]   B       .S1     $C$L5             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |144| 
   [!A0]   MV      .L1     A12,A3
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     _all_pass,A4
   [!A0]   MVKH    .S1     _all_pass,A4
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
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   MV      .L1     A12,A3
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |144| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x1,A4            ; |144| 
||         ADDKPC  .S2     $C$RL10,B3,0      ; |144| 

$C$RL10:   ; CALL OCCURS {_print_test_results} {0}  ; |144| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           MVKL    .S1     _a_sc,A12
||         ZERO    .L1     A5

           LDDW    .D2T2   *+SP(48),B5:B4
||         MVKH    .S1     0xfff00000,A5
||         MVKL    .S2     _b_sc,B17

           LDW     .D2T1   *+SP(148),A3      ; |155| 
||         MVKH    .S1     _a_sc,A12
||         MVKH    .S2     _b_sc,B17
||         ZERO    .L2     B9
||         MV      .L1     A10,A4            ; |155| 

           STDW    .D2T1   A5:A4,*+B17(24)   ; |154| 
||         MVKH    .S2     0xbff00000,B9
||         ZERO    .L2     B8                ; |156| 

           STDW    .D2T2   B9:B8,*+B17(40)   ; |156| 
||         MV      .L2X    A12,B16           ; |151| 

           STDW    .D2T2   B9:B8,*+B16(40)   ; |156| 
           STDW    .D2T2   B5:B4,*+B17(16)   ; |153| 

           ZERO    .L2     B5:B4             ; |151| 
||         STDW    .D2T2   B5:B4,*+B16(16)   ; |153| 

           STDW    .D2T2   B5:B4,*B17        ; |151| 

           MVK     .L2     0x6,B5            ; |159| 
||         STDW    .D2T2   B5:B4,*B16        ; |151| 
||         MVK     .L1     0x5,A1            ; |158| 

           MVC     .S2     B5,RILC
||         MVK     .L2     5,B4              ; |159| 
||         STDW    .D2T1   A5:A4,*+B16(24)   ; |154| 
||         ADD     .L1     1,A3,A7
||         SUB     .S1     A1,1,A1           ; |158| 
||         MV      .D1     A10,A6            ; |155| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/powdp/powdp_d.c
;*      Loop source line                 : 159
;*      Loop opening brace source line   : 159
;*      Loop closing brace source line   : 163
;*      Known Minimum Trip Count         : 6                    
;*      Known Maximum Trip Count         : 6                    
;*      Known Max Trip Count Factor      : 6
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
;*      Total cycles (est.)         : 6 + min_trip_cnt * 6 = 42        
;*----------------------------------------------------------------------------*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C108:
;*   0              ADD     .L1     A4,A3,A7          ; |161| 
;*   1              CMPLT   .L1     A7,6,A0           ; |161| 
;*   2      [!A0]   MVK     .S1     0xffffffd0,A7     ; |161| 
;*     ||   [ A0]   ZERO    .D1     A7                ; |161| 
;*   3              LDDW    .D2T2   *B8++,B5:B4       ; |160|  ^ 
;*     ||           ADD     .L1     A5,A7,A7          ; |161| 
;*   4              ADD     .L1     A6,A7,A7          ; |161| 
;*   5              LDDW    .D1T2   *A7,B5:B4         ; |161|  ^ 
;*     ||           ADD     .L1     1,A4,A4           ; |159| 
;*   6              NOP             2
;*   8              STDW    .D2T2   B5:B4,*B7++       ; |160|  ^ 
;*     ||           ADD     .L1     8,A5,A5           ; |159| 
;*   9              NOP             1
;*  10              STDW    .D2T2   B5:B4,*B6++       ; |161|  ^ 
;*     ||           SPBR            $C$C108
;*  11              NOP             1
;*  12              ; BRANCHCC OCCURS {$C$C108}       ; |159| 
;*----------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP PROLOG
;          EXCLUSIVE CPU CYCLES: 7

   [ A1]   SPLOOPD 6       ;12               ; SPRELOAD
||         MV      .L2X    A10,B12           ; |153| 
||         ZERO    .L1     A4                ; |159| 
||         MVK     .S1     0x1,A3            ; |158| 
||         STDW    .D2T1   A7:A6,*+B17(8)    ; |152| 
||         MVC     .S2     B4,ILC

;** --------------------------------------------------------------------------*
$C$L7:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 6

           SPMASK          L2,S2,D2
||         MV      .L2X    A13,B13           ; |155| 
||         MVK     .S2     0x8,B9
||         STDW    .D2T1   A7:A6,*+B16(8)    ; |152| 
||         ADD     .L1     A4,A3,A7          ; |161| (P) <0,0> 

           SPMASK          S1,D2
||         STDW    .D2T2   B13:B12,*+B17(32) ; |155| 
||         MV      .S1X    B17,A14           ; |151| 
||         CMPLT   .L1     A7,6,A0           ; |161| (P) <0,1> 

           SPMASK          L1,L2,D2
||         STDW    .D2T2   B13:B12,*+B16(32) ; |155| 
||         MV      .L2X    A12,B8
||         MV      .L1X    B9,A5
|| [ A0]   ZERO    .D1     A7                ; |161| (P) <0,2> 
|| [!A0]   MVK     .S1     0xffffffd0,A7     ; |161| (P) <0,2> 

           SPMASK          S1
||         MV      .S1     A14,A6
||         LDDW    .D2T2   *B8++,B5:B4       ; |160| (P) <0,3>  ^ 
||         ADD     .L1     A5,A7,A7          ; |161| (P) <0,3> 

           SPMASK          D2
||         ADDAD   .D2     B17,6,B6
||         ADD     .L1     A6,A7,A7          ; |161| (P) <0,4> 

           SPMASK          D2
||         ADDAD   .D2     B16,6,B7
||         ADD     .L1     1,A4,A4           ; |159| (P) <0,5> 
||         LDDW    .D1T2   *A7,B5:B4         ; |161| (P) <0,5>  ^ 

           NOP             2

           STDW    .D2T2   B5:B4,*B7++       ; |160| <0,8>  ^ 
||         ADD     .L1     8,A5,A5           ; |159| <0,8> 

           NOP             1

           SPKERNEL 0,0
||         STDW    .D2T2   B5:B4,*B6++       ; |161| <0,10>  ^ 

;** --------------------------------------------------------------------------*
$C$L8:    ; PIPED LOOP EPILOG AND PROLOG
;          EXCLUSIVE CPU CYCLES: 9
           NOP             2

           SPMASKR         ;$C$L8
||         ZERO    .S1     A4                ; |159| 
||         ADD     .D1     1,A3,A3           ; |158| 

           ADD     .L2     8,B9,B9           ; |158| 
|| [ A1]   B       .S2     $C$L8             ; |158| 

           MV      .S1     A6,A14
||         SUB     .D1     A1,1,A1           ; |158| 

           MV      .L2X    A12,B8
||         MV      .L1X    B9,A5

           MV      .S1     A14,A6
||         MVK     .L2     0x6,B5            ; |159| 
||         MVK     .S2     5,B4              ; |159| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L8}         ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVK     .S1     0x24,A3           ; |166| 

           CALL    .S1     _pow              ; |168| 
||         STW     .D2T1   A3,*+SP(12)
||         ZERO    .L1     A13
||         SUB     .L2X    A14,8,B12
||         SUB     .D1     A12,8,A10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D1T1   *++A10,A5:A4      ; |168| 
||         LDDW    .D2T2   *++B12,B5:B4      ; |168| 

           ADDKPC  .S2     $C$RL11,B3,3      ; |168| 
$C$RL11:   ; CALL OCCURS {_pow} {0}          ; |168| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           MVKL    .S1     _output,A3
           MVKH    .S1     _output,A3
           LDW     .D1T1   *A3,A3            ; |168| 
           ZERO    .L2     B7:B6             ; |169| 
           NOP             3
           ADD     .L1     A13,A3,A3         ; |168| 
           STDW    .D1T1   A5:A4,*A3         ; |168| 
           LDDW    .D2T2   *B12,B5:B4        ; |169| 
           NOP             4
           CMPLTDP .S2     B5:B4,B7:B6,B0    ; |169| 
           NOP             1
   [!B0]   B       .S1     $C$L10            ; |169| 

   [ B0]   CALL    .S1     _pow              ; |169| 
|| [ B0]   LDDW    .D1T1   *A10,A5:A4        ; |169| 

   [!B0]   CALL    .S1     _powdp            ; |169| 
   [!B0]   LDDW    .D1T1   *A10,A5:A4        ; |169| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L10}        ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL12,B3,0      ; |169| 
$C$RL12:   ; CALL OCCURS {_pow} {0}          ; |169| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L11            ; |169| 
||         MVKL    .S2     _output,B4

           MVKH    .S2     _output,B4
           NOP             1
           MV      .L1X    B4,A15            ; |169| 
           LDW     .D1T1   *+A15(4),A3       ; |169| 
           NOP             1
           ; BRANCH OCCURS {$C$L11}          ; |169| 
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 8
           ADDKPC  .S2     $C$RL13,B3,1      ; |169| 
$C$RL13:   ; CALL OCCURS {_powdp} {0}        ; |169| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           NOP             1
           MV      .L1X    B4,A15            ; |169| 
           LDW     .D1T1   *+A15(4),A3       ; |169| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 10
           NOP             3
           ADD     .L1     A13,A3,A3         ; |169| 

           STDW    .D1T1   A5:A4,*A3         ; |169| 
||         CALL    .S1     _powdp_c          ; |170| 

           LDDW    .D1T1   *A10,A5:A4        ; |170| 
||         LDDW    .D2T2   *B12,B5:B4        ; |170| 

           ADDKPC  .S2     $C$RL14,B3,3      ; |170| 
$C$RL14:   ; CALL OCCURS {_powdp_c} {0}      ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDW     .D1T1   *+A15(8),A3       ; |170| 
           DADD    .L2X    0,A5:A4,B5:B4     ; |170| 
           NOP             3
           ADD     .L1     A13,A3,A3         ; |170| 
           STDW    .D1T2   B5:B4,*A3         ; |170| 
           LDDW    .D1T1   *A10,A27:A26      ; |171| 
           LDDW    .D2T2   *B12,B23:B22      ; |171| 
           NOP             3
           ABSDP   .S1     A27:A26,A29:A28   ; |195| 
           NOP             1

           DADD    .L1     0,A29:A28,A5:A4   ; |195| 
||         CALLP   .S2     _logdpMod_powdpi,B3

$C$RL15:   ; CALL OCCURS {_logdpMod_powdpi} {0}  ; |195| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 119

           ZERO    .L1     A7
||         FMPYDP  .M2X    B23:B22,A5:A4,B5:B4 ; |195| 
||         ZERO    .S1     A6                ; |196| 
||         MVKL    .S2     0x652b82fe,B6

           SET     .S1     A7,0x14,0x1d,A7
||         MVKL    .S2     0x3ff71547,B7

           CMPEQDP .S1     A29:A28,A7:A6,A0  ; |196| 
||         MVKH    .S2     0x652b82fe,B6

           MVKH    .S2     0x3ff71547,B7
   [ A0]   ZERO    .L2     B5:B4             ; |197| 
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |153| 
           MVKL    .S1     0xbf2bd010,A5
           ZERO    .L1     A8                ; |154| 
           MVKL    .S2     0x6f58dc1c,B16
           DPINT   .L2     B7:B6,B18         ; |153| 
           MVKL    .S1     0x3fe63000,A7
           MVKL    .S2     0x3ef152a4,B17
           MVKH    .S1     0x3fe63000,A7
           INTDP   .L2     B18,B7:B6         ; |153| 
           MVKH    .S2     0x6f58dc1c,B16
           MVKL    .S1     0x5c610ca8,A4
           MVKH    .S2     0x3ef152a4,B17
           MVKH    .S1     0xbf2bd010,A5
           MVKL    .S2     0x3f7c70e4,B25
           FMPYDP  .M1X    A7:A6,B7:B6,A7:A6 ; |153| 
           MVKH    .S1     0x5c610ca8,A4
           MVKL    .S2     0x6fb3f6e0,B24
           FMPYDP  .M2X    A5:A4,B7:B6,B7:B6 ; |153| 
           MVKH    .S2     0x3f7c70e4,B25
           FSUBDP  .L2X    B5:B4,A7:A6,B9:B8 ; |153| 
           MVKH    .S2     0x6fb3f6e0,B24
           MVKL    .S2     0x3fac718e,B21
           FSUBDP  .L2     B9:B8,B7:B6,B9:B8 ; |153| 
           MVKL    .S2     0x714251b3,B20
           MVKH    .S2     0x3fac718e,B21
           FMPYDP  .M2     B9:B8,B9:B8,B7:B6 ; |153| 
           MVKL    .S1     0x3f403f99,A5
           MVKL    .S1     0x6fde3809,A4
           MVKH    .S1     0x3f403f99,A5
           FMPYDP  .M2     B17:B16,B7:B6,B17:B16 ; |153| 
           MVKH    .S1     0x6fde3809,A4
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |154| 
           MVKH    .S2     0x714251b3,B20
           FADDDP  .L2     B25:B24,B17:B16,B17:B16 ; |153| 
           ZERO    .L1     A6                ; |153| 
           FADDDP  .L1X    B21:B20,A5:A4,A5:A4 ; |154| 
           FMPYDP  .M2     B7:B6,B17:B16,B17:B16 ; |153| 
           ZERO    .S1     A7
           MVKH    .S1     0x3fd00000,A7
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |154| 
           ZERO    .L1     A9
           FADDDP  .L1X    A7:A6,B17:B16,A7:A6 ; |153| 
           SET     .S1     A9,0x15,0x1d,A9
           FADDDP  .L1     A9:A8,A5:A4,A5:A4 ; |154| 
           FMPYDP  .M1X    B9:B8,A7:A6,A7:A6 ; |153| 
           DPINT   .L2     B23:B22,B19       ; |186| 
           ZERO    .L2     B29
           ZERO    .L2     B26
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |154| 
           ZERO    .L2     B6                ; |159| 
           SET     .S2     B29,0x1e,0x1e,B7
           RCPDP   .S1     A5:A4,A9:A8       ; |159| 
           LDW     .D2T1   *+SP(12),A24      ; |207| 
           FMPYDP  .M1     A5:A4,A9:A8,A17:A16 ; |159| 
           ZERO    .L1     A18               ; |159| 
           ZERO    .L1     A19
           ZERO    .L1     A31
           SUB     .L1     A24,1,A23         ; |166| 
           FSUBDP  .L2X    B7:B6,A17:A16,B7:B6 ; |159| 
           STW     .D2T1   A23,*+SP(12)      ; |171| 
           SET     .S1     A19,0x1e,0x1e,A19
           EXTU    .S2     B19,31,31,B28     ; |188| 
           FMPYDP  .M1X    A9:A8,B7:B6,A9:A8 ; |159| 
           MVK     .S2     0x400,B27
           MVKL    .S2     0xc086232b,B9
           MVKL    .S2     0xdd7abcd2,B8
           FMPYDP  .M1     A5:A4,A9:A8,A17:A16 ; |159| 
           MVKH    .S2     0xc086232b,B9
           MVKH    .S2     0xdd7abcd2,B8
           CMPLTDP .S2     B5:B4,B9:B8,B1    ; |167| 
           FSUBDP  .L1     A19:A18,A17:A16,A17:A16 ; |159| 
           ZERO    .L2     B6                ; |159| 
           MV      .L2X    A19,B7            ; |159| 
           FMPYDP  .M1     A9:A8,A17:A16,A9:A8 ; |159| 
           ZERO    .L1     A17:A16           ; |188| 
           CMPLTDP .S1     A27:A26,A17:A16,A3 ; |188| 
           NOP             1
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |159| 
           NOP             4

           FSUBDP  .S2X    B7:B6,A5:A4,B17:B16 ; |159| 
||         INTDP   .L2     B19,B7:B6         ; |188| 

           ZERO    .L1     A4                ; |159| 
           SET     .S1     A31,0x15,0x1d,A5

           FMPYDP  .M2X    A9:A8,B17:B16,B17:B16 ; |159| 
||         MVKL    .S1     0x40862e42,A9

           MVKL    .S1     0xfefa39cc,A8

           CMPEQDP .S2     B23:B22,B7:B6,B20 ; |188| 
||         MVKH    .S1     0x40862e42,A9

           MVKH    .S1     0xfefa39cc,A8

           FMPYDP  .M2X    A7:A6,B17:B16,B7:B6 ; |159| 
||         ZERO    .L2     B16               ; |159| 
||         CMPGTDP .S1X    B5:B4,A9:A8,A0    ; |162| 

           AND     .L2X    B20,A3,B9         ; |188| 
           INTDP   .L1X    B19,A7:A6         ; |202| 
           AND     .L2     B28,B9,B0         ; |188| 

           FADDDP  .L2X    A5:A4,B7:B6,B9:B8 ; |159| 
||         ADD     .S2     B27,B18,B7        ; |159| 
||         MVK     .D2     0x1,B6            ; |184| 
||         ZERO    .L1     A5:A4             ; |202| 

           SHL     .S2     B7,20,B17         ; |159| 
|| [ B0]   ADD     .L2     -2,B6,B6
||         CMPLTDP .S1     A27:A26,A5:A4,A3  ; |202| 

           INTDP   .L2     B6,B7:B6          ; |200| 

           FMPYDP  .M2     B17:B16,B9:B8,B5:B4 ; |159| 
||         ZERO    .L1     A5:A4             ; |206| 
||         CMPEQDP .S1X    B23:B22,A7:A6,A9  ; |202| 

           MVK     .L2     0xffffffff,B8     ; |203| 
           ZERO    .L1     A7:A6             ; |206| 
           XOR     .L1     1,A9,A30          ; |202| 

   [ A0]   MVKL    .S2     0x7fefffff,B5
|| [ A0]   MVK     .L2     0xffffffff,B4     ; |163| 

   [ A0]   MVKH    .S2     0x7fefffff,B5
||         AND     .L1     A30,A3,A0         ; |202| 
||         ADDAW   .D1     A15,3,A30

   [ B1]   ZERO    .L2     B5:B4             ; |168| 
||         LDW     .D1T1   *A30,A8           ; |171| 

           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |200| 
||         CMPLTDP .S2X    B23:B22,A5:A4,B6  ; |206| 

           CMPEQDP .S1     A27:A26,A7:A6,A2  ; |206| 
           SET     .S2     B26,0x0,0x1e,B9

           AND     .L1X    B6,A2,A1          ; |206| 
||         SUB     .S1     A24,1,A2          ; |166| 

   [ A1]   LDDW    .D2T2   *+SP(48),B7:B6    ; |203| 
|| [ A0]   DADD    .L2     0,B9:B8,B5:B4     ; |203| 
||         ADD     .L1     A13,A8,A25        ; |171| 
||         ADD     .S1     8,A13,A13         ; |172| 

   [ A2]   BNOP    .S1     $C$L9,3           ; |166| 
   [ A1]   DADD    .L2     0,B7:B6,B5:B4     ; |207| 

   [ A2]   CALL    .S1     _pow              ; |168| 
||         STDW    .D1T2   B5:B4,*A25        ; |171| 

           ; BRANCHCC OCCURS {$C$L9}         ; |166| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           MV      .L2X    A15,B12
||         CALL    .S1     _powdp_v          ; |175| 

           LDW     .D2T1   *+B12(16),A6      ; |175| 
           MVK     .S2     0x24,B6           ; |175| 
           ADDKPC  .S2     $C$RL16,B3,1      ; |175| 

           MV      .L2X    A14,B4            ; |175| 
||         MV      .L1     A12,A4            ; |175| 

$C$RL16:   ; CALL OCCURS {_powdp_v} {0}      ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B12,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MVK     .S1     0x24,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .S1     0x24,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL18:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .S1     0x24,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL19:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B4

           LDW     .D2T1   *+SP(28),A13      ; |68| 
||         MVKL    .S2     0xd9d7bdbb,B6

           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B4

           MV      .L1     A15,A31           ; |69| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T1   *A31,A4           ; |69| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A13,B4           ; |69| 
||         MVK     .S1     0x24,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL20:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(32),A3       ; |69| 
           MVKL    .S2     _fcn_pass,B31
           MVKH    .S2     _fcn_pass,B31
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           NOP             1

           MV      .L2X    A3,B4             ; |69| 
||         STW     .D2T1   A3,*+SP(40)       ; |69| 

           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T1   *+SP(36),A3
           NOP             3

   [!B0]   B       .S2     $C$L12            ; |72| 
|| [!B0]   MVKL    .S1     _all_pass,A4
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     _print_test_results ; |179| 
|| [ B0]   MV      .L2X    A3,B4
|| [!B0]   MVKH    .S1     _all_pass,A4
||         STW     .D2T1   A3,*+SP(44)       ; |72| 
|| [!B0]   ZERO    .L1     A3                ; |72| 

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             2
           ; BRANCHCC OCCURS {$C$L12}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           CMPEQ   .L1     A4,0,A3           ; |72| 
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           NOP             2
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   ZERO    .L1     A3                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |179| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x3,A4            ; |179| 
||         ADDKPC  .S2     $C$RL21,B3,0      ; |179| 

$C$RL21:   ; CALL OCCURS {_print_test_results} {0}  ; |179| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 33
           LDW     .D2T1   *+SP(140),A29     ; |203| 
           LDW     .D2T1   *+SP(132),A27     ; |159| 
           LDW     .D2T1   *+SP(100),A25     ; |159| 
           LDW     .D2T1   *+SP(128),A26     ; |159| 
           LDW     .D2T1   *+SP(136),A28     ; |159| 
           LDW     .D2T1   *+SP(148),A30     ; |203| 
           STW     .D2T2   B10,*+SP(96)      ; |153| 
           STW     .D2T1   A11,*+SP(156)     ; |159| 
           STW     .D2T1   A11,*+SP(140)     ; |159| 
           STW     .D2T1   A11,*+SP(132)     ; |159| 

           STW     .D2T2   B11,*+SP(100)     ; |153| 
||         ZERO    .L2     B5

           LDW     .D2T1   *+SP(24),A12      ; |189| 
||         MVKH    .S2     0xbff80000,B5

           STW     .D2T2   B5,*+SP(196)      ; |190| 
||         MVK     .L1     0xffffffff,A22    ; |203| 

           STW     .D2T1   A22,*+SP(176)     ; |182| 
||         ZERO    .L1     A24

           STW     .D2T1   A24,*+SP(120)     ; |183| 
||         ZERO    .L2     B30

           STW     .D2T2   B30,*+SP(64)      ; |183| 

           STW     .D2T2   B30,*+SP(144)     ; |182| 
||         ZERO    .L2     B31

           STW     .D2T2   B31,*+SP(80)      ; |183| 

           STW     .D2T2   B31,*+SP(192)     ; |182| 
||         ZERO    .L1     A4

           STW     .D2T1   A4,*+SP(152)      ; |182| 
||         MVKL    .S1     0xcccccccd,A31
||         ZERO    .L1     A7

           STW     .D2T1   A7,*+SP(128)      ; |183| 
||         MVKL    .S1     0xc000cccc,A3
||         ZERO    .L1     A6

           STW     .D2T1   A6,*+SP(136)      ; |183| 
||         MVKH    .S1     0xcccccccd,A31

           STW     .D2T1   A31,*+SP(184)     ; |189| 
||         MVKH    .S1     0xc000cccc,A3

           STW     .D2T1   A3,*+SP(188)      ; |189| 
           STW     .D2T1   A25,*+SP(124)     ; |154| 
           STW     .D2T1   A26,*+SP(160)     ; |159| 
           STW     .D2T1   A27,*+SP(164)     ; |159| 
           STW     .D2T1   A28,*+SP(168)     ; |159| 

           STW     .D2T1   A29,*+SP(172)     ; |159| 
||         MVKL    .S1     _a_ext,A10
||         MVKL    .S2     _b_ext,B4
||         ZERO    .L1     A5

           STW     .D2T1   A30,*+SP(180)     ; |203| 
||         SET     .S1     A5,0x14,0x14,A5
||         MVKH    .S2     _b_ext,B4

           STW     .D2T1   A25,*+SP(148)     ; |154| 
||         MVK     .S2     0x777,B5
||         MVKH    .S1     _a_ext,A10

           STDW    .D2T1   A5:A4,*B4         ; |183| 
||         MV      .L1     A10,A23           ; |183| 
||         ZERO    .L2     B12

           CALL    .S2     _pow              ; |185| 
||         STDW    .D1T1   A5:A4,*A23        ; |182| 
||         MV      .L1X    B5,A14
||         MV      .L2     B4,B10            ; |183| 
||         ZERO    .S1     A11
||         ZERO    .D2     B11

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
;          EXCLUSIVE CPU CYCLES: 5

           LDDW    .D1T1   *A10,A5:A4        ; |185| 
||         LDDW    .D2T2   *B10,B5:B4        ; |185| 

           ADDKPC  .S2     $C$RL22,B3,3      ; |185| 
$C$RL22:   ; CALL OCCURS {_pow} {0}          ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 49
           MV      .L2X    A15,B4            ; |185| 
           LDW     .D2T2   *B4,B4            ; |185| 
           NOP             4
           ADD     .L1X    A11,B4,A3         ; |185| 
           STDW    .D1T1   A5:A4,*A3         ; |185| 

           CALLP   .S2     _powdp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |186| 
||         LDDW    .D2T2   *B10,B5:B4        ; |186| 

$C$RL23:   ; CALL OCCURS {_powdp} {0}        ; |186| 
           MV      .L2X    A15,B4            ; |186| 
           LDW     .D2T2   *+B4(4),B4        ; |186| 
           NOP             4
           ADD     .L1X    A11,B4,A3         ; |186| 
           STDW    .D1T1   A5:A4,*A3         ; |186| 

           CALLP   .S2     _powdp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |187| 
||         LDDW    .D2T2   *B10,B5:B4        ; |187| 

$C$RL24:   ; CALL OCCURS {_powdp_c} {0}      ; |187| 
           MV      .L2X    A15,B4            ; |187| 
           LDW     .D2T2   *+B4(8),B4        ; |187| 
           NOP             4
           ADD     .L2X    A11,B4,B4         ; |187| 
           STDW    .D2T1   A5:A4,*B4         ; |187| 
           LDDW    .D1T1   *A10,A27:A26      ; |188| 
           LDDW    .D2T2   *B10,B23:B22      ; |188| 
           NOP             3
           ABSDP   .S1     A27:A26,A29:A28   ; |195| 
           NOP             1

           DADD    .L1     0,A29:A28,A5:A4   ; |195| 
||         CALLP   .S2     _logdpMod_powdpi,B3

$C$RL25:   ; CALL OCCURS {_logdpMod_powdpi} {0}  ; |195| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 133

           LDDW    .D2T2   *+SP(56),B7:B6    ; |200| 
||         FMPYDP  .M2X    B23:B22,A5:A4,B5:B4 ; |195| 

           CMPEQDP .S2X    A29:A28,B13:B12,B0 ; |196| 
           LDDW    .D2T2   *+SP(64),B9:B8
           LDDW    .D2T1   *+SP(72),A5:A4
   [ B0]   ZERO    .L2     B5:B4             ; |197| 
           FMPYDP  .M2     B7:B6,B5:B4,B7:B6 ; |153| 
           DPINT   .L2     B23:B22,B29       ; |186| 
           MVK     .S2     0x400,B28
           LDW     .D1T1   *A12,A31          ; |188| 
           DPINT   .L2     B7:B6,B20         ; |153| 
           EXTU    .S2     B29,31,31,B27     ; |188| 
           SUB     .L1     A14,1,A2          ; |184| 
           SUB     .L1     A14,1,A14         ; |184| 
           INTDP   .L2     B20,B7:B6         ; |153| 
           NOP             4
           FMPYDP  .M2     B9:B8,B7:B6,B9:B8 ; |153| 
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |153| 
           NOP             2
           FSUBDP  .L2     B5:B4,B9:B8,B7:B6 ; |153| 
           LDDW    .D2T2   *+SP(88),B9:B8
           NOP             1
           FSUBDP  .L2X    B7:B6,A5:A4,B19:B18 ; |153| 
           LDDW    .D2T2   *+SP(96),B7:B6
           LDDW    .D2T1   *+SP(112),A5:A4   ; |153| 
           FMPYDP  .M2     B19:B18,B19:B18,B17:B16 ; |153| 
           NOP             3
           FMPYDP  .M2     B7:B6,B17:B16,B7:B6 ; |153| 
           FMPYDP  .M1X    A5:A4,B17:B16,A7:A6 ; |154| 
           LDDW    .D2T1   *+SP(104),A5:A4
           NOP             1
           FADDDP  .L2     B9:B8,B7:B6,B7:B6 ; |153| 
           LDDW    .D2T2   *+SP(80),B9:B8
           NOP             1
           FMPYDP  .M2     B17:B16,B7:B6,B7:B6 ; |153| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |154| 
           LDDW    .D2T1   *+SP(120),A7:A6
           NOP             1
           FADDDP  .L2     B9:B8,B7:B6,B7:B6 ; |153| 
           FMPYDP  .M1X    B17:B16,A5:A4,A5:A4 ; |154| 
           MV      .S2     B11,B8            ; |159| 
           FMPYDP  .M2     B19:B18,B7:B6,B7:B6 ; |153| 
           ADD     .L2     B28,B20,B9        ; |159| 
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |154| 
           SHL     .S2     B9,20,B9          ; |159| 
           NOP             1
           FSUBDP  .L1X    A5:A4,B7:B6,A17:A16 ; |154| 
           LDDW    .D2T1   *+SP(128),A5:A4
           NOP             1
           RCPDP   .S1     A17:A16,A7:A6     ; |159| 
           NOP             1
           FMPYDP  .M1     A17:A16,A7:A6,A9:A8 ; |159| 
           NOP             3
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |159| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |159| 
           LDDW    .D2T1   *+SP(136),A5:A4
           NOP             2
           FMPYDP  .M1     A17:A16,A7:A6,A9:A8 ; |159| 
           NOP             3
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |159| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |159| 
           LDDW    .D2T1   *+SP(152),A5:A4
           NOP             2
           FMPYDP  .M1     A17:A16,A7:A6,A9:A8 ; |159| 
           NOP             3
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |159| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A7:A6 ; |159| 
           NOP             2
           INTDP   .L1X    B29,A5:A4         ; |188| 
           NOP             1

           FMPYDP  .M2X    B7:B6,A7:A6,B17:B16 ; |159| 
||         LDDW    .D2T2   *+SP(144),B7:B6   ; |188| 
||         ZERO    .L1     A7:A6             ; |188| 

           CMPLTDP .S1     A27:A26,A7:A6,A3  ; |188| 
           NOP             1
           CMPEQDP .S1X    B23:B22,A5:A4,A4  ; |188| 
           NOP             1

           FADDDP  .L2     B7:B6,B17:B16,B7:B6 ; |159| 
||         AND     .L1     A4,A3,A3          ; |188| 
||         LDDW    .D2T1   *+SP(160),A5:A4   ; |159| 

           NOP             1

           AND     .S2X    B27,A3,B0         ; |188| 
||         MVK     .L1     0x1,A3            ; |184| 

   [ B0]   ADD     .L1     -2,A3,A3
||         FMPYDP  .M2     B9:B8,B7:B6,B17:B16 ; |159| 
||         LDDW    .D2T2   *+SP(168),B9:B8   ; |159| 

           INTDP   .L2     B29,B7:B6         ; |202| 
           CMPGTDP .S1X    B5:B4,A5:A4,A0    ; |162| 
           INTDP   .L1     A3,A5:A4          ; |200| 
   [ A0]   MVKL    .S2     0x7fefffff,B17
           CMPLTDP .S2     B5:B4,B9:B8,B0    ; |167| 
   [ A0]   MVK     .L2     0xffffffff,B16    ; |163| 
   [ A0]   MVKH    .S2     0x7fefffff,B17

           CMPEQDP .S2     B23:B22,B7:B6,B6  ; |202| 
|| [ B0]   ZERO    .L2     B17:B16           ; |168| 

           ZERO    .L2     B5:B4             ; |202| 

           CMPLTDP .S2X    A27:A26,B5:B4,B8  ; |202| 
||         XOR     .L2     1,B6,B6           ; |202| 
||         FMPYDP  .M1X    B17:B16,A5:A4,A7:A6 ; |200| 
||         ZERO    .L1     A5:A4             ; |206| 

           CMPEQDP .S1     A27:A26,A5:A4,A8  ; |206| 
           AND     .L2     B6,B8,B0          ; |202| 
   [ B0]   LDDW    .D2T1   *+SP(176),A5:A4   ; |202| 
           ZERO    .L2     B5:B4             ; |206| 
           CMPLTDP .S2     B23:B22,B5:B4,B4  ; |206| 
           ADD     .L1     A11,A31,A3        ; |188| 
           AND     .L2X    B4,A8,B2          ; |206| 

   [ B0]   DADD    .L1     0,A5:A4,A7:A6     ; |203| 
|| [ B2]   LDDW    .D2T1   *+SP(48),A5:A4    ; |203| 

           LDDW    .D2T2   *+SP(192),B5:B4
           ADD     .L1     8,A11,A11         ; |184| 
           NOP             2

   [ B2]   DADD    .L1     0,A5:A4,A7:A6     ; |207| 
||         LDDW    .D2T1   *+SP(184),A5:A4

           STDW    .D1T1   A7:A6,*A3         ; |188| 

           LDDW    .D2T2   *B10,B7:B6        ; |190| 
||         LDDW    .D1T1   *A10,A7:A6        ; |189| 

           NOP             3
   [ A2]   B       .S1     $C$L13            ; |184| 

           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |190| 
||         FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |189| 

           NOP             3

   [ A2]   CALL    .S1     _pow              ; |185| 
||         STDW    .D2T2   B5:B4,*++B10      ; |190| 
||         STDW    .D1T1   A5:A4,*++A10      ; |189| 

           ; BRANCHCC OCCURS {$C$L13}        ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     _powdp_v          ; |192| 
||         MV      .L2X    A15,B10
||         MVKL    .S2     _b_ext,B4

           MVKH    .S2     _b_ext,B4
||         LDW     .D2T1   *+B10(16),A6      ; |192| 

           MVKL    .S1     _a_ext,A4
           MVKH    .S1     _a_ext,A4
           MVK     .S2     0x777,B6          ; |192| 
           ADDKPC  .S2     $C$RL26,B3,0      ; |192| 
$C$RL26:   ; CALL OCCURS {_powdp_v} {0}      ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .S1     0x777,A6          ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL27:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B11
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     _fcn_pass,B11
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B11(4)       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0x777,A6          ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL28:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A15,A3            ; |67| 
||         STW     .D2T1   A4,*+B11(8)       ; |67| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0x777,A6          ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL29:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A13,A3            ; |68| 
||         MV      .L2X    A15,B4            ; |68| 
||         STW     .D2T1   A4,*+B11(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x777,A6          ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL30:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(32),A3       ; |69| 
           LDW     .D2T2   *+SP(36),B4
           STW     .D2T1   A4,*+B11(16)      ; |69| 
           NOP             2
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L14            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |196| 
   [!A0]   MV      .L1X    B12,A4
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     _all_pass,A3
   [!A0]   MVKH    .S1     _all_pass,A3
           ; BRANCHCC OCCURS {$C$L14}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   MV      .L1X    B12,A0            ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   MV      .L1X    B12,A4
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |196| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x4,A4            ; |196| 
||         ADDKPC  .S2     $C$RL31,B3,0      ; |196| 

$C$RL31:   ; CALL OCCURS {_print_test_results} {0}  ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MV      .L1X    B12,A5            ; |114| 
||         MVKL    .S1     _cycle_counts+24,A3

           MVKH    .S1     _cycle_counts+24,A3
||         MV      .L2     B12,B4            ; |114| 
||         MV      .L1X    B12,A4            ; |114| 

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

           CALL    .S1     _gimme_random     ; |206| 
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKL    .S1     _t_offset,A3

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     _t_offset,A3

           ZERO    .L2     B5
||         STDW    .D1T2   B5:B4,*A3         ; |117| 
||         MV      .L1X    B12,A10

           MVKH    .S2     0xc0240000,B5
||         MV      .D2     B12,B4            ; |206| 
||         MV      .L1X    B12,A4            ; |206| 
||         ZERO    .D1     A5
||         DADD    .L2X    0,A5:A4,B11:B10   ; |114| 
||         MVK     .S1     0x80,A11

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
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 1

           ADDKPC  .S2     $C$RL32,B3,0      ; |206| 
||         MVKH    .S1     0x40340000,A5

$C$RL32:   ; CALL OCCURS {_gimme_random} {0}  ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     _input,B4
           MVKH    .S2     _input,B4
           NOP             1
           MV      .L1X    B4,A12            ; |206| 
           LDW     .D1T2   *A12,B4           ; |206| 
           NOP             4

           ADD     .L1X    A10,B4,A3         ; |206| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |206| 

           STDW    .D1T2   B5:B4,*A3         ; |206| 
||         ZERO    .L2     B5

           ZERO    .L1     A5
||         MVKH    .S2     0xc0240000,B5

           CALLP   .S2     _gimme_random,B3
||         MV      .L2     B12,B4            ; |207| 
||         MVKH    .S1     0x40340000,A5
||         MV      .L1X    B12,A4            ; |207| 

$C$RL33:   ; CALL OCCURS {_gimme_random} {0}  ; |207| 
           LDW     .D1T2   *+A12(4),B4       ; |207| 
           DADD    .L1     0,A5:A4,A27:A26   ; |207| 
           NOP             3
           ADD     .L2X    A10,B4,B4         ; |207| 

           STDW    .D2T1   A27:A26,*B4       ; |207| 
||         MVC     .S2     TSCL,B22          ; |122| 

           MVC     .S2     TSCH,B23          ; |122| 
           MV      .L1     A12,A3            ; |122| 
           LDW     .D1T1   *A3,A3            ; |211| 
           NOP             4
           ADD     .L1     A10,A3,A3         ; |211| 
           LDDW    .D1T1   *A3,A29:A28       ; |211| 
           NOP             4
           ABSDP   .S1     A29:A28,A31:A30   ; |195| 
           NOP             1

           CALLP   .S2     _logdpMod_powdpi,B3
||         DADD    .L1     0,A31:A30,A5:A4   ; |195| 

$C$RL34:   ; CALL OCCURS {_logdpMod_powdpi} {0}  ; |195| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 134

           FMPYDP  .M1     A27:A26,A5:A4,A5:A4 ; |195| 
||         ZERO    .L2     B5
||         MV      .D2     B12,B4            ; |195| 
||         MVKL    .S2     0x652b82fe,B6
||         MVKL    .S1     0x3fe63000,A7
||         MV      .L1X    B12,A6            ; |153| 
||         ZERO    .D1     A21

           SET     .S2     B5,0x14,0x1d,B5
||         MVKH    .S1     0x3fe63000,A7
||         MV      .L1X    B12,A20           ; |154| 
||         ZERO    .L2     B29
||         ZERO    .D1     A2
||         ZERO    .D2     B13

           CMPEQDP .S2X    A31:A30,B5:B4,B0  ; |196| 
||         MVKL    .S1     0x5c610ca8,A8
||         DPINT   .L1     A27:A26,A3        ; |186| 
||         MVK     .L2     0x1,B18           ; |184| 

           MVKL    .S1     0xbf2bd010,A9

   [ B0]   ZERO    .L1     A5:A4             ; |197| 
||         MVKL    .S2     0x3ff71547,B7
||         MVKH    .S1     0x5c610ca8,A8

           MVKH    .S2     0x652b82fe,B6
||         MVKH    .S1     0xbf2bd010,A9

           MVKH    .S2     0x3ff71547,B7
||         MVKL    .S1     0x3fac718e,A19

           FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |153| 
||         MVKL    .S2     0x3f7c70e4,B17
||         MVKL    .S1     0x714251b3,A18

           MVKL    .S2     0x6fb3f6e0,B16
||         MVKH    .S1     0x3fac718e,A19

           MVKH    .S2     0x3f7c70e4,B17
||         MVKH    .S1     0x714251b3,A18

           MVKH    .S2     0x6fb3f6e0,B16
||         MVKH    .S1     0x3fd00000,A21

           DPINT   .L2     B5:B4,B8          ; |153| 
||         SET     .S2     B13,0x15,0x1d,B13
||         MVKL    .S1     _output+12,A23

           MVK     .S2     0x400,B9
||         MVKH    .S1     _output+12,A23

           LDW     .D1T2   *A23,B27          ; |211| 
||         MVKL    .S1     _t_start,A14

           MVKH    .S1     _t_start,A14

           INTDP   .L2     B8,B5:B4          ; |153| 
||         STDW    .D1T2   B23:B22,*A14

           NOP             2
           ADD     .S2X    A10,B27,B26       ; |211| 
           NOP             1
           FMPYDP  .M2X    A7:A6,B5:B4,B7:B6 ; |153| 

           FMPYDP  .M1X    A9:A8,B5:B4,A7:A6 ; |153| 
||         MVKL    .S2     0x3ef152a4,B5

           MVKL    .S2     0x6f58dc1c,B4
           MVKH    .S2     0x3ef152a4,B5
           MVKH    .S2     0x6f58dc1c,B4

           FSUBDP  .L1X    A5:A4,B7:B6,A9:A8 ; |153| 
||         MVKL    .S2     0x3f403f99,B7

           MVKL    .S2     0x6fde3809,B6
           MVKH    .S2     0x3f403f99,B7

           FSUBDP  .L1     A9:A8,A7:A6,A9:A8 ; |153| 
||         MVKH    .S2     0x6fde3809,B6

           NOP             2
           FMPYDP  .M1     A9:A8,A9:A8,A7:A6 ; |153| 
           NOP             3

           FMPYDP  .M1X    B7:B6,A7:A6,A17:A16 ; |154| 
||         SET     .S2     B29,0x15,0x1d,B7
||         MV      .L2     B12,B6            ; |153| 

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |153| 
           NOP             2

           FADDDP  .L1     A19:A18,A17:A16,A17:A16 ; |154| 
||         SET     .S1     A2,0x1e,0x1e,A19
||         MV      .D1X    B12,A18           ; |154| 
||         ZERO    .L2     B12               ; |159| 

           FADDDP  .L2     B17:B16,B5:B4,B5:B4 ; |153| 
           NOP             2

           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |153| 
||         FMPYDP  .M1     A7:A6,A17:A16,A7:A6 ; |154| 

           NOP             3

           FADDDP  .L2X    A21:A20,B5:B4,B5:B4 ; |153| 
||         FADDDP  .L1X    B7:B6,A7:A6,A7:A6 ; |154| 

           MV      .L2X    A19,B7            ; |159| 
           NOP             1
           FMPYDP  .M2X    A9:A8,B5:B4,B5:B4 ; |153| 
           NOP             4
           FSUBDP  .L1X    A7:A6,B5:B4,A9:A8 ; |154| 
           NOP             2
           RCPDP   .S1     A9:A8,A7:A6       ; |159| 
           NOP             1
           FMPYDP  .M1     A9:A8,A7:A6,A17:A16 ; |159| 
           NOP             3
           FSUBDP  .L1     A19:A18,A17:A16,A17:A16 ; |159| 
           NOP             2
           FMPYDP  .M1     A7:A6,A17:A16,A7:A6 ; |159| 
           NOP             3
           FMPYDP  .M1     A9:A8,A7:A6,A17:A16 ; |159| 
           NOP             4

           FSUBDP  .L2X    B7:B6,A17:A16,B7:B6 ; |159| 
||         ZERO    .L1     A17:A16           ; |188| 

           CMPLTDP .S1     A29:A28,A17:A16,A25 ; |188| 
           NOP             1

           FMPYDP  .M2X    A7:A6,B7:B6,B7:B6 ; |159| 
||         MV      .L1     A19,A7            ; |188| 
||         MV      .S1     A18,A6            ; |188| 

           NOP             3

           FMPYDP  .M2X    A9:A8,B7:B6,B17:B16 ; |159| 
||         INTDP   .L1     A3,A9:A8          ; |188| 

           NOP             4

           FSUBDP  .L1X    A7:A6,B17:B16,A7:A6 ; |159| 
||         CMPEQDP .S1     A27:A26,A9:A8,A1  ; |188| 
||         MVKL    .S2     0xfefa39cc,B16

           MVKL    .S2     0x40862e42,B17

           AND     .D1     A1,A25,A24        ; |188| 
||         EXTU    .S1     A3,31,31,A8       ; |188| 
||         MVKH    .S2     0xfefa39cc,B16

           AND     .L1     A8,A24,A0         ; |188| 
||         MVKH    .S2     0x40862e42,B17

           FMPYDP  .M2X    B7:B6,A7:A6,B7:B6 ; |159| 
|| [ A0]   ADD     .L2     -2,B18,B18
||         MVKL    .S1     0xc086232b,A7

           INTDP   .L2     B18,B9:B8         ; |200| 
||         ADD     .S2     B9,B8,B18         ; |159| 
||         MVKL    .S1     0xdd7abcd2,A6

           SHL     .S2     B18,20,B19        ; |159| 
||         ZERO    .L2     B18               ; |159| 
||         CMPGTDP .S1X    A5:A4,B17:B16,A2  ; |162| 

           NOP             1

           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |159| 
||         INTDP   .L2X    A3,B5:B4          ; |202| 
||         MVKH    .S1     0xc086232b,A7

           MVKH    .S1     0xdd7abcd2,A6
           CMPLTDP .S1     A5:A4,A7:A6,A1    ; |167| 

           ZERO    .L1     A7:A6             ; |206| 
||         MVK     .D1     0xffffffff,A4     ; |203| 

           FADDDP  .L2     B13:B12,B7:B6,B7:B6 ; |159| 
||         CMPEQDP .S1     A29:A28,A7:A6,A22 ; |206| 

           CMPEQDP .S2X    A27:A26,B5:B4,B28 ; |202| 
           NOP             1

           FMPYDP  .M2     B19:B18,B7:B6,B17:B16 ; |159| 
||         ZERO    .L2     B7:B6             ; |206| 

           CMPLTDP .S2X    A27:A26,B7:B6,B18 ; |206| 
||         ZERO    .L2     B5:B4             ; |202| 

           NOP             2

   [ A2]   MVKL    .S2     0x7fefffff,B17
|| [ A2]   MVK     .L2     0xffffffff,B16    ; |163| 
||         AND     .L1X    B18,A22,A0        ; |206| 
||         ZERO    .S1     A22

   [ A2]   MVKH    .S2     0x7fefffff,B17
||         SET     .S1     A22,0x0,0x1e,A5

           CMPLTDP .S2X    A29:A28,B5:B4,B4  ; |202| 
|| [ A1]   ZERO    .L2     B17:B16           ; |168| 

           XOR     .L2     1,B28,B5          ; |202| 
||         FMPYDP  .M2     B17:B16,B9:B8,B7:B6 ; |200| 

           AND     .L2     B5,B4,B0          ; |202| 
|| [ A0]   LDDW    .D2T2   *+SP(48),B5:B4    ; |203| 

           NOP             2
   [ B0]   DADD    .L2X    0,A5:A4,B7:B6     ; |203| 
           NOP             1
   [ A0]   DADD    .L2     0,B5:B4,B7:B6     ; |207| 

           STDW    .D2T2   B7:B6,*B26        ; |211| 
||         MVC     .S2     TSCL,B4           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S1     _t_offset,A15
||         SUB     .L1     A11,1,A0          ; |204| 

           MVKH    .S1     _t_offset,A15

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         MVKL    .S1     _cycle_counts+24,A6

           MVKH    .S1     _cycle_counts+24,A6

           LDDW    .D1T1   *A6,A7:A6         ; |130| 
||         MVKL    .S1     _t_stop,A3

           MVKL    .S1     _cycle_counts+24,A12
           MVKH    .S1     _cycle_counts+24,A12

           ADDU    .L2X    A4,B22,B7:B6      ; |130| 
||         MVKH    .S1     _t_stop,A3

           ADD     .S2X    B7,A5,B8          ; |130| 
||         SUBU    .L2     B4,B6,B7:B6       ; |130| 
||         STDW    .D1T2   B5:B4,*A3         ; |128| 
|| [ A0]   MV      .D2     B12,B4            ; |206| 

           ADD     .L2     B8,B23,B8         ; |130| 
|| [ A0]   B       .S1     $C$L15            ; |204| 

           SUB     .L2     B5,B8,B7          ; |130| 
||         EXT     .S2     B7,24,24,B8       ; |130| 
|| [ A0]   CALL    .S1     _gimme_random     ; |206| 
||         ADDU    .L1X    A6,B6,A5:A4       ; |130| 
|| [ A0]   ZERO    .D2     B5

           ADD     .L2     B7,B8,B6          ; |130| 
||         ADD     .L1     A5,A7,A5          ; |130| 
|| [ A0]   MVKH    .S2     0xc0240000,B5

           NOP             1

           ADD     .L1X    A5,B6,A5          ; |130| 
||         SUB     .S1     A11,1,A11         ; |204| 
||         ADD     .D1     8,A10,A10         ; |204| 

           STDW    .D1T1   A5:A4,*A12        ; |130| 
|| [ A0]   ZERO    .L1     A5
|| [ A0]   MV      .S1X    B12,A4            ; |206| 

           ; BRANCHCC OCCURS {$C$L15}        ; |204| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALLP   .S2     __fltllif,B3
||         LDDW    .D1T1   *A12,A5:A4        ; |135| 

$C$RL35:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A10               ; |135| 
           MV      .L1X    B13,A11           ; |135| 
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |135| 

$C$RL36:   ; CALL OCCURS {__fixdlli} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           MV      .L2X    A12,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           SUBAW   .D2     B4,6,B12
||         ZERO    .L2     B5                ; |115| 

           STDW    .D2T2   B11:B10,*B12      ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           MVKL    .S1     _input,A12
           MVKH    .S1     _input,A12
           LDW     .D1T2   *+A12(4),B13

           MV      .L2X    A15,B30
||         LDW     .D1T1   *A12,A15

           SUBU    .L2     B4,B8,B5:B4       ; |117| 
||         MVK     .S2     0x80,B29

           EXT     .S2     B5,24,24,B7       ; |117| 
||         SUB     .L2     B6,B9,B31         ; |117| 
||         MVKL    .S1     _output,A3

           ADD     .L2     B31,B7,B7         ; |117| 
||         MV      .S2     B4,B6             ; |117| 
||         MVKH    .S1     _output,A3
||         STW     .D2T2   B29,*+SP(12)      ; |117| 

           STDW    .D2T2   B7:B6,*B30        ; |117| 
||         CALL    .S1     _pow              ; |219| 
||         LDW     .D1T1   *A3,A10

           LDDW    .D1T1   *A15++,A5:A4      ; |219| 
||         LDDW    .D2T2   *B13++,B5:B4      ; |219| 

           NOP             3
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL37,B3,0      ; |219| 
$C$RL37:   ; CALL OCCURS {_pow} {0}          ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(12),B4       ; |219| 
           STDW    .D1T1   A5:A4,*A10++      ; |219| 
           NOP             3

           SUB     .L1X    B4,1,A0           ; |218| 
||         SUB     .L2     B4,1,B4           ; |218| 

   [ A0]   B       .S1     $C$L16            ; |218| 
||         STW     .D2T2   B4,*+SP(12)       ; |219| 

   [ A0]   LDDW    .D1T1   *A15++,A5:A4      ; |219| 
|| [ A0]   CALL    .S1     _pow              ; |219| 

   [ A0]   LDDW    .D2T2   *B13++,B5:B4      ; |219| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L16}        ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     _t_offset,B13
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           MVKH    .S2     _t_offset,B13
           LDDW    .D2T2   *B13,B7:B6        ; |130| 
           LDDW    .D2T2   *B12,B17:B16      ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A4          ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 
||         ADD     .S2     B7,B17,B31        ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         MVKL    .S2     _t_stop,B4

           ADD     .L2     B31,B5,B7         ; |130| 
||         MVKH    .S2     _t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL38,B3,0      ; |130| 

$C$RL38:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
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

$C$RL39:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16

           MV      .L2X    A10,B4            ; |114| 
||         STDW    .D2T2   B11:B10,*+B12(8)  ; |114| 

           STDW    .D2T1   A5:A4,*B12        ; |130| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVKL    .S2     _input,B4
||         ADD     .L1     4,A12,A12

           LDW     .D1T1   *A12,A3           ; |227| 
||         MVKH    .S2     _input,B4

           LDW     .D2T2   *B4,B4            ; |227| 
           MVK     .S2     0x80,B31
           LDW     .D2T1   *+SP(16),A10      ; |117| 

           STW     .D2T2   B31,*+SP(12)      ; |117| 
||         ZERO    .L1     A15

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 8
           ADD     .L1     A15,A3,A3         ; |227| 

           ADD     .L2X    A15,B4,B4         ; |227| 
||         LDDW    .D1T1   *A3,A5:A4         ; |227| 

           LDDW    .D2T2   *B4,B5:B4         ; |227| 
||         CALL    .S1     _powdp            ; |227| 

           ADDKPC  .S2     $C$RL40,B3,3      ; |227| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |227| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |227| 

$C$RL40:   ; CALL OCCURS {_powdp} {0}        ; |227| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(12),B4       ; |227| 
||         LDW     .D1T1   *A10,A3           ; |227| 

           NOP             4

           SUB     .L1X    B4,1,A0           ; |226| 
||         SUB     .L2     B4,1,B4           ; |226| 
||         ADD     .S1     A15,A3,A3         ; |227| 

   [ A0]   B       .S1     $C$L17            ; |226| 
||         STW     .D2T2   B4,*+SP(12)       ; |227| 
||         MVKL    .S2     _input,B4
||         STDW    .D1T1   A5:A4,*A3         ; |227| 

           MVKH    .S2     _input,B4
|| [ A0]   LDW     .D1T1   *A12,A3           ; |227| 

   [ A0]   LDW     .D2T2   *B4,B4            ; |227| 
           ADD     .L1     8,A15,A15         ; |226| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L17}        ; |226| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MV      .L2     B13,B4            ; |128| 
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           LDDW    .D2T2   *+B12(8),B17:B16  ; |130| 
           MV      .L2     B5,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A4          ; |130| 

           ADD     .L1     A4,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __fltllif         ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 
||         ADD     .S2     B7,B17,B31        ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         MVKL    .S2     _t_stop,B4

           ADD     .L2     B31,B5,B7         ; |130| 
||         MVKH    .S2     _t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL41,B3,0      ; |130| 

$C$RL41:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
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

$C$RL42:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           STDW    .D2T2   B11:B10,*+B12(16) ; |114| 

           ADDAD   .D2     B12,1,B13
||         MV      .L2X    A10,B4            ; |114| 

           STDW    .D2T1   A5:A4,*B13        ; |130| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B5           ; |117| 

           SUBU    .L2     B4,B8,B7:B6       ; |117| 
||         MVKL    .S2     _t_offset,B31

           SUB     .L2     B5,B9,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVKH    .S2     _t_offset,B31

           STDW    .D2T2   B7:B6,*B31        ; |117| 
||         MVKL    .S2     _input,B4

           LDW     .D1T1   *A12,A3           ; |235| 
||         MVKH    .S2     _input,B4

           LDW     .D2T2   *B4,B4            ; |235| 
           MVK     .S2     0x80,B30
           LDW     .D2T1   *+SP(20),A10      ; |117| 

           STW     .D2T2   B30,*+SP(12)      ; |117| 
||         ZERO    .L1     A15

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 8
           ADD     .L1     A15,A3,A3         ; |235| 

           ADD     .L2X    A15,B4,B4         ; |235| 
||         LDDW    .D1T1   *A3,A5:A4         ; |235| 

           LDDW    .D2T2   *B4,B5:B4         ; |235| 
||         CALL    .S1     _powdp_c          ; |235| 

           ADDKPC  .S2     $C$RL43,B3,3      ; |235| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |235| 
||         DADD    .L2X    0,A5:A4,B5:B4     ; |235| 

$C$RL43:   ; CALL OCCURS {_powdp_c} {0}      ; |235| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(12),B4       ; |235| 
||         LDW     .D1T1   *A10,A3           ; |235| 

           NOP             4

           SUB     .L1X    B4,1,A0           ; |234| 
||         SUB     .L2     B4,1,B4           ; |234| 
||         ADD     .S1     A15,A3,A3         ; |235| 

   [ A0]   B       .S1     $C$L18            ; |234| 
||         STW     .D2T2   B4,*+SP(12)       ; |235| 
||         MVKL    .S2     _input,B4
||         STDW    .D1T1   A5:A4,*A3         ; |235| 

           MVKH    .S2     _input,B4
|| [ A0]   LDW     .D1T1   *A12,A3           ; |235| 

   [ A0]   LDW     .D2T2   *B4,B4            ; |235| 
           ADD     .L1     8,A15,A15         ; |234| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L18}        ; |234| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     _t_offset,B4
||         LDDW    .D1T1   *A14,A5:A4        ; |130| 

           MVKH    .S2     _t_offset,B4
           LDDW    .D2T2   *B4,B7:B6         ; |130| 
           MV      .L2     B12,B31           ; |130| 
           LDDW    .D2T2   *+B31(16),B17:B16 ; |130| 
           MV      .L2     B5,B9             ; |128| 
           MV      .L1X    B12,A15           ; |130| 
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2X    B6,A5,B6          ; |130| 
||         CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2     B16,B4,B5:B4      ; |130| 

           SUB     .L2     B9,B6,B6          ; |130| 
||         ADD     .S2     B5,B17,B5         ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         MVKL    .S2     _t_stop,B6

           MVKH    .S2     _t_stop,B6

           STDW    .D2T2   B9:B8,*B6         ; |128| 
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL44,B3,0      ; |130| 

$C$RL44:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 112
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL45:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 

           ADDAD   .D2     B13,1,B12
||         MV      .L2X    A15,B4

           MV      .L2X    A10,B31           ; |114| 
||         STDW    .D2T2   B11:B10,*+B4(32)  ; |114| 

           STDW    .D2T1   A5:A4,*B12        ; |130| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A14        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     _input,A3
           MVKH    .S1     _input,A3
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           MV      .L2X    A3,B16            ; |242| 
||         MVKL    .S1     _t_offset,A3

           MVKH    .S1     _t_offset,A3

           MVKL    .S1     _output,A15
||         MV      .L2X    A12,B9            ; |117| 
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .D2     B8,B5,B5          ; |117| 

           MVKH    .S1     _output,A15
||         LDW     .D2T2   *B9,B4            ; |242| 
||         MV      .L2X    A3,B10            ; |117| 
||         ADD     .S2     B5,B7,B7          ; |117| 

           LDW     .D1T1   *+A15(16),A6      ; |242| 
||         STDW    .D2T2   B7:B6,*B10        ; |117| 
||         MVK     .S2     0x80,B6           ; |242| 

           CALLP   .S2     _powdp_v,B3
||         LDW     .D2T1   *B16,A4           ; |242| 

$C$RL46:   ; CALL OCCURS {_powdp_v} {0}      ; |242| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A9:A8        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 

           MVK     .S1     16,A12
           ADD     .L1X    B12,A12,A12
           MVKL    .S1     _t_stop,A3

           LDDW    .D1T1   *A12,A17:A16      ; |130| 
||         MVKH    .S1     _t_stop,A3

           ADDU    .L1X    B6,A8,A5:A4       ; |130| 

           MV      .L2     B4,B9             ; |128| 
||         MV      .S2X    A3,B4             ; |128| 
||         ADD     .L1X    A5,B7,A3          ; |130| 

           SUBU    .L1X    B8,A4,A7:A6       ; |130| 

           ADD     .L1     A3,A9,A4          ; |130| 
||         EXT     .S1     A7,24,24,A3       ; |130| 

           SUB     .S1X    B9,A4,A6          ; |130| 
||         ADDU    .L1     A16,A6,A5:A4      ; |130| 

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A6,A3,A5          ; |130| 

           CALLP   .S2     __fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL47:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL48:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STDW    .D1T1   A5:A4,*A12        ; |130| 
||         MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 

$C$RL49:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     _fcn_pass,B10
           MVKH    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S2     _fcn_pass,B10

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A15(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL50:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL51:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *A13,B4           ; |69| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL52:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(40),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(44),B4
           NOP             3

   [!B0]   B       .S1     $C$L19            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L19}        ; |72| 
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
   [ A0]   B       .S1     $C$L20            ; |72| 
   [ A0]   CALL    .S1     _print_test_results ; |248| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L20}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |248| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1     A10,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |248| 
||         ADDKPC  .S2     $C$RL53,B3,0      ; |248| 

$C$RL53:   ; CALL OCCURS {_print_test_results} {0}  ; |248| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |249| 

$C$RL54:   ; CALL OCCURS {_printf} {0}       ; |249| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |249| 

$C$RL55:   ; CALL OCCURS {_printf} {0}       ; |249| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |256| 

$C$RL56:   ; CALL OCCURS {_print_profile_results} {0}  ; |256| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |259| 

$C$RL57:   ; CALL OCCURS {_print_memory_results} {0}  ; |259| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADDK    .S2     200,SP            ; |260| 
           LDW     .D2T2   *++SP(8),B3       ; |260| 
           LDDW    .D2T1   *++SP,A13:A12     ; |260| 
           LDDW    .D2T1   *++SP,A15:A14     ; |260| 
           LDDW    .D2T2   *++SP,B11:B10     ; |260| 
           LDDW    .D2T2   *++SP,B13:B12     ; |260| 

           LDW     .D2T1   *++SP(8),A10      ; |260| 
||         RET     .S2     B3                ; |260| 

           LDW     .D2T1   *++SP(8),A11      ; |260| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |260| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"powDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_pow
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_powdp
	.global	_powdp_c
	.global	_powdp_v
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
	.global	__fltllif
	.global	__fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
