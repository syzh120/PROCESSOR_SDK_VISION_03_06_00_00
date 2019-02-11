#ifndef _TI_vcop_fft_512_16ix32o_kernel_h_
#define _TI_vcop_fft_512_16ix32o_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix32o_radix2_stage_5_overflow[80];

/* Basic Runner Function */
void vcop_fft_512_16ix32o_radix2_stage_5_overflow(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_512_16ix32o_radix2_stage_5_overflow_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix32o_radix2_stage_5_overflow_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix32o_radix2_stage_5_overflow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix32o_radix2_stage_5_overflow ((unsigned int)80)
unsigned int vcop_fft_512_16ix32o_radix2_stage_5_overflow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix32o_radix2_stage_5_overflow ((unsigned int)0)
unsigned int vcop_fft_512_16ix32o_radix2_stage_5_overflow_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix32o_radix2_stage_5[40];

/* Basic Runner Function */
void vcop_fft_512_16ix32o_radix2_stage_5(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_512_16ix32o_radix2_stage_5_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix32o_radix2_stage_5_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix32o_radix2_stage_5_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix32o_radix2_stage_5 ((unsigned int)40)
unsigned int vcop_fft_512_16ix32o_radix2_stage_5_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix32o_radix2_stage_5 ((unsigned int)0)
unsigned int vcop_fft_512_16ix32o_radix2_stage_5_ctrl_count(void);

/***********************************************************/
#endif

