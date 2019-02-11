;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:57:15 2013                                *
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
	.field  	_logtable+0,32
	.word	000000000h,000000000h		; _logtable[0] @ 0
	.word	0bfbe2707h,06decf45eh		; _logtable[1] @ 64
	.word	0bfcc8ff7h,0c792ca49h		; _logtable[2] @ 128
	.word	0bfd4618bh,0c2174681h		; _logtable[3] @ 192
	.word	0bfd9f323h,0ecbd59c8h		; _logtable[4] @ 256
	.word	0bfdf128fh,05f9891beh		; _logtable[5] @ 320
	.word	0bfe1e85fh,05e6b627dh		; _logtable[6] @ 384
	.word	0bfe41d8fh,0e8435f76h		; _logtable[7] @ 448
$C$IR_1:	.set	64

	.sect	".cinit"
	.align	8
	.field  	$C$IR_2,32
	.field  	_kTable+0,32
	.word	03ff00000h,000000000h		; _kTable[0] @ 0
	.word	03ff306feh,00a318737h		; _kTable[1] @ 64
	.word	03ff6a09eh,06665983eh		; _kTable[2] @ 128
	.word	03ffae89fh,0997cad14h		; _kTable[3] @ 192
$C$IR_2:	.set	32

	.sect	".cinit"
	.align	8
	.field  	$C$IR_3,32
	.field  	_jTable+0,32
	.word	03ff00000h,000000000h		; _jTable[0] @ 0
	.word	03ff0b558h,06cdc29ebh		; _jTable[1] @ 64
	.word	03ff172b8h,03c945254h		; _jTable[2] @ 128
	.word	03ff2387ah,06e861a8ch		; _jTable[3] @ 192
$C$IR_3:	.set	32

	.sect	".cinit"
	.align	8
	.field  	$C$IR_4,32
	.field  	_V+0,32
	.word	000000000h,000000000h		; _V[0] @ 0
	.word	03fe0c152h,0382d7366h		; _V[1] @ 64
	.word	03ff921fbh,054442d18h		; _V[2] @ 128
	.word	03ff0c152h,0382d7366h		; _V[3] @ 192
$C$IR_4:	.set	32

	.global	_logtable
_logtable:	.usect	".far",64,8
	.global	_kTable
_kTable:	.usect	".far",32,8
	.global	_jTable
_jTable:	.usect	".far",32,8
	.global	_V
_V:	.usect	".far",32,8
;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\173722 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\173724 

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "TI", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
