#ifndef _TI_vcop_fft_64_16ix32o_kernel_h_
#define _TI_vcop_fft_64_16ix32o_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16ix32o_stage_3_overflow[96];

/* Basic Runner Function */
void vcop_fft_64_16ix32o_stage_3_overflow(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_64_16ix32o_stage_3_overflow_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16ix32o_stage_3_overflow_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16ix32o_stage_3_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16ix32o_stage_3_overflow ((unsigned int)96)
unsigned int vcop_fft_64_16ix32o_stage_3_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16ix32o_stage_3_overflow ((unsigned int)0)
unsigned int vcop_fft_64_16ix32o_stage_3_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16ix32o_stage_3[54];

/* Basic Runner Function */
void vcop_fft_64_16ix32o_stage_3(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_64_16ix32o_stage_3_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16ix32o_stage_3_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16ix32o_stage_3_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16ix32o_stage_3 ((unsigned int)54)
unsigned int vcop_fft_64_16ix32o_stage_3_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16ix32o_stage_3 ((unsigned int)0)
unsigned int vcop_fft_64_16ix32o_stage_3_ctrl_count(void);

/***********************************************************/
#endif

