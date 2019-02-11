#ifndef _TI_vcop_dsTLUindexAndFrac_h_
#define _TI_vcop_dsTLUindexAndFrac_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_dsTLUindexAndFracBilInterpolate[74];

/* Basic Runner Function */
void vcop_dsTLUindexAndFracBilInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift);
/* Custom Runner Function */
void vcop_dsTLUindexAndFracBilInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dsTLUindexAndFracBilInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dsTLUindexAndFracBilInterpolate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dsTLUindexAndFracBilInterpolate ((unsigned int)74)
unsigned int vcop_dsTLUindexAndFracBilInterpolate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dsTLUindexAndFracBilInterpolate ((unsigned int)0)
unsigned int vcop_dsTLUindexAndFracBilInterpolate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_dsTLUindexAndFracNNInterpolate[48];

/* Basic Runner Function */
void vcop_dsTLUindexAndFracNNInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   unsigned char stride,
   unsigned char QShift);
/* Custom Runner Function */
void vcop_dsTLUindexAndFracNNInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   unsigned char stride,
   unsigned char QShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dsTLUindexAndFracNNInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   unsigned char stride,
   unsigned char QShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dsTLUindexAndFracNNInterpolate_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dsTLUindexAndFracNNInterpolate ((unsigned int)48)
unsigned int vcop_dsTLUindexAndFracNNInterpolate_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dsTLUindexAndFracNNInterpolate ((unsigned int)0)
unsigned int vcop_dsTLUindexAndFracNNInterpolate_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_dsTLUindexAndFracBilInterpolateBB[34];

/* Basic Runner Function */
void vcop_dsTLUindexAndFracBilInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short outputBlockSize);
/* Custom Runner Function */
void vcop_dsTLUindexAndFracBilInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dsTLUindexAndFracBilInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dsTLUindexAndFracBilInterpolateBB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dsTLUindexAndFracBilInterpolateBB ((unsigned int)34)
unsigned int vcop_dsTLUindexAndFracBilInterpolateBB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dsTLUindexAndFracBilInterpolateBB ((unsigned int)0)
unsigned int vcop_dsTLUindexAndFracBilInterpolateBB_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_dsTLUindexAndFracNNInterpolateBB[24];

/* Basic Runner Function */
void vcop_dsTLUindexAndFracNNInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   unsigned short outputBlockSize);
/* Custom Runner Function */
void vcop_dsTLUindexAndFracNNInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dsTLUindexAndFracNNInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dsTLUindexAndFracNNInterpolateBB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dsTLUindexAndFracNNInterpolateBB ((unsigned int)24)
unsigned int vcop_dsTLUindexAndFracNNInterpolateBB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dsTLUindexAndFracNNInterpolateBB ((unsigned int)0)
unsigned int vcop_dsTLUindexAndFracNNInterpolateBB_ctrl_count(void);

/***********************************************************/
#endif

