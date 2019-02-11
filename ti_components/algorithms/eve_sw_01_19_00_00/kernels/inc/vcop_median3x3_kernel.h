#ifndef _TI_vcop_median3x3_kernel_h_
#define _TI_vcop_median3x3_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_median3x3_char[62];

/* Basic Runner Function */
void vcop_median3x3_char(
   __vptr_int8 in,
   __vptr_int8 out,
   __vptr_int8 scratch1,
   __vptr_int8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk);
/* Custom Runner Function */
void vcop_median3x3_char_custom(
   __vptr_int8 in,
   __vptr_int8 out,
   __vptr_int8 scratch1,
   __vptr_int8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median3x3_char_init(
   __vptr_int8 in,
   __vptr_int8 out,
   __vptr_int8 scratch1,
   __vptr_int8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median3x3_char_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median3x3_char ((unsigned int)62)
unsigned int vcop_median3x3_char_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median3x3_char ((unsigned int)0)
unsigned int vcop_median3x3_char_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_median3x3_uchar[62];

/* Basic Runner Function */
void vcop_median3x3_uchar(
   __vptr_uint8 in,
   __vptr_uint8 out,
   __vptr_uint8 scratch1,
   __vptr_uint8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk);
/* Custom Runner Function */
void vcop_median3x3_uchar_custom(
   __vptr_uint8 in,
   __vptr_uint8 out,
   __vptr_uint8 scratch1,
   __vptr_uint8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_median3x3_uchar_init(
   __vptr_uint8 in,
   __vptr_uint8 out,
   __vptr_uint8 scratch1,
   __vptr_uint8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_median3x3_uchar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_median3x3_uchar ((unsigned int)62)
unsigned int vcop_median3x3_uchar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_median3x3_uchar ((unsigned int)0)
unsigned int vcop_median3x3_uchar_ctrl_count(void);

/***********************************************************/
#endif

