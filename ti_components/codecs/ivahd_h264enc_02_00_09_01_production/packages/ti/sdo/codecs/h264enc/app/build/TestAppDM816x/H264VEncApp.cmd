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
-stack  0x100500                          /* SOFTWARE STACK SIZE              */
-heap   0x2000000                        /* HEAP AREA SIZE                   */
__S_STACK_SIZE = 0x40;                  /* SUPERVISOR Stack                 */
__F_STACK_SIZE = 0x80;                  /* FIQ Stack                        */
__I_STACK_SIZE = 0x40;                  /* IRQ Stack                        */
__U_STACK_SIZE = 0x40;                  /* UNDEF Stack                      */
__Y_STACK_SIZE = 0x40;                  /* SYSYEM Stack                     */
__A_STACK_SIZE = 0x40;                  /* ABORT Stack                      */

/*-l rtsv7M3_T_le_tiarm9.lib        */  /* GET RUN-TIME SUPPORT             */
-l rtsv7M3_T_le_eabi.lib
/*--------------------------------------------------------------------------*/
/* SPECIFY THE SYSTEM MEMORY MAP                                            */
/*--------------------------------------------------------------------------*/
MEMORY
{
    VECS          :     o = 0x00000000     l = 0x00000100
    ITCM          :     o = 0x00000100     l = 0x0002FF00
    EXTMEM_SHARED :     o = 0x94000000     l = 0x00100000
    EXTMEM_PCI    :     o = 0xB8000000     l = 0x00000100
    
    
    /* For RTSC and PCI File IO */
    EXTMEM_IO     :     o = 0xB8000100     l = 0x06000000
    EXTMEM        :     o = 0x8C000000     l = 0x03000000 
       
    
    /* For Host File IO */
    /*   EXTMEM_IO          :            o = 0x94100000     l = 0x04000000
    EXTMEM             :            o = 0x98100000     l = 0x04000000 */
    
}
 
/*--------------------------------------------------------------------------*/
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY                              */
/*--------------------------------------------------------------------------*/
SECTIONS
{

   .M3_text {
            ../../../../Lib/h264enc_ti_host.lib  (.text)
    } > EXTMEM
  .rts_lib {
         rtsv7M3_T_le_eabi.lib  (.text)
    } > EXTMEM

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
    .cio            >       EXTMEM
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
   .analyticinfo_sect >    EXTMEM_IO  PALIGN(16)
   .UserDataUnRegSect >    EXTMEM_IO
   .inputbuffer_mem   >    EXTMEM_IO
   .bitStream_sect    >    EXTMEM_IO  PALIGN(16)
   .recon_tmp         >    EXTMEM
   .pci_stat          >    EXTMEM_PCI
   .InternalMemory    >    EXTMEM PALIGN(16)
   .fileIOSys         >    EXTMEM_SHARED
   .RawInput   :{}    >    EXTMEM_IO PALIGN(16)
   
    
    .M3_const {
                ../../../../Lib/h264enc_ti_host.lib  (.const)
    } > EXTMEM
}
