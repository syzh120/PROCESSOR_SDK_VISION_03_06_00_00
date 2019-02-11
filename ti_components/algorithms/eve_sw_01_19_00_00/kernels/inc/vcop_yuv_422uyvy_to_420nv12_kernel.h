#ifndef _TI_vcop_yuv_422uyvy_to_420nv12_kernel_h_
#define _TI_vcop_yuv_422uyvy_to_420nv12_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_yuv_422uyvy_to_420nv12[20];

/* Basic Runner Function */
void vcop_yuv_422uyvy_to_420nv12(
   __vptr_uint8 in_img_A,
   __vptr_uint8 out_B,
   unsigned short width,
   unsigned short height,
   unsigned short in_stride,
   unsigned short out_stride);
/* Custom Runner Function */
void vcop_yuv_422uyvy_to_420nv12_custom(
   __vptr_uint8 in_img_A,
   __vptr_uint8 out_B,
   unsigned short width,
   unsigned short height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_yuv_422uyvy_to_420nv12_init(
   __vptr_uint8 in_img_A,
   __vptr_uint8 out_B,
   unsigned short width,
   unsigned short height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_yuv_422uyvy_to_420nv12_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_yuv_422uyvy_to_420nv12 ((unsigned int)20)
unsigned int vcop_yuv_422uyvy_to_420nv12_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_yuv_422uyvy_to_420nv12 ((unsigned int)0)
unsigned int vcop_yuv_422uyvy_to_420nv12_ctrl_count(void);

/***********************************************************/
#endif

