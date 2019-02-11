#ifndef _TI_vcop_fft_N_16x16t_kernel_h_
#define _TI_vcop_fft_N_16x16t_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_N_16x16t_stages_initial[120];

/* Basic Runner Function */
void vcop_fft_N_16x16t_stages_initial(
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
void vcop_fft_N_16x16t_stages_initial_custom(
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
unsigned int vcop_fft_N_16x16t_stages_initial_init(
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
void vcop_fft_N_16x16t_stages_initial_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_N_16x16t_stages_initial ((unsigned int)120)
unsigned int vcop_fft_N_16x16t_stages_initial_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_N_16x16t_stages_initial ((unsigned int)1)
unsigned int vcop_fft_N_16x16t_stages_initial_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_N_16x16t_stage_2ndLast[24];

/* Basic Runner Function */
void vcop_fft_N_16x16t_stage_2ndLast(
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
void vcop_fft_N_16x16t_stage_2ndLast_custom(
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
unsigned int vcop_fft_N_16x16t_stage_2ndLast_init(
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
void vcop_fft_N_16x16t_stage_2ndLast_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_N_16x16t_stage_2ndLast ((unsigned int)24)
unsigned int vcop_fft_N_16x16t_stage_2ndLast_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_N_16x16t_stage_2ndLast ((unsigned int)0)
unsigned int vcop_fft_N_16x16t_stage_2ndLast_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_N_16x16t_stage_Last[16];

/* Basic Runner Function */
void vcop_fft_N_16x16t_stage_Last(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4);
/* Custom Runner Function */
void vcop_fft_N_16x16t_stage_Last_custom(
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
unsigned int vcop_fft_N_16x16t_stage_Last_init(
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
void vcop_fft_N_16x16t_stage_Last_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_N_16x16t_stage_Last ((unsigned int)16)
unsigned int vcop_fft_N_16x16t_stage_Last_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_N_16x16t_stage_Last ((unsigned int)0)
unsigned int vcop_fft_N_16x16t_stage_Last_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_digit_rev_N[16];

/* Basic Runner Function */
void vcop_fft_digit_rev_N(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py,
   unsigned short N);
/* Custom Runner Function */
void vcop_fft_digit_rev_N_custom(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py,
   unsigned short N,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_digit_rev_N_init(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py,
   unsigned short N,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_digit_rev_N_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_digit_rev_N ((unsigned int)16)
unsigned int vcop_fft_digit_rev_N_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_digit_rev_N ((unsigned int)0)
unsigned int vcop_fft_digit_rev_N_ctrl_count(void);

/***********************************************************/
#endif

