#ifndef _TI_vcop_bilateralFilter_kernel_h_
#define _TI_vcop_bilateralFilter_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_img_bilateralFilter[100];

/* Basic Runner Function */
void vcop_img_bilateralFilter(
   __vptr_uint8 input_ptr,
   __vptr_uint8 output_ptr,
   __vptr_uint8 diff_ptr,
   __vptr_uint16 G_pq_ptr,
   __vptr_uint32 W_p_ptr,
   __vptr_uint32 BF_p_ptr,
   __vptr_uint16 LUT_RANGE_8TBL,
   __vptr_uint16 LUT_SPACE_TBL,
   int blk_width,
   int blk_height,
   int blk_stride,
   int horz_pad_size,
   int vert_pad_size,
   unsigned int Qpoint_tbl,
   unsigned int Qpoint_div,
   unsigned char pixel_format);
/* Custom Runner Function */
void vcop_img_bilateralFilter_custom(
   __vptr_uint8 input_ptr,
   __vptr_uint8 output_ptr,
   __vptr_uint8 diff_ptr,
   __vptr_uint16 G_pq_ptr,
   __vptr_uint32 W_p_ptr,
   __vptr_uint32 BF_p_ptr,
   __vptr_uint16 LUT_RANGE_8TBL,
   __vptr_uint16 LUT_SPACE_TBL,
   int blk_width,
   int blk_height,
   int blk_stride,
   int horz_pad_size,
   int vert_pad_size,
   unsigned int Qpoint_tbl,
   unsigned int Qpoint_div,
   unsigned char pixel_format,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_img_bilateralFilter_init(
   __vptr_uint8 input_ptr,
   __vptr_uint8 output_ptr,
   __vptr_uint8 diff_ptr,
   __vptr_uint16 G_pq_ptr,
   __vptr_uint32 W_p_ptr,
   __vptr_uint32 BF_p_ptr,
   __vptr_uint16 LUT_RANGE_8TBL,
   __vptr_uint16 LUT_SPACE_TBL,
   int blk_width,
   int blk_height,
   int blk_stride,
   int horz_pad_size,
   int vert_pad_size,
   unsigned int Qpoint_tbl,
   unsigned int Qpoint_div,
   unsigned char pixel_format,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_img_bilateralFilter_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_img_bilateralFilter ((unsigned int)100)
unsigned int vcop_img_bilateralFilter_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_img_bilateralFilter ((unsigned int)0)
unsigned int vcop_img_bilateralFilter_ctrl_count(void);

/***********************************************************/
#endif

