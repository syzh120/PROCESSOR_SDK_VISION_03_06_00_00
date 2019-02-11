

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
	OCMCRAM1      : org = 0x40300000,  len = 0x0007FC00  /* OCMC RAM1        */
    /* Below area is reserved for vector table. Do not allocate anything here*/
    OCMC_VEC_TBL  : org = 0x4037FC00,  len = 0x400
	OCMCRAM2      : org = 0x40400000,  len = 0x00100000  /* OCMC RAM2        */
	OCMCRAM3      : org = 0x40500000,  len = 0x00100000  /* OCMC RAM3        */
	SBL_REG_LOG_BFR_SEG  : org = 0x40590000 , len = 0x100  /* SBL Regression test log buffer*/
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
	BOARD_IO_DELAY_DATA : {*(BOARD_IO_DELAY_DATA)}  AT> OCMCRAM1
	BOARD_IO_DELAY_CODE : {*(BOARD_IO_DELAY_CODE)}  AT> OCMCRAM1
        .text        : {*(.text)}         > OCMCRAM3
	.data        : {*(.data)}	        > OCMCRAM3
	.sbl_reg_log_bfr ALIGN(0x4): {} > SBL_REG_LOG_BFR_SEG
	.bss ALIGN(0x4):
	{
		_bss_start = . ;
		*(.bss.*) *(COMMON);
		_bss_end = . ;
	}	> OCMCRAM3

	. = ALIGN(4);
	_end = .;
	PROVIDE (end = .);

	.stack ALIGN(0x4):
	{
		stack_start = .;
		*(.stack.*) ;
		. = . + 0x3000;
		stack_end = .;
	}	> OCMCRAM3

	. = ALIGN(4);
	__exidx_start = .;
	PROVIDE(__exidx_start = __exidx_start);

	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*);
	} > OCMCRAM3

	. = ALIGN(4);
	__exidx_end = .;
	PROVIDE(__exidx_end = __exidx_end);

	.const     ALIGN(0x4): {*(.const)}	    > OCMCRAM3
	.my_sect_ddr ALIGN(0x4): {*(.my_sect_ddr)}  > OCMCRAM3

	_stack = stack_end;
    .a15_vector_table : {
     __vector_base__ = .;
        *(.a15_vector_table.*) ;
     __vector_base_end__ = .;
    } > OCMC_VEC_TBL
}