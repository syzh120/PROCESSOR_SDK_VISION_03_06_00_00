#ifndef _TI_vcop_foreach_multiblock_bilinear_interp_7x7_u8_kernel_h_
#define _TI_vcop_foreach_multiblock_bilinear_interp_7x7_u8_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8[416];

/* Basic Runner Function */
void vcop_foreach_multiblock_bilinear_interp_7x7_u8(
   __vptr_uint8_arr pIn_A,
   __vptr_uint16_arr pInpWts_B,
   __vptr_uint8_arr pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short outBlkWidth,
   unsigned short outBlkHeight,
   unsigned short shiftValue,
   unsigned short numKeyPoints);
/* Custom Runner Function */
void vcop_foreach_multiblock_bilinear_interp_7x7_u8_custom(
   __vptr_uint8_arr pIn_A,
   __vptr_uint16_arr pInpWts_B,
   __vptr_uint8_arr pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short outBlkWidth,
   unsigned short outBlkHeight,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(
   __vptr_uint8_arr pIn_A,
   __vptr_uint16_arr pInpWts_B,
   __vptr_uint8_arr pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short outBlkWidth,
   unsigned short outBlkHeight,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_foreach_multiblock_bilinear_interp_7x7_u8 ((unsigned int)416)
unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_foreach_multiblock_bilinear_interp_7x7_u8 ((unsigned int)1)
unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_ctrl_count(void);

/***********************************************************/
#endif

