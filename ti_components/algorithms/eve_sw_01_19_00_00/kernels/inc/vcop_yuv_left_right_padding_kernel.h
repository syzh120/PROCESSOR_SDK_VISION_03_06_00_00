#ifndef _TI_vcop_yuv_left_right_padding_kernel_h_
#define _TI_vcop_yuv_left_right_padding_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_yuv_left_right_padding_u8[14];

/* Basic Runner Function */
void vcop_yuv_left_right_padding_u8(
   __vptr_uint8 in_left_A,
   __vptr_uint8 in_right_B,
   __vptr_uint8 out_left_A,
   __vptr_uint8 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride);
/* Custom Runner Function */
void vcop_yuv_left_right_padding_u8_custom(
   __vptr_uint8 in_left_A,
   __vptr_uint8 in_right_B,
   __vptr_uint8 out_left_A,
   __vptr_uint8 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_yuv_left_right_padding_u8_init(
   __vptr_uint8 in_left_A,
   __vptr_uint8 in_right_B,
   __vptr_uint8 out_left_A,
   __vptr_uint8 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_yuv_left_right_padding_u8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_yuv_left_right_padding_u8 ((unsigned int)14)
unsigned int vcop_yuv_left_right_padding_u8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_yuv_left_right_padding_u8 ((unsigned int)0)
unsigned int vcop_yuv_left_right_padding_u8_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_yuv_left_right_padding_u16[16];

/* Basic Runner Function */
void vcop_yuv_left_right_padding_u16(
   __vptr_uint16 in_left_A,
   __vptr_uint16 in_right_B,
   __vptr_uint16 out_left_A,
   __vptr_uint16 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride);
/* Custom Runner Function */
void vcop_yuv_left_right_padding_u16_custom(
   __vptr_uint16 in_left_A,
   __vptr_uint16 in_right_B,
   __vptr_uint16 out_left_A,
   __vptr_uint16 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_yuv_left_right_padding_u16_init(
   __vptr_uint16 in_left_A,
   __vptr_uint16 in_right_B,
   __vptr_uint16 out_left_A,
   __vptr_uint16 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_yuv_left_right_padding_u16_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_yuv_left_right_padding_u16 ((unsigned int)16)
unsigned int vcop_yuv_left_right_padding_u16_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_yuv_left_right_padding_u16 ((unsigned int)0)
unsigned int vcop_yuv_left_right_padding_u16_ctrl_count(void);

/***********************************************************/
#endif

