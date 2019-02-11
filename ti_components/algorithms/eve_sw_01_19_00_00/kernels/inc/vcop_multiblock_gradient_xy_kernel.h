#ifndef _TI_vcop_multiblock_gradient_xy_kernel_h_
#define _TI_vcop_multiblock_gradient_xy_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_multiblock_gradient_xy[20];

/* Basic Runner Function */
void vcop_multiblock_gradient_xy(
   __vptr_uint8 pIn_A,
   __vptr_int16 pIntlvGradXY_B,
   unsigned short inputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short numBlocks);
/* Custom Runner Function */
void vcop_multiblock_gradient_xy_custom(
   __vptr_uint8 pIn_A,
   __vptr_int16 pIntlvGradXY_B,
   unsigned short inputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short numBlocks,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_multiblock_gradient_xy_init(
   __vptr_uint8 pIn_A,
   __vptr_int16 pIntlvGradXY_B,
   unsigned short inputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short numBlocks,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_multiblock_gradient_xy_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_multiblock_gradient_xy ((unsigned int)20)
unsigned int vcop_multiblock_gradient_xy_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_multiblock_gradient_xy ((unsigned int)0)
unsigned int vcop_multiblock_gradient_xy_ctrl_count(void);

/***********************************************************/
#endif

