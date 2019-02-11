;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:25:00 2013                                *
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
	.word	04095f1dfh		; a[0] @ 0
	.word	0c08c7117h		; a[1] @ 32
	.word	0c0c71a0fh		; a[2] @ 64
	.word	0403e4c45h		; a[3] @ 96
	.word	0c05963a3h		; a[4] @ 128
	.word	04068e0f4h		; a[5] @ 160
	.word	0bfe6080bh		; a[6] @ 192
	.word	0c0aedd23h		; a[7] @ 224
	.word	0c07f15b0h		; a[8] @ 256
	.word	0bf0eff92h		; a[9] @ 288
	.word	04078f59eh		; a[10] @ 320
	.word	0bfa88ff6h		; a[11] @ 352
	.word	0c0ae08f3h		; a[12] @ 384
	.word	0c070f6e8h		; a[13] @ 416
	.word	04095b49ch		; a[14] @ 448
	.word	0beedf41eh		; a[15] @ 480
	.word	03f855e62h		; a[16] @ 512
	.word	0bf84a9d4h		; a[17] @ 544
	.word	0bf99cabch		; a[18] @ 576
	.word	0c00b2a54h		; a[19] @ 608
	.word	04047a123h		; a[20] @ 640
	.word	0408b1771h		; a[21] @ 672
	.word	03fa541c7h		; a[22] @ 704
	.word	0bfa2cd43h		; a[23] @ 736
	.word	040ad4d10h		; a[24] @ 768
	.word	03f54e1ach		; a[25] @ 800
	.word	0c0c1ea2eh		; a[26] @ 832
	.word	0bf41de51h		; a[27] @ 864
	.word	0408f3b52h		; a[28] @ 896
	.word	0c0c5a714h		; a[29] @ 928
	.word	03ebf564dh		; a[30] @ 960
	.word	03f03ffb8h		; a[31] @ 992
	.word	03f7e1d3eh		; a[32] @ 1024
	.word	040b2caf9h		; a[33] @ 1056
	.word	0bfcd56ffh		; a[34] @ 1088
	.word	0c08dd3e3h		; a[35] @ 1120
	.word	03d46887bh		; a[36] @ 1152
	.word	0be4b41fch		; a[37] @ 1184
	.word	0c096dca5h		; a[38] @ 1216
	.word	0c0b70dd5h		; a[39] @ 1248
	.word	0bfd26d42h		; a[40] @ 1280
	.word	0c0a7f0d0h		; a[41] @ 1312
	.word	0401e0a14h		; a[42] @ 1344
	.word	0bfdee7e6h		; a[43] @ 1376
	.word	0c0322602h		; a[44] @ 1408
	.word	03f194de5h		; a[45] @ 1440
	.word	0bfde853ah		; a[46] @ 1472
	.word	03f7051bbh		; a[47] @ 1504
	.word	03ffd4075h		; a[48] @ 1536
	.word	0c0c000c0h		; a[49] @ 1568
	.word	0402e59d8h		; a[50] @ 1600
	.word	0bb269454h		; a[51] @ 1632
	.word	0c029b5e8h		; a[52] @ 1664
	.word	040c898a3h		; a[53] @ 1696
	.word	0402a54e6h		; a[54] @ 1728
	.word	0c029222ah		; a[55] @ 1760
	.word	0c028f5f1h		; a[56] @ 1792
	.word	0c01eea1eh		; a[57] @ 1824
	.word	03ff12363h		; a[58] @ 1856
	.word	0bef15828h		; a[59] @ 1888
	.word	0c0949d86h		; a[60] @ 1920
	.word	0c09a5001h		; a[61] @ 1952
	.word	0c08a181eh		; a[62] @ 1984
	.word	04091b025h		; a[63] @ 2016
	.word	03fbeaae4h		; a[64] @ 2048
	.word	040b652cch		; a[65] @ 2080
	.word	0c05c22ech		; a[66] @ 2112
	.word	0400cb2b9h		; a[67] @ 2144
	.word	040a3f9b6h		; a[68] @ 2176
	.word	040174ad0h		; a[69] @ 2208
	.word	0c0840c7bh		; a[70] @ 2240
	.word	0bf359565h		; a[71] @ 2272
	.word	0be07c44fh		; a[72] @ 2304
	.word	03e84e3c4h		; a[73] @ 2336
	.word	04005ea76h		; a[74] @ 2368
	.word	0c0b880a2h		; a[75] @ 2400
	.word	0c0677014h		; a[76] @ 2432
	.word	0c0c59c50h		; a[77] @ 2464
	.word	0403629b3h		; a[78] @ 2496
	.word	0401f6426h		; a[79] @ 2528
	.word	0c0455297h		; a[80] @ 2560
	.word	0c0b93054h		; a[81] @ 2592
	.word	04021a8f9h		; a[82] @ 2624
	.word	040c08d23h		; a[83] @ 2656
	.word	0c08d41c1h		; a[84] @ 2688
	.word	0409000e0h		; a[85] @ 2720
	.word	0c026983bh		; a[86] @ 2752
	.word	0406b8f4eh		; a[87] @ 2784
	.word	040579505h		; a[88] @ 2816
	.word	0c0b94257h		; a[89] @ 2848
	.word	03f223777h		; a[90] @ 2880
	.word	0bfade7d9h		; a[91] @ 2912
	.word	0c0109a6bh		; a[92] @ 2944
	.word	03e93d47ch		; a[93] @ 2976
	.word	0408c008fh		; a[94] @ 3008
	.word	0bfbff0c7h		; a[95] @ 3040
	.word	0bfd12b00h		; a[96] @ 3072
	.word	03f5848bah		; a[97] @ 3104
	.word	040afdc3ah		; a[98] @ 3136
	.word	040225ffbh		; a[99] @ 3168
	.word	04080a0bfh		; a[100] @ 3200
	.word	0406d8b1dh		; a[101] @ 3232
	.word	040958402h		; a[102] @ 3264
	.word	03fdac174h		; a[103] @ 3296
	.word	040a694cbh		; a[104] @ 3328
	.word	0c08ba564h		; a[105] @ 3360
	.word	0c0a65fefh		; a[106] @ 3392
	.word	040787db9h		; a[107] @ 3424
	.word	0c04ba3efh		; a[108] @ 3456
	.word	040b676d7h		; a[109] @ 3488
	.word	0c002c3c0h		; a[110] @ 3520
	.word	0c06ad73dh		; a[111] @ 3552
	.word	0404b6bc9h		; a[112] @ 3584
	.word	04089dc4eh		; a[113] @ 3616
	.word	040371514h		; a[114] @ 3648
	.word	0c0915945h		; a[115] @ 3680
	.word	04028b551h		; a[116] @ 3712
	.word	0406fcb57h		; a[117] @ 3744
	.word	0402b0813h		; a[118] @ 3776
	.word	0c03b30e4h		; a[119] @ 3808
	.word	0403ab170h		; a[120] @ 3840
	.word	0c0890b96h		; a[121] @ 3872
	.word	0c0a80f35h		; a[122] @ 3904
	.word	03f98335ch		; a[123] @ 3936
	.word	0406e2614h		; a[124] @ 3968
	.word	03fa5ecefh		; a[125] @ 4000
	.word	040c0924bh		; a[126] @ 4032
	.word	0bea3a882h		; a[127] @ 4064
	.word	0c06e2f97h		; a[128] @ 4096
	.word	0c08d2fd8h		; a[129] @ 4128
	.word	040973a5ch		; a[130] @ 4160
	.word	03f9891a4h		; a[131] @ 4192
	.word	03fb87e16h		; a[132] @ 4224
	.word	0c086cabfh		; a[133] @ 4256
	.word	03fad5579h		; a[134] @ 4288
	.word	040c6236ah		; a[135] @ 4320
	.word	0c0c1caeeh		; a[136] @ 4352
	.word	0bfec4d1fh		; a[137] @ 4384
	.word	0c00559a0h		; a[138] @ 4416
	.word	0c0b7ae5fh		; a[139] @ 4448
	.word	040519d65h		; a[140] @ 4480
	.word	04058ac44h		; a[141] @ 4512
	.word	03f6a4184h		; a[142] @ 4544
	.word	0be896784h		; a[143] @ 4576
	.word	03e934b9eh		; a[144] @ 4608
	.word	04070bd9eh		; a[145] @ 4640
	.word	0c07f0986h		; a[146] @ 4672
	.word	0bfdf1bb5h		; a[147] @ 4704
	.word	0c004c5d7h		; a[148] @ 4736
	.word	0c07676ach		; a[149] @ 4768
	.word	0bfebab35h		; a[150] @ 4800
	.word	0c0a14107h		; a[151] @ 4832
	.word	03f4f6464h		; a[152] @ 4864
	.word	0c0bbe871h		; a[153] @ 4896
	.word	03fdf7262h		; a[154] @ 4928
	.word	0bf0a8eaah		; a[155] @ 4960
	.word	040af9166h		; a[156] @ 4992
	.word	0403d2c73h		; a[157] @ 5024
	.word	040a8ab7ch		; a[158] @ 5056
	.word	03e6e2677h		; a[159] @ 5088
	.word	03d01d10bh		; a[160] @ 5120
	.word	0c0a708feh		; a[161] @ 5152
	.word	0bf589632h		; a[162] @ 5184
	.word	0403de70fh		; a[163] @ 5216
	.word	040061a45h		; a[164] @ 5248
	.word	0c07f333bh		; a[165] @ 5280
	.word	04045faa9h		; a[166] @ 5312
	.word	0409dafeeh		; a[167] @ 5344
	.word	0c0828395h		; a[168] @ 5376
	.word	0be1441f1h		; a[169] @ 5408
	.word	040682d07h		; a[170] @ 5440
	.word	0c0996e9eh		; a[171] @ 5472
	.word	0c0971224h		; a[172] @ 5504
	.word	0407ce2f7h		; a[173] @ 5536
	.word	0407a3f4bh		; a[174] @ 5568
	.word	0409c3e21h		; a[175] @ 5600
	.word	040b08ebdh		; a[176] @ 5632
	.word	0c024b39bh		; a[177] @ 5664
	.word	0bf62957bh		; a[178] @ 5696
	.word	0c0c1f7efh		; a[179] @ 5728
	.word	0bf9cb353h		; a[180] @ 5760
	.word	0bf78bd0fh		; a[181] @ 5792
	.word	03f840d6fh		; a[182] @ 5824
	.word	04005f160h		; a[183] @ 5856
	.word	03fe6b050h		; a[184] @ 5888
	.word	0c0bcd581h		; a[185] @ 5920
	.word	03f806c06h		; a[186] @ 5952
	.word	0c0028556h		; a[187] @ 5984
	.word	0c09a5937h		; a[188] @ 6016
	.word	0c025f1aeh		; a[189] @ 6048
	.word	0c0b74140h		; a[190] @ 6080
	.word	0409a0d85h		; a[191] @ 6112
	.word	03fd5770dh		; a[192] @ 6144
	.word	0403ec629h		; a[193] @ 6176
	.word	040bb632dh		; a[194] @ 6208
	.word	0bd3deee3h		; a[195] @ 6240
	.word	0bff07608h		; a[196] @ 6272
	.word	0c064a4bch		; a[197] @ 6304
	.word	040050ddbh		; a[198] @ 6336
	.word	0402b0acbh		; a[199] @ 6368
	.word	04051ca9dh		; a[200] @ 6400

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\114642 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\114644 
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
||         MVKL    .S2     output,B11

           CALL    .S1     atanf             ; |127| 
||         MV      .L1     A11,A12
||         MV      .D1X    B4,A10
||         MVKH    .S2     output,B11
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |127| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |127| 
$C$RL1:    ; CALL OCCURS {atanf} {0}         ; |127| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |127| 
||         SUB     .L1     A10,1,A0          ; |126| 
||         SUB     .S1     A10,1,A10         ; |126| 

   [ A0]   BNOP    .S1     $C$L1,3           ; |126| 
|| [!A0]   MVK     .S2     0xc9,B5

           ADD     .L2     B10,B4,B4         ; |127| 
||         ADD     .S2     4,B10,B10         ; |126| 

   [ A0]   CALL    .S1     atanf             ; |127| 
||         STW     .D2T1   A4,*B4            ; |127| 
|| [!A0]   ADD     .L2     4,B11,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |126| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           CALL    .S1     atansp            ; |130| 
||         ZERO    .L2     B10
||         MV      .L1X    B5,A10
||         MV      .D1     A11,A15
||         STW     .D2T2   B4,*+SP(40)

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |130| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |130| 
$C$RL2:    ; CALL OCCURS {atansp} {0}        ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(40),B4       ; |130| 
           SUB     .L1     A10,1,A0          ; |129| 
           SUB     .L1     A10,1,A10         ; |129| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |130| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |129| 

           ADD     .L2     B10,B4,B4         ; |130| 
||         ADD     .S2     4,B10,B10         ; |129| 

   [ A0]   CALL    .S1     atansp            ; |130| 
||         STW     .D2T1   A4,*B4            ; |130| 

           ; BRANCHCC OCCURS {$C$L2}         ; |129| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D2T2   *+SP(40),B4
           MVK     .S2     0xc9,B5
           ZERO    .L2     B10
           MV      .L1     A15,A11
           MV      .L1X    B5,A10
           ADD     .L2     4,B4,B4

           STW     .D2T2   B4,*+SP(44)
||         CALL    .S1     atansp_c          ; |133| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |133| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |133| 
$C$RL3:    ; CALL OCCURS {atansp_c} {0}      ; |133| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(44),B4       ; |133| 
           SUB     .L1     A10,1,A0          ; |132| 
           SUB     .L1     A10,1,A10         ; |132| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |133| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |132| 

           ADD     .L2     B10,B4,B4         ; |133| 
||         ADD     .S2     4,B10,B10         ; |132| 

   [ A0]   CALL    .S1     atansp_c          ; |133| 
||         STW     .D2T1   A4,*B4            ; |133| 

           ; BRANCHCC OCCURS {$C$L3}         ; |132| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(44),B4
||         MVKL    .S1     0x3d21435c,A3
||         MVKL    .S2     0xbe11271d,B8
||         ZERO    .L1     A4
||         ZERO    .D1     A6
||         MV      .L2X    A15,B16

           MVKH    .S1     0x3d21435c,A3
||         MVKL    .S2     0xbc647bb5,B7
||         ZERO    .L2     B24               ; |110| 

           MVKL    .S1     0xbeaaaa23,A12
||         MVKL    .S2     0x3dd77af5,B5
||         STW     .D2T1   A3,*+SP(12)

           SET     .S1     A6,0x17,0x1d,A3
||         MVKH    .S2     0xbe11271d,B8
||         MV      .L2X    A3,B21

           SET     .S1     A4,0x1e,0x1e,A4
||         MVKH    .S2     0xbc647bb5,B7
||         STW     .D2T2   B8,*+SP(24)

           MVKH    .S1     0xbeaaaa23,A12
||         MVKH    .S2     0x3dd77af5,B5
||         ADD     .L2     4,B4,B9
||         MV      .L1X    B8,A6
||         STW     .D2T2   B7,*+SP(16)

           MVKL    .S2     0x3b16d624,B6
||         MVKL    .S1     0xbd942fbf,A14
||         LDW     .D2T2   *B9,B17
||         ZERO    .L1     A4                ; |110| 
||         MV      .L2X    A4,B22

           MVKL    .S1     0x3e4cb0c1,A5
||         MVKL    .S2     0x3fc90fdb,B31
||         STW     .D2T2   B9,*+SP(48)
||         MV      .L2X    A12,B19

           MVKH    .S2     0x3b16d624,B6
||         MVKH    .S1     0xbd942fbf,A14
||         STW     .D2T2   B5,*+SP(28)
||         MV      .L2X    A3,B23

           MVKH    .S1     0x3e4cb0c1,A5
||         MVKH    .S2     0x3fc90fdb,B31
||         MV      .L1     A14,A9
||         MV      .L2     B6,B20

           MVK     .S1     0xc9,A8
||         MV      .L1     A5,A7
||         STW     .D2T1   A5,*+SP(20)
||         MV      .D1X    B5,A5
||         MV      .L2     B31,B18
||         DINT                              ; interrupts off

           SUB     .L1     A8,1,A1
||         MV      .S1X    B7,A8
||         STW     .D2T2   B31,*+SP(32)

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/atansp/atansp_d.c
;*      Loop source line                 : 135
;*      Loop opening brace source line   : 135
;*      Loop closing brace source line   : 137
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 75
;*      Unpartitioned Resource Bound     : 10
;*      Partitioned Resource Bound(*)    : 15
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     2        5     
;*      .D units                     0        2     
;*      .M units                     5       15*    
;*      .X cross paths               6        4     
;*      .T address paths             0        2     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           3        9     (.L or .S unit)
;*      Addition ops (.LSD)          2        9     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             3        7     
;*      Bound(.L .S .D .LS .LSD)     3        9     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 75 Did not find schedule
;*         ii = 76 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: | *  ******                      |         *      **********      |
;*       1: | *  ******                      |         *      **********      |
;*       2: | *  ******                      |         *      **********      |
;*       3: | *  ******                      |         *      **********      |
;*       4: | *  ******                      |         *      **********      |
;*       5: | *  ******                      |      *  *      **********      |
;*       6: | *  ******                      |    * *  *      **********      |
;*       7: | *  ******                      |*     *  *      **********      |
;*       8: | *  ******                      |*   * *  *      **********      |
;*       9: | *  ******                      |*   * ** *      **********      |
;*      10: | *  ******                      |*   * ** *      **********      |
;*      11: | *  ******                      |*   * ** *      **********      |
;*      12: | *  ******                      |*   * ** *      **********      |
;*      13: | *  ******                      |*   **** *      **********      |
;*      14: | *  ******                      |*   * ** *      **********      |
;*      15: | *  ******                      |*   * ** *      **********      |
;*      16: | *  ******                      |*   **** *      **********      |
;*      17: | *  ******                      |*   * *  *      **********      |
;*      18: | *  ******                      |*   * *  *      **********      |
;*      19: | *  ******                      |*   * *  *      **********      |
;*      20: | *  ******                      |*   ***  *      **********      |
;*      21: | *  ******                      |*    **  *      **********      |
;*      22: | *  ******                      |*    **  *      **********      |
;*      23: | *  ******                      |*    **  *      **********      |
;*      24: | *  ******                      |*   ***  *      **********      |
;*      25: | *  ******                      |*    **  *      **********      |
;*      26: | *  ******                      |*    **  *      **********      |
;*      27: | *  ******                      |*   ***  *      **********      |
;*      28: | *  ******                      |*     *  *      **********      |
;*      29: | *  ******                      |*     *  *      **********      |
;*      30: |** *******                      |**    *  *      **********      |
;*      31: |** *******                      | *  * *  *      **********      |
;*      32: |**  ******                      |*   *    *      **********      |
;*      33: |**  ******                      |*   * *  *      **********      |
;*      34: |**  ******                      |*   * *  *      **********      |
;*      35: |**  ******                      |*   * ** *      **********      |
;*      36: |**  ******                      |*   * ** *      **********      |
;*      37: |**  ******                      |*   * ** *      **********      |
;*      38: |**  ******                      |*   * ** *      **********      |
;*      39: |**  ******                      |*   * ****      **********      |
;*      40: |**  ******                      |*   * ****      **********      |
;*      41: |**  ******                      |*   * ****      **********      |
;*      42: |**  ******                      |*   * ****      **********      |
;*      43: |**  ******                      |*   ******      **********      |
;*      44: |**  ******                      |*   **** *      ***********     |
;*      45: |**  ******                      |*   **** *      ***********     |
;*      46: |**  ******                      |*   **** *      ***********     |
;*      47: |**  ******      *               |*   ******      ***********     |
;*      48: |** *******      *               |*   ******      ************    |
;*      49: |** *******                      |*   ******      ***********     |
;*      50: |**  ******                      |*   * ****      **********      |
;*      51: |**  ******                      |*   ******      **********      |
;*      52: |** *******       *              |*   **** *      **********      |
;*      53: |** *******       *              |*   **** *      **********      |
;*      54: |** *******      **              |*   ******      **********      |
;*      55: |**  ******       *              |*   * ** *      **********      |
;*      56: |**  ******      **              |*   * ** *      **********      |
;*      57: |** *******      **              |*   * ** *      **********      |
;*      58: |**  ******      *               |*   **** *      **********      |
;*      59: |**  ******                      |*   * ** *      **********      |
;*      60: |** *******                      |*   * ** *      **********      |
;*      61: |** *******                      |*   **** *      **********      |
;*      62: |**  ******                      |*   * ** *      **********      |
;*      63: |**  ******                      |*   * ** *      **********      |
;*      64: |**  ******                      |*   **** *      **********      |
;*      65: |**  ******                      |*   * ** *      **********      |
;*      66: |**  ******                      |*   * ** *      **********      |
;*      67: |**  ******                      |*   * ** *      **********      |
;*      68: |**  ******                      |*   **** *      **********      |
;*      69: |**  ******                      |*   * *  *      **********      |
;*      70: |**  ******                      |*   * *  *      **********      |
;*      71: |**  ******                      |*   ***  *      **********      |
;*      72: | *  ******                      |*   * *  *      **********      |
;*      73: | *  ******                      |*   * *  *      **********      |
;*      74: | *  ******                      |*   * *  *      **********      |
;*      75: | *  ******                      |    * *  *      **********      |
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
;*      Total cycles (est.)         : 0 + min_trip_cnt * 76 = 15276        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             A1,1,A1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C129:
;*   0              LDW     .D2T2   *B16++,B6         ; |136|  ^ 
;*   1              NOP             4
;*   5              ABSSP   .S2     B6,B4             ; |130|  ^ 
;*   6              CMPGTSP .S2     B4,B23,B0         ; |130|  ^ 
;*   7      [!B0]   MV      .S2     B23,B4            ; |123|  ^ 
;*     ||   [ B0]   MV      .L2     B6,B4             ; |131|  ^ 
;*   8              RCPSP   .S2     B4,B7             ; |98|  ^ 
;*   9              MPYSP   .M2     B4,B7,B5          ; |98|  ^ 
;*  10              NOP             3
;*  13              FSUBSP  .L2     B22,B5,B5         ; |98|  ^ 
;*  14              NOP             2
;*  16              MPYSP   .M2     B7,B5,B5          ; |98|  ^ 
;*  17              NOP             3
;*  20              MPYSP   .M2     B4,B5,B4          ; |98|  ^ 
;*  21              NOP             3
;*  24              FSUBSP  .L2     B22,B4,B4         ; |98|  ^ 
;*  25              NOP             2
;*  27              MPYSP   .M2     B5,B4,B4          ; |98|  ^ 
;*  28              NOP             1
;*  29              CMPLTSP .S2     B6,B24,B1         ; |127| 
;*     ||   [!B0]   ZERO    .L1     A0                ; |125| 
;*     ||   [ B0]   MVK     .D1     0x1,A0            ; |133| 
;*     ||           SET     .S1     A4,31,31,A3       ; |110| 
;*  30      [ B0]   MV      .L2     B23,B6            ; |132| 
;*     ||   [!A0]   MV      .D2     B24,B25           ; |110| 
;*     ||   [ A0]   MV      .S2     B18,B25           ; |110| 
;*  31              MPYSP   .M2     B6,B4,B7          ; |98|  ^ 
;*     ||   [ B1]   XOR     .L2X    B25,A3,B4         ; |110| 
;*     ||   [!B1]   MV      .D2     B25,B4            ; |110| 
;*     ||           CMPEQSP .S2     B6,B24,B0         ; |110| 
;*  32      [ B0]   MV      .L2     B24,B6            ; |110| 
;*  33              NOP             2
;*  35              MPYSP   .M2     B7,B7,B8          ; |98|  ^ 
;*  36              NOP             3
;*  39              MPYSP   .M2     B8,B8,B5          ; |98|  ^ 
;*  40              MPYSP   .M2     B19,B8,B26        ; |107| 
;*  41              NOP             2
;*  43              MPYSP   .M2     B5,B8,B8          ; |107|  ^ 
;*     ||           MPYSP   .M1X    A8,B8,A16         ; |107| 
;*  44              MPYSP   .M1X    A7,B5,A3          ; |107| 
;*     ||           MPYSP   .M2     B20,B5,B27        ; |107|  ^ 
;*  45              MPYSP   .M2     B5,B5,B8          ; |107| 
;*  46              NOP             1
;*  47              MPYSP   .M2     B5,B8,B5          ; |107|  ^ 
;*  48              MPYSP   .M1X    A6,B8,A3          ; |107| 
;*     ||           FADDSP  .L2X    A16,B27,B8        ; |107|  ^ 
;*  49              FADDSP  .L1X    B26,A3,A17        ; |107| 
;*     ||           MPYSP   .M2     B5,B8,B5          ; |107| 
;*  50              MPYSP   .M1X    A5,B8,A16         ; |107| 
;*  51              FADDSP  .L2     B21,B8,B8         ; |107|  ^ 
;*  52              MPYSP   .M1X    A9,B5,A16         ; |107|  ^ 
;*  53              NOP             1
;*  54              FADDSP  .L1     A3,A16,A3         ; |107| 
;*     ||           MPYSP   .M2     B5,B8,B5          ; |107|  ^ 
;*  55              NOP             2
;*  57              FADDSP  .L1     A17,A3,A3         ; |107| 
;*  58              FADDSP  .L2X    A16,B5,B5         ; |107|  ^ 
;*  59              NOP             2
;*  61              FADDSP  .L2X    B5,A3,B5          ; |107|  ^ 
;*  62              NOP             2
;*  64              MPYSP   .M2     B7,B5,B5          ; |107|  ^ 
;*  65              NOP             3
;*  68              FADDSP  .L2     B7,B5,B5          ; |107|  ^ 
;*  69              NOP             1
;*  70      [ A1]   BDEC    .S1     $C$C129,A1        ; |135| 
;*  71      [ A0]   FSUBSP  .L2     B4,B5,B9          ; |110|  ^ 
;*     ||   [!A0]   FADDSP  .S2     B5,B4,B9          ; |110|  ^ 
;*  72              NOP             2
;*  74      [!B0]   MV      .L2     B9,B6             ; |110|  ^ 
;*  75              STW     .D2T2   B6,*B17++         ; |110|  ^ 
;*  76              ; BRANCHCC OCCURS {$C$C129}       ; |135| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 76
           LDW     .D2T2   *B16++,B6         ; |136| <0,0>  ^ 
           NOP             4
           ABSSP   .S2     B6,B4             ; |130| <0,5>  ^ 
           CMPGTSP .S2     B4,B23,B0         ; |130| <0,6>  ^ 

   [ B0]   MV      .L2     B6,B4             ; |131| <0,7>  ^ 
|| [!B0]   MV      .S2     B23,B4            ; |123| <0,7>  ^ 

           RCPSP   .S2     B4,B7             ; |98| <0,8>  ^ 
           MPYSP   .M2     B4,B7,B5          ; |98| <0,9>  ^ 
           NOP             3
           FSUBSP  .L2     B22,B5,B5         ; |98| <0,13>  ^ 
           NOP             2
           MPYSP   .M2     B7,B5,B5          ; |98| <0,16>  ^ 
           NOP             3
           MPYSP   .M2     B4,B5,B4          ; |98| <0,20>  ^ 
           NOP             3
           FSUBSP  .L2     B22,B4,B4         ; |98| <0,24>  ^ 
           NOP             2
           MPYSP   .M2     B5,B4,B4          ; |98| <0,27>  ^ 
           NOP             1

           SET     .S1     A4,31,31,A3       ; |110| <0,29> 
||         CMPLTSP .S2     B6,B24,B1         ; |127| <0,29> 
|| [!B0]   ZERO    .L1     A0                ; |125| <0,29> 
|| [ B0]   MVK     .D1     0x1,A0            ; |133| <0,29> 

   [ B0]   MV      .L2     B23,B6            ; |132| <0,30> 
|| [ A0]   MV      .S2     B18,B25           ; |110| <0,30> 
|| [!A0]   MV      .D2     B24,B25           ; |110| <0,30> 

           CMPEQSP .S2     B6,B24,B0         ; |110| <0,31> 
|| [ B1]   XOR     .L2X    B25,A3,B4         ; |110| <0,31> 
|| [!B1]   MV      .D2     B25,B4            ; |110| <0,31> 
||         MPYSP   .M2     B6,B4,B7          ; |98| <0,31>  ^ 

   [ B0]   MV      .L2     B24,B6            ; |110| <0,32> 
           NOP             2
           MPYSP   .M2     B7,B7,B8          ; |98| <0,35>  ^ 
           NOP             3
           MPYSP   .M2     B8,B8,B5          ; |98| <0,39>  ^ 
           MPYSP   .M2     B19,B8,B26        ; |107| <0,40> 
           NOP             2

           MPYSP   .M1X    A8,B8,A16         ; |107| <0,43> 
||         MPYSP   .M2     B5,B8,B8          ; |107| <0,43>  ^ 

           MPYSP   .M1X    A7,B5,A3          ; |107| <0,44> 
||         MPYSP   .M2     B20,B5,B27        ; |107| <0,44>  ^ 

           MPYSP   .M2     B5,B5,B8          ; |107| <0,45> 
           NOP             1
           MPYSP   .M2     B5,B8,B5          ; |107| <0,47>  ^ 

           MPYSP   .M1X    A6,B8,A3          ; |107| <0,48> 
||         FADDSP  .L2X    A16,B27,B8        ; |107| <0,48>  ^ 

           FADDSP  .L1X    B26,A3,A17        ; |107| <0,49> 
||         MPYSP   .M2     B5,B8,B5          ; |107| <0,49> 

           MPYSP   .M1X    A5,B8,A16         ; |107| <0,50> 
           FADDSP  .L2     B21,B8,B8         ; |107| <0,51>  ^ 
           MPYSP   .M1X    A9,B5,A16         ; |107| <0,52>  ^ 
           NOP             1

           FADDSP  .L1     A3,A16,A3         ; |107| <0,54> 
||         MPYSP   .M2     B5,B8,B5          ; |107| <0,54>  ^ 

           NOP             2
           FADDSP  .L1     A17,A3,A3         ; |107| <0,57> 
           FADDSP  .L2X    A16,B5,B5         ; |107| <0,58>  ^ 
           NOP             2
           FADDSP  .L2X    B5,A3,B5          ; |107| <0,61>  ^ 
           NOP             2
           MPYSP   .M2     B7,B5,B5          ; |107| <0,64>  ^ 
           NOP             3
           FADDSP  .L2     B7,B5,B5          ; |107| <0,68>  ^ 
           NOP             1
   [ A1]   BDEC    .S1     $C$L5,A1          ; |135| <0,70> 

   [!A0]   FADDSP  .S2     B5,B4,B9          ; |110| <0,71>  ^ 
|| [ A0]   FSUBSP  .L2     B4,B5,B9          ; |110| <0,71>  ^ 

           NOP             2
   [!B0]   MV      .L2     B9,B6             ; |110| <0,74>  ^ 
           STW     .D2T2   B6,*B17++         ; |110| <0,75>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A6,*+SP(24)
           STW     .D2T2   B18,*+SP(32)
           STW     .D2T1   A8,*+SP(16)

           MV      .L1X    B19,A12
||         STW     .D2T1   A7,*+SP(20)

           MV      .L1X    B20,A13
||         STW     .D2T1   A5,*+SP(28)

           RINT                              ; interrupts on
||         STW     .D2T2   B21,*+SP(12)
||         MV      .L1X    B22,A11
||         MV      .S1     A15,A4            ; |138| 

           CALLP   .S2     atansp_v,B3
||         LDW     .D2T2   *+B11(16),B4      ; |138| 
||         MVK     .S1     0xc9,A6           ; |138| 
||         MV      .L1     A9,A14
||         MV      .D1X    B23,A10
||         MV      .L2     B24,B10

$C$RL4:    ; CALL OCCURS {atansp_v} {0}      ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 48
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0xa0b5ed8d,B6

           MV      .L2     B11,B5
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4

           LDW     .D2T1   *+SP(48),A3       ; |68| 
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B4
           MVKL    .S2     output,B31
           MVKH    .S2     0xa0b5ed8d,B6

           ADD     .L1     4,A3,A3
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

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

   [!A0]   CALL    .S1     print_test_results ; |142| 
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
;          EXCLUSIVE CPU CYCLES: 14
           LDW     .D2T1   *+SP(48),A3       ; |152| 

           MVKL    .S2     a_sc,B6
||         MVK     .L2     0x7,B31

           MVKH    .S2     a_sc,B6
||         ZERO    .L1     A4
||         MVK     .L2     -1,B7             ; |155| 
||         STW     .D2T2   B31,*+SP(36)      ; |150| 

           MVKH    .S1     0xbf800000,A4
||         MV      .L1     A10,A5            ; |154| 
||         STW     .D2T2   B7,*+B6(24)       ; |155| 

           MV      .L1X    B6,A15            ; |150| 
||         ZERO    .S1     A6
||         ZERO    .L2     B4
||         STDW    .D2T1   A5:A4,*+B6(16)    ; |154| 

           MVKH    .S1     0x80000000,A6
||         MV      .L1X    B10,A7            ; |150| 
||         ZERO    .L2     B5
||         MVKH    .S2     0xff800000,B4
||         STW     .D2T1   A3,*+SP(64)       ; |93| 

           STDW    .D2T1   A7:A6,*B6         ; |150| 
||         MV      .L2X    A15,B6            ; |150| 
||         SET     .S2     B5,0x17,0x1e,B5

           STDW    .D2T2   B5:B4,*+B6(8)     ; |152| 
           LDW     .D1T1   *A15,A3           ; |157| 
           ZERO    .L2     B11
           NOP             1
           CALL    .S1     atan              ; |157| 
           NOP             1
           SPDP    .S2X    A3,B5:B4          ; |157| 
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
;          EXCLUSIVE CPU CYCLES: 3
           NOP             2

           DADD    .L1X    0,B5:B4,A5:A4     ; |157| 
||         ADDKPC  .S2     $C$RL10,B3,0      ; |157| 

$C$RL10:   ; CALL OCCURS {atan} {0}          ; |157| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *A3,A6            ; |157| 
           DPSP    .L1     A5:A4,A3          ; |157| 
           NOP             3
           ADD     .L1X    B11,A6,A4         ; |157| 
           STW     .D1T1   A3,*A4            ; |157| 

           CALLP   .S2     atansp,B3
||         LDW     .D1T1   *A15,A4           ; |158| 

$C$RL11:   ; CALL OCCURS {atansp} {0}        ; |158| 
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *+A3(4),A3        ; |158| 
           NOP             4
           ADD     .L2X    B11,A3,B4         ; |158| 
           STW     .D2T1   A4,*B4            ; |158| 

           CALLP   .S2     atansp_c,B3
||         LDW     .D1T1   *A15,A4           ; |159| 

$C$RL12:   ; CALL OCCURS {atansp_c} {0}      ; |159| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 94
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           LDW     .D1T1   *+A3(8),A3        ; |159| 
           LDW     .D2T2   *+SP(16),B31      ; |107| 
           LDW     .D2T2   *+SP(20),B30
           LDW     .D2T2   *+SP(28),B29      ; |107| 
           LDW     .D2T2   *+SP(24),B28      ; |107| 
           ADD     .L2X    B11,A3,B4         ; |159| 
           STW     .D2T1   A4,*B4            ; |159| 
           LDW     .D1T1   *A15++,A6         ; |160| 
           LDW     .D2T2   *+SP(12),B27      ; |107| 
           LDW     .D2T2   *+SP(64),B24      ; |87| 
           ZERO    .L2     B25               ; |93| 
           NOP             1
           MV      .L1     A6,A3             ; |130| 
           ABSSP   .S1     A3,A4             ; |130| 
           CMPGTSP .S1     A4,A10,A0         ; |130| 
   [!A0]   MV      .L1     A10,A3            ; |123| 
           RCPSP   .S1     A3,A4             ; |139| 
           MPYSP   .M1     A3,A4,A5          ; |139| 
           CMPLTSP .S2X    A6,B10,B0         ; |127| 
   [ A0]   MV      .L1     A10,A6            ; |132| 

   [!A0]   ZERO    .L1     A0                ; |125| 
|| [ A0]   MVK     .S1     0x1,A0            ; |133| 

           FSUBSP  .L1     A11,A5,A5         ; |139| 
   [ A0]   LDW     .D2T2   *+SP(32),B12      ; |139| 
   [!A0]   MV      .L2     B10,B12           ; |87| 
           MPYSP   .M1     A4,A5,A4          ; |139| 
           CMPEQSP .S1X    A6,B10,A2         ; |141| 
           NOP             2
           MPYSP   .M1     A3,A4,A3          ; |139| 
           NOP             3
           FSUBSP  .L1     A11,A3,A3         ; |139| 
           NOP             2
           MPYSP   .M1     A4,A3,A3          ; |139| 
           NOP             3
           MPYSP   .M1     A6,A3,A3          ; |139| 
           NOP             3
           MPYSP   .M1     A3,A3,A5          ; |107| 
           NOP             3
           MPYSP   .M1     A5,A5,A4          ; |107| 
           MPYSP   .M2X    B31,A5,B5         ; |107| 
           MPYSP   .M1     A12,A5,A9         ; |107| 
           NOP             1
           MPYSP   .M1     A13,A4,A16        ; |107| 
           MPYSP   .M1     A4,A5,A7          ; |107| 
           MPYSP   .M1     A4,A4,A8          ; |107| 
           MPYSP   .M2X    B30,A4,B6         ; |107| 
           NOP             1
           FADDSP  .L2X    B5,A16,B5         ; |107| 

           MPYSP   .M1     A4,A8,A5          ; |107| 
||         MPYSP   .M2X    B28,A7,B8         ; |107| 

           MPYSP   .M1     A4,A7,A4          ; |107| 
||         MPYSP   .M2X    B29,A8,B7         ; |107| 

           FADDSP  .L2     B27,B5,B4         ; |107| 
           FADDSP  .L1X    A9,B6,A31         ; |107| 
           SET     .S2     B25,31,31,B6      ; |93| 

           FADDSP  .L2     B8,B7,B26         ; |107| 
||         MPYSP   .M1     A14,A4,A4         ; |107| 

           MPYSP   .M2X    A5,B4,B5          ; |107| 
   [ B0]   XOR     .S2     B12,B6,B12        ; |93| 
           FADDSP  .L2X    A31,B26,B4        ; |107| 
           NOP             1
           FADDSP  .L2X    A4,B5,B5          ; |107| 
           NOP             2
           FADDSP  .L2     B5,B4,B5          ; |107| 
           NOP             2
           MPYSP   .M2X    A3,B5,B5          ; |107| 
           NOP             3

           FADDSP  .L2X    A3,B5,B4          ; |107| 
||         LDW     .D2T2   *B24,B5           ; |160| 

           NOP             2

   [!A0]   FADDSP  .L2     B4,B12,B13        ; |110| 
|| [ A0]   FSUBSP  .S2     B12,B4,B13        ; |110| 
||         LDW     .D2T2   *+SP(36),B4       ; |142| 

           NOP             1
           ADD     .D2     B11,B5,B5         ; |160| 

   [ A2]   MV      .L2     B10,B13           ; |142| 
||         ADD     .S2     4,B11,B11         ; |156| 

           STW     .D2T2   B13,*B5           ; |160| 

           SUB     .L1X    B4,1,A0           ; |156| 
||         SUB     .L2     B4,1,B4           ; |156| 

   [ A0]   B       .S1     $C$L8             ; |156| 
|| [ A0]   LDW     .D1T1   *A15,A3           ; |157| 
|| [!A0]   MVKL    .S2     output,B11
||         STW     .D2T2   B4,*+SP(36)       ; |160| 

   [!A0]   MVKL    .S1     a_sc,A4
   [!A0]   MVKH    .S2     output,B11
   [ A0]   CALL    .S1     atan              ; |157| 
   [!A0]   CALL    .S1     atansp_v          ; |162| 

           SPDP    .S2X    A3,B5:B4          ; |157| 
|| [!A0]   LDW     .D2T2   *+B11(16),B4      ; |162| 

           ; BRANCHCC OCCURS {$C$L8}         ; |156| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S1     a_sc,A4
           MVK     .L1     0x7,A6            ; |162| 
           ADDKPC  .S2     $C$RL13,B3,1      ; |162| 
$C$RL13:   ; CALL OCCURS {atansp_v} {0}      ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL14:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1X    B11,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |68| 

           LDW     .D2T1   *+SP(52),A3       ; |68| 
||         MVKL    .S2     fcn_pass,B4

           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           MV      .L2     B11,B31           ; |69| 
||         STW     .D2T1   A3,*+SP(64)       ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(56),A3       ; |69| 
           MVKL    .S2     fcn_pass,B31
           MVKH    .S2     fcn_pass,B31
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           NOP             1

           MV      .L2X    A3,B4             ; |69| 
||         STW     .D2T1   A3,*+SP(68)       ; |69| 

           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T1   *+SP(60),A3
           NOP             3

   [!B0]   B       .S1     $C$L9             ; |72| 
|| [!B0]   ZERO    .L1     A4                ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |166| 
|| [ B0]   MV      .L2X    A3,B4
||         STW     .D2T1   A3,*+SP(72)       ; |72| 
|| [!B0]   MVKL    .S1     all_pass,A3

   [!B0]   MVKH    .S1     all_pass,A3
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           NOP             2
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           CMPEQ   .L1     A4,0,A3           ; |72| 
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
           NOP             1
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
;          EXCLUSIVE CPU CYCLES: 10
           MVKL    .S2     0xc000cccc,B4
           MVKL    .S2     0xcccccccd,B31
           MVKL    .S2     a_ext,B5

           MVKH    .S2     0xc000cccc,B4
||         MVK     .S1     0xed,A3

           STW     .D2T1   A3,*+SP(36)       ; |169| 
||         MVKH    .S2     0xcccccccd,B31

           STW     .D2T2   B4,*+SP(80)       ; |175| 
||         MVKH    .S2     a_ext,B5
||         ZERO    .L1     A4

           STW     .D2T2   B31,*+SP(84)      ; |175| 
||         MV      .L2     B5,B30            ; |169| 
||         SET     .S1     A4,0x17,0x17,A4

           STW     .D2T1   A4,*B30           ; |169| 
||         MV      .L1X    B5,A15            ; |169| 

           LDW     .D1T1   *A15,A3           ; |171| 
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
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 7
           NOP             1
           CALL    .S1     atan              ; |171| 
           ADDKPC  .S2     $C$RL19,B3,0      ; |171| 
           SPDP    .S2X    A3,B5:B4          ; |171| 
           NOP             2
           DADD    .L1X    0,B5:B4,A5:A4     ; |171| 
$C$RL19:   ; CALL OCCURS {atan} {0}          ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |171| 
           DPSP    .L1     A5:A4,A3          ; |171| 
           NOP             3
           ADD     .L2     B11,B4,B4         ; |171| 
           STW     .D2T1   A3,*B4            ; |171| 

           CALLP   .S2     atansp,B3
||         LDW     .D1T1   *A15,A4           ; |172| 

$C$RL20:   ; CALL OCCURS {atansp} {0}        ; |172| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |172| 
           NOP             4
           ADD     .L2     B11,B4,B4         ; |172| 
           STW     .D2T1   A4,*B4            ; |172| 

           CALLP   .S2     atansp_c,B3
||         LDW     .D1T1   *A15,A4           ; |173| 

$C$RL21:   ; CALL OCCURS {atansp_c} {0}      ; |173| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 106
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |173| 
           LDW     .D2T2   *+SP(16),B31      ; |107| 
           LDW     .D2T2   *+SP(20),B30
           LDW     .D2T2   *+SP(28),B29      ; |107| 
           LDW     .D2T2   *+SP(24),B28      ; |107| 
           ADD     .L2     B11,B4,B4         ; |173| 
           STW     .D2T1   A4,*B4            ; |173| 
           LDW     .D1T1   *A15,A5           ; |174| 
           LDW     .D2T2   *+SP(12),B27      ; |107| 
           ZERO    .L2     B25               ; |93| 
           LDW     .D2T2   *+SP(48),B24      ; |87| 
           LDW     .D2T1   *+SP(36),A28
           MV      .L1     A5,A3             ; |130| 
           ABSSP   .S1     A3,A4             ; |130| 
           CMPGTSP .S1     A4,A10,A0         ; |130| 
   [!A0]   MV      .L1     A10,A3            ; |123| 
           RCPSP   .S1     A3,A4             ; |139| 
           MPYSP   .M1     A3,A4,A6          ; |139| 
           CMPLTSP .S1X    A5,B10,A16        ; |127| 
   [ A0]   MV      .L1     A10,A5            ; |132| 

   [!A0]   ZERO    .L1     A0                ; |125| 
|| [ A0]   MVK     .S1     0x1,A0            ; |133| 

           FSUBSP  .L1     A11,A6,A6         ; |139| 
   [ A0]   LDW     .D2T2   *+SP(32),B12      ; |139| 
           MV      .L2X    A16,B0            ; |139| 
           MPYSP   .M1     A4,A6,A4          ; |139| 
   [!A0]   MV      .L2     B10,B12           ; |87| 
           CMPEQSP .S2X    A5,B10,B2         ; |141| 
           SUB     .L1     A28,1,A2          ; |170| 
           MPYSP   .M1     A3,A4,A3          ; |139| 
           NOP             3
           FSUBSP  .L1     A11,A3,A3         ; |139| 
           NOP             2
           MPYSP   .M1     A4,A3,A3          ; |139| 
           NOP             3
           MPYSP   .M1     A5,A3,A6          ; |139| 
           NOP             3
           MPYSP   .M1     A6,A6,A4          ; |107| 
           NOP             3
           MPYSP   .M1     A4,A4,A3          ; |107| 
           MPYSP   .M2X    B31,A4,B5         ; |107| 
           MPYSP   .M1     A12,A4,A31        ; |107| 
           NOP             1
           MPYSP   .M1     A13,A3,A9         ; |107| 
           MPYSP   .M1     A3,A4,A7          ; |107| 
           MPYSP   .M1     A3,A3,A8          ; |107| 
           MPYSP   .M2X    B30,A3,B7         ; |107| 
           NOP             1

           FADDSP  .L2X    B5,A9,B5          ; |107| 
||         MPYSP   .M1     A3,A7,A29         ; |107| 

           MPYSP   .M1     A3,A8,A30         ; |107| 
||         MPYSP   .M2X    B28,A7,B8         ; |107| 

           MPYSP   .M2X    B29,A8,B6         ; |107| 
           FADDSP  .L2     B27,B5,B4         ; |107| 
           FADDSP  .L1X    A31,B7,A3         ; |107| 
           MPYSP   .M1     A14,A29,A4        ; |107| 

           MPYSP   .M2X    A30,B4,B5         ; |107| 
||         FADDSP  .L2     B8,B6,B26         ; |107| 

           SET     .S2     B25,31,31,B6      ; |93| 
   [ B0]   XOR     .S2     B12,B6,B12        ; |93| 
           FADDSP  .L2X    A3,B26,B4         ; |107| 
           FADDSP  .L2X    A4,B5,B5          ; |107| 
           NOP             2
           FADDSP  .L2     B5,B4,B5          ; |107| 
           NOP             2
           MPYSP   .M2X    A6,B5,B5          ; |107| 
           NOP             3

           FADDSP  .L2X    A6,B5,B4          ; |107| 
||         LDW     .D2T2   *B24,B5           ; |174| 

           NOP             2

   [ A0]   FSUBSP  .L2     B12,B4,B13        ; |110| 
|| [!A0]   FADDSP  .S2     B4,B12,B13        ; |110| 

           NOP             1
           ADD     .D2     B11,B5,B4         ; |174| 
   [ B2]   MV      .L2     B10,B13           ; |142| 
           STW     .D2T2   B13,*B4           ; |174| 
           LDW     .D1T2   *A15,B6           ; |175| 
           LDDW    .D2T2   *+SP(80),B5:B4
           ADD     .L2     4,B11,B11         ; |170| 
   [!A2]   MVKL    .S2     output,B11
   [!A2]   MVKH    .S2     output,B11
           NOP             1
           MPYSPDP .M2     B6,B5:B4,B5:B4    ; |175| 
           NOP             6
           DPSP    .L2     B5:B4,B4          ; |175| 
   [ A2]   BNOP    .S1     $C$L10,2          ; |170| 
           STW     .D1T2   B4,*++A15         ; |175| 
   [ A2]   LDW     .D1T1   *A15,A3           ; |171| 

   [!A2]   CALL    .S1     atansp_v          ; |177| 
||         STW     .D2T1   A2,*+SP(36)       ; |175| 

           ; BRANCHCC OCCURS {$C$L10}        ; |170| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B11(16),B4      ; |177| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           MVK     .S1     0xed,A6           ; |177| 
           ADDKPC  .S2     $C$RL22,B3,0      ; |177| 
$C$RL22:   ; CALL OCCURS {atansp_v} {0}      ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 43
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL23:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B12
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B12
           MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B11(8),B4       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B12(4)       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1X    B11,A3            ; |67| 
||         STW     .D2T1   A4,*+B12(8)       ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(52),A3       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L2     B11,B4            ; |68| 
||         STW     .D2T1   A4,*+B12(12)      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(56),A3       ; |69| 
           LDW     .D2T2   *+SP(60),B4
           STW     .D2T1   A4,*+B12(16)      ; |69| 
           NOP             2
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L11            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |181| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   ZERO    .L1     A3                ; |72| 
   [!A0]   MVKL    .S1     all_pass,A4
   [!A0]   MVKH    .S1     all_pass,A4
           ; BRANCHCC OCCURS {$C$L11}        ; |72| 
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
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |181| 
||         ADDKPC  .S2     $C$RL27,B3,0      ; |181| 

$C$RL27:   ; CALL OCCURS {print_test_results} {0}  ; |181| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
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

           CALL    .S1     gimme_random      ; |191| 
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         MVKL    .S1     t_offset,A5
||         SUB     .L2     B8,B7,B31         ; |117| 

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A5
||         MVK     .S2     0x80,B30

           STDW    .D1T2   B5:B4,*A5         ; |117| 
||         MVKL    .S2     0xc0c90fda,B4
||         MVKL    .S1     0x41490fda,A4

           MVKH    .S2     0xc0c90fda,B4
||         STW     .D2T2   B30,*+SP(36)      ; |117| 
||         MVKH    .S1     0x41490fda,A4
||         ZERO    .L1     A15

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL28,B3,0      ; |191| 
$C$RL28:   ; CALL OCCURS {gimme_random} {0}  ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 102

           MVKL    .S1     input,A3
||         MV      .L1     A4,A5             ; |191| 

           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |191| 
           NOP             4
           ADD     .L1     A15,A3,A3         ; |191| 

           STW     .D1T1   A5,*A3            ; |191| 
||         MVC     .S2     TSCL,B16          ; |122| 

           MVC     .S2     TSCH,B17          ; |122| 

           ABSSP   .S1     A4,A3             ; |130| 
||         LDW     .D2T2   *+SP(16),B4       ; |107| 
||         ZERO    .L2     B27               ; |93| 

           CMPGTSP .S1     A3,A10,A0         ; |130| 
||         LDW     .D2T2   *+SP(20),B31

   [!A0]   MV      .L1     A10,A4            ; |123| 
||         LDW     .D2T2   *+SP(28),B30      ; |107| 
||         MVKL    .S1     output+12,A27

           RCPSP   .S1     A4,A3             ; |139| 
||         LDW     .D2T2   *+SP(24),B29      ; |107| 

           MPYSP   .M1     A4,A3,A6          ; |139| 
||         LDW     .D2T2   *+SP(12),B8       ; |107| 
||         MVKH    .S1     output+12,A27

           MVKL    .S1     t_start,A26
           MVKH    .S1     t_start,A26
           STDW    .D1T2   B17:B16,*A26
           FSUBSP  .L1     A11,A6,A6         ; |139| 
           NOP             2
           MPYSP   .M1     A3,A6,A3          ; |139| 
           NOP             3
           MPYSP   .M1     A4,A3,A4          ; |139| 
           NOP             3
           FSUBSP  .L1     A11,A4,A4         ; |139| 
           NOP             2

           MPYSP   .M1     A3,A4,A3          ; |139| 
||         MV      .L1     A5,A4             ; |195| 

           CMPLTSP .S1X    A4,B10,A16        ; |127| 
|| [ A0]   MV      .L1     A10,A4            ; |132| 

   [!A0]   ZERO    .L1     A0                ; |125| 
|| [ A0]   MVK     .S1     0x1,A0            ; |133| 

   [ A0]   LDW     .D2T2   *+SP(32),B11
||         MV      .L2X    A16,B0            ; |139| 
|| [!A0]   MV      .S2     B10,B11           ; |87| 

           MPYSP   .M1     A4,A3,A8          ; |139| 
||         CMPEQSP .S2X    A4,B10,B2         ; |141| 

           NOP             3
           MPYSP   .M1     A8,A8,A7          ; |107| 
           NOP             3
           MPYSP   .M1     A7,A7,A6          ; |107| 

           MPYSP   .M2X    B4,A7,B6          ; |107| 
||         MPYSP   .M1     A12,A7,A31        ; |107| 

           NOP             2
           MPYSP   .M1     A13,A6,A9         ; |107| 

           MPYSP   .M1     A6,A6,A5          ; |107| 
||         MPYSP   .M2X    B31,A6,B5         ; |107| 

           MPYSP   .M1     A6,A7,A3          ; |107| 
           NOP             2

           FADDSP  .L2X    B6,A9,B7          ; |107| 
||         MPYSP   .M1     A6,A5,A30         ; |107| 

           MPYSP   .M1     A6,A3,A29         ; |107| 
||         MPYSP   .M2X    B30,A5,B6         ; |107| 
||         FADDSP  .L1X    A31,B5,A28        ; |107| 

           MPYSP   .M2X    B29,A3,B4         ; |107| 
||         LDW     .D1T1   *A27,A3           ; |195| 

           FADDSP  .L2     B8,B7,B7          ; |107| 
           NOP             1
           MPYSP   .M1     A14,A29,A5        ; |107| 

           MPYSP   .M2X    A30,B7,B28        ; |107| 
||         FADDSP  .L2     B4,B6,B4          ; |107| 

           ADD     .L1     A15,A3,A3         ; |195| 
           NOP             1
           FADDSP  .L2X    A28,B4,B4         ; |107| 
           FADDSP  .L2X    A5,B28,B5         ; |107| 
           NOP             2

           FADDSP  .L2     B5,B4,B4          ; |107| 
||         SET     .S2     B27,31,31,B5      ; |93| 

   [ B0]   XOR     .L2     B11,B5,B11        ; |93| 
           NOP             1
           MPYSP   .M2X    A8,B4,B4          ; |107| 
           NOP             3
           FADDSP  .L2X    A8,B4,B4          ; |107| 
           NOP             2

   [!A0]   FADDSP  .L2     B4,B11,B12        ; |110| 
|| [ A0]   FSUBSP  .S2     B11,B4,B12        ; |110| 

           NOP             2
   [ B2]   MV      .L2     B10,B12           ; |142| 

           STW     .D1T2   B12,*A3           ; |195| 
||         MVC     .S2     TSCL,B4           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     t_offset,B13
||         MVKL    .S1     t_stop,A3
||         ADD     .L1     4,A15,A15         ; |189| 

           MVKH    .S2     t_offset,B13
||         MVKH    .S1     t_stop,A3

           LDDW    .D2T2   *B13,B7:B6        ; |130| 
||         MVKL    .S2     cycle_counts+24,B8

           MVKH    .S2     cycle_counts+24,B8
||         STDW    .D1T2   B5:B4,*A3         ; |128| 
||         MVKL    .S1     cycle_counts+24,A3

           LDDW    .D2T2   *B8,B19:B18       ; |130| 
||         MVKH    .S1     cycle_counts+24,A3

           NOP             2
           ADDU    .L2     B6,B16,B9:B8      ; |130| 

           ADD     .S2     B9,B7,B8          ; |130| 
||         SUBU    .L2     B4,B8,B7:B6       ; |130| 
||         LDW     .D2T2   *+SP(36),B4       ; |130| 

           ADD     .D2     B8,B17,B8         ; |130| 
||         EXT     .S2     B7,24,24,B9       ; |130| 
||         ADDU    .L2     B18,B6,B7:B6      ; |130| 

           SUB     .L2     B5,B8,B8          ; |130| 
||         ADD     .S2     B7,B19,B7         ; |130| 

           ADD     .L2     B8,B9,B8          ; |130| 
           ADD     .L2     B7,B8,B7          ; |130| 

           SUB     .L1X    B4,1,A0           ; |189| 
||         SUB     .L2     B4,1,B4           ; |189| 
||         STDW    .D1T2   B7:B6,*A3         ; |130| 

           STW     .D2T2   B4,*+SP(36)       ; |130| 
|| [ A0]   MVKL    .S1     0x41490fda,A4
|| [ A0]   B       .S2     $C$L12            ; |189| 
|| [!A0]   LDDW    .D1T1   *A3,A5:A4         ; |135| 

   [ A0]   CALL    .S1     gimme_random      ; |191| 
|| [ A0]   MVKL    .S2     0xc0c90fda,B4

   [!A0]   CALL    .S2     __c6xabi_fltllif  ; |135| 
|| [ A0]   MVKH    .S1     0x41490fda,A4

   [ A0]   MVKH    .S2     0xc0c90fda,B4
           NOP             2
           ; BRANCHCC OCCURS {$C$L12}        ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL29,B3,1      ; |135| 
$C$RL29:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
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

$C$RL30:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           LDDW    .D2T2   *+SP(80),B5:B4
           MVKL    .S2     cycle_counts+24,B6
           MVKH    .S2     cycle_counts+24,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 

           SUBAW   .D2     B6,6,B10
||         MV      .L2X    A12,B31           ; |114| 

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T2   B5:B4,*B10        ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A14
           MVKH    .S1     t_start,A14

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B7:B6,*A14        ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 

           MVK     .S2     0x80,B4
||         STDW    .D2T2   B5:B4,*B13        ; |117| 

           MVKL    .S1     input,A10

           MV      .L1X    B4,A15            ; |117| 
||         MVKH    .S1     input,A10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A10,A3           ; |203| 
           NOP             4

           ADD     .L1     A12,A3,A3         ; |203| 
||         CALL    .S1     atanf             ; |203| 

           LDW     .D1T1   *A3,A4            ; |203| 
           ADDKPC  .S2     $C$RL31,B3,3      ; |203| 
$C$RL31:   ; CALL OCCURS {atanf} {0}         ; |203| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A15,1,A0          ; |202| 
||         SUB     .S1     A15,1,A15         ; |202| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |203| 
   [ A0]   BNOP    .S1     $C$L13,3          ; |202| 

           ADD     .L1X    A12,B4,A3         ; |203| 
||         ADD     .S1     4,A12,A12         ; |202| 

           STW     .D1T1   A4,*A3            ; |203| 
           ; BRANCHCC OCCURS {$C$L13}        ; |202| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B9:B8        ; |130| 

           MVKL    .S2     t_stop,B11
           MV      .L2     B4,B7             ; |128| 
           MVKH    .S2     t_stop,B11
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
           STDW    .D2T2   B7:B6,*B11        ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL32,B3,0      ; |130| 

$C$RL32:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL33:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDDW    .D2T2   *+SP(80),B5:B4    ; |130| 
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B10(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B8           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B9             ; |116| 

           STDW    .D1T2   B9:B8,*A14        ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B4           ; |117| 
           SUBU    .L2     B5,B8,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B4,B9,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MVK     .S2     0x80,B4

           LDW     .D2T2   *+SP(40),B12      ; |117| 

           STDW    .D2T2   B7:B6,*B13        ; |117| 
||         MV      .L1     A12,A15           ; |117| 
||         MV      .S1X    B4,A12            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A10,A3           ; |211| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |211| 
||         CALL    .S1     atansp            ; |211| 

           LDW     .D1T1   *A3,A4            ; |211| 
           ADDKPC  .S2     $C$RL34,B3,3      ; |211| 
$C$RL34:   ; CALL OCCURS {atansp} {0}        ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |211| 
||         SUB     .L1     A12,1,A0          ; |210| 
||         SUB     .S1     A12,1,A12         ; |210| 

   [ A0]   BNOP    .S1     $C$L14,3          ; |210| 

           ADD     .L1X    A15,B4,A3         ; |211| 
||         ADD     .S1     4,A15,A15         ; |210| 

           STW     .D1T1   A4,*A3            ; |211| 
           ; BRANCHCC OCCURS {$C$L14}        ; |210| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           LDDW    .D2T2   *+B10(8),B17:B16  ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
           ADD     .L1X    A7,B7,A3          ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B8,A6,B5:B4       ; |130| 

           CALL    .S1     __c6xabi_fltllif  ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .L2X    B9,A3,B4          ; |130| 
||         ADD     .S2     B7,B17,B31        ; |130| 

           ADD     .L2     B4,B5,B5          ; |130| 
||         MV      .S2     B11,B4            ; |130| 

           ADD     .L2     B31,B5,B7         ; |130| 
           STDW    .D2T2   B9:B8,*B4         ; |128| 

           DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL35,B3,0      ; |130| 

$C$RL35:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
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

           STDW    .D1T2   B9:B8,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B6           ; |117| 
           SUBU    .L2     B4,B8,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B6,B9,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1     A12,A15

           MV      .L1X    B4,A12            ; |117| 
||         LDW     .D2T2   *+SP(44),B12      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A10,A3           ; |219| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |219| 
||         CALL    .S1     atansp_c          ; |219| 

           LDW     .D1T1   *A3,A4            ; |219| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |219| 
$C$RL37:   ; CALL OCCURS {atansp_c} {0}      ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |219| 
||         SUB     .L1     A12,1,A0          ; |218| 
||         SUB     .S1     A12,1,A12         ; |218| 

   [ A0]   BNOP    .S1     $C$L15,3          ; |218| 

           ADD     .L1X    A15,B4,A3         ; |219| 
||         ADD     .S1     4,A15,A15         ; |218| 

           STW     .D1T1   A4,*A3            ; |219| 
           ; BRANCHCC OCCURS {$C$L15}        ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           LDDW    .D2T2   *+B10(16),B17:B16 ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B4          ; |130| 
||         SUBU    .L2     B8,B4,B7:B6       ; |130| 

           ADD     .L2X    B4,A5,B4          ; |130| 
||         MV      .S2     B6,B5             ; |130| 
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
||         ADDKPC  .S2     $C$RL38,B3,0      ; |130| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           MPYSP   .M1     A11,A4,A3         ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1X    A13:A12,B5:B4,A5:A4 ; |130| 

$C$RL39:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           LDDW    .D2T2   *+SP(80),B5:B4
           ADDAD   .D2     B11,1,B12
           MV      .L2X    A12,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B10(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A14        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B8,B5,B5          ; |117| 

           MVKL    .S1     output,A15
||         ADD     .L2     B5,B7,B5          ; |117| 
||         MV      .S2     B6,B4             ; |117| 

           MVKH    .S1     output,A15
||         MV      .L2X    A10,B9            ; |226| 
||         STDW    .D2T2   B5:B4,*B13        ; |117| 

           CALLP   .S2     atansp_v,B3
||         LDW     .D1T2   *+A15(16),B4      ; |226| 
||         LDW     .D2T1   *B9,A4            ; |226| 
||         MVK     .S1     0x80,A6           ; |226| 

$C$RL40:   ; CALL OCCURS {atansp_v} {0}      ; |226| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MVK     .S1     16,A10
           ADD     .L1X    B12,A10,A10
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

$C$RL41:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           MPYSP   .M1     A11,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6

           STDW    .D1T1   A5:A4,*A10        ; |130| 
||         MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL43:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     fcn_pass,B10
           MVKH    .S2     0x3eb0c6f7,B7
           MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S2     fcn_pass,B10

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A15(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(64),A3       ; |68| 
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D1T1   *A15,A4           ; |69| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(68),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(72),B4
           NOP             3

   [!B0]   B       .S1     $C$L16            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L16}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L17            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |232| 
   [ A0]   MVKL    .S1     all_pass,A3
   [ A0]   MVKH    .S1     all_pass,A3
           NOP             2
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |232| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           MV      .L1     A12,A4
           NOP             1
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x2,A4            ; |232| 
||         ADDKPC  .S2     $C$RL47,B3,0      ; |232| 

$C$RL47:   ; CALL OCCURS {print_test_results} {0}  ; |232| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |233| 

$C$RL48:   ; CALL OCCURS {printf} {0}        ; |233| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |233| 

$C$RL49:   ; CALL OCCURS {printf} {0}        ; |233| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |240| 

$C$RL50:   ; CALL OCCURS {print_profile_results} {0}  ; |240| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |243| 

$C$RL51:   ; CALL OCCURS {print_memory_results} {0}  ; |243| 
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
$C$SL1:	.string	"atanSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	atan
	.global	atanf
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	atansp
	.global	atansp_v
	.global	atansp_c
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
