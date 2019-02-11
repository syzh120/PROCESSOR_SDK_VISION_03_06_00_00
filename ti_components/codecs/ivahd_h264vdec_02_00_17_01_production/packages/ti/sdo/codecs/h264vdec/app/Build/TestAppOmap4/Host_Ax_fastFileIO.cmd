/*
*******************************************************************************
 * HDVICP2.0 Based H.264 HP Decoder
 * 
 * "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on ISO/IEC 14496-10." 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*******************************************************************************
*/
/**  
*******************************************************************************
 * @file Host_Omap4.cmd                        
 *                                       
 * @brief  Linker command file for the Test application. 
 *
 *         This File contains the Memory map and linker secctions used by the 
 *         test application for Omap4 
 *
 * @author:  Keshava Prasad <prasadk@ti.com>
 *
 * @version 0.1 (Jan 2008) : Base version 
 ******************************************************************************
*/

-c                                      /* LINK USING C CONVENTIONS         */
-stack  0x4000                          /* SOFTWARE STACK SIZE              */
-heap   0x05700000                      /* HEAP AREA SIZE                   */
-l rtsv7M3_T_le_eabi.lib                /* GET RUN-TIME SUPPORT             */

/*--------------------------------------------------------------------------*/
/* SPECIFY THE SYSTEM MEMORY MAP                                            */
/*--------------------------------------------------------------------------*/
MEMORY
{
    I_MEM         : o = 0x00000000     l = 0x00000100  /* PROGRAM MEMORY (ROM) */
    EXTMEM_SHARED : o = 0x94000000     l = 0x00100000 
    EXTMEM        : o = 0x94100000     l = 0x06F00000
    /*-----------------------------------------------------------------------*/
    /* After EXTMEM memory(0x9B000000), output buffers are allocated. If you */
    /* want to increase the EXTMEM, you need to modify the output buffers    */
    /* address accordingly in TestApp_bufmanager.c                           */
    /*-----------------------------------------------------------------------*/
}


/*--------------------------------------------------------------------------*/
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY                              */
/*--------------------------------------------------------------------------*/

SECTIONS
{
    .intvecs : {} > I_MEM              /* INTERRUPT VECTORS                 */
    .bss     : {} > EXTMEM             /* GLOBAL & STATIC VARS              */
    .sysmem  : {} > EXTMEM             /* DYNAMIC MEMORY ALLOCATION AREA    */
    .stack   : {} > EXTMEM             /* SOFTWARE SYSTEM STACK             */
    .data    : {} > EXTMEM
    .text    : {} > EXTMEM             /* CODE                              */
    .cinit   : {} > EXTMEM             /* INITIALIZATION TABLES             */
    .const   : {} > EXTMEM             /* CONSTANT DATA                     */

    .pinit   : {} > EXTMEM             /* C++ CONSTRUCTOR TABLES            */
    .input   : {} > EXTMEM
    .output  : {} > EXTMEM
    .mytemp  : {} > EXTMEM
//    .pci_stat: {} > EXTMEM_PCI
    .fileIOSys: {} >    EXTMEM_SHARED
}

