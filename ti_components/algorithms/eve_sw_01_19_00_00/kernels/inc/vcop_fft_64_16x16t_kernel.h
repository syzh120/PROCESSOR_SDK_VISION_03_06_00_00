#ifndef _TI_vcop_fft_64_16x16t_kernel_h_
#define _TI_vcop_fft_64_16x16t_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16x16t_stage_1[120];

/* Basic Runner Function */
void vcop_fft_64_16x16t_stage_1(
   __vptr_int16_arr Pxi0,
   __vptr_int16_arr Pxi1,
   __vptr_int16_arr Pxi2,
   __vptr_int16_arr Pxi3,
   __vptr_int16_arr PCS1,
   __vptr_int16_arr PCS2,
   __vptr_int16_arr PCS3,
   unsigned short bfys_per_grp[],
   unsigned short grps[],
   unsigned short passes,
   unsigned short pinc3[],
   unsigned short pinc4[],
   unsigned short ptnc3[],
   unsigned short ptnc4[]);
/* Custom Runner Function */
void vcop_fft_64_16x16t_stage_1_custom(
   __vptr_int16_arr Pxi0,
   __vptr_int16_arr Pxi1,
   __vptr_int16_arr Pxi2,
   __vptr_int16_arr Pxi3,
   __vptr_int16_arr PCS1,
   __vptr_int16_arr PCS2,
   __vptr_int16_arr PCS3,
   unsigned short bfys_per_grp[],
   unsigned short grps[],
   unsigned short passes,
   unsigned short pinc3[],
   unsigned short pinc4[],
   unsigned short ptnc3[],
   unsigned short ptnc4[],
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16x16t_stage_1_init(
   __vptr_int16_arr Pxi0,
   __vptr_int16_arr Pxi1,
   __vptr_int16_arr Pxi2,
   __vptr_int16_arr Pxi3,
   __vptr_int16_arr PCS1,
   __vptr_int16_arr PCS2,
   __vptr_int16_arr PCS3,
   unsigned short bfys_per_grp[],
   unsigned short grps[],
   unsigned short passes,
   unsigned short pinc3[],
   unsigned short pinc4[],
   unsigned short ptnc3[],
   unsigned short ptnc4[],
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16x16t_stage_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16x16t_stage_1 ((unsigned int)120)
unsigned int vcop_fft_64_16x16t_stage_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16x16t_stage_1 ((unsigned int)1)
unsigned int vcop_fft_64_16x16t_stage_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16x16t_stage2[24];

/* Basic Runner Function */
void vcop_fft_64_16x16t_stage2(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   __vptr_int16 PCS1,
   __vptr_int16 PCS2,
   __vptr_int16 PCS3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short ptnc3,
   unsigned short ptnc4);
/* Custom Runner Function */
void vcop_fft_64_16x16t_stage2_custom(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   __vptr_int16 PCS1,
   __vptr_int16 PCS2,
   __vptr_int16 PCS3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short ptnc3,
   unsigned short ptnc4,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16x16t_stage2_init(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   __vptr_int16 PCS1,
   __vptr_int16 PCS2,
   __vptr_int16 PCS3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short ptnc3,
   unsigned short ptnc4,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16x16t_stage2_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16x16t_stage2 ((unsigned int)24)
unsigned int vcop_fft_64_16x16t_stage2_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16x16t_stage2 ((unsigned int)0)
unsigned int vcop_fft_64_16x16t_stage2_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_64_16x16t_stage3[16];

/* Basic Runner Function */
void vcop_fft_64_16x16t_stage3(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4);
/* Custom Runner Function */
void vcop_fft_64_16x16t_stage3_custom(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_64_16x16t_stage3_init(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_64_16x16t_stage3_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_64_16x16t_stage3 ((unsigned int)16)
unsigned int vcop_fft_64_16x16t_stage3_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_64_16x16t_stage3 ((unsigned int)0)
unsigned int vcop_fft_64_16x16t_stage3_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_digit_rev_64[16];

/* Basic Runner Function */
void vcop_fft_digit_rev_64(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py);
/* Custom Runner Function */
void vcop_fft_digit_rev_64_custom(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_digit_rev_64_init(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_digit_rev_64_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_digit_rev_64 ((unsigned int)16)
unsigned int vcop_fft_digit_rev_64_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_digit_rev_64 ((unsigned int)0)
unsigned int vcop_fft_digit_rev_64_ctrl_count(void);

/***********************************************************/
#endif

