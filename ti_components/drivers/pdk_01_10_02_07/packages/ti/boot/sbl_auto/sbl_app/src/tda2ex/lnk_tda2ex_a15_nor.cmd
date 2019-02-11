/**
 *  \file     lnk_tda2xx_a15_nor.cmd
 *
 *  \brief    This file contains the System Memory Map used by Secondary
 *            Bootloader (SBL) for NOR boot mode for tda2ex SoC.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

ENTRY(nor_lowlevel_init)
MEMORY
{
    OCMCRAM1_0 (RWIX): org = 0x40300000  , len = 0x0007F000  /* OCMC RAM      */
    /* Following is reserved for Vector Table */
    OCMCRAM1_1 (RWIX): org = 0x4037F000  , len = 0x00001000
    NOR_MEM1 (RWIX): org = 0x08000000 , len = 0x04000000
}

SECTIONS
{
    . = 0x08000000;

    .public : {*(.public.*)} > NOR_MEM1
    .init   : { *(.init.*) } > NOR_MEM1
    .text   : { *(.text) ;*(.text.*); }  > NOR_MEM1
    .const  : { *(.const.*) } > NOR_MEM1
    .rodata : {*(.rodata.*) } > NOR_MEM1

    .data :
    {
        data_start = .;
        *(.data.*);
        data_end = .;
    } > OCMCRAM1_0 AT>NOR_MEM1

    .bss :
    {
        _bss_start = .;
        *(.bss.*) *(COMMON);
        _bss_end = .;
    } > OCMCRAM1_0 AT>NOR_MEM1

    .stack :
    {
        . = ALIGN(8);
        stack_start = .;
        *(.stack.*) ;
        . = . + 0x1000;
        stack_end = .;
    } > OCMCRAM1_0

    data_start_ldr = LOADADDR(.data);

    _stack = stack_end;
    _text_size = SIZEOF(.text);
    _data_size = SIZEOF(.data);
    .a15_vector_table : {
     __vector_base__ = .;
        *(.a15_vector_table.*) ;
     __vector_base_end__ = .;
    } > OCMCRAM1_1
}