#ifndef _TI_vcop_clahe_generate_lut_kernel_h_
#define _TI_vcop_clahe_generate_lut_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_clahe_memset[10];

/* Basic Runner Function */
void vcop_clahe_memset(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size);
/* Custom Runner Function */
void vcop_clahe_memset_custom(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_clahe_memset_init(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_clahe_memset_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_clahe_memset ((unsigned int)10)
unsigned int vcop_clahe_memset_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_clahe_memset ((unsigned int)0)
unsigned int vcop_clahe_memset_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_clahe_histogram_8c_word[14];

/* Basic Runner Function */
void vcop_clahe_histogram_8c_word(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy);
/* Custom Runner Function */
void vcop_clahe_histogram_8c_word_custom(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_clahe_histogram_8c_word_init(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_clahe_histogram_8c_word_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_clahe_histogram_8c_word ((unsigned int)14)
unsigned int vcop_clahe_histogram_8c_word_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_clahe_histogram_8c_word ((unsigned int)0)
unsigned int vcop_clahe_histogram_8c_word_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_clahe_histogram_8c_word_sum[24];

/* Basic Runner Function */
void vcop_clahe_histogram_8c_word_sum(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram);
/* Custom Runner Function */
void vcop_clahe_histogram_8c_word_sum_custom(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_clahe_histogram_8c_word_sum_init(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_clahe_histogram_8c_word_sum_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_clahe_histogram_8c_word_sum ((unsigned int)24)
unsigned int vcop_clahe_histogram_8c_word_sum_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_clahe_histogram_8c_word_sum ((unsigned int)0)
unsigned int vcop_clahe_histogram_8c_word_sum_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_clahe_clip_hist[42];

/* Basic Runner Function */
void vcop_clahe_clip_hist(
   __vptr_uint32 histogram,
   __vptr_uint32 scratch,
   __vptr_uint16 residual,
   __vptr_uint16 clipDist,
   __vptr_uint16 enableResidual,
   unsigned short histSize,
   unsigned short clipValue);
/* Custom Runner Function */
void vcop_clahe_clip_hist_custom(
   __vptr_uint32 histogram,
   __vptr_uint32 scratch,
   __vptr_uint16 residual,
   __vptr_uint16 clipDist,
   __vptr_uint16 enableResidual,
   unsigned short histSize,
   unsigned short clipValue,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_clahe_clip_hist_init(
   __vptr_uint32 histogram,
   __vptr_uint32 scratch,
   __vptr_uint16 residual,
   __vptr_uint16 clipDist,
   __vptr_uint16 enableResidual,
   unsigned short histSize,
   unsigned short clipValue,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_clahe_clip_hist_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_clahe_clip_hist ((unsigned int)42)
unsigned int vcop_clahe_clip_hist_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_clahe_clip_hist ((unsigned int)0)
unsigned int vcop_clahe_clip_hist_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_clahe_generate_lut[34];

/* Basic Runner Function */
void vcop_clahe_generate_lut(
   __vptr_uint32 histogram,
   __vptr_uint8 lut,
   unsigned short scaleValue,
   unsigned short histSize,
   unsigned short clipDist,
   unsigned short residual,
   unsigned short ebaleResidual);
/* Custom Runner Function */
void vcop_clahe_generate_lut_custom(
   __vptr_uint32 histogram,
   __vptr_uint8 lut,
   unsigned short scaleValue,
   unsigned short histSize,
   unsigned short clipDist,
   unsigned short residual,
   unsigned short ebaleResidual,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_clahe_generate_lut_init(
   __vptr_uint32 histogram,
   __vptr_uint8 lut,
   unsigned short scaleValue,
   unsigned short histSize,
   unsigned short clipDist,
   unsigned short residual,
   unsigned short ebaleResidual,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_clahe_generate_lut_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_clahe_generate_lut ((unsigned int)34)
unsigned int vcop_clahe_generate_lut_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_clahe_generate_lut ((unsigned int)0)
unsigned int vcop_clahe_generate_lut_ctrl_count(void);

/***********************************************************/
#endif

