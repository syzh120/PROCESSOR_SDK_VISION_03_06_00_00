;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:50:27 2013                                *
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
	.elfsym	a,SYM_SIZE(804)
a:
	.word	04957871bh		; a[0] @ 0
	.word	04908cbd1h		; a[1] @ 32
	.word	047eecb43h		; a[2] @ 64
	.word	048ee9b46h		; a[3] @ 96
	.word	04769c16dh		; a[4] @ 128
	.word	0490eab2dh		; a[5] @ 160
	.word	048b6ed1ah		; a[6] @ 192
	.word	0495ea9a7h		; a[7] @ 224
	.word	0494dc1fdh		; a[8] @ 256
	.word	04898b6a0h		; a[9] @ 288
	.word	04930b6dfh		; a[10] @ 320
	.word	04944ccfah		; a[11] @ 352
	.word	047f88b18h		; a[12] @ 384
	.word	04963d7dah		; a[13] @ 416
	.word	048b938b1h		; a[14] @ 448
	.word	048139381h		; a[15] @ 480
	.word	048cbaa02h		; a[16] @ 512
	.word	04849ed94h		; a[17] @ 544
	.word	048045b00h		; a[18] @ 576
	.word	048f63ebbh		; a[19] @ 608
	.word	04941aaadh		; a[20] @ 640
	.word	048f564dfh		; a[21] @ 672
	.word	048b757c2h		; a[22] @ 704
	.word	0473703c5h		; a[23] @ 736
	.word	0496a808ah		; a[24] @ 768
	.word	0493e1256h		; a[25] @ 800
	.word	047b88105h		; a[26] @ 832
	.word	048fc9eeeh		; a[27] @ 864
	.word	04834bea7h		; a[28] @ 896
	.word	04911c0d2h		; a[29] @ 928
	.word	049513659h		; a[30] @ 960
	.word	048860d4ah		; a[31] @ 992
	.word	048a89e0ah		; a[32] @ 1024
	.word	047be1956h		; a[33] @ 1056
	.word	0494deeddh		; a[34] @ 1088
	.word	0487faa44h		; a[35] @ 1120
	.word	0495cd230h		; a[36] @ 1152
	.word	046b547c8h		; a[37] @ 1184
	.word	049462ceeh		; a[38] @ 1216
	.word	046b4a24ah		; a[39] @ 1248
	.word	04963162fh		; a[40] @ 1280
	.word	0492bad91h		; a[41] @ 1312
	.word	047f16f7bh		; a[42] @ 1344
	.word	04925e39eh		; a[43] @ 1376
	.word	04792067ah		; a[44] @ 1408
	.word	047986297h		; a[45] @ 1440
	.word	049313b6ah		; a[46] @ 1472
	.word	0496a6642h		; a[47] @ 1504
	.word	049105773h		; a[48] @ 1536
	.word	04921834ah		; a[49] @ 1568
	.word	04825efa4h		; a[50] @ 1600
	.word	0483683e5h		; a[51] @ 1632
	.word	04898ffaah		; a[52] @ 1664
	.word	0490ab25ch		; a[53] @ 1696
	.word	049106a3ch		; a[54] @ 1728
	.word	048804359h		; a[55] @ 1760
	.word	04926cf68h		; a[56] @ 1792
	.word	048fa39aah		; a[57] @ 1824
	.word	049318d2bh		; a[58] @ 1856
	.word	0492d6a0bh		; a[59] @ 1888
	.word	04931b46ch		; a[60] @ 1920
	.word	04941e5f9h		; a[61] @ 1952
	.word	0495d3faeh		; a[62] @ 1984
	.word	04916d9e3h		; a[63] @ 2016
	.word	04791cabbh		; a[64] @ 2048
	.word	0489911deh		; a[65] @ 2080
	.word	047169421h		; a[66] @ 2112
	.word	049276bcdh		; a[67] @ 2144
	.word	049656cbdh		; a[68] @ 2176
	.word	04909736bh		; a[69] @ 2208
	.word	0491dd177h		; a[70] @ 2240
	.word	0484260c2h		; a[71] @ 2272
	.word	04800c84dh		; a[72] @ 2304
	.word	0491866b7h		; a[73] @ 2336
	.word	0494c5549h		; a[74] @ 2368
	.word	0470af778h		; a[75] @ 2400
	.word	0476bf3cch		; a[76] @ 2432
	.word	0482b19f3h		; a[77] @ 2464
	.word	0489935fah		; a[78] @ 2496
	.word	049256990h		; a[79] @ 2528
	.word	0492fa1f6h		; a[80] @ 2560
	.word	048ed9ea6h		; a[81] @ 2592
	.word	048b44df1h		; a[82] @ 2624
	.word	0483b6845h		; a[83] @ 2656
	.word	0492bbdfbh		; a[84] @ 2688
	.word	048d1ce69h		; a[85] @ 2720
	.word	04959df7fh		; a[86] @ 2752
	.word	04868ceedh		; a[87] @ 2784
	.word	0484319cah		; a[88] @ 2816
	.word	048e0c3c8h		; a[89] @ 2848
	.word	048b5ecb1h		; a[90] @ 2880
	.word	0479e3e23h		; a[91] @ 2912
	.word	049723aa5h		; a[92] @ 2944
	.word	0491a135ah		; a[93] @ 2976
	.word	04955eaf1h		; a[94] @ 3008
	.word	04908ebf4h		; a[95] @ 3040
	.word	048d97097h		; a[96] @ 3072
	.word	0491145cdh		; a[97] @ 3104
	.word	047a7b105h		; a[98] @ 3136
	.word	047f86b73h		; a[99] @ 3168
	.word	04901f0eah		; a[100] @ 3200
	.word	0490f1638h		; a[101] @ 3232
	.word	0487b1acdh		; a[102] @ 3264
	.word	04946cb74h		; a[103] @ 3296
	.word	04946e2f5h		; a[104] @ 3328
	.word	048d817e1h		; a[105] @ 3360
	.word	0487435e6h		; a[106] @ 3392
	.word	0487e8188h		; a[107] @ 3424
	.word	048da3d4eh		; a[108] @ 3456
	.word	049115d7eh		; a[109] @ 3488
	.word	048fc9925h		; a[110] @ 3520
	.word	04927689ah		; a[111] @ 3552
	.word	0482c0ac6h		; a[112] @ 3584
	.word	0476c3f9dh		; a[113] @ 3616
	.word	047d330b5h		; a[114] @ 3648
	.word	0495e0b86h		; a[115] @ 3680
	.word	048aad192h		; a[116] @ 3712
	.word	048df9681h		; a[117] @ 3744
	.word	049204a29h		; a[118] @ 3776
	.word	048a8415bh		; a[119] @ 3808
	.word	0495ad583h		; a[120] @ 3840
	.word	0497352c7h		; a[121] @ 3872
	.word	048c1e600h		; a[122] @ 3904
	.word	042c07aefh		; a[123] @ 3936
	.word	048aa2d46h		; a[124] @ 3968
	.word	048eb6cd4h		; a[125] @ 4000
	.word	048194c2fh		; a[126] @ 4032
	.word	048e76e3dh		; a[127] @ 4064
	.word	0494c096ah		; a[128] @ 4096
	.word	04894d14ah		; a[129] @ 4128
	.word	048afbbd2h		; a[130] @ 4160
	.word	0496b7cfeh		; a[131] @ 4192
	.word	047855ba7h		; a[132] @ 4224
	.word	048e403ffh		; a[133] @ 4256
	.word	04661ba32h		; a[134] @ 4288
	.word	048754124h		; a[135] @ 4320
	.word	048b02c69h		; a[136] @ 4352
	.word	04903f5d3h		; a[137] @ 4384
	.word	0493316fch		; a[138] @ 4416
	.word	04930195fh		; a[139] @ 4448
	.word	0491785d5h		; a[140] @ 4480
	.word	0492e1bb1h		; a[141] @ 4512
	.word	0492e9093h		; a[142] @ 4544
	.word	048ad76f3h		; a[143] @ 4576
	.word	048a4146ah		; a[144] @ 4608
	.word	04938f2c1h		; a[145] @ 4640
	.word	04939c9d5h		; a[146] @ 4672
	.word	0492d6871h		; a[147] @ 4704
	.word	049163462h		; a[148] @ 4736
	.word	046f3bdb2h		; a[149] @ 4768
	.word	0487895cbh		; a[150] @ 4800
	.word	0496956ech		; a[151] @ 4832
	.word	048048994h		; a[152] @ 4864
	.word	048f41007h		; a[153] @ 4896
	.word	04832e271h		; a[154] @ 4928
	.word	0494e8b25h		; a[155] @ 4960
	.word	0482f1064h		; a[156] @ 4992
	.word	0492f4a61h		; a[157] @ 5024
	.word	047e8aafah		; a[158] @ 5056
	.word	049339fd7h		; a[159] @ 5088
	.word	049158ec5h		; a[160] @ 5120
	.word	049496a4fh		; a[161] @ 5152
	.word	04865afa3h		; a[162] @ 5184
	.word	0490ac894h		; a[163] @ 5216
	.word	0495e5082h		; a[164] @ 5248
	.word	0490cb1fch		; a[165] @ 5280
	.word	04892d18dh		; a[166] @ 5312
	.word	04955f3fdh		; a[167] @ 5344
	.word	04805d05dh		; a[168] @ 5376
	.word	0488edb8ch		; a[169] @ 5408
	.word	049219af7h		; a[170] @ 5440
	.word	049434d13h		; a[171] @ 5472
	.word	0496688a9h		; a[172] @ 5504
	.word	0495d6498h		; a[173] @ 5536
	.word	0488962aeh		; a[174] @ 5568
	.word	0474e9466h		; a[175] @ 5600
	.word	0490dedffh		; a[176] @ 5632
	.word	049678fb4h		; a[177] @ 5664
	.word	0492c6e8bh		; a[178] @ 5696
	.word	0496b8d3dh		; a[179] @ 5728
	.word	049584b5ch		; a[180] @ 5760
	.word	048fdfb29h		; a[181] @ 5792
	.word	0477d5cfdh		; a[182] @ 5824
	.word	048d81506h		; a[183] @ 5856
	.word	04890af8dh		; a[184] @ 5888
	.word	048a64596h		; a[185] @ 5920
	.word	047c603f8h		; a[186] @ 5952
	.word	049727d74h		; a[187] @ 5984
	.word	0494ed6edh		; a[188] @ 6016
	.word	0492e1b84h		; a[189] @ 6048
	.word	048022fbdh		; a[190] @ 6080
	.word	04930e498h		; a[191] @ 6112
	.word	0481a83d0h		; a[192] @ 6144
	.word	04902690ah		; a[193] @ 6176
	.word	047a8837bh		; a[194] @ 6208
	.word	0489aed95h		; a[195] @ 6240
	.word	048d9850dh		; a[196] @ 6272
	.word	0488ec95ah		; a[197] @ 6304
	.word	048e9b849h		; a[198] @ 6336
	.word	0478d102dh		; a[199] @ 6368
	.word	04901495eh		; a[200] @ 6400

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\135602 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\135604 
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
;*   Local Frame Size  : 8 Args + 92 Auto + 56 Save = 156 byte                *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |129| 
           STW     .D2T1   A10,*SP--(8)      ; |129| 
           STDW    .D2T2   B13:B12,*SP--     ; |129| 
           STDW    .D2T2   B11:B10,*SP--     ; |129| 
           STDW    .D2T1   A15:A14,*SP--     ; |129| 

           STDW    .D2T1   A13:A12,*SP--     ; |129| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(112)     ; |129| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     0xc9,B4
||         MVKL    .S1     a,A11

           MVKH    .S1     a,A11

           CALL    .S1     logf              ; |146| 
||         MV      .L1     A11,A13
||         MV      .D1X    B4,A12
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A13++,A4         ; |146| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |146| 
$C$RL1:    ; CALL OCCURS {logf} {0}          ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A12,1,A0          ; |145| 
||         SUB     .S1     A12,1,A12         ; |145| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |146| 
   [ A0]   BNOP    .S1     $C$L1,3           ; |145| 

           ADD     .L2     B10,B4,B4         ; |146| 
||         ADD     .S2     4,B10,B10         ; |145| 

   [ A0]   CALL    .S1     logf              ; |146| 
||         STW     .D2T1   A4,*B4            ; |146| 
|| [!A0]   MVKL    .S2     output,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |145| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           MVKH    .S2     output,B4
||         ZERO    .L2     B10
||         MV      .L1     A11,A10

           ADD     .L2     4,B4,B5
||         MVK     .S2     0xc9,B4

           STW     .D2T2   B5,*+SP(36)

           MV      .L1X    B4,A12
||         CALL    .S1     logsp             ; |149| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |149| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |149| 
$C$RL2:    ; CALL OCCURS {logsp} {0}         ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(36),B4       ; |149| 
           SUB     .L1     A12,1,A0          ; |148| 
           SUB     .L1     A12,1,A12         ; |148| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |149| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |148| 

           ADD     .L2     B10,B4,B4         ; |149| 
||         ADD     .S2     4,B10,B10         ; |148| 

   [ A0]   CALL    .S1     logsp             ; |149| 
||         STW     .D2T1   A4,*B4            ; |149| 

           ; BRANCHCC OCCURS {$C$L2}         ; |148| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           LDW     .D2T2   *+SP(36),B4
           ZERO    .L2     B10
           MV      .L1     A10,A11
           NOP             2

           ADD     .L2     4,B4,B5
||         MVK     .S2     0xc9,B4

           STW     .D2T2   B5,*+SP(40)

           MV      .L1X    B4,A12
||         CALL    .S1     logsp_c           ; |152| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |152| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |152| 
$C$RL3:    ; CALL OCCURS {logsp_c} {0}       ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(40),B4       ; |152| 
||         SUB     .L1     A12,1,A0          ; |151| 
||         SUB     .S1     A12,1,A12         ; |151| 

   [!A0]   LDW     .D2T2   *+SP(40),B29
|| [!A0]   MVKL    .S1     0xbe6bd0fc,A3

   [!A0]   MVKH    .S1     0xbe6bd0fc,A3

   [!A0]   MV      .L1     A3,A21
|| [!A0]   STW     .D2T1   A3,*+SP(12)
|| [!A0]   MVKL    .S1     0x7f7fffff,A3

   [!A0]   MVKL    .S1     0x3eaaa872,A12
           LDW     .D2T2   *B4,B4            ; |152| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |151| 

           ADD     .L2     B10,B4,B4         ; |152| 
||         ADD     .S2     4,B10,B10         ; |151| 

   [ A0]   CALL    .S1     logsp_c           ; |152| 
||         STW     .D2T1   A4,*B4            ; |152| 
|| [!A0]   ZERO    .L1     A4
|| [!A0]   MVKL    .S2     0x3e436581,B10

           ; BRANCHCC OCCURS {$C$L3}         ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S2     0x44317218,B4
||         MVKL    .S1     logtable,A14
||         ZERO    .L2     B30
||         ADD     .D2     4,B29,B12
||         ZERO    .L1     A8                ; |83| 
||         ZERO    .D1     A17               ; |83| 

           MVKL    .S2     0xbf000003,B13
||         MVKH    .S1     0x3eaaa872,A12
||         LDW     .D2T2   *B12,B17
||         ZERO    .L2     B20               ; |83| 
||         MV      .L1     A10,A18

           MVKL    .S2     0xbe804d66,B11
||         MVKH    .S1     0x7f7fffff,A3

           MVKL    .S2     0x3fe62e42,B5
||         MVKH    .S1     logtable,A14
||         STW     .D2T1   A3,*+SP(24)
||         MV      .L2X    A12,B23

           MVKL    .S2     0xfefa39ec,B31
||         MVK     .S1     0xfffffc01,A15
||         MV      .L1     A14,A19
||         MV      .L2X    A3,B18

           MVKH    .S2     0x44317218,B4
||         SET     .S1     A4,0x14,0x1d,A4
||         MV      .L1     A15,A20

           MVKH    .S2     0xbf000003,B13
||         STW     .D2T2   B4,*+SP(20)
||         MV      .L1     A4,A9
||         MV      .L2     B4,B19

           MVKH    .S2     0xbe804d66,B11
||         STW     .D2T1   A4,*+SP(32)       ; |83| 
||         MV      .L2     B13,B22

           MVKH    .S2     0x3fe62e42,B5
||         MV      .L2     B11,B25

           MVKH    .S2     0xfefa39ec,B31
||         STW     .D2T2   B5,*+SP(48)       ; |83| 
||         MV      .L2     B5,B7

           MVKH    .S2     0xff800000,B30
||         STW     .D2T2   B31,*+SP(44)      ; |83| 

           MVK     .S2     0xc9,B6
||         STW     .D2T2   B30,*+SP(16)
||         MV      .L2     B30,B21

           MVKH    .S2     0x3e436581,B10
||         SUB     .L2     B6,1,B1
||         MV      .D2     B31,B6

           MV      .L2     B10,B24
||         DINT                              ; interrupts off

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/logsp/logsp_d.c
;*      Loop source line                 : 154
;*      Loop opening brace source line   : 154
;*      Loop closing brace source line   : 156
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 59
;*      Unpartitioned Resource Bound     : 7
;*      Partitioned Resource Bound(*)    : 9
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     3        1     
;*      .S units                     7        5     
;*      .D units                     2        1     
;*      .M units                     5        6     
;*      .X cross paths               1        9*    
;*      .T address paths             2        1     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           3        5     (.L or .S unit)
;*      Addition ops (.LSD)          3        6     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             7        6     
;*      Bound(.L .S .D .LS .LSD)     6        6     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 59 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |        **       *****          | *    **         *********      |
;*       1: |        **       *****          | *    **         *********      |
;*       2: |        **       *****          | *    **         *********      |
;*       3: |        **       *****          | *    **         *********      |
;*       4: |        **       *****          | *    **         *********      |
;*       5: |        **      ******          | *    **         *********      |
;*       6: |        **      ******          | *    **         *********      |
;*       7: |    **  **      ******          | *    **         *********      |
;*       8: |        **      ******          | *    **         *********      |
;*       9: |     *  **      ******          | *    **         *********      |
;*      10: |    * * **      ******          | *    **         *********      |
;*      11: |   **** **      ******          | *    **         *********      |
;*      12: |   ***  **      ****** *        | *    **         *********      |
;*      13: |   *    **      ****** *        | *    **         *********      |
;*      14: |   *    **      ****** *        | *    **         *********      |
;*      15: |   *    **      ****** *        | *    **         *********      |
;*      16: |   *    **      ****** *        | *    **         *********      |
;*      17: |   *    **      ****** *        | *    **         *********      |
;*      18: |   ***  **      ****** *        | *    **         *********      |
;*      19: |   *    **      ****** *        | *    **         *********      |
;*      20: |   *    **      ****** *        | *    **         *********      |
;*      21: |   *  ****      ****** *        | *    **         *********      |
;*      22: |   *  ****      ****** *        | *    **         *********      |
;*      23: |   *  ****      ****** *        | *    **         *********      |
;*      24: |   *  ****      ****** *        | *    **         *********      |
;*      25: |   ** ****      ****** *        | *    **         *********      |
;*      26: |   ** ****      ****** *        | *    **         *********      |
;*      27: |   ** ****      ****** *        | *  * **         *********      |
;*      28: |   *  ****      ****** *        | *  * **         *********      |
;*      29: |   ** ****      ****** *        | *  * **         *********      |
;*      30: |   ** ****      ****** *        | *  * **         *********      |
;*      31: |    * ****      ****** *        | *  ****         *********      |
;*      32: |      ****      ****** *        | *    **         *********      |
;*      33: |   *  ****      ****** *        | *    **         *********      |
;*      34: |   *  ****      ********        | *  * ***        *********      |
;*      35: |    ******      ********        | *  * ***        *********      |
;*      36: |    ******      ********        | *    ***        *********      |
;*      37: |      ****      *******         | *  * ***        *********      |
;*      38: |      ****      ******          | *    ***        *********      |
;*      39: |      ****      ******          | *    ****       *********      |
;*      40: |      ****      ******          | *  ******       *********      |
;*      41: |    ******      ******          | *  ******      **********      |
;*      42: |      ****      ******          | *    ***        *********      |
;*      43: |      ****      ******          | *    ***        *********      |
;*      44: |    ******      ******          | *  * ***        *********      |
;*      45: |        **      ******          | *    **         *********      |
;*      46: |        **      ******          | *    **         *********      |
;*      47: |    **  **      ******          | *  * **         *********      |
;*      48: |    **  **      ******          | *    **         *********      |
;*      49: |    **  **      ******          | *  ****         *********      |
;*      50: |        **      ******          | *    **         *********      |
;*      51: |        **      ******          | *    **         *********      |
;*      52: |        **      ******          | *  ****         *********      |
;*      53: |        **      ******          | *    **         *********      |
;*      54: |        **      ******          | *    **         *********      |
;*      55: |        **       *****          | *   ***         *********      |
;*      56: |        **       *****          |**  ****         *********      |
;*      57: |        **       *****          |**  * **         *********      |
;*      58: |        **       *****          | *  ****         *********      |
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
;*      Total cycles (est.)         : 0 + min_trip_cnt * 59 = 11859        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             B1,1,B1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C96:
;*   0              LDW     .D1T1   *A18++,A16        ; |83|  ^ 
;*   1              NOP             4
;*   5              SPDP    .S1     A16,A5:A4         ; |83|  ^ 
;*   6              NOP             1
;*   7              RCPDP   .S1     A5:A4,A5:A4       ; |83|  ^ 
;*   8              NOP             1
;*   9              CLR     .S1     A5,0,16,A6        ; |83|  ^ 
;*     ||           MV      .L1     A17,A4            ; |83| 
;*  10              MV      .L1     A6,A5             ; |83|  ^ 
;*     ||           EXTU    .S1     A6,1,21,A3        ; |83| 
;*  11              MPYSPDP .M1     A16,A5:A4,A5:A4   ; |83|  ^ 
;*     ||           ADD     .L1     A20,A3,A3         ; |83| 
;*     ||           EXTU    .S1     A6,12,29,A23      ; |83| 
;*  12              NOP             6
;*  18              FSUBDP  .L1     A5:A4,A9:A8,A7:A6 ; |83|  ^ 
;*  19              NOP             2
;*  21              DPSP    .L1     A7:A6,A4          ; |83|  ^ 
;*  22              NOP             3
;*  25              MPYSP   .M1     A4,A4,A4          ; |83|  ^ 
;*  26              MV      .L2X    A4,B4             ; |83| Define a twin register
;*  27              MPYSP   .M2X    B24,A4,B5         ; |83| 
;*  28              NOP             1
;*  29              MPYSP   .M1     A21,A4,A3         ; |83|  ^ 
;*  30              INTDP   .L1     A3,A5:A4          ; |83| 
;*     ||           MPYSP   .M1     A4,A4,A22         ; |83| 
;*     ||           MPYSP   .M2X    B22,A4,B8         ; |83| 
;*  31              FADDSP  .L2     B25,B5,B4         ; |83| 
;*     ||           MPYSP   .M2X    A4,B4,B4          ; |83| 
;*  32              NOP             2
;*  34              FADDSP  .L2X    A3,B4,B4          ; |83|  ^ 
;*  35              MPYSP   .M2     B23,B4,B9         ; |83| 
;*  36              FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |83| 
;*     ||           LDDW    .D1T1   *+A19[A23],A5:A4  ; |83| 
;*  37              MPYSP   .M2X    A22,B4,B16        ; |83|  ^ 
;*  38              NOP             3
;*  41              FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |83| 
;*     ||           FADDSP  .L2     B16,B9,B4         ; |83|  ^ 
;*  42              NOP             2
;*  44              FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |83| 
;*     ||           FADDSP  .L2     B4,B8,B4          ; |83|  ^ 
;*  45              NOP             2
;*  47              SPDP    .S2     B4,B5:B4          ; |83|  ^ 
;*  48              NOP             1
;*  49              FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |83|  ^ 
;*  50              NOP             2
;*  52              DPSP    .L2     B5:B4,B4          ; |83|  ^ 
;*  53      [ B1]   BDEC    .S2     $C$C96,B1         ; |154| 
;*  54              MV      .L2X    A16,B5            ; |83| Define a twin register
;*  55              CMPGTSP .S2     B5,B20,B0         ; |83| 
;*  56      [!B0]   MV      .L2     B21,B4            ; |83| 
;*     ||           CMPGTSP .S2     B5,B18,B0         ; |83| 
;*  57      [!B0]   MV      .S2     B4,B5             ; |83|  ^ 
;*     ||   [ B0]   MV      .L2     B19,B5            ; |83| 
;*  58              STW     .D2T2   B5,*B17++         ; |83|  ^ 
;*  59              ; BRANCHCC OCCURS {$C$C96}        ; |154| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 59
           LDW     .D1T1   *A18++,A16        ; |83| <0,0>  ^ 
           NOP             4
           SPDP    .S1     A16,A5:A4         ; |83| <0,5>  ^ 
           NOP             1
           RCPDP   .S1     A5:A4,A5:A4       ; |83| <0,7>  ^ 
           NOP             1

           CLR     .S1     A5,0,16,A6        ; |83| <0,9>  ^ 
||         MV      .L1     A17,A4            ; |83| <0,9> 

           EXTU    .S1     A6,1,21,A3        ; |83| <0,10> 
||         MV      .L1     A6,A5             ; |83| <0,10>  ^ 

           EXTU    .S1     A6,12,29,A23      ; |83| <0,11> 
||         ADD     .L1     A20,A3,A3         ; |83| <0,11> 
||         MPYSPDP .M1     A16,A5:A4,A5:A4   ; |83| <0,11>  ^ 

           NOP             6
           FSUBDP  .L1     A5:A4,A9:A8,A7:A6 ; |83| <0,18>  ^ 
           NOP             2
           DPSP    .L1     A7:A6,A4          ; |83| <0,21>  ^ 
           NOP             3
           MPYSP   .M1     A4,A4,A4          ; |83| <0,25>  ^ 
           MV      .L2X    A4,B4             ; |83| <0,26> Define a twin register
           MPYSP   .M2X    B24,A4,B5         ; |83| <0,27> 
           NOP             1
           MPYSP   .M1     A21,A4,A3         ; |83| <0,29>  ^ 

           MPYSP   .M1     A4,A4,A22         ; |83| <0,30> 
||         INTDP   .L1     A3,A5:A4          ; |83| <0,30> 
||         MPYSP   .M2X    B22,A4,B8         ; |83| <0,30> 

           MPYSP   .M2X    A4,B4,B4          ; |83| <0,31> 
||         FADDSP  .L2     B25,B5,B4         ; |83| <0,31> 

           NOP             2
           FADDSP  .L2X    A3,B4,B4          ; |83| <0,34>  ^ 
           MPYSP   .M2     B23,B4,B9         ; |83| <0,35> 

           LDDW    .D1T1   *+A19[A23],A5:A4  ; |83| <0,36> 
||         FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |83| <0,36> 

           MPYSP   .M2X    A22,B4,B16        ; |83| <0,37>  ^ 
           NOP             3

           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |83| <0,41> 
||         FADDSP  .L2     B16,B9,B4         ; |83| <0,41>  ^ 

           NOP             2

           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |83| <0,44> 
||         FADDSP  .L2     B4,B8,B4          ; |83| <0,44>  ^ 

           NOP             2
           SPDP    .S2     B4,B5:B4          ; |83| <0,47>  ^ 
           NOP             1
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |83| <0,49>  ^ 
           NOP             2
           DPSP    .L2     B5:B4,B4          ; |83| <0,52>  ^ 
   [ B1]   BDEC    .S2     $C$L5,B1          ; |154| <0,53> 
           MV      .L2X    A16,B5            ; |83| <0,54> Define a twin register
           CMPGTSP .S2     B5,B20,B0         ; |83| <0,55> 

           CMPGTSP .S2     B5,B18,B0         ; |83| <0,56> 
|| [!B0]   MV      .L2     B21,B4            ; |83| <0,56> 

   [ B0]   MV      .L2     B19,B5            ; |83| <0,57> 
|| [!B0]   MV      .S2     B4,B5             ; |83| <0,57>  ^ 

           STW     .D2T2   B5,*B17++         ; |83| <0,58>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           STW     .D2T2   B19,*+SP(20)
           STW     .D2T2   B18,*+SP(24)
           STW     .D2T1   A21,*+SP(12)
           STW     .D2T2   B7,*+SP(48)
           STW     .D2T2   B6,*+SP(44)

           MVKL    .S2     output,B4
||         STW     .D2T1   A9,*+SP(32)

           STW     .D2T2   B21,*+SP(16)
||         RINT                              ; interrupts on

           MVKH    .S2     output,B4
||         MVK     .S1     0xc9,A6           ; |157| 
||         MV      .L1X    B20,A11
||         MV      .L2     B22,B13
||         MV      .D2     B24,B10
||         MV      .D1     A10,A4            ; |157| 

           CALLP   .S2     logsp_v,B3
||         LDW     .D2T2   *+B4(16),B4       ; |157| 
||         MV      .L1     A19,A14
||         MV      .S1     A20,A15
||         MV      .D1X    B23,A12
||         MV      .L2     B25,B11

$C$RL4:    ; CALL OCCURS {logsp_v} {0}       ; |157| 
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

           MV      .L2     B5,B4             ; |146| 
||         STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B4(12),B4       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     fcn_pass,B4
           MVKL    .S2     output,B31
           MVKH    .S2     0x3ee4f8b5,B7

           ADD     .L1X    4,B12,A3
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           MVKH    .S2     output,B31
||         STW     .D2T1   A3,*+SP(52)

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     fcn_pass,B5

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     fcn_pass,B5

           ADD     .L1     4,A3,A3
           LDW     .D1T1   *A3,A0            ; |72| 
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           ADD     .L2     8,B5,B4
           STW     .D2T2   B4,*+SP(60)       ; |69| 
           STW     .D2T1   A3,*+SP(56)

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |161| 
   [!A0]   ZERO    .L1     A3                ; |72| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     all_pass,A4
   [!A0]   MVKH    .S1     all_pass,A4
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
           CALL    .S1     print_test_results ; |161| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x1,A4            ; |161| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |161| 

$C$RL9:    ; CALL OCCURS {print_test_results} {0}  ; |161| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           MVKL    .S2     a_sc,B5

           ZERO    .L2     B7
||         MVKL    .S2     0x7f7fffff,B29

           LDW     .D2T2   *+SP(16),B4       ; |174| 
||         MVKH    .S2     0xbf800000,B7

           MVKH    .S2     a_sc,B5
||         ZERO    .L2     B31
||         MVK     .D2     -1,B6             ; |174| 

           MV      .L2     B5,B30            ; |169| 
||         STW     .D2T2   B7,*+SP(84)       ; |173| 
||         MVKH    .S2     0x7f7fffff,B29

           SET     .S2     B31,0x17,0x1d,B7
||         STW     .D2T2   B6,*+B30(24)      ; |174| 

           MV      .L1X    B5,A13            ; |169| 
||         ADD     .L2     1,B29,B5
||         MV      .S2     B30,B6
||         STW     .D2T2   B7,*+SP(80)       ; |173| 

           STDW    .D2T2   B5:B4,*+B6(8)     ; |171| 
           LDDW    .D2T2   *+SP(80),B5:B4    ; |169| 
           ZERO    .L1     A10
           MVK     .L2     0x7,B27

           MV      .L2     B6,B28            ; |171| 
||         MVKH    .S1     0x80000000,A10
||         STW     .D2T2   B27,*+SP(28)      ; |173| 

           STDW    .D2T1   A11:A10,*B28      ; |169| 
           STDW    .D2T2   B5:B4,*+B6(16)    ; |173| 
           LDW     .D1T1   *A13,A3           ; |176| 
           CALL    .S1     log               ; |176| 
           ZERO    .L1     A10
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |176| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL10,B3,0      ; |176| 
$C$RL10:   ; CALL OCCURS {log} {0}           ; |176| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |176| 
           DPSP    .L1     A5:A4,A4          ; |176| 
           NOP             3
           ADD     .L1X    A10,B4,A3         ; |176| 
           STW     .D1T1   A4,*A3            ; |176| 

           CALLP   .S2     __c6xabi_isinff,B3
||         LDW     .D1T1   *A13,A4           ; |177| 

$C$RL11:   ; CALL OCCURS {__c6xabi_isinff} {0}  ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           MV      .L1     A4,A0             ; |177| 

           MV      .L1     A0,A2             ; |177| branch predicate copy
|| [ A0]   LDW     .D1T1   *A13,A3           ; |177| 
|| [!A0]   B       .S1     $C$L10            ; |177| 

   [!A2]   CALL    .S1     logsp             ; |177| 
   [!A2]   LDW     .D1T1   *A13,A4           ; |177| 
           NOP             2
           CMPGTSP .S1     A3,A11,A0         ; |177| 
           ; BRANCHCC OCCURS {$C$L10}        ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
   [!A0]   B       .S1     $C$L9             ; |177| 
   [ A0]   CALL    .S1     log               ; |177| 
   [ A0]   SPDP    .S1     A3,A5:A4          ; |177| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L9}         ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL12,B3,0      ; |177| 
$C$RL12:   ; CALL OCCURS {log} {0}           ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L11            ; |177| 
||         DPSP    .L1     A5:A4,A3          ; |177| 
||         MVKL    .S2     output,B5

           MVKH    .S2     output,B5
           LDW     .D2T2   *+B5(4),B5        ; |177| 
           NOP             2
           MV      .L2X    A3,B4             ; |177| 
           ; BRANCH OCCURS {$C$L11}          ; |177| 
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     logsp             ; |177| 
           LDW     .D1T1   *A13,A4           ; |177| 
           NOP             3
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL13,B3,0      ; |177| 
$C$RL13:   ; CALL OCCURS {logsp} {0}         ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           SPDP    .S1     A4,A5:A4          ; |177| 
           MVKL    .S2     output,B5
           DPSP    .L1     A5:A4,A3          ; |177| 
           MVKH    .S2     output,B5
           LDW     .D2T2   *+B5(4),B5        ; |177| 
           NOP             2
           MV      .L2X    A3,B4             ; |177| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             1
           ADD     .L2X    A10,B5,B5         ; |177| 

           STW     .D2T2   B4,*B5            ; |177| 
||         CALL    .S1     logsp_c           ; |178| 

           LDW     .D1T1   *A13,A4           ; |178| 
           ADDKPC  .S2     $C$RL14,B3,3      ; |178| 
$C$RL14:   ; CALL OCCURS {logsp_c} {0}       ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 75
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |178| 
           ZERO    .L1     A6                ; |83| 
           ZERO    .L1     A7
           SET     .S1     A7,0x14,0x1d,A7
           LDW     .D2T1   *+SP(12),A30      ; |83| 
           ADD     .L2X    A10,B4,B4         ; |178| 
           STW     .D2T1   A4,*B4            ; |178| 
           LDW     .D1T1   *A13++,A3         ; |179| 
           MVKL    .S2     0xfefa39ec,B4
           MVKH    .S2     0xfefa39ec,B4
           LDW     .D2T2   *+SP(24),B30
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |83| 
           NOP             1
           RCPDP   .S1     A5:A4,A5:A4       ; |83| 
           CMPGTSP .S2X    A3,B30,B0         ; |88| 

           CLR     .S1     A5,0,16,A9        ; |83| 
||         ZERO    .L1     A4                ; |83| 

           MV      .L1     A9,A5             ; |83| 
           MPYSPDP .M1     A3,A5:A4,A5:A4    ; |83| 
           EXTU    .S1     A9,1,21,A31       ; |83| 
           EXTU    .S1     A9,12,29,A29      ; |83| 
           CMPGTSP .S1     A3,A11,A0         ; |85| 
           NOP             3
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |83| 
           ADD     .L1     A15,A31,A4        ; |83| 
           NOP             1
           DPSP    .L1     A7:A6,A18         ; |83| 
           INTDP   .L1     A4,A5:A4          ; |83| 
           NOP             2
           MPYSP   .M1     A18,A18,A8        ; |83| 
           MPYSP   .M2X    B10,A18,B5        ; |83| 
           NOP             2
           MPYSP   .M1     A30,A8,A16        ; |83| 

           FADDSP  .L2     B11,B5,B6         ; |83| 
||         MPYSP   .M1     A8,A8,A17         ; |83| 
||         MVKL    .S2     0x3fe62e42,B5

           MVKH    .S2     0x3fe62e42,B5
           MPYSP   .M1     A8,A18,A18        ; |83| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |83| 
           FADDSP  .L2X    A16,B6,B6         ; |83| 
           LDDW    .D1T1   *+A14[A29],A5:A4  ; |83| 
           MPYSP   .M1     A12,A18,A28       ; |83| 
           MPYSP   .M2X    A17,B6,B7         ; |83| 
           MPYSP   .M2X    B13,A8,B31        ; |83| 
           NOP             2
           FADDSP  .L2X    B7,A28,B7         ; |83| 
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |83| 
           NOP             1
           FADDSP  .L2     B7,B31,B4         ; |83| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |83| 
           MVKL    .S1     output+12,A6
           SPDP    .S2     B4,B5:B4          ; |83| 
           MVKH    .S1     output+12,A6
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |83| 
           LDW     .D1T1   *A6,A27           ; |179| 
           NOP             1

           DPSP    .L2     B5:B4,B4          ; |83| 
|| [!A0]   LDW     .D2T2   *+SP(16),B4       ; |88| 

   [ B0]   LDW     .D2T2   *+SP(20),B4       ; |86| 
           LDW     .D2T2   *+SP(28),B5       ; |89| 
           ADD     .L1     A10,A27,A26       ; |179| 
           ADD     .L1     4,A10,A10         ; |175| 
           NOP             1
           STW     .D1T2   B4,*A26           ; |179| 

           SUB     .L1X    B5,1,A0           ; |175| 
||         SUB     .L2     B5,1,B29          ; |175| 

   [ A0]   LDW     .D1T1   *A13,A3           ; |176| 
|| [ A0]   B       .S1     $C$L8             ; |175| 
|| [!A0]   MVK     .S2     12,B4
||         STW     .D2T2   B29,*+SP(28)      ; |179| 

   [ A0]   CALL    .S1     log               ; |176| 
|| [!A0]   SUB     .L2X    A6,B4,B4

   [!A0]   CALL    .S1     logsp_v           ; |181| 
   [!A0]   LDW     .D2T2   *+B4(16),B4       ; |181| 
   [!A0]   MVKL    .S1     a_sc,A4
   [ A0]   SPDP    .S1     A3,A5:A4          ; |176| 
           ; BRANCHCC OCCURS {$C$L8}         ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVK     .L1     0x7,A6            ; |181| 

           ADDKPC  .S2     $C$RL15,B3,0      ; |181| 
||         MVKH    .S1     a_sc,A4

$C$RL15:   ; CALL OCCURS {logsp_v} {0}       ; |181| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 54
           MVKL    .S2     output,B5
           MVKL    .S2     output,B4
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     output,B5
           MVKH    .S2     output,B4
           MVKH    .S2     0x88e368f1,B6

           LDW     .D2T1   *B5,A4            ; |66| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B4(4),B4        ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     output,B4
           MVKL    .S2     fcn_pass,B5
           MVKH    .S2     output,B4

           LDW     .D2T2   *B4,B8            ; |67| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B4(8),B4        ; |67| 
||         MV      .L1X    B8,A4             ; |67| 
||         MVK     .S1     0x7,A6            ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x88e368f1,B6

           MVKL    .S1     output,A3
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKH    .S1     output,A3
||         MVKH    .S2     fcn_pass,B5

           MVKH    .S2     0x88e368f1,B6

           MV      .L2X    A3,B4             ; |177| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B4(12),B4       ; |68| 
||         LDW     .D1T1   *A3,A4            ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL18:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6

           LDW     .D2T1   *+SP(52),A10      ; |68| 
||         MVKL    .S2     output,B31

           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     output,B31
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A10,B4           ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL19:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(56),B4       ; |69| 
           MVKL    .S2     fcn_pass,B31
           LDW     .D2T1   *+SP(60),A3
           MVKH    .S2     fcn_pass,B31
           LDW     .D2T1   *+SP(84),A31      ; |72| 
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           STW     .D2T1   A3,*+SP(68)       ; |72| 
           STW     .D2T2   B4,*+SP(64)       ; |173| 
           STW     .D2T1   A31,*+SP(28)      ; |69| 

   [!B0]   ZERO    .L1     A4                ; |72| 
|| [!B0]   B       .S1     $C$L12            ; |72| 
|| [ B0]   LDW     .D2T2   *+SP(68),B4

   [!B0]   CALL    .S1     print_test_results ; |185| 
   [!B0]   MVKL    .S1     all_pass,A3
           MV      .L2     B0,B1             ; guard predicate rewrite
   [!B0]   MVKH    .S1     all_pass,A3

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
|| [ B1]   ADD     .L2     4,B4,B4

           ; BRANCHCC OCCURS {$C$L12}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
           NOP             1
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           NOP             3
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   ZERO    .L1     A4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |185| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |185| 
||         ADDKPC  .S2     $C$RL20,B3,0      ; |185| 

$C$RL20:   ; CALL OCCURS {print_test_results} {0}  ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           LDW     .D2T1   *+SP(32),A30      ; |83| 
           LDW     .D2T1   *+SP(48),A3       ; |83| 

           LDW     .D2T1   *+SP(44),A31      ; |83| 
||         MVK     .S2     0xed,B29

           MVKL    .S2     0xc000cccc,B4
||         ZERO    .L1     A29               ; |83| 
||         STW     .D2T2   B12,*+SP(72)      ; |83| 

           MVKL    .S2     0xcccccccd,B31
||         STW     .D2T1   A29,*+SP(84)      ; |188| 

           MVKH    .S2     0xc000cccc,B4
||         STW     .D2T2   B29,*+SP(32)      ; |188| 

           MVKH    .S2     0xcccccccd,B31
||         STW     .D2T2   B4,*+SP(96)       ; |194| 

           STW     .D2T2   B31,*+SP(100)     ; |194| 

           MVKL    .S2     a_ext,B5
||         STW     .D2T1   A3,*+SP(88)       ; |83| 

           MVKH    .S2     a_ext,B5
||         ZERO    .L1     A4
||         STW     .D2T1   A31,*+SP(92)      ; |83| 

           MV      .L2     B5,B30            ; |188| 
||         SET     .S1     A4,0x17,0x17,A4
||         STW     .D2T1   A30,*+SP(80)      ; |83| 

           MV      .L1X    B5,A13            ; |188| 
||         STW     .D2T1   A4,*B30           ; |188| 

           LDW     .D1T1   *A13,A3           ; |190| 
           ZERO    .L2     B12               ; |83| 
           NOP             1
           CALL    .S1     log               ; |190| 
           NOP             1
           SPDP    .S2X    A3,B5:B4          ; |190| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 3
           NOP             2

           DADD    .L1X    0,B5:B4,A5:A4     ; |190| 
||         ADDKPC  .S2     $C$RL21,B3,0      ; |190| 

$C$RL21:   ; CALL OCCURS {log} {0}           ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |190| 
           DPSP    .L1     A5:A4,A3          ; |190| 
           NOP             3
           ADD     .L2     B12,B4,B4         ; |190| 
           STW     .D2T1   A3,*B4            ; |190| 

           CALLP   .S2     logsp,B3
||         LDW     .D1T1   *A13,A4           ; |191| 

$C$RL22:   ; CALL OCCURS {logsp} {0}         ; |191| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |191| 
           NOP             4
           ADD     .L2     B12,B4,B4         ; |191| 
           STW     .D2T1   A4,*B4            ; |191| 

           CALLP   .S2     logsp_c,B3
||         LDW     .D1T1   *A13,A4           ; |192| 

$C$RL23:   ; CALL OCCURS {logsp_c} {0}       ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 97
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |192| 
           LDDW    .D2T1   *+SP(80),A7:A6
           LDW     .D2T1   *+SP(12),A31
           LDW     .D2T2   *+SP(72),B6
           LDW     .D2T2   *+SP(24),B30
           ADD     .L2     B12,B4,B4         ; |192| 
           STW     .D2T1   A4,*B4            ; |192| 
           LDW     .D1T1   *A13,A3           ; |193| 
           LDW     .D2T2   *B6,B6            ; |193| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |83| 
           CMPGTSP .S2X    A3,B30,B0         ; |88| 
           RCPDP   .S1     A5:A4,A5:A4       ; |83| 
           ADD     .L2     B12,B6,B29        ; |193| 

           CLR     .S1     A5,0,16,A8        ; |83| 
||         ZERO    .L1     A4                ; |83| 

           MV      .L1     A8,A5             ; |83| 
           MPYSPDP .M1     A3,A5:A4,A5:A4    ; |83| 
           EXTU    .S1     A8,1,21,A30       ; |83| 
           EXTU    .S1     A8,12,29,A29      ; |83| 
           CMPGTSP .S1     A3,A11,A0         ; |85| 
           ADD     .L2     4,B12,B12         ; |189| 
           NOP             2
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |83| 
           NOP             2
           DPSP    .L1     A7:A6,A4          ; |83| 
           NOP             3
           MPYSP   .M1     A4,A4,A18         ; |83| 
           MPYSP   .M2X    B10,A4,B4         ; |83| 
           NOP             2
           MPYSP   .M1     A31,A18,A17       ; |83| 
           FADDSP  .L2     B11,B4,B4         ; |83| 
           MPYSP   .M1     A18,A18,A16       ; |83| 
           MPYSP   .M1     A18,A4,A9         ; |83| 
           ADD     .L1     A15,A30,A4        ; |83| 
           FADDSP  .L2X    A17,B4,B4         ; |83| 
           INTDP   .L1     A4,A5:A4          ; |83| 
           MPYSP   .M1     A12,A9,A19        ; |83| 

           MPYSP   .M2X    A16,B4,B5         ; |83| 
||         LDDW    .D2T1   *+SP(88),A17:A16  ; |83| 

           LDDW    .D1T1   *+A14[A29],A9:A8  ; |83| 
           MPYSP   .M2X    B13,A18,B31       ; |83| 
           NOP             2
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |83| 
           FADDSP  .L2X    B5,A19,B5         ; |83| 
           NOP             2
           FSUBDP  .L1     A9:A8,A5:A4,A5:A4 ; |83| 
           FADDSP  .L2     B5,B31,B4         ; |83| 
           NOP             1
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |83| 
           SPDP    .S2     B4,B5:B4          ; |83| 
           NOP             2
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |83| 
           NOP             2

           DPSP    .L2     B5:B4,B5          ; |83| 
|| [!A0]   LDW     .D2T2   *+SP(16),B5       ; |88| 

   [ B0]   LDW     .D2T2   *+SP(20),B5       ; |86| 
           NOP             4
           STW     .D2T2   B5,*B29           ; |193| 
           LDW     .D1T2   *A13,B6           ; |194| 
           LDDW    .D2T2   *+SP(96),B5:B4
           NOP             4
           MPYSPDP .M2     B6,B5:B4,B5:B4    ; |194| 
           NOP             6

           DPSP    .L2     B5:B4,B5          ; |194| 
||         LDW     .D2T2   *+SP(32),B4

           NOP             3
           STW     .D1T2   B5,*++A13         ; |194| 

           SUB     .L1X    B4,1,A0           ; |189| 
||         SUB     .L2     B4,1,B4           ; |189| 

   [ A0]   B       .S1     $C$L13            ; |189| 
|| [ A0]   LDW     .D1T1   *A13,A3           ; |190| 
|| [!A0]   MVKL    .S2     output,B12
||         STW     .D2T2   B4,*+SP(32)       ; |194| 

   [!A0]   MVKL    .S1     a_ext,A4
   [!A0]   MVKH    .S2     output,B12
   [ A0]   CALL    .S1     log               ; |190| 
   [!A0]   CALL    .S1     logsp_v           ; |196| 

           SPDP    .S2X    A3,B5:B4          ; |190| 
|| [!A0]   LDW     .D2T2   *+B12(16),B4      ; |196| 

           ; BRANCHCC OCCURS {$C$L13}        ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S1     a_ext,A4
           MVK     .S1     0xed,A6           ; |196| 
           ADDKPC  .S2     $C$RL24,B3,1      ; |196| 
$C$RL24:   ; CALL OCCURS {logsp_v} {0}       ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D2T1   *B12,A4           ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B12(4),B4       ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B12(8),B4       ; |67| 
||         MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B12,A4           ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B12,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B12(12),B4      ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1     A10,A3            ; |68| 
||         MV      .L2     B12,B4            ; |68| 
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL28:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(56),A3       ; |69| 
           LDW     .D2T2   *+SP(60),B4
           MVKL    .S2     fcn_pass,B5
           MVKH    .S2     fcn_pass,B5
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L14            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |200| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   ZERO    .L1     A3                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A4
   [!A0]   MVKH    .S1     all_pass,A4
           ; BRANCHCC OCCURS {$C$L14}        ; |72| 
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
           CALL    .S1     print_test_results ; |200| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |200| 
||         ADDKPC  .S2     $C$RL29,B3,0      ; |200| 

$C$RL29:   ; CALL OCCURS {print_test_results} {0}  ; |200| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ZERO    .L2     B5                ; |114| 

           ZERO    .L2     B4                ; |114| 
||         STW     .D2T2   B5,*+SP(84)       ; |114| 

           STW     .D2T2   B4,*+SP(80)       ; |114| 
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
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         MVKL    .S1     t_offset,A4
||         SUB     .L2     B8,B7,B31         ; |117| 

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A4

           CALL    .S1     gimme_random      ; |210| 
||         STDW    .D1T2   B5:B4,*A4         ; |117| 

           LDW     .D2T2   *+SP(28),B4       ; |210| 
           MVKL    .S1     0x49742410,A4
           MVK     .S2     0x80,B30

           MVKH    .S1     0x49742410,A4
||         STW     .D2T2   B30,*+SP(32)      ; |117| 
||         ZERO    .L1     A13

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL30,B3,0      ; |210| 
$C$RL30:   ; CALL OCCURS {gimme_random} {0}  ; |210| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 86
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |210| 
           NOP             4
           ADD     .L1     A13,A3,A3         ; |210| 

           STW     .D1T1   A4,*A3            ; |210| 
||         MVC     .S2     TSCL,B6           ; |122| 

           MVC     .S2     TSCH,B7           ; |122| 

           SPDP    .S1     A4,A7:A6          ; |83| 
||         ZERO    .L1     A9
||         ZERO    .D1     A8                ; |83| 
||         LDW     .D2T1   *+SP(12),A31      ; |83| 
||         MVKL    .S2     0xfefa39ec,B4

           MVKH    .S2     0xfefa39ec,B4
||         LDW     .D2T2   *+SP(24),B30

           RCPDP   .S1     A7:A6,A7:A6       ; |83| 
           NOP             1

           CLR     .S1     A7,0,16,A5        ; |83| 
||         ZERO    .L1     A6                ; |83| 

           MV      .L1     A5,A7             ; |83| 
||         SET     .S1     A9,0x14,0x1d,A9

           MPYSPDP .M1     A4,A7:A6,A7:A6    ; |83| 
||         EXTU    .S1     A5,12,29,A30      ; |83| 
||         CMPGTSP .S2X    A4,B30,B0         ; |88| 

           MVKL    .S1     output+12,A29
           MVKH    .S1     output+12,A29
           CMPGTSP .S1     A4,A11,A0         ; |85| 
           MVKL    .S1     t_start,A28
           MVKH    .S1     t_start,A28
           STDW    .D1T2   B7:B6,*A28
           FSUBDP  .L1     A7:A6,A9:A8,A9:A8 ; |83| 
           NOP             2
           DPSP    .L1     A9:A8,A3          ; |83| 
           NOP             3
           MPYSP   .M1     A3,A3,A18         ; |83| 
           MPYSP   .M2X    B10,A3,B5         ; |83| 
           NOP             2

           MPYSP   .M1     A31,A18,A17       ; |83| 
||         EXTU    .S1     A5,1,21,A31       ; |83| 

           ADD     .L1     A15,A31,A6        ; |83| 
||         FADDSP  .L2     B11,B5,B8         ; |83| 
||         MPYSP   .M1     A18,A18,A16       ; |83| 
||         MVKL    .S2     0x3fe62e42,B5
||         MPYSP   .M2X    B13,A18,B31       ; |83| 

           INTDP   .L1     A6,A7:A6          ; |83| 
||         MPYSP   .M1     A18,A3,A3         ; |83| 
||         MVKH    .S2     0x3fe62e42,B5

           NOP             2
           FADDSP  .L2X    A17,B8,B8         ; |83| 
           MPYSP   .M1     A12,A3,A3         ; |83| 
           NOP             1
           MPYSP   .M2X    A16,B8,B9         ; |83| 

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |83| 
||         LDDW    .D1T1   *+A14[A30],A7:A6  ; |83| 

           NOP             2

           FADDSP  .L2X    B9,A3,B9          ; |83| 
||         LDW     .D1T1   *A29,A3           ; |214| 

           NOP             1
           FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |83| 
           FADDSP  .L2     B9,B31,B4         ; |83| 
           NOP             1

           FADDDP  .L1     A7:A6,A9:A8,A7:A6 ; |83| 
||         ADD     .S1     A13,A3,A27        ; |214| 

           SPDP    .S2     B4,B5:B4          ; |83| 
           NOP             2
           FADDDP  .L2X    B5:B4,A7:A6,B5:B4 ; |83| 
           NOP             2

           DPSP    .L2     B5:B4,B4          ; |83| 
|| [!A0]   LDW     .D2T2   *+SP(16),B4       ; |214| 

   [ B0]   LDW     .D2T2   *+SP(20),B4       ; |86| 
           NOP             4

           STW     .D1T2   B4,*A27           ; |214| 
||         MVC     .S2     TSCL,B4           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     t_offset,B12
||         MVKL    .S1     t_stop,A3
||         ADD     .L1     4,A13,A13         ; |208| 

           MVKH    .S2     t_offset,B12
||         MVKH    .S1     t_stop,A3

           LDDW    .D2T2   *B12,B17:B16      ; |130| 
||         MVKL    .S2     cycle_counts+24,B8

           MVKH    .S2     cycle_counts+24,B8
||         STDW    .D1T2   B5:B4,*A3         ; |128| 
||         MVKL    .S1     cycle_counts+24,A3

           LDDW    .D2T2   *B8,B19:B18       ; |130| 
||         MVKH    .S1     cycle_counts+24,A3

           NOP             2
           ADDU    .L2     B16,B6,B9:B8      ; |130| 

           ADD     .S2     B9,B17,B6         ; |130| 
||         SUBU    .L2     B4,B8,B9:B8       ; |130| 
||         LDW     .D2T2   *+SP(32),B4       ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
||         EXT     .S2     B9,24,24,B9       ; |130| 

           ADDU    .L2     B18,B8,B7:B6      ; |130| 
||         SUB     .S2     B5,B6,B8          ; |130| 

           ADD     .L2     B7,B19,B7         ; |130| 
||         ADD     .S2     B8,B9,B8          ; |130| 

           ADD     .L2     B7,B8,B7          ; |130| 

           SUB     .L1X    B4,1,A0           ; |208| 
||         SUB     .L2     B4,1,B4           ; |208| 
||         STDW    .D1T2   B7:B6,*A3         ; |130| 

           STW     .D2T2   B4,*+SP(32)       ; |130| 
|| [ A0]   MVKL    .S1     0x49742410,A4
|| [ A0]   B       .S2     $C$L15            ; |208| 
|| [!A0]   LDDW    .D1T1   *A3,A5:A4         ; |135| 

   [ A0]   LDW     .D2T2   *+SP(28),B4       ; |210| 
|| [ A0]   CALL    .S2     gimme_random      ; |210| 
|| [ A0]   MVKH    .S1     0x49742410,A4

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L15}        ; |208| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL31,B3,1      ; |135| 
$C$RL31:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

$C$RL32:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVKL    .S1     cycle_counts+24,A3

           LDDW    .D2T2   *+SP(80),B5:B4
||         MVKH    .S1     cycle_counts+24,A3

           MV      .L2X    A12,B31           ; |114| 
           MV      .L2X    A3,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B10

           STDW    .D2T2   B5:B4,*B10        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVKL    .S1     t_start,A15

           MVKH    .S1     t_start,A15
||         MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 
||         MV      .S2     B12,B13           ; |117| 
||         MVKL    .S1     input,A14

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVKH    .S1     input,A14
||         MVK     .S2     0x80,B11

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A14,A3           ; |222| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |222| 
||         CALL    .S1     logf              ; |222| 

           LDW     .D1T1   *A3,A4            ; |222| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |222| 
$C$RL33:   ; CALL OCCURS {logf} {0}          ; |222| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1X    B11,1,A0          ; |221| 
||         SUB     .L2     B11,1,B11         ; |221| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |222| 
   [ A0]   BNOP    .S1     $C$L16,3          ; |221| 

           ADD     .L1X    A12,B4,A3         ; |222| 
||         ADD     .S1     4,A12,A12         ; |221| 

           STW     .D1T1   A4,*A3            ; |222| 
           ; BRANCHCC OCCURS {$C$L16}        ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MVKL    .S2     t_stop,B11
           MV      .L2     B4,B9             ; |128| 
           LDDW    .D2T2   *B10,B17:B16      ; |130| 
           MVKH    .S2     t_stop,B11
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
           STDW    .D2T2   B9:B8,*B11        ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL34,B3,0      ; |130| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL35:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
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

           STDW    .D1T2   B9:B8,*A15        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
           STDW    .D2T2   B5:B4,*B13        ; |117| 
           LDW     .D1T1   *A14,A3           ; |230| 
           MVK     .S2     0x80,B30
           LDW     .D2T2   *+SP(36),B12      ; |117| 
           STW     .D2T2   B30,*+SP(12)      ; |117| 
           NOP             1

           CALL    .S1     logsp             ; |230| 
||         ADD     .L1     A12,A3,A3         ; |230| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A4            ; |230| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |230| 
$C$RL36:   ; CALL OCCURS {logsp} {0}         ; |230| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *B12,B4           ; |230| 
           NOP             4

           ADD     .L1X    A12,B4,A3         ; |230| 
||         LDW     .D2T2   *+SP(12),B4       ; |230| 

           ADD     .L1     4,A12,A12         ; |229| 
           STW     .D1T1   A4,*A3            ; |230| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |229| 
||         SUB     .L2     B4,1,B4           ; |229| 

   [ A0]   BNOP    .S1     $C$L17,4          ; |229| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |230| 
||         STW     .D2T2   B4,*+SP(12)       ; |230| 

   [ A0]   CALL    .S1     logsp             ; |230| 
||         ADD     .L1     A12,A3,A3         ; |230| 

           ; BRANCHCC OCCURS {$C$L17}        ; |229| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MV      .L2     B4,B9             ; |128| 
           LDDW    .D2T2   *+B10(8),B5:B4    ; |130| 
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
||         MV      .S2     B11,B4            ; |130| 

           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL37,B3,0      ; |130| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 21
           LDDW    .D2T2   *+SP(80),B5:B4
           ADDAD   .D2     B10,1,B11
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B11        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(16)   ; |114| 
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
           LDW     .D1T1   *A14,A3           ; |238| 
           MVK     .S2     0x80,B30
           LDW     .D2T2   *+SP(40),B12      ; |117| 
           STW     .D2T2   B30,*+SP(12)      ; |117| 
           NOP             1

           CALL    .S1     logsp_c           ; |238| 
||         ADD     .L1     A12,A3,A3         ; |238| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A3,A4            ; |238| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |238| 
$C$RL39:   ; CALL OCCURS {logsp_c} {0}       ; |238| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *B12,B4           ; |238| 
           NOP             4

           ADD     .L1X    A12,B4,A3         ; |238| 
||         LDW     .D2T2   *+SP(12),B4       ; |238| 

           ADD     .L1     4,A12,A12         ; |237| 
           STW     .D1T1   A4,*A3            ; |238| 
           NOP             2

           SUB     .L1X    B4,1,A0           ; |237| 
||         SUB     .L2     B4,1,B4           ; |237| 

   [ A0]   BNOP    .S1     $C$L18,4          ; |237| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |238| 
||         STW     .D2T2   B4,*+SP(12)       ; |238| 

   [ A0]   CALL    .S1     logsp_c           ; |238| 
||         ADD     .L1     A12,A3,A3         ; |238| 

           ; BRANCHCC OCCURS {$C$L18}        ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D2T2   *B13,B7:B6        ; |130| 
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 

           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B4          ; |130| 
||         SUBU    .L2     B8,B4,B7:B6       ; |130| 

           MV      .L2     B6,B5             ; |130| 
||         ADD     .S2X    B4,A5,B4          ; |130| 
||         CALL    .S1     __c6xabi_fltllif  ; |130| 

           SUB     .D2     B9,B4,B4          ; |130| 
||         ADDU    .L2     B16,B5,B7:B6      ; |130| 
||         EXT     .S2     B7,24,24,B5       ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         ADD     .S2     B7,B17,B4         ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MVKL    .S2     t_stop,B4

           MVKH    .S2     t_stop,B4

           STDW    .D2T2   B9:B8,*B4         ; |128| 
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL40,B3,0      ; |130| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL41:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(80),B5:B4
           ADDAD   .D2     B11,1,B12
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A15        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           MVKL    .S1     output,A12
||         ADD     .L2     B4,B5,B7          ; |117| 

           MVKH    .S1     output,A12
||         MV      .L2X    A14,B9            ; |245| 
||         STDW    .D2T2   B7:B6,*B13        ; |117| 

           CALLP   .S2     logsp_v,B3
||         LDW     .D1T2   *+A12(16),B4      ; |245| 
||         LDW     .D2T1   *B9,A4            ; |245| 
||         MVK     .S1     0x80,A6           ; |245| 

$C$RL42:   ; CALL OCCURS {logsp_v} {0}       ; |245| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A9:A8        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MVK     .S1     16,A14
           ADD     .L1X    B12,A14,A14
           MVKL    .S1     t_stop,A3

           LDDW    .D1T1   *A14,A17:A16      ; |130| 
||         MVKH    .S1     t_stop,A3

           ADDU    .L1X    B6,A8,A5:A4       ; |130| 

           MV      .L2     B4,B9             ; |128| 
||         MV      .S2X    A3,B4             ; |128| 
||         ADD     .L1X    A5,B7,A3          ; |130| 

           SUBU    .L1X    B8,A4,A7:A6       ; |130| 

           ADD     .L1     A3,A9,A3          ; |130| 
||         EXT     .S1     A7,24,24,A7       ; |130| 

           SUB     .S1X    B9,A3,A3          ; |130| 
||         ADDU    .L1     A16,A6,A5:A4      ; |130| 

           ADD     .L1     A5,A17,A3         ; |130| 
||         ADD     .S1     A3,A7,A5          ; |130| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           MPYSP   .M1     A11,A4,A3         ; |130| 
           MV      .L1     A13,A5            ; |130| 
           ZERO    .L1     A4                ; |130| 
           NOP             2
           SPDP    .S1     A3,A7:A6          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |130| 

$C$RL44:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6

           STDW    .D1T1   A5:A4,*A14        ; |130| 
||         MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D1T2   *+A12(4),B4       ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     fcn_pass,B10
           MVKH    .S2     0x3ee4f8b5,B7
           MVKH    .S2     0x88e368f1,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A12,A4           ; |67| 
||         MVKH    .S2     fcn_pass,B10

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A12(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A12(12),B4      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL47:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         LDW     .D1T2   *A10,B4           ; |69| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A12,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL48:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(64),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(68),B4
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
   [!B0]   ZERO    .L1     A0                ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L20            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |251| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L20}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |251| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           ZERO    .L1     A3                ; |72| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |251| 
||         ADDKPC  .S2     $C$RL49,B3,0      ; |251| 

$C$RL49:   ; CALL OCCURS {print_test_results} {0}  ; |251| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL50:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |252| 

$C$RL51:   ; CALL OCCURS {printf} {0}        ; |252| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |259| 

$C$RL52:   ; CALL OCCURS {print_profile_results} {0}  ; |259| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |262| 

$C$RL53:   ; CALL OCCURS {print_memory_results} {0}  ; |262| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(112),B3     ; |263| 
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
$C$SL1:	.string	"logSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	log
	.global	logf
	.global	__c6xabi_isinff
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	logsp
	.global	logsp_c
	.global	logsp_v
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
	.global	logtable
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
