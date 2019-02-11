#ifndef _TI_vcop_multiblock_bilinear_interp_intlv_7x7_s16_kernel_h_
#define _TI_vcop_multiblock_bilinear_interp_intlv_7x7_s16_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_multiblock_bilinear_interp_intlv_7x7_s16[32];

/* Basic Runner Function */
void vcop_multiblock_bilinear_interp_intlv_7x7_s16(
   __vptr_int16 pIntlvGradXY_A,
   __vptr_uint16 pInpWts_X,
   __vptr_int16 pGradXBilinearInterpImg_B,
   __vptr_int16 pGradYBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short shiftValue,
   unsigned short numKeyPoints);
/* Custom Runner Function */
void vcop_multiblock_bilinear_interp_intlv_7x7_s16_custom(
   __vptr_int16 pIntlvGradXY_A,
   __vptr_uint16 pInpWts_X,
   __vptr_int16 pGradXBilinearInterpImg_B,
   __vptr_int16 pGradYBilinearInterpImg_C,
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
unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_init(
   __vptr_int16 pIntlvGradXY_A,
   __vptr_uint16 pInpWts_X,
   __vptr_int16 pGradXBilinearInterpImg_B,
   __vptr_int16 pGradYBilinearInterpImg_C,
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
void vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_multiblock_bilinear_interp_intlv_7x7_s16 ((unsigned int)32)
unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_multiblock_bilinear_interp_intlv_7x7_s16 ((unsigned int)0)
unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_ctrl_count(void);

/***********************************************************/
#endif

