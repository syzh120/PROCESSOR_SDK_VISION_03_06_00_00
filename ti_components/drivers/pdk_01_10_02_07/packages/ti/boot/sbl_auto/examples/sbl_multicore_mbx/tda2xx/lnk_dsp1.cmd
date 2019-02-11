

-stack  0x00500000                            /* SOFTWARE STACK SIZE           */
-heap   0x00500000                         /* HEAP AREA SIZE                */
-e      _c_int00

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    IRAM_MEM:     org = 0x00800000 len = 0x8000      /*   RAM 0x1FBFF*/
	/*CODE SECTION - 20MB*/
	/*DATA SECTION - 10MB*/
	/*STACK - 5MB*/
	/*HEAP - 5MB*/	
	DDR3_MPU_CPU0_CODE : org = 0x90000000,len = 0x01400000
	DDR3_MPU_CPU0_DATA :  org = 0x91400000, len = 0x00A00000
	DDR3_MPU_CPU0_STACK : org = 0x91E00000, len = 0x00500000
	DDR3_MPU_CPU0_HEAP :  org = 0x92300000, len = 0x00500000
	
	DDR3_IPU1_CPU0_CODE : org = 0x93200000,len = 0x01400000
	DDR3_IPU1_CPU0_DATA :  org = 0x94600000, len = 0x00A00000
	DDR3_IPU1_CPU0_STACK : org = 0x95000000, len = 0x00500000
	DDR3_IPU1_CPU0_HEAP :  org = 0x95500000, len = 0x00500000
	
	DDR3_IPU1_CPU1_CODE : org = 0x96400000,len = 0x01400000
	DDR3_IPU1_CPU1_DATA :  org = 0x97800000,len = 0x00A00000
	DDR3_IPU1_CPU1_STACK : org = 0x98200000,len = 0x00500000
	DDR3_IPU1_CPU1_HEAP :  org = 0x98700000,len = 0x00500000
	
	DDR3_IPU2_CPU0_CODE : org = 0x99600000,len = 0x01400000
	DDR3_IPU2_CPU0_DATA :  org = 0x9AA00000,len = 0x00A00000
	DDR3_IPU2_CPU0_STACK : org = 0x9B400000,len = 0x00500000
	DDR3_IPU2_CPU0_HEAP :  org = 0x9B900000,len = 0x00500000
	
	DDR3_IPU2_CPU1_CODE : org = 0x9C800000,len = 0x01400000
	DDR3_IPU2_CPU1_DATA :  org = 0x9DC00000,len = 0x00A00000
	DDR3_IPU2_CPU1_STACK : org = 0x9E600000,len = 0x00500000
	DDR3_IPU2_CPU1_HEAP :  org = 0x9EB00000,len = 0x00500000
	
	DDR3_DSP1_CODE : org = 0x83200000,len = 0x01400000
	DDR3_DSP1_DATA : org = 0x84600000, len = 0x00A00000
	DDR3_DSP1_STACK :org = 0x85000000, len = 0x00500000
	DDR3_DSP1_HEAP : org = 0x85500000, len = 0x00500000
	
	DDR3_DSP2_CODE : org = 0x86400000,len = 0x01400000
	DDR3_DSP2_DATA :  org = 0x87800000,len = 0x00A00000
	DDR3_DSP2_STACK : org = 0x88200000,len = 0x00500000
	DDR3_DSP2_HEAP :  org = 0x88700000,len = 0x00500000
	
	DDR3_EVE1_CODE : org = 0x89000000,len = 0x01400000
	DDR3_EVE1_DATA :  org = 0x8AA00000,len = 0x00A00000
	DDR3_EVE1_STACK : org = 0x8B400000,len = 0x00500000
	DDR3_EVE1_HEAP :  org = 0x8B900000,len = 0x00500000
	
	DDR3_MPU_CPU1_CODE : org = 0x8C800000,len = 0x01400000
	DDR3_MPU_CPU1_DATA :  org = 0x8DC00000,len = 0x00A00000
	DDR3_MPU_CPU1_STACK : org = 0x8E600000,len = 0x00500000
	DDR3_MPU_CPU1_HEAP :  org = 0x8EB00000,len = 0x00500000
	
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .vects : load > IRAM_MEM
    .l2_int  : load > IRAM_MEM
	boot :
	{
		rts*.lib<boot.obj>(.text)
	}load > DDR3_DSP1_CODE ALIGN(0x400)
	
    .init    : load > DDR3_DSP1_DATA
    .cio     : load > DDR3_DSP1_DATA
              
    .text    : load > DDR3_DSP1_CODE /* CODE                         */
    .data    : load > DDR3_DSP1_DATA /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss     : load > DDR3_DSP1_DATA /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end) 
    .const   : load > DDR3_DSP1_DATA              /* GLOBAL CONSTANTS             */
    .cinit   : load > DDR3_DSP1_DATA
    .stack   : load > DDR3_DSP1_STACK            /* SOFTWARE SYSTEM STACK        */
    .plt     : load > DDR3_DSP1_DATA
	.my_sect_ddr : load > DDR3_DSP1_DATA
	.far  : load > DDR3_DSP1_DATA
    .fardata : load > DDR3_DSP1_DATA
	.neardata : load > DDR3_DSP1_DATA
	.rodata : load > DDR3_DSP1_DATA
	.switch : load > DDR3_DSP1_DATA
}

