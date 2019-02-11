#ifndef _TI_vcop_median_filter_mxn_u8_kernel_h_
#define _TI_vcop_median_filter_mxn_u8_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_select_kth_smallest_from_hist[56];

/* Basic Runner Function */
void vcop_select_kth_smallest_from_hist(
   __vptr_int16 blk_histo_B,
   __vptr_int16 coarse_hist_scratch_A,
   __vptr_int16 hist_scratch_C,
   __vptr_uint8 optr_A,
   unsigned short k);
/* Custom Runner Function */
void vcop_select_kth_smallest_from_hist_custom(
   __vptr_int16 blk_histo_B,
   __vptr_int16 coarse_hist_scratch_A,
   __vptr_int16 hist_scratch_C,
   __vptr_uint8 optr_A,
   unsigned short k,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_select_kth_smallest_from_hist_init(
   __vptr_int16 blk_histo_B,
   __vptr_int16 coarse_hist_scratch_A,
   __vptr_int16 hist_scratch_C,
   __vptr_uint8 optr_A,
   unsigned short k,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_select_kth_smallest_from_hist_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_select_kth_smallest_from_hist ((unsigned int)56)
unsigned int vcop_select_kth_smallest_from_hist_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_select_kth_smallest_from_hist ((unsigned int)0)
unsigned int vcop_select_kth_smallest_from_hist_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_update_block_histogram_8c[100];

/* Basic Runner Function */
void vcop_update_block_histogram_8c(
   __vptr_uint8 inp_data_A,
   __vptr_uint8 last_strip_A,
   __vptr_int16 histo_B,
   __vptr_int8 wgt_ones_C,
   __vptr_int8 wgt_delta_C,
   __vptr_int16 scratch_histo_C,
   __vptr_int16 blk_histo_B,
   unsigned int blk_wdth,
   unsigned int blk_hght,
   unsigned int blk_stride);
/* Custom Runner Function */
void vcop_update_block_histogram_8c_custom(
   __vptr_uint8 inp_data_A,
   __vptr_uint8 last_strip_A,
   __vptr_int16 histo_B,
   __vptr_int8 wgt_ones_C,
   __vptr_int8 wgt_delta_C,
   __vptr_int16 scratch_histo_C,
   __vptr_int16 blk_histo_B,
   unsigned int blk_wdth,
   unsigned int blk_hght,
   unsigned int blk_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_update_block_histogram_8c_init(
   __vptr_uint8 inp_data_A,
   __vptr_uint8 last_strip_A,
   __vptr_int16 histo_B,
   __vptr_int8 wgt_ones_C,
   __vptr_int8 wgt_delta_C,
   __vptr_int16 scratch_histo_C,
   __vptr_int16 blk_histo_B,
   unsigned int blk_wdth,
   unsigned int blk_hght,
   unsigned int blk_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_update_block_histogram_8c_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_update_block_histogram_8c ((unsigned int)100)
unsigned int vcop_update_block_histogram_8c_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_update_block_histogram_8c ((unsigned int)0)
unsigned int vcop_update_block_histogram_8c_ctrl_count(void);

/***********************************************************/
#endif

