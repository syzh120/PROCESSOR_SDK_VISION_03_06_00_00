

-stack  0x1000                             /* SOFTWARE STACK SIZE           */
-heap   0x2000                             /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
        IRAM_MEM:       org = 0x00800000  len = 0x8000
        MMU_TLB:		ORIGIN = 0x4031C000  LENGTH = 0x000004000
		/*SBL will use 1 KB of space from address 0x80000000 for EVE */
        DDR3_A8:		org = 0x80000400 len = (0x0B000000 - 0x400)    /* 176 MB */
        DDR3_BOOT:      org = 0x8B000000 len = 0x00010000    /* 32 MB */
		DDR3_DSP:		org = 0x8B010000 len = 0x01FF0000    /* 32 MB */
		DDR3_M3VPSS:	org = 0x8D000000 len = 0x01000000    /* 16 MB */
		DDR3_M3VIDEO:	org = 0x8E000000 len = 0x01000000    /* 16 MB */
		DDR3_SR0:		org = 0x8F000000 len = 0x01000000    /* 16 MB */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
	boot :
	{
	 rts*.lib<boot.obj>(.text)
	}load > DDR3_BOOT

    .vects : load > IRAM_MEM
    .l2_int  : load > IRAM_MEM
    .pmIdleFunc : load > IRAM_MEM
    .init    : load > DDR3_DSP
    .cio     : load > DDR3_DSP

    .text 	 : load > DDR3_DSP              /* CODE                         */
    .data    : load > DDR3_DSP              /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss     : load > DDR3_DSP              /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const   : load > DDR3_DSP              /* GLOBAL CONSTANTS             */
    .cinit   : load > DDR3_DSP
    .stack   : load > DDR3_DSP            /* SOFTWARE SYSTEM STACK        */
	.far	 : load > DDR3_DSP
	.plt     : load > DDR3_DSP
	.fardata : load > DDR3_DSP
	.neardata: load > DDR3_DSP
	.switch	 : load > DDR3_DSP
	.my_sect_ddr : load > DDR3_DSP
	.sysmem : load > DDR3_DSP
	.rodata : load > DDR3_DSP
}

