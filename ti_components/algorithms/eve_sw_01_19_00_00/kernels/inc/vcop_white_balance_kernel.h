#ifndef _TI_vcop_white_balance_kernel_h_
#define _TI_vcop_white_balance_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_white_balance_BGGR[24];

/* Basic Runner Function */
void vcop_white_balance_BGGR(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride);
/* Custom Runner Function */
void vcop_white_balance_BGGR_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_white_balance_BGGR_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_white_balance_BGGR_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_white_balance_BGGR ((unsigned int)24)
unsigned int vcop_white_balance_BGGR_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_white_balance_BGGR ((unsigned int)0)
unsigned int vcop_white_balance_BGGR_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_white_balance_GBRG[24];

/* Basic Runner Function */
void vcop_white_balance_GBRG(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride);
/* Custom Runner Function */
void vcop_white_balance_GBRG_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_white_balance_GBRG_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_white_balance_GBRG_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_white_balance_GBRG ((unsigned int)24)
unsigned int vcop_white_balance_GBRG_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_white_balance_GBRG ((unsigned int)0)
unsigned int vcop_white_balance_GBRG_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_white_balance_GRBG[24];

/* Basic Runner Function */
void vcop_white_balance_GRBG(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride);
/* Custom Runner Function */
void vcop_white_balance_GRBG_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_white_balance_GRBG_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_white_balance_GRBG_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_white_balance_GRBG ((unsigned int)24)
unsigned int vcop_white_balance_GRBG_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_white_balance_GRBG ((unsigned int)0)
unsigned int vcop_white_balance_GRBG_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_white_balance_RGGB[24];

/* Basic Runner Function */
void vcop_white_balance_RGGB(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride);
/* Custom Runner Function */
void vcop_white_balance_RGGB_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_white_balance_RGGB_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_white_balance_RGGB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_white_balance_RGGB ((unsigned int)24)
unsigned int vcop_white_balance_RGGB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_white_balance_RGGB ((unsigned int)0)
unsigned int vcop_white_balance_RGGB_ctrl_count(void);

/***********************************************************/
#endif

