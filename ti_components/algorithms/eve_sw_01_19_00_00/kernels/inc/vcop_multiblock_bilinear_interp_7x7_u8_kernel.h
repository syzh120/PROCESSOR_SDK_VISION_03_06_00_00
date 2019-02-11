#ifndef _TI_vcop_multiblock_bilinear_interp_7x7_u8_kernel_h_
#define _TI_vcop_multiblock_bilinear_interp_7x7_u8_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_multiblock_bilinear_interp_7x7_u8[30];

/* Basic Runner Function */
void vcop_multiblock_bilinear_interp_7x7_u8(
   __vptr_uint8 pIn_A,
   __vptr_uint16 pInpWts_B,
   __vptr_uint8 pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short shiftValue,
   unsigned short numKeyPoints);
/* Custom Runner Function */
void vcop_multiblock_bilinear_interp_7x7_u8_custom(
   __vptr_uint8 pIn_A,
   __vptr_uint16 pInpWts_B,
   __vptr_uint8 pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_multiblock_bilinear_interp_7x7_u8_init(
   __vptr_uint8 pIn_A,
   __vptr_uint16 pInpWts_B,
   __vptr_uint8 pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_multiblock_bilinear_interp_7x7_u8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_multiblock_bilinear_interp_7x7_u8 ((unsigned int)30)
unsigned int vcop_multiblock_bilinear_interp_7x7_u8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_multiblock_bilinear_interp_7x7_u8 ((unsigned int)0)
unsigned int vcop_multiblock_bilinear_interp_7x7_u8_ctrl_count(void);

/***********************************************************/
#endif

