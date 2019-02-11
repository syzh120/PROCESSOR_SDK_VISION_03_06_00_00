#ifndef _TI_vcop_vec_bin_image_dilate_square_kernel_h_
#define _TI_vcop_vec_bin_image_dilate_square_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_bin_image_dilate_square[28];

/* Basic Runner Function */
void vcop_vec_bin_image_dilate_square(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height);
/* Custom Runner Function */
void vcop_vec_bin_image_dilate_square_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_bin_image_dilate_square_init(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_bin_image_dilate_square_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_bin_image_dilate_square ((unsigned int)28)
unsigned int vcop_vec_bin_image_dilate_square_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_bin_image_dilate_square ((unsigned int)0)
unsigned int vcop_vec_bin_image_dilate_square_ctrl_count(void);

/***********************************************************/
#endif

