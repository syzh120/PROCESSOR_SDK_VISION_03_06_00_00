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
    OCMCRAM1_0 (RWIX): org = 0x40300000  , len = 0x0007F000  /* OCMC RAM      */
    /* Following is reserved for Vector Table */
    OCMCRAM1_1 (RWIX): org = 0x4037F000  , len = 0x00001000
}

SECTIONS
{
    . = 0x40300000;

    .public : {*(.public.*)}             > OCMCRAM1_0
    .init   : { *(.init.*) }             > OCMCRAM1_0
    .text   : { *(.text) ;*(.text.*); }  > OCMCRAM1_0
    .data   : { *(.data.*) }             > OCMCRAM1_0
    .const  : { *(.const.*) }            > OCMCRAM1_0
    .rodata : {*(.rodata.*) }            > OCMCRAM1_0
    .cinit  : { *(.cinit.*) }            > OCMCRAM1_0
    .cio    : { *(CIO) }

    .bss :
    {
        _bss_start = .;
        *(.bss.*) *(COMMON);
        _bss_end = .;
    } > OCMCRAM1_0

    .stack :
    {
        . = ALIGN(8);
        stack_start = .;
        *(.stack.*) ;
        . = . + 0x2000;
        stack_end = .;
    } > OCMCRAM1_0

    _stack     = stack_end;
    _text_size = SIZEOF(.text);
    _data_size = SIZEOF(.data);
    .a15_vector_table : {
     __vector_base__ = .;
        *(.a15_vector_table.*) ;
     __vector_base_end__ = .;
    } > OCMCRAM1_1
}