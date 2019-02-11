#ifndef _TI_vcop_median_filter_row_kernel_h_
#define _TI_vcop_median_filter_row_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_median_3tap_filt_row_char[16];

/* Basic Runner Function */
void vcop_median_3tap_filt_row_char(
   __vptr_int8 input_ptr,
   __vptr_int8 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type);
/* Custom Runner Function */
void vcop_median_3tap_filt_row_char_custom(
   __vptr_int8 input_ptr,
   __vptr_int8 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median_3tap_filt_row_char_init(
   __vptr_int8 input_ptr,
   __vptr_int8 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median_3tap_filt_row_char_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median_3tap_filt_row_char ((unsigned int)16)
unsigned int vcop_median_3tap_filt_row_char_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median_3tap_filt_row_char ((unsigned int)0)
unsigned int vcop_median_3tap_filt_row_char_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_median_3tap_filt_row_short[24];

/* Basic Runner Function */
void vcop_median_3tap_filt_row_short(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type);
/* Custom Runner Function */
void vcop_median_3tap_filt_row_short_custom(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median_3tap_filt_row_short_init(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median_3tap_filt_row_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median_3tap_filt_row_short ((unsigned int)24)
unsigned int vcop_median_3tap_filt_row_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median_3tap_filt_row_short ((unsigned int)0)
unsigned int vcop_median_3tap_filt_row_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_median_5tap_filt_row_char[20];

/* Basic Runner Function */
void vcop_median_5tap_filt_row_char(
   __vptr_int8 input_ptr,
   __vptr_int8 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type);
/* Custom Runner Function */
void vcop_median_5tap_filt_row_char_custom(
   __vptr_int8 input_ptr,
   __vptr_int8 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median_5tap_filt_row_char_init(
   __vptr_int8 input_ptr,
   __vptr_int8 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median_5tap_filt_row_char_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median_5tap_filt_row_char ((unsigned int)20)
unsigned int vcop_median_5tap_filt_row_char_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median_5tap_filt_row_char ((unsigned int)0)
unsigned int vcop_median_5tap_filt_row_char_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_median_5tap_filt_row_short[20];

/* Basic Runner Function */
void vcop_median_5tap_filt_row_short(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type);
/* Custom Runner Function */
void vcop_median_5tap_filt_row_short_custom(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median_5tap_filt_row_short_init(
   __vptr_int16 input_ptr,
   __vptr_int16 output_ptr,
   unsigned short input_width,
   unsigned short input_height,
   unsigned short output_width,
   unsigned short output_height,
   unsigned short compute_width,
   unsigned short compute_height,
   unsigned short median_size,
   unsigned short input_type,
   unsigned short output_type,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median_5tap_filt_row_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median_5tap_filt_row_short ((unsigned int)20)
unsigned int vcop_median_5tap_filt_row_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median_5tap_filt_row_short ((unsigned int)0)
unsigned int vcop_median_5tap_filt_row_short_ctrl_count(void);

/***********************************************************/
#endif

