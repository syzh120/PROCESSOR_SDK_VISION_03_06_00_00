/*==========================================================================*/
/* LNK.CMD   - v2.50a COMMAND FILE FOR LINKING TMS470 32BIS C/C++ PROGRAMS  */
/*                                                                          */
/*   Usage:  lnk470 <obj files...>    -o <out file> -m <map file> lnk.cmd   */
/*           cl470 <src files...> -z -o <out file> -m <map file> lnk.cmd    */
/*                                                                          */
/*   Description: < Empty >                                                 */
/*                                                                          */
/*   Notes: (1)   You must specify the directory in which run-time support  */
/*                library is located.  Either add a "-i<directory>" line to */
/*                this file, or use the system environment variable C_DIR   */
/*                to specify a search path for libraries.                   */
/*                                                                          */
/*          (2)   If the run-time support library you are using is not      */
/*                named below, be sure to use the correct name here.        */
/*                                                                          */
/*==========================================================================*/

/*-c   */                                /* LINK USING C CONVENTIONS         */
-stack  0x8000                           /* SOFTWARE STACK SIZE              */
-heap   0x4800000                        /* HEAP AREA SIZE                   */

/*--------------------------------------------------------------------------*/
/* SPECIFY THE SYSTEM MEMORY MAP                                            */
/*--------------------------------------------------------------------------*/
MEMORY
{
  VECS         	: o = 0x00000000     l = 0x00000100  
  EXTMEM        : o = 0x80000000     l = 0x0C100000
  EXTMEM_TEXT   : o = 0x8C100000     l = 0x00010000
  TEMP_BUFFER   : o = 0x8D000000     l = 0x03000000
}

/*--------------------------------------------------------------------------*/
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY                              */
/*--------------------------------------------------------------------------*/
SECTIONS
{
  .intvecs        : {} > VECS            /* INTERRUPT VECTORS                 */

  .bss            : {} > EXTMEM          /* GLOBAL & STATIC VARS              */

  .pci_stat		: {} > EXTMEM
  .input_buffer   : {} > EXTMEM

  .sysmem         : {} > EXTMEM          /* DYNAMIC MEMORY ALLOCATION AREA    */
  .io_buffer      : {} > EXTMEM
  .chroma_buffer  : {} > EXTMEM
  .ref_buffer     : {} > EXTMEM

  .const          : {} > EXTMEM          /* CONSTANT DATA                     */
  .stack          : {} > EXTMEM          /* SOFTWARE SYSTEM STACK             */
  .data           : {} > EXTMEM          /* DATA                              */
  .text           : {} > EXTMEM_TEXT     /* CODE                              */
  .cinit          : {} > EXTMEM          /* INITIALIZATION TABLES             */
  .pinit          : {} > EXTMEM          /* C++ CONSTRUCTOR TABLES            */
  .temp_buffer    : {} > TEMP_BUFFER     /* Temporary buffer for data sync purpose only */
}

