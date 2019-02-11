/****************************************************************************/
/*  ivahd.cmd                                                               */
/*  Copyright (c) 1996-2011  Texas Instruments Incorporated                 */
/****************************************************************************/
-c
-stack 0x6000
-heap 0x50000

--retain vec_table

MEMORY
{
    PAGE 0:
        INTVECS   :   origin = 00000000h   length = 00000030h
        EXITSECT  :   origin = 00000100h   length = 00000100h
	RESET	  :   origin = 00000200h   length = 000002c0h
        ON_CHIP   :   origin = 00000500h   length = 0003FAFFh

    PAGE 1:
        DATASECT  :   origin = 00000004h   length = 0001FFFFh
        STACKSECT :   origin = 00030000h   length = 0003FFFFh
	SL2	  :   origin = 00400000h   length = 00080000h
}

SECTIONS
{
    .intvecs    >       INTVECS PAGE 0
    .inthandler >       RESET PAGE 0

    .init_array >       DATASECT PAGE 1
    .text       >       ON_CHIP PAGE 0

    /* __bss_start required to preserve .bss section for temporary simluator */
    /* bug workaround.                                                       */
    GROUP
    {
        .bss        /* This order facilitates a single segment for */
        .data       /* GDP-relative addressing                     */
        .rodata
    }>DATASECT PAGE 1, RUN_START(__bss_start)

    .stack      >       STACKSECT PAGE 1
    .cinit      >       DATASECT PAGE 1
    .cio        >       DATASECT PAGE 1
    .const      >       DATASECT PAGE 1
    Adata       >	DATASECT PAGE 1
    Bdata       >	DATASECT PAGE 1
    Cdata       >	DATASECT PAGE 1
    Sdata       >	DATASECT PAGE 1
    EOutdata    >	DATASECT PAGE 1
    .switch     >       SL2 PAGE 1
    .sysmem     >       SL2 PAGE 1
    .far        >       SL2 PAGE 1
    .fardata    >       DATASECT PAGE 1
}
