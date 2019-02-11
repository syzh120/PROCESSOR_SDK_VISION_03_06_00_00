#ifndef _TI_vcop_contrast_stretching_kernel_h_
#define _TI_vcop_contrast_stretching_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_memset[10];

/* Basic Runner Function */
void vcop_memset(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size);
/* Custom Runner Function */
void vcop_memset_custom(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_memset_init(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_memset_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_memset ((unsigned int)10)
unsigned int vcop_memset_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_memset ((unsigned int)0)
unsigned int vcop_memset_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_histogram_8c_word[14];

/* Basic Runner Function */
void vcop_histogram_8c_word(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy);
/* Custom Runner Function */
void vcop_histogram_8c_word_custom(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_histogram_8c_word_init(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_histogram_8c_word_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_histogram_8c_word ((unsigned int)14)
unsigned int vcop_histogram_8c_word_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_histogram_8c_word ((unsigned int)0)
unsigned int vcop_histogram_8c_word_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_contrast_stretching[22];

/* Basic Runner Function */
void vcop_contrast_stretching(
   __vptr_uint8 inputImage,
   __vptr_uint8 outputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned char minVal,
   unsigned short scaleFactorQ16);
/* Custom Runner Function */
void vcop_contrast_stretching_custom(
   __vptr_uint8 inputImage,
   __vptr_uint8 outputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned char minVal,
   unsigned short scaleFactorQ16,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_contrast_stretching_init(
   __vptr_uint8 inputImage,
   __vptr_uint8 outputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned char minVal,
   unsigned short scaleFactorQ16,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_contrast_stretching_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_contrast_stretching ((unsigned int)22)
unsigned int vcop_contrast_stretching_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_contrast_stretching ((unsigned int)0)
unsigned int vcop_contrast_stretching_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_histogram_8c_word_sum[24];

/* Basic Runner Function */
void vcop_histogram_8c_word_sum(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram);
/* Custom Runner Function */
void vcop_histogram_8c_word_sum_custom(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_histogram_8c_word_sum_init(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_histogram_8c_word_sum_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_histogram_8c_word_sum ((unsigned int)24)
unsigned int vcop_histogram_8c_word_sum_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_histogram_8c_word_sum ((unsigned int)0)
unsigned int vcop_histogram_8c_word_sum_ctrl_count(void);

/***********************************************************/
#endif

