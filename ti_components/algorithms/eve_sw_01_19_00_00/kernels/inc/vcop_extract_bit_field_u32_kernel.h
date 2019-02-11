#ifndef _TI_vcop_extract_bit_field_u32_kernel_h_
#define _TI_vcop_extract_bit_field_u32_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_extract_bit_field_u32[14];

/* Basic Runner Function */
void vcop_extract_bit_field_u32(
   __vptr_uint32 inArray_A,
   unsigned short length,
   unsigned int bit_mask,
   unsigned char shift,
   __vptr_uint8 outList_B);
/* Custom Runner Function */
void vcop_extract_bit_field_u32_custom(
   __vptr_uint32 inArray_A,
   unsigned short length,
   unsigned int bit_mask,
   unsigned char shift,
   __vptr_uint8 outList_B,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_extract_bit_field_u32_init(
   __vptr_uint32 inArray_A,
   unsigned short length,
   unsigned int bit_mask,
   unsigned char shift,
   __vptr_uint8 outList_B,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_extract_bit_field_u32_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_extract_bit_field_u32 ((unsigned int)14)
unsigned int vcop_extract_bit_field_u32_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_extract_bit_field_u32 ((unsigned int)0)
unsigned int vcop_extract_bit_field_u32_ctrl_count(void);

/***********************************************************/
#endif

