/**
 *  \file     lnk_tda2xx_a15_test_auto.cmd
 *
 *  \brief    This file contains the System Memory Map used by test automation
 *            Secondary Bootloader (SBL) for SD boot mode for tda2xx SoC.
 *
 *  \copyright Copyright (C) 2010 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

ENTRY(SBL_Start)
MEMORY
{
    OCMCRAM1 (RWIX): org = 0x40300000,  len = 0x0007FC00  /* OCMC RAM1        */
    /* Below area is reserved for vector table. Do not allocate anything here*/
    OCMC_VEC_TBL  : org = 0x4037FC00,  len = 0x400
}

SECTIONS
{
    . = 0x40300000;

    .public : {*(.public.*)}             > OCMCRAM1
    .init   : { *(.init.*) }             > OCMCRAM1
    .text   : { *(.text) ;*(.text.*); }  > OCMCRAM1
    .data   : { *(.data.*) }             > OCMCRAM1
    .const  : { *(.const.*) }            > OCMCRAM1
    .rodata : {*(.rodata.*) }            > OCMCRAM1
    .cinit  : { *(.cinit.*) }            > OCMCRAM1
    .cio    : { *(CIO) }

    .bss :
    {
        _bss_start = .;
        *(.bss.*) *(COMMON);
        _bss_end = .;
    } > OCMCRAM1

    .stack :
    {
        . = ALIGN(8);
        stack_start = .;
        *(.stack.*) ;
        . = . + 0x2000;
        stack_end = .;
    } > OCMCRAM1

    _stack     = stack_end;
    _text_size = SIZEOF(.text);
    _data_size = SIZEOF(.data);
    .a15_vector_table : {
     __vector_base__ = .;
        *(.a15_vector_table.*) ;
     __vector_base_end__ = .;
    } > OCMC_VEC_TBL
}