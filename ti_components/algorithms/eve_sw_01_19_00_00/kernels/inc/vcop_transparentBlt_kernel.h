#ifndef _TI_vcop_transparentBlt_kernel_h_
#define _TI_vcop_transparentBlt_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_transparentBlt_ushort_ushort[16];

/* Basic Runner Function */
void vcop_transparentBlt_ushort_ushort(
   __vptr_uint16 inrgb555_ptr,
   __vptr_uint16 backrgb555_ptr,
   unsigned short transparentClr,
   unsigned short in1_w,
   unsigned short in1_h,
   unsigned short in2_w,
   unsigned short in2_h,
   unsigned short comp_w,
   unsigned short comp_h,
   unsigned short out_w,
   unsigned short out_h,
   __vptr_uint16 outptr);
/* Custom Runner Function */
void vcop_transparentBlt_ushort_ushort_custom(
   __vptr_uint16 inrgb555_ptr,
   __vptr_uint16 backrgb555_ptr,
   unsigned short transparentClr,
   unsigned short in1_w,
   unsigned short in1_h,
   unsigned short in2_w,
   unsigned short in2_h,
   unsigned short comp_w,
   unsigned short comp_h,
   unsigned short out_w,
   unsigned short out_h,
   __vptr_uint16 outptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_transparentBlt_ushort_ushort_init(
   __vptr_uint16 inrgb555_ptr,
   __vptr_uint16 backrgb555_ptr,
   unsigned short transparentClr,
   unsigned short in1_w,
   unsigned short in1_h,
   unsigned short in2_w,
   unsigned short in2_h,
   unsigned short comp_w,
   unsigned short comp_h,
   unsigned short out_w,
   unsigned short out_h,
   __vptr_uint16 outptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_transparentBlt_ushort_ushort_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_transparentBlt_ushort_ushort ((unsigned int)16)
unsigned int vcop_transparentBlt_ushort_ushort_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_transparentBlt_ushort_ushort ((unsigned int)0)
unsigned int vcop_transparentBlt_ushort_ushort_ctrl_count(void);

/***********************************************************/
#endif

