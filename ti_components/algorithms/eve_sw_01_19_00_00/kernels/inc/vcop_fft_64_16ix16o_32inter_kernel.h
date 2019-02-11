#ifndef _TI_vcop_fft_64_16ix16o_32inter_kernel_h_
#define _TI_vcop_fft_64_16ix16o_32inter_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_32inter_stage_1[88];

/* Basic Runner Function */
void vcop_fft_64_32inter_stage_1(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pScratchWBuf,
   __vptr_uint16 pScratchWBuf16_lo,
   __vptr_int16 pScratchWBuf16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_64_32inter_stage_1_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pScratchWBuf,
   __vptr_uint16 pScratchWBuf16_lo,
   __vptr_int16 pScratchWBuf16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_32inter_stage_1_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pScratchWBuf,
   __vptr_uint16 pScratchWBuf16_lo,
   __vptr_int16 pScratchWBuf16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_32inter_stage_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_32inter_stage_1 ((unsigned int)88)
unsigned int vcop_fft_64_32inter_stage_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_32inter_stage_1 ((unsigned int)0)
unsigned int vcop_fft_64_32inter_stage_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_32inter_stage_2[86];

/* Basic Runner Function */
void vcop_fft_64_32inter_stage_2(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch116_lo,
   __vptr_int16 pScratch116_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch216_lo,
   __vptr_int16 pScratch216_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_64_32inter_stage_2_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch116_lo,
   __vptr_int16 pScratch116_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch216_lo,
   __vptr_int16 pScratch216_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_32inter_stage_2_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch116_lo,
   __vptr_int16 pScratch116_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch216_lo,
   __vptr_int16 pScratch216_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_32inter_stage_2_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_32inter_stage_2 ((unsigned int)86)
unsigned int vcop_fft_64_32inter_stage_2_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_32inter_stage_2 ((unsigned int)0)
unsigned int vcop_fft_64_32inter_stage_2_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16ix16o_32inter_stage_3_overflow[92];

/* Basic Runner Function */
void vcop_fft_64_16ix16o_32inter_stage_3_overflow(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_64_16ix16o_32inter_stage_3_overflow_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16ix16o_32inter_stage_3_overflow_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16ix16o_32inter_stage_3_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16ix16o_32inter_stage_3_overflow ((unsigned int)92)
unsigned int vcop_fft_64_16ix16o_32inter_stage_3_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16ix16o_32inter_stage_3_overflow ((unsigned int)0)
unsigned int vcop_fft_64_16ix16o_32inter_stage_3_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16ix16o_32inter_stage_3[56];

/* Basic Runner Function */
void vcop_fft_64_16ix16o_32inter_stage_3(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_64_16ix16o_32inter_stage_3_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16ix16o_32inter_stage_3_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16ix16o_32inter_stage_3_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16ix16o_32inter_stage_3 ((unsigned int)56)
unsigned int vcop_fft_64_16ix16o_32inter_stage_3_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16ix16o_32inter_stage_3 ((unsigned int)0)
unsigned int vcop_fft_64_16ix16o_32inter_stage_3_ctrl_count(void);

/***********************************************************/
#endif

