/****************************************************************************/
/*  link.vcop.cmd                                                           */
/*  Copyright (c) 1996-2011  Texas Instruments Incorporated                 */
/****************************************************************************/

-heap  0x5000
-stack 0x1000

MEMORY
{
    PAGE 0:
      EXTMEM  :    origin = 0x80000000 length = 0x10000

    PAGE 1:
      DATMEM  :    origin = 0x40020000 length = 0x20000
      WMEM    :    origin = 0x40040000 length = 0x7E00
      IMEMLA  :    origin = 0x40050000 length = 0x4000
      IMEMHA  :    origin = 0x40054000 length = 0x4000
      IMEMLB  :    origin = 0x40070000 length = 0x4000
      IMEMHB  :    origin = 0x40074000 length = 0x4000
      GEM0_L2_MEM: origin = 0x40800000 length = 0x8000
}

#ifdef VCOP_CAMA
/*----------------------------------------------------------------------------
* VCOP Compiler Assisted Memory Allocation
*---------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------
* Define VCOP heap sizes. These can be smaller than the actual memory region
*---------------------------------------------------------------------------*/ 
IMEML_SIZE = 0x4000;
IMEMH_SIZE = 0x4000;
WMEM_SIZE  = 0x4000;

/*----------------------------------------------------------------------------
* Define VCOP heap locations and ensure heaps span the appropriate size
*---------------------------------------------------------------------------*/ 
SECTIONS
{
  .imemla: { *(.imemla) . += (IMEML_SIZE - 8); } > IMEMLA PAGE 1
  .imemha: { *(.imemha) . += (IMEMH_SIZE - 8); } > IMEMHA PAGE 1
  .imemlb: { *(.imemlb) . += (IMEML_SIZE - 8); } > IMEMLB PAGE 1
  .imemhb: { *(.imemhb) . += (IMEMH_SIZE - 8); } > IMEMHB PAGE 1
  .wmem  : { *(.wmem)   . += (WMEM_SIZE  - 8); } > WMEM   PAGE 1
}
#else

/*----------------------------------------------------------------------------
* VCOP Manual Allocation
*---------------------------------------------------------------------------*/ 
SECTIONS
{
  Adata:    load = IMEMLA PAGE 1
  Bdata:    load = IMEMHA PAGE 1
  Cdata:    load = WMEM   PAGE 1
  Sdata:    load = DATMEM PAGE 1
  Udata:    load = WMEM   PAGE 1
  Vdata:    load = WMEM   PAGE 1
  Ydata:    load = WMEM   PAGE 1
}

/*----------------------------------------------------------------------------
* Disable VCOP Compiler Assisted Memory Allocation by setting heapsize to zero
*---------------------------------------------------------------------------*/ 
IMEML_SIZE = 0x0;
IMEMH_SIZE = 0x0;
WMEM_SIZE  = 0x0;
#endif

SECTIONS
{
  .text:     load = EXTMEM PAGE 0

  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1

  EOutdata              > DATMEM  PAGE 1
  .const                > DATMEM  PAGE 1
  .cint                 > DATMEM  PAGE 1
  .stack                > DATMEM  PAGE 1
  .sysmem               > DATMEM  PAGE 1
  .cinit                > DATMEM  PAGE 1
  .cio                  > DATMEM  PAGE 1
  .far                  > DATMEM  PAGE 1
  .fardata              > DATMEM  PAGE 1
  .init_array           > DATMEM  PAGE 1
  .vcop_parameter_block > WMEM    PAGE 1
}
