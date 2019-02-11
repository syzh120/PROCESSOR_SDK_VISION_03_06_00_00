/**
 *  \file     lnk_mpu_cpu0.cmd
 *
 *  \brief    This file contains the System Memory Map used by MPU CPU0 binary
 *            for multicore mailbox app image.
 */

ENTRY(Entry)

/* Specify the System Memory Map */
MEMORY
{
    /* Code Section - 20MB */
    /* Data Section - 10MB */
    /* Stack - 5MB */
    /* Heap - 5MB */
    OCMCRAM1      : org = 0x40300000,  len = 0x0007FC00  /* OCMC RAM1        */
    /* Below area is reserved for vector table. Do not allocate anything here*/
    OCMC_VEC_TBL  : org = 0x4037FC00,  len = 0x400
    DDR3_MPU_CPU0_CODE  : org = 0x83200000,  len = 0x01400000
    DDR3_MPU_CPU0_DATA  : org = 0x84600000,  len = 0x00A00000
    DDR3_MPU_CPU0_STACK : org = 0x85000000,  len = 0x00500000
    DDR3_MPU_CPU0_HEAP  : org = 0x85500000,  len = 0x00500000

    DDR3_IPU1_CPU0_CODE  : org = 0x86400000, len = 0x01400000
    DDR3_IPU1_CPU0_DATA  : org = 0x87800000, len = 0x00A00000
    DDR3_IPU1_CPU0_STACK : org = 0x88200000, len = 0x00500000
    DDR3_IPU1_CPU0_HEAP  : org = 0x88700000, len = 0x00500000

    DDR3_IPU1_CPU1_CODE  : org = 0x89600000, len = 0x01400000
    DDR3_IPU1_CPU1_DATA  : org = 0x8AA00000, len = 0x00A00000
    DDR3_IPU1_CPU1_STACK : org = 0x8B400000, len = 0x00500000
    DDR3_IPU1_CPU1_HEAP  : org = 0x8B900000, len = 0x00500000

    DDR3_DSP1_CODE  : org = 0x8C800000,      len = 0x01400000
    DDR3_DSP1_DATA  : org = 0x8DC00000,      len = 0x00A00000
    DDR3_DSP1_STACK : org = 0x8E600000,      len = 0x00500000
    DDR3_DSP1_HEAP  : org = 0x8EB00000,      len = 0x00500000
}

/* Specify the Section Allocation into Memory */
SECTIONS
{
    .init        : {*(.init)}        > DDR3_MPU_CPU0_CODE
    .text        : {*(.text)}        > DDR3_MPU_CPU0_CODE /* Code */
    .data        : {*(.data)}        > DDR3_MPU_CPU0_DATA /* Initialized Global and Static variables */
    .bss         :                                        /* Uninitialized or Zero initialized */
    {
        _bss_start = . ;
		*(.bss.*) *(COMMON);
		_bss_end = . ;
    }   > DDR3_MPU_CPU0_DATA
                                                          /* Global and Static Variables       */
    .const       : {*(.const)}       > DDR3_MPU_CPU0_DATA /* Global Constants */
    .cinit       : {*(.cinit)}       > DDR3_MPU_CPU0_DATA
    .my_sect_ddr : {*(.my_sect_ddr)} > DDR3_MPU_CPU0_CODE
    .stack :
    {
        . = ALIGN(8);
        stack_start = .;
        *(.stack.*) ;
        . = . + 0x500000;
        stack_end = .;
    }> DDR3_MPU_CPU0_STACK /* Software System Stack */
    .cio         : {*(CIO)}

    _stack = stack_end;
    .a15_vector_table : {
     __vector_base__ = .;
        *(.a15_vector_table.*) ;
     __vector_base_end__ = .;
    } > OCMC_VEC_TBL
}

