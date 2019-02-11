#ifndef _TI_vcop_sobel_xy_kernel_h_
#define _TI_vcop_sobel_xy_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_sobelXY_3x3_separable_uchar[40];

/* Basic Runner Function */
void vcop_sobelXY_3x3_separable_uchar(
   __vptr_uint8 inData,
   __vptr_int16 interimDataX,
   __vptr_int16 interimDataY,
   __vptr_int8 outDataX,
   __vptr_int8 outDataY,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift);
/* Custom Runner Function */
void vcop_sobelXY_3x3_separable_uchar_custom(
   __vptr_uint8 inData,
   __vptr_int16 interimDataX,
   __vptr_int16 interimDataY,
   __vptr_int8 outDataX,
   __vptr_int8 outDataY,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sobelXY_3x3_separable_uchar_init(
   __vptr_uint8 inData,
   __vptr_int16 interimDataX,
   __vptr_int16 interimDataY,
   __vptr_int8 outDataX,
   __vptr_int8 outDataY,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sobelXY_3x3_separable_uchar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sobelXY_3x3_separable_uchar ((unsigned int)40)
unsigned int vcop_sobelXY_3x3_separable_uchar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sobelXY_3x3_separable_uchar ((unsigned int)0)
unsigned int vcop_sobelXY_3x3_separable_uchar_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_sobelX_3x3_separable_uchar[32];

/* Basic Runner Function */
void vcop_sobelX_3x3_separable_uchar(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift);
/* Custom Runner Function */
void vcop_sobelX_3x3_separable_uchar_custom(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sobelX_3x3_separable_uchar_init(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sobelX_3x3_separable_uchar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sobelX_3x3_separable_uchar ((unsigned int)32)
unsigned int vcop_sobelX_3x3_separable_uchar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sobelX_3x3_separable_uchar ((unsigned int)0)
unsigned int vcop_sobelX_3x3_separable_uchar_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_sobelY_3x3_separable_uchar[30];

/* Basic Runner Function */
void vcop_sobelY_3x3_separable_uchar(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift);
/* Custom Runner Function */
void vcop_sobelY_3x3_separable_uchar_custom(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sobelY_3x3_separable_uchar_init(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sobelY_3x3_separable_uchar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sobelY_3x3_separable_uchar ((unsigned int)30)
unsigned int vcop_sobelY_3x3_separable_uchar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sobelY_3x3_separable_uchar ((unsigned int)0)
unsigned int vcop_sobelY_3x3_separable_uchar_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_sobelXy_3x3_L1_thresholding[22];

/* Basic Runner Function */
void vcop_sobelXy_3x3_L1_thresholding(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold);
/* Custom Runner Function */
void vcop_sobelXy_3x3_L1_thresholding_custom(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sobelXy_3x3_L1_thresholding_init(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sobelXy_3x3_L1_thresholding_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sobelXy_3x3_L1_thresholding ((unsigned int)22)
unsigned int vcop_sobelXy_3x3_L1_thresholding_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sobelXy_3x3_L1_thresholding ((unsigned int)0)
unsigned int vcop_sobelXy_3x3_L1_thresholding_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_sobelXy_3x3_L1_thresholding_binPack[24];

/* Basic Runner Function */
void vcop_sobelXy_3x3_L1_thresholding_binPack(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold);
/* Custom Runner Function */
void vcop_sobelXy_3x3_L1_thresholding_binPack_custom(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sobelXy_3x3_L1_thresholding_binPack_init(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sobelXy_3x3_L1_thresholding_binPack_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sobelXy_3x3_L1_thresholding_binPack ((unsigned int)24)
unsigned int vcop_sobelXy_3x3_L1_thresholding_binPack_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sobelXy_3x3_L1_thresholding_binPack ((unsigned int)0)
unsigned int vcop_sobelXy_3x3_L1_thresholding_binPack_ctrl_count(void);

/***********************************************************/
#endif

