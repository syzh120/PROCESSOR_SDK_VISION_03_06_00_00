;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:28:32 2013                                *
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
	.word	03f8239c5h		; a[0] @ 0
	.word	0340db22eh		; a[1] @ 32
	.word	0b41cdb83h		; a[2] @ 64
	.word	0342da428h		; a[3] @ 96
	.word	0b4403888h		; a[4] @ 128
	.word	03454c9d9h		; a[5] @ 160
	.word	0b46b8e8dh		; a[6] @ 192
	.word	034826176h		; a[7] @ 224
	.word	0b49054d7h		; a[8] @ 256
	.word	0349fc65eh		; a[9] @ 288
	.word	0b4b0deefh		; a[10] @ 320
	.word	034c3cbc8h		; a[11] @ 352
	.word	0b4d8bf05h		; a[12] @ 384
	.word	034eff022h		; a[13] @ 416
	.word	0b504ce41h		; a[14] @ 448
	.word	035130412h		; a[15] @ 480
	.word	0b522bf21h		; a[16] @ 512
	.word	035342915h		; a[17] @ 544
	.word	0b547700bh		; a[18] @ 576
	.word	0355cc709h		; a[19] @ 608
	.word	0b5746692h		; a[20] @ 640
	.word	035874699h		; a[21] @ 672
	.word	0b595c00eh		; a[22] @ 704
	.word	035a5c606h		; a[23] @ 736
	.word	0b5b782e7h		; a[24] @ 768
	.word	035cb25a1h		; a[25] @ 800
	.word	0b5e0e242h		; a[26] @ 832
	.word	035f8f245h		; a[27] @ 864
	.word	0b609cab4h		; a[28] @ 896
	.word	036188916h		; a[29] @ 928
	.word	0b628db5ah		; a[30] @ 960
	.word	0363aecach		; a[31] @ 992
	.word	0b64eece8h		; a[32] @ 1024
	.word	036651102h		; a[33] @ 1056
	.word	0b67d9399h		; a[34] @ 1088
	.word	0368c5ac9h		; a[35] @ 1120
	.word	0b69b5f62h		; a[36] @ 1152
	.word	036abff58h		; a[37] @ 1184
	.word	0b6be66b3h		; a[38] @ 1216
	.word	036d2c62ah		; a[39] @ 1248
	.word	0b6e953b1h		; a[40] @ 1280
	.word	03701257dh		; a[41] @ 1312
	.word	0b70ef712h		; a[42] @ 1344
	.word	0371e432bh		; a[43] @ 1376
	.word	0b72f3248h		; a[44] @ 1408
	.word	03741f143h		; a[45] @ 1440
	.word	0b756b1c0h		; a[46] @ 1472
	.word	0376daaa3h		; a[47] @ 1504
	.word	0b7838c69h		; a[48] @ 1536
	.word	037919fc7h		; a[49] @ 1568
	.word	0b7a134bbh		; a[50] @ 1600
	.word	037b27479h		; a[51] @ 1632
	.word	0b7c58cb4h		; a[52] @ 1664
	.word	037daafffh		; a[53] @ 1696
	.word	0b7f21646h		; a[54] @ 1728
	.word	03805fec4h		; a[55] @ 1760
	.word	0b8145529h		; a[56] @ 1792
	.word	038243449h		; a[57] @ 1824
	.word	0b835c62bh		; a[58] @ 1856
	.word	038493955h		; a[59] @ 1888
	.word	0b85ec142h		; a[60] @ 1920
	.word	0387696f5h		; a[61] @ 1952
	.word	0b8887cc4h		; a[62] @ 1984
	.word	03897176fh		; a[63] @ 2016
	.word	0b8a74222h		; a[64] @ 2048
	.word	038b927ach		; a[65] @ 2080
	.word	0b8ccf770h		; a[66] @ 2112
	.word	038e2e5e4h		; a[67] @ 2144
	.word	0b8fb2d15h		; a[68] @ 2176
	.word	0390b06a6h		; a[69] @ 2208
	.word	0b919e6d6h		; a[70] @ 2240
	.word	0392a5e82h		; a[71] @ 2272
	.word	0b93c9942h		; a[72] @ 2304
	.word	03950c761h		; a[73] @ 2336
	.word	0b9671e3ch		; a[74] @ 2368
	.word	0397fd904h		; a[75] @ 2400
	.word	0b98d9c99h		; a[76] @ 2432
	.word	0399cc3a0h		; a[77] @ 2464
	.word	0b9ad89b8h		; a[78] @ 2496
	.word	039c01b45h		; a[79] @ 2528
	.word	0b9d4a973h		; a[80] @ 2560
	.word	039eb6ab0h		; a[81] @ 2592
	.word	0ba024d9ch		; a[82] @ 2624
	.word	03a103ee0h		; a[83] @ 2656
	.word	0ba1fae0dh		; a[84] @ 2688
	.word	03a30c3ffh		; a[85] @ 2720
	.word	0ba43adf6h		; a[86] @ 2752
	.word	03a589e04h		; a[87] @ 2784
	.word	0ba6fcb99h		; a[88] @ 2816
	.word	03a84ba06h		; a[89] @ 2848
	.word	0ba92edaeh		; a[90] @ 2880
	.word	03aa2a655h		; a[91] @ 2912
	.word	0bab40da8h		; a[92] @ 2944
	.word	03ac751b0h		; a[93] @ 2976
	.word	0badca56eh		; a[94] @ 3008
	.word	03af4415bh		; a[95] @ 3040
	.word	0bb073201h		; a[96] @ 3072
	.word	03b15a946h		; a[97] @ 3104
	.word	0bb25acc9h		; a[98] @ 3136
	.word	03b3766f5h		; a[99] @ 3168
	.word	0bb4b06b5h		; a[100] @ 3200
	.word	03b60c001h		; a[101] @ 3232
	.word	0bb78cc5ah		; a[102] @ 3264
	.word	03b89b5b9h		; a[103] @ 3296
	.word	0bb9871deh		; a[104] @ 3328
	.word	03ba8c1a2h		; a[105] @ 3360
	.word	0bbbad036h		; a[106] @ 3392
	.word	03bcecd67h		; a[107] @ 3424
	.word	0bbe4ee21h		; a[108] @ 3456
	.word	03bfd6cfeh		; a[109] @ 3488
	.word	0bc0c4569h		; a[110] @ 3520
	.word	03c1b47b8h		; a[111] @ 3552
	.word	0bc2be52bh		; a[112] @ 3584
	.word	03c3e49b2h		; a[113] @ 3616
	.word	0bc52a615h		; a[114] @ 3648
	.word	03c693025h		; a[115] @ 3680
	.word	0bc8111d3h		; a[116] @ 3712
	.word	03c8ee14fh		; a[117] @ 3744
	.word	0bc9e2b14h		; a[118] @ 3776
	.word	03caf17a0h		; a[119] @ 3808
	.word	0bcc1d3c0h		; a[120] @ 3840
	.word	03cd6910ch		; a[121] @ 3872
	.word	0bced8676h		; a[122] @ 3904
	.word	03d037860h		; a[123] @ 3936
	.word	0bd11899dh		; a[124] @ 3968
	.word	03d211c2dh		; a[125] @ 4000
	.word	0bd32594eh		; a[126] @ 4032
	.word	03d456ea2h		; a[127] @ 4064
	.word	0bd5a8eb2h		; a[128] @ 4096
	.word	03d71f16ah		; a[129] @ 4128
	.word	0bd85ea5dh		; a[130] @ 4160
	.word	03d943e94h		; a[131] @ 4192
	.word	0bda41b49h		; a[132] @ 4224
	.word	03db5aa7dh		; a[133] @ 4256
	.word	0bdc91ab0h		; a[134] @ 4288
	.word	03dde9f50h		; a[135] @ 4320
	.word	0bdf67169h		; a[136] @ 4352
	.word	03e0867feh		; a[137] @ 4384
	.word	0be170070h		; a[138] @ 4416
	.word	03e2728adh		; a[139] @ 4448
	.word	0be390b7eh		; a[140] @ 4480
	.word	03e4cd83bh		; a[141] @ 4512
	.word	0be62c358h		; a[142] @ 4544
	.word	03e7b06d2h		; a[143] @ 4576
	.word	0be8af178h		; a[144] @ 4608
	.word	03e99cf68h		; a[145] @ 4640
	.word	0beaa4492h		; a[146] @ 4672
	.word	03ebc7c8fh		; a[147] @ 4704
	.word	0bed0a793h		; a[148] @ 4736
	.word	03ee6fb0ch		; a[149] @ 4768
	.word	0beffb211h		; a[150] @ 4800
	.word	03f0d870ah		; a[151] @ 4832
	.word	0bf1cabc2h		; a[152] @ 4864
	.word	03f2d6f4ah		; a[153] @ 4896
	.word	0bf3ffe04h		; a[154] @ 4928
	.word	03f548912h		; a[155] @ 4960
	.word	0bf6b46d6h		; a[156] @ 4992
	.word	0c2b2d072h		; a[157] @ 5024
	.word	0bf9028e5h		; a[158] @ 5056
	.word	03f9f95bch		; a[159] @ 5088
	.word	0bfb0a915h		; a[160] @ 5120
	.word	03fc3902ah		; a[161] @ 5152
	.word	0bfd87d0bh		; a[162] @ 5184
	.word	03fefa711h		; a[163] @ 5216
	.word	0c004a5d3h		; a[164] @ 5248
	.word	04012d752h		; a[165] @ 5280
	.word	0c0228d93h		; a[166] @ 5312
	.word	04033f23dh		; a[167] @ 5344
	.word	0c0473355h		; a[168] @ 5376
	.word	0405c83d3h		; a[169] @ 5408
	.word	0c0741c2ah		; a[170] @ 5440
	.word	040871d6bh		; a[171] @ 5472
	.word	0c095927bh		; a[172] @ 5504
	.word	040a59390h		; a[173] @ 5536
	.word	0c0b74b08h		; a[174] @ 5568
	.word	040cae7cdh		; a[175] @ 5600
	.word	0c0e09dc9h		; a[176] @ 5632
	.word	040f8a67ah		; a[177] @ 5664
	.word	0c109a0c0h		; a[178] @ 5696
	.word	041185aa8h		; a[179] @ 5728
	.word	0c128a7f0h		; a[180] @ 5760
	.word	0413ab3c6h		; a[181] @ 5792
	.word	0c14eadebh		; a[182] @ 5824
	.word	04164cb49h		; a[183] @ 5856
	.word	0c17d4669h		; a[184] @ 5888
	.word	0418c300ch		; a[185] @ 5920
	.word	0c19b3016h		; a[186] @ 5952
	.word	041abcafah		; a[187] @ 5984
	.word	0c1be2cbah		; a[188] @ 6016
	.word	041d28600h		; a[189] @ 6048
	.word	0c1e90ca8h		; a[190] @ 6080
	.word	04200fe2bh		; a[191] @ 6112
	.word	0c20ecb8dh		; a[192] @ 6144
	.word	0421e12fch		; a[193] @ 6176
	.word	0c22efcf5h		; a[194] @ 6208
	.word	04241b63bh		; a[195] @ 6240
	.word	0c2567062h		; a[196] @ 6272
	.word	0426d624bh		; a[197] @ 6304
	.word	0c283645bh		; a[198] @ 6336
	.word	042917373h		; a[199] @ 6368
	.word	0c2b2d072h		; a[200] @ 6400

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\054003 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\054005 
	.sect	".text:optci"
	.clink

;******************************************************************************
;* FUNCTION NAME: expsp_coshsp_i                                              *
;*                                                                            *
;*   Regs Modified     : A0,A3,A4,A5,A6,A7,A8,B4,B5,B6,B7,B8,B9               *
;*   Regs Used         : A0,A3,A4,A5,A6,A7,A8,B3,B4,B5,B6,B7,B8,B9            *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
expsp_coshsp_i:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 67
           MVKL    .S1     0x41b8aa3b,A3
           MVKH    .S1     0x41b8aa3b,A3
           MPYSP   .M1     A3,A4,A3          ; |79| 
           ZERO    .L2     B4
           SET     .S2     B4,0x18,0x1d,B4
           ZERO    .L1     A5
           MVKH    .S1     0xbf000000,A5
           FADDSP  .L2X    B4,A3,B4          ; |79| 
           CMPLTSP .S1     A3,A5,A0          ; |80| 
           MVKL    .S2     0x3fa62e42,B9
           SPTRUNC .L2     B4,B6             ; |79| 
           MVKL    .S2     0xfef2e4e7,B8
           MVKH    .S2     0x3fa62e42,B9
           MVKH    .S2     0xfef2e4e7,B8
   [ A0]   SUB     .L2     B6,1,B6           ; |81| 
           INTDP   .L2     B6,B5:B4          ; |89| 
           SPDP    .S1     A4,A7:A6          ; |89| 
           MVKL    .S2     jTable,B7
           MVKH    .S2     jTable,B7
           MVKL    .S1     0x42b17218,A8
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |89| 
           SUB     .D2     B6,16,B8          ; |91| 
           EXTU    .S2     B8,30,30,B6       ; |102| 
           LDDW    .D2T2   *+B7[B6],B7:B6    ; |102| 
           MVKH    .S1     0x42b17218,A8
           FSUBDP  .L1X    A7:A6,B5:B4,A7:A6 ; |89| 
           MVKL    .S2     0x3f00010f,B4
           MVKH    .S2     0x3f00010f,B4
           DPSP    .L1     A7:A6,A3          ; |89| 
           MVKL    .S1     0x3e2aab29,A7
           MVKH    .S1     0x3e2aab29,A7
           MVKL    .S2     kTable,B5
           MPYSP   .M1     A3,A3,A5          ; |89| 
           MVKH    .S2     kTable,B5
           NOP             2
           MPYSP   .M1     A5,A3,A6          ; |89| 
           MPYSP   .M2X    B4,A5,B9          ; |89| 
           EXTU    .S2     B8,28,30,B4       ; |102| 
           LDDW    .D2T2   *+B5[B4],B5:B4    ; |102| 
           MPYSP   .M1     A7,A6,A5          ; |89| 
           NOP             3
           FADDSP  .L1X    B9,A5,A6          ; |89| 
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |102| 
           ZERO    .S1     A5
           FADDSP  .L1     A6,A3,A6          ; |89| 
           SET     .S1     A5,0x17,0x1d,A5
           SHL     .S1X    B8,16,A3          ; |102| 
           FADDSP  .L1     A5,A6,A5          ; |102| 
           CLR     .S1     A3,0,19,A3        ; |102| 
           MV      .S1X    B4,A6             ; |102| 
           ADD     .L1X    A3,B5,A7          ; |102| 
           MPYSPDP .M1     A5,A7:A6,A7:A6    ; |102| 
           MVKL    .S2     0x3f317218,B4
           MVKH    .S2     0x3f317218,B4
           ZERO    .L1     A5
           FSUBSP  .L1X    A4,B4,A3          ; |106| 
           SET     .S1     A5,0x17,0x1e,A5
           NOP             1
           RET     .S2     B3                ; |111| 
           DPSP    .L1     A7:A6,A4          ; |102| 
           CMPGTSP .S1     A3,A8,A0          ; |106| 
           NOP             2
   [ A0]   MV      .L1     A5,A4             ; |107| 
           ; BRANCH OCCURS {B3}              ; |111| 
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
;*   Local Frame Size  : 8 Args + 4 Auto + 56 Save = 68 byte                  *
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

           STW     .D2T2   B3,*SP--(24)      ; |122| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL0:    ; CALL OCCURS {driver_init} {0}   ; |130| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     0xc9,B4
||         MVKL    .S1     a,A12

           MVKH    .S1     a,A12
||         MVKL    .S2     output,B11

           CALL    .S1     coshf             ; |138| 
||         MV      .L1     A12,A13
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
           LDW     .D1T1   *A13++,A4         ; |138| 
           ADDKPC  .S2     $C$RL1,B3,3       ; |138| 
$C$RL1:    ; CALL OCCURS {coshf} {0}         ; |138| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |138| 
||         SUB     .L1     A10,1,A0          ; |137| 
||         SUB     .S1     A10,1,A10         ; |137| 

   [ A0]   BNOP    .S1     $C$L1,3           ; |137| 

           ADD     .L2     B10,B4,B5         ; |138| 
||         ADD     .D2     4,B10,B10         ; |137| 
|| [!A0]   MVK     .S2     0xc9,B4

   [ A0]   CALL    .S1     coshf             ; |138| 
||         STW     .D2T1   A4,*B5            ; |138| 

           ; BRANCHCC OCCURS {$C$L1}         ; |137| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           CALL    .S1     coshsp            ; |141| 
||         MV      .L1X    B4,A10
||         ZERO    .L2     B10
||         MV      .D1     A12,A11
||         ADD     .S2     4,B11,B12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |141| 
           ADDKPC  .S2     $C$RL2,B3,3       ; |141| 
$C$RL2:    ; CALL OCCURS {coshsp} {0}        ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |141| 
||         SUB     .L1     A10,1,A0          ; |140| 
||         SUB     .S1     A10,1,A10         ; |140| 

   [ A0]   BNOP    .S1     $C$L2,3           ; |140| 

           ADD     .L2     B10,B4,B5         ; |141| 
||         ADD     .D2     4,B10,B10         ; |140| 
|| [!A0]   MVK     .S2     0xc9,B4

   [ A0]   CALL    .S1     coshsp            ; |141| 
||         STW     .D2T1   A4,*B5            ; |141| 

           ; BRANCHCC OCCURS {$C$L2}         ; |140| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           CALL    .S1     coshsp_c          ; |144| 
||         MV      .L1X    B4,A10
||         ZERO    .L2     B10
||         MV      .D1     A11,A12
||         ADD     .S2     4,B12,B12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |144| 
           ADDKPC  .S2     $C$RL3,B3,3       ; |144| 
$C$RL3:    ; CALL OCCURS {coshsp_c} {0}      ; |144| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B12,B4           ; |144| 
||         SUB     .L1     A10,1,A0          ; |143| 
||         SUB     .S1     A10,1,A10         ; |143| 

   [ A0]   BNOP    .S1     $C$L3,3           ; |143| 
|| [!A0]   ADD     .L1X    4,B12,A10

           ADD     .L2     B10,B4,B5         ; |144| 
||         ADD     .S2     4,B10,B10         ; |143| 

   [ A0]   CALL    .S1     coshsp_c          ; |144| 
||         STW     .D2T1   A4,*B5            ; |144| 

           ; BRANCHCC OCCURS {$C$L3}         ; |143| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           ZERO    .L1     A12
||         MVK     .S1     0xc9,A1
||         SUB     .L2X    A11,4,B16
||         LDW     .D1T2   *A10,B17

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 13
           LDW     .D2T2   *++B16,B5         ; |147| 
           ZERO    .L2     B4
           MVKH    .S2     0x41800000,B4
           NOP             2
           ABSSP   .S2     B5,B18            ; |208| 

           CMPGTSP .S2     B18,B4,B0         ; |212| 
||         ZERO    .L2     B4

   [!B0]   ZERO    .L1     A9
|| [ B0]   B       .S1     $C$L6             ; |212| 
||         SET     .S2     B4,0x17,0x1d,B4
||         MV      .L2     B0,B2             ; |212| branch predicate copy
||         MV      .D2     B0,B1             ; guard predicate rewrite

   [!B0]   SET     .S1     A9,0x18,0x1d,A9
||         CMPGTSP .S2     B18,B4,B0         ; |215| 

   [ B1]   MVK     .L2     0x1,B0            ; |215| nullify predicate
   [!B0]   B       .S1     $C$L5             ; |215| 
   [ B2]   CALL    .S1     expsp_coshsp_i    ; |213| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L6}         ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

   [ B0]   CALL    .S1     expsp_coshsp_i    ; |219| 
|| [!B0]   MPYSP   .M2     B5,B5,B5          ; |178| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L5}         ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           ADDKPC  .S2     $C$RL4,B3,1       ; |219| 
           MV      .L1X    B5,A4             ; |219| 
$C$RL4:    ; CALL OCCURS {expsp_coshsp_i} {0}  ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           ZERO    .L1     A6
           SET     .S1     A6,0x1e,0x1e,A6
           MPYSP   .M1     A6,A4,A3          ; |219| 
           MV      .L1     A6,A4             ; |219| 
           MVKL    .S2     0x7f7fffff,B4
           MVKH    .S2     0x7f7fffff,B4
           RCPSP   .S1     A3,A5             ; |131| 
           MPYSP   .M1     A3,A5,A7          ; |131| 
           CMPEQSP .S1     A3,A12,A0         ; |133| 
           ABSSP   .S2X    A3,B5             ; |137| 
           CMPGTSP .S2     B5,B4,B0          ; |137| 
           FSUBSP  .L1     A4,A7,A6          ; |131| 
           SUB     .L1     A1,1,A1           ; |146| 
           MVKL    .S2     0x42b2d4fc,B4
           MPYSP   .M1     A5,A6,A5          ; |131| 
           NOP             3
           MPYSP   .M1     A3,A5,A6          ; |131| 
           NOP             3
           FSUBSP  .L1     A4,A6,A4          ; |131| 
           NOP             2
           MPYSP   .M1     A5,A4,A4          ; |131| 
           NOP             3
   [ A0]   MV      .L1     A12,A4            ; |134| 
   [ B0]   MV      .L1     A12,A4            ; |138| 
           FADDSP  .L1     A4,A3,A3          ; |221| 
           NOP             2

           BNOP    .S1     $C$L7,4           ; |221| 
||         MPYSP   .M1     A9,A3,A3          ; |221| 

           MV      .L2X    A3,B5             ; |221| Define a twin register
||         ZERO    .L1     A3

           ; BRANCH OCCURS {$C$L7}           ; |221| 
;** --------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 21

           MVKL    .S1     0x3ab60b61,A4
||         MVKL    .S2     0x37d00d01,B8

           MVKH    .S2     0x37d00d01,B8
||         MPYSP   .M2     B5,B5,B4          ; |178| 

           MPYSP   .M1X    A9,B5,A5          ; |178| 
           MVKL    .S1     0x3d2aaaab,A3
           MVKH    .S1     0x3ab60b61,A4
           MPYSP   .M2     B4,B5,B7          ; |178| 
           MPYSP   .M2     B4,B4,B6          ; |178| 
           MVKH    .S1     0x3d2aaaab,A3
           MPYSP   .M1X    A3,B4,A3          ; |178| 
           MPYSP   .M2X    A4,B7,B4          ; |178| 
           MPYSP   .M2     B8,B6,B5          ; |178| 
           SUB     .L1     A1,1,A1           ; |146| 
           ZERO    .L2     B31
           FADDSP  .L1     A3,A5,A3          ; |178| 
           FADDSP  .L2     B4,B5,B4          ; |178| 
           BNOP    .S1     $C$L8,1           ; |178| 

           FADDSP  .L2X    B4,A3,B5          ; |178| 
||         ZERO    .L1     A3
||         SET     .S2     B31,0x17,0x1d,B4

           SET     .S1     A3,0x17,0x1e,A3
   [ A1]   B       .S1     $C$L4             ; |146| 

           FADDSP  .L2     B4,B5,B5          ; |178| 
||         MVKL    .S2     0x42b2d4fc,B4

           ; BRANCH OCCURS {$C$L8}           ; |178| 
;** --------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 4
           MV      .L1X    B18,A4            ; |213| 
           ADDKPC  .S2     $C$RL5,B3,2       ; |213| 
$C$RL5:    ; CALL OCCURS {expsp_coshsp_i} {0}  ; |213| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           SUB     .L1     A1,1,A1           ; |146| 
||         MVKL    .S2     0x42b2d4fc,B4
||         MV      .L2X    A4,B5             ; |213| 
||         ZERO    .S1     A3

;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 2

   [ A1]   BNOP    .S2     $C$L4,1           ; |146| 
||         SET     .S1     A3,0x17,0x1e,A3

;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 4
           MVKH    .S2     0x42b2d4fc,B4
           CMPGTSP .S2     B18,B4,B0         ; |224| 
   [ B0]   MV      .L2X    A3,B5             ; |225| 

           STW     .D2T2   B5,*B17++         ; |147| 
|| [!A1]   CALL    .S1     coshsp_v          ; |149| 

           ; BRANCHCC OCCURS {$C$L4}         ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+B11(16),B4      ; |149| 
           ADDKPC  .S2     $C$RL6,B3,2       ; |149| 

           MV      .L1     A11,A4            ; |149| 
||         MVK     .S1     0xc9,A6           ; |149| 

$C$RL6:    ; CALL OCCURS {coshsp_v} {0}      ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T1   *B11,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B11(4),B4       ; |66| 
||         MVK     .S1     0xc9,A6           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 

$C$RL7:    ; CALL OCCURS {isequal} {0}       ; |66| 
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
||         MVK     .S1     0xc9,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL8:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5

           LDW     .D2T2   *+B11(12),B4      ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L2     B11,B8
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B8,A4            ; |68| 
||         MVK     .S1     0xc9,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL9:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0x3eb0c6f7,B7

           ADD     .L1     4,A10,A15
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B11,A4           ; |69| 
||         LDW     .D1T2   *A15,B4           ; |69| 
||         MVK     .S1     0xc9,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL10:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S1     fcn_pass,A3
           MVKH    .S1     fcn_pass,A3
           ADD     .L1     4,A3,A14
           LDW     .D1T1   *A14,A0           ; |72| 
           MV      .L2X    A3,B4             ; |72| 
           STW     .D2T1   A4,*+B4(16)       ; |69| 
           ADD     .L2X    8,A3,B10
           NOP             1

   [!A0]   B       .S1     $C$L9             ; |72| 
|| [ A0]   LDW     .D2T2   *B10,B0           ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |155| 
   [ A0]   ADD     .L2     4,B10,B4
   [!A0]   MVKL    .S2     all_pass,B4
   [!A0]   MV      .L2X    A12,B5
   [!A0]   MVKH    .S2     all_pass,B4
           ; BRANCHCC OCCURS {$C$L9}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
           MVK     .L2     0x1,B5            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   MV      .L2X    A12,B5
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |155| 
           MVKL    .S2     all_pass,B4
           MVKH    .S2     all_pass,B4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x1,A4            ; |155| 
||         STW     .D2T2   B5,*B4            ; |72| 
||         ADDKPC  .S2     $C$RL11,B3,0      ; |155| 

$C$RL11:   ; CALL OCCURS {print_test_results} {0}  ; |155| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           ZERO    .L1     A13

           MVKH    .S1     0x80000000,A13
||         MVKL    .S2     a_sc,B12
||         ZERO    .L1     A3

           SET     .S1     A3,0x17,0x1d,A3
||         MVKH    .S2     a_sc,B12

           STDW    .D2T1   A13:A12,*B12      ; |163| 
||         ADD     .L1     -1,A13,A6
||         ZERO    .L2     B5
||         ZERO    .S1     A31
||         MVK     .D1     -1,A7             ; |169| 

           STDW    .D2T1   A7:A6,*+B12(24)   ; |169| 
||         SET     .S1     A31,0x17,0x1e,A3
||         MV      .L2X    A3,B4             ; |167| 
||         MVKH    .S2     0xbf800000,B5
||         ZERO    .L1     A5

           STDW    .D2T2   B5:B4,*+B12(16)   ; |167| 
||         MV      .L1     A3,A4             ; |165| 
||         MVKH    .S1     0xff800000,A5

           CALL    .S1     coshf             ; |172| 
||         STDW    .D2T1   A5:A4,*+B12(8)    ; |165| 
||         SUB     .L1X    B12,4,A11
||         MV      .D1     A12,A10
||         MVK     .L2     0x8,B11

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
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *++A11,A4         ; |172| 
           ADDKPC  .S2     $C$RL12,B3,3      ; |172| 
$C$RL12:   ; CALL OCCURS {coshf} {0}         ; |172| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 28
           MVKL    .S1     output,A13
           MVKH    .S1     output,A13
           LDW     .D1T2   *A13,B4           ; |172| 
           NOP             4
           ADD     .L2X    A10,B4,B4         ; |172| 
           STW     .D2T1   A4,*B4            ; |172| 

           CALLP   .S2     coshsp,B3
||         LDW     .D1T1   *A11,A4           ; |173| 

$C$RL13:   ; CALL OCCURS {coshsp} {0}        ; |173| 
           LDW     .D1T2   *+A13(4),B4       ; |173| 
           NOP             4
           ADD     .L2X    A10,B4,B4         ; |173| 
           STW     .D2T1   A4,*B4            ; |173| 

           CALLP   .S2     coshsp_c,B3
||         LDW     .D1T1   *A11,A4           ; |174| 

$C$RL14:   ; CALL OCCURS {coshsp_c} {0}      ; |174| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDW     .D1T1   *+A13(8),A3       ; |174| 
           ZERO    .L2     B4
           MVKH    .S2     0x41800000,B4
           NOP             2
           ADD     .L1     A10,A3,A3         ; |174| 
           STW     .D1T1   A4,*A3            ; |174| 
           LDW     .D1T1   *A11,A4           ; |175| 
           NOP             4
           ABSSP   .S2X    A4,B16            ; |208| 

           CMPGTSP .S2     B16,B4,B0         ; |212| 
||         ZERO    .L2     B4

   [ B0]   B       .S1     $C$L12            ; |212| 
|| [!B0]   ZERO    .L1     A9
||         SET     .S2     B4,0x17,0x1d,B4
||         MV      .L2     B0,B2             ; |212| branch predicate copy
||         MV      .D2     B0,B1             ; guard predicate rewrite

   [!B0]   SET     .S1     A9,0x18,0x1d,A9
||         CMPGTSP .S2     B16,B4,B0         ; |215| 

   [ B1]   MVK     .L2     0x1,B0            ; |215| nullify predicate
   [!B0]   B       .S1     $C$L11            ; |215| 
   [ B2]   CALL    .S1     expsp_coshsp_i    ; |213| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L12}        ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

   [ B0]   CALL    .S1     expsp_coshsp_i    ; |219| 
|| [!B0]   MPYSP   .M1     A4,A4,A4          ; |178| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L11}        ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           ADDKPC  .S2     $C$RL15,B3,2      ; |219| 
$C$RL15:   ; CALL OCCURS {expsp_coshsp_i} {0}  ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           ZERO    .L1     A6
           SET     .S1     A6,0x1e,0x1e,A6
           MPYSP   .M1     A6,A4,A3          ; |219| 
           MV      .L1     A6,A4             ; |219| 
           ZERO    .L1     A31
           MVKL    .S2     0x7f7fffff,B4
           RCPSP   .S1     A3,A5             ; |131| 
           MPYSP   .M1     A3,A5,A7          ; |131| 
           MVKH    .S2     0x7f7fffff,B4
           CMPEQSP .S1     A3,A12,A0         ; |133| 
           ABSSP   .S2X    A3,B5             ; |137| 
           FSUBSP  .L1     A4,A7,A6          ; |131| 
           CMPGTSP .S2     B5,B4,B0          ; |137| 
           MVKL    .S2     0x42b2d4fc,B4
           MPYSP   .M1     A5,A6,A5          ; |131| 
           NOP             3
           MPYSP   .M1     A3,A5,A6          ; |131| 
           NOP             3
           FSUBSP  .L1     A4,A6,A4          ; |131| 
           NOP             2
           MPYSP   .M1     A5,A4,A4          ; |131| 
           NOP             3
   [ A0]   MV      .L1     A12,A4            ; |134| 
   [ B0]   MV      .L1     A12,A4            ; |138| 
           FADDSP  .L1     A4,A3,A3          ; |221| 
           SUB     .L1X    B11,1,A0          ; |171| 
           SUB     .L2     B11,1,B11         ; |171| 

           BNOP    .S1     $C$L13,4          ; |221| 
||         MPYSP   .M1     A9,A3,A3          ; |221| 

           MV      .L2X    A3,B5             ; |221| Define a twin register
||         ADDAW   .D1     A13,3,A3

           ; BRANCH OCCURS {$C$L13}          ; |221| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 22

           MVKL    .S2     0x3d2aaaab,B4
||         MVKL    .S1     0x37d00d01,A7

           MVKH    .S1     0x37d00d01,A7
||         MPYSP   .M1     A4,A4,A3          ; |178| 

           MVKL    .S2     0x3ab60b61,B5
           MPYSP   .M1     A9,A4,A8          ; |178| 
           MVKH    .S2     0x3d2aaaab,B4
           MPYSP   .M1     A3,A4,A6          ; |178| 
           MPYSP   .M1     A3,A3,A5          ; |178| 
           MVKH    .S2     0x3ab60b61,B5
           MPYSP   .M2X    B4,A3,B4          ; |178| 
           MPYSP   .M1X    B5,A6,A3          ; |178| 
           MPYSP   .M1     A7,A5,A4          ; |178| 
           SUB     .L1X    B11,1,A0          ; |171| 
           SUB     .L2     B11,1,B11         ; |171| 
           FADDSP  .L1X    B4,A8,A31         ; |178| 
           FADDSP  .L1     A3,A4,A4          ; |178| 
           ZERO    .L2     B31
           B       .S1     $C$L13            ; |178| 
           FADDSP  .L1     A4,A31,A3         ; |178| 
           SET     .S2     B31,0x17,0x1d,B4
           ZERO    .S1     A31
           NOP             1

           FADDSP  .L2X    B4,A3,B5          ; |178| 
||         ADDAW   .D1     A13,3,A3
||         MVKL    .S2     0x42b2d4fc,B4

           ; BRANCH OCCURS {$C$L13}          ; |178| 
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 4
           MV      .L1X    B16,A4            ; |213| 
           ADDKPC  .S2     $C$RL16,B3,2      ; |213| 
$C$RL16:   ; CALL OCCURS {expsp_coshsp_i} {0}  ; |213| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1

           SUB     .L2     B11,1,B11         ; |171| 
||         MV      .D2X    A4,B5             ; |213| 
||         ZERO    .L1     A31
||         MVKL    .S2     0x42b2d4fc,B4
||         ADDAW   .D1     A13,3,A3
||         SUB     .S1X    B11,1,A0          ; |171| 

;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D1T1   *A3,A4            ; |175| 
||         SET     .S1     A31,0x17,0x1e,A3
||         MVKH    .S2     0x42b2d4fc,B4

   [ A0]   BNOP    .S1     $C$L10,2          ; |171| 
||         CMPGTSP .S2     B16,B4,B0         ; |224| 

   [ B0]   MV      .L2X    A3,B5             ; |225| 

           ADD     .L1     A10,A4,A3         ; |175| 
||         ADD     .S1     4,A10,A10         ; |171| 

   [ A0]   CALL    .S1     coshf             ; |172| 
||         STW     .D1T2   B5,*A3            ; |175| 

           ; BRANCHCC OCCURS {$C$L10}        ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     coshsp_v          ; |177| 
           LDW     .D1T2   *+A13(16),B4      ; |177| 
           ADDKPC  .S2     $C$RL17,B3,2      ; |177| 

           MV      .L1X    B12,A4
||         MVK     .S1     0x8,A6            ; |177| 

$C$RL17:   ; CALL OCCURS {coshsp_v} {0}      ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D1T1   *A13,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A13(4),B4       ; |66| 
||         MVK     .L1     0x8,A6            ; |66| 
||         MVK     .S1     0x9,A8            ; |66| 

$C$RL18:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A13(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A3
||         MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A13,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A5,*+A3(4)        ; |66| 
||         MVK     .L1     0x8,A6            ; |67| 
||         MVK     .S1     0x9,A8            ; |67| 

$C$RL19:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3eb0c6f7,B7

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L2X    A13,B4            ; |177| 
||         STW     .D1T1   A4,*+A3(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B4,A4            ; |68| 
||         LDW     .D1T2   *+A13(12),B4      ; |68| 
||         MVK     .L1     0x8,A6            ; |68| 
||         MVK     .S1     0x9,A8            ; |68| 

$C$RL20:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L2X    A15,B12           ; |68| 
||         STW     .D1T1   A4,*+A3(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A13,A4           ; |69| 
||         LDW     .D2T2   *B12,B4           ; |69| 
||         MVK     .L1     0x8,A6            ; |69| 
||         MVK     .S1     0x9,A8            ; |69| 

$C$RL21:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MV      .L2X    A14,B11           ; |69| 
           LDW     .D2T2   *B11,B0           ; |72| 
           MVKL    .S1     fcn_pass,A3
           MVKH    .S1     fcn_pass,A3
           STW     .D1T1   A4,*+A3(16)       ; |69| 
           NOP             1

   [!B0]   MVKL    .S1     all_pass,A4
|| [!B0]   B       .S2     $C$L14            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [!B0]   MV      .L1     A12,A3

   [!B0]   CALL    .S2     print_test_results ; |181| 
|| [!B0]   MVKH    .S1     all_pass,A4
|| [ B0]   LDW     .D2T2   *B10,B0           ; |72| 

   [ B1]   ADD     .L2     4,B10,B4
           NOP             3
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
           CALL    .S1     print_test_results ; |181| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           NOP             2
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x3,A4            ; |181| 
||         ADDKPC  .S2     $C$RL22,B3,0      ; |181| 

$C$RL22:   ; CALL OCCURS {print_test_results} {0}  ; |181| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           MVKL    .S2     a_ext,B4

           MVKH    .S2     a_ext,B4
||         ZERO    .L1     A3

           SET     .S1     A3,0x17,0x17,A3

           MV      .L1X    B4,A10            ; |184| 
||         STW     .D2T1   A3,*B4            ; |184| 
||         MVK     .S2     0x7d,B4

           MV      .L2X    A12,B13

           CALL    .S1     coshf             ; |186| 
||         MV      .L1X    B4,A11            ; |184| 

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
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A10,A4           ; |186| 
           ADDKPC  .S2     $C$RL23,B3,3      ; |186| 
$C$RL23:   ; CALL OCCURS {coshf} {0}         ; |186| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D1T1   *A13,A3           ; |186| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |186| 
           STW     .D1T1   A4,*A3            ; |186| 

           CALLP   .S2     coshsp,B3
||         LDW     .D1T1   *A10,A4           ; |187| 

$C$RL24:   ; CALL OCCURS {coshsp} {0}        ; |187| 
           LDW     .D1T1   *+A13(4),A3       ; |187| 
           NOP             4
           ADD     .L1X    B13,A3,A3         ; |187| 
           STW     .D1T1   A4,*A3            ; |187| 

           CALLP   .S2     coshsp_c,B3
||         LDW     .D1T1   *A10,A4           ; |188| 

$C$RL25:   ; CALL OCCURS {coshsp_c} {0}      ; |188| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           LDW     .D1T1   *+A13(8),A3       ; |188| 
           ZERO    .L2     B31
           MVKH    .S2     0x41800000,B31
           NOP             2
           ADD     .L2X    B13,A3,B4         ; |188| 
           STW     .D2T1   A4,*B4            ; |188| 
           LDW     .D1T1   *A10,A4           ; |189| 
           ZERO    .L2     B4
           SET     .S2     B4,0x17,0x1d,B4
           NOP             2
           ABSSP   .S2X    A4,B16            ; |208| 
           CMPGTSP .S2     B16,B31,B0        ; |212| 

   [ B0]   B       .S1     $C$L17            ; |212| 
|| [!B0]   ZERO    .L1     A9
||         MV      .L2     B0,B2             ; |212| branch predicate copy
||         MV      .S2     B0,B1             ; guard predicate rewrite

   [!B0]   SET     .S1     A9,0x18,0x1d,A9
||         CMPGTSP .S2     B16,B4,B0         ; |215| 

   [ B1]   MVK     .L2     0x1,B0            ; |215| nullify predicate
   [!B0]   B       .S1     $C$L16            ; |215| 
   [ B2]   CALL    .S1     expsp_coshsp_i    ; |213| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L17}        ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

   [ B0]   CALL    .S1     expsp_coshsp_i    ; |219| 
|| [!B0]   MPYSP   .M1     A4,A4,A4          ; |178| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L16}        ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           ADDKPC  .S2     $C$RL26,B3,2      ; |219| 
$C$RL26:   ; CALL OCCURS {expsp_coshsp_i} {0}  ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           ZERO    .L1     A6
           SET     .S1     A6,0x1e,0x1e,A6
           MPYSP   .M1     A6,A4,A3          ; |219| 
           MVKL    .S2     0x7f7fffff,B4
           MV      .L1     A6,A4             ; |219| 
           MVKH    .S2     0x7f7fffff,B4
           RCPSP   .S1     A3,A5             ; |131| 
           MPYSP   .M1     A3,A5,A7          ; |131| 
           ABSSP   .S2X    A3,B5             ; |137| 
           CMPGTSP .S2     B5,B4,B0          ; |137| 
           MVK     .S2     12,B5
           FSUBSP  .L1     A4,A7,A6          ; |131| 
           ADD     .L2X    A13,B5,B5
           LDW     .D2T2   *B5,B6            ; |189| 
           MPYSP   .M1     A5,A6,A5          ; |131| 
           MVKL    .S2     0x42b2d4fc,B31
           MVKH    .S2     0x42b2d4fc,B31
           CMPEQSP .S1     A3,A12,A0         ; |133| 
           MPYSP   .M1     A3,A5,A6          ; |131| 
           ADD     .L2     B13,B6,B5         ; |189| 
           ADD     .L2     4,B13,B13         ; |185| 
           NOP             1
           FSUBSP  .L1     A4,A6,A4          ; |131| 
           NOP             2
           MPYSP   .M1     A5,A4,A4          ; |131| 
           MVKL    .S1     0xc000cccc,A5
           MVKH    .S1     0xc000cccc,A5
           NOP             1

   [ A0]   MV      .L1     A12,A4            ; |134| 
||         SUB     .S1     A11,1,A0          ; |185| 
||         SUB     .D1     A11,1,A11         ; |185| 

   [ B0]   MV      .L1     A12,A4            ; |138| 
||         CMPGTSP .S2     B16,B31,B0        ; |224| 

           FADDSP  .L1     A4,A3,A3          ; |221| 
           MVKL    .S1     0xcccccccd,A4
           MVKH    .S1     0xcccccccd,A4

           BNOP    .S1     $C$L18,4          ; |221| 
||         MPYSP   .M1     A9,A3,A3          ; |221| 

           MV      .L2X    A3,B4             ; |221| Define a twin register
||         ZERO    .L1     A3

           ; BRANCH OCCURS {$C$L18}          ; |221| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 22

           MVKL    .S2     0x3ab60b61,B4
||         MVKL    .S1     0x37d00d01,A7
||         ZERO    .L2     B31
||         SUB     .L1     A11,1,A0          ; |185| 
||         SUB     .D1     A11,1,A11         ; |185| 

           MPYSP   .M1     A4,A4,A3          ; |178| 
           MVKL    .S2     0x3d2aaaab,B5
           MPYSP   .M1     A9,A4,A31         ; |178| 
           MVKH    .S2     0x3d2aaaab,B5
           MPYSP   .M1     A3,A4,A6          ; |178| 

           MPYSP   .M1     A3,A3,A5          ; |178| 
||         MPYSP   .M2X    B5,A3,B5          ; |178| 

           MVKH    .S2     0x3ab60b61,B4
           MVKH    .S1     0x37d00d01,A7

           MPYSP   .M1X    B4,A6,A3          ; |178| 
||         SET     .S2     B31,0x17,0x1d,B4

           MPYSP   .M1     A7,A5,A5          ; |178| 
||         MVKL    .S2     0x42b2d4fc,B31

           FADDSP  .L1X    B5,A31,A4         ; |178| 
||         MVK     .S2     12,B5

           ADD     .L2X    A13,B5,B5
||         MVKH    .S2     0x42b2d4fc,B31

           LDW     .D2T2   *B5,B6            ; |189| 
||         CMPGTSP .S2     B16,B31,B0        ; |224| 

           FADDSP  .L1     A3,A5,A3          ; |178| 
||         MVKL    .S1     0xc000cccc,A5

           MVKH    .S1     0xc000cccc,A5
           B       .S1     $C$L18            ; |178| 

           FADDSP  .L1     A3,A4,A3          ; |178| 
||         MVKL    .S1     0xcccccccd,A4

           ADD     .L2     B13,B6,B5         ; |189| 
           MVKH    .S1     0xcccccccd,A4
           ADD     .L2     4,B13,B13         ; |185| 

           FADDSP  .L2X    B4,A3,B4          ; |178| 
||         ZERO    .L1     A3

           ; BRANCH OCCURS {$C$L18}          ; |178| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 4
           MV      .L1X    B16,A4            ; |213| 
           ADDKPC  .S2     $C$RL27,B3,2      ; |213| 
$C$RL27:   ; CALL OCCURS {expsp_coshsp_i} {0}  ; |213| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVK     .S2     12,B5
           ADD     .L2X    A13,B5,B5
           LDW     .D2T2   *B5,B6            ; |189| 
           MVKL    .S1     0xc000cccc,A5
           MVKL    .S2     0x42b2d4fc,B31

           MV      .L2X    A4,B4             ; |213| 
||         MVKL    .S1     0xcccccccd,A4

           MVKH    .S2     0x42b2d4fc,B31
||         MVKH    .S1     0xc000cccc,A5
||         SUB     .L1     A11,1,A0          ; |185| 

           ADD     .L2     B13,B6,B5         ; |189| 
||         ADD     .D2     4,B13,B13         ; |185| 
||         CMPGTSP .S2     B16,B31,B0        ; |224| 
||         MVKH    .S1     0xcccccccd,A4
||         ZERO    .L1     A3
||         SUB     .D1     A11,1,A11         ; |185| 

;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 21
           SET     .S1     A3,0x17,0x1e,A3
           NOP             1
   [ B0]   MV      .L2X    A3,B4             ; |225| 
           STW     .D2T2   B4,*B5            ; |189| 
           LDW     .D1T1   *A10,A3           ; |190| 
           NOP             4
           MPYSPDP .M1     A3,A5:A4,A5:A4    ; |190| 
           NOP             5
   [ A0]   B       .S1     $C$L15            ; |185| 
           DPSP    .L1     A5:A4,A3          ; |190| 
           NOP             3

   [ A0]   CALL    .S1     coshf             ; |186| 
||         STW     .D1T1   A3,*++A10         ; |190| 

           ; BRANCHCC OCCURS {$C$L15}        ; |185| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6

           CALL    .S1     coshsp_v          ; |192| 
||         MV      .L2X    A13,B13           ; |192| 

           LDW     .D2T2   *+B13(16),B4      ; |192| 
           MVKL    .S1     a_ext,A4
           MVKH    .S1     a_ext,A4
           ADDKPC  .S2     $C$RL28,B3,0      ; |192| 
           MVK     .S1     0x7d,A6           ; |192| 
$C$RL28:   ; CALL OCCURS {coshsp_v} {0}      ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 47
           LDW     .D2T2   *B13,B5           ; |66| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7
           MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MV      .L1X    B5,A4             ; |66| 
||         MVK     .S1     0x7d,A6           ; |66| 
||         MVK     .D1     0x9,A8            ; |66| 

$C$RL29:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .S1     0x7d,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL30:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A13,A4           ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .S1     0x7d,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL31:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0xa0b5ed8d,B6

           STW     .D2T1   A4,*+B4(12)       ; |68| 
||         LDW     .D1T2   *A15,B4           ; |69| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A13,A4           ; |69| 
||         MVK     .S1     0x7d,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL32:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D1T1   *A14,A0           ; |72| 
           MVKL    .S2     fcn_pass,B4
           MV      .L2     B10,B5            ; |72| 
           MVKH    .S2     fcn_pass,B4
           STW     .D2T1   A4,*+B4(16)       ; |69| 

   [ A0]   ADD     .L2     4,B5,B4
|| [!A0]   B       .S1     $C$L19            ; |72| 
|| [ A0]   LDW     .D2T2   *B5,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |196| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
   [!A0]   MV      .L2X    A12,B4
   [!A0]   MV      .L2X    A3,B5
           ; BRANCHCC OCCURS {$C$L19}        ; |72| 
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
           CALL    .S1     print_test_results ; |196| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             1
           MV      .L2X    A3,B5
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x4,A4            ; |196| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL33,B3,0      ; |196| 

$C$RL33:   ; CALL OCCURS {print_test_results} {0}  ; |196| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S2     cycle_counts+24,B5

           MVKH    .S2     cycle_counts+24,B5
||         MV      .L2X    A12,B4            ; |114| 
||         MV      .L1     A12,A10           ; |114| 
||         MV      .S1     A12,A11           ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A11:A10,*B5       ; |114| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           MVC     .S2     TSCL,B4           ; |117| 
||         STDW    .D1T2   B7:B6,*A3         ; |116| 

           MVC     .S2     TSCH,B8           ; |117| 

           CALL    .S2     gimme_random      ; |206| 
||         SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVKL    .S1     t_offset,A4

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A4
||         ZERO    .L1     A13

           ZERO    .L2     B4
||         STDW    .D1T2   B5:B4,*A4         ; |117| 
||         MVKH    .S1     0x43480000,A13

           MVKH    .S2     0xc2c80000,B4
||         MV      .L1     A13,A4            ; |206| 
||         STW     .D2T1   A3,*+SP(12)       ; |117| 
||         MV      .L2X    A12,B13           ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL34,B3,0      ; |206| 
$C$RL34:   ; CALL OCCURS {gimme_random} {0}  ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |206| 
           NOP             4
           ADD     .L2X    B13,A3,B4         ; |206| 

           STW     .D2T1   A4,*B4            ; |206| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A16            ; |122| Define a twin register
||         MVC     .S2     TSCH,B5           ; |122| 

           ZERO    .L2     B4
||         ABSSP   .S2X    A4,B16            ; |208| 

           MVKH    .S2     0x41800000,B4
||         MV      .L1X    B5,A17            ; |122| 

           CMPGTSP .S2     B16,B4,B0         ; |212| 
||         ZERO    .L2     B4

   [ B0]   B       .S1     $C$L22            ; |212| 
|| [!B0]   ZERO    .L1     A9
||         SET     .S2     B4,0x17,0x1d,B4
||         MV      .L2     B0,B2             ; |212| branch predicate copy
||         MV      .D2     B0,B1             ; guard predicate rewrite

   [!B0]   SET     .S1     A9,0x18,0x1d,A9
||         CMPGTSP .S2     B16,B4,B0         ; |215| 

   [ B1]   MVK     .L2     0x1,B0            ; |215| nullify predicate
|| [ B2]   MVKL    .S1     t_start,A3

   [!B0]   B       .S1     $C$L21            ; |215| 
   [ B2]   CALL    .S1     expsp_coshsp_i    ; |213| 
   [ B2]   MVKH    .S1     t_start,A3
           ; BRANCHCC OCCURS {$C$L22}        ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

   [ B0]   CALL    .S1     expsp_coshsp_i    ; |219| 
|| [!B0]   MPYSP   .M1     A4,A4,A4          ; |178| 

           NOP             2
           ; BRANCHCC OCCURS {$C$L21}        ; |215| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           MVKL    .S2     t_start,B4
           MVKH    .S2     t_start,B4

           STDW    .D2T1   A17:A16,*B4
||         ADDKPC  .S2     $C$RL35,B3,0      ; |219| 

$C$RL35:   ; CALL OCCURS {expsp_coshsp_i} {0}  ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 40
           ZERO    .L1     A5
           SET     .S1     A5,0x1e,0x1e,A5
           MPYSP   .M1     A5,A4,A3          ; |219| 
           MVKL    .S1     t_start,A31
           MVKL    .S2     0x7f7fffff,B4
           MVKH    .S2     0x7f7fffff,B4
           RCPSP   .S1     A3,A4             ; |131| 
           MPYSP   .M1     A3,A4,A6          ; |131| 
           MVKH    .S1     t_start,A31
           MVKL    .S2     0x42b2d4fc,B6
           LDDW    .D1T1   *A31,A17:A16      ; |221| 
           FSUBSP  .L1     A5,A6,A6          ; |131| 
           MVKH    .S2     0x42b2d4fc,B6
           ABSSP   .S2X    A3,B5             ; |137| 
           MPYSP   .M1     A4,A6,A4          ; |131| 
           CMPGTSP .S2     B5,B4,B0          ; |137| 
           MVKL    .S2     output+12,B5
           MVKH    .S2     output+12,B5
           MPYSP   .M1     A3,A4,A6          ; |131| 
           LDW     .D2T2   *B5,B5            ; |210| 
           CMPEQSP .S1     A3,A12,A0         ; |133| 
           NOP             1
           FSUBSP  .L1     A5,A6,A5          ; |131| 
           NOP             2
           MPYSP   .M1     A4,A5,A4          ; |131| 
           ADD     .L2     B13,B5,B5         ; |210| 
           NOP             2
   [ A0]   MV      .L1     A12,A4            ; |134| 
   [ B0]   MV      .L1     A12,A4            ; |138| 
           FADDSP  .L1     A4,A3,A3          ; |221| 
           CMPGTSP .S2     B16,B6,B0         ; |224| 
           NOP             1

           BNOP    .S1     $C$L23,4          ; |221| 
||         MPYSP   .M1     A9,A3,A3          ; |221| 

           MV      .L2X    A3,B4             ; |221| Define a twin register
||         ZERO    .L1     A3

           ; BRANCH OCCURS {$C$L23}          ; |221| 
;** --------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 22

           MVKL    .S2     0x3ab60b61,B4
||         MVKL    .S1     0x37d00d01,A7
||         ZERO    .L2     B31

           MPYSP   .M1     A4,A4,A3          ; |178| 
||         MVKL    .S2     0x3d2aaaab,B5
||         MVKH    .S1     0x37d00d01,A7

           MVKH    .S2     0x3ab60b61,B4
||         MPYSP   .M1     A9,A4,A31         ; |178| 
||         MVKL    .S1     t_start,A30

           MVKH    .S2     0x3d2aaaab,B5
||         MVKH    .S1     t_start,A30

           STDW    .D1T1   A17:A16,*A30
           MPYSP   .M1     A3,A4,A6          ; |178| 

           MPYSP   .M1     A3,A3,A5          ; |178| 
||         MPYSP   .M2X    B5,A3,B5          ; |178| 

           MVKL    .S2     0x42b2d4fc,B6
           MVKH    .S2     0x42b2d4fc,B6
           MPYSP   .M1X    B4,A6,A3          ; |178| 
           MPYSP   .M1     A7,A5,A5          ; |178| 
           FADDSP  .L1X    B5,A31,A4         ; |178| 
           MVKL    .S2     output+12,B5
           MVKH    .S2     output+12,B5
           FADDSP  .L1     A3,A5,A3          ; |178| 
           LDW     .D2T2   *B5,B5            ; |210| 
           B       .S1     $C$L23            ; |178| 
           FADDSP  .L1     A3,A4,A3          ; |178| 
           CMPGTSP .S2     B16,B6,B0         ; |224| 
           SET     .S2     B31,0x17,0x1d,B4
           ADD     .L2     B13,B5,B5         ; |210| 

           FADDSP  .L2X    B4,A3,B4          ; |178| 
||         ZERO    .L1     A3

           ; BRANCH OCCURS {$C$L23}          ; |178| 
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 4
           MV      .L1X    B16,A4            ; |213| 
           ADDKPC  .S2     $C$RL36,B3,1      ; |213| 
           STDW    .D1T1   A17:A16,*A3
$C$RL36:   ; CALL OCCURS {expsp_coshsp_i} {0}  ; |213| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S2     output+12,B5
           MVKH    .S2     output+12,B5
           LDW     .D2T2   *B5,B5            ; |210| 
           MVKL    .S2     0x42b2d4fc,B6
           MVKH    .S2     0x42b2d4fc,B6
           CMPGTSP .S2     B16,B6,B0         ; |224| 
           ZERO    .L1     A3

           MV      .L2X    A4,B4             ; |213| 
||         ADD     .S2     B13,B5,B5         ; |210| 

;** --------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 20
           SET     .S1     A3,0x17,0x1e,A3
           NOP             1
   [ B0]   MV      .L2X    A3,B4             ; |225| 

           STW     .D2T2   B4,*B5            ; |210| 
||         MVC     .S2     TSCL,B6           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A15
||         LDW     .D2T1   *+SP(12),A31      ; |128| 
||         MVKL    .S2     cycle_counts+24,B5
||         MV      .L2     B4,B7             ; |128| 

           MVKH    .S1     t_offset,A15
||         MVKH    .S2     cycle_counts+24,B5
||         ADD     .L2     4,B13,B13         ; |204| 

           LDDW    .D1T1   *A15,A7:A6        ; |130| 
||         LDDW    .D2T2   *B5,B5:B4         ; |130| 
||         MVKL    .S1     t_stop,A3

           MVKL    .S1     cycle_counts+24,A14
           MVKH    .S1     t_stop,A3

           SUB     .L1     A31,1,A0          ; |204| 
||         MVKH    .S1     cycle_counts+24,A14
||         STDW    .D1T2   B7:B6,*A3         ; |128| 

           STW     .D2T1   A0,*+SP(12)       ; |130| 
           ADDU    .L1     A6,A16,A5:A4      ; |130| 
           ADD     .L1     A5,A7,A5          ; |130| 

           SUBU    .L2X    B6,A4,B9:B8       ; |130| 
||         ADD     .L1     A5,A17,A4         ; |130| 
|| [ A0]   B       .S1     $C$L20            ; |204| 

   [ A0]   CALL    .S1     gimme_random      ; |206| 
||         EXT     .S2     B9,24,24,B16      ; |130| 
||         ADDU    .L2     B4,B8,B9:B8       ; |130| 

           SUB     .L2X    B7,A4,B4          ; |130| 
|| [ A0]   MV      .L1     A13,A4            ; |206| 

           ADD     .L2     B9,B5,B4          ; |130| 
||         ADD     .S2     B4,B16,B5         ; |130| 

           ADD     .L2     B4,B5,B9          ; |130| 
|| [ A0]   ZERO    .S2     B4

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T2   B9:B8,*A14        ; |130| 
|| [ A0]   MVKH    .S2     0xc2c80000,B4

           ; BRANCHCC OCCURS {$C$L20}        ; |204| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL37,B3,3      ; |135| 
$C$RL37:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           NOP             1
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL38:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MV      .L2X    A14,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           SUBAW   .D2     B4,6,B5
||         MV      .L2X    A10,B31           ; |114| 

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T1   A11:A10,*B5       ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 

           STDW    .D1T2   B5:B4,*A15        ; |117| 
||         MVK     .S1     0x80,A14

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L24:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |219| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |219| 
||         CALL    .S1     coshf             ; |219| 

           LDW     .D1T1   *A3,A4            ; |219| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |219| 
$C$RL39:   ; CALL OCCURS {coshf} {0}         ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |219| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |219| 

           STW     .D1T1   A4,*A3            ; |219| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S2     t_start,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         MVKL    .S1     cycle_counts,A3
||         SUB     .L1     A14,1,A0          ; |217| 
||         MV      .L2     B6,B17            ; |128| 

           MVKH    .S2     t_start,B4
||         MVKH    .S1     cycle_counts,A3
||         SUB     .L1     A14,1,A14         ; |217| 
||         ADD     .D1     4,A12,A12         ; |217| 

           LDDW    .D2T2   *B4,B9:B8         ; |130| 
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S2     cycle_counts,B6
||         MVKL    .S1     t_stop,A31

           MVKH    .S1     t_stop,A31
           MVKH    .S2     cycle_counts,B6
           STDW    .D1T2   B17:B16,*A31      ; |128| 
   [!A0]   MV      .L1X    B6,A14
           ADDU    .L2X    A4,B8,B5:B4       ; |130| 

           ADD     .S2X    B5,A5,B7          ; |130| 
|| [ A0]   B       .S1     $C$L24            ; |217| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B7,B9,B7          ; |130| 
||         EXT     .S2     B5,24,24,B8       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B7,B7         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B7,B8,B7          ; |130| 
           ADD     .L2     B5,B7,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B6         ; |130| 

           ; BRANCHCC OCCURS {$C$L24}        ; |217| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL40,B3,3      ; |135| 
$C$RL40:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL41:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A11:A10,*+A14(16) ; |114| 
||         MV      .L2X    A11,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A14        ; |135| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B8           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B8,B5,B9:B8       ; |117| 

           EXT     .S2     B9,24,24,B5       ; |117| 
||         SUB     .L2     B7,B4,B4          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B4,B5,B9          ; |117| 
||         STW     .D2T1   A3,*+SP(12)       ; |117| 
||         MV      .S2X    A15,B6            ; |117| 

           STDW    .D2T2   B9:B8,*B6         ; |117| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L25:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |228| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |228| 
||         CALL    .S1     coshsp_c          ; |228| 

           LDW     .D1T1   *A3,A4            ; |228| 
           ADDKPC  .S2     $C$RL42,B3,3      ; |228| 
$C$RL42:   ; CALL OCCURS {coshsp_c} {0}      ; |228| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+8,B4
           MVKH    .S2     output+8,B4
           LDW     .D2T2   *B4,B4            ; |228| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |228| 

           STW     .D1T1   A4,*A3            ; |228| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S2     t_start,B5
||         LDW     .D2T1   *+SP(12),A30      ; |128| 
||         ADDAD   .D1     A14,2,A3
||         MV      .L2     B4,B17            ; |128| 
||         MVKL    .S1     t_stop,A31
||         ADD     .L1     4,A12,A12         ; |226| 

           MVKH    .S2     t_start,B5
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         MVKH    .S1     t_stop,A31

           LDDW    .D2T2   *B5,B9:B8         ; |130| 
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVK     .S2     16,B13

           STDW    .D1T2   B17:B16,*A31      ; |128| 
           ADD     .L2X    A14,B13,B13
           SUB     .L1     A30,1,A0          ; |226| 
           STW     .D2T1   A0,*+SP(12)       ; |130| 
           ADDU    .L2X    A4,B8,B7:B6       ; |130| 

   [ A0]   B       .S1     $C$L25            ; |226| 
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
||         STDW    .D2T2   B5:B4,*B13        ; |130| 

           ; BRANCHCC OCCURS {$C$L25}        ; |226| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A14(16),A5:A4   ; |135| 
           ADDKPC  .S2     $C$RL43,B3,3      ; |135| 
$C$RL43:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A11,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL44:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A11:A10,*+A14(8)  ; |114| 
||         MV      .L2X    A10,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D2T1   A5:A4,*B13        ; |135| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVK     .S1     0x80,A3

           STDW    .D1T2   B5:B4,*A15        ; |117| 
||         STW     .D2T1   A3,*+SP(12)       ; |117| 

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
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |237| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |237| 
||         CALL    .S1     coshsp            ; |237| 

           LDW     .D1T1   *A3,A4            ; |237| 
           ADDKPC  .S2     $C$RL45,B3,3      ; |237| 
$C$RL45:   ; CALL OCCURS {coshsp} {0}        ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+4,B4
           MVKH    .S2     output+4,B4
           LDW     .D2T2   *B4,B4            ; |237| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |237| 

           STW     .D1T1   A4,*A3            ; |237| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B5           ; |128| 

           MVKL    .S2     t_start,B4
||         LDW     .D2T1   *+SP(12),A30      ; |128| 
||         ADDAD   .D1     A14,1,A3
||         MV      .L2     B5,B17            ; |128| 
||         MVKL    .S1     t_stop,A31
||         ADD     .L1     4,A12,A12         ; |235| 

           MVKH    .S2     t_start,B4
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         MVKH    .S1     t_stop,A31

           MV      .L2X    A3,B13            ; |128| 
||         LDDW    .D2T2   *B4,B7:B6         ; |130| 

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           STDW    .D1T2   B17:B16,*A31      ; |128| 
           SUB     .L1     A30,1,A0          ; |235| 
           STW     .D2T1   A0,*+SP(12)       ; |130| 
           ADDU    .L2X    A4,B6,B9:B8       ; |130| 

           ADD     .S2X    B9,A5,B6          ; |130| 
|| [ A0]   B       .S1     $C$L26            ; |235| 
||         SUBU    .L2     B16,B8,B5:B4      ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B8       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B7         ; |130| 
||         MV      .S2     B4,B6             ; |130| 
||         ADD     .D2X    B5,A7,B4          ; |130| 

           ADD     .L2     B7,B8,B5          ; |130| 
           ADD     .L2     B4,B5,B7          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B7:B6,*B13        ; |130| 

           ; BRANCHCC OCCURS {$C$L26}        ; |235| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A14(8),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL46,B3,3      ; |135| 
$C$RL46:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 112
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A11,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL47:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 

           MV      .L2X    A10,B4            ; |114| 
||         MV      .L1X    B13,A12           ; |135| 
||         STDW    .D1T1   A11:A10,*+A14(32) ; |114| 

           STDW    .D1T1   A5:A4,*A12        ; |135| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3
           NOP             1
           MV      .L2X    A3,B13            ; |116| 

           STDW    .D2T2   B5:B4,*B13        ; |116| 
||         MVC     .S2     TSCL,B6           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3

           MV      .L1     A3,A10            ; |117| 
||         MVKL    .S1     input,A3
||         SUBU    .L2     B6,B4,B7:B6       ; |117| 

           MVKH    .S1     input,A3
||         SUB     .L2     B8,B5,B4          ; |117| 
||         EXT     .S2     B7,24,24,B5       ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 

           MV      .L2X    A3,B9             ; |244| 
||         STDW    .D1T2   B7:B6,*A15        ; |117| 

           CALLP   .S2     coshsp_v,B3
||         LDW     .D2T1   *B9,A4            ; |244| 
||         LDW     .D1T2   *+A10(16),B4      ; |244| 
||         MVK     .S1     0x80,A6           ; |244| 

$C$RL48:   ; CALL OCCURS {coshsp_v} {0}      ; |244| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B13,B7:B6        ; |130| 

           MVK     .S2     24,B13
           ADD     .L2X    A12,B13,B13

           MV      .L2     B4,B9             ; |128| 
||         LDDW    .D2T2   *B13,B5:B4        ; |130| 

           MVKL    .S1     t_stop,A3
           ADDU    .L1X    A4,B6,A7:A6       ; |130| 

           ADD     .S1     A7,A5,A6          ; |130| 
||         SUBU    .L1X    B8,A6,A5:A4       ; |130| 

           MVKH    .S1     t_stop,A3

           ADDU    .L1X    B4,A4,A7:A6       ; |130| 
||         ADD     .L2X    A6,B7,B4          ; |130| 

           MV      .L2X    A3,B6             ; |128| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           SUB     .L2     B9,B4,B7          ; |130| 
||         ADD     .S2X    A7,B5,B5          ; |130| 

           ADD     .L2X    B7,A3,B7          ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 
||         MV      .S2X    A6,B4             ; |130| 

           STDW    .D2T2   B9:B8,*B6         ; |128| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 

$C$RL49:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1     A11,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL50:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STDW    .D2T1   A5:A4,*B13        ; |130| 
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVK     .L1     0x9,A8            ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 

$C$RL51:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xa0b5ed8d,B6

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A10(8),B4       ; |67| 
||         MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MV      .S1     A3,A11            ; |66| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A5,*+A11(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x9,A8            ; |67| 

$C$RL52:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6

           STW     .D1T1   A4,*+A11(8)       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1     A10,A3            ; |68| 
||         LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x9,A8            ; |68| 

$C$RL53:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1     A10,A3            ; |68| 
||         STW     .D1T1   A4,*+A11(12)      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         LDW     .D2T2   *B12,B4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x9,A8            ; |69| 

$C$RL54:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *B11,B0           ; |72| 
           STW     .D1T1   A4,*+A11(16)      ; |69| 
           NOP             3

   [!B0]   BNOP    .S1     $C$L27,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B10,B0           ; |72| 

   [ B1]   ADD     .L2     4,B10,B4
           ; BRANCHCC OCCURS {$C$L27}        ; |72| 
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
   [ A0]   B       .S1     $C$L28            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |250| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L28}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L27:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |250| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L28:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |250| 
||         ADDKPC  .S2     $C$RL55,B3,0      ; |250| 

$C$RL55:   ; CALL OCCURS {print_test_results} {0}  ; |250| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |251| 

$C$RL56:   ; CALL OCCURS {printf} {0}        ; |251| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |251| 

$C$RL57:   ; CALL OCCURS {printf} {0}        ; |251| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |258| 

$C$RL58:   ; CALL OCCURS {print_profile_results} {0}  ; |258| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |261| 

$C$RL59:   ; CALL OCCURS {print_memory_results} {0}  ; |261| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(24),B3      ; |262| 
           LDDW    .D2T1   *++SP,A13:A12     ; |262| 
           LDDW    .D2T1   *++SP,A15:A14     ; |262| 
           LDDW    .D2T2   *++SP,B11:B10     ; |262| 
           LDDW    .D2T2   *++SP,B13:B12     ; |262| 

           LDW     .D2T1   *++SP(8),A10      ; |262| 
||         RET     .S2     B3                ; |262| 

           LDW     .D2T1   *++SP(8),A11      ; |262| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |262| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"coshSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	coshf
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	coshsp_c
	.global	coshsp
	.global	coshsp_v
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
	.global	kTable
	.global	jTable
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
