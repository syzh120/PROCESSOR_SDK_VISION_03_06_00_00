#ifndef _TI_vcop_fft_512_16ix16o_kernel_overflow_h_
#define _TI_vcop_fft_512_16ix16o_kernel_overflow_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_1_overflow[114];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_1_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_int32 pScratchH,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_1_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_int32 pScratchH,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_1_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_int32 pScratchH,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_1_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_1_overflow ((unsigned int)114)
unsigned int vcop_fft_512_16ix16o_stage_1_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_1_overflow ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_1_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_2_overflow[108];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_2_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_2_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_2_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_2_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_2_overflow ((unsigned int)108)
unsigned int vcop_fft_512_16ix16o_stage_2_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_2_overflow ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_2_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_3_overflow[118];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_3_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_3_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_3_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_3_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_3_overflow ((unsigned int)118)
unsigned int vcop_fft_512_16ix16o_stage_3_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_3_overflow ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_3_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_4_overflow[116];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_4_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_4_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_4_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_4_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_4_overflow ((unsigned int)116)
unsigned int vcop_fft_512_16ix16o_stage_4_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_4_overflow ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_4_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_radix2_stage_5_overflow[76];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_radix2_stage_5_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_radix2_stage_5_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_radix2_stage_5_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_radix2_stage_5_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_radix2_stage_5_overflow ((unsigned int)76)
unsigned int vcop_fft_512_16ix16o_radix2_stage_5_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_radix2_stage_5_overflow ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_radix2_stage_5_overflow_ctrl_count(void);

/***********************************************************/
#endif

