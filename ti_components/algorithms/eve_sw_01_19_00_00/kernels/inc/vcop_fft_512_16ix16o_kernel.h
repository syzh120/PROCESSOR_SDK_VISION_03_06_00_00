#ifndef _TI_vcop_fft_512_16ix16o_kernel_h_
#define _TI_vcop_fft_512_16ix16o_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_1[38];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_1(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_1_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_1_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_1 ((unsigned int)38)
unsigned int vcop_fft_512_16ix16o_stage_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_1 ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_2[38];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_2(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_2_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_2_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_2_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_2 ((unsigned int)38)
unsigned int vcop_fft_512_16ix16o_stage_2_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_2 ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_2_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_3[50];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_3(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_3_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_3_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_3_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_3 ((unsigned int)50)
unsigned int vcop_fft_512_16ix16o_stage_3_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_3 ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_3_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_stage_4[40];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_stage_4(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_stage_4_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_stage_4_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_stage_4_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_stage_4 ((unsigned int)40)
unsigned int vcop_fft_512_16ix16o_stage_4_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_stage_4 ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_stage_4_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_512_16ix16o_radix2_stage_5[24];

/* Basic Runner Function */
void vcop_fft_512_16ix16o_radix2_stage_5(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_512_16ix16o_radix2_stage_5_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_512_16ix16o_radix2_stage_5_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_512_16ix16o_radix2_stage_5_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_512_16ix16o_radix2_stage_5 ((unsigned int)24)
unsigned int vcop_fft_512_16ix16o_radix2_stage_5_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_512_16ix16o_radix2_stage_5 ((unsigned int)0)
unsigned int vcop_fft_512_16ix16o_radix2_stage_5_ctrl_count(void);

/***********************************************************/
#endif

