#ifndef _TI_vcop_vec_array_l1_distance_kernel_h_
#define _TI_vcop_vec_array_l1_distance_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_array_l1_distance[16];

/* Basic Runner Function */
void vcop_vec_array_l1_distance(
   __vptr_int16 a,
   __vptr_int16 b,
   __vptr_uint32 c,
   int array_len);
/* Custom Runner Function */
void vcop_vec_array_l1_distance_custom(
   __vptr_int16 a,
   __vptr_int16 b,
   __vptr_uint32 c,
   int array_len,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_array_l1_distance_init(
   __vptr_int16 a,
   __vptr_int16 b,
   __vptr_uint32 c,
   int array_len,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_array_l1_distance_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_array_l1_distance ((unsigned int)16)
unsigned int vcop_vec_array_l1_distance_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_array_l1_distance ((unsigned int)0)
unsigned int vcop_vec_array_l1_distance_ctrl_count(void);

/***********************************************************/
#endif

