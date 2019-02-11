/****************************************************************************/
/*  bin.link.rtsboot.v1.cmd                                                 */
/*  Copyright (c) 1996-2011  Texas Instruments Incorporated                 */
/****************************************************************************/
-c
-stack 0x6000
-heap 0x50000

MEMORY
{
        VECS      :   origin = 00000000h   length = 00000020h
        ISAINIT   :   origin = 00000020h   length = 000000e0h
        EXITSECT  :   origin = 00000100h   length = 00000200h
        STACKSECT :   origin = 00000300h   length = 00006000h
        ON_CHIPA  :   origin = 00006300h   length = 00220000h
}

SECTIONS
{
    .vecs       >       VECS
    .isainit    >       ISAINIT

    .text       >       ON_CHIPA
    .stack      >       STACKSECT

    GROUP
    {
        .bss            /* This order facilitates a single segment for */
        .data           /* GDP-relative addressing                     */
        .rodata
    }>ON_CHIPA

    .cinit      >       ON_CHIPA
    .cio        >       ON_CHIPA
    .const      >       ON_CHIPA
    .switch     >       ON_CHIPA
    .sysmem     >       ON_CHIPA
    .far        >       ON_CHIPA
    .fardata    >       ON_CHIPA
}
