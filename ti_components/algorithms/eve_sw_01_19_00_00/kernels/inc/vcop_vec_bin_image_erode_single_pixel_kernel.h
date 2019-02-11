#ifndef _TI_vcop_vec_bin_image_erode_single_pixel_kernel_h_
#define _TI_vcop_vec_bin_image_erode_single_pixel_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_bin_image_erode_single_pixel[28];

/* Basic Runner Function */
void vcop_vec_bin_image_erode_single_pixel(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   int cols,
   int pitch,
   int height);
/* Custom Runner Function */
void vcop_vec_bin_image_erode_single_pixel_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   int cols,
   int pitch,
   int height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_bin_image_erode_single_pixel_init(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   int cols,
   int pitch,
   int height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_bin_image_erode_single_pixel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_bin_image_erode_single_pixel ((unsigned int)28)
unsigned int vcop_vec_bin_image_erode_single_pixel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_bin_image_erode_single_pixel ((unsigned int)0)
unsigned int vcop_vec_bin_image_erode_single_pixel_ctrl_count(void);

/***********************************************************/
#endif

