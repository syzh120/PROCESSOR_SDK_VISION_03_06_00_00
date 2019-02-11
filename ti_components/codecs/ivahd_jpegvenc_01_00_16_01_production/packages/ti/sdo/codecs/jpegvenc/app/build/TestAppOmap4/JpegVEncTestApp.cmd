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
-stack  0x3500                           /* SOFTWARE STACK SIZE              */
-heap   0x4803000                       /* HEAP AREA SIZE                   */
__S_STACK_SIZE = 0x10;                 /* SUPERVISOR Stack                 */
__F_STACK_SIZE = 0x20;                 /* FIQ Stack                        */
__I_STACK_SIZE = 0x10;                 /* IRQ Stack                        */
__U_STACK_SIZE = 0x10;                  /* UNDEF Stack                      */
__Y_STACK_SIZE = 0x10;                  /* SYSYEM Stack                     */
__A_STACK_SIZE = 0x10;                  /* ABORT Stack                      */

/*-l rtsv7M3_T_le_tiarm9.lib */                   /* GET RUN-TIME SUPPORT             */
-l rtsv7M3_T_le_eabi.lib

/*--------------------------------------------------------------------------*/
/* SPECIFY THE SYSTEM MEMORY MAP                                            */
/*--------------------------------------------------------------------------*/
MEMORY
{
    VECS               :            o = 0x00000000     l = 0x00000100
    EXTMEM_CODE        :            o = 0x80000200     l = 0x0002FF00
    EXTMEM_DATA        :            o = 0x80030200     l = 0x00800000
    EXTMEM_DV_I :                   o = 0x80830300     l = 0x002f7600
    EXTMEM_DV_INPARS :              o = 0x80B27A00     l = 0x00006500 
    EXTMEM_DV_CONFIG :              o = 0x80B2DF10     l = 0x00000500
    EXTMEM           :              o = 0x80B2E500     l = 0x0A100000
}

/*--------------------------------------------------------------------------*/
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY                              */
/*--------------------------------------------------------------------------*/
SECTIONS
{

    .pinit   : {} > EXTMEM_DATA              /* TEMPLATE INSTANTIATION TABLES      */
    .data    : {} > EXTMEM
    .intc    : {} > EXTMEM_CODE              /* INTERRUPT RELATED                  */
    .sstack  : {} > EXTMEM_CODE              /* INTERRUPT RELATED                  */
    .fstack  : {} > EXTMEM_CODE             /* INTERRUPT RELATED                  */
    .istack  : {} > EXTMEM_CODE              /* INTERRUPT RELATED                  */
    .ystack  : {} > EXTMEM_CODE             /* INTERRUPT RELATED                  */
    .ustack  : {} > EXTMEM_CODE              /* INTERRUPT RELATED                  */
    .astack  : {} > EXTMEM_CODE             /* INTERRUPT RELATED                  */

    .intvecs        >       VECS
    /*.intc           >       EXTMEM*/
    .switch         >       EXTMEM
    .cio            >       EXTMEM
    .text           >       EXTMEM
    .cinit          >       EXTMEM_DATA
    .stack          >       EXTMEM_DATA
    .handle         >       EXTMEM_DATA
    .bss            >       EXTMEM
	.thumbnail_data >       EXTMEM
	.userDefQuantTab >       EXTMEM
    .const          >       EXTMEM
    .scratch        >       EXTMEM_DATA
    .chroma_buffer  >       EXTMEM
    .sysmem         >       EXTMEM
    .tables         >       EXTMEM
    .far            >       EXTMEM
    .handler        >       EXTMEM_DATA
	

    .input          >       EXTMEM_DV_I
	.inpars         >       EXTMEM_DV_INPARS
	.inConfig       >       EXTMEM_DV_CONFIG
}

