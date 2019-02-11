#ifndef _TI_vcop_rgb_to_yuv_kernel_h_
#define _TI_vcop_rgb_to_yuv_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_rgb_to_yuv_UYVY[32];

/* Basic Runner Function */
void rgb_to_yuv_UYVY(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 rgb2yuv_coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut);
/* Custom Runner Function */
void rgb_to_yuv_UYVY_custom(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 rgb2yuv_coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int rgb_to_yuv_UYVY_init(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 rgb2yuv_coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void rgb_to_yuv_UYVY_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_rgb_to_yuv_UYVY ((unsigned int)32)
unsigned int rgb_to_yuv_UYVY_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_rgb_to_yuv_UYVY ((unsigned int)0)
unsigned int rgb_to_yuv_UYVY_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_rgb_to_yuv_YUYV[32];

/* Basic Runner Function */
void rgb_to_yuv_YUYV(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut);
/* Custom Runner Function */
void rgb_to_yuv_YUYV_custom(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int rgb_to_yuv_YUYV_init(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void rgb_to_yuv_YUYV_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_rgb_to_yuv_YUYV ((unsigned int)32)
unsigned int rgb_to_yuv_YUYV_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_rgb_to_yuv_YUYV ((unsigned int)0)
unsigned int rgb_to_yuv_YUYV_ctrl_count(void);

/***********************************************************/
#endif

