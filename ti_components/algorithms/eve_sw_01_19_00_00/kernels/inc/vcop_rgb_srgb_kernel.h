#ifndef _TI_vcop_rgb_srgb_kernel_h_
#define _TI_vcop_rgb_srgb_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_rgb_to_srgb[42];

/* Basic Runner Function */
void rgb_to_srgb(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   __vptr_uint16 oPtrR,
   __vptr_uint16 oPtrG,
   __vptr_uint16 oPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_int16 rgb2srgb_coefs);
/* Custom Runner Function */
void rgb_to_srgb_custom(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   __vptr_uint16 oPtrR,
   __vptr_uint16 oPtrG,
   __vptr_uint16 oPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_int16 rgb2srgb_coefs,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int rgb_to_srgb_init(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   __vptr_uint16 oPtrR,
   __vptr_uint16 oPtrG,
   __vptr_uint16 oPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_int16 rgb2srgb_coefs,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void rgb_to_srgb_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_rgb_to_srgb ((unsigned int)42)
unsigned int rgb_to_srgb_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_rgb_to_srgb ((unsigned int)0)
unsigned int rgb_to_srgb_ctrl_count(void);

/***********************************************************/
#endif

