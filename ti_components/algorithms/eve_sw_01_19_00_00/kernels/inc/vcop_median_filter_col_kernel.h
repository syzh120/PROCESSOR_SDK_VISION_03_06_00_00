#ifndef _TI_vcop_median_filter_col_kernel_h_
#define _TI_vcop_median_filter_col_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_median_3tap_filt_col_short[14];

/* Basic Runner Function */
void vcop_median_3tap_filt_col_short(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   signed short input_width,
   signed short input_height,
   signed short output_width,
   signed short output_height,
   signed short compute_width,
   signed short compute_height,
   signed short median_size,
   signed short input_type,
   signed short output_type);
/* Custom Runner Function */
void vcop_median_3tap_filt_col_short_custom(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   signed short input_width,
   signed short input_height,
   signed short output_width,
   signed short output_height,
   signed short compute_width,
   signed short compute_height,
   signed short median_size,
   signed short input_type,
   signed short output_type,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median_3tap_filt_col_short_init(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   signed short input_width,
   signed short input_height,
   signed short output_width,
   signed short output_height,
   signed short compute_width,
   signed short compute_height,
   signed short median_size,
   signed short input_type,
   signed short output_type,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median_3tap_filt_col_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median_3tap_filt_col_short ((unsigned int)14)
unsigned int vcop_median_3tap_filt_col_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median_3tap_filt_col_short ((unsigned int)0)
unsigned int vcop_median_3tap_filt_col_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_median_5tap_filt_col_short[18];

/* Basic Runner Function */
void vcop_median_5tap_filt_col_short(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   signed short input_width,
   signed short input_height,
   signed short output_width,
   signed short output_height,
   signed short compute_width,
   signed short compute_height,
   signed short median_size,
   signed short input_type,
   signed short output_type);
/* Custom Runner Function */
void vcop_median_5tap_filt_col_short_custom(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   signed short input_width,
   signed short input_height,
   signed short output_width,
   signed short output_height,
   signed short compute_width,
   signed short compute_height,
   signed short median_size,
   signed short input_type,
   signed short output_type,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median_5tap_filt_col_short_init(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   signed short input_width,
   signed short input_height,
   signed short output_width,
   signed short output_height,
   signed short compute_width,
   signed short compute_height,
   signed short median_size,
   signed short input_type,
   signed short output_type,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median_5tap_filt_col_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median_5tap_filt_col_short ((unsigned int)18)
unsigned int vcop_median_5tap_filt_col_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median_5tap_filt_col_short ((unsigned int)0)
unsigned int vcop_median_5tap_filt_col_short_ctrl_count(void);

/***********************************************************/
#endif

