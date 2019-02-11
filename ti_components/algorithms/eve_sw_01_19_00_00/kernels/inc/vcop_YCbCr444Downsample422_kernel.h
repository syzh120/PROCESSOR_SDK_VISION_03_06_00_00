#ifndef _TI_vcop_YCbCr444Downsample422_kernel_h_
#define _TI_vcop_YCbCr444Downsample422_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_YCbCr444_Downsample422_char[34];

/* Basic Runner Function */
void vcop_YCbCr444_Downsample422_char(
   __vptr_uint32 YCbCr_char,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char);
/* Custom Runner Function */
void vcop_YCbCr444_Downsample422_char_custom(
   __vptr_uint32 YCbCr_char,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_YCbCr444_Downsample422_char_init(
   __vptr_uint32 YCbCr_char,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_YCbCr444_Downsample422_char_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_YCbCr444_Downsample422_char ((unsigned int)34)
unsigned int vcop_YCbCr444_Downsample422_char_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_YCbCr444_Downsample422_char ((unsigned int)0)
unsigned int vcop_YCbCr444_Downsample422_char_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_YCbCr444_Downsample422_short[34];

/* Basic Runner Function */
void vcop_YCbCr444_Downsample422_short(
   __vptr_uint32 YCbCr_short,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short);
/* Custom Runner Function */
void vcop_YCbCr444_Downsample422_short_custom(
   __vptr_uint32 YCbCr_short,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_YCbCr444_Downsample422_short_init(
   __vptr_uint32 YCbCr_short,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_YCbCr444_Downsample422_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_YCbCr444_Downsample422_short ((unsigned int)34)
unsigned int vcop_YCbCr444_Downsample422_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_YCbCr444_Downsample422_short ((unsigned int)0)
unsigned int vcop_YCbCr444_Downsample422_short_ctrl_count(void);

/***********************************************************/
#endif

