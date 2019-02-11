

/****************************************************************************/
/* LNK32.CMD - v4.5.0 COMMAND FILE FOR LINKING TMS470 32BIS C/C++ PROGRAMS  */
/*                                                                          */
/*   Usage:  armlnk <obj files...>    -o <out file> -m <map file> lnk32.cmd */
/*           armcl <src files...> -z -o <out file> -m <map file> lnk32.cmd  */
/*                                                                          */
/*   Description: This file is a sample command file that can be used       */
/*                for linking programs built with the TMS470 C/C++          */
/*                Compiler.   Use it as a guideline; you may want to change */
/*                the allocation scheme according to the size of your       */
/*                program and the memory layout of your target system.      */
/*                                                                          */
/*   Notes: (1)   You must specify the directory in which run-time support  */
/*                library is located.  Either add a "-i<directory>" line to */
/*                this file, or use the system environment variable C_DIR   */
/*                to specify a search path for libraries.                   */
/*                                                                          */
/*          (2)   If the run-time support library you are using is not      */
/*                named below, be sure to use the correct name here.        */
/*                                                                          */
/****************************************************************************/
/*-stack  0x0800                              SOFTWARE STACK SIZE           */
/*-heap   0x2000                              HEAP AREA SIZE                */
/*-e Entry*/
/* Since we used 'Entry' as the entry-point symbol the compiler issues a    */
/* warning (#10063-D: entry-point symbol other than "_c_int00" specified:   */
/* "Entry"). The CCS Version (5.1.0.08000) stops building from command      */
/* line when there is a warning. So this warning is suppressed with the     */
/* below flag. */

/*--diag_suppress=10063*/


ENTRY(Entry)
MEMORY
{
    IRAM_MEM      : org = 0x402F0000,  len = 0x00010000
    /* SBL Start : SBL will use 256 Bytes of space from address 0x40300000 for
     * while creating tiimage
     */
    OCMCRAM1_1    : org = 0x40300200,  len = (0x00030000 - 0x200)/*OCMC RAM1_1*/
    OCMCRAM1_2    : org = 0x40330000,  len = 0x00010000          /*OCMC RAM1_2*/
    OCMCRAM1_3    : org = 0x40340000,  len = 0x0003FC00          /*OCMC RAM1_3*/
    /* Below area is reserved for vector table. Do not allocate anything here*/
    OCMC_VEC_TBL  : org = 0x4037FC00,  len = 0x400
    /*SBL will use 1 KB of space from address 0x80000000 for EVE */
    DDR3_A15      : org = 0x80000400,  len = (0x0B000000 - 0x400)
    DDR3_DSP      : org = 0x8B000000,  len = 0x02000000
    DDR3_M3VPSS   : org = 0x8D000000,  len = 0x01000000
    DDR3_M3VIDEO  : org = 0x8E000000,  len = 0x01000000
    DDR3_SR0      : org = 0x8F000000,  len = 0x01000000
}




/* SPECIFY THE SYSTEM MEMORY MAP */
SECTIONS
{

	.text        : {*(.text)}         > OCMCRAM1_3
	.data        : {*(.data)}	      > OCMCRAM1_3
	.bss ALIGN(0x4):
	{
		_bss_start = . ;
		*(.bss.*) *(COMMON);
		_bss_end = . ;
	}	> OCMCRAM1_3

	. = ALIGN(4);
	_end = .;
	PROVIDE (end = .);

	.stack ALIGN(0x4):
	{
		stack_start = .;
		*(.stack.*) ;
		. = . + 0x1000;
		stack_end = .;
	}	> OCMCRAM1_3

	. = ALIGN(4);
	__exidx_start = .;
	PROVIDE(__exidx_start = __exidx_start);

	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*);
	} > OCMCRAM1_3

	. = ALIGN(4);
	__exidx_end = .;
	PROVIDE(__exidx_end = __exidx_end);

	.const     ALIGN(0x4): {*(.const)}	    	> OCMCRAM1_3
	.my_sect_ddr ALIGN(0x4): {*(.my_sect_ddr)}  > OCMCRAM1_3

	_stack = stack_end;
    .a15_vector_table : {
     __vector_base__ = .;
        *(.a15_vector_table.*) ;
     __vector_base_end__ = .;
    } > OCMC_VEC_TBL
}