#ifndef _TI_vcop_chromaTLUIndexCalc_h_
#define _TI_vcop_chromaTLUIndexCalc_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_chromaTLUIndexCalcBilInterpolate[40];

/* Basic Runner Function */
void vcop_chromaTLUIndexCalcBilInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned char QShift);
/* Custom Runner Function */
void vcop_chromaTLUIndexCalcBilInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned char QShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_chromaTLUIndexCalcBilInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned char QShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_chromaTLUIndexCalcBilInterpolate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_chromaTLUIndexCalcBilInterpolate ((unsigned int)40)
unsigned int vcop_chromaTLUIndexCalcBilInterpolate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_chromaTLUIndexCalcBilInterpolate ((unsigned int)0)
unsigned int vcop_chromaTLUIndexCalcBilInterpolate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_chromaTLUIndexCalcNNInterpolate[34];

/* Basic Runner Function */
void vcop_chromaTLUIndexCalcNNInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint16 scatterStoreArrayUV);
/* Custom Runner Function */
void vcop_chromaTLUIndexCalcNNInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_chromaTLUIndexCalcNNInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_chromaTLUIndexCalcNNInterpolate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_chromaTLUIndexCalcNNInterpolate ((unsigned int)34)
unsigned int vcop_chromaTLUIndexCalcNNInterpolate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_chromaTLUIndexCalcNNInterpolate ((unsigned int)0)
unsigned int vcop_chromaTLUIndexCalcNNInterpolate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_chromaTLUIndexCalcBilInterpolateBB[42];

/* Basic Runner Function */
void vcop_chromaTLUIndexCalcBilInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   unsigned char QShift,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight);
/* Custom Runner Function */
void vcop_chromaTLUIndexCalcBilInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   unsigned char QShift,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_chromaTLUIndexCalcBilInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   unsigned char QShift,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_chromaTLUIndexCalcBilInterpolateBB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_chromaTLUIndexCalcBilInterpolateBB ((unsigned int)42)
unsigned int vcop_chromaTLUIndexCalcBilInterpolateBB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_chromaTLUIndexCalcBilInterpolateBB ((unsigned int)0)
unsigned int vcop_chromaTLUIndexCalcBilInterpolateBB_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_chromaTLUIndexCalcNNInterpolateBB[26];

/* Basic Runner Function */
void vcop_chromaTLUIndexCalcNNInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight);
/* Custom Runner Function */
void vcop_chromaTLUIndexCalcNNInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_chromaTLUIndexCalcNNInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_chromaTLUIndexCalcNNInterpolateBB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_chromaTLUIndexCalcNNInterpolateBB ((unsigned int)26)
unsigned int vcop_chromaTLUIndexCalcNNInterpolateBB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_chromaTLUIndexCalcNNInterpolateBB ((unsigned int)0)
unsigned int vcop_chromaTLUIndexCalcNNInterpolateBB_ctrl_count(void);

/***********************************************************/
#endif

