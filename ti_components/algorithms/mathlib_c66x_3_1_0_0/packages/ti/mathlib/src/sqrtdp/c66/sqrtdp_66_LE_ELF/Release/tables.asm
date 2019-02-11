;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Mon Nov 04 23:03:46 2013                                *
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

	.global	logtable
	.sect	".fardata:logtable", RW
	.clink
	.align	8
	.elfsym	logtable,SYM_SIZE(64)
logtable:
	.word	000000000h,000000000h		; logtable[0] @ 0
	.word	06decf45eh,0bfbe2707h		; logtable[1] @ 64
	.word	0c792ca49h,0bfcc8ff7h		; logtable[2] @ 128
	.word	0c2174681h,0bfd4618bh		; logtable[3] @ 192
	.word	0ecbd59c8h,0bfd9f323h		; logtable[4] @ 256
	.word	05f9891beh,0bfdf128fh		; logtable[5] @ 320
	.word	05e6b627dh,0bfe1e85fh		; logtable[6] @ 384
	.word	0e8435f76h,0bfe41d8fh		; logtable[7] @ 448

	.global	kTable
	.sect	".fardata:kTable", RW
	.clink
	.align	8
	.elfsym	kTable,SYM_SIZE(32)
kTable:
	.word	000000000h,03ff00000h		; kTable[0] @ 0
	.word	00a318737h,03ff306feh		; kTable[1] @ 64
	.word	06665983eh,03ff6a09eh		; kTable[2] @ 128
	.word	0997cad14h,03ffae89fh		; kTable[3] @ 192

	.global	jTable
	.sect	".fardata:jTable", RW
	.clink
	.align	8
	.elfsym	jTable,SYM_SIZE(32)
jTable:
	.word	000000000h,03ff00000h		; jTable[0] @ 0
	.word	06cdc29ebh,03ff0b558h		; jTable[1] @ 64
	.word	03c945254h,03ff172b8h		; jTable[2] @ 128
	.word	06e861a8ch,03ff2387ah		; jTable[3] @ 192

	.global	V
	.sect	".fardata:V", RW
	.clink
	.align	8
	.elfsym	V,SYM_SIZE(32)
V:
	.word	000000000h,000000000h		; V[0] @ 0
	.word	0382d7366h,03fe0c152h		; V[1] @ 64
	.word	054442d18h,03ff921fbh		; V[2] @ 128
	.word	0382d7366h,03ff0c152h		; V[3] @ 192

;	C:\MATHLIB_Tools\CCSV5_4_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\182042 C:\\DOCUME~1\\a0868396\\LOCALS~1\\Temp\\182044 

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
