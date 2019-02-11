#ifndef _TI_vcop_alpha_blend_yuv422i_kernel_h_
#define _TI_vcop_alpha_blend_yuv422i_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_alpha_blend_yuv422i[22];

/* Basic Runner Function */
void vcop_alpha_blend_yuv422i(
   __vptr_uint8 in_img1_X,
   __vptr_uint8 in_img2_X,
   __vptr_uint8 alphaFrame_X,
   __vptr_uint8 out_X,
   unsigned short width,
   unsigned short height,
   unsigned short in_img1_stride,
   unsigned short in_img2_stride,
   unsigned short out_stride);
/* Custom Runner Function */
void vcop_alpha_blend_yuv422i_custom(
   __vptr_uint8 in_img1_X,
   __vptr_uint8 in_img2_X,
   __vptr_uint8 alphaFrame_X,
   __vptr_uint8 out_X,
   unsigned short width,
   unsigned short height,
   unsigned short in_img1_stride,
   unsigned short in_img2_stride,
   unsigned short out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_alpha_blend_yuv422i_init(
   __vptr_uint8 in_img1_X,
   __vptr_uint8 in_img2_X,
   __vptr_uint8 alphaFrame_X,
   __vptr_uint8 out_X,
   unsigned short width,
   unsigned short height,
   unsigned short in_img1_stride,
   unsigned short in_img2_stride,
   unsigned short out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_alpha_blend_yuv422i_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_alpha_blend_yuv422i ((unsigned int)22)
unsigned int vcop_alpha_blend_yuv422i_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_alpha_blend_yuv422i ((unsigned int)0)
unsigned int vcop_alpha_blend_yuv422i_ctrl_count(void);

/***********************************************************/
#endif

