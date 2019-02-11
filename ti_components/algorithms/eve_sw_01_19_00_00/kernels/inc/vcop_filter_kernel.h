#ifndef _TI_vcop_filter_kernel_h_
#define _TI_vcop_filter_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_uchar_char_uchar[22];

/* Basic Runner Function */
void vcop_filter_uchar_char_uchar(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_uchar_char_uchar_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_uchar_char_uchar_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_uchar_char_uchar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_uchar_char_uchar ((unsigned int)22)
unsigned int vcop_filter_uchar_char_uchar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_uchar_char_uchar ((unsigned int)0)
unsigned int vcop_filter_uchar_char_uchar_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_uchar_char_char[22];

/* Basic Runner Function */
void vcop_filter_uchar_char_char(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_uchar_char_char_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_uchar_char_char_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_uchar_char_char_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_uchar_char_char ((unsigned int)22)
unsigned int vcop_filter_uchar_char_char_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_uchar_char_char ((unsigned int)0)
unsigned int vcop_filter_uchar_char_char_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_uchar_char_short[22];

/* Basic Runner Function */
void vcop_filter_uchar_char_short(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_uchar_char_short_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_uchar_char_short_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_uchar_char_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_uchar_char_short ((unsigned int)22)
unsigned int vcop_filter_uchar_char_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_uchar_char_short ((unsigned int)0)
unsigned int vcop_filter_uchar_char_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_ushort_short_short[22];

/* Basic Runner Function */
void vcop_filter_ushort_short_short(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_ushort_short_short_custom(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_ushort_short_short_init(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_ushort_short_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_ushort_short_short ((unsigned int)22)
unsigned int vcop_filter_ushort_short_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_ushort_short_short ((unsigned int)0)
unsigned int vcop_filter_ushort_short_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_short_short_short[22];

/* Basic Runner Function */
void vcop_filter_short_short_short(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_short_short_short_custom(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_short_short_short_init(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_short_short_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_short_short_short ((unsigned int)22)
unsigned int vcop_filter_short_short_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_short_short_short ((unsigned int)0)
unsigned int vcop_filter_short_short_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_ushort_ushort_short[22];

/* Basic Runner Function */
void vcop_filter_ushort_ushort_short(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_ushort_ushort_short_custom(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_ushort_ushort_short_init(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_ushort_ushort_short_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_ushort_ushort_short ((unsigned int)22)
unsigned int vcop_filter_ushort_ushort_short_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_ushort_ushort_short ((unsigned int)0)
unsigned int vcop_filter_ushort_ushort_short_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_filter_ushort_short_int[22];

/* Basic Runner Function */
void vcop_filter_ushort_short_int(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift);
/* Custom Runner Function */
void vcop_filter_ushort_short_int_custom(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_filter_ushort_short_int_init(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_filter_ushort_short_int_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_filter_ushort_short_int ((unsigned int)22)
unsigned int vcop_filter_ushort_short_int_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_filter_ushort_short_int ((unsigned int)0)
unsigned int vcop_filter_ushort_short_int_ctrl_count(void);

/***********************************************************/
#endif

