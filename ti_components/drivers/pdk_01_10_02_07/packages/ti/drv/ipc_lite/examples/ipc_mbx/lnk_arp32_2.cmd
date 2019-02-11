
-e _reset_handler
-heap  0x3000
-stack 0x1000

MEMORY
{
    PAGE 0:
      DMEM            :    origin = 0x40020000 length = 0x8000
      WBUF            :    origin = 0x40040000 length = 0x8000
      IMEMLA          :    origin = 0x40050000 length = 0x4000
      IMEMHA          :    origin = 0x40054000 length = 0x4000
      IMEMLB          :    origin = 0x40070000 length = 0x4000
      IMEMHB          :    origin = 0x40074000 length = 0x4000
      OCMC_RAM1       :    origin = 0x40300000 length = 0x80000
      OCMC_RAM2       :    origin = 0x40400000 length = 0x100000
      OCMC_RAM3       :    origin = 0x40500000 length = 0x100000
      DDR_VECS_MEM    :    origin = 0x81000000 length = 0x0100
      DDR_CMD_MEM     :    origin = 0x81000100 length = 0x1000
      DDR_CODE_MEM    :    origin = 0x81001100 length = 0x200000
      DDR_DATA_MEM    :    origin = 0x81201100 length = 0xd80000
}

SECTIONS
{
  .intvecs      > DDR_VECS_MEM  PAGE 0
  .inthandler   > DDR_CMD_MEM   PAGE 0   /* needs a dedicated region */
  .exitlocation > DDR_VECS_MEM  PAGE 0
  .vecs:        > DDR_VECS_MEM  PAGE 0

  .text > DDR_CODE_MEM  PAGE 0
  {
    *(.text)
    }

   GROUP
   {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
    }>DDR_DATA_MEM  PAGE 0

  Adata:                 load = IMEMLA          PAGE 0
  Bdata:                 load = IMEMHA          PAGE 0
  Cdata:                 load = WBUF            PAGE 0
  .imemha:               load = IMEMHA          PAGE 0
  .imemhb:               load = IMEMHB          PAGE 0
  .imemla:               load = IMEMLA          PAGE 0
  .imemlb:               load = IMEMLB          PAGE 0
  .wmem:                 load = WBUF            PAGE 0
  .dmem_int_sec:         load = DMEM            PAGE 0
  .vcop_parameter_block: load = WBUF            PAGE 0
  Udata:                 load = WBUF            PAGE 0
  .const                 load = DDR_DATA_MEM    PAGE 0
  EOutdata:              load = DDR_DATA_MEM    PAGE 0
  Sdata:                 load = DDR_DATA_MEM    PAGE 0
  .cint:                 load = DDR_DATA_MEM    PAGE 0
  .bss :                 load = DDR_DATA_MEM    PAGE 0
  .data:                 load = DDR_DATA_MEM    PAGE 0
  SRC_REGION:            load = DDR_DATA_MEM    PAGE 0
  DST1_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST2_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST3_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST4_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST5_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST6_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST7_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST8_REGION:           load = DDR_DATA_MEM    PAGE 0
  DST_REGION:            load = DDR_DATA_MEM    PAGE 0
  .cinit:                load = DDR_DATA_MEM    PAGE 0
  .far:                  load = DDR_DATA_MEM    PAGE 0
  .fardata:              load = DDR_DATA_MEM    PAGE 0
  .stack:                load = DDR_DATA_MEM    PAGE 0
  .sysmem:               load = DDR_DATA_MEM    PAGE 0
  .init_array:           load = DDR_DATA_MEM    PAGE 0
  .cio:                  load = DDR_DATA_MEM    PAGE 0
}
