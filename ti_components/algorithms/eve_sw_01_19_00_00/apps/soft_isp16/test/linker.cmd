/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
//-e _c_int00
-e _reset_handler
-heap  0x1000000 /* For EXTDMEM heap allocation. .sysmem is in EXTDMEM */
-stack 0x4000 /* Need at least 7092 bytes for evelib_imagePyramid_u8.c */
--define VCOP_CAMA

MEMORY
{
    PAGE 0:
      VECMEM  :    origin      = 0x80000000, length = 0x0100
      CMDMEM  :    origin      = 0x80000100, length = 0x1000
      EXTMEM  :    origin      = 0x80001100, length = 0x20000

    PAGE 1:
      DATMEM  :    origin = 0x40020000 length = 0x8000
      WMEM    :    origin = 0x40040000 length = 0x7FE0
      IMEMLA  :    origin = 0x40050000 length = 0x4000
      IMEMHA  :    origin = 0x40054000 length = 0x4000
      IMEMLB  :    origin = 0x40070000 length = 0x4000
      IMEMHB  :    origin = 0x40074000 length = 0x4000
      GEM0_L2_MEM: origin = 0x40800000 length = 0x8000
      EXTDMEM :    origin = 0x80030000 length = 0x2000000
      L3MEM   :    origin = 0x40300000, length = 0x100000
}



#ifdef VCOP_CAMA
/*---------------------------------------------------------------------------*/
/* VCOP Compiler Assisted Memory Allocation                                  */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Define VCOP heap sizes. These can be smaller than the actual memory region*/
/*---------------------------------------------------------------------------*/

IMEML_SIZE = 0x4000;
IMEMH_SIZE = 0x4000;
WMEM_SIZE  = 0x7000; /*for bop*/
/*WMEM_SIZE  = 0x4000;*/

/*--------------------------------------------------------------------------*/
/* Define VCOP heap locations and ensure heaps span the appropriate size    */
/*--------------------------------------------------------------------------*/
SECTIONS
{
  .imemla: { *(.imemla) . += (IMEML_SIZE - 8); } > IMEMLA PAGE 1
  .imemha: { *(.imemha) . += (IMEMH_SIZE - 8); } > IMEMHA PAGE 1
  .imemlb: { *(.imemlb) . += (IMEML_SIZE - 8); } > IMEMLB PAGE 1
  .imemhb: { *(.imemhb) . += (IMEMH_SIZE - 8); } > IMEMHB PAGE 1
  .wmem  : { *(.wmem)   . += (WMEM_SIZE  - 8); } > WMEM   PAGE 1
}

#else

/*-----------------------------------------------------------------------------*/
/* Disable VCOP Compiler Assisted Memory Allocation by setting heapsize to zero*/
/*-----------------------------------------------------------------------------*/
IMEML_SIZE = 0x0;
IMEMH_SIZE = 0x0;
WMEM_SIZE  = 0x0;

#endif

/*---------------------------------------------------------------------------*/
/* VCOP Manual Allocation                                                    */
/*---------------------------------------------------------------------------*/

SECTIONS
{
  .const       > EXTDMEM  PAGE 1 //moving to extmem due to dmem space constraint
  Adata        > IMEMLA  PAGE 1
  Bdata        > IMEMHA  PAGE 1
  Cdata        > WMEM    PAGE 1
  EOutdata     > DATMEM  PAGE 1
  Sdata        > DATMEM  PAGE 1
  Udata        > WMEM    PAGE 1
  Vdata        > WMEM    PAGE 1
  Ydata        > WMEM    PAGE 1
  .dmemSect    > DATMEM  PAGE 1
  .cint        > DATMEM  PAGE 1
  .stack       > DATMEM  PAGE 1
  .sysmem      > EXTDMEM  PAGE 1
  .cinit       > DATMEM  PAGE 1
  .cio         > DATMEM  PAGE 1
  .far         > EXTDMEM  PAGE 1
  .fardata     > EXTDMEM  PAGE 1
  .init_array  > DATMEM  PAGE 1
  .vcop_parameter_block > WMEM PAGE 1
}


SECTIONS
{
  .intvecs      > VECMEM  PAGE 0
  .inthandler   > CMDMEM  PAGE 0
  .exitlocation > CMDMEM  PAGE 0

  .rts_fardata
  {
    rtsarp32_v200.lib<*.o*> (.far)
    rtsarp32_v200.lib<*.o*> (.fardata)
  } SIZE(_rts_fardata_size) > EXTDMEM  PAGE 1


  .algo_fardata
  {
    //libevekernels.eve.lib<*blockAverage2x2*.o*> (.far)
    libevekernels.eve.lib<*census_8bits*.o*> (.fardata)
	libevekernels.eve.lib<*census_16bits*.o*> (.fardata)
  } SIZE(_algo_fardata_size) > EXTDMEM  PAGE 1

  .starterware_fardata
  {
    //libevestarterware_eve.lib<*.o*> (.far)
    libevestarterware_eve.lib<*.o*> (.fardata)
  } SIZE(_starterware_fardata_size) > EXTDMEM  PAGE 1

  .bam_fardata
  {
    algframework.lib<*.o*> (.far)
    algframework.lib<*.o*> (.fardata)
  } SIZE(_bam_fardata_size) > EXTDMEM  PAGE 1

  .bam_neardata
  {
    //algframework.lib<*.o*> (.bss)
    //algframework.lib<*.o*> (.data)
    algframework.lib<*.o*> (.rodata)
    algframework.lib<*.o*> (.const)
  } SIZE(_bam_neardata_size) > DATMEM   PAGE 1

  .algo_neardata
  {
  } SIZE(_algo_neardata_size) > DATMEM   PAGE 1

  .starterware_neardata
  {
    libevestarterware_eve.lib<*.o*> (.bss)
    libevestarterware_eve.lib<*.o*> (.data)
    //libevestarterware_eve.lib<*.o*> (.rodata)
    //libevestarterware_eve.lib<*.o*> (.const)
  } SIZE(_starterware_neardata_size) > DATMEM  PAGE 1

  .rts_neardata
  {
    //rtsarp32_v200.lib<*.o*> (.bss)
    //rtsarp32_v200.lib<*.o*> (.data)
    //rtsarp32_v200.lib<*.o*> (.rodata)
    rtsarp32_v200.lib<*.o*> (.const)
  } SIZE(_rts_neardata_size) > DATMEM  PAGE 1

  .bam_text
  {
    algframework.lib<*.o*> (.text)
  } SIZE(_bam_text_size) > EXTMEM   PAGE 0

  .algo_text
  {
    libeveSoftIsp16.eve.lib<*.o*> (.text)
  } SIZE(_algo_text_size) > EXTMEM   PAGE 0

  .starterware_text
  {
    libevestarterware_eve.lib<*.o*> (.text)
  } SIZE(_starterware_text_size) > EXTMEM   PAGE 0

  .rts_text
  {
    rtsarp32_v200.lib<*.o*> (.text)
  } SIZE(_rts_text_size) > EXTMEM   PAGE 0

  .text
  {
    *(.text)
  } SIZE(_text_size) > EXTMEM   PAGE 0

  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1


   SRC_MEM        > EXTDMEM    PAGE 1//, type= NOLOAD
   DDR_MEM        > EXTDMEM    PAGE 1
   DST_MEM        > EXTDMEM    PAGE 1
   IBUFLA         > IMEMLA     PAGE 1
   IBUFHA         > IMEMHA     PAGE 1
   IBUFLB         > IMEMLB     PAGE 1
   IBUFHB         > IMEMHB     PAGE 1
   WBUF           > WMEM       PAGE 1
   DMEM           > DATMEM	   PAGE 1
}


