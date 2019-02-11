

-stack  0x1000                             /* SOFTWARE STACK SIZE           */
-heap   0x2000                             /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
        IRAM_MEM:       org = 0x00800000  len = 0x8000
        IRAM_MEM_L2_1:       org = 0x00809000  len = 0x1000
        IRAM_MEM_L2_2:       org = 0x0080A000  len = 0x1000
        MMU_TLB:        ORIGIN = 0x4031C000  LENGTH = 0x000004000
        /*SBL will use 1 KB of space from address 0x80000000 for EVE */
        DDR3_BOOT:      org = 0x8B000000 len = 0x00010000    /* 32 MB */
        DDR3_DSP:        org = 0x8B010000 len = 0x01FF0000    /* 32 MB */
        DDR3_M3VPSS:    org = 0x8D000000 len = 0x01000000    /* 16 MB */
        DDR3_M3VIDEO:    org = 0x8E000000 len = 0x01000000    /* 16 MB */
        DDR3_SR0:        org = 0x8F000000 len = 0x01000000    /* 16 MB */
        DDR_CODE1:       org = 0x80000400 len = 0x00001000    /* 4 KB */
        DDR_CODE2:       org = 0x81000400 len = 0x00001000    /* 4 KB */
        DDR_DATA1:       org = 0x82000400 len = 0x00001000    /* 4 KB */
        DDR_DATA2:       org = 0x83000400 len = 0x00001000    /* 4 KB */
        DDR_DATA3:       org = 0x84000400 len = 0x00001000    /* 4 KB */
        DDR_DATA4:       org = 0x85000400 len = 0x00001000    /* 4 KB */
        DDR_DATA5:       org = 0x86000400 len = 0x00001000    /* 4 KB */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    boot :
    {
     rts*.lib<boot.obj>(.text)
    }load > DDR3_BOOT

    GROUP: load > DDR3_DSP
    {
        .bss:       /* UNINITIALIZED OR ZERO INITIALIZED */
        .neardata:
        .rodata:
    }
    .vects : load > IRAM_MEM
    .csl_vect : load > IRAM_MEM
    .l2_int  : load > IRAM_MEM
    .pmIdleFunc : load > IRAM_MEM
    BOARD_IO_DELAY_DATA : load > IRAM_MEM
    BOARD_IO_DELAY_CODE : load > IRAM_MEM
    .init    : load > DDR3_DSP
    .cio     : load > DDR3_DSP

    .text      : load > DDR3_DSP              /* CODE                         */
    .data    : load > DDR3_DSP              /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const   : load > DDR3_DSP              /* GLOBAL CONSTANTS             */
    .cinit   : load > DDR3_DSP
    .stack   : load > DDR3_DSP            /* SOFTWARE SYSTEM STACK        */
    .far     : load > DDR3_DSP
    .plt     : load > DDR3_DSP
    .fardata : load > DDR3_DSP
    .switch     : load > DDR3_DSP
    .my_sect_ddr : load > DDR3_DSP
    .sysmem : load > DDR3_DSP

    .my_l1p_code_sec1: load > DDR_CODE1
    .my_l1p_code_sec2: load > DDR_CODE2
    .my_l2_data_sec1: load > DDR_DATA1
    .my_l2_data_sec2: load > DDR_DATA2
    .my_l2_data_sec3: load > DDR_DATA3
    .my_l2_data_sec4: load > DDR_DATA4
    .my_l2_data_sec5: load > DDR_DATA5
    .my_l2_code_sec1: load > IRAM_MEM_L2_1
    .my_l2_code_sec2: load > IRAM_MEM_L2_2
}

