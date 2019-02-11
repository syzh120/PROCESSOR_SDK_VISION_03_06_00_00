#ifndef _TI_vcop_vec_bin_image_dilate_cross_kernel_h_
#define _TI_vcop_vec_bin_image_dilate_cross_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_bin_image_dilate_cross[28];

/* Basic Runner Function */
void vcop_vec_bin_image_dilate_cross(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height);
/* Custom Runner Function */
void vcop_vec_bin_image_dilate_cross_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_bin_image_dilate_cross_init(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_bin_image_dilate_cross_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_bin_image_dilate_cross ((unsigned int)28)
unsigned int vcop_vec_bin_image_dilate_cross_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_bin_image_dilate_cross ((unsigned int)0)
unsigned int vcop_vec_bin_image_dilate_cross_ctrl_count(void);

/***********************************************************/
#endif

