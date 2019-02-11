/*==========================================================================*/
/*   LNK.CMD   - v2.50a COMMAND FILE FOR LINKING TMS470 32BIS C/C++ PROGRAMS*/
/*                                                                          */
/*   Usage:  lnk470 <obj files...>    -o <out file> -m <map file> lnk.cmd   */
/*           cl470 <src files...>  -z -o <out file> -m <map file> lnk.cmd   */
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

-c                                      /* LINK USING C CONVENTIONS         */
-stack  0x25500                          /* SOFTWARE STACK SIZE              */
-heap   0x5EF0000                        /* HEAP AREA SIZE                   */
__S_STACK_SIZE = 0x40;                  /* SUPERVISOR Stack                 */
__F_STACK_SIZE = 0x80;                  /* FIQ Stack                        */
__I_STACK_SIZE = 0x40;                  /* IRQ Stack                        */
__U_STACK_SIZE = 0x40;                  /* UNDEF Stack                      */
__Y_STACK_SIZE = 0x40;                  /* SYSYEM Stack                     */
__A_STACK_SIZE = 0x40;                  /* ABORT Stack                      */

-l rtsv7M3_T_le_eabi.lib
/*--------------------------------------------------------------------------*/
/* SPECIFY THE SYSTEM MEMORY MAP                                            */
/*--------------------------------------------------------------------------*/
MEMORY
{
    VECS        :                   o = 0x00000000     l = 0x00000100
    EXTMEM_SHARED :                 o = 0x94000000     l = 0x00100000 
    EXTMEM_IO          :            o = 0x94100000     l = 0x04000000
    EXTMEM             :            o = 0x98100000     l = 0x07EF0000 
    EXTMEM2            :            o = 0x9FFF0000     l = 0x00010000 

}

/*--------------------------------------------------------------------------*/
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY                              */
/*--------------------------------------------------------------------------*/
SECTIONS
{

  .rts_lib {
         rtsv7M3_T_le_eabi.lib  (.text)
    } > EXTMEM2

    .pinit   : {} > EXTMEM              /* TEMPLATE INSTANTIATION TABLES      */
    .intc    : {} > EXTMEM              /* INTERRUPT RELATED                  */
    .sstack  : {} > EXTMEM              /* INTERRUPT RELATED                  */
    .fstack  : {} > EXTMEM              /* INTERRUPT RELATED                  */
    .istack  : {} > EXTMEM              /* INTERRUPT RELATED                  */
    .ystack  : {} > EXTMEM              /* INTERRUPT RELATED                  */
    .ustack  : {} > EXTMEM              /* INTERRUPT RELATED                  */
    .astack  : {} > EXTMEM              /* INTERRUPT RELATED                  */
    .data    : {} > EXTMEM
    .intvecs        >       VECS
    .switch         >       EXTMEM
    .text           >       EXTMEM
    .cinit          >       EXTMEM
    .stack          >       EXTMEM
    .bss            >       EXTMEM
    .const          >       EXTMEM
    .sysmem         >       EXTMEM
    .far            >       EXTMEM
    .H264ENC_TI_dSect1 : {}          > EXTMEM PALIGN(16)
    .h264e_host_scalingMatrix  > EXTMEM
   /*--------------------------------*/
   /* Application specific sections  */
   /*--------------------------------*/
   .analyticinfo_sect >    EXTMEM PALIGN(16)
   .UserDataUnRegSect >    EXTMEM
   .inputbuffer_mem   >    EXTMEM_IO
   .bitStream_sect    >    EXTMEM  PALIGN(16)
   .recon_tmp         >    EXTMEM
   .pci_stat          >    EXTMEM
   .InternalMemory    >    EXTMEM PALIGN(16)
   .fileIOSys         >    EXTMEM_SHARED
   .RawInput   :{}    >    EXTMEM PALIGN(16)
   .cio            >       EXTMEM2
}
