#ifndef _TI_vcop_fft_128_16ix32o_kernel_h_
#define _TI_vcop_fft_128_16ix32o_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_128_16ix32o_radix2_stage_4_overflow[78];

/* Basic Runner Function */
void vcop_fft_128_16ix32o_radix2_stage_4_overflow(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_128_16ix32o_radix2_stage_4_overflow_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_128_16ix32o_radix2_stage_4_overflow_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_128_16ix32o_radix2_stage_4_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_128_16ix32o_radix2_stage_4_overflow ((unsigned int)78)
unsigned int vcop_fft_128_16ix32o_radix2_stage_4_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_128_16ix32o_radix2_stage_4_overflow ((unsigned int)0)
unsigned int vcop_fft_128_16ix32o_radix2_stage_4_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_128_16ix32o_radix2_stage_4[38];

/* Basic Runner Function */
void vcop_fft_128_16ix32o_radix2_stage_4(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_128_16ix32o_radix2_stage_4_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_128_16ix32o_radix2_stage_4_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_128_16ix32o_radix2_stage_4_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_128_16ix32o_radix2_stage_4 ((unsigned int)38)
unsigned int vcop_fft_128_16ix32o_radix2_stage_4_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_128_16ix32o_radix2_stage_4 ((unsigned int)0)
unsigned int vcop_fft_128_16ix32o_radix2_stage_4_ctrl_count(void);

/***********************************************************/
#endif

