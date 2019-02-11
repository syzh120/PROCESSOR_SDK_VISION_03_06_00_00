#ifndef _TI_vcop_BayerCFA_interpolate_kernel_h_
#define _TI_vcop_BayerCFA_interpolate_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_BayerCFA_interpolate_short_BGGR[76];

/* Basic Runner Function */
void vcop_BayerCFA_interpolate_short_BGGR(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride);
/* Custom Runner Function */
void vcop_BayerCFA_interpolate_short_BGGR_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_BayerCFA_interpolate_short_BGGR_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_BayerCFA_interpolate_short_BGGR_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_BayerCFA_interpolate_short_BGGR ((unsigned int)76)
unsigned int vcop_BayerCFA_interpolate_short_BGGR_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_BayerCFA_interpolate_short_BGGR ((unsigned int)0)
unsigned int vcop_BayerCFA_interpolate_short_BGGR_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_BayerCFA_interpolate_short_GRBG[76];

/* Basic Runner Function */
void vcop_BayerCFA_interpolate_short_GRBG(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride);
/* Custom Runner Function */
void vcop_BayerCFA_interpolate_short_GRBG_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_BayerCFA_interpolate_short_GRBG_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_BayerCFA_interpolate_short_GRBG_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_BayerCFA_interpolate_short_GRBG ((unsigned int)76)
unsigned int vcop_BayerCFA_interpolate_short_GRBG_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_BayerCFA_interpolate_short_GRBG ((unsigned int)0)
unsigned int vcop_BayerCFA_interpolate_short_GRBG_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_BayerCFA_interpolate_short_RGGB[76];

/* Basic Runner Function */
void vcop_BayerCFA_interpolate_short_RGGB(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride);
/* Custom Runner Function */
void vcop_BayerCFA_interpolate_short_RGGB_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_BayerCFA_interpolate_short_RGGB_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_BayerCFA_interpolate_short_RGGB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_BayerCFA_interpolate_short_RGGB ((unsigned int)76)
unsigned int vcop_BayerCFA_interpolate_short_RGGB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_BayerCFA_interpolate_short_RGGB ((unsigned int)0)
unsigned int vcop_BayerCFA_interpolate_short_RGGB_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_BayerCFA_interpolate_short_GBRG[76];

/* Basic Runner Function */
void vcop_BayerCFA_interpolate_short_GBRG(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride);
/* Custom Runner Function */
void vcop_BayerCFA_interpolate_short_GBRG_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_BayerCFA_interpolate_short_GBRG_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_BayerCFA_interpolate_short_GBRG_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_BayerCFA_interpolate_short_GBRG ((unsigned int)76)
unsigned int vcop_BayerCFA_interpolate_short_GBRG_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_BayerCFA_interpolate_short_GBRG ((unsigned int)0)
unsigned int vcop_BayerCFA_interpolate_short_GBRG_ctrl_count(void);

/***********************************************************/
#endif

