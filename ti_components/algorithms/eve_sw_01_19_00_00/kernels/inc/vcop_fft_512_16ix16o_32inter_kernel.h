#ifndef _TI_vcop_fft_512_16ix16o_32inter_kernel_h_
#define _TI_vcop_fft_512_16ix16o_32inter_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_32inter_stage_1[64];

/* Basic Runner Function */
void vcop_fft_512_32inter_stage_1(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_uint16 pScratchWBUF16_lo,
   __vptr_int16 pScratchWBUF16_hi,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_512_32inter_stage_1_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_uint16 pScratchWBUF16_lo,
   __vptr_int16 pScratchWBUF16_hi,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_32inter_stage_1_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_uint16 pScratchWBUF16_lo,
   __vptr_int16 pScratchWBUF16_hi,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_32inter_stage_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_32inter_stage_1 ((unsigned int)64)
unsigned int vcop_fft_512_32inter_stage_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_32inter_stage_1 ((unsigned int)0)
unsigned int vcop_fft_512_32inter_stage_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_32inter_stage_2[86];

/* Basic Runner Function */
void vcop_fft_512_32inter_stage_2(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_512_32inter_stage_2_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_32inter_stage_2_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_32inter_stage_2_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_32inter_stage_2 ((unsigned int)86)
unsigned int vcop_fft_512_32inter_stage_2_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_32inter_stage_2 ((unsigned int)0)
unsigned int vcop_fft_512_32inter_stage_2_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_32inter_stage_3[88];

/* Basic Runner Function */
void vcop_fft_512_32inter_stage_3(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_512_32inter_stage_3_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_32inter_stage_3_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_32inter_stage_3_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_32inter_stage_3 ((unsigned int)88)
unsigned int vcop_fft_512_32inter_stage_3_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_32inter_stage_3 ((unsigned int)0)
unsigned int vcop_fft_512_32inter_stage_3_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_32inter_stage_4[90];

/* Basic Runner Function */
void vcop_fft_512_32inter_stage_4(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_512_32inter_stage_4_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_32inter_stage_4_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_32inter_stage_4_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_32inter_stage_4 ((unsigned int)90)
unsigned int vcop_fft_512_32inter_stage_4_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_32inter_stage_4 ((unsigned int)0)
unsigned int vcop_fft_512_32inter_stage_4_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow[78];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow ((unsigned int)78)
unsigned int vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_32inter_radix2_stage_5[42];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_32inter_radix2_stage_5(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_32inter_radix2_stage_5_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_32inter_radix2_stage_5_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_32inter_radix2_stage_5_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_32inter_radix2_stage_5 ((unsigned int)42)
unsigned int vcop_fft_512_16ix16o_32inter_radix2_stage_5_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_32inter_radix2_stage_5 ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_32inter_radix2_stage_5_ctrl_count(void);

/***********************************************************/
#endif

