;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:38:40 2013                                *
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
	.elfsym	a,SYM_SIZE(804)
a:
	.word	0c123972fh		; a[0] @ 0
	.word	0c2289da2h		; a[1] @ 32
	.word	0428e08cdh		; a[2] @ 64
	.word	041135bd1h		; a[3] @ 96
	.word	0425f6ed4h		; a[4] @ 128
	.word	0c2a64e0bh		; a[5] @ 160
	.word	0c2a1417ch		; a[6] @ 192
	.word	0c144f58bh		; a[7] @ 224
	.word	0c0ecceebh		; a[8] @ 256
	.word	042922475h		; a[9] @ 288
	.word	0c26f31cdh		; a[10] @ 320
	.word	0c2537aefh		; a[11] @ 352
	.word	0c27490b3h		; a[12] @ 384
	.word	0429c7456h		; a[13] @ 416
	.word	0423631adh		; a[14] @ 448
	.word	0411af942h		; a[15] @ 480
	.word	0c1a76a52h		; a[16] @ 512
	.word	0c28e53d3h		; a[17] @ 544
	.word	042b6edf9h		; a[18] @ 576
	.word	0422c6c2ch		; a[19] @ 608
	.word	0c262f247h		; a[20] @ 640
	.word	0c219de6dh		; a[21] @ 672
	.word	0429d9faah		; a[22] @ 704
	.word	0426c9dc8h		; a[23] @ 736
	.word	03f485c12h		; a[24] @ 768
	.word	042737909h		; a[25] @ 800
	.word	0c24a9d59h		; a[26] @ 832
	.word	04127e7aah		; a[27] @ 864
	.word	04289cecdh		; a[28] @ 896
	.word	042512e2ah		; a[29] @ 928
	.word	0c100b9b5h		; a[30] @ 960
	.word	0c0450b4fh		; a[31] @ 992
	.word	040d2a4f9h		; a[32] @ 1024
	.word	0c2ba5245h		; a[33] @ 1056
	.word	04214d8b6h		; a[34] @ 1088
	.word	04275ed94h		; a[35] @ 1120
	.word	0418647ech		; a[36] @ 1152
	.word	0c274e6b8h		; a[37] @ 1184
	.word	04271f2d7h		; a[38] @ 1216
	.word	0c13e5ac8h		; a[39] @ 1248
	.word	04236e3cch		; a[40] @ 1280
	.word	0409a2690h		; a[41] @ 1312
	.word	0c196a7a8h		; a[42] @ 1344
	.word	0c2bb6408h		; a[43] @ 1376
	.word	0c17995dch		; a[44] @ 1408
	.word	0c2b971e5h		; a[45] @ 1440
	.word	0426e2873h		; a[46] @ 1472
	.word	042b659ebh		; a[47] @ 1504
	.word	04287ae63h		; a[48] @ 1536
	.word	0c1115d15h		; a[49] @ 1568
	.word	0c2c0664eh		; a[50] @ 1600
	.word	0c22527bdh		; a[51] @ 1632
	.word	0429181a0h		; a[52] @ 1664
	.word	0c257bb0ah		; a[53] @ 1696
	.word	0427c3cd0h		; a[54] @ 1728
	.word	0428cf43ch		; a[55] @ 1760
	.word	0c29b9ef4h		; a[56] @ 1792
	.word	0401a62d1h		; a[57] @ 1824
	.word	041fff8f0h		; a[58] @ 1856
	.word	0c28b01e6h		; a[59] @ 1888
	.word	042a1ca5bh		; a[60] @ 1920
	.word	0c2707018h		; a[61] @ 1952
	.word	042359b83h		; a[62] @ 1984
	.word	0c1465c05h		; a[63] @ 2016
	.word	0c22344ach		; a[64] @ 2048
	.word	0429b8b7fh		; a[65] @ 2080
	.word	042af1ee0h		; a[66] @ 2112
	.word	042076942h		; a[67] @ 2144
	.word	0c2b5e602h		; a[68] @ 2176
	.word	0429d23f5h		; a[69] @ 2208
	.word	042a4277dh		; a[70] @ 2240
	.word	040aa90f9h		; a[71] @ 2272
	.word	041e08fb2h		; a[72] @ 2304
	.word	0c24042b4h		; a[73] @ 2336
	.word	042c44f8ah		; a[74] @ 2368
	.word	0c19b6bfbh		; a[75] @ 2400
	.word	0c2320857h		; a[76] @ 2432
	.word	04241a965h		; a[77] @ 2464
	.word	0c2524059h		; a[78] @ 2496
	.word	0c1826e8ah		; a[79] @ 2528
	.word	0429b6ac1h		; a[80] @ 2560
	.word	0427d698eh		; a[81] @ 2592
	.word	0c14d8be2h		; a[82] @ 2624
	.word	0c18f84a9h		; a[83] @ 2656
	.word	0c29bfc0bh		; a[84] @ 2688
	.word	0420d5c13h		; a[85] @ 2720
	.word	0c2a79273h		; a[86] @ 2752
	.word	042ae14c6h		; a[87] @ 2784
	.word	0c2213c52h		; a[88] @ 2816
	.word	0c24ddbe3h		; a[89] @ 2848
	.word	0c1ad7acfh		; a[90] @ 2880
	.word	0c23e27d5h		; a[91] @ 2912
	.word	040dba8f6h		; a[92] @ 2944
	.word	0c28e6eb0h		; a[93] @ 2976
	.word	0c21822c1h		; a[94] @ 3008
	.word	0c1b8599ah		; a[95] @ 3040
	.word	041aa7a21h		; a[96] @ 3072
	.word	04234a099h		; a[97] @ 3104
	.word	0c0299e75h		; a[98] @ 3136
	.word	0c2c4c52fh		; a[99] @ 3168
	.word	0c2b68c4ah		; a[100] @ 3200
	.word	0c2add0bdh		; a[101] @ 3232
	.word	0c2223cb6h		; a[102] @ 3264
	.word	0416aa2b5h		; a[103] @ 3296
	.word	0c2abb107h		; a[104] @ 3328
	.word	042b4fd69h		; a[105] @ 3360
	.word	042880945h		; a[106] @ 3392
	.word	0c25e3922h		; a[107] @ 3424
	.word	041e1b12ch		; a[108] @ 3456
	.word	04299dac7h		; a[109] @ 3488
	.word	042a91497h		; a[110] @ 3520
	.word	0427a289bh		; a[111] @ 3552
	.word	0c15b1681h		; a[112] @ 3584
	.word	0c2a0381bh		; a[113] @ 3616
	.word	0c2a7edc3h		; a[114] @ 3648
	.word	042b2771eh		; a[115] @ 3680
	.word	04284a3afh		; a[116] @ 3712
	.word	040f87b6fh		; a[117] @ 3744
	.word	0413ff1b3h		; a[118] @ 3776
	.word	042a8464bh		; a[119] @ 3808
	.word	042b12753h		; a[120] @ 3840
	.word	04291ef3ch		; a[121] @ 3872
	.word	0c20b5c39h		; a[122] @ 3904
	.word	0424b964fh		; a[123] @ 3936
	.word	0419e1b10h		; a[124] @ 3968
	.word	0c1015da8h		; a[125] @ 4000
	.word	0c2aaca1bh		; a[126] @ 4032
	.word	0c272003fh		; a[127] @ 4064
	.word	0c1f17b5dh		; a[128] @ 4096
	.word	0c16f22a6h		; a[129] @ 4128
	.word	0c26eb93ch		; a[130] @ 4160
	.word	042235e49h		; a[131] @ 4192
	.word	0c11abf7bh		; a[132] @ 4224
	.word	04186d17dh		; a[133] @ 4256
	.word	042894c22h		; a[134] @ 4288
	.word	0c0fa3b68h		; a[135] @ 4320
	.word	0429e8bf4h		; a[136] @ 4352
	.word	0c0b8b804h		; a[137] @ 4384
	.word	042841c37h		; a[138] @ 4416
	.word	0c1e2c57ah		; a[139] @ 4448
	.word	0c1b77482h		; a[140] @ 4480
	.word	0c1f8dae6h		; a[141] @ 4512
	.word	0423bad7bh		; a[142] @ 4544
	.word	0c2c20207h		; a[143] @ 4576
	.word	0c20282c0h		; a[144] @ 4608
	.word	0c27da571h		; a[145] @ 4640
	.word	042850aa9h		; a[146] @ 4672
	.word	04257cc37h		; a[147] @ 4704
	.word	0429ed829h		; a[148] @ 4736
	.word	042112aa0h		; a[149] @ 4768
	.word	0c29301f7h		; a[150] @ 4800
	.word	0420e0375h		; a[151] @ 4832
	.word	042a8474fh		; a[152] @ 4864
	.word	0c2472567h		; a[153] @ 4896
	.word	0c200baa4h		; a[154] @ 4928
	.word	03f8be27ch		; a[155] @ 4960
	.word	042c274cah		; a[156] @ 4992
	.word	0c2bd462eh		; a[157] @ 5024
	.word	0429ec31fh		; a[158] @ 5056
	.word	0424a1724h		; a[159] @ 5088
	.word	0c1b2d29dh		; a[160] @ 5120
	.word	0428e6b40h		; a[161] @ 5152
	.word	042b910f9h		; a[162] @ 5184
	.word	041ca23e9h		; a[163] @ 5216
	.word	0c28c24b7h		; a[164] @ 5248
	.word	0c211aab6h		; a[165] @ 5280
	.word	0c1910cedh		; a[166] @ 5312
	.word	0c2b0c949h		; a[167] @ 5344
	.word	042c56d90h		; a[168] @ 5376
	.word	04219b051h		; a[169] @ 5408
	.word	04283fb0bh		; a[170] @ 5440
	.word	0421918cbh		; a[171] @ 5472
	.word	0c1bb6a74h		; a[172] @ 5504
	.word	042c41471h		; a[173] @ 5536
	.word	04104ed34h		; a[174] @ 5568
	.word	0429f28bfh		; a[175] @ 5600
	.word	0c041c80ch		; a[176] @ 5632
	.word	042aff0fch		; a[177] @ 5664
	.word	0415e6cc6h		; a[178] @ 5696
	.word	042512c95h		; a[179] @ 5728
	.word	0c27751a1h		; a[180] @ 5760
	.word	042bedfc3h		; a[181] @ 5792
	.word	04205bc34h		; a[182] @ 5824
	.word	0c2a8b63ah		; a[183] @ 5856
	.word	0c29ca9f7h		; a[184] @ 5888
	.word	0c231b5a5h		; a[185] @ 5920
	.word	0c21fe6cdh		; a[186] @ 5952
	.word	0c1ad3d89h		; a[187] @ 5984
	.word	0414fd369h		; a[188] @ 6016
	.word	04231b27fh		; a[189] @ 6048
	.word	041f67ce2h		; a[190] @ 6080
	.word	042aaa27ch		; a[191] @ 6112
	.word	041ad51d4h		; a[192] @ 6144
	.word	042a0f023h		; a[193] @ 6176
	.word	041ddd93fh		; a[194] @ 6208
	.word	041f17881h		; a[195] @ 6240
	.word	0c2c57cd2h		; a[196] @ 6272
	.word	0c28d4b3dh		; a[197] @ 6304
	.word	04297e956h		; a[198] @ 6336
	.word	0c24f0a04h		; a[199] @ 6368
	.word	0c250e9b0h		; a[200] @ 6400

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\134322 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\134324 
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
;*   Local Frame Size  : 8 Args + 76 Auto + 56 Save = 140 byte                *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |110| 
           STW     .D2T1   A10,*SP--(8)      ; |110| 
           STDW    .D2T2   B13:B12,*SP--     ; |110| 
           STDW    .D2T2   B11:B10,*SP--     ; |110| 
           STDW    .D2T1   A15:A14,*SP--     ; |110| 

           STDW    .D2T1   A13:A12,*SP--     ; |110| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(96)      ; |110| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |118| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     0xc9,B4
||         MVKL    .S1     a,A11

           MVKH    .S1     a,A11

           CALL    .S1     exp2f             ; |127| 
||         MV      .L1     A11,A13
||         MV      .D1X    B4,A10
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A13++,A4         ; |127| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |127| 
$C$RL1:    ; CALL OCCURS {exp2f} {0}         ; |127| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A10,1,A0          ; |126| 
||         SUB     .S1     A10,1,A10         ; |126| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |127| 
   [ A0]   BNOP    .S1     $C$L1,3           ; |126| 

           ADD     .L2     B10,B4,B4         ; |127| 
||         ADD     .S2     4,B10,B10         ; |126| 

   [ A0]   CALL    .S1     exp2f             ; |127| 
||         STW     .D2T1   A4,*B4            ; |127| 
|| [!A0]   MVKL    .S2     output,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |126| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           MVK     .S2     0xc9,B5
||         ZERO    .L2     B10
||         MV      .L1     A11,A12

           MVKH    .S2     output,B4

           ADD     .L2     4,B4,B4
||         MV      .L1X    B5,A10

           STW     .D2T2   B4,*+SP(44)
||         CALL    .S1     exp2sp            ; |130| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |130| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |130| 
$C$RL2:    ; CALL OCCURS {exp2sp} {0}        ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(44),B4       ; |130| 
           SUB     .L1     A10,1,A0          ; |129| 
           SUB     .L1     A10,1,A10         ; |129| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |130| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |129| 

           ADD     .L2     B10,B4,B4         ; |130| 
||         ADD     .S2     4,B10,B10         ; |129| 

   [ A0]   CALL    .S1     exp2sp            ; |130| 
||         STW     .D2T1   A4,*B4            ; |130| 

           ; BRANCHCC OCCURS {$C$L2}         ; |129| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(44),B4
           MVK     .S2     0xc9,B5
           ZERO    .L2     B10
           MV      .L1     A12,A11
           MV      .L1X    B5,A10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(48)
||         CALL    .S1     exp2sp_c          ; |133| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |133| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |133| 
$C$RL3:    ; CALL OCCURS {exp2sp_c} {0}      ; |133| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(48),B4       ; |133| 
||         SUB     .L1     A10,1,A0          ; |132| 
||         SUB     .S1     A10,1,A10         ; |132| 

   [!A0]   LDW     .D2T2   *+SP(48),B7
|| [!A0]   MVKL    .S1     0x3d4cbf5b,A3
|| [!A0]   ZERO    .L2     B5
|| [!A0]   ZERO    .L1     A14
|| [!A0]   MVKL    .S2     0xb95e8083,B6

   [!A0]   MVKH    .S1     0x3d4cbf5b,A3
|| [!A0]   SET     .S2     B5,0x18,0x1d,B17
|| [!A0]   ZERO    .L2     B5

   [!A0]   STW     .D2T1   A3,*+SP(28)
|| [!A0]   MVKL    .S1     0x7f7fffff,A3

   [!A0]   MVKL    .S1     0x3f317218,A5

           LDW     .D2T2   *B4,B4            ; |133| 
|| [!A0]   MVKL    .S1     0x3f318000,A11

   [ A0]   BNOP    .S2     $C$L3,3           ; |132| 
|| [!A0]   MVKL    .S1     0x3b885308,A13

           ADD     .L2     B10,B4,B4         ; |133| 
||         ADD     .S2     4,B10,B10         ; |132| 

   [ A0]   CALL    .S1     exp2sp_c          ; |133| 
||         STW     .D2T1   A4,*B4            ; |133| 
|| [!A0]   ZERO    .L1     A4

           ; BRANCHCC OCCURS {$C$L3}         ; |132| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11

           MVKL    .S2     0x3fb8aa3b,B4
||         MVK     .S1     0x80,A15
||         ZERO    .L2     B13
||         ZERO    .D2     B9

           MVKH    .S1     0x3f317218,A5
||         MVKH    .S2     0xb95e8083,B6
||         ADD     .L2     4,B7,B11
||         MV      .D2X    A12,B8

           MVKH    .S1     0x3f318000,A11
||         MVKH    .S2     0xc2fc0000,B5
||         STW     .D2T1   A5,*+SP(20)
||         MV      .L2X    A15,B22

           MVKH    .S1     0x3b885308,A13
||         MVKH    .S2     0x3fb8aa3b,B4
||         MV      .L1X    B6,A5
||         STW     .D2T2   B6,*+SP(12)
||         MV      .L2X    A5,B26

           MVKH    .S1     0x3e800000,A14
||         MVKH    .S2     0x43000000,B13
||         STW     .D2T2   B4,*+SP(16)
||         MV      .L2X    A11,B23

           MVKH    .S1     0x7f7fffff,A3
||         SET     .S2     B9,0x1e,0x1e,B7
||         STW     .D2T2   B5,*+SP(32)
||         MV      .L2X    A13,B19

           MVKH    .S1     0x30800000,A4
||         STW     .D2T1   A3,*+SP(36)
||         DINT                              ; interrupts off
||         MV      .L2X    A14,B20

           MVK     .S1     0xc9,A6
||         STW     .D2T1   A4,*+SP(24)
||         MV      .L2     B4,B27
||         MV      .S2     B7,B18

           LDW     .D2T1   *+SP(28),A4
||         SUB     .L1     A6,1,A0
||         MV      .L2X    A4,B24
||         ZERO    .S2     B25

           LDW     .D2T2   *B11,B9
||         MV      .L2     B13,B16
||         MV      .S2     B17,B21

           MV      .L2X    A3,B17
||         MV      .L1X    B5,A3

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/exp2sp/exp2sp_d.c
;*      Loop source line                 : 135
;*      Loop opening brace source line   : 135
;*      Loop closing brace source line   : 137
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 88
;*      Unpartitioned Resource Bound     : 7
;*      Partitioned Resource Bound(*)    : 12
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     2        5     
;*      .D units                     0        2     
;*      .M units                     2       12*    
;*      .X cross paths               3        2     
;*      .T address paths             0        2     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0       10     (.L or .S unit)
;*      Addition ops (.LSD)          0        6     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             1        8     
;*      Bound(.L .S .D .LS .LSD)     1        8     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 88 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |*  ***                          |        **      ************    |
;*       1: |*  ***                          |        **      ************    |
;*       2: |*  ***                          |        **      ************    |
;*       3: |*  ***                          |        **      ************    |
;*       4: |*  ***                          |        **      ************    |
;*       5: |*  ***                          |        **      *************   |
;*       6: |*  ***                          |        **      *************   |
;*       7: |*  ***                          |        **      *************   |
;*       8: |*  ***                          |        **      *************   |
;*       9: |*  ***                          |    *   **      *************   |
;*      10: |*  ***                          |    **  **      *************   |
;*      11: |*  ***                          |*   *   **      *************   |
;*      12: |*  ***                          |     *  **      *************   |
;*      13: |*  ***                          |     *  **      *************   |
;*      14: |*  ***                          |     *  **      *************   |
;*      15: |*  ***                          |     *  **      *************   |
;*      16: |*  ***                          |    **  **      *************   |
;*      17: |*  ***                          |     *  **      *************   |
;*      18: |*  ***                          |     *  **      *************   |
;*      19: |*  ***                          |     *  **      *************   |
;*      20: |*  ***                          |    **  **      *************   |
;*      21: |*  ***                          |    **  **      *************   |
;*      22: |*  ***                          |     *  **      **************  |
;*      23: |*  ***                          |     *  **      **************  |
;*      24: |*  ***                          |    **  **      **************  |
;*      25: |*  ***                          |    **  **      **************  |
;*      26: |*  ***                          |     *  **      **************  |
;*      27: |*  ***                          |     *  **      **************  |
;*      28: |*  ***                          |    **  **      **************  |
;*      29: |*  ****                         |        **      **************  |
;*      30: |*  ****                         |        **      **************  |
;*      31: |*  ****                         |    *   **      **************  |
;*      32: |*  ***                          |        **      **************  |
;*      33: |*  ***                          |        **      **************  |
;*      34: |*  ***                          |    *   **      **************  |
;*      35: |*  ***                          |    *   **      **************  |
;*      36: |*  ***                          |    *   **      **************  |
;*      37: |*  ***                          |    *   **      **************  |
;*      38: |*  ***                          |    **  **      **************  |
;*      39: |*  ***                          |    **  **      **************  |
;*      40: |*  ***                          |    *   **      **************  |
;*      41: |*  ***                          |    *   **      **************  |
;*      42: |*  ***                          |    **  **      **************  |
;*      43: |*  ****                         |    *   **      **************  |
;*      44: |*  ****                         |    *   **      **************  |
;*      45: |*  ***                          |    **  **      **************  |
;*      46: |*  ***                          |        **      **************  |
;*      47: |*  ***                          |    *   **      **************  |
;*      48: |*  ***                          |    *   **      **************  |
;*      49: |*  ***                          |    **  **      **************  |
;*      50: |*  ***                          |     *  **      **************  |
;*      51: |*  ***                          |     *  **      **************  |
;*      52: |*  ***                          |     * ***      **************  |
;*      53: |*  ***                          |    ** ***      **************  |
;*      54: |*  ***                          |    ** ***      **************  |
;*      55: |*  ***                          |    ** ***      **************  |
;*      56: |*  ***                          |    ** ***      **************  |
;*      57: |*  ***                          |    ******      **************  |
;*      58: |*  ***                          |    ** ***      **************  |
;*      59: |*  ***                          |    ** ***      **************  |
;*      60: |*  ***                          |    ******      **************  |
;*      61: |*  ***                          |     * ***      **************  |
;*      62: |*  ***                          |     * ***      **************  |
;*      63: |*  ***                          |     * ***      **************  |
;*      64: |*  ***                          |     *****      **************  |
;*      65: |*  ***                          |     ** **      **************  |
;*      66: |*  ***                          |     ** **      **************  |
;*      67: |*  ***                          |     ** **      **************  |
;*      68: |*  ***                          |    *** **      **************  |
;*      69: |*  ***                          |     ** **      **************  |
;*      70: |*  ***                          |     ** **      **************  |
;*      71: |*  ***                          |    *** **      **************  |
;*      72: |*  ***                          |     *  **      **************  |
;*      73: |*  ***                          |     *  **      **************  |
;*      74: |*  ***                          |     *  **      **************  |
;*      75: |*  ***                          |    **  **      **************  |
;*      76: |*  ***                          |        **      **************  |
;*      77: |*  ***                          |        **      **************  |
;*      78: |*  ***                          |        **      **************  |
;*      79: |*  ***                          |    *   **      **************  |
;*      80: |*  ***                          |        **      **************  |
;*      81: |*  ***                          |        **      **************  |
;*      82: |** ***                          |    *   **      **************  |
;*      83: |*  ***                          |    *   **      *************   |
;*      84: |*  ***                          |    *   **      *************   |
;*      85: |*  ***                          |    *   **      *************   |
;*      86: |*  ***                          |*   *   **      ************    |
;*      87: |*  ***                          |    **  **      ************    |
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
;*      Total cycles (est.)         : 0 + min_trip_cnt * 88 = 17688        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A0,1,A0
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C116:
;*   0              LDW     .D2T2   *B8++,B28         ; |55|  ^ 
;*   1              NOP             4
;*   5              MPYSP   .M2     B26,B28,B4        ; |55|  ^ 
;*   6              NOP             3
;*   9              ABSSP   .S2     B4,B5             ; |55|  ^ 
;*  10              CMPLTSP .S2     B5,B24,B0         ; |55|  ^ 
;*  11      [ B0]   MV      .L2     B25,B5            ; |55|  ^ 
;*     ||   [!B0]   MV      .S2     B4,B5             ; |55|  ^ 
;*  12              MPYSP   .M2     B27,B5,B4         ; |55|  ^ 
;*  13              NOP             3
;*  16              SPINT   .L2     B4,B4             ; |55|  ^ 
;*  17              NOP             3
;*  20              INTSP   .L2     B4,B4             ; |55|  ^ 
;*     ||           ADD     .S2     B22,B4,B4         ; |55| 
;*  21              SHL     .S2     B4,23,B29         ; |55| 
;*  22              NOP             2
;*  24              MPYSP   .M2     B23,B4,B4         ; |55|  ^ 
;*  25              MPYSP   .M1X    A5,B4,A6          ; |55| 
;*  26              NOP             2
;*  28              FSUBSP  .L2     B5,B4,B4          ; |55|  ^ 
;*  29              NOP             2
;*  31              FSUBSP  .L2X    B4,A6,B4          ; |55|  ^ 
;*  32              NOP             2
;*  34              MPYSP   .M2     B4,B4,B5          ; |55|  ^ 
;*  35              NOP             3
;*  38              MPYSP   .M2     B19,B5,B5         ; |55|  ^ 
;*  39              MPYSP   .M1X    A4,B5,A6          ; |55| 
;*  40              NOP             2
;*  42              FADDSP  .L2     B20,B5,B5         ; |55|  ^ 
;*  43              NOP             1
;*  44              FADDSP  .L2X    B21,A6,B4         ; |55| 
;*  45              MPYSP   .M2     B4,B5,B5          ; |55|  ^ 
;*  46              NOP             3
;*  49              FSUBSP  .L2     B4,B5,B7          ; |55|  ^ 
;*  50              NOP             2
;*  52              RCPSP   .S2     B7,B4             ; |55|  ^ 
;*  53              MPYSP   .M2     B4,B7,B6          ; |55|  ^ 
;*  54              NOP             3
;*  57              FSUBSP  .L2     B18,B6,B6         ; |55|  ^ 
;*  58              NOP             2
;*  60              MPYSP   .M2     B4,B6,B6          ; |55|  ^ 
;*  61              NOP             3
;*  64              MPYSP   .M2     B6,B7,B4          ; |55|  ^ 
;*  65              NOP             3
;*  68              FSUBSP  .L2     B18,B4,B4         ; |55|  ^ 
;*  69              NOP             2
;*  71              MPYSP   .M2     B6,B4,B4          ; |55|  ^ 
;*  72              NOP             3
;*  75              MPYSP   .M2     B5,B4,B4          ; |55|  ^ 
;*  76              NOP             3
;*  79              FADDSP  .L2     B21,B4,B4         ; |55|  ^ 
;*  80              NOP             1
;*  81              CMPLTSP .S1X    B28,A3,A1         ; |55| 
;*  82      [ A1]   MV      .L2     B25,B4            ; |55| 
;*     ||   [!A1]   MPYSP   .M2     B29,B4,B4         ; |55|  ^ 
;*     ||   [ A0]   BDEC    .S1     $C$C116,A0        ; |135| 
;*  83              NOP             2
;*  85              CMPGTSP .S2     B28,B16,B0        ; |55| 
;*  86      [!B0]   MV      .S2     B4,B5             ; |55|  ^ 
;*     ||   [ B0]   MV      .L2     B17,B5            ; |55| 
;*  87              STW     .D2T2   B5,*B9++          ; |55|  ^ 
;*  88              ; BRANCHCC OCCURS {$C$C116}       ; |135| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 88
           LDW     .D2T2   *B8++,B28         ; |55| <0,0>  ^ 
           NOP             4
           MPYSP   .M2     B26,B28,B4        ; |55| <0,5>  ^ 
           NOP             3
           ABSSP   .S2     B4,B5             ; |55| <0,9>  ^ 
           CMPLTSP .S2     B5,B24,B0         ; |55| <0,10>  ^ 

   [ B0]   MV      .L2     B25,B5            ; |55| <0,11>  ^ 
|| [!B0]   MV      .S2     B4,B5             ; |55| <0,11>  ^ 

           MPYSP   .M2     B27,B5,B4         ; |55| <0,12>  ^ 
           NOP             3
           SPINT   .L2     B4,B4             ; |55| <0,16>  ^ 
           NOP             3

           ADD     .S2     B22,B4,B4         ; |55| <0,20> 
||         INTSP   .L2     B4,B4             ; |55| <0,20>  ^ 

           SHL     .S2     B4,23,B29         ; |55| <0,21> 
           NOP             2
           MPYSP   .M2     B23,B4,B4         ; |55| <0,24>  ^ 
           MPYSP   .M1X    A5,B4,A6          ; |55| <0,25> 
           NOP             2
           FSUBSP  .L2     B5,B4,B4          ; |55| <0,28>  ^ 
           NOP             2
           FSUBSP  .L2X    B4,A6,B4          ; |55| <0,31>  ^ 
           NOP             2
           MPYSP   .M2     B4,B4,B5          ; |55| <0,34>  ^ 
           NOP             3
           MPYSP   .M2     B19,B5,B5         ; |55| <0,38>  ^ 
           MPYSP   .M1X    A4,B5,A6          ; |55| <0,39> 
           NOP             2
           FADDSP  .L2     B20,B5,B5         ; |55| <0,42>  ^ 
           NOP             1
           FADDSP  .L2X    B21,A6,B4         ; |55| <0,44> 
           MPYSP   .M2     B4,B5,B5          ; |55| <0,45>  ^ 
           NOP             3
           FSUBSP  .L2     B4,B5,B7          ; |55| <0,49>  ^ 
           NOP             2
           RCPSP   .S2     B7,B4             ; |55| <0,52>  ^ 
           MPYSP   .M2     B4,B7,B6          ; |55| <0,53>  ^ 
           NOP             3
           FSUBSP  .L2     B18,B6,B6         ; |55| <0,57>  ^ 
           NOP             2
           MPYSP   .M2     B4,B6,B6          ; |55| <0,60>  ^ 
           NOP             3
           MPYSP   .M2     B6,B7,B4          ; |55| <0,64>  ^ 
           NOP             3
           FSUBSP  .L2     B18,B4,B4         ; |55| <0,68>  ^ 
           NOP             2
           MPYSP   .M2     B6,B4,B4          ; |55| <0,71>  ^ 
           NOP             3
           MPYSP   .M2     B5,B4,B4          ; |55| <0,75>  ^ 
           NOP             3
           FADDSP  .L2     B21,B4,B4         ; |55| <0,79>  ^ 
           NOP             1
           CMPLTSP .S1X    B28,A3,A1         ; |55| <0,81> 

   [ A1]   MV      .L2     B25,B4            ; |55| <0,82> 
|| [ A0]   BDEC    .S1     $C$L5,A0          ; |135| <0,82> 
|| [!A1]   MPYSP   .M2     B29,B4,B4         ; |55| <0,82>  ^ 

           NOP             2
           CMPGTSP .S2     B28,B16,B0        ; |55| <0,85> 

   [ B0]   MV      .L2     B17,B5            ; |55| <0,86> 
|| [!B0]   MV      .S2     B4,B5             ; |55| <0,86>  ^ 

           STW     .D2T2   B5,*B9++          ; |55| <0,87>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           STW     .D2T1   A4,*+SP(28)
           STW     .D2T2   B26,*+SP(20)
           STW     .D2T2   B24,*+SP(24)

           MV      .L1X    B19,A13
||         STW     .D2T2   B17,*+SP(36)

           MVKL    .S2     output,B4
||         MV      .L1X    B20,A14
||         STW     .D2T1   A5,*+SP(12)

           MVKH    .S2     output,B4
||         MV      .L2     B16,B13
||         MV      .L1X    B22,A15
||         STW     .D2T1   A3,*+SP(32)

           MV      .L2     B18,B12
||         MV      .L1X    B23,A11
||         STW     .D2T2   B27,*+SP(16)
||         RINT                              ; interrupts on

           CALLP   .S2     exp2sp_v,B3
||         LDW     .D2T2   *+B4(16),B4       ; |138| 
||         MV      .L1     A12,A4            ; |138| 
||         MVK     .S1     0xc9,A6           ; |138| 
||         MV      .L2     B21,B10
||         MV      .D1X    B25,A10

$C$RL4:    ; CALL OCCURS {exp2sp_v} {0}      ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 56
           MVKL    .S2     output,B4
           MVKL    .S2     output,B5
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     output,B4
           MVKH    .S2     output,B5
           MVKH    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B4(4),B4        ; |66| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     output,B4
           MVKL    .S2     fcn_pass,B6
           MVKH    .S2     output,B4

           LDW     .D2T2   *B4,B5            ; |67| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B4(8),B4        ; |67| 
||         MV      .L1X    B5,A4             ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     output,B5
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     output,B5
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L2     B5,B4             ; |127| 
||         STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B4(12),B4       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     output,B4
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     output,B4

           ADD     .L1X    4,B11,A3
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           STW     .D2T1   A3,*+SP(52)
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4

           ADD     .L2     4,B4,B4
||         MVKL    .S2     fcn_pass,B5

           LDW     .D2T2   *B4,B0            ; |72| 
           MVKH    .S2     fcn_pass,B5
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           STW     .D2T2   B4,*+SP(56)
           ADD     .L2     8,B5,B4

   [!B0]   MVKL    .S1     all_pass,A4
|| [!B0]   B       .S2     $C$L7             ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [!B0]   ZERO    .L1     A3                ; |72| 

   [!B0]   CALL    .S2     print_test_results ; |142| 
|| [!B0]   MVKH    .S1     all_pass,A4
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

           STW     .D2T2   B4,*+SP(60)       ; |69| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             2
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
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   ZERO    .L1     A3                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |142| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x1,A4            ; |142| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |142| 

$C$RL9:    ; CALL OCCURS {print_test_results} {0}  ; |142| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           MVKL    .S2     a_sc,B4

           MVKL    .S2     0x7f7fffff,B31
||         MVK     .L2     -1,B9             ; |155| 
||         MVK     .D2     0x7,B29

           STW     .D2T2   B11,*+SP(64)
||         MVKH    .S2     a_sc,B4
||         ZERO    .L2     B7
||         ZERO    .L1     A5

           STW     .D2T2   B29,*+SP(40)      ; |154| 
||         MV      .L2     B4,B8             ; |150| 
||         MVKH    .S1     0xbf800000,A5
||         MV      .S2X    A10,B6            ; |150| 
||         ZERO    .L1     A4

           STW     .D2T2   B9,*+B8(24)       ; |155| 
||         MV      .L2     B8,B30            ; |152| 
||         MVKH    .S2     0x80000000,B7
||         SET     .S1     A4,0x17,0x1d,A4

           STDW    .D2T1   A5:A4,*+B30(16)   ; |154| 
||         MVKH    .S2     0x7f7fffff,B31
||         ZERO    .L2     B5

           STDW    .D2T2   B7:B6,*B30        ; |150| 
||         ADD     .L2     1,B31,B4
||         MV      .L1X    B4,A12            ; |150| 
||         MVKH    .S2     0xff800000,B5

           STDW    .D2T2   B5:B4,*+B8(8)     ; |152| 
           LDW     .D1T1   *A12,A3           ; |157| 
           CALL    .S1     exp2              ; |157| 
           ZERO    .L2     B11
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
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL10,B3,1      ; |157| 
           SPDP    .S1     A3,A5:A4          ; |157| 
           NOP             1
$C$RL10:   ; CALL OCCURS {exp2} {0}          ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |157| 
           DPSP    .L1     A5:A4,A3          ; |157| 
           NOP             3
           ADD     .L2     B11,B4,B4         ; |157| 
           STW     .D2T1   A3,*B4            ; |157| 

           CALLP   .S2     exp2sp,B3
||         LDW     .D1T1   *A12,A4           ; |158| 

$C$RL11:   ; CALL OCCURS {exp2sp} {0}        ; |158| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |158| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |158| 
           STW     .D2T1   A4,*B4            ; |158| 

           CALLP   .S2     exp2sp_c,B3
||         LDW     .D1T1   *A12,A4           ; |159| 

$C$RL12:   ; CALL OCCURS {exp2sp_c} {0}      ; |159| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 106
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |159| 
           LDW     .D2T1   *+SP(20),A3
           LDW     .D2T1   *+SP(24),A31      ; |87| 
           LDW     .D2T1   *+SP(16),A30      ; |88| 
           LDW     .D2T2   *+SP(12),B31
           ADD     .L2     B11,B4,B4         ; |159| 
           STW     .D2T1   A4,*B4            ; |159| 
           LDW     .D1T1   *A12++,A6         ; |160| 
           LDW     .D2T2   *+SP(28),B30      ; |99| 
           LDW     .D2T2   *+SP(64),B29
           LDW     .D2T1   *+SP(32),A29
           NOP             1
           MPYSP   .M1     A3,A6,A4          ; |84| 
           CMPGTSP .S2X    A6,B13,B0         ; |109| 
           NOP             2
           ABSSP   .S1     A4,A5             ; |87| 
           CMPLTSP .S1     A5,A31,A0         ; |87| 
   [ A0]   MV      .L1     A10,A4            ; |88| 
           MPYSP   .M1     A30,A4,A3         ; |99| 
           CMPLTSP .S1     A6,A29,A0         ; |104| 
           NOP             2
           SPINT   .L1     A3,A3             ; |99| 
           NOP             3
           INTSP   .L1     A3,A5             ; |99| 
           ADD     .L1     A15,A3,A3         ; |101| 
           SHL     .S1     A3,23,A3          ; |101| 
           NOP             1
           MPYSP   .M1     A11,A5,A7         ; |99| 
           MPYSP   .M2X    B31,A5,B4         ; |99| 
           NOP             2
           FSUBSP  .L1     A4,A7,A4          ; |99| 
           NOP             2
           FSUBSP  .L1X    A4,B4,A4          ; |99| 
           NOP             2
           MPYSP   .M1     A4,A4,A5          ; |99| 
           NOP             3
           MPYSP   .M1     A13,A5,A7         ; |99| 
           MPYSP   .M2X    B30,A5,B4         ; |99| 
           NOP             2
           FADDSP  .L1     A14,A7,A7         ; |99| 
           FADDSP  .L2     B10,B4,B4         ; |99| 
           NOP             1
           MPYSP   .M1     A4,A7,A4          ; |99| 
           NOP             4
           FSUBSP  .L2X    B4,A4,B4          ; |99| 
           NOP             2
           RCPSP   .S2     B4,B5             ; |55| 
           MPYSP   .M2     B4,B5,B6          ; |55| 
           NOP             3
           FSUBSP  .L2     B12,B6,B6         ; |55| 
           NOP             2
           MPYSP   .M2     B5,B6,B5          ; |55| 
           NOP             3
           MPYSP   .M2     B4,B5,B4          ; |55| 
           NOP             3
           FSUBSP  .L2     B12,B4,B4         ; |55| 
           NOP             2
           MPYSP   .M2     B5,B4,B4          ; |55| 
           NOP             3
           MPYSP   .M2X    A4,B4,B4          ; |55| 
           NOP             3

           FADDSP  .L2     B10,B4,B5         ; |101| 
||         LDW     .D2T2   *B29,B4           ; |160| 

           NOP             3
           MPYSP   .M1X    A3,B5,A4          ; |101| 

           ADD     .L2     B11,B4,B5         ; |160| 
||         LDW     .D2T2   *+SP(40),B4       ; |110| 

           ADD     .L2     4,B11,B11         ; |156| 
           NOP             1

   [ A0]   MV      .L1     A10,A4            ; |105| 
|| [ B0]   LDW     .D2T1   *+SP(36),A4       ; |105| 

           NOP             1

           SUB     .L1X    B4,1,A0           ; |156| 
||         SUB     .L2     B4,1,B4           ; |156| 

   [ A0]   B       .S1     $C$L8             ; |156| 
|| [!A0]   MVKL    .S2     output,B11
||         STW     .D2T2   B4,*+SP(40)       ; |160| 

   [!A0]   MVKH    .S2     output,B11

   [!A0]   CALL    .S1     exp2sp_v          ; |162| 
||         STW     .D2T1   A4,*B5            ; |160| 

   [!A0]   LDW     .D2T2   *+B11(16),B4      ; |162| 
|| [ A0]   LDW     .D1T1   *A12,A3           ; |157| 

   [ A0]   CALL    .S1     exp2              ; |157| 
   [!A0]   MVKL    .S1     a_sc,A4
           ; BRANCHCC OCCURS {$C$L8}         ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVK     .L1     0x7,A6            ; |162| 

           ADDKPC  .S2     $C$RL13,B3,0      ; |162| 
||         MVKH    .S1     a_sc,A4

$C$RL13:   ; CALL OCCURS {exp2sp_v} {0}      ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B11,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |68| 

           LDW     .D2T1   *+SP(52),A3       ; |68| 
||         MVKL    .S2     fcn_pass,B4

           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           MV      .L2     B11,B5            ; |68| 
||         STW     .D2T1   A3,*+SP(64)       ; |68| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(56),A3       ; |69| 
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           NOP             1
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A3,*+SP(68)       ; |69| 
           LDW     .D2T1   *+SP(60),A3
           NOP             2

   [!A0]   B       .S1     $C$L9             ; |72| 
|| [!A0]   ZERO    .L1     A4                ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |166| 

   [ A0]   MV      .L2X    A3,B4
||         STW     .D2T1   A3,*+SP(72)       ; |72| 
|| [!A0]   MVKL    .S1     all_pass,A3

   [ A0]   LDW     .D2T2   *B4,B0            ; |72| 
   [!A0]   MVKH    .S1     all_pass,A3
   [ A0]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
           NOP             2
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   ZERO    .L1     A4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |166| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |166| 
||         ADDKPC  .S2     $C$RL18,B3,0      ; |166| 

$C$RL18:   ; CALL OCCURS {print_test_results} {0}  ; |166| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           MVKL    .S1     a_ext,A3
           MVKH    .S1     a_ext,A3

           ZERO    .L1     A4
||         MVK     .S2     0xed,B31

           MV      .L2X    A3,B4             ; |169| 
||         SET     .S1     A4,0x17,0x17,A4
||         STW     .D2T2   B31,*+SP(40)      ; |169| 

           STW     .D2T1   A4,*B4            ; |169| 
||         MV      .L1     A3,A12            ; |169| 

           LDW     .D1T1   *A12,A3           ; |171| 
           CALL    .S1     exp2              ; |171| 
           ZERO    .L2     B11
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |171| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL19,B3,0      ; |171| 
$C$RL19:   ; CALL OCCURS {exp2} {0}          ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |171| 
           DPSP    .L1     A5:A4,A3          ; |171| 
           ZERO    .L2     B31
           MVKH    .S2     0xc3800000,B31
           NOP             1
           ADD     .L2     B11,B4,B4         ; |171| 
           STW     .D2T1   A3,*B4            ; |171| 
           LDW     .D1T1   *A12,A4           ; |172| 
           NOP             4
           CMPGTSP .S2X    A4,B31,B0         ; |172| 
   [!B0]   B       .S1     $C$L11            ; |172| 
   [ B0]   CALL    .S1     exp2sp            ; |172| 
   [!B0]   CALL    .S1     exp2              ; |172| 
   [!B0]   SPDP    .S1     A4,A5:A4          ; |172| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L11}        ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL20,B3,0      ; |172| 
$C$RL20:   ; CALL OCCURS {exp2sp} {0}        ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8

           SPDP    .S1     A4,A5:A4          ; |172| 
||         MVKL    .S2     output,B4

           MVKH    .S2     output,B4

           BNOP    .S1     $C$L12,4          ; |172| 
||         DPSP    .L1     A5:A4,A3          ; |172| 
||         LDW     .D2T2   *+B4(4),B4        ; |172| 

           MV      .L2X    A3,B5             ; |172| 
||         ADD     .S2     B11,B4,B4         ; |172| 

           ; BRANCH OCCURS {$C$L12}          ; |172| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL21,B3,1      ; |172| 
$C$RL21:   ; CALL OCCURS {exp2} {0}          ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4

           LDW     .D2T2   *+B4(4),B4        ; |172| 
||         DPSP    .L1     A5:A4,A3          ; |172| 

           NOP             4

           ADD     .L2     B11,B4,B4         ; |172| 
||         MV      .S2X    A3,B5             ; |172| 

;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     exp2sp_c          ; |173| 
||         STW     .D2T2   B5,*B4            ; |172| 

           LDW     .D1T1   *A12,A4           ; |173| 
           ADDKPC  .S2     $C$RL22,B3,3      ; |173| 
$C$RL22:   ; CALL OCCURS {exp2sp_c} {0}      ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 127
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |173| 
           LDW     .D2T1   *+SP(20),A3
           LDW     .D2T1   *+SP(24),A31      ; |87| 
           LDW     .D2T1   *+SP(16),A30      ; |88| 
           LDW     .D2T2   *+SP(12),B31
           ADD     .L2     B11,B4,B4         ; |173| 
           STW     .D2T1   A4,*B4            ; |173| 
           LDW     .D1T1   *A12,A6           ; |174| 
           LDW     .D2T2   *+SP(28),B30      ; |99| 
           MVKL    .S2     output+12,B29
           LDW     .D2T2   *+SP(32),B28
           MVKH    .S2     output+12,B29
           MPYSP   .M1     A3,A6,A4          ; |84| 
           CMPGTSP .S1X    A6,B13,A2         ; |109| 
           NOP             2
           ABSSP   .S1     A4,A5             ; |87| 
           CMPLTSP .S1     A5,A31,A0         ; |87| 
   [ A0]   MV      .L1     A10,A4            ; |88| 
           MPYSP   .M1     A30,A4,A3         ; |99| 
           CMPLTSP .S2X    A6,B28,B0         ; |104| 
           NOP             2
           SPINT   .L1     A3,A7             ; |99| 
           NOP             3
           INTSP   .L1     A7,A3             ; |99| 
           ADD     .L1     A15,A7,A29        ; |101| 
           NOP             2
           MPYSP   .M1     A11,A3,A5         ; |99| 
           MPYSP   .M2X    B31,A3,B4         ; |99| 
           NOP             2
           FSUBSP  .L1     A4,A5,A3          ; |99| 
           NOP             2
           FSUBSP  .L1X    A3,B4,A4          ; |99| 
           NOP             2
           MPYSP   .M1     A4,A4,A5          ; |99| 
           NOP             3
           MPYSP   .M1     A13,A5,A3         ; |99| 
           MPYSP   .M2X    B30,A5,B4         ; |99| 
           MVKL    .S1     0xc000cccc,A5
           MVKH    .S1     0xc000cccc,A5
           FADDSP  .L1     A14,A3,A3         ; |99| 
           FADDSP  .L2     B10,B4,B4         ; |99| 
           NOP             1
           MPYSP   .M1     A4,A3,A3          ; |99| 
           NOP             4
           FSUBSP  .L2X    B4,A3,B4          ; |99| 
           NOP             2
           RCPSP   .S2     B4,B5             ; |55| 
           MPYSP   .M2     B4,B5,B6          ; |55| 
           NOP             3
           FSUBSP  .L2     B12,B6,B6         ; |55| 
           NOP             2
           MPYSP   .M2     B5,B6,B5          ; |55| 
           NOP             3
           MPYSP   .M2     B4,B5,B4          ; |55| 
           NOP             3
           FSUBSP  .L2     B12,B4,B4         ; |55| 
           NOP             2
           MPYSP   .M2     B5,B4,B4          ; |55| 
           LDW     .D2T2   *B29,B5           ; |174| 
           NOP             2
           MPYSP   .M2X    A3,B4,B4          ; |55| 
           SHL     .S1     A29,23,A3         ; |101| 
           ADD     .L2     B11,B5,B27        ; |174| 
           ADD     .L2     4,B11,B11         ; |170| 
           FADDSP  .L2     B10,B4,B4         ; |101| 
           NOP             3
           MPYSP   .M1X    A3,B4,A4          ; |101| 
           NOP             3

   [ B0]   MV      .L1     A10,A4            ; |105| 
|| [ A2]   LDW     .D2T1   *+SP(36),A4       ; |105| 

           NOP             4
           STW     .D2T1   A4,*B27           ; |174| 
           LDW     .D1T2   *A12,B4           ; |175| 
           MVKL    .S1     0xcccccccd,A4
           MVKH    .S1     0xcccccccd,A4
           NOP             2
           MPYSPDP .M2X    B4,A5:A4,B5:B4    ; |175| 
           NOP             6

           DPSP    .L2     B5:B4,B5          ; |175| 
||         LDW     .D2T2   *+SP(40),B4

           NOP             3
           STW     .D1T2   B5,*++A12         ; |175| 

           SUB     .L1X    B4,1,A0           ; |170| 
||         SUB     .L2     B4,1,B4           ; |170| 

   [ A0]   B       .S1     $C$L10            ; |170| 
|| [ A0]   LDW     .D1T1   *A12,A3           ; |171| 
|| [!A0]   MVKL    .S2     output,B11
||         STW     .D2T2   B4,*+SP(40)       ; |175| 

   [ A0]   CALL    .S1     exp2              ; |171| 
   [!A0]   MVKH    .S2     output,B11
   [!A0]   LDW     .D2T2   *+B11(16),B4      ; |177| 
   [!A0]   CALL    .S1     exp2sp_v          ; |177| 
           SPDP    .S1     A3,A5:A4          ; |171| 
           ; BRANCHCC OCCURS {$C$L10}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL23,B3,0      ; |177| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           MVK     .S1     0xed,A6           ; |177| 
$C$RL23:   ; CALL OCCURS {exp2sp_v} {0}      ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T2   *B11,B5           ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7
           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MV      .L1X    B5,A4             ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .D1     0x1,A8            ; |66| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6

           LDW     .D2T2   *B11,B5           ; |67| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MV      .L1X    B5,A4             ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B11,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B5

           LDW     .D2T1   *+SP(64),A3       ; |68| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L2     B11,B4            ; |68| 
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(68),A3       ; |69| 
           LDW     .D2T2   *+SP(72),B5
           MVKL    .S2     fcn_pass,B4
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L13            ; |72| 
|| [ A0]   LDW     .D2T2   *B5,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |181| 
   [ A0]   ADD     .L2     4,B5,B4
   [!A0]   ZERO    .L1     A3                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A4
   [!A0]   MVKH    .S1     all_pass,A4
           ; BRANCHCC OCCURS {$C$L13}        ; |72| 
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
||         MVK     .S1     0x1,A3            ; |72| 

   [!A0]   ZERO    .L1     A3                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |181| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |181| 
||         ADDKPC  .S2     $C$RL28,B3,0      ; |181| 

$C$RL28:   ; CALL OCCURS {print_test_results} {0}  ; |181| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           ZERO    .L2     B5                ; |114| 

           ZERO    .L2     B4                ; |114| 
||         STW     .D2T2   B5,*+SP(80)       ; |114| 

           STW     .D2T2   B4,*+SP(84)       ; |114| 
           LDDW    .D2T2   *+SP(80),B5:B4    ; |114| 
           MVKL    .S2     cycle_counts+24,B7
           MVKH    .S2     cycle_counts+24,B7
           ZERO    .L2     B6                ; |114| 
           NOP             1

           STDW    .D2T2   B5:B4,*B7         ; |114| 
||         MVC     .S2     B6,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           CALL    .S1     gimme_random      ; |191| 
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         MVKL    .S1     t_offset,A4
||         SUB     .L2     B8,B7,B31         ; |117| 

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A4
||         ZERO    .L1     A12

           STDW    .D1T2   B5:B4,*A4         ; |117| 
||         ZERO    .L2     B4
||         MVKH    .S1     0x43480000,A12

           MVKH    .S2     0xc2c80000,B4
||         MV      .L1     A12,A4            ; |191| 
||         ZERO    .L2     B11               ; |189| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL29,B3,0      ; |191| 
$C$RL29:   ; CALL OCCURS {gimme_random} {0}  ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 119
           MVKL    .S2     input,B4
           MVKH    .S2     input,B4
           LDW     .D2T2   *B4,B4            ; |191| 
           NOP             4

           STW     .D2T1   A4,*+B4[B11]      ; |191| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B7           ; |122| 
           LDW     .D2T1   *+SP(20),A3       ; |122| 
           LDW     .D2T1   *+SP(24),A31      ; |87| 
           LDW     .D2T1   *+SP(16),A30      ; |88| 
           LDW     .D2T2   *+SP(12),B4
           LDW     .D2T2   *+SP(28),B31      ; |99| 
           MPYSP   .M1     A3,A4,A5          ; |84| 
           MVKL    .S2     output+12,B30
           MV      .L2X    A4,B29            ; |195| 
           CMPGTSP .S2     B29,B13,B0        ; |109| 
           ABSSP   .S1     A5,A6             ; |87| 
           CMPLTSP .S1     A6,A31,A0         ; |87| 
   [ A0]   MV      .L1     A10,A5            ; |88| 
           MPYSP   .M1     A30,A5,A3         ; |99| 
           LDW     .D2T2   *+SP(32),B27      ; |195| 
           MVKH    .S2     output+12,B30
           LDW     .D2T2   *B30,B28          ; |195| 
           SPINT   .L1     A3,A6             ; |99| 
           MVKL    .S1     t_start,A28
           CMPLTSP .S2     B29,B27,B1        ; |104| 
           MVKH    .S1     t_start,A28
           INTSP   .L1     A6,A3             ; |99| 
           ADD     .L1     A15,A6,A29        ; |101| 
           SHL     .S1     A29,23,A4         ; |101| 
           STDW    .D1T2   B7:B6,*A28
           MPYSP   .M1     A11,A3,A7         ; |99| 
           MPYSP   .M2X    B4,A3,B4          ; |99| 
           NOP             2
           FSUBSP  .L1     A5,A7,A3          ; |99| 
           NOP             2
           FSUBSP  .L1X    A3,B4,A3          ; |99| 
           NOP             2
           MPYSP   .M1     A3,A3,A5          ; |99| 
           NOP             3
           MPYSP   .M1     A13,A5,A7         ; |99| 
           MPYSP   .M2X    B31,A5,B4         ; |99| 
           NOP             2
           FADDSP  .L1     A14,A7,A7         ; |99| 
           FADDSP  .L2     B10,B4,B4         ; |99| 
           NOP             1
           MPYSP   .M1     A3,A7,A3          ; |99| 
           NOP             4
           FSUBSP  .L2X    B4,A3,B4          ; |99| 
           NOP             2
           RCPSP   .S2     B4,B5             ; |55| 
           MPYSP   .M2     B4,B5,B8          ; |55| 
           NOP             3
           FSUBSP  .L2     B12,B8,B8         ; |55| 
           NOP             2
           MPYSP   .M2     B5,B8,B5          ; |55| 
           NOP             3
           MPYSP   .M2     B4,B5,B4          ; |55| 
           NOP             3
           FSUBSP  .L2     B12,B4,B4         ; |55| 
           NOP             2
           MPYSP   .M2     B5,B4,B4          ; |55| 
           NOP             3
           MPYSP   .M2X    A3,B4,B5          ; |55| 
           NOP             3
           FADDSP  .L2     B10,B5,B5         ; |101| 
           NOP             3
           MPYSP   .M1X    A4,B5,A3          ; |101| 
           NOP             3

   [ B1]   MV      .L1     A10,A3            ; |105| 
|| [ B0]   LDW     .D2T1   *+SP(36),A3       ; |105| 

           NOP             4

           STW     .D2T1   A3,*+B28[B11]     ; |195| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B9           ; |128| 

           MVKL    .S1     t_offset,A3
||         ADD     .L2     1,B11,B11         ; |189| 
||         MVK     .S2     128,B26           ; |189| 

           MVKH    .S1     t_offset,A3
||         CMPLT   .L2     B11,B26,B0        ; |189| 

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     cycle_counts+24,A27

           MVKH    .S1     cycle_counts+24,A27

           LDDW    .D1T1   *A27,A5:A4        ; |130| 
||         MVKL    .S1     cycle_counts+24,A3

           MVKL    .S1     t_stop,A26
           MVKH    .S1     cycle_counts+24,A3

           ADDU    .L2X    A6,B6,B5:B4       ; |130| 
||         MVKH    .S1     t_stop,A26

           ADD     .S2X    B5,A7,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 
||         STDW    .D1T2   B9:B8,*A26        ; |128| 

           ADD     .D2     B6,B7,B6          ; |130| 
|| [ B0]   B       .S1     $C$L14            ; |189| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A4,B4,B5:B4       ; |130| 

   [ B0]   CALL    .S1     gimme_random      ; |191| 
||         SUB     .L2     B9,B6,B6          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
||         ADD     .L1X    B5,A5,A5          ; |130| 

           MV      .L1X    B4,A4             ; |130| 
|| [ B0]   ZERO    .L2     B4

           ADD     .L1X    A5,B6,A5          ; |130| 
|| [ B0]   MVKH    .S2     0xc2c80000,B4

   [!B0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T1   A5:A4,*A3         ; |130| 
|| [ B0]   MV      .L1     A12,A4            ; |191| 

           ; BRANCHCC OCCURS {$C$L14}        ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A3,A5:A4         ; |135| 
           ADDKPC  .S2     $C$RL30,B3,3      ; |135| 
$C$RL30:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A11
           SET     .S1     A11,0x1a,0x1d,A11
           MPYSP   .M1     A11,A4,A3         ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           ZERO    .L1     A12               ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           LDDW    .D2T2   *+SP(80),B5:B4
           MVKL    .S2     cycle_counts+24,B6
           MVKH    .S2     cycle_counts+24,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 

           SUBAW   .D2     B6,6,B10
||         MV      .L2X    A12,B31           ; |114| 

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A10
           MVKH    .S1     t_start,A10

           STDW    .D1T2   B7:B6,*A10        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S2     t_offset,B11

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 
||         MVKH    .S2     t_offset,B11
||         MVKL    .S1     input,A14

           STDW    .D2T2   B5:B4,*B11        ; |117| 
||         MVKH    .S1     input,A14

           LDW     .D1T1   *A14,A3           ; |203| 
           MVK     .S1     128,A15           ; |202| 
           NOP             2
           CALL    .S1     exp2f             ; |203| 
           LDW     .D1T1   *+A3[A12],A4      ; |203| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL32,B3,3      ; |203| 
$C$RL32:   ; CALL OCCURS {exp2f} {0}         ; |203| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A3            ; |203| 
           NOP             4

           STW     .D1T1   A4,*+A3[A12]      ; |203| 
||         ADD     .L1     1,A12,A12         ; |202| 

           CMPLT   .L1     A12,A15,A0        ; |202| 

   [ A0]   BNOP    .S1     $C$L15,3          ; |202| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |203| 

   [ A0]   CALL    .S1     exp2f             ; |203| 
   [ A0]   LDW     .D1T1   *+A3[A12],A4      ; |203| 
           ; BRANCHCC OCCURS {$C$L15}        ; |202| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B9:B8        ; |130| 

           MVKL    .S2     t_stop,B12
           MV      .L2     B4,B7             ; |128| 
           MVKH    .S2     t_stop,B12
           NOP             1
           ADDU    .L1X    B8,A6,A5:A4       ; |130| 

           ADD     .L1X    A5,B9,A3          ; |130| 
||         LDDW    .D2T2   *B10,B9:B8        ; |130| 

           ADD     .L1     A3,A7,A3          ; |130| 
||         SUBU    .L2X    B6,A4,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B7,A3,B31         ; |130| 
           CALL    .S1     __c6xabi_fltllif  ; |130| 

           ADDU    .L2     B8,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B8        ; |130| 

           ADD     .L2     B5,B9,B5          ; |130| 
           ADD     .L2     B5,B8,B5          ; |130| 
           STDW    .D2T2   B7:B6,*B12        ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL33,B3,0      ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           LDDW    .D2T2   *+SP(80),B5:B4    ; |130| 
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A10        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
           STDW    .D2T2   B5:B4,*B11        ; |117| 
           LDW     .D1T1   *A14,A3           ; |211| 
           ZERO    .L1     A11               ; |210| 
           LDW     .D2T1   *+SP(44),A12      ; |117| 
           NOP             1
           CALL    .S1     exp2sp            ; |211| 
           LDW     .D1T1   *+A3[A11],A4      ; |211| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL35,B3,3      ; |211| 
$C$RL35:   ; CALL OCCURS {exp2sp} {0}        ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           LDW     .D1T1   *A12,A3           ; |211| 
           NOP             4

           STW     .D1T1   A4,*+A3[A11]      ; |211| 
||         ADD     .L1     1,A11,A11         ; |210| 

           CMPLT   .L1     A11,A15,A0        ; |210| 

   [ A0]   BNOP    .S1     $C$L16,3          ; |210| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |211| 

   [ A0]   CALL    .S1     exp2sp            ; |211| 
   [ A0]   LDW     .D1T1   *+A3[A11],A4      ; |211| 
           ; BRANCHCC OCCURS {$C$L16}        ; |210| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           LDDW    .D2T2   *+B10(8),B17:B16  ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
           ADD     .L1X    A5,B7,A3          ; |130| 

           ADD     .L1     A3,A7,A3          ; |130| 
||         SUBU    .L2X    B8,A4,B5:B4       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B5,24,24,B6       ; |130| 
||         ADDU    .L2     B16,B4,B5:B4      ; |130| 

           SUB     .L2X    B9,A3,B7          ; |130| 
||         ADD     .S2     B5,B17,B5         ; |130| 

           ADD     .L2     B7,B6,B6          ; |130| 

           ADD     .L2     B5,B6,B5          ; |130| 
||         MV      .S2     B12,B6            ; |130| 

           STDW    .D2T2   B9:B8,*B6         ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL36,B3,0      ; |130| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           LDDW    .D2T2   *+SP(80),B5:B4
           ADDAD   .D2     B10,1,B12
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A10        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B5       ; |117| 
||         SUB     .L2     B6,B9,B6          ; |117| 

           ADD     .L2     B6,B5,B5          ; |117| 
           STDW    .D2T2   B5:B4,*B11        ; |117| 
           LDW     .D1T1   *A14,A3           ; |219| 
           ZERO    .L1     A11               ; |218| 
           LDW     .D2T1   *+SP(48),A12      ; |117| 
           NOP             1
           CALL    .S1     exp2sp_c          ; |219| 
           LDW     .D1T1   *+A3[A11],A4      ; |219| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 4
           ADDKPC  .S2     $C$RL38,B3,3      ; |219| 
$C$RL38:   ; CALL OCCURS {exp2sp_c} {0}      ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 13
           LDW     .D1T1   *A12,A3           ; |219| 
           NOP             4

           STW     .D1T1   A4,*+A3[A11]      ; |219| 
||         ADD     .L1     1,A11,A11         ; |218| 

           CMPLT   .L1     A11,A15,A0        ; |218| 

   [ A0]   BNOP    .S1     $C$L17,3          ; |218| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |219| 

   [ A0]   CALL    .S1     exp2sp_c          ; |219| 
   [ A0]   LDW     .D1T1   *+A3[A11],A4      ; |219| 
           ; BRANCHCC OCCURS {$C$L17}        ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B7           ; |128| 

           LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B11,B5:B4        ; |130| 

           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           NOP             3
           ADDU    .L2X    B4,A4,B9:B8       ; |130| 

           ADD     .S2     B9,B5,B8          ; |130| 
||         SUBU    .L2     B6,B8,B5:B4       ; |130| 

           ADD     .L2X    B8,A5,B8          ; |130| 
||         CALL    .S1     __c6xabi_fltllif  ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .S2     B7,B8,B4          ; |130| 
||         ADDU    .L2     B16,B4,B9:B8      ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B9,B17,B4         ; |130| 

           ADD     .L2     B4,B5,B9          ; |130| 
||         MVKL    .S2     t_stop,B4

           MVKH    .S2     t_stop,B4

           STDW    .D2T2   B7:B6,*B4         ; |128| 
||         DADD    .L1X    0,B9:B8,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL39,B3,0      ; |130| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 112
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(80),B5:B4
           ADDAD   .D2     B12,1,B13
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B13        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A10        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           MVKL    .S1     output,A11
||         ADD     .L2     B4,B5,B7          ; |117| 

           MVKH    .S1     output,A11
||         MV      .L2X    A14,B9            ; |226| 
||         STDW    .D2T2   B7:B6,*B11        ; |117| 

           CALLP   .S2     exp2sp_v,B3
||         LDW     .D1T2   *+A11(16),B4      ; |226| 
||         LDW     .D2T1   *B9,A4            ; |226| 
||         MVK     .S1     0x80,A6           ; |226| 

$C$RL41:   ; CALL OCCURS {exp2sp_v} {0}      ; |226| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A7:A6        ; |130| 
||         LDDW    .D2T2   *B11,B7:B6        ; |130| 

           MVK     .S1     16,A10
           ADD     .L1X    B13,A10,A10
           LDDW    .D1T1   *A10,A9:A8        ; |130| 
           MVKL    .S1     t_stop,A3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           MVKH    .S1     t_stop,A3
||         SUBU    .L1X    B8,A4,A17:A16     ; |130| 

           ADD     .L1X    A5,B7,A4          ; |130| 
||         MV      .L2     B4,B9             ; |128| 

           ADD     .L1     A4,A7,A4          ; |130| 
||         MV      .L2X    A3,B4             ; |128| 
||         MV      .D1     A16,A3            ; |130| 
||         EXT     .S1     A17,24,24,A6      ; |130| 

           SUB     .S1X    B9,A4,A3          ; |130| 
||         ADDU    .L1     A8,A3,A5:A4       ; |130| 

           ADD     .L1     A5,A9,A3          ; |130| 
||         ADD     .S1     A3,A6,A5          ; |130| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6

           STDW    .D1T1   A5:A4,*A10        ; |130| 
||         MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A11,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     fcn_pass,B10
           MVKH    .S2     0x3ee4f8b5,B7
           MVKH    .S2     0x88e368f1,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S2     fcn_pass,B10

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A11(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(52),A3       ; |68| 
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           LDW     .D1T1   *A11,A4           ; |69| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL47:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(56),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(60),B4
           NOP             3

   [!B0]   B       .S1     $C$L18            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L18}        ; |72| 
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
   [ A0]   B       .S1     $C$L19            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |232| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L19}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |232| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |232| 
||         ADDKPC  .S2     $C$RL48,B3,0      ; |232| 

$C$RL48:   ; CALL OCCURS {print_test_results} {0}  ; |232| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |233| 

$C$RL49:   ; CALL OCCURS {printf} {0}        ; |233| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |233| 

$C$RL50:   ; CALL OCCURS {printf} {0}        ; |233| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |240| 

$C$RL51:   ; CALL OCCURS {print_profile_results} {0}  ; |240| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |243| 

$C$RL52:   ; CALL OCCURS {print_memory_results} {0}  ; |243| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(96),B3      ; |244| 
           LDDW    .D2T1   *++SP,A13:A12     ; |244| 
           LDDW    .D2T1   *++SP,A15:A14     ; |244| 
           LDDW    .D2T2   *++SP,B11:B10     ; |244| 
           LDDW    .D2T2   *++SP,B13:B12     ; |244| 

           LDW     .D2T1   *++SP(8),A10      ; |244| 
||         RET     .S2     B3                ; |244| 

           LDW     .D2T1   *++SP(8),A11      ; |244| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |244| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"exp2SP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	exp2f
	.global	exp2
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	exp2sp
	.global	exp2sp_c
	.global	exp2sp_v
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
