;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:47:22 2013                                *
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
	.word	0451b943dh		; _a[0] @ 0
	.word	046138d3bh		; _a[1] @ 32
	.word	045d95bfch		; _a[2] @ 64
	.word	044f1a053h		; _a[3] @ 96
	.word	045249b7dh		; _a[4] @ 128
	.word	04592f9a6h		; _a[5] @ 160
	.word	044045c86h		; _a[6] @ 192
	.word	0451769c3h		; _a[7] @ 224
	.word	0461a7820h		; _a[8] @ 256
	.word	042af4475h		; _a[9] @ 288
	.word	04510e3c4h		; _a[10] @ 320
	.word	045cc1eb3h		; _a[11] @ 352
	.word	0459ccdb4h		; _a[12] @ 384
	.word	046034912h		; _a[13] @ 416
	.word	04599c238h		; _a[14] @ 448
	.word	0456a8a8ah		; _a[15] @ 480
	.word	045085001h		; _a[16] @ 512
	.word	045b9bef4h		; _a[17] @ 544
	.word	04581d7ech		; _a[18] @ 576
	.word	045e0ba99h		; _a[19] @ 608
	.word	0460cf8deh		; _a[20] @ 640
	.word	0451cb21dh		; _a[21] @ 672
	.word	04613227ch		; _a[22] @ 704
	.word	0454da5ceh		; _a[23] @ 736
	.word	045cbe0eah		; _a[24] @ 768
	.word	044943e9fh		; _a[25] @ 800
	.word	0455b9d3ah		; _a[26] @ 832
	.word	044eee802h		; _a[27] @ 864
	.word	04611124eh		; _a[28] @ 896
	.word	046071e7ah		; _a[29] @ 928
	.word	0451fd402h		; _a[30] @ 960
	.word	045c5da1dh		; _a[31] @ 992
	.word	045a2731fh		; _a[32] @ 1024
	.word	04598f737h		; _a[33] @ 1056
	.word	045c3e5e8h		; _a[34] @ 1088
	.word	0455204aah		; _a[35] @ 1120
	.word	045b0cca5h		; _a[36] @ 1152
	.word	04558c5aah		; _a[37] @ 1184
	.word	045f216eeh		; _a[38] @ 1216
	.word	0454c262eh		; _a[39] @ 1248
	.word	045a9b1adh		; _a[40] @ 1280
	.word	0449baae4h		; _a[41] @ 1312
	.word	0455da619h		; _a[42] @ 1344
	.word	04616420ah		; _a[43] @ 1376
	.word	045302cbfh		; _a[44] @ 1408
	.word	0460525f0h		; _a[45] @ 1440
	.word	045610c33h		; _a[46] @ 1472
	.word	046149718h		; _a[47] @ 1504
	.word	0461481c0h		; _a[48] @ 1536
	.word	0461061cdh		; _a[49] @ 1568
	.word	044a248a7h		; _a[50] @ 1600
	.word	0455873ddh		; _a[51] @ 1632
	.word	0441172c6h		; _a[52] @ 1664
	.word	044047101h		; _a[53] @ 1696
	.word	0455c2f21h		; _a[54] @ 1728
	.word	045a7e951h		; _a[55] @ 1760
	.word	045912cdch		; _a[56] @ 1792
	.word	045414c87h		; _a[57] @ 1824
	.word	04405c101h		; _a[58] @ 1856
	.word	04529251ah		; _a[59] @ 1888
	.word	04564f5b7h		; _a[60] @ 1920
	.word	04482ab1ch		; _a[61] @ 1952
	.word	045bd25d6h		; _a[62] @ 1984
	.word	045c3f12dh		; _a[63] @ 2016
	.word	0453f5255h		; _a[64] @ 2048
	.word	044eb74bdh		; _a[65] @ 2080
	.word	045e14381h		; _a[66] @ 2112
	.word	043a2c826h		; _a[67] @ 2144
	.word	044dbe056h		; _a[68] @ 2176
	.word	045d1d6d1h		; _a[69] @ 2208
	.word	04590b70fh		; _a[70] @ 2240
	.word	045220333h		; _a[71] @ 2272
	.word	045007068h		; _a[72] @ 2304
	.word	046199263h		; _a[73] @ 2336
	.word	04513de7fh		; _a[74] @ 2368
	.word	045822aaah		; _a[75] @ 2400
	.word	0461702b1h		; _a[76] @ 2432
	.word	0460e98c1h		; _a[77] @ 2464
	.word	045f4e8b5h		; _a[78] @ 2496
	.word	046168f77h		; _a[79] @ 2528
	.word	0456f9d2fh		; _a[80] @ 2560
	.word	045b93401h		; _a[81] @ 2592
	.word	044f02a83h		; _a[82] @ 2624
	.word	045dc4702h		; _a[83] @ 2656
	.word	045df8454h		; _a[84] @ 2688
	.word	04598b88bh		; _a[85] @ 2720
	.word	0460dc397h		; _a[86] @ 2752
	.word	045f4b0a9h		; _a[87] @ 2784
	.word	045b22874h		; _a[88] @ 2816
	.word	04586e31ch		; _a[89] @ 2848
	.word	045dacf37h		; _a[90] @ 2880
	.word	045d78d77h		; _a[91] @ 2912
	.word	0460bb19bh		; _a[92] @ 2944
	.word	045b24739h		; _a[93] @ 2976
	.word	045d82584h		; _a[94] @ 3008
	.word	0451cd74ch		; _a[95] @ 3040
	.word	04619818dh		; _a[96] @ 3072
	.word	04583114ah		; _a[97] @ 3104
	.word	045597c65h		; _a[98] @ 3136
	.word	045cc4143h		; _a[99] @ 3168
	.word	04594d7f9h		; _a[100] @ 3200
	.word	045ffd8c8h		; _a[101] @ 3232
	.word	045978f44h		; _a[102] @ 3264
	.word	04580530dh		; _a[103] @ 3296
	.word	0455b27c4h		; _a[104] @ 3328
	.word	04615b1f8h		; _a[105] @ 3360
	.word	0451b34afh		; _a[106] @ 3392
	.word	04572d7bdh		; _a[107] @ 3424
	.word	04611e7d5h		; _a[108] @ 3456
	.word	045703bbbh		; _a[109] @ 3488
	.word	044a6a411h		; _a[110] @ 3520
	.word	045f759fah		; _a[111] @ 3552
	.word	0460bef19h		; _a[112] @ 3584
	.word	04617b602h		; _a[113] @ 3616
	.word	04619dd8dh		; _a[114] @ 3648
	.word	044dd46e5h		; _a[115] @ 3680
	.word	0451acb43h		; _a[116] @ 3712
	.word	04612e6e1h		; _a[117] @ 3744
	.word	0461a7f6ah		; _a[118] @ 3776
	.word	0458874cch		; _a[119] @ 3808
	.word	045592618h		; _a[120] @ 3840
	.word	046066814h		; _a[121] @ 3872
	.word	045d14798h		; _a[122] @ 3904
	.word	045fd858bh		; _a[123] @ 3936
	.word	0460b08b0h		; _a[124] @ 3968
	.word	045c97e81h		; _a[125] @ 4000
	.word	0460cd0bch		; _a[126] @ 4032
	.word	046096dc0h		; _a[127] @ 4064
	.word	046103d6fh		; _a[128] @ 4096
	.word	045aa6f8bh		; _a[129] @ 4128
	.word	0460bc9fbh		; _a[130] @ 4160
	.word	045b33bc0h		; _a[131] @ 4192
	.word	046023f33h		; _a[132] @ 4224
	.word	044cbb94eh		; _a[133] @ 4256
	.word	04506409fh		; _a[134] @ 4288
	.word	044c70c96h		; _a[135] @ 4320
	.word	0455c8ae2h		; _a[136] @ 4352
	.word	045885f70h		; _a[137] @ 4384
	.word	045eee1f4h		; _a[138] @ 4416
	.word	0451d982bh		; _a[139] @ 4448
	.word	045ae82d3h		; _a[140] @ 4480
	.word	045cb179bh		; _a[141] @ 4512
	.word	045f61d2ah		; _a[142] @ 4544
	.word	045fcee28h		; _a[143] @ 4576
	.word	0460697f6h		; _a[144] @ 4608
	.word	04589d91ah		; _a[145] @ 4640
	.word	04609331dh		; _a[146] @ 4672
	.word	044abb02bh		; _a[147] @ 4704
	.word	04396a4dfh		; _a[148] @ 4736
	.word	045f1dd70h		; _a[149] @ 4768
	.word	0461729cch		; _a[150] @ 4800
	.word	046090153h		; _a[151] @ 4832
	.word	044d5d584h		; _a[152] @ 4864
	.word	046181528h		; _a[153] @ 4896
	.word	0454feca4h		; _a[154] @ 4928
	.word	043071dadh		; _a[155] @ 4960
	.word	045e391beh		; _a[156] @ 4992
	.word	045da2210h		; _a[157] @ 5024
	.word	045bba960h		; _a[158] @ 5056
	.word	0460a02e7h		; _a[159] @ 5088
	.word	0459e542ch		; _a[160] @ 5120
	.word	04614d5c0h		; _a[161] @ 5152
	.word	045e3515dh		; _a[162] @ 5184
	.word	044d583a6h		; _a[163] @ 5216
	.word	045c4df9ch		; _a[164] @ 5248
	.word	04445550ah		; _a[165] @ 5280
	.word	043ae8d86h		; _a[166] @ 5312
	.word	046097323h		; _a[167] @ 5344
	.word	045b89309h		; _a[168] @ 5376
	.word	045f40348h		; _a[169] @ 5408
	.word	044d0bf74h		; _a[170] @ 5440
	.word	04573918ah		; _a[171] @ 5472
	.word	045016f82h		; _a[172] @ 5504
	.word	04450bbb9h		; _a[173] @ 5536
	.word	0449bcd3bh		; _a[174] @ 5568
	.word	045772e55h		; _a[175] @ 5600
	.word	045cccc83h		; _a[176] @ 5632
	.word	04569abc6h		; _a[177] @ 5664
	.word	04517c709h		; _a[178] @ 5696
	.word	04616aea8h		; _a[179] @ 5728
	.word	0458899dah		; _a[180] @ 5760
	.word	04568cef4h		; _a[181] @ 5792
	.word	0450813bah		; _a[182] @ 5824
	.word	045941ba3h		; _a[183] @ 5856
	.word	04581dd0ch		; _a[184] @ 5888
	.word	044b5dcd0h		; _a[185] @ 5920
	.word	0441f2aedh		; _a[186] @ 5952
	.word	045d2f7a7h		; _a[187] @ 5984
	.word	045f62592h		; _a[188] @ 6016
	.word	04487c01ch		; _a[189] @ 6048
	.word	044c84e12h		; _a[190] @ 6080
	.word	045ca9e1dh		; _a[191] @ 6112
	.word	04479663ah		; _a[192] @ 6144
	.word	042e2dd0dh		; _a[193] @ 6176
	.word	0450c6f52h		; _a[194] @ 6208
	.word	045ff0c98h		; _a[195] @ 6240
	.word	045160d8dh		; _a[196] @ 6272
	.word	0461444f6h		; _a[197] @ 6304
	.word	04543086ch		; _a[198] @ 6336
	.word	0461478aeh		; _a[199] @ 6368
	.word	04587c610h		; _a[200] @ 6400
$C$IR_1:	.set	804

	.global	_a
_a:	.usect	".far",804,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\091322 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\091324 
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
;*   Local Frame Size  : 8 Args + 124 Auto + 56 Save = 188 byte               *
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
||         ADDK    .S2     -136,SP           ; |130| 

           CALLP   .S2     _driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {_driver_init} {0}  ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     0xc9,B4
||         MVKL    .S1     _a,A10

           MVKH    .S1     _a,A10
||         MVKL    .S2     _output,B10

           CALL    .S1     _log2f            ; |147| 
||         MV      .L1     A10,A12
||         MV      .D1X    B4,A11
||         MVKH    .S2     _output,B10
||         ZERO    .L2     B11

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |147| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |147| 
$C$RL1:    ; CALL OCCURS {_log2f} {0}        ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B10,B4           ; |147| 
||         SUB     .L1     A11,1,A0          ; |146| 
||         SUB     .S1     A11,1,A11         ; |146| 

   [ A0]   BNOP    .S1     $C$L1,3           ; |146| 
|| [!A0]   ADD     .L2     4,B10,B5

           ADD     .L2     B11,B4,B4         ; |147| 
||         ADD     .S2     4,B11,B11         ; |146| 

   [ A0]   CALL    .S1     _log2f            ; |147| 
||         STW     .D2T1   A4,*B4            ; |147| 
|| [!A0]   MVK     .S2     0xc9,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           ZERO    .L2     B11
||         STW     .D2T2   B5,*+SP(36)
||         MV      .L1     A10,A14

           MV      .L1X    B4,A11
||         CALL    .S1     _log2sp           ; |150| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A10++,A4         ; |150| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |150| 
$C$RL2:    ; CALL OCCURS {_log2sp} {0}       ; |150| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D2T2   *+SP(36),B4       ; |150| 
           SUB     .L1     A11,1,A0          ; |149| 
           SUB     .L1     A11,1,A11         ; |149| 
           NOP             2
           LDW     .D2T2   *B4,B4            ; |150| 
   [ A0]   BNOP    .S1     $C$L2,3           ; |149| 

           ADD     .L2     B11,B4,B4         ; |150| 
||         ADD     .S2     4,B11,B11         ; |149| 

   [ A0]   CALL    .S1     _log2sp           ; |150| 
||         STW     .D2T1   A4,*B4            ; |150| 

           ; BRANCHCC OCCURS {$C$L2}         ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           LDW     .D2T2   *+SP(36),B4
           ZERO    .L2     B11
           MV      .L1     A14,A11
           NOP             2

           ADD     .L2     4,B4,B5
||         MVK     .S2     0xc9,B4

           STW     .D2T2   B5,*+SP(40)

           MV      .L1X    B4,A10
||         CALL    .S1     _log2sp_c         ; |153| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |153| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |153| 
$C$RL3:    ; CALL OCCURS {_log2sp_c} {0}     ; |153| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           LDW     .D2T2   *+SP(40),B4       ; |153| 
||         SUB     .L1     A10,1,A0          ; |152| 
||         SUB     .S1     A10,1,A10         ; |152| 

   [!A0]   MVKL    .S1     0xbe804d66,A5
   [!A0]   ZERO    .L1     A3
   [!A0]   LDW     .D2T2   *+SP(40),B7
   [!A0]   MVKL    .S1     0x3eaaa872,A13
           LDW     .D2T2   *B4,B4            ; |153| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |152| 

           ADD     .L2     B11,B4,B4         ; |153| 
||         ADD     .S2     4,B11,B11         ; |152| 

   [ A0]   CALL    .S2     _log2sp_c         ; |153| 
||         STW     .D2T1   A4,*B4            ; |153| 
|| [!A0]   MVKL    .S1     0xbf000003,A4

           ; BRANCHCC OCCURS {$C$L3}         ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17

           MVKL    .S1     0x7f7fffff,A11
||         MVKL    .S2     0x652b83a3,B8
||         ZERO    .L2     B4
||         ZERO    .D2     B30
||         ZERO    .L1     A6                ; |85| 
||         MV      .D1     A14,A8

           MVKL    .S1     0xbe6bd0fc,A7
||         MVKL    .S2     0x3e436581,B12
||         ADD     .L2     4,B7,B7
||         ZERO    .D2     B23               ; |85| 

           MVKL    .S1     _logtable,A12
||         MVKL    .S2     0xfefa39ec,B31
||         STW     .D2T2   B7,*+SP(32)

           SET     .S1     A3,0x14,0x1d,A3
||         MVKL    .S2     0x3fb8aa3b,B5
||         LDW     .D2T2   *B7,B21

           MVKH    .S1     0xbe804d66,A5
||         MVKL    .S2     0x3ff71547,B9
||         STW     .D2T1   A3,*+SP(44)       ; |85| 
||         ZERO    .L1     A3                ; |85| 

           MVKH    .S1     0x3eaaa872,A13
||         MVKL    .S2     0x3fe62e42,B6

           MVKH    .S1     0xbf000003,A4
||         MVKH    .S2     0x44800000,B4
||         MV      .L2X    A5,B28

           MVKH    .S1     0x7f7fffff,A11
||         MVKH    .S2     0x652b83a3,B8
||         STW     .D2T2   B4,*+SP(24)
||         MV      .L2X    A13,B26

           MVKH    .S1     0xbe6bd0fc,A7
||         MVKH    .S2     0x3e436581,B12
||         MV      .L1     A11,A9
||         STW     .D2T2   B8,*+SP(48)       ; |85| 
||         MV      .L2X    A4,B25

           MVKH    .S1     _logtable,A12
||         MVKH    .S2     0xfefa39ec,B31
||         STW     .D2T1   A7,*+SP(16)
||         MV      .L1     A7,A18
||         MV      .L2     B4,B22

           MVKH    .S2     0x3fb8aa3b,B5
||         MVK     .S1     0xfffffc01,A15
||         LDW     .D2T1   *+SP(44),A7
||         MV      .L1     A12,A16
||         MV      .L2     B8,B18

           MVKH    .S2     0x3ff71547,B9
||         STW     .D2T2   B31,*+SP(56)      ; |85| 
||         MV      .L1     A15,A17
||         MV      .L2     B12,B27

           MVKH    .S2     0xff800000,B30
||         STW     .D2T2   B5,*+SP(12)
||         MV      .L2     B5,B29

           MVKH    .S2     0x3fe62e42,B6
||         STW     .D2T2   B9,*+SP(52)       ; |85| 
||         MV      .L2     B9,B19

           MVK     .S2     0xc9,B16
||         STW     .D2T2   B30,*+SP(20)
||         MV      .L2     B30,B24

           DINT                              ; interrupts off
||         SUB     .L2     B16,1,B1
||         MV      .D2     B31,B16

           STW     .D2T2   B6,*+SP(60)       ; |85| 
||         MV      .L2     B6,B17

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/log2sp/log2sp_d.c
;*      Loop source line                 : 155
;*      Loop opening brace source line   : 155
;*      Loop closing brace source line   : 157
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 63
;*      Unpartitioned Resource Bound     : 8
;*      Partitioned Resource Bound(*)    : 9
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     3        1     
;*      .S units                     8        4     
;*      .D units                     2        1     
;*      .M units                     6        8     
;*      .X cross paths               1        9*    
;*      .T address paths             2        1     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           2        6     (.L or .S unit)
;*      Addition ops (.LSD)          3        5     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             7        6     
;*      Bound(.L .S .D .LS .LSD)     6        6     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 63 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |   *  ****      ***             | *      **      **** *********  |
;*       1: |   *  ****      ***             | *      **      **** *********  |
;*       2: |   *  ****      ***             | *      **      **** *********  |
;*       3: |   *  ****      ***             | *      **      **** *********  |
;*       4: |   *  ****      ***             | *      **      **** *********  |
;*       5: |   *  ****      ****            | *      **      **** *********  |
;*       6: |   *  ****      ****            | *      **      **************  |
;*       7: |   *******      ****            | *      **      **************  |
;*       8: |   *  ****      ****            | *      **      **************  |
;*       9: |   * *****      ****            | *      **      **************  |
;*      10: |   ** ****      **** *          | *      **      **************  |
;*      11: |   *******      ******          | *      **      **************  |
;*      12: |   *******      ******          | *      **      **************  |
;*      13: |   *  ****      ******          | *      **      **************  |
;*      14: |   *  ****      ******          | *      **      **************  |
;*      15: |   *  ****      ******          | *      **      **************  |
;*      16: |   *  ****      ******          | *      **      **************  |
;*      17: |   *  ****      ******          | *      **      **************  |
;*      18: |   *******      ******          | *      **      **************  |
;*      19: |   *  ****      ******          | *      **      **************  |
;*      20: |   *  ****      ******          | *      **      **************  |
;*      21: |   *******      ******          | *      **      **************  |
;*      22: |   *******      ******          | *      **      **************  |
;*      23: |   *  ****      ******          | *      **      **************  |
;*      24: |   *  ****      ******          | *      **      **************  |
;*      25: |   ** ****      ******          | *      **      **************  |
;*      26: |   ** ****      ******          | *    ****      **************  |
;*      27: |   ** ****      ******          | *    ****      **************  |
;*      28: |   ** ****      ******          | *    ****      **************  |
;*      29: |   *******      ******          | *    ****      **************  |
;*      30: |   *******      ******          | *  * ****      **************  |
;*      31: |   * *****      *****           | *    ****      **************  |
;*      32: |   *  ****      *****           | *    ****      **************  |
;*      33: |   *  ****      ***** *         | *  * ****      **************  |
;*      34: |   *  ****      *******         | *  * ****      *************** |
;*      35: |   *******      *******         | *    ****      *************** |
;*      36: |   *******      ***** *         | *    ****      *************** |
;*      37: |   *  ****      ****  *         | *  * ****      *************** |
;*      38: |   *  ****      ****            | *    ****      *************** |
;*      39: |   *  ****      ****            | *    ****      ****************|
;*      40: |   *  ****      ****            | *  ******      ****************|
;*      41: |   *******      ****            |**  ******      ****************|
;*      42: |   *  ****      ****            | *    ****      *************** |
;*      43: |   *  ****      ****            | *    ****      *************** |
;*      44: |   *******      ****            | *  * ****      *************** |
;*      45: |   *******      ****            | *    ****      **************  |
;*      46: |   *  ****      ****            | *    ****      **************  |
;*      47: |   *  ****      ****            | *  * ****      **************  |
;*      48: |   *  ****      ****            | *    ****      **************  |
;*      49: |   *  ****      ****            | *  ******      **************  |
;*      50: |   *  ****      ****            | *      **      **************  |
;*      51: |   *  ****      ****            | *  *   **      **************  |
;*      52: |   *  ****      ****            | *  **  **      **************  |
;*      53: |   *  ****      ****            | *  ******      **************  |
;*      54: |   *  ****      ****            | *      **      **************  |
;*      55: |   *  ****      ****            | *      **      **************  |
;*      56: |   *  ****      ****            | *  **  **      **************  |
;*      57: |   *  ****      ****            | *      **      **************  |
;*      58: |   *  ****      ****            | *      **      **************  |
;*      59: |   *  ****      ****            | *      **      **************  |
;*      60: |   *  ****      ****            |**  *   **      **** *********  |
;*      61: |*  *  ****      ***             | *  *   **      **** *********  |
;*      62: |   *  ****      ***             | *  **  **      **** *********  |
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
;*      Total cycles (est.)         : 0 + min_trip_cnt * 63 = 12663        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             B1,1,B1
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C96:
;*   0              LDW     .D1T1   *A8++,A19         ; |85|  ^ 
;*   1              NOP             4
;*   5              MV      .L2X    A19,B20           ; |85| Define a twin register
;*     ||           SPDP    .S1     A19,A5:A4         ; |85|  ^ 
;*   6              NOP             1
;*   7              RCPDP   .S1     A5:A4,A5:A4       ; |85|  ^ 
;*   8              NOP             1
;*   9              CLR     .S1     A5,0,16,A21       ; |85|  ^ 
;*     ||           MV      .L1     A3,A4             ; |85| 
;*  10              MV      .L1     A21,A5            ; |85|  ^ 
;*     ||           EXTU    .S1     A21,1,21,A20      ; |85| 
;*  11              MPYSPDP .M1     A19,A5:A4,A5:A4   ; |85|  ^ 
;*     ||           ADD     .L1     A17,A20,A21       ; |85| 
;*     ||           EXTU    .S1     A21,12,29,A20     ; |85| 
;*  12              NOP             6
;*  18              FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |85|  ^ 
;*  19              NOP             2
;*  21              DPSP    .L1     A5:A4,A4          ; |85|  ^ 
;*  22              FMPYDP  .M2X    B9:B8,A5:A4,B7:B6 ; |85| 
;*  23              NOP             2
;*  25              MPYSP   .M1     A4,A4,A5          ; |85|  ^ 
;*  26              MPYSP   .M2X    B27,A4,B4         ; |85| 
;*  27              NOP             2
;*  29              MPYSP   .M1     A18,A5,A22        ; |85|  ^ 
;*  30              INTDP   .L1     A21,A5:A4         ; |85| 
;*     ||           FADDSP  .L2     B28,B4,B4         ; |85| 
;*     ||           MPYSP   .M1     A5,A4,A21         ; |85| 
;*     ||           MPYSP   .M2X    B25,A5,B30        ; |85| 
;*  31              MPYSP   .M1     A5,A5,A22         ; |85| 
;*  32              NOP             2
;*  34              FADDSP  .L2X    A22,B4,B4         ; |85|  ^ 
;*  35              MPYSP   .M2X    B26,A21,B31       ; |85| 
;*  36              FMPYDP  .M2X    B17:B16,A5:A4,B5:B4 ; |85| 
;*     ||           LDDW    .D1T1   *+A16[A20],A5:A4  ; |85| 
;*  37              MPYSP   .M2X    A22,B4,B0         ; |85|  ^ 
;*  38              NOP             3
;*  41              FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |85| 
;*     ||           FADDSP  .L2     B0,B31,B4         ; |85|  ^ 
;*  42              NOP             2
;*  44              FADDSP  .L2     B4,B30,B4         ; |85|  ^ 
;*  45              FMPYDP  .M2X    B19:B18,A5:A4,B5:B4 ; |85| 
;*  46              NOP             1
;*  47              MPYSP   .M2     B29,B4,B4         ; |85|  ^ 
;*  48              NOP             1
;*  49              FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |85| 
;*  50              NOP             1
;*  51              SPDP    .S2     B4,B7:B6          ; |85|  ^ 
;*  52              NOP             1
;*  53              FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |85|  ^ 
;*  54              NOP             2
;*  56              DPSP    .L2     B5:B4,B4          ; |85|  ^ 
;*  57      [ B1]   BDEC    .S2     $C$C96,B1         ; |155| 
;*  58              NOP             1
;*  59              CMPGTSP .S2     B20,B23,B0        ; |85| 
;*  60      [!B0]   MV      .L2     B24,B4            ; |85| 
;*     ||           CMPGTSP .S1     A19,A9,A0         ; |85| 
;*  61      [!A0]   MV      .S2     B4,B5             ; |85|  ^ 
;*     ||   [ A0]   MV      .L2     B22,B5            ; |85| 
;*  62              STW     .D2T2   B5,*B21++         ; |85|  ^ 
;*  63              ; BRANCHCC OCCURS {$C$C96}        ; |155| 
;*----------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L5:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 63
           LDW     .D1T1   *A8++,A19         ; |85| <0,0>  ^ 
           NOP             4

           MV      .L2X    A19,B20           ; |85| <0,5> Define a twin register
||         SPDP    .S1     A19,A5:A4         ; |85| <0,5>  ^ 

           NOP             1
           RCPDP   .S1     A5:A4,A5:A4       ; |85| <0,7>  ^ 
           NOP             1

           CLR     .S1     A5,0,16,A21       ; |85| <0,9>  ^ 
||         MV      .L1     A3,A4             ; |85| <0,9> 

           EXTU    .S1     A21,1,21,A20      ; |85| <0,10> 
||         MV      .L1     A21,A5            ; |85| <0,10>  ^ 

           EXTU    .S1     A21,12,29,A20     ; |85| <0,11> 
||         ADD     .L1     A17,A20,A21       ; |85| <0,11> 
||         MPYSPDP .M1     A19,A5:A4,A5:A4   ; |85| <0,11>  ^ 

           NOP             6
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |85| <0,18>  ^ 
           NOP             2
           DPSP    .L1     A5:A4,A4          ; |85| <0,21>  ^ 
           FMPYDP  .M2X    B9:B8,A5:A4,B7:B6 ; |85| <0,22> 
           NOP             2
           MPYSP   .M1     A4,A4,A5          ; |85| <0,25>  ^ 
           MPYSP   .M2X    B27,A4,B4         ; |85| <0,26> 
           NOP             2
           MPYSP   .M1     A18,A5,A22        ; |85| <0,29>  ^ 

           MPYSP   .M2X    B25,A5,B30        ; |85| <0,30> 
||         MPYSP   .M1     A5,A4,A21         ; |85| <0,30> 
||         INTDP   .L1     A21,A5:A4         ; |85| <0,30> 
||         FADDSP  .L2     B28,B4,B4         ; |85| <0,30> 

           MPYSP   .M1     A5,A5,A22         ; |85| <0,31> 
           NOP             2
           FADDSP  .L2X    A22,B4,B4         ; |85| <0,34>  ^ 
           MPYSP   .M2X    B26,A21,B31       ; |85| <0,35> 

           LDDW    .D1T1   *+A16[A20],A5:A4  ; |85| <0,36> 
||         FMPYDP  .M2X    B17:B16,A5:A4,B5:B4 ; |85| <0,36> 

           MPYSP   .M2X    A22,B4,B0         ; |85| <0,37>  ^ 
           NOP             3

           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |85| <0,41> 
||         FADDSP  .L2     B0,B31,B4         ; |85| <0,41>  ^ 

           NOP             2
           FADDSP  .L2     B4,B30,B4         ; |85| <0,44>  ^ 
           FMPYDP  .M2X    B19:B18,A5:A4,B5:B4 ; |85| <0,45> 
           NOP             1
           MPYSP   .M2     B29,B4,B4         ; |85| <0,47>  ^ 
           NOP             1
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |85| <0,49> 
           NOP             1
           SPDP    .S2     B4,B7:B6          ; |85| <0,51>  ^ 
           NOP             1
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |85| <0,53>  ^ 
           NOP             2
           DPSP    .L2     B5:B4,B4          ; |85| <0,56>  ^ 
   [ B1]   BDEC    .S2     $C$L5,B1          ; |155| <0,57> 
           NOP             1
           CMPGTSP .S2     B20,B23,B0        ; |85| <0,59> 

           CMPGTSP .S1     A19,A9,A0         ; |85| <0,60> 
|| [!B0]   MV      .L2     B24,B4            ; |85| <0,60> 

   [ A0]   MV      .L2     B22,B5            ; |85| <0,61> 
|| [!A0]   MV      .S2     B4,B5             ; |85| <0,61>  ^ 

           STW     .D2T2   B5,*B21++         ; |85| <0,62>  ^ 
;** --------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           STW     .D2T2   B22,*+SP(24)
           STW     .D2T2   B19,*+SP(52)
           STW     .D2T2   B18,*+SP(48)
           STW     .D2T2   B17,*+SP(60)
           STW     .D2T2   B16,*+SP(56)
           STW     .D2T1   A18,*+SP(16)
           STW     .D2T1   A7,*+SP(44)

           RINT                              ; interrupts on
||         STW     .D2T2   B24,*+SP(20)
||         MVK     .S1     0xc9,A6           ; |158| 

           MV      .L1     A9,A11
||         MV      .S1X    B23,A10
||         MV      .L2     B25,B11
||         MV      .S2     B27,B12
||         STW     .D2T2   B29,*+SP(12)
||         MV      .D1     A14,A4            ; |158| 

           CALLP   .S2     _log2sp_v,B3
||         LDW     .D2T2   *+B10(16),B4      ; |158| 
||         MV      .L1     A16,A12
||         MV      .S1     A17,A15
||         MV      .D1X    B26,A13
||         MV      .L2     B28,B13

$C$RL4:    ; CALL OCCURS {_log2sp_v} {0}     ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 48
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL5:    ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL6:    ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B6(8)        ; |67| 
||         MVKL    .S2     0x88e368f1,B6

           MV      .L2     B10,B5
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B5,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL7:    ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B4

           LDW     .D2T1   *+SP(32),A3       ; |68| 
||         MVKL    .S2     0x88e368f1,B6

           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B4
           MVKL    .S2     _output,B31
           MVKH    .S2     0x88e368f1,B6

           ADD     .L1     4,A3,A3
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x3ee4f8b5,B7

           MVKH    .S2     _output,B31
||         STW     .D2T1   A3,*+SP(64)

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL8:    ; CALL OCCURS {_isequal} {0}      ; |69| 
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
           STW     .D2T2   B4,*+SP(72)       ; |69| 
           STW     .D2T1   A3,*+SP(68)

   [!A0]   B       .S1     $C$L7             ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |162| 
   [!A0]   ZERO    .L1     A3                ; |72| 
   [ A0]   ADD     .L2     4,B4,B4
   [!A0]   MVKL    .S1     _all_pass,A4
   [!A0]   MVKH    .S1     _all_pass,A4
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
           CALL    .S1     _print_test_results ; |162| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x1,A4            ; |162| 
||         ADDKPC  .S2     $C$RL9,B3,0       ; |162| 

$C$RL9:    ; CALL OCCURS {_print_test_results} {0}  ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           MVKL    .S2     _a_sc,B5

           ZERO    .L2     B7
||         MVKL    .S2     0x7f7fffff,B29

           LDW     .D2T2   *+SP(20),B4       ; |175| 
||         MVKH    .S2     0xbf800000,B7

           MVKH    .S2     _a_sc,B5
||         ZERO    .L2     B31
||         MVK     .D2     -1,B6             ; |175| 

           MV      .L2     B5,B30            ; |170| 
||         STW     .D2T2   B7,*+SP(100)      ; |174| 
||         MVKH    .S2     0x7f7fffff,B29

           SET     .S2     B31,0x17,0x1d,B7
||         STW     .D2T2   B6,*+B30(24)      ; |175| 

           MV      .L1X    B5,A14            ; |170| 
||         ADD     .L2     1,B29,B5
||         MV      .S2     B30,B6
||         STW     .D2T2   B7,*+SP(96)       ; |174| 

           STDW    .D2T2   B5:B4,*+B6(8)     ; |172| 
           LDDW    .D2T2   *+SP(96),B5:B4    ; |170| 
           ZERO    .L1     A4
           MVK     .L2     0x7,B27

           MV      .L2     B6,B28            ; |172| 
||         MVKH    .S1     0x80000000,A4
||         MV      .L1     A10,A5            ; |170| 
||         STW     .D2T2   B27,*+SP(28)      ; |174| 

           STDW    .D2T1   A5:A4,*B28        ; |170| 
           STDW    .D2T2   B5:B4,*+B6(16)    ; |174| 
           LDW     .D1T1   *A14,A3           ; |177| 

           ZERO    .L2     B10
||         CALL    .S1     _log2             ; |177| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 5
           ADDKPC  .S2     $C$RL10,B3,2      ; |177| 
           SPDP    .S1     A3,A5:A4          ; |177| 
           NOP             1
$C$RL10:   ; CALL OCCURS {_log2} {0}         ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |177| 
           DPSP    .L1     A5:A4,A3          ; |177| 
           NOP             3
           ADD     .L2     B10,B4,B4         ; |177| 
           STW     .D2T1   A3,*B4            ; |177| 

           CALLP   .S2     ___isinff,B3
||         LDW     .D1T1   *A14,A4           ; |178| 

$C$RL11:   ; CALL OCCURS {___isinff} {0}     ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           MV      .L1     A4,A0             ; |178| 

           MV      .L1     A0,A2             ; |178| branch predicate copy
|| [ A0]   LDW     .D1T1   *A14,A3           ; |178| 
|| [!A0]   B       .S1     $C$L10            ; |178| 

   [!A2]   CALL    .S1     _log2sp           ; |178| 
   [!A2]   LDW     .D1T1   *A14,A4           ; |178| 
           NOP             2
           CMPGTSP .S1     A3,A10,A0         ; |178| 
           ; BRANCHCC OCCURS {$C$L10}        ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
   [!A0]   B       .S1     $C$L9             ; |178| 
   [ A0]   CALL    .S1     _log2             ; |178| 
   [ A0]   SPDP    .S1     A3,A5:A4          ; |178| 
           NOP             3
           ; BRANCHCC OCCURS {$C$L9}         ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL12,B3,0      ; |178| 
$C$RL12:   ; CALL OCCURS {_log2} {0}         ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           B       .S1     $C$L11            ; |178| 
||         DPSP    .L1     A5:A4,A3          ; |178| 
||         MVKL    .S2     _output,B5

           MVKH    .S2     _output,B5
           LDW     .D2T2   *+B5(4),B5        ; |178| 
           NOP             2
           MV      .L2X    A3,B4             ; |178| 
           ; BRANCH OCCURS {$C$L11}          ; |178| 
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _log2sp           ; |178| 
           LDW     .D1T1   *A14,A4           ; |178| 
           NOP             3
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL13,B3,0      ; |178| 
$C$RL13:   ; CALL OCCURS {_log2sp} {0}       ; |178| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           SPDP    .S1     A4,A5:A4          ; |178| 
           MVKL    .S2     _output,B5
           DPSP    .L1     A5:A4,A3          ; |178| 
           MVKH    .S2     _output,B5
           LDW     .D2T2   *+B5(4),B5        ; |178| 
           NOP             2
           MV      .L2X    A3,B4             ; |178| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 8
           NOP             1
           ADD     .L2     B10,B5,B5         ; |178| 

           STW     .D2T2   B4,*B5            ; |178| 
||         CALL    .S1     _log2sp_c         ; |179| 

           LDW     .D1T1   *A14,A4           ; |179| 
           ADDKPC  .S2     $C$RL14,B3,3      ; |179| 
$C$RL14:   ; CALL OCCURS {_log2sp_c} {0}     ; |179| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 75
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |179| 
           LDW     .D2T1   *+SP(16),A30      ; |85| 
           ZERO    .L1     A6                ; |85| 
           ZERO    .L1     A7
           SET     .S1     A7,0x14,0x1d,A7
           ADD     .L2     B10,B4,B4         ; |179| 
           STW     .D2T1   A4,*B4            ; |179| 
           LDW     .D1T1   *A14++,A3         ; |180| 
           LDW     .D2T2   *+SP(12),B31      ; |85| 
           MVKL    .S2     0xfefa39ec,B4
           MVKH    .S2     0xfefa39ec,B4
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |85| 
           NOP             1
           RCPDP   .S1     A5:A4,A5:A4       ; |85| 
           NOP             1

           CLR     .S1     A5,0,16,A8        ; |85| 
||         ZERO    .L1     A4                ; |85| 

           MV      .L1     A8,A5             ; |85| 
           MPYSPDP .M1     A3,A5:A4,A5:A4    ; |85| 
           EXTU    .S1     A8,1,21,A31       ; |85| 
           EXTU    .S1     A8,12,29,A29      ; |85| 
           CMPGTSP .S1     A3,A10,A1         ; |87| 
           CMPGTSP .S1     A3,A11,A0         ; |90| 
           NOP             2
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |85| 
           ADD     .L1     A15,A31,A6        ; |85| 
           NOP             1
           DPSP    .L1     A5:A4,A16         ; |85| 
           INTDP   .L1     A6,A7:A6          ; |85| 
           NOP             2
           MPYSP   .M1     A16,A16,A9        ; |85| 
           MPYSP   .M2X    B12,A16,B5        ; |85| 
           NOP             2
           MPYSP   .M1     A30,A9,A18        ; |85| 

           FADDSP  .L2     B13,B5,B6         ; |85| 
||         MPYSP   .M1     A9,A9,A17         ; |85| 
||         MVKL    .S2     0x3fe62e42,B5
||         MPYSP   .M2X    B11,A9,B8         ; |85| 

           MPYSP   .M1     A9,A16,A16        ; |85| 
||         MVKH    .S2     0x3fe62e42,B5

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |85| 
           LDDW    .D1T1   *+A12[A29],A7:A6  ; |85| 

           FADDSP  .L2X    A18,B6,B7         ; |85| 
||         MVKL    .S2     0x652b83a3,B6

           MVKH    .S2     0x652b83a3,B6
           MPYSP   .M1     A13,A16,A16       ; |85| 
           MPYSP   .M2X    A17,B7,B9         ; |85| 
           FSUBDP  .S1X    A7:A6,B5:B4,A7:A6 ; |85| 
           MVKL    .S2     0x3ff71547,B7
           MV      .L1X    B6,A8             ; |85| 
           FADDSP  .L2X    B9,A16,B9         ; |85| 
           MVKH    .S2     0x3ff71547,B7
           FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |85| 
           FADDSP  .L2     B9,B8,B8          ; |85| 
           MV      .L1X    B7,A9             ; |85| 
           FMPYDP  .M1     A9:A8,A7:A6,A5:A4 ; |85| 
           MPYSP   .M2     B31,B8,B6         ; |85| 
           MVKL    .S2     _output+12,B8
           MVKH    .S2     _output+12,B8
           LDW     .D2T2   *B8,B30           ; |180| 

           SPDP    .S2     B6,B5:B4          ; |85| 
||         FADDDP  .L2X    A5:A4,B5:B4,B7:B6 ; |85| 

           NOP             2

           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |85| 
||         LDW     .D2T2   *+SP(28),B6       ; |91| 

           NOP             2

           DPSP    .L2     B5:B4,B4          ; |85| 
|| [!A1]   LDW     .D2T2   *+SP(20),B4       ; |90| 
||         ADD     .S2     B10,B30,B5        ; |180| 

   [ A0]   LDW     .D2T2   *+SP(24),B4       ; |88| 
||         ADD     .L2     4,B10,B10         ; |176| 

           SUB     .L1X    B6,1,A0           ; |176| 

   [ A0]   BNOP    .S2     $C$L8,2           ; |176| 
|| [!A0]   SUBAW   .D2     B8,3,B10
|| [!A0]   MVKL    .S1     _a_sc,A4

           STW     .D2T2   B4,*B5            ; |180| 
||         SUB     .L2     B6,1,B4           ; |176| 

   [!A0]   CALL    .S1     _log2sp_v         ; |182| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |177| 
||         STW     .D2T2   B4,*+SP(28)       ; |180| 

   [ A0]   CALL    .S1     _log2             ; |177| 
|| [!A0]   LDW     .D2T2   *+B10(16),B4      ; |182| 

           ; BRANCHCC OCCURS {$C$L8}         ; |176| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S1     _a_sc,A4
           MVK     .L1     0x7,A6            ; |182| 
           ADDKPC  .S2     $C$RL15,B3,1      ; |182| 
$C$RL15:   ; CALL OCCURS {_log2sp_v} {0}     ; |182| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D2T1   *B10,A4           ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MVK     .L1     0x7,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL16:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B5
           MVKL    .S2     0x88e368f1,B6

           LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B10,A4           ; |67| 
||         MVK     .L1     0x7,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL17:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B10,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .L1     0x7,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL18:   ; CALL OCCURS {_isequal} {0}      ; |68| 

           LDW     .D2T1   *+SP(64),A3       ; |68| 
||         MVKL    .S2     _fcn_pass,B4

           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7
           MVKH    .S2     _fcn_pass,B4

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           MV      .L2     B10,B31           ; |69| 
||         STW     .D2T1   A3,*+SP(76)       ; |68| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B31,A4           ; |69| 
||         MVK     .L1     0x7,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL19:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(68),A3       ; |69| 
           MVKL    .S2     _fcn_pass,B31
           MVKH    .S2     _fcn_pass,B31
           LDW     .D2T1   *+SP(100),A30     ; |72| 
           LDW     .D2T1   *+SP(72),A31
           MV      .L2X    A3,B4             ; |174| 
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T1   A4,*+B31(16)      ; |69| 
           STW     .D2T1   A3,*+SP(80)       ; |174| 
           STW     .D2T1   A30,*+SP(28)      ; |69| 
           STW     .D2T1   A31,*+SP(84)      ; |72| 

   [!B0]   ZERO    .L1     A4                ; |72| 
|| [!B0]   B       .S1     $C$L12            ; |72| 
|| [ B0]   LDW     .D2T2   *+SP(84),B4

   [!B0]   CALL    .S1     _print_test_results ; |186| 
   [!B0]   MVKL    .S1     _all_pass,A3
           MV      .L2     B0,B1             ; guard predicate rewrite
   [!B0]   MVKH    .S1     _all_pass,A3

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
           CALL    .S1     _print_test_results ; |186| 
           MVKL    .S1     _all_pass,A3
           MVKH    .S1     _all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |186| 
||         ADDKPC  .S2     $C$RL20,B3,0      ; |186| 

$C$RL20:   ; CALL OCCURS {_print_test_results} {0}  ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 25
           LDW     .D2T1   *+SP(32),A4       ; |195| 
           LDW     .D2T1   *+SP(60),A31      ; |85| 
           LDW     .D2T1   *+SP(56),A30      ; |85| 

           LDW     .D2T1   *+SP(52),A29      ; |85| 
||         MVK     .S2     0xed,B30

           LDW     .D2T1   *+SP(48),A28      ; |85| 
||         MVKL    .S2     0xc000cccc,B5

           LDW     .D2T1   *+SP(44),A27      ; |85| 
||         MVKL    .S2     0xcccccccd,B31
||         ZERO    .L1     A26               ; |85| 

           MVKL    .S2     _a_ext,B4
||         STW     .D2T1   A26,*+SP(100)     ; |189| 

           MVKH    .S2     0xc000cccc,B5
||         STW     .D2T2   B30,*+SP(32)      ; |189| 

           ZERO    .L1     A3
||         MVKH    .S2     0xcccccccd,B31
||         STW     .D2T2   B5,*+SP(128)      ; |195| 

           MVKH    .S2     _a_ext,B4
||         SET     .S1     A3,0x17,0x17,A3
||         STW     .D2T2   B31,*+SP(132)     ; |195| 

           STW     .D2T1   A3,*B4            ; |189| 
           STW     .D2T1   A4,*+SP(88)       ; |85| 
           STW     .D2T1   A31,*+SP(112)     ; |85| 
           STW     .D2T1   A30,*+SP(116)     ; |85| 
           STW     .D2T1   A29,*+SP(104)     ; |85| 
           STW     .D2T1   A29,*+SP(120)     ; |85| 
           STW     .D2T1   A28,*+SP(108)     ; |85| 
           STW     .D2T1   A28,*+SP(124)     ; |85| 

           STW     .D2T1   A27,*+SP(96)      ; |85| 
||         MV      .L1X    B4,A14            ; |189| 

           LDW     .D1T1   *A14,A3           ; |191| 
           ZERO    .L2     B10               ; |85| 
           NOP             1
           CALL    .S1     _log2             ; |191| 
           NOP             1
           SPDP    .S2X    A3,B5:B4          ; |191| 
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

           DADD    .L1X    0,B5:B4,A5:A4     ; |191| 
||         ADDKPC  .S2     $C$RL21,B3,0      ; |191| 

$C$RL21:   ; CALL OCCURS {_log2} {0}         ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |191| 
           DPSP    .L1     A5:A4,A3          ; |191| 
           NOP             3
           ADD     .L2     B10,B4,B4         ; |191| 
           STW     .D2T1   A3,*B4            ; |191| 

           CALLP   .S2     _log2sp,B3
||         LDW     .D1T1   *A14,A4           ; |192| 

$C$RL22:   ; CALL OCCURS {_log2sp} {0}       ; |192| 
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(4),B4        ; |192| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |192| 
           STW     .D2T1   A4,*B4            ; |192| 

           CALLP   .S2     _log2sp_c,B3
||         LDW     .D1T1   *A14,A4           ; |193| 

$C$RL23:   ; CALL OCCURS {_log2sp_c} {0}     ; |193| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 108
           MVKL    .S2     _output,B4
           MVKH    .S2     _output,B4
           LDW     .D2T2   *+B4(8),B4        ; |193| 
           LDDW    .D2T1   *+SP(96),A7:A6
           LDW     .D2T1   *+SP(16),A31
           LDW     .D2T2   *+SP(12),B30
           LDW     .D2T2   *+SP(88),B6
           ADD     .L2     B10,B4,B4         ; |193| 
           STW     .D2T1   A4,*B4            ; |193| 
           LDW     .D1T1   *A14,A3           ; |194| 
           NOP             4
           SPDP    .S1     A3,A5:A4          ; |85| 
           LDW     .D2T2   *B6,B6            ; |194| 
           RCPDP   .S1     A5:A4,A5:A4       ; |85| 
           NOP             1

           CLR     .S1     A5,0,16,A8        ; |85| 
||         ZERO    .L1     A4                ; |85| 

           MV      .L1     A8,A5             ; |85| 
           MPYSPDP .M1     A3,A5:A4,A5:A4    ; |85| 
           EXTU    .S1     A8,1,21,A30       ; |85| 
           EXTU    .S1     A8,12,29,A29      ; |85| 
           CMPGTSP .S1     A3,A10,A1         ; |87| 
           CMPGTSP .S1     A3,A11,A0         ; |90| 
           ADD     .L2     B10,B6,B29        ; |194| 
           ADD     .L2     4,B10,B10         ; |190| 
           FSUBDP  .L1     A5:A4,A7:A6,A7:A6 ; |85| 
           NOP             2
           DPSP    .L1     A7:A6,A4          ; |85| 
           NOP             3
           MPYSP   .M1     A4,A4,A18         ; |85| 
           MPYSP   .M2X    B12,A4,B4         ; |85| 
           NOP             2
           MPYSP   .M1     A31,A18,A17       ; |85| 
           FADDSP  .L2     B13,B4,B4         ; |85| 
           MPYSP   .M1     A18,A18,A16       ; |85| 
           MPYSP   .M1     A18,A4,A9         ; |85| 
           ADD     .L1     A15,A30,A4        ; |85| 
           FADDSP  .L2X    A17,B4,B4         ; |85| 
           INTDP   .L1     A4,A5:A4          ; |85| 
           MPYSP   .M1     A13,A9,A19        ; |85| 

           MPYSP   .M2X    A16,B4,B5         ; |85| 
||         LDDW    .D2T1   *+SP(112),A17:A16 ; |85| 

           LDDW    .D1T1   *+A12[A29],A9:A8  ; |85| 
           MPYSP   .M2X    B11,A18,B31       ; |85| 
           NOP             2
           FMPYDP  .M1     A17:A16,A5:A4,A5:A4 ; |85| 
           FADDSP  .L2X    B5,A19,B5         ; |85| 
           NOP             2

           FSUBDP  .L1     A9:A8,A5:A4,A5:A4 ; |85| 
||         LDDW    .D2T1   *+SP(120),A9:A8

           FADDSP  .L2     B5,B31,B4         ; |85| 
           NOP             3

           FMPYDP  .M1     A9:A8,A7:A6,A7:A6 ; |85| 
||         LDDW    .D2T1   *+SP(104),A9:A8   ; |85| 

           MPYSP   .M2     B30,B4,B4         ; |85| 
           NOP             3
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |85| 
           SPDP    .S2     B4,B5:B4          ; |85| 
           NOP             2
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |85| 
           NOP             3
           FADDDP  .L2X    B5:B4,A5:A4,B5:B4 ; |85| 
           NOP             2

           DPSP    .L2     B5:B4,B4          ; |85| 
|| [!A1]   LDW     .D2T2   *+SP(20),B4       ; |90| 

   [ A0]   LDW     .D2T2   *+SP(24),B4       ; |88| 
           NOP             4
           STW     .D2T2   B4,*B29           ; |194| 
           LDW     .D1T2   *A14,B6           ; |195| 
           LDDW    .D2T2   *+SP(128),B5:B4
           NOP             4
           MPYSPDP .M2     B6,B5:B4,B5:B4    ; |195| 
           NOP             6

           DPSP    .L2     B5:B4,B4          ; |195| 
||         LDW     .D2T2   *+SP(32),B5

           NOP             3
           STW     .D1T2   B4,*++A14         ; |195| 

           SUB     .L1X    B5,1,A0           ; |190| 
||         SUB     .L2     B5,1,B4           ; |190| 

   [ A0]   B       .S1     $C$L13            ; |190| 
|| [ A0]   LDW     .D1T1   *A14,A3           ; |191| 
|| [!A0]   MVKL    .S2     _output,B10
||         STW     .D2T2   B4,*+SP(32)       ; |195| 

   [!A0]   MVKL    .S1     _a_ext,A4
   [!A0]   MVKH    .S2     _output,B10
   [ A0]   CALL    .S1     _log2             ; |191| 
   [!A0]   CALL    .S1     _log2sp_v         ; |197| 

           SPDP    .S2X    A3,B5:B4          ; |191| 
|| [!A0]   LDW     .D2T2   *+B10(16),B4      ; |197| 

           ; BRANCHCC OCCURS {$C$L13}        ; |190| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S1     _a_ext,A4
           MVK     .S1     0xed,A6           ; |197| 
           ADDKPC  .S2     $C$RL24,B3,1      ; |197| 
$C$RL24:   ; CALL OCCURS {_log2sp_v} {0}     ; |197| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T2   *B10,B5           ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7
           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(4),B4       ; |66| 
||         MV      .L1X    B5,A4             ; |66| 
||         MVK     .S1     0xed,A6           ; |66| 
||         MVK     .D1     0x1,A8            ; |66| 

$C$RL25:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     _fcn_pass,B6

           LDW     .D2T2   *B10,B5           ; |67| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKH    .S2     _fcn_pass,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B6(4)        ; |66| 
||         MVKL    .S2     0x88e368f1,B6

           MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T2   *+B10(8),B4       ; |67| 
||         MV      .L1X    B5,A4             ; |67| 
||         MVK     .S1     0xed,A6           ; |67| 
||         MVK     .D1     0x1,A8            ; |67| 

$C$RL26:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     _fcn_pass,B5
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L1X    B10,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B10(12),B4      ; |68| 
||         MVK     .S1     0xed,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL27:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           MVKL    .S2     _fcn_pass,B5

           LDW     .D2T1   *+SP(64),A3       ; |68| 
||         MVKL    .S2     0x3ee4f8b5,B7

           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     _fcn_pass,B5
           MVKH    .S2     0x3ee4f8b5,B7

           MV      .L2     B10,B4            ; |68| 
||         STW     .D2T1   A4,*+B5(12)       ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D2T1   *B4,A4            ; |69| 
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0xed,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL28:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(68),A3       ; |69| 
           LDW     .D2T2   *+SP(72),B5
           MVKL    .S2     _fcn_pass,B4
           MVKH    .S2     _fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [!A0]   B       .S1     $C$L14            ; |72| 
|| [ A0]   LDW     .D2T2   *B5,B0            ; |72| 

   [!A0]   CALL    .S1     _print_test_results ; |201| 
   [ A0]   ADD     .L2     4,B5,B4
   [!A0]   ZERO    .L1     A3                ; |72| 
   [!A0]   MVKL    .S1     _all_pass,A4
   [!A0]   MVKH    .S1     _all_pass,A4
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
           CALL    .S1     _print_test_results ; |201| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x4,A4            ; |201| 
||         ADDKPC  .S2     $C$RL29,B3,0      ; |201| 

$C$RL29:   ; CALL OCCURS {_print_test_results} {0}  ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ZERO    .L2     B5                ; |114| 

           ZERO    .L2     B4                ; |114| 
||         STW     .D2T2   B5,*+SP(96)       ; |114| 

           STW     .D2T2   B4,*+SP(100)      ; |114| 
           LDDW    .D2T2   *+SP(96),B5:B4    ; |114| 
           MVKL    .S2     _cycle_counts+24,B7
           MVKH    .S2     _cycle_counts+24,B7
           ZERO    .L2     B6                ; |114| 
           NOP             1

           STDW    .D2T2   B5:B4,*B7         ; |114| 
||         MVC     .S2     B6,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     _t_start,A3
           MVKH    .S1     _t_start,A3

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKL    .S1     _t_offset,A3

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     _t_offset,A3

           CALL    .S1     _gimme_random     ; |211| 
||         STDW    .D1T2   B5:B4,*A3         ; |117| 

           LDW     .D2T2   *+SP(28),B4       ; |211| 
||         MVKL    .S1     0x461c4400,A14

           MVK     .S1     0x80,A31
           MVKH    .S1     0x461c4400,A14

           MV      .L1     A14,A4            ; |211| 
||         STW     .D2T1   A31,*+SP(32)      ; |117| 
||         ZERO    .L2     B10

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
           ADDKPC  .S2     $C$RL30,B3,0      ; |211| 
$C$RL30:   ; CALL OCCURS {_gimme_random} {0}  ; |211| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 86
           MVKL    .S2     _input,B4
           MVKH    .S2     _input,B4
           LDW     .D2T2   *B4,B4            ; |211| 
           NOP             4
           ADD     .L2     B10,B4,B4         ; |211| 

           STW     .D2T1   A4,*B4            ; |211| 
||         MVC     .S2     TSCL,B8           ; |122| 

           MVC     .S2     TSCH,B9           ; |122| 

           SPDP    .S1     A4,A7:A6          ; |85| 
||         ZERO    .L1     A9
||         ZERO    .D1     A8                ; |85| 
||         LDW     .D2T1   *+SP(16),A30      ; |85| 
||         MVKL    .S2     0xfefa39ec,B4

           MVKH    .S2     0xfefa39ec,B4
||         LDW     .D2T2   *+SP(12),B31      ; |85| 

           RCPDP   .S1     A7:A6,A7:A6       ; |85| 
||         MVKL    .S2     _output+12,B30

           MVKH    .S2     _output+12,B30

           CLR     .S1     A7,0,16,A16       ; |85| 
||         ZERO    .L1     A6                ; |85| 
||         LDW     .D2T2   *B30,B29          ; |215| 
||         MVKL    .S2     _t_start,B28

           MV      .L1     A16,A7            ; |85| 
||         SET     .S1     A9,0x14,0x1d,A9
||         MVKH    .S2     _t_start,B28

           MPYSPDP .M1     A4,A7:A6,A7:A6    ; |85| 
||         EXTU    .S1     A16,1,21,A31      ; |85| 
||         STDW    .D2T2   B9:B8,*B28

           EXTU    .S1     A16,12,29,A28     ; |85| 
           CMPGTSP .S1     A4,A10,A1         ; |87| 
           CMPGTSP .S1     A4,A11,A0         ; |90| 
           NOP             3

           FSUBDP  .L1     A7:A6,A9:A8,A9:A8 ; |85| 
||         ADD     .S1     A15,A31,A6        ; |85| 

           INTDP   .L1     A6,A7:A6          ; |85| 
           NOP             1
           DPSP    .L1     A9:A8,A3          ; |85| 
           NOP             3
           MPYSP   .M1     A3,A3,A5          ; |85| 
           MPYSP   .M2X    B12,A3,B5         ; |85| 
           NOP             2
           MPYSP   .M1     A30,A5,A17        ; |85| 

           FADDSP  .L2     B13,B5,B6         ; |85| 
||         MPYSP   .M1     A5,A3,A18         ; |85| 
||         MVKL    .S2     0x3fe62e42,B5
||         MPYSP   .M2X    B11,A5,B16        ; |85| 

           MPYSP   .M1     A5,A5,A3          ; |85| 
||         MVKH    .S2     0x3fe62e42,B5

           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |85| 
||         LDDW    .D1T1   *+A12[A28],A7:A6  ; |85| 

           NOP             1

           FADDSP  .L2X    A17,B6,B7         ; |85| 
||         MPYSP   .M1     A13,A18,A29       ; |85| 
||         MVKL    .S2     0x652b83a3,B6

           MVKH    .S2     0x652b83a3,B6
           NOP             1

           MPYSP   .M2X    A3,B7,B17         ; |85| 
||         MVKL    .S2     0x3ff71547,B7
||         FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |85| 

           MVKH    .S2     0x3ff71547,B7
||         MV      .L1X    B6,A16            ; |85| 

           FMPYDP  .M2X    B7:B6,A9:A8,B5:B4 ; |85| 
           MV      .L1X    B7,A17            ; |85| 

           FADDSP  .L2X    B17,A29,B17       ; |85| 
||         FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |85| 

           NOP             2
           FADDSP  .L2     B17,B16,B16       ; |85| 
           NOP             2
           MPYSP   .M2     B31,B16,B6        ; |85| 
           NOP             3

           SPDP    .S2     B6,B5:B4          ; |85| 
||         FADDDP  .L2X    A7:A6,B5:B4,B7:B6 ; |85| 

           NOP             2
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |85| 
           NOP             2

           DPSP    .L2     B5:B4,B4          ; |85| 
|| [!A1]   LDW     .D2T2   *+SP(20),B4       ; |215| 
||         ADD     .S2     B10,B29,B5        ; |215| 

   [ A0]   LDW     .D2T2   *+SP(24),B4       ; |88| 
           NOP             4

           STW     .D2T2   B4,*B5            ; |215| 
||         MVC     .S2     TSCL,B4           ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     _t_offset,B6
||         MVKL    .S1     _cycle_counts+24,A3
||         LDW     .D2T1   *+SP(32),A27      ; |128| 

           MVKH    .S2     _t_offset,B6
||         MVKH    .S1     _cycle_counts+24,A3

           LDDW    .D2T2   *B6,B17:B16       ; |130| 
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S2     _t_stop,B27

           MVKH    .S2     _t_stop,B27
           STDW    .D2T2   B5:B4,*B27        ; |128| 
           SUB     .L1     A27,1,A0          ; |209| 
           STW     .D2T1   A0,*+SP(32)       ; |130| 
           ADDU    .L2     B16,B8,B7:B6      ; |130| 

           ADD     .S2     B7,B17,B16        ; |130| 
||         SUBU    .L2     B4,B6,B7:B6       ; |130| 
|| [ A0]   LDW     .D2T2   *+SP(28),B4       ; |211| 

           ADD     .L2     B16,B9,B8         ; |130| 

           SUB     .L2     B5,B8,B7          ; |130| 
||         EXT     .S2     B7,24,24,B8       ; |130| 
|| [ A0]   B       .S1     $C$L15            ; |209| 
||         ADDU    .L1X    A6,B6,A5:A4       ; |130| 

           ADD     .L2     B7,B8,B6          ; |130| 
|| [ A0]   CALL    .S1     _gimme_random     ; |211| 
||         ADD     .L1     A5,A7,A3          ; |130| 

           NOP             1

           ADD     .L1X    A3,B6,A5          ; |130| 
||         MVKL    .S1     _cycle_counts+24,A3

           MVKH    .S1     _cycle_counts+24,A3

           STDW    .D1T1   A5:A4,*A3         ; |130| 
||         ADD     .L2     4,B10,B10         ; |209| 
|| [ A0]   MV      .L1     A14,A4            ; |211| 

           ; BRANCHCC OCCURS {$C$L15}        ; |209| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALLP   .S2     __fltllif,B3
||         LDDW    .D1T1   *A3,A5:A4         ; |135| 

$C$RL31:   ; CALL OCCURS {__fltllif} {0}     ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A13
           SET     .S1     A13,0x1a,0x1d,A13
           MPYSP   .M1     A13,A4,A3         ; |135| 
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
           MVKL    .S1     _cycle_counts+24,A3

           LDDW    .D2T2   *+SP(96),B5:B4
||         MVKH    .S1     _cycle_counts+24,A3

           MV      .L2X    A10,B31           ; |114| 
           MV      .L2X    A3,B6
           STDW    .D2T1   A5:A4,*B6         ; |135| 
           SUBAW   .D2     B6,6,B11

           STDW    .D2T2   B5:B4,*B11        ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     _t_start,A14
           MVKH    .S1     _t_start,A14

           STDW    .D1T2   B7:B6,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S2     _t_offset,B13

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 
||         MVKH    .S2     _t_offset,B13

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MVKL    .S1     _input,A12

           MV      .L1X    B4,A15            ; |117| 
||         MVKH    .S1     _input,A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A12,A3           ; |223| 
           NOP             4

           ADD     .L1     A10,A3,A3         ; |223| 
||         CALL    .S1     _log2f            ; |223| 

           LDW     .D1T1   *A3,A4            ; |223| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |223| 
$C$RL33:   ; CALL OCCURS {_log2f} {0}        ; |223| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     _output,B4
||         SUB     .L1     A15,1,A0          ; |222| 
||         SUB     .S1     A15,1,A15         ; |222| 

           MVKH    .S2     _output,B4
           LDW     .D2T2   *B4,B4            ; |223| 
   [ A0]   BNOP    .S1     $C$L16,3          ; |222| 

           ADD     .L1X    A10,B4,A3         ; |223| 
||         ADD     .S1     4,A10,A10         ; |222| 

           STW     .D1T1   A4,*A3            ; |223| 
           ; BRANCHCC OCCURS {$C$L16}        ; |222| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B9:B8        ; |130| 

           MVKL    .S2     _t_stop,B10
           MV      .L2     B4,B7             ; |128| 
           MVKH    .S2     _t_stop,B10
           NOP             1
           ADDU    .L1X    B8,A6,A5:A4       ; |130| 

           ADD     .L1X    A5,B9,A3          ; |130| 
||         LDDW    .D2T2   *B11,B9:B8        ; |130| 

           ADD     .L1     A3,A7,A3          ; |130| 
||         SUBU    .L2X    B6,A4,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B7,A3,B31         ; |130| 
           CALL    .S1     __fltllif         ; |130| 

           ADDU    .L2     B8,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B8        ; |130| 

           ADD     .L2     B5,B9,B5          ; |130| 
           ADD     .L2     B5,B8,B5          ; |130| 
           STDW    .D2T2   B7:B6,*B10        ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL34,B3,0      ; |130| 

$C$RL34:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A13,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL35:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(96),B5:B4    ; |130| 
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B11        ; |130| 
           NOP             2

           STDW    .D2T2   B5:B4,*+B11(8)    ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B7             ; |116| 

           STDW    .D1T2   B7:B6,*A14        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B30         ; |117| 

           ADD     .L2     B30,B6,B5         ; |117| 

           STDW    .D2T2   B5:B4,*B13        ; |117| 
||         MVK     .S2     0x80,B4

           MV      .L1     A10,A15

           MV      .L1X    B4,A10            ; |117| 
||         LDW     .D2T2   *+SP(36),B12      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A12,A3           ; |231| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |231| 
||         CALL    .S1     _log2sp           ; |231| 

           LDW     .D1T1   *A3,A4            ; |231| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |231| 
$C$RL36:   ; CALL OCCURS {_log2sp} {0}       ; |231| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |231| 
||         SUB     .L1     A10,1,A0          ; |230| 
||         SUB     .S1     A10,1,A10         ; |230| 

   [ A0]   BNOP    .S1     $C$L17,3          ; |230| 

           ADD     .L1X    A15,B4,A3         ; |231| 
||         ADD     .S1     4,A15,A15         ; |230| 

           STW     .D1T1   A4,*A3            ; |231| 
           ; BRANCHCC OCCURS {$C$L17}        ; |230| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 18
           MVC     .S2     TSCL,B6           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B9:B8        ; |130| 

           MV      .L2     B4,B7             ; |128| 
           NOP             3
           ADDU    .L1X    B8,A4,A7:A6       ; |130| 

           ADD     .L1X    A7,B9,A3          ; |130| 
||         LDDW    .D2T2   *+B11(8),B9:B8    ; |130| 

           ADD     .L1     A3,A5,A3          ; |130| 
||         SUBU    .L2X    B6,A6,B5:B4       ; |130| 

           EXT     .S2     B5,24,24,B16      ; |130| 
           SUB     .L2X    B7,A3,B31         ; |130| 
           CALL    .S1     __fltllif         ; |130| 

           ADDU    .L2     B8,B4,B5:B4       ; |130| 
||         ADD     .S2     B31,B16,B8        ; |130| 

           ADD     .L2     B5,B9,B5          ; |130| 

           ADD     .L2     B5,B8,B5          ; |130| 
||         MV      .S2     B10,B8            ; |130| 

           STDW    .D2T2   B7:B6,*B8         ; |128| 

           DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         ADDKPC  .S2     $C$RL37,B3,0      ; |130| 

$C$RL37:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A13,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL38:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDDW    .D2T2   *+SP(96),B5:B4
           ADDAD   .D2     B11,1,B12
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B12        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B11(16)   ; |114| 
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

           MV      .L1     A10,A15

           MV      .L1X    B4,A10            ; |117| 
||         LDW     .D2T2   *+SP(40),B10      ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A12,A3           ; |239| 
           NOP             4

           ADD     .L1     A15,A3,A3         ; |239| 
||         CALL    .S1     _log2sp_c         ; |239| 

           LDW     .D1T1   *A3,A4            ; |239| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |239| 
$C$RL39:   ; CALL OCCURS {_log2sp_c} {0}     ; |239| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B10,B4           ; |239| 
||         SUB     .L1     A10,1,A0          ; |238| 
||         SUB     .S1     A10,1,A10         ; |238| 

   [ A0]   BNOP    .S1     $C$L18,3          ; |238| 

           ADD     .L1X    A15,B4,A3         ; |239| 
||         ADD     .S1     4,A15,A15         ; |238| 

           STW     .D1T1   A4,*A3            ; |239| 
           ; BRANCHCC OCCURS {$C$L18}        ; |238| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           LDDW    .D2T2   *+B11(16),B17:B16 ; |130| 
           MV      .L2     B4,B9             ; |128| 
           NOP             2
           ADDU    .L2X    B6,A4,B5:B4       ; |130| 

           ADD     .S2     B5,B7,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .L2X    B6,A5,B6          ; |130| 
||         CALL    .S1     __fltllif         ; |130| 
||         EXT     .S2     B5,24,24,B5       ; |130| 

           SUB     .S2     B9,B6,B4          ; |130| 
||         ADDU    .L2     B16,B4,B7:B6      ; |130| 

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
;          EXCLUSIVE CPU CYCLES: 108
           MPYSP   .M1     A13,A4,A3         ; |130| 
           ZERO    .L1     A10               ; |130| 
           NOP             3
           SPDP    .S2X    A3,B5:B4          ; |130| 
           NOP             2

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1X    A11:A10,B5:B4,A5:A4 ; |130| 

$C$RL41:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           LDDW    .D2T2   *+SP(96),B5:B4
           ADDAD   .D2     B12,1,B10
           MV      .L2X    A10,B31           ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |130| 
           NOP             1

           STDW    .D2T2   B5:B4,*+B11(32)   ; |114| 
||         MVC     .S2     B31,TSCL          ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 

           STDW    .D1T2   B5:B4,*A14        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B4,B7:B6       ; |117| 

           SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           MVKL    .S1     _output,A15
||         ADD     .L2     B4,B5,B7          ; |117| 

           MVKH    .S1     _output,A15
||         MV      .L2X    A12,B9            ; |246| 
||         STDW    .D2T2   B7:B6,*B13        ; |117| 

           CALLP   .S2     _log2sp_v,B3
||         LDW     .D1T2   *+A15(16),B4      ; |246| 
||         LDW     .D2T1   *B9,A4            ; |246| 
||         MVK     .S1     0x80,A6           ; |246| 

$C$RL42:   ; CALL OCCURS {_log2sp_v} {0}     ; |246| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MVK     .S1     16,A12
           ADD     .L1X    B10,A12,A12
           LDDW    .D1T1   *A12,A9:A8        ; |130| 
           MVKL    .S1     _t_stop,A3
           ADDU    .L1X    B6,A6,A5:A4       ; |130| 

           MVKH    .S1     _t_stop,A3
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

           CALLP   .S2     __fltllif,B3
||         ADD     .L1     A3,A5,A5          ; |130| 
||         STDW    .D2T2   B9:B8,*B4         ; |128| 

$C$RL43:   ; CALL OCCURS {__fltllif} {0}     ; |130| 
           MPYSP   .M1     A13,A4,A3         ; |130| 
           NOP             3
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __fixdlli,B3
||         FADDDP  .L1     A11:A10,A5:A4,A5:A4 ; |130| 

$C$RL44:   ; CALL OCCURS {__fixdlli} {0}     ; |130| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6

           STDW    .D1T1   A5:A4,*A12        ; |130| 
||         MVKH    .S2     0x3ee4f8b5,B7

           LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL45:   ; CALL OCCURS {_isequal} {0}      ; |66| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     _fcn_pass,B10
           MVKH    .S2     0x3ee4f8b5,B7
           MVKH    .S2     0x88e368f1,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S2     _fcn_pass,B10

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *+A15(8),B4       ; |67| 
||         STW     .D2T1   A3,*+B10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL46:   ; CALL OCCURS {_isequal} {0}      ; |67| 
           MVKL    .S2     0x3ee4f8b5,B7
           MVKL    .S2     0x88e368f1,B6
           MVKH    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(8)       ; |67| 
||         LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           CALLP   .S2     _isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL47:   ; CALL OCCURS {_isequal} {0}      ; |68| 
           LDW     .D2T1   *+SP(76),A3       ; |68| 
           MVKL    .S2     0x88e368f1,B6
           MVKL    .S2     0x3ee4f8b5,B7

           STW     .D2T1   A4,*+B10(12)      ; |68| 
||         MVKH    .S2     0x88e368f1,B6

           LDW     .D1T1   *A15,A4           ; |69| 
||         MVKH    .S2     0x3ee4f8b5,B7

           CALLP   .S2     _isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL48:   ; CALL OCCURS {_isequal} {0}      ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(80),B4       ; |69| 
           STW     .D2T1   A4,*+B10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(84),B4
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
   [ A0]   CALL    .S1     _print_test_results ; |252| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     _all_pass,A4
   [ A0]   MVKH    .S1     _all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L20}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     _print_test_results ; |252| 
           MVKL    .S1     _all_pass,A4
           MVKH    .S1     _all_pass,A4
           MV      .L1     A10,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |252| 
||         ADDKPC  .S2     $C$RL49,B3,0      ; |252| 

$C$RL49:   ; CALL OCCURS {_print_test_results} {0}  ; |252| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |253| 

$C$RL50:   ; CALL OCCURS {_printf} {0}       ; |253| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     _printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |253| 

$C$RL51:   ; CALL OCCURS {_printf} {0}       ; |253| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     _print_profile_results,B3
||         MV      .L1     A10,A4            ; |260| 

$C$RL52:   ; CALL OCCURS {_print_profile_results} {0}  ; |260| 

           CALLP   .S2     _print_memory_results,B3
||         MV      .L1     A10,A4            ; |263| 

$C$RL53:   ; CALL OCCURS {_print_memory_results} {0}  ; |263| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADDK    .S2     136,SP            ; |264| 
           LDW     .D2T2   *++SP(8),B3       ; |264| 
           LDDW    .D2T1   *++SP,A13:A12     ; |264| 
           LDDW    .D2T1   *++SP,A15:A14     ; |264| 
           LDDW    .D2T2   *++SP,B11:B10     ; |264| 
           LDDW    .D2T2   *++SP,B13:B12     ; |264| 

           LDW     .D2T1   *++SP(8),A10      ; |264| 
||         RET     .S2     B3                ; |264| 

           LDW     .D2T1   *++SP(8),A11      ; |264| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |264| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"log2SP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_printf
	.global	_log2f
	.global	___isinff
	.global	_log2
	.global	_driver_init
	.global	_print_profile_results
	.global	_print_memory_results
	.global	_print_test_results
	.global	_gimme_random
	.global	_isequal
	.global	_log2sp
	.global	_log2sp_c
	.global	_log2sp_v
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
	.global	_logtable
	.global	__fltllif
	.global	__fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
