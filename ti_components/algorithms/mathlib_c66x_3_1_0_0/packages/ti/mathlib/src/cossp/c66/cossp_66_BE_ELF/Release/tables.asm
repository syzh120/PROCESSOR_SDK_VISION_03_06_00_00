;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 22:30:06 2013                                *
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

	.global	logtable
	.sect	".fardata:logtable", RW
	.clink
	.align	8
	.elfsym	logtable,SYM_SIZE(64)
logtable:
	.word	000000000h,000000000h		; logtable[0] @ 0
	.word	0bfbe2707h,06decf45eh		; logtable[1] @ 64
	.word	0bfcc8ff7h,0c792ca49h		; logtable[2] @ 128
	.word	0bfd4618bh,0c2174681h		; logtable[3] @ 192
	.word	0bfd9f323h,0ecbd59c8h		; logtable[4] @ 256
	.word	0bfdf128fh,05f9891beh		; logtable[5] @ 320
	.word	0bfe1e85fh,05e6b627dh		; logtable[6] @ 384
	.word	0bfe41d8fh,0e8435f76h		; logtable[7] @ 448

	.global	kTable
	.sect	".fardata:kTable", RW
	.clink
	.align	8
	.elfsym	kTable,SYM_SIZE(32)
kTable:
	.word	03ff00000h,000000000h		; kTable[0] @ 0
	.word	03ff306feh,00a318737h		; kTable[1] @ 64
	.word	03ff6a09eh,06665983eh		; kTable[2] @ 128
	.word	03ffae89fh,0997cad14h		; kTable[3] @ 192

	.global	jTable
	.sect	".fardata:jTable", RW
	.clink
	.align	8
	.elfsym	jTable,SYM_SIZE(32)
jTable:
	.word	03ff00000h,000000000h		; jTable[0] @ 0
	.word	03ff0b558h,06cdc29ebh		; jTable[1] @ 64
	.word	03ff172b8h,03c945254h		; jTable[2] @ 128
	.word	03ff2387ah,06e861a8ch		; jTable[3] @ 192

	.global	V
	.sect	".fardata:V", RW
	.clink
	.align	8
	.elfsym	V,SYM_SIZE(32)
V:
	.word	000000000h,000000000h		; V[0] @ 0
	.word	03fe0c152h,0382d7366h		; V[1] @ 64
	.word	03ff921fbh,054442d18h		; V[2] @ 128
	.word	03ff0c152h,0382d7366h		; V[3] @ 192

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\148482 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\148484 

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
