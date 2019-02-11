#ifndef _TI_sample_vcop_array_add_uns_short_kernel_h_
#define _TI_sample_vcop_array_add_uns_short_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_sample_eve_array_add_uns_short[12];

/* Basic Runner Function */
void sample_eve_array_add_uns_short(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 in2_ptr,
   __vptr_uint16 optr,
   unsigned short width,
   unsigned short height);
/* Custom Runner Function */
void sample_eve_array_add_uns_short_custom(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 in2_ptr,
   __vptr_uint16 optr,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int sample_eve_array_add_uns_short_init(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 in2_ptr,
   __vptr_uint16 optr,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void sample_eve_array_add_uns_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_sample_eve_array_add_uns_short ((unsigned int)12)
unsigned int sample_eve_array_add_uns_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_sample_eve_array_add_uns_short ((unsigned int)0)
unsigned int sample_eve_array_add_uns_short_ctrl_count(void);

/***********************************************************/
#endif

