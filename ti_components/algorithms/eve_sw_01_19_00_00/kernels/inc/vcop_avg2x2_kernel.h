#ifndef _TI_vcop_avg2x2_kernel_h_
#define _TI_vcop_avg2x2_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_avg2x2_uchar[18];

/* Basic Runner Function */
void vcop_avg2x2_uchar(
   __vptr_uint8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output);
/* Custom Runner Function */
void vcop_avg2x2_uchar_custom(
   __vptr_uint8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_avg2x2_uchar_init(
   __vptr_uint8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_avg2x2_uchar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_avg2x2_uchar ((unsigned int)18)
unsigned int vcop_avg2x2_uchar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_avg2x2_uchar ((unsigned int)0)
unsigned int vcop_avg2x2_uchar_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_avg2x2_char[18];

/* Basic Runner Function */
void vcop_avg2x2_char(
   __vptr_int8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output);
/* Custom Runner Function */
void vcop_avg2x2_char_custom(
   __vptr_int8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_avg2x2_char_init(
   __vptr_int8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_avg2x2_char_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_avg2x2_char ((unsigned int)18)
unsigned int vcop_avg2x2_char_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_avg2x2_char ((unsigned int)0)
unsigned int vcop_avg2x2_char_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_avg2x2_ushort[18];

/* Basic Runner Function */
void vcop_avg2x2_ushort(
   __vptr_uint16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output);
/* Custom Runner Function */
void vcop_avg2x2_ushort_custom(
   __vptr_uint16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_avg2x2_ushort_init(
   __vptr_uint16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_avg2x2_ushort_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_avg2x2_ushort ((unsigned int)18)
unsigned int vcop_avg2x2_ushort_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_avg2x2_ushort ((unsigned int)0)
unsigned int vcop_avg2x2_ushort_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_avg2x2_short[18];

/* Basic Runner Function */
void vcop_avg2x2_short(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output);
/* Custom Runner Function */
void vcop_avg2x2_short_custom(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_avg2x2_short_init(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_avg2x2_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_avg2x2_short ((unsigned int)18)
unsigned int vcop_avg2x2_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_avg2x2_short ((unsigned int)0)
unsigned int vcop_avg2x2_short_ctrl_count(void);

/***********************************************************/
#endif

