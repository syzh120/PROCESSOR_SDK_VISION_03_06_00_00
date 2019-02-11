#ifndef _TI_vcop_grayscale_morphology_kernel_h_
#define _TI_vcop_grayscale_morphology_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_grayscale_dilate_mask[20];

/* Basic Runner Function */
void vcop_grayscale_dilate_mask(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr);
/* Custom Runner Function */
void vcop_grayscale_dilate_mask_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_grayscale_dilate_mask_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_grayscale_dilate_mask_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_grayscale_dilate_mask ((unsigned int)20)
unsigned int vcop_grayscale_dilate_mask_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_grayscale_dilate_mask ((unsigned int)0)
unsigned int vcop_grayscale_dilate_mask_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_grayscale_erode_mask[20];

/* Basic Runner Function */
void vcop_grayscale_erode_mask(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr);
/* Custom Runner Function */
void vcop_grayscale_erode_mask_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_grayscale_erode_mask_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_grayscale_erode_mask_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_grayscale_erode_mask ((unsigned int)20)
unsigned int vcop_grayscale_erode_mask_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_grayscale_erode_mask ((unsigned int)0)
unsigned int vcop_grayscale_erode_mask_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_grayscale_dilate_rect[32];

/* Basic Runner Function */
void vcop_grayscale_dilate_rect(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr);
/* Custom Runner Function */
void vcop_grayscale_dilate_rect_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_grayscale_dilate_rect_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_grayscale_dilate_rect_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_grayscale_dilate_rect ((unsigned int)32)
unsigned int vcop_grayscale_dilate_rect_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_grayscale_dilate_rect ((unsigned int)0)
unsigned int vcop_grayscale_dilate_rect_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_grayscale_erode_rect[32];

/* Basic Runner Function */
void vcop_grayscale_erode_rect(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr);
/* Custom Runner Function */
void vcop_grayscale_erode_rect_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_grayscale_erode_rect_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_grayscale_erode_rect_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_grayscale_erode_rect ((unsigned int)32)
unsigned int vcop_grayscale_erode_rect_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_grayscale_erode_rect ((unsigned int)0)
unsigned int vcop_grayscale_erode_rect_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_grayscale_dilate_cross[32];

/* Basic Runner Function */
void vcop_grayscale_dilate_cross(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr);
/* Custom Runner Function */
void vcop_grayscale_dilate_cross_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_grayscale_dilate_cross_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_grayscale_dilate_cross_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_grayscale_dilate_cross ((unsigned int)32)
unsigned int vcop_grayscale_dilate_cross_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_grayscale_dilate_cross ((unsigned int)0)
unsigned int vcop_grayscale_dilate_cross_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_grayscale_erode_cross[32];

/* Basic Runner Function */
void vcop_grayscale_erode_cross(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr);
/* Custom Runner Function */
void vcop_grayscale_erode_cross_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_grayscale_erode_cross_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_grayscale_erode_cross_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_grayscale_erode_cross ((unsigned int)32)
unsigned int vcop_grayscale_erode_cross_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_grayscale_erode_cross ((unsigned int)0)
unsigned int vcop_grayscale_erode_cross_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_grayscale_morp_diff[14];

/* Basic Runner Function */
void vcop_grayscale_morp_diff(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   __vptr_uint8 data2_ptr,
   __vptr_uint8 output_ptr);
/* Custom Runner Function */
void vcop_grayscale_morp_diff_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   __vptr_uint8 data2_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_grayscale_morp_diff_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   __vptr_uint8 data2_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_grayscale_morp_diff_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_grayscale_morp_diff ((unsigned int)14)
unsigned int vcop_grayscale_morp_diff_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_grayscale_morp_diff ((unsigned int)0)
unsigned int vcop_grayscale_morp_diff_ctrl_count(void);

/***********************************************************/
#endif

