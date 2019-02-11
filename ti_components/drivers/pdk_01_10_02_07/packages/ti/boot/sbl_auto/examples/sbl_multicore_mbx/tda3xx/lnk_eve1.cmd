

/****************************************************************************/
/* LNK32.CMD - v4.5.0 COMMAND FILE FOR LINKING TMS470 32BIS C/C++ PROGRAMS  */
/*                                                                          */
/*   Usage:  armlnk <obj files...>    -o <out file> -m <map file> lnk32.cmd */
/*           armcl <src files...> -z -o <out file> -m <map file> lnk32.cmd  */
/*                                                                          */
/*   Description: This file is a sample command file that can be used       */
/*                for linking programs built with the TMS470 C/C++          */
/*                Compiler.   Use it as a guideline; you may want to change */
/*                the allocation scheme according to the size of your       */
/*                program and the memory layout of your target system.      */
/*                                                                          */
/*   Notes: (1)   You must specify the directory in which run-time support  */
/*                library is located.  Either add a "-i<directory>" line to */
/*                this file, or use the system environment variable C_DIR   */
/*                to specify a search path for libraries.                   */
/*                                                                          */
/*          (2)   If the run-time support library you are using is not      */
/*                named below, be sure to use the correct name here.        */
/*                                                                          */
/****************************************************************************/
/*-stack  0x0800                              SOFTWARE STACK SIZE           */
/*-heap   0x2000                              HEAP AREA SIZE                */
/*-e Entry*/
/* Since we used 'Entry' as the entry-point symbol the compiler issues a    */
/* warning (#10063-D: entry-point symbol other than "_c_int00" specified:   */
/* "Entry"). The CCS Version (5.1.0.08000) stops building from command      */
/* line when there is a warning. So this warning is suppressed with the     */
/* below flag. */

/*--diag_suppress=10063*/


-e _reset_handler
//-e _c_int00
-heap  0x1000
-stack 0x500000

MEMORY
{
/*	IRAM_MEM : org = 0x40300000,len = 0x1C000
	MMU_TLB : org = 0x4031C000,len = 0x000004000
*/
	/*CODE SECTION - 20MB*/
	/*DATA SECTION - 10MB*/
	/*STACK - 5MB*/
	/*HEAP - 5MB*/
/*	DDR3_MPU_CPU0_CODE : org = 0x90000000,len = 0x01400000
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

	DDR3_EVE1_CODE : org = 0x89600000,len = 0x01400000
	DDR3_EVE1_DATA :  org = 0x8AA00000,len = 0x00A00000
	DDR3_EVE1_STACK : org = 0x8B400000,len = 0x00500000
	DDR3_EVE1_HEAP :  org = 0x8B900000,len = 0x00500000

	DDR3_EVE2_CODE : org = 0x8C800000,len = 0x01400000
	DDR3_EVE2_DATA :  org = 0x8DC00000,len = 0x00A00000
	DDR3_EVE2_STACK : org = 0x8E600000,len = 0x00500000
	DDR3_EVE2_HEAP :  org = 0x8EB00000,len = 0x00500000

*/
    PAGE 0:
      VECMEM  :    origin      = 0x89000000, length = 0x0100
      CMDMEM  :    origin      = 0x89000100, length = 0x1000
      EXTMEM  :    origin      = 0x89001100, length = 0x10000
//      VECMEM  :    origin      = 0x80000000, length = 0x0100
//      CMDMEM  :    origin      = 0x80000100, length = 0x1000
//      EXTMEM  :    origin      = 0x80001100, length = 0x10000

    PAGE 1:
      DATMEM  :    origin = 0x40020000, length = 0x8000
      WMEM    :    origin = 0x40040000, length = 0x7E00
      IMEMLA  :    origin = 0x40050000, length = 0x4000
      IMEMHA  :    origin = 0x40054000, length = 0x4000
      IMEMLB  :    origin = 0x40070000, length = 0x4000
      IMEMHB  :    origin = 0x40074000, length = 0x4000
//      GEM0_L2_MEM: origin = 0x40800000 length = 0x8000
      EXTDMEM :    origin = 0x89030000, length = 0x1000000
//      EXTDMEM :    origin = 0x80030000, length = 0x1000000
//      L3MEM   :    origin = 0x40300000, length = 0x100000
}


SECTIONS
{
  .intvecs      > VECMEM  PAGE 0
  .inthandler   > CMDMEM  PAGE 0
  .exitlocation > CMDMEM  PAGE 0

  .text > EXTMEM   PAGE 0
  {
    *(.text)
  }

  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1

  .const       > DATMEM  PAGE 1
  Adata        > IMEMLA  PAGE 1
  Bdata        > IMEMHA  PAGE 1
  Cdata        > WMEM    PAGE 1
  EOutdata     > DATMEM  PAGE 1
  Sdata        > DATMEM  PAGE 1
  Udata        > WMEM    PAGE 1
  Vdata        > WMEM    PAGE 1
  Ydata        > WMEM    PAGE 1
  .cint        > EXTDMEM  PAGE 1
  .stack       > EXTDMEM  PAGE 1
  .sysmem      > EXTDMEM  PAGE 1
  .cinit       > EXTDMEM  PAGE 1
  .cio         > EXTDMEM  PAGE 1
  .far         > EXTDMEM  PAGE 1
  .fardata     > EXTDMEM  PAGE 1
  .init_array  > EXTDMEM  PAGE  1
  .vcop_parameter_block > WMEM PAGE 1

   SRC_MEM        > EXTDMEM    PAGE 1
   DDR_MEM        > EXTDMEM    PAGE 1
   DST_MEM        > EXTDMEM    PAGE 1
   IBUFLA         > IMEMLA     PAGE 1
   IBUFHA         > IMEMHA     PAGE 1
   IBUFLB         > IMEMLB     PAGE 1
   IBUFHB         > IMEMHB     PAGE 1
   WBUF           > WMEM       PAGE 1
}













