#ifndef _TI_vcop_rotate_kernel_h_
#define _TI_vcop_rotate_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_rotate_90[28];

/* Basic Runner Function */
void vcop_rotate_90(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift);
/* Custom Runner Function */
void vcop_rotate_90_custom(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rotate_90_init(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rotate_90_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rotate_90 ((unsigned int)28)
unsigned int vcop_rotate_90_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rotate_90 ((unsigned int)0)
unsigned int vcop_rotate_90_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_rotate_180[14];

/* Basic Runner Function */
void vcop_rotate_180(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift);
/* Custom Runner Function */
void vcop_rotate_180_custom(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rotate_180_init(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rotate_180_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rotate_180 ((unsigned int)14)
unsigned int vcop_rotate_180_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rotate_180 ((unsigned int)0)
unsigned int vcop_rotate_180_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_rotate_270[24];

/* Basic Runner Function */
void vcop_rotate_270(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift);
/* Custom Runner Function */
void vcop_rotate_270_custom(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rotate_270_init(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rotate_270_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rotate_270 ((unsigned int)24)
unsigned int vcop_rotate_270_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rotate_270 ((unsigned int)0)
unsigned int vcop_rotate_270_ctrl_count(void);

/***********************************************************/
#endif

