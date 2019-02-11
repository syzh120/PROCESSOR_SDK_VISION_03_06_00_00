#ifndef _TI_vcop_nxn_block_sum_kernel_h_
#define _TI_vcop_nxn_block_sum_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_nxn_sum_interleaved[62];

/* Basic Runner Function */
void vcop_nxn_sum_interleaved(
   __vptr_uint8 inPtr1,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   signed short shiftValue);
/* Custom Runner Function */
void vcop_nxn_sum_interleaved_custom(
   __vptr_uint8 inPtr1,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   signed short shiftValue,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nxn_sum_interleaved_init(
   __vptr_uint8 inPtr1,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   signed short shiftValue,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nxn_sum_interleaved_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nxn_sum_interleaved ((unsigned int)62)
unsigned int vcop_nxn_sum_interleaved_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nxn_sum_interleaved ((unsigned int)0)
unsigned int vcop_nxn_sum_interleaved_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nxn_sum_u8[66];

/* Basic Runner Function */
void vcop_nxn_sum_u8(
   __vptr_uint8 inPtr1,
   __vptr_uint8 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2);
/* Custom Runner Function */
void vcop_nxn_sum_u8_custom(
   __vptr_uint8 inPtr1,
   __vptr_uint8 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nxn_sum_u8_init(
   __vptr_uint8 inPtr1,
   __vptr_uint8 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nxn_sum_u8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nxn_sum_u8 ((unsigned int)66)
unsigned int vcop_nxn_sum_u8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nxn_sum_u8 ((unsigned int)0)
unsigned int vcop_nxn_sum_u8_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nxn_sum_u16[66];

/* Basic Runner Function */
void vcop_nxn_sum_u16(
   __vptr_uint16 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2);
/* Custom Runner Function */
void vcop_nxn_sum_u16_custom(
   __vptr_uint16 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nxn_sum_u16_init(
   __vptr_uint16 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nxn_sum_u16_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nxn_sum_u16 ((unsigned int)66)
unsigned int vcop_nxn_sum_u16_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nxn_sum_u16 ((unsigned int)0)
unsigned int vcop_nxn_sum_u16_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nxn_sum_u8_u16[66];

/* Basic Runner Function */
void vcop_nxn_sum_u8_u16(
   __vptr_uint8 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2);
/* Custom Runner Function */
void vcop_nxn_sum_u8_u16_custom(
   __vptr_uint8 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nxn_sum_u8_u16_init(
   __vptr_uint8 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nxn_sum_u8_u16_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nxn_sum_u8_u16 ((unsigned int)66)
unsigned int vcop_nxn_sum_u8_u16_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nxn_sum_u8_u16 ((unsigned int)0)
unsigned int vcop_nxn_sum_u8_u16_ctrl_count(void);

/***********************************************************/
#endif

