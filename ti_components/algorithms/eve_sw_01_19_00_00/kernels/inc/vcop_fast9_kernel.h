#ifndef _TI_vcop_fast9_kernel_h_
#define _TI_vcop_fast9_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fast9[184];

/* Basic Runner Function */
void vcop_fast9(
   __vptr_uint8 vec1,
   __vptr_uint8 out_0_ptr,
   __vptr_uint8 out_1_ptr,
   __vptr_uint16 out_4_ptr,
   __vptr_uint8 Out,
   signed char Thr,
   unsigned int pitch,
   unsigned int in_w,
   unsigned int in_h);
/* Custom Runner Function */
void vcop_fast9_custom(
   __vptr_uint8 vec1,
   __vptr_uint8 out_0_ptr,
   __vptr_uint8 out_1_ptr,
   __vptr_uint16 out_4_ptr,
   __vptr_uint8 Out,
   signed char Thr,
   unsigned int pitch,
   unsigned int in_w,
   unsigned int in_h,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fast9_init(
   __vptr_uint8 vec1,
   __vptr_uint8 out_0_ptr,
   __vptr_uint8 out_1_ptr,
   __vptr_uint16 out_4_ptr,
   __vptr_uint8 Out,
   signed char Thr,
   unsigned int pitch,
   unsigned int in_w,
   unsigned int in_h,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fast9_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fast9 ((unsigned int)184)
unsigned int vcop_fast9_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fast9 ((unsigned int)0)
unsigned int vcop_fast9_ctrl_count(void);

/***********************************************************/
#endif

