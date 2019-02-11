#ifndef _TI_vcop_fft_64_16ix16o_kernel_overflow_h_
#define _TI_vcop_fft_64_16ix16o_kernel_overflow_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16ix16o_stage_1_overflow[126];

/* Basic Runner Function */
void vcop_fft_64_16ix16o_stage_1_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_64_16ix16o_stage_1_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16ix16o_stage_1_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16ix16o_stage_1_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16ix16o_stage_1_overflow ((unsigned int)126)
unsigned int vcop_fft_64_16ix16o_stage_1_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16ix16o_stage_1_overflow ((unsigned int)0)
unsigned int vcop_fft_64_16ix16o_stage_1_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16ix16o_stage_2_overflow[116];

/* Basic Runner Function */
void vcop_fft_64_16ix16o_stage_2_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_64_16ix16o_stage_2_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16ix16o_stage_2_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16ix16o_stage_2_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16ix16o_stage_2_overflow ((unsigned int)116)
unsigned int vcop_fft_64_16ix16o_stage_2_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16ix16o_stage_2_overflow ((unsigned int)0)
unsigned int vcop_fft_64_16ix16o_stage_2_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16ix16o_stage_3_overflow[86];

/* Basic Runner Function */
void vcop_fft_64_16ix16o_stage_3_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_64_16ix16o_stage_3_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16ix16o_stage_3_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16ix16o_stage_3_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16ix16o_stage_3_overflow ((unsigned int)86)
unsigned int vcop_fft_64_16ix16o_stage_3_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16ix16o_stage_3_overflow ((unsigned int)0)
unsigned int vcop_fft_64_16ix16o_stage_3_overflow_ctrl_count(void);

/***********************************************************/
#endif

